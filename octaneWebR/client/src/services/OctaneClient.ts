/**
 * OctaneWebR gRPC Client
 * TypeScript React implementation of Octane gRPC communication
 */

import { EventEmitter } from '../utils/EventEmitter';

export interface RenderState {
  isRendering: boolean;
  progress: number;
  samples: number;
  renderTime: number;
  resolution: { width: number; height: number };
}

export interface SceneNode {
  handle: number;
  name: string;
  type: string;
  typeEnum?: number;
  visible: boolean;
  children?: SceneNode[];
  [key: string]: any;
}

export interface Scene {
  tree: SceneNode[];
  map: Map<number, SceneNode>;
  connections: Map<number, any>;
}

export class OctaneClient extends EventEmitter {
  private serverUrl: string;
  private ws: WebSocket | null = null;
  private connected: boolean = false;
  private scene: Scene = {
    tree: [],
    map: new Map(),
    connections: new Map()
  };
  private renderState: RenderState = {
    isRendering: false,
    progress: 0,
    samples: 0,
    renderTime: 0,
    resolution: { width: 1920, height: 1080 }
  };

  constructor(serverUrl: string = 'http://localhost:45769') {
    super();
    this.serverUrl = serverUrl;
    console.log('🎬 OctaneClient initialized:', serverUrl);
  }

  async connect(): Promise<boolean> {
    try {
      console.log('📡 Connecting to server...');
      
      // Check server health
      const healthResponse = await fetch(`${this.serverUrl}/api/health`, {
        method: 'GET',
        headers: { 'Content-Type': 'application/json' }
      });
      
      if (!healthResponse.ok) {
        throw new Error(`Server unhealthy: ${healthResponse.status}`);
      }
      
      // Setup WebSocket for callbacks
      this.connectWebSocket();
      
      this.connected = true;
      this.emit('connected');
      console.log('✅ Connected to OctaneWebR server');
      
      return true;
    } catch (error: any) {
      console.error('❌ Connection failed:', error.message);
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
        this.ws?.send(JSON.stringify({ type: 'subscribe' }));
      };
      
      this.ws.onmessage = (event) => {
        try {
          const message = JSON.parse(event.data);
          if (message.type === 'newImage') {
            this.emit('OnNewImage', message.data);
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

  async callApi(service: string, method: string, handle?: any, params: any = {}): Promise<any> {
    const url = `${this.serverUrl}/api/grpc/${service}/${method}`;
    
    console.log(`📤 ${service}.${method}`, handle ? `(handle: ${handle})` : '');
    
    // Build request body
    const body: any = {};
    
    // ApiItemService and related services expect objectPtr structure
    const servicesNeedingObjectPtr = ['ApiItemService', 'ApiNodeService', 'ApiNodeGraphService', 'ApiItemArrayService', 'ApiNodeArrayService'];
    if (servicesNeedingObjectPtr.includes(service) && handle !== undefined && handle !== null) {
      // Extract type from handle if it's an object, otherwise default to ApiRootNodeGraph
      let objectType = 18; // ApiRootNodeGraph default
      let handleValue = handle;
      
      if (typeof handle === 'object' && handle.handle) {
        handleValue = handle.handle;
        if (handle.type) {
          // Map type strings to ObjectType enum values (from common.proto)
          const typeMap: Record<string, number> = {
            'ApiRootNodeGraph': 18,
            'ApiNodeGraph': 20,
            'ApiNode': 17,
            'ApiItem': 16,
            'ApiItemArray': 31,
            'ApiNodeArray': 34
          };
          objectType = typeMap[handle.type] || 16; // Default to ApiItem
          console.log(`🔍 Mapped type '${handle.type}' to enum value ${objectType}`);
        }
      } else {
        console.log(`🔍 Handle is primitive:`, handle, 'using default type', objectType);
      }
      
      body.objectPtr = {
        handle: handleValue,
        type: objectType
      };
    } else if (handle !== undefined && handle !== null) {
      body.handle = handle;
    }
    
    if (params && Object.keys(params).length > 0) {
      Object.assign(body, params);
    }
    
    try {
      const response = await fetch(url, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(body)
      });
      
      if (!response.ok) {
        const error = await response.json();
        throw new Error(error.error || `API call failed: ${response.status}`);
      }
      
      const data = await response.json();
      console.log(`✅ ${service}.${method} success`);
      return data;
    } catch (error: any) {
      console.error(`❌ ${service}.${method} error:`, error.message);
      throw error;
    }
  }

  // Camera API
  async getCamera(): Promise<any> {
    return this.callApi('ApiProjectManager', 'getCamera', {});
  }

  async setCameraPosition(x: number, y: number, z: number): Promise<void> {
    await this.callApi('ApiProjectManager', 'setCameraPosition', { x, y, z });
  }

  async setCameraTarget(x: number, y: number, z: number): Promise<void> {
    await this.callApi('ApiProjectManager', 'setCameraTarget', { x, y, z });
  }

  // Scene API
  async buildSceneTree(): Promise<SceneNode[]> {
    const response = await this.callApi('ApiSceneOutliner', 'buildSceneTree', {});
    if (response && response.tree) {
      this.scene.tree = response.tree;
      this.updateSceneMap(this.scene.tree);
      this.emit('sceneTreeUpdated', this.scene);
    }
    return this.scene.tree;
  }

  private updateSceneMap(nodes: SceneNode[]): void {
    for (const node of nodes) {
      this.scene.map.set(node.handle, node);
      if (node.children && node.children.length > 0) {
        this.updateSceneMap(node.children);
      }
    }
  }

  async setNodeVisibility(handle: number, visible: boolean): Promise<void> {
    await this.callApi('ApiSceneOutliner', 'setNodeVisibility', { handle, visible });
  }

  // Render API
  async startRender(): Promise<void> {
    await this.callApi('ApiRenderView', 'startRender', {});
    this.renderState.isRendering = true;
    this.emit('renderStateChanged', this.renderState);
  }

  async stopRender(): Promise<void> {
    await this.callApi('ApiRenderView', 'stopRender', {});
    this.renderState.isRendering = false;
    this.emit('renderStateChanged', this.renderState);
  }

  // State getters
  getScene(): Scene {
    return this.scene;
  }

  getRenderState(): RenderState {
    return this.renderState;
  }

  isConnected(): boolean {
    return this.connected;
  }
}

// Singleton instance
let octaneClient: OctaneClient | null = null;

export function getOctaneClient(): OctaneClient {
  if (!octaneClient) {
    octaneClient = new OctaneClient();
  }
  return octaneClient;
}
