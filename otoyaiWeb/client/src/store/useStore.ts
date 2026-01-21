import { create } from 'zustand';
import { addEdge, applyNodeChanges, applyEdgeChanges, Connection, NodeChange, EdgeChange } from '@xyflow/react';
import { Endpoint, AppNode, AppEdge } from '../types';
import { otoyAPI } from '../services/api';
import { logger } from '../services/logger';

interface AppState {
  endpoints: Endpoint[];
  loadingEndpoints: boolean;
  nodes: AppNode[];
  edges: AppEdge[];
  selectedCategory: string | null;
  showSettings: boolean;

  fetchEndpoints: () => Promise<void>;
  setSelectedCategory: (category: string | null) => void;
  setShowSettings: (show: boolean) => void;
  
  addNode: (node: AppNode) => void;
  onNodesChange: (changes: NodeChange[]) => void;
  onEdgesChange: (changes: EdgeChange[]) => void;
  onConnect: (connection: Connection) => void;
  clearGraph: () => void;
}

export const useStore = create<AppState>((set, get) => ({
  endpoints: [],
  loadingEndpoints: false,
  nodes: [],
  edges: [],
  selectedCategory: null,
  showSettings: false,

  fetchEndpoints: async () => {
    set({ loadingEndpoints: true });
    try {
      const data = await otoyAPI.fetchEndpoints();
      set({ endpoints: data.endpoints, loadingEndpoints: false });
    } catch (error) {
      logger.error('Failed to load endpoints', error as Error);
      set({ loadingEndpoints: false });
    }
  },

  setSelectedCategory: (category) => {
    logger.debug('Category selected', { category });
    set({ selectedCategory: category });
  },

  setShowSettings: (show) => {
    set({ showSettings: show });
  },

  addNode: (node) => {
    logger.info('Node added', { type: node.type, id: node.id });
    set((state) => ({
      nodes: [...state.nodes, node],
    }));
  },

  onNodesChange: (changes) => {
    set((state) => ({
      nodes: applyNodeChanges(changes, state.nodes),
    }));
  },

  onEdgesChange: (changes) => {
    set((state) => ({
      edges: applyEdgeChanges(changes, state.edges),
    }));
  },

  onConnect: (connection) => {
    logger.info('Nodes connected', { 
      source: connection.source, 
      target: connection.target 
    });
    set((state) => ({
      edges: addEdge(connection, state.edges),
    }));
  },

  clearGraph: () => {
    logger.info('Graph cleared');
    set({ nodes: [], edges: [] });
  },
}));
