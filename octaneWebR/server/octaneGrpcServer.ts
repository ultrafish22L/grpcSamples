import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';
import express from 'express';
import cors from 'cors';
import path from 'path';
import { fileURLToPath } from 'url';
import { dirname } from 'path';
import * as fs from 'fs';

// ========================================
//  DIRECT gRPC CONNECTION TO OCTANE
//  NO Python proxy!
// ========================================

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

const PROTO_DIR = path.join(__dirname, '../../sdk/src/api/grpc/protodef');

// Detect sandbox environment (Docker/containerized)
const isDockerOrSandbox = process.env.DOCKER || process.env.SANDBOX || 
  fs.existsSync('/.dockerenv') || fs.existsSync('/run/.containerenv');
const OCTANE_HOST = isDockerOrSandbox ? 'host.docker.internal' : '127.0.0.1';
const OCTANE_ADDRESS = `${OCTANE_HOST}:51022`;

console.log(`🐳 Environment: ${isDockerOrSandbox ? 'Docker/Sandbox' : 'Native'}`);
console.log(`🎯 Octane target: ${OCTANE_ADDRESS}`);

console.log('Loading protobuf definitions from:', PROTO_DIR);

// Load specific proto files (avoids naming conflicts)
import fs from 'fs';

const requiredProtos = [
  'livelink.proto',
  'apiprojectmanager.proto',
  'apinodesystem_3.proto',  // Contains ApiItemService
  'apinodesystem_6.proto',  // Contains ApiNodeGraphService
  'apinodesystem_7.proto',  // Contains ApiNodeService
  'apiitemarray.proto'
];

console.log(`Loading ${requiredProtos.length} required proto files`);

const allProtos: any = {};

// Load each required proto file
for (const protoFile of requiredProtos) {
  try {
    const packageDef = protoLoader.loadSync(
      path.join(PROTO_DIR, protoFile),
      {
        keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true,
        includeDirs: [PROTO_DIR]
      }
    );
    
    const loaded = grpc.loadPackageDefinition(packageDef);
    // Merge packages without overwriting
    for (const pkgName of Object.keys(loaded)) {
      if (!allProtos[pkgName]) {
        allProtos[pkgName] = {};
      }
      Object.assign(allProtos[pkgName], loaded[pkgName]);
    }
    console.log(`✅ Loaded ${protoFile}`);
  } catch (error: any) {
    console.warn(`⚠️ Could not load ${protoFile}:`, error.message);
  }
}

console.log('✅ Loaded proto packages:', Object.keys(allProtos));

// Debug: show what's in octaneapi
if (allProtos.octaneapi) {
  console.log('📦 octaneapi services:', Object.keys(allProtos.octaneapi).filter(k => k.endsWith('Service')).slice(0, 10));
}

// Create gRPC clients
const grpcClients: any = {};

// Create LiveLink camera client
if (allProtos.livelinkapi && allProtos.livelinkapi.LiveLinkService) {
  grpcClients.LiveLink = new allProtos.livelinkapi.LiveLinkService(
    OCTANE_ADDRESS,
    grpc.credentials.createInsecure()
  );
  console.log('✅ LiveLink client created');
}

// Create all octaneapi services dynamically
if (allProtos.octaneapi) {
  const serviceNames = [
    'ApiProjectManagerService',
    'ApiNodeGraphService', 
    'ApiItemService',
    'ApiItemArrayService',
    'ApiNodeService'
  ];
  
  for (const serviceName of serviceNames) {
    if (allProtos.octaneapi[serviceName]) {
      // Remove 'Service' suffix for client name (ApiProjectManagerService → ApiProjectManager)
      const clientName = serviceName.replace('Service', '');
      grpcClients[clientName] = new allProtos.octaneapi[serviceName](
        OCTANE_ADDRESS,
        grpc.credentials.createInsecure()
      );
      console.log(`✅ ${clientName} client created`);
    } else {
      console.log(`⚠️ ${serviceName} not found in octaneapi`);
    }
  }
}

console.log('✅ gRPC clients ready for Octane at', OCTANE_ADDRESS);
console.log('✅ Available clients:', Object.keys(grpcClients));

// Express server for browser REST API
const app = express();
app.use(cors());
app.use(express.json({ limit: '50mb' }));

// Generic gRPC call handler - maps REST to direct gRPC
app.post('/api/rpc/:service/:method', (req, res) => {
  const { service, method } = req.params;
  const request = req.body;
  
  console.log(`[gRPC Direct] ${service}.${method}`);
  
  const client = grpcClients[service];
  
  if (!client) {
    return res.status(404).json({ error: `Service ${service} not found` });
  }
  
  if (!client[method]) {
    return res.status(404).json({ error: `Method ${method} not found in ${service}` });
  }
  
  try {
    client[method](request, (err: grpc.ServiceError | null, response: any) => {
      if (err) {
        console.error(`[gRPC Error] ${service}.${method}:`, err.message);
        res.status(500).json({ 
          error: err.message,
          code: err.code,
          details: err.details 
        });
      } else {
        res.json(response);
      }
    });
  } catch (error: any) {
    console.error(`[Exception] ${service}.${method}:`, error.message);
    res.status(500).json({ error: error.message });
  }
});

// Health check endpoint
app.get('/api/health', (req, res) => {
  // Try to ping LiveLink service
  const liveLinkClient = grpcClients.LiveLink;
  
  if (!liveLinkClient) {
    return res.status(503).json({
      status: 'disconnected',
      error: 'LiveLink client not initialized',
      octane: OCTANE_ADDRESS
    });
  }
  
  liveLinkClient.GetCamera({}, (err: grpc.ServiceError | null, response: any) => {
    if (err) {
      res.status(503).json({ 
        status: 'disconnected',
        error: err.message,
        octane: OCTANE_ADDRESS
      });
    } else {
      res.json({ 
        status: 'connected',
        architecture: 'Node.js → Direct gRPC → Octane',
        proxy: 'NONE (direct connection)',
        octane: OCTANE_ADDRESS,
        camera: response 
      });
    }
  });
});

const PORT = 45042; // Use available port
app.listen(PORT, '0.0.0.0', () => {
  console.log('\n==============================================');
  console.log('  OctaneWebR Backend - DIRECT gRPC');
  console.log('==============================================');
  console.log(`  REST API:        http://0.0.0.0:${PORT}`);
  console.log(`  Octane gRPC:     ${OCTANE_ADDRESS} (DIRECT)`);
  console.log(`  Architecture:    Node.js + @grpc/grpc-js`);
  console.log(`  Python proxy:    NOT RUNNING`);
  console.log('==============================================\n');
  console.log('Test connection: curl http://localhost:' + PORT + '/api/health\n');
});
