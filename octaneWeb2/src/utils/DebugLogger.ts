/**
 * Debug Logger - Auto-Save Console Interceptor
 * 
 * Captures all console.log, console.error, console.warn and automatically
 * saves them to a file via the proxy server. This allows AI agents to read
 * runtime errors without needing humans to paste console logs.
 * 
 * Key Features:
 * - Intercepts all console methods (log, error, warn)
 * - Captures uncaught errors and promise rejections
 * - Automatically saves to file via proxy /debug/append-log endpoint
 * - Session-based logging with unique session IDs
 * - Non-blocking - logs are sent async and failures are silent
 * - Preserves original console behavior
 * 
 * Usage:
 * 1. Import and initialize early in app lifecycle
 * 2. All console output automatically saved to debug_logs/
 * 3. Read logs with: cat octaneWeb2/debug_logs/octane-debug-*.log
 * 
 * AI Agent Instructions:
 * - ALWAYS check the log file before asking user for console output
 * - Log file path: /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-{sessionId}.log
 * - Use: tail -100 /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
 */

export type LogLevel = 'info' | 'warn' | 'error'

export interface LogEntry {
  timestamp: string
  level: LogLevel
  message: string
}

export class DebugLogger {
  private sessionId: string
  private proxyUrl: string
  private logs: LogEntry[] = []
  private maxLogsInMemory = 200
  
  // Store original console methods
  private originalLog: typeof console.log
  private originalError: typeof console.error
  private originalWarn: typeof console.warn
  
  // Flag to prevent infinite loops
  private isLogging = false
  
  constructor(proxyUrl: string = '/api') {
    this.sessionId = this.generateSessionId()
    this.proxyUrl = proxyUrl
    
    // Store originals
    this.originalLog = console.log.bind(console)
    this.originalError = console.error.bind(console)
    this.originalWarn = console.warn.bind(console)
    
    // Intercept console methods
    this.interceptConsole()
    
    // Capture global errors
    this.setupGlobalErrorHandlers()
    
    // Log initialization
    this.addLog('info', '🚀 DebugLogger initialized')
    this.addLog('info', `📋 Session ID: ${this.sessionId}`)
    this.addLog('info', `📁 Log file: octaneWeb2/debug_logs/octane-debug-${this.sessionId}.log`)
  }
  
  private generateSessionId(): string {
    return Date.now().toString(36) + Math.random().toString(36).substr(2, 5)
  }
  
  private interceptConsole(): void {
    // Intercept console.log
    console.log = (...args: any[]) => {
      this.originalLog(...args)
      this.addLog('info', this.formatArgs(args))
    }
    
    // Intercept console.error
    console.error = (...args: any[]) => {
      this.originalError(...args)
      this.addLog('error', this.formatArgs(args))
    }
    
    // Intercept console.warn
    console.warn = (...args: any[]) => {
      this.originalWarn(...args)
      this.addLog('warn', this.formatArgs(args))
    }
  }
  
  private setupGlobalErrorHandlers(): void {
    // Capture uncaught errors
    window.addEventListener('error', (event: ErrorEvent) => {
      const errorMsg = `❌ Uncaught Error: ${event.message}`
      const location = `at ${event.filename}:${event.lineno}:${event.colno}`
      this.addLog('error', `${errorMsg} ${location}`)
      
      if (event.error?.stack) {
        this.addLog('error', `Stack trace:\n${event.error.stack}`)
      }
    })
    
    // Capture unhandled promise rejections
    window.addEventListener('unhandledrejection', (event: PromiseRejectionEvent) => {
      const reason = event.reason
      this.addLog('error', `❌ Unhandled Promise Rejection: ${reason}`)
      
      if (reason?.stack) {
        this.addLog('error', `Stack trace:\n${reason.stack}`)
      }
    })
  }
  
  private formatArgs(args: any[]): string {
    return args.map(arg => {
      if (arg === null) return 'null'
      if (arg === undefined) return 'undefined'
      if (typeof arg === 'object') {
        try {
          return JSON.stringify(arg, null, 2)
        } catch (e) {
          return String(arg)
        }
      }
      return String(arg)
    }).join(' ')
  }
  
  private addLog(level: LogLevel, message: string): void {
    // Prevent infinite loops
    if (this.isLogging) return
    this.isLogging = true
    
    try {
      const timestamp = new Date().toISOString()
      const entry: LogEntry = { timestamp, level, message }
      
      // Add to memory buffer
      this.logs.push(entry)
      
      // Trim old logs
      if (this.logs.length > this.maxLogsInMemory) {
        this.logs.shift()
      }
      
      // Send to proxy (async, non-blocking)
      this.sendLogToProxy(entry).catch(() => {
        // Silently fail - don't spam console with proxy errors
        // Original console methods still work
      })
    } finally {
      this.isLogging = false
    }
  }
  
  private async sendLogToProxy(entry: LogEntry): Promise<void> {
    try {
      const logLine = `[${entry.timestamp}] ${entry.level.toUpperCase()}: ${entry.message}`
      
      await fetch(`${this.proxyUrl}/debug/append-log`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          sessionId: this.sessionId,
          logEntry: logLine,
          timestamp: entry.timestamp
        })
      })
    } catch (error) {
      // Silently fail - proxy might not be available during development
    }
  }
  
  /**
   * Get all logs in memory
   */
  public getLogs(): LogEntry[] {
    return [...this.logs]
  }
  
  /**
   * Get session ID
   */
  public getSessionId(): string {
    return this.sessionId
  }
  
  /**
   * Clear in-memory logs (file logs are preserved)
   */
  public clearMemory(): void {
    this.logs = []
    this.addLog('info', '🧹 Memory logs cleared')
  }
  
  /**
   * Restore original console methods (for cleanup)
   */
  public restore(): void {
    console.log = this.originalLog
    console.error = this.originalError
    console.warn = this.originalWarn
    
    this.originalLog('DebugLogger restored original console methods')
  }
}

// Create singleton instance
let debugLoggerInstance: DebugLogger | null = null

/**
 * Initialize the debug logger (call this early in app lifecycle)
 */
export function initDebugLogger(proxyUrl?: string): DebugLogger {
  if (!debugLoggerInstance) {
    debugLoggerInstance = new DebugLogger(proxyUrl)
    
    // Make it globally accessible for debugging
    ;(window as any).debugLogger = debugLoggerInstance
  }
  return debugLoggerInstance
}

/**
 * Get the debug logger instance
 */
export function getDebugLogger(): DebugLogger | null {
  return debugLoggerInstance
}

export default DebugLogger
