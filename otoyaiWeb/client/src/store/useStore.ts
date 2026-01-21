import { create } from 'zustand';
import { persist } from 'zustand/middleware';
import { addEdge, applyNodeChanges, applyEdgeChanges, reconnectEdge, Connection, NodeChange, EdgeChange } from '@xyflow/react';
import { Endpoint, AppNode, AppEdge } from '../types';
import { getHandleType, getHandleColorStyle } from '../utils/connectionValidator';
import { otoyAPI } from '../services/api';
import { logger } from '../services/logger';

// Default 8 popular AI models to show in NodeBar
const DEFAULT_VISIBLE_ENDPOINTS = [
  'fal-ai/flux-1/dev',           // FLUX.1 Dev (text-to-image)
  'fal-ai/flux-1/schnell',       // FLUX.1 Schnell (text-to-image, faster)
  'fal-ai/stable-diffusion-v3',  // Stable Diffusion v3 (text-to-image)
  'fal-ai/aura-flow',            // Aura Flow (text-to-image)
  'fal-ai/flux-1/dev/image-to-image', // FLUX image-to-image
  'fal-ai/hunyuan-video/image-to-video', // Hunyuan video
  'fal-ai/cogvideox-5b/image-to-video', // CogVideoX video
  'openai/whisper-large-v3',     // Whisper (speech-to-text)
];

export interface Project {
  id: string;
  name: string;
  created: number;
  modified: number;
  nodes: AppNode[];
  edges: AppEdge[];
  workflow: Workflow;
}

export interface Workflow {
  visibleEndpoints: string[];
}

interface AppState {
  endpoints: Endpoint[];
  loadingEndpoints: boolean;
  nodes: AppNode[];
  edges: AppEdge[];
  selectedCategory: string | null;
  showSettings: boolean;
  visibleEndpoints: string[];
  projects: Project[];
  currentProject: Project | null;

  fetchEndpoints: () => Promise<void>;
  setSelectedCategory: (category: string | null) => void;
  setShowSettings: (show: boolean) => void;
  
  addNode: (node: AppNode) => void;
  updateNode: (nodeId: string, data: Partial<unknown>) => void;
  onNodesChange: (changes: NodeChange[]) => void;
  onEdgesChange: (changes: EdgeChange[]) => void;
  onConnect: (connection: Connection) => void;
  onReconnect: (oldEdge: AppEdge, newConnection: Connection) => void;
  removeEdge: (edgeId: string) => void;
  clearGraph: () => void;
  
  addVisibleEndpoint: (endpointId: string) => void;
  removeVisibleEndpoint: (endpointId: string) => void;
  setVisibleEndpoints: (endpointIds: string[]) => void;
  resetVisibleEndpoints: () => void;
  
  saveProject: (name: string) => void;
  loadProject: (projectId: string) => void;
  deleteProject: (projectId: string) => void;
  newProject: () => void;
  
  saveWorkflow: () => void;
  loadWorkflow: (workflow: Workflow) => void;
}

export const useStore = create<AppState>()(
  persist(
    (set, get) => ({
      endpoints: [],
      loadingEndpoints: false,
      nodes: [],
      edges: [],
      selectedCategory: null,
      showSettings: false,
      visibleEndpoints: DEFAULT_VISIBLE_ENDPOINTS,
      projects: [],
      currentProject: null,

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

      updateNode: (nodeId, data) => {
        set((state) => ({
          nodes: state.nodes.map((node) =>
            node.id === nodeId ? { ...node, data: { ...node.data, ...data } } : node
          ),
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
        const state = get();
        
        // Remove any existing connections to the target handle (inputs can only have one connection)
        const existingEdges = state.edges.filter(
          (edge) => !(edge.target === connection.target && edge.targetHandle === connection.targetHandle)
        );
        
        // Determine the edge color based on the connection type
        const sourceNode = state.nodes.find((n) => n.id === connection.source);
        const handleType = getHandleType(sourceNode, connection.sourceHandle, true);
        const edgeColor = getHandleColorStyle(handleType);
        
        logger.info('Nodes connected', { 
          source: connection.source, 
          target: connection.target,
          handleType,
          color: edgeColor,
          removedOldConnection: existingEdges.length < state.edges.length
        });
        
        // Create the edge with custom styling - color matches the pin type
        const newEdge = {
          ...connection,
          style: { stroke: edgeColor, strokeWidth: 2 },
          animated: false,
        };
        
        set({
          edges: addEdge(newEdge, existingEdges),
        });
      },

      onReconnect: (oldEdge, newConnection) => {
        const state = get();
        
        // Use reconnectEdge utility to handle the edge update
        // This removes the old edge and creates a new one
        let updatedEdges = reconnectEdge(oldEdge, newConnection, state.edges);
        
        // Remove any existing connection to the new target handle (inputs can only have one connection)
        updatedEdges = updatedEdges.filter(
          (edge) => edge.id === oldEdge.id || 
                   !(edge.target === newConnection.target && edge.targetHandle === newConnection.targetHandle)
        );
        
        // Determine the edge color based on the new connection type
        const sourceNode = state.nodes.find((n) => n.id === newConnection.source);
        const handleType = getHandleType(sourceNode, newConnection.sourceHandle, true);
        const edgeColor = getHandleColorStyle(handleType);
        
        logger.info('Edge reconnected', {
          oldEdge: oldEdge.id,
          oldSource: oldEdge.source,
          oldTarget: oldEdge.target,
          newSource: newConnection.source,
          newTarget: newConnection.target,
          handleType,
          color: edgeColor,
        });
        
        // Update the edge style with the correct color
        updatedEdges = updatedEdges.map(edge => 
          edge.id === oldEdge.id
            ? { ...edge, style: { stroke: edgeColor, strokeWidth: 2 }, animated: false }
            : edge
        );
        
        set({ edges: updatedEdges });
      },

      removeEdge: (edgeId) => {
        const state = get();
        const updatedEdges = state.edges.filter((edge) => edge.id !== edgeId);
        logger.info('Edge removed', { edgeId });
        set({ edges: updatedEdges });
      },

      clearGraph: () => {
        logger.info('Graph cleared');
        set({ nodes: [], edges: [] });
      },

      addVisibleEndpoint: (endpointId) => {
        set((state) => {
          if (!state.visibleEndpoints.includes(endpointId)) {
            logger.info('Added endpoint to NodeBar', { endpointId });
            return { visibleEndpoints: [...state.visibleEndpoints, endpointId] };
          }
          return state;
        });
      },

      removeVisibleEndpoint: (endpointId) => {
        set((state) => {
          logger.info('Removed endpoint from NodeBar', { endpointId });
          return {
            visibleEndpoints: state.visibleEndpoints.filter((id) => id !== endpointId),
          };
        });
      },

      setVisibleEndpoints: (endpointIds) => {
        logger.info('Set visible endpoints', { count: endpointIds.length });
        set({ visibleEndpoints: endpointIds });
      },

      resetVisibleEndpoints: () => {
        logger.info('Reset to default endpoints');
        set({ visibleEndpoints: DEFAULT_VISIBLE_ENDPOINTS });
      },

      saveProject: (name) => {
        const state = get();
        const project: Project = {
          id: `project-${Date.now()}`,
          name,
          created: Date.now(),
          modified: Date.now(),
          nodes: state.nodes,
          edges: state.edges,
          workflow: { visibleEndpoints: state.visibleEndpoints },
        };
        set((state) => ({
          projects: [...state.projects, project],
          currentProject: project,
        }));
        logger.info('Project saved', { name, nodeCount: project.nodes.length });
      },

      loadProject: (projectId) => {
        const state = get();
        const project = state.projects.find((p) => p.id === projectId);
        if (project) {
          set({
            nodes: project.nodes,
            edges: project.edges,
            visibleEndpoints: project.workflow.visibleEndpoints,
            currentProject: project,
          });
          logger.info('Project loaded', { name: project.name });
        }
      },

      deleteProject: (projectId) => {
        set((state) => ({
          projects: state.projects.filter((p) => p.id !== projectId),
          currentProject: state.currentProject?.id === projectId ? null : state.currentProject,
        }));
        logger.info('Project deleted', { projectId });
      },

      newProject: () => {
        logger.info('New project created');
        set({
          nodes: [],
          edges: [],
          currentProject: null,
        });
      },

      saveWorkflow: () => {
        const state = get();
        logger.info('Workflow saved', { endpointCount: state.visibleEndpoints.length });
        // Workflow is automatically persisted via zustand middleware
      },

      loadWorkflow: (workflow) => {
        logger.info('Workflow loaded', { endpointCount: workflow.visibleEndpoints.length });
        set({ visibleEndpoints: workflow.visibleEndpoints });
      },
    }),
    {
      name: 'otoyai-storage',
      partialize: (state) => ({
        visibleEndpoints: state.visibleEndpoints,
        projects: state.projects,
      }),
    }
  )
);
