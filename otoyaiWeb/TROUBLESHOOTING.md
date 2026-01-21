# Troubleshooting Guide - otoyaiWeb

Common issues and solutions for running otoyaiWeb.

---

## Installation Issues

### "Cannot find package 'axios'" or similar module errors

**Problem**: Server or client missing dependencies after git pull.

**Solution**: Install all dependencies:

```bash
# From otoyaiWeb root directory
npm install

# This will automatically run postinstall and install:
# - Root dependencies (concurrently)
# - Client dependencies
# - Server dependencies

# Or manually install in each directory:
cd client && npm install
cd ../server && npm install
```

**Why this happens**: 
- `node_modules/` folders are git-ignored
- After pulling changes, you need to reinstall dependencies
- The root `npm install` now automatically installs all sub-dependencies

---

## Server Issues

### Port 3001 already in use

**Problem**: `EADDRINUSE: address already in use :::3001`

**Solution**:

```bash
# Windows (PowerShell)
Get-Process -Id (Get-NetTCPConnection -LocalPort 3001).OwningProcess | Stop-Process

# Windows (Command Prompt)
netstat -ano | findstr :3001
taskkill /PID <PID> /F

# Linux/Mac
lsof -ti:3001 | xargs kill -9
```

Or change the port:
```bash
# Windows
set PORT=5001 && npm run dev

# Linux/Mac
PORT=5001 npm run dev
```

---

## Client Issues

### Port 5173 or 60023 already in use

**Problem**: Vite dev server port conflict

**Solution**:

```bash
# Kill process on port
# Windows
netstat -ano | findstr :5173
taskkill /PID <PID> /F

# Linux/Mac
lsof -ti:5173 | xargs kill -9
```

Or change the port in `client/vite.config.ts`:
```typescript
export default defineConfig({
  server: {
    port: 8080, // Change to any available port
  }
})
```

---

## Build Issues

### TypeScript errors after pulling changes

**Problem**: Build fails with type errors

**Solution**:

```bash
# Clear all node_modules and reinstall
rm -rf node_modules client/node_modules server/node_modules
rm -f package-lock.json client/package-lock.json server/package-lock.json
npm install

# Or on Windows:
rmdir /s /q node_modules client\node_modules server\node_modules
del package-lock.json client\package-lock.json server\package-lock.json
npm install
```

### Vite cache issues

**Problem**: Hot reload not working, stale builds

**Solution**:

```bash
cd client
rm -rf node_modules/.vite
npm run dev

# Windows:
rmdir /s /q node_modules\.vite
npm run dev
```

---

## Runtime Issues

### Endpoints not loading

**Problem**: Node Palette shows no AI models

**Checklist**:
1. ✅ Server running? Check console for "Server running on http://localhost:3001"
2. ✅ Internet connected? API fetches from play.otoy.ai
3. ✅ CORS enabled? Check server logs
4. ✅ Proxy working? Test: `curl http://localhost:3001/otoy-api/endpoints`

**Solution**:
```bash
# Test server health
curl http://localhost:3001/health
# Should return: {"status":"ok"}

# Test endpoints proxy
curl http://localhost:3001/otoy-api/endpoints
# Should return JSON with endpoints array
```

### CORS errors in browser

**Problem**: "Access to fetch blocked by CORS policy"

**Solution**: Ensure both client and server are running:
```bash
npm run dev  # Starts both concurrently
```

Server automatically enables CORS for:
- `http://localhost:5173` (default Vite port)
- `http://localhost:60023` (WORKER_1 port)

---

## Development Issues

### Hot reload not working

**Problem**: Changes not reflecting in browser

**Solutions**:
1. Hard refresh: `Ctrl+Shift+R` (Windows/Linux) or `Cmd+Shift+R` (Mac)
2. Clear Vite cache: `rm -rf client/node_modules/.vite`
3. Restart dev server: `Ctrl+C` then `npm run dev`

### Node graph performance issues

**Problem**: Canvas lagging with many nodes

**Solutions**:
1. Reduce visible endpoints (save workspace with fewer models)
2. Use minimap for navigation instead of panning
3. Close node inspector when not needed
4. Disable animations in React Flow settings (future feature)

---

## Windows-Specific Issues

### Path errors with `cd` commands

**Problem**: Scripts fail with path errors on Windows

**Solution**: Ensure you're using a compatible terminal:
- ✅ PowerShell (recommended)
- ✅ Git Bash
- ✅ WSL (Linux subsystem)
- ❌ Old Command Prompt (may have issues)

### `concurrently` not found

**Problem**: `'concurrently' is not recognized...`

**Solution**:
```bash
npm install --save-dev concurrently
# Or reinstall root dependencies
npm install
```

---

## Logging and Debugging

### Check server logs

```bash
# View logs
cat server/logs/app.log

# Windows
type server\logs\app.log

# Tail logs (live)
tail -f server/logs/app.log

# Windows (PowerShell)
Get-Content server\logs\app.log -Wait
```

### Clear logs

```bash
# Use Reset button in UI
# Or manually:
rm server/logs/app.log

# Windows
del server\logs\app.log
```

### Enable verbose logging

Add to `server/src/index.ts`:
```typescript
// Add at top of file
console.log('Environment:', process.env);
console.log('Port:', PORT);
```

---

## Network Issues

### Testing API connectivity

```bash
# Test OTOY API directly
curl https://play.otoy.ai/api/endpoints

# Test through proxy
curl http://localhost:3001/otoy-api/endpoints

# Windows (PowerShell)
Invoke-WebRequest -Uri https://play.otoy.ai/api/endpoints
Invoke-WebRequest -Uri http://localhost:3001/otoy-api/endpoints
```

---

## File Access Issues (Save/Load)

### Native file dialogs not working

**Problem**: Save/Load buttons don't open dialogs

**Browser Support**:
- ✅ Chrome 86+ (File System Access API)
- ✅ Edge 86+
- ⚠️ Firefox (falls back to download/upload)
- ⚠️ Safari (falls back to download/upload)

**Fallback**: Files automatically download to default download folder.

### Permissions denied

**Problem**: Can't save to selected folder

**Solution**: Browser security - select a folder you have write access to, or use Downloads folder.

---

## Quick Diagnostic Commands

Run these to check your setup:

```bash
# Check Node.js version (should be 18+)
node --version

# Check npm version
npm --version

# Check if dependencies installed
ls client/node_modules/@xyflow/react  # Should exist
ls server/node_modules/axios           # Should exist

# Windows
dir client\node_modules\@xyflow\react
dir server\node_modules\axios

# Test TypeScript compilation
cd client && npx tsc --noEmit
cd ../server && npx tsc --noEmit

# Test build
npm run build
```

---

## Still Having Issues?

1. **Check the logs**: `server/logs/app.log`
2. **Browser console**: F12 → Console tab (check for errors)
3. **Network tab**: F12 → Network tab (check API requests)
4. **Clean install**: Delete all node_modules and reinstall
5. **Check documentation**: README.md, ARCHITECTURE.md, FEATURES.md

---

## Environment Variables

Default values (change if needed):

| Variable | Default | Purpose |
|----------|---------|---------|
| `PORT` | `3001` | Server port |
| `WORKER_1` | `5173` | Client port (Vite) |

Set in your shell:
```bash
# Windows (Command Prompt)
set PORT=5001
set WORKER_1=8080

# Windows (PowerShell)
$env:PORT=5001
$env:WORKER_1=8080

# Linux/Mac
export PORT=5001
export WORKER_1=8080
```

Or create `.env` files (future enhancement).

---

**Last Updated**: 2025-01-21
