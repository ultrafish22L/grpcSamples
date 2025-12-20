/**
 * OctaneWebR gRPC Client
 * TypeScript React implementation of Octane gRPC communication
 */

import { EventEmitter } from '../utils/EventEmitter';
import { getObjectTypeForService, createObjectPtr } from '../constants/OctaneTypes';

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
  visible?: boolean;
  level?: number;
  children?: SceneNode[];
  graphInfo?: any;
  nodeInfo?: any;
  pinInfo?: any;
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

  constructor(serverUrl?: string) {
    super();
    // Default to same-origin (Vite dev server with gRPC plugin)
    this.serverUrl = serverUrl || window.location.origin;
    console.log('🎬 OctaneClient initialized:', this.serverUrl);
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
    
    // Build request body - following octaneWeb's makeApiCall logic
    let body: any = {};
    
    // If handle is a string (typical case), check if service needs objectPtr wrapping
    if (typeof handle === 'string') {
      const objectType = getObjectTypeForService(service);
      
      if (objectType !== undefined) {
        // Service requires objectPtr structure
        body.objectPtr = createObjectPtr(handle, objectType);
      } else {
        // No objectPtr needed, pass handle directly
        body.handle = handle;
      }
    } else if (handle !== undefined && handle !== null) {
      // Handle is an object, merge it into body
      body = { ...handle };
    }
    
    // Merge additional params
    if (params && Object.keys(params).length > 0) {
      body = { ...body, ...params };
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

  // Scene API - Port of octaneWeb syncScene() implementation
  async buildSceneTree(): Promise<SceneNode[]> {
    console.log('🌳 Building scene tree...');
    
    // Clear previous scene data
    this.scene = {
      tree: [],
      map: new Map(),
      connections: new Map()
    };
    
    try {
      // Get root node graph
      const rootResponse = await this.callApi('ApiProjectManager', 'rootNodeGraph', {});
      if (!rootResponse || !rootResponse.result || !rootResponse.result.handle) {
        throw new Error('Failed to get root node graph');
      }
      
      const rootHandle = rootResponse.result.handle;
      console.log('📍 Root handle:', rootHandle);
      
      // Check if it's a graph
      const isGraphResponse = await this.callApi('ApiItem', 'isGraph', rootHandle);
      const isGraph = isGraphResponse?.result || false;
      
      // Recursively build scene tree starting from root
      // Note: syncSceneRecurse handles building children for level 1 items
      this.scene.tree = await this.syncSceneRecurse(rootHandle, null, isGraph, 0);
      
      console.log('✅ Scene tree built:', this.scene.tree.length, 'top-level items');
      this.emit('sceneTreeUpdated', this.scene);
      
      return this.scene.tree;
    } catch (error: any) {
      console.error('❌ Failed to build scene tree:', error.message);
      throw error;
    }
  }

  private async syncSceneRecurse(
    itemHandle: number | null,
    sceneItems: SceneNode[] | null,
    isGraph: boolean,
    level: number
  ): Promise<SceneNode[]> {
    if (sceneItems === null) {
      sceneItems = [];
    }
    
    level = level + 1;
    
    // Limit recursion depth to prevent overwhelming Octane
    if (level > 5) {
      console.warn(`⚠️ Recursion depth limit reached at level ${level}`);
      return sceneItems;
    }
    
    try {
      // First call - get the root
      if (itemHandle === null) {
        const response = await this.callApi('ApiProjectManager', 'rootNodeGraph', {});
        if (!response || !response.result || !response.result.handle) {
          throw new Error('Failed ApiProjectManager/rootNodeGraph');
        }
        itemHandle = response.result.handle;
        
        // Check if it's a graph or node
        const isGraphResponse = await this.callApi('ApiItem', 'isGraph', itemHandle);
        isGraph = isGraphResponse?.result || false;
      }
      
      if (isGraph) {
        // Get owned items
        const ownedResponse = await this.callApi('ApiNodeGraph', 'getOwnedItems', itemHandle);
        // getOwnedItems returns {list: {handle, type}} not {result: {handle, type}}
        if (!ownedResponse || !ownedResponse.list || !ownedResponse.list.handle) {
          throw new Error('Failed ApiNodeGraph/getOwnedItems');
        }
        const ownedItemsHandle = ownedResponse.list.handle;
        
        // Get the size of the item array
        const sizeResponse = await this.callApi('ApiItemArray', 'size', ownedItemsHandle);
        const size = sizeResponse?.result || 0;
        
        console.log(`📦 Level ${level}: Found ${size} owned items`);
        
        // Iterate through each owned item
        for (let i = 0; i < size; i++) {
          const itemResponse = await this.callApi('ApiItemArray', 'get', ownedItemsHandle, { index: i });
          if (itemResponse && itemResponse.result && itemResponse.result.handle) {
            await this.addSceneItem(sceneItems, itemResponse.result, null, level);
          }
        }
        
        // At level 1, build children for all items SEQUENTIALLY
        if (level === 1) {
          console.log(`🔄 Building children for ${sceneItems.length} level 1 items`);
          for (const item of sceneItems) {
            await this.addItemChildren(item);
            // Small delay to avoid overwhelming Octane
            await new Promise(resolve => setTimeout(resolve, 50));
          }
        }
      }
      // TODO: Handle nodes (not just graphs) - follow pins for node connections
      
    } catch (error: any) {
      console.error('❌ syncSceneRecurse failed:', error.message);
    }
    
    return sceneItems;
  }

  private async addSceneItem(
    sceneItems: SceneNode[],
    item: any,
    pinInfo: any,
    level: number
  ): Promise<SceneNode | undefined> {
    if (!item || !item.handle) {
      return undefined;
    }
    
    // Check if already exists at level 1
    const existing = this.scene.map.get(item.handle);
    if (existing && existing.level === 1) {
      sceneItems.push(existing);
      return existing;
    }
    
    try {
      // Get item name
      const nameResponse = await this.callApi('ApiItem', 'name', item.handle);
      const itemName = nameResponse?.result || 'Unnamed';
      
      // Get outType (node type enum)
      const outTypeResponse = await this.callApi('ApiItem', 'outType', item.handle);
      const outType = outTypeResponse?.result || 0;
      
      // Check if it's a graph or node
      const isGraphResponse = await this.callApi('ApiItem', 'isGraph', item.handle);
      const isGraph = isGraphResponse?.result || false;
      
      let graphInfo = null;
      let nodeInfo = null;
      
      if (isGraph) {
        // Get graph info
        const infoResponse = await this.callApi('ApiNodeGraph', 'info1', item.handle);
        graphInfo = infoResponse?.result || null;
      } else {
        // Get node info
        const infoResponse = await this.callApi('ApiNode', 'info', item.handle);
        nodeInfo = infoResponse?.result || null;
      }
      
      const entry: SceneNode = {
        level,
        name: itemName,
        handle: item.handle,
        type: this.mapOutTypeToString(outType),
        typeEnum: outType,
        visible: true,
        graphInfo,
        nodeInfo,
        pinInfo,
        children: []
      };
      
      // Save to scene items and map
      sceneItems.push(entry);
      this.scene.map.set(item.handle, entry);
      
      console.log(`  📄 Added item: ${itemName} (type: ${outType}, level: ${level})`);
      
      return entry;
      
    } catch (error: any) {
      console.error('❌ addSceneItem failed:', error.message);
      return undefined;
    }
  }

  private async addItemChildren(item: SceneNode): Promise<void> {
    if (!item || !item.handle) {
      return;
    }
    
    const isGraph = item.graphInfo !== null && item.graphInfo !== undefined;
    
    try {
      // Recursively get children
      const children = await this.syncSceneRecurse(item.handle, null, isGraph, item.level || 1);
      item.children = children;
      
      // For end nodes (no children), fetch attribute info
      if (children.length === 0) {
        try {
          const attrInfoResponse = await this.callApi(
            'ApiItem',
            'attrInfo',
            item.handle,
            { id: 12 } // A_VALUE attribute ID
          );
          
          if (attrInfoResponse?.result) {
            item.attrInfo = attrInfoResponse.result;
            console.log(`  📊 End node: ${item.name} (${item.attrInfo.type})`);
          }
        } catch (attrError: any) {
          // Not all end nodes have attribute info, that's OK
          console.log(`  ℹ️ No attrInfo for ${item.name}`);
        }
      } else {
        console.log(`  👶 Added ${children.length} children to ${item.name}`);
      }
      
    } catch (error: any) {
      console.error('❌ addItemChildren failed:', error.message);
    }
  }

  private mapOutTypeToString(outType: number): string {
    // Map NodePinType enum values to readable strings
    // From OctaneTypes.js NodePinType enum
    const typeMap: Record<number, string> = {
      1: 'Bool',
      2: 'Float',
      3: 'Int',
      4: 'Transform',
      5: 'Texture',
      6: 'Emission',
      7: 'Material',
      8: 'Camera',
      9: 'Environment',
      10: 'Imager',
      11: 'Kernel',
      12: 'Geometry',
      13: 'Medium',
      15: 'Film Settings',
      16: 'Enum',
      18: 'Postprocessing',
      19: 'Render Target',
      22: 'Displacement',
      23: 'String',
      24: 'Render Passes',
      25: 'Render Layer',
      27: 'Animation Settings',
      37: 'Output AOV Group'
    };
    
    if (outType >= 50000 && outType <= 50136) {
      return 'Material';
    }
    
    return typeMap[outType] || `Type${outType}`;
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
