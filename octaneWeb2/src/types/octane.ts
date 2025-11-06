export interface SceneNode {
  id: string;
  name: string;
  type: string;
  visible: boolean;
  children: SceneNode[];
}

export interface Vector3 {
  x: number;
  y: number;
  z: number;
}

export interface RenderStats {
  samples: number;
  renderTime: number;
  fps: number;
  resolution: {
    width: number;
    height: number;
  };
}

export interface NodeParameter {
  name: string;
  type: 'number' | 'color' | 'boolean' | 'string' | 'enum';
  value: any;
  min?: number;
  max?: number;
  options?: string[];
}

export interface GraphNode {
  id: string;
  type: string;
  name: string;
  position: { x: number; y: number };
  inputs: Port[];
  outputs: Port[];
}

export interface Port {
  id: string;
  name: string;
  type: string;
}

export interface Connection {
  id: string;
  from: { nodeId: string; portId: string };
  to: { nodeId: string; portId: string };
}
