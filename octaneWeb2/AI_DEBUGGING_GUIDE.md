# AI Agent Debugging Guide - Quick Reference

## 🚨 ALWAYS DO THIS FIRST

Before asking user for console logs or errors:

```bash
tail -100 /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```

If no logs exist, ask user to refresh browser at **http://localhost:41604**

## Common Debugging Commands

### View Recent Logs
```bash
# Last 100 lines (recommended)
tail -100 /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Last 50 lines
tail -50 /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# All logs
cat /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```

### Watch Logs in Real-Time
```bash
tail -f /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```
(Press Ctrl+C to stop)

### Find Errors
```bash
# Errors only
grep ERROR /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Errors with context
grep -B 5 -A 10 ERROR /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Count errors
grep -c ERROR /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```

### Find Stack Traces
```bash
# Stack traces with full context
grep -A 20 "Stack trace" /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Just the error lines
grep "at.*\.tsx:" /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```

### Find Specific Issues
```bash
# CORS errors
grep -i cors /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Network errors
grep -i "fetch\|network" /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# React errors
grep -i "useeffect\|hook\|render" /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Type errors
grep -i "undefined\|cannot read" /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```

## Development Workflow

### Standard Workflow (With Logs)

1. **Make code changes**
2. **Check logs**:
   ```bash
   tail -100 /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
   ```
3. **If errors found**:
   - Read error message and stack trace
   - Fix the code
   - Repeat from step 1
4. **If no errors**:
   - Ask user to verify UX/functionality

### If No Logs Exist

1. Ask user: "Please refresh your browser at http://localhost:41604"
2. Wait for response
3. Check logs again
4. Continue with standard workflow

### After Making Fixes

```bash
# Clear screen and check latest logs
clear && tail -50 /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```

## Server Status Check

```bash
# Check Vite dev server
curl -s http://localhost:41604 | head -3

# Check proxy server
curl -s http://localhost:51023/health

# View server logs
tail -20 /tmp/vite_dev.log    # Vite
tail -20 /tmp/proxy.log        # Proxy
```

## Common Error Patterns

### "Cannot read property 'x' of undefined"
```bash
grep -B 5 -A 5 "Cannot read property" /workspace/grpcSamples/octaneWeb2/debug_logs/*.log
```
**Solution**: Add null checks or optional chaining (`?.`)

### "Invalid pointer type"
```bash
grep -B 5 -A 5 "invalid pointer" /workspace/grpcSamples/octaneWeb2/debug_logs/*.log
```
**Solution**: Handle variable is undefined, add guard clause

### CORS Errors
```bash
grep -B 5 -A 5 -i cors /workspace/grpcSamples/octaneWeb2/debug_logs/*.log
```
**Solution**: Check Vite proxy config, ensure using `/api` prefix

### React Hook Errors
```bash
grep -B 5 -A 5 -i "useeffect\|hook" /workspace/grpcSamples/octaneWeb2/debug_logs/*.log
```
**Solution**: Check dependency arrays, ensure hooks at top level

## Log File Locations

```
/workspace/grpcSamples/
├── octaneWeb2/
│   └── debug_logs/
│       ├── octane-debug-{sessionId}.log  ← NEW logs here
│       └── README.md
└── octaneWeb/
    └── debug_logs/
        └── octane-debug-{sessionId}.log  ← OLD logs here
```

## When Logs Are Missing

### Check if logger is initialized
```bash
grep "DebugLogger initialized" /workspace/grpcSamples/octaneWeb2/debug_logs/*.log
```

### Check if proxy is running
```bash
ps aux | grep octane_proxy | grep -v grep
```

### Check proxy logs for errors
```bash
tail -30 /tmp/proxy.log | grep -i error
```

## Session Management

### Find current session ID
```bash
ls -lt /workspace/grpcSamples/octaneWeb2/debug_logs/*.log | head -1
```

### View specific session
```bash
cat /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-l9x2k3p4q5.log
```

### Compare sessions
```bash
# Count errors in each session
for log in /workspace/grpcSamples/octaneWeb2/debug_logs/*.log; do
  echo "$log: $(grep -c ERROR "$log") errors"
done
```

## Cleanup

```bash
# Remove all logs
rm /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log

# Remove logs older than 7 days
find /workspace/grpcSamples/octaneWeb2/debug_logs -name "*.log" -mtime +7 -delete
```

## Quick Checks

### Is everything running?
```bash
echo "=== SERVER STATUS ===" && \
echo "Vite: $(curl -s -o /dev/null -w '%{http_code}' http://localhost:41604)" && \
echo "Proxy: $(curl -s http://localhost:51023/health | jq -r .status)" && \
echo "Logs: $(ls /workspace/grpcSamples/octaneWeb2/debug_logs/*.log 2>/dev/null | wc -l) files"
```

### Recent activity
```bash
echo "=== RECENT LOGS ===" && \
tail -20 /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log && \
echo "=== ERROR COUNT ===" && \
grep -c ERROR /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
```

## Remember

✅ **Always check logs first** - Don't ask user for console output  
✅ **Check after every change** - Catch errors immediately  
✅ **Read stack traces** - They show exact error locations  
✅ **Watch for patterns** - Similar errors indicate systemic issues  
✅ **Only ask user for UX verification** - Not for debugging info  

## Browser Console Still Works

If you need user to check something specific:
- User can still open DevTools (F12)
- All console output appears in both browser AND log file
- `window.debugLogger` is available for manual inspection
