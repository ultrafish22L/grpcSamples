/**
 * Node Service - Node creation, deletion, and connection management
 * Handles node lifecycle and pin connections
 */

import { BaseService } from './BaseService';
import { ApiService } from './ApiService';
import { SceneNode } from './types';
import { SceneService } from './SceneService';

export class NodeService extends BaseService {
  private apiService: ApiService;
  private sceneService: SceneService;

  constructor(emitter: any, serverUrl: string, apiService: ApiService, sceneService: SceneService) {
    super(emitter, serverUrl);
    this.apiService = apiService;
    this.sceneService = sceneService;
  }

  async createNode(nodeType: string, nodeTypeId: number): Promise<number | null> {
    console.log('🔧 Creating node:', nodeType, 'ID:', nodeTypeId);
    
    try {
      const rootResponse = await this.apiService.callApi('ApiProjectManager', 'rootNodeGraph', {});
      if (!rootResponse?.result) {
        console.error('❌ Failed to get root node graph');
        return null;
      }
      
      const owner = rootResponse.result;
      console.log('📦 Root node graph:', owner);
      
      const createResponse = await this.apiService.callApi('ApiNode', 'create', null, {
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
      
      console.log('➕ Adding node to scene tree...');
      await this.sceneService.buildSceneTree(createdNodeHandle);
      
      const newNode = this.sceneService.getNodeByHandle(createdNodeHandle);
      if (newNode) {
        console.log('✅ Node added incrementally - emitting nodeAdded event');
        this.emit('nodeAdded', { node: newNode, handle: createdNodeHandle });
      } else {
        console.error('❌ Failed to find newly created node in scene map');
      }
      
      return createdNodeHandle;
    } catch (error: any) {
      console.error('❌ Error creating node:', error.message);
      return null;
    }
  }

  async deleteNodeOptimized(nodeHandle: number): Promise<boolean> {
    console.log('🗑️ Deleting node (optimized):', nodeHandle);
    
    try {
      const scene = this.sceneService.getScene();
      const node = scene.map.get(nodeHandle);
      
      const collapsedChildren = this.findCollapsedChildren(node);
      console.log(`🔍 Found ${collapsedChildren.length} collapsed children to remove`);
      
      await this.apiService.callApi('ApiItem', 'destroy', nodeHandle, {});
      console.log('✅ Node deleted from Octane');
      
      scene.map.delete(nodeHandle);
      collapsedChildren.forEach(h => scene.map.delete(h));
      
      scene.tree = scene.tree.filter(n => n.handle !== nodeHandle);
      
      console.log('✅ Scene map and tree updated (optimized)');
      
      this.emit('nodeDeleted', { handle: nodeHandle, collapsedChildren });
      
      return true;
    } catch (error: any) {
      console.error('❌ Error deleting node:', error.message);
      return false;
    }
  }

  async deleteNode(nodeHandle: string): Promise<boolean> {
    const handleNum = Number(nodeHandle);
    return this.deleteNodeOptimized(handleNum);
  }

  async connectPinByIndex(
    targetNodeHandle: number,
    pinIdx: number,
    sourceNodeHandle: number,
    evaluate: boolean = true
  ): Promise<void> {
    console.log(`🔌 Connecting pin: target=${targetNodeHandle}, pin=${pinIdx}, source=${sourceNodeHandle}`);
    
    await this.apiService.callApi('ApiNode', 'connectToIx', targetNodeHandle, {
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

  async disconnectPin(
    nodeHandle: number,
    pinIdx: number,
    evaluate: boolean = true
  ): Promise<void> {
    console.log(`🔌 Disconnecting pin: node=${nodeHandle}, pin=${pinIdx}`);
    
    await this.apiService.callApi('ApiNode', 'connectToIx', nodeHandle, {
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

  async handlePinConnectionCleanup(oldSourceHandle: number | null): Promise<void> {
    if (!oldSourceHandle) return;
    
    console.log('🔍 Checking if old source node is collapsed:', oldSourceHandle);
    
    const scene = this.sceneService.getScene();
    
    if (!this.isNodeExpanded(oldSourceHandle)) {
      console.log('🗑️ Removing orphaned collapsed node from map:', oldSourceHandle);
      
      const oldSourceNode = scene.map.get(oldSourceHandle);
      const collapsedChildren = this.findCollapsedChildren(oldSourceNode);
      
      scene.map.delete(oldSourceHandle);
      collapsedChildren.forEach(h => scene.map.delete(h));
      
      console.log(`✅ Removed ${1 + collapsedChildren.length} collapsed nodes from map`);
    } else {
      console.log('✅ Old source is expanded, keeping in scene tree');
    }
    
    this.emit('sceneUpdated', scene);
  }

  private isNodeExpanded(handle: number): boolean {
    const scene = this.sceneService.getScene();
    return scene.tree.some(node => node.handle === handle);
  }

  private findCollapsedChildren(node: SceneNode | undefined): number[] {
    if (!node?.children) return [];
    
    const collapsed: number[] = [];
    const scene = this.sceneService.getScene();
    
    for (const child of node.children) {
      if (!child.handle) continue;
      
      if (!this.isNodeExpanded(child.handle)) {
        collapsed.push(child.handle);
        const grandNode = scene.map.get(child.handle);
        collapsed.push(...this.findCollapsedChildren(grandNode));
      }
    }
    
    return collapsed;
  }
}
