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
        console.log(`🗑️ Deleting node: ${node.handle} (${node.label || node.type || 'unknown'})`);
        const success = await client.deleteNode(String(node.handle));
        
        if (success) {
          successCount++;
          console.log(`✅ Deleted node: ${node.handle}`);
        } else {
          failCount++;
          console.error(`❌ Failed to delete node: ${node.handle}`);
        }
      } catch (error) {
        failCount++;
        console.error(`❌ Error deleting node ${node.handle}:`, error);
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
   * Flow:
   * 1. Copy nodes to clipboard (serialize)
   * 2. Delete nodes from scene
   */
  static async cutNodes(context: EditCommandContext): Promise<boolean> {
    const { selectedNodes } = context;
    
    if (!selectedNodes || selectedNodes.length === 0) {
      console.warn('⚠️ Cut: No nodes selected');
      return false;
    }

    console.log(`✂️ EditCommands.cut: ${selectedNodes.length} node(s)`);
    
    // Copy to clipboard first
    const copied = await this.copyNodes(context);
    if (!copied) {
      console.error('❌ Cut: Failed to copy nodes to clipboard');
      return false;
    }
    
    // Then delete the nodes
    const deleted = await this.deleteNodes(context);
    if (!deleted) {
      console.error('❌ Cut: Failed to delete nodes after copy');
      return false;
    }
    
    console.log('✅ Cut complete');
    return true;
  }

  /**
   * Copy selected nodes to clipboard
   * 
   * Flow:
   * 1. Serialize selected nodes and connections
   * 2. Store in localStorage (browser clipboard API requires user gesture)
   */
  static async copyNodes(context: EditCommandContext): Promise<boolean> {
    const { selectedNodes } = context;
    
    if (!selectedNodes || selectedNodes.length === 0) {
      console.warn('⚠️ Copy: No nodes selected');
      return false;
    }

    console.log(`📋 EditCommands.copy: ${selectedNodes.length} node(s)`);
    
    try {
      // Serialize nodes for clipboard
      const clipboardData = {
        version: '1.0',
        type: 'octane-nodes',
        timestamp: Date.now(),
        nodes: selectedNodes.map(node => ({
          handle: node.handle,
          type: node.type,
          label: node.label,
          // Note: Full serialization would include:
          // - All parameter values (requires getAttribute calls)
          // - Pin connections (requires connection API)
          // - Position data (for paste offset)
          // This is a simplified version for now
        }))
      };
      
      // Store in localStorage (always works, no user gesture required)
      localStorage.setItem('octane-clipboard', JSON.stringify(clipboardData));
      console.log('✅ Copied to clipboard (localStorage)');
      
      // Try browser clipboard API (may fail without user gesture)
      try {
        if (navigator.clipboard && navigator.clipboard.writeText) {
          await navigator.clipboard.writeText(JSON.stringify(clipboardData));
          console.log('✅ Copied to system clipboard');
        }
      } catch (clipError) {
        console.log('ℹ️ System clipboard not available (requires user gesture)');
      }
      
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
   * 1. Read from clipboard
   * 2. Deserialize and validate
   * 3. Create new nodes via API (future implementation)
   * 4. Restore connections (future implementation)
   */
  static async pasteNodes(context: EditCommandContext): Promise<boolean> {
    const { client: _client, onComplete } = context;
    
    console.log('📋 EditCommands.paste: Reading from clipboard...');
    
    try {
      // Try to read from localStorage
      const clipboardText = localStorage.getItem('octane-clipboard');
      if (!clipboardText) {
        console.warn('⚠️ Paste: Clipboard is empty');
        alert('Clipboard is empty\n\nUse Copy or Cut first to add nodes to clipboard.');
        return false;
      }
      
      const clipboardData = JSON.parse(clipboardText);
      
      if (clipboardData.type !== 'octane-nodes') {
        console.warn('⚠️ Paste: Invalid clipboard data type');
        return false;
      }
      
      console.log(`📋 Paste: ${clipboardData.nodes.length} node(s) from clipboard`);
      
      // TODO: Implement full paste functionality
      // This requires:
      // 1. Create new nodes via client.createNode() for each clipboard node
      // 2. Set parameter values via setAttribute for each parameter
      // 3. Restore pin connections via connectPin API
      // 4. Position nodes offset from originals
      
      console.log('ℹ️ Paste: Full implementation requires node duplication API');
      alert(
        `Paste Nodes\n\n` +
        `Found ${clipboardData.nodes.length} node(s) in clipboard.\n\n` +
        `Full paste implementation requires:\n` +
        `• Node creation API (✓ available)\n` +
        `• Parameter copying\n` +
        `• Connection restoration\n` +
        `• Position offset calculation\n\n` +
        `Coming soon!`
      );
      
      if (onComplete) {
        onComplete();
      }
      
      return false; // Not yet fully implemented
    } catch (error) {
      console.error('❌ Paste failed:', error);
      return false;
    }
  }

  /**
   * Duplicate selected nodes
   * 
   * Flow:
   * 1. Copy selected nodes (without deleting)
   * 2. Paste immediately (creates duplicates)
   */
  static async duplicateNodes(context: EditCommandContext): Promise<boolean> {
    console.log('📑 EditCommands.duplicate: Starting...');
    
    const copied = await this.copyNodes(context);
    if (!copied) {
      console.error('❌ Duplicate: Failed to copy nodes');
      return false;
    }
    
    const pasted = await this.pasteNodes(context);
    if (!pasted) {
      console.error('❌ Duplicate: Failed to paste nodes');
      return false;
    }
    
    console.log('✅ Duplicate complete');
    return true;
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
    const { selectedNodes } = context;
    
    if (!selectedNodes || selectedNodes.length < 2) {
      console.warn('⚠️ Group: Need at least 2 nodes selected');
      alert('Group Nodes\n\nSelect at least 2 nodes to create a group.');
      return false;
    }

    console.log(`📦 EditCommands.group: ${selectedNodes.length} node(s)`);
    
    // TODO: Implement grouping
    // This requires:
    // 1. Create NT_GRP_GROUP node via createNode
    // 2. Reparent selected nodes (set owner/parent)
    // 3. Update connections to go through group pins
    alert(
      `Group ${selectedNodes.length} nodes\n\n` +
      `Requires grouping API:\n` +
      `• Create NT_GRP_GROUP node\n` +
      `• Reparent nodes\n` +
      `• Maintain connections\n\n` +
      `Coming soon!`
    );
    
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
    const { selectedNodes } = context;
    
    if (!selectedNodes || selectedNodes.length !== 1) {
      console.warn('⚠️ Ungroup: Select exactly one group node');
      alert('Ungroup\n\nSelect exactly one group node to ungroup.');
      return false;
    }

    const node = selectedNodes[0];
    console.log(`🔓 EditCommands.ungroup: ${node.label || node.handle}`);
    
    // TODO: Check if node is actually a group (check type)
    // TODO: Implement ungrouping
    alert(
      `Ungroup node: ${node.label || node.handle}\n\n` +
      `Requires ungrouping API:\n` +
      `• Extract child nodes\n` +
      `• Delete group container\n` +
      `• Restore connections\n\n` +
      `Coming soon!`
    );
    
    return false; // Not yet implemented
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
