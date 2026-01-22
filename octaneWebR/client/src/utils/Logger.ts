/**
 * Centralized logging utility for OctaneWebR
 * Provides environment-aware logging with configurable log levels
 */

export enum LogLevel {
  DEBUG = 0,
  INFO = 1,
  WARN = 2,
  ERROR = 3,
  NONE = 4,
}

export interface LoggerConfig {
  level: LogLevel;
  prefix?: string;
  timestamp?: boolean;
  colors?: boolean;
}

class LoggerInstance {
  private config: LoggerConfig;
  private readonly isDevelopment: boolean;

  constructor() {
    // Detect environment
    this.isDevelopment = import.meta.env.MODE === 'development' || import.meta.env.DEV;
    
    // Default configuration
    this.config = {
      level: this.isDevelopment ? LogLevel.DEBUG : LogLevel.WARN,
      prefix: '[OctaneWebR]',
      timestamp: this.isDevelopment,
      colors: true,
    };
  }

  /**
   * Configure logger settings
   */
  configure(config: Partial<LoggerConfig>): void {
    this.config = { ...this.config, ...config };
  }

  /**
   * Get current log level
   */
  getLevel(): LogLevel {
    return this.config.level;
  }

  /**
   * Set log level
   */
  setLevel(level: LogLevel): void {
    this.config.level = level;
  }

  /**
   * Format log message with prefix and timestamp
   */
  private formatMessage(icon: string, ...args: unknown[]): unknown[] {
    const parts: string[] = [];
    
    if (this.config.prefix) {
      parts.push(this.config.prefix);
    }
    
    if (this.config.timestamp) {
      const time = new Date().toLocaleTimeString();
      parts.push(`[${time}]`);
    }
    
    if (this.config.colors) {
      parts.push(icon);
    }
    
    const prefix = parts.length > 0 ? parts.join(' ') : '';
    return prefix ? [prefix, ...args] : args;
  }

  /**
   * Debug level logging (development only)
   */
  debug(...args: unknown[]): void {
    if (this.config.level <= LogLevel.DEBUG) {
      console.log(...this.formatMessage('🔍', ...args));
    }
  }

  /**
   * Info level logging
   */
  info(...args: unknown[]): void {
    if (this.config.level <= LogLevel.INFO) {
      console.log(...this.formatMessage('ℹ️', ...args));
    }
  }

  /**
   * Success logging (special case of info)
   */
  success(...args: unknown[]): void {
    if (this.config.level <= LogLevel.INFO) {
      console.log(...this.formatMessage('✅', ...args));
    }
  }

  /**
   * Warning level logging
   */
  warn(...args: unknown[]): void {
    if (this.config.level <= LogLevel.WARN) {
      console.warn(...this.formatMessage('⚠️', ...args));
    }
  }

  /**
   * Error level logging
   */
  error(...args: unknown[]): void {
    if (this.config.level <= LogLevel.ERROR) {
      console.error(...this.formatMessage('❌', ...args));
    }
  }

  /**
   * Group logging (for nested logs)
   */
  group(label: string): void {
    if (this.config.level <= LogLevel.DEBUG) {
      console.group(...this.formatMessage('📁', label));
    }
  }

  /**
   * End group logging
   */
  groupEnd(): void {
    if (this.config.level <= LogLevel.DEBUG) {
      console.groupEnd();
    }
  }

  /**
   * API call logging (specialized debug)
   */
  api(service: string, method: string, handle?: unknown): void {
    if (this.config.level <= LogLevel.DEBUG) {
      const handleStr = handle ? `(handle: ${handle})` : '';
      this.debug(`📤 ${service}.${method}`, handleStr);
    }
  }

  /**
   * Network logging (specialized debug)
   */
  network(message: string, ...args: unknown[]): void {
    if (this.config.level <= LogLevel.DEBUG) {
      console.log(...this.formatMessage('📡', message, ...args));
    }
  }

  /**
   * Scene logging (specialized debug)
   */
  scene(message: string, ...args: unknown[]): void {
    if (this.config.level <= LogLevel.DEBUG) {
      console.log(...this.formatMessage('🌲', message, ...args));
    }
  }

  /**
   * Render logging (specialized debug)
   */
  render(message: string, ...args: unknown[]): void {
    if (this.config.level <= LogLevel.DEBUG) {
      console.log(...this.formatMessage('🎬', message, ...args));
    }
  }
}

// Export singleton instance
export const Logger = new LoggerInstance();

// Export default for convenience
export default Logger;
