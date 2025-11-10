import { octaneClient } from '../api/octaneClient'

/**
 * Camera System for 3D Viewport Control
 * 
 * Manages camera state and interactions for the render viewport:
 * - Mouse drag to orbit (left button)
 * - Mouse drag to pan (middle button)  
 * - Scroll wheel to zoom
 * - Live synchronization with Octane
 * - Smooth animations and momentum
 * 
 * Uses spherical coordinates (radius, theta, phi) internally
 * for intuitive arcball rotation around a center point.
 */

export interface CameraConfig {
  radius?: number
  theta?: number
  phi?: number
  center?: [number, number, number]
  fov?: number
  sensitivity?: number
  zoomSpeed?: number
  panSpeed?: number
  smoothing?: number
  minRadius?: number
  maxRadius?: number
}

export interface CameraState {
  position: [number, number, number]
  target: [number, number, number]
  fov: number
}

export class Camera {
  // Spherical coordinates
  private radius: number = 20.0
  private theta: number = 0.0
  private phi: number = 0.0
  private center: [number, number, number] = [0, 0, 0]
  
  // Camera properties
  private fov: number = 45.0
  
  // Interaction state
  private isDragging: boolean = false
  private isPanning: boolean = false
  private lastMouseX: number = 0
  private lastMouseY: number = 0
  
  // Animation state
  private targetRadius: number = 20.0
  private isAnimating: boolean = false
  private animationFrame: number | null = null
  
  // Configuration
  private config = {
    sensitivity: 0.01,
    zoomSpeed: 0.1,
    panSpeed: 0.01,
    smoothing: 0.15,
    minRadius: 1.0,
    maxRadius: 200.0,
    updateDebounceMs: 16 // ~60 FPS
  }
  
  // Debouncing for network calls
  private updateTimeout: ReturnType<typeof setTimeout> | null = null
  private lastUpdateTime: number = 0
  
  constructor(config?: CameraConfig) {
    if (config) {
      if (config.radius !== undefined) this.radius = config.radius
      if (config.theta !== undefined) this.theta = config.theta
      if (config.phi !== undefined) this.phi = config.phi
      if (config.center !== undefined) this.center = config.center
      if (config.fov !== undefined) this.fov = config.fov
      if (config.sensitivity !== undefined) this.config.sensitivity = config.sensitivity
      if (config.zoomSpeed !== undefined) this.config.zoomSpeed = config.zoomSpeed
      if (config.panSpeed !== undefined) this.config.panSpeed = config.panSpeed
      if (config.smoothing !== undefined) this.config.smoothing = config.smoothing
      if (config.minRadius !== undefined) this.config.minRadius = config.minRadius
      if (config.maxRadius !== undefined) this.config.maxRadius = config.maxRadius
      
      this.targetRadius = this.radius
    }
  }
  
  // ============================================================================
  // INITIALIZATION
  // ============================================================================
  
  async initializeFromOctane(): Promise<void> {
    try {
      const cameraInfo = await octaneClient.getCameraInfo()
      
      this.center = cameraInfo.target
      this.fov = cameraInfo.fov
      this.cartesianToSpherical(cameraInfo.position)
      this.targetRadius = this.radius
      
      console.log('📷 Camera initialized from Octane')
    } catch (error) {
      console.warn('Could not initialize camera from Octane, using defaults:', error)
    }
  }
  
  // ============================================================================
  // MOUSE EVENT HANDLERS
  // ============================================================================
  
  onMouseDown(e: MouseEvent): void {
    if (e.button === 0) {
      this.isDragging = true
    } else if (e.button === 1) {
      this.isPanning = true
      e.preventDefault()
    }
    
    this.lastMouseX = e.clientX
    this.lastMouseY = e.clientY
  }
  
  onMouseMove(e: MouseEvent): void {
    if (!this.isDragging && !this.isPanning) return
    
    const deltaX = e.clientX - this.lastMouseX
    const deltaY = e.clientY - this.lastMouseY
    
    if (this.isDragging) {
      this.rotate(deltaX, deltaY)
    } else if (this.isPanning) {
      this.pan(deltaX, deltaY)
    }
    
    this.lastMouseX = e.clientX
    this.lastMouseY = e.clientY
  }
  
  onMouseUp(e: MouseEvent): void {
    if (e.button === 0) {
      this.isDragging = false
    } else if (e.button === 1) {
      this.isPanning = false
    }
  }
  
  onWheel(e: WheelEvent): void {
    e.preventDefault()
    this.zoom(e.deltaY)
  }
  
  // ============================================================================
  // CAMERA OPERATIONS
  // ============================================================================
  
  private rotate(deltaX: number, deltaY: number): void {
    this.theta -= deltaX * this.config.sensitivity
    this.phi -= deltaY * this.config.sensitivity
    
    // Clamp phi to avoid gimbal lock
    const epsilon = 0.01
    this.phi = Math.max(-Math.PI / 2 + epsilon, Math.min(Math.PI / 2 - epsilon, this.phi))
    
    this.updateOctaneCamera()
  }
  
  private pan(deltaX: number, deltaY: number): void {
    const right = this.getRightVector()
    const up = this.getUpVector()
    
    const panScale = this.radius * this.config.panSpeed
    
    this.center[0] -= (right[0] * deltaX + up[0] * deltaY) * panScale
    this.center[1] -= (right[1] * deltaX + up[1] * deltaY) * panScale
    this.center[2] -= (right[2] * deltaX + up[2] * deltaY) * panScale
    
    this.updateOctaneCamera()
  }
  
  private zoom(delta: number): void {
    this.targetRadius += delta * this.config.zoomSpeed
    this.targetRadius = Math.max(
      this.config.minRadius,
      Math.min(this.config.maxRadius, this.targetRadius)
    )
    
    this.animateZoom()
  }
  
  private animateZoom(): void {
    if (this.isAnimating) return
    
    this.isAnimating = true
    
    const animate = () => {
      const diff = this.targetRadius - this.radius
      
      if (Math.abs(diff) < 0.01) {
        this.radius = this.targetRadius
        this.isAnimating = false
        this.updateOctaneCamera()
        return
      }
      
      this.radius += diff * this.config.smoothing
      this.updateOctaneCamera()
      
      this.animationFrame = requestAnimationFrame(animate)
    }
    
    this.animationFrame = requestAnimationFrame(animate)
  }
  
  async reset(): Promise<void> {
    this.radius = 20.0
    this.targetRadius = 20.0
    this.theta = 0.0
    this.phi = 0.0
    this.center = [0, 0, 0]
    this.fov = 45.0
    
    await this.sendCameraToOctane()
    
    console.log('📷 Camera reset to defaults')
  }
  
  // ============================================================================
  // COORDINATE CONVERSION
  // ============================================================================
  
  private sphericalToCartesian(): [number, number, number] {
    const x = this.radius * Math.cos(this.phi) * Math.cos(this.theta) + this.center[0]
    const y = this.radius * Math.sin(this.phi) + this.center[1]
    const z = this.radius * Math.cos(this.phi) * Math.sin(this.theta) + this.center[2]
    
    return [x, y, z]
  }
  
  private cartesianToSpherical(position: [number, number, number]): void {
    const dx = position[0] - this.center[0]
    const dy = position[1] - this.center[1]
    const dz = position[2] - this.center[2]
    
    this.radius = Math.sqrt(dx * dx + dy * dy + dz * dz)
    this.theta = Math.atan2(dz, dx)
    
    if (this.radius > 0.0001) {
      this.phi = Math.asin(dy / this.radius)
    } else {
      this.phi = 0
    }
  }
  
  private getRightVector(): [number, number, number] {
    const x = -Math.sin(this.theta)
    const y = 0
    const z = Math.cos(this.theta)
    return [x, y, z]
  }
  
  private getUpVector(): [number, number, number] {
    const x = -Math.sin(this.phi) * Math.cos(this.theta)
    const y = Math.cos(this.phi)
    const z = -Math.sin(this.phi) * Math.sin(this.theta)
    return [x, y, z]
  }
  
  // ============================================================================
  // OCTANE SYNCHRONIZATION
  // ============================================================================
  
  private updateOctaneCamera(): void {
    if (this.updateTimeout) {
      clearTimeout(this.updateTimeout)
    }
    
    const now = Date.now()
    const timeSinceLastUpdate = now - this.lastUpdateTime
    
    if (timeSinceLastUpdate < this.config.updateDebounceMs) {
      this.updateTimeout = setTimeout(() => {
        this.sendCameraToOctane()
      }, this.config.updateDebounceMs - timeSinceLastUpdate)
    } else {
      this.sendCameraToOctane()
    }
  }
  
  private async sendCameraToOctane(): Promise<void> {
    this.lastUpdateTime = Date.now()
    
    const position = this.sphericalToCartesian()
    
    try {
      await Promise.all([
        octaneClient.setCameraPosition(position[0], position[1], position[2]),
        octaneClient.setCameraTarget(this.center[0], this.center[1], this.center[2])
      ])
    } catch (error) {
      console.error('Failed to update Octane camera:', error)
    }
  }
  
  // ============================================================================
  // STATE ACCESSORS
  // ============================================================================
  
  getState(): CameraState {
    return {
      position: this.sphericalToCartesian(),
      target: [...this.center],
      fov: this.fov
    }
  }
  
  setState(state: Partial<CameraState>): void {
    if (state.position) {
      this.cartesianToSpherical(state.position)
      this.targetRadius = this.radius
    }
    
    if (state.target) {
      this.center = [...state.target]
    }
    
    if (state.fov !== undefined) {
      this.fov = state.fov
    }
    
    this.updateOctaneCamera()
  }
  
  // ============================================================================
  // CLEANUP
  // ============================================================================
  
  dispose(): void {
    if (this.updateTimeout) {
      clearTimeout(this.updateTimeout)
      this.updateTimeout = null
    }
    
    if (this.animationFrame) {
      cancelAnimationFrame(this.animationFrame)
      this.animationFrame = null
    }
    
    this.isDragging = false
    this.isPanning = false
    this.isAnimating = false
  }
}

export default Camera
