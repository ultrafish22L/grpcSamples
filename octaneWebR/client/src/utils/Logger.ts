/**
 * Logger Utility
 * Provides conditional logging based on environment
 * Production builds automatically remove debug logs via tree-shaking
 */

const isDevelopment = import.meta.env.DEV;
const isDebugEnabled = import.meta.env.VITE_DEBUG === 'true' || isDevelopment;

export const Logger = {
  /**
   * Debug level - only logs in development mode
   * Completely removed in production builds
   */
  debug: (...args: any[]) => {
    if (isDebugEnabled) {
      console.debug('[DEBUG]', ...args);
    }
  },

  /**
   * Info level - logs in development mode
   * Can be enabled in production via VITE_INFO=true
   */
  info: (...args: any[]) => {
    if (isDevelopment || import.meta.env.VITE_INFO === 'true') {
      console.info('[INFO]', ...args);
    }
  },

  /**
   * Warning level - always logs
   */
  warn: (...args: any[]) => {
    console.warn('[WARN]', ...args);
  },

  /**
   * Error level - always logs
   */
  error: (...args: any[]) => {
    console.error('[ERROR]', ...args);
  },

  /**
   * Group logging for better console organization
   */
  group: (label: string, collapsed: boolean = false) => {
    if (isDevelopment) {
      if (collapsed) {
        console.groupCollapsed(label);
      } else {
        console.group(label);
      }
    }
  },

  groupEnd: () => {
    if (isDevelopment) {
      console.groupEnd();
    }
  },

  /**
   * Performance timing
   */
  time: (label: string) => {
    if (isDevelopment) {
      console.time(label);
    }
  },

  timeEnd: (label: string) => {
    if (isDevelopment) {
      console.timeEnd(label);
    }
  },

  /**
   * Table display for structured data
   */
  table: (data: any) => {
    if (isDevelopment) {
      console.table(data);
    }
  }
};

/**
 * Conditional logging wrapper
 * Usage: if (DEV) Logger.debug('message')
 */
export const DEV = isDevelopment;
