# Generic Node Inspector Implementation Plan

## Overview
Transform the Node Inspector from hard-coded renderOctaneStyleInspector() to a completely generic system that works like the Scene Outliner, using tree data and ApiNodePinInfo.

## Current State Analysis ✅
- **Phase 1 Complete**: OctaneIconMapper.js consolidation working correctly
- Icons displaying properly in both Scene Outliner and Node Inspector
- System connected to live Octane with 310 nodes cached
- Current hard-coded approach shows: Render target → Physical camera parameters, Viewing angle, Clipping, Depth of field, Position

## Architecture Design

### 1. GenericNodeRenderer.js Structure
```javascript
class GenericNodeRenderer {
    constructor(iconMapper, apiClient) {
        this.iconMapper = iconMapper;
        this.apiClient = apiClient;
        this.expandedGroups = new Set(); // Track expanded/collapsed state
    }
    
    // Main rendering method - replaces renderOctaneStyleInspector()
    renderNode(nodeData, pinInfo) {
        // Build complete node tree from data
    }
    
    // Recursive tree building
    buildNodeTree(nodeData, level = 0) {
        // Create node boxes with proper indentation
    }
    
    // Pin group rendering using ApiNodePinInfo
    renderPinGroups(pinInfo, level) {
        // Use real pin group data instead of hard-coded groups
    }
    
    // Generic parameter rendering
    renderParameter(paramData, level) {
        // Use tree data for parameter info
    }
}
```

### 2. Data Flow Integration
```
Selected Node Handle → findNodeInSceneItems() → Node Tree Data
                                                      ↓
ApiNodePinInfo Request → Pin Group Data → GenericNodeRenderer
                                                      ↓
                                          Rendered HTML Tree
```

### 3. Layout System (matching screenshot requirements)

#### Node Structure:
- **Top Node**: Selected node (no collapse icon, no indentation)
- **Child Nodes**: Indented based on tree level
- **Pin Groups**: Collapsible sections with expand/collapse icons
- **Parameters**: Individual rounded boxes with icons

#### Visual Layout (from screenshot):
```
🎯 Render target                    ← Top node (level 0, no indent, no collapse icon)
├─ ▼ Scene                          ← Main section (level 1, indented)
│   ├─ 📷 ► Camera                  ← Parameter with children (level 2, more indent)
│   ├─ 🌍 ► Environment             ← Parameter with children
│   └─ 👁 Visible environment       ← Simple parameter
├─ ▼ Render settings                ← Main section (level 1)
│   ├─ ▼ Film settings              ← Sub-section (level 2)
│   │   ├─ 📐 ► Resolution:         ← Parameter with values
│   │   ├─ 🎯 ► Region start (pixel):
│   │   └─ 📏 ► Region size:
│   ├─ ▼ Animation                  ← Sub-section (level 2)
│   │   ├─ 📷 ► Shutter alignment:
│   │   └─ ⏱ ► Shutter time:
│   └─ ▼ Kernel                     ← Sub-section (level 2)
│       └─ ▼ Quality                ← Sub-sub-section (level 3)
│           ├─ 🔢 ► Max. samples:
│           └─ 💡 ► Global illumination...
```

## Implementation Phases

### Phase 2: Create GenericNodeRenderer.js ⏳
1. **Create base GenericNodeRenderer class**
   - Constructor with iconMapper and apiClient
   - Main renderNode() method
   - Expand/collapse state management

2. **Implement tree traversal**
   - buildNodeTree() for recursive rendering
   - Level-based indentation system
   - Icon and color mapping integration

3. **ApiNodePinInfo integration**
   - renderPinGroups() using real pin data
   - Dynamic parameter discovery
   - Type-based parameter rendering

### Phase 3: CSS Layout System Updates ⏳
1. **Indentation system**
   ```css
   .node-level-0 { margin-left: 0; }      /* Top node */
   .node-level-1 { margin-left: 20px; }   /* Child nodes */
   .node-level-2 { margin-left: 40px; }   /* Parameters */
   ```

2. **Icon box positioning**
   ```css
   .node-icon-box {
       position: absolute;
       left: -30px;  /* Hang beyond left edge */
       /* Color coding based on node type */
   }
   ```

3. **Rounded box system**
   - Individual parameter boxes
   - Expandable group containers
   - Proper background sizing

### Phase 4: NodeInspector.js Integration ⏳
1. **Replace hard-coded method**
   ```javascript
   // OLD: renderOctaneStyleInspector(nodeInfo, parameters)
   // NEW: this.genericRenderer.renderNode(nodeData, pinInfo)
   ```

2. **Update loadGenericParameters()**
   - Use GenericNodeRenderer instead of hard-coded HTML
   - Maintain existing parameter loading logic
   - Preserve expand/collapse functionality

3. **Event handling updates**
   - Generic click handlers for any node type
   - Dynamic expand/collapse for pin groups
   - Parameter value change handling

### Phase 5: Testing & Validation ⏳
1. **Functionality preservation**
   - All current features work identically
   - Expand/collapse behavior maintained
   - Parameter editing preserved

2. **Visual consistency**
   - Exact match to current appearance
   - Proper indentation and spacing
   - Icon positioning and colors

3. **Performance validation**
   - No regression in rendering speed
   - Efficient tree traversal
   - Memory usage optimization

## Key Technical Requirements

### 1. Tree Data Usage
- Use nodeData.children for hierarchical structure
- Use nodeData.outtype for node type identification
- Use nodeData.name for display labels

### 2. ApiNodePinInfo Integration
- Fetch real pin group names and structure
- Use pin type information for parameter rendering
- Handle dynamic pin discovery

### 3. Icon & Color Mapping
- Use OctaneIconMapper.getNodeIcon() for node icons
- Use OctaneIconMapper.getParameterIcon() for parameter icons
- Use OctaneIconMapper.getNodeColor() for color coding

### 4. Layout Consistency
- Match exact visual appearance of current system
- Maintain rounded box styling
- Preserve indentation and spacing

## Success Criteria
- ✅ Complete removal of hard-coded renderOctaneStyleInspector()
- ✅ Generic rendering works for any node type
- ✅ Visual appearance identical to current system
- ✅ All functionality preserved (expand/collapse, parameter editing)
- ✅ Uses real tree data and ApiNodePinInfo
- ✅ Consolidated icon/color mapping system
- ✅ Performance maintained or improved

## Risk Mitigation
- Implement incrementally with fallbacks
- Preserve existing functionality during transition
- Test with multiple node types
- Validate against screenshot requirements
- Maintain backward compatibility during development