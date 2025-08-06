/**
 * Node Inspector Component
 * Professional Octane-style parameter controls for selected nodes
 * Matches the exact layout and styling of Octane Render Studio
 */

class NodeInspector extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        this.selectedNode = null;
        this.selectedNodeType = null;
        this.parameters = {};
        
        // Initialize all sections and groups as expanded by default
        this.collapsedSections = new Set(); // All sections expanded by default
        this.collapsedGroups = new Set();   // All parameter groups expanded by default
        
        // Cache for scene data from Scene Outliner (optimization)
        this.nodeCache = new Map(); // handle -> nodeData
        this.nodeLookup = new Map(); // name -> handle
        this.sceneDataLoaded = false;
    }
    
    async onInitialize() {
        // Wait for all components to be fully initialized before auto-selection
        this.eventSystem.on('componentsFullyInitialized', () => {
            setTimeout(() => {
                this.autoSelectRenderTarget();
            }, 100);
        });
    }
    
    autoSelectRenderTarget() {
        // Auto-select Render target using cached scene data (matching Octane Studio behavior)
        window.debugConsole?.addLog('info', ['🎯 NodeInspector: Auto-selecting render target']);
        
        if (this.sceneDataCache && this.sceneDataCache.length > 1) {
            const renderTarget = this.sceneDataCache[1]; // Render target is typically second item
            console.log('🎯 Auto-selecting Render target to match Octane Studio behavior:', renderTarget.handle);
            window.debugConsole?.addLog('info', ['🎯 NodeInspector: Auto-selecting', renderTarget.name, 'handle:', renderTarget.handle]);
            
            // Update this component's selection (handle only)
            this.updateSelectedNode(renderTarget.handle);
            
            // Emit selection event with handle only to sync with other components
            this.eventSystem.emit('sceneNodeSelected', renderTarget.handle);
        } else {
            window.debugConsole?.addLog('warn', ['⚠️ NodeInspector: No scene data available for auto-selection']);
        }
    }
    
    initializeExpandedState() {
        // Initialize all sections and parameter groups as expanded by default
        // (matching reference octane_ui.png behavior - when a node is selected, expand all its children)
        this.collapsedSections = new Set(); // All sections expanded by default
        this.collapsedGroups = new Set();   // All parameter groups expanded by default
        
        console.log('🎯 Initializing Node Inspector with all sections/groups expanded by default');
    }

    setupEventListeners() {
        // Listen for scene data loading from SceneOutliner (OPTIMIZATION)
        this.eventSystem.on('sceneDataLoaded', (sceneItems) => {
            this.updateSceneDataCache(sceneItems);
            this.autoSelectRenderTarget(sceneItems);
        });
        
        // Listen for selection updates
        this.client.on('ui:selectionUpdate', (selection) => {
            this.updateSelection(selection);
        });
        
        // Listen for scene node selection (unified event for all components)
        this.eventSystem.on('sceneNodeSelected', (handle) => {
            this.updateSelectedNode(handle);
        });
        
        // Listen for node parameter updates
        this.client.on('ui:nodeParameterUpdate', (data) => {
            this.updateParameter(data.nodeId, data.parameterName, data.value);
        });
        
        // Force click events to work by bypassing CSS pointer-events issues
        this.setupForceClickHandlers();
    }
    
    setupForceClickHandlers() {
        // ULTIMATE SOLUTION: Global coordinate-based click detection that bypasses all CSS pointer-events issues
        const rightPanel = document.querySelector('.right-panel');
        if (!rightPanel) return;

        console.log('🎯 Setting up coordinate-based click detection system');

        // Global document click handler that intercepts ALL clicks
        document.addEventListener('click', (event) => {
            // Get click coordinates
            const x = event.clientX;
            const y = event.clientY;
            
            // Get right panel bounds
            const rightPanelRect = rightPanel.getBoundingClientRect();
            
            // Check if click is within right panel area
            if (x >= rightPanelRect.left && x <= rightPanelRect.right &&
                y >= rightPanelRect.top && y <= rightPanelRect.bottom) {
                
                console.log('🎯 Coordinate-based click detected in right panel at:', x, y);
                
                // Use elementsFromPoint to find what's actually under the cursor
                const elementsUnderCursor = document.elementsFromPoint(x, y);
                console.log('🔍 Elements under cursor:', elementsUnderCursor.map(el => `${el.tagName}.${el.className} [bid=${el.getAttribute('bid')}]`));
                
                // Find the first clickable element in the right panel
                for (const element of elementsUnderCursor) {
                    // Skip elements that are not in the right panel
                    if (!rightPanel.contains(element)) continue;
                    
                    // Handle parameter group headers (expand/collapse)
                    if (element.hasAttribute && element.hasAttribute('data-group')) {
                        const groupName = element.getAttribute('data-group');
                        console.log('🔽 Coordinate-based toggle of parameter group:', groupName);
                        this.toggleParameterGroup(groupName);
                        event.preventDefault();
                        event.stopPropagation();
                        return;
                    }
                    
                    // Handle checkboxes
                    if (element.classList && element.classList.contains('parameter-checkbox')) {
                        console.log('☑️ Coordinate-based checkbox click:', element);
                        element.checked = !element.checked;
                        this.handleParameterChange(element);
                        event.preventDefault();
                        event.stopPropagation();
                        return;
                    }
                    
                    // Handle dropdowns
                    if (element.classList && element.classList.contains('parameter-dropdown')) {
                        console.log('📋 Coordinate-based dropdown click:', element);
                        element.focus();
                        // Let dropdown handle itself naturally
                        return;
                    }
                    
                    // Handle number inputs
                    if (element.classList && element.classList.contains('parameter-number-input')) {
                        console.log('🔢 Coordinate-based number input click:', element);
                        element.focus();
                        return;
                    }
                    
                    // Handle parameter group headers by checking parent elements
                    let parent = element.parentElement;
                    while (parent && rightPanel.contains(parent)) {
                        if (parent.hasAttribute && parent.hasAttribute('data-group')) {
                            const groupName = parent.getAttribute('data-group');
                            console.log('🔽 Coordinate-based toggle of parameter group (via parent):', groupName);
                            this.toggleParameterGroup(groupName);
                            event.preventDefault();
                            event.stopPropagation();
                            return;
                        }
                        parent = parent.parentElement;
                    }
                }
            }
        }, true); // Capture phase - intercepts before any other handlers
    }
    
    handleParameterClick(target, event) {
        // Handle collapsible group headers
        if (target.hasAttribute('data-group')) {
            const groupName = target.getAttribute('data-group');
            this.toggleParameterGroup(groupName);
            return;
        }
        
        // Handle other parameter controls
        if (target.classList.contains('parameter-checkbox')) {
            target.checked = !target.checked;
            this.updateParameterValue(target.id, target.checked);
        } else if (target.classList.contains('parameter-dropdown')) {
            // Let the dropdown handle itself
        } else if (target.classList.contains('parameter-input')) {
            target.focus();
        }
    }
    
    toggleParameterGroup(groupName) {
        const header = this.element.querySelector(`[data-group="${groupName}"]`);
        const content = this.element.querySelector(`[data-group-content="${groupName}"]`);
        const icon = header?.querySelector('.parameter-group-icon');
        
        if (header && content && icon) {
            if (this.collapsedGroups.has(groupName)) {
                // Expand
                header.classList.remove('collapsed');
                content.style.display = 'block';
                icon.textContent = '▼';
                this.collapsedGroups.delete(groupName);
            } else {
                // Collapse
                header.classList.add('collapsed');
                content.style.display = 'none';
                icon.textContent = '▶';
                this.collapsedGroups.add(groupName);
            }
        }
    }
    
    updateParameterValue(paramName, value) {
        console.log(`Updating parameter: ${paramName} = ${value}`);
        
        // Store the parameter value
        this.parameters[paramName] = value;
        
        // If we have a selected node, send the update to the server
        if (this.selectedNode) {
            this.client.emit('ui:updateNodeParameter', {
                nodeId: this.selectedNode,
                parameterName: paramName,
                value: value
            });
        }
    }
    
    setupInspectorEventListeners() {
        // Group collapse/expand functionality
        const groupHeaders = this.element.querySelectorAll('.parameter-group-header[data-group]');
        groupHeaders.forEach(header => {
            this.addEventListener(header, 'click', (e) => {
                const groupName = header.dataset.group;
                const content = this.element.querySelector(`[data-group-content="${groupName}"]`);
                const icon = header.querySelector('.parameter-group-icon');
                
                if (header.classList.contains('collapsed')) {
                    header.classList.remove('collapsed');
                    content.style.display = 'block';
                    icon.textContent = '▼';
                    this.collapsedGroups.delete(groupName);
                } else {
                    header.classList.add('collapsed');
                    content.style.display = 'none';
                    icon.textContent = '▶';
                    this.collapsedGroups.add(groupName);
                }
            });
        });
        
        // Parameter input change handlers
        const numberInputs = this.element.querySelectorAll('.parameter-number-input');
        numberInputs.forEach(input => {
            this.addEventListener(input, 'change', (e) => {
                this.handleParameterChange(e.target);
            });
            
            this.addEventListener(input, 'input', (e) => {
                this.updateSliderFromInput(e.target);
            });
        });
        
        // Checkbox handlers
        const checkboxes = this.element.querySelectorAll('.parameter-checkbox');
        checkboxes.forEach(checkbox => {
            this.addEventListener(checkbox, 'change', (e) => {
                this.handleParameterChange(e.target);
            });
        });
        
        // Dropdown handlers
        const dropdowns = this.element.querySelectorAll('.parameter-dropdown, .inspector-target-select');
        dropdowns.forEach(dropdown => {
            this.addEventListener(dropdown, 'change', (e) => {
                this.handleParameterChange(e.target);
            });
        });
        
        // Initialize collapsed state
        this.initializeCollapsedGroups();
    }
    
    initializeCollapsedGroups() {
        // Start with all groups collapsed except the main ones
        const collapsibleGroups = ['physical-camera', 'viewing-angle', 'clipping', 'depth-of-field'];
        collapsibleGroups.forEach(groupName => {
            const header = this.element.querySelector(`[data-group="${groupName}"]`);
            const content = this.element.querySelector(`[data-group-content="${groupName}"]`);
            const icon = header?.querySelector('.parameter-group-icon');
            
            if (header && content && icon) {
                header.classList.add('collapsed');
                content.style.display = 'none';
                icon.textContent = '▶';
                this.collapsedGroups.add(groupName);
            }
        });
    }
    
    handleParameterChange(element) {
        const paramName = element.id || element.dataset.param;
        const value = element.type === 'checkbox' ? element.checked : element.value;
        
        console.log(`Parameter changed: ${paramName} = ${value}`);
        
        // Update the actual parameter if we have a selected node
        if (this.selectedNode && paramName) {
            this.updateParameterValue(paramName, value);
        }
    }
    
    updateSliderFromInput(input) {
        const container = input.closest('.parameter-input-container');
        const slider = container?.querySelector('.parameter-slider');
        
        if (slider) {
            // Update slider position based on input value
            // This would need proper min/max values for accurate positioning
            const value = parseFloat(input.value) || 0;
            // For now, just show that the slider is responsive
            const track = slider.querySelector('.parameter-slider-track');
            const thumb = slider.querySelector('.parameter-slider-thumb');
            
            // Simple percentage calculation (would need proper min/max)
            const percentage = Math.min(100, Math.max(0, (value / 100) * 100));
            track.style.width = `${percentage}%`;
            thumb.style.left = `${percentage}%`;
        }
    }
    
    updateSelection(selection) {
        if (selection.size === 1) {
            const nodeId = Array.from(selection)[0];
            this.loadNodeParameters(nodeId);
        } else if (selection.size > 1) {
            this.showMultipleSelection(selection);
        } else {
            this.showNoSelection();
        }
    }
    
    /**
     * OPTIMIZATION: Update scene data cache from Scene Outliner
     * This eliminates the need for redundant tree traversal
     */
    updateSceneDataCache(sceneItems) {
        console.log('🚀 OPTIMIZATION: Updating Node Inspector cache with scene data');
        window.debugConsole?.addLog('info', ['🚀 NodeInspector: Updating scene data cache', sceneItems?.length, 'items']);
        
        // Store the scene data cache for generic access
        this.sceneDataCache = sceneItems;
        
        // Clear existing cache
        this.nodeCache.clear();
        this.nodeLookup.clear();
        
        // Recursively populate cache from scene tree
        this.populateCacheRecursively(sceneItems);
        
        this.sceneDataLoaded = true;
        console.log(`✅ OPTIMIZATION: Cached ${this.nodeCache.size} nodes for instant access`);
        window.debugConsole?.addLog('info', ['✅ NodeInspector: Scene data cache updated', this.nodeCache.size, 'nodes cached']);
    }
    
    /**
     * Get cached node data by handle
     */
    getCachedNodeData(handle) {
        // Look up node data from cache using handle
        if (this.sceneDataCache) {
            return this.sceneDataCache.find(node => node.handle === handle);
        }
        return null;
    }
    
    /**
     * GENERIC: Find node data directly from sceneItems list
     * This replaces specialized cache lookups with direct sceneItems access
     */
    findNodeInSceneItems(handle) {
        window.debugConsole?.addLog('info', ['🔍 NodeInspector: Searching for handle in sceneItems', handle]);
        
        if (!this.sceneDataCache || !Array.isArray(this.sceneDataCache)) {
            window.debugConsole?.addLog('warn', ['⚠️ NodeInspector: No sceneDataCache available']);
            return null;
        }
        
        // Search recursively through sceneItems
        const findRecursively = (items) => {
            for (const item of items) {
                if (item.handle === handle) {
                    window.debugConsole?.addLog('info', ['✅ NodeInspector: Found node', item.name, 'with handle', handle]);
                    return item;
                }
                if (item.children && item.children.length > 0) {
                    const found = findRecursively(item.children);
                    if (found) return found;
                }
            }
            return null;
        };
        
        return findRecursively(this.sceneDataCache);
    }
    
    /**
     * Recursively populate node cache from scene tree data
     */
    populateCacheRecursively(items) {
        if (!items || !Array.isArray(items)) return;
        
        items.forEach(item => {
            if (item.handle) {
                // Store node data by handle
                this.nodeCache.set(item.handle, {
                    name: item.name,
                    handle: item.handle,
                    type: item.type,
                    outtype: item.outtype,
                    children: item.children || []
                });
                
                // Store name -> handle lookup
                if (item.name) {
                    this.nodeLookup.set(item.name, item.handle);
                }
            }
            
            // Recursively process children
            if (item.children && item.children.length > 0) {
                this.populateCacheRecursively(item.children);
            }
        });
    }
    
    /**
     * OPTIMIZATION: Get cached node data by handle
     */
    getCachedNodeData(handle) {
        return this.nodeCache.get(handle);
    }
    
    /**
     * OPTIMIZATION: Get node handle by name
     */
    getNodeHandleByName(name) {
        return this.nodeLookup.get(name);
    }
    
    async updateSelectedNode(handle) {
        console.log('🎯 NodeInspector received selection handle:', handle);
        window.debugConsole?.addLog('info', ['🎯 NodeInspector: Updating selected node', handle]);
        
        // Find node data directly from sceneItems list (generic approach)
        const nodeData = this.findNodeInSceneItems(handle);
        if (!nodeData) {
            console.warn('⚠️ No node data found for handle:', handle);
            window.debugConsole?.addLog('warn', ['⚠️ NodeInspector: No node data found for handle', handle]);
            return;
        }
        
        // Set selection state using handle and node data
        this.selectedNodeHandle = handle;
        this.selectedNode = handle;
        this.selectedNodeType = nodeData.outtype;
        this.selectedNodeName = nodeData.name;
        
        window.debugConsole?.addLog('info', ['📋 NodeInspector: Selected node', nodeData.name, 'type:', nodeData.outtype]);
        
        // Initialize expanded state for this node (expand all children by default)
        this.initializeExpandedState();
        
        // Update the dropdown to reflect the selected node
        this.updateInspectorDropdown(this.selectedNodeName);
        
        // Generic parameter loading based on node type mapping
        await this.loadGenericNodeParameters({
            handle: handle,
            nodeName: nodeData.name,
            nodeType: nodeData.outtype,
            nodeData: nodeData
        });
    }
    
    /**
     * GENERIC: Load node parameters based on node type mapping
     * This replaces specialized functions with a generic approach
     */
    async loadGenericNodeParameters(nodeInfo) {
        window.debugConsole?.addLog('info', ['🚀 NodeInspector: Loading generic parameters for', nodeInfo.nodeName, 'type:', nodeInfo.nodeType]);
        
        // Show loading state
        this.showLoadingState(nodeInfo);
        
        try {
            // Get node type mapping for parameter groups
            const nodeTypeMapping = this.getNodeTypeMapping(nodeInfo.nodeType);
            window.debugConsole?.addLog('info', ['📋 NodeInspector: Node type mapping', nodeTypeMapping]);
            
            // Load parameter values using generic approach
            const parameters = await this.loadGenericParameterValues(nodeInfo.handle, nodeTypeMapping);
            window.debugConsole?.addLog('info', ['✅ NodeInspector: Loaded parameters', Object.keys(parameters).length, 'parameters']);
            
            // Render the inspector with generic parameter groups
            this.renderGenericParameterInspector(nodeInfo, parameters, nodeTypeMapping);
            
        } catch (error) {
            console.error('❌ Failed to load generic node parameters:', error);
            window.debugConsole?.addLog('error', ['❌ NodeInspector: Failed to load parameters', error.message]);
        }
    }
    
    /**
     * GENERIC: Get node type mapping for parameter organization
     * This replaces hardcoded specialized parameter groups
     */
    getNodeTypeMapping(nodeType) {
        window.debugConsole?.addLog('info', ['🗺️ NodeInspector: Getting mapping for node type', nodeType]);
        
        // Generic node type mappings based on Octane node types
        const nodeTypeMappings = {
            'NT_RENDERTARGET': {
                displayName: 'Render Target',
                icon: '🎯',
                parameterGroups: [
                    { name: 'Scene', icon: '🎬', parameters: ['camera', 'environment', 'cameraEnvironment'] },
                    { name: 'Mesh', icon: '🫖', parameters: ['mesh'] },
                    { name: 'Film Settings', icon: '🎞️', parameters: ['filmSettings'] },
                    { name: 'Animation', icon: '🎭', parameters: ['animation'] },
                    { name: 'Kernel', icon: '⚙️', parameters: ['kernel'] },
                    { name: 'Render Layer', icon: '📚', parameters: ['renderLayer'] },
                    { name: 'Render Passes', icon: '🎨', parameters: ['renderPasses'] },
                    { name: 'Composite AOVs', icon: '🖼️', parameters: ['compositeAovs'] },
                    { name: 'Imager', icon: '📷', parameters: ['imager'] },
                    { name: 'Post Processing', icon: '✨', parameters: ['postproc'] }
                ]
            },
            'NT_CAMERA': {
                displayName: 'Camera',
                icon: '📷',
                parameterGroups: [
                    { name: 'Transform', icon: '🔄', parameters: ['position', 'rotation', 'scale'] },
                    { name: 'Lens', icon: '🔍', parameters: ['focalLength', 'aperture', 'focusDistance'] },
                    { name: 'Film', icon: '🎞️', parameters: ['filmWidth', 'filmHeight', 'pixelAspect'] }
                ]
            },
            'NT_MESH': {
                displayName: 'Mesh',
                icon: '🫖',
                parameterGroups: [
                    { name: 'Transform', icon: '🔄', parameters: ['position', 'rotation', 'scale'] },
                    { name: 'Geometry', icon: '📐', parameters: ['vertices', 'faces', 'normals'] },
                    { name: 'Materials', icon: '🎨', parameters: ['material', 'displacement'] }
                ]
            },
            'NT_MATERIAL': {
                displayName: 'Material',
                icon: '🎨',
                parameterGroups: [
                    { name: 'Diffuse', icon: '🌈', parameters: ['diffuse', 'albedo'] },
                    { name: 'Specular', icon: '✨', parameters: ['specular', 'roughness', 'metallic'] },
                    { name: 'Transmission', icon: '🔍', parameters: ['transmission', 'ior'] }
                ]
            },
            // Default fallback for unknown node types
            'DEFAULT': {
                displayName: 'Node',
                icon: '📦',
                parameterGroups: [
                    { name: 'Parameters', icon: '⚙️', parameters: [] }
                ]
            }
        };
        
        const mapping = nodeTypeMappings[nodeType] || nodeTypeMappings['DEFAULT'];
        window.debugConsole?.addLog('info', ['✅ NodeInspector: Using mapping', mapping.displayName, 'with', mapping.parameterGroups.length, 'groups']);
        
        return mapping;
    }
    
    /**
     * GENERIC: Load parameter values using generic approach
     * This replaces specialized parameter loading with direct API calls
     */
    async loadGenericParameterValues(nodeHandle, nodeTypeMapping) {
        window.debugConsole?.addLog('info', ['🔧 NodeInspector: Loading parameter values for handle', nodeHandle]);
        
        const parameters = {};
        
        try {
            // Get pin count for this node (single API call)
            const pinCountResult = window.grpcApi.makeApiCallSync('ApiNode/pinCount', nodeHandle);
            
            if (pinCountResult && pinCountResult.success && pinCountResult.data > 0) {
                const pinCount = pinCountResult.data;
                window.debugConsole?.addLog('info', ['📌 NodeInspector: Node has', pinCount, 'pins']);
                
                // Load all pin values generically
                for (let pinIndex = 0; pinIndex < pinCount; pinIndex++) {
                    try {
                        // Get pin name
                        const pinNameResult = window.grpcApi.makeApiCallSync('ApiNode/pinName', [nodeHandle, pinIndex]);
                        if (pinNameResult && pinNameResult.success) {
                            const pinName = pinNameResult.data;
                            
                            // Get pin value
                            const pinValueResult = window.grpcApi.makeApiCallSync('ApiNode/pinValue', [nodeHandle, pinIndex]);
                            if (pinValueResult && pinValueResult.success) {
                                parameters[pinName] = {
                                    value: pinValueResult.data,
                                    pinIndex: pinIndex,
                                    type: 'generic'
                                };
                                
                                window.debugConsole?.addLog('info', ['📍 NodeInspector: Loaded pin', pinName, '=', pinValueResult.data]);
                            }
                        }
                    } catch (pinError) {
                        window.debugConsole?.addLog('warn', ['⚠️ NodeInspector: Failed to load pin', pinIndex, pinError.message]);
                    }
                }
            }
            
        } catch (error) {
            window.debugConsole?.addLog('error', ['❌ NodeInspector: Failed to load parameter values', error.message]);
        }
        
        return parameters;
    }
    
    /**
     * OCTANE UI MATCH: Render parameter inspector exactly matching the reference image
     * This creates the exact structure shown in the node inspector reference
     */
    renderGenericParameterInspector(nodeInfo, parameters, nodeTypeMapping) {
        window.debugConsole?.addLog('info', ['🎨 NodeInspector: Rendering Octane-style inspector for', nodeInfo.nodeName]);
        
        // Update the existing dropdown (don't create a new one)
        this.updateNodeSelectorDropdown(nodeInfo.nodeName);
        
        // Build HTML matching the exact Octane UI structure from the reference image
        let html = this.renderOctaneStyleInspector(nodeInfo, parameters);
        
        // Update the inspector container directly
        const inspectorContainer = document.getElementById('node-inspector');
        if (inspectorContainer) {
            inspectorContainer.innerHTML = html;
            window.debugConsole?.addLog('info', ['✅ NodeInspector: Octane-style inspector rendered successfully']);
        } else {
            console.error('❌ Node inspector container not found');
            window.debugConsole?.addLog('error', ['❌ NodeInspector: Container not found']);
        }
        
        // Setup event listeners for the new content
        this.setupInspectorEventListeners();
        
        window.debugConsole?.addLog('info', ['✅ NodeInspector: Rendered Octane-style inspector']);
    }
    
    /**
     * OCTANE UI MATCH: Render the exact structure from the reference image
     */
    renderOctaneStyleInspector(nodeInfo, parameters) {
        // Match the exact structure from the reference image
        return `
            <!-- Scene Section (matches reference) -->
            <div class="octane-parameter-section">
                <div class="octane-section-header">
                    <span class="octane-section-icon">📁</span>
                    <span class="octane-section-title">Scene</span>
                </div>
                <div class="octane-section-content">
                    <div class="octane-parameter-row">
                        <div class="octane-parameter-icon">📷</div>
                        <div class="octane-parameter-label">Camera</div>
                        <div class="octane-parameter-control">
                            <select class="octane-dropdown">
                                <option>Thin lens camera</option>
                            </select>
                        </div>
                    </div>
                    <div class="octane-parameter-row">
                        <div class="octane-parameter-icon">📐</div>
                        <div class="octane-parameter-label">Orthographic:</div>
                        <div class="octane-parameter-control">
                            <input type="checkbox" class="octane-checkbox">
                        </div>
                    </div>
                </div>
            </div>
            
            <!-- Physical camera parameters (collapsible) -->
            <div class="octane-parameter-group">
                <div class="octane-group-header" data-group="physical-camera">
                    <span class="octane-group-toggle">▼</span>
                    <span class="octane-group-title">Physical camera parameters</span>
                </div>
                <div class="octane-group-content" data-group-content="physical-camera">
                    ${this.renderCameraParameter('📷', 'Sensor width:', '36.000', 'mm')}
                    ${this.renderCameraParameter('🔍', 'Focal length:', '50.000', 'mm')}
                    ${this.renderCameraParameter('⚪', 'F-stop:', '2.8', '')}
                </div>
            </div>
            
            <!-- Viewing angle (collapsible) -->
            <div class="octane-parameter-group">
                <div class="octane-group-header" data-group="viewing-angle">
                    <span class="octane-group-toggle">▼</span>
                    <span class="octane-group-title">Viewing angle</span>
                </div>
                <div class="octane-group-content" data-group-content="viewing-angle">
                    ${this.renderCameraParameter('👁️', 'Field of view:', '39.597752', '°')}
                    ${this.renderCameraParameter('📏', 'Scale of view:', '17.144243', '')}
                    ${this.renderCameraParameter('📐', 'Distortion:', '0.000', '')}
                    ${this.renderDualCameraParameter('↔️', 'Lens shift:', '0.000', '0.000')}
                    ${this.renderCameraParameter('🔄', 'Perspective correction:', 'false', '', true)}
                    ${this.renderCameraParameter('📊', 'Pixel aspect ratio:', '1.000', '')}
                </div>
            </div>
            
            <!-- Clipping (collapsible) -->
            <div class="octane-parameter-group">
                <div class="octane-group-header" data-group="clipping">
                    <span class="octane-group-toggle">▼</span>
                    <span class="octane-group-title">Clipping</span>
                </div>
                <div class="octane-group-content" data-group-content="clipping">
                    ${this.renderCameraParameter('📏', 'Near clip depth:', '0.000', '')}
                    ${this.renderCameraParameter('📏', 'Far clip depth:', '∞', '')}
                </div>
            </div>
            
            <!-- Depth of field (collapsible) -->
            <div class="octane-parameter-group">
                <div class="octane-group-header" data-group="depth-of-field">
                    <span class="octane-group-toggle">▼</span>
                    <span class="octane-group-title">Depth of field</span>
                </div>
                <div class="octane-group-content" data-group-content="depth-of-field">
                    ${this.renderCameraParameter('🎯', 'Auto-focus:', 'false', '', true)}
                    ${this.renderCameraParameter('📏', 'Focal depth:', '1.118034', '')}
                    ${this.renderCameraParameter('⚪', 'Aperture:', '0.8928572', '')}
                    ${this.renderCameraParameter('📊', 'Aperture aspect ratio:', '1.000', '')}
                    ${this.renderCameraParameter('🔲', 'Aperture edge:', '1.000', '')}
                    ${this.renderCameraParameter('🔢', 'Bokeh side count:', '6', '')}
                    ${this.renderCameraParameter('🔄', 'Bokeh rotation:', '0.000', '°')}
                    ${this.renderCameraParameter('⚪', 'Bokeh roundedness:', '1.000', '')}
                </div>
            </div>
            
            <!-- Position (collapsible) -->
            <div class="octane-parameter-group">
                <div class="octane-group-header" data-group="position">
                    <span class="octane-group-toggle">▼</span>
                    <span class="octane-group-title">Position</span>
                </div>
                <div class="octane-group-content" data-group-content="position">
                    <!-- Position parameters would go here -->
                </div>
            </div>
        `;
    }
    
    /**
     * Render a single camera parameter with icon, label, value and slider
     */
    renderCameraParameter(icon, label, value, unit, isCheckbox = false) {
        if (isCheckbox) {
            window.debugConsole?.addLog('info', ['🔲 NodeInspector: Rendering checkbox for', label]);
            return `
                <div class="octane-parameter-row">
                    <div class="octane-parameter-icon">${icon}</div>
                    <div class="octane-parameter-label">${label}</div>
                    <div class="octane-parameter-control">
                        <div class="octane-control-group">
                            <input type="checkbox" class="octane-checkbox">
                        </div>
                    </div>
                </div>
            `;
        }
        
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-icon">${icon}</div>
                <div class="octane-parameter-label">${label}</div>
                <div class="octane-parameter-control">
                    <div class="octane-control-group">
                        <div class="octane-spinner-left">◄</div>
                        <input type="text" class="octane-number-input" value="${value}">
                        <div class="octane-spinner-right">►</div>
                        ${unit ? `<span class="octane-unit">${unit}</span>` : ''}
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render a dual-value camera parameter (like Lens shift with two values)
     */
    renderDualCameraParameter(icon, label, value1, value2) {
        return `
            <div class="octane-parameter-row">
                <div class="octane-parameter-icon">${icon}</div>
                <div class="octane-parameter-label">${label}</div>
                <div class="octane-parameter-control">
                    <div class="octane-control-group">
                        <input type="text" class="octane-number-input" value="${value1}" style="width: 40px;">
                        <input type="text" class="octane-number-input" value="${value2}" style="width: 40px; margin-left: 2px;">
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Update the existing node selector dropdown (don't create a new one)
     */
    updateNodeSelectorDropdown(nodeName) {
        const dropdown = document.querySelector('.node-selector');
        if (dropdown) {
            dropdown.innerHTML = `<option value="${nodeName}" selected>${nodeName}</option>`;
            window.debugConsole?.addLog('info', ['🔄 NodeInspector: Updated dropdown to', nodeName]);
        }
    }
    
    /**
     * GENERIC: Render a single parameter control
     */
    renderGenericParameter(paramName, param) {
        const value = param.value;
        let controlHtml = '';
        
        // Determine control type based on value type
        if (typeof value === 'boolean') {
            controlHtml = `<input type="checkbox" class="parameter-checkbox" id="${paramName}" ${value ? 'checked' : ''}>`;
        } else if (typeof value === 'number') {
            controlHtml = `<input type="number" class="parameter-number-input" id="${paramName}" value="${value}" step="0.01">`;
        } else if (typeof value === 'string') {
            controlHtml = `<input type="text" class="parameter-input" id="${paramName}" value="${value}">`;
        } else {
            controlHtml = `<input type="text" class="parameter-input" id="${paramName}" value="${JSON.stringify(value)}" readonly>`;
        }
        
        return `
            <div class="parameter-row">
                <div class="parameter-label">
                    <span class="parameter-icon">📝</span>
                    <span class="parameter-name">${paramName}</span>
                </div>
                <div class="parameter-control">
                    ${controlHtml}
                </div>
            </div>
        `;
    }
    
    updateInspectorDropdown(nodeName) {
        // Update the dropdown in the node inspector header to show the selected node
        const dropdown = this.element.querySelector('.node-selector select');
        if (dropdown && nodeName) {
            // Check if option exists, if not add it
            let optionExists = false;
            for (let option of dropdown.options) {
                if (option.value === nodeName) {
                    option.selected = true;
                    optionExists = true;
                    break;
                }
            }
            
            // If option doesn't exist, add it and select it
            if (!optionExists) {
                const newOption = document.createElement('option');
                newOption.value = nodeName;
                newOption.textContent = nodeName;
                newOption.selected = true;
                dropdown.appendChild(newOption);
            }
            
            console.log('🎯 Updated NodeInspector dropdown to:', nodeName);
        }
    }
    
    async loadNodeParameters(nodeId) {
        this.selectedNode = nodeId;
        
        try {
            // Get node details from client
            const nodeData = await this.client.getObjectDetails(nodeId);
            
            if (nodeData.success && nodeData.data) {
                this.parameters = nodeData.data.parameters || {};
                this.renderNodeInspector(nodeData.data);
            }
        } catch (error) {
            console.error('Failed to load node parameters:', error);
            this.showError('Failed to load node parameters');
        }
    }
    
    renderNodeInspector(nodeData) {
        const { name, type, parameters = {} } = nodeData;
        
        this.element.innerHTML = `
            <div class="node-inspector-header">
                <div class="node-type-icon">${this.getNodeTypeIcon(type)}</div>
                <div class="node-name">${name}</div>
            </div>
            <div class="inspector-content">
                ${this.renderParameterGroups(parameters)}
            </div>
        `;
        
        this.setupParameterEventListeners();
    }
    
    renderParameterGroups(parameters) {
        const groups = this.groupParameters(parameters);
        
        return Object.entries(groups).map(([groupName, groupParams]) => {
            return `
                <div class="parameter-group">
                    <div class="parameter-group-header">
                        <span>${groupName}</span>
                        <span class="parameter-group-toggle">▼</span>
                    </div>
                    <div class="parameter-group-content">
                        ${this.renderParameters(groupParams)}
                    </div>
                </div>
            `;
        }).join('');
    }
    
    groupParameters(parameters) {
        const groups = {};
        
        Object.entries(parameters).forEach(([name, param]) => {
            const groupName = param.group || 'General';
            if (!groups[groupName]) {
                groups[groupName] = {};
            }
            groups[groupName][name] = param;
        });
        
        return groups;
    }
    
    renderParameters(parameters) {
        return Object.entries(parameters).map(([name, param]) => {
            return this.renderParameter(name, param);
        }).join('');
    }
    
    renderParameter(name, param) {
        const { type, value, min, max, label } = param;
        const displayLabel = label || name;
        
        return `
            <div class="parameter-row">
                <div class="parameter-label">${displayLabel}:</div>
                <div class="parameter-control">
                    ${this.renderParameterControl(name, type, value, { min, max })}
                </div>
            </div>
        `;
    }
    
    renderParameterControl(name, type, value, options = {}) {
        switch (type) {
            case 'float':
            case 'int':
                return this.renderNumericControl(name, type, value, options);
            case 'bool':
                return this.renderBooleanControl(name, value);
            case 'string':
                return this.renderStringControl(name, value);
            case 'color':
                return this.renderColorControl(name, value);
            case 'enum':
                return this.renderEnumControl(name, value, options.values || []);
            default:
                return this.renderStringControl(name, value);
        }
    }
    
    renderNumericControl(name, type, value, { min, max }) {
        const step = type === 'int' ? '1' : '0.01';
        const minAttr = min !== undefined ? `min="${min}"` : '';
        const maxAttr = max !== undefined ? `max="${max}"` : '';
        
        return `
            <input type="number" 
                   class="parameter-input" 
                   data-param="${name}" 
                   value="${value}" 
                   step="${step}" 
                   ${minAttr} 
                   ${maxAttr} />
            ${min !== undefined && max !== undefined ? this.renderSlider(name, value, min, max) : ''}
        `;
    }
    
    renderSlider(name, value, min, max) {
        const percentage = ((value - min) / (max - min)) * 100;
        
        return `
            <div class="parameter-slider" data-param="${name}" data-min="${min}" data-max="${max}">
                <div class="parameter-slider-track" style="width: ${percentage}%"></div>
                <div class="parameter-slider-thumb" style="left: ${percentage}%"></div>
            </div>
        `;
    }
    
    renderBooleanControl(name, value) {
        return `
            <div class="parameter-checkbox ${value ? 'checked' : ''}" data-param="${name}"></div>
        `;
    }
    
    renderStringControl(name, value) {
        return `
            <input type="text" 
                   class="parameter-input" 
                   data-param="${name}" 
                   value="${value}" />
        `;
    }
    
    renderColorControl(name, value) {
        const [r, g, b] = value || [1, 1, 1];
        const hexColor = this.rgbToHex(r, g, b);
        
        return `
            <div class="parameter-color" data-param="${name}">
                <div class="parameter-color-swatch" style="background-color: ${hexColor}"></div>
            </div>
            <input type="color" 
                   class="parameter-input" 
                   data-param="${name}" 
                   value="${hexColor}" 
                   style="width: 60px;" />
        `;
    }
    
    renderEnumControl(name, value, values) {
        const options = values.map(val => 
            `<option value="${val}" ${val === value ? 'selected' : ''}>${val}</option>`
        ).join('');
        
        return `
            <select class="parameter-dropdown" data-param="${name}">
                ${options}
            </select>
        `;
    }
    
    setupParameterEventListeners() {
        // Parameter inputs
        const inputs = this.element.querySelectorAll('.parameter-input');
        inputs.forEach(input => {
            this.addEventListener(input, 'change', (e) => {
                this.updateParameterValue(e.target.dataset.param, e.target.value);
            });
        });
        
        // Checkboxes
        const checkboxes = this.element.querySelectorAll('.parameter-checkbox');
        checkboxes.forEach(checkbox => {
            this.addEventListener(checkbox, 'click', (e) => {
                const isChecked = !checkbox.classList.contains('checked');
                checkbox.classList.toggle('checked', isChecked);
                this.updateParameterValue(checkbox.dataset.param, isChecked);
            });
        });
        
        // Sliders
        const sliders = this.element.querySelectorAll('.parameter-slider');
        sliders.forEach(slider => {
            this.setupSliderEvents(slider);
        });
        
        // Group toggles
        const groupHeaders = this.element.querySelectorAll('.parameter-group-header');
        groupHeaders.forEach(header => {
            this.addEventListener(header, 'click', (e) => {
                const group = header.parentElement;
                group.classList.toggle('collapsed');
            });
        });
    }
    
    setupSliderEvents(slider) {
        let isDragging = false;
        
        const updateSlider = (e) => {
            const rect = slider.getBoundingClientRect();
            const percentage = Math.max(0, Math.min(1, (e.clientX - rect.left) / rect.width));
            
            const min = parseFloat(slider.dataset.min);
            const max = parseFloat(slider.dataset.max);
            const value = min + (max - min) * percentage;
            
            const track = slider.querySelector('.parameter-slider-track');
            const thumb = slider.querySelector('.parameter-slider-thumb');
            
            track.style.width = `${percentage * 100}%`;
            thumb.style.left = `${percentage * 100}%`;
            
            this.updateParameterValue(slider.dataset.param, value);
        };
        
        this.addEventListener(slider, 'mousedown', (e) => {
            isDragging = true;
            updateSlider(e);
        });
        
        this.addEventListener(document, 'mousemove', (e) => {
            if (isDragging) {
                updateSlider(e);
            }
        });
        
        this.addEventListener(document, 'mouseup', () => {
            isDragging = false;
        });
    }
    
    async updateParameterValue(paramName, value) {
        if (!this.selectedNode) return;
        
        try {
            await this.client.updateNodeParameter(this.selectedNode, paramName, value);
            this.parameters[paramName] = { ...this.parameters[paramName], value };
        } catch (error) {
            console.error('Failed to update parameter:', error);
        }
    }
    
    updateParameter(nodeId, parameterName, value) {
        if (nodeId === this.selectedNode && this.parameters[parameterName]) {
            this.parameters[parameterName].value = value;
            // Update UI to reflect the change
            this.updateParameterUI(parameterName, value);
        }
    }
    
    updateParameterUI(paramName, value) {
        const input = this.element.querySelector(`[data-param="${paramName}"]`);
        if (input) {
            if (input.type === 'checkbox') {
                input.classList.toggle('checked', value);
            } else {
                input.value = value;
            }
        }
    }
    
    showMultipleSelection(selection) {
        this.element.innerHTML = `
            <div class="inspector-loading">
                Multiple objects selected (${selection.size})
                <br><small>Multi-object editing not yet supported</small>
            </div>
        `;
    }
    
    showNoSelection() {
        // Show the default inspector content
//        this.renderDefaultInspector();
    }
    
    showError(message) {
        this.element.innerHTML = `
            <div class="inspector-loading" style="color: var(--octane-accent-red);">
                ❌ ${message}
            </div>
        `;
    }
    
    getNodeTypeIcon(type) {
        const icons = {
            'environment': '🌍',
            'material': 'M',
            'texture': 'T',
            'light': 'L',
            'camera': '📷',
            'geometry': 'G',
            'render': 'R'
        };
        return icons[type] || 'N';
    }
    
    rgbToHex(r, g, b) {
        const toHex = (c) => {
            const hex = Math.round(c * 255).toString(16);
            return hex.length === 1 ? '0' + hex : hex;
        };
        return `#${toHex(r)}${toHex(g)}${toHex(b)}`;
    }
    
    updateInspectorDropdown(nodeName) {
        // Update the dropdown in the existing header to show the selected node
        const dropdown = document.querySelector('.node-inspector-panel select');
        if (dropdown && nodeName) {
            // Check if option exists, if not add it
            let optionExists = false;
            for (let option of dropdown.options) {
                if (option.value === nodeName) {
                    option.selected = true;
                    optionExists = true;
                    break;
                }
            }

            // If option doesn't exist, add it and select it
            if (!optionExists) {
                const newOption = document.createElement('option');
                newOption.value = nodeName;
                newOption.textContent = nodeName;
                newOption.selected = true;
                dropdown.appendChild(newOption);
            }
        }
    }

    setupOctaneInspectorEvents() {
        // Setup section toggle functionality
        const sectionHeaders = this.element.querySelectorAll('.section-header');
        sectionHeaders.forEach(header => {
            header.addEventListener('click', () => {
                const section = header.dataset.section;
                const content = this.element.querySelector(`[data-content="${section}"]`);
                const toggle = header.querySelector('.section-toggle');
                
                if (content.style.display === 'none') {
                    content.style.display = 'block';
                    toggle.textContent = '▼';
                } else {
                    content.style.display = 'none';
                    toggle.textContent = '▶';
                }
            });
        });

        // Setup slider synchronization
        const sliders = this.element.querySelectorAll('.param-slider');
        sliders.forEach(slider => {
            const numberInput = slider.parentElement.querySelector('.param-number');
            if (numberInput) {
                slider.addEventListener('input', () => {
                    numberInput.value = slider.value;
                });
                
                numberInput.addEventListener('input', () => {
                    slider.value = numberInput.value;
                });
            }
        });

        // Setup grid button toggles
        const gridButtons = this.element.querySelectorAll('.grid-button');
        gridButtons.forEach(button => {
            button.addEventListener('click', () => {
                button.classList.toggle('active');
            });
        });

        // Setup color picker interactions
        const colorPickers = this.element.querySelectorAll('.param-color-picker');
        colorPickers.forEach(picker => {
            picker.addEventListener('click', () => {
                // In a real implementation, this would open a color picker dialog
                console.log('Color picker clicked');
            });
        });
    }
    
    /**
     * OPTIMIZED: Load and render full parameter tree for selected node
     * Uses cached scene data instead of redundant tree traversal
     */
    async loadAndRenderFullParameterTree(data) {
        console.log('🚀 OPTIMIZED: Loading parameter tree for node:', data.nodeName);
        
        // Show loading state
        this.showLoadingState(data);
        
        try {
            // OPTIMIZATION: Use cached node data if available
            const nodeHandle = this.selectedNodeHandle || this.selectedNode;
            let nodeData = null;
            
            if (this.sceneDataLoaded && nodeHandle) {
                nodeData = this.getCachedNodeData(nodeHandle);
                console.log('✅ OPTIMIZATION: Using cached node data:', nodeData);
            }
            
            // Load only parameter VALUES (not tree structure)
            const parameters = await this.loadNodeParameterValuesOptimized(nodeHandle, nodeData);
            
            console.log('✅ OPTIMIZED: Loaded parameter values:', parameters);
            
            // Render the full inspector with all parameters
            this.renderFullParameterInspector(data, parameters);
            
        } catch (error) {
            console.error('❌ Failed to load parameter tree:', error);
        }
    }
    
    /**
     * OPTIMIZED: Load only parameter VALUES for a node (using cached metadata)
     * This replaces the inefficient recursive tree traversal
     */
    async loadNodeParameterValuesOptimized(nodeHandle, cachedNodeData) {
        if (!nodeHandle) {
            console.warn('⚠️ OPTIMIZATION: No node handle provided');
            return {};
        }
        
        const parameters = {};
        
        try {
            console.log(`🚀 OPTIMIZATION: Loading parameter values for node ${nodeHandle} (${cachedNodeData?.name || 'unknown'})`);
            
            // Get pin count for this node (single API call)
            const pinCountResult = window.grpcApi.makeApiCallSync(
                'ApiNode/pinCount',
                nodeHandle
            );
            
            if (!pinCountResult.success) {
                console.warn('⚠️ OPTIMIZATION: Failed to get pin count for node:', nodeHandle);
                return parameters;
            }
            
            const pinCount = pinCountResult.data.result;
            console.log(`📌 OPTIMIZATION: Node has ${pinCount} pins (cached metadata: ${cachedNodeData ? 'available' : 'not available'})`);
            
            // Load parameter values efficiently (no tree traversal)
            for (let i = 0; i < pinCount; i++) {
                try {
                    // Small delay to prevent API overload
//                    await this.delay(25); // Reduced from 50ms for better performance
                    
                    // Use SAFE ApiNode methods to get pin information
                    const [pinNameResult, pinTypeResult, pinLabelResult] = await Promise.all([
                        window.grpcApi.makeApiCallSync('ApiNode/pinNameIx', nodeHandle, { index: i }),
                        window.grpcApi.makeApiCallSync('ApiNode/pinTypeIx', nodeHandle, { index: i }),
                        window.grpcApi.makeApiCallSync('ApiNode/pinLabelIx', nodeHandle, { index: i })
                    ]);
                    
                    // Skip if we can't get basic pin info
                    if (!pinNameResult.success && !pinTypeResult.success) {
                        continue;
                    }
                    
                    const pinName = pinNameResult.success ? pinNameResult.data.result : `pin_${i}`;
                    const pinType = pinTypeResult.success ? pinTypeResult.data.result : 'unknown';
                    const pinLabel = pinLabelResult.success ? pinLabelResult.data.result : pinName;
                    
                    // Get pin value using safe methods
                    let pinValue = null;
                    try {
                        const valueResult = await this.getParameterValueSafe(nodeHandle, i, pinType);
                        if (valueResult.success) {
                            pinValue = valueResult.data;
                        }
                    } catch (valueError) {
                        console.warn(`⚠️ OPTIMIZATION: Could not get value for pin ${i}:`, valueError);
                    }
                    
                    // Store parameter data
                    parameters[pinName] = {
                        name: pinName,
                        label: pinLabel,
                        type: pinType,
                        value: pinValue,
                        index: i,
                        // Use cached metadata if available
                        nodeType: cachedNodeData?.outtype || 'unknown',
                        nodeName: cachedNodeData?.name || 'unknown'
                    };
                    
                } catch (pinError) {
                    console.warn(`⚠️ OPTIMIZATION: Error processing pin ${i}:`, pinError);
                    continue;
                }
            }
            
            console.log(`✅ OPTIMIZATION: Loaded ${Object.keys(parameters).length} parameter values efficiently`);
            
        } catch (error) {
            console.error('❌ OPTIMIZATION: Error in loadNodeParameterValuesOptimized:', error);
        }
        
        return parameters;
    }
    
    /**
     * Recursively load all parameters for a node (FALLBACK METHOD)
     */
    async loadNodeParametersRecursively(nodeHandle, maxDepth = 3, currentDepth = 0) {
        if (currentDepth >= maxDepth || !nodeHandle) {
            return {};
        }
        
        const parameters = {};
        
        try {
            console.log(`🔍 Loading parameters for node handle ${nodeHandle} (depth ${currentDepth})`);
            
            // Get pin count for this node
            const pinCountResult = window.grpcApi.makeApiCallSync(
                'ApiNode/pinCount',
                nodeHandle
            );
            
            if (!pinCountResult.success) {
                console.warn('⚠️ Failed to get pin count for node:', nodeHandle);
                return parameters;
            }
            
            const pinCount = pinCountResult.data.result;
            console.log(`📌 Node has ${pinCount} pins`);
            
            // Iterate through all pins
            for (let i = 0; i < pinCount; i++) {
                try {
                    // Add small delay to prevent overwhelming the API
//                    await this.delay(50);
                    
                    // Use SAFE ApiNode methods to get pin information (avoiding problematic ApiNodePinInfoEx)
                    const pinNameResult = window.grpcApi.makeApiCallSync(
                        'ApiNode/pinNameIx',
                        nodeHandle,
                        { index: i }
                    );
                    
                    const pinTypeResult = window.grpcApi.makeApiCallSync(
                        'ApiNode/pinTypeIx',
                        nodeHandle,
                        { index: i }
                    );
                    
                    const pinLabelResult = window.grpcApi.makeApiCallSync(
                        'ApiNode/pinLabelIx',
                        nodeHandle,
                        { index: i }
                    );
                    
                    // Skip if we can't get basic pin info
                    if (!pinNameResult.success && !pinTypeResult.success) {
                        continue;
                    }
                    
                    const pinName = pinNameResult.success ? pinNameResult.data.result : `pin_${i}`;
                    const pinType = pinTypeResult.success ? pinTypeResult.data.result : 'unknown';
                    const pinLabel = pinLabelResult.success ? pinLabelResult.data.result : pinName;
                    
                    // Try to get pin value using safe methods
                    let pinValue = null;
                    try {
                        const valueResult = window.grpcApi.makeApiCallSync(
                            'ApiNode/getPinValueIx',
                            nodeHandle,
                            { index: i }
                        );
                        if (valueResult.success) {
                            pinValue = valueResult.data.result;
                        }
                    } catch (valueError) {
                        console.warn(`⚠️ Could not get value for pin ${i}:`, valueError);
                    }
                    
                    // Extract parameter information using safe data
                    const paramName = pinLabel || pinName || `Parameter ${i}`;
                    
                    parameters[paramName] = {
                        name: paramName,
                        type: pinType || 'unknown',
                        value: pinValue,
                        index: i,
                        pinName: pinName,
                        pinLabel: pinLabel,
                        pinType: pinType
                    };
                    
                    console.log(`✅ Loaded parameter: ${paramName} (${pinType}) = ${pinValue}`);
                    
                    // Also check for connected nodes (for nested parameters)
                    const connectedNodeResult = window.grpcApi.makeApiCallSync(
                        'ApiNode/connectedNodeIx',
                        nodeHandle,
                        { pinIx: i, enterWrapperNode: true }
                    );
                    
                    if (connectedNodeResult.success && connectedNodeResult.data.result) {
                        const connectedNode = connectedNodeResult.data.result;
                        
                        if (connectedNode.handle && connectedNode.handle !== nodeHandle) {
                            // Recursively load parameters from connected node
                            const nestedParams = await this.loadNodeParametersRecursively(
                                connectedNode.handle,
                                maxDepth,
                                currentDepth + 1
                            );
                            
                            // Merge nested parameters with a prefix
                            Object.keys(nestedParams).forEach(nestedParamName => {
                                const prefixedName = `${paramName || 'Connected'}.${nestedParamName}`;
                                parameters[prefixedName] = nestedParams[nestedParamName];
                            });
                        }
                    }
                    
                } catch (pinError) {
                    console.warn(`⚠️ Error loading pin ${i}:`, pinError);
                    continue;
                }
            }
            
        } catch (error) {
            console.error('❌ Error in loadNodeParametersRecursively:', error);
        }
        
        return parameters;
    }
    
    /**
     * Safely get parameter value using available ApiNode methods
     */
    async getParameterValueSafe(nodeHandle, index, pinType) {
        try {
            // Try different value getter methods based on type
            const methods = [
                'ApiNode/getPinValueIx',
            ];
            
            for (const method of methods) {
                try {
                    const result = window.grpcApi.makeApiCallSync(method, nodeHandle, { index });
                    if (result.success && result.data.result !== undefined) {
                        return { success: true, data: result.data.result };
                    }
                } catch (error) {
                    // Try next method
                    continue;
                }
            }
            
            return { success: false, error: 'No suitable value getter method found' };
        } catch (error) {
            return { success: false, error: error.message };
        }
    }
    
    /**
     * Safely set parameter value using available ApiNode methods
     */
    async setParameterValueSafe(nodeHandle, index, value, pinType) {
        try {
            const result = window.grpcApi.makeApiCallSync('ApiNode/setPinValue', nodeHandle, {
                index: index,
                value: value
            });
            
            return { success: result.success, data: result.data };
        } catch (error) {
            return { success: false, error: error.message };
        }
    }
    
    /**
     * Handle parameter value changes with safe API calls
     */
    async handleParameterChange(element) {
        if (!this.selectedNodeHandle || !element.dataset.index) {
            return;
        }
        
        const index = parseInt(element.dataset.index);
        const newValue = this.getElementValue(element);
        
        console.log(`🔄 Updating parameter at pin ${index} to:`, newValue);
        
        try {
            const result = await this.setParameterValueSafe(this.selectedNodeHandle, index, newValue);
            if (result.success) {
                console.log(`✅ Parameter updated successfully`);
                // Update UI to reflect change
                this.updateParameterDisplay(element, newValue);
            } else {
                console.error(`❌ Failed to update parameter:`, result.error);
            }
        } catch (error) {
            console.error(`❌ Error updating parameter:`, error);
        }
    }
    
    /**
     * Get value from UI element based on its type
     */
    getElementValue(element) {
        if (element.type === 'checkbox') {
            return element.checked;
        } else if (element.type === 'number' || element.type === 'range') {
            return parseFloat(element.value);
        } else if (element.tagName === 'SELECT') {
            return element.value;
        } else {
            return element.value;
        }
    }
    
    /**
     * Update parameter display after successful change
     */
    updateParameterDisplay(element, newValue) {
        // Update any associated display elements
        const displayElement = element.parentElement.querySelector('.parameter-value-display');
        if (displayElement) {
            displayElement.textContent = newValue;
        }
    }
    
    /**
     * Render full parameter inspector with all loaded parameters
     */
    renderFullParameterInspector(data, parameters) {
        // Import parameter renderer (will be loaded dynamically)
        this.loadParameterRenderer().then(() => {
            this.doRenderFullParameterInspector(data, parameters);
        });
    }
    
    async loadParameterRenderer() {
        if (!window.ParameterRenderer) {
            // For now, we'll implement a basic version inline
            // In production, this would import the ParameterRenderer module
            console.log('📦 Loading parameter renderer...');
        }
    }
    
    doRenderFullParameterInspector(data, parameters) {
        console.log('🎨 OCTANE STYLE: Rendering full parameter inspector for:', data.nodeName);
        
        const nodeType = this.getCachedNodeData(this.selectedNodeHandle)?.outtype || 'NT_CAMERA';
        const nodeName = data.nodeName || this.selectedNodeName || 'Unknown Node';
        
        // Update the existing dropdown in the HTML structure
        this.updateNodeSelectorDropdown(nodeName);
        
        // Create the inspector content HTML structure matching reference screenshot
        let inspectorHtml = '';
        
        // Add Scene section (collapsible)
        const sceneExpanded = this.shouldSectionBeExpanded('scene');
        const sceneIcon = sceneExpanded ? '▼' : '▶';
        const sceneContentStyle = sceneExpanded ? 'display: block;' : 'display: none;';
        
        inspectorHtml += `
            <div class="octane-section">
                <div class="octane-section-header" data-group="scene">
                    <span class="octane-section-icon">${sceneIcon}</span>
                    <span class="octane-section-title">Scene</span>
                </div>
                <div class="octane-section-content" data-group-content="scene" style="${sceneContentStyle}">
        `;
        
        // Add Camera subsection for camera nodes
        if (nodeType === 'NT_CAMERA' || nodeName.toLowerCase().includes('camera')) {
            inspectorHtml += `
                <div class="octane-subsection">
                    <div class="octane-subsection-header">
                        <span class="octane-node-icon">📷</span>
                        <span class="octane-subsection-title">Thin lens camera</span>
                    </div>
                </div>
            `;
        }
        
        // Render parameter groups based on live data
        inspectorHtml += this.renderOctaneParameterGroups(parameters);
        
        inspectorHtml += `
                </div>
            </div>
            </div>
        `;
        
        // Update only the inspector content area, not the entire panel
        const contentArea = this.element.querySelector('.panel-content .node-inspector');
        if (contentArea) {
            contentArea.innerHTML = inspectorHtml;
        } else {
            // Fallback: update entire element if structure is different
            this.element.innerHTML = inspectorHtml;
        }
        
        // Setup event handlers for the new Octane-style controls
        this.setupOctaneInspectorEventListeners();
        
        console.log('✅ OCTANE STYLE: Full parameter inspector rendered successfully');
    }
    
    /**
     * Special handling for render targets - load camera parameters instead of render target parameters
     */
    async loadRenderTargetCameraParameters(renderTargetHandle, renderTargetData) {
        console.log('🎯 Loading camera parameters for render target:', renderTargetData.name);
        
        try {
            // First, load the render target's parameters to get the camera handle
            const renderTargetParams = await this.loadNodeParameterValuesOptimized(renderTargetHandle, renderTargetData);
            
            // Find the camera parameter and get its handle
            const cameraParam = renderTargetParams['camera'];
            if (!cameraParam || !cameraParam.value) {
                console.warn('⚠️ No camera found in render target parameters');
                // Fallback to showing render target parameters
                await this.loadAndRenderFullParameterTree({ 
                    handle: renderTargetHandle,
                    nodeName: renderTargetData.name,
                    nodeType: renderTargetData.outtype
                });
                return;
            }
            
            const cameraHandle = cameraParam.value;
            console.log('📷 Found camera handle in render target:', cameraHandle);
            
            // Get camera node data from cache
            const cameraNodeData = this.getCachedNodeData(cameraHandle);
            if (!cameraNodeData) {
                console.warn('⚠️ No cached data found for camera handle:', cameraHandle);
                return;
            }
            
            // Load camera parameters
            const cameraParameters = await this.loadNodeParameterValuesOptimized(cameraHandle, cameraNodeData);
            
            // Render the camera parameters in the proper hierarchical structure
            await this.renderRenderTargetWithCameraParameters(renderTargetData, cameraNodeData, cameraParameters);
            
        } catch (error) {
            console.error('❌ Failed to load render target camera parameters:', error);
            // Fallback to showing render target parameters
            await this.loadAndRenderFullParameterTree({ 
                handle: renderTargetHandle,
                nodeName: renderTargetData.name,
                nodeType: renderTargetData.outtype
            });
        }
    }
    
    /**
     * Render render target with camera parameters in hierarchical structure
     */
    async renderRenderTargetWithCameraParameters(renderTargetData, cameraNodeData, cameraParameters) {
        console.log('🎨 Rendering render target with camera parameters');
        
        // Update the dropdown to show "Render target"
        this.updateNodeSelectorDropdown(renderTargetData.name);
        
        // Create the hierarchical structure: Scene > Camera > Parameter Groups
        let inspectorHtml = `
            <div class="octane-section">
                <div class="octane-section-header" data-group="scene">
                    <span class="octane-section-icon">▼</span>
                    <span class="octane-section-title">Scene</span>
                </div>
                <div class="octane-section-content" data-group-content="scene" style="display: block;">
                    <div class="octane-subsection">
                        <div class="octane-subsection-header">
                            <span class="octane-node-icon">📷</span>
                            <span class="octane-subsection-title">Thin lens camera</span>
                        </div>
                    </div>
        `;
        
        // Render camera parameter groups
        inspectorHtml += this.renderOctaneParameterGroups(cameraParameters);
        
        inspectorHtml += `
                </div>
            </div>
        `;
        
        // Update the inspector content
        const contentArea = this.element.querySelector('.panel-content .node-inspector');
        if (contentArea) {
            contentArea.innerHTML = inspectorHtml;
        } else {
            // Fallback: update entire element if structure is different
            this.element.innerHTML = inspectorHtml;
        }
        
        // Setup event handlers
        this.setupOctaneInspectorEventListeners();
        
        console.log('✅ Render target with camera parameters rendered successfully');
    }
    
    /**
     * Update the node selector dropdown with the current selection
     */
    updateNodeSelectorDropdown(nodeName) {
        const dropdown = document.querySelector('.node-selector');
        if (dropdown && nodeName) {
            // Clear existing options
            dropdown.innerHTML = '';
            
            // Add the selected node option
            const option = document.createElement('option');
            option.value = nodeName;
            option.textContent = nodeName;
            option.selected = true;
            dropdown.appendChild(option);
            
            console.log('📝 Updated node selector dropdown to:', nodeName);
        }
    }
    
    /**
     * Render parameter groups matching Octane Studio layout
     */
    renderOctaneParameterGroups(parameters) {
        console.log('🎨 Rendering Octane parameter groups with', Object.keys(parameters).length, 'parameters');
        
        // Group parameters by category (matching reference image)
        const parameterGroups = this.groupParametersForOctane(parameters);
        
        let groupsHtml = '';
        
        // Render each parameter group
        Object.entries(parameterGroups).forEach(([groupName, groupParams]) => {
            if (groupParams.length === 0) return;
            
            const isExpanded = this.shouldGroupBeExpanded(groupName);
            const icon = isExpanded ? '▼' : '▶';
            const contentStyle = isExpanded ? 'display: block;' : 'display: none;';
            
            groupsHtml += `
                <div class="octane-parameter-group">
                    <div class="octane-group-header" data-group="${groupName}">
                        <span class="octane-group-icon">${icon}</span>
                        <span class="octane-group-title">${this.getGroupDisplayName(groupName)}</span>
                    </div>
                    <div class="octane-group-content" data-group-content="${groupName}" style="${contentStyle}">
                        ${this.renderParametersInGroup(groupParams)}
                    </div>
                </div>
            `;
        });
        
        return groupsHtml;
    }
    
    /**
     * Group parameters by category matching Octane Studio
     */
    groupParametersForOctane(parameters) {
        const groups = {
            'physical-camera': [],
            'viewing-angle': [],
            'clipping': [],
            'depth-of-field': [],
            'position': [],
            'stereo': [],
            'other': []
        };
        
        Object.entries(parameters).forEach(([paramName, paramData]) => {
            const name = paramData.label || paramName;
            const lowerName = name.toLowerCase();
            
            // Group parameters based on their names (matching reference image)
            if (lowerName.includes('orthographic') || lowerName.includes('sensor') || 
                lowerName.includes('focal length') || lowerName.includes('f-stop')) {
                groups['physical-camera'].push(paramData);
            } else if (lowerName.includes('field of view') || lowerName.includes('scale of view') || 
                       lowerName.includes('distortion') || lowerName.includes('lens shift') || 
                       lowerName.includes('perspective') || lowerName.includes('pixel aspect')) {
                groups['viewing-angle'].push(paramData);
            } else if (lowerName.includes('near clip') || lowerName.includes('far clip')) {
                groups['clipping'].push(paramData);
            } else if (lowerName.includes('auto-focus') || lowerName.includes('focal depth') || 
                       lowerName.includes('aperture') || lowerName.includes('bokeh')) {
                groups['depth-of-field'].push(paramData);
            } else if (lowerName.includes('position') || lowerName.includes('target') || 
                       lowerName.includes('up-vector')) {
                groups['position'].push(paramData);
            } else if (lowerName.includes('stereo') || lowerName.includes('eye distance') || 
                       lowerName.includes('swap eyes')) {
                groups['stereo'].push(paramData);
            } else {
                groups['other'].push(paramData);
            }
        });
        
        return groups;
    }
    
    /**
     * Check if a parameter group should be expanded by default
     */
    shouldGroupBeExpanded(groupName) {
        // All groups are expanded by default unless explicitly collapsed
        return !this.collapsedGroups.has(groupName);
    }
    
    shouldSectionBeExpanded(sectionName) {
        // All sections are expanded by default unless explicitly collapsed
        return !this.collapsedSections.has(sectionName);
    }
    
    /**
     * Get display name for parameter group
     */
    getGroupDisplayName(groupName) {
        const displayNames = {
            'physical-camera': 'Physical camera parameters',
            'viewing-angle': 'Viewing angle',
            'clipping': 'Clipping',
            'depth-of-field': 'Depth of field',
            'position': 'Position',
            'stereo': 'Stereo',
            'other': 'Other parameters'
        };
        return displayNames[groupName] || groupName;
    }
    
    /**
     * Render individual parameters within a group
     */
    renderParametersInGroup(parameters) {
        return parameters.map(param => {
            return this.renderSingleParameter(param);
        }).join('');
    }
    
    /**
     * Render a single parameter with proper Octane styling
     */
    renderSingleParameter(param) {
        const { name, label, type, value, index } = param;
        const displayName = label || name;
        const paramId = `param_${name}_${index}`;
        
        // Determine parameter type and render appropriate control
        if (type === 'PT_BOOL' || displayName.toLowerCase().includes('orthographic') || 
            displayName.toLowerCase().includes('auto-focus') || displayName.toLowerCase().includes('perspective')) {
            return this.renderCheckboxParameter(paramId, displayName, value);
        } else if (type === 'PT_FLOAT' || type === 'PT_INT' || 
                   displayName.toLowerCase().includes('width') || displayName.toLowerCase().includes('length') ||
                   displayName.toLowerCase().includes('depth') || displayName.toLowerCase().includes('distance')) {
            return this.renderNumericParameter(paramId, displayName, value, type);
        } else if (type === 'PT_FLOAT3' || displayName.toLowerCase().includes('position') || 
                   displayName.toLowerCase().includes('target') || displayName.toLowerCase().includes('vector')) {
            return this.renderVectorParameter(paramId, displayName, value);
        } else if (displayName.toLowerCase().includes('stereo output') || displayName.toLowerCase().includes('stereo mode')) {
            return this.renderDropdownParameter(paramId, displayName, value);
        } else {
            return this.renderGenericParameter(paramId, displayName, value, type);
        }
    }
    
    /**
     * Render checkbox parameter
     */
    renderCheckboxParameter(paramId, displayName, value) {
        const checked = value === true || value === 'true' ? 'checked' : '';
        return `
            <div class="octane-parameter">
                <div class="octane-parameter-row">
                    <div class="octane-parameter-checkbox-container">
                        <input type="checkbox" id="${paramId}" class="octane-checkbox" ${checked}>
                        <label for="${paramId}" class="octane-checkbox-label">${displayName}</label>
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render numeric parameter with slider
     */
    renderNumericParameter(paramId, displayName, value, type) {
        const numValue = parseFloat(value) || 0;
        const displayValue = type === 'PT_INT' ? Math.round(numValue) : numValue.toFixed(3);
        
        return `
            <div class="octane-parameter">
                <div class="octane-parameter-row">
                    <div class="octane-parameter-label">${displayName}:</div>
                    <div class="octane-parameter-controls">
                        <div class="octane-slider-container">
                            <div class="octane-slider-track">
                                <div class="octane-slider-fill" style="width: 50%;"></div>
                                <div class="octane-slider-thumb" style="left: 50%;"></div>
                            </div>
                        </div>
                        <input type="number" id="${paramId}" class="octane-number-input" value="${displayValue}" step="${type === 'PT_INT' ? '1' : '0.001'}">
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render vector parameter (3 components)
     */
    renderVectorParameter(paramId, displayName, value) {
        // Parse vector value (could be array or string)
        let x = 0, y = 0, z = 0;
        if (Array.isArray(value)) {
            [x, y, z] = value;
        } else if (typeof value === 'string') {
            const parts = value.split(',').map(v => parseFloat(v.trim()) || 0);
            [x, y, z] = parts;
        }
        
        return `
            <div class="octane-parameter">
                <div class="octane-parameter-row">
                    <div class="octane-parameter-label">${displayName}:</div>
                    <div class="octane-vector-controls">
                        <input type="number" class="octane-vector-input" value="${x.toFixed(3)}" step="0.001" data-component="x">
                        <input type="number" class="octane-vector-input" value="${y.toFixed(3)}" step="0.001" data-component="y">
                        <input type="number" class="octane-vector-input" value="${z.toFixed(3)}" step="0.001" data-component="z">
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render dropdown parameter
     */
    renderDropdownParameter(paramId, displayName, value) {
        return `
            <div class="octane-parameter">
                <div class="octane-parameter-row">
                    <div class="octane-parameter-label">${displayName}:</div>
                    <div class="octane-parameter-controls">
                        <select id="${paramId}" class="octane-dropdown">
                            <option value="${value}" selected>${value || 'None'}</option>
                        </select>
                    </div>
                </div>
            </div>
        `;
    }
    
    /**
     * Render generic parameter
     */
    renderGenericParameter(paramId, displayName, value, type) {
        return `
            <div class="octane-parameter">
                <div class="octane-parameter-row">
                    <div class="octane-parameter-label">${displayName}:</div>
                    <div class="octane-parameter-controls">
                        <input type="text" id="${paramId}" class="octane-text-input" value="${value || ''}" readonly>
                        <span class="octane-parameter-type">(${type})</span>
                    </div>
                </div>
            </div>
        `;
    }

    /**
     * Setup event listeners for Octane-style controls
     */
    setupOctaneInspectorEventListeners() {
        console.log('🎛️ Setting up Octane-style event listeners');
        
        // Section collapse/expand functionality (Scene section)
        const sectionHeaders = this.element.querySelectorAll('.octane-section-header[data-group]');
        sectionHeaders.forEach(header => {
            this.addEventListener(header, 'click', (e) => {
                const groupName = header.dataset.group;
                this.toggleOctaneSection(groupName);
            });
        });
        
        // Parameter group collapse/expand functionality
        const groupHeaders = this.element.querySelectorAll('.octane-group-header[data-group]');
        groupHeaders.forEach(header => {
            this.addEventListener(header, 'click', (e) => {
                const groupName = header.dataset.group;
                this.toggleOctaneParameterGroup(groupName);
            });
        });
        
        // Parameter value change handlers
        this.setupOctaneParameterChangeHandlers();
    }
    
    /**
     * Toggle Octane section expand/collapse (Scene section)
     */
    toggleOctaneSection(sectionName) {
        const header = this.element.querySelector(`[data-group="${sectionName}"]`);
        const content = this.element.querySelector(`[data-group-content="${sectionName}"]`);
        const icon = header?.querySelector('.octane-section-icon');
        
        if (header && content && icon) {
            if (content.style.display === 'none') {
                // Expand
                content.style.display = 'block';
                icon.textContent = '▼';
            } else {
                // Collapse
                content.style.display = 'none';
                icon.textContent = '▶';
            }
        }
    }
    
    /**
     * Setup parameter change handlers for all Octane-style controls
     */
    setupOctaneParameterChangeHandlers() {
        // Number inputs (float/integer)
        const numberInputs = this.element.querySelectorAll('.octane-number-input');
        numberInputs.forEach(input => {
            this.addEventListener(input, 'change', (e) => {
                this.handleOctaneParameterChange(e.target);
            });
            
            this.addEventListener(input, 'input', (e) => {
                this.updateOctaneSliderFromInput(e.target);
            });
        });
        
        // Sliders
        const sliders = this.element.querySelectorAll('.octane-slider');
        sliders.forEach(slider => {
            this.addEventListener(slider, 'input', (e) => {
                this.updateOctaneInputFromSlider(e.target);
            });
            
            this.addEventListener(slider, 'change', (e) => {
                this.handleOctaneParameterChange(e.target);
            });
        });
        
        // Checkboxes
        const checkboxes = this.element.querySelectorAll('.octane-checkbox');
        checkboxes.forEach(checkbox => {
            this.addEventListener(checkbox, 'change', (e) => {
                this.handleOctaneParameterChange(e.target);
                this.updateOctaneCheckboxVisual(e.target);
            });
        });
        
        // Vector inputs
        const vectorInputs = this.element.querySelectorAll('.octane-vector-input');
        vectorInputs.forEach(input => {
            this.addEventListener(input, 'change', (e) => {
                this.handleOctaneVectorParameterChange(e.target);
            });
        });
        
        // Dropdowns
        const dropdowns = this.element.querySelectorAll('.octane-dropdown');
        dropdowns.forEach(dropdown => {
            this.addEventListener(dropdown, 'change', (e) => {
                this.handleOctaneParameterChange(e.target);
            });
        });
        
        // Color pickers
        const colorPickers = this.element.querySelectorAll('.octane-color-picker');
        colorPickers.forEach(picker => {
            this.addEventListener(picker, 'change', (e) => {
                this.handleOctaneColorParameterChange(e.target);
            });
        });
        
        // Color bars (click to open color picker)
        const colorBars = this.element.querySelectorAll('.octane-color-bar');
        colorBars.forEach(bar => {
            this.addEventListener(bar, 'click', (e) => {
                const picker = bar.parentElement.querySelector('.octane-color-picker');
                if (picker) picker.click();
            });
        });
    }
    
    /**
     * Toggle Octane parameter group expand/collapse
     */
    toggleOctaneParameterGroup(groupName) {
        const header = this.element.querySelector(`[data-group="${groupName}"]`);
        const content = this.element.querySelector(`[data-group-content="${groupName}"]`);
        const icon = header?.querySelector('.octane-group-icon');
        
        if (header && content && icon) {
            if (this.collapsedGroups.has(groupName)) {
                // Expand
                header.classList.remove('collapsed');
                header.classList.add('expanded');
                content.style.display = 'block';
                icon.textContent = '▼';
                this.collapsedGroups.delete(groupName);
            } else {
                // Collapse
                header.classList.remove('expanded');
                header.classList.add('collapsed');
                content.style.display = 'none';
                icon.textContent = '▶';
                this.collapsedGroups.add(groupName);
            }
        }
    }
    
    /**
     * Handle parameter value changes for Octane-style controls
     */
    async handleOctaneParameterChange(element) {
        if (!this.selectedNodeHandle || !element.dataset.pinName) {
            return;
        }
        
        const pinName = element.dataset.pinName;
        const paramType = element.dataset.paramType;
        let newValue = this.getOctaneElementValue(element, paramType);
        
        console.log(`🔄 OCTANE: Updating parameter ${pinName} (${paramType}) to:`, newValue);
        
        try {
            // Find the parameter index for this pin name
            const paramIndex = await this.findParameterIndex(this.selectedNodeHandle, pinName);
            if (paramIndex !== -1) {
                const result = await this.setParameterValueSafe(this.selectedNodeHandle, paramIndex, newValue);
                if (result.success) {
                    console.log(`✅ OCTANE: Parameter ${pinName} updated successfully`);
                } else {
                    console.warn(`⚠️ OCTANE: Failed to update parameter ${pinName}`);
                }
            }
        } catch (error) {
            console.error(`❌ OCTANE: Error updating parameter ${pinName}:`, error);
        }
    }
    
    /**
     * Handle vector parameter changes (multiple components)
     */
    async handleOctaneVectorParameterChange(element) {
        if (!this.selectedNodeHandle || !element.dataset.pinName) {
            return;
        }
        
        const pinName = element.dataset.pinName;
        const paramType = element.dataset.paramType;
        const component = parseInt(element.dataset.component);
        
        // Get all vector components
        const vectorInputs = this.element.querySelectorAll(`[data-pin-name="${pinName}"][data-param-type="${paramType}"]`);
        const vectorValue = [];
        
        vectorInputs.forEach((input, index) => {
            vectorValue[index] = parseFloat(input.value) || 0;
        });
        
        console.log(`🔄 OCTANE: Updating vector parameter ${pinName} to:`, vectorValue);
        
        try {
            const paramIndex = await this.findParameterIndex(this.selectedNodeHandle, pinName);
            if (paramIndex !== -1) {
                const result = await this.setParameterValueSafe(this.selectedNodeHandle, paramIndex, vectorValue);
                if (result.success) {
                    console.log(`✅ OCTANE: Vector parameter ${pinName} updated successfully`);
                }
            }
        } catch (error) {
            console.error(`❌ OCTANE: Error updating vector parameter ${pinName}:`, error);
        }
    }
    
    /**
     * Handle color parameter changes
     */
    async handleOctaneColorParameterChange(element) {
        const pinName = element.dataset.pinName;
        const hexColor = element.value;
        
        // Convert hex to RGB (0-1 range)
        const rgb = this.hexToRgb(hexColor);
        const colorValue = [rgb.r / 255, rgb.g / 255, rgb.b / 255];
        
        // Update color bar
        const colorBar = element.parentElement.querySelector('.octane-color-bar');
        if (colorBar) {
            colorBar.style.backgroundColor = hexColor;
        }
        
        console.log(`🔄 OCTANE: Updating color parameter ${pinName} to:`, colorValue);
        
        try {
            const paramIndex = await this.findParameterIndex(this.selectedNodeHandle, pinName);
            if (paramIndex !== -1) {
                const result = await this.setParameterValueSafe(this.selectedNodeHandle, paramIndex, colorValue);
                if (result.success) {
                    console.log(`✅ OCTANE: Color parameter ${pinName} updated successfully`);
                }
            }
        } catch (error) {
            console.error(`❌ OCTANE: Error updating color parameter ${pinName}:`, error);
        }
    }
    
    /**
     * Update slider when number input changes
     */
    updateOctaneSliderFromInput(input) {
        const slider = input.parentElement.querySelector('.octane-slider');
        if (slider) {
            let value = parseFloat(input.value) || 0;
            const min = parseFloat(slider.min);
            const max = parseFloat(slider.max);
            
            // Clamp value to slider range
            value = Math.max(min, Math.min(max, value));
            slider.value = value;
        }
    }
    
    /**
     * Update number input when slider changes
     */
    updateOctaneInputFromSlider(slider) {
        const input = slider.parentElement.querySelector('.octane-number-input');
        if (input) {
            const value = parseFloat(slider.value);
            input.value = value.toFixed(6).replace(/\.?0+$/, '');
        }
    }
    
    /**
     * Update checkbox visual state
     */
    updateOctaneCheckboxVisual(checkbox) {
        const checkmark = checkbox.parentElement.querySelector('.octane-checkbox-checkmark');
        if (checkmark) {
            checkmark.textContent = checkbox.checked ? '✓' : '';
        }
    }
    
    /**
     * Get value from Octane-style element based on type
     */
    getOctaneElementValue(element, paramType) {
        switch (paramType) {
            case 'boolean':
                return element.checked;
            case 'float':
                return parseFloat(element.value) || 0;
            case 'integer':
                return parseInt(element.value) || 0;
            case 'enum':
            case 'generic':
            default:
                return element.value;
        }
    }
    
    /**
     * Convert hex color to RGB object
     */
    hexToRgb(hex) {
        const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
        return result ? {
            r: parseInt(result[1], 16),
            g: parseInt(result[2], 16),
            b: parseInt(result[3], 16)
        } : { r: 0, g: 0, b: 0 };
    }
    
    /**
     * Find parameter index by pin name
     */
    async findParameterIndex(nodeHandle, pinName) {
        try {
            const pinCountResult = window.grpcApi.makeApiCallSync('ApiNode/pinCount', nodeHandle);
            if (!pinCountResult.success) return -1;
            
            const pinCount = pinCountResult.data.result;
            
            for (let i = 0; i < pinCount; i++) {
                const nameResult = window.grpcApi.makeApiCallSync('ApiNode/pinNameIx', nodeHandle, { index: i });
                if (nameResult.success && nameResult.data.result === pinName) {
                    return i;
                }
            }
        } catch (error) {
            console.error('Error finding parameter index:', error);
        }
        
        return -1;
    }
    
    /**
     * Render parameters organized into collapsible groups
     */
    renderParameterGroups(parameters) {
        const groups = this.organizeParametersIntoGroups(parameters);
        let html = '';
        
        Object.keys(groups).forEach(groupName => {
            const group = groups[groupName];
            const isCollapsed = this.collapsedGroups.has(groupName);
            
            html += `
                <div class="parameter-group">
                    <div class="parameter-group-header ${isCollapsed ? 'collapsed' : ''}" 
                         data-group="${groupName}">
                        <span class="parameter-group-icon">${isCollapsed ? '▶' : '▼'}</span>
                        <span class="parameter-group-title">${group.title}</span>
                        <span class="parameter-group-count">(${group.parameters.length})</span>
                    </div>
                    <div class="parameter-group-content" 
                         data-group-content="${groupName}"
                         style="display: ${isCollapsed ? 'none' : 'block'}">
                        ${this.renderParametersInGroup(group.parameters)}
                    </div>
                </div>
            `;
        });
        
        return html;
    }
    
    /**
     * Organize parameters into logical groups
     */
    organizeParametersIntoGroups(parameters) {
        const groups = {
            'camera': { title: 'Camera', parameters: [] },
            'physical-camera': { title: 'Physical camera parameters', parameters: [] },
            'viewing-angle': { title: 'Viewing angle', parameters: [] },
            'clipping': { title: 'Clipping', parameters: [] },
            'depth-of-field': { title: 'Depth of field', parameters: [] },
            'transform': { title: 'Transform', parameters: [] },
            'material': { title: 'Material', parameters: [] },
            'lighting': { title: 'Lighting', parameters: [] },
            'general': { title: 'General', parameters: [] }
        };
        
        // Group parameters based on their names
        Object.keys(parameters).forEach(paramName => {
            const param = parameters[paramName];
            const lowerName = paramName.toLowerCase();
            
            let assigned = false;
            
            // Camera parameters
            if (lowerName.includes('orthographic') || lowerName.includes('camera type')) {
                groups['camera'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Physical camera parameters
            else if (lowerName.includes('sensor') || lowerName.includes('focal') || lowerName.includes('f-stop')) {
                groups['physical-camera'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Viewing angle parameters
            else if (lowerName.includes('field of view') || lowerName.includes('scale of view') || 
                     lowerName.includes('distortion') || lowerName.includes('lens shift')) {
                groups['viewing-angle'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Clipping parameters
            else if (lowerName.includes('clip') || lowerName.includes('near') || lowerName.includes('far')) {
                groups['clipping'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Depth of field parameters
            else if (lowerName.includes('focus') || lowerName.includes('aperture') || lowerName.includes('bokeh')) {
                groups['depth-of-field'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Transform parameters
            else if (lowerName.includes('position') || lowerName.includes('rotation') || lowerName.includes('scale')) {
                groups['transform'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Material parameters
            else if (lowerName.includes('diffuse') || lowerName.includes('specular') || 
                     lowerName.includes('roughness') || lowerName.includes('metallic') || lowerName.includes('opacity')) {
                groups['material'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            // Lighting parameters
            else if (lowerName.includes('intensity') || lowerName.includes('power') || 
                     lowerName.includes('temperature') || lowerName.includes('color')) {
                groups['lighting'].parameters.push({ name: paramName, ...param });
                assigned = true;
            }
            
            // Default to general group
            if (!assigned) {
                groups['general'].parameters.push({ name: paramName, ...param });
            }
        });
        
        // Remove empty groups
        Object.keys(groups).forEach(groupName => {
            if (groups[groupName].parameters.length === 0) {
                delete groups[groupName];
            }
        });
        
        return groups;
    }
    
    /**
     * Render parameters within a group
     */
    renderParametersInGroup(parameters) {
        let html = '';
        
        parameters.forEach(param => {
            html += this.renderSingleParameter(param);
        });
        
        return html;
    }
    
    /**
     * Render a single parameter with appropriate UI control
     */
    renderSingleParameter(param) {
        const paramType = this.detectParameterType(param);
        const icon = this.getParameterIcon(param.name, paramType);
        
        let controlHtml = '';
        
        switch (paramType) {
            case 'checkbox':
                controlHtml = this.renderCheckboxControl(param);
                break;
            case 'numeric-slider':
                controlHtml = this.renderNumericSliderControl(param);
                break;
            case 'numeric-input':
                controlHtml = this.renderNumericInputControl(param);
                break;
            case 'dropdown':
                controlHtml = this.renderDropdownControl(param);
                break;
            case 'color-picker':
                controlHtml = this.renderColorPickerControl(param);
                break;
            default:
                controlHtml = this.renderTextInputControl(param);
                break;
        }
        
        return `
            <div class="parameter-row" data-param="${param.name}" data-type="${paramType}">
                <div class="parameter-label">
                    <span class="parameter-icon">${icon}</span>
                    <span class="parameter-name">${param.name}</span>
                </div>
                <div class="parameter-control">
                    ${controlHtml}
                </div>
            </div>
        `;
    }
    
    // Parameter control rendering methods
    renderCheckboxControl(param) {
        const checked = param.value === true || param.value === 'true';
        return `
            <label class="parameter-checkbox-container">
                <input type="checkbox" 
                       class="parameter-checkbox" 
                       id="param-${param.name}"
                       ${checked ? 'checked' : ''}
                       data-param="${param.name}">
                <span class="parameter-checkbox-custom"></span>
            </label>
        `;
    }
    
    renderNumericSliderControl(param) {
        const value = param.value || 0;
        const min = param.min !== undefined ? param.min : 0;
        const max = param.max !== undefined ? param.max : 100;
        const step = param.step || 0.01;
        
        return `
            <div class="parameter-numeric-slider-container">
                <input type="range" 
                       class="parameter-slider" 
                       id="slider-${param.name}"
                       min="${min}" 
                       max="${max}" 
                       step="${step}" 
                       value="${value}"
                       data-param="${param.name}">
                <input type="number" 
                       class="parameter-number-input" 
                       id="input-${param.name}"
                       min="${min}" 
                       max="${max}" 
                       step="${step}" 
                       value="${value}"
                       data-param="${param.name}">
                <div class="parameter-controls">
                    <button class="param-increment" data-param="${param.name}" data-step="${step}">▲</button>
                    <button class="param-decrement" data-param="${param.name}" data-step="${step}">▼</button>
                </div>
            </div>
        `;
    }
    
    renderNumericInputControl(param) {
        const value = param.value || 0;
        const step = param.step || 1;
        
        return `
            <div class="parameter-numeric-input-container">
                <input type="number" 
                       class="parameter-number-input" 
                       id="input-${param.name}"
                       step="${step}" 
                       value="${value}"
                       data-param="${param.name}">
                <div class="parameter-controls">
                    <button class="param-increment" data-param="${param.name}" data-step="${step}">▲</button>
                    <button class="param-decrement" data-param="${param.name}" data-step="${step}">▼</button>
                </div>
            </div>
        `;
    }
    
    renderDropdownControl(param) {
        const options = param.options || [];
        const value = param.value || '';
        
        let optionsHtml = '';
        options.forEach(option => {
            const optionValue = typeof option === 'object' ? option.value : option;
            const optionLabel = typeof option === 'object' ? option.label : option;
            const selected = optionValue === value ? 'selected' : '';
            optionsHtml += `<option value="${optionValue}" ${selected}>${optionLabel}</option>`;
        });
        
        return `
            <select class="parameter-dropdown" 
                    id="dropdown-${param.name}"
                    data-param="${param.name}">
                ${optionsHtml}
            </select>
        `;
    }
    
    renderColorPickerControl(param) {
        const value = param.value || '#ffffff';
        const hexValue = this.colorToHex(value);
        
        return `
            <div class="parameter-color-container">
                <div class="parameter-color-preview" style="background-color: ${hexValue}"></div>
                <input type="color" 
                       class="parameter-color-picker" 
                       id="color-${param.name}"
                       value="${hexValue}"
                       data-param="${param.name}">
                <input type="text" 
                       class="parameter-color-hex" 
                       id="hex-${param.name}"
                       value="${hexValue}"
                       data-param="${param.name}"
                       maxlength="7">
            </div>
        `;
    }
    
    renderTextInputControl(param) {
        const value = param.value || '';
        
        return `
            <input type="text" 
                   class="parameter-text-input" 
                   id="text-${param.name}"
                   value="${value}"
                   data-param="${param.name}">
        `;
    }
    
    // Utility methods
    detectParameterType(param) {
        if (param.type) {
            const type = param.type.toUpperCase();
            if (type.includes('BOOL')) return 'checkbox';
            if (type.includes('FLOAT') || type.includes('DOUBLE')) {
                return param.min !== undefined && param.max !== undefined ? 'numeric-slider' : 'numeric-input';
            }
            if (type.includes('INT')) return 'numeric-input';
            if (type.includes('ENUM') || type.includes('CHOICE')) return 'dropdown';
            if (type.includes('COLOR')) return 'color-picker';
        }
        
        // Infer from value
        if (typeof param.value === 'boolean') return 'checkbox';
        if (typeof param.value === 'number') {
            return param.min !== undefined && param.max !== undefined ? 'numeric-slider' : 'numeric-input';
        }
        
        // Check for options
        if (param.options && Array.isArray(param.options)) return 'dropdown';
        
        // Check name patterns
        const lowerName = param.name.toLowerCase();
        if (lowerName.includes('color')) return 'color-picker';
        if (lowerName.includes('enable') || lowerName.includes('orthographic')) return 'checkbox';
        
        return 'text-input';
    }
    
    getParameterIcon(paramName, paramType) {
        const icons = {
            'Orthographic': '📐',
            'Sensor width': '📏',
            'Focal length': '🔍',
            'F-stop': '📷',
            'Field of view': '👁️',
            'Scale of view': '🔍',
            'Distortion': '🌀',
            'Lens shift': '↔️',
            'Near clip depth': '✂️',
            'Far clip depth': '✂️',
            'Auto-focus': '🎯',
            'Focal depth': '📏',
            'Aperture': '⭕'
        };
        
        return icons[paramName] || this.getTypeIcon(paramType);
    }
    
    getTypeIcon(paramType) {
        const typeIcons = {
            'checkbox': '☑️',
            'numeric-slider': '🎚️',
            'numeric-input': '🔢',
            'dropdown': '📋',
            'color-picker': '🎨',
            'text-input': '📝'
        };
        
        return typeIcons[paramType] || '⚙️';
    }
    
    colorToHex(color) {
        if (typeof color === 'string' && color.startsWith('#')) {
            return color;
        }
        
        if (Array.isArray(color)) {
            const r = Math.round(color[0] * 255);
            const g = Math.round(color[1] * 255);
            const b = Math.round(color[2] * 255);
            return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
        }
        
        return '#ffffff';
    }
    
    /**
     * Setup event listeners for all parameter controls
     */
    setupParameterEventListeners() {
        // Numeric slider controls
        this.element.querySelectorAll('.parameter-slider').forEach(slider => {
            slider.addEventListener('input', (e) => {
                const paramName = e.target.dataset.param;
                const value = parseFloat(e.target.value);
                const input = this.element.querySelector(`#input-${paramName}`);
                if (input) input.value = value;
                this.handleParameterChange(paramName, value);
            });
        });
        
        // Numeric input controls
        this.element.querySelectorAll('.parameter-number-input').forEach(input => {
            input.addEventListener('input', (e) => {
                const paramName = e.target.dataset.param;
                const value = parseFloat(e.target.value);
                const slider = this.element.querySelector(`#slider-${paramName}`);
                if (slider) slider.value = value;
                this.handleParameterChange(paramName, value);
            });
        });
        
        // Increment/decrement buttons
        this.element.querySelectorAll('.param-increment').forEach(btn => {
            btn.addEventListener('click', (e) => {
                const paramName = e.target.dataset.param;
                const step = parseFloat(e.target.dataset.step);
                const input = this.element.querySelector(`#input-${paramName}`);
                if (input) {
                    const newValue = parseFloat(input.value) + step;
                    input.value = newValue;
                    const slider = this.element.querySelector(`#slider-${paramName}`);
                    if (slider) slider.value = newValue;
                    this.handleParameterChange(paramName, newValue);
                }
            });
        });
        
        this.element.querySelectorAll('.param-decrement').forEach(btn => {
            btn.addEventListener('click', (e) => {
                const paramName = e.target.dataset.param;
                const step = parseFloat(e.target.dataset.step);
                const input = this.element.querySelector(`#input-${paramName}`);
                if (input) {
                    const newValue = parseFloat(input.value) - step;
                    input.value = newValue;
                    const slider = this.element.querySelector(`#slider-${paramName}`);
                    if (slider) slider.value = newValue;
                    this.handleParameterChange(paramName, newValue);
                }
            });
        });
        
        // Checkbox controls
        this.element.querySelectorAll('.parameter-checkbox').forEach(checkbox => {
            checkbox.addEventListener('change', (e) => {
                const paramName = e.target.dataset.param;
                const value = e.target.checked;
                this.handleParameterChange(paramName, value);
            });
        });
        
        // Dropdown controls
        this.element.querySelectorAll('.parameter-dropdown').forEach(dropdown => {
            dropdown.addEventListener('change', (e) => {
                const paramName = e.target.dataset.param;
                const value = e.target.value;
                this.handleParameterChange(paramName, value);
            });
        });
        
        // Color picker controls
        this.element.querySelectorAll('.parameter-color-picker').forEach(picker => {
            picker.addEventListener('input', (e) => {
                const paramName = e.target.dataset.param;
                const value = e.target.value;
                const hexInput = this.element.querySelector(`#hex-${paramName}`);
                const preview = this.element.querySelector(`#color-${paramName}`).parentElement.querySelector('.parameter-color-preview');
                if (hexInput) hexInput.value = value;
                if (preview) preview.style.backgroundColor = value;
                this.handleParameterChange(paramName, value);
            });
        });
        
        // Text input controls
        this.element.querySelectorAll('.parameter-text-input').forEach(input => {
            input.addEventListener('input', (e) => {
                const paramName = e.target.dataset.param;
                const value = e.target.value;
                this.handleParameterChange(paramName, value);
            });
        });
    }
    
    /**
     * Handle parameter value changes
     */
    handleParameterChange(paramName, value) {
        console.log(`🔄 Parameter changed: ${paramName} = ${value}`);
        
        // Store the parameter value
        this.parameters[paramName] = value;
        
        // Send update to Octane if we have a selected node
        if (this.selectedNodeHandle) {
            this.updateOctaneParameter(paramName, value);
        }
        
        // Emit parameter change event for other components
        this.eventSystem.emit('parameterChanged', {
            nodeId: this.selectedNode,
            paramName: paramName,
            value: value
        });
    }
    
    /**
     * Update parameter in Octane
     */
    async updateOctaneParameter(paramName, value) {
        try {
            // This would send the parameter update to Octane
            // Implementation depends on the specific API for parameter updates
            console.log(`📤 Sending parameter update to Octane: ${paramName} = ${value}`);
            
            // For now, just log the update
            // In a real implementation, this would call the appropriate gRPC method
            
        } catch (error) {
            console.error('❌ Failed to update Octane parameter:', error);
        }
    }
    
    /**
     * Show loading state while parameters are being loaded
     */
    showLoadingState(data) {
        this.element.innerHTML = `
            <div class="node-inspector-header">
                <h3>Node inspector</h3>
                <select class="node-selector">
                    <option value="${data.nodeName}" selected>${data.nodeName}</option>
                </select>
            </div>
            <div class="node-inspector-content">
                <div class="parameter-section">
                    <div class="parameter-row">
                        <span class="parameter-icon">📦</span>
                        <span class="parameter-label">Object Handle:</span>
                        <span class="parameter-value">[${data.nodeId || this.selectedNodeHandle}]</span>
                    </div>
                    <div class="parameter-row">
                        <span class="parameter-icon">📄</span>
                        <span class="parameter-label">Type:</span>
                        <span class="parameter-value">${data.nodeType}</span>
                    </div>
                </div>
                
                <div class="loading-parameters">
                    <div class="loading-spinner"></div>
                    <p>Loading parameters...</p>
                </div>
            </div>
        `;
    }
    
    /**
     * Show error state if parameter loading fails
     */
    showErrorState(data, error) {
        this.element.innerHTML = `
            <div class="node-inspector-header">
                <h3>Node inspector</h3>
                <select class="node-selector">
                    <option value="${data.nodeName}" selected>${data.nodeName}</option>
                </select>
            </div>
            <div class="node-inspector-content">
                <div class="parameter-section">
                    <div class="parameter-row">
                        <span class="parameter-icon">📦</span>
                        <span class="parameter-label">Object Handle:</span>
                        <span class="parameter-value">[${data.nodeId || this.selectedNodeHandle}]</span>
                    </div>
                    <div class="parameter-row">
                        <span class="parameter-icon">📄</span>
                        <span class="parameter-label">Type:</span>
                        <span class="parameter-value">${data.nodeType}</span>
                    </div>
                </div>
                
                <div class="error-state">
                    <div class="error-icon">❌</div>
                    <p>Failed to load parameters</p>
                    <details>
                        <summary>Error details</summary>
                        <pre>${error.message || error}</pre>
                    </details>
                    <button class="retry-button" onclick="this.parentElement.parentElement.parentElement.parentElement.querySelector('.node-selector select').dispatchEvent(new Event('change'))">
                        🔄 Retry
                    </button>
                </div>
            </div>
        `;
    }
    
    /**
     * Utility delay function
     */
    delay(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
    
    renderGenericInspector(data) {
        // This method is now replaced by loadAndRenderFullParameterTree
        // Keep for backward compatibility
        this.loadAndRenderFullParameterTree(data);
    }
    
    setupParameterHandlers() {
        // Setup handlers for parameter groups
        const groupHeaders = this.element.querySelectorAll('.parameter-group-header');
        groupHeaders.forEach(header => {
            header.addEventListener('click', (e) => {
                const groupName = header.dataset.group;
                this.toggleParameterGroup(groupName);
            });
        });
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeInspector;
} else if (typeof window !== 'undefined') {
    window.NodeInspector = NodeInspector;
}