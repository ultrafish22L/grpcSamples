# Debug Logs Directory

This directory contains runtime console logs from octaneWeb2 browser sessions.

## Overview

The **DebugLogger** system automatically captures all console output (log, error, warn) and saves it to files in this directory. This allows AI agents to debug runtime errors without needing humans to paste console logs.

## Log Files

- **Format**: `octane-debug-{sessionId}.log`
- **Session ID**: Generated timestamp + random suffix (e.g., `l9x2k3p4q5`)
- **Content**: All console.log, console.error, console.warn messages with timestamps
- **Also captures**: Uncaught errors, unhandled promise rejections with stack traces

## How It Works

1. **DebugLogger.ts** intercepts console methods at app startup
2. All logs are forwarded to original console (browser console still works)
3. Logs are sent async to proxy server `/api/debug/append-log` endpoint
4. Proxy server writes logs to this directory
5. Logs persist across page refreshes for debugging

## AI Agent Usage

**Check logs before asking user for console output:**

```bash
# View latest log file
tail -100 /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# View all recent logs
cat /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Watch logs in real-time
tail -f /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Find errors
grep -i error /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Find stack traces
grep -A 10 "Stack trace" /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```

## Log Format

```
[2025-11-10T12:34:56.789Z] INFO: 🚀 DebugLogger initialized
[2025-11-10T12:34:56.790Z] INFO: 📋 Session ID: l9x2k3p4q5
[2025-11-10T12:34:57.100Z] ERROR: ❌ Uncaught Error: Cannot read property 'x' of undefined at App.tsx:42:15
[2025-11-10T12:34:57.101Z] ERROR: Stack trace:
TypeError: Cannot read property 'x' of undefined
    at App (http://localhost:41604/src/App.tsx:42:15)
    at renderWithHooks (react-dom.development.js:14985)
```

## Cleanup

Log files accumulate over time. Clean up old logs periodically:

```bash
# Remove logs older than 7 days
find /workspace/grpcSamples/octaneWeb2/debug_logs -name "octane-debug-*.log" -mtime +7 -delete

# Remove all logs
rm /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```

## Configuration

To disable logging or change proxy URL, edit `src/main.tsx`:

```typescript
// Disable logging (not recommended)
// initDebugLogger('/api')

// Change proxy URL
initDebugLogger('http://custom-proxy:8080/api')
```

## Development Workflow

1. **Make code changes** in src/
2. **Vite HMR** rebuilds automatically
3. **Refresh browser** if needed
4. **Check logs** with `tail -100 debug_logs/octane-debug-*.log`
5. **Fix errors** and repeat

No more copy-pasting console logs! 🎉
