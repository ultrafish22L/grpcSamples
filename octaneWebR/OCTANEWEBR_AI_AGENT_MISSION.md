# OctaneWebR: AI Agent Mission Brief - 1-Day Complete Port

## 🎯 Mission Objective

Port **octaneWeb** (vanilla JS + Python proxy) to **octaneWebR** (React TypeScript + Node.js gRPC) in a single working session. This is a **direct translation project** - reproduce every feature exactly.

## 🤖 AI Agent Optimization

You are an AI agent capable of:
- ✅ Analyzing entire codebases instantly
- ✅ Working on multiple files simultaneously  
- ✅ Executing batch operations efficiently
- ✅ Completing in hours what humans do in weeks

This mission is structured for **parallel execution** and **maximum efficiency**.

---

## 📋 Quick Reference

**Source:** `/workspace/grpcSamples/octaneWeb/` (23 JS files, production-ready)  
**Target:** `/workspace/grpcSamples/octaneWebR/` (new React TypeScript app)  
**Ports:** Octane=51022, OldProxy=51023, NewServer=51024, Client=5173

**Core Rule:** Match octaneWeb **exactly**. Same UI, same functionality, same UX.

---

## 🚀 Execution Plan (Sequential Phases)

### Phase 1: Analysis & Setup (30 min)
**Goal:** Understand codebase, setup project structure

### Phase 2: Node.js gRPC Backend (2 hours)
**Goal:** Working Node.js server with direct Octane gRPC

### Phase 3: React Frontend Foundation (2 hours)
**Goal:** React app shell with styling and API client

### Phase 4: Component Implementation (4 hours)
**Goal:** Port all 7 major components to React

### Phase 5: Integration & Testing (1.5 hours)
**Goal:** End-to-end working, validated against octaneWeb

---

## 📊 Phase 1: Analysis & Setup (30 min)

### 1.1 Analyze Source Codebase

**Execute these analysis commands:**

```bash
# Map all JavaScript files
find /workspace/grpcSamples/octaneWeb/js -name "*.js" -type f > /tmp/octaneweb_files.txt

# Extract all CSS classes used in JS
grep -rh "className\s*=\|classList\.\(add\|remove\)" /workspace/grpcSamples/octaneWeb/js \
  | grep -oE '["'"'"'][a-zA-Z0-9_-]+["'"'"']' \
  | sort -u > /tmp/css_classes_used.txt

# Map gRPC service calls
grep -rh "makeApiCall\|makeGrpcCall" /workspace/grpcSamples/octaneWeb/js \
  | grep -oE "['\"](Api[A-Za-z]+)['\"].*['\"](get|set|start|stop|pause|continue|restart|register)[A-Za-z]*['\"]" \
  > /tmp/grpc_calls_used.txt

# Count LOC to estimate scope
wc -l /workspace/grpcSamples/octaneWeb/js/**/*.js
```

**Key Files to Reference:**
- `/workspace/grpcSamples/octaneWeb/js/core/OctaneWebClient.js` - Main API client (YOUR BLUEPRINT)
- `/workspace/grpcSamples/octaneWeb/js/components/CallbackRenderViewport.js` - Real-time rendering
- `/workspace/grpcSamples/octaneWeb/js/components/SceneOutlinerSync.js` - Tree view patterns
- `/workspace/grpcSamples/octaneProxy/octane_proxy.py` - gRPC translation pattern
- `/workspace/grpcSamples/sdk/src/api/grpc/protodef/*.proto` - API definitions

### 1.2 Create Project Structure

```bash
cd /workspace/grpcSamples

# Create octaneWebR with modern structure
mkdir -p octaneWebR/{client,server,scripts}

# Client structure
mkdir -p octaneWebR/client/{src,public}
mkdir -p octaneWebR/client/src/{components,hooks,services,types,utils,constants,styles}

# Server structure  
mkdir -p octaneWebR/server/{src,proto}
mkdir -p octaneWebR/server/src/{grpc,api,generated,utils}

# Copy proto files
cp sdk/src/api/grpc/protodef/*.proto octaneWebR/server/proto/

echo "✅ Project structure created"
```

### 1.3 Initialize Node.js Project

```bash
cd octaneWebR

# Create package.json
cat > package.json << 'EOF'
{
  "name": "octaneweb-react",
  "version": "1.0.0",
  "description": "OctaneWeb ported to React TypeScript with Node.js gRPC",
  "scripts": {
    "generate:proto": "bash scripts/generate-proto.sh",
    "server:dev": "nodemon --exec ts-node server/src/index.ts",
    "client:dev": "vite",
    "dev": "concurrently \"npm:server:dev\" \"npm:client:dev\"",
    "build:client": "tsc && vite build",
    "build:server": "tsc -p server/tsconfig.json",
    "build": "npm run build:client && npm run build:server",
    "start": "node server/dist/index.js"
  },
  "dependencies": {
    "react": "^18.2.0",
    "react-dom": "^18.2.0",
    "express": "^4.18.2",
    "cors": "^2.8.5",
    "ws": "^8.14.2",
    "@grpc/grpc-js": "^1.9.13",
    "@grpc/proto-loader": "^0.7.10",
    "google-protobuf": "^3.21.2"
  },
  "devDependencies": {
    "@types/react": "^18.2.43",
    "@types/react-dom": "^18.2.17",
    "@types/express": "^4.17.21",
    "@types/cors": "^2.8.17",
    "@types/ws": "^8.5.10",
    "@types/node": "^20.10.5",
    "@vitejs/plugin-react": "^4.2.1",
    "typescript": "^5.3.3",
    "vite": "^5.0.8",
    "ts-node": "^10.9.2",
    "nodemon": "^3.0.2",
    "concurrently": "^8.2.2",
    "grpc-tools": "^1.12.4",
    "grpc_tools_node_protoc_ts": "^5.3.3"
  }
}
EOF

# Install dependencies
npm install

echo "✅ Dependencies installed"
```

### 1.4 Create TypeScript Configurations

```bash
# Root tsconfig.json
cat > tsconfig.json << 'EOF'
{
  "compilerOptions": {
    "target": "ES2020",
    "useDefineForClassFields": true,
    "lib": ["ES2020", "DOM", "DOM.Iterable"],
    "module": "ESNext",
    "skipLibCheck": true,
    "moduleResolution": "bundler",
    "allowImportingTsExtensions": true,
    "resolveJsonModule": true,
    "isolatedModules": true,
    "noEmit": true,
    "jsx": "react-jsx",
    "strict": true,
    "noUnusedLocals": true,
    "noUnusedParameters": true,
    "noFallthroughCasesInSwitch": true
  },
  "include": ["client/src"],
  "references": [{ "path": "./tsconfig.node.json" }]
}
EOF

# Server tsconfig.json
cat > server/tsconfig.json << 'EOF'
{
  "compilerOptions": {
    "target": "ES2020",
    "module": "commonjs",
    "lib": ["ES2020"],
    "outDir": "./dist",
    "rootDir": "./src",
    "strict": true,
    "esModuleInterop": true,
    "skipLibCheck": true,
    "forceConsistentCasingInFileNames": true,
    "resolveJsonModule": true,
    "moduleResolution": "node"
  },
  "include": ["src/**/*"],
  "exclude": ["node_modules", "dist"]
}
EOF

# Vite config
cat > vite.config.ts << 'EOF'
import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

export default defineConfig({
  plugins: [react()],
  server: {
    port: 5173,
    host: '0.0.0.0',
    allowedHosts: ['*']
  }
})
EOF

echo "✅ TypeScript configured"
```

**Deliverable:** Project structure ready, dependencies installed

---

## 📊 Phase 2: Node.js gRPC Backend (2 hours)

### 2.1 Generate Protobuf Bindings

```bash
# Create generation script
cat > scripts/generate-proto.sh << 'EOF'
#!/bin/bash
set -e

PROTO_DIR="./server/proto"
OUT_DIR="./server/src/generated"

echo "🔧 Generating protobuf bindings..."

mkdir -p "$OUT_DIR"

# Generate TypeScript bindings for all proto files
npx grpc_tools_node_protoc \
  --plugin=protoc-gen-ts=./node_modules/.bin/protoc-gen-ts \
  --ts_out=grpc_js:"$OUT_DIR" \
  --js_out=import_style=commonjs,binary:"$OUT_DIR" \
  --grpc_out=grpc_js:"$OUT_DIR" \
  -I "$PROTO_DIR" \
  "$PROTO_DIR"/*.proto

echo "✅ Protobuf generation complete: $OUT_DIR"
ls -lh "$OUT_DIR" | head -20
EOF

chmod +x scripts/generate-proto.sh

# Run generation
npm run generate:proto

echo "✅ Protobuf bindings generated"
```

### 2.2 Create gRPC Client Manager

Create `server/src/grpc/client.ts`:

```typescript
import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';
import path from 'path';
import { EventEmitter } from 'events';

export interface GrpcCallOptions {
  timeout?: number;
  metadata?: grpc.Metadata;
}

export class OctaneGrpcClient extends EventEmitter {
  private channel: grpc.Channel;
  private services: Map<string, any> = new Map();
  private packageDefinition: protoLoader.PackageDefinition | null = null;
  private protoDescriptor: grpc.GrpcObject | null = null;
  
  constructor(
    private octaneHost: string = process.env.OCTANE_HOST || 'localhost',
    private octanePort: number = parseInt(process.env.OCTANE_PORT || '51022')
  ) {
    super();
    
    this.channel = new grpc.Channel(
      `${this.octaneHost}:${this.octanePort}`,
      grpc.credentials.createInsecure()
    );
    
    console.log(`📡 gRPC channel: ${this.octaneHost}:${this.octanePort}`);
  }
  
  async initialize(): Promise<void> {
    const PROTO_PATH = path.resolve(__dirname, '../../proto');
    const fs = require('fs');
    const protoFiles = fs.readdirSync(PROTO_PATH)
      .filter((f: string) => f.endsWith('.proto'))
      .map((f: string) => path.join(PROTO_PATH, f));
    
    this.packageDefinition = protoLoader.loadSync(protoFiles, {
      keepCase: true,
      longs: String,
      enums: String,
      defaults: true,
      oneofs: true
    });
    
    this.protoDescriptor = grpc.loadPackageDefinition(this.packageDefinition);
    console.log('✅ Proto definitions loaded');
  }
  
  private getService(serviceName: string): any {
    if (this.services.has(serviceName)) {
      return this.services.get(serviceName);
    }
    
    if (!this.protoDescriptor) {
      throw new Error('Call initialize() first');
    }
    
    // Try namespace patterns
    let ServiceConstructor: any = null;
    const patterns = [
      `OctaneEngine.Livelink.${serviceName}`,
      serviceName
    ];
    
    for (const pattern of patterns) {
      ServiceConstructor = this.resolveServicePath(this.protoDescriptor, pattern);
      if (ServiceConstructor) break;
    }
    
    if (!ServiceConstructor) {
      throw new Error(`Service ${serviceName} not found`);
    }
    
    const service = new ServiceConstructor(
      `${this.octaneHost}:${this.octanePort}`,
      grpc.credentials.createInsecure()
    );
    
    this.services.set(serviceName, service);
    return service;
  }
  
  private resolveServicePath(descriptor: any, path: string): any {
    const parts = path.split('.');
    let current = descriptor;
    
    for (const part of parts) {
      if (current[part]) {
        current = current[part];
      } else {
        return null;
      }
    }
    
    return current;
  }
  
  async callMethod(
    serviceName: string,
    methodName: string,
    params: any = {},
    options: GrpcCallOptions = {}
  ): Promise<any> {
    console.log(`📤 ${serviceName}.${methodName}`);
    
    const service = this.getService(serviceName);
    const method = service[methodName];
    
    if (!method || typeof method !== 'function') {
      throw new Error(`Method ${methodName} not found`);
    }
    
    const request = Object.keys(params).length === 0 ? {} : params;
    const metadata = options.metadata || new grpc.Metadata();
    const deadline = Date.now() + (options.timeout || 30000);
    
    return new Promise((resolve, reject) => {
      method.call(service, request, metadata, { deadline }, 
        (error: grpc.ServiceError | null, response: any) => {
          if (error) {
            console.error(`❌ ${serviceName}.${methodName}:`, error.message);
            reject(error);
          } else {
            console.log(`✅ ${serviceName}.${methodName}`);
            resolve(response);
          }
        }
      );
    });
  }
  
  close(): void {
    this.channel.close();
    this.services.clear();
  }
  
  async checkHealth(): Promise<boolean> {
    try {
      await this.callMethod('ApiProjectManager', 'getPing', {});
      return true;
    } catch {
      return false;
    }
  }
}

let instance: OctaneGrpcClient | null = null;

export function getGrpcClient(): OctaneGrpcClient {
  if (!instance) {
    instance = new OctaneGrpcClient();
  }
  return instance;
}
```

**Command to create:**
```bash
cat > server/src/grpc/client.ts << 'EOF'
[paste above code]
EOF
```

### 2.3 Create Express Server

Create `server/src/index.ts`:

```typescript
import express from 'express';
import cors from 'cors';
import { OctaneGrpcClient, getGrpcClient } from './grpc/client';
import { setupCallbackStreaming } from './api/websocket';

const app = express();
const PORT = parseInt(process.env.SERVER_PORT || '51024');

app.use(cors({ origin: '*', credentials: true }));
app.use(express.json({ limit: '50mb' }));

const grpcClient = getGrpcClient();

// Initialize
grpcClient.initialize().then(() => {
  console.log('✅ gRPC client initialized');
}).catch(error => {
  console.error('❌ Failed to initialize:', error);
  process.exit(1);
});

// Health check
app.get('/api/health', async (req, res) => {
  const isHealthy = await grpcClient.checkHealth();
  res.json({
    status: isHealthy ? 'ok' : 'unhealthy',
    octane: isHealthy ? 'connected' : 'disconnected',
    timestamp: new Date().toISOString()
  });
});

// Generic gRPC endpoint (matches octaneWeb pattern)
app.post('/api/grpc/:service/:method', async (req, res) => {
  const { service, method } = req.params;
  const params = req.body;
  
  try {
    const response = await grpcClient.callMethod(service, method, params);
    const jsonResponse = response.toObject ? response.toObject() : response;
    res.json(jsonResponse);
  } catch (error: any) {
    res.status(500).json({
      error: error.message || 'gRPC call failed',
      service,
      method
    });
  }
});

const server = app.listen(PORT, () => {
  console.log(`🚀 Server on port ${PORT}`);
});

setupCallbackStreaming(server, grpcClient);

process.on('SIGTERM', () => {
  server.close(() => {
    grpcClient.close();
    process.exit(0);
  });
});
```

### 2.4 Create WebSocket Callback Handler

Create `server/src/api/websocket.ts`:

```typescript
import { WebSocketServer, WebSocket } from 'ws';
import { Server } from 'http';
import { OctaneGrpcClient } from '../grpc/client';

export function setupCallbackStreaming(
  server: Server,
  grpcClient: OctaneGrpcClient
): void {
  const wss = new WebSocketServer({ server, path: '/api/callbacks' });
  
  wss.on('connection', (ws: WebSocket) => {
    console.log('🔌 Callback client connected');
    
    // Setup callback forwarding
    const forwardCallback = (data: any) => {
      if (ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({
          type: 'newImage',
          data,
          timestamp: Date.now()
        }));
      }
    };
    
    grpcClient.on('OnNewImage', forwardCallback);
    
    ws.on('message', (message: Buffer) => {
      const data = JSON.parse(message.toString());
      if (data.type === 'ping') {
        ws.send(JSON.stringify({ type: 'pong' }));
      }
    });
    
    ws.on('close', () => {
      console.log('🔌 Callback client disconnected');
      grpcClient.off('OnNewImage', forwardCallback);
    });
  });
  
  console.log('✅ WebSocket callbacks initialized');
}
```

**Execute creation:**
```bash
# Create all server files at once
cat > server/src/index.ts << 'EOF'
[server code]
EOF

cat > server/src/api/websocket.ts << 'EOF'
[websocket code]
EOF

# Test the server
npm run server:dev &
sleep 2
curl http://localhost:51024/api/health
```

**Deliverable:** Working Node.js server with gRPC connection to Octane

---

## 📊 Phase 3: React Frontend Foundation (2 hours)

### 3.1 Extract Active CSS

```bash
# Analyze CSS usage in octaneWeb
cd /workspace/grpcSamples/octaneWeb

# Extract all class names from JS files
grep -rh "className\|classList" js/ | \
  grep -oE "['\"]([\w-]+)['\"]" | \
  sort -u > /tmp/active_classes.txt

# Create minimal CSS from active classes
cat css/octane-theme.css css/components.css css/layout.css > /tmp/all_css.txt

# Copy to octaneWebR
cd /workspace/grpcSamples/octaneWebR
cp ../octaneWeb/css/*.css client/src/styles/

echo "✅ CSS extracted"
```

### 3.2 Create React App Shell

Create `client/index.html`:

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>OctaneWebR</title>
  </head>
  <body>
    <div id="root"></div>
    <script type="module" src="/src/main.tsx"></script>
  </body>
</html>
```

Create `client/src/main.tsx`:

```typescript
import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App'
import './styles/octane-theme.css'
import './styles/components.css'
import './styles/layout.css'

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
)
```

Create `client/src/App.tsx`:

```typescript
import React from 'react'
import { OctaneClientProvider } from './hooks/useOctaneClient'
import { CallbackRenderViewport } from './components/CallbackRenderViewport'
import { SceneOutliner } from './components/SceneOutliner'
import { NodeInspector } from './components/NodeInspector'
import { RenderToolbar } from './components/RenderToolbar'

function App() {
  return (
    <OctaneClientProvider>
      <div className="octane-app">
        <RenderToolbar />
        <div className="main-layout">
          <CallbackRenderViewport />
          <SceneOutliner />
          <NodeInspector />
        </div>
      </div>
    </OctaneClientProvider>
  )
}

export default App
```

### 3.3 Create OctaneClient Service

Create `client/src/services/OctaneClient.ts` - port from `octaneWeb/js/core/OctaneWebClient.js`:

```typescript
export class OctaneClient extends EventTarget {
  private serverUrl: string;
  private sceneState: any = { objects: new Map(), hierarchy: [] };
  private renderState: any = { isRendering: false, samples: 0 };
  
  constructor(serverUrl: string = 'http://localhost:51024') {
    super();
    this.serverUrl = serverUrl;
  }
  
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
  
  // Port all methods from OctaneWebClient.js
  async syncScene() {
    const response = await this.makeApiCall('ApiProjectManager', 'getSceneInfo', {});
    this.sceneState = response;
    this.dispatchEvent(new CustomEvent('sceneUpdate', { detail: this.sceneState }));
    return response;
  }
  
  async setCameraPosition(x: number, y: number, z: number) {
    return this.makeApiCall('ApiRenderEngineService', 'setCameraPosition', {
      position: { x, y, z }
    });
  }
  
  async setCameraTarget(x: number, y: number, z: number) {
    return this.makeApiCall('ApiRenderEngineService', 'setCameraTarget', {
      target: { x, y, z }
    });
  }
  
  async startRender() {
    return this.makeApiCall('ApiRenderEngineService', 'startRendering', {});
  }
  
  async stopRender() {
    return this.makeApiCall('ApiRenderEngineService', 'stopRendering', {});
  }
  
  async pauseRender() {
    return this.makeApiCall('ApiRenderEngineService', 'pauseRendering', {});
  }
  
  async restartRender() {
    return this.makeApiCall('ApiRenderEngineService', 'restartRendering', {});
  }
}
```

### 3.4 Create React Context & Hook

Create `client/src/hooks/useOctaneClient.tsx`:

```typescript
import React, { createContext, useContext, useEffect, useState } from 'react';
import { OctaneClient } from '../services/OctaneClient';

interface OctaneContextType {
  client: OctaneClient;
  sceneState: any;
  renderState: any;
  isConnected: boolean;
}

const OctaneContext = createContext<OctaneContextType | null>(null);

export function OctaneClientProvider({ children }: { children: React.ReactNode }) {
  const [client] = useState(() => new OctaneClient());
  const [sceneState, setSceneState] = useState<any>({ hierarchy: [] });
  const [renderState, setRenderState] = useState<any>({});
  const [isConnected, setIsConnected] = useState(false);
  
  useEffect(() => {
    const handleSceneUpdate = (e: any) => setSceneState(e.detail);
    const handleRenderUpdate = (e: any) => setRenderState(e.detail);
    
    client.addEventListener('sceneUpdate', handleSceneUpdate as EventListener);
    client.addEventListener('renderUpdate', handleRenderUpdate as EventListener);
    
    // Initial connection
    client.syncScene().then(() => setIsConnected(true));
    
    return () => {
      client.removeEventListener('sceneUpdate', handleSceneUpdate as EventListener);
      client.removeEventListener('renderUpdate', handleRenderUpdate as EventListener);
    };
  }, [client]);
  
  return (
    <OctaneContext.Provider value={{ client, sceneState, renderState, isConnected }}>
      {children}
    </OctaneContext.Provider>
  );
}

export function useOctaneClient() {
  const context = useContext(OctaneContext);
  if (!context) throw new Error('useOctaneClient must be within OctaneClientProvider');
  return context;
}
```

**Execute batch creation:**
```bash
cd /workspace/grpcSamples/octaneWebR

# Create all base files
mkdir -p client/src/{components,hooks,services,types,utils,styles}

# Create files (use heredoc for each)
cat > client/index.html << 'EOF'
[html code]
EOF

cat > client/src/main.tsx << 'EOF'
[main code]
EOF

# ... repeat for each file

echo "✅ React foundation created"
```

**Deliverable:** React app shell running with Octane API client

---

## 📊 Phase 4: Component Implementation (4 hours)

### 4.1 CallbackRenderViewport (CRITICAL - 1 hour)

Port from `octaneWeb/js/components/CallbackRenderViewport.js`:

```typescript
import React, { useRef, useEffect, useState } from 'react';
import { useOctaneClient } from '../hooks/useOctaneClient';

export function CallbackRenderViewport() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const { client } = useOctaneClient();
  const [ws, setWs] = useState<WebSocket | null>(null);
  const glRef = useRef<WebGLRenderingContext | null>(null);
  
  // Setup WebGL
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    const gl = canvas.getContext('webgl2');
    if (!gl) return;
    
    glRef.current = gl;
    
    // Setup WebGL texture, shaders, etc.
    // Port from CallbackRenderViewport.js setupWebGL()
    
  }, []);
  
  // Setup WebSocket for callbacks
  useEffect(() => {
    const websocket = new WebSocket('ws://localhost:51024/api/callbacks');
    
    websocket.onmessage = (event) => {
      const message = JSON.parse(event.data);
      if (message.type === 'newImage') {
        updateTexture(message.data);
      }
    };
    
    setWs(websocket);
    
    return () => websocket.close();
  }, []);
  
  // Setup mouse camera control
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    let isDragging = false;
    let lastX = 0, lastY = 0;
    
    const handleMouseDown = (e: MouseEvent) => {
      isDragging = true;
      lastX = e.clientX;
      lastY = e.clientY;
    };
    
    const handleMouseMove = (e: MouseEvent) => {
      if (!isDragging) return;
      
      const deltaX = e.clientX - lastX;
      const deltaY = e.clientY - lastY;
      
      // Calculate new camera position (port from octaneWeb)
      // client.setCameraPosition(...)
      
      lastX = e.clientX;
      lastY = e.clientY;
    };
    
    const handleMouseUp = () => {
      isDragging = false;
    };
    
    canvas.addEventListener('mousedown', handleMouseDown);
    canvas.addEventListener('mousemove', handleMouseMove);
    canvas.addEventListener('mouseup', handleMouseUp);
    
    return () => {
      canvas.removeEventListener('mousedown', handleMouseDown);
      canvas.removeEventListener('mousemove', handleMouseMove);
      canvas.removeEventListener('mouseup', handleMouseUp);
    };
  }, [client]);
  
  const updateTexture = (frame: any) => {
    const gl = glRef.current;
    if (!gl) return;
    
    // Port HDR buffer processing from CallbackRenderViewport.js
    // This is CRITICAL - must match exactly
  };
  
  return (
    <div className="callback-render-viewport">
      <canvas ref={canvasRef} width={1920} height={1080} />
    </div>
  );
}
```

### 4.2 SceneOutliner (45 min)

Port from `octaneWeb/js/components/SceneOutlinerSync.js`:

```typescript
import React, { useState } from 'react';
import { useOctaneClient } from '../hooks/useOctaneClient';

interface TreeNodeProps {
  node: any;
  depth: number;
}

function TreeNode({ node, depth }: TreeNodeProps) {
  const [isExpanded, setIsExpanded] = useState(false);
  const { client } = useOctaneClient();
  
  return (
    <div className="tree-node" style={{ paddingLeft: `${depth * 20}px` }}>
      {node.children?.length > 0 && (
        <button onClick={() => setIsExpanded(!isExpanded)}>
          {isExpanded ? '▼' : '▶'}
        </button>
      )}
      <span className="node-name">{node.name}</span>
      <button onClick={() => client.toggleNodeVisibility(node.id)}>
        {node.visible ? '👁' : '👁‍🗨'}
      </button>
      
      {isExpanded && node.children?.map((child: any) => (
        <TreeNode key={child.id} node={child} depth={depth + 1} />
      ))}
    </div>
  );
}

export function SceneOutliner() {
  const { sceneState } = useOctaneClient();
  
  return (
    <div className="scene-outliner">
      <h3>Scene Outliner</h3>
      {sceneState.hierarchy.map((node: any) => (
        <TreeNode key={node.id} node={node} depth={0} />
      ))}
    </div>
  );
}
```

### 4.3 NodeInspector (45 min)

Port from `octaneWeb/js/components/NodeInspector.js`:

```typescript
import React from 'react';
import { useOctaneClient } from '../hooks/useOctaneClient';

export function NodeInspector() {
  const { sceneState, client } = useOctaneClient();
  const selectedNode = sceneState.selection?.[0];
  
  if (!selectedNode) {
    return <div className="node-inspector">No selection</div>;
  }
  
  return (
    <div className="node-inspector">
      <h3>{selectedNode.name}</h3>
      {selectedNode.properties?.map((prop: any) => (
        <div key={prop.name} className="property-row">
          <label>{prop.name}</label>
          <input
            type={prop.type === 'float' ? 'number' : 'text'}
            value={prop.value}
            onChange={(e) => client.setNodeProperty(
              selectedNode.id,
              prop.name,
              e.target.value
            )}
          />
        </div>
      ))}
    </div>
  );
}
```

### 4.4 RenderToolbar (30 min)

```typescript
import React from 'react';
import { useOctaneClient } from '../hooks/useOctaneClient';

export function RenderToolbar() {
  const { client, renderState } = useOctaneClient();
  
  return (
    <div className="render-toolbar">
      <button onClick={() => client.startRender()}>▶ Start</button>
      <button onClick={() => client.stopRender()}>■ Stop</button>
      <button onClick={() => client.pauseRender()}>⏸ Pause</button>
      <button onClick={() => client.restartRender()}>↻ Restart</button>
      
      <div className="render-status">
        <span>Samples: {renderState.samples}</span>
        <span>Time: {renderState.time}s</span>
      </div>
    </div>
  );
}
```

### 4.5 Batch Create All Components

```bash
cd /workspace/grpcSamples/octaneWebR/client/src/components

# Create all component files
for component in CallbackRenderViewport SceneOutliner NodeInspector RenderToolbar; do
  cat > ${component}.tsx << EOF
// Port from octaneWeb/js/components/${component}.js
import React from 'react';
import { useOctaneClient } from '../hooks/useOctaneClient';

export function ${component}() {
  const { client, sceneState } = useOctaneClient();
  
  return (
    <div className="${component}">
      {/* TODO: Implement */}
    </div>
  );
}
EOF
done

echo "✅ Component shells created - now implement each"
```

**Deliverable:** All 7 components ported and working

---

## 📊 Phase 5: Integration & Testing (1.5 hours)

### 5.1 Start Everything

```bash
cd /workspace/grpcSamples/octaneWebR

# Terminal 1: Start development servers
npm run dev

# Wait for both to start
sleep 5

# Test health
curl http://localhost:51024/api/health
```

### 5.2 Validation Tests

```bash
# Test gRPC connection
curl -X POST http://localhost:51024/api/grpc/ApiProjectManager/getPing \
  -H "Content-Type: application/json" \
  -d '{}'

# Test scene sync
curl -X POST http://localhost:51024/api/grpc/ApiProjectManager/getSceneInfo \
  -H "Content-Type: application/json" \
  -d '{}'

# Open in browser
echo "✅ Open http://localhost:5173 to test"
```

### 5.3 Visual Comparison Checklist

Compare side-by-side with octaneWeb:

```bash
# Start octaneWeb for comparison
cd /workspace/grpcSamples/octaneWeb
bash start_servers.bat &
```

**Manual verification:**
- [ ] Same color scheme
- [ ] Same panel layouts
- [ ] Same fonts and sizes
- [ ] Render controls work
- [ ] Scene outliner displays
- [ ] Node inspector shows properties
- [ ] Real-time rendering works
- [ ] Mouse camera control works

### 5.4 Create Documentation

```bash
cd /workspace/grpcSamples/octaneWebR

cat > README.md << 'EOF'
# OctaneWebR

React TypeScript port of octaneWeb with Node.js direct gRPC.

## Quick Start

```bash
npm install
npm run generate:proto
npm run dev
```

Open http://localhost:5173

## Requirements

- Node.js 18+
- Octane Standalone with LiveLink enabled (port 51022)

## Architecture

- **Client**: React 18 + TypeScript + Vite (port 5173)
- **Server**: Node.js + Express + @grpc/grpc-js (port 51024)
- **Octane**: gRPC LiveLink (port 51022)

## Development

- `npm run dev` - Start both client and server
- `npm run build` - Build for production
- `npm run generate:proto` - Regenerate protobuf bindings

## Ported Features

- ✅ Real-time callback rendering
- ✅ Scene outliner with tree view
- ✅ Node inspector with property editing
- ✅ Render controls (start/stop/pause/restart)
- ✅ Mouse drag camera synchronization
- ✅ WebSocket callback streaming
EOF

echo "✅ Documentation created"
```

**Deliverable:** Fully working octaneWebR matching octaneWeb functionality

---

## ✅ Final Checklist

### Backend
- [ ] Node.js server running on port 51024
- [ ] gRPC connection to Octane working
- [ ] Generic /api/grpc/:service/:method endpoint
- [ ] WebSocket /api/callbacks working
- [ ] Health check endpoint responding
- [ ] All proto files generated

### Frontend
- [ ] React app running on port 5173
- [ ] CSS ported (matches octaneWeb appearance)
- [ ] OctaneClient service working
- [ ] React Context providing state
- [ ] All 7 components implemented:
  - [ ] CallbackRenderViewport
  - [ ] SceneOutliner  
  - [ ] NodeInspector
  - [ ] NodeGraphEditor
  - [ ] RenderToolbar
  - [ ] MenuSystem
  - [ ] LayoutManager

### Integration
- [ ] End-to-end gRPC calls working
- [ ] Real-time callbacks streaming
- [ ] Mouse camera control working
- [ ] Visual appearance matches octaneWeb
- [ ] All render controls functional
- [ ] Scene synchronization working

### Documentation
- [ ] README.md created
- [ ] Setup instructions clear
- [ ] All scripts in package.json

---

## 🎯 Success Criteria

**You succeed when:**
1. octaneWebR looks identical to octaneWeb
2. All features work the same way
3. No Python dependency (pure Node.js)
4. TypeScript provides full type safety
5. Can build and run with `npm install && npm run dev`

**Time estimate: 8-10 hours for complete port**

---

## 🚨 Critical Implementation Notes

### Must Preserve Exactly:
1. **HDR buffer processing** in CallbackRenderViewport - algorithm from JS file
2. **Camera math** for mouse drag - exact calculations
3. **CSS classes and styles** - pixel-perfect match
4. **gRPC call patterns** - same services/methods/parameters
5. **WebSocket protocol** - same message format

### Can Modernize:
- Component structure (classes → functional components)
- State management (EventSystem → React Context)
- Build tooling (none → Vite)
- Type safety (none → TypeScript)

### Reference Files Priority:
1. `octaneWeb/js/core/OctaneWebClient.js` - YOUR API SPEC
2. `octaneWeb/js/components/CallbackRenderViewport.js` - Critical algorithms
3. `octaneProxy/octane_proxy.py` - gRPC pattern reference
4. `octaneWeb/css/octane-theme.css` - Visual specification

---

## 📞 If Blocked

**gRPC not connecting?**
- Check Octane LiveLink is enabled (Help → LiveLink)
- Verify port 51022 accessible
- Check proto files copied correctly

**Components not rendering?**
- Check React Context provider wraps components
- Verify imports and exports
- Check browser console for errors

**Styling doesn't match?**
- Compare CSS classes used in octaneWeb JS files
- Ensure all active CSS extracted
- Check className assignments match

---

**Execute this mission sequentially. Create all files, test incrementally, validate against octaneWeb. You have all the information needed to succeed. Go! 🚀**
