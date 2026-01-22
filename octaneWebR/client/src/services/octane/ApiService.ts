/**
 * API Service - Core gRPC communication
 * Handles all API calls to the Octane server
 */

import { getObjectTypeForService, createObjectPtr } from '../../constants/OctaneTypes';
import { BaseService } from './BaseService';
import Logger from '../../utils/Logger';

/**
 * Request body structure for API calls
 */
interface ApiRequestBody {
  objectPtr?: {
    handle: string;
    type: number;
  };
  handle?: string | number;
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  [key: string]: any;
}

/**
 * API Service handles all gRPC communication with Octane server
 */
export class ApiService extends BaseService {
  /**
   * Make a gRPC API call to the Octane server
   * @param service - Service name (e.g., 'ApiItem', 'ApiScene')
   * @param method - Method name (e.g., 'getValueByAttrID')
   * @param handle - Node handle, null, or request object
   * @param params - Additional parameters to merge into request
   * @returns Promise resolving to the API response data
   * @note Returns 'any' type as API responses have dynamic structure from gRPC
   */
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  async callApi(
    service: string, 
    method: string, 
    handle?: string | number | Record<string, unknown> | null, 
    params: Record<string, unknown> = {}
  ): Promise<any> {
    const url = `${this.serverUrl}/api/grpc/${service}/${method}`;
    
    Logger.api(service, method, handle);
    
    // Build request body - following octaneWeb's makeApiCall logic
    let body: ApiRequestBody = {};
    
    // If handle is a string or number (typical case), check if service needs objectPtr wrapping
    if (typeof handle === 'string' || typeof handle === 'number') {
      const objectType = getObjectTypeForService(service);
      
      if (objectType !== undefined) {
        // Service requires objectPtr structure
        // Convert handle to string for objectPtr (proto expects string handles)
        body.objectPtr = createObjectPtr(String(handle), objectType);
        Logger.debug('Created objectPtr:', body.objectPtr);
      } else {
        // No objectPtr needed, pass handle directly
        body.handle = handle;
      }
    } else if (handle !== undefined && handle !== null) {
      // Handle is an object, merge it into body
      body = { ...handle };
    }
    
    // Merge additional params
    if (params && Object.keys(params).length > 0) {
      body = { ...body, ...params };
      Logger.debug('Added params:', params);
    }
    
    Logger.debug('Request body:', JSON.stringify(body));
    
    try {
      const response = await fetch(url, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(body)
      });
      
      if (!response.ok) {
        const error = await response.json();
        throw new Error(error.error || `API call failed: ${response.status}`);
      }
      
      const data = await response.json();
      Logger.debug(`${service}.${method} success`);
      return data;
    } catch (error) {
      const errorMessage = error instanceof Error ? error.message : 'Unknown error';
      Logger.error(`${service}.${method} error:`, errorMessage);
      throw error;
    }
  }

  /**
   * Check if the Octane server is healthy and responding
   * @returns Promise resolving to true if server is healthy, false otherwise
   */
  async checkServerHealth(): Promise<boolean> {
    const healthUrl = `${this.serverUrl}/api/health`;
    Logger.network('Fetching health check:', healthUrl);
    
    try {
      const healthResponse = await fetch(healthUrl, {
        method: 'GET',
        headers: { 'Content-Type': 'application/json' }
      });
      
      Logger.debug('Health response status:', healthResponse.status);
      
      if (!healthResponse.ok) {
        const healthData = await healthResponse.json().catch(() => ({}));
        Logger.error('Server unhealthy:', healthData);
        return false;
      }
      
      const healthData = await healthResponse.json();
      Logger.success('Server health check passed:', healthData);
      return true;
    } catch (error) {
      const errorMessage = error instanceof Error ? error.message : 'Unknown error';
      Logger.error('Health check failed:', errorMessage);
      return false;
    }
  }
}
