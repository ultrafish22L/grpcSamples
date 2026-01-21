import { Node as ReactFlowNode, Edge as ReactFlowEdge } from '@xyflow/react';
import { Endpoint } from './endpoints';

export type NodeType = 'aiEndpoint' | 'image' | 'video' | 'textInput' | 'output';

export interface AIEndpointNodeData {
  endpoint: Endpoint;
  parameters: Record<string, unknown>;
  result?: unknown;
  isExecuting?: boolean;
  selectedPin?: string; // 'output' or input pin name
}

export interface MediaItem {
  id: string;
  url?: string;
  file?: File;
  preview?: string;
  name?: string;
  collapsed?: boolean;
}

export interface ImageNodeData {
  items: MediaItem[];
}

export interface VideoNodeData {
  items: MediaItem[];
}

export interface TextInputNodeData {
  value: string;
  label?: string;
}

export interface OutputNodeData {
  value?: unknown;
  label?: string;
}

export type NodeData =
  | AIEndpointNodeData
  | ImageNodeData
  | VideoNodeData
  | TextInputNodeData
  | OutputNodeData;

export type AppNode = ReactFlowNode<NodeData & Record<string, unknown>>;
export type AppEdge = ReactFlowEdge;
