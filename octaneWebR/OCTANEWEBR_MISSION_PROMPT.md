# OctaneWebR: Production-Ready React TypeScript Port - Mission Brief

## 🎯 Project Goal

Create **octaneWebR**, a modern React TypeScript application that faithfully reproduces the production-ready **octaneWeb** application with enhanced architecture. This is a **port, not a rewrite** - every UI element, interaction, and feature must be preserved exactly.

## 📋 Executive Summary

**What You're Building:**
- A React TypeScript UI that looks and behaves identically to octaneWeb
- A Node.js backend with direct gRPC communication to Octane Standalone (no Python proxy)
- Same professional OTOY branding, panel layouts, and user experience
- All existing functionality: Scene Outliner, Node Inspector, Node Graph Editor, Real-time Rendering

**What You're Replacing:**
- Vanilla JavaScript → React TypeScript with functional components and hooks
- Python HTTP-to-gRPC proxy → Node.js direct gRPC communication
- Programmatic DOM manipulation → React declarative rendering

**What You Must Preserve:**
- Exact visual appearance (same CSS, colors, fonts, spacing, layouts)
- All user interactions and workflows
- Real-time callback streaming for rendering updates
- Camera synchronization on mouse drag
- Scene hierarchy and node graph editing
- All render controls and debugging features

---

## 🏗️ Architecture Overview

### Current octaneWeb Architecture
```
Browser (Vanilla JS) → HTTP/JSON → Python Proxy (octaneProxy) → gRPC → Octane Standalone (port 51022)
                     ← HTTP/JSON ←                            ← gRPC ←
```

### Target octaneWebR Architecture  
```
Browser (React TS) → HTTP/JSON/WebSocket → Node.js Server (Express) → gRPC → Octane Standalone (port 51022)
                   ← HTTP/JSON/WebSocket ←                          ← gRPC ←
```

### Key Architectural Changes
1. **Frontend**: Vanilla JS → React TypeScript with Vite build system
2. **Backend**: Python aiohttp → Node.js Express with @grpc/grpc-js
3. **Communication**: Same HTTP/JSON + WebSocket for callbacks
4. **Styling**: Preserve exact CSS, migrate to CSS modules or styled-components
5. **State Management**: React Context API + hooks (useState, useEffect, useCallback)

---

## 📂 Repository Structure Analysis

### Source Material: octaneWeb/
```
octaneWeb/
├── index.html                          # Main HTML shell
├── js/
│   ├── app.js                         # Application entry point, initialization
│   ├── core/
│   │   ├── OctaneWebClient.js        # Main gRPC client wrapper (YOUR KEY REFERENCE)
│   │   ├── EventSystem.js            # Event bus for component communication
│   │   └── StateManager.js           # Global state management
│   ├── components/
│   │   ├── CallbackRenderViewport.js # Real-time rendering display (critical!)
│   │   ├── RenderViewport.js         # Standard viewport
│   │   ├── SceneOutlinerSync.js      # Scene tree view (DOM creation pattern)
│   │   ├── NodeInspector.js          # Node property editor (DOM creation pattern)
│   │   ├── NodeGraphEditor.js        # Visual node graph
│   │   ├── RenderToolbar.js          # Render control buttons
│   │   └── MenuSystem.js             # Top menu bar
│   ├── utils/
│   │   ├── GenericNodeRenderer.js    # Reusable DOM builders (STUDY THIS)
│   │   ├── LayoutManager.js          # Panel layout system
│   │   ├── Camera.js                 # Camera math and controls
│   │   └── DebugConsole.js           # Debug overlay
│   └── constants/
│       └── octaneNodeTypes.js        # Node type definitions
├── css/
│   ├── octane-theme.css              # Main theme (OTOY branding)
│   ├── components.css                # Component-specific styles
│   └── layout.css                    # Panel layouts
└── shared/js/
    └── webgl-utils.js                # WebGL helpers

octaneProxy/                           # Python proxy (REFERENCE FOR GRPC LOGIC)
├── octane_proxy.py                    # Main proxy logic
├── callback_streamer.py               # Real-time callback system
└── generated/                         # Python protobuf bindings
    └── *_pb2.py

sdk/src/api/grpc/protodef/            # Source .proto files
├── apiprojectmanager.proto
├── apirenderengineservice.proto
├── apiobjectgraphservice.proto
└── [many more...]
```

### Target Structure: octaneWebR/
```
octaneWebR/
├── package.json                       # Node.js dependencies
├── tsconfig.json                      # TypeScript configuration
├── vite.config.ts                     # Vite build config
├── .env.example                       # Environment variables template
├── README.md                          # Setup and usage documentation
│
├── client/                            # React TypeScript frontend
│   ├── src/
│   │   ├── main.tsx                  # React entry point
│   │   ├── App.tsx                   # Main application component
│   │   ├── components/               # React components (one per octaneWeb component)
│   │   │   ├── CallbackRenderViewport.tsx
│   │   │   ├── SceneOutliner.tsx
│   │   │   ├── NodeInspector.tsx
│   │   │   ├── NodeGraphEditor.tsx
│   │   │   ├── RenderToolbar.tsx
│   │   │   └── MenuSystem.tsx
│   │   ├── hooks/                    # Custom React hooks
│   │   │   ├── useOctaneClient.ts   # gRPC client hook
│   │   │   ├── useSceneState.ts     # Scene state management
│   │   │   └── useCamera.ts         # Camera controls
│   │   ├── services/                 # Business logic
│   │   │   ├── OctaneClient.ts      # Main API client (port from OctaneWebClient.js)
│   │   │   └── CallbackStreamer.ts  # WebSocket callback handler
│   │   ├── types/                    # TypeScript interfaces
│   │   │   ├── octane.d.ts          # Octane API types
│   │   │   └── scene.d.ts           # Scene object types
│   │   ├── utils/                    # Helper functions
│   │   │   ├── camera.ts            # Camera math
│   │   │   └── formatting.ts        # Data formatting
│   │   ├── constants/                # Constants
│   │   │   └── nodeTypes.ts         # Node type definitions
│   │   └── styles/                   # CSS modules or styled-components
│   │       ├── theme.module.css     # Port of octane-theme.css
│   │       ├── components.module.css
│   │       └── layout.module.css
│   ├── public/                       # Static assets
│   │   └── assets/                   # Icons, images
│   └── index.html                    # HTML shell
│
├── server/                            # Node.js backend
│   ├── src/
│   │   ├── index.ts                  # Server entry point
│   │   ├── grpc/                     # gRPC client setup
│   │   │   ├── client.ts            # gRPC connection management
│   │   │   ├── services.ts          # Service method wrappers
│   │   │   └── callbacks.ts         # Callback registration
│   │   ├── api/                      # Express routes
│   │   │   ├── routes.ts            # HTTP endpoints
│   │   │   └── websocket.ts         # WebSocket handler
│   │   ├── generated/                # Generated TypeScript protobuf bindings
│   │   │   └── [auto-generated]
│   │   └── utils/
│   │       └── logger.ts
│   └── proto/                        # Protobuf definitions (copied from sdk/)
│       └── *.proto
│
└── scripts/                           # Build and development scripts
    ├── generate-proto.sh             # Generate TS bindings from .proto files
    └── start-dev.sh                  # Start both client and server in dev mode
```

---

## 🔍 Phase 1: Analysis & Planning (DO THIS FIRST)

### 1.1 Study Current Implementation

**Critical Files to Analyze:**

1. **OctaneWebClient.js** (Lines to study: entire file ~800 lines)
   - Understand the `makeApiCall()` function pattern
   - Identify all gRPC service/method calls used
   - Note state management patterns
   - Extract callback registration logic

2. **octane_proxy.py** (Lines to study: focus on `handle_grpc_request()` function)
   - Understand how it maps HTTP requests to gRPC calls
   - Note protobuf message construction patterns
   - Identify special case handling for different request types
   - Study how it loads protobuf classes dynamically

3. **CallbackRenderViewport.js** (Critical for real-time rendering)
   - HDR/LDR buffer processing
   - WebGL texture updates
   - Frame rate handling
   - Error recovery patterns

4. **SceneOutlinerSync.js, NodeInspector.js** (DOM creation patterns)
   - How they programmatically build UI elements
   - CSS classes they use (these are the ACTIVE styles)
   - Event handler patterns
   - Hierarchy management

5. **GenericNodeRenderer.js** (Reusable UI patterns)
   - Generic control builders
   - Parameter type handling
   - Validation patterns

**Deliverable for Phase 1.1:**
Create `ANALYSIS.md` documenting:
- List of all gRPC services and methods used
- All CSS classes actually used by components
- State management patterns identified
- Critical algorithms that must be preserved exactly
- Special cases and edge cases handled

### 1.2 Extract Active CSS Styles

**Task:** Create a minimal CSS file with only the styles actually used.

**Method:**
1. Search through SceneOutlinerSync.js for all `classList.add()`, `className=` patterns
2. Search through NodeInspector.js for same
3. Search through GenericNodeRenderer.js for same
4. Search all component files for CSS class usage
5. Extract ONLY those rules from octane-theme.css, components.css, layout.css

**Deliverable for Phase 1.2:**
- `octaneWebR/client/src/styles/extracted-active-styles.css` - The minimal working CSS
- `CSS_MAPPING.md` - Document which classes are used where

### 1.3 Map gRPC Service Architecture

**Task:** Create a complete mapping of how Python proxy translates to Node.js gRPC.

**Study:**
1. How octane_proxy.py imports protobuf modules
2. How it creates gRPC stubs
3. How it constructs Request objects
4. How it handles Empty vs. populated requests
5. How callback_streamer.py manages streaming callbacks

**Deliverable for Phase 1.3:**
- `GRPC_MIGRATION_GUIDE.md` documenting:
  - Node.js equivalents for each Python pattern
  - How to use @grpc/grpc-js and @grpc/proto-loader
  - Request object construction patterns
  - Callback streaming setup in Node.js

---

## 🏗️ Phase 2: Setup & Infrastructure (BUILD THE FOUNDATION)

### 2.1 Initialize Project Structure

**Tasks:**
1. Create octaneWebR directory at same level as octaneWeb
2. Initialize Node.js project with TypeScript:
   ```bash
   npm init -y
   npm install --save-dev typescript @types/node vite @vitejs/plugin-react
   ```

3. Setup monorepo structure (client + server):
   ```bash
   npm install --save-dev concurrently nodemon
   ```

4. Configure TypeScript (tsconfig.json for both client and server)

5. Configure Vite for React development

**Deliverable for Phase 2.1:**
- Working package.json with all dependencies
- TypeScript configurations
- Build scripts in package.json
- Basic folder structure created

### 2.2 Generate TypeScript Protobuf Bindings

**Critical Task:** Generate TypeScript bindings from .proto files.

**Method:**
1. Copy relevant .proto files from `sdk/src/api/grpc/protodef/` to `server/proto/`
2. Install protobuf tooling:
   ```bash
   npm install --save-dev grpc-tools @grpc/proto-loader
   npm install @grpc/grpc-js google-protobuf
   ```

3. Create generation script `scripts/generate-proto.sh`:
   ```bash
   #!/bin/bash
   PROTO_DIR="./server/proto"
   OUT_DIR="./server/src/generated"
   
   mkdir -p $OUT_DIR
   
   # Generate TypeScript bindings
   grpc_tools_node_protoc \
     --plugin=protoc-gen-ts=./node_modules/.bin/protoc-gen-ts \
     --ts_out=grpc_js:$OUT_DIR \
     --js_out=import_style=commonjs:$OUT_DIR \
     --grpc_out=grpc_js:$OUT_DIR \
     -I $PROTO_DIR \
     $PROTO_DIR/*.proto
   ```

4. Test generation with a simple .proto file first

**Deliverable for Phase 2.2:**
- Working protobuf generation script
- Generated TypeScript bindings in server/src/generated/
- Type definitions exported for client use

### 2.3 Create Node.js gRPC Client

**Task:** Build the core gRPC client that replaces Python proxy functionality.

**Implementation File:** `server/src/grpc/client.ts`

**Key Features to Implement:**
1. Connection management to Octane on port 51022
2. Dynamic service stub creation (like Python proxy does)
3. Generic request handler (replaces Python's `handle_grpc_request`)
4. Error handling and retry logic
5. Health checking

**Reference Pattern from Python:**
```python
# Python proxy pattern
def handle_grpc_request(service_name, method_name, params):
    # Load service module
    service_module = importlib.import_module(f'generated.{service_name}_pb2_grpc')
    # Create stub
    stub_class = getattr(service_module, f'{service_name}Stub')
    stub = stub_class(channel)
    # Get method
    method = getattr(stub, method_name)
    # Call
    response = method(request)
```

**Your Node.js Equivalent:**
```typescript
// TypeScript Node.js pattern
import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';

class OctaneGrpcClient {
  private client: grpc.Client;
  private services: Map<string, any> = new Map();
  
  async callMethod(serviceName: string, methodName: string, params: any) {
    // Get or create service stub
    const service = this.getService(serviceName);
    // Call method
    return new Promise((resolve, reject) => {
      service[methodName](params, (error: any, response: any) => {
        if (error) reject(error);
        else resolve(response);
      });
    });
  }
  
  // Additional methods...
}
```

**Deliverable for Phase 2.3:**
- Working `server/src/grpc/client.ts` with connection to Octane
- Test script that can make a simple gRPC call (e.g., getPing)
- Error handling and logging

### 2.4 Create Express API Server

**Task:** Build HTTP API that frontend will call.

**Implementation File:** `server/src/index.ts` and `server/src/api/routes.ts`

**Required Endpoints:**
1. `POST /api/grpc/:service/:method` - Generic gRPC call handler
2. `GET /api/health` - Health check
3. `WebSocket /api/callbacks` - Streaming callbacks (like Python callback_streamer)

**Pattern:**
```typescript
import express from 'express';
import cors from 'cors';
import { OctaneGrpcClient } from './grpc/client';

const app = express();
app.use(cors());
app.use(express.json());

const grpcClient = new OctaneGrpcClient();

app.post('/api/grpc/:service/:method', async (req, res) => {
  const { service, method } = req.params;
  const params = req.body;
  
  try {
    const response = await grpcClient.callMethod(service, method, params);
    res.json(response);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// WebSocket setup for callbacks...
```

**Deliverable for Phase 2.4:**
- Working Express server on port 51024 (or configurable)
- Generic gRPC endpoint tested with simple calls
- CORS configured for local development
- WebSocket endpoint created (callback streaming in Phase 4)

---

## 🎨 Phase 3: React Frontend Foundation (BUILD THE UI SHELL)

### 3.1 Create Base React Application

**Task:** Setup React with TypeScript and Vite.

**Files to Create:**
1. `client/index.html` - Port from octaneWeb/index.html
2. `client/src/main.tsx` - React entry point
3. `client/src/App.tsx` - Main application shell

**App.tsx Structure:**
```typescript
import React from 'react';
import { OctaneClientProvider } from './contexts/OctaneClientContext';
import { LayoutManager } from './components/LayoutManager';
import { MenuSystem } from './components/MenuSystem';
import { CallbackRenderViewport } from './components/CallbackRenderViewport';
import { SceneOutliner } from './components/SceneOutliner';
import { NodeInspector } from './components/NodeInspector';
import { NodeGraphEditor } from './components/NodeGraphEditor';

function App() {
  return (
    <OctaneClientProvider>
      <div className="octane-app">
        <MenuSystem />
        <LayoutManager>
          <CallbackRenderViewport />
          <SceneOutliner />
          <NodeInspector />
          <NodeGraphEditor />
        </LayoutManager>
      </div>
    </OctaneClientProvider>
  );
}

export default App;
```

**Deliverable for Phase 3.1:**
- React app running on Vite dev server
- Basic component shells created (empty but rendered)
- Hot module replacement working

### 3.2 Port CSS Styles

**Task:** Migrate the extracted active CSS to React styling system.

**Decision Point:** Choose ONE approach:
- **Option A:** CSS Modules (recommended for direct port)
- **Option B:** Styled-components (if you want TypeScript benefits)
- **Option C:** Plain CSS imports (fastest, least React-native)

**For CSS Modules Approach:**
1. Rename `octane-theme.css` → `theme.module.css`
2. Import in components: `import styles from './styles/theme.module.css'`
3. Use: `<div className={styles.sceneOutliner}>`

**Critical:** Preserve all CSS values exactly (colors, sizes, fonts, spacing)

**Deliverable for Phase 3.2:**
- All CSS ported to chosen system
- Visual appearance matches octaneWeb exactly
- No style regressions

### 3.3 Create OctaneClient Service

**Task:** Port OctaneWebClient.js to TypeScript React service.

**Implementation File:** `client/src/services/OctaneClient.ts`

**Key Responsibilities:**
1. HTTP calls to Node.js backend (`/api/grpc/:service/:method`)
2. State management (scene state, render state, node graph state)
3. Event emission (for React components to subscribe)
4. Error handling and retries

**Pattern:**
```typescript
export class OctaneClient {
  private serverUrl: string;
  private sceneState: SceneState = { objects: new Map(), hierarchy: [] };
  private eventListeners: Map<string, Set<Function>> = new Map();
  
  async makeApiCall(service: string, method: string, params: any = {}) {
    const response = await fetch(
      `${this.serverUrl}/api/grpc/${service}/${method}`,
      {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(params)
      }
    );
    
    if (!response.ok) {
      throw new Error(`API call failed: ${response.statusText}`);
    }
    
    return response.json();
  }
  
  // Port all methods from OctaneWebClient.js...
  async syncScene() { /* ... */ }
  async setCameraPosition(position: Vector3) { /* ... */ }
  // etc.
}
```

**Deliverable for Phase 3.3:**
- OctaneClient class with all methods from OctaneWebClient.js
- TypeScript interfaces for all data types
- Custom hook `useOctaneClient()` for React components
- Test that basic API calls work (e.g., getPing, getSceneInfo)

### 3.4 Create React Context for Global State

**Task:** Setup React Context API for state management.

**Implementation File:** `client/src/contexts/OctaneClientContext.tsx`

**Pattern:**
```typescript
import React, { createContext, useContext, useEffect, useState } from 'react';
import { OctaneClient } from '../services/OctaneClient';

interface OctaneContextType {
  client: OctaneClient;
  sceneState: SceneState;
  renderState: RenderState;
  isConnected: boolean;
}

const OctaneContext = createContext<OctaneContextType | null>(null);

export function OctaneClientProvider({ children }: { children: React.ReactNode }) {
  const [client] = useState(() => new OctaneClient('http://localhost:51024'));
  const [sceneState, setSceneState] = useState<SceneState>({ /* ... */ });
  const [isConnected, setIsConnected] = useState(false);
  
  useEffect(() => {
    // Setup client event listeners
    client.on('sceneStateUpdate', setSceneState);
    client.connect();
    
    return () => client.disconnect();
  }, [client]);
  
  return (
    <OctaneContext.Provider value={{ client, sceneState, isConnected }}>
      {children}
    </OctaneContext.Provider>
  );
}

export function useOctaneClient() {
  const context = useContext(OctaneContext);
  if (!context) throw new Error('useOctaneClient must be used within OctaneClientProvider');
  return context;
}
```

**Deliverable for Phase 3.4:**
- Working Context Provider
- Custom hook for accessing client and state
- Connection lifecycle managed
- Event subscriptions working

---

## 🎯 Phase 4: Component Implementation (PORT EACH FEATURE)

### 4.1 CallbackRenderViewport Component (HIGHEST PRIORITY)

**Task:** Port CallbackRenderViewport.js to React - this is the real-time rendering display.

**Implementation File:** `client/src/components/CallbackRenderViewport.tsx`

**Critical Requirements:**
1. WebGL canvas setup (useRef for canvas element)
2. WebSocket connection for callback streaming
3. HDR/LDR buffer processing (preserve exact algorithm from JS)
4. Texture updates on every frame
5. Mouse drag camera synchronization

**Key Algorithms to Preserve:**
- `convertHDRRGBA()` - Buffer processing for HDR data
- `updateTexture()` - WebGL texture upload
- Mouse event handlers for camera control
- Frame rate limiting

**React Patterns:**
```typescript
export function CallbackRenderViewport() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const { client } = useOctaneClient();
  const [isRendering, setIsRendering] = useState(false);
  
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    // Setup WebGL context
    const gl = canvas.getContext('webgl2');
    // Initialize textures, shaders, etc.
    
    // Setup WebSocket for callbacks
    const ws = new WebSocket('ws://localhost:51024/api/callbacks');
    ws.onmessage = (event) => {
      const frame = JSON.parse(event.data);
      updateTexture(gl, frame.buffer, frame.width, frame.height);
    };
    
    // Setup mouse handlers
    const handleMouseDrag = (e: MouseEvent) => {
      // Camera update logic
      client.setCameraPosition(newPosition);
    };
    
    canvas.addEventListener('mousemove', handleMouseDrag);
    
    return () => {
      ws.close();
      canvas.removeEventListener('mousemove', handleMouseDrag);
    };
  }, [client]);
  
  return <canvas ref={canvasRef} className={styles.renderViewport} />;
}
```

**Testing:**
1. Connect to Octane
2. Start render
3. Verify frames display correctly
4. Test mouse drag camera sync
5. Test HDR/LDR switching

**Deliverable for Phase 4.1:**
- Working CallbackRenderViewport component
- Real-time frames displaying
- Mouse camera control working
- Performance equivalent to octaneWeb

### 4.2 SceneOutliner Component

**Task:** Port SceneOutlinerSync.js to React.

**Implementation File:** `client/src/components/SceneOutliner.tsx`

**Critical Requirements:**
1. Hierarchical tree view (use recursive component pattern)
2. Expand/collapse functionality
3. Node icons (based on node type)
4. Visibility toggles (eye icons)
5. Selection handling
6. Right-click context menu

**React Patterns:**
```typescript
interface TreeNodeProps {
  node: SceneNode;
  depth: number;
}

function TreeNode({ node, depth }: TreeNodeProps) {
  const [isExpanded, setIsExpanded] = useState(false);
  const { client } = useOctaneClient();
  
  const handleToggleVisibility = () => {
    client.setNodeVisibility(node.id, !node.visible);
  };
  
  return (
    <div className={styles.treeNode} style={{ paddingLeft: `${depth * 20}px` }}>
      <button onClick={() => setIsExpanded(!isExpanded)}>
        {node.children.length > 0 && (isExpanded ? '▼' : '▶')}
      </button>
      <img src={getNodeIcon(node.type)} alt="" />
      <span>{node.name}</span>
      <button onClick={handleToggleVisibility}>
        {node.visible ? '👁' : '👁‍🗨'}
      </button>
      
      {isExpanded && node.children.map(child => (
        <TreeNode key={child.id} node={child} depth={depth + 1} />
      ))}
    </div>
  );
}

export function SceneOutliner() {
  const { sceneState } = useOctaneClient();
  
  return (
    <div className={styles.sceneOutliner}>
      {sceneState.hierarchy.map(node => (
        <TreeNode key={node.id} node={node} depth={0} />
      ))}
    </div>
  );
}
```

**Deliverable for Phase 4.2:**
- Working SceneOutliner with hierarchical tree
- Expand/collapse working
- Visibility toggles working
- Visual appearance matches octaneWeb exactly

### 4.3 NodeInspector Component

**Task:** Port NodeInspector.js to React.

**Implementation File:** `client/src/components/NodeInspector.tsx`

**Critical Requirements:**
1. Display properties of selected node
2. Editable controls (text inputs, sliders, checkboxes, dropdowns)
3. Real-time updates to Octane on value change
4. Type-specific rendering (use GenericNodeRenderer.js as reference)
5. Collapsible sections

**React Patterns:**
```typescript
function PropertyControl({ property }: { property: NodeProperty }) {
  const { client } = useOctaneClient();
  const [value, setValue] = useState(property.value);
  
  const handleChange = (newValue: any) => {
    setValue(newValue);
    client.setNodeProperty(property.nodeId, property.name, newValue);
  };
  
  // Render different control types based on property.type
  switch (property.type) {
    case 'float':
      return <input type="number" value={value} onChange={e => handleChange(parseFloat(e.target.value))} />;
    case 'bool':
      return <input type="checkbox" checked={value} onChange={e => handleChange(e.target.checked)} />;
    case 'enum':
      return <select value={value} onChange={e => handleChange(e.target.value)}>
        {property.options.map(opt => <option key={opt}>{opt}</option>)}
      </select>;
    // ... more types
  }
}

export function NodeInspector() {
  const { sceneState } = useOctaneClient();
  const selectedNode = sceneState.selection[0]; // First selected node
  
  if (!selectedNode) {
    return <div className={styles.nodeInspector}>No selection</div>;
  }
  
  return (
    <div className={styles.nodeInspector}>
      <h3>{selectedNode.name}</h3>
      {selectedNode.properties.map(prop => (
        <PropertyControl key={prop.name} property={prop} />
      ))}
    </div>
  );
}
```

**Deliverable for Phase 4.3:**
- Working NodeInspector with all control types
- Real-time property updates to Octane
- Visual appearance matches octaneWeb exactly

### 4.4 NodeGraphEditor Component

**Task:** Port NodeGraphEditor.js to React.

**Implementation File:** `client/src/components/NodeGraphEditor.tsx`

**Critical Requirements:**
1. Visual node graph display
2. Node creation (right-click context menu)
3. Node connections (drag between ports)
4. Node positioning and dragging
5. Selection and deletion

**Consider Using:** React Flow library (https://reactflow.dev/) - it handles 90% of this

**If using React Flow:**
```typescript
import ReactFlow, { Node, Edge } from 'reactflow';
import 'reactflow/dist/style.css';

export function NodeGraphEditor() {
  const { client, sceneState } = useOctaneClient();
  const [nodes, setNodes] = useState<Node[]>([]);
  const [edges, setEdges] = useState<Edge[]>([]);
  
  // Convert Octane node graph to React Flow format
  useEffect(() => {
    const flowNodes = sceneState.nodeGraph.nodes.map(node => ({
      id: node.id,
      type: node.type,
      position: { x: node.x, y: node.y },
      data: { label: node.name }
    }));
    setNodes(flowNodes);
    
    const flowEdges = sceneState.nodeGraph.connections.map(conn => ({
      id: `${conn.from}-${conn.to}`,
      source: conn.from,
      target: conn.to
    }));
    setEdges(flowEdges);
  }, [sceneState.nodeGraph]);
  
  const handleNodeDrag = (event: any, node: Node) => {
    client.setNodePosition(node.id, node.position.x, node.position.y);
  };
  
  return (
    <ReactFlow
      nodes={nodes}
      edges={edges}
      onNodeDrag={handleNodeDrag}
    />
  );
}
```

**Deliverable for Phase 4.4:**
- Working NodeGraphEditor with visual graph
- Node creation and deletion
- Connection editing
- Matches octaneWeb appearance and functionality

### 4.5 RenderToolbar Component

**Task:** Port RenderToolbar.js to React.

**Implementation File:** `client/src/components/RenderToolbar.tsx`

**Critical Requirements:**
1. Render control buttons (Start, Stop, Pause, Restart)
2. Real-time render toggle
3. Reset camera button
4. Status indicators (FPS, samples, render time)

**React Pattern:**
```typescript
export function RenderToolbar() {
  const { client, renderState } = useOctaneClient();
  
  return (
    <div className={styles.renderToolbar}>
      <button onClick={() => client.startRender()}>▶ Start</button>
      <button onClick={() => client.stopRender()}>■ Stop</button>
      <button onClick={() => client.pauseRender()}>⏸ Pause</button>
      <button onClick={() => client.restartRender()}>↻ Restart</button>
      <button onClick={() => client.resetCamera()}>⌂ Reset Camera</button>
      
      <div className={styles.renderStatus}>
        <span>FPS: {renderState.fps}</span>
        <span>Samples: {renderState.samples}</span>
        <span>Time: {renderState.time}s</span>
      </div>
    </div>
  );
}
```

**Deliverable for Phase 4.5:**
- Working RenderToolbar with all controls
- Status display updating in real-time
- All buttons calling correct gRPC methods

### 4.6 MenuSystem Component

**Task:** Port MenuSystem.js to React.

**Implementation File:** `client/src/components/MenuSystem.tsx`

**Critical Requirements:**
1. Top menu bar (File, Edit, View, Help)
2. Dropdown menus on hover/click
3. Menu actions (Open Scene, Save, Export, etc.)
4. Keyboard shortcuts

**Deliverable for Phase 4.6:**
- Working MenuSystem matching octaneWeb
- All menu actions implemented
- Keyboard shortcuts working

### 4.7 LayoutManager Component

**Task:** Port LayoutManager.js to React - manages panel layouts.

**Implementation File:** `client/src/components/LayoutManager.tsx`

**Consider Using:** react-resizable-panels or react-grid-layout

**Critical Requirements:**
1. Resizable panels
2. Drag-and-drop panel rearrangement
3. Save/restore layout preferences
4. Responsive behavior

**Deliverable for Phase 4.7:**
- Working LayoutManager with resizable panels
- Layout persistence
- Matches octaneWeb layout system

---

## 🔄 Phase 5: Callback Streaming (REAL-TIME UPDATES)

### 5.1 Implement WebSocket Callback System

**Task:** Port callback_streamer.py functionality to Node.js WebSocket.

**Implementation File:** `server/src/api/websocket.ts`

**Critical Requirements:**
1. WebSocket server on Node.js backend
2. Register callback with Octane gRPC (OnNewImage, OnRenderProgress, etc.)
3. Stream callback data to connected clients
4. Handle multiple clients
5. Cleanup on disconnect

**Node.js Pattern:**
```typescript
import { WebSocketServer } from 'ws';
import { Server } from 'http';

export function setupCallbackStreaming(server: Server, grpcClient: OctaneGrpcClient) {
  const wss = new WebSocketServer({ server, path: '/api/callbacks' });
  
  wss.on('connection', (ws) => {
    console.log('Client connected for callbacks');
    
    // Register callback with Octane
    const callbackId = await grpcClient.registerCallback('OnNewImage', (frame) => {
      // Forward frame to WebSocket client
      ws.send(JSON.stringify({
        type: 'newImage',
        data: frame
      }));
    });
    
    ws.on('close', () => {
      console.log('Client disconnected');
      grpcClient.unregisterCallback(callbackId);
    });
  });
}
```

**Deliverable for Phase 5.1:**
- Working WebSocket server
- Callback registration with Octane
- Frame streaming to clients
- Cleanup on disconnect

### 5.2 Connect Frontend to WebSocket

**Task:** Create React hook for callback streaming.

**Implementation File:** `client/src/hooks/useCallbackStream.ts`

**Pattern:**
```typescript
export function useCallbackStream() {
  const [lastFrame, setLastFrame] = useState<RenderFrame | null>(null);
  const wsRef = useRef<WebSocket | null>(null);
  
  useEffect(() => {
    const ws = new WebSocket('ws://localhost:51024/api/callbacks');
    
    ws.onmessage = (event) => {
      const message = JSON.parse(event.data);
      if (message.type === 'newImage') {
        setLastFrame(message.data);
      }
    };
    
    ws.onerror = (error) => {
      console.error('WebSocket error:', error);
    };
    
    wsRef.current = ws;
    
    return () => {
      ws.close();
    };
  }, []);
  
  return lastFrame;
}
```

**Usage in CallbackRenderViewport:**
```typescript
export function CallbackRenderViewport() {
  const lastFrame = useCallbackStream();
  
  useEffect(() => {
    if (lastFrame) {
      updateTexture(gl, lastFrame.buffer, lastFrame.width, lastFrame.height);
    }
  }, [lastFrame]);
  
  // ... rest of component
}
```

**Deliverable for Phase 5.2:**
- Custom hook for callback streaming
- Integration with CallbackRenderViewport
- Real-time frame updates working
- Error handling and reconnection

---

## ✅ Phase 6: Testing & Validation (ENSURE QUALITY)

### 6.1 Visual Appearance Testing

**Task:** Compare octaneWebR to octaneWeb side-by-side.

**Checklist:**
- [ ] Same color scheme and branding
- [ ] Same fonts and font sizes
- [ ] Same panel layouts and spacing
- [ ] Same icon styles
- [ ] Same button styles
- [ ] Same control sizes and alignment
- [ ] Same status indicators
- [ ] Same debug console appearance

**Method:** Screenshot comparison and pixel-level diff if possible.

### 6.2 Functional Testing

**Task:** Test every feature against octaneWeb.

**Checklist:**
- [ ] Scene loading and synchronization
- [ ] Scene Outliner tree expansion/collapse
- [ ] Node selection and highlighting
- [ ] Visibility toggles
- [ ] Node Inspector property editing
- [ ] Real-time property updates to Octane
- [ ] Node Graph Editor node creation
- [ ] Node connections and editing
- [ ] Render controls (Start, Stop, Pause, Restart)
- [ ] Real-time rendering frame display
- [ ] Mouse drag camera synchronization
- [ ] Camera reset
- [ ] Menu actions
- [ ] Keyboard shortcuts
- [ ] Layout resizing and rearrangement
- [ ] Debug console toggle

### 6.3 Performance Testing

**Task:** Ensure octaneWebR performs as well as octaneWeb.

**Metrics:**
- Frame rate during rendering (should be 30+ FPS)
- Scene synchronization time (< 1 second for typical scenes)
- Memory usage (similar to octaneWeb)
- CPU usage (similar to octaneWeb)
- Network latency (should be lower without Python proxy)

### 6.4 Error Handling Testing

**Task:** Test error scenarios.

**Scenarios:**
- Octane not running
- Octane LiveLink disabled
- Network disconnection during render
- Invalid property values
- Large scene loading
- Rapid user interactions

---

## 📦 Phase 7: Documentation & Deployment (FINISH STRONG)

### 7.1 Create Documentation

**Files to Create:**

1. **README.md** - Main documentation
   - Project overview
   - Architecture diagram
   - Setup instructions
   - Usage guide
   - Troubleshooting

2. **SETUP.md** - Detailed setup guide
   - Prerequisites
   - Installation steps
   - Configuration
   - First run

3. **DEVELOPMENT.md** - Development guide
   - Project structure
   - Code organization
   - Adding new features
   - Debugging tips

4. **API.md** - API documentation
   - gRPC methods used
   - REST API endpoints
   - WebSocket protocol

### 7.2 Create Startup Scripts

**Files to Create:**

1. **start-dev.sh** / **start-dev.bat**
   ```bash
   #!/bin/bash
   # Start both client and server in development mode
   npm run server:dev & npm run client:dev
   ```

2. **start-prod.sh** / **start-prod.bat**
   ```bash
   #!/bin/bash
   # Build and start in production mode
   npm run build
   npm run start
   ```

3. **package.json scripts:**
   ```json
   {
     "scripts": {
       "client:dev": "vite",
       "server:dev": "nodemon server/src/index.ts",
       "dev": "concurrently \"npm:client:dev\" \"npm:server:dev\"",
       "build:client": "vite build",
       "build:server": "tsc -p server",
       "build": "npm run build:client && npm run build:server",
       "start": "node server/dist/index.js"
     }
   }
   ```

### 7.3 Create Configuration Files

**Files to Create:**

1. **.env.example**
   ```
   OCTANE_HOST=localhost
   OCTANE_PORT=51022
   SERVER_PORT=51024
   CLIENT_PORT=5173
   ```

2. **.gitignore**
   ```
   node_modules/
   dist/
   build/
   .env
   *.log
   .DS_Store
   ```

### 7.4 Final Validation

**Checklist:**
- [ ] Clean clone and install works
- [ ] Both dev and prod modes work
- [ ] All dependencies documented
- [ ] All configuration options documented
- [ ] Troubleshooting guide complete
- [ ] Code comments sufficient
- [ ] No console errors or warnings
- [ ] All features working
- [ ] Visual appearance matches octaneWeb exactly

---

## 🎯 Success Criteria

Your port is successful when:

1. **Visual Fidelity:** octaneWebR looks identical to octaneWeb
2. **Functional Parity:** All features work exactly the same way
3. **Performance:** Equivalent or better performance
4. **Code Quality:** Clean, maintainable TypeScript code
5. **Documentation:** Complete setup and usage documentation
6. **Testing:** All features tested and validated
7. **Deployment:** Easy to install and run

---

## 🚨 Critical Reminders

### What You MUST Preserve Exactly:
- **CSS styles and visual appearance** - pixel-perfect match
- **User interaction patterns** - same clicks, drags, hovers
- **Algorithm implementations** - especially HDR buffer processing, camera math
- **gRPC call patterns** - same services, methods, parameters
- **State management patterns** - same data flow and updates

### What You CAN Change:
- **Implementation technology** - JS → TypeScript, Python → Node.js
- **Component structure** - vanilla DOM → React components
- **Code organization** - as long as functionality is preserved
- **Developer experience** - better debugging, type safety

### What You MUST NOT Do:
- **Don't redesign the UI** - port it exactly
- **Don't skip features** - everything must be implemented
- **Don't assume** - when in doubt, match the original exactly
- **Don't optimize prematurely** - get it working first, then optimize

---

## 📞 Asking for Help

When you encounter issues:

1. **Reference the original code** - octaneWeb is your specification
2. **Test incrementally** - don't build everything before testing
3. **Document blockers** - clearly state what's blocking progress
4. **Propose solutions** - suggest approaches before asking for decisions

---

## 🎓 Additional Resources

### Key Files to Reference Constantly:
- `octaneWeb/js/core/OctaneWebClient.js` - Your API reference
- `octaneWeb/js/components/CallbackRenderViewport.js` - Critical rendering logic
- `octaneWeb/css/octane-theme.css` - Visual specification
- `octaneProxy/octane_proxy.py` - gRPC pattern reference
- `octaneProxy/callback_streamer.py` - Callback system reference

### Technology Documentation:
- React: https://react.dev/
- TypeScript: https://www.typescriptlang.org/docs/
- Vite: https://vitejs.dev/guide/
- @grpc/grpc-js: https://grpc.github.io/grpc/node/
- React Flow (for node graph): https://reactflow.dev/

---

## 📅 Estimated Timeline

- **Phase 1 (Analysis):** 1-2 days
- **Phase 2 (Infrastructure):** 2-3 days
- **Phase 3 (React Foundation):** 2-3 days
- **Phase 4 (Components):** 5-7 days
- **Phase 5 (Callbacks):** 1-2 days
- **Phase 6 (Testing):** 2-3 days
- **Phase 7 (Documentation):** 1 day

**Total: 14-21 days** for a faithful, high-quality port

---

## 🎯 Final Notes

This is a **translation project**, not a greenfield project. You have a working reference implementation (octaneWeb) that defines the specification. Your job is to faithfully reproduce it in modern React TypeScript while improving the backend architecture with direct Node.js gRPC.

**Success = octaneWebR looks, feels, and works exactly like octaneWeb, but with better technology under the hood.**

**When in doubt, match the original exactly. Quality over speed. Completeness over cleverness.**

Good luck! 🚀
