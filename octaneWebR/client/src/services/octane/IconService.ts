/**
 * Icon Service - Node icon fetching and caching
 * Handles icon retrieval from Octane and caching
 */

import { BaseService } from './BaseService';
import { ApiService } from './ApiService';

export class IconService extends BaseService {
  private apiService: ApiService;
  private iconCache: Map<string, string> = new Map();
  private iconFetchQueue: Set<string> = new Set();
  private iconFetchInProgress: boolean = false;

  constructor(emitter: any, serverUrl: string, apiService: ApiService) {
    super(emitter, serverUrl);
    this.apiService = apiService;
  }

  async getNodeIconImage(nodeType: string): Promise<string | null> {
    // Check cache first
    if (this.iconCache.has(nodeType)) {
      return this.iconCache.get(nodeType)!;
    }

    try {
      // Query icon image from Octane via ApiInfo.nodeIconImage
      const response = await this.apiService.callApi('ApiInfo', 'nodeIconImage', null, { nodeType });
      
      if (!response || !response.result) {
        console.warn(`⚠️ No icon found for node type: ${nodeType}`);
        return null;
      }

      // Get the image handle from ObjectRef
      const imageHandle = response.result.handle || response.result;
      
      // Get image data - Octane returns image as ApiImage with data
      const imageDataResponse = await this.apiService.callApi('ApiImage', 'getData', imageHandle);
      
      if (!imageDataResponse || !imageDataResponse.data) {
        console.warn(`⚠️ No image data for icon: ${nodeType}`);
        return null;
      }

      // Convert image data to data URI
      const base64Data = imageDataResponse.data;
      const dataUri = `data:image/png;base64,${base64Data}`;
      
      // Cache the icon
      this.iconCache.set(nodeType, dataUri);
      console.log(`✅ Cached icon for: ${nodeType}`);
      
      return dataUri;
    } catch (error: any) {
      console.error(`❌ Failed to fetch icon for ${nodeType}:`, error.message);
      return null;
    }
  }

  queueIconFetch(nodeType: string): void {
    if (!this.iconCache.has(nodeType) && !this.iconFetchQueue.has(nodeType)) {
      this.iconFetchQueue.add(nodeType);
      // Start background processing if not already running
      this.processIconQueue();
    }
  }

  private async processIconQueue(): Promise<void> {
    if (this.iconFetchInProgress || this.iconFetchQueue.size === 0) {
      return;
    }

    this.iconFetchInProgress = true;

    try {
      // Process icons one at a time to avoid overwhelming the server
      for (const nodeType of this.iconFetchQueue) {
        this.iconFetchQueue.delete(nodeType);
        
        const icon = await this.getNodeIconImage(nodeType);
        
        if (icon) {
          // Emit event so UI can update
          this.emit('icon-loaded', { nodeType, icon });
        }
        
        // Small delay to prevent flooding
        await new Promise(resolve => setTimeout(resolve, 50));
      }
    } finally {
      this.iconFetchInProgress = false;
      
      // Check if more items were added during processing
      if (this.iconFetchQueue.size > 0) {
        this.processIconQueue();
      }
    }
  }

  getCachedIcon(nodeType: string): string | null {
    return this.iconCache.get(nodeType) || null;
  }
}
