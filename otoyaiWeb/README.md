# OtoyaiWeb

**Node-based visual workflow editor for OTOY.AI**

Alternative UI for [play.otoy.ai](https://play.otoy.ai) featuring an Octane Render-inspired node graph interface. Build complex AI generation pipelines by visually connecting prompts, images, videos, and AI models.

![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![React](https://img.shields.io/badge/react-18.3-61dafb)
![TypeScript](https://img.shields.io/badge/typescript-5.6-3178c6)

---

## 🚀 Quick Start

```bash
# Clone and install
cd grpcSamples/otoyaiWeb
npm install

# Start development servers (client + backend)
npm run dev

# Open browser
http://localhost:60023
```

See [QUICKSTART.MD](./QUICKSTART.MD) for detailed setup instructions.

---

## ✨ Features

### Node Graph Interface
- **Visual Workflow Editor** - Drag-and-drop node graph powered by React Flow
- **Type-Safe Connections** - Color-coded pins prevent invalid connections
- **Multi-Output Nodes** - Image/Video nodes support multiple outputs per node
- **Smart Edge Routing** - Animated, color-matched connection lines
- **Context Menus** - Right-click nodes for quick actions (delete, disconnect, etc.)

### Node Types
- **📝 Text Input** - Editable prompts and parameters
- **🖼️ Image** - Upload multiple images or provide URLs
- **🎬 Video** - Upload multiple videos or provide URLs
- **🤖 AI Endpoints** - 1,137+ models from play.otoy.ai
  - Text-to-Image (FLUX.1, Stable Diffusion, Bria, etc.)
  - Image-to-Image (style transfer, upscaling, editing)
  - Image-to-Video (Kling, CogVideoX, Runway, etc.)
  - Text-to-Video (generative video models)
  - LLM (GPT-4o, Claude, Gemini)
  - Audio (text-to-speech, music generation)

### UI Components
- **Left Toolbar** - Quick actions (new, save, load, reset)
- **Node Palette** - Categorized model browser with token cost display
- **Node Inspector** - Parameter editor for selected nodes
- **Minimap** - Bird's-eye view of large graphs

### Smart Features
- **Connected Input Display** - Shows source node values in inspector
- **Token Cost Display** - See estimated costs before adding nodes
- **Project Save/Load** - Native file dialogs for .otoyai projects
- **Workspace Management** - Save/load custom node palette configurations
- **File Logger** - Runtime debugging with local log files

---

## 🎨 Color-Coded Type System

Inspired by Octane Render's node editor, pins are color-coded by data type:

| Type | Color | Hex | Use Case |
|------|-------|-----|----------|
| **String** | 🟠 Orange | `#ffaa44` | Prompts, text parameters |
| **Integer** | 🟡 Yellow | `#ffdd44` | Steps, seed, dimensions |
| **Float** | 🔵 Cyan | `#00ddff` | Guidance scale, CFG, temperature |
| **Boolean** | 🔴 Red | `#ff4444` | Enable/disable flags |
| **Enum** | 🟣 Purple | `#cc44ff` | Dropdown selections (scheduler, style) |
| **Image** | 🟢 Green | `#44ff44` | Image data (input & output) |
| **Video** | 💗 Magenta | `#ff44ff` | Video data (input & output) |
| **Audio** | 🔷 Blue | `#4499ff` | Audio data (input & output) |
| **JSON** | 🐚 Teal | `#44ffdd` | Structured data |
| **Any** | ⚪ Gray | `#aaaaaa` | Accepts any type |

**Design Principle:** Media types (image/video/audio) use **identical colors** for inputs and outputs, making valid connections visually obvious.

---

## 🏗️ Architecture

```
otoyaiWeb/
├── client/                    # React frontend (Vite)
│   ├── src/
│   │   ├── components/
│   │   │   ├── Layout/       # UI layout (Toolbar, NodeBar, Inspector, Minimap)
│   │   │   └── Nodes/        # Node components (Text, Image, Video, AI)
│   │   ├── services/
│   │   │   ├── api.ts        # OTOY.AI API client
│   │   │   └── logger.ts     # File-based logging
│   │   ├── types/
│   │   │   └── index.ts      # TypeScript definitions
│   │   ├── utils/
│   │   │   ├── connectionValidator.ts  # Pin type validation
│   │   │   ├── endpointCosts.ts        # Token cost database
│   │   │   └── endpointSchema.ts       # AI model schemas
│   │   ├── App.tsx           # Main React Flow app
│   │   └── main.tsx          # Entry point
│   └── package.json
│
├── server/                    # Express backend
│   ├── src/
│   │   └── index.ts          # CORS proxy for play.otoy.ai
│   └── package.json
│
├── README.md                  # This file
├── QUICKSTART.MD             # Setup guide
├── FEATURES.md               # Detailed feature documentation
└── ARCHITECTURE.md           # Technical deep dive
```

See [ARCHITECTURE.md](./ARCHITECTURE.md) for detailed technical documentation.

---

## 🛠️ Tech Stack

| Layer | Technology | Purpose |
|-------|-----------|---------|
| **Frontend** | React 18 + TypeScript | UI framework |
| **Build Tool** | Vite 5 | Fast dev server & bundler |
| **Node Graph** | React Flow v12 | Node editor library |
| **State** | Zustand | Global state management |
| **Backend** | Node.js + Express | API proxy server |
| **Styling** | CSS Modules | Component-scoped styles |
| **HTTP Client** | Axios | API requests |
| **Logger** | Custom | File-based debug logging |

---

## 📦 Project & Workspace Files

### File Types

- **`.otoyai`** - Complete project files
  - Nodes, edges, parameters, connections
  - Visible endpoints configuration
  - Load with "Load Project" button

- **`.otoyai-workspace`** - Node palette configurations
  - Visible endpoint lists only (no graph data)
  - Load with "Load Workspace" button in Node Palette

### Storage Options

1. **File System** (Recommended)
   - Uses native save/load dialogs
   - Portable, shareable, version-controllable
   - Modern browsers use File System Access API
   - Fallback to download/upload for older browsers

2. **Browser Storage** (Auto-cached)
   - Recent projects saved to localStorage
   - Quick access for resuming work
   - Key: `otoyai-storage`

---

## 🎯 Development Commands

```bash
# Full stack development (recommended)
npm run dev                    # Start client + server concurrently

# Individual services
npm run dev:client             # Frontend only → localhost:60023
npm run dev:server             # Backend only → localhost:3001

# Production build
npm run build                  # Build client for production
npm run build:client           # Client build only

# Client-specific
cd client
npm run dev                    # Vite dev server
npm run build                  # Production build
npm run preview                # Preview production build
```

---

## 📚 Documentation

- **[QUICKSTART.MD](./QUICKSTART.MD)** - Installation and setup
- **[FEATURES.md](./FEATURES.md)** - Comprehensive feature documentation
- **[ARCHITECTURE.md](./ARCHITECTURE.md)** - Technical architecture guide
- **[React Flow Docs](https://reactflow.dev)** - Node graph library
- **[OTOY.AI Playground](https://play.otoy.ai)** - Original API interface

---

## 🔮 Roadmap

### ✅ Completed
- [x] Node graph core (React Flow integration)
- [x] Type-safe pin system with color coding
- [x] Dynamic AI endpoint loading (1,137+ models)
- [x] Multi-output media nodes
- [x] Project save/load with native dialogs
- [x] Workspace save/load for node palette
- [x] Connected input display in inspector
- [x] Token cost display in node palette
- [x] Edge reconnection system
- [x] Context menus for nodes
- [x] Minimap navigation
- [x] File-based logging

### 🚧 In Progress
- [ ] AI endpoint execution system
- [ ] Parameter packaging for all endpoint types
- [ ] Live result previews in nodes

### 📋 Planned
- [ ] Export results (download generated images/videos)
- [ ] Node result caching
- [ ] Batch processing workflows
- [ ] Undo/redo system
- [ ] Node search/filter
- [ ] Custom node templates
- [ ] Octane node (octaneWebR integration)
- [ ] Cloud project storage

---

## 🤝 Contributing

This project is part of the grpcSamples repository. Contributions welcome!

---

## 📄 License

MIT

---

## 🔗 Links

- **OTOY.AI API**: https://play.otoy.ai/api/endpoints
- **Beta UI Reference**: https://beta.otoy.ai
- **React Flow**: https://reactflow.dev
- **Vite**: https://vitejs.dev
