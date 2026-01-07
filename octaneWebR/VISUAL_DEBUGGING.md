# OctaneWebR Visual Debugging Guide

## 🎯 Overview

This guide provides everything needed to start visual debugging octaneWebR in a new chat session. OctaneWebR is a React + TypeScript port of octaneWeb that provides real-time interaction with OTOY Octane Render through the LiveLink gRPC API.

## 🚀 Quick Start Commands

### 1. Navigate to Project Directory
```bash
cd /workspace/project/grpcSamples/octaneWebR
```

### 2. Install Dependencies (if needed)
```bash
npm install
```

### 3. Start Development Server
```bash
npm run dev
```

**Expected Output:**
```
📡 Vite gRPC Plugin: Connected to Octane at host.docker.internal:51022
🐳 Using Docker networking (sandbox environment detected)
📦 Proto files ready for lazy loading
✅ Octane gRPC Plugin configured
   • HTTP API: /api/grpc/:service/:method
   • WebSocket: /api/callbacks
   • Health: /api/health

VITE v5.4.21  ready in 248 ms

➜  Local:   http://localhost:43929/
➜  Network: http://172.17.0.3:43929/
```

### 4. Open Browser for Visual Debugging
```bash
# Use the browser tools to navigate to the application
# URL will be shown in the terminal output (typically http://localhost:43929)
```

## 🔍 Visual Debugging Process

### Browser Navigation
1. **Navigate to Application**: Use `browser_navigate` with the URL from terminal output
2. **Take Screenshots**: Use `browser_get_state` with `include_screenshot: true` to see current state
3. **Interact with Elements**: Use `browser_click` to interact with UI elements
4. **Monitor Logs**: Watch terminal output for API calls and scene sync progress

### Key Visual Elements to Verify

#### Scene Outliner (Left Panel)
- **Expected**: Hierarchical tree showing:
  - 📁 Scene (root)
  - 🫖 teapot.obj (geometry)
  - 🎯 Render target (should auto-select)
  - 📷 Camera
  - 🌍 Environment
  - 🎬 Film settings
  - ⏱️ Animation
  - 🔧 Kernel
  - 🎭 Render layer
  - 📊 Render AOVs
  - 📤 Output AOVs
  - 📷 Imager
  - ⚙️ Post processing

#### Node Inspector (Right Panel)
- **Expected**: Detailed properties for selected node
- **For Render Target**: Should show expandable sections:
  - ▼ Scene
  - ▼ Camera (with Orthographic, Physical camera parameters, etc.)
  - ▼ Environment
  - ▼ Render settings
- **Input Fields**: Sensor width, Focal length, F-stop, etc.

#### Node Graph Editor (Bottom Panel)
- **Expected**: Visual node graph showing:
  - teapot.obj node (PT_GEOMETRY)
  - Connected to cube material node (PT_MATERIAL)
  - Blue connection lines between nodes

### Connection Status Indicators
- **Top Right**: Should show "Connected" (green)
- **Status Bar**: "OctaneLive: connected"
- **Scene Outliner**: Should NOT show "Loading scene..." after sync completes

## 🐛 Common Issues & Solutions

### Scene Not Loading
**Symptoms**: Scene outliner shows "Loading scene..." indefinitely

**Debug Steps**:
1. **Check Terminal Logs**: Look for API call progress
   ```
   📤 ApiProjectManager.rootNodeGraph {}
   ✅ ApiProjectManager.rootNodeGraph → {"result":{"handle":"1000000"}}
   📤 ApiItem.name {"objectPtr":{"handle":"1000002","type":16}}
   ✅ ApiItem.name → {"result":"teapot.obj"}
   ```

2. **Wait for Completion**: Scene sync can take 30-60 seconds for complex scenes
3. **Manual Refresh**: Click the 🔄 button in scene outliner
4. **Check Connection**: Verify "Connected" status in top right

### Connection Issues
**Symptoms**: Shows "disconnected" or connection errors

**Solutions**:
1. **Octane Not Running**: Ensure Octane is running on host machine
2. **LiveLink Disabled**: Enable LiveLink in Octane (Help → LiveLink)
3. **Docker Networking**: System auto-detects sandbox environment and uses `host.docker.internal:51022`

### UI Layout Issues
**Symptoms**: Panels not showing correctly or overlapping

**Solutions**:
1. **Refresh Browser**: Hard refresh (Ctrl+F5)
2. **Check CSS**: Verify all stylesheets are loading
3. **Resize Window**: Try different browser window sizes

## 📊 Monitoring Scene Sync Progress

### Terminal Log Patterns
```bash
# Scene sync starts
📤 ApiProjectManager.rootNodeGraph {}
✅ ApiProjectManager.rootNodeGraph → {"result":{"handle":"1000000","type":"ApiRootNodeGraph"}}

# Building scene tree
📤 ApiItem.name {"objectPtr":{"handle":"1000002","type":16}}
✅ ApiItem.name → {"result":"teapot.obj"}
📤 ApiItem.outType {"objectPtr":{"handle":"1000002","type":16}}
✅ ApiItem.outType → {"result":"PT_GEOMETRY"}

# Processing node connections
📤 ApiNode.connectedNodeIx {"objectPtr":{"handle":"1000002","type":17},"pinIx":0}
✅ ApiNode.connectedNodeIx → {"result":{"handle":"1000004","type":"ApiNode"}}

# Attribute loading (final phase)
📤 ApiItem.getByAttrID {"item_ref":{"handle":"1000006","type":16},"attribute_id":185}
✅ ApiItem.getByAttrID → {"float_value":36.000,"value":"float_value"}
```

### Completion Indicators
- **API Calls Stop**: No more 📤/✅ messages in terminal
- **Scene Tree Appears**: Hierarchical tree replaces "Loading scene..."
- **Node Selection**: Render target auto-selected (highlighted in yellow)
- **Node Inspector Populated**: Right panel shows detailed properties

## 🎨 Expected Visual Result

The final result should match the reference screenshot exactly:

### Layout Structure
```
┌─────────────────────────────────────────────────────────────────────────────┐
│ File Edit Script Module Cloud Window Help                        Connected │
├─────────────┬─────────────────────────────────────────────┬─────────────────┤
│ Scene       │ Render viewport - Render target @ 100%     │ Node inspector  │
│ outliner    │ ⊞ 1:1 🔍+ 🔍-                              │                 │
│             │                                             │ 🎯 Render target│
│ 📁 Scene    │                                             │ ▼ Scene         │
│ 🫖 teapot   │                                             │ ▼ Camera        │
│ 🎯 Render   │                                             │   Orthographic  │
│   target    │                                             │   ▼ Physical... │
│ 📷 Camera   │                                             │     Sensor width│
│ 🌍 Environ  │                                             │     Focal length│
│ ...         │                                             │     F-stop      │
│             ├─────────────────────────────────────────────┤ ...             │
│             │ Node graph editor                           │                 │
│             │ + 🗑 ⊞                                      │                 │
│             │                                             │                 │
│             │ teapot.obj ──────→ cube                     │                 │
│             │ PT_GEOMETRY       PT_MATERIAL               │                 │
│             │                                             │                 │
└─────────────┴─────────────────────────────────────────────┴─────────────────┘
│ Ready                    OctaneWebR - React TypeScript + Node.js gRPC      │
│                                                   OctaneLive: connected FPS:0│
└─────────────────────────────────────────────────────────────────────────────┘
```

## 🔧 Development Tools

### Browser Developer Tools
- **Console**: Check for JavaScript errors or API call logs
- **Network**: Monitor HTTP requests to proxy server
- **React DevTools**: Inspect component state and props

### Useful Browser Console Commands
```javascript
// Check connection status
console.log('Connected:', window.octaneClient?.connected);

// Force scene reload
window.octaneClient?.buildSceneTree();

// Check scene data
console.log('Scene tree:', window.octaneClient?.scene);
```

## 📝 Debugging Checklist

### Before Starting
- [ ] Octane is running on host machine
- [ ] LiveLink is enabled in Octane (Help → LiveLink)
- [ ] Dependencies are installed (`npm install`)
- [ ] Development server starts without errors

### During Visual Debugging
- [ ] Browser navigates to correct URL
- [ ] Connection status shows "Connected"
- [ ] Scene sync completes (watch terminal logs)
- [ ] Scene outliner shows hierarchical tree
- [ ] Node inspector shows properties for selected node
- [ ] Node graph shows visual connections

### If Issues Occur
- [ ] Check terminal for error messages
- [ ] Verify Octane is still running
- [ ] Try manual scene refresh (🔄 button)
- [ ] Check browser console for JavaScript errors
- [ ] Restart development server if needed

## 🎯 Success Criteria

Visual debugging is successful when:

1. **Scene Outliner**: Shows complete hierarchical tree with proper icons
2. **Node Inspector**: Displays detailed properties with expandable sections
3. **Node Graph**: Shows visual node connections with proper labels
4. **Real-time Sync**: Changes in Octane reflect in the web interface
5. **Performance**: Smooth interaction with no lag or errors

## 📚 Reference Files

### Key Source Files
- `client/src/App.tsx` - Main application layout
- `client/src/components/SceneOutliner.tsx` - Scene tree component
- `client/src/components/NodeInspector.tsx` - Property editor
- `client/src/components/NodeGraphEditor.tsx` - Visual node graph
- `client/src/services/OctaneClient.ts` - Core gRPC client
- `client/src/hooks/useOctane.tsx` - React hooks for Octane integration

### Documentation
- `OVERVIEW.md` - Project architecture and features
- `QUICKSTART.md` - Setup and run instructions
- Working octaneWeb reference in `../octaneWeb/` directory

---

**Status**: ✅ Production Ready  
**Last Updated**: 2025-01-20  
**Visual Debugging**: Fully Functional