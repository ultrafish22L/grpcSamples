import { Endpoint } from '../types';

export type InputType = 'text' | 'integer' | 'float' | 'image' | 'video' | 'audio' | 'select' | 'boolean';

export interface InputParameter {
  name: string;
  label: string;
  type: InputType;
  description?: string;
  required?: boolean;
  default?: unknown;
  options?: string[];
  min?: number;
  max?: number;
  step?: number;
}

export interface EndpointSchema {
  inputs: InputParameter[];
  outputs: {
    type: 'image' | 'video' | 'audio' | 'text' | 'json';
  }[];
}

// Infer schema from endpoint metadata
export function inferEndpointSchema(endpoint: Endpoint): EndpointSchema {
  const category = endpoint.category[0] || '';
  const inputs: InputParameter[] = [];

  // Common inputs based on category patterns
  if (category.includes('text-to-')) {
    inputs.push({
      name: 'prompt',
      label: 'Prompt',
      type: 'text',
      description: 'Text prompt describing what to generate',
      required: true,
    });
  }

  if (category.includes('image-to-') || category === 'edit' || category === 'upscale') {
    inputs.push({
      name: 'image',
      label: 'Image',
      type: 'image',
      description: 'Input image',
      required: true,
    });
  }

  if (category.includes('video-to-') || category.includes('lipsync')) {
    inputs.push({
      name: 'video',
      label: 'Video',
      type: 'video',
      description: 'Input video',
      required: true,
    });
  }

  if (category.includes('audio-to-') || category.includes('speech')) {
    inputs.push({
      name: 'audio',
      label: 'Audio',
      type: 'audio',
      description: 'Input audio',
      required: true,
    });
  }

  // Add prompt for image/video inputs that support it
  if ((category.includes('image-to-') || category.includes('video-to-')) && 
      (category.includes('image') || category.includes('video'))) {
    inputs.push({
      name: 'prompt',
      label: 'Prompt',
      type: 'text',
      description: 'Optional text prompt for guidance',
      required: false,
    });
  }

  // Specific patterns
  if (endpoint.title.toLowerCase().includes('kling')) {
    // Kling models often have these
    if (category.includes('video')) {
      inputs.push({
        name: 'style',
        label: 'Style',
        type: 'select',
        description: 'Video generation style',
        options: ['cinematic', 'natural', 'artistic', 'anime'],
        default: 'natural',
      });

      if (endpoint.title.includes('Standard') || endpoint.title.includes('o1')) {
        inputs.push({
          name: 'start_image',
          label: 'Start Image',
          type: 'image',
          description: 'Starting frame image',
          required: false,
        });

        inputs.push({
          name: 'end_image',
          label: 'End Image',
          type: 'image',
          description: 'Ending frame image',
          required: false,
        });
      }

      inputs.push({
        name: 'duration',
        label: 'Duration',
        type: 'select',
        description: 'Video duration in seconds',
        options: ['5', '10'],
        default: '5',
      });
    }
  }

  // Add common optional parameters
  if (category.includes('text-to-image') || category.includes('image-to-image')) {
    inputs.push({
      name: 'negative_prompt',
      label: 'Negative Prompt',
      type: 'text',
      description: 'What to avoid in the generation',
      required: false,
    });

    inputs.push({
      name: 'seed',
      label: 'Seed',
      type: 'integer',
      description: 'Random seed for reproducibility',
      required: false,
      min: 0,
      max: 2147483647,
    });

    inputs.push({
      name: 'num_inference_steps',
      label: 'Steps',
      type: 'integer',
      description: 'Number of inference steps',
      required: false,
      default: 50,
      min: 1,
      max: 150,
    });

    inputs.push({
      name: 'guidance_scale',
      label: 'Guidance Scale',
      type: 'float',
      description: 'How closely to follow the prompt',
      required: false,
      default: 7.5,
      min: 1,
      max: 20,
      step: 0.5,
    });
  }

  // LLM inputs
  if (category === 'llm' || category === 'vision') {
    if (!inputs.find(i => i.name === 'prompt')) {
      inputs.push({
        name: 'prompt',
        label: 'Prompt',
        type: 'text',
        description: 'Input text prompt',
        required: true,
      });
    }

    inputs.push({
      name: 'temperature',
      label: 'Temperature',
      type: 'float',
      description: 'Sampling temperature',
      default: 0.7,
      min: 0,
      max: 2,
      step: 0.1,
    });

    inputs.push({
      name: 'max_tokens',
      label: 'Max Tokens',
      type: 'integer',
      description: 'Maximum output length',
      default: 512,
      min: 1,
      max: 4096,
    });
  }

  // Determine output type
  const outputs: EndpointSchema['outputs'] = [];
  if (category.includes('image') || category === 'upscale') {
    outputs.push({ type: 'image' });
  } else if (category.includes('video')) {
    outputs.push({ type: 'video' });
  } else if (category.includes('audio') || category.includes('speech')) {
    outputs.push({ type: 'audio' });
  } else if (category === 'llm') {
    outputs.push({ type: 'text' });
  } else {
    outputs.push({ type: 'json' });
  }

  return { inputs, outputs };
}

// Check if input type should have an open pin (hollow circle) vs filled dot
export function isMediaInput(type: InputType): boolean {
  return type === 'image' || type === 'video' || type === 'audio';
}
