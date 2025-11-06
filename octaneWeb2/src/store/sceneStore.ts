import { create } from 'zustand';
import { SceneData } from '../api/octaneClient';

interface SceneStore {
  sceneData: SceneData;
  selectedNode: string | null;
  expandedNodes: Set<string>;
  loading: boolean;
  
  setSceneData: (data: SceneData) => void;
  selectNode: (handle: string | null) => void;
  toggleNodeExpanded: (handle: string) => void;
  setLoading: (loading: boolean) => void;
}

export const useSceneStore = create<SceneStore>((set) => ({
  sceneData: { nodes: [], connections: [] },
  selectedNode: null,
  expandedNodes: new Set(['scene-root']),
  loading: false,
  
  setSceneData: (data) => set({ sceneData: data }),
  
  selectNode: (handle) => set({ selectedNode: handle }),
  
  toggleNodeExpanded: (handle) => set((state) => {
    const next = new Set(state.expandedNodes);
    if (next.has(handle)) {
      next.delete(handle);
    } else {
      next.add(handle);
    }
    return { expandedNodes: next };
  }),
  
  setLoading: (loading) => set({ loading }),
}));
