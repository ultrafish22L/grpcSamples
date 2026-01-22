/**
 * Viewport Service - Viewport picking and interaction
 * Handles picking objects, materials, white points, and scene info
 */

import { BaseService } from './BaseService';
import { ApiService } from './ApiService';

export class ViewportService extends BaseService {
  private apiService: ApiService;

  constructor(emitter: any, serverUrl: string, apiService: ApiService) {
    super(emitter, serverUrl);
    this.apiService = apiService;
  }

  async pick(x: number, y: number): Promise<any[]> {
    try {
      console.log(`🎯 Picking at viewport position (${x}, ${y})...`);
      const response = await this.apiService.callApi('ApiRenderEngine', 'pick', null, {
        position: { x, y }
      });
      
      if (!response?.intersections || response.intersections.length === 0) {
        console.log('🎯 Pick: No intersections found');
        return [];
      }
      
      console.log(`🎯 Pick: Found ${response.intersections.length} intersection(s)`);
      console.log('🎯 Pick result:', response.intersections);
      return response.intersections;
    } catch (error: any) {
      console.error('❌ Failed to pick at viewport position:', error.message);
      return [];
    }
  }

  async pickWhitePoint(x: number, y: number): Promise<{ x: number; y: number; z: number } | null> {
    try {
      const response = await this.apiService.callApi('ApiRenderEngine', 'pickWhitePoint', null, { x, y });
      if (response?.result && response?.whitePoint) {
        console.log(`✅ White point picked at (${x}, ${y}):`, response.whitePoint);
        return response.whitePoint;
      } else {
        console.warn('⚠️ No white point returned from pick');
        return null;
      }
    } catch (error: any) {
      console.error('❌ Failed to pick white point:', error.message);
      throw error;
    }
  }

  async pickSceneInfo(x: number, y: number): Promise<any> {
    try {
      const response = await this.apiService.callApi('ApiRenderEngine', 'pick', null, {
        x,
        y,
        filterDuplicateMaterialPins: true,
        intersectionsSize: 10
      });
      console.log(`🎯 Scene pick at (${x}, ${y}):`, response);
      return response;
    } catch (error: any) {
      console.error('❌ Failed to pick scene info:', error.message);
      throw error;
    }
  }
}
