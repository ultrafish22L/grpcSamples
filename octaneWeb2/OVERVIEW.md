# OctaneWeb2 - Modern React Edition

## What is OctaneWeb2?

OctaneWeb2 is a modern React + TypeScript rewrite of the original octaneWeb application. It provides a web-based interface for controlling and monitoring OctaneRender through the Octane LiveLink gRPC API.

## Goal

Reproduce the UX and functionality of octaneWeb with a clean, maintainable React codebase using modern best practices.

## Key Features

- **Real-time Rendering**: View live renders from Octane through callback streaming
- **Scene Management**: Browse and interact with the Octane scene hierarchy
- **Node Inspection**: Inspect and modify node properties
- **Node Graph**: Visual node graph editor (in progress)
- **Camera Control**: Interactive viewport with camera synchronization

## Technology Stack

- **Frontend**: React 19 + TypeScript
- **State Management**: Zustand
- **Build Tool**: Vite
- **UI**: Custom CSS (matching Octane's dark theme)
- **Backend**: Python proxy server (shared with octaneWeb)

## Architecture

```
Browser (React App on port 42219)
  ↓ HTTP/JSON via /api proxy
Python Proxy Server (port 51023)
  ↓ gRPC
Octane LiveLink Service (port 51022)
```

## Project Structure

```
octaneWeb2/
├── src/
│   ├── api/              # Octane API client
│   ├── components/       # React components
│   │   ├── layout/       # MenuBar, StatusBar
│   │   └── panels/       # SceneOutliner, NodeInspector, NodeGraph
│   ├── constants/        # NodeType enums and constants
│   ├── core/             # Event system
│   ├── store/            # Zustand state stores
│   ├── styles/           # Global CSS
│   ├── types/            # TypeScript types
│   └── utils/            # Utility functions (Camera)
├── dist/                 # Build output (generated)
├── index.html            # Dev HTML template
├── package.json          # Dependencies
├── tsconfig.json         # TypeScript config
└── vite.config.ts        # Vite build config
```

## Current Status

### ✅ Completed

- React application structure
- TypeScript setup with strict typing
- Component architecture (MenuBar, StatusBar, SceneOutliner, NodeInspector, NodeGraph, RenderViewport)
- State management with Zustand
- Connection management
- Scene tree loading and display
- Basic node inspection
- Build system with Vite
- Successful compilation and serving

### 🚧 In Progress

- Camera synchronization
- Real-time callback rendering
- Node parameter editing
- Node graph visual editor

### 📋 Planned

- Material editor
- Render settings
- Performance monitoring
- Advanced viewport controls

## Comparison to Original octaneWeb

| Feature | octaneWeb | octaneWeb2 |
|---------|-----------|------------|
| Language | Vanilla JS | React + TypeScript |
| State | Manual DOM manipulation | Zustand stores |
| Build | None (raw files) | Vite bundler |
| Type Safety | None | Full TypeScript |
| Component Reuse | Copy-paste | React components |
| Testing | Manual | Testable architecture |
| Bundle Size | ~50KB | ~265KB (includes React) |

## Design Principles

1. **Type Safety**: Full TypeScript with strict mode
2. **Component Isolation**: Each panel is a self-contained React component
3. **State Management**: Centralized stores for connection, scene, and render state
4. **Event System**: Custom event bus for cross-component communication
5. **API Abstraction**: Single OctaneClient class handles all gRPC communication
6. **Modern Patterns**: Hooks, functional components, immutable state updates

## Next Steps

1. Implement real-time callback rendering with canvas display
2. Add camera synchronization from viewport
3. Complete node parameter editing UI
4. Add node graph visual connections
5. Optimize performance and bundle size
6. Add comprehensive error handling
7. Write unit tests for critical components
