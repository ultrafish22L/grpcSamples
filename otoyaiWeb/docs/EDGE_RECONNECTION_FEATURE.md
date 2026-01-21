# Edge Reconnection Feature

## Overview

The edge reconnection feature allows users to easily modify connections in the node graph by clicking and dragging edges near their endpoints (pins). This is a standard node editor interaction pattern that provides an intuitive way to rewire your workflow.

## User Interactions

### Reconnecting an Edge

1. **Click Near a Pin**: Click on a connection line within **20 pixels** of either end (near the source or target pin)
2. **Drag to New Pin**: While holding the mouse button, drag to a different compatible pin
3. **Release to Connect**: Release the mouse button to establish the new connection
   - The edge automatically updates with the correct color for the new data type
   - Any existing connection to the target pin is removed (inputs accept only one connection)

### Deleting an Edge

1. **Release Without Connecting**: If you start dragging an edge but release the mouse button without connecting to a valid pin, the edge is automatically deleted
2. **Click Middle of Edge**: Alternatively, click on the middle of an edge (not near the pins) to delete it immediately

## Visual Feedback

- **Connection Lines**: Edges are color-coded based on their data type (see PIN_COLOR_SYSTEM.md)
- **Cursor Changes**: The cursor indicates when you're hovering over a draggable edge endpoint
- **Snap Radius**: Pins "snap" to connections when you're within 20 pixels during dragging

## Technical Details

### React Flow Configuration

```tsx
<ReactFlow
  onReconnect={handleReconnect}           // Called when edge is reconnected
  onReconnectStart={handleReconnectStart} // Called when drag starts
  onReconnectEnd={handleReconnectEnd}     // Called when drag ends
  reconnectRadius={20}                     // Clickable radius around pins (in pixels)
  // ... other props
/>
```

### Implementation

**Files Modified:**
- `client/src/store/useStore.ts` - Added `onReconnect` handler
- `client/src/components/NodeGraph/NodeGraph.tsx` - Added reconnect event handlers

**Key Functions:**

1. **onReconnect** (Store)
   ```typescript
   onReconnect: (oldEdge, newConnection) => {
     // Remove old edge and create new one
     let updatedEdges = reconnectEdge(oldEdge, newConnection, state.edges);
     // Update edge color based on new source type
     // Apply changes to store
   }
   ```

2. **Edge Color Preservation**
   - When an edge is reconnected, the color is recalculated based on the **new source pin's data type**
   - This ensures visual consistency and type safety

### Logging

The feature logs the following events for debugging:

```
DEBUG: Edge reconnect started - { edge: "edge-id" }
INFO:  Edge reconnected - {
  oldEdge: "old-edge-id",
  oldSource: "node-1",
  oldTarget: "node-2",
  newSource: "node-1",
  newTarget: "node-3",
  handleType: "string",
  color: "#ffaa44"
}
DEBUG: Edge reconnect ended - { edge: "edge-id" }
```

## Type Safety

The reconnection feature respects the existing type validation system:
- Only compatible types can be connected (enforced by `isValidConnection`)
- Attempting to connect incompatible types shows a warning
- The connection is rejected if types don't match

### Compatible Type Connections

See `connectionValidator.ts` for the complete type compatibility matrix. Examples:
- ✅ String → String
- ✅ Integer → Float (numeric types are compatible)
- ✅ Any type → Any
- ❌ String → Image
- ❌ Boolean → Integer

## User Testing

To test the edge reconnection feature:

1. **Create a Simple Graph**
   ```
   [Text Input] → [FLUX.1 Dev]
   ```

2. **Add Another Text Input**
   ```
   [Text Input 1]
   [Text Input 2] → [FLUX.1 Dev]
   ```

3. **Reconnect the Edge**
   - Click near the FLUX input pin where Text Input 2 connects
   - Drag to Text Input 1's output pin
   - Release to reconnect
   - The line should maintain its orange color (string type)

4. **Test Deletion**
   - Click near a pin on any edge
   - Drag away from all nodes
   - Release - the edge should disappear

5. **Test Type Validation**
   - Try reconnecting a String edge to an Image input
   - The connection should be rejected (visual feedback)

## Keyboard Shortcuts

Currently, there are no keyboard modifiers for edge reconnection. To delete an edge:
- Method 1: Drag and release without connecting
- Method 2: Click the middle of the edge

Future enhancements could include:
- `Delete` key to remove selected edges
- `Ctrl+Drag` for duplicate-and-connect

## Browser Compatibility

The edge reconnection feature works in all modern browsers:
- ✅ Chrome/Edge 90+
- ✅ Firefox 88+
- ✅ Safari 14+

Requires pointer events support (available in all modern browsers).

## Known Limitations

1. **Mobile Support**: Touch-based reconnection works but may be less precise due to finger size
2. **High DPI Displays**: The 20px radius is in logical pixels, may feel different on retina displays
3. **Zoomed Views**: Reconnection radius scales with zoom level

## Future Enhancements

Potential improvements to consider:

1. **Variable Radius**: Make `reconnectRadius` configurable per node type
2. **Visual Indicators**: Show small circles/handles at edge endpoints when hovering
3. **Undo/Redo**: Track edge reconnections in history
4. **Batch Operations**: Reconnect multiple edges at once
5. **Smart Routing**: Auto-route edges to avoid node overlaps

## Related Documentation

- [PIN_COLOR_SYSTEM.md](./PIN_COLOR_SYSTEM.md) - Color coding for data types
- [EDGE_COLOR_IMPLEMENTATION.md](./EDGE_COLOR_IMPLEMENTATION.md) - How edge colors work
- [React Flow Reconnecting Docs](https://reactflow.dev/examples/interaction/reconnect-edge)
