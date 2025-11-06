# gRPC Communication Alternatives for OctaneWeb2

## Current Architecture

```
Browser (React/JS) → HTTP/JSON → Python Proxy → gRPC → Octane Standalone
                                  (Port 51023)        (Port 51022)
```

**What we have now:**
- Custom Python proxy (`octane_proxy.py`) that translates HTTP requests to gRPC calls
- JSON serialization for requests/responses
- Server-Sent Events (SSE) for callback streaming
- Works well, battle-tested, stable

---

## Alternative Approaches

### Option 1: gRPC-Web (Official Google Solution) ⭐ **RECOMMENDED**

**Architecture:**
```
Browser (React/TypeScript) → gRPC-Web → Proxy → gRPC → Octane
                            (binary/text)    (Envoy)   (native)
```

**How it works:**
- Browser uses gRPC-Web protocol (subset of gRPC for browsers)
- Envoy proxy or grpcwebproxy translates gRPC-Web ↔ native gRPC
- TypeScript code generated directly from `.proto` files
- Binary protocol (more efficient than JSON)

**Pros:**
- ✅ Official standard from Google
- ✅ Type-safe: Generate TypeScript client from `.proto` files
- ✅ Better performance (binary vs JSON)
- ✅ Automatic type validation
- ✅ Streaming support (unary, server streaming, client streaming)
- ✅ No custom serialization code
- ✅ Industry standard (used by Google Cloud, etc.)

**Cons:**
- ❌ Need to run Envoy proxy (additional dependency)
- ❌ More complex setup than Python proxy
- ❌ Need to compile `.proto` files for TypeScript
- ❌ Learning curve for gRPC-Web

**Setup:**

1. **Install gRPC-Web dependencies:**
```bash
npm install grpc-web @types/google-protobuf
npm install -D grpc-tools grpc_tools_node_protoc_ts
```

2. **Generate TypeScript client from .proto files:**
```bash
# Script to generate TypeScript from proto files
cd /workspace/grpcSamples/sdk/src/api/grpc/protodef

protoc \
  --plugin=protoc-gen-ts=./node_modules/.bin/protoc-gen-ts \
  --js_out=import_style=commonjs:./src/generated \
  --grpc-web_out=import_style=typescript,mode=grpcwebtext:./src/generated \
  *.proto
```

3. **Run Envoy proxy (Docker):**
```yaml
# docker-compose.yml
services:
  envoy:
    image: envoyproxy/envoy:v1.28-latest
    ports:
      - "8080:8080"  # HTTP/gRPC-Web port
      - "9901:9901"  # Admin interface
    volumes:
      - ./envoy.yaml:/etc/envoy/envoy.yaml
    command: /usr/local/bin/envoy -c /etc/envoy/envoy.yaml
```

```yaml
# envoy.yaml
static_resources:
  listeners:
  - name: listener_0
    address:
      socket_address:
        address: 0.0.0.0
        port_value: 8080
    filter_chains:
    - filters:
      - name: envoy.filters.network.http_connection_manager
        typed_config:
          "@type": type.googleapis.com/envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager
          codec_type: AUTO
          stat_prefix: ingress_http
          access_log:
          - name: envoy.access_loggers.stdout
            typed_config:
              "@type": type.googleapis.com/envoy.extensions.access_loggers.stream.v3.StdoutAccessLog
          http_filters:
          - name: envoy.filters.http.grpc_web
            typed_config:
              "@type": type.googleapis.com/envoy.extensions.filters.http.grpc_web.v3.GrpcWeb
          - name: envoy.filters.http.cors
            typed_config:
              "@type": type.googleapis.com/envoy.extensions.filters.http.cors.v3.Cors
          - name: envoy.filters.http.router
            typed_config:
              "@type": type.googleapis.com/envoy.extensions.filters.http.router.v3.Router
          route_config:
            name: local_route
            virtual_hosts:
            - name: local_service
              domains: ["*"]
              routes:
              - match:
                  prefix: "/"
                route:
                  cluster: octane_grpc
                  timeout: 0s
                  max_stream_duration:
                    grpc_timeout_header_max: 0s
              cors:
                allow_origin_string_match:
                - prefix: "*"
                allow_methods: GET, PUT, DELETE, POST, OPTIONS
                allow_headers: keep-alive,user-agent,cache-control,content-type,content-transfer-encoding,custom-header-1,x-accept-content-transfer-encoding,x-accept-response-streaming,x-user-agent,x-grpc-web,grpc-timeout
                max_age: "1728000"
                expose_headers: custom-header-1,grpc-status,grpc-message
  clusters:
  - name: octane_grpc
    type: LOGICAL_DNS
    connect_timeout: 0.25s
    dns_lookup_family: V4_ONLY
    typed_extension_protocol_options:
      envoy.extensions.upstreams.http.v3.HttpProtocolOptions:
        "@type": type.googleapis.com/envoy.extensions.upstreams.http.v3.HttpProtocolOptions
        explicit_http_config:
          http2_protocol_options: {}
    load_assignment:
      cluster_name: octane_grpc
      endpoints:
      - lb_endpoints:
        - endpoint:
            address:
              socket_address:
                address: host.docker.internal  # or localhost
                port_value: 51022
```

4. **Use in React:**
```typescript
// src/api/octaneClient.ts
import { RenderServerInfoClient } from './generated/livelink_grpc_web_pb'
import { GetServerInfoRequest } from './generated/livelink_pb'

class OctaneClient {
  private client: RenderServerInfoClient
  
  constructor() {
    this.client = new RenderServerInfoClient('http://localhost:8080')
  }
  
  async getServerInfo() {
    const request = new GetServerInfoRequest()
    
    try {
      const response = await this.client.getServerInfo(request, {})
      return {
        version: response.getVersion(),
        buildDate: response.getBuildDate(),
        // Fully typed!
      }
    } catch (error) {
      console.error('gRPC error:', error)
      throw error
    }
  }
  
  // Server streaming example (for callbacks)
  registerCallback(callbackType: string) {
    const request = new RegisterCallbackRequest()
    request.setCallbackType(callbackType)
    
    const stream = this.client.registerCallback(request, {})
    
    stream.on('data', (response) => {
      const imageData = response.getImageData()
      // Handle callback
    })
    
    stream.on('error', (error) => {
      console.error('Stream error:', error)
    })
    
    stream.on('end', () => {
      console.log('Stream ended')
    })
    
    return stream
  }
}
```

**Verdict**: ⭐ **Best long-term solution** if you're willing to set up Envoy

---

### Option 2: Connect-Web (Modern gRPC Alternative)

**Architecture:**
```
Browser (React/TypeScript) → Connect Protocol → Proxy → gRPC → Octane
                            (HTTP/JSON or binary)
```

**What is Connect?**
- Modern RPC framework from Buf (https://buf.build/docs/connect)
- Compatible with gRPC servers
- Better TypeScript support than gRPC-Web
- Simpler than gRPC-Web

**Pros:**
- ✅ Simpler than gRPC-Web
- ✅ Better TypeScript experience
- ✅ Works with existing gRPC servers
- ✅ Generated TypeScript code is cleaner
- ✅ Built-in retry logic and error handling

**Cons:**
- ❌ Still needs proxy (Connect proxy or Envoy)
- ❌ Less mature than gRPC-Web
- ❌ Smaller community

**Setup:**
```bash
npm install @connectrpc/connect @connectrpc/connect-web
npm install -D @bufbuild/buf @bufbuild/protoc-gen-es @connectrpc/protoc-gen-connect-es
```

**Usage:**
```typescript
import { createPromiseClient } from "@connectrpc/connect"
import { createGrpcWebTransport } from "@connectrpc/connect-web"
import { RenderServerInfo } from "./generated/livelink_connect"

const transport = createGrpcWebTransport({
  baseUrl: "http://localhost:8080",
})

const client = createPromiseClient(RenderServerInfo, transport)

// Use it (fully typed)
const response = await client.getServerInfo({})
console.log(response.version)
```

**Verdict**: 🟡 **Good alternative to gRPC-Web**, but adds another tool to learn

---

### Option 3: Keep Python Proxy, Add WebSocket Streaming

**Architecture:**
```
Browser (React/JS) → HTTP/JSON + WebSocket → Python Proxy → gRPC → Octane
                                            (improved)
```

**Improvements to current setup:**
- Replace SSE with WebSocket for bidirectional streaming
- Add request batching
- Add connection pooling
- Better error handling

**Pros:**
- ✅ Keep what's working
- ✅ No new dependencies (Envoy, etc.)
- ✅ Familiar HTTP/JSON API
- ✅ Easy to debug
- ✅ Can add features incrementally

**Cons:**
- ❌ Still doing JSON serialization (slower than binary)
- ❌ Not type-safe (no .proto enforcement)
- ❌ Manual error mapping
- ❌ Custom protocol (not standard)

**Improvements:**
```python
# octane_proxy_improved.py
import asyncio
import websockets
from aiohttp import web

class OctaneProxyImproved:
    def __init__(self):
        self.grpc_client = OctaneGrpcClient()
        self.websocket_connections = {}
    
    async def handle_websocket(self, request):
        ws = web.WebSocketResponse()
        await ws.prepare(request)
        
        connection_id = str(uuid.uuid4())
        self.websocket_connections[connection_id] = ws
        
        try:
            async for msg in ws:
                if msg.type == web.WSMsgType.TEXT:
                    data = json.loads(msg.data)
                    
                    # Handle different message types
                    if data['type'] == 'rpc':
                        response = await self.handle_rpc(data)
                        await ws.send_json(response)
                    
                    elif data['type'] == 'subscribe_callback':
                        await self.subscribe_callback(connection_id, data['callbackType'])
        
        finally:
            del self.websocket_connections[connection_id]
        
        return ws
    
    async def subscribe_callback(self, connection_id, callback_type):
        """Stream callbacks to WebSocket client"""
        callback_id = await self.grpc_client.register_callback(callback_type)
        
        async for callback_data in self.grpc_client.stream_callbacks(callback_id):
            ws = self.websocket_connections.get(connection_id)
            if ws and not ws.closed:
                await ws.send_json({
                    'type': 'callback',
                    'data': callback_data
                })
```

**Verdict**: 🟢 **Easiest path forward**, improves what you have

---

### Option 4: Electron App with Node.js gRPC

**Architecture:**
```
Electron App → Native Node.js gRPC → Octane
(Chromium + Node.js)
```

**What changes:**
- Build Electron desktop app instead of web app
- Use native Node.js `@grpc/grpc-js` (no proxy needed!)
- Direct gRPC connection to Octane

**Pros:**
- ✅ No proxy needed at all
- ✅ Native gRPC performance
- ✅ Can use all Node.js modules
- ✅ Desktop app with native features (file system, etc.)

**Cons:**
- ❌ No longer a web app (requires installation)
- ❌ More complex build/distribution
- ❌ Loses web deployment benefits
- ❌ Larger download size

**Setup:**
```bash
npm install electron @grpc/grpc-js @grpc/proto-loader
```

**Usage:**
```typescript
// main.ts (Node.js process)
import * as grpc from '@grpc/grpc-js'
import * as protoLoader from '@grpc/proto-loader'

const packageDefinition = protoLoader.loadSync('livelink.proto')
const proto = grpc.loadPackageDefinition(packageDefinition)

const client = new proto.octane.render.RenderServerInfo(
  'localhost:51022',
  grpc.credentials.createInsecure()
)

client.getServerInfo({}, (error, response) => {
  if (error) {
    console.error(error)
  } else {
    console.log(response)
  }
})
```

**Verdict**: 🔴 **Only if you want a desktop app**, loses web benefits

---

## Performance Comparison

| Approach | Latency | Throughput | Type Safety | Setup Complexity |
|----------|---------|------------|-------------|------------------|
| **Current (Python Proxy + JSON)** | ~5-10ms | ~50 MB/s | ❌ No | ⭐ Simple |
| **gRPC-Web + Envoy** | ~2-5ms | ~200 MB/s | ✅ Yes | ⭐⭐⭐ Complex |
| **Connect-Web** | ~2-5ms | ~200 MB/s | ✅ Yes | ⭐⭐ Medium |
| **Improved Python Proxy** | ~4-8ms | ~70 MB/s | ❌ No | ⭐ Simple |
| **Electron + Native gRPC** | ~1-2ms | ~500 MB/s | ✅ Yes | ⭐⭐⭐⭐ Very Complex |

---

## Recommendation

### Short Term (Next 2-4 weeks): Keep Python Proxy ✅

**Why:**
- It's working well
- Focus on implementing features, not changing infrastructure
- Can optimize later without affecting React code much

**Small improvements to make:**
1. Add WebSocket endpoint for better streaming
2. Add request batching
3. Add connection pooling
4. Better error messages

### Medium Term (2-3 months): Evaluate gRPC-Web

**Once core features are stable:**
1. Set up Envoy as parallel proxy (both proxies running)
2. Generate TypeScript clients from `.proto` files
3. Migrate one component at a time (start with simple RPCs)
4. Compare performance and developer experience
5. Decide whether to fully migrate

### Long Term (6+ months): Full gRPC-Web Migration

**If benefits are clear:**
1. Remove Python proxy entirely
2. All communication via gRPC-Web
3. Full type safety from `.proto` files
4. Better performance

---

## Migration Path (If You Choose gRPC-Web)

### Phase 1: Proof of Concept (1 week)
- [ ] Set up Envoy proxy
- [ ] Generate TypeScript client for one service (e.g., RenderServerInfo)
- [ ] Test basic RPC call (GetServerInfo)
- [ ] Verify it works alongside Python proxy

### Phase 2: Parallel Implementation (2 weeks)
- [ ] Generate TypeScript clients for all services
- [ ] Create adapter layer to abstract transport
- [ ] Keep Python proxy as fallback
- [ ] Test both paths in parallel

### Phase 3: Gradual Migration (4 weeks)
- [ ] Migrate ConnectionStore to use gRPC-Web
- [ ] Migrate SceneStore to use gRPC-Web
- [ ] Migrate callback streaming to gRPC-Web server streaming
- [ ] Verify performance and stability

### Phase 4: Complete Migration (1 week)
- [ ] Remove Python proxy code paths
- [ ] Update documentation
- [ ] Performance testing
- [ ] Production deployment

---

## Code Example: Abstraction Layer

**To make migration easier, create abstraction:**

```typescript
// src/api/transport.ts
export interface OctaneTransport {
  makeCall<Req, Res>(
    service: string,
    method: string,
    request: Req
  ): Promise<Res>
  
  streamCall<Req, Res>(
    service: string,
    method: string,
    request: Req,
    onData: (data: Res) => void
  ): () => void
}

// Current implementation
class HttpTransport implements OctaneTransport {
  async makeCall<Req, Res>(service: string, method: string, request: Req): Promise<Res> {
    const response = await fetch(`${this.baseUrl}/rpc/${service}/${method}`, {
      method: 'POST',
      body: JSON.stringify(request)
    })
    return response.json()
  }
}

// Future gRPC-Web implementation
class GrpcWebTransport implements OctaneTransport {
  async makeCall<Req, Res>(service: string, method: string, request: Req): Promise<Res> {
    // Use generated gRPC-Web client
    const client = this.getClient(service)
    return client[method](request)
  }
}

// Usage in OctaneClient
class OctaneClient {
  constructor(private transport: OctaneTransport) {}
  
  async getServerInfo() {
    return this.transport.makeCall('RenderServerInfo', 'GetServerInfo', {})
  }
}

// Easy to swap transports
const client = new OctaneClient(new HttpTransport('http://localhost:51023'))
// Later: const client = new OctaneClient(new GrpcWebTransport('http://localhost:8080'))
```

---

## My Recommendation

**For this project, right now:**

1. ✅ **Keep Python proxy** - it's battle-tested and works
2. ✅ **Add abstraction layer** - makes future migration easy
3. ✅ **Focus on features** - implement all the missing functionality first
4. ⏳ **Evaluate gRPC-Web in 2-3 months** - once core features are stable
5. ⏳ **Migrate if beneficial** - only if performance or type safety becomes critical

**Why not migrate now:**
- Python proxy works fine
- gRPC-Web setup is complex (Envoy config, proto compilation, etc.)
- Would delay feature development by 2-3 weeks
- Benefits are incremental, not revolutionary
- Can migrate later without rewriting React components (if you use abstraction layer)

**When to migrate:**
- Performance becomes bottleneck (unlikely with current usage)
- Type safety from `.proto` files becomes critical
- Team has bandwidth for infrastructure work
- Core features are complete and stable

---

## Quick Start: Test gRPC-Web Without Commitment

Want to try it without committing? Here's a minimal test:

```bash
# 1. Install grpcwebproxy (simpler than Envoy for testing)
go install github.com/improbable-eng/grpc-web/go/grpcwebproxy@latest

# 2. Run proxy
grpcwebproxy \
  --backend_addr=localhost:51022 \
  --run_tls_server=false \
  --allow_all_origins \
  --server_http_debug_port=8080

# 3. Test with curl
curl -X POST http://localhost:8080/octane.render.RenderServerInfo/GetServerInfo \
  -H "Content-Type: application/grpc-web-text" \
  -d ""

# If you see a response, it works!
```

Then in React:
```typescript
import { grpc } from "@improbable-eng/grpc-web"

grpc.unary(RenderServerInfo.GetServerInfo, {
  request: new GetServerInfoRequest(),
  host: "http://localhost:8080",
  onEnd: (response) => {
    console.log(response.message)
  }
})
```

---

## Questions to Consider

**Before migrating to gRPC-Web, ask:**

1. **Is JSON serialization actually slow?**
   - Profile your app - is the proxy a bottleneck?
   - Probably not until you're streaming huge amounts of data

2. **Do you need `.proto` type safety?**
   - TypeScript interfaces work fine for most cases
   - Type safety is nice but not essential

3. **Is the team comfortable with gRPC/Protobuf?**
   - Learning curve for debugging, error handling
   - Python proxy is easier to understand

4. **Do you have time for infrastructure work?**
   - 2-3 weeks to set up properly
   - Could be implementing features instead

5. **What's the deployment story?**
   - Envoy is another service to manage
   - Python proxy is one simple script

**My guess:** You'll stick with Python proxy for now, and that's totally fine! 

---

**TL;DR**: Keep Python proxy, focus on features. Evaluate gRPC-Web in a few months when things are stable.
