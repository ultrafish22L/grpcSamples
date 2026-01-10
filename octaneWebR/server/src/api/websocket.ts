import { WebSocketServer, WebSocket } from 'ws';
import { Server } from 'http';
import { OctaneGrpcClient } from '../grpc/client';
import { CallbackManager } from '../services/callbackManager';

export function setupCallbackStreaming(
  server: Server,
  grpcClient: OctaneGrpcClient,
  callbackManager: CallbackManager
): void {
  const wss = new WebSocketServer({ 
    server, 
    path: '/api/callbacks' 
  });
  
  console.log('📡 WebSocket server initialized at /api/callbacks');
  
  wss.on('connection', (ws: WebSocket) => {
    console.log('🔌 Callback client connected');
    
    // Forward callback events from CallbackManager to WebSocket
    const forwardCallback = (data: any) => {
      if (ws.readyState === WebSocket.OPEN) {
        try {
          console.log('📡 [WebSocket] Forwarding OnNewImage to client');
          ws.send(JSON.stringify({
            type: 'newImage',
            data,
            timestamp: Date.now()
          }));
        } catch (error: any) {
          console.error('❌ Error forwarding callback:', error.message);
        }
      }
    };
    
    // Listen for OnNewImage callbacks from CallbackManager
    callbackManager.on('OnNewImage', forwardCallback);
    
    // Handle messages from client
    ws.on('message', (message: Buffer) => {
      try {
        const data = JSON.parse(message.toString());
        
        if (data.type === 'ping') {
          ws.send(JSON.stringify({ type: 'pong', timestamp: Date.now() }));
        } else if (data.type === 'subscribe') {
          // Handle subscription requests if needed
          console.log('📥 Client subscribed to callbacks');
        }
      } catch (error: any) {
        console.error('❌ Error handling WebSocket message:', error.message);
      }
    });
    
    ws.on('close', () => {
      console.log('🔌 Callback client disconnected');
      callbackManager.off('OnNewImage', forwardCallback);
    });
    
    ws.on('error', (error) => {
      console.error('❌ WebSocket error:', error.message);
    });
  });
  
  console.log('✅ WebSocket callback streaming ready');
}
