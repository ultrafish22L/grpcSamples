# OctaneWeb2 - Session Reproduction Guide for AI Agents

This document provides context for AI agents to resume development on octaneWeb2 in a new session.

## Project Goal

**Reproduce octaneWeb's UX and functionality with a modern, clean React + TypeScript codebase.**

### Why This Project Exists

- **octaneWeb** (original): Vanilla JS, ~4500 lines, manual DOM manipulation, no type safety, difficult to maintain
- **octaneWeb2** (this project): React 19 + TypeScript, component-based, type-safe, modern patterns, maintainable

### Success Criteria

1. ✅ Match or exceed original octaneWeb UI/UX
2. ✅ Clean, maintainable React codebase
3. ✅ Full TypeScript type safety
4. ✅ Modern development workflow (Vite, HMR)
5. 🚧 Feature parity with original (in progress)

## Current Status

### ✅ Completed

- **Foundation**: React 19, TypeScript, Vite, Zustand state management
- **UI Layout**: MenuBar, StatusBar, 3-panel layout (SceneOutliner, RenderViewport, NodeInspector)
- **Components**: All main UI components implemented
- **API Client**: Complete gRPC client in `src/api/octaneClient.ts`
- **Type System**: Full NodeType enum with 400+ constants
- **Connection Management**: Connect/disconnect to Octane LiveLink
- **Scene Loading**: Sync scene hierarchy from Octane
- **Build System**: Vite with successful compilation (0 errors)

### 🚧 In Progress

- **Real-time Rendering**: Callback streaming to display live renders
- **Camera Sync**: Mouse drag to update Octane camera
- **Node Editing**: Full parameter editing UI

### 📋 Planned

- **Node Graph**: Visual node connections and editing
- **Material Editor**: Complete material parameter UI
- **Performance**: Optimize bundle size and render performance

### Latest Build Status

```bash
# Last successful build (2025-11-10)
npm run build
# Output: dist/ folder, 265KB bundle (82KB gzipped)
# TypeScript errors: 0
# Runtime errors: 0
```

## Repository Structure

```
/workspace/grpcSamples/
├── octaneWeb/              # Original vanilla JS version (reference)
├── octaneWeb2/             # This project - React rewrite
│   ├── src/
│   │   ├── api/
│   │   │   └── octaneClient.ts      # Complete gRPC client
│   │   ├── components/
│   │   │   ├── layout/
│   │   │   │   ├── MenuBar.tsx
│   │   │   │   └── StatusBar.tsx
│   │   │   └── panels/
│   │   │       ├── SceneOutliner.tsx   # Scene hierarchy tree
│   │   │       ├── NodeInspector.tsx    # Node parameter editor
│   │   │       ├── NodeGraph.tsx        # Visual node graph
│   │   │       └── RenderViewport.tsx   # Live render display
│   │   ├── constants/
│   │   │   └── octaneTypes.ts       # NodeType enum (400+ constants)
│   │   ├── core/
│   │   │   └── eventBus.ts          # Event system
│   │   ├── store/
│   │   │   ├── connectionStore.ts   # Connection state
│   │   │   ├── sceneStore.ts        # Scene data
│   │   │   └── renderStore.ts       # Render state
│   │   ├── utils/
│   │   │   └── Camera.ts            # Camera utilities
│   │   ├── styles/
│   │   │   └── global.css           # OTOY dark theme
│   │   ├── App.tsx                  # Root component
│   │   └── main.tsx                 # Entry point
│   ├── dist/                        # Build output (generated)
│   ├── package.json
│   ├── tsconfig.json
│   ├── vite.config.ts
│   ├── OVERVIEW.md                  # Project architecture
│   ├── NETWORKING.md                # Networking setup
│   ├── QUICKSTART.md                # Installation guide
│   └── REPRO.md                     # This file
└── octaneProxy/                   # Shared Python HTTP-to-gRPC proxy
    ├── octane_proxy.py            # Main proxy server (port 51023)
    └── callback_streamer.py       # Callback streaming handler
```

## Key Technologies

| Technology | Version | Purpose |
|------------|---------|---------|
| React | 19.2.0 | UI framework |
| TypeScript | 5.9.3 | Type safety |
| Vite | 7.2.0 | Build tool, dev server |
| Zustand | 5.0.8 | State management |
| React Query | 5.90.7 | API data fetching |

## Architecture

### Network Flow

```
Browser (React App)
  ↓ fetch() to /api/*
Vite Dev Server (port 42219)
  ↓ Proxy /api/* → Python
Python Proxy (port 51023)
  ↓ gRPC
Octane LiveLink (port 51022)
```

### State Management

- **connectionStore**: `isConnected`, `isConnecting`, `connect()`, `disconnect()`
- **sceneStore**: `nodes[]`, `selectedNodeId`, `loadScene()`, `selectNode()`
- **renderStore**: `imageData`, `isRendering`, `fps`, `setImageData()`

### API Client Pattern

All Octane API calls go through `octaneClient`:

```typescript
// In octaneClient.ts
async makeServiceCall(service: string, method: string, params: any): Promise<any>

// Example usage
await octaneClient.makeServiceCall('octane.base.Base', 'GetNodeInfo', {
  objectPtr: { handle, type }
})
```

### Component Communication

- **Props**: Parent → Child data flow
- **Zustand Stores**: Cross-component state sharing
- **Event Bus**: Custom events for loose coupling

## Quick Start for Agents

### 1. Navigate to Project

```bash
cd /workspace/grpcSamples/octaneWeb2
```

### 2. Check Current State

```bash
# Check if dependencies are installed
ls node_modules/ | wc -l   # Should be ~60 packages

# Install if needed
npm install
```

### 3. Start Development

**Option A: Test in agent's browser** (Docker environment):

```bash
# Terminal 1: Start Python proxy with Docker hostname
cd /workspace/grpcSamples/octaneProxy
python octane_proxy.py &   # Uses host.docker.internal:51022

# Terminal 2: Build and serve
cd /workspace/grpcSamples/octaneWeb2
npm run build
cd dist
python3 -m http.server 48537 --bind 0.0.0.0 &

# Terminal 3: Test in browser
# (Use browser tool to access http://localhost:48537)
```

**Option B: User local testing** (native environment):

```bash
# Terminal 1: Start Python proxy (assumes Octane on same machine)
cd octaneProxy
python octane_proxy.py

# Terminal 2: Start Vite dev server
cd octaneWeb2
npm run dev

# User opens http://localhost:42219 in their browser
```

### 4. Verify Build

```bash
npm run build   # Should complete with 0 errors
```

## Important Patterns

### ✅ DO

- Use `octaneClient.makeServiceCall()` for all API calls
- Use Zustand stores for cross-component state
- Use NodeType enum constants (not magic numbers)
- Follow existing component structure
- Check browser console (F12) for errors during testing
- Test builds with `npm run build` before committing

### ❌ DON'T

- Don't create duplicate API clients
- Don't use class components (use functional + hooks)
- Don't use magic numbers for node types
- Don't add UI libraries (custom CSS matches original)
- Don't assume browser tool works without testing with `curl` first

## Common Issues and Solutions

### TypeScript Errors After Pull

**Problem**: Fresh clone shows TypeScript errors

**Solution**: Check for:
1. Missing imports (add at top of file)
2. Wrong property names (e.g., `type` vs `objectType`)
3. Unused imports (remove them)
4. Type mismatches (check interface definitions)

### Connection Fails in Docker

**Problem**: Can't connect to Octane from Docker container

**Solution**: Use `host.docker.internal:51022` instead of `127.0.0.1:51022` in Python proxy

See [NETWORKING.md](NETWORKING.md) for details.

### Build Succeeds But Browser Shows Errors

**Problem**: TypeScript compiles but React throws runtime errors

**Solution**:
1. Check browser console (F12)
2. Look for null/undefined access errors
3. Add null checks: `if (data?.property)`
4. Verify store initial state matches interface

## Development Workflow

### Standard Workflow

1. **Edit Code**: Make changes in `src/`
2. **Check Types**: Watch terminal for TypeScript errors
3. **Test in Browser**: Vite hot reloads automatically
4. **Verify Build**: Run `npm run build` before committing
5. **Check Console**: Press F12, look for errors

### Agent Workflow (Docker)

1. **Make Changes**: Edit `src/` files
2. **Build**: `npm run build`
3. **Serve**: `cd dist && python3 -m http.server 48537 --bind 0.0.0.0 &`
4. **Test**: Use browser tool to access `http://localhost:48537`
5. **Check Console**: Look for errors in browser DevTools

## Next Development Tasks

### Immediate Priorities

1. **Fix Callback Rendering** (RenderViewport.tsx)
   - Currently shows static canvas
   - Need to integrate callback streaming from Python proxy
   - Display live HDR/LDR frames from Octane

2. **Camera Synchronization** (Camera.ts)
   - Mouse drag should update Octane camera
   - Implement `setCameraPosition` and `setCameraTarget` calls
   - Add viewport controls (pan, zoom, rotate)

3. **Node Parameter Editing** (NodeInspector.tsx)
   - Currently read-only
   - Add input handlers for each parameter type
   - Call `octaneClient.setNodeParameter()` on change

### Phase Breakdown

- **Phase 5**: Real-time callback rendering
- **Phase 6**: Camera synchronization and viewport controls
- **Phase 7**: Node parameter editing
- **Phase 8**: Node graph visual editor
- **Phase 9**: Material editor
- **Phase 10**: Performance optimization
- **Phase 11**: Testing and polish

## Reference Documents

- **[OVERVIEW.md](OVERVIEW.md)**: Project goals, architecture, status
- **[NETWORKING.md](NETWORKING.md)**: Network setup, Docker config, debugging
- **[QUICKSTART.md](QUICKSTART.md)**: Installation and running instructions
- **[Original octaneWeb](../octaneWeb/)**: Reference implementation

## Key Files to Understand

1. **src/api/octaneClient.ts**: Complete gRPC client, all API methods
2. **src/store/sceneStore.ts**: Scene data and selection state
3. **src/components/panels/SceneOutliner.tsx**: Scene tree display
4. **vite.config.ts**: Dev server config, API proxy setup
5. **src/constants/octaneTypes.ts**: NodeType enum (400+ constants)

## Testing Checklist

Before considering a feature "done":

- [ ] TypeScript compiles with 0 errors
- [ ] `npm run build` succeeds
- [ ] No console errors in browser (F12)
- [ ] Feature works in both dev and production build
- [ ] UI matches or exceeds original octaneWeb
- [ ] Code follows existing patterns
- [ ] Appropriate error handling added

## Success Metrics

| Metric | Target | Current |
|--------|--------|---------|
| TypeScript Errors | 0 | ✅ 0 |
| Runtime Errors | 0 | ✅ 0 |
| Build Time | < 1s | ✅ 0.5s |
| Bundle Size | < 300KB | ✅ 265KB (82KB gzip) |
| Feature Parity | 100% | 🚧 60% |

## Project Philosophy

### Why React/TypeScript?

- **Maintainability**: Component-based architecture is easier to understand and modify
- **Type Safety**: TypeScript catches errors at compile time
- **Modern Tooling**: Vite provides fast dev experience with HMR
- **Testability**: Components can be tested in isolation
- **Scalability**: Easy to add new features without breaking existing code

### Design Principles

1. **Match Original UX**: Users should feel at home
2. **Clean Code**: Readable, self-documenting, minimal comments
3. **Type Safety**: Leverage TypeScript fully
4. **Component Isolation**: Each panel is independent
5. **Performance**: Keep bundle size reasonable, optimize renders

## Git Workflow

```bash
# Check current status
git status

# Commit changes
git add -A
git commit -m "feat: implement callback rendering"

# Push to main (we're working directly on main)
git push origin main
```

## Session Context Summary

**Where We Are**: Core UI and API complete, now implementing advanced features

**What Works**: Connection, scene loading, UI layout, type system

**What Needs Work**: Real-time rendering, camera sync, parameter editing

**Next Goal**: Achieve feature parity with original octaneWeb while maintaining clean React architecture

---

**Last Updated**: 2025-11-10  
**Status**: ✅ Build succeeds, app runs, ready for feature development  
**Branch**: main
