import axios from 'axios';

export type LogLevel = 'INFO' | 'WARN' | 'ERROR' | 'DEBUG';

interface LogEntry {
  level: LogLevel;
  message: string;
  timestamp: string;
  data?: unknown;
}

class Logger {
  private readonly apiBase = '/api';
  private readonly isDevelopment = import.meta.env.DEV;

  private async sendToServer(entry: LogEntry): Promise<void> {
    try {
      await axios.post(`${this.apiBase}/log`, entry);
    } catch (error) {
      console.error('Failed to send log to server:', error);
    }
  }

  private log(level: LogLevel, message: string, data?: unknown): void {
    const entry: LogEntry = {
      level,
      message,
      timestamp: new Date().toISOString(),
      data,
    };

    const consoleMessage = `[${entry.timestamp}] ${level}: ${message}`;

    switch (level) {
      case 'ERROR':
        console.error(consoleMessage, data);
        break;
      case 'WARN':
        console.warn(consoleMessage, data);
        break;
      case 'DEBUG':
        if (this.isDevelopment) {
          console.debug(consoleMessage, data);
        }
        break;
      default:
        console.log(consoleMessage, data);
    }

    this.sendToServer(entry);
  }

  info(message: string, data?: unknown): void {
    this.log('INFO', message, data);
  }

  warn(message: string, data?: unknown): void {
    this.log('WARN', message, data);
  }

  error(message: string, error?: Error): void {
    const errorData = error
      ? {
          name: error.name,
          message: error.message,
          stack: error.stack,
        }
      : undefined;
    this.log('ERROR', message, errorData);
  }

  debug(message: string, data?: unknown): void {
    this.log('DEBUG', message, data);
  }

  async clear(): Promise<void> {
    try {
      await axios.post(`${this.apiBase}/log/clear`);
      console.log('Logs cleared');
    } catch (error) {
      console.error('Failed to clear logs:', error);
    }
  }

  async getLogs(): Promise<string> {
    try {
      const response = await axios.get(`${this.apiBase}/log`);
      return response.data;
    } catch (error) {
      console.error('Failed to get logs:', error);
      throw error;
    }
  }
}

export const logger = new Logger();
