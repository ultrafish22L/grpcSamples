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
    }
    
    async onInitialize() {
        this.initCanvas();
        this.setupControls();
        this.startRenderLoop();
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
    }
    
    initCanvas() {
        this.ctx = this.canvas.getContext('2d');
        if (!this.ctx) {
            console.error('Failed to get 2D context');
            return;
        }
        
        this.handleResize();
        console.log('Node graph canvas initialized');
    }
    
    setupControls() {
        // Prevent context menu
        this.addEventListener(this.canvas, 'contextmenu', (e) => {
            e.preventDefault();
        });
    }
    
    startRenderLoop() {
        const render = () => {
            this.render();
            requestAnimationFrame(render);
        };
        requestAnimationFrame(render);
    }
    
    render() {
        if (!this.ctx) return;
        
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
    
    drawNode(node) {
        const { x, y, width = 120, height = 80 } = node;
        const isSelected = this.selectedNodes.has(node.id);
        
        // Node background
        this.ctx.fillStyle = isSelected ? '#4a4a4a' : '#3a3a3a';
        this.ctx.strokeStyle = isSelected ? '#4a90e2' : '#555555';
        this.ctx.lineWidth = 1 / this.viewport.zoom;
        
        this.ctx.fillRect(x, y, width, height);
        this.ctx.strokeRect(x, y, width, height);
        
        // Node header
        this.ctx.fillStyle = '#404040';
        this.ctx.fillRect(x, y, width, 20);
        
        // Node title
        this.ctx.fillStyle = '#ffffff';
        this.ctx.font = `${12 / this.viewport.zoom}px Arial`;
        this.ctx.textAlign = 'center';
        this.ctx.fillText(node.name || node.type, x + width / 2, y + 14);
        
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
        const mousePos = {
            x: (e.clientX - rect.left - this.viewport.x) / this.viewport.zoom,
            y: (e.clientY - rect.top - this.viewport.y) / this.viewport.zoom
        };
        
        // Create new node at mouse position
        this.createNodeAtPosition(mousePos.x, mousePos.y);
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
        try {
            const response = await this.client.createNode('material', { x, y });
            if (response.success) {
                console.log('Node created:', response.data);
            }
        } catch (error) {
            console.error('Failed to create node:', error);
        }
    }
    
    async deleteSelectedNodes() {
        for (const nodeId of this.selectedNodes) {
            try {
                await this.client.deleteNode(nodeId);
            } catch (error) {
                console.error('Failed to delete node:', error);
            }
        }
        this.selectedNodes.clear();
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
        this.canvas.width = rect.width;
        this.canvas.height = rect.height;
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeGraphEditor;
} else if (typeof window !== 'undefined') {
    window.NodeGraphEditor = NodeGraphEditor;
}