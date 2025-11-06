import mitt, { Emitter } from 'mitt'
import type { SceneNode, Parameter } from '../api/octaneClient'

/**
 * Event Bus for Cross-Component Communication
 * 
 * Provides type-safe event handling across the application.
 */

export type AppEvents = {
  // Connection events
  'connection:connecting': void
  'connection:connected': { serverUrl: string }
  'connection:disconnected': void
  'connection:error': { error: Error }
  
  // Scene events
  'scene:loading': void
  'scene:loaded': { nodes: SceneNode[] }
  'scene:error': { error: Error }
  'node:selected': { node: SceneNode }
  'node:deselected': void
  'node:visibility-changed': { nodeHandle: string; visible: boolean }
  
  // Camera events
  'camera:changed': { position: [number, number, number]; target: [number, number, number] }
  
  // Parameter events
  'parameter:changed': { nodeHandle: string; paramName: string; value: any }
  'parameters:loaded': { nodeHandle: string; parameters: Parameter[] }
  
  // Render events
  'render:new-image': { imageData: string; width: number; height: number }
}

export const eventBus: Emitter<AppEvents> = mitt<AppEvents>()

export const emitEvent = <K extends keyof AppEvents>(
  event: K,
  data: AppEvents[K]
) => {
  eventBus.emit(event, data)
}

export const onEvent = <K extends keyof AppEvents>(
  event: K,
  handler: (data: AppEvents[K]) => void
) => {
  eventBus.on(event, handler)
  return () => eventBus.off(event, handler)
}

export default eventBus
