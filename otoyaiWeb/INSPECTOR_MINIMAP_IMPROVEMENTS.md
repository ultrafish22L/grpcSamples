# Inspector and Minimap Improvements

## Changes Made

### 1. Auto-updating Node Inspector ✅
- **What:** The Node Inspector now automatically updates when items are added/removed from image/video nodes, and when connections are made/broken.
- **How:** The inspector now reads both `nodes` and `edges` from the Zustand store, which are reactive. Any changes to node data or connections will automatically trigger re-renders.
- **Files Modified:**
  - `src/components/Layout/NodeInspector.tsx` - Added `edges` to store selector

### 2. Inspector Preview with Collapse/Expand ✅
- **What:** Image and video nodes in the inspector now have collapsible preview sections, similar to the nodes themselves.
- **Features:**
  - **Collapse/Expand Button:** Toggle preview visibility with ▼/▶ button
  - **Connected Inputs Section:** Shows previews of media connected from other nodes via edges
  - **Local Items Section:** Shows previews of locally loaded images/videos
  - **Thumbnails:** Full preview thumbnails for both connected and local items
  - **Auto-update:** Preview updates automatically when connections change
- **Files Modified:**
  - `src/components/Layout/NodeInspector.tsx` - Added preview section to MediaInspector
  - `src/components/Layout/NodeInspector.module.css` - Added preview styles

### 3. Minimap Node Colors Match Output Pins ✅
- **What:** Node colors in the minimap now dynamically match their output pin colors.
- **How:** 
  - Uses `getHandleType()` to determine the node's output type
  - Uses `getHandleColorStyle()` to get the matching color
  - Colors now accurate for all node types (image=green, video=magenta, text=orange, etc.)
- **Files Modified:**
  - `src/components/NodeGraph/NodeGraph.tsx` - Updated minimap `nodeColor` function

### 4. Minimap Click-and-Drag Navigation ✅
- **What:** The minimap now supports click-and-drag to navigate the node graph.
- **How:** Added `pannable` and `zoomable` props to the MiniMap component
- **Files Modified:**
  - `src/components/NodeGraph/NodeGraph.tsx` - Added `pannable` and `zoomable` props

## Technical Implementation

### Connected Inputs Detection
```typescript
const connectedInputs = useMemo(() => {
  return edges
    .filter((edge) => edge.target === node.id)
    .map((edge) => {
      const sourceNode = nodes.find((n) => n.id === edge.source);
      if (!sourceNode) return null;
      
      // Get the source data based on node type
      let sourceData: any = null;
      if (sourceNode.type === 'image' || sourceNode.type === 'video') {
        const mediaData = sourceNode.data as ImageNodeData | VideoNodeData;
        const handleIndex = parseInt(edge.sourceHandle?.replace('output-', '') || '0');
        sourceData = mediaData.items[handleIndex];
      }
      
      return {
        nodeId: sourceNode.id,
        nodeType: sourceNode.type,
        handleId: edge.sourceHandle,
        data: sourceData,
      };
    })
    .filter((conn) => conn !== null);
}, [edges, node.id, nodes]);
```

### Dynamic Minimap Colors
```typescript
<MiniMap
  pannable
  zoomable
  nodeColor={(node: Node) => {
    // Get the output handle type for this node
    const handleType = getHandleType(node, 'output', true);
    return getHandleColorStyle(handleType);
  }}
/>
```

## CSS Classes Added

### Preview Section
- `.previewHeader` - Header with title and collapse button
- `.collapseButton` - Collapse/expand button
- `.previewArea` - Container for preview content
- `.subsectionTitle` - Section headers (Connected Inputs, Local Items)

### Connected Inputs
- `.connectedInputs` - Container for connected inputs section
- `.connectedList` - List of connected items
- `.connectedItem` - Individual connected item
- `.connectedIcon` - Node type icon (🖼️/🎬/📎)
- `.connectedInfo` - Info container
- `.connectedNodeId` - Node type label
- `.connectedPreview` - Preview container
- `.connectedThumbnail` - Thumbnail image/video

### Local Items
- `.localItems` - Container for local items section
- `.mediaPreviewGrid` - Grid layout for previews
- `.mediaPreviewItem` - Individual preview item
- `.mediaThumbnail` - Thumbnail image/video
- `.mediaPreviewLabel` - Item label with index and name
- `.emptyPreview` - Empty state message

## Files Changed
1. `src/components/Layout/NodeInspector.tsx` - Inspector logic
2. `src/components/Layout/NodeInspector.module.css` - Inspector styles
3. `src/components/NodeGraph/NodeGraph.tsx` - Minimap configuration

## Testing
✅ Build successful with no TypeScript errors
✅ Dev server running on http://localhost:60023/

## User Benefits
- **Better visibility:** See connected media previews directly in inspector
- **Faster workflow:** Collapse/expand preview to manage screen space
- **Auto-updates:** No need to refresh - inspector updates automatically
- **Accurate colors:** Minimap colors match node output types
- **Easy navigation:** Click-drag minimap to move around large graphs
