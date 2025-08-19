/**
 * Node Inspector Component
 * 
 * Professional parameter editing interface that provides real-time control
 * over Octane node parameters with live updates to the rendering engine.
 * Matches the exact layout and styling of Octane Render Studio for consistency.
 * 
 * Core Features:
 * - Real-time parameter editing with live Octane updates
 * - Professional Octane-style UI with collapsible sections
 * - Generic node rendering system supporting all Octane node types
 * - Intelligent parameter grouping and organization
 * - Auto-selection of render target on initialization
 * - Cached scene data integration for performance
 * 
 * Technical Implementation:
 * - Extends OctaneComponent for consistent lifecycle management
 * - Uses GenericNodeRenderer for flexible parameter display
 * - Maintains parameter state cache for performance optimization
 * - Integrates with Scene Outliner for node selection synchronization
 * - Provides expandable/collapsible parameter groups
 * 
 * Parameter Types Supported:
 * - Numeric inputs (float, int) with range validation
 * - Boolean checkboxes with live toggle updates
 * - Dropdown selections for enumerated values
 * - Color pickers for RGB/RGBA parameters
 * - File path inputs for texture and model loading
 */

class NodeInspector extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        // Current node selection state
        this.selectedNode = null;             // Currently selected node handle
        this.selectedNodeType = null;         // Type of selected node for rendering
        this.parameters = {};                 // Current parameter values cache
        
        // UI state management for collapsible sections
        this.collapsedSections = new Set();  // Collapsed parameter sections (default: all expanded)
        this.collapsedGroups = new Set();    // Collapsed parameter groups (default: all expanded)
        
        this.sceneDataLoaded = false;        // Scene data loading state
        
        // Generic node rendering system for flexible parameter display
        this.genericRenderer = null;         // Initialized in onInitialize()
    }
    
    async onInitialize() {
        // Initialize Generic Node Renderer
        this.genericRenderer = new window.GenericNodeRenderer(window.OctaneIconMapper, this.client);
        console.log('✅ NodeInspector: GenericNodeRenderer initialized');
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
            this.updatesceneItems(sceneItems);
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
                    
                    // Handle spinner buttons
                    if (element.classList && element.classList.contains('parameter-spinner-btn')) {
                        console.log('🔄 Coordinate-based spinner button click:', element);
                        const action = element.getAttribute('data-action');
                        const paramName = element.getAttribute('data-param');
                        this.handleSpinnerClick(paramName, action);
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
        
        // NEW: Generic parameter control handlers for GenericNodeRenderer controls
        const parameterControls = this.element.querySelectorAll('.parameter-control');
        parameterControls.forEach(control => {
            this.addEventListener(control, 'change', (e) => {
                console.log('🎛️ Parameter control changed:', e.target.dataset.parameter, e.target.value);
                this.handleParameterChange(e.target);
            });
            
            // Also handle input events for real-time updates on number inputs
            if (control.type === 'number' || control.type === 'range') {
                this.addEventListener(control, 'input', (e) => {
                    this.handleParameterChange(e.target);
                });
            }
        });
        
        // Initialize expanded state - all groups expanded by default
        this.initializeExpandedGroups();
    }
    
    initializeExpandedGroups() {
        // Start with all groups expanded by default
        const expandableGroups = ['physical-camera', 'viewing-angle', 'clipping', 'depth-of-field'];
        expandableGroups.forEach(groupName => {
            const header = this.element.querySelector(`[data-group="${groupName}"]`);
            const content = this.element.querySelector(`[data-group-content="${groupName}"]`);
            const icon = header?.querySelector('.parameter-group-icon');
            
            if (header && content && icon) {
                header.classList.remove('collapsed');
                content.style.display = 'block';
                icon.textContent = '▼';
                this.collapsedGroups.delete(groupName);
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
    
    handleSpinnerClick(paramName, action) {
        // Find the corresponding input field
        const input = this.element.querySelector(`input[data-param="${paramName}"]`);
        if (!input) return;
        
        const currentValue = parseFloat(input.value) || 0;
        const step = parseFloat(input.step) || 0.01;
        const min = input.min ? parseFloat(input.min) : -Infinity;
        const max = input.max ? parseFloat(input.max) : Infinity;
        
        let newValue;
        if (action === 'increment') {
            newValue = Math.min(max, currentValue + step);
        } else if (action === 'decrement') {
            newValue = Math.max(min, currentValue - step);
        } else {
            return;
        }
        
        // Update the input value
        input.value = newValue;
        
        // Trigger parameter change
        this.handleParameterChange(input);
        
        console.log(`🔄 Spinner ${action}: ${paramName} = ${newValue}`);
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
    updatesceneItems(sceneItems) {
        console.log('🚀 OPTIMIZATION: Updating Node Inspector cache with scene data');
        window.debugConsole?.addLog('info', ['🚀 NodeInspector: Updating scene data cache', sceneItems?.length, 'items']);
        
        // Store the scene data cache for generic access
        this.sceneItems = sceneItems;
        
        this.sceneDataLoaded = true;
        window.debugConsole?.addLog('info', ['✅ NodeInspector: Scene data cache updated', this.sceneItems.size, 'scene items']);
    }
    

    
    /**
     * GENERIC: Find node data directly from sceneItems list
     * This replaces specialized cache lookups with direct sceneItems access
     */
    findNodeInSceneItems(handle) {
        window.debugConsole?.addLog('info', ['🔍 NodeInspector: Searching for handle in sceneItems', handle]);
        
        if (!this.sceneItems || !Array.isArray(this.sceneItems)) {
            window.debugConsole?.addLog('warn', ['⚠️ NodeInspector: No sceneItems available']);
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
        
        return findRecursively(this.sceneItems);
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
        await this.buildTree({
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
    async buildTree(nodeInfo) {
        window.debugConsole?.addLog('info', ['🚀 NodeInspector: Loading generic parameters for', nodeInfo.nodeName, 'type:', nodeInfo.nodeType]);
        
        // Show loading state
        this.showLoadingState(nodeInfo);
        
        try {
            // Render the inspector using GenericNodeRenderer
            this.buildTreeRecurse(nodeInfo);
            
        } catch (error) {
            console.error('❌ Failed to load generic node parameters:', error);
            window.debugConsole?.addLog('error', ['❌ NodeInspector: Failed to load parameters', error.message]);
        }
    }
    
    /**
     * SIMPLIFIED: Get node type mapping for color and icon only
     * All other info is built into the scene tree or obtained via nodePinInfo
     */
    getNodeTypeMapping(nodeType) {
        window.debugConsole?.addLog('info', ['🗺️ NodeInspector: Getting mapping for node type', nodeType]);
        
        // Simplified node type mappings - only color and icon
        const nodeTypeMappings = {
            'NT_RENDERTARGET': {
                icon: '🎯',
                color: '#d32f2f'
            },
            'NT_CAMERA': {
                icon: '📷',
                color: '#1976d2'
            },
            'NT_MESH': {
                icon: '🫖',
                color: '#388e3c'
            },
            'NT_MATERIAL': {
                icon: '🎨',
                color: '#f57c00'
            },
            'NT_ENVIRONMENT': {
                icon: '🌍',
                color: '#7b1fa2'
            },
            'NT_LIGHT': {
                icon: '💡',
                color: '#fbc02d'
            },
            'NT_TEXTURE': {
                icon: '🖼️',
                color: '#5d4037'
            },
            // Default fallback for unknown node types
            'DEFAULT': {
                icon: '📦',
                color: '#666666'
            }
        };
        
        const mapping = nodeTypeMappings[nodeType] || nodeTypeMappings['DEFAULT'];
        window.debugConsole?.addLog('info', ['✅ NodeInspector: Using mapping', mapping.icon, 'color:', mapping.color]);
        
        return mapping;
    }
    
    /**
     * GENERIC: Load parameter values using generic approach
     * This replaces specialized parameter loading with direct API calls
     */
    async loadGenericParameterValues(nodeHandle) {
        window.debugConsole?.addLog('info', ['🔧 NodeInspector: Loading parameter values for handle', nodeHandle]);
        
        const parameters = {};
        
        try {
            // Get pin count for this node (single API call)
            window.debugConsole?.addLog('info', ['🔍 NodeInspector: Calling ApiNode/pinCount for handle', nodeHandle]);
            const pinCountResult = window.grpcApi.makeApiCallSync('ApiNode/pinCount', nodeHandle);
            window.debugConsole?.addLog('info', ['🔍 NodeInspector: Pin count result for handle', nodeHandle, ':', JSON.stringify(pinCountResult)]);
            
            if (pinCountResult && pinCountResult.success) {
                window.debugConsole?.addLog('info', ['📌 NodeInspector: Pin count API success, data:', JSON.stringify(pinCountResult.data), 'type:', typeof pinCountResult.data]);
                
                // Extract the actual pin count value
                let pinCount = 0;
                if (typeof pinCountResult.data === 'number') {
                    pinCount = pinCountResult.data;
                } else if (typeof pinCountResult.data === 'object' && pinCountResult.data !== null) {
                    // Handle different possible object structures
                    if (pinCountResult.data.value !== undefined) {
                        pinCount = pinCountResult.data.value;
                    } else if (pinCountResult.data.count !== undefined) {
                        pinCount = pinCountResult.data.count;
                    } else if (pinCountResult.data.pinCount !== undefined) {
                        pinCount = pinCountResult.data.pinCount;
                    } else {
                        // Try to get the first numeric property
                        for (const key in pinCountResult.data) {
                            if (typeof pinCountResult.data[key] === 'number') {
                                pinCount = pinCountResult.data[key];
                                window.debugConsole?.addLog('info', ['🔍 NodeInspector: Found numeric property', key, '=', pinCountResult.data[key]]);
                                break;
                            }
                        }
                    }
                }
                
                window.debugConsole?.addLog('info', ['📌 NodeInspector: Extracted pin count:', pinCount]);
                
                if (pinCount > 0) {
                    window.debugConsole?.addLog('info', ['📌 NodeInspector: Node has', pinCount, 'pins']);
                
                // Load all pin values using pinIx functions
                window.debugConsole?.addLog('info', ['🔄 NodeInspector: Starting to load', pinCount, 'pins using pinIx functions']);
                for (let pinIndex = 0; pinIndex < pinCount; pinIndex++) {
                    window.debugConsole?.addLog('info', ['🔄 NodeInspector: Loading pin', pinIndex, 'of', pinCount]);
                    try {
                        // Try type-specific ApiNode pinIx methods to get pin value
                        let pinValue = null;
                        let pinType = 'unknown';
                        
                        // Try different type-specific getters using ApiNode service (correct service for pinIx functions)
                        const typeGetters = [
                            { method: 'ApiNode/getPinBoolIx', type: 'bool' },
                            { method: 'ApiNode/getPinFloatIx', type: 'float' },
                            { method: 'ApiNode/getPinFloat2Ix', type: 'float2' },
                            { method: 'ApiNode/getPinFloat3Ix', type: 'float3' },
                            { method: 'ApiNode/getPinFloat4Ix', type: 'float4' },
                            { method: 'ApiNode/getPinIntIx', type: 'int' },
                            { method: 'ApiNode/getPinInt2Ix', type: 'int2' },
                            { method: 'ApiNode/getPinInt3Ix', type: 'int3' },
                            { method: 'ApiNode/getPinInt4Ix', type: 'int4' },
                            { method: 'ApiNode/getPinStringIx', type: 'string' },
                            { method: 'ApiNode/getPinFilePathIx', type: 'filepath' }
                        ];
                        
                        for (const getter of typeGetters) {
                            try {
                                const result = window.grpcApi.makeApiCallSync(getter.method, nodeHandle, { index: pinIndex });
                                if (result && result.success) {
                                    pinValue = result.data;
                                    pinType = getter.type;
                                    window.debugConsole?.addLog('info', ['✅ NodeInspector: Got', getter.type, 'value for pin index', pinIndex, ':', pinValue]);
                                    break;
                                }
                            } catch (error) {
                                // Continue to next type
                            }
                        }
                        
                        if (pinValue !== null) {
                            // Use pin index as key since we don't need pin names
                            const paramKey = `pin_${pinIndex}`;
                            parameters[paramKey] = {
                                value: pinValue,
                                pinIndex: pinIndex,
                                type: pinType,
                                name: paramKey
                            };
                            window.debugConsole?.addLog('info', ['✅ NodeInspector: Added parameter:', paramKey, 'type:', pinType, 'value:', pinValue]);
                        } else {
                            window.debugConsole?.addLog('warn', ['❌ NodeInspector: Failed to get value for pin index', pinIndex]);
                        }
                    } catch (pinError) {
                        window.debugConsole?.addLog('error', ['💥 NodeInspector: Error loading pin', pinIndex, ':', pinError.message]);
                    }
                }
                } else {
                    window.debugConsole?.addLog('warn', ['⚠️ NodeInspector: Pin count is 0 for handle', nodeHandle]);
                }
            } else {
                window.debugConsole?.addLog('error', ['❌ NodeInspector: Pin count API failed for handle', nodeHandle, 'result:', pinCountResult]);
            }
            
        } catch (error) {
            window.debugConsole?.addLog('error', ['❌ NodeInspector: Failed to load parameter values', error.message]);
        }
        
        return parameters;
    }
    
    /**
     * GENERIC: Render parameter inspector using GenericNodeRenderer
     */
    buildTreeRecurse(nodeInfo) {
        const nodeName = nodeInfo.nodeName || nodeInfo.name || 'Unknown Node';
        window.debugConsole?.addLog('info', ['🎨 NodeInspector: Rendering generic node inspector for', nodeName]);
        
        const nodeHandle = nodeInfo.handle;
        let nodeData = this.findNodeInSceneItems(nodeHandle);

        if (!nodeData) {
            console.error('❌ Node data not found for handle:', nodeHandle);
            window.debugConsole?.addLog('error', ['❌ NodeInspector: Node data not found', nodeHandle]);
            return;
        }
        // Get node type mapping for color and icon only
        const nodeTypeMapping = this.getNodeTypeMapping(nodeInfo.nodeType);
            
        // Add the color and icon from nodeTypeMapping to nodeData (if provided)
        if (nodeTypeMapping) {
            nodeData.inspectorColor = nodeTypeMapping.color;
            nodeData.inspectorIcon = nodeTypeMapping.icon;
        } else {
            // Use default values for render targets
            nodeData.inspectorColor = '#ff6600';
            nodeData.inspectorIcon = '🎯';
        }
        const pinData = null;
        // Convert parameters to pin format for the renderer
//        const pinData = parameters;
        
//        console.log('🎛️ Creating interactive controls for', Object.keys(parameters).length, 'parameters');
        
        // Use the GenericNodeRenderer with the node data and pin data
        const html = this.genericRenderer.renderNode(nodeData, pinData);
        
        // Update the inspector container directly
        const inspectorContainer = document.getElementById('node-inspector');
        if (inspectorContainer) {
            inspectorContainer.innerHTML = html;
            this.genericRenderer.setupEventHandlers(inspectorContainer);
            window.debugConsole?.addLog('info', ['✅ NodeInspector: Inspector rendered successfully']);
        } else {
            console.error('❌ Node inspector container not found');
            window.debugConsole?.addLog('error', ['❌ NodeInspector: Container not found']);
        }
        
        // Setup event listeners for the new content
        this.setupInspectorEventListeners();
        
        window.debugConsole?.addLog('info', ['✅ NodeInspector: Rendered node inspector with interactive controls']);
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
        const { type, value, min, max, label, icon, unit } = param;
        const displayLabel = label || name;
        const paramIcon = icon || this.getParameterIcon(name, type);
        
        return `
            <div class="parameter-row">
                <div class="parameter-icon">${paramIcon}</div>
                <div class="parameter-label">${displayLabel}:</div>
                <div class="parameter-control">
                    ${this.renderParameterControl(name, type, value, { min, max, unit })}
                </div>
            </div>
        `;
    }
    
    getParameterIcon(name, type) {
        // Return appropriate icons based on parameter name/type (matching official Octane Studio)
        const iconMap = {
            'sensor_width': '▣',
            'focal_length': '◐', 
            'f_stop': '◯',
            'field_of_view': '◐',
            'scale_of_view': '▤',
            'distortion': '◈',
            'lens_shift': '⟷',
            'perspective_correction': '◐',
            'pixel_aspect_ratio': '▦',
            'near_clip_depth': '▤',
            'far_clip_depth': '▤',
            'auto_focus': '◎',
            'focal_depth': '▤',
            'aperture': '◯',
            'aperture_aspect_ratio': '▦',
            'aperture_edge': '▢',
            'bokeh_side_count': '#',
            'bokeh_rotation': '↻',
            'bokeh_roundedness': '◯'
        };
        
        return iconMap[name] || (type === 'bool' ? '☐' : type === 'float' || type === 'int' ? '▤' : '◦');
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
    
    renderNumericControl(name, type, value, { min, max, unit }) {
        const step = type === 'int' ? '1' : '0.01';
        const minAttr = min !== undefined ? `min="${min}"` : '';
        const maxAttr = max !== undefined ? `max="${max}"` : '';
        const unitDisplay = unit ? `<span class="parameter-unit">${unit}</span>` : '';
        
        return `
            <div class="parameter-control-group">
                <button class="parameter-spinner-btn" data-action="decrement" data-param="${name}">◄</button>
                <input type="number" 
                       class="parameter-number-input" 
                       data-param="${name}" 
                       value="${value}" 
                       step="${step}" 
                       ${minAttr} 
                       ${maxAttr} />
                <button class="parameter-spinner-btn" data-action="increment" data-param="${name}">►</button>
                ${unitDisplay}
            </div>
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
            <input type="checkbox" 
                   class="parameter-checkbox" 
                   data-param="${name}" 
                   ${value ? 'checked' : ''} />
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
                    const result = window.grpcApi.makeApiCallSync(
                        method, 
                        nodeHandle, 
                        { index }
                    );
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
            const result = window.grpcApi.makeApiCallSync(
                'ApiNode/setPinValue', 
                nodeHandle, 
                { index: index, value: value}
            );
            
            return { success: result.success, data: result.data };
        } catch (error) {
            return { success: false, error: error.message };
        }
    }
    
    /**
     * Handle parameter value changes with safe API calls
     */
    async handleParameterChange(element) {
        if (!this.selectedNodeHandle) {
            console.warn('⚠️ No selected node handle for parameter change');
            return;
        }
        
        // Handle both old and new parameter systems
        const index = element.dataset.index ? parseInt(element.dataset.index) : 0;
        const parameterName = element.dataset.parameter || element.id || element.dataset.param;
        const newValue = this.getElementValue(element);
        
        console.log(`🔄 Updating parameter "${parameterName}" at pin ${index} to:`, newValue);
        
        try {
            const result = await this.setParameterValueSafe(this.selectedNodeHandle, index, newValue);
            if (result.success) {
                console.log(`✅ Parameter "${parameterName}" updated successfully`);
                // Update UI to reflect change
                this.updateParameterDisplay(element, newValue);
            } else {
                console.error(`❌ Failed to update parameter "${parameterName}":`, result.error);
            }
        } catch (error) {
            console.error(`❌ Error updating parameter "${parameterName}":`, error);
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
        } else if (element.type === 'color') {
            // Convert hex color to RGB array [r, g, b] with values 0-1
            const hex = element.value;
            const r = parseInt(hex.substr(1, 2), 16) / 255;
            const g = parseInt(hex.substr(3, 2), 16) / 255;
            const b = parseInt(hex.substr(5, 2), 16) / 255;
            return [r, g, b];
        } else if (element.tagName === 'SELECT') {
            return element.value;
        } else if (element.dataset.type === 'vector3' || element.dataset.type === 'vector2') {
            // For vector controls, collect all components
            const parameterName = element.dataset.parameter;
            const vectorContainer = element.closest('.octane-vector-control');
            if (vectorContainer) {
                const inputs = vectorContainer.querySelectorAll(`[data-parameter="${parameterName}"]`);
                const values = Array.from(inputs).map(input => parseFloat(input.value) || 0);
                return values;
            }
            return parseFloat(element.value) || 0;
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
    
    
    // OLD UNUSED METHODS REMOVED - See node_inspector_old_code.txt for backup
    
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
     * Utility delay function
     */
    delay(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = NodeInspector;
} else if (typeof window !== 'undefined') {
    window.NodeInspector = NodeInspector;
}