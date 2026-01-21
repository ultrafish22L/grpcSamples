import { create } from 'zustand';
import { persist } from 'zustand/middleware';
import { addEdge, applyNodeChanges, applyEdgeChanges, reconnectEdge, Connection, NodeChange, EdgeChange } from '@xyflow/react';
import { Endpoint, AppNode, AppEdge } from '../types';
import { getHandleType, getHandleColorStyle } from '../utils/connectionValidator';
import { otoyAPI } from '../services/api';
import { logger } from '../services/logger';

// Default popular AI models to show in Node Palette
// Based on most-used models by public (Jan 2025)
const DEFAULT_VISIBLE_ENDPOINTS = [
  // === TEXT-TO-IMAGE (Most Popular) ===
  'fal-ai/flux-1/dev',                    // FLUX.1 Dev - 767k downloads, top quality
  'fal-ai/flux-1/schnell',                // FLUX.1 Schnell - 610k downloads, faster
  'fal-ai/flux-1/pro',                    // FLUX.1 Pro - Highest quality
  'fal-ai/stable-diffusion-xl',           // SDXL - 1.86M downloads, ecosystem leader
  'fal-ai/stable-diffusion-v3',           // SD v3 - Latest Stability AI
  'fal-ai/stable-diffusion-v35-large',    // SD 3.5 Large - 86.8k downloads
  'fal-ai/stable-diffusion-v35-medium',   // SD 3.5 Medium - Balanced
  'fal-ai/aura-flow',                     // Aura Flow - Popular alternative
  'stabilityai/stable-diffusion-v1-5',    // SD 1.5 - 1.41M downloads, classic
  'zhipuai/glm-image',                    // GLM-Image - 9.87k downloads
  'tongyi/z-image-turbo',                 // Z-Image-Turbo - 441k downloads
  'qwen/qwen-image-2512',                 // Qwen-Image 2512 - 124k downloads
  
  // === IMAGE-TO-IMAGE / EDITING ===
  'fal-ai/flux-1/dev/image-to-image',     // FLUX image-to-image
  'fal-ai/flux-1/schnell/image-to-image', // FLUX schnell img2img
  'fal-ai/flux-1/dev/redux',              // FLUX Redux
  'fal-ai/clarity-upscaler',              // Clarity Upscaler - Sharp results
  'fal-ai/creative-upscaler',             // Creative Upscaler
  'fal-ai/remove-background',             // Background Removal
  'xinsir/controlnet-union-sdxl',         // ControlNet Union - 107k downloads
  
  // === IMAGE-TO-VIDEO (Most Popular) ===
  'lightricks/ltx-2',                     // LTX-2 - 1.86M downloads, #1 image-to-video
  'lightricks/ltx-video',                 // LTX-Video - 152k downloads
  'fal-ai/hunyuan-video/image-to-video',  // HunyuanVideo - Tencent
  'fal-ai/cogvideox-5b/image-to-video',   // CogVideoX-5B
  'stabilityai/stable-video-diffusion',   // Stable Video Diffusion - 117k downloads
  'wan-ai/wan2.2-i2v-a14b',               // Wan2.2 I2V - 9.22k downloads
  'runway/gen-3',                         // Runway Gen-3 - Industry standard
  'kling/video-o1',                       // Kling Video - High quality
  'pika/video-1.5',                       // Pika - User-friendly
  
  // === TEXT-TO-VIDEO (Most Popular) ===
  'tencent/hunyuan-video-1.5',            // HunyuanVideo 1.5 - 489k downloads, #1 open source
  'wan-ai/wan2.1-t2v-14b',                // Wan2.1 T2V - 41.4k downloads
  'wan-ai/wan2.2-t2v-a14b',               // Wan2.2 T2V - 4.23k downloads
  'runway/gen-3/text-to-video',           // Runway Gen-3 T2V
  'kling/video-o1/text-to-video',         // Kling T2V
  'luma/dream-machine',                   // Luma Dream Machine
  'pika/video-2.0',                       // Pika 2.0
  
  // === LARGE LANGUAGE MODELS (Top Intelligence) ===
  'openai/gpt-5.2',                       // GPT-5.2 - Intelligence: 51, top LLM
  'openai/gpt-5.1',                       // GPT-5.1 - Intelligence: 47
  'openai/gpt-4o',                        // GPT-4o - Most popular ChatGPT model
  'openai/gpt-4-turbo',                   // GPT-4 Turbo
  'openai/gpt-3.5-turbo',                 // GPT-3.5 Turbo - Budget option
  'anthropic/claude-opus-4.5',            // Claude Opus 4.5 - Intelligence: 49
  'anthropic/claude-4.5-sonnet',          // Claude 4.5 Sonnet - Developer favorite
  'anthropic/claude-3.5-sonnet',          // Claude 3.5 Sonnet - Popular
  'anthropic/claude-3-opus',              // Claude 3 Opus
  'google/gemini-3-pro',                  // Gemini 3 Pro - Intelligence: 48
  'google/gemini-3-flash',                // Gemini 3 Flash - Intelligence: 46, Speed: 206 t/s
  'google/gemini-2.0-flash',              // Gemini 2.0 Flash - Fast, free tier
  'xai/grok-4',                           // Grok 4 - Intelligence: 41
  'xai/grok-4.1-fast',                    // Grok 4.1 Fast
  'zhipuai/glm-4.7',                      // GLM-4.7 - Intelligence: 42
  'deepseek/v3.2',                        // DeepSeek V3.2 - Best value, $0.30/M tokens
  'meta/llama-4-maverick',                // Llama 4 Maverick - Open source
  'alibaba/qwen-3-235b',                  // Qwen 3 235B
  'mistralai/mistral-large-3',            // Mistral Large 3
  
  // === TEXT-TO-SPEECH & AUDIO ===
  'elevenlabs/speech',                    // ElevenLabs - Most popular TTS
  'openai/tts',                           // OpenAI TTS - Natural, affordable
  'openai/whisper-large-v3',              // Whisper - Speech-to-text
  'azure/neural-tts',                     // Azure Neural TTS
  
  // === MUSIC GENERATION ===
  'suno/v3.5',                            // Suno AI - #1 music generator
  'udio/v1.5',                            // Udio - High quality
  'meta/musicgen',                        // MusicGen - Open source
  'stabilityai/stable-audio',             // Stable Audio
  
  // === 3D GENERATION ===
  'tripo/triposr',                        // TripoSR - Fast, open source
  'meshy/v2',                             // Meshy AI - Commercial leader
  'openai/shap-e',                        // Shap-E - Text-to-3D
  
  // === SPECIAL / CUSTOM ===
  'nano-banana',                          // Nano Banana - Lightweight fast model
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
  viewport?: {
    x: number;
    y: number;
    zoom: number;
  };
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
  viewport: { x: number; y: number; zoom: number };

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
  setNodes: (nodes: AppNode[]) => void;
  setEdges: (edges: AppEdge[]) => void;
  
  addVisibleEndpoint: (endpointId: string) => void;
  removeVisibleEndpoint: (endpointId: string) => void;
  setVisibleEndpoints: (endpointIds: string[]) => void;
  resetVisibleEndpoints: () => void;
  
  setViewport: (viewport: { x: number; y: number; zoom: number }) => void;
  
  saveProject: (name: string) => void;
  saveProjectAs: (name: string) => void;
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
      viewport: { x: 0, y: 0, zoom: 1 },

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
          // Deselect all existing nodes and select the new node
          nodes: [
            ...state.nodes.map(n => ({ ...n, selected: false })),
            { ...node, selected: true }
          ],
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

      setNodes: (nodes) => {
        logger.info('Nodes set', { nodeCount: nodes.length });
        set({ nodes });
      },

      setEdges: (edges) => {
        logger.info('Edges set', { edgeCount: edges.length });
        set({ edges });
      },

      addVisibleEndpoint: (endpointId) => {
        set((state) => {
          if (!state.visibleEndpoints.includes(endpointId)) {
            logger.info('Added endpoint to Node Palette', { endpointId });
            return { visibleEndpoints: [...state.visibleEndpoints, endpointId] };
          }
          return state;
        });
      },

      removeVisibleEndpoint: (endpointId) => {
        set((state) => {
          logger.info('Removed endpoint from Node Palette', { endpointId });
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

      setViewport: (viewport) => {
        set({ viewport });
      },

      saveProject: (name) => {
        const state = get();
        const existingProject = state.currentProject;
        
        if (existingProject) {
          // Update existing project
          const updatedProject: Project = {
            ...existingProject,
            name,
            modified: Date.now(),
            nodes: state.nodes,
            edges: state.edges,
            workflow: { 
              visibleEndpoints: state.visibleEndpoints,
              viewport: state.viewport,
            },
          };
          set((state) => ({
            projects: state.projects.map(p => p.id === updatedProject.id ? updatedProject : p),
            currentProject: updatedProject,
          }));
          logger.info('Project saved (updated)', { name, nodeCount: updatedProject.nodes.length });
        } else {
          // Create new project
          const project: Project = {
            id: `project-${Date.now()}`,
            name,
            created: Date.now(),
            modified: Date.now(),
            nodes: state.nodes,
            edges: state.edges,
            workflow: { 
              visibleEndpoints: state.visibleEndpoints,
              viewport: state.viewport,
            },
          };
          set((state) => ({
            projects: [...state.projects, project],
            currentProject: project,
          }));
          logger.info('Project saved (new)', { name, nodeCount: project.nodes.length });
        }
      },

      saveProjectAs: (name) => {
        const state = get();
        const project: Project = {
          id: `project-${Date.now()}`,
          name,
          created: Date.now(),
          modified: Date.now(),
          nodes: state.nodes,
          edges: state.edges,
          workflow: { 
            visibleEndpoints: state.visibleEndpoints,
            viewport: state.viewport,
          },
        };
        set((state) => ({
          projects: [...state.projects, project],
          currentProject: project,
        }));
        logger.info('Project saved as', { name, nodeCount: project.nodes.length });
      },

      loadProject: (projectId) => {
        const state = get();
        const project = state.projects.find((p) => p.id === projectId);
        if (project) {
          set({
            nodes: project.nodes,
            edges: project.edges,
            visibleEndpoints: project.workflow.visibleEndpoints,
            viewport: project.workflow.viewport || { x: 0, y: 0, zoom: 1 },
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
        // Only persist projects, NOT visibleEndpoints
        // Node Palette should only be saved/loaded via workspace files
        projects: state.projects,
      }),
    }
  )
);
