import { logger } from '../services/logger';
import { InputParameter } from './endpointSchema';

export interface PackagedParameters {
  [key: string]: any;
}

/**
 * Package parameters for AI endpoint execution
 * Handles type conversion, validation, and encoding (e.g., base64 for media)
 */
export async function packageParameters(
  parameters: Record<string, any>,
  schema: InputParameter[]
): Promise<PackagedParameters> {
  const packaged: PackagedParameters = {};

  for (const param of schema) {
    const value = parameters[param.name];

    // Skip undefined or null values for optional parameters
    if (value === undefined || value === null) {
      if (param.required) {
        throw new Error(`Required parameter "${param.name}" is missing`);
      }
      continue;
    }

    try {
      packaged[param.name] = await packageParameter(value, param);
    } catch (error) {
      logger.error(`Failed to package parameter "${param.name}"`, error as Error);
      throw new Error(`Failed to package parameter "${param.name}": ${(error as Error).message}`);
    }
  }

  return packaged;
}

/**
 * Package a single parameter based on its type
 */
async function packageParameter(value: any, param: InputParameter): Promise<any> {
  switch (param.type) {
    case 'text':
      return packageText(value);

    case 'integer':
      return packageInteger(value, param);

    case 'float':
      return packageFloat(value, param);

    case 'boolean':
      return packageBoolean(value);

    case 'select':
      return packageSelect(value, param);

    case 'image':
      return await packageImage(value);

    case 'video':
      return await packageVideo(value);

    case 'audio':
      return await packageAudio(value);

    default:
      // Unknown type - pass through as-is
      logger.warn(`Unknown parameter type "${param.type}" for "${param.name}", passing through as-is`);
      return value;
  }
}

/**
 * Package text parameter
 */
function packageText(value: any): string {
  if (typeof value === 'string') {
    return value;
  }
  return String(value);
}

/**
 * Package integer parameter with validation
 */
function packageInteger(value: any, param: InputParameter): number {
  const num = Number(value);

  if (!Number.isInteger(num)) {
    throw new Error(`Value must be an integer`);
  }

  if (param.min !== undefined && num < param.min) {
    throw new Error(`Value must be >= ${param.min}`);
  }

  if (param.max !== undefined && num > param.max) {
    throw new Error(`Value must be <= ${param.max}`);
  }

  return num;
}

/**
 * Package float parameter with validation
 */
function packageFloat(value: any, param: InputParameter): number {
  const num = Number(value);

  if (isNaN(num)) {
    throw new Error(`Value must be a number`);
  }

  if (param.min !== undefined && num < param.min) {
    throw new Error(`Value must be >= ${param.min}`);
  }

  if (param.max !== undefined && num > param.max) {
    throw new Error(`Value must be <= ${param.max}`);
  }

  return num;
}

/**
 * Package boolean parameter
 */
function packageBoolean(value: any): boolean {
  if (typeof value === 'boolean') {
    return value;
  }

  // Handle string representations
  if (typeof value === 'string') {
    const lower = value.toLowerCase();
    if (lower === 'true' || lower === '1' || lower === 'yes') {
      return true;
    }
    if (lower === 'false' || lower === '0' || lower === 'no') {
      return false;
    }
  }

  // Handle numeric representations
  if (typeof value === 'number') {
    return value !== 0;
  }

  return Boolean(value);
}

/**
 * Package select/enum parameter with validation
 */
function packageSelect(value: any, param: InputParameter): string {
  const str = String(value);

  if (param.options && param.options.length > 0) {
    if (!param.options.includes(str)) {
      throw new Error(`Value must be one of: ${param.options.join(', ')}`);
    }
  }

  return str;
}

/**
 * Package image parameter
 * Accepts: URL, base64 string, File object, or data URL
 */
async function packageImage(value: any): Promise<string> {
  // Already a URL or data URL
  if (typeof value === 'string') {
    if (value.startsWith('http://') || value.startsWith('https://')) {
      return value; // External URL
    }
    if (value.startsWith('data:image/')) {
      return value; // Data URL (base64)
    }
    // Assume it's already base64 without prefix
    return value;
  }

  // File object
  if (value instanceof File) {
    return await fileToBase64(value);
  }

  // Blob object
  if (value instanceof Blob) {
    return await blobToBase64(value);
  }

  throw new Error('Image value must be a URL, File, or base64 string');
}

/**
 * Package video parameter
 * Accepts: URL, base64 string, File object, or data URL
 */
async function packageVideo(value: any): Promise<string> {
  // Already a URL or data URL
  if (typeof value === 'string') {
    if (value.startsWith('http://') || value.startsWith('https://')) {
      return value; // External URL
    }
    if (value.startsWith('data:video/')) {
      return value; // Data URL (base64)
    }
    // Assume it's already base64 without prefix
    return value;
  }

  // File object
  if (value instanceof File) {
    return await fileToBase64(value);
  }

  // Blob object
  if (value instanceof Blob) {
    return await blobToBase64(value);
  }

  throw new Error('Video value must be a URL, File, or base64 string');
}

/**
 * Package audio parameter
 * Accepts: URL, base64 string, File object, or data URL
 */
async function packageAudio(value: any): Promise<string> {
  // Already a URL or data URL
  if (typeof value === 'string') {
    if (value.startsWith('http://') || value.startsWith('https://')) {
      return value; // External URL
    }
    if (value.startsWith('data:audio/')) {
      return value; // Data URL (base64)
    }
    // Assume it's already base64 without prefix
    return value;
  }

  // File object
  if (value instanceof File) {
    return await fileToBase64(value);
  }

  // Blob object
  if (value instanceof Blob) {
    return await blobToBase64(value);
  }

  throw new Error('Audio value must be a URL, File, or base64 string');
}

/**
 * Convert File to base64 data URL
 */
function fileToBase64(file: File): Promise<string> {
  return new Promise((resolve, reject) => {
    const reader = new FileReader();

    reader.onload = () => {
      if (typeof reader.result === 'string') {
        resolve(reader.result);
      } else {
        reject(new Error('Failed to read file as data URL'));
      }
    };

    reader.onerror = () => {
      reject(new Error('Failed to read file'));
    };

    reader.readAsDataURL(file);
  });
}

/**
 * Convert Blob to base64 data URL
 */
function blobToBase64(blob: Blob): Promise<string> {
  return new Promise((resolve, reject) => {
    const reader = new FileReader();

    reader.onload = () => {
      if (typeof reader.result === 'string') {
        resolve(reader.result);
      } else {
        reject(new Error('Failed to read blob as data URL'));
      }
    };

    reader.onerror = () => {
      reject(new Error('Failed to read blob'));
    };

    reader.readAsDataURL(blob);
  });
}

/**
 * Validate packaged parameters against schema
 */
export function validatePackagedParameters(
  packaged: PackagedParameters,
  schema: InputParameter[]
): { valid: boolean; errors: string[] } {
  const errors: string[] = [];

  // Check all required parameters are present
  for (const param of schema) {
    if (param.required && !(param.name in packaged)) {
      errors.push(`Required parameter "${param.name}" is missing`);
    }
  }

  return {
    valid: errors.length === 0,
    errors,
  };
}

/**
 * Get parameter values from connected nodes
 * This resolves connections to get actual values from source nodes
 */
export function resolveConnectedParameters(
  nodeParameters: Record<string, any>,
  connectedValues: Record<string, any>
): Record<string, any> {
  const resolved: Record<string, any> = { ...nodeParameters };

  // Override node parameters with connected values
  for (const [key, value] of Object.entries(connectedValues)) {
    if (value !== undefined && value !== null) {
      resolved[key] = value;
    }
  }

  return resolved;
}
