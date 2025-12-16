# OctaneWebR gRPC Technical Specification

## 🎯 Purpose

This document provides detailed technical specifications for migrating from Python HTTP-to-gRPC proxy to Node.js direct gRPC communication. It's your definitive reference for implementing the backend.

---

## 📊 Architecture Comparison

### Current: Python Proxy Architecture

```
┌─────────────────┐
│  Browser        │
│  (Vanilla JS)   │
└────────┬────────┘
         │ HTTP POST /service/method
         │ JSON: { params: {...} }
         ↓
┌─────────────────────────┐
│  octane_proxy.py        │
│  (Python/aiohttp)       │
│  Port: 51023            │
│                         │
│  1. Parse URL path      │
│  2. Import proto module │
│  3. Create gRPC stub    │
│  4. Build request       │
│  5. Make gRPC call      │
│  6. Return JSON         │
└────────┬────────────────┘
         │ gRPC
         ↓
┌─────────────────┐
│  Octane         │
│  Port: 51022    │
└─────────────────┘
```

### Target: Node.js Direct gRPC

```
┌─────────────────┐
│  Browser        │
│  (React TS)     │
└────────┬────────┘
         │ HTTP POST /api/grpc/:service/:method
         │ JSON: { params: {...} }
         ↓
┌─────────────────────────┐
│  Node.js Server         │
│  (Express/TypeScript)   │
│  Port: 51024            │
│                         │
│  1. Parse route params  │
│  2. Get service stub    │
│  3. Build typed request │
│  4. Make gRPC call      │
│  5. Return JSON         │
└────────┬────────────────┘
         │ gRPC (@grpc/grpc-js)
         ↓
┌─────────────────┐
│  Octane         │
│  Port: 51022    │
└─────────────────┘
```

**Key Differences:**
- No more Python interpreter overhead
- Type-safe gRPC calls (TypeScript)
- Shared type definitions between frontend and backend
- Potentially lower latency (no HTTP → Python → gRPC translation)

---

## 🔧 Node.js gRPC Implementation Guide

### Step 1: Install Dependencies

```bash
cd octaneWebR
npm install @grpc/grpc-js @grpc/proto-loader google-protobuf
npm install --save-dev grpc-tools grpc_tools_node_protoc_ts
```

**Package Purposes:**
- `@grpc/grpc-js`: Pure JavaScript gRPC implementation (no C++ dependencies)
- `@grpc/proto-loader`: Dynamic proto loading at runtime
- `google-protobuf`: Protobuf message serialization
- `grpc-tools`: Protobuf compiler for code generation
- `grpc_tools_node_protoc_ts`: TypeScript plugin for protoc

### Step 2: Generate TypeScript Bindings

**Copy Proto Files:**
```bash
# Copy all proto files from SDK
mkdir -p server/proto
cp ../../sdk/src/api/grpc/protodef/*.proto server/proto/
```

**Create Generation Script:** `scripts/generate-proto.sh`
```bash
#!/bin/bash

PROTO_DIR="./server/proto"
OUT_DIR="./server/src/generated"

# Create output directory
mkdir -p "$OUT_DIR"

# Generate TypeScript definitions and JavaScript implementations
npx grpc_tools_node_protoc \
  --plugin=protoc-gen-ts=./node_modules/.bin/protoc-gen-ts \
  --ts_out=grpc_js:"$OUT_DIR" \
  --js_out=import_style=commonjs,binary:"$OUT_DIR" \
  --grpc_out=grpc_js:"$OUT_DIR" \
  -I "$PROTO_DIR" \
  "$PROTO_DIR"/*.proto

echo "✅ Protobuf generation complete!"
echo "📁 Output: $OUT_DIR"
```

**Run Generation:**
```bash
chmod +x scripts/generate-proto.sh
npm run generate:proto  # Add to package.json scripts
```

**Expected Output:**
```
server/src/generated/
├── apiprojectmanager_pb.js
├── apiprojectmanager_pb.d.ts
├── apiprojectmanager_grpc_pb.js
├── apiprojectmanager_grpc_pb.d.ts
├── apirenderengineservice_pb.js
├── apirenderengineservice_pb.d.ts
├── apirenderengineservice_grpc_pb.js
├── apirenderengineservice_grpc_pb.d.ts
└── [many more...]
```

### Step 3: Create gRPC Client Manager

**File:** `server/src/grpc/client.ts`

```typescript
import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';
import path from 'path';
import { EventEmitter } from 'events';

// Types
export interface GrpcCallOptions {
  timeout?: number;  // milliseconds
  metadata?: grpc.Metadata;
}

export class OctaneGrpcClient extends EventEmitter {
  private channel: grpc.Channel;
  private services: Map<string, any> = new Map();
  private packageDefinition: protoLoader.PackageDefinition | null = null;
  private protoDescriptor: grpc.GrpcObject | null = null;
  
  constructor(
    private octaneHost: string = 'localhost',
    private octanePort: number = 51022
  ) {
    super();
    
    // Create channel to Octane
    this.channel = new grpc.Channel(
      `${this.octaneHost}:${this.octanePort}`,
      grpc.credentials.createInsecure()
    );
    
    console.log(`📡 gRPC channel created to ${this.octaneHost}:${this.octanePort}`);
  }
  
  /**
   * Initialize and load all proto definitions
   */
  async initialize(): Promise<void> {
    try {
      const PROTO_PATH = path.resolve(__dirname, '../proto');
      
      // Load proto definitions with options matching Python implementation
      this.packageDefinition = protoLoader.loadSync(
        [
          // Load all proto files
          `${PROTO_PATH}/apiprojectmanager.proto`,
          `${PROTO_PATH}/apirenderengineservice.proto`,
          `${PROTO_PATH}/apiobjectgraphservice.proto`,
          // Add more as needed
        ],
        {
          keepCase: true,           // Preserve field names
          longs: String,            // Convert longs to strings
          enums: String,            // Convert enums to strings
          defaults: true,           // Set default values
          oneofs: true              // Include oneofs
        }
      );
      
      // Load proto descriptor
      this.protoDescriptor = grpc.loadPackageDefinition(this.packageDefinition);
      
      console.log('✅ Proto definitions loaded successfully');
    } catch (error) {
      console.error('❌ Failed to load proto definitions:', error);
      throw error;
    }
  }
  
  /**
   * Get or create a gRPC service stub
   */
  private getService(serviceName: string): any {
    // Check cache
    if (this.services.has(serviceName)) {
      return this.services.get(serviceName);
    }
    
    if (!this.protoDescriptor) {
      throw new Error('Proto descriptor not loaded. Call initialize() first.');
    }
    
    // Find service in proto descriptor
    // Services are typically under OctaneEngine.Livelink namespace
    let ServiceConstructor: any = null;
    
    // Try multiple namespace patterns (match Python proxy behavior)
    const patterns = [
      `OctaneEngine.Livelink.${serviceName}`,  // Standard pattern
      serviceName,                              // Direct name
    ];
    
    for (const pattern of patterns) {
      ServiceConstructor = this.resolveServicePath(this.protoDescriptor, pattern);
      if (ServiceConstructor) break;
    }
    
    if (!ServiceConstructor) {
      throw new Error(`Service ${serviceName} not found in proto definitions`);
    }
    
    // Create service client
    const service = new ServiceConstructor(
      `${this.octaneHost}:${this.octanePort}`,
      grpc.credentials.createInsecure()
    );
    
    // Cache it
    this.services.set(serviceName, service);
    
    console.log(`✅ Created service stub: ${serviceName}`);
    return service;
  }
  
  /**
   * Resolve service constructor from nested proto descriptor
   */
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
  
  /**
   * Make a gRPC call (matches Python proxy's makeApiCall pattern)
   */
  async callMethod(
    serviceName: string,
    methodName: string,
    params: any = {},
    options: GrpcCallOptions = {}
  ): Promise<any> {
    try {
      console.log(`📤 gRPC call: ${serviceName}.${methodName}`, params);
      
      // Get service stub
      const service = this.getService(serviceName);
      
      // Get method
      const method = service[methodName];
      if (!method || typeof method !== 'function') {
        throw new Error(`Method ${methodName} not found on service ${serviceName}`);
      }
      
      // Build request message
      // If params is empty, use Empty message
      let request: any;
      if (Object.keys(params).length === 0) {
        // Import Empty from google.protobuf
        const { Empty } = require('google-protobuf/google/protobuf/empty_pb');
        request = new Empty();
      } else {
        // Create request from params
        // The method signature tells us the request type
        request = params;
      }
      
      // Setup call options
      const metadata = options.metadata || new grpc.Metadata();
      const deadline = options.timeout
        ? Date.now() + options.timeout
        : Date.now() + 30000; // 30s default
      
      // Make the call
      return new Promise((resolve, reject) => {
        method.call(
          service,
          request,
          metadata,
          { deadline },
          (error: grpc.ServiceError | null, response: any) => {
            if (error) {
              console.error(`❌ gRPC error: ${serviceName}.${methodName}`, error);
              reject(error);
            } else {
              console.log(`✅ gRPC response: ${serviceName}.${methodName}`);
              resolve(response);
            }
          }
        );
      });
    } catch (error) {
      console.error(`❌ gRPC call failed: ${serviceName}.${methodName}`, error);
      throw error;
    }
  }
  
  /**
   * Register a streaming callback (for OnNewImage, etc.)
   */
  async registerCallback(
    callbackType: string,
    handler: (data: any) => void
  ): Promise<string> {
    // Implementation depends on Octane's callback registration API
    // This is a placeholder - refer to callback_streamer.py for exact pattern
    
    const callbackId = `callback_${Date.now()}`;
    
    // Register with Octane using appropriate service method
    // Example: ApiRenderEngineService.registerCallback
    
    this.on(callbackType, handler);
    
    return callbackId;
  }
  
  /**
   * Unregister a callback
   */
  async unregisterCallback(callbackId: string): Promise<void> {
    // Unregister from Octane
    // Remove event listeners
  }
  
  /**
   * Close the gRPC connection
   */
  close(): void {
    this.channel.close();
    this.services.clear();
    console.log('📡 gRPC connection closed');
  }
  
  /**
   * Check connection health
   */
  async checkHealth(): Promise<boolean> {
    try {
      // Try a simple ping call
      await this.callMethod('ApiProjectManager', 'getPing', {});
      return true;
    } catch (error) {
      return false;
    }
  }
}

// Singleton instance
let grpcClientInstance: OctaneGrpcClient | null = null;

export function getGrpcClient(): OctaneGrpcClient {
  if (!grpcClientInstance) {
    grpcClientInstance = new OctaneGrpcClient(
      process.env.OCTANE_HOST || 'localhost',
      parseInt(process.env.OCTANE_PORT || '51022')
    );
  }
  return grpcClientInstance;
}
```

### Step 4: Create Express API Server

**File:** `server/src/index.ts`

```typescript
import express from 'express';
import cors from 'cors';
import { OctaneGrpcClient, getGrpcClient } from './grpc/client';
import { setupCallbackStreaming } from './api/websocket';

const app = express();
const PORT = parseInt(process.env.SERVER_PORT || '51024');

// Middleware
app.use(cors({
  origin: '*',  // Configure based on your needs
  credentials: true
}));
app.use(express.json({ limit: '50mb' }));

// Initialize gRPC client
const grpcClient = getGrpcClient();
grpcClient.initialize().then(() => {
  console.log('✅ gRPC client initialized');
}).catch(error => {
  console.error('❌ Failed to initialize gRPC client:', error);
  process.exit(1);
});

// Health check endpoint
app.get('/api/health', async (req, res) => {
  const isHealthy = await grpcClient.checkHealth();
  res.json({
    status: isHealthy ? 'ok' : 'unhealthy',
    octane: isHealthy ? 'connected' : 'disconnected',
    timestamp: new Date().toISOString()
  });
});

// Generic gRPC endpoint (matches Python proxy pattern)
app.post('/api/grpc/:service/:method', async (req, res) => {
  const { service, method } = req.params;
  const params = req.body;
  
  console.log(`📥 API request: ${service}.${method}`);
  
  try {
    const response = await grpcClient.callMethod(service, method, params);
    
    // Convert response to JSON
    const jsonResponse = response.toObject ? response.toObject() : response;
    
    res.json(jsonResponse);
  } catch (error: any) {
    console.error(`❌ API error: ${service}.${method}`, error);
    
    res.status(500).json({
      error: error.message || 'gRPC call failed',
      service,
      method,
      details: error.details || null
    });
  }
});

// Start HTTP server
const server = app.listen(PORT, () => {
  console.log(`🚀 OctaneWebR server listening on port ${PORT}`);
  console.log(`📡 Connected to Octane on ${process.env.OCTANE_HOST || 'localhost'}:${process.env.OCTANE_PORT || '51022'}`);
});

// Setup WebSocket for callbacks
setupCallbackStreaming(server, grpcClient);

// Graceful shutdown
process.on('SIGTERM', () => {
  console.log('📡 Shutting down server...');
  server.close(() => {
    grpcClient.close();
    console.log('✅ Server shut down gracefully');
    process.exit(0);
  });
});
```

### Step 5: Implement WebSocket Callback Streaming

**File:** `server/src/api/websocket.ts`

```typescript
import { WebSocketServer, WebSocket } from 'ws';
import { Server } from 'http';
import { OctaneGrpcClient } from '../grpc/client';

interface CallbackClient {
  ws: WebSocket;
  callbackIds: Set<string>;
}

export function setupCallbackStreaming(
  server: Server,
  grpcClient: OctaneGrpcClient
): void {
  const wss = new WebSocketServer({
    server,
    path: '/api/callbacks'
  });
  
  const clients: Set<CallbackClient> = new Set();
  
  wss.on('connection', async (ws: WebSocket) => {
    console.log('🔌 Client connected to callback stream');
    
    const client: CallbackClient = {
      ws,
      callbackIds: new Set()
    };
    
    clients.add(client);
    
    // Register OnNewImage callback
    try {
      const callbackId = await grpcClient.registerCallback(
        'OnNewImage',
        (frame: any) => {
          if (ws.readyState === WebSocket.OPEN) {
            ws.send(JSON.stringify({
              type: 'newImage',
              data: frame,
              timestamp: Date.now()
            }));
          }
        }
      );
      
      client.callbackIds.add(callbackId);
      console.log(`✅ Registered OnNewImage callback: ${callbackId}`);
    } catch (error) {
      console.error('❌ Failed to register callback:', error);
      ws.send(JSON.stringify({
        type: 'error',
        message: 'Failed to register callback'
      }));
    }
    
    // Handle client messages
    ws.on('message', (message: Buffer) => {
      try {
        const data = JSON.parse(message.toString());
        console.log('📥 Client message:', data);
        
        // Handle different message types
        switch (data.type) {
          case 'ping':
            ws.send(JSON.stringify({ type: 'pong' }));
            break;
          case 'registerCallback':
            // Register additional callback types
            break;
        }
      } catch (error) {
        console.error('❌ Error handling client message:', error);
      }
    });
    
    // Handle disconnection
    ws.on('close', async () => {
      console.log('🔌 Client disconnected from callback stream');
      
      // Unregister all callbacks for this client
      for (const callbackId of client.callbackIds) {
        try {
          await grpcClient.unregisterCallback(callbackId);
          console.log(`✅ Unregistered callback: ${callbackId}`);
        } catch (error) {
          console.error(`❌ Failed to unregister callback ${callbackId}:`, error);
        }
      }
      
      clients.delete(client);
    });
    
    // Handle errors
    ws.on('error', (error) => {
      console.error('❌ WebSocket error:', error);
    });
  });
  
  console.log('✅ WebSocket callback streaming initialized');
}
```

---

## 🔍 Key gRPC Patterns from Python Proxy

### Pattern 1: Dynamic Service Loading

**Python:**
```python
service_module = importlib.import_module(f'generated.{service_name}_pb2_grpc')
stub_class = getattr(service_module, f'{service_name}Stub')
```

**Node.js Equivalent:**
```typescript
// Using proto-loader (dynamic)
const packageDefinition = protoLoader.loadSync('service.proto', options);
const protoDescriptor = grpc.loadPackageDefinition(packageDefinition);
const service = new protoDescriptor.ServiceName(address, credentials);

// Using generated code (static, type-safe)
import { ServiceNameClient } from './generated/service_grpc_pb';
const service = new ServiceNameClient(address, credentials);
```

### Pattern 2: Request Object Construction

**Python:**
```python
# Get request class
request_class = getattr(service_module, f'{method_name}Request')

# Create request
request = request_class()

# Populate fields
for key, value in params.items():
    setattr(request, key, value)
```

**Node.js Equivalent:**
```typescript
// Using generated code
import { MethodNameRequest } from './generated/service_pb';

const request = new MethodNameRequest();
request.setFieldName(value);

// Or using object syntax if supported
const request = new MethodNameRequest();
request.setFieldName(params.fieldName);
```

### Pattern 3: Empty Request Handling

**Python:**
```python
from google.protobuf.empty_pb2 import Empty

if not params:
    request = Empty()
```

**Node.js Equivalent:**
```typescript
import { Empty } from 'google-protobuf/google/protobuf/empty_pb';

const request = Object.keys(params).length === 0
  ? new Empty()
  : buildRequest(params);
```

### Pattern 4: Response Serialization

**Python:**
```python
from google.protobuf.json_format import MessageToDict

response_dict = MessageToDict(response)
return json.dumps(response_dict)
```

**Node.js Equivalent:**
```typescript
// Most generated code has toObject() method
const responseJson = response.toObject();
return JSON.stringify(responseJson);

// Or for more control
const responseJson = {
  field1: response.getField1(),
  field2: response.getField2()
};
```

---

## 🧪 Testing Your gRPC Implementation

### Test 1: Simple Ping

```typescript
// test-grpc.ts
import { OctaneGrpcClient } from './server/src/grpc/client';

async function testPing() {
  const client = new OctaneGrpcClient();
  await client.initialize();
  
  try {
    const response = await client.callMethod('ApiProjectManager', 'getPing', {});
    console.log('✅ Ping successful:', response);
  } catch (error) {
    console.error('❌ Ping failed:', error);
  }
  
  client.close();
}

testPing();
```

### Test 2: Get Scene Info

```typescript
async function testGetSceneInfo() {
  const client = new OctaneGrpcClient();
  await client.initialize();
  
  try {
    const response = await client.callMethod(
      'ApiProjectManager',
      'getSceneInfo',
      {}
    );
    console.log('✅ Scene info:', response);
  } catch (error) {
    console.error('❌ Get scene info failed:', error);
  }
  
  client.close();
}
```

### Test 3: Set Camera Position

```typescript
async function testSetCamera() {
  const client = new OctaneGrpcClient();
  await client.initialize();
  
  try {
    const response = await client.callMethod(
      'ApiRenderEngineService',
      'setCameraPosition',
      {
        position: { x: 0, y: 5, z: 10 }
      }
    );
    console.log('✅ Camera set:', response);
  } catch (error) {
    console.error('❌ Set camera failed:', error);
  }
  
  client.close();
}
```

---

## 📋 Complete Service/Method Mapping

Based on octaneWeb usage, here are the key services and methods you need to implement:

### ApiProjectManager
```typescript
await client.callMethod('ApiProjectManager', 'getPing', {});
await client.callMethod('ApiProjectManager', 'getSceneInfo', {});
await client.callMethod('ApiProjectManager', 'openProject', { path: '/path/to/scene.orbx' });
await client.callMethod('ApiProjectManager', 'saveProject', { path: '/path/to/scene.orbx' });
```

### ApiRenderEngineService
```typescript
await client.callMethod('ApiRenderEngineService', 'startRendering', {});
await client.callMethod('ApiRenderEngineService', 'stopRendering', {});
await client.callMethod('ApiRenderEngineService', 'pauseRendering', {});
await client.callMethod('ApiRenderEngineService', 'continueRendering', {});
await client.callMethod('ApiRenderEngineService', 'restartRendering', {});
await client.callMethod('ApiRenderEngineService', 'setCameraPosition', { position: {x, y, z} });
await client.callMethod('ApiRenderEngineService', 'setCameraTarget', { target: {x, y, z} });
await client.callMethod('ApiRenderEngineService', 'getCameraInfo', {});
await client.callMethod('ApiRenderEngineService', 'setRenderPriority', { priority: 'high' | 'normal' });
```

### ApiObjectGraphService
```typescript
await client.callMethod('ApiObjectGraphService', 'getObjectTree', {});
await client.callMethod('ApiObjectGraphService', 'getObjectProperties', { objectId });
await client.callMethod('ApiObjectGraphService', 'setObjectProperty', { objectId, propertyName, value });
await client.callMethod('ApiObjectGraphService', 'getNodeGraph', {});
await client.callMethod('ApiObjectGraphService', 'createNode', { nodeType });
await client.callMethod('ApiObjectGraphService', 'deleteNode', { nodeId });
await client.callMethod('ApiObjectGraphService', 'connectNodes', { fromId, toId });
```

---

## 🚨 Common Issues and Solutions

### Issue 1: Proto Loading Errors

**Error:** `Proto file not found`

**Solution:**
```typescript
// Use absolute path
const PROTO_PATH = path.resolve(__dirname, '../proto');

// Ensure all dependencies are included
const packageDefinition = protoLoader.loadSync([
  `${PROTO_PATH}/common.proto`,  // Load dependencies first
  `${PROTO_PATH}/service.proto`
], options);
```

### Issue 2: Service Not Found

**Error:** `Service ApiProjectManager not found`

**Solution:**
```typescript
// Check the exact namespace in .proto file
// File: apiprojectmanager.proto
// package OctaneEngine.Livelink;
// service ApiProjectManager { ... }

// Access it correctly
const service = protoDescriptor.OctaneEngine.Livelink.ApiProjectManager;
```

### Issue 3: Type Conversion Errors

**Error:** `Cannot convert value to protobuf type`

**Solution:**
```typescript
// Ensure types match proto definition
// .proto: message Vector3 { float x = 1; float y = 2; float z = 3; }

// Correct:
{ position: { x: 1.0, y: 2.0, z: 3.0 } }

// Incorrect:
{ position: { x: "1", y: "2", z: "3" } }  // Strings instead of floats
```

### Issue 4: Callback Registration Fails

**Error:** `Callback registration timeout`

**Solution:**
```typescript
// Ensure Octane LiveLink is enabled
// Check Octane Help → LiveLink menu

// Add error handling
try {
  await grpcClient.registerCallback('OnNewImage', handler);
} catch (error) {
  console.error('Callback registration failed - is LiveLink enabled?');
}
```

---

## ✅ Validation Checklist

Before considering your gRPC implementation complete:

- [ ] All proto files copied from sdk/
- [ ] TypeScript bindings generated without errors
- [ ] OctaneGrpcClient class created
- [ ] Connection to Octane working (test with getPing)
- [ ] Generic callMethod() function working
- [ ] Express server running
- [ ] Generic /api/grpc/:service/:method endpoint working
- [ ] WebSocket /api/callbacks endpoint created
- [ ] Callback registration/unregistration working
- [ ] Error handling implemented
- [ ] Health check endpoint working
- [ ] Graceful shutdown implemented
- [ ] All services used by octaneWeb tested
- [ ] Type safety enforced (no `any` types where avoidable)
- [ ] Logging comprehensive but not excessive
- [ ] Environment variables for configuration

---

## 📚 Additional Resources

### gRPC Node.js Documentation
- Official guide: https://grpc.io/docs/languages/node/
- @grpc/grpc-js: https://github.com/grpc/grpc-node
- Proto loader: https://github.com/grpc/grpc-node/tree/master/packages/proto-loader

### Reference Implementations
- Python proxy: `/workspace/grpcSamples/octaneProxy/octane_proxy.py`
- Callback streaming: `/workspace/grpcSamples/octaneProxy/callback_streamer.py`
- OctaneWeb client: `/workspace/grpcSamples/octaneWeb/js/core/OctaneWebClient.js`

### Proto Files
- Location: `/workspace/grpcSamples/sdk/src/api/grpc/protodef/`
- Documentation: Check .proto files for message/service definitions

---

**Remember:** Your Node.js implementation should behave identically to the Python proxy from the frontend's perspective. The API contract must remain the same.

Good luck with your implementation! 🚀
