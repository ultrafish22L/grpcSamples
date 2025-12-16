import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';
import path from 'path';
import { EventEmitter } from 'events';
import * as fs from 'fs';

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
    private octaneHost: string = process.env.OCTANE_HOST || OctaneGrpcClient.detectDefaultHost(),
    private octanePort: number = parseInt(process.env.OCTANE_PORT || '51022')
  ) {
    super();
    
    const address = `${this.octaneHost}:${this.octanePort}`;
    this.channel = new grpc.Channel(
      address,
      grpc.credentials.createInsecure(),
      {}
    );
    
    const isSandbox = this.octaneHost === 'host.docker.internal';
    console.log(`📡 gRPC channel initialized: ${address}`);
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
    return isSandbox ? 'host.docker.internal' : 'localhost';
  }
  
  async initialize(): Promise<void> {
    const PROTO_PATH = path.resolve(__dirname, '../../proto');
    
    // Load common proto files that are needed for most services
    const coreProtoFiles = [
      'common.proto',
      'apiprojectmanager.proto',
      'livelink.proto',
      'apirender.proto',
      'callback.proto'
    ].map(f => path.join(PROTO_PATH, f)).filter(f => fs.existsSync(f));
    
    if (coreProtoFiles.length === 0) {
      console.log('⚠️ No core proto files found, will load services on-demand');
      return;
    }
    
    console.log(`📦 Loading ${coreProtoFiles.length} core proto files...`);
    
    try {
      // Use proto-loader with options that handle Octane's proto structure
      this.packageDefinition = protoLoader.loadSync(coreProtoFiles, {
        keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true,
        includeDirs: [PROTO_PATH]
      });
      
      this.protoDescriptor = grpc.loadPackageDefinition(this.packageDefinition);
      console.log('✅ Core proto definitions loaded successfully');
    } catch (error: any) {
      console.log('⚠️ Could not load proto files, will use dynamic mode:', error.message);
      this.protoDescriptor = null;
    }
  }
  
  private loadServiceProto(serviceName: string): any {
    const PROTO_PATH = path.resolve(__dirname, '../../proto');
    const protoFileName = serviceName.toLowerCase() + '.proto';
    const protoFilePath = path.join(PROTO_PATH, protoFileName);
    
    if (!fs.existsSync(protoFilePath)) {
      console.log(`⚠️ Proto file not found: ${protoFileName}`);
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
      
      const descriptor = grpc.loadPackageDefinition(packageDefinition);
      console.log(`✅ Loaded proto for ${serviceName}`);
      return descriptor;
    } catch (error: any) {
      console.log(`⚠️ Could not load proto for ${serviceName}:`, error.message);
      return null;
    }
  }
  
  private getService(serviceName: string): any {
    if (this.services.has(serviceName)) {
      return this.services.get(serviceName);
    }
    
    let descriptor = this.protoDescriptor;
    
    // If no main descriptor or service not found, try loading service-specific proto
    if (!descriptor) {
      descriptor = this.loadServiceProto(serviceName);
      if (!descriptor) {
        throw new Error(`Could not load proto for service ${serviceName}`);
      }
    }
    
    // Try different namespace patterns for Octane proto files
    let ServiceConstructor: any = null;
    const patterns = [
      `octaneapi.${serviceName}Service`,  // Try with Service suffix first (this is the client!)
      `octaneapi.${serviceName}`,
      `livelinkapi.${serviceName}Service`, // For LiveLink services
      `livelinkapi.${serviceName}`,
      `${serviceName}Service`,            // For LiveLinkService, etc.
      `OctaneEngine.Livelink.${serviceName}`,
      `Octane.${serviceName}`,
      serviceName
    ];
    
    for (const pattern of patterns) {
      ServiceConstructor = this.resolveServicePath(descriptor, pattern);
      if (ServiceConstructor) {
        console.log(`✅ Found service: ${serviceName} at ${pattern}`);
        break;
      }
    }
    
    // If not found in main descriptor, try loading service-specific proto
    if (!ServiceConstructor && descriptor === this.protoDescriptor) {
      console.log(`⚠️ Service ${serviceName} not in main descriptor, trying service-specific proto...`);
      const serviceDescriptor = this.loadServiceProto(serviceName);
      if (serviceDescriptor) {
        for (const pattern of patterns) {
          ServiceConstructor = this.resolveServicePath(serviceDescriptor, pattern);
          if (ServiceConstructor) {
            console.log(`✅ Found service: ${serviceName} at ${pattern} (service-specific proto)`);
            break;
          }
        }
      }
    }
    
    if (!ServiceConstructor) {
      throw new Error(`Service ${serviceName} not found in proto definitions`);
    }
    
    // Debugging: log what ServiceConstructor actually is
    console.log(`🔍 ServiceConstructor type for ${serviceName}:`, typeof ServiceConstructor);
    console.log(`🔍 ServiceConstructor keys:`, Object.keys(ServiceConstructor || {}).slice(0, 10));
    
    // ServiceConstructor should be a function/class that we can instantiate
    if (typeof ServiceConstructor !== 'function') {
      throw new Error(`ServiceConstructor for ${serviceName} is not a constructor (type: ${typeof ServiceConstructor})`);
    }
    
    // Check if ServiceConstructor has a 'service' property (common in grpc-js)
    if (ServiceConstructor.service) {
      console.log(`🔍 Found .service property:`, Object.keys(ServiceConstructor.service).slice(0, 10));
    }
    
    // Create the client instance
    const service = new ServiceConstructor(
      `${this.octaneHost}:${this.octanePort}`,
      grpc.credentials.createInsecure()
    );
    
    // gRPC methods might not be enumerable, check proto directly
    console.log(`✅ Created ${serviceName} client instance`);
    
    this.services.set(serviceName, service);
    return service;
  }
  
  private resolveServicePath(descriptor: any, path: string): any {
    const parts = path.split('.');
    let current = descriptor;
    
    // Debug: log what we're searching for
    console.log(`🔍 Searching for path: ${path} in descriptor with keys:`, Object.keys(descriptor).slice(0, 20));
    
    for (const part of parts) {
      if (current && current[part]) {
        current = current[part];
        console.log(`  ✅ Found part '${part}', type: ${typeof current}, keys:`, Object.keys(current || {}).slice(0, 10));
      } else {
        console.log(`  ❌ Part '${part}' not found in current object with keys:`, Object.keys(current || {}).slice(0, 20));
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
    console.log(`📤 gRPC call: ${serviceName}.${methodName}`, Object.keys(params).length > 0 ? `(${Object.keys(params).length} params)` : '');
    
    try {
      const service = this.getService(serviceName);
      
      // Check if method exists (might not be enumerable)
      const method = service[methodName];
      console.log(`🔍 Method ${methodName} type:`, typeof method);
      console.log(`🔍 Service prototype:`, Object.getPrototypeOf(service).constructor.name);
      
      if (!method || typeof method !== 'function') {
        // List all properties to debug
        const allProps = [];
        let obj = service;
        while (obj && obj !== Object.prototype) {
          allProps.push(...Object.getOwnPropertyNames(obj));
          obj = Object.getPrototypeOf(obj);
        }
        console.log(`🔍 All properties on service:`, allProps.filter(p => !p.startsWith('_')).slice(0, 20));
        throw new Error(`Method ${methodName} not found in service ${serviceName}`);
      }
      
      const request = Object.keys(params).length === 0 ? {} : params;
      const metadata = options.metadata || new grpc.Metadata();
      const deadline = Date.now() + (options.timeout || 30000);
      
      return new Promise((resolve, reject) => {
        method.call(service, request, metadata, { deadline }, 
          (error: grpc.ServiceError | null, response: any) => {
            if (error) {
              console.error(`❌ ${serviceName}.${methodName}: ${error.message}`, error.code);
              reject(error);
            } else {
              console.log(`✅ ${serviceName}.${methodName} success:`, JSON.stringify(response).slice(0, 200));
              resolve(response);
            }
          }
        );
      });
    } catch (error: any) {
      console.error(`❌ ${serviceName}.${methodName} error:`, error.message);
      throw error;
    }
  }
  
  close(): void {
    this.channel.close();
    this.services.clear();
    console.log('🔌 gRPC client closed');
  }
  
  async checkHealth(): Promise<boolean> {
    try {
      await this.callMethod('ApiProjectManager', 'getPing', {}, { timeout: 5000 });
      return true;
    } catch (error) {
      return false;
    }
  }
  
  /**
   * Register callback and start streaming OnNewImage events
   */
  async startCallbackStreaming(): Promise<void> {
    try {
      console.log('🎬 Starting callback streaming...');
      
      // Step 1: Register OnNewImage callback with Octane
      console.log('📝 Registering OnNewImage callback...');
      const registerResponse = await this.callMethod('ApiRender', 'setOnNewImageCallback', {}, { timeout: 10000 });
      console.log('✅ Callback registered:', registerResponse);
      
      // Step 2: Start streaming from callback channel
      console.log('📡 Starting callback channel stream...');
      const streamService = this.getService('StreamCallbackService');
      
      if (!streamService || !streamService.callbackChannel) {
        throw new Error('StreamCallbackService.callbackChannel not found');
      }
      
      // Create empty request for callbackChannel (server-side streaming)
      const stream = streamService.callbackChannel({});
      
      stream.on('data', (response: any) => {
        try {
          // Parse callback data and emit event
          if (response.render_images && response.render_images.data) {
            console.log(`📸 Received OnNewImage callback (${response.render_images.data.length} images)`);
            this.emit('OnNewImage', response);
          }
        } catch (error: any) {
          console.error('❌ Error processing callback data:', error.message);
        }
      });
      
      stream.on('end', () => {
        console.log('⚠️  Callback stream ended');
      });
      
      stream.on('error', (error: any) => {
        console.error('❌ Callback stream error:', error.message);
        // Try to reconnect after a delay
        setTimeout(() => {
          console.log('🔄 Attempting to reconnect callback stream...');
          this.startCallbackStreaming().catch(e => {
            console.error('❌ Reconnection failed:', e.message);
          });
        }, 5000);
      });
      
      console.log('✅ Callback streaming started');
    } catch (error: any) {
      console.error('❌ Failed to start callback streaming:', error.message);
      throw error;
    }
  }
}

// Singleton instance
let instance: OctaneGrpcClient | null = null;

export function getGrpcClient(): OctaneGrpcClient {
  if (!instance) {
    instance = new OctaneGrpcClient();
  }
  return instance;
}
