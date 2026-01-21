# Quick Start Guide - otoyaiWeb

Get up and running with the otoyaiWeb node graph interface in under 5 minutes.

---

## Prerequisites

- **Node.js** v18 or higher ([Download](https://nodejs.org/))
- **npm** (comes with Node.js)
- Modern web browser (Chrome, Firefox, Safari, Edge)

---

## Installation

### 1. Navigate to the project

```bash
cd grpcSamples/otoyaiWeb
```

### 2. Install dependencies

Install all dependencies for both client and server:

```bash
npm install
```

This runs `npm install` in the root directory, and automatically installs dependencies in both `client/` and `server/` directories via the postinstall script.

**Note**: If you get module errors later (like "Cannot find package 'axios'"), you may need to manually install in subdirectories:
```bash
cd client && npm install
cd ../server && npm install
```

See [TROUBLESHOOTING.md](./TROUBLESHOOTING.md) for more help.

---

## Running the App

### Development Mode (Recommended)

Start both the client and server concurrently:

```bash
npm run dev
```

This will:
- Start the **Express server** on `http://localhost:3001`
- Start the **Vite dev server** on `http://localhost:60023` (or `$WORKER_1` env var)
- Enable hot module reloading
- Fetch AI endpoints from play.otoy.ai on startup

**Access the app:** Open your browser to `http://localhost:60023`

### Alternative: Run Individually

**Client only:**
```bash
npm run dev:client
```
Runs on port `60023` (or `$WORKER_1` env var, defaults to `5173` if not set)

**Server only:**
```bash
npm run dev:server
```
Runs on port `3001`

---

## Environment Variables

The app uses these environment variables (optional):

| Variable | Default | Description |
|----------|---------|-------------|
| `WORKER_1` | `5173` | Client port (Vite dev server) |
| `WORKER_2` | - | Second worker port (unused) |
| `PORT` | `3001` | Server port (Express logger) |

Set them in your shell:
```bash
export WORKER_1=60023
export PORT=3001
npm run dev
```

Or prepend to the command:
```bash
WORKER_1=60023 npm run dev
```

---

## Production Build

### Build the client

```bash
npm run build
```

This runs `vite build` in the `client/` directory. Output goes to `client/dist/`.

### Preview the build

```bash
npm run preview
```

Serves the production build locally for testing.

---

## Usage

### Adding Nodes

1. **Toolbar (Left Panel)**
   - Click "Add" to open the NodeBar
   - Or click "Clear" to remove all nodes
   - Or click "Reset" to clear graph and logs

2. **NodeBar (Middle Panel)**
   - **Utility Nodes**: Click "Text Input", "Image", or "Video"
   - **AI Models**: Expand categories like "text-to-image", then click a model

3. **AI Endpoint Nodes**
   - Categories auto-populate from `https://play.otoy.ai/api/endpoints`
   - Examples: FLUX.1 [Dev], Kling Video, GPT-4o, CogVideoX

### Connecting Nodes

1. **Drag from output** (right side of node) to **input** (left side of node)
2. **Match colors**: Green to green, orange to orange, etc.
3. **Invalid connections** prevented by type system (e.g., can't connect orange to green)

### Editing Parameters

1. **Click on a node** to select it
2. **Inspector panel (right side)** shows node parameters
3. **Edit values** directly in the inspector
4. Changes update the node in real-time

### Graph Controls

- **Pan**: Click and drag on background
- **Zoom**: Mouse wheel or zoom controls (bottom-left)
- **Select**: Click nodes or edges
- **Delete**: Select and press `Delete` or `Backspace`
- **Multi-select**: Hold `Shift` and click multiple nodes

---

## Troubleshooting

### Port Already in Use

If you see `EADDRINUSE` error:

**Option 1: Kill the process using the port**
```bash
# Find process on port 60023
lsof -ti:60023 | xargs kill -9

# Find process on port 3001
lsof -ti:3001 | xargs kill -9
```

**Option 2: Use a different port**
```bash
WORKER_1=8080 npm run dev
```

### Dependencies Not Installing

Clear npm cache and reinstall:
```bash
rm -rf node_modules client/node_modules server/node_modules
rm package-lock.json client/package-lock.json server/package-lock.json
npm install
```

### CORS Errors in Browser

Make sure:
1. Server is running (`npm run dev:server`)
2. Client `.env` has correct `VITE_API_BASE_URL`:
   ```
   VITE_API_BASE_URL=http://localhost:3001
   ```
3. Server has CORS enabled (already configured in `server/server.ts`)

### Endpoints Not Loading

Check:
1. Server logs show successful fetch from `https://play.otoy.ai/api/endpoints`
2. Network tab in browser DevTools shows `/api/endpoints` request succeeding
3. Internet connection is active

**Manual test:**
```bash
curl http://localhost:3001/api/endpoints
```

Should return JSON with AI model endpoints.

### Hot Reload Not Working

1. Stop the dev server (`Ctrl+C`)
2. Clear Vite cache:
   ```bash
   rm -rf client/node_modules/.vite
   ```
3. Restart:
   ```bash
   npm run dev
   ```

---

## Logs

Logs are saved to `server/logs/app.log` (created on first run).

**View logs:**
```bash
cat server/logs/app.log
```

**Tail logs (live):**
```bash
tail -f server/logs/app.log
```

**Clear logs:**
- Use the "Reset" button in the toolbar
- Or manually: `rm server/logs/app.log`

---

## Next Steps

- **Read the [README.md](./README.md)** for architecture details
- **Check [repro_prompt.md](./repro_prompt.md)** for AI assistant context
- **Experiment** with connecting nodes and building workflows
- **Check the console** for runtime errors and debug info

---

## Common Workflows

### Example 1: Text-to-Image

1. Add "Text Input" node
2. Add "FLUX.1 [Dev]" AI node
3. Connect text output (orange) to prompt input (orange)
4. Edit prompt in Text Input or Inspector
5. (Future: Click "Run" to execute)

### Example 2: Image-to-Video

1. Add "Image" node
2. Upload an image
3. Add "Kling Video" AI node
4. Connect image output (green) to start_image input (green)
5. Add "Text Input" for prompt
6. Connect text (orange) to prompt (orange)

### Example 3: Multi-Model Pipeline

1. Add "Text Input" for prompt
2. Add "FLUX.1 [Dev]" (text-to-image)
3. Connect prompt to FLUX
4. Add "CogVideoX" (image-to-video)
5. Connect FLUX image output (green) to CogVideoX image input (green)
6. (Future: Execute pipeline and get video result)

---

## Development Tips

### File Watching

Vite watches all files in `client/src/`. Changes auto-reload in browser.

### TypeScript Errors

Run type checking:
```bash
cd client
npm run type-check
```

### Building for Production

```bash
npm run build
cd client/dist
# Deploy these files to your hosting provider
```

### Adding New Nodes

See `client/src/components/Nodes/` for examples. All nodes inherit from React Flow's `NodeProps` type.

---

## Support

For issues:
1. **Check [TROUBLESHOOTING.md](./TROUBLESHOOTING.md)** for common problems and solutions
2. Check logs: `server/logs/app.log`
3. Check browser console (F12 → Console tab)
4. Review `README.md` for architecture details
5. Check OTOY.AI API status: https://play.otoy.ai

---

**Happy node graphing! 🎨🤖**
