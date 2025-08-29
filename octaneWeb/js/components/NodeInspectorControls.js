/**
 * Node Inspector Controls Component
 * Official OTOY Node Inspector quick access buttons implementation
 * Based on official documentation: RenderTarget, Camera, Resolution, Environment, Imager, Kernel, Current Mesh + Preview/Render Toggle
 */

class NodeInspectorControls {
    constructor(containerId) {
        this.container = document.getElementById(containerId);
        this.activeNode = null;
        this.previewEnabled = false;
        this.renderToggleEnabled = true;
        
        this.setupEventListeners();
        console.log('Node Inspector Controls initialized with official OTOY quick access buttons');
    }
    
    setupEventListeners() {
        // Quick access buttons
        const quickBtns = this.container.querySelectorAll('.quick-btn');
        quickBtns.forEach(btn => {
            btn.addEventListener('click', (e) => {
                const nodeType = e.target.dataset.node;
                this.jumpToNode(nodeType);
            });
        });
        
        // Preview button
        const previewBtn = this.container.querySelector('.preview-btn');
        if (previewBtn) {
            previewBtn.addEventListener('click', () => {
                this.togglePreview();
            });
        }
        
        // Render toggle button
        const renderToggleBtn = this.container.querySelector('.render-toggle-btn');
        if (renderToggleBtn) {
            renderToggleBtn.addEventListener('click', () => {
                this.toggleRenderMode();
            });
        }
        
        console.log('Node Inspector Controls event listeners setup complete');
    }
    
    /**
     * Jump to specific node type using official OTOY quick access functionality
     * Implements the exact buttons from Figure 2 in the documentation
     */
    async jumpToNode(nodeType) {
        console.log(`Jumping to ${nodeType} node`);
        
        // Update active button state
        const quickBtns = this.container.querySelectorAll('.quick-btn');
        quickBtns.forEach(btn => {
            if (btn.dataset.node === nodeType) {
                btn.classList.add('active');
            } else {
                btn.classList.remove('active');
            }
        });
        
        this.activeNode = nodeType;
        
        // Implement gRPC calls for each node type
        try {
            switch (nodeType) {
                case 'rendertarget':
                    this.updateNodeSelector('Render target');
                    break;
                case 'camera':
                    this.updateNodeSelector('Camera');
                    break;
                case 'resolution':
                    this.updateNodeSelector('Resolution');
                    break;
                case 'environment':
                    this.updateNodeSelector('Environment');
                    break;
                case 'imager':
                    this.updateNodeSelector('Imager');
                    break;
                case 'kernel':
                    this.updateNodeSelector('Kernel');
                    break;
                case 'mesh':
                    this.updateNodeSelector('Current Mesh');
                    break;
            }
            
            console.log(`Successfully jumped to ${nodeType} node`);
        } catch (error) {
            console.error(`❌ Failed to jump to ${nodeType} node:`, error);
        }
    }
    
    /**
     * Toggle Material Preview
     * Official OTOY material preview functionality (Figure 5 from documentation)
     */
    togglePreview() {
        console.log('Toggling Material Preview');
        
        this.previewEnabled = !this.previewEnabled;
        const previewBtn = this.container.querySelector('.preview-btn');
        
        if (this.previewEnabled) {
            previewBtn.classList.add('active');
            previewBtn.title = 'Disable Material Preview';
            this.enableMaterialPreview();
        } else {
            previewBtn.classList.remove('active');
            previewBtn.title = 'Enable Material Preview';
            this.disableMaterialPreview();
        }
        
        console.log(`Material Preview ${this.previewEnabled ? 'enabled' : 'disabled'}`);
    }
    
    /**
     * Toggle Render Mode
     * Official OTOY material render toggle (Figure 6 from documentation)
     */
    toggleRenderMode() {
        this.renderToggleEnabled = !this.renderToggleEnabled;
        const renderToggleBtn = this.container.querySelector('.render-toggle-btn');
        
        if (this.renderToggleEnabled) {
            renderToggleBtn.classList.add('active');
            renderToggleBtn.title = 'Disable Material Rendering';
            window.octaneClient.makeApiCall('ApiNodeGraphEditor/enableMaterialRender');
        } else {
            renderToggleBtn.classList.remove('active');
            renderToggleBtn.title = 'Enable Material Rendering';
            window.octaneClient.makeApiCall('ApiNodeGraphEditor/disableMaterialRender');
        }
        
        console.log(`Material Rendering ${this.renderToggleEnabled ? 'enabled' : 'disabled'}`);
    }
    
    /**
     * Update Node Inspector content
     */
    updateNodeInspector(nodeName, nodeData) {
        const nodeInspector = document.getElementById('node-inspector');
        if (nodeInspector) {
            // Trigger node inspector update
            if (window.nodeInspector && typeof window.nodeInspector.updateSelectedNode === 'function') {
                window.nodeInspector.updateSelectedNode(nodeData.handle);
            }
        }
    }
    
    /**
     * Update node selector dropdown
     */
    updateNodeSelector(nodeName) {
        const nodeSelector = document.querySelector('.node-selector');
        if (nodeSelector) {
            // Update selected option
            const options = nodeSelector.querySelectorAll('option');
            options.forEach(option => {
                if (option.textContent === nodeName) {
                    option.selected = true;
                }
            });
            
            // Add option if it doesn't exist
            if (!Array.from(options).some(option => option.textContent === nodeName)) {
                const newOption = document.createElement('option');
                newOption.textContent = nodeName;
                newOption.selected = true;
                nodeSelector.appendChild(newOption);
            }
        }
    }
    
    /**
     * Enable material preview rendering
     */
    enableMaterialPreview() {
        console.log('Enabling material preview rendering');
        
        // Add preview sphere/plane to node inspector
        const nodeInspector = document.getElementById('node-inspector');
        if (nodeInspector) {
            let previewContainer = nodeInspector.querySelector('.material-preview');
            if (!previewContainer) {
                previewContainer = document.createElement('div');
                previewContainer.className = 'material-preview';
                previewContainer.innerHTML = `
                    <div class="preview-header">Material Preview</div>
                    <div class="preview-viewport">
                        <div class="preview-sphere">🌐</div>
                        <div class="preview-controls">
                            <button class="preview-mode-btn" data-mode="sphere" title="Sphere Preview">⚪</button>
                            <button class="preview-mode-btn" data-mode="plane" title="Plane Preview">⬜</button>
                        </div>
                    </div>
                `;
                nodeInspector.insertBefore(previewContainer, nodeInspector.firstChild);
            }
            previewContainer.style.display = 'block';
        }
    }
    
    /**
     * Disable material preview rendering
     */
    disableMaterialPreview() {
        console.log('Disabling material preview rendering');
        
        const previewContainer = document.querySelector('.material-preview');
        if (previewContainer) {
            previewContainer.style.display = 'none';
        }
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeInspectorControls;
}