/**
 * Node Inspector Controls Component
 * Official OTOY Node Inspector quick access buttons implementation
 * Based on official documentation: RenderTarget, Camera, Resolution, Environment, Imager, Kernel, Current Mesh + Preview/Render Toggle
 */

class NodeInspectorControls {
    constructor(containerId, octaneClient = null) {
        this.container = document.getElementById(containerId);
        this.client = octaneClient;
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
                    await this.jumpToRenderTarget();
                    break;
                case 'camera':
                    await this.jumpToCamera();
                    break;
                case 'resolution':
                    await this.jumpToResolution();
                    break;
                case 'environment':
                    await this.jumpToEnvironment();
                    break;
                case 'imager':
                    await this.jumpToImager();
                    break;
                case 'kernel':
                    await this.jumpToKernel();
                    break;
                case 'mesh':
                    await this.jumpToCurrentMesh();
                    break;
            }
            
            console.log(`Successfully jumped to ${nodeType} node`);
        } catch (error) {
            console.error(`❌ Failed to jump to ${nodeType} node:`, error);
        }
    }
    
    /**
     * Jump to Render Target node
     * Official OTOY quick access to render target settings
     */
    async jumpToRenderTarget() {
        console.log('Jumping to Render Target');
        
        if (this.client && this.client.makeGrpcCall) {
            try {
                const result = await this.client.makeGrpcCall('ApiProjectManager/rootNodeGraph');
                if (result && result.success !== false) {
                    console.log('Found Render Target node');
                    this.updateNodeInspector('Render Target', result.data);
                }
            } catch (error) {
                console.error('❌ Failed to access Render Target:', error);
            }
        }
        
        // Update node selector
        this.updateNodeSelector('Render target');
    }
    
    /**
     * Jump to Camera node
     * Official OTOY quick access to camera settings
     */
    async jumpToCamera() {
        console.log('Jumping to Camera');
        
        if (this.client && this.client.makeGrpcCall) {
            try {
                // Get camera node from render target
                const result = await this.client.makeGrpcCall('ApiRenderTarget/getCamera');
                if (result && result.success !== false) {
                    console.log('Found Camera node');
                    this.updateNodeInspector('Camera', result.data);
                }
            } catch (error) {
                console.error('❌ Failed to access Camera:', error);
            }
        }
        
        this.updateNodeSelector('Camera');
    }
    
    /**
     * Jump to Resolution settings
     * Official OTOY quick access to resolution settings
     */
    async jumpToResolution() {
        console.log('Jumping to Resolution');
        
        if (this.client && this.client.makeGrpcCall) {
            try {
                const result = await this.client.makeGrpcCall('ApiRenderTarget/getResolution');
                if (result && result.success !== false) {
                    console.log('Found Resolution settings');
                    this.updateNodeInspector('Resolution', result.data);
                }
            } catch (error) {
                console.error('❌ Failed to access Resolution:', error);
            }
        }
        
        this.updateNodeSelector('Resolution');
    }
    
    /**
     * Jump to Environment node
     * Official OTOY quick access to environment settings
     */
    async jumpToEnvironment() {
        console.log('Jumping to Environment');
        
        if (this.client && this.client.makeGrpcCall) {
            try {
                const result = await this.client.makeGrpcCall('ApiRenderTarget/getEnvironment');
                if (result && result.success !== false) {
                    console.log('Found Environment node');
                    this.updateNodeInspector('Environment', result.data);
                }
            } catch (error) {
                console.error('❌ Failed to access Environment:', error);
            }
        }
        
        this.updateNodeSelector('Environment');
    }
    
    /**
     * Jump to Imager node
     * Official OTOY quick access to imager settings
     */
    async jumpToImager() {
        console.log('Jumping to Imager');
        
        if (this.client && this.client.makeGrpcCall) {
            try {
                const result = await this.client.makeGrpcCall('ApiRenderTarget/getImager');
                if (result && result.success !== false) {
                    console.log('Found Imager node');
                    this.updateNodeInspector('Imager', result.data);
                }
            } catch (error) {
                console.error('❌ Failed to access Imager:', error);
            }
        }
        
        this.updateNodeSelector('Imager');
    }
    
    /**
     * Jump to Kernel node
     * Official OTOY quick access to render kernel settings
     */
    async jumpToKernel() {
        console.log('Jumping to Kernel');
        
        if (this.client && this.client.makeGrpcCall) {
            try {
                const result = await this.client.makeGrpcCall('ApiRenderTarget/getKernel');
                if (result && result.success !== false) {
                    console.log('Found Kernel node');
                    this.updateNodeInspector('Kernel', result.data);
                }
            } catch (error) {
                console.error('❌ Failed to access Kernel:', error);
            }
        }
        
        this.updateNodeSelector('Kernel');
    }
    
    /**
     * Jump to Current Mesh
     * Official OTOY quick access to currently selected mesh
     */
    async jumpToCurrentMesh() {
        console.log('Jumping to Current Mesh');
        
        if (this.client && this.client.makeGrpcCall) {
            try {
                const result = await this.client.makeGrpcCall('ApiSelectionManager/getSelectedMesh');
                if (result && result.success !== false) {
                    console.log('Found Current Mesh');
                    this.updateNodeInspector('Current Mesh', result.data);
                }
            } catch (error) {
                console.error('❌ Failed to access Current Mesh:', error);
            }
        }
        
        this.updateNodeSelector('Current Mesh');
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
        console.log('Toggling Material Render Mode');
        
        this.renderToggleEnabled = !this.renderToggleEnabled;
        const renderToggleBtn = this.container.querySelector('.render-toggle-btn');
        
        if (this.renderToggleEnabled) {
            renderToggleBtn.classList.add('active');
            renderToggleBtn.title = 'Disable Material Rendering';
            this.enableMaterialRendering();
        } else {
            renderToggleBtn.classList.remove('active');
            renderToggleBtn.title = 'Enable Material Rendering';
            this.disableMaterialRendering();
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
    
    /**
     * Enable material rendering in node graph
     */
    enableMaterialRendering() {
        console.log('Enabling material rendering in node graph');
        
        if (this.client && this.client.makeGrpcCall) {
            try {
                this.client.makeGrpcCall('ApiNodeGraphEditor/enableMaterialRender');
            } catch (error) {
                console.error('❌ Failed to enable material rendering:', error);
            }
        }
    }
    
    /**
     * Disable material rendering in node graph
     */
    disableMaterialRendering() {
        console.log('Disabling material rendering in node graph');
        
        if (this.client && this.client.makeGrpcCall) {
            try {
                this.client.makeGrpcCall('ApiNodeGraphEditor/disableMaterialRender');
            } catch (error) {
                console.error('❌ Failed to disable material rendering:', error);
            }
        }
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeInspectorControls;
}