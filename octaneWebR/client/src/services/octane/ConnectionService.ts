/**
 * Connection Service - WebSocket and connection management
 * Handles connection lifecycle and real-time callbacks
 */

import { BaseService } from './BaseService';
import { ApiService } from './ApiService';

export class ConnectionService extends BaseService {
  private ws: WebSocket | null = null;
  private connected: boolean = false;
  private apiService: ApiService;

  constructor(emitter: any, serverUrl: string, apiService: ApiService) {
    super(emitter, serverUrl);
    this.apiService = apiService;
  }

  async connect(): Promise<boolean> {
    try {
      console.log('📡 ConnectionService.connect() - Connecting to server:', this.serverUrl);
      
      // Check server health
      const isHealthy = await this.apiService.checkServerHealth();
      if (!isHealthy) {
        throw new Error('Server unhealthy');
      }
      
      // Setup WebSocket for callbacks
      this.connectWebSocket();
      
      this.connected = true;
      console.log('✅ Setting connected = true, emitting connected event');
      this.emit('connected');
      console.log('✅ Connected to OctaneWebR server');
      
      return true;
    } catch (error: any) {
      console.error('❌ Connection failed:', error.message);
      console.error('❌ Error stack:', error.stack);
      this.emit('connectionError', error);
      return false;
    }
  }

  private connectWebSocket(): void {
    const wsUrl = this.serverUrl.replace('http', 'ws') + '/api/callbacks';
    console.log('🔌 Connecting WebSocket:', wsUrl);
    
    try {
      this.ws = new WebSocket(wsUrl);
      
      this.ws.onopen = () => {
        console.log('✅ WebSocket connected');
        // Safety check: ensure WebSocket is actually open before sending
        if (this.ws && this.ws.readyState === WebSocket.OPEN) {
          this.ws.send(JSON.stringify({ type: 'subscribe' }));
        } else {
          console.warn('⚠️ WebSocket not ready in onopen handler, state:', this.ws?.readyState);
        }
      };
      
      this.ws.onmessage = (event) => {
        try {
          const message = JSON.parse(event.data);
          if (message.type === 'newImage') {
            this.emit('OnNewImage', message.data);
          } else if (message.type === 'newStatistics') {
            this.emit('OnNewStatistics', message.data);
          }
        } catch (error: any) {
          console.error('❌ WebSocket message error:', error.message);
        }
      };
      
      this.ws.onerror = (error) => {
        console.error('❌ WebSocket error:', error);
      };
      
      this.ws.onclose = () => {
        console.log('🔌 WebSocket disconnected');
        // Attempt reconnection after 5 seconds
        setTimeout(() => {
          if (this.connected) {
            console.log('🔄 Reconnecting WebSocket...');
            this.connectWebSocket();
          }
        }, 5000);
      };
    } catch (error: any) {
      console.error('❌ WebSocket connection failed:', error.message);
    }
  }

  async disconnect(): Promise<void> {
    this.connected = false;
    
    if (this.ws) {
      this.ws.close();
      this.ws = null;
    }
    
    this.emit('disconnected');
    console.log('🔌 Disconnected from server');
  }

  isConnected(): boolean {
    return this.connected;
  }
}
