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
// Based on Jan 2025 pricing research
export const ENDPOINT_COSTS: Record<string, EndpointCost> = {
  // === TEXT-TO-IMAGE - FLUX Models (fal-ai) ===
  'fal-ai/flux-1/dev': { tokens: 25, display: '25' },
  'fal-ai/flux-1/schnell': { tokens: 15, display: '15' },
  'fal-ai/flux-1/pro': { tokens: 40, display: '40' },
  'fal-ai/flux-1/dev/image-to-image': { tokens: 25, display: '25' },
  'fal-ai/flux-1/schnell/image-to-image': { tokens: 15, display: '15' },
  'fal-ai/flux-1/dev/redux': { tokens: 30, display: '30' },
  
  // === TEXT-TO-IMAGE - Stable Diffusion Models ===
  'fal-ai/stable-diffusion-xl': { tokens: 15, display: '15' },
  'fal-ai/stable-diffusion-v3': { tokens: 20, display: '20' },
  'fal-ai/stable-diffusion-v35-large': { tokens: 30, display: '30' },
  'fal-ai/stable-diffusion-v35-medium': { tokens: 22, display: '22' },
  'stabilityai/stable-diffusion-v1-5': { tokens: 12, display: '12' },
  
  // === TEXT-TO-IMAGE - Other Models ===
  'fal-ai/aura-flow': { tokens: 20, display: '20' },
  'zhipuai/glm-image': { tokens: 25, display: '25' },
  'tongyi/z-image-turbo': { tokens: 18, display: '18' },
  'qwen/qwen-image-2512': { tokens: 22, display: '22' },
  
  // === IMAGE-TO-IMAGE / EDITING ===
  'fal-ai/clarity-upscaler': { tokens: 20, display: '20' },
  'fal-ai/creative-upscaler': { tokens: 25, display: '25' },
  'fal-ai/remove-background': { tokens: 10, display: '10' },
  'xinsir/controlnet-union-sdxl': { tokens: 20, display: '20' },
  
  // === IMAGE-TO-VIDEO ===
  'lightricks/ltx-2': { tokens: 350, display: '350' },
  'lightricks/ltx-video': { tokens: 300, display: '300' },
  'fal-ai/hunyuan-video/image-to-video': { tokens: 400, display: '400' },
  'fal-ai/cogvideox-5b/image-to-video': { tokens: 200, display: '200' },
  'stabilityai/stable-video-diffusion': { tokens: 250, display: '250' },
  'wan-ai/wan2.2-i2v-a14b': { tokens: 380, display: '380' },
  'runway/gen-3': { tokens: 500, display: '500' },
  'kling/video-o1': { tokens: 400, display: '400' },
  'kling/video-o1/standard': { tokens: 300, display: '300' },
  'kling/video-o1/pro': { tokens: 500, display: '500' },
  'pika/video-1.5': { tokens: 280, display: '280' },
  
  // === TEXT-TO-VIDEO ===
  'tencent/hunyuan-video-1.5': { tokens: 450, display: '450' },
  'wan-ai/wan2.1-t2v-14b': { tokens: 400, display: '400' },
  'wan-ai/wan2.2-t2v-a14b': { tokens: 420, display: '420' },
  'runway/gen-3/text-to-video': { tokens: 550, display: '550' },
  'kling/video-o1/text-to-video': { tokens: 450, display: '450' },
  'luma/dream-machine': { tokens: 350, display: '350' },
  'pika/video-2.0': { tokens: 320, display: '320' },
  
  // === LARGE LANGUAGE MODELS ===
  // OpenAI
  'openai/gpt-5.2': { tokens: 150, display: '~150' },
  'openai/gpt-5.1': { tokens: 120, display: '~120' },
  'openai/gpt-4o': { tokens: 80, display: '~80' },
  'openai/gpt-4-turbo': { tokens: 100, display: '~100' },
  'openai/gpt-4': { tokens: 100, display: '~100' },
  'openai/gpt-3.5-turbo': { tokens: 10, display: '~10' },
  
  // Anthropic
  'anthropic/claude-opus-4.5': { tokens: 150, display: '~150' },
  'anthropic/claude-4.5-sonnet': { tokens: 90, display: '~90' },
  'anthropic/claude-3.5-sonnet': { tokens: 80, display: '~80' },
  'anthropic/claude-3-opus': { tokens: 80, display: '~80' },
  'anthropic/claude-3': { tokens: 80, display: '~80' },
  
  // Google
  'google/gemini-3-pro': { tokens: 100, display: '~100' },
  'google/gemini-3-flash': { tokens: 20, display: '~20' },
  'google/gemini-2.0-flash': { tokens: 15, display: '~15' },
  
  // Others
  'xai/grok-4': { tokens: 100, display: '~100' },
  'xai/grok-4.1-fast': { tokens: 60, display: '~60' },
  'zhipuai/glm-4.7': { tokens: 50, display: '~50' },
  'deepseek/v3.2': { tokens: 3, display: '~3' }, // Best value!
  'meta/llama-4-maverick': { tokens: 30, display: '~30' },
  'alibaba/qwen-3-235b': { tokens: 40, display: '~40' },
  'mistralai/mistral-large-3': { tokens: 70, display: '~70' },
  
  // === TEXT-TO-SPEECH & AUDIO ===
  'elevenlabs/speech': { tokens: 50, display: '50' },
  'openai/tts': { tokens: 30, display: '30' },
  'openai/whisper-large-v3': { tokens: 20, display: '20' },
  'azure/neural-tts': { tokens: 40, display: '40' },
  
  // === MUSIC GENERATION ===
  'suno/v3.5': { tokens: 150, display: '150' },
  'udio/v1.5': { tokens: 180, display: '180' },
  'meta/musicgen': { tokens: 100, display: '100' },
  'stabilityai/stable-audio': { tokens: 120, display: '120' },
  'beatoven/music-generation': { tokens: 100, display: '100' },
  'beatoven/sound-effect-generation': { tokens: 50, display: '50' },
  
  // === 3D GENERATION ===
  'tripo/triposr': { tokens: 150, display: '150' },
  'meshy/v2': { tokens: 200, display: '200' },
  'openai/shap-e': { tokens: 180, display: '180' },
  'bytedance/seed-3d': { tokens: 150, display: '150' },
  
  // === SPECIAL / CUSTOM ===
  'nano-banana': { tokens: 5, display: '5' }, // Lightweight fast model
  
  // === LEGACY / OTHER ===
  'cogvideox/5b': { tokens: 200, display: '200' },
  'argil/avatars/audio-to-video': { tokens: 150, display: '150' },
  'argil/avatars/text-to-video': { tokens: 200, display: '200' },
  'bria/text-to-image/3.2': { tokens: 30, display: '30' },
  'bria/reimagine/3.2': { tokens: 35, display: '35' },
  'bria/fibo/generate': { tokens: 40, display: '40' },
  'bria/fibo-lite/generate': { tokens: 25, display: '25' },
  'bria/fibo-edit/edit': { tokens: 20, display: '20' },
  'bria/fibo-edit/erase_by_text': { tokens: 15, display: '15' },
  'bria/fibo-edit/replace_object_by_text': { tokens: 20, display: '20' },
  'bria/video/background-removal': { tokens: 80, display: '80' },
  
  // Default estimates by category pattern (fallback)
  // Video generation: typically 200-500 tokens
  // Image generation: typically 15-40 tokens
  // Audio generation: typically 50-100 tokens
  // LLM inference: typically 10-150 tokens per 1k tokens
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
