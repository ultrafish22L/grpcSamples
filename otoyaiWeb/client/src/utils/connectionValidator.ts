import { Connection, Node } from '@xyflow/react';
import { AppNode, AIEndpointNodeData, NodeData } from '../types';
import { inferEndpointSchema, InputType } from './endpointSchema';

// Define handle type mapping
export type HandleType = 'text' | 'image' | 'video' | 'audio' | 'json' | 'any';

/**
 * Get the type of a handle on a node
 */
export function getHandleType(node: Node<NodeData>, handleId: string | null, isSource: boolean): HandleType {
  if (!handleId) return 'any';

  const nodeType = node.type;

  // Handle different node types
  switch (nodeType) {
    case 'textInput':
      // Text input nodes output text
      return isSource ? 'text' : 'any';

    case 'image':
      // Image nodes output image type
      return isSource ? 'image' : 'any';

    case 'video':
      // Video nodes output video type
      return isSource ? 'video' : 'any';

    case 'aiEndpoint': {
      const endpointData = node.data as unknown as AIEndpointNodeData;
      const schema = inferEndpointSchema(endpointData.endpoint);

      if (isSource) {
        // Output handles
        const output = schema.outputs.find((o) => o.type);
        return output ? (output.type as HandleType) : 'json';
      } else {
        // Input handles
        const input = schema.inputs.find((i) => i.name === handleId);
        if (input) {
          return mapInputTypeToHandleType(input.type);
        }
        return 'any';
      }
    }

    default:
      return 'any';
  }
}

/**
 * Map InputType to HandleType
 */
function mapInputTypeToHandleType(inputType: InputType): HandleType {
  switch (inputType) {
    case 'text':
      return 'text';
    case 'image':
      return 'image';
    case 'video':
      return 'video';
    case 'audio':
      return 'audio';
    default:
      return 'any';
  }
}

/**
 * Check if two handle types are compatible
 */
export function areTypesCompatible(sourceType: HandleType, targetType: HandleType): boolean {
  // 'any' type is compatible with everything
  if (sourceType === 'any' || targetType === 'any') {
    return true;
  }

  // Same types are compatible
  if (sourceType === targetType) {
    return true;
  }

  // JSON can connect to text (for text output from LLMs)
  if (sourceType === 'json' && targetType === 'text') {
    return true;
  }

  // Text can connect to json (for text prompts)
  if (sourceType === 'text' && targetType === 'json') {
    return true;
  }

  // Otherwise, types must match
  return false;
}

/**
 * Validate a connection between two nodes
 */
export function isValidConnection(connection: Connection, nodes: AppNode[]): boolean {
  const sourceNode = nodes.find((n) => n.id === connection.source);
  const targetNode = nodes.find((n) => n.id === connection.target);

  if (!sourceNode || !targetNode) {
    return false;
  }

  const sourceType = getHandleType(sourceNode, connection.sourceHandle, true);
  const targetType = getHandleType(targetNode, connection.targetHandle, false);

  return areTypesCompatible(sourceType, targetType);
}
