import { Connection, Node } from '@xyflow/react';
import { AppNode, AIEndpointNodeData } from '../types';
import { inferEndpointSchema, InputType } from './endpointSchema';

// Define fine-grained handle type mapping
export type HandleType = 
  | 'string'   // Text/prompts - Orange
  | 'integer'  // Whole numbers (steps, seed) - Yellow
  | 'float'    // Decimals (guidance_scale, strength) - Cyan
  | 'boolean'  // True/false - Red
  | 'enum'     // Selections (scheduler, sampler) - Purple
  | 'image'    // Image data (input & output) - Green
  | 'video'    // Video data (input & output) - Magenta
  | 'audio'    // Audio data (input & output) - Blue
  | 'any';     // Generic - Gray

/**
 * Get the type of a handle on a node
 */
export function getHandleType(node: Node | AppNode | undefined, handleId: string | null, isSource: boolean): HandleType {
  if (!node) return 'any';
  if (!handleId) return 'any';

  const nodeType = node.type;

  // Handle different node types
  switch (nodeType) {
    case 'textInput':
      // Text input nodes output string type
      return isSource ? 'string' : 'any';

    case 'image':
      // Image nodes output image type (same for input & output)
      return isSource ? 'image' : 'any';

    case 'video':
      // Video nodes output video type (same for input & output)
      return isSource ? 'video' : 'any';

    case 'aiEndpoint': {
      const endpointData = node.data as unknown as AIEndpointNodeData;
      const schema = inferEndpointSchema(endpointData.endpoint);

      if (isSource) {
        // Output handles
        const output = schema.outputs.find((o) => o.type);
        if (output) {
          return mapOutputTypeToHandleType(output.type);
        }
        return 'any';
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
export function mapInputTypeToHandleType(inputType: InputType): HandleType {
  switch (inputType) {
    case 'text':
      return 'string';
    case 'integer':
      return 'integer';
    case 'float':
      return 'float';
    case 'boolean':
      return 'boolean';
    case 'select':
      return 'enum';
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
 * Map output type from EndpointSchema to HandleType
 */
export function mapOutputTypeToHandleType(outputType: 'image' | 'video' | 'audio' | 'text' | 'json'): HandleType {
  switch (outputType) {
    case 'text':
      return 'string'; // LLM text outputs map to string
    case 'image':
      return 'image';
    case 'video':
      return 'video';
    case 'audio':
      return 'audio';
    case 'json':
      return 'any'; // Generic JSON data
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

  // Same types are always compatible
  if (sourceType === targetType) {
    return true;
  }

  // Allow integer to connect to float (automatic conversion)
  if (sourceType === 'integer' && targetType === 'float') {
    return true;
  }

  // Allow float to connect to integer (with rounding)
  if (sourceType === 'float' && targetType === 'integer') {
    return true;
  }

  // Otherwise, types must match exactly
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

/**
 * Get the CSS class name for a handle type
 */
export function getHandleColorClass(type: HandleType): string {
  switch (type) {
    case 'string':
      return 'handleString';
    case 'integer':
      return 'handleInteger';
    case 'float':
      return 'handleFloat';
    case 'boolean':
      return 'handleBoolean';
    case 'enum':
      return 'handleEnum';
    case 'image':
      return 'handleImage';
    case 'video':
      return 'handleVideo';
    case 'audio':
      return 'handleAudio';
    case 'any':
      return 'handleAny';
    default:
      return 'handleAny';
  }
}

/**
 * Get the inline style color for a handle type (for edges)
 */
export function getHandleColorStyle(type: HandleType): string {
  switch (type) {
    case 'string':
      return '#ffaa44'; // Orange - text/prompts
    case 'integer':
      return '#ffdd44'; // Yellow - whole numbers
    case 'float':
      return '#00ddff'; // Cyan - decimals
    case 'boolean':
      return '#ff4444'; // Red - true/false
    case 'enum':
      return '#cc44ff'; // Purple - selections
    case 'image':
      return '#44ff44'; // Green - images
    case 'video':
      return '#ff44ff'; // Magenta - video
    case 'audio':
      return '#4499ff'; // Blue - audio
    case 'any':
      return '#aaaaaa'; // Gray - generic
    default:
      return '#aaaaaa';
  }
}
