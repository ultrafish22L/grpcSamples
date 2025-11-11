import { create } from 'zustand'
import { octaneClient, SceneNode } from '../api/octaneClient'
import { emitEvent } from '../core/eventBus'

interface SceneStore {
  nodes: SceneNode[]
  selectedNodeId: string | null
  selectedNode: SceneNode | null
  expandedNodes: Set<string>
  loading: boolean
  error: string | null
  
  loadScene: () => Promise<void>
  setNodes: (nodes: SceneNode[]) => void
  selectNode: (nodeId: string | null) => void
  toggleNodeExpanded: (nodeId: string) => void
  setLoading: (loading: boolean) => void
  clearScene: () => void
}

export const useSceneStore = create<SceneStore>((set, get) => ({
  nodes: [],
  selectedNodeId: null,
  selectedNode: null,
  expandedNodes: new Set(),
  loading: false,
  error: null,
  
  loadScene: async () => {
    set({ loading: true, error: null })
    emitEvent('scene:loading', undefined)
    
    try {
      console.log('🔄 Loading scene from Octane...')
      
      // syncScene() now handles getting the root internally
      const sceneTree = await octaneClient.syncScene()
      
      set({
        nodes: sceneTree,
        loading: false,
        expandedNodes: new Set(sceneTree.map(n => n.id)) // Expand root by default
      })
      
      emitEvent('scene:loaded', { nodes: sceneTree })
      console.log('✅ Scene loaded:', sceneTree.length, 'root nodes')
    } catch (error) {
      const errorMsg = error instanceof Error ? error.message : 'Failed to load scene'
      set({
        loading: false,
        error: errorMsg
      })
      emitEvent('scene:error', { error: error as Error })
      console.error('❌ Scene load failed:', errorMsg)
    }
  },
  
  setNodes: (nodes) => set({ nodes }),
  
  selectNode: (nodeId) => {
    if (!nodeId) {
      set({ selectedNodeId: null, selectedNode: null })
      emitEvent('node:deselected', undefined)
      return
    }
    
    // Find node in tree
    const findNode = (nodes: SceneNode[], id: string): SceneNode | null => {
      for (const node of nodes) {
        if (node.id === id) return node
        if (node.children.length > 0) {
          const found = findNode(node.children, id)
          if (found) return found
        }
      }
      return null
    }
    
    const node = findNode(get().nodes, nodeId)
    
    if (node) {
      set({ selectedNodeId: nodeId, selectedNode: node })
      emitEvent('node:selected', { node })
      console.log('Selected node:', node.name)
    }
  },
  
  toggleNodeExpanded: (nodeId) => set((state) => {
    const next = new Set(state.expandedNodes)
    if (next.has(nodeId)) {
      next.delete(nodeId)
    } else {
      next.add(nodeId)
    }
    return { expandedNodes: next }
  }),
  
  setLoading: (loading) => set({ loading }),
  
  clearScene: () => set({
    nodes: [],
    selectedNodeId: null,
    selectedNode: null,
    expandedNodes: new Set(),
    error: null
  })
}))
