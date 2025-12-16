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
    private octaneHost: string = process.env.OCTANE_HOST || 'localhost',
    private octanePort: number = parseInt(process.env.OCTANE_PORT || '51022')
  ) {
    super();
    
    const address = `${this.octaneHost}:${this.octanePort}`;
    this.channel = new grpc.Channel(
      address,
      grpc.credentials.createInsecure(),
      {}
    );
    
    console.log(`📡 gRPC channel initialized: ${address}`);
  }
  
  async initialize(): Promise<void> {
    const PROTO_PATH = path.resolve(__dirname, '../../proto');
    
    // Load common proto files that are needed for most services
    const coreProtoFiles = [
      'common.proto',
      'apiprojectmanager.proto',
      'livelink.proto'
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
      `octaneapi.${serviceName}`,
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
    console.log(`📤 gRPC call: ${serviceName}.${methodName}`, Object.keys(params).length > 0 ? `(${Object.keys(params).length} params)` : '');
    
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
              console.error(`❌ ${serviceName}.${methodName}: ${error.message}`);
              reject(error);
            } else {
              console.log(`✅ ${serviceName}.${methodName} success`);
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
}

// Singleton instance
let instance: OctaneGrpcClient | null = null;

export function getGrpcClient(): OctaneGrpcClient {
  if (!instance) {
    instance = new OctaneGrpcClient();
  }
  return instance;
}
