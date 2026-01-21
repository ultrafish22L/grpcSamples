/**
 * Endpoint cost mapping for AI models
 * Costs are approximate and based on typical usage patterns
 * Format: cost per generation/inference
 */

export interface EndpointCost {
  tokens?: number; // Cost in tokens
  credits?: number; // Alternative: cost in credits
  display: string; // Human-readable display format
}

// Cost database for known endpoints
// Note: These are estimates and may vary based on actual API pricing
export const ENDPOINT_COSTS: Record<string, EndpointCost> = {
  // FLUX Models (text-to-image) - fal-ai
  'fal-ai/flux-1/dev': { tokens: 25, display: '25' },
  'fal-ai/flux-1/dev/image-to-image': { tokens: 25, display: '25' },
  'fal-ai/flux-1/dev/redux': { tokens: 30, display: '30' },
  'fal-ai/flux-1/schnell': { tokens: 15, display: '15' },
  'fal-ai/flux-1/pro': { tokens: 40, display: '40' },
  'fal-ai/flux-1/schnell/image-to-image': { tokens: 15, display: '15' },
  
  // AuraFlow (text-to-image)
  'fal-ai/aura-flow': { tokens: 20, display: '20' },
  
  // Kling Video Models
  'kling/video-o1/standard': { tokens: 300, display: '300' },
  'kling/video-o1/pro': { tokens: 500, display: '500' },
  
  // CogVideoX
  'cogvideox/5b': { tokens: 200, display: '200' },
  
  // Argil Avatars
  'argil/avatars/audio-to-video': { tokens: 150, display: '150' },
  'argil/avatars/text-to-video': { tokens: 200, display: '200' },
  
  // Beatoven Audio Generation
  'beatoven/music-generation': { tokens: 100, display: '100' },
  'beatoven/sound-effect-generation': { tokens: 50, display: '50' },
  
  // Bria AI Models
  'bria/text-to-image/3.2': { tokens: 30, display: '30' },
  'bria/reimagine/3.2': { tokens: 35, display: '35' },
  'bria/fibo/generate': { tokens: 40, display: '40' },
  'bria/fibo-lite/generate': { tokens: 25, display: '25' },
  'bria/fibo-edit/edit': { tokens: 20, display: '20' },
  'bria/fibo-edit/erase_by_text': { tokens: 15, display: '15' },
  'bria/fibo-edit/replace_object_by_text': { tokens: 20, display: '20' },
  'bria/video/background-removal': { tokens: 80, display: '80' },
  
  // LLM/Vision Models
  'openai/gpt-4': { tokens: 100, display: '~100' },
  'openai/gpt-3.5-turbo': { tokens: 10, display: '~10' },
  'anthropic/claude-3': { tokens: 80, display: '~80' },
  
  // Audio Models
  'elevenlabs/speech': { tokens: 50, display: '50' },
  
  // 3D Models
  'bytedance/seed-3d': { tokens: 150, display: '150' },
  
  // Upscale/Edit
  'fal-ai/clarity-upscaler': { tokens: 20, display: '20' },
  'fal-ai/remove-background': { tokens: 10, display: '10' },
  'fal-ai/creative-upscaler': { tokens: 25, display: '25' },
  
  // Stable Diffusion variants
  'fal-ai/stable-diffusion-v3': { tokens: 20, display: '20' },
  'fal-ai/stable-diffusion-xl': { tokens: 15, display: '15' },
  
  // Default estimates by category pattern (fallback)
  // Video generation: typically 200-500 tokens
  // Image generation: typically 15-40 tokens
  // Audio generation: typically 50-100 tokens
  // Edit/upscale: typically 10-30 tokens
};

/**
 * Get cost information for an endpoint
 * Returns null if cost is unknown
 */
export function getEndpointCost(endpointId: string): EndpointCost | null {
  return ENDPOINT_COSTS[endpointId] || null;
}

/**
 * Get formatted cost display string
 * Returns null if cost is unknown
 */
export function getEndpointCostDisplay(endpointId: string): string | null {
  const cost = getEndpointCost(endpointId);
  return cost ? cost.display : null;
}
