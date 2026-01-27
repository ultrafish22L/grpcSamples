# Copy/Paste/Duplicate/Group/Ungroup Implementation Guide

**Date:** 2026-01-27  
**Status:** Ready for Implementation  
**Estimated Effort:** 3-5 days

---

## Overview

This guide documents how to implement Copy/Paste/Duplicate/Group/Ungroup operations using the discovered gRPC API functions from `apinodesystem.proto`.

---

## Discovered API Functions

### 1. Copy Operations

#### `ApiNodeGraph.copyItemTree`
Copies a single node with its children.

**Proto Definition:**
```protobuf
// Request
message copyItemTreeRequest {
    ObjectRef objectPtr = 1;  // The graph to copy into
    ObjectRef rootItem = 2;   // Item at the root of the copy tree
}

// Response
message copyItemTreeResponse {
    ObjectRef result = 1;  // Pointer to the copied item
}
```

**Usage:**
```typescript
// Copy a single node
const response = await client.callApi('ApiNodeGraph', 'copyItemTree', graphHandle, {
  rootItem: { handle: nodeHandle }
});
const copiedNodeHandle = Number(response.result.handle);
```

---

#### `ApiNodeGraph.copyFrom2`
Copies an array of items into the node graph.

**Proto Definition:**
```protobuf
// Request
message copyFrom2Request {
    ObjectRef objectPtr = 1;           // The graph to copy into
    ObjectRefArrayT sourceItems = 2;   // Array of items to copy
    uint32 sourceItemsCount = 3;       // Number of items
    ObjectRefArrayT origItems = 4;     // Optional: track originals
    uint32 origItemsCount = 5;         // Number of originals
}

// Response
message copyFrom2Response {
    ObjectRef copiedItems = 1;  // Array of copied items
    ObjectRef copies = 2;       // Corresponding copies (if origItems provided)
}
```

**Usage:**
```typescript
// Copy multiple nodes
const sourceItems = selectedNodes.map(n => ({ handle: n.handle }));
const response = await client.callApi('ApiNodeGraph', 'copyFrom2', graphHandle, {
  sourceItems: sourceItems,
  sourceItemsCount: sourceItems.length
});
const copiedItems = response.copiedItems;
```

---

### 2. Group Operations

#### `ApiNodeGraph.groupItems`
Creates a group node containing copies of the selected items.

**Proto Definition:**
```protobuf
// Request
message groupItemsRequest {
    ObjectRef objectPtr = 1;        // The graph containing items
    ObjectRefArrayT items = 2;      // List of items to group
    uint32 itemsCount = 3;          // Number of items
}

// Response  
message groupItemsResponse {
    ObjectRef result = 1;  // The group node graph
}
```

**Note:** "All these items will be destroyed after copying" - items are moved into the group.

**Usage:**
```typescript
// Group selected nodes
const items = selectedNodes.map(n => ({ handle: n.handle }));
const response = await client.callApi('ApiNodeGraph', 'groupItems', graphHandle, {
  items: items,
  itemsCount: items.length
});
const groupNodeHandle = Number(response.result.handle);
```

---

#### `ApiNodeGraph.ungroup`
Ungroups a group node back into individual items.

**Proto Definition:**
```protobuf
// Request
message ungroupRequest {
    ObjectRef objectPtr = 1;  // The group node graph to ungroup
}

// Response
message ungroupResponse {
    ObjectRef ungroupedItems = 1;  // List of ungrouped items
}
```

**Usage:**
```typescript
// Ungroup a group node
const response = await client.callApi('ApiNodeGraph', 'ungroup', groupNodeHandle, {});
const ungroupedItems = response.ungroupedItems;
```

---

## Implementation Plan

### Phase 1: Copy/Paste/Duplicate

#### Step 1: Add Copy Methods to NodeService

**File:** `client/src/services/octane/NodeService.ts`

```typescript
/**
 * Copy a single node (creates a duplicate)
 */
async copyNode(nodeHandle: number): Promise<number | null> {
  console.log('📋 Copying node:', nodeHandle);
  
  try {
    // Get root node graph
    const rootResponse = await this.apiService.callApi('ApiProjectManager', 'rootNodeGraph', {});
    if (!rootResponse?.result) {
      console.error('❌ Failed to get root node graph');
      return null;
    }
    
    const graphHandle = rootResponse.result;
    
    // Copy the node tree
    const copyResponse = await this.apiService.callApi('ApiNodeGraph', 'copyItemTree', graphHandle, {
      rootItem: { handle: nodeHandle }
    });
    
    if (!copyResponse?.result) {
      console.error('❌ Failed to copy node');
      return null;
    }
    
    const copiedNodeHandle = Number(copyResponse.result.handle);
    console.log('✅ Node copied with handle:', copiedNodeHandle);
    
    // Add to scene tree
    await this.sceneService.buildSceneTree(copiedNodeHandle);
    
    const newNode = this.sceneService.getNodeByHandle(copiedNodeHandle);
    if (newNode) {
      console.log('✅ Copied node added - emitting nodeAdded event');
      this.emit('nodeAdded', { node: newNode, handle: copiedNodeHandle });
    }
    
    return copiedNodeHandle;
  } catch (error: any) {
    console.error('❌ Error copying node:', error.message);
    return null;
  }
}

/**
 * Copy multiple nodes
 */
async copyNodes(nodeHandles: number[]): Promise<number[]> {
  console.log('📋 Copying multiple nodes:', nodeHandles);
  
  try {
    // Get root node graph
    const rootResponse = await this.apiService.callApi('ApiProjectManager', 'rootNodeGraph', {});
    if (!rootResponse?.result) {
      console.error('❌ Failed to get root node graph');
      return [];
    }
    
    const graphHandle = rootResponse.result;
    
    // Prepare source items
    const sourceItems = nodeHandles.map(h => ({ handle: h }));
    
    // Copy all nodes
    const copyResponse = await this.apiService.callApi('ApiNodeGraph', 'copyFrom2', graphHandle, {
      sourceItems: sourceItems,
      sourceItemsCount: sourceItems.length,
      origItems: sourceItems,  // Track originals to get mapping
      origItemsCount: sourceItems.length
    });
    
    if (!copyResponse?.copiedItems) {
      console.error('❌ Failed to copy nodes');
      return [];
    }
    
    // Extract copied handles
    const copiedHandles: number[] = [];
    // TODO: Parse copiedItems array (need to check exact format)
    
    // Add all copied nodes to scene tree
    for (const handle of copiedHandles) {
      await this.sceneService.buildSceneTree(handle);
      const newNode = this.sceneService.getNodeByHandle(handle);
      if (newNode) {
        this.emit('nodeAdded', { node: newNode, handle });
      }
    }
    
    console.log('✅ Copied nodes:', copiedHandles);
    return copiedHandles;
  } catch (error: any) {
    console.error('❌ Error copying nodes:', error.message);
    return [];
  }
}
```

---

#### Step 2: Update OctaneClient

**File:** `client/src/services/OctaneClient.ts`

Add methods:
```typescript
async copyNode(nodeHandle: number): Promise<number | null> {
  return this.nodeService.copyNode(nodeHandle);
}

async copyNodes(nodeHandles: number[]): Promise<number[]> {
  return this.nodeService.copyNodes(nodeHandles);
}
```

---

#### Step 3: Update EditCommands

**File:** `client/src/commands/EditCommands.ts`

Replace the current implementations:

```typescript
/**
 * Copy selected nodes to clipboard
 */
export async function copyNodes(client: OctaneClient, selectedNodes: SceneNode[]): Promise<void> {
  if (!selectedNodes || selectedNodes.length === 0) {
    alert('Copy\n\nNo nodes selected.\n\nSelect one or more nodes first.');
    return;
  }

  console.log('📋 Copy nodes:', selectedNodes.length);
  
  // Simple approach: just store handles in clipboard
  const clipboard = {
    type: 'octane-nodes',
    handles: selectedNodes.map(n => n.handle),
    timestamp: Date.now()
  };
  
  localStorage.setItem('octaneClipboard', JSON.stringify(clipboard));
  console.log('✅ Nodes copied to clipboard');
}

/**
 * Paste nodes from clipboard
 */
export async function pasteNodes(client: OctaneClient): Promise<void> {
  console.log('📋 Paste nodes');
  
  try {
    // Get clipboard data
    const clipboardData = localStorage.getItem('octaneClipboard');
    if (!clipboardData) {
      alert('Clipboard is empty\n\nUse Copy first to add nodes to clipboard.');
      return;
    }
    
    const clipboard = JSON.parse(clipboardData);
    if (clipboard.type !== 'octane-nodes') {
      alert('Invalid clipboard data\n\nClipboard does not contain nodes.');
      return;
    }
    
    const sourceHandles = clipboard.handles;
    if (!sourceHandles || sourceHandles.length === 0) {
      alert('Clipboard is empty\n\nNo nodes to paste.');
      return;
    }
    
    console.log('📋 Pasting', sourceHandles.length, 'nodes');
    
    // Copy the nodes using the API
    const copiedHandles = await client.copyNodes(sourceHandles);
    
    if (copiedHandles.length === 0) {
      alert('Paste Failed\n\nFailed to copy nodes from clipboard.');
      return;
    }
    
    console.log('✅ Pasted', copiedHandles.length, 'nodes');
    
    // Trigger scene refresh to update UI
    await client.resyncScene();
  } catch (error: any) {
    console.error('❌ Error pasting nodes:', error);
    alert(`Paste Failed\n\n${error.message}`);
  }
}

/**
 * Duplicate selected nodes
 */
export async function duplicateNodes(client: OctaneClient, selectedNodes: SceneNode[]): Promise<void> {
  if (!selectedNodes || selectedNodes.length === 0) {
    alert('Duplicate\n\nNo nodes selected.\n\nSelect one or more nodes first.');
    return;
  }

  console.log('📋 Duplicate nodes:', selectedNodes.length);
  
  try {
    const sourceHandles = selectedNodes.map(n => n.handle);
    const copiedHandles = await client.copyNodes(sourceHandles);
    
    if (copiedHandles.length === 0) {
      alert('Duplicate Failed\n\nFailed to duplicate selected nodes.');
      return;
    }
    
    console.log('✅ Duplicated', copiedHandles.length, 'nodes');
    
    // Trigger scene refresh
    await client.resyncScene();
  } catch (error: any) {
    console.error('❌ Error duplicating nodes:', error);
    alert(`Duplicate Failed\n\n${error.message}`);
  }
}
```

---

#### Step 4: Re-enable Menu Items

**File:** `client/src/components/MenuBar/index.tsx`

Remove `enabled: false`:
```typescript
edit: [
  { label: 'Cut', action: 'edit.cut', shortcut: 'Ctrl+X' },
  { label: 'Copy', action: 'edit.copy', shortcut: 'Ctrl+C' },  // Remove enabled: false
  { label: 'Paste', action: 'edit.paste', shortcut: 'Ctrl+V' }, // Remove enabled: false
  // ...
]
```

**File:** `client/src/components/NodeGraph/NodeContextMenu.tsx`

Remove `disabled` class:
```typescript
{/* Copy */}
<div
  className="context-menu-item"  // Remove 'disabled'
  onClick={handleCopyClick}
>
  Copy
</div>

{/* Paste */}
<div
  className="context-menu-item"  // Remove 'disabled'
  onClick={handlePasteClick}
>
  Paste
</div>
```

---

### Phase 2: Group/Ungroup

#### Step 1: Add Group Methods to NodeService

**File:** `client/src/services/octane/NodeService.ts`

```typescript
/**
 * Group selected nodes into a group node
 */
async groupNodes(nodeHandles: number[]): Promise<number | null> {
  console.log('📦 Grouping nodes:', nodeHandles);
  
  try {
    // Get root node graph
    const rootResponse = await this.apiService.callApi('ApiProjectManager', 'rootNodeGraph', {});
    if (!rootResponse?.result) {
      console.error('❌ Failed to get root node graph');
      return null;
    }
    
    const graphHandle = rootResponse.result;
    
    // Prepare items
    const items = nodeHandles.map(h => ({ handle: h }));
    
    // Group items
    const groupResponse = await this.apiService.callApi('ApiNodeGraph', 'groupItems', graphHandle, {
      items: items,
      itemsCount: items.length
    });
    
    if (!groupResponse?.result) {
      console.error('❌ Failed to group nodes');
      return null;
    }
    
    const groupNodeHandle = Number(groupResponse.result.handle);
    console.log('✅ Group created with handle:', groupNodeHandle);
    
    // Remove grouped nodes from scene (they were destroyed)
    nodeHandles.forEach(h => {
      const scene = this.sceneService.getScene();
      scene.map.delete(h);
      scene.tree = scene.tree.filter(n => n.handle !== h);
    });
    
    // Add group node to scene tree
    await this.sceneService.buildSceneTree(groupNodeHandle);
    
    const groupNode = this.sceneService.getNodeByHandle(groupNodeHandle);
    if (groupNode) {
      this.emit('nodeAdded', { node: groupNode, handle: groupNodeHandle });
    }
    
    // Emit deleted events for grouped nodes
    nodeHandles.forEach(h => {
      this.emit('nodeDeleted', { handle: h, collapsedChildren: [] });
    });
    
    return groupNodeHandle;
  } catch (error: any) {
    console.error('❌ Error grouping nodes:', error.message);
    return null;
  }
}

/**
 * Ungroup a group node
 */
async ungroupNode(groupNodeHandle: number): Promise<number[]> {
  console.log('📦 Ungrouping node:', groupNodeHandle);
  
  try {
    // Ungroup
    const ungroupResponse = await this.apiService.callApi('ApiNodeGraph', 'ungroup', groupNodeHandle, {});
    
    if (!ungroupResponse?.ungroupedItems) {
      console.error('❌ Failed to ungroup node');
      return [];
    }
    
    // Extract ungrouped handles
    const ungroupedHandles: number[] = [];
    // TODO: Parse ungroupedItems array (need to check exact format)
    
    // Remove group node from scene
    const scene = this.sceneService.getScene();
    scene.map.delete(groupNodeHandle);
    scene.tree = scene.tree.filter(n => n.handle !== groupNodeHandle);
    this.emit('nodeDeleted', { handle: groupNodeHandle, collapsedChildren: [] });
    
    // Add ungrouped nodes to scene tree
    for (const handle of ungroupedHandles) {
      await this.sceneService.buildSceneTree(handle);
      const newNode = this.sceneService.getNodeByHandle(handle);
      if (newNode) {
        this.emit('nodeAdded', { node: newNode, handle });
      }
    }
    
    console.log('✅ Ungrouped into nodes:', ungroupedHandles);
    return ungroupedHandles;
  } catch (error: any) {
    console.error('❌ Error ungrouping node:', error.message);
    return [];
  }
}
```

---

#### Step 2: Update OctaneClient

**File:** `client/src/services/OctaneClient.ts`

Add methods:
```typescript
async groupNodes(nodeHandles: number[]): Promise<number | null> {
  return this.nodeService.groupNodes(nodeHandles);
}

async ungroupNode(groupNodeHandle: number): Promise<number[]> {
  return this.nodeService.ungroupNode(groupNodeHandle);
}
```

---

#### Step 3: Update EditCommands

**File:** `client/src/commands/EditCommands.ts`

Replace placeholders:

```typescript
/**
 * Group selected nodes
 */
export async function groupNodes(client: OctaneClient, selectedNodes: SceneNode[]): Promise<void> {
  if (!selectedNodes || selectedNodes.length < 2) {
    alert('Group Nodes\n\nSelect at least 2 nodes to create a group.');
    return;
  }

  console.log('📦 Group nodes:', selectedNodes.length);
  
  try {
    const nodeHandles = selectedNodes.map(n => n.handle);
    const groupHandle = await client.groupNodes(nodeHandles);
    
    if (!groupHandle) {
      alert('Group Failed\n\nFailed to create group node.');
      return;
    }
    
    console.log('✅ Group created:', groupHandle);
    
    // Trigger scene refresh
    await client.resyncScene();
  } catch (error: any) {
    console.error('❌ Error grouping nodes:', error);
    alert(`Group Failed\n\n${error.message}`);
  }
}

/**
 * Ungroup selected node
 */
export async function ungroupNodes(client: OctaneClient, selectedNodes: SceneNode[]): Promise<void> {
  if (!selectedNodes || selectedNodes.length !== 1) {
    alert('Ungroup\n\nSelect exactly one group node to ungroup.');
    return;
  }

  console.log('📦 Ungroup node:', selectedNodes[0].handle);
  
  try {
    // TODO: Check if node is actually a group (check type)
    const groupHandle = selectedNodes[0].handle;
    const ungroupedHandles = await client.ungroupNode(groupHandle);
    
    if (ungroupedHandles.length === 0) {
      alert('Ungroup Failed\n\nFailed to ungroup node.\n\nMake sure the selected node is a group.');
      return;
    }
    
    console.log('✅ Ungrouped into', ungroupedHandles.length, 'nodes');
    
    // Trigger scene refresh
    await client.resyncScene();
  } catch (error: any) {
    console.error('❌ Error ungrouping node:', error);
    alert(`Ungroup Failed\n\n${error.message}`);
  }
}
```

---

## Testing Checklist

### Copy/Paste
- [ ] Copy single node → Paste → Verify duplicate appears
- [ ] Copy multiple nodes → Paste → Verify all duplicated
- [ ] Copy → Close app → Open app → Paste → Verify clipboard persists
- [ ] Copy in one scene → Open another scene → Paste → Verify works cross-scene
- [ ] Copy node with connections → Paste → Verify connections duplicated
- [ ] Copy parent with children → Paste → Verify hierarchy preserved

### Duplicate
- [ ] Duplicate single node → Verify copy appears
- [ ] Duplicate multiple nodes → Verify all copied
- [ ] Duplicate node with connections → Verify connections copied
- [ ] Duplicate parent with children → Verify hierarchy copied

### Group
- [ ] Group 2 nodes → Verify group node created
- [ ] Group multiple nodes → Verify all inside group
- [ ] Group nodes with connections → Verify connections preserved
- [ ] Try group 1 node → Verify shows error
- [ ] Group then delete group → Verify children deleted too

### Ungroup
- [ ] Ungroup group node → Verify children extracted
- [ ] Ungroup → Verify connections restored
- [ ] Try ungroup non-group → Verify shows error
- [ ] Ungroup empty group → Verify handles gracefully

---

## Known Issues & TODOs

### 1. Array Response Parsing
The proto definitions return `ObjectRef` and `ObjectRefArrayT` types. Need to verify exact format:

```typescript
// TODO: Verify response format
const copiedHandles = response.copiedItems.items.map(item => Number(item.handle));
// OR
const copiedHandles = response.copiedItems.map(item => Number(item.handle));
```

**Solution:** Test with single node first, inspect response structure.

---

### 2. Connection Preservation
Need to verify that `copyItemTree` and `copyFrom2` preserve:
- Pin connections
- Attribute values
- Node positions in graph editor

**Solution:** Test and verify in NodeGraph component.

---

### 3. Position Offset
When pasting, nodes should appear offset from originals (not exactly on top).

**Solution:** After copy, offset node positions:
```typescript
// After pasting
for (const handle of copiedHandles) {
  await client.setNodePosition(handle, x + 50, y + 50);
}
```

---

### 4. Group Type Detection
Need to detect if a node is a group before ungrouping.

**Solution:** Check node type:
```typescript
const nodeType = await client.getNodeType(handle);
if (nodeType !== 'NT_GRP_GROUP') {
  alert('Selected node is not a group');
  return;
}
```

---

## Implementation Timeline

### Day 1: Copy/Paste Foundation
- [ ] Add `copyNode()` to NodeService
- [ ] Add `copyNodes()` to NodeService
- [ ] Test single node copy
- [ ] Test multiple node copy
- [ ] Verify response format

### Day 2: Copy/Paste Integration
- [ ] Update `copyNodes()` in EditCommands
- [ ] Update `pasteNodes()` in EditCommands
- [ ] Add `duplicateNodes()` implementation
- [ ] Re-enable menu items
- [ ] Test full copy/paste/duplicate workflow

### Day 3: Group Operations
- [ ] Add `groupNodes()` to NodeService
- [ ] Add `ungroupNode()` to NodeService
- [ ] Test grouping
- [ ] Test ungrouping
- [ ] Verify connection preservation

### Day 4: Group Integration
- [ ] Update `groupNodes()` in EditCommands
- [ ] Update `ungroupNodes()` in EditCommands
- [ ] Add group type detection
- [ ] Re-enable Group/Ungroup menu items
- [ ] Test full group workflow

### Day 5: Polish & Testing
- [ ] Add position offset for paste
- [ ] Handle edge cases (empty clipboard, invalid groups, etc.)
- [ ] Add comprehensive error handling
- [ ] Write tests
- [ ] Update documentation

---

## Summary

**API Functions Available:**
- ✅ `ApiNodeGraph.copyItemTree` - Copy single node
- ✅ `ApiNodeGraph.copyFrom2` - Copy multiple nodes
- ✅ `ApiNodeGraph.groupItems` - Group nodes
- ✅ `ApiNodeGraph.ungroup` - Ungroup nodes

**Implementation Approach:**
1. **Copy** - Store handles in localStorage
2. **Paste** - Use `copyFrom2()` to duplicate nodes from handles
3. **Duplicate** - Direct call to `copyFrom2()` (no clipboard)
4. **Group** - Use `groupItems()` API
5. **Ungroup** - Use `ungroup()` API

**Benefits:**
- ✅ Simple clipboard (just handles)
- ✅ API handles all complexity (connections, children, attributes)
- ✅ Cross-scene paste works automatically
- ✅ Proper group/ungroup with connection preservation

**Estimated Total Time:** 3-5 days

---

**Last Updated:** 2026-01-27  
**Version:** 1.0  
**Status:** Ready for Implementation 🚀
