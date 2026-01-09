/**
 * Client-side logger that sends logs to the server for file persistence
 * This helps debug issues by capturing all client-side activity
 */

type LogLevel = 'log' | 'debug' | 'info' | 'warn' | 'error';

class ClientLogger {
  private static instance: ClientLogger;
  private logQueue: Array<{ level: LogLevel; message: string }> = [];
  private enabled: boolean = true;
  private groupStack: string[] = [];

  private constructor() {
    // Intercept console methods
    this.interceptConsole();
    
    // Send logs periodically
    setInterval(() => this.flush(), 1000);
    
    // Send logs before page unload
    if (typeof window !== 'undefined') {
      window.addEventListener('beforeunload', () => this.flush());
    }
  }

  static getInstance(): ClientLogger {
    if (!ClientLogger.instance) {
      ClientLogger.instance = new ClientLogger();
    }
    return ClientLogger.instance;
  }

  private interceptConsole() {
    const originalLog = console.log;
    const originalDebug = console.debug;
    const originalInfo = console.info;
    const originalWarn = console.warn;
    const originalError = console.error;
    const originalGroup = console.group;
    const originalGroupCollapsed = console.groupCollapsed;
    const originalGroupEnd = console.groupEnd;
    const originalTable = console.table;
    const originalTime = console.time;
    const originalTimeEnd = console.timeEnd;

    console.log = (...args: any[]) => {
      originalLog.apply(console, args);
      this.log('log', this.formatArgs(args));
    };

    console.debug = (...args: any[]) => {
      originalDebug.apply(console, args);
      this.log('debug', this.formatArgs(args));
    };

    console.info = (...args: any[]) => {
      originalInfo.apply(console, args);
      this.log('info', this.formatArgs(args));
    };

    console.warn = (...args: any[]) => {
      originalWarn.apply(console, args);
      this.log('warn', this.formatArgs(args));
    };

    console.error = (...args: any[]) => {
      originalError.apply(console, args);
      this.log('error', this.formatArgs(args));
    };

    console.group = (...args: any[]) => {
      originalGroup.apply(console, args);
      const label = this.formatArgs(args);
      this.groupStack.push(label);
      this.log('log', `▼ GROUP: ${label}`);
    };

    console.groupCollapsed = (...args: any[]) => {
      originalGroupCollapsed.apply(console, args);
      const label = this.formatArgs(args);
      this.groupStack.push(label);
      this.log('log', `▶ GROUP (collapsed): ${label}`);
    };

    console.groupEnd = () => {
      originalGroupEnd.apply(console);
      const label = this.groupStack.pop();
      if (label) {
        this.log('log', `▲ END GROUP: ${label}`);
      }
    };

    console.table = (data: any) => {
      originalTable.apply(console, [data]);
      try {
        const tableStr = typeof data === 'object' ? JSON.stringify(data, null, 2) : String(data);
        this.log('log', `TABLE:\n${tableStr}`);
      } catch (e) {
        this.log('log', `TABLE: [unable to serialize]`);
      }
    };

    console.time = (label?: string) => {
      originalTime.apply(console, [label]);
      this.log('log', `⏱️ TIMER START: ${label || 'default'}`);
    };

    console.timeEnd = (label?: string) => {
      originalTimeEnd.apply(console, [label]);
      // Note: The actual timing will show in browser console, we just log the end event
      this.log('log', `⏱️ TIMER END: ${label || 'default'}`);
    };
  }

  private formatArgs(args: any[]): string {
    return args.map(arg => {
      if (typeof arg === 'object') {
        try {
          return JSON.stringify(arg, null, 2);
        } catch (e) {
          return String(arg);
        }
      }
      return String(arg);
    }).join(' ');
  }

  private log(level: LogLevel, message: string) {
    if (!this.enabled) return;
    
    this.logQueue.push({ level, message });
    
    // If queue is getting large, flush immediately
    if (this.logQueue.length > 50) {
      this.flush();
    }
  }

  private async flush() {
    if (this.logQueue.length === 0) return;

    const logsToSend = [...this.logQueue];
    this.logQueue = [];

    try {
      // Send logs to server endpoint
      await fetch('/api/log', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          level: logsToSend[logsToSend.length - 1].level, // Use last log level
          message: logsToSend.map(log => `[${log.level.toUpperCase()}] ${log.message}`).join('\n'),
        }),
      });
    } catch (error) {
      // Silently fail to avoid console spam
      // Don't log error to avoid infinite loop
    }
  }

  public enable() {
    this.enabled = true;
  }

  public disable() {
    this.enabled = false;
  }

  public manualLog(level: LogLevel, message: string) {
    this.log(level, message);
  }
}

// Initialize the logger
export const clientLogger = ClientLogger.getInstance();

// Export a manual logging function for explicit use
export function logToServer(level: LogLevel, message: string) {
  clientLogger.manualLog(level, message);
}
