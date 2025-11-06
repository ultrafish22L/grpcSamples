/**
 * Octane API Client
 * 
 * TypeScript implementation of the octaneWeb LiveLink client
 * Based on the proven patterns from octaneWeb/shared/js/livelink.js
 * 
 * HTTP client for communicating with the octaneProxy server (HTTP-to-gRPC bridge)
 * URL pattern: http://localhost:51023/LiveLink/MethodName
 */

export interface SceneNode {
  id: string;
  name: string;
  type: string;
  handle?: number;
  children?: SceneNode[];
  visible?: boolean;
  locked?: boolean;
}

export interface SceneData {
  nodes: SceneNode[];
  connections: any[];
}

export interface NodeParameter {
  name: string;
  type: string;
  value: any;
  min?: number;
  max?: number;
  options?: string[];
}

export interface RenderInfo {
  isRendering: boolean;
  samples: number;
  renderTime: number;
  progress: number;
}

class OctaneClient {
  private serverUrl: string;
  private connected: boolean = false;
  private connectionState: string = 'disconnected';
  private listeners: Map<string, Set<Function>> = new Map();
  private callCount: number = 0;
  private errorCount: number = 0;

  constructor(serverUrl: string = 'http://localhost:51023') {
    this.serverUrl = serverUrl;
  }

  // Event system for component communication
  on(event: string, callback: Function) {
    if (!this.listeners.has(event)) {
      this.listeners.set(event, new Set());
    }
    this.listeners.get(event)!.add(callback);
  }

  off(event: string, callback: Function) {
    if (this.listeners.has(event)) {
      this.listeners.get(event)!.delete(callback);
    }
  }

  emit(event: string, data: any) {
    if (this.listeners.has(event)) {
      this.listeners.get(event)!.forEach(callback => callback(data));
    }
  }

  // Connection Management
  async connect(): Promise<boolean> {
    console.log('🔌 Connecting to Octane proxy...');
    this.connectionState = 'connecting';
    
    try {
      // Test connection with health endpoint
      const response = await fetch(`${this.serverUrl}/health`);
      const data = await response.json();
      
      if (data.status === 'ok' && data.connected) {
        this.connected = true;
        this.connectionState = 'connected';
        console.log('✅ Connected to Octane');
        
        // Emit connection event
        this.emit('connected', { timestamp: new Date().toISOString() });
        return true;
      } else {
        this.connected = false;
        this.connectionState = 'disconnected';
        console.warn('⚠️ Proxy OK but Octane not connected');
        return false;
      }
    } catch (error) {
      console.error('❌ Connection failed:', error);
      this.connected = false;
      this.connectionState = 'disconnected';
      this.emit('connectionError', { error });
      return false;
    }
  }

  async disconnect(): Promise<void> {
    this.connected = false;
    this.connectionState = 'disconnected';
    this.emit('disconnected', {});
  }

  isConnected(): boolean {
    return this.connected;
  }

  isReady(): boolean {
    return this.connected && this.connectionState === 'connected';
  }

  // Generic API call method (matches livelink.js pattern)
  private async makeApiCall(method: string, request: any = {}): Promise<any> {
    const startTime = Date.now();
    const callId = `${method}_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`;
    this.callCount++;
    
    // URL pattern from livelink.js: ${this.serverUrl}/LiveLink/${method}
    const url = `${this.serverUrl}/LiveLink/${method}`;
    
    console.log(`📡 gRPC call: ${method}`, { callId, request });
    
    try {
      if (!this.isReady()) {
        throw new Error(`Client not ready. State: ${this.connectionState}`);
      }
      
      const controller = new AbortController();
      const timeoutId = setTimeout(() => {
        controller.abort();
        console.error(`⏱️ Timeout: ${method}`);
      }, 30000); // 30 second timeout
      
      const response = await fetch(url, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/grpc-web+proto',
          'Accept': 'application/grpc-web+proto',
          'X-Call-ID': callId
        },
        body: JSON.stringify(request),
        signal: controller.signal
      });
      
      clearTimeout(timeoutId);
      const responseTime = Date.now() - startTime;
      
      console.log(`✅ Response: ${method}`, {
        callId,
        status: response.status,
        duration: responseTime
      });
      
      if (!response.ok) {
        const errorText = await response.text().catch(() => 'Unable to read error response');
        const error = new Error(`gRPC call failed: ${response.status} ${response.statusText}`);
        console.error(`❌ Call failed: ${method}`, {
          status: response.status,
          error: errorText
        });
        this.errorCount++;
        throw error;
      }
      
      const responseText = await response.text();
      const result = JSON.parse(responseText);
      
      console.log(`📦 Result: ${method}`, result);
      
      return {
        success: true,
        data: result
      };
    } catch (error) {
      console.error(`❌ API call error: ${method}`, error);
      this.errorCount++;
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Unknown error'
      };
    }
  }

  // Camera API (matches livelink.js)
  async getCamera(): Promise<any> {
    const result = await this.makeApiCall('GetCamera', {});
    return result && result.success ? result.data : null;
  }

  async setCamera(position?: {x: number, y: number, z: number}, target?: {x: number, y: number, z: number}): Promise<void> {
    const request: any = {};
    if (position) request.position = position;
    if (target) request.target = target;
    await this.makeApiCall('SetCamera', request);
  }

  async setCameraPosition(x: number, y: number, z: number): Promise<void> {
    await this.setCamera({ x, y, z }, undefined);
  }

  async setCameraTarget(x: number, y: number, z: number): Promise<void> {
    await this.setCamera(undefined, { x, y, z });
  }

  // Mesh API (matches livelink.js)
  async getMeshes(): Promise<any> {
    const result = await this.makeApiCall('GetMeshes', {});
    return result && result.success ? result.data : null;
  }

  async getMesh(meshId: number): Promise<any> {
    const result = await this.makeApiCall('GetMesh', { objecthandle: meshId });
    return result && result.success ? result.data : null;
  }

  // Scene API - based on OctaneWebClient.js syncSceneRecurse
  private async makeServiceCall(service: string, method: string, handle?: number, params?: any): Promise<any> {
    const url = `${this.serverUrl}/${service}/${method}`;
    const callId = `${service}/${method}_${Date.now()}`;
    
    console.log(`📡 Service call: ${service}/${method}`, { handle, params });
    
    try {
      if (!this.isReady()) {
        throw new Error(`Client not ready. State: ${this.connectionState}`);
      }
      
      // Build request body based on what's provided
      let body: any = {};
      if (handle !== undefined) {
        body.handle = handle;
      }
      if (params) {
        body = { ...body, ...params };
      }
      
      const response = await fetch(url, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          'X-Call-ID': callId
        },
        body: JSON.stringify(body)
      });
      
      if (!response.ok) {
        throw new Error(`HTTP ${response.status}: ${response.statusText}`);
      }
      
      const result = await response.json();
      console.log(`✅ Service result: ${service}/${method}`, result);
      
      return { success: true, data: result };
    } catch (error) {
      console.error(`❌ Service call failed: ${service}/${method}`, error);
      return { success: false, error: error instanceof Error ? error.message : 'Unknown error' };
    }
  }

  async syncScene(): Promise<SceneNode[]> {
    console.log('🔄 Starting scene sync...');
    try {
      const tree: SceneNode[] = [];
      await this.syncSceneRecurse(null, tree, false, 0);
      console.log('✅ Scene sync complete:', tree);
      return tree;
    } catch (error) {
      console.error('❌ Scene sync failed:', error);
      return [];
    }
  }

  private async syncSceneRecurse(itemHandle: number | null, sceneItems: SceneNode[], isGraph: boolean, level: number): Promise<void> {
    let response;
    level = level + 1;
    
    try {
      // First call - get the root node graph
      if (itemHandle === null) {
        response = await this.makeServiceCall('ApiProjectManager', 'rootNodeGraph');
        if (!response.success) {
          throw new Error('Failed ApiProjectManager/rootNodeGraph');
        }
        itemHandle = response.data.result.handle;
        
        // Check if it's a graph or node
        response = await this.makeServiceCall('ApiItem', 'isGraph', itemHandle);
        if (!response.success) {
          throw new Error('Failed ApiItem/isGraph');
        }
        isGraph = response.data.result;
      }
      
      if (isGraph) {
        // Get owned items in this graph
        response = await this.makeServiceCall('ApiNodeGraph', 'getOwnedItems', itemHandle);
        if (!response.success) {
          throw new Error('Failed ApiNodeGraph/getOwnedItems');
        }
        const ownedItemsHandle = response.data.list.handle;
        
        // Get the size of the item array
        response = await this.makeServiceCall('ApiItemArray', 'size', ownedItemsHandle);
        if (!response.success) {
          throw new Error('Failed ApiItemArray/size');
        }
        const size = response.data.result;
        
        console.log(`📦 Found ${size} items in graph`);
        
        // Iterate through all items
        for (let i = 0; i < size; i++) {
          response = await this.makeServiceCall('ApiItemArray', 'get', ownedItemsHandle, { index: i });
          if (!response.success) {
            throw new Error('Failed ApiItemArray/get');
          }
          
          const item = response.data.result;
          const sceneNode: SceneNode = {
            id: `node_${item.handle}`,
            name: item.name || `Item ${item.handle}`,
            type: item.type || 'unknown',
            handle: item.handle,
            children: [],
            visible: true,
            locked: false
          };
          
          sceneItems.push(sceneNode);
          
          // Recurse if this item is also a graph
          if (item.graphInfo) {
            await this.syncSceneRecurse(item.handle, sceneNode.children!, true, level);
          }
        }
      }
    } catch (error) {
      console.error('❌ syncSceneRecurse failed:', error);
      throw error;
    }
  }

  async getNodeInfo(handle: number): Promise<any> {
    const result = await this.makeServiceCall('ApiItem', 'getInfo', handle);
    return result && result.success ? result.data : null;
  }

  async getNodeParameters(handle: number): Promise<NodeParameter[]> {
    // This needs to be implemented based on the specific node type
    // For now, return empty array
    return [];
  }

  async setNodeParameter(handle: number, name: string, value: any): Promise<boolean> {
    // This needs to be implemented based on the specific parameter type
    return false;
  }

  // Render API
  async getRenderInfo(): Promise<RenderInfo | null> {
    const result = await this.makeApiCall('GetRenderInfo', {});
    return result && result.success ? result.data : null;
  }

  async startRender(): Promise<void> {
    await this.makeApiCall('StartRender', {});
  }

  async stopRender(): Promise<void> {
    await this.makeApiCall('StopRender', {});
  }

  // WebSocket callback stream for real-time rendering
  connectCallbackStream(onFrame: (data: any) => void): WebSocket | null {
    try {
      const wsUrl = this.serverUrl.replace('http', 'ws') + '/stream/events';
      const ws = new WebSocket(wsUrl);
      
      ws.onopen = () => {
        console.log('🔌 WebSocket connected');
      };
      
      ws.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data);
          if (data.type === 'frame') {
            onFrame(data);
          }
        } catch (error) {
          console.error('WebSocket message parse error:', error);
        }
      };

      ws.onerror = (error) => {
        console.error('WebSocket error:', error);
      };
      
      ws.onclose = () => {
        console.log('🔌 WebSocket disconnected');
      };

      return ws;
    } catch (error) {
      console.error('WebSocket connection error:', error);
      return null;
    }
  }
}

// Export singleton instance
export const octaneClient = new OctaneClient();
