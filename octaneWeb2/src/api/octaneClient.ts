import { ObjectType } from '../constants/octaneTypes'

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

  constructor(serverUrl: string = '/api') {
    // Use relative path '/api' to go through Vite proxy (avoids CORS)
    // In development: /api → Vite proxy → Python proxy (51023) → Octane (51022)
    this.serverUrl = serverUrl
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
      await this.getServerInfo()
      return true
    } catch {
      return false
    }
  }

  async getServerInfo(): Promise<ServerInfo> {
    const response = await this.makeServiceCall(
      'octane.render.RenderServerInfo',
      'GetServerInfo',
      {}
    )
    
    return {
      version: response.version || 'Unknown',
      buildDate: response.buildDate || 'Unknown',
      platform: response.platform || 'Unknown'
    }
  }

  // ============================================================================
  // CORE RPC METHOD
  // ============================================================================

  async makeServiceCall(service: string, method: string, params: any): Promise<any> {
    // URL format: /api/{service}/{method}
    // After Vite proxy rewrite: /{service}/{method}
    // Example: /api/octane.render.RenderServerInfo/GetServerInfo → /octane.render.RenderServerInfo/GetServerInfo
    const url = `${this.serverUrl}/${service}/${method}`
    
    const startTime = performance.now()
    this.callCount++
    
    try {
      const response = await fetch(url, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(params),
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
  // SCENE OPERATIONS
  // ============================================================================

  async getRootNode(): Promise<string> {
    try {
      // Try to get the project root
      const response = await this.makeServiceCall(
        'octane.project.Project',
        'GetActiveProject',
        {}
      )
      return response.handle || '/octane/1'
    } catch (error) {
      console.warn('Could not get active project, using default root')
      return '/octane/1'
    }
  }

  async getNodeInfo(handle: string, type: number): Promise<any> {
    return await this.makeServiceCall(
      'octane.base.Base',
      'GetNodeInfo',
      { objectPtr: { handle, type } }
    )
  }

  async getNodeName(handle: string, type: number): Promise<string> {
    try {
      const response = await this.makeServiceCall(
        'octane.base.Base',
        'GetNodeName',
        { objectPtr: { handle, type } }
      )
      return response.name || 'Unnamed'
    } catch (error) {
      return 'Unknown'
    }
  }

  async getNodeType(handle: string): Promise<number> {
    try {
      const response = await this.makeServiceCall(
        'octane.base.Base',
        'GetNodeType',
        { handle }
      )
      return response.type || ObjectType.NT_UNKNOWN
    } catch (error) {
      return ObjectType.NT_UNKNOWN
    }
  }

  async getNodeChildren(handle: string, type: number): Promise<SceneNode[]> {
    try {
      const response = await this.makeServiceCall(
        'octane.base.Base',
        'GetChildNodes',
        { objectPtr: { handle, type } }
      )
      
      if (!response.children || response.children.length === 0) {
        return []
      }
      
      const children: SceneNode[] = []
      
      for (const child of response.children) {
        const childNode: SceneNode = {
          id: child.handle,
          handle: child.handle,
          name: child.name || 'Unnamed',
          objectType: child.type || ObjectType.NT_UNKNOWN,
          visible: true,
          hasChildren: false, // Will be determined lazily
          children: [],
          parent: handle,
          depth: 0
        }
        children.push(childNode)
      }
      
      return children
    } catch (error) {
      console.error(`Failed to get children for ${handle}:`, error)
      return []
    }
  }

  async getNodeVisible(handle: string, type: number): Promise<boolean> {
    try {
      const response = await this.makeServiceCall(
        'octane.base.Base',
        'GetNodeVisible',
        { objectPtr: { handle, type } }
      )
      return response.visible !== false
    } catch (error) {
      return true
    }
  }

  async setNodeVisible(handle: string, type: number, visible: boolean): Promise<void> {
    await this.makeServiceCall(
      'octane.base.Base',
      'SetNodeVisible',
      { objectPtr: { handle, type }, visible }
    )
  }

  /**
   * Build complete scene tree recursively
   */
  async syncScene(rootHandle: string): Promise<SceneNode[]> {
    console.log('🔄 Syncing scene tree from Octane...')
    
    // Clear cache
    this.sceneCache.clear()
    
    // Get root node type
    const rootType = await this.getNodeType(rootHandle)
    const rootName = await this.getNodeName(rootHandle, rootType)
    
    // Build tree recursively
    const rootNode = await this.buildSceneTree(
      rootHandle,
      rootName,
      rootType,
      0
    )
    
    console.log(`✅ Scene tree synced: ${this.sceneCache.size} nodes`)
    
    return [rootNode]
  }

  /**
   * Recursively build scene tree with depth limiting
   */
  async buildSceneTree(
    handle: string,
    name: string,
    type: number,
    depth: number,
    maxDepth: number = 10
  ): Promise<SceneNode> {
    // Create node
    const node: SceneNode = {
      id: handle,
      handle,
      name,
      objectType: type,
      visible: await this.getNodeVisible(handle, type),
      hasChildren: false,
      children: [],
      depth
    }
    
    // Cache it
    this.sceneCache.set(handle, node)
    
    // Get children if depth allows
    if (depth < maxDepth) {
      const children = await this.getNodeChildren(handle, type)
      
      if (children.length > 0) {
        node.hasChildren = true
        
        // Recursively build children (but only expand first level by default)
        if (depth === 0) {
          for (const child of children) {
            const childNode = await this.buildSceneTree(
              child.handle,
              child.name,
              child.objectType,
              depth + 1,
              maxDepth
            )
            node.children.push(childNode)
          }
        } else {
          // For deeper levels, just add placeholder children (lazy loading)
          node.children = children.map(child => ({
            ...child,
            depth: depth + 1
          }))
        }
      }
    }
    
    return node
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

  async setCameraFov(fov: number): Promise<void> {
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

  /**
   * Get root node graph
   * Service: ApiProjectManager/rootNodeGraph
   */
  async getRootNodeGraph(): Promise<any> {
    return await this.makeServiceCall('ApiProjectManager', 'rootNodeGraph', {})
  }

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
      objectPtr: { handle, type: ObjectType.NT_UNKNOWN }
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
      objectPtr: { handle, type: ObjectType.NT_UNKNOWN }
    })
  }

  /**
   * Get element from node array
   * Service: ApiNodeArray/get1
   */
  async getNodeArrayElement(handle: string, index: number): Promise<any> {
    return await this.makeServiceCall('ApiNodeArray', 'get1', {
      objectPtr: { handle, type: ObjectType.NT_UNKNOWN },
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
      objectPtr: { handle, type: ObjectType.NT_UNKNOWN },
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
  // ============================================================================

  async getNodeParameters(handle: string, type: number): Promise<Parameter[]> {
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
  }

  async getNodeParameter(handle: string, type: number, paramName: string): Promise<any> {
    const response = await this.makeServiceCall(
      'octane.base.Base',
      'GetNodeParameter',
      { objectPtr: { handle, type }, parameterName: paramName }
    )
    return response.value
  }

  async setNodeParameter(handle: string, type: number, paramName: string, value: any): Promise<void> {
    await this.makeServiceCall(
      'octane.base.Base',
      'SetNodeParameter',
      { objectPtr: { handle, type }, parameterName: paramName, value }
    )
  }

  // ============================================================================
  // CALLBACK STREAMING (LIVE RENDERING)
  // ============================================================================

  async registerCallback(callbackType: string, config: CallbackConfig = {}): Promise<string> {
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
  }

  async unregisterCallback(callbackId: string): Promise<void> {
    await this.makeServiceCall(
      'octane.callback.Callback',
      'UnregisterCallback',
      { callbackId }
    )
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
  // ============================================================================

  async getNodeInputs(handle: string, type: number): Promise<any[]> {
    try {
      const response = await this.makeServiceCall(
        'octane.nodegraph.NodeGraph',
        'GetNodeInputs',
        { objectPtr: { handle, type } }
      )
      return response.inputs || []
    } catch (error) {
      return []
    }
  }

  async getNodeOutputs(handle: string, type: number): Promise<any[]> {
    try {
      const response = await this.makeServiceCall(
        'octane.nodegraph.NodeGraph',
        'GetNodeOutputs',
        { objectPtr: { handle, type } }
      )
      return response.outputs || []
    } catch (error) {
      return []
    }
  }

  async getNodeConnections(handle: string, type: number): Promise<any[]> {
    try {
      const response = await this.makeServiceCall(
        'octane.nodegraph.NodeGraph',
        'GetNodeConnections',
        { objectPtr: { handle, type } }
      )
      return response.connections || []
    } catch (error) {
      return []
    }
  }

  async connectNodes(
    sourceHandle: string,
    sourceType: number,
    sourcePin: string,
    targetHandle: string,
    targetType: number,
    targetPin: string
  ): Promise<void> {
    await this.makeServiceCall(
      'octane.nodegraph.NodeGraph',
      'ConnectNodes',
      {
        source: { handle: sourceHandle, type: sourceType },
        sourcePin,
        target: { handle: targetHandle, type: targetType },
        targetPin
      }
    )
  }

  async disconnectNodes(connectionId: string): Promise<void> {
    await this.makeServiceCall(
      'octane.nodegraph.NodeGraph',
      'DisconnectNodes',
      { connectionId }
    )
  }

  // ============================================================================
  // NODE CREATION/DELETION
  // ============================================================================

  async createNode(nodeType: number, name: string, parentHandle: string, parentType: number): Promise<string> {
    const response = await this.makeServiceCall(
      'octane.base.Base',
      'CreateNode',
      {
        nodeType,
        name,
        parent: { handle: parentHandle, type: parentType }
      }
    )
    return response.handle
  }

  async deleteNode(handle: string, type: number): Promise<void> {
    await this.makeServiceCall(
      'octane.base.Base',
      'DeleteNode',
      { objectPtr: { handle, type } }
    )
  }

  async duplicateNode(handle: string, type: number): Promise<string> {
    const response = await this.makeServiceCall(
      'octane.base.Base',
      'DuplicateNode',
      { objectPtr: { handle, type } }
    )
    return response.handle
  }

  // ============================================================================
  // FILE OPERATIONS
  // ============================================================================

  async loadOrbx(filePath: string): Promise<void> {
    await this.makeServiceCall(
      'octane.file.File',
      'LoadOrbx',
      { filePath }
    )
  }

  async saveOrbx(filePath: string): Promise<void> {
    await this.makeServiceCall(
      'octane.file.File',
      'SaveOrbx',
      { filePath }
    )
  }

  async importObj(filePath: string): Promise<string> {
    const response = await this.makeServiceCall(
      'octane.file.File',
      'ImportObj',
      { filePath }
    )
    return response.handle
  }

  async exportImage(filePath: string, width: number, height: number): Promise<void> {
    await this.makeServiceCall(
      'octane.file.File',
      'ExportImage',
      { filePath, width, height }
    )
  }

  // ============================================================================
  // RENDER CONTROL
  // ============================================================================

  async startRender(): Promise<void> {
    await this.makeServiceCall(
      'octane.render.Render',
      'StartRender',
      {}
    )
  }

  async stopRender(): Promise<void> {
    await this.makeServiceCall(
      'octane.render.Render',
      'StopRender',
      {}
    )
  }

  async pauseRender(): Promise<void> {
    await this.makeServiceCall(
      'octane.render.Render',
      'PauseRender',
      {}
    )
  }

  async resumeRender(): Promise<void> {
    await this.makeServiceCall(
      'octane.render.Render',
      'ResumeRender',
      {}
    )
  }

  async getRenderProgress(): Promise<number> {
    try {
      const response = await this.makeServiceCall(
        'octane.render.Render',
        'GetRenderProgress',
        {}
      )
      return response.progress || 0
    } catch (error) {
      return 0
    }
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
