# AI Endpoint Node Enhancements

## Overview
Enhanced AI endpoint nodes with dynamic input pins, UI controls, and interactive features based on endpoint schema inference.

## ✅ Implemented Features

### 1. **Dynamic Input Pins** 
Each AI endpoint node now generates input pins based on the endpoint's capabilities:

#### Pin Types:
- **Open Pins (Hollow Circles)** - For media inputs (image, video, audio)
  - 12px diameter
  - Hollow with cyan border
  - Indicates connectable media inputs
  
- **Filled Dots** - For all other input types (text, number, select, boolean)
  - 8px diameter
  - Solid cyan fill
  - Indicates parameter inputs with UI controls

### 2. **UI Controls for Parameters**
Below the node title, each parameter has:
- **Label** with tooltip showing description
- **Required indicator** (`*` in red) for required fields
- **Input control** based on parameter type:

#### Control Types:
- **Text/Prompt**: Multi-line textarea (50px min height)
- **Number**: Number input with min/max/step validation
- **Select**: Dropdown with predefined options
- **Boolean**: Checkbox with label
- **Media (Image/Video/Audio)**: Placeholder showing connection status

### 3. **Create Button**
- **Gradient cyan button** at bottom of node
- Shows "▶ Create" when ready
- Shows "⏳ Creating..." when executing
- Disabled during execution
- Mock implementation (logs to console, 2s delay)

### 4. **Right-Click Context Menu**
- **Duplicate** - Clone the node (TODO: implementation pending)
- **Delete** - Remove node (TODO: implementation pending)
- Styled with dark theme matching app aesthetic
- Auto-closes when clicking outside

### 5. **Parameter Management**
- Parameters stored in node data: `{ parameters: Record<string, unknown> }`
- Auto-initialization with default values
- Updates persist across sessions (localStorage)
- Real-time updates via Zustand store

## 📊 Schema Inference System

### `endpointSchema.ts`
Intelligent schema inference based on endpoint metadata:

#### Input Detection:
- **text-to-*** categories → `prompt` (text input)
- **image-to-*** categories → `image` input
- **video-to-*** categories → `video` input
- **audio-to-*** categories → `audio` input

#### Special Cases:
**Kling Models**:
- `style` (select: cinematic, natural, artistic, anime)
- `start_image` and `end_image` (for Standard/o1 variants)
- `duration` (select: 5, 10 seconds)

**Text-to-Image/Image-to-Image**:
- `negative_prompt` (text)
- `seed` (number: 0-2147483647)
- `num_inference_steps` (number: 1-150, default 50)
- `guidance_scale` (number: 1-20, step 0.5, default 7.5)

**LLM/Vision Models**:
- `temperature` (number: 0-2, step 0.1, default 0.7)
- `max_tokens` (number: 1-4096, default 512)

#### Output Detection:
- Categories with "image" → `image` output
- Categories with "video" → `video` output
- Categories with "audio" → `audio` or `speech` output
- LLM category → `text` output
- Default → `json` output

## 🎨 Styling

### New CSS Classes:

```css
.aiEndpointNode        /* 280-320px width container */
.parameterList         /* Vertical list of parameters */
.parameterItem         /* Individual parameter row */
.parameterControl      /* Control container */
.parameterLabel        /* Label with tooltip cursor */
.required             /* Red asterisk for required fields */

/* Input Controls */
.textInput            /* Multi-line textarea */
.numberInput          /* Number input */
.selectInput          /* Dropdown select */
.checkboxLabel        /* Checkbox with label */
.mediaPlaceholder     /* Media connection status */

/* Handles */
.handleOpen           /* 12px hollow circle (media) */
.handleFilled         /* 8px solid dot (other) */

/* Create Button */
.createButton         /* Gradient cyan button */

/* Context Menu */
.nodeContextMenu      /* Right-click menu container */
.contextMenuItem      /* Menu item with hover */
```

### Design Tokens:
- **Primary color**: Cyan (#00d4ff)
- **Hover effects**: Scale transforms, color transitions
- **Shadows**: Layered for depth
- **Spacing**: Consistent with app grid

## 📁 Files Modified

### New Files:
1. **`utils/endpointSchema.ts`** (205 lines)
   - Schema inference logic
   - Type definitions for parameters
   - Helper functions

### Modified Files:
2. **`types/nodes.ts`**
   - Added `parameters: Record<string, unknown>`
   - Added `isExecuting?: boolean`

3. **`components/Nodes/AIEndpointNode.tsx`** (250 lines)
   - Dynamic pin generation
   - Parameter rendering
   - Create button handler
   - Context menu implementation

4. **`components/Nodes/nodes.module.css`** (+200 lines)
   - All new styling for enhanced features

5. **`components/Layout/NodeBar.tsx`**
   - Initialize `parameters: {}` when adding nodes

## 🔄 Data Flow

```
User adds AI node from NodeBar
    ↓
NodeBar creates node with empty parameters: {}
    ↓
AIEndpointNode renders
    ↓
useEffect initializes default parameters from schema
    ↓
User edits parameter → handleParameterChange
    ↓
updateNodeData updates Zustand store
    ↓
Store persisted to localStorage
    ↓
User clicks "Create" → handleCreate
    ↓
Mock API call (2s delay)
    ↓
Result stored in node.data.result
```

## 🧪 Example: Kling o1 Standard Node

**Generated Schema:**
```typescript
{
  inputs: [
    { name: 'prompt', type: 'text', required: true },
    { name: 'style', type: 'select', options: ['cinematic', 'natural', 'artistic', 'anime'] },
    { name: 'start_image', type: 'image', required: false },
    { name: 'end_image', type: 'image', required: false },
    { name: 'duration', type: 'select', options: ['5', '10'], default: '5' }
  ],
  outputs: [{ type: 'video' }]
}
```

**Visual Layout:**
```
┌─────────────────────────────────┐
│ Kling Video o1 [Standard]       │  ← Title (tooltip: description)
│ fal-ai                          │  ← Vendor
├─────────────────────────────────┤
│ ● Prompt *                      │  ← Filled dot (text input)
│   [textarea...................]  │
│                                 │
│ ● Style                         │  ← Filled dot (select)
│   [Dropdown: natural         ▾] │
│                                 │
│ ○ Start Image                   │  ← Open pin (image)
│   [Connect via handle →]        │
│                                 │
│ ○ End Image                     │  ← Open pin (image)
│   [Connect via handle →]        │
│                                 │
│ ● Duration                      │  ← Filled dot (select)
│   [Dropdown: 5              ▾]  │
├─────────────────────────────────┤
│      [▶ Create]                 │  ← Gradient button
└─────────────────────────────────┘ ─○  ← Output handle (video)
```

## 🚧 TODO (Pending Implementation)

### Node Actions:
- [ ] **Delete node** - Remove from ReactFlow canvas
- [ ] **Duplicate node** - Clone with same parameters

### API Integration:
- [ ] **Actual API calls** to play.otoy.ai endpoints
- [ ] **Result handling** and display
- [ ] **Error handling** and user feedback
- [ ] **Progress indicators** for long operations

### Media Connections:
- [ ] **Handle connections** from Image/Video nodes
- [ ] **Pass media data** through edges to parameters
- [ ] **Validate connections** (type checking)

### Schema Enhancement:
- [ ] **Fetch real schemas** from API (if available)
- [ ] **Schema override system** for custom definitions
- [ ] **More endpoint patterns** (3D, upscale, etc.)

## 🎯 Testing

### How to Test:

1. **Start dev server**: `npm run dev`
2. **Click "+" in MainBar** → Opens Add Node Dialog
3. **Search "Kling"** → Find Kling Video models
4. **Click model name** → Adds to canvas
5. **Observe**:
   - Node has input pins (left side)
   - Parameters show below title
   - Hover over labels for tooltips
   - Edit text/number/select controls
   - Click "Create" button (mock execution)
6. **Right-click node** → Context menu appears
7. **Select Duplicate/Delete** → (TODO: not implemented yet)

### Test Cases:
- ✅ Node renders with correct schema
- ✅ Input pins positioned correctly
- ✅ Controls update parameters
- ✅ Create button shows execution state
- ✅ Context menu appears on right-click
- ✅ Parameters persist on page refresh
- ✅ TypeScript compiles without errors
- ✅ Build succeeds

## 📸 Visual Examples

### Pin Styles:
- **Open (Media)**: `○` - Hollow circle, 12px, cyan border
- **Filled (Other)**: `●` - Solid dot, 8px, cyan fill

### Handle Positioning:
- **Left side**: Input handles (vertical spacing: 40px)
- **Right side**: Single output handle
- **Top offset**: 80px (below header)

### Hover Effects:
- **Open pin**: Fills with cyan, scales to 1.2x
- **Filled pin**: Scales to 1.3x
- **Create button**: Moves up 1px, shadow increases

## 🔗 Related Documentation
- `UI_RESTRUCTURE_COMPLETE.md` - MainBar and NodeBar system
- `QUICK_REFERENCE.md` - User guide for node management
- `IMPLEMENTATION_REPORT.md` - Full implementation details

---

## Summary

✅ **Dynamic input pins** based on endpoint schema  
✅ **UI controls** for all parameter types  
✅ **Create button** for execution  
✅ **Right-click context menu**  
✅ **Parameter persistence**  
✅ **Tooltip descriptions**  
✅ **TypeScript type-safe**  
✅ **Responsive styling**  

**Status**: ✅ **COMPLETE** (API integration pending)  
**Commit**: `bbee41b8`  
**Branch**: `main`  
**Dev Server**: http://localhost:60026
