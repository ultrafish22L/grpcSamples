# octaneWebR - AI Assistant Context & Reproduction Prompt

**For AI assistants helping with debugging, development, or feature implementation**

---

## 🎯 **Project Overview**

**octaneWebR** is a pixel-perfect React/TypeScript clone of [Octane Render Studio Standalone Edition](https://docs.otoy.com/standaloneSE/) that connects to a live Octane Render instance via gRPC LiveLink API.

**Mission**: Create a production-ready web-based UI that looks and behaves identically to Octane SE, with complete functional parity using real gRPC API calls (no mocks/simulations).

---

## 🏗️ **Architecture Summary**

### **Technology Stack**
- **Frontend**: React 18.2 + TypeScript 5.3 + Vite 5.4
- **Node Graph**: ReactFlow v12 (custom nodes with pin connections)
- **Communication**: gRPC-Web (via embedded Vite proxy plugin)
- **Protobuf**: 30+ .proto files defining Octane's gRPC API
- **State Management**: React hooks + event system for cross-component updates

### **Key Components**
1. **NodeGraphEditorNew.tsx** - Main node graph editor (ReactFlow-based, 1500+ lines)
2. **SceneOutliner.tsx** - Hierarchical scene tree viewer (left panel)
3. **NodeInspector.tsx** - Parameter editor (right panel)
4. **CallbackRenderViewport.tsx** - Live render viewport with camera controls
5. **OctaneClient.ts** - Main gRPC client wrapper (all API calls)

### **Directory Structure**
```
octaneWebR/
├── client/                    # React frontend
│   ├── src/
│   │   ├── components/        # React components
│   │   ├── services/          # Business logic (OctaneClient.ts)
│   │   ├── hooks/             # React hooks
│   │   ├── utils/             # Helper functions
│   │   ├── constants/         # Enums and constants
│   │   └── App.tsx            # Root component
│   └── public/                # Static assets (icons, favicon)
├── server/                    # Vite plugin (gRPC proxy)
│   ├── proto/                 # Compiled .proto files
│   └── src/index.ts           # vite-plugin-octane-grpc.ts
├── vite.config.mts            # Vite configuration
├── tsconfig.json              # TypeScript config
└── package.json               # Dependencies
```

---

## 🔌 **Connection Flow**

1. **User starts Octane Render** with LiveLink enabled (default port: 51022)
2. **User runs `npm run dev`** (starts Vite dev server on port 43930)
3. **Vite plugin** creates gRPC proxy at `/api/grpc/*` endpoints
4. **React app** loads in browser, connects to proxy
5. **OctaneClient** initializes gRPC stubs for all services
6. **Scene tree loads** via `ApiRender.getGraph()` + recursive node traversal
7. **WebSocket opens** for streaming callbacks (render updates, camera changes)
8. **Bidirectional sync** maintained: UI changes → Octane, Octane changes → UI

---

## 🧩 **Proto Files & Services**

### **Core Proto Files** (in `server/proto/`)
- **apirender.proto** - Main render service, scene graph operations
- **apinodesystem_3.proto** - Node/item manipulation (CRITICAL: use v3, not v1)
- **common.proto** - Enums (NodeType, AttributeId, PinType, etc.)
- **api.proto** - Base API types (Value, Handle, Pin, etc.)
- **attributes.proto** - Parameter attribute definitions

### **Service Mapping** (vite-plugin-octane-grpc.ts)
```typescript
const serviceToProtoMap = {
  ApiRender: 'apirender.proto',
  ApiItem: 'apinodesystem_3.proto',        // ⚠️ CRITICAL: use v3
  ApiItemService: 'apinodesystem_3.proto',
  ApiItemGetter: 'apinodesystem_3.proto',
  ApiItemSetter: 'apinodesystem_3.proto',
  StreamCallbackService: 'apirender.proto',
  // ... 20+ more services
};
```

### **Common gRPC Call Patterns**

**Create Node**:
```typescript
const response = await client.ApiRender.createNode({
  graphId: renderTargetHandle,
  type: NodeType.NT_DIFFUSE_MAT,
  name: 'Diffuse Material'
});
const newNodeHandle = response.handle;
```

**Connect Pins**:
```typescript
await client.ApiRender.connectPins({
  srcHandle: sourceNodeHandle,
  srcPinName: 'outMaterial',
  dstHandle: destNodeHandle,
  dstPinName: 'inMaterial'
});
```

**Set Parameter**:
```typescript
await client.ApiItemSetter.set({
  target: nodeHandle,
  name: 'diffuse',
  value: { floatVec3: [1.0, 0.5, 0.2] }
});
```

**Get Parameter**:
```typescript
const response = await client.ApiItemGetter.getValueByAttrID({
  itemHandle: nodeHandle,
  attrID: AttributeId.P_DIFFUSE  // from common.proto enum
});
```

---

## 🐛 **Recent Issues & Fixes**

### **Issue 1: Proto Loading Error** (FIXED - Jan 22, 2025)
**Symptom**: `duplicate name 'getRequest' in Type ApiItem`

**Root Cause**: `apinodesystem.proto` had duplicate message definitions causing protobuf parser errors

**Solution**: 
- Switched all ApiItem services to use `apinodesystem_3.proto`
- Updated `serviceToProtoMap` in vite-plugin-octane-grpc.ts (lines 92-95)

**Result**: Proto loads cleanly, all ApiItem calls now work

---

### **Issue 2: findAttr 500 Error** (FIXED - Jan 22, 2025)
**Symptom**: `/api/grpc/ApiItem/findAttr` returns 500 error

**Root Causes**: 
1. Wrong AttributeId value (61460 instead of 2672)
2. Passing "0" string as handle (invalid)

**Solution**:
- Changed `P_LOCK_RENDER_AOVS` AttributeId from 61460 to 2672 (OctaneClient.ts lines 1038, 1068)
- Added handle validation in `getFilmSettingsNode()` (lines 1015-1018):
  ```typescript
  if (!filmSettingsHandle || filmSettingsHandle === "0") {
    console.warn("Film Settings node not connected");
    return null;
  }
  ```

**Result**: Film Settings detection fails gracefully when not connected

---

### **Issue 3: Favicon 404** (FIXED - Jan 22, 2025)
**Symptom**: Browser console shows 404 for `/favicon.ico`

**Solution**: Added `client/public/favicon.ico` file

**Result**: No more 404 errors

---

### **Issue 4: "No valid image data in callback"** (NOT AN ERROR)
**Symptom**: Console warning when callbacks arrive without render images

**Status**: Expected behavior - happens when no render is active (2-4 times at startup, then stops)

**No fix needed**: Warning is informational only

---

## 🔍 **Common Debugging Patterns**

### **Proto Method Not Found**
1. Check if method exists in correct .proto file
2. Verify `serviceToProtoMap` points to right proto
3. Ensure proto is loaded: check `server/proto/` directory
4. Restart dev server to reload proto files

### **gRPC Call Returns 500 Error**
1. Check parameter types match proto definition
2. Verify handles are valid (not "0", null, or undefined)
3. Test with `test-findattr.js` or similar standalone script
4. Enable debug logging in OctaneClient.ts

### **UI Not Updating After API Call**
1. Check if event is emitted after API call
2. Verify event listeners in target component
3. Use React DevTools to inspect state changes
4. Check browser console for errors

### **Scene Tree Empty**
1. Verify Octane is running with LiveLink enabled
2. Check browser console for connection errors
3. Test connection: `curl http://localhost:43930/api/health`
4. Restart Octane and re-enable LiveLink

---

## 📝 **Development Guidelines**

### **When Implementing New Features**
1. ✅ Verify feature exists in [Octane SE Manual](https://docs.otoy.com/standaloneSE/)
2. ✅ Check proto files for required API methods
3. ✅ Use existing patterns from OctaneClient.ts
4. ✅ Add error handling (try/catch for all API calls)
5. ✅ Test with `npm run build` (must pass)
6. ✅ Test manually with `npm run dev`
7. ✅ Commit with descriptive message
8. ✅ Push to main
9. ✅ Update README.md Recent Achievements

### **Code Style**
- Use TypeScript strict mode (no `any` types)
- Async/await for all API calls (not `.then()` chains)
- Handle errors gracefully with try/catch
- Add comments for complex logic only
- Keep functions focused and small

### **Commit Messages**
```
Fix proto loading error in ApiItem services

- Switched to apinodesystem_3.proto to avoid duplicate 'getRequest'
- Updated serviceToProtoMap in vite-plugin-octane-grpc.ts
- All ApiItem gRPC calls now working
- Tested with scene tree load (314 nodes)
```

---

## 🚀 **Quick Start Commands**

```bash
# Install dependencies (first time only)
npm install

# Start development server
npm run dev

# Production build
npm run build

# Type check only
npx tsc --noEmit

# Test gRPC connection
curl http://localhost:43930/api/health

# View logs
# Browser: F12 → Console tab
# Server: Terminal where `npm run dev` is running
```

---

## 📦 **Key Dependencies**

```json
{
  "react": "^18.2.0",
  "typescript": "^5.3.3",
  "vite": "^5.4.21",
  "reactflow": "^12.3.4",
  "@grpc/grpc-js": "^1.12.4",
  "google-protobuf": "^3.21.4"
}
```

---

## 🔗 **Important Links**

- **Octane SE Manual**: https://docs.otoy.com/standaloneSE/CoverPage.html
- **GitHub Repo**: https://github.com/ultrafish22L/grpcSamples
- **ReactFlow Docs**: https://reactflow.dev/
- **gRPC Concepts**: https://grpc.io/docs/what-is-grpc/core-concepts/

---

## 🎓 **Learning Path for New Contributors**

### **Day 1: Understand the Basics**
1. Read this file (REPRO_PROMPT.md)
2. Read README.md "Current Status" section
3. Read QUICKSTART.md and run the app
4. Browse [Octane SE Manual](https://docs.otoy.com/standaloneSE/) (skim UI sections)

### **Day 2: Explore the Code**
1. **client/src/App.tsx** - See initialization flow
2. **client/src/services/OctaneClient.ts** - Understand gRPC patterns
3. **client/src/components/NodeGraph/NodeGraphEditorNew.tsx** - Main editor logic
4. **server/proto/** - Skim proto files (common.proto, apirender.proto, apinodesystem_3.proto)

### **Day 3: Make First Change**
1. Pick a small task (e.g., add tooltip, fix styling)
2. Make change, test with `npm run dev`
3. Build with `npm run build`
4. Commit and push
5. Update README.md

---

## 🧪 **Testing Checklist**

Before committing, verify:

- [ ] `npm run build` passes without errors
- [ ] `npm run dev` starts successfully
- [ ] Browser console shows no red errors
- [ ] Scene tree loads (left panel shows nodes)
- [ ] Feature works in both octaneWebR and Octane SE
- [ ] No TypeScript errors in code editor
- [ ] Code follows existing patterns
- [ ] Commit message is descriptive

---

## 🆘 **Common Errors & Solutions**

| Error | Cause | Solution |
|-------|-------|----------|
| `duplicate name 'getRequest'` | Wrong proto file | Use apinodesystem_3.proto, not apinodesystem.proto |
| `Cannot read property of undefined` | Handle is null | Check handle validity before API call |
| `Method not found` | Wrong service name | Verify serviceToProtoMap in vite-plugin-octane-grpc.ts |
| `WebSocket closed` | Octane disconnected | Restart Octane, re-enable LiveLink |
| `Scene tree empty` | Connection failed | Check Octane running, LiveLink enabled |
| `500 error on API call` | Invalid parameters | Check proto definition, validate handles |

---

## 📊 **Project Statistics**

- **Lines of Code**: ~15,000 TypeScript/TSX
- **React Components**: 30+
- **Proto Files**: 30+
- **Supported Node Types**: 755+
- **API Methods**: 200+
- **Development Time**: Ongoing since Jan 2025
- **Status**: Production-ready core, all runtime errors resolved

---

## 🎯 **AI Assistant Instructions**

When helping with this project:

1. **Always check proto files first** - Most issues relate to proto definitions
2. **Use apinodesystem_3.proto** - NOT apinodesystem.proto (has duplicates)
3. **Validate handles** - Check for null/"0" before API calls
4. **Follow existing patterns** - Look at OctaneClient.ts for examples
5. **Test before committing** - `npm run build` must pass
6. **Update README** - Add achievements to "Recent Achievements" section
7. **Push to main** - Always push after fixing/implementing

### **Debugging Workflow**
1. Reproduce error (check browser console + terminal)
2. Identify root cause (proto? handle? connection?)
3. Check recent fixes in this file (avoid re-fixing)
4. Implement fix using existing patterns
5. Test with `npm run build` and `npm run dev`
6. Commit, push, update README

---

**Last Updated**: 2025-01-22  
**Version**: 1.0.0  
**For**: AI assistants, new developers, debugging sessions
