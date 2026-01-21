# Feature Documentation

Comprehensive guide to all features in OtoyaiWeb.

---

## 🎨 Node Graph System

### React Flow Integration

**Core Capabilities:**
- Drag-and-drop node positioning
- Pan and zoom canvas navigation
- Multi-node selection (Shift+Click, Box select)
- Delete selected nodes (Delete/Backspace key)
- Node connection system with type validation

**Controls:**
- **Pan**: Click and drag on empty canvas
- **Zoom**: Mouse wheel or pinch gesture
- **Select**: Click node or drag box around multiple nodes
- **Connect**: Drag from output pin to input pin
- **Delete**: Select node(s) and press Delete/Backspace
- **Context Menu**: Right-click on nodes for quick actions

---

## 🔌 Pin System & Type Validation

### Color-Coded Types

All pins are color-coded based on their data type:

#### Parameter Types (Input Only)
| Type | Color | Hex | Description |
|------|-------|-----|-------------|
| `string` | Orange | `#ffaa44` | Text prompts, descriptions |
| `integer` | Yellow | `#ffdd44` | Whole numbers (steps, seed, width) |
| `float` | Cyan | `#00ddff` | Decimals (guidance_scale, CFG) |
| `boolean` | Red | `#ff4444` | True/false toggles |
| `enum` | Purple | `#cc44ff` | Dropdown selections |

#### Media Types (Input & Output)
| Type | Color | Hex | Direction |
|------|-------|-----|-----------|
| `image` | Green | `#44ff44` | Bidirectional |
| `video` | Magenta | `#ff44ff` | Bidirectional |
| `audio` | Blue | `#4499ff` | Bidirectional |
| `json` | Teal | `#44ffdd` | Bidirectional |
| `any` | Gray | `#aaaaaa` | Universal |

### Connection Validation

**Type Matching Rules:**
```typescript
// Exact match (preferred)
image output → image input ✅

// Any type accepts all
any output → string input ✅
image output → any input ✅

// Type mismatch
video output → image input ❌
integer output → string input ❌
```

**Visual Feedback:**
- ✅ **Valid**: Edge drawn in source pin color
- ❌ **Invalid**: Connection rejected, no edge created
- 🔄 **Reconnection**: Drag existing edge to new target

### Edge Features

**Edge Colors:**
- Matches **source pin color** for visual traceability
- Example: Green edge = image data, Magenta edge = video data

**Edge Actions:**
- **Reconnect**: Drag edge endpoint to different pin
- **Delete**: 
  - Right-click edge → "Delete Connection"
  - Select edge and press Delete key
  - Delete source/target node (auto-removes edges)

**Edge Styles:**
- Animated flow lines (dotted pattern moving along edge)
- Bezier curves for smooth routing
- Hover highlight (thicker stroke)

---

## 📦 Node Types

### 1. Text Input Node

**Purpose:** Source node for text prompts and string parameters

**Features:**
- Large editable text area
- Orange output pin (string type)
- Auto-grows with content
- Can connect to multiple AI nodes

**Use Cases:**
- Prompts for image/video generation
- Negative prompts
- Text parameters for LLMs
- Custom string values

---

### 2. Image Node

**Purpose:** Supply images to AI models

**Features:**
- **Multi-Item Support**: Add unlimited images to single node
- **Upload Methods**:
  - 📁 File Upload: Click folder icon, select local image
  - 🔗 URL Input: Click link icon, paste image URL
- **Each Image Gets**:
  - Individual green output pin
  - Thumbnail preview
  - File name display
  - Delete button (🗑️)
- **Pin Positioning**: Evenly spaced across node width

**Supported Formats:**
- JPG/JPEG
- PNG
- GIF
- WebP
- BMP

**Use Cases:**
- Source images for image-to-image models
- Start frames for video generation
- Reference images for style transfer
- Multiple variations in one node

---

### 3. Video Node

**Purpose:** Supply videos to AI models

**Features:**
- **Multi-Item Support**: Add unlimited videos to single node
- **Upload Methods**:
  - 📁 File Upload: Click folder icon, select local video
  - 🔗 URL Input: Click link icon, paste video URL
- **Each Video Gets**:
  - Individual magenta output pin
  - Thumbnail preview (first frame)
  - File name display
  - Delete button (🗑️)
- **Pin Positioning**: Evenly spaced across node width

**Supported Formats:**
- MP4
- WebM
- MOV
- AVI

**Use Cases:**
- Source videos for video-to-video models
- Reference videos for motion transfer
- Multiple clips in one node

---

### 4. AI Endpoint Nodes

**Purpose:** Execute AI models from play.otoy.ai

**Dynamic Generation:**
- Automatically created from API endpoint list
- 1,137+ models available (as of Jan 2025)
- Categorized by function

**Node Structure:**
- **Title Bar**: Model name and category
- **Input Pins**: Left side, color-coded by parameter type
- **Output Pin**: Right side (usually green for image, magenta for video)
- **Execute Button**: Play icon (▶️) to run model (coming soon)
- **Status Indicator**: Shows execution state (coming soon)

**Categories:**

#### text-to-image
- FLUX.1 [Dev], FLUX.1 [Schnell], FLUX.1 Pro
- Stable Diffusion variants
- AuraFlow, Bria AI models
- Specialized art styles

#### image-to-image
- FLUX.1 [Dev] (img2img mode)
- Style transfer models
- Upscalers (Real-ESRGAN, etc.)
- Image editing models

#### image-to-video
- Kling Video o1 [Standard/Pro]
- CogVideoX 5B
- Runway Gen models
- Animate Diff variants

#### text-to-video
- Generative video models
- Motion synthesis
- Scene generation

#### image-to-3d
- TripoSR
- 3D reconstruction models
- Mesh generators

#### text-to-audio
- Text-to-speech (TTS)
- Music generation (Beatoven)
- Sound effects

#### LLM (Large Language Models)
- GPT-4o, GPT-4 Turbo
- Claude 3.5 Sonnet, Claude 3 Opus
- Gemini 2.0 Flash, Gemini 1.5 Pro
- Llama models

**Token Cost Display:**
- Shown in Node Palette (right side of button)
- ~40 popular models have cost data
- Costs range from 10-500 tokens
- Graceful fallback (no cost shown if unknown)

---

## 🎛️ UI Components

### Left Toolbar

**Actions:**
| Icon | Action | Description |
|------|--------|-------------|
| 🏠 | New Project | Clear canvas (prompts to save) |
| 💾 | Save Project | Native file dialog for .otoyai files |
| 📂 | Load Project | Native file dialog to open .otoyai files |
| 🔄 | Reset | Clear logs and restart (hard reset) |

**Position:** Far left vertical strip  
**Style:** Dark theme, icon buttons with hover effects

---

### Node Palette (Middle Panel)

**Purpose:** Browse and add nodes to canvas

**Structure:**
```
┌─────────────────┐
│ Node Palette    │  ← Header
├─────────────────┤
│ ▼ utility       │  ← Category (expandable)
│   Text Input    │
│   Image         │
│   Video         │
├─────────────────┤
│ ▼ text-to-image │
│   FLUX.1 [Dev]  │ 25  ← Token cost
│   AuraFlow      │ 20
│   ...           │
├─────────────────┤
│ ▼ image-to-video│
│   Kling o1      │ 300
│   CogVideoX     │ 200
└─────────────────┘
```

**Features:**
- **Collapsible Categories**: Click header to expand/collapse
- **Token Costs**: Displayed on right side (if available)
- **Search**: Coming soon
- **Workspace Management**:
  - 💾 Save Workspace: Export visible endpoints
  - 📂 Load Workspace: Import endpoint configuration

**Adding Nodes:**
1. Find model in category
2. Click button
3. Node appears in center of canvas viewport

---

### Node Inspector (Right Panel)

**Purpose:** Edit parameters for selected node

**Dynamic Content:**
- Updates when selecting different nodes
- Shows all input parameters
- Displays connected input sources

**Parameter Editing:**

#### Basic Types
- **String**: Text input field
- **Integer**: Number input with spinner
- **Float**: Number input with decimal support
- **Boolean**: Checkbox
- **Enum**: Dropdown select

#### Connected Inputs
When an input pin has a connection:
```
┌────────────────────────────────┐
│ Parameter: prompt              │
│ ┌────────────────────────────┐ │
│ │ Connected from:            │ │
│ │ "Text Input" node          │ │
│ │                            │ │
│ │ Value: "A majestic tiger"  │ │
│ └────────────────────────────┘ │
└────────────────────────────────┘
```

**Features:**
- Read-only display of connected values
- Shows source node title
- Real-time updates when source changes
- Distinct visual styling (different background)

---

### Minimap

**Purpose:** Navigate large node graphs

**Position:** Bottom right corner  
**Size:** 200x150px

**Features:**
- Bird's-eye view of entire graph
- Viewport rectangle (draggable)
- Node representations (small rectangles)
- Pan by dragging viewport
- Toggle visibility (coming soon)

---

## 💾 Project Management

### Save Project

**Trigger:** Click 💾 button in toolbar

**Process:**
1. Opens native file save dialog
2. Default filename: `Project_{timestamp}.otoyai`
3. User selects location
4. Saves JSON file with:
   - All nodes (type, position, data)
   - All edges (connections)
   - Visible endpoints list
   - Canvas viewport state

**File Format:**
```json
{
  "nodes": [...],
  "edges": [...],
  "visibleEndpoints": [...],
  "viewport": { "x": 0, "y": 0, "zoom": 1 }
}
```

**Browser Support:**
- **Modern** (Chrome, Edge): File System Access API
- **Fallback**: Automatic download

---

### Load Project

**Trigger:** Click 📂 button in toolbar

**Process:**
1. Opens native file open dialog
2. User selects .otoyai file
3. Validates JSON structure
4. Restores:
   - All nodes at saved positions
   - All connections
   - Node palette configuration
   - Canvas viewport

**Safety:**
- Prompts to save current project if unsaved changes
- Validates file format before loading
- Error handling for corrupt files

---

### Workspace Files

**Purpose:** Save/load only the Node Palette configuration (no graph data)

**Save Workspace:**
1. Click 💾 in Node Palette header
2. Saves `.otoyai-workspace` file
3. Contains: visible endpoint IDs only

**Load Workspace:**
1. Click 📂 in Node Palette header
2. Select `.otoyai-workspace` file
3. Updates visible endpoints in palette
4. **Does not affect** nodes on canvas

**Use Case:**
- Share curated model lists
- Switch between different project contexts
- Restore favorite model sets

---

## 🐛 Logging System

### File-Based Logger

**Purpose:** Debug runtime issues with persistent logs

**Location:** `server/logs/app.log`

**Log Levels:**
```typescript
logger.info('Message', { data })    // Informational
logger.error('Error', error)        // Errors
logger.debug('Debug', { details })  // Debug info
```

**Features:**
- Cleared on app restart
- Accessible via "Reset" button
- Includes timestamps
- JSON-formatted data

**Example Log:**
```
[2025-01-21T10:30:45.123Z] INFO: Fetching endpoints from play.otoy.ai
[2025-01-21T10:30:45.456Z] INFO: Endpoints fetched successfully in 333.21ms { count: 1137 }
[2025-01-21T10:31:02.789Z] INFO: Node added to canvas { type: "aiEndpoint", endpoint: "fal-ai/flux-1/dev" }
```

---

## 🎯 Keyboard Shortcuts

| Key | Action |
|-----|--------|
| `Delete` / `Backspace` | Delete selected nodes/edges |
| `Shift + Click` | Multi-select nodes |
| `Ctrl/Cmd + A` | Select all nodes |
| `Mouse Wheel` | Zoom in/out |
| `Middle Click + Drag` | Pan canvas |
| `Space + Drag` | Pan canvas (alternative) |

---

## 🔮 Upcoming Features

### AI Endpoint Execution
- Click ▶️ to run AI model
- Parameter packaging for all types
- Progress indicators
- Result caching

### Live Previews
- Show generated images/videos in nodes
- Thumbnail view for quick reference
- Full-size preview modal

### Export System
- Download generated content
- Batch export from multiple nodes
- Custom naming patterns

### Advanced Editing
- Undo/redo (Ctrl+Z, Ctrl+Y)
- Copy/paste nodes
- Node templates
- Batch operations

---

## 📊 Performance

### Optimizations
- React Flow virtualization for large graphs
- CSS Modules for scoped styling
- Zustand for efficient state updates
- Vite for instant HMR

### Limits
- No hard limit on node count
- Tested with 100+ nodes
- Minimap auto-scales for any graph size
- Performance degrades gracefully with 500+ nodes

---

## 🎨 Theming

**Current Theme:** Dark (Octane-inspired)

**Colors:**
- Background: `#1e1e1e`
- Nodes: `#2a2a2a`
- Selected: `#00ddff` (cyan accent)
- Text: `#ffffff` / `#cccccc`
- Borders: `#444444`

**Customization:** Coming soon (theme switcher)

---

## 🤝 Browser Support

| Browser | Version | Status |
|---------|---------|--------|
| Chrome | 90+ | ✅ Full support |
| Edge | 90+ | ✅ Full support |
| Firefox | 88+ | ✅ Full support (with fallbacks) |
| Safari | 15+ | ✅ Full support (with fallbacks) |

**Note:** File System Access API fallback uses download/upload for older browsers.

---

**Last Updated:** January 21, 2025
