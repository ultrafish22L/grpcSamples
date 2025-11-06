# OctaneWeb2 UI Mockup - What You'll See

## Visual Layout

```
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃ File Edit Script Module Cloud Window Help      [●] Ready  [Connect]     ┃ Menu Bar
┣━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━┫
┃ Scene Outliner │     Render Viewport             │  Node Inspector   ┃
┃ ━━━━━━━━━━━━━━ │     ━━━━━━━━━━━━━━━━━            │  ━━━━━━━━━━━━━━━  ┃
┃                │                                  │                   ┃
┃ No scene loaded│          🎨                      │ No node selected  ┃
┃                │                                  │                   ┃
┃ Connect to     │   Render viewport ready          │ Select a node in  ┃
┃ Octane to view │                                  │ the scene to view ┃
┃ scene hierarchy│ Connect to Octane to start       │ its parameters    ┃
┃                │ rendering                        │                   ┃
┃                │                                  │                   ┃
┃                │                                  │                   ┃
┃                │                                  │                   ┃
┃                │                                  │                   ┃
┃                │                                  │                   ┃
┣━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━┫
┃ Status: Ready  │ Samples: 0  │ FPS: 0      OctaneWeb2 - React Edition   ┃ Status Bar
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
```

## Color Scheme (OTOY Dark Theme)

### Background Colors
- **Primary Background**: `#1a1a1a` (very dark gray - main panels)
- **Secondary Background**: `#2a2a2a` (dark gray - menu/status bars)
- **Tertiary Background**: `#3a3a3a` (medium gray - borders)
- **Viewport Background**: `#0a0a0a` (almost black - render canvas)

### Text Colors
- **Primary Text**: `#e0e0e0` (light gray - main text)
- **Secondary Text**: `#b0b0b0` (medium gray - labels)
- **Tertiary Text**: `#666666` (dark gray - placeholders)

### Accent Colors
- **OTOY Orange**: `#ff6b35` (buttons, highlights, hover states)
- **Status Green**: `#4caf50` (connected)
- **Status Yellow**: `#ffd700` (ready/warning)
- **Status Red**: `#f44336` (error)

## Detailed Component Breakdown

### 1. Menu Bar (Top)
```
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃ File Edit Script Module Cloud Window Help      [●] Ready  [Connect]     ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
```

**Left Side - Menu Items**:
- File, Edit, Script, Module, Cloud, Window, Help
- Hover: Orange text (#ff6b35)
- Font: 0.9rem, semi-bold

**Right Side - Connection Status**:
- Yellow dot (●) when ready
- Green dot (●) when connected
- Red dot (●) when error
- Status text: "Ready", "Connected", "Error"
- Orange "Connect" button with rounded corners

### 2. Scene Outliner (Left Panel - 250px)
```
┏━━━━━━━━━━━━━━━━┓
┃ SCENE OUTLINER ┃
┣━━━━━━━━━━━━━━━━┫
┃                ┃
┃ No scene loaded┃
┃                ┃
┃ Connect to     ┃
┃ Octane to view ┃
┃ scene hierarchy┃
┃                ┃
┃                ┃
┗━━━━━━━━━━━━━━━━┛
```

**When Connected (Future State)**:
```
┏━━━━━━━━━━━━━━━━┓
┃ SCENE OUTLINER ┃
┣━━━━━━━━━━━━━━━━┫
┃ ▼ 📷 Camera1   ┃ ← Selected (highlighted)
┃ ▶ 💡 Daylight  ┃
┃ ▼ 🔲 Meshes    ┃
┃   ▶ 🔶 Cube   ┃
┃   ▶ 🔶 Sphere ┃
┃ ▶ 🎨 Materials ┃
┗━━━━━━━━━━━━━━━━┛
```

**Features** (Phase 4):
- Hierarchical tree view
- Expand/collapse triangles (▶/▼)
- Node icons (📷 🔲 💡 🎨 etc.)
- Click to select (orange highlight)
- Visibility toggles (eye icon)
- Smooth expand/collapse animations

### 3. Render Viewport (Center Panel - Flex)
```
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃     RENDER VIEWPORT              ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃                                  ┃
┃                                  ┃
┃          🎨                      ┃
┃                                  ┃
┃   Render viewport ready          ┃
┃                                  ┃
┃ Connect to Octane to start       ┃
┃ rendering                        ┃
┃                                  ┃
┃                                  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
```

**When Rendering (Phase 2)**:
```
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃     RENDER VIEWPORT              ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃ ╔════════════════════════════╗  ┃
┃ ║                            ║  ┃
┃ ║                            ║  ┃
┃ ║   [Live Render Display]    ║  ┃
┃ ║   (Canvas with HDR/LDR)    ║  ┃
┃ ║                            ║  ┃
┃ ║                            ║  ┃
┃ ╚════════════════════════════╝  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
```

**Features** (Phase 2+3):
- HTML5 Canvas for rendering
- Auto-resize to fill panel
- Display live render from Octane
- Mouse drag to rotate camera
- Mouse wheel to zoom
- Right-click to pan

### 4. Node Inspector (Right Panel - 300px)
```
┏━━━━━━━━━━━━━━━━━━━┓
┃ NODE INSPECTOR    ┃
┣━━━━━━━━━━━━━━━━━━━┫
┃                   ┃
┃ No node selected  ┃
┃                   ┃
┃ Select a node in  ┃
┃ the scene to view ┃
┃ its parameters    ┃
┃                   ┃
┃                   ┃
┗━━━━━━━━━━━━━━━━━━━┛
```

**When Node Selected (Phase 5)**:
```
┏━━━━━━━━━━━━━━━━━━━┓
┃ NODE INSPECTOR    ┃
┣━━━━━━━━━━━━━━━━━━━┫
┃ Camera1           ┃
┃ ━━━━━━━━━━━━━━━   ┃
┃                   ┃
┃ Position          ┃
┃ X: [0.00     ▢]   ┃
┃ Y: [5.00     ▢]   ┃
┃ Z: [10.00    ▢]   ┃
┃                   ┃
┃ Target            ┃
┃ X: [0.00     ▢]   ┃
┃ Y: [0.00     ▢]   ┃
┃ Z: [0.00     ▢]   ┃
┃                   ┃
┃ FOV               ┃
┃ [45.0°  ▢━━━━○━] ┃
┗━━━━━━━━━━━━━━━━━━━┛
```

**Features** (Phase 5):
- Display all node parameters
- Numeric inputs with sliders
- Color pickers
- Boolean toggles (checkboxes)
- Enum dropdowns
- Real-time updates to Octane

### 5. Status Bar (Bottom)
```
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃ Status: Ready  │ Samples: 0  │ FPS: 0      OctaneWeb2 - React Edition   ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
```

**Left Side - Status Info**:
- Status: Ready / Rendering / Error
- Samples: Current sample count
- FPS: Frames per second
- Resolution: Canvas size (when rendering)

**Right Side - Branding**:
- "OctaneWeb2 - React Edition" (gray text with orange accent)

## Interactive States

### Connection States

**1. Disconnected (Initial)**
```
Menu Bar: [●] Ready  [Connect]
         Yellow dot
```

**2. Connecting**
```
Menu Bar: [●] Connecting...  [Cancel]
         Yellow dot pulsing
```

**3. Connected**
```
Menu Bar: [●] Connected  [Disconnect]
         Green dot
```

**4. Error**
```
Menu Bar: [●] Connection Error  [Retry]
         Red dot
```

### Hover States

**Menu Items**: 
- Default: `#e0e0e0` (light gray)
- Hover: `#ff6b35` (orange)

**Connect Button**: 
- Default: `#ff6b35` background
- Hover: `#ff8555` (lighter orange)
- Active: `#ff5015` (darker orange)

**Tree Nodes**:
- Default: Transparent background
- Hover: `#2a2a2a` background
- Selected: `#3a3a3a` background with orange left border

## Typography

### Font Family
```css
font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', 'Roboto', 'Oxygen', 
             'Ubuntu', 'Cantarell', 'Fira Sans', 'Droid Sans', 'Helvetica Neue', 
             sans-serif;
```

### Font Sizes
- **Menu items**: 0.9rem
- **Panel headers**: 0.85rem (uppercase, letter-spacing: 0.5px)
- **Panel content**: 1rem
- **Status bar**: 0.85rem
- **Placeholders**: 0.9rem

### Font Weights
- **Normal text**: 400
- **Panel headers**: 600
- **Status values**: 500

## Spacing System

### Padding
- **Panel headers**: 0.75rem 1rem
- **Panel content**: 1rem
- **Status bar**: 0.5rem 1rem
- **Tree items**: 0.4rem 0.5rem

### Gaps
- **Grid gap**: 1px (creates thin borders)
- **Menu items gap**: 1.5rem
- **Status items gap**: 1.5rem

## What It Looks Like in Practice

### Example: Connected with Scene Loaded
```
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃ File Edit Script Module Cloud Window Help   [●] Connected [Disconnect]  ┃
┣━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━┫
┃ SCENE OUTLINER │     RENDER VIEWPORT             │  NODE INSPECTOR   ┃
┣━━━━━━━━━━━━━━━━┿━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┿━━━━━━━━━━━━━━━━━━━┫
┃ ▼ 📷 Camera1   │ ╔════════════════════════════╗  │ Camera1           ┃
┃ ▶ 💡 Daylight  │ ║        ⬜⬜⬜⬜⬜⬜⬜        ║  │ ━━━━━━━━━━━━━     ┃
┃ ▼ 🔲 Meshes    │ ║        ⬜⬜🟦🟦⬜⬜⬜        ║  │                   ┃
┃   ▶ 🔶 Cube   │ ║        ⬜🟦🟦🟦🟦⬜⬜        ║  │ Position          ┃
┃   ▶ 🔶 Sphere │ ║        ⬜🟦🟦🟦🟦⬜⬜        ║  │ X: [0.00    ▢]    ┃
┃ ▶ 🎨 Materials │ ║        ⬜⬜🟦🟦⬜⬜⬜        ║  │ Y: [5.00    ▢]    ┃
┃                │ ║        ⬜⬜⬜⬜⬜⬜⬜        ║  │ Z: [10.00   ▢]    ┃
┃                │ ╚════════════════════════════╝  │                   ┃
┃                │     (Live Octane Render)        │ Target            ┃
┃                │                                  │ X: [0.00    ▢]    ┃
┃                │                                  │ Y: [0.00    ▢]    ┃
┃                │                                  │ Z: [0.00    ▢]    ┃
┣━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━┫
┃ Status: Rendering │ Samples: 125 │ FPS: 30  OctaneWeb2 - React Edition ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
```

## How to View This Yourself

### Option 1: Open the Preview HTML
```bash
# Navigate to the project
cd /workspace/grpcSamples/octaneWeb2

# Open PREVIEW.html in your browser
# (This is a static HTML mockup showing the layout and styling)
```

### Option 2: Run the Full React App
```bash
# Start the dev server
npm run dev

# Open http://localhost:46466 in your browser
# (This is the full React app with TypeScript and state management)
```

### Option 3: View on Your Local Machine
1. Copy the entire `octaneWeb2` folder to your local machine
2. Run `npm install`
3. Run `npm run dev`
4. Open http://localhost:46466

## Key Visual Features

✅ **Professional Dark Theme** - OTOY branding with orange accents  
✅ **3-Panel Layout** - Outliner, Viewport, Inspector  
✅ **Clean Typography** - System font stack, proper hierarchy  
✅ **Visual Feedback** - Hover states, status indicators  
✅ **Responsive Grid** - Resizable panels (future enhancement)  
✅ **Status Indicators** - Color-coded connection status  
✅ **Consistent Spacing** - 8px grid system  

## Comparison: Original vs React

Both have the same visual layout, but:

**Original octaneWeb**:
- Manual DOM creation (100+ lines per component)
- CSS spread across multiple files
- No component reusability

**OctaneWeb2 (React)**:
- Declarative JSX (20-30 lines per component)
- CSS Modules or styled components (organized)
- Reusable components (Button, Input, Panel, etc.)

The UI looks identical, but the code is **much cleaner**! 🚀
