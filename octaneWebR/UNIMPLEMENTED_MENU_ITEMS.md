# Unimplemented Menu Items - Complete List

This document lists ALL menu items that are not yet fully implemented in OctaneWebR.

---

## Status Legend

| Symbol | Meaning |
|--------|---------|
| ❌ | Not implemented - shows "not yet implemented" notification |
| ⚠️ | Partially implemented - shows alert or has TODO |
| 🔄 | Placeholder - triggers full resync but no actual functionality |
| ✅ | Fully implemented and working |

---

## File Menu

| Menu Item | Status | Notes |
|-----------|--------|-------|
| New | ✅ | Working - calls Octane API |
| Open... | ✅ | Working - file dialog implemented |
| Recent projects | ✅ | Working - uses localStorage |
| Save | ✅ | Working - calls Octane API |
| Save as... | ✅ | Working - calls Octane API |
| Save as package... | ⚠️ | Dialog exists, but needs backend implementation |
| Save as package settings... | ❌ | Falls through to default case |
| Unpack package... | ❌ | Falls through to default case |
| Load render state... | ❌ | Falls through to default case |
| Save render state... | ❌ | Falls through to default case |
| Save as default | ✅ | Working - saves to default.orbx |
| Preferences... | ✅ | Dialog implemented |
| Activation status... | ❌ | Falls through to default case |
| Quit | ❌ | Falls through to default case |

### File Menu: 7/15 items implemented (47%)

---

## Edit Menu

| Menu Item | Status | Notes |
|-----------|--------|-------|
| Cut | ✅ | Working - maps to delete |
| Copy | ⚠️ | Shows alert - clipboard serialization not implemented |
| Paste | ⚠️ | Shows alert - clipboard deserialization not implemented |
| Group items | 🔄 | Shows alert + triggers full resync (placeholder) |
| Ungroup items | 🔄 | Shows alert + triggers full resync (placeholder) |
| Delete | ✅ | Fully optimized with incremental updates |
| Find... | ✅ | Working - opens search dialog |
| Undo | ⚠️ | Shows notification - command history not integrated with Octane |
| Redo | ⚠️ | Shows notification - command history not integrated with Octane |

### Edit Menu: 3/9 items fully implemented (33%)
### Edit Menu: 6/9 items partially working (67%)

---

## Script Menu

| Menu Item | Status | Notes |
|-----------|--------|-------|
| Rescan script folder | ✅ | Working - rescans scripts folder |
| Run last script again | ❌ | Shows "not yet implemented" notification |
| Batch rendering | ✅ | Dialog implemented |
| Daylight animation | ✅ | Dialog implemented |
| Turntable animation | ✅ | Dialog implemented |

### Script Menu: 4/5 items implemented (80%)

---

## Module Menu

| Menu Item | Status | Notes |
|-----------|--------|-------|
| (No modules installed) | N/A | Placeholder - no actual items |

### Module Menu: Not applicable

---

## Cloud Menu

| Menu Item | Status | Notes |
|-----------|--------|-------|
| Upload scene snapshot | ❌ | Shows "not yet implemented" notification |
| Render | ❌ | Shows "not yet implemented" notification |
| Open Render Network... | ❌ | Shows "not yet implemented" notification |
| Open Render Network (external)... | ❌ | Shows "not yet implemented" notification |

### Cloud Menu: 0/4 items implemented (0%)

---

## View Menu

| Menu Item | Status | Notes |
|-----------|--------|-------|
| Render Viewport | ✅ | Working - toggles panel visibility |
| Node Inspector | ✅ | Working - toggles panel visibility |
| Graph Editor | ✅ | Working - toggles panel visibility |
| Scene Outliner | ✅ | Working - toggles panel visibility |
| Refresh Scene | ✅ | Working - forces scene refresh |

### View Menu: 5/5 items implemented (100%) ✅

---

## Window Menu

| Menu Item | Status | Notes |
|-----------|--------|-------|
| Reset workspace | ✅ | Working - resets layout to defaults |
| Save workspace layout... | ❌ | Falls through to default case |
| Load workspace layout... | ❌ | Falls through to default case |
| Rescan layout folder | ❌ | Falls through to default case |
| Save as default layout | ❌ | Falls through to default case |
| Load default layout | ❌ | Falls through to default case |
| Create log window | ❌ | Falls through to default case |
| Create graph editor | ❌ | Falls through to default case |
| Create scene viewport | ❌ | Falls through to default case |
| Create scene outliner | ❌ | Falls through to default case |
| Create scene graph export | ❌ | Falls through to default case |
| Create script editor | ❌ | Falls through to default case |
| Create OSL editor | ❌ | Falls through to default case |
| Create Lua API browser | ❌ | Falls through to default case |
| Create USD stage editor | ❌ | Falls through to default case |

### Window Menu: 1/15 items implemented (7%)

---

## Help Menu

| Menu Item | Status | Notes |
|-----------|--------|-------|
| Open online manual... | ✅ | Working - opens Octane docs in new tab |
| Manage crash reports... | ❌ | Shows "not yet implemented" notification |
| About OctaneRender... | ✅ | Dialog implemented |
| Show EULA... | ✅ | Opens EULA PDF in new tab |

### Help Menu: 3/4 items implemented (75%)

---

## NodeGraph Context Menu

| Menu Item | Status | Notes |
|-----------|--------|-------|
| Cut | ✅ | Working - maps to delete |
| Copy | ⚠️ | Shows alert - not implemented |
| Paste | ⚠️ | Shows alert - not implemented |
| Delete | ✅ | Working - optimized incremental delete |
| Duplicate | ⚠️ | Shows alert - not implemented |
| Group Items | 🔄 | Shows alert + triggers full resync |
| Collapse Items | 🔄 | Triggers full resync (silent) |
| Expand Items | 🔄 | Triggers full resync (silent) |
| Show in Lua API browser | ❌ | Shows alert "Coming soon!" |
| Save as Macro | ❌ | Shows alert - requires LocalDB API |
| Render Node | ❌ | Shows alert - requires render target API |

### NodeGraph Context Menu: 2/11 items fully implemented (18%)
### NodeGraph Context Menu: 6/11 items partially working (55%)

---

## SceneOutliner Context Menu

| Menu Item | Status | Notes |
|-----------|--------|-------|
| Delete | ✅ | Working - optimized incremental delete |
| Duplicate | ⚠️ | Listed in menu but shows alert (coming soon) |

### SceneOutliner Context Menu: 1/2 items implemented (50%)

---

## Overall Statistics

### By Status

| Status | Count | Percentage |
|--------|-------|------------|
| ✅ Fully Implemented | 29 | 45% |
| ⚠️ Partially Working | 8 | 12% |
| 🔄 Placeholder | 4 | 6% |
| ❌ Not Implemented | 24 | 37% |
| **Total** | **65** | **100%** |

### By Menu

| Menu | Implemented | Total | Percentage |
|------|-------------|-------|------------|
| File | 7 | 15 | 47% |
| Edit | 3-6 | 9 | 33%-67% |
| Script | 4 | 5 | 80% |
| Cloud | 0 | 4 | 0% |
| View | 5 | 5 | **100%** ✅ |
| Window | 1 | 15 | 7% |
| Help | 3 | 4 | 75% |
| NodeGraph Context | 2-6 | 11 | 18%-55% |
| SceneOutliner Context | 1 | 2 | 50% |

---

## Priority Categories

### High Priority (Core Functionality)

These items are essential for basic workflow:

1. **Copy/Paste** (Edit menu) ⚠️
   - Status: Shows alert
   - Needs: Clipboard serialization/deserialization
   - Impact: Core editing workflow
   
2. **Undo/Redo** (Edit menu) ⚠️
   - Status: Client-side only, not Octane-aware
   - Needs: Integration with Octane command history
   - Impact: Essential for production work

3. **Duplicate** (Edit/Context menus) ⚠️
   - Status: Shows alert
   - Needs: Octane API implementation
   - Impact: Common operation

### Medium Priority (Workflow Enhancement)

These items improve productivity:

4. **Group/Ungroup** (Edit menu) 🔄
   - Status: Placeholder (triggers resync)
   - Needs: Octane grouping API
   - Impact: Scene organization

5. **Save/Load workspace layout** (Window menu) ❌
   - Status: Not implemented
   - Needs: Layout serialization system
   - Impact: Workflow customization

6. **Run last script again** (Script menu) ❌
   - Status: Not implemented
   - Needs: Script history tracking
   - Impact: Script iteration workflow

7. **Load/Save render state** (File menu) ❌
   - Status: Not implemented
   - Needs: Render state API
   - Impact: Render preset management

### Low Priority (Advanced Features)

These are nice-to-have features:

8. **Cloud rendering** (Cloud menu) ❌
   - Status: Not implemented
   - Needs: Cloud service integration
   - Impact: Optional cloud workflow

9. **Package operations** (File menu) ⚠️/❌
   - Status: Partial (dialog exists)
   - Needs: Backend implementation
   - Impact: Asset packaging

10. **Window creation** (Window menu) ❌
    - Status: Not implemented
    - Needs: Multi-window system
    - Impact: Advanced layout customization

11. **Collapse/Expand** (NodeGraph context) 🔄
    - Status: Placeholder (triggers resync)
    - Needs: Node UI state API
    - Impact: Visual organization

12. **Lua API browser** (NodeGraph context) ❌
    - Status: Not implemented
    - Needs: API documentation viewer
    - Impact: Developer tool

13. **Save as Macro** (NodeGraph context) ❌
    - Status: Not implemented
    - Needs: LocalDB API (apilocaldb.proto)
    - Impact: Node preset system

14. **Render Node** (NodeGraph context) ❌
    - Status: Not implemented
    - Needs: Render target switching API
    - Impact: Selective rendering

---

## Implementation Notes

### Copy/Paste ⚠️

**Current State:**
- Copy: Shows alert "Clipboard features require serialization"
- Paste: Shows alert "Clipboard features require serialization"

**What's Needed:**
```typescript
// 1. Serialize nodes to JSON
const clipboard = JSON.stringify({
  nodes: selectedNodes.map(n => ({
    type: n.type,
    properties: serializeProperties(n),
    connections: serializeConnections(n)
  }))
});
localStorage.setItem('octaneClipboard', clipboard);

// 2. Deserialize and create nodes
const clipboard = localStorage.getItem('octaneClipboard');
const data = JSON.parse(clipboard);
for (const nodeData of data.nodes) {
  await client.createNode(nodeData.type);
  // Set properties, restore connections
}
```

**Estimated Effort:** 2-3 days

---

### Undo/Redo ⚠️

**Current State:**
- Client-side CommandHistory exists
- Not integrated with Octane API calls
- Shows notification "Undo/Redo requires command history integration"

**What's Needed:**
```typescript
// 1. Wrap all Octane API calls with command pattern
class DeleteNodeCommand implements Command {
  async execute() {
    await client.deleteNode(handle);
    commandHistory.push(this);
  }
  
  async undo() {
    await client.createNode(savedNodeData);
  }
}

// 2. Hook up to Edit menu
handleUndo: () => commandHistory.undo()
handleRedo: () => commandHistory.redo()
```

**Estimated Effort:** 5-7 days (needs testing across all operations)

---

### Group/Ungroup 🔄

**Current State:**
- Shows alert: "Grouping API not yet implemented"
- Triggers full scene resync (placeholder)

**What's Needed:**
```typescript
// 1. Create group node
const groupHandle = await client.createNode('NT_GRP_GROUP');

// 2. Reparent selected nodes
for (const node of selectedNodes) {
  await client.setNodeParent(node.handle, groupHandle);
}

// 3. Update connections (complex)
// Need to research Octane grouping behavior
```

**Estimated Effort:** 3-5 days (depends on Octane API)

---

### Collapse/Expand 🔄

**Current State:**
- Triggers full scene resync (silent)
- No UI state management

**What's Needed:**
```typescript
// Option 1: Client-side UI state
const [collapsedNodes, setCollapsedNodes] = useState<Set<number>>();

// Option 2: Octane API (if exists)
await client.setNodeUIState(handle, { collapsed: true });

// Update node rendering to show minimized view
```

**Estimated Effort:** 2-4 days

---

### Cloud Rendering ❌

**Current State:**
- Shows "not yet implemented" notification
- No cloud service integration

**What's Needed:**
- Research Octane Cloud API
- Authentication system
- Upload/download queue
- Progress monitoring
- Error handling

**Estimated Effort:** 10-15 days (full cloud integration)

---

### Window Management ❌

**Current State:**
- Only "Reset workspace" works
- No layout save/load system

**What's Needed:**
```typescript
// 1. Serialize layout
const layout = {
  panels: panels.map(p => ({
    id: p.id,
    position: p.position,
    size: p.size,
    visible: p.visible
  }))
};
localStorage.setItem('layout_default', JSON.stringify(layout));

// 2. Deserialize and apply
const layout = JSON.parse(localStorage.getItem('layout_default'));
applyLayout(layout);
```

**Estimated Effort:** 3-5 days

---

## Recommendations

### Phase 1: Core Editing (High Priority)
1. **Copy/Paste** - Essential for workflow
2. **Duplicate** - Common operation
3. **Undo/Redo** - Production requirement

**Time Estimate:** 2-3 weeks

---

### Phase 2: Scene Organization (Medium Priority)
4. **Group/Ungroup** - Scene management
5. **Collapse/Expand** - Visual organization
6. **Save/Load Layout** - Workflow customization

**Time Estimate:** 2-3 weeks

---

### Phase 3: Advanced Features (Low Priority)
7. **Cloud Rendering** - Optional workflow
8. **Package Operations** - Asset management
9. **Window Creation** - Advanced layouts
10. **Script Management** - Script workflow
11. **Developer Tools** (Lua API browser, etc.)

**Time Estimate:** 4-6 weeks

---

## Quick Reference: What Works Now

### ✅ Fully Working Features

**File Operations:**
- New scene
- Open scene
- Save / Save As
- Recent files
- Save as default
- Preferences dialog

**Edit Operations:**
- Cut (maps to delete)
- Delete (optimized)
- Find/Search

**View:**
- All panel toggles
- Scene refresh

**Script:**
- Rescan scripts
- Batch rendering dialog
- Animation dialogs (daylight, turntable)

**Help:**
- Online manual
- About dialog
- EULA

**Node Operations:**
- Node selection
- Node creation (via context menu)
- Node deletion
- Node property editing
- Connection creation/deletion

---

## Conclusion

**Summary:**
- **45% of menu items** are fully implemented ✅
- **12% are partially working** ⚠️
- **6% are placeholders** 🔄
- **37% are not implemented** ❌

**Most Complete Menus:**
1. View (100%)
2. Script (80%)
3. Help (75%)

**Least Complete Menus:**
1. Cloud (0%)
2. Window (7%)
3. Edit (33%)

**Next Steps:**
Focus on **Copy/Paste/Duplicate** and **Undo/Redo** for Phase 1 to reach core editing functionality parity.

---

**Last Updated:** 2026-01-27  
**Version:** 1.0  
**Author:** OctaneWebR Development Team
