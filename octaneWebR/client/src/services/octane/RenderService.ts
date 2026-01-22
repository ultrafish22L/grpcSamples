/**
 * Render Service - Render control and settings management
 * Handles render operations, modes, regions, and statistics
 */

import { BaseService } from './BaseService';
import { ApiService } from './ApiService';
import { RenderState, RenderRegion } from './types';

export class RenderService extends BaseService {
  private apiService: ApiService;
  private renderState: RenderState;

  constructor(emitter: any, serverUrl: string, apiService: ApiService) {
    super(emitter, serverUrl);
    this.apiService = apiService;
    this.renderState = {
      isRendering: false,
      progress: 0,
      samples: 0,
      renderTime: 0,
      resolution: { width: 1920, height: 1080 }
    };
  }

  async startRender(): Promise<void> {
    await this.apiService.callApi('ApiRenderEngine', 'continueRendering', {});
    this.renderState.isRendering = true;
    this.emit('renderStateChanged', this.renderState);
  }

  async stopRender(): Promise<void> {
    await this.apiService.callApi('ApiRenderEngine', 'stopRendering', {});
    this.renderState.isRendering = false;
    this.emit('renderStateChanged', this.renderState);
  }

  async pauseRender(): Promise<void> {
    await this.apiService.callApi('ApiRenderEngine', 'pauseRendering', {});
    this.renderState.isRendering = false;
    this.emit('renderStateChanged', this.renderState);
  }

  async restartRender(): Promise<void> {
    await this.apiService.callApi('ApiRenderEngine', 'restartRendering', {});
    this.renderState.isRendering = true;
    this.renderState.samples = 0;
    this.emit('renderStateChanged', this.renderState);
  }

  async getClayMode(): Promise<number> {
    const response = await this.apiService.callApi('ApiRenderEngine', 'clayMode', {});
    return response?.result ?? 0;
  }

  async setClayMode(mode: number): Promise<void> {
    await this.apiService.callApi('ApiRenderEngine', 'setClayMode', null, { mode });
  }

  async getSubSampleMode(): Promise<number> {
    const response = await this.apiService.callApi('ApiRenderEngine', 'getSubSampleMode', {});
    return response?.result ?? 1;
  }

  async setSubSampleMode(mode: number): Promise<void> {
    await this.apiService.callApi('ApiRenderEngine', 'setSubSampleMode', null, { mode });
  }

  async getRenderStatistics(): Promise<any> {
    try {
      const response = await this.apiService.callApi('ApiRenderEngine', 'getRenderStatistics', 0, {});
      return response?.statistics || null;
    } catch (error: any) {
      console.error('❌ Failed to get render statistics:', error.message);
      return null;
    }
  }

  async getRenderRegion(): Promise<RenderRegion> {
    try {
      const response = await this.apiService.callApi('ApiRenderEngine', 'getRenderRegion', {});
      return {
        active: response?.active ?? false,
        regionMin: response?.regionMin ?? { x: 0, y: 0 },
        regionMax: response?.regionMax ?? { x: 1920, y: 1080 },
        featherWidth: response?.featherWidth ?? 0
      };
    } catch (error: any) {
      console.error('❌ Failed to get render region:', error.message);
      return {
        active: false,
        regionMin: { x: 0, y: 0 },
        regionMax: { x: 1920, y: 1080 },
        featherWidth: 0
      };
    }
  }

  async setRenderRegion(
    active: boolean,
    regionMin: { x: number; y: number },
    regionMax: { x: number; y: number },
    featherWidth: number = 0
  ): Promise<void> {
    try {
      await this.apiService.callApi('ApiRenderEngine', 'setRenderRegion', null, {
        active,
        regionMin,
        regionMax,
        featherWidth
      });
      console.log(`✅ Render region ${active ? 'enabled' : 'disabled'}:`, { regionMin, regionMax, featherWidth });
    } catch (error: any) {
      console.error('❌ Failed to set render region:', error.message);
      throw error;
    }
  }

  private async getFilmSettingsNode(): Promise<number | null> {
    try {
      // Get render target
      const renderTargetResponse = await this.apiService.callApi('ApiRenderEngine', 'getRenderTargetNode', {});
      if (!renderTargetResponse?.result?.handle) {
        console.warn('⚠️ No render target found');
        return null;
      }
      
      const renderTargetHandle = renderTargetResponse.result.handle;
      
      // Get Film Settings connected to render target (typically pin 15)
      const filmSettingsResponse = await this.apiService.callApi('ApiNode', 'connectedNode', renderTargetHandle, { pinIndex: 15 });
      const handle = filmSettingsResponse?.result?.handle;
      
      // Handle "0" means no connection, treat as null
      if (!handle || handle === "0" || handle === 0) {
        console.warn('⚠️ No Film Settings node connected to render target');
        return null;
      }
      
      return handle;
    } catch (error: any) {
      console.error('❌ Failed to get Film Settings node:', error.message);
      return null;
    }
  }

  async getViewportResolutionLock(): Promise<boolean> {
    try {
      const filmSettingsHandle = await this.getFilmSettingsNode();
      if (!filmSettingsHandle) {
        return false;
      }

      // P_LOCK_RENDER_AOVS = 2672 (from common.proto AttributeId enum)
      const attrIndexResponse = await this.apiService.callApi('ApiItem', 'findAttr', filmSettingsHandle, { id: 2672 });
      if (attrIndexResponse?.result === undefined || attrIndexResponse.result < 0) {
        console.warn('⚠️ P_LOCK_RENDER_AOVS attribute not found');
        return false;
      }

      const attrIndex = attrIndexResponse.result;

      // Get the boolean value using getPinValueByIx (apinodesystem_7.proto)
      const valueResponse = await this.apiService.callApi('ApiNode', 'getPinValueByIx', filmSettingsHandle, { index: attrIndex });
      return valueResponse?.bool_value ?? false;
    } catch (error: any) {
      console.error('❌ Failed to get viewport resolution lock:', error.message);
      return false;
    }
  }

  async setViewportResolutionLock(locked: boolean): Promise<void> {
    try {
      const filmSettingsHandle = await this.getFilmSettingsNode();
      if (!filmSettingsHandle) {
        throw new Error('Film Settings node not found');
      }

      // P_LOCK_RENDER_AOVS = 2672 (from common.proto AttributeId enum)
      const attrIndexResponse = await this.apiService.callApi('ApiItem', 'findAttr', filmSettingsHandle, { id: 2672 });
      if (attrIndexResponse?.result === undefined || attrIndexResponse.result < 0) {
        throw new Error('P_LOCK_RENDER_AOVS attribute not found');
      }

      const attrIndex = attrIndexResponse.result;

      // Set the boolean value using setPinValueByIx (apinodesystem_7.proto)
      await this.apiService.callApi('ApiNode', 'setPinValueByIx', filmSettingsHandle, {
        index: attrIndex,
        bool_value: locked
      });
    } catch (error: any) {
      console.error('❌ Failed to set viewport resolution lock:', error.message);
      throw error;
    }
  }

  getRenderState(): RenderState {
    return this.renderState;
  }
}
