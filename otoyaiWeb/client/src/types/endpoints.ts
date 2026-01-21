export interface Endpoint {
  _id: string;
  endpoint_id: string;
  category: string[];
  vendor: string;
  model_path: string;
  title: string;
  description: string;
}

export interface EndpointsResponse {
  endpoints: Endpoint[];
}

export type EndpointCategory =
  | 'text-to-image'
  | 'image-to-image'
  | 'text-to-video'
  | 'video-to-video'
  | 'audio-to-video'
  | 'image-to-video'
  | 'text-to-audio'
  | 'video-to-audio'
  | 'text-to-speech'
  | 'image-to-3d'
  | 'vision'
  | 'llm'
  | 'upscale'
  | 'removal'
  | 'edit'
  | 'unknown';
