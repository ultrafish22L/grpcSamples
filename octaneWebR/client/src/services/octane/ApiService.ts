/**
 * API Service - Core gRPC communication
 * Handles all API calls to the Octane server
 */

import { getObjectTypeForService, createObjectPtr } from '../../constants/OctaneTypes';
import { BaseService } from './BaseService';

export class ApiService extends BaseService {
  async callApi(service: string, method: string, handle?: any, params: any = {}): Promise<any> {
    const url = `${this.serverUrl}/api/grpc/${service}/${method}`;
    
    // Verbose API logging (commented out to reduce log flooding)
    // console.log(`📤 ${service}.${method}`, handle ? `(handle: ${handle})` : '');
    
    // Build request body - following octaneWeb's makeApiCall logic
    let body: any = {};
    
    // If handle is a string or number (typical case), check if service needs objectPtr wrapping
    if (typeof handle === 'string' || typeof handle === 'number') {
      const objectType = getObjectTypeForService(service);
      
      if (objectType !== undefined) {
        // Service requires objectPtr structure
        // Convert handle to string for objectPtr (proto expects string handles)
        body.objectPtr = createObjectPtr(String(handle), objectType);
        // console.log(`  📦 Created objectPtr:`, body.objectPtr);
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
      // console.log(`  📋 Added params:`, params);
    }
    
    // console.log(`  📨 Request body:`, JSON.stringify(body));
    
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
      // console.log(`✅ ${service}.${method} success`);
      return data;
    } catch (error: any) {
      console.error(`❌ ${service}.${method} error:`, error.message);
      throw error;
    }
  }

  async checkServerHealth(): Promise<boolean> {
    const healthUrl = `${this.serverUrl}/api/health`;
    console.log('📡 Fetching health check:', healthUrl);
    
    const healthResponse = await fetch(healthUrl, {
      method: 'GET',
      headers: { 'Content-Type': 'application/json' }
    });
    
    console.log('📡 Health response status:', healthResponse.status);
    
    if (!healthResponse.ok) {
      const healthData = await healthResponse.json().catch(() => ({}));
      console.error('❌ Server unhealthy:', healthData);
      return false;
    }
    
    const healthData = await healthResponse.json();
    console.log('✅ Server health check passed:', healthData);
    return true;
  }
}
