/**
 * Octane API Client
 * HTTP-to-gRPC proxy communication layer for OctaneWeb2
 */

export interface SceneNode {
  handle: string;
  name: string;
  type: string;
  children?: SceneNode[];
}

export interface SceneData {
  tree: SceneNode[];
  map: Map<string, SceneNode>;
}

export interface ConnectionStatus {
  connected: boolean;
  error?: string;
}

export interface RenderInfo {
  width: number;
  height: number;
  samples: number;
  fps: number;
}

class OctaneClient {
  private proxyUrl: string;
  private connected: boolean = false;
  private eventListeners: Map<string, Set<Function>> = new Map();

  constructor(proxyUrl: string = 'http://localhost:51023') {
    this.proxyUrl = proxyUrl;
  }

  // Event system for components to listen to
  on(event: string, callback: Function) {
    if (!this.eventListeners.has(event)) {
      this.eventListeners.set(event, new Set());
    }
    this.eventListeners.get(event)!.add(callback);
  }

  off(event: string, callback: Function) {
    this.eventListeners.get(event)?.delete(callback);
  }

  private emit(event: string, data?: any) {
    this.eventListeners.get(event)?.forEach(callback => callback(data));
  }

  // Generic API call method
  private async call(method: string, params: any = {}): Promise<any> {
    try {
      const response = await fetch(`${this.proxyUrl}/${method}`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(params),
      });

      if (!response.ok) {
        throw new Error(`HTTP ${response.status}: ${response.statusText}`);
      }

      return await response.json();
    } catch (error) {
      console.error(`API call ${method} failed:`, error);
      throw error;
    }
  }

  // Connection management
  async connect(): Promise<boolean> {
    try {
      // Test connection with a simple API call
      await this.call('ping');
      this.connected = true;
      this.emit('connected');
      return true;
    } catch (error) {
      this.connected = false;
      this.emit('connectionError', error);
      return false;
    }
  }

  async disconnect(): Promise<void> {
    this.connected = false;
    this.emit('disconnected');
  }

  isConnected(): boolean {
    return this.connected;
  }

  // Scene API
  async buildSceneTree(): Promise<SceneData> {
    try {
      const response = await this.call('buildSceneTree');
      
      // Convert response to our SceneData format
      const tree = response.tree || [];
      const map = new Map<string, SceneNode>();
      
      const buildMap = (nodes: SceneNode[]) => {
        nodes.forEach(node => {
          map.set(node.handle, node);
          if (node.children) {
            buildMap(node.children);
          }
        });
      };
      
      buildMap(tree);
      
      return { tree, map };
    } catch (error) {
      console.error('Failed to build scene tree:', error);
      return { tree: [], map: new Map() };
    }
  }

  async getNodeInfo(handle: string): Promise<any> {
    try {
      return await this.call('getNodeInfo', { handle });
    } catch (error) {
      console.error(`Failed to get node info for ${handle}:`, error);
      return null;
    }
  }

  async getNodeParameters(handle: string): Promise<any> {
    try {
      return await this.call('getNodeParameters', { handle });
    } catch (error) {
      console.error(`Failed to get parameters for ${handle}:`, error);
      return null;
    }
  }

  async setNodeParameter(handle: string, paramName: string, value: any): Promise<boolean> {
    try {
      await this.call('setNodeParameter', { handle, paramName, value });
      return true;
    } catch (error) {
      console.error(`Failed to set parameter ${paramName} for ${handle}:`, error);
      return false;
    }
  }

  // Camera API
  async setCameraPosition(x: number, y: number, z: number): Promise<boolean> {
    try {
      await this.call('setCameraPosition', { x, y, z });
      return true;
    } catch (error) {
      console.error('Failed to set camera position:', error);
      return false;
    }
  }

  async setCameraTarget(x: number, y: number, z: number): Promise<boolean> {
    try {
      await this.call('setCameraTarget', { x, y, z });
      return true;
    } catch (error) {
      console.error('Failed to set camera target:', error);
      return false;
    }
  }

  // Render API
  async getRenderInfo(): Promise<RenderInfo | null> {
    try {
      return await this.call('getRenderInfo');
    } catch (error) {
      console.error('Failed to get render info:', error);
      return null;
    }
  }

  async startRender(): Promise<boolean> {
    try {
      await this.call('startRender');
      return true;
    } catch (error) {
      console.error('Failed to start render:', error);
      return false;
    }
  }

  async stopRender(): Promise<boolean> {
    try {
      await this.call('stopRender');
      return true;
    } catch (error) {
      console.error('Failed to stop render:', error);
      return false;
    }
  }

  // WebSocket for real-time callbacks
  connectCallbackStream(onFrame: (imageData: any) => void): WebSocket | null {
    try {
      const wsUrl = this.proxyUrl.replace('http', 'ws') + '/callback-stream';
      const ws = new WebSocket(wsUrl);

      ws.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data);
          if (data.type === 'image') {
            onFrame(data);
          }
        } catch (error) {
          console.error('Failed to parse callback data:', error);
        }
      };

      ws.onerror = (error) => {
        console.error('WebSocket error:', error);
      };

      ws.onclose = () => {
        console.log('WebSocket closed');
      };

      return ws;
    } catch (error) {
      console.error('Failed to connect callback stream:', error);
      return null;
    }
  }
}

// Singleton instance
export const octaneClient = new OctaneClient();

export default octaneClient;
