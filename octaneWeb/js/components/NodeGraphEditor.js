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
        
        // Tooltip system for pin hover information
        this.tooltip = {
            visible: false,
            text: '',
            x: 0,
            y: 0,
            socket: null
        };
        this.hoveredSocket = null;
    }
    
    async onInitialize() {
        this.initCanvas();
        this.initNodeTypes();
        this.setupControls();
        this.setupToolbarControls(); // Add toolbar button handlers
        
        // Wait for canvas to be properly sized before starting render loop
        setTimeout(() => {
            // Don't create sample nodes - wait for real scene data from SceneOutliner
            
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
        
        // Listen for scene node selection from SceneOutliner
        this.eventSystem.on('sceneNodeSelected', (data) => {
            this.updateSelectedNode(data);
        });
        
        // Listen for scene data loaded from SceneOutliner
        this.eventSystem.on('sceneDataLoaded', (sceneItems) => {
            console.log('🎨 NodeGraphEditor received sceneDataLoaded event:', sceneItems);
            this.createRealSceneNodes(sceneItems);
            this.render();
        });
        
        // Request scene data if SceneOutliner has already loaded it
        setTimeout(() => {
            console.log('🎨 NodeGraphEditor requesting existing scene data...');
            this.eventSystem.emit('requestSceneData');
        }, 100);
        
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
        
        // Draw tooltip (after restoring context so it's not affected by viewport transform)
        this.drawTooltip();
        
        // Clean professional node graph - no debug text overlay
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
        
        // Connection color based on data type
        let connectionColor = '#888888';
        if (connection.dataType) {
            switch (connection.dataType) {
                case 'color':
                    connectionColor = '#ff6b6b';
                    break;
                case 'float':
                    connectionColor = '#4ecdc4';
                    break;
                case 'vector':
                    connectionColor = '#45b7d1';
                    break;
                case 'texture':
                    connectionColor = '#96ceb4';
                    break;
                case 'material':
                    connectionColor = '#feca57';
                    break;
                case 'geometry':
                    connectionColor = '#a8c4a2';
                    break;
                case 'camera':
                    connectionColor = '#9b59b6';
                    break;
            }
        }
        
        this.ctx.strokeStyle = connection.selected ? '#4a90e2' : connectionColor;
        this.ctx.lineWidth = 2 / this.viewport.zoom;
        
        this.ctx.beginPath();
        this.ctx.moveTo(outputPos.x, outputPos.y);
        
        // Vertical bezier curve (top to bottom connections)
        const controlOffset = 50 / this.viewport.zoom;
        this.ctx.bezierCurveTo(
            outputPos.x, outputPos.y + controlOffset,
            inputPos.x, inputPos.y - controlOffset,
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
        // Calculate Octane-style node dimensions
        const minWidth = 180; // Much wider minimum width for proper pin spacing
        const textPadding = 30;
        const nodeHeight = 32; // Slightly taller than text but still compact
        
        // Calculate width based on number of input pins for proper spacing
        const inputCount = (node.inputs && node.inputs.length) || 0;
        const minPinSpacing = 20; // Minimum space between pins
        const pinWidth = inputCount > 0 ? Math.max(minWidth, inputCount * minPinSpacing + 40) : minWidth;
        
        // Also consider text width
        this.ctx.font = `${11 / this.viewport.zoom}px Arial`;
        const textWidth = this.ctx.measureText(node.name || node.type).width;
        const textBasedWidth = textWidth + textPadding;
        
        // Use the larger of pin-based width or text-based width
        const width = Math.max(pinWidth, textBasedWidth);
        
        const { x, y } = node;
        const height = nodeHeight;
        const isSelected = this.selectedNodes.has(node.id);
        
        // Debug: Only log first few draws to avoid spam
        if (this.drawCount < 5) {
            console.log('🎨 Drawing compact Octane-style node at:', x, y, 'size:', width, height, 'type:', node.type);
            this.drawCount = (this.drawCount || 0) + 1;
        }
        
        // Professional node colors based on type (matching Octane reference)
        let nodeColor, textColor;
        switch (node.type.toLowerCase()) {
            case 'material':
                nodeColor = '#d4b896';  // Beige/tan like Octane
                textColor = '#2a2a2a';
                break;
            case 'texture':
                nodeColor = '#7ba7d4';  // Blue like Octane
                textColor = '#ffffff';
                break;
            case 'mesh':
            case 'geometry':
                nodeColor = '#a8c4a2';  // Green like Octane
                textColor = '#2a2a2a';
                break;
            default:
                nodeColor = '#8a8a8a';  // Gray default
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

        // Draw compact rounded rectangle
        const cornerRadius = 4 / this.viewport.zoom;
        this.drawRoundedRect(x, y, width, height, cornerRadius, nodeColor, true);
        this.drawRoundedRect(x, y, width, height, cornerRadius, this.ctx.strokeStyle, false);

        // Node title (centered in the compact node)
        this.ctx.fillStyle = textColor;
        this.ctx.font = `${11 / this.viewport.zoom}px Arial`;
        this.ctx.textAlign = 'center';
        this.ctx.fillText(node.name || node.type, x + width / 2, y + height / 2 + 4);
        
        // Input sockets on TOP (horizontal layout)
        if (node.inputs && node.inputs.length > 0) {
            const inputSpacing = width / (node.inputs.length + 1);
            node.inputs.forEach((input, index) => {
                const socketX = x + inputSpacing * (index + 1);
                const socketY = y;
                this.drawSocket(socketX, socketY, input, 'input');
            });
        }
        
        // Output sockets on BOTTOM (horizontal layout)
        if (node.outputs && node.outputs.length > 0) {
            const outputSpacing = width / (node.outputs.length + 1);
            node.outputs.forEach((output, index) => {
                const socketX = x + outputSpacing * (index + 1);
                const socketY = y + height;
                this.drawSocket(socketX, socketY, output, 'output');
            });
        }
        
        // Update node dimensions for hit testing
        node.width = width;
        node.height = height;
    }
    
    drawSocket(x, y, socket, type) {
        const radius = 4 / this.viewport.zoom; // Smaller sockets like Octane
        
        // Socket colors based on type (matching Octane's color coding)
        let socketColor;
        switch (socket.dataType || 'default') {
            case 'color':
                socketColor = '#ff6b6b'; // Red for color
                break;
            case 'float':
                socketColor = '#4ecdc4'; // Teal for float
                break;
            case 'vector':
                socketColor = '#45b7d1'; // Blue for vector
                break;
            case 'texture':
                socketColor = '#96ceb4'; // Green for texture
                break;
            case 'material':
                socketColor = '#feca57'; // Yellow for material
                break;
            case 'geometry':
                socketColor = '#a8c4a2'; // Green for geometry
                break;
            case 'camera':
                socketColor = '#9b59b6'; // Purple for camera
                break;
            case 'light':
                socketColor = '#f39c12'; // Orange for light
                break;
            case 'environment':
                socketColor = '#27ae60'; // Green for environment
                break;
            case 'medium':
                socketColor = '#e74c3c'; // Red for medium
                break;
            case 'kernel':
                socketColor = '#34495e'; // Dark gray for kernel
                break;
            case 'imager':
                socketColor = '#8e44ad'; // Purple for imager
                break;
            case 'postfx':
                socketColor = '#16a085'; // Teal for post effects
                break;
            default:
                socketColor = socket.connected ? '#4a90e2' : '#888888';
        }
        
        // Draw socket circle
        this.ctx.fillStyle = socketColor;
        this.ctx.beginPath();
        this.ctx.arc(x, y, radius, 0, Math.PI * 2);
        this.ctx.fill();
        
        // Add subtle border
        this.ctx.strokeStyle = '#333333';
        this.ctx.lineWidth = 1 / this.viewport.zoom;
        this.ctx.stroke();
        
        // Socket labels (optional - can be hidden for cleaner look)
        if (socket.showLabel !== false) {
            this.ctx.fillStyle = '#cccccc';
            this.ctx.font = `${8 / this.viewport.zoom}px Arial`;
            this.ctx.textAlign = 'center';
            
            // Position labels above inputs, below outputs
            const labelY = type === 'input' ? y - radius - 8 : y + radius + 12;
            this.ctx.fillText(socket.name || socket.type, x, labelY);
        }
        
        // Store socket position for connection drawing
        socket.x = x;
        socket.y = y;
    }
    
    drawTooltip() {
        if (!this.tooltip.visible || !this.tooltip.text) {
            return;
        }
        
        const padding = 8;
        const fontSize = 12;
        const borderRadius = 4;
        
        // Set font for text measurement
        this.ctx.font = `${fontSize}px Arial`;
        const textWidth = this.ctx.measureText(this.tooltip.text).width;
        const tooltipWidth = textWidth + padding * 2;
        const tooltipHeight = fontSize + padding * 2;
        
        // Position tooltip (ensure it stays within canvas bounds)
        let x = this.tooltip.x - tooltipWidth / 2;
        let y = this.tooltip.y;
        
        // Keep tooltip within canvas bounds
        if (x < 5) x = 5;
        if (x + tooltipWidth > this.canvas.width - 5) x = this.canvas.width - tooltipWidth - 5;
        if (y < tooltipHeight + 5) y = this.tooltip.y + 40; // Show below cursor if too close to top
        
        // Draw tooltip background
        this.ctx.fillStyle = 'rgba(40, 40, 40, 0.95)';
        this.ctx.strokeStyle = 'rgba(255, 255, 255, 0.3)';
        this.ctx.lineWidth = 1;
        
        // Draw rounded rectangle background (with fallback for older browsers)
        this.ctx.beginPath();
        if (this.ctx.roundRect) {
            this.ctx.roundRect(x, y - tooltipHeight, tooltipWidth, tooltipHeight, borderRadius);
        } else {
            // Fallback to regular rectangle
            this.ctx.rect(x, y - tooltipHeight, tooltipWidth, tooltipHeight);
        }
        this.ctx.fill();
        this.ctx.stroke();
        
        // Draw tooltip text
        this.ctx.fillStyle = '#ffffff';
        this.ctx.font = `${fontSize}px Arial`;
        this.ctx.textAlign = 'center';
        this.ctx.fillText(this.tooltip.text, x + tooltipWidth / 2, y - padding - 2);
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
        const rect = this.canvas.getBoundingClientRect();
        const mouseX = (e.clientX - rect.left - this.viewport.x) / this.viewport.zoom;
        const mouseY = (e.clientY - rect.top - this.viewport.y) / this.viewport.zoom;
        
        // Handle dragging
        if (this.isDragging) {
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
        } else {
            // Handle socket hover detection for tooltips
            this.updateSocketHover(mouseX, mouseY, e.clientX, e.clientY);
        }
    }
    
    updateSocketHover(mouseX, mouseY, screenX, screenY) {
        let hoveredSocket = null;
        const hoverRadius = 8; // Slightly larger than socket radius for easier hovering
        
        // Check all nodes for socket hover
        this.nodes.forEach(node => {
            // Check input sockets (on top)
            if (node.inputs && node.inputs.length > 0) {
                const inputSpacing = node.width / (node.inputs.length + 1);
                node.inputs.forEach((input, index) => {
                    const socketX = node.x + inputSpacing * (index + 1);
                    const socketY = node.y;
                    
                    const distance = Math.sqrt((mouseX - socketX) ** 2 + (mouseY - socketY) ** 2);
                    if (distance <= hoverRadius) {
                        hoveredSocket = {
                            socket: input,
                            type: 'input',
                            node: node,
                            x: socketX,
                            y: socketY
                        };
                    }
                });
            }
            
            // Check output sockets (on bottom)
            if (node.outputs && node.outputs.length > 0) {
                const outputSpacing = node.width / (node.outputs.length + 1);
                node.outputs.forEach((output, index) => {
                    const socketX = node.x + outputSpacing * (index + 1);
                    const socketY = node.y + node.height;
                    
                    const distance = Math.sqrt((mouseX - socketX) ** 2 + (mouseY - socketY) ** 2);
                    if (distance <= hoverRadius) {
                        hoveredSocket = {
                            socket: output,
                            type: 'output',
                            node: node,
                            x: socketX,
                            y: socketY
                        };
                    }
                });
            }
        });
        
        // Update tooltip state
        if (hoveredSocket) {
            const tooltipText = hoveredSocket.socket.name || `${hoveredSocket.socket.dataType || 'unknown'} ${hoveredSocket.type}`;
            this.tooltip = {
                visible: true,
                text: tooltipText,
                x: screenX,
                y: screenY - 30, // Position above cursor
                socket: hoveredSocket
            };
        } else {
            this.tooltip.visible = false;
        }
        
        this.hoveredSocket = hoveredSocket;
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
        const width = node.width || 100;
        const height = node.height || 40;
        const sockets = type === 'input' ? node.inputs : node.outputs;
        const socketIndex = sockets?.findIndex(s => s.name === socketName) || 0;
        
        if (type === 'input') {
            // Input sockets on TOP (horizontal layout)
            const inputSpacing = width / (sockets.length + 1);
            return {
                x: node.x + inputSpacing * (socketIndex + 1),
                y: node.y
            };
        } else {
            // Output sockets on BOTTOM (horizontal layout)
            const outputSpacing = width / (sockets.length + 1);
            return {
                x: node.x + outputSpacing * (socketIndex + 1),
                y: node.y + height
            };
        }
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
    
    updateSelectedNode(data) {
        console.log('🎯 NodeGraphEditor received selection:', data);
        
        // Clear existing selection
        this.selectedNodes.clear();
        
        // Find and select the corresponding node in the graph
        for (let [nodeId, node] of this.nodes) {
            if (node.sceneHandle === data.nodeId || node.name === data.nodeName) {
                this.selectedNodes.add(nodeId);
                console.log('🎯 Selected node in graph:', nodeId, node.name);
                break;
            }
        }
        
        // Re-render to show selection
        this.render();
    }
    
    createRealSceneNodes(sceneItems = []) {
        console.log('🎨 createRealSceneNodes called with:', sceneItems, 'length:', sceneItems.length);
        
        // Clear existing nodes
        this.nodes.clear();
        this.connections.clear();
        
        if (sceneItems.length === 0) {
            console.log('🎨 No scene items available - showing no data message');
            // Show "no data" message instead of creating sample nodes
            this.showNoDataMessage();
            return;
        }
        
        console.log('🎨 Creating real scene nodes from data:', sceneItems);
        
        // Create nodes based on real scene data
        let xOffset = 100;
        const yCenter = this.canvas.height / 2;
        
        sceneItems.forEach((item, index) => {
            const nodeId = `scene_${item.handle}`;
            const nodeType = this.getNodeTypeFromName(item.name);
            
            const node = {
                id: nodeId,
                name: item.name,
                type: nodeType,
                sceneHandle: item.handle,
                sceneType: item.type,
                x: xOffset,
                y: yCenter - 40 + (index * 20), // Slight vertical offset
                width: this.getNodeWidth(item.name),
                height: 80,
                inputs: this.getNodeInputs(nodeType),
                outputs: this.getNodeOutputs(nodeType)
            };
            
            this.nodes.set(nodeId, node);
            xOffset += node.width + 80; // Space between nodes
        });
        
        // Create connections between nodes (teapot.obj -> Render target)
        this.createSceneConnections(sceneItems);
        
        console.log('🎨 Created real scene nodes:', Array.from(this.nodes.keys()));
    }
    
    getNodeTypeFromName(name) {
        if (name.toLowerCase().includes('render target')) return 'render';
        if (name.toLowerCase().includes('.obj') || name.toLowerCase().includes('.fbx')) return 'geometry';
        if (name.toLowerCase().includes('camera')) return 'camera';
        if (name.toLowerCase().includes('material')) return 'material';
        return 'generic';
    }
    
    getNodeWidth(name) {
        // Octane-style wider nodes for proper pin spacing
        const baseWidth = 180;
        const charWidth = 8;
        return Math.max(baseWidth, name.length * charWidth + 60);
    }
    
    getNodeInputs(nodeType) {
        switch (nodeType) {
            case 'render':
                return [
                    { name: 'Geometry', dataType: 'geometry', connected: true, showLabel: false },
                    { name: 'Material', dataType: 'material', connected: false, showLabel: false },
                    { name: 'Environment', dataType: 'environment', connected: false, showLabel: false },
                    { name: 'Camera', dataType: 'camera', connected: false, showLabel: false },
                    { name: 'Light1', dataType: 'light', connected: false, showLabel: false },
                    { name: 'Light2', dataType: 'light', connected: false, showLabel: false },
                    { name: 'Light3', dataType: 'light', connected: false, showLabel: false },
                    { name: 'Light4', dataType: 'light', connected: false, showLabel: false },
                    { name: 'Medium', dataType: 'medium', connected: false, showLabel: false },
                    { name: 'Kernel', dataType: 'kernel', connected: false, showLabel: false },
                    { name: 'Imager', dataType: 'imager', connected: false, showLabel: false },
                    { name: 'PostFX', dataType: 'postfx', connected: false, showLabel: false }
                ];
            case 'geometry':
                return [
                    { name: 'Material', dataType: 'material', connected: false, showLabel: false }
                ];
            case 'material':
                return [
                    { name: 'Diffuse', dataType: 'color', connected: false, showLabel: false },
                    { name: 'Roughness', dataType: 'float', connected: false, showLabel: false }
                ];
            default:
                return [];
        }
    }
    
    getNodeOutputs(nodeType) {
        switch (nodeType) {
            case 'geometry':
                return [
                    { name: 'Mesh', dataType: 'geometry', connected: true, showLabel: false }
                ];
            case 'material':
                return [
                    { name: 'Material', dataType: 'material', connected: true, showLabel: false }
                ];
            case 'camera':
                return [
                    { name: 'Camera', dataType: 'camera', connected: true, showLabel: false }
                ];
            default:
                return [];
        }
    }
    
    createSceneConnections(sceneItems) {
        // Create connection from teapot.obj to Render target
        const meshNode = Array.from(this.nodes.values()).find(n => n.name.includes('.obj'));
        const renderNode = Array.from(this.nodes.values()).find(n => n.name.includes('Render target'));
        
        if (meshNode && renderNode) {
            const connectionId = `${meshNode.id}_to_${renderNode.id}`;
            this.connections.set(connectionId, {
                id: connectionId,
                outputNodeId: meshNode.id,
                inputNodeId: renderNode.id,
                outputSocket: 'Mesh',
                inputSocket: 'Geometry',
                dataType: 'geometry'
            });
            
            console.log('🔗 Created connection:', meshNode.name, '->', renderNode.name);
        }
    }
    
    showNoDataMessage() {
        // Clear the canvas and show "no data" message
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
        
        // Draw background grid (optional, for consistency)
        this.drawGrid();
        
        // Draw "no data" message in center of canvas
        const centerX = this.canvas.width / 2;
        const centerY = this.canvas.height / 2;
        
        // Draw icon
        this.ctx.font = '48px Arial';
        this.ctx.textAlign = 'center';
        this.ctx.fillStyle = '#666';
        this.ctx.fillText('📊', centerX, centerY - 40);
        
        // Draw title
        this.ctx.font = 'bold 18px Arial';
        this.ctx.fillStyle = '#ccc';
        this.ctx.fillText('No Scene Data Available', centerX, centerY + 10);
        
        // Draw subtitle
        this.ctx.font = '14px Arial';
        this.ctx.fillStyle = '#888';
        this.ctx.fillText('Connect to Octane to view scene nodes', centerX, centerY + 35);
        
        console.log('🎨 Displayed "no data" message in node graph editor');
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
    

}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeGraphEditor;
} else if (typeof window !== 'undefined') {
    window.NodeGraphEditor = NodeGraphEditor;
}