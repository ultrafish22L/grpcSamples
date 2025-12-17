/**
 * OctaneWebR gRPC Client
 * Connects to Node.js backend which makes DIRECT gRPC calls to Octane
 * NO Python proxy involved!
 */

class OctaneClient {
  private baseUrl: string;
  private connected: boolean = false;

  constructor(baseUrl = '/api') {
    this.baseUrl = baseUrl;
  }

  /**
   * Make a direct gRPC call through Node.js backend
   * Backend connects DIRECTLY to Octane (no proxy)
   */
  async call(service: string, method: string, params: any = {}): Promise<any> {
    try {
      const response = await fetch(`${this.baseUrl}/rpc/${service}/${method}`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(params)
      });
      
      if (!response.ok) {
        const error = await response.json();
        throw new Error(error.error || `HTTP ${response.status}`);
      }
      
      return await response.json();
    } catch (error: any) {
      console.error(`[Octane gRPC] ${service}/${method}:`, error.message);
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

  // Camera operations
  async getCamera() {
    return this.call('Camera', 'GetCamera', {});
  }

  async setCameraPosition(x: number, y: number, z: number) {
    return this.call('Camera', 'SetCameraPosition', { x, y, z });
  }

  async setCameraTarget(x: number, y: number, z: number) {
    return this.call('Camera', 'SetCameraTarget', { x, y, z });
  }

  // Scene operations
  async getRootNodeGraph() {
    return this.call('GraphServer', 'rootNodeGraph', {});
  }

  async getOwnedItems(objectPtr: any) {
    return this.call('Graph', 'getOwnedItems', { objectPtr });
  }

  async getArrayLength(objectPtr: any) {
    return this.call('ApiItemArray', 'length', { objectPtr });
  }

  async getArrayItem(objectPtr: any, index: number) {
    return this.call('ApiItemArray', 'get', { objectPtr, index });
  }

  async isGraph(objectPtr: any) {
    return this.call('GraphServer', 'isGraph', { objectPtr });
  }

  async getName(objectPtr: any) {
    return this.call('GraphServer', 'getName', { objectPtr });
  }

  async getType(objectPtr: any) {
    return this.call('GraphServer', 'getType', { objectPtr });
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
