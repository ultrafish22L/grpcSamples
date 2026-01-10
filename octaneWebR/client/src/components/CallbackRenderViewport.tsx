/**
 * Callback-based Render Viewport Component (React TypeScript)
 * 
 * Production-ready port of octaneWeb's CallbackRenderViewport with React best practices:
 * - Real-time callback streaming with OnNewImage events
 * - Mouse drag camera synchronization
 * - HDR/LDR buffer processing with proper isolation
 * - Automatic render triggering when connected
 */

import { useEffect, useRef, useState, useCallback } from 'react';
import { useOctane } from '../hooks/useOctane';

interface OctaneImageData {
  type: number;
  size: { x: number; y: number };
  pitch: number;
  tonemappedSamplesPerPixel: number;
  renderTime: number;
  buffer: {
    data: string;
    size: number;
    encoding: string;
  };
}

interface CallbackData {
  type: string;
  render_images?: {
    data: OctaneImageData[];
  };
  timestamp?: number;
  callback_id?: string;
}

interface CameraState {
  radius: number;
  theta: number;
  phi: number;
  center: [number, number, number];
  fov: number;
}

export function CallbackRenderViewport() {
  const { client, connected } = useOctane();
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const viewportRef = useRef<HTMLDivElement>(null);
  const [frameCount, setFrameCount] = useState(0);
  const [status, setStatus] = useState('Initializing...');
  const [isRendering, setIsRendering] = useState(false);
  
  // Camera state for mouse controls
  const cameraRef = useRef<CameraState>({
    radius: 20.0,
    theta: 0.0,
    phi: 0.0,
    center: [0.0, 0.0, 0.0],
    fov: 45.0
  });
  
  // Mouse drag state
  const isDraggingRef = useRef(false);
  const lastMousePosRef = useRef({ x: 0, y: 0 });

  /**
   * Trigger Octane display update via ApiChangeManager
   */
  const triggerOctaneUpdate = useCallback(async () => {
    try {
      await client.callApi('ApiChangeManager', 'update', {});
    } catch (error: any) {
      console.error('❌ Failed to trigger render:', error.message);
    }
  }, [client]);

  /**
   * Initialize camera from Octane's current camera settings
   */
  const initializeCameraFromOctane = useCallback(async () => {
    try {
      // Get current camera from Octane
      const camera = await client.callApi('ApiProjectManager', 'camera', {});
      
      if (!camera || !camera.result) {
        console.warn('⚠️  No camera found in scene, using defaults');
        return;
      }

      const cameraHandle = camera.result;
      
      // Get camera position
      const posResponse = await client.callApi('ApiNode', 'getCameraPosition', {
        objectPtr: cameraHandle
      });
      
      if (posResponse && posResponse.result) {
        const pos = posResponse.result;
        console.log('📷 Camera position:', pos);
        
        // Calculate spherical coordinates from position
        if (pos.x !== undefined && pos.y !== undefined && pos.z !== undefined) {
          const x = pos.x;
          const y = pos.y;
          const z = pos.z;
          
          cameraRef.current.radius = Math.sqrt(x * x + y * y + z * z);
          cameraRef.current.theta = Math.atan2(x, z);
          cameraRef.current.phi = Math.asin(y / cameraRef.current.radius);
        }
      }
      
      console.log('✅ Camera initialized:', cameraRef.current);
    } catch (error: any) {
      console.warn('⚠️  Failed to initialize camera from Octane:', error.message);
      console.warn('   Using default camera settings');
    }
  }, [client]);

  /**
   * Update Octane camera from current state
   */
  const updateOctaneCamera = useCallback(async () => {
    if (!connected) return;

    try {
      const { radius, theta, phi, center } = cameraRef.current;
      
      // Convert spherical to Cartesian coordinates
      const x = radius * Math.cos(phi) * Math.sin(theta);
      const y = radius * Math.sin(phi);
      const z = radius * Math.cos(phi) * Math.cos(theta);
      
      const position = {
        x: x + center[0],
        y: y + center[1],
        z: z + center[2]
      };
      
      // Get current camera
      const camera = await client.callApi('ApiProjectManager', 'camera', {});
      if (!camera || !camera.result) return;
      
      const cameraHandle = camera.result;
      
      // Set camera position
      await client.callApi('ApiNode', 'setCameraPosition', {
        objectPtr: cameraHandle,
        value: position
      });
      
      // Set camera target
      await client.callApi('ApiNode', 'setCameraTarget', {
        objectPtr: cameraHandle,
        value: {
          x: center[0],
          y: center[1],
          z: center[2]
        }
      });
      
      // Trigger render update
      await triggerOctaneUpdate();
    } catch (error: any) {
      console.error('❌ Failed to update camera:', error.message);
    }
  }, [connected, client, triggerOctaneUpdate]);

  /**
   * Display image from callback data
   * CRITICAL: Direct port of octaneWeb buffer processing logic
   */
  const displayCallbackImage = useCallback((imageData: OctaneImageData) => {
    try {
      const canvas = canvasRef.current;
      if (!canvas) return;

      setFrameCount(prev => prev + 1);

      if (!imageData.buffer || !imageData.buffer.data) {
        console.error('No image buffer in callback data');
        return;
      }

      // Decode base64 buffer
      const bufferData = imageData.buffer.data;
      const width = imageData.size.x;
      const height = imageData.size.y;

      // Set canvas size
      canvas.width = width;
      canvas.height = height;

      const ctx = canvas.getContext('2d');
      if (!ctx) return;

      const canvasImageData = ctx.createImageData(width, height);

      // Decode base64 to binary
      let bytes: Uint8Array;
      try {
        const binaryString = atob(bufferData);
        bytes = new Uint8Array(binaryString.length);
        for (let i = 0; i < binaryString.length; i++) {
          bytes[i] = binaryString.charCodeAt(i);
        }
      } catch (error: any) {
        console.error('❌ Base64 decode error:', error);
        return;
      }

      // Convert buffer to RGBA format for canvas
      convertBufferToCanvas(bytes, imageData, canvasImageData);

      ctx.putImageData(canvasImageData, 0, 0);

      // Update status
      setStatus(
        `${width}x${height} | ` +
        `${(imageData.buffer.size / 1024).toFixed(1)}KB | ` +
        `${imageData.tonemappedSamplesPerPixel.toFixed(1)} spp`
      );
    } catch (error: any) {
      console.error('❌ Error displaying callback image:', error);
    }
  }, []);

  /**
   * Convert raw buffer to canvas ImageData
   * CRITICAL: Exact port of octaneWeb conversion logic
   */
  const convertBufferToCanvas = (
    buffer: Uint8Array,
    imageData: OctaneImageData,
    canvasImageData: globalThis.ImageData
  ) => {
    const width = imageData.size.x;
    const height = imageData.size.y;
    const imageType = imageData.type;

    switch (imageType) {
      case 0: // IMAGE_TYPE_LDR_RGBA
        convertLDRRGBA(buffer, width, height, imageData.pitch, canvasImageData);
        break;
      case 1: // IMAGE_TYPE_HDR_RGBA
        convertHDRRGBA(buffer, width, height, imageData.pitch, canvasImageData);
        break;
      default:
        console.warn(`Unsupported image type: ${imageType}, trying LDR RGBA`);
        convertLDRRGBA(buffer, width, height, imageData.pitch, canvasImageData);
    }
  };

  /**
   * Convert LDR RGBA buffer to canvas
   * CRITICAL: Exact port from octaneWeb - preserves buffer isolation
   */
  const convertLDRRGBA = (
    buffer: Uint8Array,
    width: number,
    height: number,
    pitch: number,
    canvasImageData: ImageData
  ) => {
    const data = canvasImageData.data;
    const expectedSize = width * height * 4;

    if (buffer.length === expectedSize) {
      // Direct copy - no pitch issues
      for (let i = 0; i < expectedSize; i += 4) {
        data[i] = buffer[i];         // R
        data[i + 1] = buffer[i + 1]; // G
        data[i + 2] = buffer[i + 2]; // B
        data[i + 3] = buffer[i + 3]; // A
      }
    } else {
      // Handle pitch (row stride)
      let pitchBytes;

      if (pitch * height === buffer.length) {
        pitchBytes = pitch;
      } else if (pitch * 4 * height === buffer.length) {
        pitchBytes = pitch * 4;
      } else {
        pitchBytes = width * 4;
      }

      // Copy with pitch consideration
      for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
          const srcIndex = y * pitchBytes + x * 4;
          const dstIndex = (y * width + x) * 4;

          if (srcIndex + 3 < buffer.length) {
            data[dstIndex] = buffer[srcIndex];         // R
            data[dstIndex + 1] = buffer[srcIndex + 1]; // G
            data[dstIndex + 2] = buffer[srcIndex + 2]; // B
            data[dstIndex + 3] = buffer[srcIndex + 3]; // A
          }
        }
      }
    }
  };

  /**
   * Convert HDR RGBA buffer to canvas
   * CRITICAL: Exact port from octaneWeb - buffer isolation prevents corruption
   */
  const convertHDRRGBA = (
    buffer: Uint8Array,
    width: number,
    height: number,
    pitch: number,
    canvasImageData: ImageData
  ) => {
    const data = canvasImageData.data;

    // Create a new ArrayBuffer to avoid buffer reuse corruption
    const floatBuffer = new ArrayBuffer(buffer.length);
    const floatView = new Float32Array(floatBuffer);
    const uint8View = new Uint8Array(floatBuffer);

    // Copy the original buffer data
    uint8View.set(buffer);

    // Now reinterpret as floats safely
    const expectedFloats = width * height * 4;

    if (floatView.length === expectedFloats) {
      // Direct copy - no pitch issues
      for (let i = 0; i < expectedFloats; i += 4) {
        // Simple tone mapping: clamp and convert to 8-bit
        data[i] = Math.min(255, Math.max(0, floatView[i] * 255));         // R
        data[i + 1] = Math.min(255, Math.max(0, floatView[i + 1] * 255)); // G
        data[i + 2] = Math.min(255, Math.max(0, floatView[i + 2] * 255)); // B
        data[i + 3] = Math.min(255, Math.max(0, floatView[i + 3] * 255)); // A
      }
    } else {
      // Handle pitch for HDR
      let pitchFloats;

      if (pitch * height === buffer.length) {
        pitchFloats = pitch / 4;
      } else if (pitch * 4 * height === buffer.length) {
        pitchFloats = pitch;
      } else {
        pitchFloats = width;
      }

      for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
          const srcIndex = (y * pitchFloats + x) * 4;
          const dstIndex = (y * width + x) * 4;

          if (srcIndex + 3 < floatView.length) {
            data[dstIndex] = Math.min(255, Math.max(0, floatView[srcIndex] * 255));
            data[dstIndex + 1] = Math.min(255, Math.max(0, floatView[srcIndex + 1] * 255));
            data[dstIndex + 2] = Math.min(255, Math.max(0, floatView[srcIndex + 2] * 255));
            data[dstIndex + 3] = Math.min(255, Math.max(0, floatView[srcIndex + 3] * 255));
          }
        }
      }
    }
  };

  /**
   * Trigger initial render when connected
   */
  useEffect(() => {
    if (!connected) {
      setStatus('Disconnected from Octane');
      return;
    }

    const initializeRendering = async () => {
      try {
        setStatus('Initializing camera...');
        
        // Initialize camera from Octane's current state
        await initializeCameraFromOctane();
        
        setStatus('Triggering initial render...');
        
        // Trigger initial render via ApiChangeManager
        await triggerOctaneUpdate();
        
        setIsRendering(true);
        setStatus('Waiting for render...');
        
        console.log('✅ Render viewport initialized');
      } catch (error: any) {
        console.error('❌ Failed to initialize rendering:', error);
        setStatus(`Error: ${error.message}`);
      }
    };

    initializeRendering();
  }, [connected, initializeCameraFromOctane, triggerOctaneUpdate]);

  /**
   * Setup callback listener for OnNewImage events
   */
  useEffect(() => {
    if (!connected) return;

    const handleNewImage = (data: CallbackData) => {
      if (data.render_images && data.render_images.data && data.render_images.data.length > 0) {
        displayCallbackImage(data.render_images.data[0]);
      }
    };

    client.on('OnNewImage', handleNewImage);

    return () => {
      client.off('OnNewImage', handleNewImage);
    };
  }, [connected, client, displayCallbackImage]);

  /**
   * Setup mouse controls for camera manipulation
   */
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas || !connected) return;

    const handleMouseDown = (e: MouseEvent) => {
      if (e.button === 0) { // Left mouse button
        isDraggingRef.current = true;
        lastMousePosRef.current = { x: e.clientX, y: e.clientY };
        canvas.style.cursor = 'grabbing';
      }
    };

    const handleMouseMove = async (e: MouseEvent) => {
      if (!isDraggingRef.current) return;

      const deltaX = e.clientX - lastMousePosRef.current.x;
      const deltaY = e.clientY - lastMousePosRef.current.y;
      lastMousePosRef.current = { x: e.clientX, y: e.clientY };

      // Update camera angles
      const sensitivity = 0.01;
      cameraRef.current.theta += deltaX * sensitivity;
      cameraRef.current.phi -= deltaY * sensitivity;

      // Clamp phi to prevent flipping
      cameraRef.current.phi = Math.max(-Math.PI / 2 + 0.1, Math.min(Math.PI / 2 - 0.1, cameraRef.current.phi));

      // Update Octane camera and trigger render
      await updateOctaneCamera();
    };

    const handleMouseUp = () => {
      if (isDraggingRef.current) {
        isDraggingRef.current = false;
        canvas.style.cursor = 'grab';
      }
    };

    const handleWheel = async (e: WheelEvent) => {
      e.preventDefault();
      const zoomSpeed = 0.1;
      cameraRef.current.radius += e.deltaY * zoomSpeed;
      cameraRef.current.radius = Math.max(1.0, Math.min(100.0, cameraRef.current.radius));
      
      await updateOctaneCamera();
    };

    canvas.addEventListener('mousedown', handleMouseDown);
    canvas.addEventListener('mousemove', handleMouseMove);
    canvas.addEventListener('mouseup', handleMouseUp);
    canvas.addEventListener('mouseleave', handleMouseUp);
    canvas.addEventListener('wheel', handleWheel, { passive: false });
    canvas.style.cursor = 'grab';

    return () => {
      canvas.removeEventListener('mousedown', handleMouseDown);
      canvas.removeEventListener('mousemove', handleMouseMove);
      canvas.removeEventListener('mouseup', handleMouseUp);
      canvas.removeEventListener('mouseleave', handleMouseUp);
      canvas.removeEventListener('wheel', handleWheel);
    };
  }, [connected, updateOctaneCamera]);

  return (
    <div className="callback-render-viewport" ref={viewportRef}>
      <div className="viewport-canvas-container">
        {!connected && (
          <div style={{
            position: 'absolute',
            top: '50%',
            left: '50%',
            transform: 'translate(-50%, -50%)',
            color: '#aaa',
            fontSize: '14px',
            textAlign: 'center'
          }}>
            <div style={{ fontSize: '48px', marginBottom: '16px' }}>📡</div>
            <div>Disconnected from Octane</div>
            <div style={{ fontSize: '12px', marginTop: '8px', opacity: 0.7 }}>
              Waiting for LiveLink connection...
            </div>
          </div>
        )}
        {connected && !isRendering && (
          <div style={{
            position: 'absolute',
            top: '50%',
            left: '50%',
            transform: 'translate(-50%, -50%)',
            color: '#aaa',
            fontSize: '14px',
            textAlign: 'center'
          }}>
            <div style={{ fontSize: '48px', marginBottom: '16px' }}>🎬</div>
            <div>{status}</div>
          </div>
        )}
        <canvas
          ref={canvasRef}
          className="render-canvas"
          style={{
            maxWidth: '100%',
            maxHeight: '100%',
            border: '1px solid #444',
            imageRendering: 'pixelated',
            display: 'block',
            margin: 'auto'
          }}
        />
      </div>
      <div className="viewport-status">
        <span>{status}</span>
        <span className="frame-count">Frames: {frameCount}</span>
        {connected && isRendering && (
          <span className="render-indicator" style={{ color: '#4CAF50' }}>● Rendering</span>
        )}
      </div>
    </div>
  );
}
