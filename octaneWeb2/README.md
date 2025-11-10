# OctaneWeb2 - Modern React Edition

A modern React + TypeScript rewrite of octaneWeb, providing a web-based interface for controlling OctaneRender through the LiveLink gRPC API.

## Quick Start

```bash
cd octaneWeb2
npm install
npm run dev
```

Open `http://localhost:42219` in your browser.

See [QUICKSTART.md](QUICKSTART.md) for detailed instructions.

## Documentation

- **[OVERVIEW.md](OVERVIEW.md)** - Project goals, architecture, and current status
- **[QUICKSTART.md](QUICKSTART.md)** - Installation and running instructions
- **[NETWORKING.md](NETWORKING.md)** - Network architecture, Docker setup, debugging
- **[REPRO.md](REPRO.md)** - Context for AI agents resuming development

## Project Goal

Reproduce octaneWeb's UX and functionality with a clean, maintainable React codebase using modern best practices.

## Technology Stack

- React 19 + TypeScript
- Vite (build tool)
- Zustand (state management)
- Custom CSS (OTOY dark theme)
- Python proxy server (shared with original octaneWeb)

## Current Status

✅ **Foundation Complete**: React app structure, TypeScript setup, build system  
✅ **UI Components**: MenuBar, StatusBar, SceneOutliner, NodeInspector, NodeGraph, RenderViewport  
✅ **API Client**: Complete gRPC client with connection management  
✅ **Scene Loading**: Sync and display scene hierarchy from Octane  
🚧 **In Progress**: Real-time rendering, camera sync, parameter editing

## Architecture

```
Browser (React on port 42219)
  ↓ HTTP/JSON via /api proxy
Python Proxy (port 51023)
  ↓ gRPC
Octane LiveLink (port 51022)
```

## Development

```bash
# Start Python proxy
cd ../octaneProxy
python octane_proxy.py

# Start Vite dev server
cd ../octaneWeb2
npm run dev

# Build for production
npm run build
```

## Project Structure

```
src/
├── api/              # Octane API client
├── components/       # React components
│   ├── layout/       # MenuBar, StatusBar
│   └── panels/       # SceneOutliner, NodeInspector, etc.
├── constants/        # NodeType enums
├── store/            # Zustand state stores
├── utils/            # Camera, helpers
└── styles/           # Global CSS
```

## Comparison to Original

| Feature | octaneWeb | octaneWeb2 |
|---------|-----------|------------|
| Language | Vanilla JS | React + TypeScript |
| State | Manual DOM | Zustand stores |
| Build | None | Vite |
| Type Safety | None | Full TypeScript |
| Lines of Code | ~4500 | ~3000 (target) |

## License

See repository root for license information.
