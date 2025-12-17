/**
 * OctaneWebR gRPC Client
 * Connects to Node.js backend which makes DIRECT gRPC calls to Octane
 */

class OctaneClient {
  private baseUrl: string;
  private connected: boolean = false;

  constructor(baseUrl = '/api') {
    this.baseUrl = baseUrl;
  }

  /**
   * Make gRPC call through Node.js backend
   * Backend path: /api/rpc/{service}/{method}
   */
  private async call(service: string, method: string, params: any = {}): Promise<any> {
    try {
      const url = `${this.baseUrl}/rpc/${service}/${method}`;
      console.log(`[Octane gRPC] ${service}.${method}`, params);
      
      const response = await fetch(url, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(params)
      });
      
      if (!response.ok) {
        const error = await response.json();
        throw new Error(error.error || `HTTP ${response.status}`);
      }
      
      const result = await response.json();
      console.log(`[Octane gRPC] ${service}.${method} response:`, result);
      
      return result;
    } catch (error: any) {
      console.error(`[Octane gRPC Error] ${service}.${method}:`, error.message);
      throw error;
    }
  }

  async checkHealth(): Promise<boolean> {
    try {
      const response = await fetch(`${this.baseUrl}/health`);
      const data = await response.json();
      this.connected = data.status === 'connected';
      return this.connected;
    } catch (error) {
      this.connected = false;
      return false;
    }
  }

  isConnected(): boolean {
    return this.connected;
  }

  // Camera operations (LiveLink service)
  async getCamera() {
    return this.call('LiveLink', 'GetCamera', {});
  }

  async setCamera(position: any, target: any) {
    return this.call('LiveLink', 'SetCamera', {
      cameraPosition: position,
      cameraTarget: target
    });
  }

  // Scene operations (ApiProjectManager service)
  async getRootNodeGraph() {
    const result = await this.call('ApiProjectManager', 'rootNodeGraph', {});
    return result.result;  // Returns full ObjectRef { handle, type }
  }

  async getOwnedItems(objectRef: any) {
    const result = await this.call('ApiNodeGraph', 'getOwnedItems', { objectPtr: objectRef });
    return result.list;  // Returns ObjectRef
  }

  async getArrayLength(objectRef: any) {
    const result = await this.call('ApiItemArray', 'size', { objectPtr: objectRef });
    return result.result;
  }

  async getArrayItem(objectRef: any, index: number) {
    const result = await this.call('ApiItemArray', 'get', { objectPtr: objectRef, index });
    return result.result;  // Returns ObjectRef
  }

  async isGraph(objectRef: any) {
    const result = await this.call('ApiNodeGraph', 'isValid', { objectPtr: objectRef });
    return result.result;
  }

  async getName(objectRef: any) {
    const result = await this.call('ApiItem', 'name', { objectPtr: objectRef });
    return result.result;
  }

  async getType(objectPtr: any) {
    const result = await this.call('ApiItem', 'type', { objectPtr });
    return result;
  }

  /**
   * Sync entire scene from Octane
   * Recursively builds scene tree
   */
  async syncScene(): Promise<any[]> {
    try {
      const rootGraphPtr = await this.getRootNodeGraph();
      return await this.syncSceneRecurse(rootGraphPtr);
    } catch (error: any) {
      console.error('[Scene Sync] Failed:', error.message);
      throw error;
    }
  }

  private async syncSceneRecurse(graphPtr: any): Promise<any[]> {
    const nodes: any[] = [];

    try {
      // Get all items in this graph
      const itemArrayPtr = await this.getOwnedItems(graphPtr);
      const arrayLength = await this.getArrayLength(itemArrayPtr);

      // Fetch each item
      for (let i = 0; i < arrayLength; i++) {
        const itemPtr = await this.getArrayItem(itemArrayPtr, i);
        const itemName = await this.getName(itemPtr);
        const itemType = await this.getType(itemPtr);
        const isGraphBool = await this.isGraph(itemPtr);

        const node: any = {
          id: `${itemPtr.handle}-${itemPtr.type}`,
          name: itemName,
          type: itemType,
          objectPtr: itemPtr,
          children: [],
          expanded: false,
          visible: true,
          selected: false
        };

        // Recursively get children
        if (isGraphBool) {
          node.children = await this.syncSceneRecurse(itemPtr);
        }

        nodes.push(node);
      }
    } catch (error: any) {
      console.error('[Scene Recurse] Failed:', error.message);
    }

    return nodes;
  }
}

export const octaneClient = new OctaneClient();
