/**
 * Unified Edit Commands
 * 
 * Centralized command handlers for all edit operations (cut, copy, paste, delete, etc.)
 * Ensures consistent behavior across all entry points:
 * - Main menu (MenuBar)
 * - Context menus (NodeGraph, SceneOutliner, NodeInspector)
 * - Keyboard shortcuts
 * 
 * These commands integrate with the existing event system:
 * - Commands call OctaneClient API methods
 * - API methods emit events (nodeDeleted, nodeAdded, etc.)
 * - Components listen to events and update their state
 * 
 * This module provides the command layer that coordinates everything.
 */

import { OctaneClient, SceneNode } from '../services/OctaneClient';

export interface EditCommandContext {
  client: OctaneClient;
  selectedNodes: SceneNode[];
  onSelectionClear?: () => void;
  onComplete?: () => void;
}

/**
 * Unified Edit Commands
 * All commands follow the same pattern:
 * 1. Validate input
 * 2. Call OctaneClient API (which emits events)
 * 3. Clear selection if appropriate
 * 4. Call onComplete callback
 */
export class EditCommands {
  /**
   * Delete selected nodes
   * 
   * Flow:
   * 1. Delete each node via client.deleteNode()
   * 2. client.deleteNode → nodeService.deleteNodeOptimized
   * 3. deleteNodeOptimized emits 'nodeDeleted' event
   * 4. SceneOutliner listens and removes from tree
   * 5. NodeGraph syncs via sceneTree prop update
   * 6. Clear selection
   */
  static async deleteNodes(context: EditCommandContext): Promise<boolean> {
    const { client, selectedNodes, onSelectionClear, onComplete } = context;
    
    if (!selectedNodes || selectedNodes.length === 0) {
      console.warn('⚠️ Delete: No nodes selected');
      return false;
    }

    console.log(`🗑️ EditCommands.delete: Deleting ${selectedNodes.length} node(s)...`);
    
    let successCount = 0;
    let failCount = 0;
    
    // Delete all selected nodes
    // Each deleteNode call will emit 'nodeDeleted' event
    for (const node of selectedNodes) {
      try {
        console.log(`🗑️ EditCommands: Deleting node handle=${node.handle} name="${node.name || node.label || 'unknown'}" type="${node.type || 'unknown'}"`);
        const success = await client.deleteNode(String(node.handle));
        
        if (success) {
          successCount++;
          console.log(`✅ EditCommands: Deleted node ${node.handle} - 'nodeDeleted' event should have been emitted`);
        } else {
          failCount++;
          console.error(`❌ EditCommands: Failed to delete node: ${node.handle}`);
        }
      } catch (error) {
        failCount++;
        console.error(`❌ EditCommands: Error deleting node ${node.handle}:`, error);
      }
    }
    
    console.log(`🗑️ Delete complete: ${successCount} succeeded, ${failCount} failed`);
    
    // Clear selection after successful deletion
    if (successCount > 0) {
      if (onSelectionClear) {
        console.log('🔲 Clearing selection after delete');
        onSelectionClear();
      }
      
      if (onComplete) {
        console.log('✅ Delete operation complete - calling onComplete');
        onComplete();
      }
    }
    
    return successCount > 0;
  }

  /**
   * Cut selected nodes to clipboard
   * 
   * Simplified: Just maps to delete for now
   * TODO: Implement full cut/paste when clipboard serialization is ready
   */
  static async cutNodes(context: EditCommandContext): Promise<boolean> {
    const { selectedNodes } = context;
    
    if (!selectedNodes || selectedNodes.length === 0) {
      console.warn('⚠️ Cut: No nodes selected');
      return false;
    }

    console.log(`✂️ EditCommands.cut: ${selectedNodes.length} node(s) - mapping to delete`);
    
    // For now, just delete (no clipboard)
    // TODO: Add clipboard serialization before delete
    const deleted = await this.deleteNodes(context);
    if (!deleted) {
      console.error('❌ Cut: Failed to delete nodes');
      return false;
    }
    
    console.log('✅ Cut complete (deleted)');
    return true;
  }

  /**
   * Copy selected nodes to clipboard
   * 
   * Flow:
   * 1. Store node handles in localStorage
   * 2. Octane will handle duplication on paste using copyFrom2 API
   */
  static async copyNodes(context: EditCommandContext): Promise<boolean> {
    const { selectedNodes } = context;
    
    if (!selectedNodes || selectedNodes.length === 0) {
      console.warn('⚠️ Copy: No nodes selected');
      alert('Copy\n\nNo nodes selected.\n\nSelect one or more nodes first.');
      return false;
    }

    console.log(`📋 EditCommands.copy: ${selectedNodes.length} node(s)`);
    
    try {
      const clipboard = {
        type: 'octane-nodes',
        handles: selectedNodes.map(n => n.handle),
        timestamp: Date.now()
      };
      
      localStorage.setItem('octane-clipboard', JSON.stringify(clipboard));
      console.log('✅ Copied to clipboard (localStorage):', clipboard.handles);
      
      return true;
    } catch (error) {
      console.error('❌ Copy failed:', error);
      return false;
    }
  }

  /**
   * Paste nodes from clipboard
   * 
   * Flow:
   * 1. Read handles from clipboard
   * 2. Use copyNodes API to duplicate them
   * 3. Trigger scene refresh
   */
  static async pasteNodes(context: EditCommandContext): Promise<boolean> {
    const { client, onComplete } = context;
    
    console.log('📋 EditCommands.paste: Reading from clipboard...');
    
    try {
      const clipboardText = localStorage.getItem('octane-clipboard');
      if (!clipboardText) {
        console.warn('⚠️ Paste: Clipboard is empty');
        alert('Clipboard is empty\n\nUse Copy first to add nodes to clipboard.');
        return false;
      }
      
      const clipboard = JSON.parse(clipboardText);
      
      if (clipboard.type !== 'octane-nodes') {
        console.warn('⚠️ Paste: Invalid clipboard data type');
        alert('Invalid clipboard data\n\nClipboard does not contain nodes.');
        return false;
      }
      
      const sourceHandles = clipboard.handles;
      if (!sourceHandles || sourceHandles.length === 0) {
        console.warn('⚠️ Paste: No handles in clipboard');
        alert('Clipboard is empty\n\nNo nodes to paste.');
        return false;
      }
      
      console.log(`📋 Paste: ${sourceHandles.length} node(s) from clipboard`);
      
      const copiedHandles = await client.copyNodes(sourceHandles);
      
      if (copiedHandles.length === 0) {
        console.error('❌ Paste: Failed to copy nodes');
        alert('Paste Failed\n\nFailed to copy nodes from clipboard.');
        return false;
      }
      
      console.log(`✅ Pasted ${copiedHandles.length} node(s)`);
      
      client.emit('forceSceneRefresh');
      
      if (onComplete) {
        onComplete();
      }
      
      return true;
    } catch (error) {
      console.error('❌ Paste failed:', error);
      alert(`Paste Failed\n\n${error}`);
      return false;
    }
  }

  /**
   * Duplicate selected nodes
   * 
   * Flow:
   * 1. Use copyNodes API directly (no clipboard)
   * 2. Trigger scene refresh
   */
  static async duplicateNodes(context: EditCommandContext): Promise<boolean> {
    const { client, selectedNodes, onComplete } = context;
    
    if (!selectedNodes || selectedNodes.length === 0) {
      console.warn('⚠️ Duplicate: No nodes selected');
      alert('Duplicate\n\nNo nodes selected.\n\nSelect one or more nodes first.');
      return false;
    }

    console.log(`📑 EditCommands.duplicate: ${selectedNodes.length} node(s)`);
    
    try {
      const sourceHandles = selectedNodes.map(n => n.handle).filter((h): h is number => h !== undefined);
      const copiedHandles = await client.copyNodes(sourceHandles);
      
      if (copiedHandles.length === 0) {
        console.error('❌ Duplicate: Failed to duplicate nodes');
        alert('Duplicate Failed\n\nFailed to duplicate selected nodes.');
        return false;
      }
      
      console.log(`✅ Duplicated ${copiedHandles.length} node(s)`);
      
      client.emit('forceSceneRefresh');
      
      if (onComplete) {
        onComplete();
      }
      
      return true;
    } catch (error) {
      console.error('❌ Duplicate failed:', error);
      alert(`Duplicate Failed\n\n${error}`);
      return false;
    }
  }

  /**
   * Group selected nodes
   * 
   * Flow:
   * 1. Validate selection (need 2+ nodes)
   * 2. Create NT_GRP_GROUP node
   * 3. Reparent selected nodes to group
   * 4. Preserve external connections
   */
  static async groupNodes(context: EditCommandContext): Promise<boolean> {
    const { client, selectedNodes, onComplete } = context;
    
    if (!selectedNodes || selectedNodes.length < 2) {
      console.warn('⚠️ Group: Need at least 2 nodes selected');
      alert('Group Nodes\n\nSelect at least 2 nodes to create a group.');
      return false;
    }

    console.log(`📦 EditCommands.group: ${selectedNodes.length} node(s) - triggering full resync`);
    
    // TODO: Implement actual grouping API
    // For now, just trigger a full scene resync
    alert(
      `Group ${selectedNodes.length} nodes\n\n` +
      `Grouping API not yet implemented.\n` +
      `Would trigger full scene resync.`
    );
    
    // Trigger full resync
    if (client) {
      console.log('🔄 Group: Triggering full scene resync');
      client.emit('forceSceneRefresh');
    }
    
    onComplete?.();
    return false; // Not yet implemented
  }

  /**
   * Ungroup selected group node
   * 
   * Flow:
   * 1. Validate selection (must be group node)
   * 2. Move child nodes out of group to parent level
   * 3. Delete group node
   * 4. Restore connections
   */
  static async ungroupNodes(context: EditCommandContext): Promise<boolean> {
    const { client, selectedNodes, onComplete } = context;
    
    if (!selectedNodes || selectedNodes.length !== 1) {
      console.warn('⚠️ Ungroup: Select exactly one group node');
      alert('Ungroup\n\nSelect exactly one group node to ungroup.');
      return false;
    }

    const node = selectedNodes[0];
    console.log(`🔓 EditCommands.ungroup: ${node.label || node.handle} - triggering full resync`);
    
    // TODO: Check if node is actually a group (check type)
    // TODO: Implement actual ungrouping API
    // For now, just trigger a full scene resync
    alert(
      `Ungroup node: ${node.label || node.handle}\n\n` +
      `Ungrouping API not yet implemented.\n` +
      `Would trigger full scene resync.`
    );
    
    // Trigger full resync
    if (client) {
      console.log('🔄 Ungroup: Triggering full scene resync');
      client.emit('forceSceneRefresh');
    }
    
    onComplete?.();
    return false; // Not yet implemented
  }

  /**
   * Collapse selected nodes (minimize/fold view)
   * 
   * Flow:
   * 1. Validate selection
   * 2. Update node state to collapsed (full resync for now)
   */
  static async collapseNodes(context: EditCommandContext): Promise<boolean> {
    const { client, selectedNodes, onComplete } = context;
    
    if (!selectedNodes || selectedNodes.length === 0) {
      console.warn('⚠️ Collapse: No nodes selected');
      return false;
    }

    console.log(`📉 EditCommands.collapse: ${selectedNodes.length} node(s) - triggering full resync`);
    
    // TODO: Implement actual collapse API
    // For now, just trigger a full scene resync
    
    // Trigger full resync
    if (client) {
      console.log('🔄 Collapse: Triggering full scene resync');
      client.emit('forceSceneRefresh');
    }
    
    onComplete?.();
    return true;
  }

  /**
   * Expand selected nodes (show all pins/parameters)
   * 
   * Flow:
   * 1. Validate selection
   * 2. Update node state to expanded (full resync for now)
   */
  static async expandNodes(context: EditCommandContext): Promise<boolean> {
    const { client, selectedNodes, onComplete } = context;
    
    if (!selectedNodes || selectedNodes.length === 0) {
      console.warn('⚠️ Expand: No nodes selected');
      return false;
    }

    console.log(`📈 EditCommands.expand: ${selectedNodes.length} node(s) - triggering full resync`);
    
    // TODO: Implement actual expand API
    // For now, just trigger a full scene resync
    
    // Trigger full resync
    if (client) {
      console.log('🔄 Expand: Triggering full scene resync');
      client.emit('forceSceneRefresh');
    }
    
    onComplete?.();
    return true;
  }

  /**
   * Select all nodes in the scene
   * 
   * This is a UI-only operation, doesn't touch Octane API
   */
  static async selectAll(
    allNodes: SceneNode[], 
    onSelectionChange: (nodes: SceneNode[]) => void
  ): Promise<boolean> {
    console.log(`🔲 EditCommands.selectAll: ${allNodes.length} node(s)`);
    
    if (!allNodes || allNodes.length === 0) {
      console.warn('⚠️ Select All: No nodes in scene');
      return false;
    }
    
    // Get all root-level nodes (nodes that are displayed in graph)
    onSelectionChange(allNodes);
    console.log(`✅ Selected ${allNodes.length} node(s)`);
    
    return true;
  }

  /**
   * Find/Search nodes
   * Opens search dialog - implementation depends on component
   */
  static async findNodes(onOpenSearchDialog: () => void): Promise<boolean> {
    console.log('🔍 EditCommands.find: Opening search dialog');
    onOpenSearchDialog();
    return true;
  }
}
