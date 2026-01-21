import axios from 'axios';
import { EndpointsResponse } from '../types';
import { logger } from './logger';

const OTOY_API_BASE = 'https://play.otoy.ai/api';

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
}

export const otoyAPI = new OtoyAPI();
