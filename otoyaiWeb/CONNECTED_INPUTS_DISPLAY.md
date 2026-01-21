# Connected Inputs Display in Node Inspector

## Problem
When AI endpoint nodes (like Kling Video) have connections to their input pins, the inspector was only showing "Connect via input pin" instead of displaying the actual connected data (image previews, text content, etc.).

## Solution
Updated the Node Inspector to detect connected inputs and display their content with previews in the parameter controls.

## Changes Made

### 1. Connected Input Detection ✅
- **AIEndpointInspector** now receives `nodes` and `edges` from the store
- Detects all incoming edges to the node
- Maps each edge to its source node and extracts the connected data:
  - **Text nodes**: Extract the text value
  - **Image nodes**: Extract the media item based on the source handle index
  - **Video nodes**: Extract the media item based on the source handle index

### 2. Connected Data Display ✅
Updated `renderControl` function to show connected inputs:

#### Text Parameters
- Shows a **green badge**: "✓ Connected from text node"
- Displays the connected text in a read-only textarea
- Visual indication with opacity and disabled cursor

#### Image Parameters
- Shows a **green badge**: "✓ Connected from image node"
- Displays the **image preview** with proper aspect ratio
- Shows the **filename/name** of the connected image
- Styled with bordered container

#### Video Parameters
- Shows a **green badge**: "✓ Connected from video node"
- Displays the **video preview** with controls
- Shows the **filename/name** of the connected video
- Styled with bordered container

#### Fallback
- When no connection exists, shows "Connect via input pin" placeholder

### 3. Auto-Update Behavior ✅
- Inspector automatically updates when:
  - Connections are made/broken between nodes
  - Media items are added/removed from source nodes
  - Text content changes in source text nodes
- Uses Zustand reactive store for automatic re-rendering

## Implementation Details

### Connected Input Detection
```typescript
const connectedInputs = useMemo(() => {
  const connections: Record<string, any> = {};
  
  // Find all edges targeting this node
  const incomingEdges = edges.filter((edge) => edge.target === node.id);
  
  for (const edge of incomingEdges) {
    const sourceNode = nodes.find((n) => n.id === edge.source);
    if (!sourceNode) continue;
    
    const targetHandle = edge.targetHandle; // This is the input parameter name
    if (!targetHandle) continue;
    
    // Get the source data based on node type
    let sourceData: any = null;
    
    if (sourceNode.type === 'textInput') {
      sourceData = {
        type: 'text',
        value: (sourceNode.data as TextInputNodeData).value || '',
        nodeType: 'textInput',
      };
    } else if (sourceNode.type === 'image') {
      const imageData = sourceNode.data as ImageNodeData;
      const handleIndex = parseInt(edge.sourceHandle?.replace('output-', '') || '0');
      const item = imageData.items[handleIndex];
      sourceData = {
        type: 'image',
        item: item,
        nodeType: 'image',
      };
    } else if (sourceNode.type === 'video') {
      const videoData = sourceNode.data as VideoNodeData;
      const handleIndex = parseInt(edge.sourceHandle?.replace('output-', '') || '0');
      const item = videoData.items[handleIndex];
      sourceData = {
        type: 'video',
        item: item,
        nodeType: 'video',
      };
    }
    
    if (sourceData) {
      connections[targetHandle] = sourceData;
    }
  }
  
  return connections;
}, [edges, node.id, nodes]);
```

### Display Example (Image)
```typescript
case 'image':
  // Show connected image if available
  if (connectedInput?.type === 'image' && connectedInput.item) {
    const item = connectedInput.item;
    return (
      <div className={styles.connectedMediaDisplay}>
        <div className={styles.connectedBadge}>
          ✓ Connected from image node
        </div>
        {(item.preview || item.url) && (
          <img
            src={item.preview || item.url}
            alt={item.name || 'Connected image'}
            className={styles.connectedMediaPreview}
          />
        )}
        <div className={styles.connectedMediaName}>
          {item.name || 'Untitled image'}
        </div>
      </div>
    );
  }
  return (
    <div className={styles.mediaPlaceholder}>
      Connect via input pin
    </div>
  );
```

## CSS Classes Added

### Connected Text Display
- `.connectedTextDisplay` - Container for connected text
- `.connectedBadge` - Green badge showing connection status

### Connected Media Display
- `.connectedMediaDisplay` - Container for connected images/videos
- `.connectedMediaPreview` - Image/video preview with max height
- `.connectedMediaName` - Filename display below preview

### Badge Styling
```css
.connectedBadge {
  display: inline-flex;
  align-items: center;
  gap: 4px;
  padding: 4px 8px;
  background: rgba(68, 255, 68, 0.15);
  border: 1px solid rgba(68, 255, 68, 0.3);
  border-radius: var(--radius-sm);
  color: #44ff44;
  font-size: 10px;
  font-weight: 600;
  text-transform: uppercase;
  letter-spacing: 0.5px;
  width: fit-content;
}
```

## Files Modified
1. `src/components/Layout/NodeInspector.tsx`
   - Added `nodes` and `edges` props to AIEndpointInspector
   - Added `connectedInputs` detection logic
   - Updated `renderControl` to display connected data
   
2. `src/components/Layout/NodeInspector.module.css`
   - Added `.connectedTextDisplay`, `.connectedBadge`
   - Added `.connectedMediaDisplay`, `.connectedMediaPreview`, `.connectedMediaName`

## Testing
✅ Build successful with no TypeScript errors  
✅ Dev server running on http://localhost:60025/

## Example Use Case
**Kling Video Node with Connections:**
- **Image** parameter: Shows preview of connected image from image node
- **Prompt** parameter: Shows text content from connected text node
- **Start Image** parameter: Shows "Connect via input pin" (not connected)
- **End Image** parameter: Shows "Connect via input pin" (not connected)

All connected inputs update automatically when source nodes change!

## User Benefits
- **Visual feedback**: See exactly what data is connected to each parameter
- **No guessing**: Preview images and read text without switching to source nodes
- **Auto-updates**: Changes in source nodes immediately reflect in the inspector
- **Better workflow**: Build complex node graphs with confidence in connections
