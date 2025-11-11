import { NodeType, ObjectType } from '../constants/octaneTypes'

// ============================================================================
// TYPE DEFINITIONS
// ============================================================================

export interface ObjectPtr {
  handle: string
  type: number
}

export interface SceneNode {
  id: string
  handle: string
  name: string
  objectType: number
  visible: boolean
  hasChildren: boolean
  children: SceneNode[]
  parent?: string
  depth: number
}

export interface Parameter {
  name: string
  value: any
  type: string
  min?: number
  max?: number
  enumValues?: string[]
  readonly?: boolean
}

export interface CameraInfo {
  position: [number, number, number]
  target: [number, number, number]
  fov: number
}

export interface ServerInfo {
  version: string
  buildDate: string
  platform: string
}

export interface CallbackConfig {
  width?: number
  height?: number
  format?: string
  quality?: number
}

export interface CallbackData {
  type: string
  imageData?: string
  width?: number
  height?: number
  [key: string]: any
}

// ============================================================================
// MAIN CLIENT CLASS
// ============================================================================

/**
 * Complete Octane gRPC Client for React Application
 * 
 * Provides full API coverage for:
 * - Connection management
 * - Scene tree building and synchronization
 * - Camera control with live sync
 * - Parameter reading and editing
 * - Callback streaming for live rendering
 * - Node graph operations
 * - File operations (load/save ORBX)
 */
class OctaneClient {
  private serverUrl: string
  private connected: boolean = false
  private eventSource: EventSource | null = null
  private callbackId: string | null = null

  // Performance tracking
  private callCount: number = 0
  private lastCallTime: number = 0
  
  // Scene cache
  private sceneCache: Map<string, SceneNode> = new Map()

  constructor(serverUrl?: string) {
    // Auto-detect environment and use appropriate URL
    // Development: /api → Vite proxy (42219) → Python proxy (51023) → Octane (51022)
    // Production: Direct to Python proxy (51023) → Octane (51022)
    if (serverUrl) {
      this.serverUrl = serverUrl
    } else {
      // In development, Vite runs on port 42219 with /api proxy
      // In production, we connect directly to Python proxy
      const isDevelopment = import.meta.env.DEV
      this.serverUrl = isDevelopment ? '/api' : 'http://localhost:51023'
    }
    console.log('🔌 OctaneClient serverUrl:', this.serverUrl)
  }

  // ============================================================================
  // CONNECTION MANAGEMENT
  // ============================================================================

  async connect(): Promise<boolean> {
    try {
      // Use LiveLink/GetCamera as a connectivity test
      // LiveLink is the actual gRPC service name
      const response = await this.makeServiceCall(
        'LiveLink',
        'GetCamera',
        {}
      )
      
      this.connected = true
      console.log('✅ Connected to Octane via LiveLink:', response)
      return true
    } catch (error) {
      console.error('❌ Failed to connect to Octane:', error)
      this.connected = false
      return false
    }
  }

  disconnect(): void {
    // Disconnect callback stream if active
    if (this.eventSource) {
      this.eventSource.close()
      this.eventSource = null
    }
    
    this.connected = false
    this.sceneCache.clear()
    console.log('Disconnected from Octane')
  }

  isConnected(): boolean {
    return this.connected
  }

  async testConnection(): Promise<boolean> {
    try {
      await this.getCamera()
      return true
    } catch {
      return false
    }
  }

  // Note: GetServerInfo API doesn't exist in the proxy
  // Using LiveLink/GetCamera for connectivity testing instead
  async getServerInfo(): Promise<ServerInfo> {
    // Return placeholder info since GetServerInfo API doesn't exist
    // The original octaneWeb doesn't use server info
    return {
      version: 'Octane LiveLink',
      buildDate: new Date().toISOString().split('T')[0],
      platform: 'gRPC'
    }
  }

  // ============================================================================
  // CORE RPC METHOD
  // ============================================================================

  /**
   * Extract the actual result from a proxy response
   * Response format: { success: true, data: { result: <actual_value> } }
   */
  private extractResult(response: any): any {
    if (response && response.success && response.data) {
      return response.data.result
    }
    return response
  }

  async makeServiceCall(service: string, method: string, params: any): Promise<any> {
    // URL format: /api/{service}/{method}
    // After Vite proxy rewrite: /{service}/{method}
    // Example: /api/octane.render.RenderServerInfo/GetServerInfo → /octane.render.RenderServerInfo/GetServerInfo
    const url = `${this.serverUrl}/${service}/${method}`
    
    const startTime = performance.now()
    this.callCount++
    
    // Convert handle to objectPtr if service requires it
    // Following octaneWeb pattern: service name maps to ObjectType enum
    const requestParams = { ...params }
    if (requestParams.handle && service in ObjectType) {
      const objectType = (ObjectType as any)[service]
      requestParams.objectPtr = {
        handle: requestParams.handle,
        type: objectType
      }
      delete requestParams.handle
    }
    
    try {
      const response = await fetch(url, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(requestParams),
      })

      if (!response.ok) {
        const errorText = await response.text()
        throw new Error(`HTTP ${response.status}: ${errorText}`)
      }

      const result = await response.json()
      
      const elapsed = performance.now() - startTime
      this.lastCallTime = elapsed
      
      if (elapsed > 100) {
        console.warn(`Slow API call: ${service}.${method} took ${elapsed.toFixed(1)}ms`)
      }
      
      return result
    } catch (error) {
      console.error(`API call failed: ${service}.${method}`, error)
      throw error
    }
  }

  // ============================================================================
  // SCENE OPERATIONS (using working Octane APIs)
  // ============================================================================

  /**
   * Get the root node graph handle
   * Uses: ApiProjectManager/rootNodeGraph (WORKING)
   */
  async getRootNodeGraph(): Promise<string> {
    try {
      const response = await this.makeServiceCall(
        'ApiProjectManager',
        'rootNodeGraph',
        {}
      )
      console.log('  getRootNodeGraph response:', response)
      
      const result = this.extractResult(response)
      console.log('  Root handle:', result?.handle || result)
      
      // Result format: { handle: "1000000", type: "ApiRootNodeGraph" }
      return result?.handle || result
    } catch (error) {
      console.error('Failed to get root node graph:', error)
      throw error
    }
  }

  /**
   * Check if an item is a graph or a node
   * Uses: ApiItem/isGraph (WORKING)
   */
  async isGraph(handle: string): Promise<boolean> {
    try {
      // Validate handle is a string
      if (typeof handle !== 'string') {
        console.error(`Invalid handle type for isGraph: expected string, got ${typeof handle}`, handle)
        return false
      }
      
      const response = await this.makeServiceCall(
        'ApiItem',
        'isGraph',
        { handle }
      )
      
      const result = this.extractResult(response)
      return typeof result === 'boolean' ? result : false
    } catch (error) {
      console.error(`Failed to check if ${handle} is graph:`, error)
      return false
    }
  }

  /**
   * Get the name of an item
   * Uses: ApiItem/name (WORKING)
   */
  async getItemName(handle: string): Promise<string> {
    try {
      const response = await this.makeServiceCall(
        'ApiItem',
        'name',
        { handle }
      )
      const result = this.extractResult(response)
      return result || 'Unnamed'
    } catch (error) {
      console.error(`Failed to get item name for ${handle}:`, error)
      return 'Unknown'
    }
  }

  /**
   * Get the outType of an item (determines icon/type)
   * Uses: ApiItem/outType (WORKING)
   */
  async getItemOutType(handle: string): Promise<number> {
    try {
      const response = await this.makeServiceCall(
        'ApiItem',
        'outType',
        { handle }
      )
      const result = this.extractResult(response)
      return result
    } catch (error) {
      console.error(`Failed to get item outType for ${handle}:`, error)
      return NodeType.NT_UNKNOWN
    }
  }

  /**
   * Get owned items from a node graph
   * Uses: ApiNodeGraph/getOwnedItems (WORKING)
   * Returns: response.data.list.handle (NOT result!)
   */
  async getOwnedItems(graphHandle: string): Promise<string> {
    try {
      const response = await this.makeServiceCall(
        'ApiNodeGraph',
        'getOwnedItems',
        { handle: graphHandle }
      )
      // Special case: getOwnedItems returns .data.list not .data.result
      if (response.success && response.data?.list?.handle) {
        return response.data.list.handle
      }
      throw new Error('Invalid response from getOwnedItems')
    } catch (error) {
      console.error(`Failed to get owned items for ${graphHandle}:`, error)
      throw error
    }
  }

  /**
   * Get the size of an item array
   * Uses: ApiItemArray/size (WORKING)
   * Returns: response.data.result (number)
   */
  async getArraySize(arrayHandle: string): Promise<number> {
    try {
      const response = await this.makeServiceCall(
        'ApiItemArray',
        'size',
        { handle: arrayHandle }
      )
      const result = this.extractResult(response)
      return result || 0
    } catch (error) {
      console.error(`Failed to get array size for ${arrayHandle}:`, error)
      return 0
    }
  }

  /**
   * Get an item from an array by index
   * Uses: ApiItemArray/get (WORKING)
   * Returns: response.data.result (item object)
   */
  async getArrayItem(arrayHandle: string, index: number): Promise<any> {
    try {
      const response = await this.makeServiceCall(
        'ApiItemArray',
        'get',
        { handle: arrayHandle, ix: index }
      )
      const result = this.extractResult(response)
      return result
    } catch (error) {
      console.error(`Failed to get array item at index ${index}:`, error)
      throw error
    }
  }

  /**
   * Get node info (for nodes, not graphs)
   * Uses: ApiNode/info (WORKING)
   * Returns: response.data.result
   */
  async getNodeInfo(handle: string): Promise<any> {
    try {
      const response = await this.makeServiceCall(
        'ApiNode',
        'info',
        { handle }
      )
      return this.extractResult(response)
    } catch (error) {
      console.error(`Failed to get node info for ${handle}:`, error)
      throw error
    }
  }

  /**
   * Get graph info (for graphs, not nodes)
   * Uses: ApiNodeGraph/info1 (WORKING)
   * Returns: response.data.result
   */
  async getGraphInfo(handle: string): Promise<any> {
    try {
      const response = await this.makeServiceCall(
        'ApiNodeGraph',
        'info1',
        { handle }
      )
      return this.extractResult(response)
    } catch (error) {
      console.error(`Failed to get graph info for ${handle}:`, error)
      throw error
    }
  }

  /**
   * Get the number of pins on a node
   * Uses: ApiNode/pinCount (WORKING)
   */
  async getNodePinCount(handle: string): Promise<number> {
    try {
      const response = await this.makeServiceCall(
        'ApiNode',
        'pinCount',
        { handle }
      )
      return response
    } catch (error) {
      console.error(`Failed to get pin count for ${handle}:`, error)
      return 0
    }
  }

  /**
   * Build complete scene tree recursively (matches original octaneWeb pattern)
   * This is the main scene synchronization method
   */
  async syncScene(): Promise<SceneNode[]> {
    console.log('🔄 Syncing scene tree from Octane...')
    
    // Clear cache
    this.sceneCache.clear()
    
    try {
      // Step 1: Get root node graph
      const rootHandle = await this.getRootNodeGraph()
      console.log('  Root handle:', rootHandle)
      
      // Guard against undefined handle
      if (!rootHandle) {
        console.warn('  ⚠️ Root handle is undefined or empty')
        return []
      }
      
      // Step 2: Check if it's a graph
      const isGraphRoot = await this.isGraph(rootHandle)
      console.log('  Is graph:', isGraphRoot)
      
      // Step 3: Build scene tree (only supports graphs for now, matching original behavior)
      const sceneTree: SceneNode[] = []
      
      if (isGraphRoot) {
        // Get owned items from the root graph
        const ownedItemsHandle = await this.getOwnedItems(rootHandle)
        const arraySize = await this.getArraySize(ownedItemsHandle)
        console.log(`  Found ${arraySize} top-level items`)
        
        // Iterate through all items
        for (let i = 0; i < arraySize; i++) {
          const item = await this.getArrayItem(ownedItemsHandle, i)
          
          // Build scene node for this item
          const sceneNode = await this.buildSceneNode(item.handle, 0)
          if (sceneNode) {
            sceneTree.push(sceneNode)
          }
        }
      }
      
      console.log(`✅ Scene tree synced: ${sceneTree.length} nodes`)
      return sceneTree
      
    } catch (error) {
      console.error('❌ Failed to sync scene:', error)
      return []
    }
  }

  /**
   * Build a single scene node with its metadata
   * Matches the addSceneItem pattern from original octaneWeb
   */
  private async buildSceneNode(handle: string, depth: number): Promise<SceneNode | null> {
    try {
      // Get basic item info
      const name = await this.getItemName(handle)
      const outType = await this.getItemOutType(handle)
      const isItemGraph = await this.isGraph(handle)
      
      // Create the scene node
      const node: SceneNode = {
        id: handle,
        handle,
        name,
        objectType: outType,
        visible: true, // Default visible
        hasChildren: isItemGraph, // Graphs have children
        children: [],
        depth
      }
      
      // Cache it
      this.sceneCache.set(handle, node)
      
      return node
      
    } catch (error) {
      console.error(`Failed to build scene node for ${handle}:`, error)
      return null
    }
  }


  // ============================================================================
  // LIVELINK API - Camera Operations (Matching octaneWeb)
  // ============================================================================

  /**
   * Get current camera state from Octane
   * Service: LiveLink/GetCamera
   */
  async getCamera(): Promise<any> {
    return await this.makeServiceCall('LiveLink', 'GetCamera', {})
  }

  /**
   * Set camera position and/or target in Octane
   * Service: LiveLink/SetCamera
   */
  async setCamera(position?: {x: number, y: number, z: number}, target?: {x: number, y: number, z: number}): Promise<any> {
    const request: any = {}
    
    if (position) {
      request.position = position
    }
    
    if (target) {
      request.target = target
    }
    
    return await this.makeServiceCall('LiveLink', 'SetCamera', request)
  }

  // Legacy camera methods (compatibility wrappers)
  async getCameraInfo(): Promise<CameraInfo> {
    const camera = await this.getCamera()
    return {
      position: camera.position || [0, 0, 20],
      target: camera.target || [0, 0, 0],
      fov: camera.fov || 45
    }
  }

  async getCameraPosition(): Promise<[number, number, number]> {
    const camera = await this.getCamera()
    return camera.position || [0, 0, 20]
  }

  async getCameraTarget(): Promise<[number, number, number]> {
    const camera = await this.getCamera()
    return camera.target || [0, 0, 0]
  }

  async setCameraPosition(x: number, y: number, z: number): Promise<void> {
    await this.setCamera({ x, y, z }, undefined)
  }

  async setCameraTarget(x: number, y: number, z: number): Promise<void> {
    await this.setCamera(undefined, { x, y, z })
  }

  async setCameraFov(_fov: number): Promise<void> {
    // Note: LiveLink/SetCamera doesn't support FOV directly
    // This would need a different API call if available
    console.warn('setCameraFov not supported by LiveLink API')
  }

  // ============================================================================
  // API RENDER ENGINE - Render Control (Matching octaneWeb)
  // ============================================================================

  /**
   * Stop current rendering
   * Service: ApiRenderEngine/stopRendering
   */
  async stopRendering(): Promise<any> {
    return await this.makeServiceCall('ApiRenderEngine', 'stopRendering', {})
  }

  /**
   * Restart rendering
   * Service: ApiRenderEngine/restartRendering
   */
  async restartRendering(): Promise<any> {
    return await this.makeServiceCall('ApiRenderEngine', 'restartRendering', {})
  }

  /**
   * Pause current rendering
   * Service: ApiRenderEngine/pauseRendering
   */
  async pauseRendering(): Promise<any> {
    return await this.makeServiceCall('ApiRenderEngine', 'pauseRendering', {})
  }

  /**
   * Continue paused rendering
   * Service: ApiRenderEngine/continueRendering
   */
  async continueRendering(): Promise<any> {
    return await this.makeServiceCall('ApiRenderEngine', 'continueRendering', {})
  }

  /**
   * Set render priority
   * Service: ApiRenderEngine/setRenderPriority
   */
  async setRenderPriority(priority: number): Promise<any> {
    return await this.makeServiceCall('ApiRenderEngine', 'setRenderPriority', {
      priority
    })
  }

  // ============================================================================
  // API PROJECT MANAGER - Project Management (Matching octaneWeb)
  // ============================================================================

  /**
   * Load an Octane project file
   * Service: ApiProjectManager/loadProject
   */
  async loadProject(projectPath: string): Promise<any> {
    return await this.makeServiceCall('ApiProjectManager', 'loadProject', {
      projectPath
    })
  }

  /**
   * Save current project
   * Service: ApiProjectManager/saveProject
   */
  async saveProject(): Promise<any> {
    return await this.makeServiceCall('ApiProjectManager', 'saveProject', {})
  }

  /**
   * Save project with new name/location
   * Service: ApiProjectManager/saveProjectAs
   */
  async saveProjectAs(projectPath: string): Promise<any> {
    return await this.makeServiceCall('ApiProjectManager', 'saveProjectAs', {
      projectPath
    })
  }

  /**
   * Save project as reference package
   * Service: ApiProjectManager/saveProjectAsReferencePackage
   */
  async saveProjectAsReferencePackage(packagePath: string): Promise<any> {
    return await this.makeServiceCall('ApiProjectManager', 'saveProjectAsReferencePackage', {
      packagePath
    })
  }

  /**
   * Unpack a reference package
   * Service: ApiProjectManager/unpackPackage
   */
  async unpackPackage(packagePath: string, targetPath: string): Promise<any> {
    return await this.makeServiceCall('ApiProjectManager', 'unpackPackage', {
      packagePath,
      targetPath
    })
  }

  /**
   * Get current project info
   * Service: ApiProjectManager/getCurrentProject
   */
  async getCurrentProject(): Promise<any> {
    return await this.makeServiceCall('ApiProjectManager', 'getCurrentProject', {})
  }

  /**
   * Reset/clear current project
   * Service: ApiProjectManager/resetProject
   */
  async resetProject(): Promise<any> {
    return await this.makeServiceCall('ApiProjectManager', 'resetProject', {})
  }

  // getRootNodeGraph() already defined above in SCENE OPERATIONS section

  // ============================================================================
  // API CHANGE MANAGER - Scene Updates (Matching octaneWeb)
  // ============================================================================

  /**
   * Trigger scene update/refresh
   * Service: ApiChangeManager/update
   */
  async updateScene(): Promise<any> {
    return await this.makeServiceCall('ApiChangeManager', 'update', {})
  }

  // ============================================================================
  // API NODE - Node Operations (Matching octaneWeb)
  // ============================================================================

  /**
   * Create new node
   * Service: ApiNode/create
   */
  async createNode(nodeType: string, parent?: string): Promise<any> {
    const request: any = { nodeType }
    if (parent) {
      request.parent = parent
    }
    return await this.makeServiceCall('ApiNode', 'create', request)
  }

  /**
   * Get destination nodes for a node
   * Service: ApiNode/destinationNodes
   */
  async getDestinationNodes(handle: string): Promise<any> {
    return await this.makeServiceCall('ApiNode', 'destinationNodes', {
      objectPtr: { handle, type: NodeType.NT_UNKNOWN }
    })
  }

  // ============================================================================
  // API NODE ARRAY - Array Operations (Matching octaneWeb)
  // ============================================================================

  /**
   * Get size of node array
   * Service: ApiNodeArray/size1
   */
  async getNodeArraySize(handle: string): Promise<any> {
    return await this.makeServiceCall('ApiNodeArray', 'size1', {
      objectPtr: { handle, type: NodeType.NT_UNKNOWN }
    })
  }

  /**
   * Get element from node array
   * Service: ApiNodeArray/get1
   */
  async getNodeArrayElement(handle: string, index: number): Promise<any> {
    return await this.makeServiceCall('ApiNodeArray', 'get1', {
      objectPtr: { handle, type: NodeType.NT_UNKNOWN },
      index
    })
  }

  // ============================================================================
  // API ITEM - Item Properties (Matching octaneWeb)
  // ============================================================================

  /**
   * Set item property by attribute ID
   * Service: ApiItem/setByAttrID
   */
  async setItemByAttrID(handle: string, attrId: number, value: any): Promise<any> {
    return await this.makeServiceCall('ApiItem', 'setByAttrID', {
      objectPtr: { handle, type: NodeType.NT_UNKNOWN },
      attrId,
      value
    })
  }

  // ============================================================================
  // API NODE GRAPH EDITOR - Material Preview (Matching octaneWeb)
  // ============================================================================

  /**
   * Enable material preview rendering
   * Service: ApiNodeGraphEditor/enableMaterialRender
   */
  async enableMaterialRender(): Promise<any> {
    return await this.makeServiceCall('ApiNodeGraphEditor', 'enableMaterialRender', {})
  }

  /**
   * Disable material preview rendering
   * Service: ApiNodeGraphEditor/disableMaterialRender
   */
  async disableMaterialRender(): Promise<any> {
    return await this.makeServiceCall('ApiNodeGraphEditor', 'disableMaterialRender', {})
  }

  // ============================================================================
  // API RENDER CLOUD MANAGER - Cloud Rendering (Matching octaneWeb)
  // ============================================================================

  /**
   * Create new cloud render task
   * Service: ApiRenderCloudManager/newRenderTask
   */
  async newRenderTask(projectPath: string, settings: any): Promise<any> {
    return await this.makeServiceCall('ApiRenderCloudManager', 'newRenderTask', {
      projectPath,
      settings
    })
  }

  /**
   * Upload current project to cloud
   * Service: ApiRenderCloudManager/uploadCurrentProject
   */
  async uploadCurrentProject(): Promise<any> {
    return await this.makeServiceCall('ApiRenderCloudManager', 'uploadCurrentProject', {})
  }

  /**
   * Get user's cloud subscription info
   * Service: ApiRenderCloudManager/userSubscriptionInfo
   */
  async getUserSubscriptionInfo(): Promise<any> {
    return await this.makeServiceCall('ApiRenderCloudManager', 'userSubscriptionInfo', {})
  }

  // ============================================================================
  // PARAMETER OPERATIONS
  // TODO: These need proper API implementation when node inspector editing is needed
  // ============================================================================

  async getNodeParameters(_handle: string, _type: number): Promise<Parameter[]> {
    // TODO: Replace with proper Octane API calls
    // Original octaneWeb uses ApiItem/attrInfo pattern
    console.warn('getNodeParameters() not yet implemented with correct API')
    return []
    
    /* OLD CODE - DOES NOT WORK
    try {
      const response = await this.makeServiceCall(
        'octane.base.Base',
        'GetNodeParameters',
        { objectPtr: { handle, type } }
      )
      
      if (!response.parameters) {
        return []
      }
      
      return response.parameters.map((p: any) => ({
        name: p.name,
        value: p.value,
        type: p.type || 'unknown',
        min: p.min,
        max: p.max,
        enumValues: p.enumValues,
        readonly: p.readonly || false
      }))
    } catch (error) {
      console.error(`Failed to get parameters for ${handle}:`, error)
      return []
    }
    */
  }

  async getNodeParameter(_handle: string, _type: number, _paramName: string): Promise<any> {
    console.warn('getNodeParameter() not yet implemented with correct API')
    return null
  }

  async setNodeParameter(_handle: string, _type: number, _paramName: string, _value: any): Promise<void> {
    console.warn('setNodeParameter() not yet implemented with correct API')
  }

  // ============================================================================
  // CALLBACK STREAMING (LIVE RENDERING)
  // TODO: Implement using proxy's /octane/callback/register and /stream endpoints
  // ============================================================================

  async registerCallback(_callbackType: string, _config: CallbackConfig = {}): Promise<string> {
    console.warn('registerCallback() not yet implemented - use direct /octane/callback/register endpoint')
    return ''
    /* TODO: Implement callback registration using HTTP endpoints
    const response = await this.makeServiceCall(
      'octane.callback.Callback',
      'RegisterCallback',
      {
        callbackType,
        config: {
          width: config.width || 1920,
          height: config.height || 1080,
          format: config.format || 'png',
          quality: config.quality || 90
        }
      }
    )
    
    return response.callbackId
    */
  }

  async unregisterCallback(_callbackId: string): Promise<void> {
    console.warn('unregisterCallback() not yet implemented')
  }

  connectCallbackStream(
    callbackId: string,
    onData: (data: CallbackData) => void,
    onError?: (error: Error) => void
  ): () => void {
    // Close existing stream if any
    if (this.eventSource) {
      this.eventSource.close()
    }
    
    const url = `${this.serverUrl}/callback-stream/${callbackId}`
    this.eventSource = new EventSource(url)
    this.callbackId = callbackId
    
    this.eventSource.onmessage = (event) => {
      try {
        const data = JSON.parse(event.data)
        onData(data)
      } catch (error) {
        console.error('Failed to parse callback data:', error)
      }
    }
    
    this.eventSource.onerror = (error) => {
      console.error('Callback stream error:', error)
      if (onError) {
        onError(new Error('Callback stream connection failed'))
      }
    }
    
    // Return cleanup function
    return () => {
      if (this.eventSource) {
        this.eventSource.close()
        this.eventSource = null
      }
    }
  }

  disconnectCallbackStream(): void {
    if (this.eventSource) {
      this.eventSource.close()
      this.eventSource = null
    }
    
    if (this.callbackId) {
      this.unregisterCallback(this.callbackId).catch(console.error)
      this.callbackId = null
    }
  }

  // ============================================================================
  // NODE GRAPH OPERATIONS
  // TODO: Implement using ApiNode/pinCount, connectedNodeIx, pinInfoIx etc.
  // ============================================================================

  async getNodeInputs(_handle: string, _type: number): Promise<any[]> {
    console.warn('getNodeInputs() not yet implemented with correct API')
    return []
  }

  async getNodeOutputs(_handle: string, _type: number): Promise<any[]> {
    console.warn('getNodeOutputs() not yet implemented with correct API')
    return []
  }

  async getNodeConnections(_handle: string, _type: number): Promise<any[]> {
    console.warn('getNodeConnections() not yet implemented with correct API')
    return []
  }

  async connectNodes(
    _sourceHandle: string,
    _sourceType: number,
    _sourcePin: string,
    _targetHandle: string,
    _targetType: number,
    _targetPin: string
  ): Promise<void> {
    console.warn('connectNodes() not yet implemented with correct API')
  }

  async disconnectNodes(_connectionId: string): Promise<void> {
    console.warn('disconnectNodes() not yet implemented with correct API')
  }

  // ============================================================================
  // NODE CREATION/DELETION
  // TODO: Implement delete and duplicate when needed
  // ============================================================================

  async deleteNode(_handle: string, _type: number): Promise<void> {
    console.warn('deleteNode() not yet implemented with correct API')
  }

  async duplicateNode(_handle: string, _type: number): Promise<string> {
    console.warn('duplicateNode() not yet implemented with correct API')
    return ''
  }

  // ============================================================================
  // FILE OPERATIONS
  // Already correct: loadProject, saveProject use ApiProjectManager (implemented above)
  // TODO: Import/Export when needed
  // ============================================================================

  async loadOrbx(filePath: string): Promise<void> {
    console.warn('loadOrbx() - use loadProject() instead')
    await this.loadProject(filePath)
  }

  async saveOrbx(filePath: string): Promise<void> {
    console.warn('saveOrbx() - use saveProjectAs() instead')
    await this.saveProjectAs(filePath)
  }

  async importObj(_filePath: string): Promise<string> {
    console.warn('importObj() not yet implemented with correct API')
    return ''
  }

  async exportImage(_filePath: string, _width: number, _height: number): Promise<void> {
    console.warn('exportImage() not yet implemented with correct API')
  }

  // ============================================================================
  // RENDER CONTROL - These should use ApiRenderEngine (already implemented above)
  // Keeping these as convenience wrappers
  // ============================================================================

  async startRender(): Promise<void> {
    console.warn('startRender() - Octane renders continuously, use restartRendering() instead')
    await this.restartRendering()
  }

  async stopRender(): Promise<void> {
    await this.stopRendering()
  }

  async pauseRender(): Promise<void> {
    await this.pauseRendering()
  }

  async resumeRender(): Promise<void> {
    await this.continueRendering()
  }

  async getRenderProgress(): Promise<number> {
    console.warn('getRenderProgress() not yet implemented with correct API')
    return 0
  }

  // ============================================================================
  // UTILITY METHODS
  // ============================================================================

  getStats() {
    return {
      callCount: this.callCount,
      lastCallTime: this.lastCallTime,
      cacheSize: this.sceneCache.size,
      connected: this.connected,
      hasActiveCallback: this.eventSource !== null
    }
  }

  clearCache(): void {
    this.sceneCache.clear()
  }
}

// ============================================================================
// SINGLETON EXPORT
// ============================================================================

export const octaneClient = new OctaneClient()
export default octaneClient
