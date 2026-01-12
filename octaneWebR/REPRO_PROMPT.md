# OctaneWebR - AI Context Resume

**Purpose**: Get AI assistant up to speed on octaneWebR project in new chat session.

## 🎯 Project Identity

**octaneWebR** = React 18 + TypeScript + Vite port of octaneWeb (vanilla JS version)

- **What**: Browser-based UI clone of Octane Standalone
- **How**: Communicates with Octane via gRPC LiveLink API (port 51022)
- **Architecture**: Single Vite dev server with embedded gRPC proxy plugin (no separate server needed)
- **Tech Stack**: React 18, TypeScript 5.6, Vite 6, ReactFlow 11, Custom CSS (no UI frameworks)

## ✅ Production-Ready Features

### Core Systems (All Working)
- **Scene Outliner**: Hierarchical tree with expand/collapse, node selection, icons (📁 🫖 🎯 📷 🌍)
- **Node Inspector**: Real-time parameter editing (checkboxes, numbers, vectors, colors, enums)
  - Full gRPC get/set integration: `ApiItem.setByAttrID` for parameter updates
  - Color pickers, enum dropdowns, vector inputs (float2/3/4)
  - Hierarchical tree view with expand/collapse groups
- **Node Graph Editor**: ReactFlow-based visual editor
  - Drag-and-drop nodes, zoom, pan, minimap
  - Custom OctaneNode components with pin coloring
  - Input pins use `pinInfo.pinColor`, output pins use `nodeInfo.nodeColor`
  - Context menu for node creation (Materials, Geometry, Textures, etc.)
  - Edge click-to-delete/reconnect (CSS fix: `pointer-events: stroke`)
- **Callback Render Viewport**: Real-time rendering
  - OnNewImage callbacks via WebSocket streaming
  - Mouse camera controls (drag rotate, scroll zoom)
  - HDR/LDR automatic format detection
  - Buffer corruption fix: proper HDR RGBA conversion isolation
- **Menu System**: File/Edit/Script/Module/Cloud/Window/Help menus
  - Native browser file dialogs for Open/Save
  - Recent files persistence (localStorage)
  - 13/40+ menu items implemented (cloud/module/script missing)

### gRPC Integration
- **Direct API Calls**: `client.callApi(service, method, params)` pattern
- **Services Used**: ApiProjectManager, ApiItem, ApiNode, ApiNodeGraph, ApiRenderEngine
- **Response Patterns**: Most return `{result: {...}}`, some return `{list: {...}}`
- **Embedded Proxy**: Vite plugin handles HTTP-to-gRPC conversion transparently

## 🚨 Critical Development Rules

### **NEVER BREAK WORKING CODE**
System is production-ready. Most dangerous pattern = breaking working functionality.

**DO NOT MODIFY**:
- Scene Outliner loading logic
- Node Inspector parameter loading
- Callback render viewport buffer processing
- ReactFlow integration

### **Mandatory Debugging Protocol**

**ALWAYS CHECK IN THIS ORDER**:
1. **Console logs** (F12) - Look for emoji markers:
   - 📤 API request sent
   - ✅ API success  
   - ❌ API error
   - 🔄 Scene conversion (Node Graph)
   - 📌 Pin detection
   - 🔗 Edge creation
   - 🎨 Rendering events

2. **TypeScript errors**:
   ```bash
   npm run build       # Full build
   tsc --noEmit        # Type check only
   ```

3. **Connection health**:
   ```bash
   curl http://localhost:43929/api/health
   ```

4. **Visual debugging** - ONLY when:
   - Console logs don't reveal issue
   - Complex state mutations
   - Async race conditions

**NEVER start debugging visually without checking console logs first.**

### **Testing Requirements**
Before committing:
- [ ] Run `npm run build` - No TypeScript errors
- [ ] Check browser console - No runtime errors
- [ ] Test with Octane connected - Verify functionality works
- [ ] Update docs if adding features

### **Never Use Mock Data**
- Always connect to real Octane LiveLink service
- Test with actual scenes loaded in Octane
- Verify API responses match real Octane behavior

## 🏗️ Architecture

### File Structure
```
octaneWebR/
├── client/src/
│   ├── components/          # React components
│   │   ├── SceneOutliner.tsx
│   │   ├── NodeInspector.tsx
│   │   ├── NodeGraph/
│   │   │   └── NodeGraphEditorNew.tsx  # ReactFlow implementation
│   │   └── CallbackRenderViewport.tsx
│   ├── hooks/
│   │   └── useOctane.tsx    # Octane client React hook
│   ├── services/
│   │   └── OctaneClient.ts  # Core gRPC client
│   └── types/
│       └── scene.ts         # TypeScript types
├── server/
│   ├── proto/               # Octane .proto files
│   ├── generated/           # Auto-generated TS types
│   └── vite-plugin-octane-grpc.ts  # Embedded proxy
├── OVERVIEW.md              # Architecture & features
├── QUICKSTART.md            # Setup guide
└── REPRO_PROMPT.md          # This file
```

### Data Flow
```
Browser (React) → Vite Dev Server (gRPC Plugin) → Octane LiveLink (127.0.0.1:51022)
                       ↓
                HTTP-to-gRPC proxy
                WebSocket callbacks
```

## 🔧 Quick Commands

```bash
# Start development
npm run dev

# Build & type check
npm run build

# Type check only (faster)
tsc --noEmit

# Regenerate protobuf types
npm run proto:generate

# Check health
curl http://localhost:43929/api/health
```

## 📊 Recent Fixes (v0.9.7)

- ✅ **Edge Clicks** (commit 471bacc9): Added CSS `pointer-events: stroke` to enable ReactFlow edge clicks
- ✅ **Output Pin Colors** (commit a1f2be66): Fixed to use `nodeInfo.nodeColor` instead of `pinInfo.pinColor`
- ✅ **ReactFlow API Compliance** (commit 62570d8b): Updated to ReactFlow 11 patterns

## 🚧 Known Limitations

- Material Database tabs (Live DB, Local DB) are UI placeholders - content not implemented
- Render Toolbar actions (~25 buttons) need API integration (start/stop/pause mostly missing)
- Menu system only 13/40+ items implemented (cloud/module/script menus missing)
- File loading dialogs work but not wired to Octane API

## 🎯 Development Patterns

### Making API Calls
```typescript
const { client, isConnected } = useOctane();

const response = await client.callApi('ApiItem', 'name', {
  handle: nodeHandle,
  type: 16 // ApiItem type
});

const name = response.result; // or response.list for collections
```

### Adding Console Logs
```typescript
console.log('📤 [Component] Action starting', { data });
console.log('✅ [Component] Action complete', { result });
console.error('❌ [Component] Action failed', { error });
```

### Error Handling
```typescript
try {
  const result = await client.callApi(...);
  // Handle success
} catch (error) {
  console.error('❌ Failed:', error);
  // Don't crash - graceful degradation
}
```

## 🔍 Debugging Connection Issues

**"Connection failed" errors are NOT code bugs**:
- `Connection refused (10061)`: Octane not running
- `Connection reset (10054)`: Network issue
- `Socket closed`: Octane disconnected

**Before assuming bugs**:
1. Is Octane running?
2. Is LiveLink enabled? (Help → LiveLink in Octane)
3. Is port 51022 accessible?
4. Try restarting dev server

## 📚 Documentation

- **OVERVIEW.md**: Complete architecture, debugging practices, development workflow
- **QUICKSTART.md**: Setup and quick start commands
- **REPRO_PROMPT.md**: This file - AI context resume

---

**STATUS**: ✅ Production-Ready Core  
**VERSION**: 0.9.7  
**LAST UPDATED**: 2025-01-23  
**RECENT CHANGES**: Edge clicks enabled, docs updated with debugging best practices
