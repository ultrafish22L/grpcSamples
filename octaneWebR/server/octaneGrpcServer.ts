import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';
import express from 'express';
import cors from 'cors';
import path from 'path';
import { fileURLToPath } from 'url';
import { dirname } from 'path';

// ========================================
//  DIRECT gRPC CONNECTION TO OCTANE
//  NO Python proxy!
// ========================================

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

const PROTO_DIR = path.join(__dirname, '../../sdk/src/api/grpc/protodef');
const OCTANE_ADDRESS = '127.0.0.1:51022';

console.log('Loading protobuf definitions from:', PROTO_DIR);

// Load ALL protobuf definitions (like octaneWeb does)
import fs from 'fs';

const protoFiles = fs.readdirSync(PROTO_DIR).filter(f => f.endsWith('.proto'));
console.log(`Found ${protoFiles.length} proto files`);

const allProtos: any = {};

// Load each proto file
for (const protoFile of protoFiles) {
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
    Object.assign(allProtos, loaded);
  } catch (error: any) {
    console.warn(`⚠️ Could not load ${protoFile}:`, error.message);
  }
}

console.log('✅ Loaded proto packages:', Object.keys(allProtos));

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

// Create GraphServer client (for scene operations)
if (allProtos.OctaneEngine && allProtos.OctaneEngine.graphserver) {
  grpcClients.GraphServer = new allProtos.OctaneEngine.graphserver.GraphServer(
    OCTANE_ADDRESS,
    grpc.credentials.createInsecure()
  );
  console.log('✅ GraphServer client created');
}

console.log('✅ gRPC clients ready for Octane at', OCTANE_ADDRESS);

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
