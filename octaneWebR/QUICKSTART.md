# OctaneWebR Quick Start

Get up and running with OctaneWebR in 5 minutes.

## Prerequisites

Before starting, ensure you have:
- ✅ **Node.js 18+** installed ([download here](https://nodejs.org/))
- ✅ **Octane Render** installed with an active license
- ✅ **Git** for cloning the repository

## Installation

### 1. Clone Repository

```bash
git clone <repository-url>
cd grpcSamples/octaneWebR
```

### 2. Install Dependencies

```bash
npm install
```

This automatically:
- Installs all required packages
- Generates TypeScript types from protobuf definitions
- Sets up development environment

## Starting the Application

### Step 1: Start Octane Render

1. Launch **Octane Render**
2. Enable LiveLink: **Help → LiveLink** (or check if already enabled)
3. Verify it shows listening on **port 51022**

### Step 2: Start Development Server

```bash
npm run dev
```

Expected output:
```
  VITE v6.x.x  ready in XXX ms

  ➜  Local:   http://localhost:5173/
  ➜  Network: use --host to expose
  ➜  press h + enter to show help
  
  🟢 gRPC Proxy listening on /octaneapi/*
  🟢 Connecting to Octane at 127.0.0.1:51022
```

### Step 3: Open Browser

Navigate to: **http://localhost:5173**

You should see:
- ✅ **"Connected"** status (green) in top-right corner
- ✅ Scene outliner showing your Octane scene
- ✅ Render viewport ready for callbacks

## Interface Overview

### 📊 Top Menu Bar
- **File, Edit, Script, Module, Cloud, Window, Help** - Standard menus
- **Connection Status** (top-right) - Shows green "Connected" when working

### 🌲 Scene Outliner (Left Panel)
- **Scene tree view**: Hierarchical node display
- **🔄 Refresh**: Reload scene from Octane
- **Scene/Live DB/Local DB tabs**: Switch between views
- **Click nodes**: Select for inspection

### 🔍 Node Inspector (Bottom Left)
- **Property grid**: Shows selected node details
- **Attributes**: Node-specific parameters
- **Type info**: Node type and output pin type

### 🖼️ Render Viewport (Center)
- **Real-time rendering**: Callback-based display
- **Zoom controls**: 🔍+ / 🔍- buttons
- **1:1 button**: Reset zoom to 100%
- **⊞ Maximize**: Full-screen viewport

### 🔗 Node Graph Editor (Right Panel)
- **Visual node graph**: See node connections
- **Right-click**: Context menu for operations
- **+ button**: Add new nodes
- **🗑️ button**: Delete selected nodes

## First Steps

### 1. Load a Scene in Octane

If you see an empty scene outliner:
- Open an `.orbx` scene file in Octane, OR
- Add geometry manually (e.g., drag teapot into scene)
- Click **🔄 Refresh** in Scene Outliner

### 2. Explore the Scene Tree

- Click **🌳 Scene** to expand root node
- Click any child node (e.g., "teapot.obj")
- Watch **Node Inspector** update with properties

### 3. Test Real-time Rendering

- Look at **Render Viewport** in center
- If rendering in Octane, frames appear automatically
- Use zoom controls to adjust view

## Troubleshooting

### ❌ "Connection Failed" Status

**Cause**: Can't reach Octane LiveLink service

**Solutions**:
1. Verify Octane is running
2. Check **Help → LiveLink** is enabled
3. Ensure port 51022 is not blocked by firewall
4. Try restarting Octane
5. Check console for error details

### ❌ Empty Scene Outliner

**Cause**: No scene loaded in Octane

**Solutions**:
1. Load an `.orbx` file in Octane
2. Add geometry to scene manually
3. Click **🔄 Refresh** button
4. Check Octane's outliner shows items

### ❌ "Module not found" Errors

**Cause**: Missing dependencies or generated types

**Solutions**:
```bash
npm install              # Reinstall dependencies
npm run proto:generate   # Regenerate types
```

### ❌ Port Already in Use

**Cause**: Port 5173 is occupied

**Solutions**:
- Vite will auto-increment to next available port (5174, 5175, etc.)
- Check terminal for actual port number
- Or kill process using port: `lsof -ti:5173 | xargs kill`

### ❌ TypeScript Errors

**Cause**: Type mismatches or outdated generated code

**Solutions**:
```bash
npm run proto:generate   # Regenerate from .proto files
npm run check            # Run TypeScript type checker
```

## Development Workflow

### Making Changes

1. **Edit files**: Modify any `.tsx` or `.ts` file
2. **Auto-reload**: Browser updates instantly (Hot Module Replacement)
3. **Check console**: See API calls and errors in browser DevTools

### Useful Commands

```bash
npm run dev              # Start development server
npm run build            # Build for production
npm run preview          # Preview production build
npm run proto:generate   # Regenerate protobuf types
npm run check            # Run TypeScript type checker
```

### Browser DevTools

Open **Developer Tools** (F12) and check:

- **Console**: API call logging with 📤 (request) and ✅ (success) markers
- **Network**: HTTP requests to gRPC proxy
- **React DevTools**: Component hierarchy and state

## Next Steps

### Learn More
- Read **OVERVIEW.md** for architecture deep-dive
- Explore **client/src/components/** for React components
- Check **server/vite-plugin-octane-grpc.ts** for proxy logic

### Customize
- Modify **client/src/App.tsx** to change layout
- Edit **client/public/index.html** for theme colors
- Add new components in **client/src/components/**

### Integrate
- Call `useOctane()` hook in your components
- Use `client.callApi()` for any Octane API
- Subscribe to scene updates with React state

## Getting Help

### Check Logs
```bash
# Terminal shows server logs
# Browser console shows client logs
```

### Common Patterns

**Making an API call:**
```typescript
const { client } = useOctane();
const response = await client.callApi('ApiItem', 'name', objectPtr);
console.log(response.result); // "teapot.obj"
```

**Handling scene updates:**
```typescript
const { sceneTree } = useOctane();
useEffect(() => {
  console.log('Scene updated:', sceneTree);
}, [sceneTree]);
```

## System Requirements

- **OS**: Windows 10+, macOS 10.15+, or Linux
- **RAM**: 4GB minimum, 8GB+ recommended
- **Browser**: Chrome 90+, Firefox 88+, Edge 90+, Safari 14+
- **Octane**: 2020+ with LiveLink support

---

**Ready to build?** Start with `npm run dev` and explore the interface!

For detailed documentation, see **OVERVIEW.md**.  
For session restoration, see **REPRO_PROMPT.md**.
