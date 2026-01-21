import { Node as ReactFlowNode, Edge as ReactFlowEdge } from '@xyflow/react';
import { Endpoint } from './endpoints';

export type NodeType = 'aiEndpoint' | 'image' | 'video' | 'textInput' | 'output';

export interface AIEndpointNodeData {
  endpoint: Endpoint;
  parameters?: Record<string, unknown>;
  result?: unknown;
}

export interface ImageNodeData {
  url?: string;
  file?: File;
  preview?: string;
}

export interface VideoNodeData {
  url?: string;
  file?: File;
  preview?: string;
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

export type AppNode = ReactFlowNode<NodeData>;
export type AppEdge = ReactFlowEdge;
