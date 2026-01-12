# OctaneWebR Development Guide

## 🎯 Core Principles

1. **Minimize visual debug sessions** - Check logs and builds first
2. **Run builds to catch TypeScript errors** - Don't rely on IDE alone
3. **Test with real Octane only** - Never mock data
4. **Check console logs before debugging** - Most issues are obvious in logs

---

## 🔧 Development Workflow

### Starting Development

```bash
cd /workspace/project/grpcSamples/octaneWebR
npm run dev
```

Opens browser at http://localhost:43929 with:
- Vite dev server with HMR
- Embedded gRPC proxy
- Real-time TypeScript compilation

### Making Changes

**Before starting**:
1. Check browser console (F12) for existing errors
2. Verify TypeScript clean: `tsc --noEmit`
3. Understand existing code patterns in similar components

**During development**:
1. Save file → Vite HMR reloads → Check browser console
2. TypeScript errors show in terminal immediately
3. Console logs show API calls with 📤 ✅ ❌ markers

**Before committing**:
1. Run full build: `npm run build`
2. Check browser console: No errors
3. Test with Octane connected: Verify functionality
4. Update docs if needed

---

## 🐛 Debugging Strategy

### Step 1: Check Console Logs

**Always check browser console FIRST** (F12):

```
📤 [callApi] service=ApiItem method=name    ← API request
✅ [callApi] success result="teapot.obj"    ← API response
❌ [callApi] error: Connection refused       ← API error

🔄 [NodeGraph] Converting scene tree...      ← Scene processing
📌 [NodeGraph] Found 3 input pins            ← Pin detection
🔗 [NodeGraph] Created 5 edges               ← Edge creation
🎨 [Viewport] Rendering frame 42             ← Rendering
```

**Most issues are obvious from console output.**

### Step 2: Check TypeScript

```bash
# Quick type check (no build)
tsc --noEmit

# Full build with type checking
npm run build
```

TypeScript catches:
- Type mismatches
- Missing properties
- Invalid API calls
- Undefined variables

### Step 3: Check Health Endpoint

```bash
curl http://localhost:43929/api/health | python -m json.tool
```

Response shows:
- Server status
- Octane connection status
- Timestamp

### Step 4: Visual Debugging (Last Resort)

**Only use when**:
- Console logs don't reveal issue
- Complex state mutation bugs
- Async race conditions
- Browser-specific rendering bugs

**How to debug**:
1. Open browser DevTools (F12)
2. Sources tab → Find file → Set breakpoint
3. Trigger the code path
4. Inspect variables, call stack
5. Step through code

**Minimize time in debugger** - understand issue, add console.log, restart.

---

## 🧪 Testing Changes

### Manual Testing Checklist

After making changes, test these in order:

1. **TypeScript Build**:
   ```bash
   npm run build
   ```
   No errors = types are correct.

2. **Browser Console**:
   - Open http://localhost:43929
   - Press F12 → Console tab
   - No red errors = runtime clean

3. **UI Functionality**:
   - Click through menus
   - Select nodes in Scene Outliner
   - Edit parameters in Node Inspector
   - Drag nodes in Node Graph
   - Check viewport rendering

4. **API Integration** (if Octane connected):
   - Verify API calls succeed (✅ in console)
   - Check Octane updates (e.g., parameter changes reflected)
   - Test edge cases (empty scenes, missing nodes)

### Quick Test Script

```bash
#!/bin/bash
# Save as test.sh

echo "🔨 Building..."
npm run build || exit 1

echo "🔍 Type checking..."
tsc --noEmit || exit 1

echo "🏥 Health check..."
curl -s http://localhost:43929/api/health | grep -q "status" || exit 1

echo "✅ All checks passed!"
```

---

## 📝 Code Patterns

### Adding New Features

1. **Find similar existing code**:
   - Look at existing components
   - Check octaneWeb reference (vanilla JS version)
   - Follow established patterns

2. **Use TypeScript types**:
   ```typescript
   import type { OctaneNode } from '@/types/scene';
   
   const node: OctaneNode = {
     handle: '1000001',
     type: 'ApiMesh',
     name: 'teapot.obj'
   };
   ```

3. **Log extensively**:
   ```typescript
   console.log('📤 [Component] Action starting', { data });
   // ... do work ...
   console.log('✅ [Component] Action complete', { result });
   ```

4. **Handle errors gracefully**:
   ```typescript
   try {
     const result = await client.callApi('ApiItem', 'name', params);
     console.log('✅ Got name:', result);
   } catch (error) {
     console.error('❌ Failed to get name:', error);
     // Don't crash - show user-friendly error
   }
   ```

### Calling Octane APIs

```typescript
import { useOctane } from '@/hooks/useOctane';

const { client, isConnected } = useOctane();

// Make API call
const response = await client.callApi('ApiItem', 'name', {
  handle: nodeHandle,
  type: 16 // ApiItem type
});

// Access response (pattern varies by method)
const name = response.result; // Most methods
const list = response.list;   // getOwnedItems, etc.
```

### Adding Console Logs

Use emoji markers for easy filtering:

```typescript
// API calls
console.log('📤 [callApi] service=ApiItem method=name', params);
console.log('✅ [callApi] success', response);
console.error('❌ [callApi] error', error);

// Scene processing
console.log('🔄 [NodeGraph] Converting scene tree...');

// Pin/edge detection
console.log('📌 [NodeGraph] Found', count, 'input pins');
console.log('🔗 [NodeGraph] Created', count, 'edges');

// Rendering
console.log('🎨 [Viewport] Rendering frame', frameNumber);
```

---

## 🔍 Common Issues & Solutions

### Issue: TypeScript errors in terminal

**Check**:
```bash
tsc --noEmit
```

**Solutions**:
- Run `npm run proto:generate` to regenerate types
- Check `server/generated/` for updated definitions
- Fix type mismatches in code

### Issue: API calls failing

**Check console for**:
- 📤 Request sent?
- ❌ Error message?

**Solutions**:
- Verify Octane running: `curl http://localhost:43929/api/health`
- Check Octane LiveLink enabled (Help → LiveLink in Octane)
- Check parameters match API signature
- Check response structure (varies by method)

### Issue: UI not updating after API call

**Check**:
- Did API call succeed? (✅ in console)
- Is React state updated?
- Is component re-rendering?

**Solutions**:
- Add console.log before/after state updates
- Use React DevTools to inspect component state
- Verify useEffect dependencies array

### Issue: Edge clicks not working

**Status**: ✅ Fixed in commit 471bacc9

**Solution applied**:
- Added CSS `pointer-events: stroke` to `.react-flow__edge`
- Overrode parent blocking with `!important`

### Issue: Hot Module Replacement not working

**Solutions**:
- Check Vite terminal for errors
- Refresh browser (Ctrl+R)
- Restart dev server: `npm run dev`
- Clear browser cache

---

## 📦 Dependencies

### Core Stack
- React 18 - UI framework
- TypeScript 5.6 - Type safety
- Vite 6 - Build tool & dev server
- ReactFlow 11 - Node graph editor

### Adding New Dependencies

```bash
# Install dependency
npm install package-name

# Install dev dependency
npm install -D package-name

# Rebuild
npm run build
```

**Before adding**:
- Check if needed functionality already exists
- Prefer smaller, focused packages
- Avoid large UI frameworks (we use custom CSS)

---

## 🚀 Build & Deploy

### Development Build

```bash
npm run dev
```
Starts Vite dev server with HMR and embedded gRPC proxy.

### Production Build

```bash
npm run build
```
Outputs to `dist/` directory:
- Minified JavaScript
- Optimized CSS
- Static HTML

### Preview Production Build

```bash
npm run preview
```
Serves production build locally for testing.

### Regenerate Protobuf Types

```bash
npm run proto:generate
```
Regenerates TypeScript types from `server/proto/*.proto` files.

---

## 📚 Related Documentation

- **OVERVIEW.md** - Architecture and feature overview
- **QUICKSTART.md** - Setup and quick start guide
- **IMPLEMENTATION_PLAN.md** - Long-term roadmap
- **CODE_REVIEW.md** - Code quality guidelines

---

**Last Updated**: 2025-01-23  
**Version**: 0.9.7
