# Render Viewport Features Implementation Plan

**Source**: [Octane SE Manual - The Render Viewport](https://docs.otoy.com/standaloneSE/TheRenderViewport.html)

---

## Feature Categories

### 1. Render Progress & Statistics Display
- [x] **Render Progress Indicator** - Basic implementation exists
- [ ] **GPU Quick Information Bar** - Detailed GPU stats display
- [ ] **Right-click Statistics Menu** - General statistics affecting GPU resources
- [ ] **Real-time Statistics Updates** - Live FPS, samples/sec, memory usage

### 2. Viewport Navigation Controls
- [ ] **Horizontal/Vertical Scrollbars** - For viewing parts of image outside display area
- [ ] **Recenter View** - Centers the render view display area without affecting zoom
- [ ] **Zoom Controls** - Control+MouseWheel zoom in/out, Control+LMB pan
- [ ] **Camera View Presets** - Preset camera views (top, bottom, left, right, front, back, perspective)

### 3. Render Process Controls
- [ ] **Start Render** - Starts or resumes rendering
- [ ] **Pause Render** - Pauses rendering without losing data
- [ ] **Stop Render** - Aborts rendering and frees resources
- [ ] **Restart Render** - Halts and restarts at zero samples
- [ ] **Real Time Rendering Toggle** - More interactive experience (uses more memory)

### 4. Camera & Focus Controls  
- [ ] **Reset Camera** - Resets camera to original/default position
- [x] **Auto Focus Picking Mode** - Click to focus camera on point
- [ ] **White Balance Picking Mode** - Click to select white point for scene
- [ ] **Camera Target Picker** - Click to set center of rotation/zooming
- [ ] **Focus Picking Context Menu** - Right-click shows objects along ray path

### 5. Object & Material Picking
- [x] **Material Picker** - Select material from rendered scene (basic exists)
- [x] **Object Picker** - Select object to inspect attributes (basic exists)
- [ ] **Picker Context Menus** - Right-click shows objects/materials along ray path
- [ ] **Node Inspector Integration** - Picked objects appear in inspector

### 6. Render Region Controls
- [ ] **Render Region Picker** - Rectangular area selection to restrict rendering
- [ ] **Film Region Picker** - Sets film region for render (different from render region)
- [ ] **Feathered Border Display** - Visual indicator for selected region
- [ ] **Clear Region** - Click once to return to full image rendering

### 7. Visual Quality & Display Modes
- [ ] **Clay Mode Rendering** - Show model details without textures/colors
- [ ] **Sub-Sampling Settings** - 2x2 or 4x4 sub-sampling for smoother navigation
- [ ] **Sub-sampling Auto-Apply** - Reduced quality during navigation, restore after
- [ ] **Decal Wireframe Boundaries** - Toggle wireframe for decals
- [ ] **Alpha Channel Background** - Shows background image when alpha enabled

### 8. Image Operations
- [ ] **Copy to Clipboard** - Copy rendered image in LDR format
- [ ] **Save Render** - Save current render to disk (various formats)
- [ ] **Export Render Passes** - Opens Render Passes Export window
- [ ] **Set Background Image** - Places background in viewport

### 9. Viewport Locking & Priority
- [ ] **Lock Viewport** - Prevents accidental changes or render restarts
- [ ] **Viewport Resolution Lock** - Adjusts resolution to viewport size automatically
- [ ] **Render Priority Settings** - Low/Normal/High priority for GPU allocation

### 10. Object Manipulation Gizmos
- [ ] **Object Control Alignment Mode** - World axis vs local axis toggle
- [ ] **Placement Translation Tool** - Move gizmo for translation
- [ ] **Placement Rotation Tool** - Rotate gizmo with multiple controls
- [ ] **Placement Scale Tool** - Scale gizmo (uniform and axis-constrained)
- [ ] **Gizmo Visual Feedback** - Color-coded axes, interactive handles

### 11. World Coordinate Display
- [x] **Display World Coordinate** - Small axis representation (basic exists)
- [ ] **XYZ Axis Colors** - Standard coloring (X=red, Y=green, Z=blue)
- [ ] **Orientation Updates** - Rotates with camera

### 12. Animation Timeline
- [ ] **Time Slider** - For Alembic/FBX animated geometry
- [ ] **Frame Scrubbing** - Drag to preview animation
- [ ] **Play/Pause Controls** - Animation playback
- [ ] **Frame Range Display** - Current frame / total frames

---

## API Mapping (from proto files)

### ApiRenderEngine (apirender_pb2_grpc.py)
```python
# Render control
- start() / pause() / stop()  # Render process control
- restartRender()  # Restart at zero samples

# Render regions
- setRenderRegion() / getRenderRegion()  # Rectangular render region

# Visual modes
- setClayMode() / clayMode()  # Clay mode toggle
- setSubSampleMode() / getSubSampleMode()  # Sub-sampling 1x1/2x2/4x4

# Statistics
- getRenderStatistics()  # Overall render stats
- getRenderResultStatistics()  # Result-specific stats
- fps() / setFps()  # Frame rate control

# Image operations
- saveImage() / saveImage1() / saveImage2()  # Save render to disk
- saveRenderPasses() / saveRenderPassesMultiExr()  # Export passes
- grabRenderResult() / releaseRenderResult()  # Get render buffer

# Camera
- getRenderCameraNode()  # Get active camera
- setRenderTargetNode() / getRenderTargetNode()  # Render target control

# Callbacks
- setOnNewImageCallback()  # Real-time image updates
- setOnNewStatisticsCallback()  # Real-time stats updates
```

### ApiChangeManager
```python
- update()  # Trigger display update/render
```

### ApiCamera (likely in apicamera_pb2_grpc.py)
```python
- reset()  # Reset camera to default
- setPosition() / setTarget() / setFov()  # Camera manipulation
```

---

## Implementation Priority

### Phase 1: Core Render Controls ⭐ START HERE
1. Start/Pause/Stop/Restart Render buttons
2. Real-time render statistics (samples, time, status)
3. Render region picker (rectangular selection)
4. Clay mode toggle
5. Sub-sampling mode (2x2/4x4)

### Phase 2: Image Operations
1. Save render to disk
2. Copy to clipboard
3. Export render passes
4. Set background image

### Phase 3: Camera & Navigation
1. Reset camera button
2. Camera view presets menu
3. Recenter view
4. Zoom/pan controls refinement

### Phase 4: Picking & Inspection
1. Focus picking mode
2. White balance picking
3. Camera target picker
4. Picker context menus (right-click)

### Phase 5: Object Manipulation
1. Translation gizmo
2. Rotation gizmo
3. Scale gizmo
4. World/Local axis toggle

### Phase 6: Advanced Features
1. Film region picker
2. Viewport locking
3. Render priority settings
4. Animation timeline

---

## Current Status (2025-01-20)

### ✅ Implemented
- Basic render viewport with canvas
- Mouse drag camera controls (orbit + pan)
- Real-time callback streaming
- Connection status display
- Basic picking modes (focus, material, object)
- Render toolbar skeleton

### 🚧 Partially Implemented
- Render statistics (exists but needs enhancement)
- Clay mode toggle (API exists, UI needs work)
- Sub-sampling (API exists, UI needs work)
- World coordinate display (basic implementation)

### ❌ Not Implemented
- Start/Pause/Stop/Restart buttons
- Render region picker
- Save render / Copy to clipboard
- Camera view presets
- Object manipulation gizmos
- Animation timeline
- Export render passes
- GPU statistics display

---

## Next Steps

1. **Review proto files** for camera reset, view presets, save image APIs
2. **Implement Phase 1 features** (core render controls)
3. **Build to check TypeScript errors** after each feature
4. **Visual verification** against Octane SE screenshots
5. **Commit progress** after each working feature

