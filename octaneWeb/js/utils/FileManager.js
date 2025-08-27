/**
 * File Manager Utility
 * Handles file operations and drag-and-drop
 */

class FileManager {
    constructor(octaneClient = null) {
        this.supportedFormats = {
            scene: ['.orbx'],  // Only support .orbx files for Octane projects
            model: ['.obj/.fbx/.dae/.3ds/.ply/.stl'],
            texture: ['.jpg/.jpeg/.png/.tiff/.tga/.exr/.hdr'],
            material: ['.mtl/.mat']
        };
        this.client = octaneClient;

        this.dropZones = new Set();
        this.isInitialized = false;
        
        // Bind methods
        this.handleDragOver = this.handleDragOver.bind(this);
        this.handleDragLeave = this.handleDragLeave.bind(this);
        this.handleDrop = this.handleDrop.bind(this);
    }
    
    initialize() {
        if (this.isInitialized) return;
        
        this.setupGlobalDropZone();
        this.isInitialized = true;
        
        console.log('File manager initialized');
    }
    
    setupGlobalDropZone() {
        // Make entire document a drop zone
        document.addEventListener('dragover', this.handleDragOver);
        document.addEventListener('dragleave', this.handleDragLeave);
        document.addEventListener('drop', this.handleDrop);
        
        // Prevent default drag behaviors
        document.addEventListener('dragenter', (e) => e.preventDefault());
    }
    
    handleDragOver(e) {
        e.preventDefault();
        e.dataTransfer.dropEffect = 'copy';
        
        // Add visual feedback
        document.body.classList.add('drag-over');
        
        // Show drop indicator
        this.showDropIndicator(e);
    }
    
    handleDragLeave(e) {
        // Only remove if leaving the document
        if (e.clientX === 0 && e.clientY === 0) {
            document.body.classList.remove('drag-over');
            this.hideDropIndicator();
        }
    }
    
    handleDrop(e) {
        e.preventDefault();
        
        document.body.classList.remove('drag-over');
        this.hideDropIndicator();
        
        const files = Array.from(e.dataTransfer.files);
        if (files.length > 0) {
            this.processFiles(files);
        }
    }
    
    showDropIndicator(e) {
        let indicator = document.getElementById('drop-indicator');
        
        if (!indicator) {
            indicator = document.createElement('div');
            indicator.id = 'drop-indicator';
            indicator.className = 'drop-indicator';
            indicator.innerHTML = `
                <div class="drop-indicator-content">
                    <div class="drop-indicator-icon">📁</div>
                    <div class="drop-indicator-text">Drop files here</div>
                    <div class="drop-indicator-formats">
                        Supported: .orbx (Octane projects), .obj, .fbx, .jpg, .png, .exr, .hdr
                    </div>
                </div>
            `;
            document.body.appendChild(indicator);
        }
        
        indicator.style.display = 'flex';
    }
    
    hideDropIndicator() {
        const indicator = document.getElementById('drop-indicator');
        if (indicator) {
            indicator.style.display = 'none';
        }
    }
    
    async processFiles(files) {
        const results = [];
        
        for (const file of files) {
            try {
                const result = await this.processFile(file);
                results.push(result);
            } catch (error) {
                console.error(`Failed to process file ${file.name}:`, error);
                results.push({ file, success: false, error: error.message });
            }
        }
        
        // Emit results
        this.emitFileProcessed(results);
        
        return results;
    }
    
    async processFile(file) {
        const fileType = this.getFileType(file.name);
        const fileData = await this.readFile(file);
        
        const result = {
            file,
            name: file.name,
            size: file.size,
            type: fileType,
            data: fileData,
            success: true
        };
        
        // Process based on file type
        switch (fileType) {
            case 'scene':
                await this.processSceneFile(result);
                break;
            case 'model':
                await this.processModelFile(result);
                break;
            case 'texture':
                await this.processTextureFile(result);
                break;
            case 'material':
                await this.processMaterialFile(result);
                break;
            default:
                throw new Error(`Unsupported file type: ${fileType}`);
        }
        
        return result;
    }
    
    getFileType(filename) {
        const ext = this.getFileExtension(filename);
        
        for (const [type, extensions] of Object.entries(this.supportedFormats)) {
            if (extensions.includes(ext)) {
                return type;
            }
        }
        
        return 'unknown';
    }
    
    getFileExtension(filename) {
        return filename.toLowerCase().substring(filename.lastIndexOf('.'));
    }
    
    async readFile(file) {
        return new Promise((resolve, reject) => {
            const reader = new FileReader();
            
            reader.onload = (e) => resolve(e.target.result);
            reader.onerror = (e) => reject(new Error('Failed to read file'));
            
            // Read as appropriate type
            const ext = this.getFileExtension(file.name);
            if (['.jpg/.jpeg/.png/.tiff/.tga'].includes(ext)) {
                reader.readAsDataURL(file);
            } else {
                reader.readAsText(file);
            }
        });
    }
    
    async processSceneFile(result) {
        console.log('Processing scene file:', result.name);
        
        if (result.name.endsWith('.orbx')) {
            // Handle ORBX files - load via gRPC
            result.metadata = { type: 'orbx', version: '1.0' };
            
            // Attempt to load the project via gRPC if we have a client
            if (this.client && this.client.connected) {
                try {
                    console.log('Loading ORBX project via gRPC:', result.file.path || result.name);
                    
                    // Use the file path if available, otherwise use the name
                    const projectPath = result.file.path || result.name;
                    
                    const loadResult = await this.loadOrbxProject(projectPath);
                    result.loadResult = loadResult;
                    result.metadata.loaded = loadResult.success;
                    
                    if (loadResult.success) {
                        console.log('ORBX project loaded successfully');
                    } else {
                        console.warn(' ORBX project load failed:', loadResult.error);
                    }
                } catch (error) {
                    console.error('❌ Failed to load ORBX project:', error);
                    result.loadResult = { success: false, error: error.message };
                    result.metadata.loaded = false;
                }
            } else {
                console.warn(' Octane client not connected - ORBX file processed but not loaded');
                result.metadata.loaded = false;
                result.loadResult = { success: false, error: 'Octane client not connected' };
            }
        }
    }
    
    async loadOrbxProject(projectPath) {
        /**
         * Load ORBX project via gRPC ApiProjectManager.loadProject()
         */
        try {
            if (!this.client) {
                throw new Error('Octane client not available');
            }
            
            // Make gRPC call to load project
            const response = await this.client.makeGrpcCall('ApiProjectManager/loadProject', {
                projectPath: projectPath
            });
            
            if (response.success && response.data) {
                return {
                    success: response.data.success,
                    callbackId: response.data.callbackId,
                    projectPath: projectPath
                };
            } else {
                throw new Error(response.error || 'Load project request failed');
            }
            
        } catch (error) {
            console.error('Failed to load ORBX project:', error);
            return {
                success: false,
                error: error.message,
                projectPath: projectPath
            };
        }
    }
    
    async processModelFile(result) {
        console.log('Processing model file:', result.name);
        
        const ext = this.getFileExtension(result.name);
        result.metadata = {
            type: ext.substring(1), // Remove dot
            vertices: 0, // TODO: Parse and count
            faces: 0     // TODO: Parse and count
        };
        
        // TODO: Parse model data based on format
        if (ext === '.obj') {
            result.parsed = this.parseOBJ(result.data);
        }
    }
    
    async processTextureFile(result) {
        console.log('Processing texture file:', result.name);
        
        // Create image element to get dimensions
        if (result.data.startsWith('data:image')) {
            const img = new Image();
            
            await new Promise((resolve, reject) => {
                img.onload = () => {
                    result.metadata = {
                        width: img.width,
                        height: img.height,
                        format: this.getFileExtension(result.name).substring(1)
                    };
                    resolve();
                };
                img.onerror = reject;
                img.src = result.data;
            });
        }
    }
    
    async processMaterialFile(result) {
        console.log('Processing material file:', result.name);
        
        if (result.name.endsWith('.mtl')) {
            result.parsed = this.parseMTL(result.data);
            result.metadata = {
                type: 'mtl',
                materials: Object.keys(result.parsed).length
            };
        }
    }
    
    parseOBJ(data) {
        const vertices = [];
        const normals = [];
        const texCoords = [];
        const faces = [];
        
        const lines = data.split('\n');
        
        for (const line of lines) {
            const parts = line.trim().split(/\s+/);
            const type = parts[0];
            
            switch (type) {
                case 'v':
                    vertices.push([
                        parseFloat(parts[1]),
                        parseFloat(parts[2]),
                        parseFloat(parts[3])
                    ]);
                    break;
                case 'vn':
                    normals.push([
                        parseFloat(parts[1]),
                        parseFloat(parts[2]),
                        parseFloat(parts[3])
                    ]);
                    break;
                case 'vt':
                    texCoords.push([
                        parseFloat(parts[1]),
                        parseFloat(parts[2])
                    ]);
                    break;
                case 'f':
                    const face = [];
                    for (let i = 1; i < parts.length; i++) {
                        const indices = parts[i].split('/');
                        face.push({
                            vertex: parseInt(indices[0]) - 1,
                            texCoord: indices[1] ? parseInt(indices[1]) - 1 : null,
                            normal: indices[2] ? parseInt(indices[2]) - 1 : null
                        });
                    }
                    faces.push(face);
                    break;
            }
        }
        
        return { vertices, normals, texCoords, faces };
    }
    
    parseMTL(data) {
        const materials = {};
        let currentMaterial = null;
        
        const lines = data.split('\n');
        
        for (const line of lines) {
            const parts = line.trim().split(/\s+/);
            const type = parts[0];
            
            switch (type) {
                case 'newmtl':
                    currentMaterial = parts[1];
                    materials[currentMaterial] = {};
                    break;
                case 'Ka':
                    if (currentMaterial) {
                        materials[currentMaterial].ambient = [
                            parseFloat(parts[1]),
                            parseFloat(parts[2]),
                            parseFloat(parts[3])
                        ];
                    }
                    break;
                case 'Kd':
                    if (currentMaterial) {
                        materials[currentMaterial].diffuse = [
                            parseFloat(parts[1]),
                            parseFloat(parts[2]),
                            parseFloat(parts[3])
                        ];
                    }
                    break;
                case 'Ks':
                    if (currentMaterial) {
                        materials[currentMaterial].specular = [
                            parseFloat(parts[1]),
                            parseFloat(parts[2]),
                            parseFloat(parts[3])
                        ];
                    }
                    break;
                case 'Ns':
                    if (currentMaterial) {
                        materials[currentMaterial].shininess = parseFloat(parts[1]);
                    }
                    break;
                case 'map_Kd':
                    if (currentMaterial) {
                        materials[currentMaterial].diffuseMap = parts[1];
                    }
                    break;
            }
        }
        
        return materials;
    }
    
    async openFileDialog(options = {}) {
        const {
            accept = '*/*',
            multiple = false,
            directory = false
        } = options;
        
        return new Promise((resolve, reject) => {
            const input = document.createElement('input');
            input.type = 'file';
            input.accept = accept;
            input.multiple = multiple;
            
            if (directory) {
                input.webkitdirectory = true;
            }
            
            input.onchange = async (e) => {
                const files = Array.from(e.target.files);
                if (files.length > 0) {
                    try {
                        const results = await this.processFiles(files);
                        resolve(results);
                    } catch (error) {
                        reject(error);
                    }
                } else {
                    resolve([]);
                }
            };
            
            input.oncancel = () => resolve([]);
            
            input.click();
        });
    }
    
    async saveFile(filename, data, mimeType = 'application/octet-stream') {
        const blob = new Blob([data], { type: mimeType });
        const url = URL.createObjectURL(blob);
        
        const a = document.createElement('a');
        a.href = url;
        a.download = filename;
        a.style.display = 'none';
        
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
        
        URL.revokeObjectURL(url);
    }
    
    emitFileProcessed(results) {
        const event = new CustomEvent('filesProcessed', {
            detail: { results }
        });
        document.dispatchEvent(event);
    }
    
    addDropZone(element, callback) {
        this.dropZones.add({ element, callback });
        
        element.addEventListener('dragover', (e) => {
            e.preventDefault();
            e.stopPropagation();
            element.classList.add('drop-zone-active');
        });
        
        element.addEventListener('dragleave', (e) => {
            e.preventDefault();
            e.stopPropagation();
            element.classList.remove('drop-zone-active');
        });
        
        element.addEventListener('drop', async (e) => {
            e.preventDefault();
            e.stopPropagation();
            element.classList.remove('drop-zone-active');
            
            const files = Array.from(e.dataTransfer.files);
            if (files.length > 0) {
                const results = await this.processFiles(files);
                callback(results);
            }
        });
    }
    
    removeDropZone(element) {
        this.dropZones.forEach(zone => {
            if (zone.element === element) {
                this.dropZones.delete(zone);
            }
        });
    }
    
    destroy() {
        // Remove global event listeners
        document.removeEventListener('dragover', this.handleDragOver);
        document.removeEventListener('dragleave', this.handleDragLeave);
        document.removeEventListener('drop', this.handleDrop);
        
        // Clear drop zones
        this.dropZones.clear();
        
        // Remove drop indicator
        const indicator = document.getElementById('drop-indicator');
        if (indicator) {
            indicator.remove();
        }
        
        this.isInitialized = false;
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = FileManager;
} else if (typeof window !== 'undefined') {
    window.FileManager = FileManager;
}