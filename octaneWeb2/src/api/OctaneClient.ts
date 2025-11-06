import type { SceneNode, Vector3, NodeParameter } from '@/types/octane';

class OctaneClient {
  private baseUrl: string;
  
  constructor(baseUrl: string) {
    this.baseUrl = baseUrl;
  }
  
  private async request<T>(endpoint: string, data?: any): Promise<T> {
    const response = await fetch(`${this.baseUrl}/${endpoint}`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: data ? JSON.stringify(data) : undefined,
    });
    
    if (!response.ok) {
      throw new Error(`API Error: ${response.statusText}`);
    }
    
    return response.json();
  }
  
  // Connection
  async ping(): Promise<boolean> {
    try {
      await this.request('ping');
      return true;
    } catch {
      return false;
    }
  }
  
  // Scene Management
  async getSceneTree(): Promise<SceneNode[]> {
    return this.request<SceneNode[]>('buildSceneTree');
  }
  
  async setNodeVisibility(id: string, visible: boolean): Promise<void> {
    return this.request('setNodeVisibility', { id, visible });
  }
  
  // Camera Control
  async setCameraPosition(position: Vector3): Promise<void> {
    return this.request('setCameraPosition', position);
  }
  
  async setCameraTarget(target: Vector3): Promise<void> {
    return this.request('setCameraTarget', target);
  }
  
  // Node Parameters
  async getNodeParameters(nodeId: string): Promise<NodeParameter[]> {
    return this.request<NodeParameter[]>('getNodeParameters', { nodeId });
  }
  
  async setNodeParameter(nodeId: string, paramName: string, value: any): Promise<void> {
    return this.request('setNodeParameter', { nodeId, paramName, value });
  }
  
  // Render Control
  async startRender(): Promise<void> {
    return this.request('startRender');
  }
  
  async stopRender(): Promise<void> {
    return this.request('stopRender');
  }
}

// Singleton instance
export const octaneClient = new OctaneClient('http://localhost:51023');
