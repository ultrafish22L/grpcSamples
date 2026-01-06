/**
 * Vite Plugin for Octane gRPC Integration
 * 
 * This plugin integrates gRPC functionality directly into the Vite dev server,
 * eliminating the need for a separate Node.js Express server.
 * 
 * Features:
 * - Direct gRPC calls to Octane LiveLink (127.0.0.1:51022)
 * - WebSocket streaming for OnNewImage callbacks
 * - Health check endpoint
 * - All running within the Vite dev server
 */

import { Plugin, ViteDevServer } from 'vite';
import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';
import { WebSocketServer, WebSocket } from 'ws';
import * as path from 'path';
import * as fs from 'fs';
import { IncomingMessage } from 'http';

interface GrpcCallOptions {
  timeout?: number;
  metadata?: grpc.Metadata;
}

class OctaneGrpcClient {
  private channel: grpc.Channel;
  private services: Map<string, any> = new Map();
  private packageDefinition: protoLoader.PackageDefinition | null = null;
  private protoDescriptor: grpc.GrpcObject | null = null;
  private callbacks: Set<(data: any) => void> = new Set();
  private callbackId: number = 0;
  private isCallbackRegistered: boolean = false;
  private pollingInterval: NodeJS.Timeout | null = null;
  
  constructor(
    private octaneHost: string = process.env.OCTANE_HOST || OctaneGrpcClient.detectDefaultHost(),
    private octanePort: number = parseInt(process.env.OCTANE_PORT || '51022')
  ) {
    const address = `${this.octaneHost}:${this.octanePort}`;
    this.channel = new grpc.Channel(
      address,
      grpc.credentials.createInsecure(),
      {}
    );
    
    const isSandbox = this.octaneHost === 'host.docker.internal';
    console.log(`📡 Vite gRPC Plugin: Connected to Octane at ${address}`);
    if (isSandbox) {
      console.log(`🐳 Using Docker networking (sandbox environment detected)`);
    }
  }

  private static detectDefaultHost(): string {
    // Detect sandbox/Docker environment
    const indicators = [
      fs.existsSync('/.dockerenv'),
      process.env.USER?.toLowerCase().includes('sandbox'),
      process.env.KUBERNETES_SERVICE_HOST !== undefined,
      fs.existsSync('/workspace') // OpenHands indicator
    ];
    
    const isSandbox = indicators.some(indicator => indicator);
    return isSandbox ? 'host.docker.internal' : '127.0.0.1';
  }

  async initialize(): Promise<void> {
    const PROTO_PATH = path.resolve(__dirname, './server/proto');
    
    // Check if proto directory exists
    if (!fs.existsSync(PROTO_PATH)) {
      console.log('⚠️  Proto directory not found:', PROTO_PATH);
      return;
    }
    
    console.log(`📦 Proto files ready for lazy loading from:`, PROTO_PATH);
    console.log('✅ Proto definitions will be loaded on-demand per service');
    
    // Note: We use lazy loading to avoid duplicate name conflicts
    // Each service loads its own proto file when first accessed
  }
  
  private loadServiceProto(serviceName: string): any {
    const PROTO_PATH = path.resolve(__dirname, './server/proto');
    
    const serviceToProtoMap: Record<string, string> = {
      'ApiProjectManager': 'apiprojectmanager.proto',
      'ApiItemService': 'apinodesystem_3.proto',
      'ApiItem': 'apinodesystem_3.proto',
      'ApiNodeGraphService': 'apinodesystem_6.proto',
      'ApiNodeGraph': 'apinodesystem_6.proto',
      'ApiItemArrayService': 'apinodesystem_1.proto',
      'ApiItemArray': 'apinodesystem_1.proto',
      'ApiNodeService': 'apinodesystem_7.proto',
      'ApiNode': 'apinodesystem_7.proto',
      'ApiNodeArray': 'apinodesystem_5.proto',
      'ApiNodePinInfoEx': 'apinodepininfohelper.proto',
      'ApiRenderEngine': 'apirender.proto',
      'ApiSceneOutliner': 'apisceneoutliner.proto',
    };
    
    const protoFileName = serviceToProtoMap[serviceName] || (serviceName.toLowerCase() + '.proto');
    const protoFilePath = path.join(PROTO_PATH, protoFileName);
    
    if (!fs.existsSync(protoFilePath)) {
      return null;
    }
    
    try {
      // Load with dependencies for complex services
      const protoFiles = [protoFilePath];
      
      // ApiRenderEngine needs common.proto and callback.proto
      if (serviceName === 'ApiRenderEngine') {
        const commonProto = path.join(PROTO_PATH, 'common.proto');
        const callbackProto = path.join(PROTO_PATH, 'callback.proto');
        if (fs.existsSync(commonProto)) protoFiles.unshift(commonProto);
        if (fs.existsSync(callbackProto)) protoFiles.push(callbackProto);
      }
      
      const packageDefinition = protoLoader.loadSync(protoFiles, {
        keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true,
        includeDirs: [PROTO_PATH]
      });
      
      return grpc.loadPackageDefinition(packageDefinition);
    } catch (error: any) {
      console.log(`⚠️  Could not load proto for ${serviceName}:`, error.message);
      return null;
    }
  }
  
  private getService(serviceName: string): any {
    if (this.services.has(serviceName)) {
      return this.services.get(serviceName);
    }
    
    let descriptor = this.protoDescriptor;
    
    if (!descriptor) {
      descriptor = this.loadServiceProto(serviceName);
      if (!descriptor) {
        throw new Error(`Could not load proto for service ${serviceName}`);
      }
    }
    
    let ServiceConstructor: any = null;
    const patterns = [
      `octaneapi.${serviceName}Service`,
      `octaneapi.${serviceName}`,
      `livelinkapi.${serviceName}Service`,
      `livelinkapi.${serviceName}`,
      `${serviceName}Service`,
      serviceName
    ];
    
    for (const pattern of patterns) {
      ServiceConstructor = this.resolveServicePath(descriptor, pattern);
      if (ServiceConstructor) {
        break;
      }
    }
    
    if (!ServiceConstructor && descriptor === this.protoDescriptor) {
      const serviceDescriptor = this.loadServiceProto(serviceName);
      if (serviceDescriptor) {
        for (const pattern of patterns) {
          ServiceConstructor = this.resolveServicePath(serviceDescriptor, pattern);
          if (ServiceConstructor) {
            break;
          }
        }
      }
    }
    
    if (!ServiceConstructor || typeof ServiceConstructor !== 'function') {
      throw new Error(`Service ${serviceName} not found in proto definitions`);
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
      if (current && current[part]) {
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
    try {
      const service = this.getService(serviceName);
      const method = service[methodName];
      
      if (!method || typeof method !== 'function') {
        throw new Error(`Method ${methodName} not found in service ${serviceName}`);
      }
      
      const request = Object.keys(params).length === 0 ? {} : params;
      const metadata = options.metadata || new grpc.Metadata();
      const deadline = Date.now() + (options.timeout || 30000);
      
      return new Promise((resolve, reject) => {
        method.call(service, request, metadata, { deadline }, 
          (error: grpc.ServiceError | null, response: any) => {
            if (error) {
              reject(error);
            } else {
              resolve(response);
            }
          }
        );
      });
    } catch (error: any) {
      console.error(`❌ ${serviceName}.${methodName}:`, error.message);
      throw error;
    }
  }
  
  async checkHealth(): Promise<boolean> {
    try {
      // Use rootNodeGraph as a health check - it's a valid lightweight method
      await this.callMethod('ApiProjectManager', 'rootNodeGraph', {}, { timeout: 5000 });
      return true;
    } catch (error) {
      return false;
    }
  }

  async registerOctaneCallbacks(): Promise<void> {
    if (this.isCallbackRegistered) {
      console.log('⚠️  Callbacks already registered');
      return;
    }

    try {
      this.callbackId = Math.floor(Math.random() * 1000000);
      console.log(`📡 Registering OnNewImage callback with ID: ${this.callbackId}`);

      await this.callMethod('ApiRenderEngine', 'setOnNewImageCallback', {
        callback: {
          callbackSource: 'grpc',
          callbackId: this.callbackId
        },
        userData: 0
      });

      console.log(`✅ Callback registered with Octane`);
      this.isCallbackRegistered = true;
//      this.startCallbackPolling();
    } catch (error: any) {
      console.error('❌ Failed to register callback:', error.message);
      console.error('   (Callbacks will not work until Octane is running and LiveLink is enabled)');
    }
  }
/*
  private startCallbackPolling(): void {
    if (this.pollingInterval) {
      return;
    }

    console.log('✅ Starting callback polling (30fps)');
    this.pollingInterval = setInterval(() => this.pollOctaneCallbacks(), 33);
  }

  private async pollOctaneCallbacks(): Promise<void> {
    if (!this.isCallbackRegistered) {
      return;
    }

    try {
      const response = await this.callMethod('ApiRenderEngine', 'getNewImageFromCallback', {
        callbackId: this.callbackId
      }, { timeout: 100 });

      if (response && response.render_images) {
        this.notifyCallbacks(response);
      }
    } catch (error: any) {
      // Silently ignore polling errors (Octane might not have new frames)
    }
  }
*/
  async unregisterOctaneCallbacks(): Promise<void> {
    if (!this.isCallbackRegistered) {
      return;
    }

    try {
      if (this.pollingInterval) {
        clearInterval(this.pollingInterval);
        this.pollingInterval = null;
      }

      await this.callMethod('ApiRenderEngine', 'setOnNewImageCallback', {
        callback: null,
        userData: 0
      });

      console.log('✅ Callbacks unregistered');
      this.isCallbackRegistered = false;
      this.callbackId = 0;
    } catch (error: any) {
      console.error('❌ Failed to unregister callback:', error.message);
    }
  }

  registerCallback(callback: (data: any) => void): void {
    this.callbacks.add(callback);
  }

  unregisterCallback(callback: (data: any) => void): void {
    this.callbacks.delete(callback);
  }

  private notifyCallbacks(data: any): void {
    this.callbacks.forEach(callback => {
      try {
        callback(data);
      } catch (error) {
        console.error('❌ Error in callback handler:', error);
      }
    });
  }

  close(): void {
    this.channel.close();
    this.services.clear();
  }
}

export function octaneGrpcPlugin(): Plugin {
  let grpcClient: OctaneGrpcClient | null = null;
  let wss: WebSocketServer | null = null;

  return {
    name: 'vite-plugin-octane-grpc',
    
    async configureServer(server: ViteDevServer) {
      // Initialize gRPC client
      grpcClient = new OctaneGrpcClient();
      await grpcClient.initialize();
      
      // Register Octane callbacks
      try {
        await grpcClient.registerOctaneCallbacks();
      } catch (error: any) {
        console.error('⚠️  Initial callback registration failed:', error.message);
      }
      
      // Setup WebSocket server for callbacks
      wss = new WebSocketServer({ noServer: true });
      
      wss.on('connection', (ws: WebSocket) => {
        console.log('🔌 WebSocket client connected');
        
        const callbackHandler = (data: any) => {
          try {
            ws.send(JSON.stringify({ type: 'newImage', data }));
          } catch (error) {
            console.error('❌ Error sending WebSocket message:', error);
          }
        };
        
        grpcClient?.registerCallback(callbackHandler);
        
        ws.on('close', () => {
          console.log('🔌 WebSocket client disconnected');
          grpcClient?.unregisterCallback(callbackHandler);
        });
        
        ws.on('message', (message: string) => {
          try {
            const data = JSON.parse(message.toString());
            if (data.type === 'subscribe') {
              console.log('📡 Client subscribed to callbacks');
            }
          } catch (error) {
            console.error('❌ Error parsing WebSocket message:', error);
          }
        });
      });
      
      // Handle WebSocket upgrade
      server.httpServer?.on('upgrade', (request: IncomingMessage, socket, head) => {
        const url = request.url;
        if (url === '/api/callbacks') {
          wss?.handleUpgrade(request, socket, head, (ws) => {
            wss?.emit('connection', ws, request);
          });
        }
      });
      
      // Add API endpoints
      server.middlewares.use((req, res, next) => {
        const url = req.url;
        
        // Health check endpoint
        if (url === '/api/health') {
          (async () => {
            try {
              const isHealthy = await grpcClient?.checkHealth();
              res.setHeader('Content-Type', 'application/json');
              res.statusCode = 200;
              res.end(JSON.stringify({
                status: isHealthy ? 'ok' : 'unhealthy',
                octane: isHealthy ? 'connected' : 'disconnected',
                server: 'vite',
                timestamp: new Date().toISOString()
              }));
            } catch (error: any) {
              res.setHeader('Content-Type', 'application/json');
              res.statusCode = 500;
              res.end(JSON.stringify({
                status: 'error',
                error: error.message,
                timestamp: new Date().toISOString()
              }));
            }
          })();
          return;
        }
        
        // Client logging endpoint
        if (url === '/api/log' && req.method === 'POST') {
          let body = '';
          req.on('data', chunk => body += chunk);
          req.on('end', () => {
            try {
              const logData = JSON.parse(body);
              const timestamp = new Date().toISOString();
              const logLine = `[${timestamp}] [${logData.level}] ${logData.message}\n`;
              
              // Append to log file
              fs.appendFileSync('/tmp/octaneWebR_client.log', logLine);
              
              // Also log to console with appropriate color
              if (logData.level === 'error') {
                console.error('🔴 CLIENT:', logData.message);
              } else if (logData.level === 'warn') {
                console.warn('🟡 CLIENT:', logData.message);
              } else {
                console.log('🟢 CLIENT:', logData.message);
              }
              
              res.setHeader('Content-Type', 'application/json');
              res.statusCode = 200;
              res.end(JSON.stringify({ success: true }));
            } catch (error: any) {
              console.error('❌ Failed to write client log:', error.message);
              res.statusCode = 500;
              res.end(JSON.stringify({ success: false, error: error.message }));
            }
          });
          return;
        }
/*
📤 ApiItem.getByAttrID {"item_ref":{"handle":"1000588","type":16},"attribute_id":185,"expected_type":"AT_FLOAT4"}
📤 ApiItem.getByAttrID {"item_ref":{"handle":"1000590","type":16},"attribute_id":185,"expected_type":"AT_INT4"}
📤 ApiItem.getByAttrID {"item_ref":{"handle":"1000592","type":16},"attribute_id":185,"expected_type":"AT_FLOAT4"}
📤 ApiItem.getByAttrID {"item_ref":{"handle":"1000594","type":16},"attribute_id":185,"expected_type":"AT_FLOAT4"}
📤 ApiItem.getByAttrID {"item_ref":{"handle":"1000596","type":16},"attribute_id":185,"expected_type":"AT_BOOL"}
📤 ApiItem.getByAttrID {"item_ref":{"handle":"1000598","type":16},"attribute_id":185,"expected_type":"AT_FLOAT4"}
❌ API error: ApiItem.getByAttrID: 3 INVALID_ARGUMENT: Unsupported or missing expected_type
❌ API error: ApiItem.getByAttrID: 3 INVALID_ARGUMENT: Unsupported or missing expected_type
❌ API error: ApiItem.getByAttrID: 3 INVALID_ARGUMENT: Unsupported or missing expected_type
❌ API error: ApiItem.getByAttrID: 3 INVALID_ARGUMENT: Unsupported or missing expected_type
❌ API error: ApiItem.getByAttrID: 3 INVALID_ARGUMENT: Unsupported or missing expected_type
❌ API error: ApiItem.getByAttrID: 3 INVALID_ARGUMENT: Unsupported or missing expected_type
*/        
        // gRPC proxy endpoint
        const grpcMatch = url?.match(/^\/api\/grpc\/([^\/]+)\/([^\/\?]+)/);
        if (grpcMatch && req.method === 'POST') {
          const [, service, method] = grpcMatch;
          
          let body = '';
          req.on('data', chunk => {
            body += chunk.toString();
          });
          
          req.on('end', async () => {
            try {
              let params = body ? JSON.parse(body) : {};
              
              // Parameter remapping (to match Python proxy behavior)
              // Some proto messages use different field names than what the client sends
              if (params.objectPtr) {
                if (service === 'ApiNodePinInfoEx' && method === 'getApiNodePinInfo') {
                  // GetNodePinInfoRequest uses nodePinInfoRef instead of objectPtr
                  params = { nodePinInfoRef: params.objectPtr };
                } else if (method === 'getByAttrID' || method === 'getValue') {
                  // Some methods use item_ref instead of objectPtr
                  params = { item_ref: params.objectPtr, ...params };
                  delete params.objectPtr;
                }
              }
              
              console.log(`📤 ${service}.${method}`, JSON.stringify(params).substring(0, 100));
              const response = await grpcClient?.callMethod(service, method, params);
              console.log(`✅ ${service}.${method} → ${JSON.stringify(response).substring(0, 100)}`);
              
              res.setHeader('Content-Type', 'application/json');
              res.statusCode = 200;
              res.end(JSON.stringify(response || {}));
            } catch (error: any) {
              console.error(`❌ API error: ${service}.${method}:`, error.message);
              res.setHeader('Content-Type', 'application/json');
              res.statusCode = 500;
              res.end(JSON.stringify({
                error: error.message || 'gRPC call failed',
                service,
                method,
                code: error.code || 'UNKNOWN'
              }));
            }
          });
          
          return;
        }
        
        next();
      });
      
      console.log('✅ Octane gRPC Plugin configured');
      console.log('   • HTTP API: /api/grpc/:service/:method');
      console.log('   • WebSocket: /api/callbacks');
      console.log('   • Health: /api/health');
    },
    
    async closeBundle() {
      if (grpcClient) {
        try {
          await grpcClient.unregisterOctaneCallbacks();
        } catch (error) {
          console.error('❌ Error unregistering callbacks:', error);
        }
        grpcClient.close();
      }
      if (wss) {
        wss.close();
      }
    }
  };
}
