/**
 * OctaneWebR gRPC Client
 * TypeScript React implementation of Octane gRPC communication
 */

import { EventEmitter } from '../utils/EventEmitter';
import { getObjectTypeForService, createObjectPtr, AttributeId } from '../constants/OctaneTypes';

export interface RenderState {
  isRendering: boolean;
  progress: number;
  samples: number;
  renderTime: number;
  resolution: { width: number; height: number };
}

export interface SceneNode {
  handle?: number;  // Optional: will be undefined for unconnected pins
  name: string;
  type: string;  // String type like 'PT_GEOMETRY' from API
  typeEnum?: number;  // Legacy numeric enum (deprecated)
  outType?: string | number;  // Raw API value (octaneWeb uses outType)
  visible?: boolean;
  level?: number;
  children?: SceneNode[];
  graphInfo?: any;
  nodeInfo?: any;
  pinInfo?: any;
  attrInfo?: any;
  icon?: string;
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
      console.log('📡 OctaneClient.connect() - Connecting to server:', this.serverUrl);
      
      // Check server health
      const healthUrl = `${this.serverUrl}/api/health`;
      console.log('📡 Fetching health check:', healthUrl);
      
      const healthResponse = await fetch(healthUrl, {
        method: 'GET',
        headers: { 'Content-Type': 'application/json' }
      });
      
      console.log('📡 Health response status:', healthResponse.status);
      
      if (!healthResponse.ok) {
        const healthData = await healthResponse.json().catch(() => ({}));
        console.error('❌ Server unhealthy:', healthData);
        throw new Error(`Server unhealthy: ${healthResponse.status}`);
      }
      
      const healthData = await healthResponse.json();
      console.log('📡 Health data:', healthData);
      
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
        console.log(`  📦 Created objectPtr:`, body.objectPtr);
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
      console.log(`  📋 Added params:`, params);
    }
    
    console.log(`  📨 Request body:`, JSON.stringify(body));
    
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
      console.log('🔍 Step 1: Getting root node graph...');
      const rootResponse = await this.callApi('ApiProjectManager', 'rootNodeGraph', {});
      if (!rootResponse || !rootResponse.result || !rootResponse.result.handle) {
        throw new Error('Failed to get root node graph');
      }
      
      const rootHandle = rootResponse.result.handle;
      console.log('📍 Root handle:', rootHandle);
      
      // Check if it's a graph
      console.log('🔍 Step 2: Checking if root is graph...');
      const isGraphResponse = await this.callApi('ApiItem', 'isGraph', rootHandle);
      const isGraph = isGraphResponse?.result || false;
      console.log('📍 Is graph:', isGraph);
      
      // Recursively build scene tree starting from root
      // Note: syncSceneRecurse handles building children for level 1 items
      console.log('🔍 Step 3: Building tree recursively...');
      this.scene.tree = await this.syncSceneRecurse(rootHandle, null, isGraph, 0);
      
      console.log('✅ Scene tree built:', this.scene.tree.length, 'top-level items');
      console.log('✅ Scene map has', this.scene.map.size, 'items');
      console.log('🔍 Step 4: Emitting sceneTreeUpdated event...');
      this.emit('sceneTreeUpdated', this.scene);
      console.log('✅ SceneTreeUpdated event emitted');
      
      return this.scene.tree;
    } catch (error: any) {
      console.error('❌ Failed to build scene tree:', error.message);
      console.error('❌ Error stack:', error.stack);
      throw error;
    }
  }

  /**
   * Lookup node data by handle from the scene tree
   */
  lookupItem(handle: number): SceneNode | null {
    return this.scene.map.get(handle) || null;
  }

  /**
   * Get destination nodes for a given node (for connection graph)
   * DISABLED: This function was causing Octane crashes by making too many API calls during recursion
   * 
   * The issue: Calling this during buildSceneTree() recursion multiplies API calls by 3-4x,
   * overwhelming Octane with requests.
   * 
   * TODO: Implement connection mapping AFTER tree is fully built, not during recursive construction.
   * This should be a separate pass over the completed tree to build the connection map.
   */
  /*
  private async getDestination(nodeData: SceneNode): Promise<SceneNode | null> {
    if (!nodeData || !nodeData.handle) {
      return null;
    }
    
    try {
      // Get destination nodes array
      const response = await this.callApi('ApiNode', 'destinationNodes', nodeData.handle);
      if (!response || !response.nodes || !response.nodes.handle) {
        return null;
      }
      
      const handle = response.nodes.handle;
      
      // Get the size of the node array
      const sizeResponse = await this.callApi('ApiNodeArray', 'size1', handle);
      if (!sizeResponse || !sizeResponse.result) {
        return null;
      }
      
      const size = sizeResponse.result;
      
      // Iterate through destination nodes
      for (let i = 0; i < size; i++) {
        const nodeResponse = await this.callApi('ApiNodeArray', 'get1', handle, { index: i });
        if (nodeResponse && nodeResponse.result && nodeResponse.result.handle) {
          const destNode = this.scene.map.get(nodeResponse.result.handle);
          if (destNode) {
            console.log('🔗 getDestination:', nodeData.name, nodeData.handle, '->', destNode.name, destNode.handle);
            return destNode;
          }
        }
      }
    } catch (error: any) {
      console.warn('⚠️ getDestination failed:', error.message);
    }
    
    return null;
  }
  */

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
            console.log(`📍 Before addItemChildren for ${item.name} (handle: ${item.handle})`);
            await this.addItemChildren(item);
            console.log(`📍 After addItemChildren for ${item.name}, children count: ${item.children?.length || 0}`);
            // Small delay to avoid overwhelming Octane
            await new Promise(resolve => setTimeout(resolve, 50));
          }
          console.log(`✅ Finished building children for all level 1 items`);
        }
      } else if (itemHandle != 0) {
        // It's a node - get its input pins and connected nodes
        console.log(`📌 Level ${level}: Processing node pins for handle ${itemHandle}`);
        
        try {
          const pinCountResponse = await this.callApi('ApiNode', 'pinCount', itemHandle);
          const pinCount = pinCountResponse?.result || 0;
          
          console.log(`  Found ${pinCount} pins`);
          
          for (let i = 0; i < pinCount; i++) {
            try {
              // Get connected node for this pin
              const connectedResponse = await this.callApi(
                'ApiNode',
                'connectedNodeIx',
                itemHandle,
                { pinIx: i, enterWrapperNode: true }
              );
              
              const connectedNode = connectedResponse?.result || null;
              
              // Get pin info
              const pinInfoHandleResponse = await this.callApi(
                'ApiNode',
                'pinInfoIx',
                itemHandle,
                { index: i }
              );
              
              if (pinInfoHandleResponse && pinInfoHandleResponse.result && pinInfoHandleResponse.result.handle) {
                const pinInfoResponse = await this.callApi(
                  'ApiNodePinInfoEx',
                  'getApiNodePinInfo',
                  pinInfoHandleResponse.result.handle
                );
                
                const pinInfo = pinInfoResponse?.nodePinInfo || null;
                if (pinInfo) {
                  pinInfo.ix = i;
                  
                  // Add connected node with pin info (connectedNode can be null for unconnected pins)
                  await this.addSceneItem(sceneItems, connectedNode, pinInfo, level);
                }
              }
            } catch (pinError: any) {
              console.warn(`  ⚠️ Failed to load pin ${i}:`, pinError.message);
              // Continue with next pin
            }
          }
        } catch (pinCountError: any) {
          console.error(`  ❌ Failed to get pin count:`, pinCountError.message);
        }
      }
      
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
    // Setup defaults for item properties
    let itemName = item?.name || pinInfo?.staticLabel || 'Unnamed';
    let outType = pinInfo?.outType || '';
    let graphInfo = null;
    let nodeInfo = null;
    let isGraph = false;
    
    // If item has a valid handle, fetch full data from Octane
    if (item != null && item.handle != 0) {
      // Check if already exists at level 1 - reuse existing node
      const existing = this.scene.map.get(item.handle);
      if (existing && existing.handle && existing.level === 1) {
        // TODO: Setup connection info for NodeGraphEditor
        // For now, just reuse the existing node to avoid overwhelming Octane with API calls
        // Connection mapping should be done AFTER full tree is built, not during recursion
        
        // Update existing node's pinInfo
        existing.pinInfo = pinInfo;
        sceneItems.push(existing);
        return existing;
      }
      
      // Fetch item data from Octane
      try {
        // Get item name
        const nameResponse = await this.callApi('ApiItem', 'name', item.handle);
        itemName = nameResponse?.result || 'Unnamed';
        
        // Get outType (node type string like 'PT_GEOMETRY', not numeric enum)
        const outTypeResponse = await this.callApi('ApiItem', 'outType', item.handle);
        outType = outTypeResponse?.result || '';
        
        console.log(`  🔍 API returned outType: "${outType}" (type: ${typeof outType}) for ${itemName}`);
        
        // Check if it's a graph or node
        const isGraphResponse = await this.callApi('ApiItem', 'isGraph', item.handle);
        isGraph = isGraphResponse?.result || false;
        
        if (isGraph) {
          // Get graph info
          const infoResponse = await this.callApi('ApiNodeGraph', 'info1', item.handle);
          graphInfo = infoResponse?.result || null;
        } else {
          // Get node info
          const infoResponse = await this.callApi('ApiNode', 'info', item.handle);
          nodeInfo = infoResponse?.result || null;
        }
        
      } catch (error: any) {
        console.error('❌ addSceneItem failed to fetch item data:', error.message);
      }
    } else {
      // No valid handle - this is an unconnected pin
      // Still create a node entry with pinInfo data (mirrors octaneWeb behavior)
      console.log(`  ⚪ Unconnected pin: ${itemName}`);
    }
    
    // Use pin label if available, otherwise use item name
    const displayName = pinInfo?.staticLabel || itemName;
    const icon = this.getNodeIcon(outType);
    
    // Create entry - even for null items (unconnected pins)
    const entry: SceneNode = {
      level,
      name: displayName,
      handle: item?.handle,  // Will be undefined for unconnected pins
      type: outType,  // Use raw API value (e.g., 'PT_GEOMETRY')
      typeEnum: typeof outType === 'number' ? outType : 0,
      outType: outType,  // octaneWeb uses outType
      icon,
      visible: true,
      graphInfo,
      nodeInfo,
      pinInfo,
      children: []
    };
    
    // Always add to scene items array
    sceneItems.push(entry);
    
    // Only add to scene.map if we have a valid handle
    if (item != null && item.handle != 0) {
      this.scene.map.set(item.handle, entry);
      console.log(`  📄 Added item: ${itemName} (type: "${outType}", icon: ${icon}, level: ${level})`);
      
      // Recursively add children if level > 1 (mirrors octaneWeb lines 548-551)
      if (level > 1) {
        await this.addItemChildren(entry);
      }
    }
    
    return entry;
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
            { id: AttributeId.A_VALUE } // 185 - A_VALUE attribute ID
          );
          
          if (attrInfoResponse?.result && attrInfoResponse.result.type != "AT_UNKNOWN") {
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

  private getNodeIcon(outType: string | number): string {
    // API returns string types like 'PT_GEOMETRY', not numeric enums
    // Reference: octaneWeb/js/utils/OctaneIconMapper.js
    const iconMap: Record<string, string> = {
      // Parameter types
      'PT_BOOL': '☑️',
      'PT_FLOAT': '🔢',
      'PT_INT': '🔢',
      'PT_ENUM': '📋',
      'PT_RGB': '🎨',
      'PT_STRING': '📝',
      'PT_TRANSFORM': '🔄',
      
      // Scene node types
      'PT_RENDER_TARGET': '🎯',
      'PT_RENDERTARGET': '🎯',  // Fallback without underscore
      'PT_MESH': '🫖',
      'PT_GEOMETRY': '🫖',
      'PT_CAMERA': '📷',
      'PT_LIGHT': '💡',
      'PT_MATERIAL': '🎨',
      'PT_EMISSION': '💡',
      'PT_TEXTURE': '🖼️',
      'PT_DISPLACEMENT': '〰️',
      'PT_ENVIRONMENT': '🌍',
      'PT_MEDIUM': '💨',
      
      // Settings and configuration types
      'PT_FILM_SETTINGS': '🎬',
      'PT_ANIMATION_SETTINGS': '⏱️',
      'PT_KERNEL': '🔧',
      'PT_RENDER_LAYER': '🎭',
      'PT_RENDER_PASSES': '📊',
      'PT_OUTPUT_AOV_GROUP': '📤',
      'PT_IMAGER': '📷',
      'PT_POSTPROCESSING': '⚙️',
    };
    
    if (typeof outType === 'string' && iconMap[outType]) {
      return iconMap[outType];
    }
    
    return '⚪';  // Default icon
  }

  // @ts-ignore - Reserved for future use
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

  // @ts-ignore - Used recursively for scene tree traversal
  private updateSceneMap(nodes: SceneNode[]): void {
    for (const node of nodes) {

      if (node.handle != null)   {
        this.scene.map.set(node.handle, node);
        if (node.children && node.children.length > 0) {
          this.updateSceneMap(node.children);
        }
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
