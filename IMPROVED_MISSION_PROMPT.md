# Improved Mission Prompt for OctaneWebR Port

## Original User Request
The user requested help improving a prompt for porting octaneWeb (vanilla JavaScript) to octaneWebR (React + TypeScript with direct Node.js gRPC).

## Analysis of Original Prompt

### Strengths
1. Clear goal: port octaneWeb to React TypeScript with direct gRPC
2. Identified key requirements: UI must match exactly, all functionality must be preserved
3. Mentioned important files to examine (NodeInspector.js, GenericNodeRenderer.js, SceneOutlinerSync.js)
4. Specified architecture: React TypeScript UI + Node.js gRPC backend

### Weaknesses
1. **Vague about specifics**: "examine carefully" without concrete deliverables
2. **No clear phases**: Presented as one big task rather than structured phases
3. **Missing technical details**: No mention of build tools, state management, or specific React patterns
4. **Unclear about CSS strategy**: Mentioned CSS but not how to organize it in React
5. **No success criteria**: What does "done" look like?
6. **Over-emphasis on autonomy**: "minimum of interaction" can lead to wrong assumptions

## Improved Mission Prompt

---

# Mission: Port octaneWeb to octaneWebR (React + TypeScript + Direct gRPC)

## Executive Summary
Port the working octaneWeb project from vanilla JavaScript to a modern React TypeScript application (octaneWebR) with **direct Node.js gRPC communication** to Octane (no Python proxy). The UI must **pixel-perfectly match** octaneWeb, and all functionality must be preserved.

## Success Criteria
✅ **Architecture**: Browser → Node.js Backend (Express) → Octane gRPC (direct via @grpc/grpc-js)  
✅ **UI Match**: All panels, controls, layouts match octaneWeb screenshot exactly  
✅ **Functionality**: Scene sync, node inspection, viewport rendering, node graph editing all working  
✅ **No Python**: Eliminate Python proxy dependency entirely  
✅ **Production Ready**: Clean code, proper error handling, documented APIs

## Phase 1: Repository Analysis (30 minutes)

### 1.1 Examine octaneWeb Structure
- [ ] Map out `/workspace/grpcSamples/octaneWeb/` directory structure
- [ ] Identify all JavaScript modules and their dependencies
- [ ] Document the current architecture: `octaneWeb → Python Proxy → Octane gRPC`
- [ ] List all API calls made to the proxy (check `OctaneWebClient.js`)

### 1.2 Analyze CSS and Styling
- [ ] Review `/workspace/grpcSamples/octaneWeb/css/` files:
  - `octane-theme.css` - color scheme, fonts, variables
  - `layout.css` - grid layouts, panel sizing, responsive design
  - `components.css` - component-specific styles
- [ ] Identify which CSS classes are actually used (many are unused)
- [ ] Note the DOM structure in `index.html` for the 4-panel layout

### 1.3 Study Key Components
Focus on these files for programmatic DOM creation patterns:
- `NodeInspector.js` - property panel with parameter controls
- `GenericNodeRenderer.js` - node graph rendering
- `SceneOutlinerSync.js` - tree view with expand/collapse

### 1.4 Understand gRPC Communication
- [ ] Review `/workspace/grpcSamples/sdk/src/api/grpc/protodef/*.proto` files
- [ ] Document what `OctaneProxy` does (special case handling for gRPC requests)
- [ ] List all gRPC services used: `LiveLink`, `GraphServer`, etc.
- [ ] Understand the `makeApiCall()` function in `OctaneWebClient.js`

**Deliverable**: Create `ANALYSIS.md` with findings before proceeding.

## Phase 2: Project Setup (45 minutes)

### 2.1 Create octaneWebR Project Structure
```bash
mkdir -p /workspace/grpcSamples/octaneWebR
cd /workspace/grpcSamples/octaneWebR

# Initialize with Vite + React + TypeScript
npm create vite@latest . -- --template react-ts

# Install dependencies
npm install zustand axios @types/node

# Backend dependencies
npm install express cors @grpc/grpc-js @grpc/proto-loader
npm install --save-dev @types/express @types/cors tsx ts-node nodemon concurrently
```

### 2.2 Set Up Directory Structure
```
octaneWebR/
├── src/
│   ├── components/
│   │   ├── layout/          # MenuBar, StatusBar, MainLayout
│   │   └── panels/          # SceneOutliner, RenderViewport, NodeInspector, NodeGraphEditor
│   ├── api/                 # octaneClient.ts (REST wrapper for backend)
│   ├── store/               # sceneStore.ts (Zustand state management)
│   ├── types/               # TypeScript interfaces
│   ├── styles/css/          # Copied CSS from octaneWeb
│   ├── App.tsx
│   └── main.tsx
├── server/
│   └── octaneGrpcServer.ts  # Node.js gRPC backend
├── package.json
├── vite.config.ts
├── tsconfig.json
└── README.md
```

### 2.3 Configure Build Tools
- [ ] Update `vite.config.ts` to proxy `/api` to backend (port 45042)
- [ ] Configure `tsconfig.json` for Node.js compatibility
- [ ] Add `package.json` scripts:
  ```json
  {
    "scripts": {
      "dev": "concurrently \"npm run dev:backend\" \"npm run dev:frontend\"",
      "dev:backend": "tsx server/octaneGrpcServer.ts",
      "dev:frontend": "vite",
      "build": "tsc && vite build"
    }
  }
  ```

**Deliverable**: Runnable project skeleton with `npm run dev`.

## Phase 3: Backend Implementation (2 hours)

### 3.1 Create gRPC Backend (`server/octaneGrpcServer.ts`)
```typescript
import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';
import express from 'express';
import cors from 'cors';
import { fileURLToPath } from 'url';
import path from 'path';

const OCTANE_ADDRESS = '127.0.0.1:51022'; // Direct to Octane
const PROTO_DIR = path.join(__dirname, '../../sdk/src/api/grpc/protodef');

// Load ALL proto files dynamically
// Create separate gRPC clients for LiveLink, GraphServer, etc.
// Expose REST API: POST /api/rpc/:service/:method
// Health check: GET /api/health
```

### 3.2 Key Backend Features
- [ ] Dynamic proto loading from SDK directory
- [ ] Multi-service gRPC client architecture
- [ ] Generic REST endpoint routing: `/:service/:method` → gRPC service
- [ ] Proper error handling and logging
- [ ] CORS enabled for frontend requests

### 3.3 Test Backend Independently
```bash
# Start backend
npm run dev:backend

# Test health check
curl http://localhost:45042/api/health

# Test gRPC call
curl -X POST http://localhost:45042/api/rpc/LiveLink/GetCamera \
  -H "Content-Type: application/json" \
  -d '{}'
```

**Deliverable**: Working backend that connects to Octane at `127.0.0.1:51022`.

## Phase 4: Frontend Core (2 hours)

### 4.1 State Management (`src/store/sceneStore.ts`)
```typescript
import { create } from 'zustand';

interface SceneNode {
  id: string;
  name: string;
  type: string;
  children?: SceneNode[];
  visible: boolean;
  expanded: boolean;
}

interface SceneStore {
  connected: boolean;
  sceneTree: SceneNode[];
  selectedNode: SceneNode | null;
  
  setConnected: (connected: boolean) => void;
  loadScene: () => Promise<void>;
  selectNode: (node: SceneNode) => void;
  toggleNodeVisibility: (nodeId: string) => void;
  toggleNodeExpanded: (nodeId: string) => void;
}

export const useSceneStore = create<SceneStore>((set, get) => ({
  // Implementation here
}));
```

### 4.2 API Client (`src/api/octaneClient.ts`)
```typescript
import axios from 'axios';

const API_BASE = '/api'; // Proxied by Vite to backend

class OctaneClient {
  async checkHealth(): Promise<boolean> {
    try {
      const response = await axios.get(`${API_BASE}/health`);
      return response.data.status === 'connected';
    } catch (error) {
      return false;
    }
  }

  async makeApiCall(service: string, method: string, params: any): Promise<any> {
    const response = await axios.post(`${API_BASE}/rpc/${service}/${method}`, params);
    return response.data;
  }

  async syncScene(): Promise<any> {
    // Port the logic from octaneWeb/js/core/OctaneWebClient.js syncScene()
    // 1. Get camera
    // 2. Build scene tree
    // 3. Get meshes
    // etc.
  }
}

export const octaneClient = new OctaneClient();
```

### 4.3 Copy and Organize CSS
```bash
# Copy CSS from octaneWeb
cp -r /workspace/grpcSamples/octaneWeb/css/* /workspace/grpcSamples/octaneWebR/src/styles/css/

# Import in App.tsx
import './styles/css/octane-theme.css';
import './styles/css/layout.css';
import './styles/css/components.css';
```

**Important CSS Notes**:
- `octane-theme.css` defines CSS variables (colors, fonts, sizes)
- `layout.css` defines grid layouts and panel structure
- `components.css` has component-specific styles
- Add base styles for `html`, `body`, `#root`, `.app-container`, `.main-content`

**Deliverable**: State management and API client ready, CSS imported.

## Phase 5: UI Components (4 hours)

### 5.1 Main Layout (`src/components/layout/MainLayout.tsx`)
```typescript
import { useSceneStore } from '../../store/sceneStore';
import MenuBar from './MenuBar';
import SceneOutliner from '../panels/SceneOutliner';
import RenderViewport from '../panels/RenderViewport';
import NodeInspector from '../panels/NodeInspector';
import NodeGraphEditor from '../panels/NodeGraphEditor';
import StatusBar from './StatusBar';

export const MainLayout: React.FC = () => {
  const { connected, setConnected, loadScene } = useSceneStore();

  // Auto-connect on mount
  useEffect(() => {
    handleConnect();
  }, []);

  return (
    <div className="app-container">
      <MenuBar connected={connected} onConnect={handleConnect} onDisconnect={handleDisconnect} />
      
      <main className="main-content">
        <aside className="scene-outliner">
          <SceneOutliner connected={connected} />
        </aside>

        <section className="center-panels">
          <div className="render-viewport">
            <RenderViewport connected={connected} />
          </div>
          
          <div className="node-graph-editor">
            <NodeGraphEditor connected={connected} />
          </div>
        </section>

        <aside className="node-inspector">
          <NodeInspector connected={connected} />
        </aside>
      </main>

      <StatusBar connected={connected} />
    </div>
  );
};
```

### 5.2 Menu Bar (`src/components/layout/MenuBar.tsx`)
- File, Edit, Script, Module, Cloud, Window, Help menu items
- Connection status LED (yellow=ready, green=connected, red=error)
- Server address input (disabled, shows "Node.js Direct gRPC")
- Connect/disconnect toggle switch

### 5.3 Scene Outliner (`src/components/panels/SceneOutliner.tsx`)
Study `SceneOutlinerSync.js` for the tree view logic:
- Recursive tree component with expand/collapse
- Scene/Link/Local tabs
- Search box (filter scene tree)
- Refresh button
- Visibility toggle per node (eye icon)
- Node selection (highlights in blue)
- Node icons based on type (camera, mesh, light, etc.)

### 5.4 Render Viewport (`src/components/panels/RenderViewport.tsx`)
- Canvas element for WebGL rendering
- Panel header with title
- Placeholder message when disconnected
- Future: Callback streaming for real-time renders

### 5.5 Node Inspector (`src/components/panels/NodeInspector.tsx`)
Study `NodeInspector.js` and `GenericNodeRenderer.js`:
- Display properties of selected node
- Parameter groups (collapsible sections)
- Input controls: text, number, color, dropdown, slider
- Property grid layout (label on left, control on right)
- Placeholder when no node selected

### 5.6 Node Graph Editor (`src/components/panels/NodeGraphEditor.tsx`)
Study `GenericNodeRenderer.js`:
- Canvas for node graph visualization
- Zoom/pan controls (+, -, fit)
- Placeholder message when disconnected
- Future: Node creation, connection editing

### 5.7 Status Bar (`src/components/layout/StatusBar.tsx`)
- Left: Status message ("Ready", "Connecting...", "Connected")
- Center: "OctaneWebR - Direct gRPC (No Proxy)"
- Right: "Octane: Connected/Disconnected"

**Deliverable**: All UI components implemented and styled to match octaneWeb.

## Phase 6: Integration and Testing (2 hours)

### 6.1 Verify UI Match
Compare side-by-side with octaneWeb:
- [ ] Layout proportions match (300px left, flex center, 320px right)
- [ ] Colors match (dark theme, orange accents)
- [ ] Fonts and sizing match
- [ ] Spacing and padding match
- [ ] All panels, buttons, controls visible

### 6.2 Test Connection Flow
- [ ] Start Octane and enable LiveLink (Help → LiveLink)
- [ ] Start octaneWebR: `npm run dev`
- [ ] Verify auto-connect on page load
- [ ] Check backend health: `curl http://localhost:45042/api/health`
- [ ] Verify scene loads in Scene Outliner
- [ ] Test node selection → Node Inspector updates

### 6.3 Test Each Component
- [ ] Scene Outliner: expand/collapse, search, visibility toggle
- [ ] Render Viewport: displays message when disconnected
- [ ] Node Inspector: shows properties of selected node
- [ ] Node Graph Editor: placeholder visible
- [ ] Status Bar: shows correct connection status

### 6.4 Error Handling
- [ ] Octane not running: graceful error message
- [ ] Network timeout: retry logic
- [ ] Invalid gRPC response: error logging
- [ ] Frontend displays user-friendly errors

**Deliverable**: Working application with all components functional.

## Phase 7: Documentation (1 hour)

### 7.1 Create README.md
```markdown
# OctaneWebR - React + TypeScript Port

## Architecture
Browser → Node.js Backend (port 45042) → Octane gRPC (127.0.0.1:51022)

**No Python proxy required!**

## Quick Start
1. Start Octane and enable LiveLink (Help → LiveLink)
2. Run: `npm run dev`
3. Open: http://localhost:44479

## Project Structure
- `src/` - React TypeScript frontend
- `server/` - Node.js gRPC backend
- `src/styles/css/` - Copied from octaneWeb

## API Endpoints
- `GET /api/health` - Check Octane connection
- `POST /api/rpc/:service/:method` - Generic gRPC call

## State Management
Uses Zustand for global state (scene tree, selection, connection status).

## Development
- `npm run dev` - Start both backend and frontend
- `npm run dev:backend` - Backend only
- `npm run dev:frontend` - Frontend only
- `npm run build` - Production build
```

### 7.2 Create MIGRATION_NOTES.md
Document differences from octaneWeb:
- Architecture changes (Python proxy → Node.js)
- State management (global vars → Zustand)
- DOM manipulation (programmatic → React components)
- CSS organization (inline → imported)
- API calls (direct fetch → axios + REST wrapper)

**Deliverable**: Complete documentation for future developers.

## Key Differences from Original Prompt

### What We Changed
1. **Structured Phases**: Clear progression from analysis → setup → backend → frontend → testing
2. **Concrete Deliverables**: Each phase has specific "done" criteria
3. **Technical Specificity**: Exact package names, file structures, code snippets
4. **CSS Strategy**: Explicit instructions to copy CSS and add base styles
5. **Architecture Clarity**: Exact ports, endpoints, and data flow
6. **Testing Protocol**: Step-by-step verification process
7. **Interaction Expectations**: Regular check-ins after each phase

### What We Kept
1. Goal: Faithful port of octaneWeb functionality
2. UI must match exactly
3. Direct gRPC (no Python proxy)
4. Study key files (NodeInspector.js, GenericNodeRenderer.js, SceneOutlinerSync.js)

## Common Pitfalls to Avoid

### 1. CSS Issues
❌ **Wrong**: Assume React will magically style components  
✅ **Right**: Copy all CSS from octaneWeb, import in App.tsx, add base styles for html/body/#root

### 2. State Management
❌ **Wrong**: Use local useState in every component  
✅ **Right**: Centralize in Zustand store for scene tree, selection, connection status

### 3. API Architecture
❌ **Wrong**: Try to use gRPC-web directly in browser  
✅ **Right**: Node.js backend with @grpc/grpc-js, REST wrapper for frontend

### 4. Proto Loading
❌ **Wrong**: Manually write TypeScript definitions for 95 proto files  
✅ **Right**: Use @grpc/proto-loader for dynamic loading

### 5. Layout Structure
❌ **Wrong**: Use random div nesting  
✅ **Right**: Match octaneWeb structure: `.app-container` → `.main-content` → panels

## Conclusion

This improved prompt provides:
- ✅ **Clear phases** with time estimates
- ✅ **Concrete deliverables** for each phase
- ✅ **Technical specificity** (packages, ports, file structures)
- ✅ **Success criteria** (what "done" looks like)
- ✅ **Common pitfalls** to avoid
- ✅ **Testing protocol** to verify UI match

By following this prompt, an engineer can successfully port octaneWeb to octaneWebR in approximately **12 hours** with minimal back-and-forth communication.
