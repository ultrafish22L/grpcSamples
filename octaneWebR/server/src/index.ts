import express from 'express';
import cors from 'cors';
import { OctaneGrpcClient, getGrpcClient } from './grpc/client';
import { setupCallbackStreaming } from './api/websocket';

const app = express();
const PORT = parseInt(process.env.SERVER_PORT || '51024');

// Middleware
app.use(cors({ 
  origin: '*', 
  credentials: true,
  methods: ['GET', 'POST', 'OPTIONS'],
  allowedHeaders: ['Content-Type', 'Authorization']
}));
app.use(express.json({ limit: '50mb' }));

// Request logging
app.use((req, res, next) => {
  console.log(`${req.method} ${req.path}`);
  next();
});

const grpcClient = getGrpcClient();

// Initialize gRPC client
grpcClient.initialize().then(() => {
  console.log('✅ gRPC client initialized successfully');
}).catch(error => {
  console.error('❌ Failed to initialize gRPC client:', error);
  process.exit(1);
});

// Health check endpoint
app.get('/api/health', async (req, res) => {
  try {
    const isHealthy = await grpcClient.checkHealth();
    res.json({
      status: isHealthy ? 'ok' : 'unhealthy',
      octane: isHealthy ? 'connected' : 'disconnected',
      server: 'running',
      timestamp: new Date().toISOString()
    });
  } catch (error: any) {
    res.status(500).json({
      status: 'error',
      octane: 'disconnected',
      error: error.message,
      timestamp: new Date().toISOString()
    });
  }
});

// Generic gRPC endpoint (matches octaneWeb pattern)
// POST /api/grpc/:service/:method
app.post('/api/grpc/:service/:method', async (req, res) => {
  const { service, method } = req.params;
  const params = req.body || {};
  
  try {
    const response = await grpcClient.callMethod(service, method, params);
    
    // Convert response to plain object if needed
    let jsonResponse = response;
    if (response && typeof response.toObject === 'function') {
      jsonResponse = response.toObject();
    } else if (response && typeof response === 'object') {
      // Already a plain object
      jsonResponse = response;
    }
    
    res.json(jsonResponse);
  } catch (error: any) {
    console.error(`❌ API error: ${service}.${method}:`, error.message);
    res.status(500).json({
      error: error.message || 'gRPC call failed',
      service,
      method,
      code: error.code || 'UNKNOWN'
    });
  }
});

// Start server
const server = app.listen(PORT, '0.0.0.0', () => {
  console.log(`
╔═══════════════════════════════════════════════════╗
║           OctaneWebR Server Started               ║
╠═══════════════════════════════════════════════════╣
║  HTTP Server:     http://localhost:${PORT}        ║
║  WebSocket:       ws://localhost:${PORT}/api/callbacks  ║
║  Octane gRPC:     ${grpcClient['octaneHost']}:${grpcClient['octanePort']}        ║
╚═══════════════════════════════════════════════════╝
  `);
});

// Setup WebSocket callback streaming
setupCallbackStreaming(server, grpcClient);

// Graceful shutdown
process.on('SIGTERM', () => {
  console.log('⚠️  SIGTERM received, shutting down gracefully...');
  server.close(() => {
    grpcClient.close();
    console.log('✅ Server closed');
    process.exit(0);
  });
});

process.on('SIGINT', () => {
  console.log('\n⚠️  SIGINT received, shutting down gracefully...');
  server.close(() => {
    grpcClient.close();
    console.log('✅ Server closed');
    process.exit(0);
  });
});
