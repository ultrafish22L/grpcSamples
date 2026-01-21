# Architecture Documentation

Technical deep dive into OtoyaiWeb's architecture, codebase structure, and implementation details.

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                         Browser                             │
│  ┌────────────────────────────────────────────────────────┐ │
│  │  React App (Vite Dev Server: localhost:60023)         │ │
│  │  ┌──────────────────────────────────────────────────┐ │ │
│  │  │  React Flow Canvas                               │ │ │
│  │  │  - Nodes (Text, Image, Video, AI Endpoints)      │ │ │
│  │  │  - Edges (Type-validated connections)            │ │ │
│  │  └──────────────────────────────────────────────────┘ │ │
│  │  ┌────────┐  ┌──────────┐  ┌──────────┐  ┌─────────┐│ │
│  │  │Toolbar │  │NodePalette│  │Inspector │  │Minimap  ││ │
│  │  └────────┘  └──────────┘  └──────────┘  └─────────┘│ │
│  │                                                        │ │
│  │  Services: API Client | Logger | Validation          │ │
│  └────────────────────────────────────────────────────────┘ │
│                          ↕ HTTP (Axios)                     │
└─────────────────────────────────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│  Express Server (localhost:3001)                            │
│  ┌────────────────────────────────────────────────────────┐ │
│  │  CORS Proxy Middleware                                 │ │
│  │  - /otoy-api/endpoints → play.otoy.ai/api/endpoints   │ │
│  │  - /otoy-api/execute → play.otoy.ai/api/execute       │ │
│  └────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│  OTOY.AI REST API (play.otoy.ai)                            │
│  - 1,137+ AI model endpoints                                │
│  - Endpoint metadata & schemas                              │
│  - Model execution & results                                │
└─────────────────────────────────────────────────────────────┘
```

---

## 📂 Directory Structure

```
otoyaiWeb/
├── client/                           # Frontend application
│   ├── src/
│   │   ├── components/
│   │   │   ├── Layout/
│   │   │   │   ├── Toolbar.tsx       # Left toolbar (New, Save, Load, Reset)
│   │   │   │   ├── NodeBar.tsx       # Middle panel (Node palette)
│   │   │   │   ├── Inspector.tsx     # Right panel (Parameter editor)
│   │   │   │   ├── Minimap.tsx       # Bottom-right minimap
│   │   │   │   └── Layout.module.css # Layout styles
│   │   │   │
│   │   │   └── Nodes/
│   │   │       ├── TextNode.tsx      # Text input node
│   │   │       ├── ImageNode.tsx     # Image upload/URL node
│   │   │       ├── VideoNode.tsx     # Video upload/URL node
│   │   │       ├── AIEndpointNode.tsx # AI model node
│   │   │       └── Nodes.module.css  # Node styles
│   │   │
│   │   ├── services/
│   │   │   ├── api.ts                # Axios-based API client
│   │   │   └── logger.ts             # File-based logging service
│   │   │
│   │   ├── types/
│   │   │   └── index.ts              # TypeScript type definitions
│   │   │
│   │   ├── utils/
│   │   │   ├── connectionValidator.ts # Pin type validation logic
│   │   │   ├── endpointCosts.ts       # Token cost database
│   │   │   └── endpointSchema.ts      # Endpoint parameter schemas
│   │   │
│   │   ├── App.tsx                   # Main app component (React Flow)
│   │   ├── main.tsx                  # React entry point
│   │   └── App.css                   # Global styles
│   │
│   ├── public/                       # Static assets
│   ├── dist/                         # Production build output
│   ├── index.html                    # HTML template
│   ├── vite.config.ts                # Vite configuration
│   ├── tsconfig.json                 # TypeScript config
│   └── package.json
│
├── server/                           # Backend server
│   ├── src/
│   │   └── index.ts                  # Express server with CORS proxy
│   ├── logs/
│   │   └── app.log                   # Runtime logs (git-ignored)
│   ├── tsconfig.json
│   └── package.json
│
├── docs/                             # (Legacy - to be removed)
├── README.md                         # Main documentation
├── FEATURES.md                       # Feature documentation
├── ARCHITECTURE.md                   # This file
├── QUICKSTART.MD                     # Setup guide
└── package.json                      # Root package (scripts only)
```

---

## 🧩 Component Architecture

### App.tsx (Main Component)

**Responsibilities:**
- Initialize React Flow instance
- Manage global state (Zustand store)
- Handle node/edge CRUD operations
- Provide callbacks to child components

**State Management:**
```typescript
interface AppState {
  nodes: Node[];
  edges: Edge[];
  endpoints: Endpoint[];
  visibleEndpoints: string[];
  selectedNode: Node | null;
  contextMenu: ContextMenuState | null;
}
```

**Key Hooks:**
- `useNodesState()` - React Flow nodes
- `useEdgesState()` - React Flow edges
- `useReactFlow()` - Canvas controls (zoom, pan, etc.)

---

### Node Components

#### Base Node Structure
All nodes follow this pattern:
```typescript
interface NodeProps {
  id: string;              // Unique node ID
  data: NodeData;          // Node-specific data
  selected: boolean;       // Selection state
}
```

#### TextNode.tsx
**State:**
```typescript
interface TextNodeData {
  text: string;            // User input
  label?: string;          // Display title
}
```

**Features:**
- Single orange output pin (string type)
- Auto-growing textarea
- Real-time text updates via `updateNodeData()`

---

#### ImageNode.tsx
**State:**
```typescript
interface ImageNodeData {
  items: MediaItem[];      // Array of images
}

interface MediaItem {
  id: string;              // Unique item ID
  url?: string;            // Image URL
  file?: File;             // Uploaded file
  preview?: string;        // Base64 preview
  name: string;            // Display name
  collapsed: boolean;      // UI state (future)
}
```

**Features:**
- Multi-item support (unlimited images per node)
- Dynamic handle creation (one per image)
- Handle positioning: evenly spaced across width
- Upload methods: file picker or URL prompt
- Individual delete buttons per image

**Handle Position Calculation:**
```typescript
// For N items, handles positioned at:
// [1/(N+1), 2/(N+1), ..., N/(N+1)]
const handlePositions = items.map((_, index) => 
  (index + 1) / (items.length + 1)
);
```

**Update Strategy:**
```typescript
// Dual-phase update for React Flow internals
useLayoutEffect(() => {
  updateNodeInternals(id);  // Sync after DOM update
}, [items.length]);

useEffect(() => {
  setTimeout(() => {
    updateNodeInternals(id); // Delayed to catch edge cases
  }, 10);
}, [items.length]);
```

---

#### VideoNode.tsx
**State:** Same as ImageNode (but for videos)

**Features:**
- Multi-item support (unlimited videos per node)
- Magenta output pins (video type)
- Video preview (first frame thumbnail)
- Same handle positioning logic as ImageNode

---

#### AIEndpointNode.tsx
**State:**
```typescript
interface AIEndpointNodeData {
  endpoint: Endpoint;          // Model metadata from API
  parameters: Record<string, any>; // User inputs
  executionStatus: 'idle' | 'executing' | 'success' | 'error';
  result?: any;                // Execution result (future)
  previewCollapsed: boolean;   // UI state
}

interface Endpoint {
  id: string;                  // e.g., "fal-ai/flux-1/dev"
  title: string;               // Display name
  category: string;            // e.g., "text-to-image"
  schema: {
    input: Record<string, ParameterSchema>;
    output: Record<string, any>;
  };
}
```

**Dynamic Handle Creation:**
```typescript
// Input handles (left side)
Object.entries(endpoint.schema.input).map(([key, param]) => (
  <Handle
    type="target"
    position={Position.Left}
    id={`input-${key}`}
    style={{
      top: calculateVerticalPosition(index, totalInputs),
      background: getColorForType(param.type)
    }}
  />
));

// Output handle (right side)
<Handle
  type="source"
  position={Position.Right}
  id="output"
  style={{ background: getColorForType(outputType) }}
/>
```

---

### Layout Components

#### Toolbar.tsx
**Actions:**
```typescript
const toolbarActions = {
  newProject: () => {
    if (confirm('Clear current project?')) {
      clearCanvas();
    }
  },
  
  saveProject: async () => {
    const data = serializeCanvas();
    await showSaveFilePicker('.otoyai');
    writeFile(data);
  },
  
  loadProject: async () => {
    const [fileHandle] = await showOpenFilePicker();
    const data = await readFile(fileHandle);
    deserializeCanvas(data);
  },
  
  reset: () => {
    clearLogs();
    location.reload();
  }
};
```

---

#### NodeBar.tsx
**Endpoint Organization:**
```typescript
interface CategoryState {
  [category: string]: {
    expanded: boolean;
    endpoints: Endpoint[];
  };
}

// Categories: utility, text-to-image, image-to-image, 
//             image-to-video, text-to-video, image-to-3d, etc.
```

**Node Addition:**
```typescript
const addNode = (endpoint: Endpoint) => {
  const newNode = {
    id: `node-${Date.now()}`,
    type: 'aiEndpoint',
    position: getViewportCenter(), // Center in visible area
    data: {
      endpoint,
      parameters: getDefaultParameters(endpoint),
      executionStatus: 'idle'
    }
  };
  
  setNodes((nodes) => [...nodes, newNode]);
  logger.info('Node added', { endpoint: endpoint.id });
};
```

**Token Cost Display:**
```typescript
import { getEndpointCostDisplay } from '../../utils/endpointCosts';

const cost = getEndpointCostDisplay(endpoint.id);
// Returns string like "25" or null if unknown
```

---

#### Inspector.tsx
**Parameter Rendering:**
```typescript
const renderParameter = (key: string, schema: ParameterSchema) => {
  const isConnected = hasIncomingEdge(selectedNode.id, key);
  
  if (isConnected) {
    return (
      <ConnectedInput
        sourceNode={getSourceNode(key)}
        value={getConnectedValue(key)}
      />
    );
  }
  
  // Render editable input based on type
  switch (schema.type) {
    case 'string':
      return <textarea value={value} onChange={handleChange} />;
    case 'integer':
    case 'float':
      return <input type="number" value={value} onChange={handleChange} />;
    case 'boolean':
      return <input type="checkbox" checked={value} onChange={handleChange} />;
    case 'enum':
      return (
        <select value={value} onChange={handleChange}>
          {schema.enum?.map(option => (
            <option key={option} value={option}>{option}</option>
          ))}
        </select>
      );
    default:
      return <input type="text" value={value} onChange={handleChange} />;
  }
};
```

**Connected Input Display:**
```typescript
interface ConnectedInputProps {
  sourceNode: Node;
  value: any;
}

const ConnectedInput = ({ sourceNode, value }: ConnectedInputProps) => (
  <div className={styles.connectedInput}>
    <div className={styles.connectedLabel}>
      Connected from: "{sourceNode.data.label || sourceNode.type}"
    </div>
    <div className={styles.connectedValue}>
      {formatValue(value)}
    </div>
  </div>
);
```

---

## 🔌 Type System Implementation

### Pin Color Mapping

**Definition:**
```typescript
// utils/connectionValidator.ts
export const TYPE_COLORS: Record<string, string> = {
  // Parameter types
  string: '#ffaa44',  // Orange
  integer: '#ffdd44', // Yellow
  float: '#00ddff',   // Cyan
  boolean: '#ff4444', // Red
  enum: '#cc44ff',    // Purple
  
  // Media types
  image: '#44ff44',   // Green
  video: '#ff44ff',   // Magenta
  audio: '#4499ff',   // Blue
  json: '#44ffdd',    // Teal
  any: '#aaaaaa',     // Gray
};

export const getColorForType = (type: string): string => {
  return TYPE_COLORS[type.toLowerCase()] || TYPE_COLORS.any;
};
```

---

### Connection Validation

**Logic:**
```typescript
export const isValidConnection = (
  sourceType: string,
  targetType: string
): boolean => {
  // Normalize types
  const source = sourceType.toLowerCase();
  const target = targetType.toLowerCase();
  
  // Any type accepts everything
  if (target === 'any' || source === 'any') {
    return true;
  }
  
  // Exact type match
  if (source === target) {
    return true;
  }
  
  // Type compatibility (future: array types, etc.)
  return false;
};
```

**React Flow Integration:**
```typescript
const onConnect = useCallback((connection: Connection) => {
  const sourceNode = nodes.find(n => n.id === connection.source);
  const targetNode = nodes.find(n => n.id === connection.target);
  
  const sourceHandle = getHandleById(sourceNode, connection.sourceHandle);
  const targetHandle = getHandleById(targetNode, connection.targetHandle);
  
  if (!isValidConnection(sourceHandle.type, targetHandle.type)) {
    logger.warn('Invalid connection rejected', { connection });
    return; // Don't create edge
  }
  
  const newEdge = {
    ...connection,
    animated: true,
    style: {
      stroke: getColorForType(sourceHandle.type),
      strokeWidth: 2
    }
  };
  
  setEdges((edges) => [...edges, newEdge]);
}, [nodes, setEdges]);
```

---

## 🌐 API Integration

### Client Service

**File:** `client/src/services/api.ts`

```typescript
import axios from 'axios';
import { logger } from './logger';

const OTOY_API_BASE = '/otoy-api'; // Proxied by Express server

class OtoyAPI {
  async fetchEndpoints(): Promise<EndpointsResponse> {
    try {
      logger.info('Fetching endpoints from play.otoy.ai');
      const startTime = performance.now();
      
      const response = await axios.get<EndpointsResponse>(
        `${OTOY_API_BASE}/endpoints`
      );
      
      const duration = performance.now() - startTime;
      logger.info(`Endpoints fetched in ${duration.toFixed(2)}ms`, {
        count: response.data.endpoints.length
      });
      
      return response.data;
    } catch (error) {
      logger.error('Failed to fetch endpoints', error as Error);
      throw error;
    }
  }
  
  // Coming soon: executeEndpoint()
}

export const otoyAPI = new OtoyAPI();
```

---

### Server Proxy

**File:** `server/src/index.ts`

```typescript
import express from 'express';
import cors from 'cors';
import axios from 'axios';

const app = express();
const PORT = 3001;

// CORS for local development
app.use(cors({
  origin: ['http://localhost:60023', 'http://localhost:5173'],
  credentials: true
}));

app.use(express.json());

// Proxy to play.otoy.ai
app.get('/otoy-api/endpoints', async (req, res) => {
  try {
    const response = await axios.get('https://play.otoy.ai/api/endpoints');
    res.json(response.data);
  } catch (error) {
    console.error('Proxy error:', error);
    res.status(500).json({ error: 'Failed to fetch endpoints' });
  }
});

// Coming soon: POST /otoy-api/execute

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
```

---

## 💾 State Management

### Zustand Store (Conceptual - not yet extracted)

**Current:** State managed in App.tsx with React hooks

**Future Refactor:**
```typescript
// store/useAppStore.ts
import { create } from 'zustand';

interface AppStore {
  // State
  nodes: Node[];
  edges: Edge[];
  endpoints: Endpoint[];
  visibleEndpoints: string[];
  selectedNode: Node | null;
  
  // Actions
  addNode: (node: Node) => void;
  removeNode: (id: string) => void;
  updateNodeData: (id: string, data: Partial<NodeData>) => void;
  addEdge: (edge: Edge) => void;
  removeEdge: (id: string) => void;
  setSelectedNode: (node: Node | null) => void;
  
  // Project management
  loadProject: (data: ProjectData) => void;
  clearProject: () => void;
}

export const useAppStore = create<AppStore>((set, get) => ({
  // Implementation
}));
```

---

## 📦 File Format Specifications

### .otoyai Project File

**Structure:**
```json
{
  "version": "1.0",
  "timestamp": 1705823456789,
  "nodes": [
    {
      "id": "node-1",
      "type": "textInput",
      "position": { "x": 100, "y": 100 },
      "data": {
        "text": "A majestic tiger",
        "label": "Prompt"
      }
    },
    {
      "id": "node-2",
      "type": "aiEndpoint",
      "position": { "x": 400, "y": 100 },
      "data": {
        "endpoint": {
          "id": "fal-ai/flux-1/dev",
          "title": "FLUX.1 [Dev]",
          "category": "text-to-image"
        },
        "parameters": {
          "prompt": "A majestic tiger",
          "num_inference_steps": 50
        },
        "executionStatus": "idle"
      }
    }
  ],
  "edges": [
    {
      "id": "edge-1",
      "source": "node-1",
      "target": "node-2",
      "sourceHandle": "output",
      "targetHandle": "input-prompt",
      "animated": true,
      "style": {
        "stroke": "#ffaa44",
        "strokeWidth": 2
      }
    }
  ],
  "visibleEndpoints": [
    "fal-ai/flux-1/dev",
    "fal-ai/flux-1/schnell",
    "kling/video-o1/standard"
  ],
  "viewport": {
    "x": 0,
    "y": 0,
    "zoom": 1
  }
}
```

---

### .otoyai-workspace File

**Structure:**
```json
{
  "version": "1.0",
  "timestamp": 1705823456789,
  "visibleEndpoints": [
    "fal-ai/flux-1/dev",
    "fal-ai/flux-1/schnell",
    "fal-ai/auraflow",
    "kling/video-o1/standard",
    "cog-video-x/5b"
  ]
}
```

---

## 🎨 Styling Architecture

### CSS Modules

**Benefits:**
- Scoped class names (no global pollution)
- Tree-shaking unused styles
- TypeScript support with `.module.css.d.ts`

**Example:**
```typescript
// Component
import styles from './Nodes.module.css';

<div className={styles.baseNode}>
  <div className={styles.nodeTitle}>Title</div>
</div>
```

```css
/* Nodes.module.css */
.baseNode {
  background: #2a2a2a;
  border: 1px solid #444;
  border-radius: 8px;
  padding: 12px;
}

.nodeTitle {
  color: #fff;
  font-size: 14px;
  font-weight: 600;
}
```

---

### Theme Variables (Future)

**Planned:**
```css
:root {
  /* Colors */
  --bg-primary: #1e1e1e;
  --bg-secondary: #2a2a2a;
  --border-color: #444444;
  --text-primary: #ffffff;
  --text-secondary: #cccccc;
  --accent-color: #00ddff;
  
  /* Spacing */
  --spacing-xs: 4px;
  --spacing-sm: 8px;
  --spacing-md: 12px;
  --spacing-lg: 16px;
  
  /* Pin colors */
  --pin-string: #ffaa44;
  --pin-integer: #ffdd44;
  --pin-float: #00ddff;
  --pin-image: #44ff44;
  --pin-video: #ff44ff;
}
```

---

## 🔧 Build Configuration

### Vite Config

**File:** `client/vite.config.ts`

```typescript
import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

export default defineConfig({
  plugins: [react()],
  
  server: {
    port: parseInt(process.env.WORKER_1 || '60023'),
    host: '0.0.0.0',
    cors: true,
    proxy: {
      '/otoy-api': {
        target: 'http://localhost:3001',
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/otoy-api/, '')
      }
    }
  },
  
  build: {
    outDir: 'dist',
    sourcemap: true
  }
});
```

---

## 🧪 Testing Strategy (Future)

**Planned:**
```
client/
├── src/
│   ├── components/
│   │   ├── Layout/
│   │   │   ├── Toolbar.tsx
│   │   │   └── Toolbar.test.tsx          ← Unit tests
│   │   └── Nodes/
│   │       ├── TextNode.tsx
│   │       └── TextNode.test.tsx
│   │
│   └── utils/
│       ├── connectionValidator.ts
│       └── connectionValidator.test.ts    ← Logic tests
│
└── e2e/
    ├── node-creation.spec.ts              ← E2E tests
    ├── connection-validation.spec.ts
    └── save-load.spec.ts
```

**Tools:**
- Vitest (unit tests)
- React Testing Library (component tests)
- Playwright (E2E tests)

---

## 📊 Performance Considerations

### React Flow Optimization

**Current:**
- Default virtualization enabled
- Debounced edge updates on drag
- Memoized node components

**Future Optimizations:**
- `React.memo()` for all node components
- Virtualized inspector parameter list
- Web Worker for heavy computations
- IndexedDB for large project caching

---

## 🔒 Security

**Current:**
- CORS enabled for local development only
- No authentication (local app)
- File System Access API (user-granted permissions)

**Future:**
- API key management for OTOY.AI
- Secure token storage
- Rate limiting on execution
- Sandboxed user code (if custom nodes added)

---

## 📈 Roadmap Implementation Details

### AI Endpoint Execution (Next)

**Client Changes:**
```typescript
// api.ts
async executeEndpoint(
  endpointId: string,
  parameters: Record<string, any>
): Promise<ExecutionResult> {
  const response = await axios.post(`${OTOY_API_BASE}/execute`, {
    endpoint: endpointId,
    input: parameters
  });
  return response.data;
}
```

**Server Changes:**
```typescript
// server/src/index.ts
app.post('/otoy-api/execute', async (req, res) => {
  try {
    const { endpoint, input } = req.body;
    
    const response = await axios.post(
      `https://play.otoy.ai/api/${endpoint}`,
      input
    );
    
    res.json(response.data);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});
```

**Node Updates:**
```typescript
// AIEndpointNode.tsx
const handleExecute = async () => {
  setExecutionStatus('executing');
  
  try {
    const result = await otoyAPI.executeEndpoint(
      endpoint.id,
      parameters
    );
    
    updateNodeData(id, { result, executionStatus: 'success' });
  } catch (error) {
    setExecutionStatus('error');
    logger.error('Execution failed', error);
  }
};
```

---

**Last Updated:** January 21, 2025
