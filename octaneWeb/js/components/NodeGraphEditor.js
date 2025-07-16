/**
 * Node Graph Editor Component
 * Visual node-based editor for material and scene graphs
 */

class NodeGraphEditor extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        this.canvas = element;
        this.ctx = null;
        this.nodes = new Map();
        this.connections = new Map();
        this.selectedNodes = new Set();
        this.viewport = { x: 0, y: 0, zoom: 1 };
        this.isDragging = false;
        this.dragTarget = null;
        this.lastMousePos = { x: 0, y: 0 };
        this.contextMenu = null;
    }
    
    async onInitialize() {
        this.initCanvas();
        this.initNodeTypes();
        this.setupControls();
        this.setupToolbarControls(); // Add toolbar button handlers
        
        // Wait for canvas to be properly sized before creating nodes
        setTimeout(() => {
            this.createSampleNodes(); // Add sample nodes for testing
            
            // Ensure canvas is ready before starting render loop
            if (this.canvas.width > 0 && this.canvas.height > 0) {
                console.log('🎨 Canvas ready, starting render loop with size:', this.canvas.width, this.canvas.height);
                this.startRenderLoop();
            } else {
                console.log('⚠️ Canvas not ready, forcing resize and starting render loop');
                this.handleResize();
                setTimeout(() => this.startRenderLoop(), 100);
            }
            
            // Force multiple renders to ensure visibility
            setTimeout(() => {
                console.log('🔄 Force render 1 - Canvas size:', this.canvas.width, this.canvas.height);
                this.render();
            }, 100);
            
            setTimeout(() => {
                console.log('🔄 Force render 2 - Canvas size:', this.canvas.width, this.canvas.height);
                this.render();
            }, 300);
            
            setTimeout(() => {
                console.log('🔄 Force render 3 - Canvas size:', this.canvas.width, this.canvas.height);
                this.render();
            }, 600);
        }, 200);
    }
    
    setupEventListeners() {
        // Listen for node graph updates
        this.client.on('ui:nodeGraphUpdate', (nodeGraphState) => {
            this.updateNodeGraph(nodeGraphState);
        });
        
        // Mouse events
        this.addEventListener(this.canvas, 'mousedown', this.handleMouseDown.bind(this));
        this.addEventListener(this.canvas, 'mousemove', this.handleMouseMove.bind(this));
        this.addEventListener(this.canvas, 'mouseup', this.handleMouseUp.bind(this));
        this.addEventListener(this.canvas, 'wheel', this.handleWheel.bind(this));
        this.addEventListener(this.canvas, 'dblclick', this.handleDoubleClick.bind(this));
        
        // Keyboard events
        this.addEventListener(document, 'keydown', this.handleKeyDown.bind(this));
        
        // Window resize
        this.addEventListener(window, 'resize', this.handleResize.bind(this));
    }
    
    initCanvas() {
        console.log('🎨 Initializing canvas:', this.canvas);
        console.log('🎨 Canvas element:', this.canvas.tagName, this.canvas.id, this.canvas.className);
        console.log('🎨 Canvas size:', this.canvas.width, this.canvas.height);
        console.log('🎨 Canvas client size:', this.canvas.clientWidth, this.canvas.clientHeight);
        
        this.ctx = this.canvas.getContext('2d');
        if (!this.ctx) {
            console.error('❌ Failed to get 2D context');
            return;
        }
        
        console.log('✅ Got 2D context:', this.ctx);
        
        // Test immediate draw
        this.ctx.fillStyle = '#00ff00';
        this.ctx.fillRect(0, 0, 50, 50);
        console.log('🧪 Drew test green rectangle at canvas init');
        
        // Initial resize
        this.handleResize();
        
        // Multiple delayed resizes to ensure DOM layout is complete
        setTimeout(() => this.handleResize(), 100);
        setTimeout(() => this.handleResize(), 250);
        setTimeout(() => this.handleResize(), 500);
        
        // Also trigger resize on window load event
        if (document.readyState === 'loading') {
            window.addEventListener('load', () => {
                setTimeout(() => this.handleResize(), 100);
            });
        }
        
        console.log('Node graph canvas initialized');
    }
    
    setupControls() {
        // Right-click context menu for node creation
        this.addEventListener(this.canvas, 'contextmenu', (e) => {
            e.preventDefault();
            const rect = this.canvas.getBoundingClientRect();
            const x = e.clientX;
            const y = e.clientY;
            this.showContextMenu(x, y);
        });
        
        // Hide context menu on click elsewhere
        this.addEventListener(document, 'click', (e) => {
            if (this.contextMenu && !this.contextMenu.contains(e.target)) {
                this.hideContextMenu();
            }
        });
        
        // Hide context menu on escape
        this.addEventListener(document, 'keydown', (e) => {
            if (e.key === 'Escape') {
                this.hideContextMenu();
            }
        });
    }

    setupToolbarControls() {
        // Find toolbar buttons
        const nodeGraphSection = this.canvas.closest('.node-graph-section');
        if (!nodeGraphSection) return;

        const addButton = nodeGraphSection.querySelector('.node-btn[title="Add Node"]');
        const deleteButton = nodeGraphSection.querySelector('.node-btn[title="Delete Node"]');
        const fitButton = nodeGraphSection.querySelector('.node-btn[title="Fit All"]');

        // Add Node button
        if (addButton) {
            this.addEventListener(addButton, 'click', () => {
                // Ensure canvas dimensions are available
                if (!this.canvas.width || !this.canvas.height) {
                    this.handleResize();
                }
                
                // Create node at center of viewport
                const centerX = (-this.viewport.x + this.canvas.width / 2) / this.viewport.zoom;
                const centerY = (-this.viewport.y + this.canvas.height / 2) / this.viewport.zoom;
                
                // Fallback to (0, 0) if calculations result in NaN
                const nodeX = isNaN(centerX) ? 0 : centerX;
                const nodeY = isNaN(centerY) ? 0 : centerY;
                
                this.createNodeAtPosition(nodeX, nodeY);
            });
        }

        // Delete Node button
        if (deleteButton) {
            this.addEventListener(deleteButton, 'click', () => {
                if (this.selectedNodes.size > 0) {
                    this.deleteSelectedNodes();
                } else {
                    if (window.debugConsole) {
                        window.debugConsole.log('⚠️ No nodes selected for deletion');
                    }
                }
            });
        }

        // Fit All button
        if (fitButton) {
            this.addEventListener(fitButton, 'click', () => {
                this.frameAll();
                if (window.debugConsole) {
                    window.debugConsole.log('🔍 Framed all nodes in viewport');
                }
            });
        }

        console.log('🎛️ Node graph toolbar controls initialized');
    }
    
    startRenderLoop() {
        if (this.renderLoopRunning) return;
        this.renderLoopRunning = true;
        
        console.log('🔄 Starting render loop...');
        
        // Test: Try calling render directly first
        console.log('🧪 Testing direct render call...');
        try {
            this.render();
            console.log('✅ Direct render call succeeded');
        } catch (error) {
            console.error('❌ Direct render call failed:', error);
        }
        
        // Use setInterval instead of requestAnimationFrame as fallback
        console.log('🔄 Using setInterval render loop...');
        this.renderInterval = setInterval(() => {
            if (!this.renderLoopRunning) {
                clearInterval(this.renderInterval);
                return;
            }
            try {
                this.render();
            } catch (error) {
                console.error('🚨 Render error:', error);
                console.error('🚨 Error stack:', error.stack);
                this.renderLoopRunning = false;
                clearInterval(this.renderInterval);
            }
        }, 16); // ~60 FPS
    }
    
    render() {
        // Debug: Check if render is being called FIRST
        if (this.renderCount < 5) {
            console.log('🎨 Render called, ctx exists:', !!this.ctx, 'nodes count:', this.nodes.size, 'canvas size:', this.canvas.width, 'x', this.canvas.height);
            console.log('🎨 Nodes data:', Array.from(this.nodes.keys()));
            this.renderCount = (this.renderCount || 0) + 1;
        }
        
        if (!this.ctx) {
            console.log('❌ No context, returning early');
            return;
        }
        
        // Debug: Log render call with node count
        if (this.renderCount < 10) {
            console.log(`🎨 Render call ${this.renderCount || 0}: ${this.nodes.size} nodes, viewport:`, this.viewport);
            this.renderCount = (this.renderCount || 0) + 1;
        }
        
        // Clear canvas
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
        
        // TEST: Draw a simple red rectangle to verify canvas is working
        this.ctx.fillStyle = '#ff0000';
        this.ctx.fillRect(10, 10, 100, 50);
        this.ctx.fillStyle = '#ffffff';
        this.ctx.font = '12px Arial';
        this.ctx.fillText('TEST CANVAS', 15, 30);
        
        // Save context
        this.ctx.save();
        
        // Apply viewport transform
        this.ctx.translate(this.viewport.x, this.viewport.y);
        this.ctx.scale(this.viewport.zoom, this.viewport.zoom);
        
        // Draw grid
        this.drawGrid();
        
        // Draw connections
        this.drawConnections();
        
        // Draw nodes
        this.drawNodes();
        
        // Restore context
        this.ctx.restore();
        
        // Debug info (outside viewport transform)
        this.ctx.fillStyle = '#ffffff';
        this.ctx.font = '12px Arial';
        this.ctx.fillText(`Nodes: ${this.nodes.size}`, 10, 20);
        this.ctx.fillText(`Viewport: ${this.viewport.x.toFixed(0)}, ${this.viewport.y.toFixed(0)}, ${this.viewport.zoom.toFixed(2)}`, 10, 35);
    }
    
    drawGrid() {
        const gridSize = 20;
        const startX = Math.floor(-this.viewport.x / this.viewport.zoom / gridSize) * gridSize;
        const startY = Math.floor(-this.viewport.y / this.viewport.zoom / gridSize) * gridSize;
        const endX = startX + (this.canvas.width / this.viewport.zoom) + gridSize;
        const endY = startY + (this.canvas.height / this.viewport.zoom) + gridSize;
        
        this.ctx.strokeStyle = 'rgba(255, 255, 255, 0.1)';
        this.ctx.lineWidth = 1 / this.viewport.zoom;
        
        this.ctx.beginPath();
        for (let x = startX; x < endX; x += gridSize) {
            this.ctx.moveTo(x, startY);
            this.ctx.lineTo(x, endY);
        }
        for (let y = startY; y < endY; y += gridSize) {
            this.ctx.moveTo(startX, y);
            this.ctx.lineTo(endX, y);
        }
        this.ctx.stroke();
    }
    
    drawConnections() {
        this.connections.forEach(connection => {
            this.drawConnection(connection);
        });
    }
    
    drawConnection(connection) {
        const outputNode = this.nodes.get(connection.outputNodeId);
        const inputNode = this.nodes.get(connection.inputNodeId);
        
        if (!outputNode || !inputNode) return;
        
        const outputPos = this.getSocketPosition(outputNode, connection.outputSocket, 'output');
        const inputPos = this.getSocketPosition(inputNode, connection.inputSocket, 'input');
        
        // Draw bezier curve
        this.ctx.strokeStyle = connection.selected ? '#4a90e2' : '#888888';
        this.ctx.lineWidth = 2 / this.viewport.zoom;
        
        this.ctx.beginPath();
        this.ctx.moveTo(outputPos.x, outputPos.y);
        
        const controlOffset = 100 / this.viewport.zoom;
        this.ctx.bezierCurveTo(
            outputPos.x + controlOffset, outputPos.y,
            inputPos.x - controlOffset, inputPos.y,
            inputPos.x, inputPos.y
        );
        
        this.ctx.stroke();
    }
    
    drawNodes() {
        this.nodes.forEach(node => {
            this.drawNode(node);
        });
    }
    
    // Helper method for drawing rounded rectangles (professional Octane-style nodes)
    drawRoundedRect(x, y, width, height, radius, color, fill = true, topOnly = false) {
        this.ctx.beginPath();
        
        if (topOnly) {
            // Only round top corners for headers
            this.ctx.moveTo(x + radius, y);
            this.ctx.lineTo(x + width - radius, y);
            this.ctx.quadraticCurveTo(x + width, y, x + width, y + radius);
            this.ctx.lineTo(x + width, y + height);
            this.ctx.lineTo(x, y + height);
            this.ctx.lineTo(x, y + radius);
            this.ctx.quadraticCurveTo(x, y, x + radius, y);
        } else {
            // Full rounded rectangle
            this.ctx.moveTo(x + radius, y);
            this.ctx.lineTo(x + width - radius, y);
            this.ctx.quadraticCurveTo(x + width, y, x + width, y + radius);
            this.ctx.lineTo(x + width, y + height - radius);
            this.ctx.quadraticCurveTo(x + width, y + height, x + width - radius, y + height);
            this.ctx.lineTo(x + radius, y + height);
            this.ctx.quadraticCurveTo(x, y + height, x, y + height - radius);
            this.ctx.lineTo(x, y + radius);
            this.ctx.quadraticCurveTo(x, y, x + radius, y);
        }
        
        this.ctx.closePath();
        
        if (fill) {
            this.ctx.fillStyle = color;
            this.ctx.fill();
        } else {
            this.ctx.strokeStyle = color;
            this.ctx.stroke();
        }
    }
    
    drawNode(node) {
        const { x, y, width = 120, height = 80 } = node;
        const isSelected = this.selectedNodes.has(node.id);
        
        // Debug: Only log first few draws to avoid spam
        if (this.drawCount < 5) {
            console.log('🎨 Drawing professional node at:', x, y, 'size:', width, height, 'type:', node.type);
            this.drawCount = (this.drawCount || 0) + 1;
        }
        
        // Professional node colors based on type (matching Octane reference)
        let nodeColor, headerColor, textColor;
        switch (node.type.toLowerCase()) {
            case 'material':
                nodeColor = '#d4b896';  // Beige/tan like Octane
                headerColor = '#c4a886';
                textColor = '#2a2a2a';
                break;
            case 'texture':
                nodeColor = '#7ba7d4';  // Blue like Octane
                headerColor = '#6b97c4';
                textColor = '#ffffff';
                break;
            case 'mesh':
            case 'geometry':
                nodeColor = '#a8c4a2';  // Green like Octane
                headerColor = '#98b492';
                textColor = '#2a2a2a';
                break;
            default:
                nodeColor = '#8a8a8a';  // Gray default
                headerColor = '#7a7a7a';
                textColor = '#ffffff';
        }

        // Selection highlight
        if (isSelected) {
            this.ctx.strokeStyle = '#4a90e2';
            this.ctx.lineWidth = 2 / this.viewport.zoom;
        } else {
            this.ctx.strokeStyle = '#555555';
            this.ctx.lineWidth = 1 / this.viewport.zoom;
        }

        // Draw rounded rectangle for professional look
        const cornerRadius = 6 / this.viewport.zoom;
        this.drawRoundedRect(x, y, width, height, cornerRadius, nodeColor, true);
        this.drawRoundedRect(x, y, width, height, cornerRadius, this.ctx.strokeStyle, false);

        // Node header with rounded top corners
        this.drawRoundedRect(x, y, width, 24, cornerRadius, headerColor, true, true);

        // Node title
        this.ctx.fillStyle = textColor;
        this.ctx.font = `${11 / this.viewport.zoom}px Arial`;
        this.ctx.textAlign = 'center';
        this.ctx.fillText(node.name || node.type, x + width / 2, y + 16);
        
        // Input sockets
        if (node.inputs) {
            node.inputs.forEach((input, index) => {
                this.drawSocket(x, y + 30 + index * 15, input, 'input');
            });
        }
        
        // Output sockets
        if (node.outputs) {
            node.outputs.forEach((output, index) => {
                this.drawSocket(x + width, y + 30 + index * 15, output, 'output');
            });
        }
    }
    
    drawSocket(x, y, socket, type) {
        const radius = 6 / this.viewport.zoom;
        
        // Socket circle
        this.ctx.fillStyle = socket.connected ? '#4a90e2' : '#666666';
        this.ctx.beginPath();
        this.ctx.arc(x, y, radius, 0, Math.PI * 2);
        this.ctx.fill();
        
        // Socket label
        this.ctx.fillStyle = '#cccccc';
        this.ctx.font = `${10 / this.viewport.zoom}px Arial`;
        this.ctx.textAlign = type === 'input' ? 'left' : 'right';
        
        const labelX = type === 'input' ? x + radius + 4 : x - radius - 4;
        this.ctx.fillText(socket.name, labelX, y + 3);
    }
    
    updateNodeGraph(nodeGraphState) {
        this.nodes = new Map(nodeGraphState.nodes);
        this.connections = new Map(nodeGraphState.connections);
        this.selectedNodes = new Set(nodeGraphState.selectedNodes);
        
        if (nodeGraphState.viewport) {
            this.viewport = { ...this.viewport, ...nodeGraphState.viewport };
        }
    }
    
    handleMouseDown(e) {
        const rect = this.canvas.getBoundingClientRect();
        const mousePos = {
            x: (e.clientX - rect.left - this.viewport.x) / this.viewport.zoom,
            y: (e.clientY - rect.top - this.viewport.y) / this.viewport.zoom
        };
        
        // Check for node hit
        const hitNode = this.getNodeAtPosition(mousePos.x, mousePos.y);
        
        if (hitNode) {
            this.isDragging = true;
            this.dragTarget = hitNode;
            
            if (!e.ctrlKey && !e.metaKey) {
                this.selectedNodes.clear();
            }
            this.selectedNodes.add(hitNode.id);
        } else {
            // Pan viewport
            this.isDragging = true;
            this.dragTarget = 'viewport';
        }
        
        this.lastMousePos = { x: e.clientX, y: e.clientY };
    }
    
    handleMouseMove(e) {
        if (!this.isDragging) return;
        
        const deltaX = e.clientX - this.lastMousePos.x;
        const deltaY = e.clientY - this.lastMousePos.y;
        
        if (this.dragTarget === 'viewport') {
            this.viewport.x += deltaX;
            this.viewport.y += deltaY;
        } else if (this.dragTarget && typeof this.dragTarget === 'object') {
            // Move node
            this.dragTarget.x += deltaX / this.viewport.zoom;
            this.dragTarget.y += deltaY / this.viewport.zoom;
        }
        
        this.lastMousePos = { x: e.clientX, y: e.clientY };
    }
    
    handleMouseUp(e) {
        this.isDragging = false;
        this.dragTarget = null;
    }
    
    handleWheel(e) {
        e.preventDefault();
        
        const rect = this.canvas.getBoundingClientRect();
        const mouseX = e.clientX - rect.left;
        const mouseY = e.clientY - rect.top;
        
        const zoomFactor = e.deltaY > 0 ? 0.9 : 1.1;
        const newZoom = Math.max(0.1, Math.min(3, this.viewport.zoom * zoomFactor));
        
        // Zoom towards mouse position
        this.viewport.x = mouseX - (mouseX - this.viewport.x) * (newZoom / this.viewport.zoom);
        this.viewport.y = mouseY - (mouseY - this.viewport.y) * (newZoom / this.viewport.zoom);
        this.viewport.zoom = newZoom;
    }
    
    handleDoubleClick(e) {
        const rect = this.canvas.getBoundingClientRect();
        const mouseX = (e.clientX - rect.left - this.viewport.x) / this.viewport.zoom;
        const mouseY = (e.clientY - rect.top - this.viewport.y) / this.viewport.zoom;
        
        // Fallback to (0, 0) if calculations result in NaN
        const nodeX = isNaN(mouseX) ? 0 : mouseX;
        const nodeY = isNaN(mouseY) ? 0 : mouseY;
        
        // Create new node at mouse position
        this.createNodeAtPosition(nodeX, nodeY);
    }
    
    handleKeyDown(e) {
        if (e.key === 'Delete' && this.selectedNodes.size > 0) {
            this.deleteSelectedNodes();
        } else if (e.key === 'f' || e.key === 'F') {
            this.frameAll();
        }
    }
    
    getNodeAtPosition(x, y) {
        for (const node of this.nodes.values()) {
            const width = node.width || 120;
            const height = node.height || 80;
            
            if (x >= node.x && x <= node.x + width &&
                y >= node.y && y <= node.y + height) {
                return node;
            }
        }
        return null;
    }
    
    getSocketPosition(node, socketName, type) {
        const width = node.width || 120;
        const sockets = type === 'input' ? node.inputs : node.outputs;
        const socketIndex = sockets?.findIndex(s => s.name === socketName) || 0;
        
        return {
            x: type === 'input' ? node.x : node.x + width,
            y: node.y + 30 + socketIndex * 15
        };
    }
    


    async createNodeAtPosition(x, y) {
        // Convert world coordinates to screen coordinates for context menu
        const screenX = x * this.viewport.zoom + this.viewport.x;
        const screenY = y * this.viewport.zoom + this.viewport.y;
        
        // Show context menu at the calculated screen position
        this.showContextMenu(screenX, screenY);
    }
    
    async deleteSelectedNodes() {
        const deletedNodes = [];
        
        for (const nodeId of this.selectedNodes) {
            const node = this.nodes.get(nodeId);
            if (node) {
                // Remove connections involving this node
                const connectionsToRemove = [];
                this.connections.forEach((connection, connId) => {
                    if (connection.outputNodeId === nodeId || connection.inputNodeId === nodeId) {
                        connectionsToRemove.push(connId);
                    }
                });
                
                connectionsToRemove.forEach(connId => {
                    this.connections.delete(connId);
                });
                
                // Remove the node
                this.nodes.delete(nodeId);
                deletedNodes.push(node.name);
            }
        }
        
        this.selectedNodes.clear();
        
        if (deletedNodes.length > 0) {
            console.log(`🗑️ Deleted nodes: ${deletedNodes.join(', ')}`);
            
            // Log to debug console
            if (window.debugConsole) {
                window.debugConsole.log(`🗑️ Deleted ${deletedNodes.length} node(s): ${deletedNodes.join(', ')}`);
            }
        }
    }
    
    createSampleNodes() {
        // Create sample nodes for testing
        const sampleNodes = [
            {
                id: 'material_1',
                name: 'Diffuse Material',
                type: 'material',
                x: 300,
                y: 150,
                width: 140,
                height: 100,
                inputs: [
                    { name: 'Diffuse', connected: false },
                    { name: 'Roughness', connected: false },
                    { name: 'Normal', connected: false }
                ],
                outputs: [
                    { name: 'Material', connected: true }
                ]
            },
            {
                id: 'texture_1',
                name: 'Image Texture',
                type: 'texture',
                x: 50,
                y: 120,
                width: 120,
                height: 80,
                inputs: [
                    { name: 'UV', connected: false }
                ],
                outputs: [
                    { name: 'Color', connected: true },
                    { name: 'Alpha', connected: false }
                ]
            },
            {
                id: 'geometry_1',
                name: 'Mesh',
                type: 'geometry',
                x: 500,
                y: 150,
                width: 100,
                height: 80,
                inputs: [
                    { name: 'Material', connected: true }
                ],
                outputs: []
            }
        ];

        // Add nodes to the map
        sampleNodes.forEach(node => {
            this.nodes.set(node.id, node);
        });

        // Create sample connection
        this.connections.set('conn_1', {
            id: 'conn_1',
            outputNodeId: 'texture_1',
            outputSocket: 'Color',
            inputNodeId: 'material_1',
            inputSocket: 'Diffuse',
            selected: false
        });

        this.connections.set('conn_2', {
            id: 'conn_2',
            outputNodeId: 'material_1',
            outputSocket: 'Material',
            inputNodeId: 'geometry_1',
            inputSocket: 'Material',
            selected: false
        });

        console.log('🎨 Created sample nodes for node graph editor');
        
        // Force immediate render after creating nodes
        setTimeout(() => {
            console.log('🔄 Forcing render after node creation');
            this.render();
        }, 100);
        
        // Also force render after a longer delay to ensure canvas is ready
        setTimeout(() => {
            console.log('🔄 Second forced render after node creation');
            this.render();
        }, 500);
    }

    frameAll() {
        if (this.nodes.size === 0) return;
        
        let minX = Infinity, minY = Infinity, maxX = -Infinity, maxY = -Infinity;
        
        this.nodes.forEach(node => {
            const width = node.width || 120;
            const height = node.height || 80;
            
            minX = Math.min(minX, node.x);
            minY = Math.min(minY, node.y);
            maxX = Math.max(maxX, node.x + width);
            maxY = Math.max(maxY, node.y + height);
        });
        
        const centerX = (minX + maxX) / 2;
        const centerY = (minY + maxY) / 2;
        const width = maxX - minX;
        const height = maxY - minY;
        
        const zoomX = this.canvas.width / (width + 100);
        const zoomY = this.canvas.height / (height + 100);
        const zoom = Math.min(zoomX, zoomY, 1);
        
        this.viewport.zoom = zoom;
        this.viewport.x = this.canvas.width / 2 - centerX * zoom;
        this.viewport.y = this.canvas.height / 2 - centerY * zoom;
    }
    
    handleResize() {
        if (!this.canvas) return;
        
        const rect = this.canvas.getBoundingClientRect();
        console.log('Canvas resize - rect:', rect.width, rect.height);
        
        // If canvas rect is 0, try to get dimensions from parent container
        if (rect.width === 0 || rect.height === 0) {
            const parent = this.canvas.parentElement;
            if (parent) {
                const parentRect = parent.getBoundingClientRect();
                console.log('Parent rect:', parentRect.width, parentRect.height);
                
                if (parentRect.width > 0 && parentRect.height > 0) {
                    this.canvas.width = parentRect.width;
                    this.canvas.height = parentRect.height;
                    console.log('Canvas sized from parent:', this.canvas.width, this.canvas.height);
                    this.render();
                    return;
                }
            }
            
            // Fallback: Force minimum dimensions based on CSS
            const nodeGraphSection = document.querySelector('.node-graph-section');
            if (nodeGraphSection) {
                const sectionRect = nodeGraphSection.getBoundingClientRect();
                console.log('Section rect:', sectionRect.width, sectionRect.height);
                
                if (sectionRect.width > 0 && sectionRect.height > 0) {
                    // Account for header height (approximately 32px)
                    this.canvas.width = sectionRect.width;
                    this.canvas.height = Math.max(sectionRect.height - 32, 150);
                    console.log('Canvas sized from section:', this.canvas.width, this.canvas.height);
                    this.render();
                    return;
                }
            }
        }
        
        // Ensure we have valid dimensions
        if (rect.width > 0 && rect.height > 0) {
            this.canvas.width = rect.width;
            this.canvas.height = rect.height;
            console.log('Canvas actual size:', this.canvas.width, this.canvas.height);
            
            // Trigger a render after resize
            this.render();
        } else {
            console.log('Canvas dimensions not ready, retrying...');
            // Retry after a short delay if dimensions aren't ready
            setTimeout(() => this.handleResize(), 50);
        }
    }
    
    initNodeTypes() {
        // Octane node type hierarchy based on octaneids.h
        this.nodeTypes = {
            'Cameras': {
                'NT_CAM_THINLENS': { name: 'Thin lens camera', color: '#8B4513' },
                'NT_CAM_PANORAMIC': { name: 'Panoramic camera', color: '#8B4513' },
                'NT_CAM_UNIVERSAL': { name: 'Universal camera', color: '#8B4513' },
                'NT_CAM_BAKING': { name: 'Baking camera', color: '#8B4513' },
                'NT_CAM_OSL': { name: 'OSL camera', color: '#8B4513' },
                'NT_CAM_SIMULATED_LENS': { name: 'Simulated lens camera', color: '#8B4513' }
            },
            'Displacement': {
                'NT_DISPLACEMENT': { name: 'Displacement', color: '#FF6B35' }
            },
            'Emission': {
                'NT_EMIS_BLACKBODY': { name: 'Blackbody emission', color: '#FFD700' },
                'NT_EMIS_TEXTURE': { name: 'Texture emission', color: '#FFD700' }
            },
            'Environments': {
                'NT_ENV_DAYLIGHT': { name: 'Daylight environment', color: '#87CEEB' },
                'NT_ENV_PLANETARY': { name: 'Planetary environment', color: '#87CEEB' },
                'NT_ENV_TEXTURE': { name: 'Texture environment', color: '#87CEEB' }
            },
            'Geometry': {
                'NT_GEO_MESH': { name: 'Mesh', color: '#32CD32' },
                'NT_GEO_GROUP': { name: 'Group', color: '#32CD32' },
                'NT_GEO_PLACEMENT': { name: 'Placement', color: '#32CD32' },
                'NT_GEO_SCATTER': { name: 'Scatter', color: '#32CD32' },
                'NT_GEO_PLANE': { name: 'Plane', color: '#32CD32' },
                'NT_GEO_VOLUME': { name: 'Volume', color: '#32CD32' },
                'NT_GEO_OBJECT': { name: 'Object', color: '#32CD32' }
            },
            'Input': {
                'NT_BOOL': { name: 'Boolean', color: '#9370DB' },
                'NT_FLOAT': { name: 'Float', color: '#9370DB' },
                'NT_INT': { name: 'Integer', color: '#9370DB' },
                'NT_ENUM': { name: 'Enum', color: '#9370DB' }
            },
            'Kernels': {
                'NT_KERN_PMC': { name: 'PMC kernel', color: '#FF1493' },
                'NT_KERN_DIRECTLIGHTING': { name: 'Direct lighting kernel', color: '#FF1493' },
                'NT_KERN_PATHTRACING': { name: 'Path tracing kernel', color: '#FF1493' },
                'NT_KERN_INFO': { name: 'Info kernel', color: '#FF1493' }
            },
            'Lights': {
                'NT_LIGHT_QUAD': { name: 'Quad light', color: '#FFFF00' },
                'NT_LIGHT_SPHERE': { name: 'Sphere light', color: '#FFFF00' },
                'NT_LIGHT_VOLUME_SPOT': { name: 'Volume spot light', color: '#FFFF00' },
                'NT_LIGHT_DIRECTIONAL': { name: 'Directional light', color: '#FFFF00' },
                'NT_LIGHT_ANALYTIC': { name: 'Analytic light', color: '#FFFF00' }
            },
            'Materials': {
                'NT_MAT_DIFFUSE': { name: 'Diffuse material', color: '#4169E1' },
                'NT_MAT_GLOSSY': { name: 'Glossy material', color: '#4169E1' },
                'NT_MAT_SPECULAR': { name: 'Specular material', color: '#4169E1' },
                'NT_MAT_MIX': { name: 'Mix material', color: '#4169E1' },
                'NT_MAT_PORTAL': { name: 'Portal material', color: '#4169E1' },
                'NT_MAT_UNIVERSAL': { name: 'Universal material', color: '#4169E1' },
                'NT_MAT_METAL': { name: 'Metal material', color: '#4169E1' },
                'NT_MAT_TOON': { name: 'Toon material', color: '#4169E1' }
            },
            'Medium': {
                'NT_MED_ABSORPTION': { name: 'Absorption medium', color: '#8A2BE2' },
                'NT_MED_SCATTERING': { name: 'Scattering medium', color: '#8A2BE2' },
                'NT_MED_VOLUME': { name: 'Volume medium', color: '#8A2BE2' },
                'NT_MED_RANDOMWALK': { name: 'Random walk medium', color: '#8A2BE2' }
            },
            'Textures': {
                'NT_TEX_IMAGE': { name: 'Image texture', color: '#20B2AA' },
                'NT_TEX_FLOATIMAGE': { name: 'Float image texture', color: '#20B2AA' },
                'NT_TEX_ALPHAIMAGE': { name: 'Alpha image texture', color: '#20B2AA' },
                'NT_TEX_RGB': { name: 'RGB texture', color: '#20B2AA' },
                'NT_TEX_FLOAT': { name: 'Float texture', color: '#20B2AA' },
                'NT_TEX_NOISE': { name: 'Noise texture', color: '#20B2AA' },
                'NT_TEX_CHECKS': { name: 'Checks texture', color: '#20B2AA' },
                'NT_TEX_MARBLE': { name: 'Marble texture', color: '#20B2AA' },
                'NT_TEX_TURBULENCE': { name: 'Turbulence texture', color: '#20B2AA' },
                'NT_TEX_MIX': { name: 'Mix texture', color: '#20B2AA' },
                'NT_TEX_MULTIPLY': { name: 'Multiply texture', color: '#20B2AA' },
                'NT_TEX_ADD': { name: 'Add texture', color: '#20B2AA' },
                'NT_TEX_SUBTRACT': { name: 'Subtract texture', color: '#20B2AA' },
                'NT_TEX_GRADIENT': { name: 'Gradient texture', color: '#20B2AA' },
                'NT_TEX_FALLOFF': { name: 'Falloff texture', color: '#20B2AA' }
            }
        };
    }
    
    showContextMenu(x, y) {
        this.hideContextMenu();
        
        const contextMenu = document.createElement('div');
        contextMenu.className = 'node-context-menu';
        contextMenu.style.left = x + 'px';
        contextMenu.style.top = y + 'px';
        
        // Create menu structure
        Object.keys(this.nodeTypes).forEach(category => {
            const categoryItem = document.createElement('div');
            categoryItem.className = 'context-menu-category';
            categoryItem.textContent = category;
            
            const submenu = document.createElement('div');
            submenu.className = 'context-submenu';
            
            Object.keys(this.nodeTypes[category]).forEach(nodeType => {
                const nodeInfo = this.nodeTypes[category][nodeType];
                const nodeItem = document.createElement('div');
                nodeItem.className = 'context-menu-item';
                nodeItem.textContent = nodeInfo.name;
                nodeItem.addEventListener('click', () => {
                    this.createNodeFromType(nodeType, x, y);
                    this.hideContextMenu();
                });
                submenu.appendChild(nodeItem);
            });
            
            // Add hover events for submenu positioning
            categoryItem.addEventListener('mouseenter', () => {
                const categoryRect = categoryItem.getBoundingClientRect();
                submenu.style.left = (categoryRect.right + 2) + 'px';
                submenu.style.top = categoryRect.top + 'px';
                
                // Adjust if submenu goes off screen
                const submenuRect = submenu.getBoundingClientRect();
                if (submenuRect.right > window.innerWidth) {
                    submenu.style.left = (categoryRect.left - submenuRect.width - 2) + 'px';
                }
                if (submenuRect.bottom > window.innerHeight) {
                    submenu.style.top = (window.innerHeight - submenuRect.height) + 'px';
                }
                
                submenu.style.display = 'block';
            });

            categoryItem.addEventListener('mouseleave', () => {
                submenu.style.display = 'none';
            });
            
            categoryItem.appendChild(submenu);
            contextMenu.appendChild(categoryItem);
        });
        
        document.body.appendChild(contextMenu);
        this.contextMenu = contextMenu;
        
        // Position adjustment to keep menu on screen
        const rect = contextMenu.getBoundingClientRect();
        if (rect.right > window.innerWidth) {
            contextMenu.style.left = (x - rect.width) + 'px';
        }
        if (rect.bottom > window.innerHeight) {
            contextMenu.style.top = (y - rect.height) + 'px';
        }
    }
    
    hideContextMenu() {
        if (this.contextMenu) {
            document.body.removeChild(this.contextMenu);
            this.contextMenu = null;
        }
    }
    
    createNodeFromType(nodeType, x, y) {
        console.log('createNodeFromType called with:', nodeType, x, y);
        
        const category = this.findNodeCategory(nodeType);
        console.log('Found category:', category);
        
        if (!this.nodeTypes[category] || !this.nodeTypes[category][nodeType]) {
            console.error('Node type not found:', nodeType, 'in category:', category);
            return;
        }
        
        const nodeInfo = this.nodeTypes[category][nodeType];
        console.log('Node info:', nodeInfo);
        
        // For now, create nodes at the center of the visible area
        const centerX = this.canvas.width / 2;
        const centerY = this.canvas.height / 2;
        
        // Convert to world coordinates
        const worldX = (centerX - this.viewport.x) / this.viewport.zoom;
        const worldY = (centerY - this.viewport.y) / this.viewport.zoom;
        
        console.log('World coordinates:', worldX, worldY);
        console.log('Viewport:', JSON.stringify(this.viewport));
        console.log('Canvas size:', this.canvas.width, this.canvas.height);
        console.log('Center calc:', centerX, centerY);
        
        const node = {
            id: this.nextNodeId++,
            type: nodeType,
            name: nodeInfo.name,
            x: worldX,
            y: worldY,
            width: 140,
            height: 80,
            color: nodeInfo.color,
            inputs: this.getNodeInputs(nodeType),
            outputs: this.getNodeOutputs(nodeType)
        };
        
        console.log('Created node:', node);
        
        this.nodes.set(node.id, node);
        console.log('Total nodes:', this.nodes.size);
        
        // Trigger a render to show the new node
        this.render();
        
        // Log the creation
        if (window.debugConsole) {
            window.debugConsole.log(`🎨 Created ${nodeInfo.name} node at (${worldX.toFixed(0)}, ${worldY.toFixed(0)})`);
        }
    }
    
    findNodeCategory(nodeType) {
        for (const category in this.nodeTypes) {
            if (this.nodeTypes[category][nodeType]) {
                return category;
            }
        }
        return 'Other';
    }
    
    getNodeInputs(nodeType) {
        // Define inputs based on node type
        const inputMap = {
            'NT_MAT_DIFFUSE': ['Diffuse', 'Roughness', 'Normal'],
            'NT_MAT_GLOSSY': ['Diffuse', 'Specular', 'Roughness', 'IOR', 'Normal'],
            'NT_MAT_UNIVERSAL': ['Albedo', 'Metallic', 'Roughness', 'Specular', 'Normal'],
            'NT_TEX_IMAGE': ['UV', 'Gamma'],
            'NT_TEX_NOISE': ['UV', 'Scale', 'Detail'],
            'NT_TEX_MIX': ['Texture1', 'Texture2', 'Amount'],
            'NT_LIGHT_QUAD': ['Power', 'Color', 'Size'],
            'NT_ENV_DAYLIGHT': ['Sun direction', 'Turbidity', 'Power']
        };
        return inputMap[nodeType] || ['Input'];
    }
    
    getNodeOutputs(nodeType) {
        // Define outputs based on node type
        const outputMap = {
            'NT_MAT_DIFFUSE': ['Material'],
            'NT_MAT_GLOSSY': ['Material'],
            'NT_MAT_UNIVERSAL': ['Material'],
            'NT_TEX_IMAGE': ['Color', 'Alpha'],
            'NT_TEX_NOISE': ['Color'],
            'NT_TEX_MIX': ['Color'],
            'NT_LIGHT_QUAD': ['Light'],
            'NT_ENV_DAYLIGHT': ['Environment']
        };
        return outputMap[nodeType] || ['Output'];
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeGraphEditor;
} else if (typeof window !== 'undefined') {
    window.NodeGraphEditor = NodeGraphEditor;
}