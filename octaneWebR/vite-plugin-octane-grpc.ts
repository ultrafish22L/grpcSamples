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
    
    const coreProtoFiles = [
      'common.proto',
      'apiprojectmanager.proto',
      'livelink.proto',
      'apirender.proto',
      'callback.proto',
      'apiitemarray.proto',
      'apinodearray.proto',
      'apinodesystem.proto',
      'apinodegraph.proto',
      'octaneenums.proto',
      'octaneids.proto',
      'apisceneoutliner.proto'
    ].map(f => path.join(PROTO_PATH, f)).filter(f => fs.existsSync(f));
    
    if (coreProtoFiles.length === 0) {
      console.log('⚠️  No proto files found at:', PROTO_PATH);
      return;
    }
    
    console.log(`📦 Loading ${coreProtoFiles.length} proto files...`);
    
    try {
      this.packageDefinition = protoLoader.loadSync(coreProtoFiles, {
        keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true,
        includeDirs: [PROTO_PATH]
      });
      
      this.protoDescriptor = grpc.loadPackageDefinition(this.packageDefinition);
      console.log('✅ Proto definitions loaded');
    } catch (error: any) {
      console.log('⚠️  Could not load proto files:', error.message);
    }
  }
  
  private loadServiceProto(serviceName: string): any {
    const PROTO_PATH = path.resolve(__dirname, './server/proto');
    
    const serviceToProtoMap: Record<string, string> = {
      'ApiItemService': 'apinodesystem_3.proto',
      'ApiItem': 'apinodesystem_3.proto',
      'ApiNodeGraphService': 'apinodesystem_6.proto',
      'ApiNodeGraph': 'apinodesystem_6.proto',
      'ApiItemArrayService': 'apinodesystem_1.proto',
      'ApiItemArray': 'apinodesystem_1.proto',
      'ApiNodeService': 'apinodesystem_7.proto',
      'ApiNode': 'apinodesystem_7.proto',
      'ApiNodeArray': 'apinodesystem_5.proto',
      'ApiRenderEngine': 'apirender.proto',
      'ApiSceneOutliner': 'apisceneoutliner.proto',
    };
    
    const protoFileName = serviceToProtoMap[serviceName] || (serviceName.toLowerCase() + '.proto');
    const protoFilePath = path.join(PROTO_PATH, protoFileName);
    
    if (!fs.existsSync(protoFilePath)) {
      return null;
    }
    
    try {
      const packageDefinition = protoLoader.loadSync([protoFilePath], {
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
              const params = body ? JSON.parse(body) : {};
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
    
    closeBundle() {
      if (grpcClient) {
        grpcClient.close();
      }
      if (wss) {
        wss.close();
      }
    }
  };
}
