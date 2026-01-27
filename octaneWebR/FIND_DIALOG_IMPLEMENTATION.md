# Find Dialog Implementation

## Overview
The Find dialog (Search Dialog) is fully implemented and functional, matching the OctaneSE manual specification:

> **"Search Dialog - Pressing CTRL+F brings up the Search Dialog, which finds and selects nodes and dynamic pins that contain the entered search string."**
> 
> *Source: OctaneSE Manual - The Graph Editor - Node Graph Editor Navigation*

---

## Features

### ✅ Keyboard Shortcuts
- **Ctrl+F** - Opens the search dialog
- **Escape** - Closes the dialog
- **Enter** - Selects all matching nodes

### ✅ Search Capabilities
1. **Node Name Search** (substring, case-insensitive)
   - Searches in node names with highest priority
   
2. **Node Type Search** (substring, case-insensitive)
   - Searches in node type names (e.g., "Camera", "Environment")
   
3. **Pin Name Search** (substring, case-insensitive)
   - Searches in dynamic pin names
   - Shows which pins matched in results

### ✅ User Interface
- **Auto-focus**: Input field is automatically focused when dialog opens
- **Results counter**: Shows number of matching nodes
- **Match context**: Each result shows **WHERE** it matched:
  - 📌 "Matched in node name"
  - 🏷️ "Matched in node type"
  - 📍 "Matched in X pins: [pin names]"
- **Interactive results**:
  - Click any result to select that specific node
  - "Select All" button to select all matching nodes
  - Hover effects for better UX

### ✅ Selection Behavior
- Individual selection: Click a result to select just that node
- Batch selection: Click "Select All" or press Enter to select all matches
- Dialog auto-closes after selection

---

## Implementation Details

### Component Location
```
client/src/components/NodeGraph/SearchDialog.tsx
```

### Integration Points
1. **NodeGraph Component**
   - Registers `handleFind` with EditActionsContext
   - Opens dialog via `setSearchDialogVisible(true)`
   - Provides `handleSearchSelectNodes` callback for node selection

2. **MenuBar Component**
   - Edit menu item: "Find..." with Ctrl+F shortcut
   - Calls `editActions.find()` which triggers NodeGraph handler

3. **EditActionsContext**
   - Global `find()` action available throughout app
   - Properly registered/unregistered by NodeGraph

### Search Algorithm
```typescript
1. Search Priority (first match wins):
   a. Node name contains search term → mark as 'nodeName'
   b. Node type contains search term → mark as 'nodeType'
   c. Any pin name contains search term → mark as 'pinName' + list matched pins

2. Results stored with match metadata:
   - node: ReactFlow Node reference
   - matchType: 'nodeName' | 'nodeType' | 'pinName'
   - matchedPins?: string[] (only for pinName matches)

3. Display results with context indicator
```

---

## Enhancement (Latest Update)

### **Match Context Display**
Previously, search results only showed:
- Node name
- Node type

**Now enhanced to show:**
- Node name
- Node type  
- **Match context** (what matched and where)

**Example Results:**
```
Camera 1
  Thin Lens
  📌 Matched in node name

Env_HDRI
  Texture Environment
  🏷️ Matched in node type

Material_1
  Universal Material
  📍 Matched in 2 pins: roughness, roughness_map
```

---

## Usage Example

### User Workflow
1. Open NodeGraph with scene loaded
2. Press **Ctrl+F**
3. Type search term (e.g., "camera")
4. View matching nodes with context
5. Either:
   - Click specific node to select it
   - Click "Select All" to select all matches
   - Press Enter to select all matches

### Search Examples
| Search Term | Matches | Context |
|-------------|---------|---------|
| "camera" | All camera nodes | Node name / type |
| "environment" | Env nodes | Node type |
| "roughness" | Materials with roughness pin | Pin name |
| "diffuse" | Diffuse materials + any node with diffuse pin | Node type + pins |

---

## Testing Status

### ✅ Functional Tests
- [x] Opens on Ctrl+F
- [x] Searches node names
- [x] Searches node types
- [x] Searches pin names
- [x] Shows match context
- [x] Selects individual nodes
- [x] Selects all matching nodes
- [x] Closes on Escape
- [x] Closes on selection
- [x] Auto-focuses input
- [x] Case-insensitive search
- [x] Substring matching

### Build Status
✅ TypeScript compilation successful  
✅ Vite build passing  
✅ No runtime errors  

---

## Comparison to OctaneSE

| Feature | OctaneSE | OctaneWebR | Status |
|---------|----------|------------|--------|
| Ctrl+F shortcut | ✅ | ✅ | ✅ Match |
| Find nodes by name | ✅ | ✅ | ✅ Match |
| Find pins by name | ✅ | ✅ | ✅ Match |
| Substring search | ✅ | ✅ | ✅ Match |
| Select matching nodes | ✅ | ✅ | ✅ Match |
| Show match context | ❓ | ✅ | ✅ **Enhanced** |
| Live results | ❓ | ✅ | ✅ **Enhanced** |

---

## Future Enhancements (Optional)

### Not Currently Needed
- ❌ gRPC `ApiNodeGraph.findItemsByName` - Does exact match only (less user-friendly)
- ❌ "Find Next" / "Find Previous" navigation - Not in manual
- ❌ Regex support - Not in manual
- ❌ Replace functionality - Not in manual

### Reason for Client-Side Implementation
The client-side search is **superior** because:
1. Supports substring matching (gRPC API only does exact matches)
2. Real-time results as you type
3. No network latency
4. Shows match context for better UX
5. All nodes are already loaded in memory

---

## Conclusion

The Find dialog is **fully functional** and **exceeds** the OctaneSE manual specification by:
- ✅ Meeting all documented requirements
- ✅ Adding match context display
- ✅ Providing real-time, substring-based search
- ✅ Enhanced UX with visual feedback

**Status: ✅ COMPLETE and ENHANCED**
