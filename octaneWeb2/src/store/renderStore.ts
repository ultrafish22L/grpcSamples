import { create } from 'zustand';

interface RenderState {
  imageData: ImageData | null;
  isRendering: boolean;
  samples: number;
  renderTime: number;
  fps: number;
  resolution: { width: number; height: number };
  
  setImageData: (data: ImageData | null) => void;
  setRendering: (rendering: boolean) => void;
  updateStats: (stats: { samples?: number; renderTime?: number; fps?: number }) => void;
}

export const useRenderStore = create<RenderState>((set) => ({
  imageData: null,
  isRendering: false,
  samples: 0,
  renderTime: 0,
  fps: 0,
  resolution: { width: 1920, height: 1080 },
  
  setImageData: (data) => set({ imageData: data }),
  setRendering: (rendering) => set({ isRendering: rendering }),
  updateStats: (stats) => set((state) => ({
    ...state,
    ...stats
  })),
}));
