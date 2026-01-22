/**
 * Callback Manager - Handles Octane render callback registration and streaming
 * Port of octaneProxy/callback_streamer.py functionality
 */

import { OctaneGrpcClient } from '../grpc/client';
import { EventEmitter } from 'events';

export class CallbackManager extends EventEmitter {
  private grpcClient: OctaneGrpcClient;
  private callbackId: number = 0;
  private isRegistered: boolean = false;

  constructor(grpcClient: OctaneGrpcClient) {
    super();
    this.grpcClient = grpcClient;
  }

  /**
   * Register for OnNewImage callbacks from Octane
   */
  async registerCallbacks(): Promise<void> {
    if (this.isRegistered) {
      console.log('⚠️ Callbacks already registered');
      return;
    }

    try {
      // Generate unique callback ID
      this.callbackId = Math.floor(Math.random() * 1000000);
      
      console.log(`📡 Registering OnNewImage callback with ID: ${this.callbackId}`);

      // Register callback with Octane
      const response = await this.grpcClient.callMethod('ApiRenderEngine', 'setOnNewImageCallback', {
        callback: {
          callbackSource: 'grpc',
          callbackId: this.callbackId
        },
        userData: 0
      });

      console.log(`✅ Callback registered:`, response);
      this.isRegistered = true;

      // Start listening for callbacks
      await this.startCallbackStream();

    } catch (error: any) {
      console.error('❌ Failed to register callback:', error.message);
      throw error;
    }
  }

  /**
   * Start streaming callbacks from Octane
   * Uses polling instead of streaming due to proto loading limitations
   */
  private async startCallbackStream(): Promise<void> {
    try {
      console.log('✅ Callback stream initialized (using polling mode)');
      
      // Start polling for callbacks every 33ms (30fps)
      this.pollCallbacks();

    } catch (error: any) {
      console.error('❌ Failed to start callback stream:', error.message);
      throw error;
    }
  }

  /**
   * Poll for new render callbacks from Octane
   */
  private async pollCallbacks(): Promise<void> {
    if (!this.isRegistered) {
      return;
    }

    try {
      // Check for new render images
      const response = await this.grpcClient.callMethod('ApiRenderEngine', 'getNewImageFromCallback', {
        callbackId: this.callbackId
      });

      if (response && response.render_images) {
        this.handleCallbackData(response);
      }
    } catch (error: any) {
      // Silently ignore polling errors (Octane might not have new frames)
    }

    // Schedule next poll
    if (this.isRegistered) {
      setTimeout(() => this.pollCallbacks(), 33); // 30fps polling
    }
  }

  /**
   * Handle incoming callback data from Octane
   */
  private handleCallbackData(data: any): void {
    try {
      // Extract render images from callback
      // Check if render_images exists, has a data array, AND that array is not empty
      if (data.render_images && data.render_images.data && Array.isArray(data.render_images.data) && data.render_images.data.length > 0) {
        const imageCount = data.render_images.data.length;
        const firstImage = data.render_images.data[0];
        console.log(`📸 [CallbackManager] Received ${imageCount} render image(s)`);
        console.log(`📸 [CallbackManager] Image details:`, {
          type: firstImage?.type,
          size: firstImage?.size,
          bufferSize: firstImage?.buffer?.size,
          hasData: !!firstImage?.buffer?.data
        });
        
        // Emit OnNewImage event to WebSocket clients
        this.emit('OnNewImage', {
          render_images: data.render_images,
          callback_id: data.callback_id,
          timestamp: Date.now()
        });
      } else {
        // Debug logging for invalid/empty callback data
        console.log('⚠️ [CallbackManager] Callback data has no valid images:', {
          hasRenderImages: !!data.render_images,
          hasData: !!data.render_images?.data,
          isArray: Array.isArray(data.render_images?.data),
          length: data.render_images?.data?.length || 0
        });
      }
    } catch (error: any) {
      console.error('❌ Error handling callback data:', error.message);
    }
  }

  /**
   * Unregister callbacks
   */
  async unregisterCallbacks(): Promise<void> {
    if (!this.isRegistered) {
      return;
    }

    try {
      console.log('📡 Unregistering callbacks');

      // Stop polling
      this.isRegistered = false;

      // Unregister callback (send null callback)
      await this.grpcClient.callMethod('ApiRenderEngine', 'setOnNewImageCallback', {
        callback: null,
        userData: 0
      });

      console.log('✅ Callbacks unregistered');

    } catch (error: any) {
      console.error('❌ Failed to unregister callbacks:', error.message);
    }
  }

  /**
   * Get registration status
   */
  isCallbackRegistered(): boolean {
    return this.isRegistered;
  }
}

let instance: CallbackManager | null = null;

export function getCallbackManager(grpcClient: OctaneGrpcClient): CallbackManager {
  if (!instance) {
    instance = new CallbackManager(grpcClient);
  }
  return instance;
}
