/**
 * Base service class providing common functionality for all Octane services
 */

import { EventEmitter } from '../../utils/EventEmitter';

export abstract class BaseService {
  protected emitter: EventEmitter;
  protected serverUrl: string;

  constructor(emitter: EventEmitter, serverUrl: string) {
    this.emitter = emitter;
    this.serverUrl = serverUrl;
  }

  protected emit(event: string, data?: any): void {
    this.emitter.emit(event, data);
  }

  protected on(event: string, handler: (...args: any[]) => void): void {
    this.emitter.on(event, handler);
  }

  protected off(event: string, handler: (...args: any[]) => void): void {
    this.emitter.off(event, handler);
  }
}
