/**
 * Node Service - Node creation, deletion, and connection management
 * Handles node lifecycle and pin connections
 */

import { BaseService } from './BaseService';
import { ApiService } from './ApiService';
import { SceneNode } from './types';
import { SceneService } from './SceneService';
import { ObjectType } from '../../constants/OctaneTypes';

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
        type: ObjectType.ApiNode,
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
        type: ObjectType.ApiNode,
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

  /**
   * Copy a single node (creates a duplicate)
   */
  async copyNode(nodeHandle: number): Promise<number | null> {
    console.log('📋 Copying node:', nodeHandle);
    
    try {
      const rootResponse = await this.apiService.callApi('ApiProjectManager', 'rootNodeGraph', {});
      if (!rootResponse?.result) {
        console.error('❌ Failed to get root node graph');
        return null;
      }
      
      const graphHandle = rootResponse.result;
      
      const copyResponse = await this.apiService.callApi('ApiNodeGraph', 'copyItemTree', graphHandle, {
        rootItem: { handle: nodeHandle }
      });
      
      if (!copyResponse?.result) {
        console.error('❌ Failed to copy node');
        return null;
      }
      
      const copiedNodeHandle = Number(copyResponse.result.handle);
      console.log('✅ Node copied with handle:', copiedNodeHandle);
      
      await this.sceneService.buildSceneTree(copiedNodeHandle);
      
      const newNode = this.sceneService.getNodeByHandle(copiedNodeHandle);
      if (newNode) {
        console.log('✅ Copied node added - emitting nodeAdded event');
        this.emit('nodeAdded', { node: newNode, handle: copiedNodeHandle });
      }
      
      return copiedNodeHandle;
    } catch (error: any) {
      console.error('❌ Error copying node:', error.message);
      return null;
    }
  }

  /**
   * Copy multiple nodes
   */
  async copyNodes(nodeHandles: number[]): Promise<number[]> {
    console.log('📋 Copying multiple nodes:', nodeHandles);
    
    try {
      const rootResponse = await this.apiService.callApi('ApiProjectManager', 'rootNodeGraph', {});
      if (!rootResponse?.result) {
        console.error('❌ Failed to get root node graph');
        return [];
      }
      
      const graphHandle = rootResponse.result;
      
      const sourceItems = nodeHandles.map(h => ({ handle: h }));
      
      const copyResponse = await this.apiService.callApi('ApiNodeGraph', 'copyFrom2', graphHandle, {
        sourceItems: sourceItems,
        sourceItemsCount: sourceItems.length,
        origItems: sourceItems,
        origItemsCount: sourceItems.length
      });
      
      if (!copyResponse?.copiedItems) {
        console.error('❌ Failed to copy nodes');
        return [];
      }
      
      console.log('📋 Copy response:', copyResponse);
      
      const copiedHandles: number[] = [];
      
      if (Array.isArray(copyResponse.copiedItems)) {
        for (const item of copyResponse.copiedItems) {
          if (item?.handle) {
            copiedHandles.push(Number(item.handle));
          }
        }
      } else if (copyResponse.copiedItems?.items) {
        for (const item of copyResponse.copiedItems.items) {
          if (item?.handle) {
            copiedHandles.push(Number(item.handle));
          }
        }
      }
      
      console.log('📋 Extracted copied handles:', copiedHandles);
      
      for (const handle of copiedHandles) {
        await this.sceneService.buildSceneTree(handle);
        const newNode = this.sceneService.getNodeByHandle(handle);
        if (newNode) {
          this.emit('nodeAdded', { node: newNode, handle });
        }
      }
      
      console.log('✅ Copied nodes:', copiedHandles);
      return copiedHandles;
    } catch (error: any) {
      console.error('❌ Error copying nodes:', error.message);
      return [];
    }
  }

  /**
   * Group selected nodes into a group node
   */
  async groupNodes(nodeHandles: number[]): Promise<number | null> {
    console.log('📦 Grouping nodes:', nodeHandles);
    
    try {
      const rootResponse = await this.apiService.callApi('ApiProjectManager', 'rootNodeGraph', {});
      if (!rootResponse?.result) {
        console.error('❌ Failed to get root node graph');
        return null;
      }
      
      const graphHandle = rootResponse.result;
      
      const items = nodeHandles.map(h => ({ handle: h }));
      
      const groupResponse = await this.apiService.callApi('ApiNodeGraph', 'groupItems', graphHandle, {
        items: items,
        itemsCount: items.length
      });
      
      if (!groupResponse?.result) {
        console.error('❌ Failed to group nodes');
        return null;
      }
      
      const groupNodeHandle = Number(groupResponse.result.handle);
      console.log('✅ Group created with handle:', groupNodeHandle);
      
      const scene = this.sceneService.getScene();
      nodeHandles.forEach(h => {
        scene.map.delete(h);
        scene.tree = scene.tree.filter(n => n.handle !== h);
      });
      
      await this.sceneService.buildSceneTree(groupNodeHandle);
      
      const groupNode = this.sceneService.getNodeByHandle(groupNodeHandle);
      if (groupNode) {
        this.emit('nodeAdded', { node: groupNode, handle: groupNodeHandle });
      }
      
      nodeHandles.forEach(h => {
        this.emit('nodeDeleted', { handle: h, collapsedChildren: [] });
      });
      
      return groupNodeHandle;
    } catch (error: any) {
      console.error('❌ Error grouping nodes:', error.message);
      return null;
    }
  }

  /**
   * Ungroup a group node
   */
  async ungroupNode(groupNodeHandle: number): Promise<number[]> {
    console.log('📦 Ungrouping node:', groupNodeHandle);
    
    try {
      const ungroupResponse = await this.apiService.callApi('ApiNodeGraph', 'ungroup', groupNodeHandle, {});
      
      if (!ungroupResponse?.ungroupedItems) {
        console.error('❌ Failed to ungroup node');
        return [];
      }
      
      console.log('📋 Ungroup response:', ungroupResponse);
      
      const ungroupedHandles: number[] = [];
      
      if (Array.isArray(ungroupResponse.ungroupedItems)) {
        for (const item of ungroupResponse.ungroupedItems) {
          if (item?.handle) {
            ungroupedHandles.push(Number(item.handle));
          }
        }
      } else if (ungroupResponse.ungroupedItems?.items) {
        for (const item of ungroupResponse.ungroupedItems.items) {
          if (item?.handle) {
            ungroupedHandles.push(Number(item.handle));
          }
        }
      }
      
      console.log('📋 Extracted ungrouped handles:', ungroupedHandles);
      
      const scene = this.sceneService.getScene();
      scene.map.delete(groupNodeHandle);
      scene.tree = scene.tree.filter(n => n.handle !== groupNodeHandle);
      this.emit('nodeDeleted', { handle: groupNodeHandle, collapsedChildren: [] });
      
      for (const handle of ungroupedHandles) {
        await this.sceneService.buildSceneTree(handle);
        const newNode = this.sceneService.getNodeByHandle(handle);
        if (newNode) {
          this.emit('nodeAdded', { node: newNode, handle });
        }
      }
      
      console.log('✅ Ungrouped into nodes:', ungroupedHandles);
      return ungroupedHandles;
    } catch (error: any) {
      console.error('❌ Error ungrouping node:', error.message);
      return [];
    }
  }

  /**
   * Expand a node (show all children/pins)
   */
  async expandNode(nodeHandle: number): Promise<boolean> {
    console.log('📈 Expanding node:', nodeHandle);
    
    try {
      await this.apiService.callApi('ApiItem', 'expand', nodeHandle, {});
      console.log('✅ Node expanded:', nodeHandle);
      return true;
    } catch (error: any) {
      console.error('❌ Error expanding node:', error.message);
      return false;
    }
  }

  /**
   * Collapse a node (hide children/pins)
   */
  async collapseNode(nodeHandle: number): Promise<boolean> {
    console.log('📉 Collapsing node:', nodeHandle);
    
    try {
      const response = await this.apiService.callApi('ApiItem', 'collapse', nodeHandle, {});
      const collapsed = response?.result || false;
      console.log('✅ Node collapse result:', collapsed);
      return collapsed;
    } catch (error: any) {
      console.error('❌ Error collapsing node:', error.message);
      return false;
    }
  }

  /**
   * Get the position of a node in the graph
   */
  async getNodePosition(nodeHandle: number): Promise<{ x: number; y: number } | null> {
    try {
      const response = await this.apiService.callApi('ApiItem', 'position', nodeHandle, {});
      if (response?.result) {
        return {
          x: response.result.x || 0,
          y: response.result.y || 0
        };
      }
      return null;
    } catch (error: any) {
      console.error('❌ Error getting node position:', error.message);
      return null;
    }
  }

  /**
   * Set the position of a node in the graph
   */
  async setNodePosition(nodeHandle: number, x: number, y: number): Promise<boolean> {
    console.log(`📍 Setting node position: handle=${nodeHandle}, x=${x}, y=${y}`);
    
    try {
      await this.apiService.callApi('ApiItem', 'setPosition', nodeHandle, {
        newPos: { x, y }
      });
      console.log('✅ Node position updated');
      return true;
    } catch (error: any) {
      console.error('❌ Error setting node position:', error.message);
      return false;
    }
  }

  /**
   * Replace a node with a new node of a different type
   * This maintains the connection to the parent pin
   */
  async replaceNode(oldNodeHandle: number, newNodeType: string): Promise<number | null> {
    console.log(`🔄 Replacing node ${oldNodeHandle} with ${newNodeType}`);
    
    try {
      // Get the scene tree to find parent and pin info
      const scene = this.sceneService.getScene();
      const oldNode = scene.map.get(oldNodeHandle);
      
      if (!oldNode) {
        console.error('❌ Old node not found in scene');
        return null;
      }
      
      // Find parent and pin index from pinInfo
      const pinInfo = oldNode.pinInfo;
      const parentHandle = pinInfo?.pinOwner?.handle;
      const pinIdx = pinInfo?.pinId;
      
      if (!parentHandle || pinIdx === undefined) {
        console.error('❌ Could not find parent or pin index for node');
        return null;
      }
      
      console.log(`  Parent: ${parentHandle}, Pin: ${pinIdx}`);
      
      // Get node type ID for the new node type  
      const nodeTypeId = await this.getNodeTypeId(newNodeType);
      if (!nodeTypeId) {
        console.error('❌ Could not get node type ID for', newNodeType);
        return null;
      }
      
      // Create the new node
      const newNodeHandle = await this.createNode(newNodeType, nodeTypeId);
      if (!newNodeHandle) {
        console.error('❌ Failed to create new node');
        return null;
      }
      
      console.log(`✅ Created new node: ${newNodeHandle}`);
      
      // Connect the new node to the parent pin (this replaces the old connection)
      await this.connectPinByIndex(parentHandle, pinIdx, newNodeHandle, true);
      
      console.log(`✅ Connected new node to parent pin`);
      
      // Delete the old node
      await this.deleteNodeOptimized(oldNodeHandle);
      
      console.log(`✅ Deleted old node`);
      
      // Rebuild scene tree to reflect changes
      await this.sceneService.buildSceneTree();
      
      return newNodeHandle;
    } catch (error) {
      console.error('❌ Failed to replace node:', error);
      return null;
    }
  }

  /**
   * Get the numeric ID for a node type string
   */
  private async getNodeTypeId(_nodeType: string): Promise<number | null> {
    // For now, we'll use 1 as a placeholder
    // The API should handle the nodeType string directly
    return 1;
  }

}
