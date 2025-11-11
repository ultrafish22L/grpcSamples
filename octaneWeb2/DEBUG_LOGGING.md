# Debug Logging System

## Overview

OctaneWeb2 includes an automatic debug logging system that captures all console output and runtime errors, saving them to files that AI agents can read directly. This eliminates the need for humans to copy-paste console logs during development.

## Architecture

```
Browser Console
    ↓
DebugLogger.ts (intercepts)
    ↓
Original console (browser DevTools still works)
    ↓
POST /api/debug/append-log
    ↓
Proxy Server (octane_proxy.py)
    ↓
octaneWeb2/debug_logs/octane-debug-{sessionId}.log
```

## Components

### 1. DebugLogger.ts (`src/utils/DebugLogger.ts`)

**Purpose**: Intercepts console methods and captures all output

**Features**:
- Intercepts `console.log`, `console.error`, `console.warn`
- Captures uncaught errors with stack traces
- Captures unhandled promise rejections
- Preserves original console behavior (browser DevTools still works)
- Session-based logging with unique IDs
- Non-blocking async log transmission
- Prevents infinite loops with `isLogging` flag

**API**:
```typescript
// Initialize (called in main.tsx)
import { initDebugLogger } from './utils/DebugLogger'
initDebugLogger('/api')

// Access from browser console
window.debugLogger.getLogs()           // Get in-memory logs
window.debugLogger.getSessionId()      // Get current session ID
window.debugLogger.clearMemory()       // Clear memory (file logs preserved)
window.debugLogger.restore()           // Restore original console methods
```

### 2. Proxy Server Endpoint (`octaneProxy/octane_proxy.py`)

**Endpoint**: `POST /api/debug/append-log`

**Request Format**:
```json
{
  "sessionId": "l9x2k3p4q5",
  "logEntry": "[2025-11-10T12:34:56.789Z] INFO: Test message",
  "timestamp": "2025-11-10T12:34:56.789Z"
}
```

**Features**:
- Auto-detects calling app (octaneWeb vs octaneWeb2) via Referer header
- Creates appropriate directory: `octaneWeb2/debug_logs/` or `octaneWeb/debug_logs/`
- Creates directory if it doesn't exist
- Appends log entries to session file
- Silent failure if proxy is unavailable (doesn't break app)

### 3. Log Files (`octaneWeb2/debug_logs/`)

**Format**: `octane-debug-{sessionId}.log`

**Example**:
```
[2025-11-10T12:34:56.789Z] INFO: 🚀 DebugLogger initialized
[2025-11-10T12:34:56.790Z] INFO: 📋 Session ID: l9x2k3p4q5
[2025-11-10T12:34:56.791Z] INFO: 📁 Log file: octaneWeb2/debug_logs/octane-debug-l9x2k3p4q5.log
[2025-11-10T12:34:57.100Z] ERROR: ❌ Uncaught Error: Cannot read property 'x' of undefined at App.tsx:42:15
[2025-11-10T12:34:57.101Z] ERROR: Stack trace:
TypeError: Cannot read property 'x' of undefined
    at App (http://localhost:41604/src/App.tsx:42:15)
    at renderWithHooks (react-dom.development.js:14985)
```

## AI Agent Usage

### Quick Commands

```bash
# View latest logs (recommended)
tail -100 /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Watch logs in real-time
tail -f /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# View all logs
cat /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Find errors only
grep -i error /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Find errors with context
grep -B 5 -A 10 -i error /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Find stack traces
grep -A 15 "Stack trace" /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Count errors
grep -c ERROR /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```

### Development Workflow

**OLD WAY (inefficient)**:
1. Make code changes
2. Tell user to refresh browser
3. Ask user to paste console logs
4. Wait for response
5. Debug based on logs

**NEW WAY (efficient)**:
1. Make code changes
2. Check logs directly: `tail -100 octaneWeb2/debug_logs/octane-debug-*.log`
3. Debug and fix immediately
4. Repeat until no errors
5. Only then ask user to verify UX

### Best Practices for AI Agents

1. **Always check logs first** before asking user for console output
2. **Check after every code change** to catch errors immediately
3. **Look for patterns** - multiple similar errors indicate systemic issues
4. **Read stack traces** - they point to exact line numbers
5. **Check timestamps** - see order of operations and timing issues
6. **Watch for warnings** - they often precede errors

### Common Log Patterns

**Initialization Errors**:
```bash
grep "initialized\|connected\|failed" octaneWeb2/debug_logs/*.log
```

**Network Errors**:
```bash
grep -i "fetch\|cors\|network\|connection" octaneWeb2/debug_logs/*.log
```

**React Errors**:
```bash
grep -i "useeffect\|hook\|render\|component" octaneWeb2/debug_logs/*.log
```

**Type Errors**:
```bash
grep -i "undefined\|null\|cannot read property" octaneWeb2/debug_logs/*.log
```

## User Benefits

### No More Copy-Paste
- Users don't need to open DevTools and copy logs
- Logs are automatically saved and persistent
- AI agent can debug independently

### Better Debugging
- Complete session history preserved
- Timestamps show execution order
- Stack traces captured automatically
- Errors can't be missed or forgotten

### Development Speed
- AI agent can iterate faster
- Fewer back-and-forth messages
- User only verifies final result

## Configuration

### Change Proxy URL

Edit `src/main.tsx`:
```typescript
// Default (uses Vite proxy)
initDebugLogger('/api')

// Custom proxy
initDebugLogger('http://localhost:51023')
```

### Disable Logging (Not Recommended)

Comment out in `src/main.tsx`:
```typescript
// initDebugLogger('/api')
```

### Adjust Memory Buffer

Edit `src/utils/DebugLogger.ts`:
```typescript
private maxLogsInMemory = 200  // Change to 500, 1000, etc.
```

## Maintenance

### Cleanup Old Logs

```bash
# Remove logs older than 7 days
find octaneWeb2/debug_logs -name "*.log" -mtime +7 -delete

# Remove all logs
rm octaneWeb2/debug_logs/octane-debug-*.log

# Remove logs for specific session
rm octaneWeb2/debug_logs/octane-debug-l9x2k3p4q5.log
```

### Monitor Log Size

```bash
# Check total size
du -sh octaneWeb2/debug_logs/

# List logs by size
ls -lhS octaneWeb2/debug_logs/*.log

# Find large logs (>1MB)
find octaneWeb2/debug_logs -name "*.log" -size +1M
```

## Troubleshooting

### Logs Not Appearing

1. **Check if logger initialized**:
   ```bash
   grep "DebugLogger initialized" octaneWeb2/debug_logs/*.log
   ```

2. **Check proxy is running**:
   ```bash
   curl http://localhost:51023/health
   ```

3. **Check browser console** (original console still works):
   - Open DevTools (F12)
   - Look for "DebugLogger initialized" message
   - Check for network errors to `/api/debug/append-log`

4. **Check proxy logs**:
   ```bash
   tail -50 /tmp/proxy.log
   ```

### Logs Missing Errors

If logs show successful initialization but errors aren't captured:

1. **Check if error happened before logger init**:
   - Logger must be initialized before errors occur
   - Move `initDebugLogger()` earlier in `main.tsx`

2. **Check if error is caught**:
   - Try/catch blocks prevent error events
   - Add console.error() in catch blocks

### Directory Permissions

If proxy can't write logs:
```bash
# Fix permissions
chmod 755 octaneWeb2/debug_logs
```

## Implementation Details

### Why Intercept Console?

- **Automatic**: No code changes needed to add logging
- **Comprehensive**: Catches all console output automatically
- **Non-invasive**: Original console still works
- **Zero overhead**: Async transmission doesn't block execution

### Why Use Proxy?

- **Security**: Browsers can't write to filesystem directly
- **CORS-safe**: Proxy handles cross-origin requests
- **Centralized**: One endpoint for all logging
- **Flexible**: Can add features like log aggregation, filtering

### Session IDs

**Format**: `{timestamp}.{random}`

**Example**: `l9x2k3p4q5` = `Date.now().toString(36)` + `Math.random().toString(36)`

**Purpose**:
- Separate logs from different sessions
- Track user sessions across page refreshes
- Correlate errors to specific sessions

## Future Enhancements

Possible improvements:

1. **Log levels**: Add verbose/debug/trace levels
2. **Filtering**: Client-side filtering by level or component
3. **Log rotation**: Automatic cleanup of old logs
4. **Visual panel**: Optional UI panel for viewing logs in browser
5. **Search**: Full-text search across log files
6. **Analytics**: Error frequency tracking and reporting
7. **Alerting**: Send alerts for critical errors

## Summary

The debug logging system provides:

✅ **Automatic** console interception  
✅ **Persistent** log file storage  
✅ **AI-friendly** file-based access  
✅ **Non-blocking** async transmission  
✅ **Comprehensive** error capture  
✅ **Zero configuration** for basic use  

This enables faster development cycles by eliminating the need for manual log copying and allowing AI agents to independently debug runtime errors.
