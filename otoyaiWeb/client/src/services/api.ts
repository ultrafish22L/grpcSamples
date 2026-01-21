import axios from 'axios';
import { EndpointsResponse } from '../types';
import { logger } from './logger';

const OTOY_API_BASE = '/otoy-api';

export interface ExecutionRequest {
  endpoint_id: string;
  parameters: Record<string, any>;
}

export interface ExecutionResponse {
  success: boolean;
  data?: any;
  error?: string;
  request_id?: string;
}

class OtoyAPI {
  async fetchEndpoints(): Promise<EndpointsResponse> {
    try {
      logger.info('Fetching endpoints from play.otoy.ai');
      const startTime = performance.now();

      const response = await axios.get<EndpointsResponse>(`${OTOY_API_BASE}/endpoints`);

      const duration = performance.now() - startTime;
      logger.info(`Endpoints fetched successfully in ${duration.toFixed(2)}ms`, {
        count: response.data.endpoints.length,
      });

      return response.data;
    } catch (error) {
      logger.error('Failed to fetch endpoints', error as Error);
      throw error;
    }
  }

  async executeEndpoint(request: ExecutionRequest): Promise<ExecutionResponse> {
    try {
      logger.info('Executing endpoint', {
        endpoint: request.endpoint_id,
        paramCount: Object.keys(request.parameters).length,
      });
      const startTime = performance.now();

      const response = await axios.post<ExecutionResponse>(
        `${OTOY_API_BASE}/execute`,
        request,
        {
          timeout: 120000, // 2 minute timeout for long-running operations
        }
      );

      const duration = performance.now() - startTime;
      logger.info(`Execution completed in ${duration.toFixed(2)}ms`, {
        endpoint: request.endpoint_id,
        success: response.data.success,
      });

      return response.data;
    } catch (error) {
      logger.error('Execution failed', error as Error);
      throw error;
    }
  }
}

export const otoyAPI = new OtoyAPI();
