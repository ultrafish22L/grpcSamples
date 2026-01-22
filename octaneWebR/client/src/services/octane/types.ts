/**
 * Shared types for Octane services
 */

export interface RenderState {
  isRendering: boolean;
  progress: number;
  samples: number;
  renderTime: number;
  resolution: { width: number; height: number };
}

export interface SceneNode {
  handle?: number;  // Optional: will be undefined for unconnected pins
  name: string;
  type: string;  // String type like 'PT_GEOMETRY' from API
  typeEnum?: number;  // Legacy numeric enum (deprecated)
  outType?: string | number;  // Raw API value (octaneWeb uses outType)
  visible?: boolean;
  level?: number;
  children?: SceneNode[];
  graphInfo?: any;
  nodeInfo?: any;
  pinInfo?: any;
  attrInfo?: any;
  icon?: string;
  [key: string]: any;
}

export interface Scene {
  tree: SceneNode[];
  map: Map<number, SceneNode>;
  connections: Map<number, any>;
}

export interface NodeAddedEvent {
  node: SceneNode;
  handle: number;
}

export interface NodeDeletedEvent {
  handle: number;
  collapsedChildren: number[];
}

export interface DeviceMemoryUsage {
  total: number;
  used: number;
  free: number;
}

export interface DeviceResourceStatistics {
  textures: number;
  geometry: number;
  nodes: number;
}

export interface DeviceGeometryStatistics {
  meshes: number;
  vertices: number;
  triangles: number;
}

export interface DeviceTexturesStatistics {
  count: number;
  memory: number;
}

export interface RenderRegion {
  active: boolean;
  regionMin: { x: number; y: number };
  regionMax: { x: number; y: number };
  featherWidth: number;
}

export interface PickResult {
  nodeHandle: number;
  position: { x: number; y: number; z: number };
  normal: { x: number; y: number; z: number };
}

export interface MaterialCategory {
  id: number;
  name: string;
  parentID: number;
  typeID: number;
}

export interface Material {
  id: number;
  name: string;
  nickname: string;
  copyright: string;
}

export interface CameraState {
  position: { x: number; y: number; z: number };
  target: { x: number; y: number; z: number };
  up?: { x: number; y: number; z: number };
  fov?: number;
}
