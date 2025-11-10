# OctaneWeb2 - Quick Start Guide

Get OctaneWeb2 running locally in 5 minutes.

## Prerequisites

- **Node.js** v20+ and npm
- **Python 3.8+**
- **OctaneRender Standalone** with LiveLink enabled (for full functionality)
- Modern web browser (Chrome 90+, Firefox 88+, Edge 90+)

## Installation

```bash
# Navigate to project
cd octaneWeb2

# Install dependencies
npm install
```

## Running the Application

### Development Mode (with hot reload)

**Terminal 1** - Start Python Proxy:
```bash
cd ../octaneProxy
python octane_proxy.py
```

**Terminal 2** - Start Vite Dev Server:
```bash
cd ../octaneWeb2
npm run dev
```

**Terminal 3** - Start Octane:
- Launch OctaneRender Standalone
- Enable LiveLink: **Help → LiveLink** ✓
- Verify port is **51022**

**Browser**:
- Open `http://localhost:42219` (or port shown in terminal)
- Click **Connect** button (top-right)
- Should show green "Connected" indicator

### Production Mode (static build)

```bash
# Build app
npm run build

# Serve dist folder
cd dist
python3 -m http.server 8080 --bind 0.0.0.0
```

Access at `http://localhost:8080`

## Verification

After connecting, you should see:

1. ✅ **MenuBar** (top): Green "Connected" indicator
2. ✅ **StatusBar** (bottom): "Octane: Connected"
3. ✅ **Scene Outliner** (left): Scene hierarchy loaded
4. ✅ **Console** (F12): No errors, connection logs visible

## Troubleshooting

### Connection Fails

**Check these in order**:
1. Is Python proxy running? Test: `curl http://127.0.0.1:51023/health`
2. Is Octane running with LiveLink enabled? (Help → LiveLink)
3. Check browser console (F12) for errors
4. Check terminal output for Python proxy errors

### Port Already in Use

```bash
# Kill process on port 42219
lsof -ti:42219 | xargs kill   # Mac/Linux
netstat -ano | findstr :42219  # Windows (then taskkill /PID <PID>)

# Or change port in vite.config.ts
```

### Build Errors

```bash
# Clean reinstall
rm -rf node_modules package-lock.json
npm install
npm run build
```

### CORS Errors

Always access via Vite dev server (`http://localhost:42219`), not Python proxy directly (`http://localhost:51023`).

## Docker/Sandbox Environments

If running in Docker (e.g., OpenHands agent):

1. Modify Python proxy to use `host.docker.internal`:
   ```python
   # In octaneProxy/octane_proxy.py
   OCTANE_ADDRESS = 'host.docker.internal:51022'
   ```

2. Build and serve (dev server may not be accessible):
   ```bash
   npm run build
   cd dist
   python3 -m http.server 48537 --bind 0.0.0.0
   ```

See [NETWORKING.md](NETWORKING.md) for details.

## Project Structure

```
octaneWeb2/
├── src/
│   ├── api/              # OctaneClient - gRPC API wrapper
│   ├── components/       # React UI components
│   │   ├── layout/       # MenuBar, StatusBar
│   │   └── panels/       # SceneOutliner, NodeInspector, NodeGraph, RenderViewport
│   ├── constants/        # NodeType enums
│   ├── store/            # Zustand state stores
│   ├── utils/            # Camera, helpers
│   └── styles/           # Global CSS
├── dist/                 # Build output (npm run build)
├── package.json          # Dependencies
├── tsconfig.json         # TypeScript config
└── vite.config.ts        # Vite config with API proxy
```

## Development Workflow

1. **Edit Code**: Make changes in `src/`
2. **Hot Reload**: Vite automatically reloads browser
3. **Check Types**: TypeScript errors show in terminal
4. **Test**: Interact with UI, check console (F12)

## Common Commands

```bash
npm run dev        # Start dev server
npm run build      # Build for production
npm run preview    # Preview production build
```

## Next Steps

- Read [OVERVIEW.md](OVERVIEW.md) - Project goals and architecture
- Read [NETWORKING.md](NETWORKING.md) - Detailed networking setup
- Read [REPRO.md](REPRO.md) - Context for AI agents
