# OctaneWeb2 Testing Guide

## Quick Start

### Prerequisites
1. **Octane running** with LiveLink enabled (Help → LiveLink in Octane)
2. **Octane accessible** at `127.0.0.1:51022` (or `host.docker.internal:51022` in sandboxed environments)

### Start Servers

#### 1. Start Proxy Server (if not already running)
```bash
cd /workspace/grpcSamples/octaneProxy
python octane_proxy.py
```

You should see:
```
🚀 Octane Proxy Server starting...
✅ Connected to Octane at host.docker.internal:51022
🌐 Proxy server running on http://0.0.0.0:51023
```

#### 2. Start React App (if not already running)
```bash
cd /workspace/grpcSamples/octaneWeb2
npm run dev
```

You should see:
```
VITE v7.2.0  ready in XXms
➜  Local:   http://localhost:42222/
```

Note: Port might vary (42221, 42222, etc.) - use the one Vite shows.

### Test in Browser

1. **Open**: http://localhost:42222/ (or the port Vite assigned)

2. **Open Browser Console** (F12) to see logs

3. **Expected Sequence**:
   ```
   🔌 Connecting to Octane at http://localhost:51023...
   ✅ Connected to Octane!
   📡 Service call: ApiProjectManager/rootNodeGraph
   ✅ Service result: ApiProjectManager/rootNodeGraph {...}
   📡 Service call: ApiItem/isGraph
   ✅ Service result: ApiItem/isGraph {...}
   📡 Service call: ApiNodeGraph/getOwnedItems
   ✅ Service result: ApiNodeGraph/getOwnedItems {...}
   📦 Found X items in graph
   ✅ Scene sync complete: [...]
   ```

## What to Look For

### ✅ Success Indicators

#### Status Bar (Bottom)
- **LED**: Should be **GREEN** (connected)
- **Text**: "Connected to http://localhost:51023"
- **FPS**: Should show current framerate

#### Scene Outliner (Left Panel)
- Should show **real scene nodes** from your Octane scene
- Node names match what's in your Octane project
- Tree structure reflects actual scene hierarchy
- Click **Refresh** button (↻) to reload scene

#### Node Inspector (Right Panel)
- Shows: "Select a node to inspect" initially
- **Click a node** in Scene Outliner
- Should show: Node name at top, "Loading parameters..."
- Then either shows parameters or "No parameters available"

#### Node Graph (Center)
- Shows empty canvas with grid (no mock nodes)
- Ready for real node graph data (next phase)

### ❌ Failure Indicators

#### Connection Failed
- LED stays **YELLOW** or turns **RED**
- Status bar: "Connecting..." or "Disconnected"
- Scene Outliner: "Connect to Octane to load scene"
- **Check**: Is proxy server running? Is Octane running with LiveLink enabled?

#### Scene Loading Failed
- LED is green but Scene Outliner shows "No scene data"
- Console shows: `❌ Service call failed: ...`
- **Check console** for specific error messages
- **Common causes**:
  - Octane not running
  - LiveLink service not enabled
  - Proxy can't reach Octane (network issues)
  - Wrong port configuration

#### No Nodes Appear
- LED green, no error messages, but tree is empty
- Could mean: Empty Octane scene (which is valid)
- Try: Open a scene in Octane with objects, then refresh in browser

## Console Log Guide

### Normal Flow
```
🔌 Connecting to Octane at http://localhost:51023...
✅ Connected to Octane!
🔄 Starting scene sync...
📡 Service call: ApiProjectManager/rootNodeGraph { handle: undefined, params: undefined }
✅ Service result: ApiProjectManager/rootNodeGraph { result: { handle: 1234 } }
📡 Service call: ApiItem/isGraph { handle: 1234, params: undefined }
✅ Service result: ApiItem/isGraph { result: true }
📡 Service call: ApiNodeGraph/getOwnedItems { handle: 1234, params: undefined }
✅ Service result: ApiNodeGraph/getOwnedItems { list: { handle: 5678 } }
📡 Service call: ApiItemArray/size { handle: 5678, params: undefined }
✅ Service result: ApiItemArray/size { result: 10 }
📦 Found 10 items in graph
[... more API calls for each item ...]
✅ Scene sync complete: [array of nodes]
```

### Error Flow
```
🔌 Connecting to Octane at http://localhost:51023...
❌ Connection failed: Failed to fetch
```
or
```
✅ Connected to Octane!
🔄 Starting scene sync...
📡 Service call: ApiProjectManager/rootNodeGraph { handle: undefined, params: undefined }
❌ Service call failed: ApiProjectManager/rootNodeGraph HTTP 500: Internal Server Error
❌ Scene sync failed: Error: Failed ApiProjectManager/rootNodeGraph
```

## Interactive Testing

### Test 1: Scene Loading
1. Open browser to React app
2. Wait 2-3 seconds for auto-connect
3. **Verify**: Scene Outliner shows nodes
4. **Verify**: Console shows successful API calls
5. **Verify**: Status LED is green

### Test 2: Scene Refresh
1. Make changes in Octane (add/remove objects)
2. Click **Refresh** button (↻) in Scene Outliner header
3. **Verify**: Scene reloads with updated content
4. **Verify**: Console shows new API call sequence

### Test 3: Node Selection
1. Click a node in Scene Outliner
2. **Verify**: Node gets highlighted (blue background)
3. **Verify**: Node Inspector shows node name at top
4. **Verify**: Console shows: `Node info: { ... }` and `Node parameters: []`

### Test 4: Tree Expand/Collapse
1. Click expand arrow (▶) next to a node with children
2. **Verify**: Arrow changes to ▼ and children appear
3. Click again to collapse
4. **Verify**: Arrow changes to ▶ and children hide

### Test 5: Search
1. Type in search box at top of Scene Outliner
2. **Verify**: Tree filters to matching nodes only
3. Clear search
4. **Verify**: Full tree reappears

## Troubleshooting

### Problem: "Module not found" error in console
**Solution**: 
```bash
cd /workspace/grpcSamples/octaneWeb2
npm install
npm run dev
```

### Problem: Proxy connection refused
**Check**:
```bash
curl http://localhost:51023/health
```

Should return: `{"status": "ok", "connected": true}`

If not, restart proxy:
```bash
cd /workspace/grpcSamples/octaneProxy
python octane_proxy.py
```

### Problem: Octane connection failed
**Check in Octane**:
1. Help → LiveLink
2. Verify "Enable LiveLink" is checked
3. Verify port is 51022
4. Try restarting Octane's LiveLink service

### Problem: CORS errors in console
**This is normal** if you see them briefly during connection. The proxy handles CORS.

If they persist, check proxy is running and accessible.

### Problem: "Port already in use"
Vite will automatically try next port. Just use the port it shows in console.

## Next Steps After Successful Testing

Once you confirm:
- ✅ Scene loads from Octane
- ✅ Nodes appear in tree
- ✅ Selection works
- ✅ No console errors

We can proceed with:
1. **Node Parameters**: Full parameter loading based on node type
2. **Node Graph**: Load and display actual node graph from Octane
3. **Render Viewport**: Real-time rendering with callback streaming
4. **Camera Sync**: Mouse drag to update Octane camera
5. **Event System**: Complete cross-component communication

## Support

If you encounter issues:
1. **Check**: `IMPLEMENTATION_STATUS.md` for architecture details
2. **Review**: Browser console logs (look for ❌ emojis)
3. **Verify**: Proxy logs in terminal
4. **Check**: Octane LiveLink is enabled
5. **Report**: Specific error messages from console

## Port Reference

| Service | Port | URL |
|---------|------|-----|
| Octane LiveLink | 51022 | - |
| Proxy Server | 51023 | http://localhost:51023 |
| React App (Vite) | 42222* | http://localhost:42222 |

*Port may vary - use whatever Vite assigns

## API Endpoints Being Used

### Proxy Health Check
```bash
curl http://localhost:51023/health
```

### Scene Loading (automatic)
- `POST /ApiProjectManager/rootNodeGraph`
- `POST /ApiItem/isGraph`
- `POST /ApiNodeGraph/getOwnedItems`
- `POST /ApiItemArray/size`
- `POST /ApiItemArray/get`

### Camera (not yet used)
- `POST /LiveLink/GetCamera`
- `POST /LiveLink/SetCamera`
- `POST /LiveLink/SetCameraPosition`
- `POST /LiveLink/SetCameraTarget`

All endpoints accept JSON body with `handle` and optional parameters.
