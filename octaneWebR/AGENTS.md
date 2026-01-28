# octaneWebR - AI Assistant Memory

**Repository-specific knowledge and development context for AI assistants**

This file serves as persistent memory across sessions to help AI assistants understand the project structure, recent changes, and development workflows.

---

## Project Overview

**octaneWebR** is a React/TypeScript web UI clone of Octane Render Studio Standalone Edition. It communicates with a live instance of Octane via the gRPC LiveLink API.

### Key Facts
- **No Mocking**: All features connect to real Octane via gRPC
- **UI Clone**: Interface matches [Octane SE Manual](https://docs.otoy.com/standaloneSE/)
- **Tech Stack**: React 18 + TypeScript + Vite + ReactFlow + gRPC-Web
- **Architecture**: Service-based with event-driven communication
- **Styling**: CSS Variables theme system (no inline styles, no hardcoded colors)

---

## Recent Major Features (2025-01)

### Node Type Dropdown Feature ✅ COMPLETED
**Date**: January 2025  
**Status**: Fully implemented and tested

#### What Was Built
Added node type dropdown to NodeInspector for all non-end nodes (nodes with parameters/children):
- Dropdown shows compatible node types based on parent pin type
- Uses `PT_TO_NT` mapping from `PinTypes.ts`
- Selection replaces current node via gRPC while preserving UI state
- Extended from top-level node fake implementation to all applicable nodes

#### Files Modified
1. **`client/src/components/NodeInspector/index.tsx`**
   - Added `shouldShowDropdown()` - determines if node has parameters (non-end node)
   - Added `getCompatibleNodeTypes()` import from `PinTypes.ts`
   - Added `getNodeTypeInfo()` import from `NodeTypes.ts`
   - Added `handleNodeTypeChange()` - handles dropdown selection
   - Added dropdown JSX for non-end nodes with compatible type options

2. **`client/src/services/octane/NodeService.ts`**
   - Added `replaceNode()` method with create → connect → delete flow
   - Uses `ApiNode.create`, `connectPinByIndex`, `deleteNodeOptimized`
   - Emits `node:replaced` event for UI synchronization

3. **`client/src/services/OctaneClient.ts`**
   - Exposed `replaceNode()` method in public API

#### Implementation Details
```typescript
// Node replacement flow
async replaceNode(oldNodeHandle: number, newNodeType: string): Promise<number> {
  // 1. Create new node
  const newNode = await ApiNode.create(newNodeType);
  
  // 2. Find parent connection and reconnect
  const parents = await this.getNodeParents(oldNodeHandle);
  if (parents.length > 0) {
    await this.connectPinByIndex(parent, pin, newNode.handle);
  }
  
  // 3. Delete old node
  await this.deleteNodeOptimized(oldNodeHandle);
  
  // 4. Emit event
  this.emit('node:replaced', { oldHandle, newHandle: newNode.handle });
  
  return newNode.handle;
}
```

#### Testing Results
- ✅ TypeScript compilation passed
- ✅ Vite build succeeded
- ✅ Browser load successful
- ✅ Dropdowns rendered for: Camera, Sun direction, Daylight model, Geometry, Material, Film settings, Kernel
- ✅ No errors in server logs
- ✅ UI state preserved (collapsed panel states maintained)

---

## Development & Testing Workflow

### Standard Dev/Test Routine

This is the proven workflow for making changes and testing them:

#### 1. Stop Running Servers
```bash
# Kill any processes on dev ports
lsof -ti:57341,49019 2>/dev/null | xargs kill -9 2>/dev/null
echo "✅ Stopped all servers"
```

#### 2. Build Client
```bash
cd /workspace/project/grpcSamples/octaneWebR

# Type check first
npx tsc --noEmit
echo "✅ TypeScript compilation passed"

# Build production bundle
npm run build
echo "✅ Client build completed"

# Verify build output
ls -lh dist/client/assets/ | head -10
```

Expected output:
```
dist/client/
├── assets/
│   ├── index-[hash].js      (~800KB)
│   ├── index-[hash].css     (~50KB)
│   └── vendor-[hash].js     (~600KB)
└── index.html
```

#### 3. Start Development Server
```bash
# Start fresh dev server
npm run dev &
DEV_PID=$!

# Wait for server to be ready
sleep 5

# Verify server is running
curl -s http://localhost:57341/api/health | python3 -m json.tool
```

Expected response:
```json
{
  "status": "ok",
  "octane": "connected",
  "timestamp": 1737504000000
}
```

#### 4. Test in Browser
```bash
# Check server logs (should show):
# ✅ Vite dev server running at http://localhost:57341
# ✅ Connected to Octane at host.docker.internal:51022
# ✅ Callback registration successful
# ✅ WebSocket server listening
```

**Browser Checklist**:
1. Open `http://localhost:57341` in browser
2. Check browser console for connection logs:
   - ✅ "Connected to Octane"
   - ✅ "Scene tree loaded"
   - ✅ No errors
3. Test UI components:
   - Scene Outliner: Expand/collapse nodes
   - Node Graph Editor: Create/connect/delete nodes
   - Node Inspector: Edit parameters, test dropdowns
   - Viewport: Camera controls, render output

**Visual Verification**:
- Take screenshot for documentation
- Check dropdown rendering
- Verify icons load correctly
- Test interaction (click, hover, select)

#### 5. Test Feature-Specific Functionality

For **Node Type Dropdown** feature:
```javascript
// In browser console:
1. Select a node in Node Graph
2. Check Node Inspector shows dropdown
3. Open dropdown → verify compatible types shown
4. Select different type → verify node replacement
5. Check scene tree updated
6. Verify no console errors
```

#### 6. Review Logs
```bash
# Check for errors in terminal
# Look for:
# ✅ No TypeScript errors
# ✅ No gRPC connection errors
# ✅ No WebSocket disconnections
# ✅ No render callback failures
```

#### 7. Stop Servers
```bash
# Clean shutdown
kill $DEV_PID 2>/dev/null
lsof -ti:57341,49019 2>/dev/null | xargs kill -9 2>/dev/null
echo "✅ Stopped all servers"
```

### Quick Test Script
Save as `test-dev.sh`:
```bash
#!/bin/bash
set -e

echo "🧪 Starting development test routine..."

# 1. Stop servers
echo "1️⃣ Stopping existing servers..."
lsof -ti:57341,49019 2>/dev/null | xargs kill -9 2>/dev/null || true

# 2. Type check
echo "2️⃣ Running TypeScript check..."
npx tsc --noEmit

# 3. Build
echo "3️⃣ Building client..."
npm run build

# 4. Start server
echo "4️⃣ Starting dev server..."
npm run dev &
DEV_PID=$!

# 5. Wait and test
echo "5️⃣ Waiting for server..."
sleep 5
curl -s http://localhost:57341/api/health | python3 -m json.tool

echo ""
echo "✅ Dev server ready at http://localhost:57341"
echo "📋 Manual testing checklist:"
echo "   1. Open http://localhost:57341 in browser"
echo "   2. Check browser console for connection"
echo "   3. Test UI components"
echo "   4. Verify feature functionality"
echo ""
echo "⏹️  To stop: kill $DEV_PID"
```

---

## Architecture Patterns

### Service Layer
All services extend `BaseService` and follow consistent patterns:

```typescript
// services/octane/MyService.ts
export class MyService extends BaseService {
  async myMethod(param: Type): Promise<ResultType> {
    try {
      // 1. Make gRPC call
      const response = await this.apiCall(param);
      
      // 2. Emit event for UI synchronization
      this.emit('event:name', { data: response });
      
      // 3. Return result
      return response;
    } catch (error) {
      console.error('[MyService] myMethod failed:', error);
      throw error;
    }
  }
}
```

### Component Patterns
```typescript
// Functional components with hooks
const MyComponent: React.FC<Props> = ({ prop }) => {
  // 1. State
  const [state, setState] = useState<Type>(initial);
  
  // 2. Context
  const { client, connected } = useOctane();
  
  // 3. Effects
  useEffect(() => {
    const handler = (data) => setState(data);
    client.on('event:name', handler);
    return () => client.off('event:name', handler);
  }, [client]);
  
  // 4. Handlers
  const handleAction = async () => {
    try {
      await client.service.method();
    } catch (error) {
      console.error('Action failed:', error);
    }
  };
  
  // 5. Render
  return <div>{/* JSX */}</div>;
};
```

### gRPC Call Pattern
```typescript
// 1. Check proto file exists
// server/proto/apinodesystem_3.proto

// 2. Implement in service
async createNode(type: string): Promise<NodeHandle> {
  const response = await fetch(`${this.serverUrl}/api/node/create`, {
    method: 'POST',
    body: JSON.stringify({ nodeType: type })
  });
  return response.json();
}

// 3. Expose in OctaneClient
public get node() {
  return {
    create: (type: string) => this._nodeService.createNode(type)
  };
}

// 4. Use in component
const { client } = useOctane();
const node = await client.node.create('NT_DIFFUSE_MAT');
```

---

## Code Conventions

### TypeScript
- ✅ **Strict mode enabled** - No `any` types
- ✅ **Named exports** for utilities, default for components
- ✅ **Interface for props** - Define before component
- ✅ **Arrow functions** for components and handlers
- ✅ **Type guards** for unknown data

### Styling
- ✅ **CSS Variables** - Use `var(--octane-*)` for all colors/spacing
- ✅ **No inline styles** - Except dynamic values (transforms, etc.)
- ✅ **CSS Modules** - Component-scoped styles
- ✅ **Theme system** - `octane-theme.css` defines all variables

### File Naming
- ✅ **PascalCase** - Components: `MyComponent.tsx`
- ✅ **camelCase** - Utilities: `myUtility.ts`
- ✅ **kebab-case** - CSS files: `my-component.css`

### Import Order
```typescript
// 1. External dependencies
import React, { useEffect, useState } from 'react';
import { ReactFlowProvider } from '@xyflow/react';

// 2. Internal services
import { OctaneClient } from './services/OctaneClient';

// 3. Internal components
import { NodeGraph } from './components/NodeGraph';

// 4. Internal utilities
import { formatColor } from './utils/formatters';

// 5. Types
import type { SceneNode } from './types';

// 6. Styles
import styles from './MyComponent.module.css';
```

---

## Common Tasks

### Adding a Service Method

1. **Check proto file**
   ```bash
   grep -r "methodName" server/proto/
   ```

2. **Add to service**
   ```typescript
   // services/octane/MyService.ts
   async myMethod(param: Type): Promise<Result> {
     // Implementation
   }
   ```

3. **Expose in OctaneClient**
   ```typescript
   // services/OctaneClient.ts
   public get myService() {
     return {
       myMethod: (param) => this._myService.myMethod(param)
     };
   }
   ```

4. **Use in component**
   ```typescript
   const result = await client.myService.myMethod(param);
   ```

### Adding an Icon

1. **Verify icon exists**
   ```bash
   ls client/public/icons/ | grep "ICON_NAME"
   ```

2. **Add mapping**
   ```typescript
   // constants/IconMapping.ts
   export const iconMap = {
     'MY_KEY': '/icons/my_icon.png'
   };
   ```

3. **Use in component**
   ```typescript
   import { getNodeIconPath } from '../constants/IconMapping';
   const icon = getNodeIconPath('MY_KEY');
   ```

### Debugging Checklist

1. **Browser console** - Check for errors
2. **Network tab** - Verify gRPC calls
3. **TypeScript** - Run `npx tsc --noEmit`
4. **Server logs** - Check terminal output
5. **Octane** - Ensure LiveLink enabled

---

## Known Issues & Solutions

### Issue: WebSocket Connection Warnings
**Symptom**: Warnings on page refresh  
**Fix**: 50ms delay in onopen handler (already implemented)  
**Status**: ✅ Resolved

### Issue: Scene Tree Not Loading
**Symptom**: Empty scene outliner  
**Fix**: Press F5 (Refresh Scene) or check Octane has scene loaded  
**Status**: User action required

### Issue: TypeScript Errors on Build
**Symptom**: Build fails with type errors  
**Fix**: Run `npx tsc --noEmit` to see specific errors  
**Common causes**: Missing imports, incorrect types, unused variables  
**Status**: Check each error individually

### Issue: Icons Not Showing
**Symptom**: Broken image icons  
**Fix**: 
1. Check icon exists: `ls client/public/icons/[name].png`
2. Verify mapping in `constants/IconMapping.ts`
3. Check browser network tab for 404s  
**Status**: Verify file paths

---

## Dependencies

### Core Dependencies
```json
{
  "react": "^18.2.0",
  "react-dom": "^18.2.0",
  "typescript": "^5.2.2",
  "@xyflow/react": "^12.0.0",
  "zustand": "^4.5.0",
  "@grpc/grpc-js": "^1.9.0",
  "google-protobuf": "^3.21.0"
}
```

### Dev Dependencies
```json
{
  "vite": "^5.0.0",
  "@vitejs/plugin-react": "^4.2.0",
  "ts-node": "^10.9.0",
  "nodemon": "^3.0.0",
  "concurrently": "^8.2.0"
}
```

### Build Tools
- **Vite** - Dev server and bundler
- **TypeScript** - Type checking
- **ts-node** - TypeScript execution
- **nodemon** - Auto-restart on changes
- **concurrently** - Run multiple npm scripts

---

## File Structure

```
octaneWebR/
├── client/src/
│   ├── components/          # React UI components
│   │   ├── NodeGraph/       # ReactFlow node editor
│   │   ├── SceneOutliner/   # Scene tree view
│   │   ├── NodeInspector/   # Parameter editor ⭐ RECENTLY MODIFIED
│   │   ├── CallbackRenderViewport/  # Live render
│   │   ├── MenuBar/         # Top menu
│   │   ├── RenderToolbar/   # Render controls
│   │   └── MaterialDatabase/  # LiveDB/LocalDB
│   ├── services/            # Business logic
│   │   ├── octane/
│   │   │   ├── NodeService.ts       # ⭐ RECENTLY MODIFIED
│   │   │   ├── SceneService.ts
│   │   │   ├── ViewportService.ts
│   │   │   ├── RenderService.ts
│   │   │   └── MaterialDatabaseService.ts
│   │   └── OctaneClient.ts  # ⭐ RECENTLY MODIFIED
│   ├── constants/
│   │   ├── NodeTypes.ts     # 755+ node type definitions
│   │   ├── PinTypes.ts      # PT_TO_NT mapping ⭐ USED BY NEW FEATURE
│   │   └── IconMapping.ts   # Icon mappings
│   ├── utils/               # Helper functions
│   ├── hooks/               # React hooks
│   ├── styles/              # CSS files
│   │   ├── octane-theme.css  # 134 CSS variables
│   │   ├── app.css
│   │   ├── node-graph.css
│   │   ├── node-inspector.css
│   │   ├── scene-outliner.css
│   │   └── viewport.css
│   └── App.tsx              # Root component
├── server/
│   ├── proto/               # gRPC proto files
│   └── src/                 # Proxy server
├── scripts/                 # Build utilities
├── vite-plugin-octane-grpc.ts  # Embedded proxy
├── package.json
├── tsconfig.json
├── vite.config.mts
├── README.md               # Project overview
├── QUICKSTART.md           # Setup guide
├── DEVELOPMENT.md          # Dev guide
├── CHANGELOG.md            # Version history
└── AGENTS.md               # This file
```

---

## Reference Links

- **Octane SE Manual**: https://docs.otoy.com/standaloneSE/
- **ReactFlow Docs**: https://reactflow.dev/
- **React Docs**: https://react.dev/
- **Vite Guide**: https://vitejs.dev/guide/
- **TypeScript Handbook**: https://www.typescriptlang.org/docs/

---

## AI Assistant Guidelines

When working on this project:

1. **Always check this file first** - It contains up-to-date project context
2. **Follow established patterns** - See Architecture Patterns section
3. **Use the dev/test workflow** - See Development & Testing Workflow section
4. **No inline styles** - Use CSS variables from `octane-theme.css`
5. **No `any` types** - TypeScript strict mode enabled
6. **Test with real Octane** - No mocking, real gRPC connections only
7. **Update this file** - Document significant changes here

### When Adding Features
1. Check Octane SE Manual for UI reference
2. Check proto files for available gRPC APIs
3. Follow service-based architecture
4. Use existing component patterns
5. Test with the standard workflow

### When Debugging
1. Check browser console first
2. Run TypeScript check: `npx tsc --noEmit`
3. Check server logs in terminal
4. Verify Octane connection and LiveLink
5. Review this file for known issues

---

**Last Updated**: 2025-01-22  
**Status**: Active development  
**Next Tasks**: See project backlog in GitHub Issues

