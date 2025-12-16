/**
 * Callback-based Render Viewport Component (React TypeScript)
 * Port of octaneWeb's CallbackRenderViewport with identical buffer processing
 */

import React, { useEffect, useRef, useState } from 'react';
import { useOctane } from '../hooks/useOctane';

interface ImageData {
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
    data: ImageData[];
  };
  timestamp?: number;
  callback_id?: string;
}

export function CallbackRenderViewport() {
  const { client, connected } = useOctane();
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [frameCount, setFrameCount] = useState(0);
  const [status, setStatus] = useState('Initializing...');

  useEffect(() => {
    if (!connected) return;

    // Setup callback listener
    const handleNewImage = (data: CallbackData) => {
      if (data.render_images && data.render_images.data && data.render_images.data.length > 0) {
        displayCallbackImage(data.render_images.data[0]);
      }
    };

    client.on('OnNewImage', handleNewImage);

    return () => {
      client.off('OnNewImage', handleNewImage);
    };
  }, [connected, client]);

  /**
   * Display image from callback data
   * CRITICAL: Direct port of octaneWeb buffer processing logic
   */
  const displayCallbackImage = (imageData: ImageData) => {
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
  };

  /**
   * Convert raw buffer to canvas ImageData
   * CRITICAL: Exact port of octaneWeb conversion logic
   */
  const convertBufferToCanvas = (
    buffer: Uint8Array,
    imageData: ImageData,
    canvasImageData: ImageData
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

  return (
    <div className="callback-render-viewport">
      <div className="viewport-canvas-container">
        <canvas
          ref={canvasRef}
          className="render-canvas"
          style={{
            maxWidth: '100%',
            maxHeight: '100%',
            border: '1px solid #444',
            imageRendering: 'pixelated'
          }}
        />
      </div>
      <div className="viewport-status">
        <span>{status}</span>
        <span className="frame-count">Frames: {frameCount}</span>
      </div>
    </div>
  );
}
