/**
 * Simple EventEmitter for TypeScript
 */

type EventHandler = (...args: any[]) => void;

export class EventEmitter {
  private events: Map<string, EventHandler[]> = new Map();

  on(event: string, handler: EventHandler): void {
    if (!this.events.has(event)) {
      this.events.set(event, []);
    }
    this.events.get(event)!.push(handler);
    console.log(`🎧 [EventEmitter] Registered listener for '${event}' (total: ${this.events.get(event)!.length})`);
  }

  off(event: string, handler: EventHandler): void {
    const handlers = this.events.get(event);
    if (handlers) {
      const index = handlers.indexOf(handler);
      if (index > -1) {
        handlers.splice(index, 1);
      }
    }
  }

  emit(event: string, ...args: any[]): void {
    const handlers = this.events.get(event);
    if (handlers) {
      console.log(`📢 [EventEmitter] Emitting '${event}' to ${handlers.length} listener(s)`);
      handlers.forEach(handler => handler(...args));
    } else {
      console.warn(`⚠️  [EventEmitter] No listeners for event '${event}'`);
    }
  }

  removeAllListeners(event?: string): void {
    if (event) {
      this.events.delete(event);
    } else {
      this.events.clear();
    }
  }
}
