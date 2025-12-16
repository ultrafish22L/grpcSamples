# OctaneWebR Quick Reference Guide

## 🎯 One-Page Cheat Sheet for Engineers

### Project Goal
Port octaneWeb (vanilla JS + Python proxy) → octaneWebR (React TypeScript + Node.js gRPC)  
**Rule:** Match octaneWeb EXACTLY. This is a port, not a redesign.

---

## 📂 Key Source Files to Study

### Frontend Logic (octaneWeb/js/)
```
core/OctaneWebClient.js         ← Main API client - YOUR BLUEPRINT
core/EventSystem.js              ← Event bus pattern
core/StateManager.js             ← State management

components/CallbackRenderViewport.js  ← Real-time rendering (CRITICAL)
components/SceneOutlinerSync.js       ← Tree view with DOM creation
components/NodeInspector.js           ← Property editor with DOM creation
components/NodeGraphEditor.js         ← Visual node graph

utils/GenericNodeRenderer.js          ← Reusable control builders
utils/Camera.js                       ← Camera math
```

### Backend Logic (octaneProxy/)
```
octane_proxy.py                  ← HTTP → gRPC translation (YOUR PATTERN)
callback_streamer.py             ← Real-time streaming callbacks
```

### Styling (octaneWeb/css/)
```
octane-theme.css                 ← Main OTOY theme
components.css                   ← Component styles
layout.css                       ← Panel layouts
```

---

## 🏗️ Architecture Translation

### Current (octaneWeb)
```
Browser (Vanilla JS) → HTTP/JSON → Python Proxy → gRPC → Octane (51022)
                     ← JSON      ←              ← gRPC ←
```

### Target (octaneWebR)
```
Browser (React TS) → HTTP/JSON → Node.js Server → gRPC → Octane (51022)
                   ← JSON/WS   ←                ← gRPC ←
```

---

## 🔑 Critical Code Patterns

### 1. Python gRPC Call → Node.js Equivalent

**Python (octane_proxy.py):**
```python
# Dynamic service loading
service_module = importlib.import_module(f'generated.{service_name}_pb2_grpc')
stub_class = getattr(service_module, f'{service_name}Stub')
stub = stub_class(channel)
method = getattr(stub, method_name)
response = method(request)
```

**Node.js (your server/src/grpc/client.ts):**
```typescript
import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';

class OctaneGrpcClient {
  private services: Map<string, any> = new Map();
  
  async callMethod(service: string, method: string, params: any) {
    const svc = this.getOrCreateService(service);
    return new Promise((resolve, reject) => {
      svc[method](params, (err: any, response: any) => {
        if (err) reject(err);
        else resolve(response);
      });
    });
  }
}
```

### 2. Vanilla JS Component → React Component

**Vanilla JS (SceneOutlinerSync.js):**
```javascript
class SceneOutlinerSync {
  constructor(container, eventSystem, client) {
    this.container = container;
    this.eventSystem = eventSystem;
    this.client = client;
    this.render();
  }
  
  render() {
    this.container.innerHTML = '';
    const tree = this.buildTree(this.sceneData);
    this.container.appendChild(tree);
  }
  
  buildTree(nodes) {
    const ul = document.createElement('ul');
    nodes.forEach(node => {
      const li = document.createElement('li');
      li.textContent = node.name;
      li.addEventListener('click', () => this.selectNode(node));
      ul.appendChild(li);
    });
    return ul;
  }
}
```

**React (SceneOutliner.tsx):**
```typescript
interface SceneOutlinerProps {}

export function SceneOutliner() {
  const { sceneState, client } = useOctaneClient();
  
  const handleSelectNode = (node: SceneNode) => {
    client.selectNode(node.id);
  };
  
  return (
    <div className={styles.sceneOutliner}>
      <TreeView
        nodes={sceneState.hierarchy}
        onSelect={handleSelectNode}
      />
    </div>
  );
}

function TreeView({ nodes, onSelect }) {
  return (
    <ul>
      {nodes.map(node => (
        <li key={node.id} onClick={() => onSelect(node)}>
          {node.name}
          {node.children && <TreeView nodes={node.children} onSelect={onSelect} />}
        </li>
      ))}
    </ul>
  );
}
```

### 3. Event System → React Context

**Vanilla JS (EventSystem.js):**
```javascript
class EventSystem {
  constructor() {
    this.listeners = new Map();
  }
  
  on(event, callback) {
    if (!this.listeners.has(event)) {
      this.listeners.set(event, new Set());
    }
    this.listeners.get(event).add(callback);
  }
  
  emit(event, data) {
    if (this.listeners.has(event)) {
      this.listeners.get(event).forEach(cb => cb(data));
    }
  }
}
```

**React (OctaneClientContext.tsx):**
```typescript
const OctaneContext = createContext<OctaneContextType | null>(null);

export function OctaneClientProvider({ children }) {
  const [sceneState, setSceneState] = useState<SceneState>({});
  const [renderState, setRenderState] = useState<RenderState>({});
  
  useEffect(() => {
    // Setup client event listeners
    client.on('sceneUpdate', setSceneState);
    client.on('renderUpdate', setRenderState);
    
    return () => client.off('sceneUpdate', setSceneState);
  }, []);
  
  return (
    <OctaneContext.Provider value={{ sceneState, renderState }}>
      {children}
    </OctaneContext.Provider>
  );
}
```

### 4. Callback Streaming

**Python (callback_streamer.py):**
```python
class CallbackStreamer:
    def __init__(self):
        self.callbacks = {}
        
    async def stream_callbacks(self, websocket):
        callback_id = await self.register_with_octane('OnNewImage')
        
        async for frame in octane_callback_stream:
            await websocket.send_json({
                'type': 'newImage',
                'data': frame
            })
```

**Node.js (websocket.ts):**
```typescript
export function setupCallbackStreaming(server: Server, grpcClient: OctaneGrpcClient) {
  const wss = new WebSocketServer({ server, path: '/api/callbacks' });
  
  wss.on('connection', async (ws) => {
    const callbackId = await grpcClient.registerCallback('OnNewImage', (frame) => {
      ws.send(JSON.stringify({ type: 'newImage', data: frame }));
    });
    
    ws.on('close', () => {
      grpcClient.unregisterCallback(callbackId);
    });
  });
}
```

**React (useCallbackStream.ts):**
```typescript
export function useCallbackStream() {
  const [frame, setFrame] = useState<RenderFrame | null>(null);
  
  useEffect(() => {
    const ws = new WebSocket('ws://localhost:51024/api/callbacks');
    ws.onmessage = (event) => {
      const msg = JSON.parse(event.data);
      if (msg.type === 'newImage') setFrame(msg.data);
    };
    return () => ws.close();
  }, []);
  
  return frame;
}
```

---

## 🎨 CSS Extraction Strategy

### Finding Active Styles

**Step 1:** Search for className usage in JS files
```bash
cd octaneWeb/js
grep -r "className\s*=\|classList.add\|classList.remove" . | grep -v node_modules
```

**Step 2:** Extract those class names
```bash
# Example output:
# SceneOutlinerSync.js: element.className = 'scene-outliner-item'
# NodeInspector.js: div.classList.add('property-editor')
```

**Step 3:** Find those rules in CSS files
```bash
cd ../css
grep -h "\.scene-outliner-item\|\.property-editor" *.css
```

**Step 4:** Copy ONLY those rules to new CSS file

### Common Active Classes to Look For
```css
/* From SceneOutliner */
.scene-outliner
.scene-outliner-item
.tree-node
.tree-node-expanded
.tree-node-icon
.visibility-toggle

/* From NodeInspector */
.node-inspector
.property-editor
.property-group
.property-label
.property-value

/* From CallbackRenderViewport */
.render-viewport
.viewport-canvas
.viewport-overlay

/* From RenderToolbar */
.render-toolbar
.toolbar-button
.toolbar-separator
.render-status
```

---

## 🔧 Tech Stack

### Dependencies to Install

**Client (React TypeScript):**
```bash
npm install react react-dom
npm install --save-dev @vitejs/plugin-react vite typescript
npm install --save-dev @types/react @types/react-dom
```

**Server (Node.js gRPC):**
```bash
npm install express cors ws
npm install @grpc/grpc-js @grpc/proto-loader google-protobuf
npm install --save-dev @types/express @types/cors @types/ws
npm install --save-dev nodemon ts-node
```

**Optional but Recommended:**
```bash
npm install reactflow           # For node graph editor
npm install react-resizable-panels  # For layout manager
```

### Protobuf Generation

**Install tools:**
```bash
npm install --save-dev grpc-tools grpc_tools_node_protoc_ts
```

**Generate command:**
```bash
grpc_tools_node_protoc \
  --plugin=protoc-gen-ts=./node_modules/.bin/protoc-gen-ts \
  --ts_out=grpc_js:./server/src/generated \
  --js_out=import_style=commonjs:./server/src/generated \
  --grpc_out=grpc_js:./server/src/generated \
  -I ./server/proto \
  ./server/proto/*.proto
```

---

## 📋 Implementation Checklist

### Phase 1: Setup (Day 1)
- [ ] Create octaneWebR folder structure
- [ ] Initialize npm project with TypeScript
- [ ] Install all dependencies
- [ ] Copy .proto files from sdk/src/api/grpc/protodef/
- [ ] Generate TypeScript protobuf bindings
- [ ] Test protobuf generation

### Phase 2: Backend (Days 2-3)
- [ ] Create Node.js gRPC client class
- [ ] Test connection to Octane (getPing call)
- [ ] Implement generic gRPC call handler
- [ ] Create Express server with /api/grpc/:service/:method endpoint
- [ ] Test simple gRPC calls through REST API
- [ ] Implement WebSocket for callbacks
- [ ] Test callback streaming

### Phase 3: Frontend Foundation (Days 4-5)
- [ ] Create React app with Vite
- [ ] Port CSS to CSS modules
- [ ] Create OctaneClient service (port from OctaneWebClient.js)
- [ ] Create React Context for state management
- [ ] Create basic App.tsx with layout
- [ ] Test connection to backend

### Phase 4: Components (Days 6-10)
- [ ] Port CallbackRenderViewport (PRIORITY 1)
  - [ ] WebGL canvas setup
  - [ ] WebSocket connection
  - [ ] HDR buffer processing
  - [ ] Mouse camera control
- [ ] Port SceneOutliner
  - [ ] Tree view rendering
  - [ ] Expand/collapse
  - [ ] Visibility toggles
- [ ] Port NodeInspector
  - [ ] Property display
  - [ ] Control rendering
  - [ ] Value updates
- [ ] Port NodeGraphEditor
  - [ ] Visual graph (consider React Flow)
  - [ ] Node creation
  - [ ] Connection editing
- [ ] Port RenderToolbar
  - [ ] Control buttons
  - [ ] Status display
- [ ] Port MenuSystem
  - [ ] Menu bar
  - [ ] Dropdowns
- [ ] Port LayoutManager
  - [ ] Resizable panels

### Phase 5: Testing (Days 11-12)
- [ ] Visual comparison (screenshot diff)
- [ ] Functional testing (all features)
- [ ] Performance testing (FPS, latency)
- [ ] Error handling testing
- [ ] Cross-browser testing

### Phase 6: Polish (Days 13-14)
- [ ] Write documentation (README, SETUP, API)
- [ ] Create startup scripts
- [ ] Add configuration files
- [ ] Final validation
- [ ] Code cleanup and comments

---

## 🚨 Common Pitfalls to Avoid

### 1. Don't Redesign
❌ "I can make this UI better..."  
✅ "I'll match it exactly, then propose improvements"

### 2. Don't Skip CSS Details
❌ "Close enough..."  
✅ "Pixel-perfect match"

### 3. Don't Assume API Behavior
❌ "This probably works like..."  
✅ "Let me check the original code"

### 4. Don't Implement Everything at Once
❌ Build all components → test  
✅ Build one component → test → next component

### 5. Don't Ignore Performance
❌ "It works, ship it"  
✅ "Does it match octaneWeb's frame rate?"

---

## 🎯 Success Metrics

| Metric | Target | How to Verify |
|--------|--------|---------------|
| Visual Match | 100% | Screenshot comparison |
| Feature Parity | 100% | Feature checklist |
| Frame Rate | ≥30 FPS | Real-time rendering test |
| Load Time | ≤1s | Scene sync performance |
| Bundle Size | <2MB gzipped | Build output analysis |
| Type Safety | 100% | No TypeScript errors |

---

## 📞 When You're Stuck

### Problem: "I don't understand this algorithm"
→ **Solution:** Find it in octaneWeb source, read it carefully, port it line-by-line

### Problem: "This CSS doesn't look right"
→ **Solution:** Use browser inspector on octaneWeb to see computed styles

### Problem: "gRPC call isn't working"
→ **Solution:** Check octane_proxy.py for how Python does it, compare your Node.js code

### Problem: "React component is too complex"
→ **Solution:** Break it into smaller sub-components, but preserve functionality

### Problem: "Performance is slow"
→ **Solution:** Profile with React DevTools, compare to octaneWeb, identify bottleneck

---

## 🎓 Key Learnings to Remember

1. **octaneWeb is your spec** - When in doubt, check the original
2. **Port, don't rewrite** - Preserve algorithms and patterns
3. **Test incrementally** - Don't build everything before testing
4. **CSS matters** - Visual fidelity is part of the requirement
5. **Document as you go** - Future you will thank present you

---

## 📚 Quick Links

- **octaneWeb source:** `/workspace/grpcSamples/octaneWeb/`
- **octaneProxy source:** `/workspace/grpcSamples/octaneProxy/`
- **Proto files:** `/workspace/grpcSamples/sdk/src/api/grpc/protodef/`
- **Documentation:** `/workspace/grpcSamples/octaneWeb/REPRO_PROMPT.md`

---

## 🎯 Daily Progress Template

```markdown
## Day X Progress

### Completed Today
- [ ] Task 1
- [ ] Task 2

### Blockers
- Issue 1: Description and proposed solution

### Tomorrow's Plan
- [ ] Task 1
- [ ] Task 2

### Questions
1. Question about X?
```

---

**Remember: Quality over speed. Completeness over cleverness. When in doubt, match the original exactly.**

Good luck! 🚀
