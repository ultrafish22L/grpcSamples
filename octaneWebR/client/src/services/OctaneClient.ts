/**
 * OctaneWebR gRPC Client
 * TypeScript React implementation of Octane gRPC communication
 */

import { EventEmitter } from '../utils/EventEmitter';
import { getObjectTypeForService, createObjectPtr, AttributeId } from '../constants/OctaneTypes';
import { OctaneIconMapper } from '../utils/OctaneIconMapper';

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
  
  // Icon cache: nodeType -> data URI
  private iconCache: Map<string, string> = new Map();
  private iconFetchQueue: Set<string> = new Set();
  private iconFetchInProgress: boolean = false;
  
  // Original camera state (captured on connect/scene load)
  private originalCameraState: any = null;

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
      
      // Capture initial camera state for reset functionality
      try {
        this.originalCameraState = await this.getCamera();
        console.log('📷 Captured original camera state:', this.originalCameraState);
      } catch (error: any) {
        console.warn('⚠️ Could not capture initial camera state:', error.message);
      }
      
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
    
    // Verbose API logging (commented out to reduce log flooding)
    // console.log(`📤 ${service}.${method}`, handle ? `(handle: ${handle})` : '');
    
    // Build request body - following octaneWeb's makeApiCall logic
    let body: any = {};
    
    // If handle is a string or number (typical case), check if service needs objectPtr wrapping
    if (typeof handle === 'string' || typeof handle === 'number') {
      const objectType = getObjectTypeForService(service);
      
      if (objectType !== undefined) {
        // Service requires objectPtr structure
        // Convert handle to string for objectPtr (proto expects string handles)
        body.objectPtr = createObjectPtr(String(handle), objectType);
        // console.log(`  📦 Created objectPtr:`, body.objectPtr);
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
      // console.log(`  📋 Added params:`, params);
    }
    
    // console.log(`  📨 Request body:`, JSON.stringify(body));
    
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
      // console.log(`✅ ${service}.${method} success`);
      return data;
    } catch (error: any) {
      console.error(`❌ ${service}.${method} error:`, error.message);
      throw error;
    }
  }

  // Camera API - Uses LiveLink service (not ApiProjectManager)
  async getCamera(): Promise<any> {
    // LiveLink.GetCamera returns CameraState with position, target, up vectors
    return this.callApi('LiveLink', 'GetCamera', {});
  }

  async setCameraPosition(x: number, y: number, z: number): Promise<void> {
    // LiveLink.SetCamera takes CameraState with optional position, target, up
    await this.callApi('LiveLink', 'SetCamera', {
      position: { x, y, z }
    });
  }

  async setCameraTarget(x: number, y: number, z: number): Promise<void> {
    // LiveLink.SetCamera takes CameraState with optional position, target, up
    await this.callApi('LiveLink', 'SetCamera', {
      target: { x, y, z }
    });
  }

  async setCameraPositionAndTarget(
    posX: number, posY: number, posZ: number,
    targetX: number, targetY: number, targetZ: number
  ): Promise<void> {
    // More efficient: set both position and target in one call
    await this.callApi('LiveLink', 'SetCamera', {
      position: { x: posX, y: posY, z: posZ },
      target: { x: targetX, y: targetY, z: targetZ }
    });
  }
  
  async resetCamera(): Promise<void> {
    // Reset camera to original position captured at connection time
    if (!this.originalCameraState) {
      console.warn('⚠️ No original camera state stored - fetching current as fallback');
      this.originalCameraState = await this.getCamera();
    }
    
    console.log('📷 Resetting camera to original state:', this.originalCameraState);
    await this.callApi('LiveLink', 'SetCamera', this.originalCameraState);
  }

  // Icon API - Query node icons from Octane
  async getNodeIconImage(nodeType: string): Promise<string | null> {
    // Check cache first
    if (this.iconCache.has(nodeType)) {
      return this.iconCache.get(nodeType)!;
    }

    try {
      // Query icon image from Octane via ApiInfo.nodeIconImage
      const response = await this.callApi('ApiInfo', 'nodeIconImage', null, { nodeType });
      
      if (!response || !response.result) {
        console.warn(`⚠️ No icon found for node type: ${nodeType}`);
        return null;
      }

      // Get the image handle from ObjectRef
      const imageHandle = response.result.handle || response.result;
      
      // Get image data - Octane returns image as ApiImage with data
      const imageDataResponse = await this.callApi('ApiImage', 'getData', imageHandle);
      
      if (!imageDataResponse || !imageDataResponse.data) {
        console.warn(`⚠️ No image data for icon: ${nodeType}`);
        return null;
      }

      // Convert image data to data URI
      // Assuming the data is base64 encoded or raw bytes
      const base64Data = imageDataResponse.data;
      const dataUri = `data:image/png;base64,${base64Data}`;
      
      // Cache the icon
      this.iconCache.set(nodeType, dataUri);
      console.log(`✅ Cached icon for: ${nodeType}`);
      
      return dataUri;
    } catch (error: any) {
      console.error(`❌ Failed to fetch icon for ${nodeType}:`, error.message);
      return null;
    }
  }

  // Queue icon for background fetching
  queueIconFetch(nodeType: string): void {
    if (!this.iconCache.has(nodeType) && !this.iconFetchQueue.has(nodeType)) {
      this.iconFetchQueue.add(nodeType);
      // Start background processing if not already running
      this.processIconQueue();
    }
  }

  // Background icon fetching - processes queue without blocking
  private async processIconQueue(): Promise<void> {
    if (this.iconFetchInProgress || this.iconFetchQueue.size === 0) {
      return;
    }

    this.iconFetchInProgress = true;

    try {
      // Process icons one at a time to avoid overwhelming the server
      for (const nodeType of this.iconFetchQueue) {
        this.iconFetchQueue.delete(nodeType);
        
        const icon = await this.getNodeIconImage(nodeType);
        
        if (icon) {
          // Emit event so UI can update
          this.emit('icon-loaded', { nodeType, icon });
        }
        
        // Small delay to prevent flooding
        await new Promise(resolve => setTimeout(resolve, 50));
      }
    } finally {
      this.iconFetchInProgress = false;
      
      // Check if more items were added during processing
      if (this.iconFetchQueue.size > 0) {
        this.processIconQueue();
      }
    }
  }

  // Get cached icon or return null (non-blocking)
  getCachedIcon(nodeType: string): string | null {
    return this.iconCache.get(nodeType) || null;
  }

  // Get node by handle from scene map (for pin connection lookups)
  getNodeByHandle(handle: number): SceneNode | undefined {
    return this.scene.map.get(handle);
  }

  // Scene API - Port of octaneWeb syncScene() implementation
  async buildSceneTree(newNodeHandle?: number): Promise<SceneNode[]> {
    // Optimized update: if a specific node handle is provided, only add that new node
    if (newNodeHandle !== undefined) {
      console.log('➕ Adding new node to scene tree:', newNodeHandle);
      
      try {
          // Add the new node at level 1 (top-level)
          const newNode = await this.addSceneItem(
          this.scene.tree, 
          { handle: newNodeHandle }, 
          null, 
          1
        );
        
        if (newNode) {
          // Build children for the new node
          console.log(`🔄 Building children for new node: ${newNode.name}`);
          await this.addItemChildren(newNode);
                    
          console.log('✅ New node added to scene tree:', newNode.name);
          console.log('✅ Scene tree now has', this.scene.tree.length, 'top-level items');
          console.log('🔍 Emitting sceneTreeUpdated event...');
          this.emit('sceneTreeUpdated', this.scene);
          console.log('✅ SceneTreeUpdated event emitted');
        } else {
          console.error('❌ Failed to create new scene node');
        }
        
        return this.scene.tree;
      } catch (error: any) {
        console.error('❌ Failed to add new node to scene tree:', error.message);
        throw error;
      }
    }
    
    // Full rebuild: no specific handle provided
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
   * Remove node from scene (map and tree) - used for collapsed node cleanup
   */
  removeFromScene(handle: number): void {
    // Remove from map
    this.scene.map.delete(handle);
    
    // Remove from tree - recursively search and remove
    const removeFromArray = (arr: SceneNode[]): boolean => {
      for (let i = 0; i < arr.length; i++) {
        if (arr[i].handle === handle) {
          arr.splice(i, 1);
          return true;
        }
        // Check children recursively
        if (arr[i].children && arr[i].children!.length > 0) {
          if (removeFromArray(arr[i].children!)) {
            return true;
          }
        }
      }
      return false;
    };
    
    removeFromArray(this.scene.tree);
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
          const handleNum = Number(nodeResponse.result.handle);
          const destNode = this.scene.map.get(handleNum);
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
      const handleNum = Number(item.handle);
      const existing = this.scene.map.get(handleNum);
      if (existing && existing.handle) {
        
        // Update existing node's pinInfo
        existing.pinInfo = pinInfo;
        if (level > 1) {
          sceneItems.push(existing);
        }
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
    const icon = this.getNodeIcon(outType, displayName);
    
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
    
    // Always add to scene items array (includes NO_ITEM pins with handle=0)
    sceneItems.push(entry);
    
    // Only add to scene.map if we have a valid handle (skip NO_ITEM with handle=0)
    if (item != null && item.handle != 0) {
      // Normalize handle to number for consistent Map key type (handles come as strings from protobuf)
      const handleNum = Number(item.handle);
      this.scene.map.set(handleNum, entry);
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

  private getNodeIcon(outType: string | number, name?: string): string {
    // Use OctaneIconMapper for consistent icon mapping across the application
    const typeStr = typeof outType === 'string' ? outType : String(outType);
    
    // TODO: Icon fetching disabled - crashes Octane when called during scene sync
    // Will be implemented as a separate background task later
    // this.queueIconFetch(typeStr);
    
    return OctaneIconMapper.getNodeIcon(typeStr, name);
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
        // Normalize handle to number for consistent Map key type
        const handleNum = Number(node.handle);
        this.scene.map.set(handleNum, node);
        if (node.children && node.children.length > 0) {
          this.updateSceneMap(node.children);
        }
      }
    }
  }

  async setNodeVisibility(handle: number, visible: boolean): Promise<void> {
    await this.callApi('ApiSceneOutliner', 'setNodeVisibility', { handle, visible });
  }

  // Render Control API
  // Based on Octane SE Manual - The Render Viewport section
  // https://docs.otoy.com/standaloneSE/TheRenderViewport.html
  
  /**
   * Start or resume rendering
   * If paused, resumes from current state. Otherwise starts new render.
   */
  async startRender(): Promise<void> {
    await this.callApi('ApiRenderEngine', 'continueRendering', {});
    this.renderState.isRendering = true;
    this.emit('renderStateChanged', this.renderState);
  }

  /**
   * Stop rendering - Aborts the rendering process and frees all resources
   */
  async stopRender(): Promise<void> {
    await this.callApi('ApiRenderEngine', 'stopRendering', {});
    this.renderState.isRendering = false;
    this.emit('renderStateChanged', this.renderState);
  }

  /**
   * Pause rendering - Pauses without losing rendered data, keeps GPU memory intact
   */
  async pauseRender(): Promise<void> {
    await this.callApi('ApiRenderEngine', 'pauseRendering', {});
    this.renderState.isRendering = false;
    this.emit('renderStateChanged', this.renderState);
  }

  /**
   * Restart rendering - Halts and restarts at zero samples, keeps loaded contents in memory
   */
  async restartRender(): Promise<void> {
    await this.callApi('ApiRenderEngine', 'restartRendering', {});
    this.renderState.isRendering = true;
    this.renderState.samples = 0;
    this.emit('renderStateChanged', this.renderState);
  }

  /**
   * Get current clay mode from Octane
   * @returns Clay mode: 0 = NONE (off), 1 = GREY, 2 = COLOR
   */
  async getClayMode(): Promise<number> {
    const response = await this.callApi('ApiRenderEngine', 'clayMode', {});
    return response?.result ?? 0;
  }

  /**
   * Set clay mode in Octane
   * @param mode - Clay mode: 0 = NONE (off), 1 = GREY, 2 = COLOR
   */
  async setClayMode(mode: number): Promise<void> {
    await this.callApi('ApiRenderEngine', 'setClayMode', null, { mode });
  }

  /**
   * Get current sub-sampling mode from Octane
   * @returns Sub-sample mode: 1 = NONE, 2 = 2x2, 4 = 4x4
   */
  async getSubSampleMode(): Promise<number> {
    const response = await this.callApi('ApiRenderEngine', 'getSubSampleMode', {});
    return response?.result ?? 1;
  }

  /**
   * Set sub-sampling mode in Octane
   * @param mode - Sub-sample mode: 1 = NONE, 2 = 2x2, 4 = 4x4
   */
  async setSubSampleMode(mode: number): Promise<void> {
    await this.callApi('ApiRenderEngine', 'setSubSampleMode', null, { mode });
  }

  /**
   * Helper: Get Film Settings node handle from Render Target
   * @returns Film Settings node handle, or null if not found
   */
  private async getFilmSettingsNode(): Promise<number | null> {
    try {
      // Get render target
      const renderTargetResponse = await this.callApi('ApiRenderEngine', 'getRenderTargetNode', {});
      if (!renderTargetResponse?.result?.handle) {
        console.warn('⚠️ No render target found');
        return null;
      }
      
      const renderTargetHandle = renderTargetResponse.result.handle;
      
      // Get Film Settings connected to render target (typically pin 15)
      const filmSettingsResponse = await this.callApi('ApiNode', 'connectedNode', renderTargetHandle, { pinIndex: 15 });
      if (!filmSettingsResponse?.result?.handle) {
        console.warn('⚠️ No Film Settings node found');
        return null;
      }
      
      return filmSettingsResponse.result.handle;
    } catch (error: any) {
      console.error('❌ Failed to get Film Settings node:', error.message);
      return null;
    }
  }

  /**
   * Get viewport resolution lock state from Octane Film Settings
   * @returns true if viewport resolution is locked, false otherwise
   */
  async getViewportResolutionLock(): Promise<boolean> {
    try {
      const filmSettingsHandle = await this.getFilmSettingsNode();
      if (!filmSettingsHandle) {
        return false;
      }

      // P_LOCK_RENDER_AOVS = 61460 (0xf014)
      // Find the attribute index
      const attrIndexResponse = await this.callApi('ApiItem', 'findAttr', filmSettingsHandle, { attrId: 61460 });
      if (attrIndexResponse?.result === undefined || attrIndexResponse.result < 0) {
        console.warn('⚠️ P_LOCK_RENDER_AOVS attribute not found');
        return false;
      }

      const attrIndex = attrIndexResponse.result;

      // Get the boolean value using the attribute index as pin index
      const valueResponse = await this.callApi('ApiNode', 'getPinBoolIx', filmSettingsHandle, { pinIx: attrIndex });
      return valueResponse?.result ?? false;
    } catch (error: any) {
      console.error('❌ Failed to get viewport resolution lock:', error.message);
      return false;
    }
  }

  /**
   * Set viewport resolution lock in Octane Film Settings
   * @param locked - true to lock viewport resolution, false to unlock
   */
  async setViewportResolutionLock(locked: boolean): Promise<void> {
    try {
      const filmSettingsHandle = await this.getFilmSettingsNode();
      if (!filmSettingsHandle) {
        throw new Error('Film Settings node not found');
      }

      // P_LOCK_RENDER_AOVS = 61460 (0xf014)
      const attrIndexResponse = await this.callApi('ApiItem', 'findAttr', filmSettingsHandle, { attrId: 61460 });
      if (attrIndexResponse?.result === undefined || attrIndexResponse.result < 0) {
        throw new Error('P_LOCK_RENDER_AOVS attribute not found');
      }

      const attrIndex = attrIndexResponse.result;

      // Set the boolean value
      await this.callApi('ApiNode', 'setPinValueIx', filmSettingsHandle, {
        pinIx: attrIndex,
        value: locked
      });
    } catch (error: any) {
      console.error('❌ Failed to set viewport resolution lock:', error.message);
      throw error;
    }
  }

  // Node Creation API
  /**
   * Create a new node of the specified type in the scene
   * Based on octaneWeb's NodeGraphEditor.createNodeFromType() (line 1356)
   * 
   * @param nodeType - Node type string (e.g., 'NT_MAT_DIFFUSE')
   * @param nodeTypeId - Numeric node type ID from NodeType enum
   * @returns Handle of the created node, or null if creation failed
   */
  async createNode(nodeType: string, nodeTypeId: number): Promise<number | null> {
    console.log('🔧 Creating node:', nodeType, 'ID:', nodeTypeId);
    
    try {
      // Step 1: Get root node graph (owner)
      const rootResponse = await this.callApi('ApiProjectManager', 'rootNodeGraph', {});
      if (!rootResponse?.result) {
        console.error('❌ Failed to get root node graph');
        return null;
      }
      
      const owner = rootResponse.result;
      console.log('📦 Root node graph:', owner);
      
      // Step 2: Create the node
      // ApiNode.create expects: { type: number, ownerGraph: {handle, type}, configurePins: boolean }
      const createResponse = await this.callApi('ApiNode', 'create', null, {
        type: nodeTypeId,
        ownerGraph: owner,
        configurePins: true,
      });
      
      if (!createResponse?.result) {
        console.error('❌ Failed to create node');
        return null;
      }
      
      const createdNodeHandle = Number(createResponse.result.handle);
      console.log('✅ Node created with handle:', createdNodeHandle);
      
      // Step 3: Refresh scene tree
      console.log('🔄 Refreshing scene tree...');
      this.scene.tree = await this.buildSceneTree(createdNodeHandle);
      this.emit('sceneUpdated', this.scene);
      
      return createdNodeHandle;
    } catch (error: any) {
      console.error('❌ Error creating node:', error.message);
      return null;
    }
  }

  /**
   * Check if a node is expanded (exists in scene.tree at root level)
   */
  private isNodeExpanded(handle: number): boolean {
    return this.scene.tree.some(node => node.handle === handle);
  }

  /**
   * Find all collapsed children recursively
   * Collapsed nodes (NOT in scene.tree) will be deleted by Octane when parent is deleted
   */
  private findCollapsedChildren(node: SceneNode | undefined): number[] {
    if (!node?.children) return [];
    
    const collapsed: number[] = [];
    
    for (const child of node.children) {
      if (!child.handle) continue; // Skip unconnected pins
      
      // Check if child is expanded (exists in scene.tree)
      if (!this.isNodeExpanded(child.handle)) {
        collapsed.push(child.handle);
        // Recursively find collapsed grandchildren
        const grandNode = this.scene.map.get(child.handle);
        collapsed.push(...this.findCollapsedChildren(grandNode));
      }
    }
    
    return collapsed;
  }

  /**
   * Handle pin connection cleanup with optimized orphan removal
   * When connecting to an input pin, check if old source was collapsed (not in scene.tree)
   * and remove it from scene.map since Octane will delete it
   */
  async handlePinConnectionCleanup(
    oldSourceHandle: number | null
  ): Promise<void> {
    if (!oldSourceHandle) return;
    
    console.log('🔍 Checking if old source node is collapsed:', oldSourceHandle);
    
    // Check if old source is expanded (in scene.tree)
    if (!this.isNodeExpanded(oldSourceHandle)) {
      // Old source was collapsed → will be deleted by Octane
      console.log('🗑️ Removing orphaned collapsed node from map:', oldSourceHandle);
      
      // Find all collapsed children that will also be deleted
      const oldSourceNode = this.scene.map.get(oldSourceHandle);
      const collapsedChildren = this.findCollapsedChildren(oldSourceNode);
      
      // Remove from scene.map
      this.scene.map.delete(oldSourceHandle);
      collapsedChildren.forEach(h => this.scene.map.delete(h));
      
      console.log(`✅ Removed ${1 + collapsedChildren.length} collapsed nodes from map`);
    } else {
      console.log('✅ Old source is expanded, keeping in scene tree');
    }
    
    // Emit update without full rebuild
    this.emit('sceneUpdated', this.scene);
  }

  /**
   * Delete a node from the scene with optimized cascade (no full rebuild)
   * Expanded children stay in tree, collapsed children are removed
   */
  async deleteNodeOptimized(nodeHandle: number): Promise<boolean> {
    console.log('🗑️ Deleting node (optimized):', nodeHandle);
    
    try {
      const node = this.scene.map.get(nodeHandle);
      
      // Find all collapsed children that will be deleted by Octane
      const collapsedChildren = this.findCollapsedChildren(node);
      console.log(`🔍 Found ${collapsedChildren.length} collapsed children to remove`);
      
      // Delete from Octane
      await this.callApi('ApiItem', 'destroy', nodeHandle, {});
      console.log('✅ Node deleted from Octane');
      
      // Remove from scene.map
      this.scene.map.delete(nodeHandle);
      collapsedChildren.forEach(h => this.scene.map.delete(h));
      
      // Remove from scene.tree (expanded nodes only appear here)
      this.scene.tree = this.scene.tree.filter(n => n.handle !== nodeHandle);
      
      console.log('✅ Scene map and tree updated (optimized)');
      this.emit('sceneUpdated', this.scene);
      
      return true;
    } catch (error: any) {
      console.error('❌ Error deleting node:', error.message);
      return false;
    }
  }

  /**
   * Delete a node from the scene
   * 
   * @param nodeHandle - Handle of the node to delete
   * @returns True if deletion was successful
   */
  async deleteNode(nodeHandle: string): Promise<boolean> {
    const handleNum = Number(nodeHandle);
    return this.deleteNodeOptimized(handleNum);
  }

  /**
   * Connect one node's output to another node's input pin
   * @param targetNodeHandle - Node receiving the connection
   * @param pinIdx - Input pin index on target node
   * @param sourceNodeHandle - Node providing the connection
   * @param evaluate - Whether to evaluate after connection (default: true)
   */
  async connectPinByIndex(
    targetNodeHandle: number,
    pinIdx: number,
    sourceNodeHandle: number,
    evaluate: boolean = true
  ): Promise<void> {
    console.log(`🔌 Connecting pin: target=${targetNodeHandle}, pin=${pinIdx}, source=${sourceNodeHandle}`);
    
    await this.callApi('ApiNode', 'connectToIx', targetNodeHandle, {
      pinIdx,
      sourceNode: {
        handle: sourceNodeHandle,
        type: 17, // ApiNode type
      },
      evaluate,
      doCycleCheck: true,
    });
    
    console.log('✅ Pin connected in Octane');
  }

  /**
   * Disconnect a node's input pin
   * @param nodeHandle - Node with the pin to disconnect
   * @param pinIdx - Input pin index to disconnect
   * @param evaluate - Whether to evaluate after disconnection (default: true)
   */
  async disconnectPin(
    nodeHandle: number,
    pinIdx: number,
    evaluate: boolean = true
  ): Promise<void> {
    console.log(`🔌 Disconnecting pin: node=${nodeHandle}, pin=${pinIdx}`);
    
    // Disconnect by calling connectToIx with empty sourceNode
    await this.callApi('ApiNode', 'connectToIx', nodeHandle, {
      pinIdx,
      sourceNode: {
        handle: 0, // 0 = disconnect
        type: 17,
      },
      evaluate,
      doCycleCheck: true,
    });
    
    console.log('✅ Pin disconnected in Octane');
  }

  // ==================== LocalDB Methods ====================
  
  /**
   * Get the root category of LocalDB
   * Returns category handle that can be used to browse subcategories/packages
   */
  async getLocalDBRoot(): Promise<number | null> {
    try {
      const response = await this.callApi('ApiLocalDB', 'root', null, {});
      if (response?.result?.handle) {
        console.log(`✅ LocalDB root category handle: ${response.result.handle}`);
        return response.result.handle;
      }
      return null;
    } catch (error) {
      console.error('❌ Failed to get LocalDB root:', error);
      return null;
    }
  }

  /**
   * Get the name of a category
   */
  async getCategoryName(categoryHandle: number): Promise<string> {
    try {
      const response = await this.callApi('ApiLocalDB_Category', 'name', categoryHandle, {});
      return response?.result || 'Unknown Category';
    } catch (error) {
      console.error(`❌ Failed to get category name for handle ${categoryHandle}:`, error);
      return 'Error';
    }
  }

  /**
   * Get number of subcategories in a category
   */
  async getSubCategoryCount(categoryHandle: number): Promise<number> {
    try {
      const response = await this.callApi('ApiLocalDB_Category', 'subCategoryCount', categoryHandle, {});
      return response?.result || 0;
    } catch (error) {
      console.error(`❌ Failed to get subcategory count:`, error);
      return 0;
    }
  }

  /**
   * Get a subcategory by index
   */
  async getSubCategory(categoryHandle: number, index: number): Promise<number | null> {
    try {
      const response = await this.callApi('ApiLocalDB_Category', 'subCategory', categoryHandle, { index });
      if (response?.result?.handle) {
        return response.result.handle;
      }
      return null;
    } catch (error) {
      console.error(`❌ Failed to get subcategory at index ${index}:`, error);
      return null;
    }
  }

  /**
   * Get number of packages in a category
   */
  async getPackageCount(categoryHandle: number): Promise<number> {
    try {
      const response = await this.callApi('ApiLocalDB_Category', 'packageCount', categoryHandle, {});
      return response?.result || 0;
    } catch (error) {
      console.error(`❌ Failed to get package count:`, error);
      return 0;
    }
  }

  /**
   * Get a package by index
   */
  async getPackage(categoryHandle: number, index: number): Promise<number | null> {
    try {
      const response = await this.callApi('ApiLocalDB_Category', 'package', categoryHandle, { index });
      if (response?.result?.handle) {
        return response.result.handle;
      }
      return null;
    } catch (error) {
      console.error(`❌ Failed to get package at index ${index}:`, error);
      return null;
    }
  }

  /**
   * Get the name of a package
   */
  async getPackageName(packageHandle: number): Promise<string> {
    try {
      const response = await this.callApi('ApiLocalDB_Package', 'name1', packageHandle, {});
      return response?.result || 'Unknown Package';
    } catch (error) {
      console.error(`❌ Failed to get package name:`, error);
      return 'Error';
    }
  }

  /**
   * Check if package has a thumbnail
   */
  async packageHasThumbnail(packageHandle: number): Promise<boolean> {
    try {
      const response = await this.callApi('ApiLocalDB_Package', 'hasThumbnail', packageHandle, {});
      return response?.result || false;
    } catch (error) {
      console.error(`❌ Failed to check package thumbnail:`, error);
      return false;
    }
  }

  /**
   * Load a package into the current graph
   * @param packageHandle - Handle to the package
   * @param destinationGraphHandle - Handle to destination graph (optional, uses current graph if not provided)
   */
  async loadPackage(packageHandle: number, destinationGraphHandle?: number): Promise<boolean> {
    try {
      // If no destination graph specified, use current render target's graph
      let graphHandle = destinationGraphHandle;
      if (!graphHandle) {
        // Get current render target
        const renderTargetResponse = await this.callApi('ApiScene', 'firstItem', null, { type: 11 }); // PT_RENDERTARGET = 11
        if (renderTargetResponse?.result?.handle) {
          const renderTargetHandle = renderTargetResponse.result.handle;
          // Get graph from render target (pin 0 is typically the graph pin)
          const graphResponse = await this.callApi('ApiNode', 'connectedNode', renderTargetHandle, { pinIndex: 0 });
          if (graphResponse?.result?.handle) {
            graphHandle = graphResponse.result.handle;
          }
        }
      }

      if (!graphHandle) {
        console.error('❌ No graph found to load package into');
        return false;
      }

      const response = await this.callApi('ApiLocalDB_Package', 'loadPackage', packageHandle, {
        destinationGraph: { handle: graphHandle }
      });

      if (response?.result) {
        console.log(`✅ Package loaded into graph (handle: ${graphHandle})`);
        // Refresh scene tree to show new nodes
        this.scene.tree = await this.buildSceneTree();
        this.emit('sceneTreeUpdated', this.scene.tree);
        return true;
      }
      return false;
    } catch (error) {
      console.error(`❌ Failed to load package:`, error);
      return false;
    }
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
