import { create } from 'zustand';
import { octaneClient } from '../api/octaneClient';

interface SceneNode {
  id: string;
  name: string;
  type: string;
  objectPtr: any;
  children: SceneNode[];
  expanded: boolean;
  visible: boolean;
  selected: boolean;
}

interface SceneStore {
  connected: boolean;
  sceneTree: SceneNode[];
  selectedNode: SceneNode | null;
  loading: boolean;
  error: string | null;
  
  setConnected: (connected: boolean) => void;
  loadScene: () => Promise<void>;
  selectNode: (nodeId: string) => void;
  toggleExpanded: (nodeId: string) => void;
  toggleVisibility: (nodeId: string) => void;
}

const findNodeById = (nodes: SceneNode[], id: string): SceneNode | null => {
  for (const node of nodes) {
    if (node.id === id) return node;
    if (node.children.length > 0) {
      const found = findNodeById(node.children, id);
      if (found) return found;
    }
  }
  return null;
};

const updateNodeById = (nodes: SceneNode[], id: string, updates: Partial<SceneNode>): SceneNode[] => {
  return nodes.map(node => {
    if (node.id === id) {
      return { ...node, ...updates };
    }
    if (node.children.length > 0) {
      return { ...node, children: updateNodeById(node.children, id, updates) };
    }
    return node;
  });
};

export const useSceneStore = create<SceneStore>((set, get) => ({
  connected: false,
  sceneTree: [],
  selectedNode: null,
  loading: false,
  error: null,
  
  setConnected: (connected) => set({ connected }),
  
  loadScene: async () => {
    set({ loading: true, error: null });
    try {
      const tree = await octaneClient.syncScene();
      set({ sceneTree: tree, loading: false });
    } catch (error: any) {
      set({ error: error.message, loading: false });
    }
  },
  
  selectNode: (nodeId) => {
    const node = findNodeById(get().sceneTree, nodeId);
    set({ selectedNode: node });
  },
  
  toggleExpanded: (nodeId) => {
    const tree = get().sceneTree;
    const updatedTree = updateNodeById(tree, nodeId, { 
      expanded: !findNodeById(tree, nodeId)?.expanded 
    });
    set({ sceneTree: updatedTree });
  },
  
  toggleVisibility: (nodeId) => {
    const tree = get().sceneTree;
    const updatedTree = updateNodeById(tree, nodeId, { 
      visible: !findNodeById(tree, nodeId)?.visible 
    });
    set({ sceneTree: updatedTree });
  }
}));
