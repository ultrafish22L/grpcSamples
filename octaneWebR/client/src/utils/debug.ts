/**
 * Debug Utility for octaneWebR
 * Provides conditional logging that only runs in development mode
 * 
 * Usage:
 *   import { debug } from '../utils/debug';
 *   debug.log('Node created:', node);        // Only in dev
 *   debug.warn('Deprecated API');            // Only in dev
 *   debug.error('Critical error:', error);   // Always logged
 */

const isDevelopment = process.env.NODE_ENV === 'development';

export const debug = {
  /**
   * Log message (development only)
   * Equivalent to console.log but only runs in dev mode
   */
  log: (...args: any[]): void => {
    if (isDevelopment) {
      console.log(...args);
    }
  },

  /**
   * Warning message (development only)
   * Equivalent to console.warn but only runs in dev mode
   */
  warn: (...args: any[]): void => {
    if (isDevelopment) {
      console.warn(...args);
    }
  },

  /**
   * Error message (always logged)
   * Always logs to console even in production
   */
  error: (...args: any[]): void => {
    console.error(...args);
  },

  /**
   * Info message (development only)
   * Equivalent to console.info but only runs in dev mode
   */
  info: (...args: any[]): void => {
    if (isDevelopment) {
      console.info(...args);
    }
  },

  /**
   * Debug message (development only)
   * Equivalent to console.debug but only runs in dev mode
   */
  debug: (...args: any[]): void => {
    if (isDevelopment) {
      console.debug(...args);
    }
  },

  /**
   * Group log messages (development only)
   */
  group: (label: string): void => {
    if (isDevelopment) {
      console.group(label);
    }
  },

  /**
   * End group (development only)
   */
  groupEnd: (): void => {
    if (isDevelopment) {
      console.groupEnd();
    }
  },

  /**
   * Table display (development only)
   */
  table: (data: any): void => {
    if (isDevelopment) {
      console.table(data);
    }
  },

  /**
   * Time measurement start (development only)
   */
  time: (label: string): void => {
    if (isDevelopment) {
      console.time(label);
    }
  },

  /**
   * Time measurement end (development only)
   */
  timeEnd: (label: string): void => {
    if (isDevelopment) {
      console.timeEnd(label);
    }
  },

  /**
   * Assert (development only)
   */
  assert: (condition: boolean, ...args: any[]): void => {
    if (isDevelopment) {
      console.assert(condition, ...args);
    }
  },
};

/**
 * Performance marker utility (development only)
 * Measures time between start and end calls
 */
export class PerformanceMarker {
  private startTime: number | null = null;
  private label: string;

  constructor(label: string) {
    this.label = label;
  }

  start(): void {
    if (isDevelopment) {
      this.startTime = performance.now();
      debug.log(`⏱️ [${this.label}] Started`);
    }
  }

  end(): void {
    if (isDevelopment && this.startTime !== null) {
      const duration = performance.now() - this.startTime;
      debug.log(`⏱️ [${this.label}] Completed in ${duration.toFixed(2)}ms`);
      this.startTime = null;
    }
  }
}

/**
 * Create a performance marker for timing operations
 * 
 * Usage:
 *   const marker = createPerformanceMarker('Node Creation');
 *   marker.start();
 *   // ... do work
 *   marker.end(); // Logs: "⏱️ [Node Creation] Completed in 123.45ms"
 */
export function createPerformanceMarker(label: string): PerformanceMarker {
  return new PerformanceMarker(label);
}

/**
 * Log only in development mode (shorthand)
 */
export const devLog = debug.log;

/**
 * Check if running in development mode
 */
export const isDevMode = isDevelopment;
