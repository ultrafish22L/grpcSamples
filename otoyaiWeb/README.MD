# otoyaiWeb

**Visual node graph interface for OTOY.AI model endpoints**

Alternative UI for [play.otoy.ai](https://play.otoy.ai) that replaces form-based workflows with an Octane Render-inspired node graph editor.

---

## Overview

otoyaiWeb provides a professional node-based workflow editor for AI generation. Connect text prompts, images, videos, and AI models visually to create complex generation pipelines.

### Key Features

- **🎨 Visual Node Graph** - Drag-and-drop interface powered by React Flow
- **🤖 AI Model Nodes** - FLUX.1, Stable Diffusion, Kling Video, GPT-4o, and more
- **🎯 Type-Safe Connections** - Color-coded pins based on data types (string, int, float, image, video, audio)
- **👁️ Live Previews** - See outputs directly in nodes (planned)
- **🎬 Octane-Style UI** - Dark theme matching beta.otoy.ai aesthetic
- **📝 Smart Inspector** - Context-aware parameter editing in right panel
- **🔄 Hot Module Reload** - Instant updates during development

---

## Tech Stack

| Layer | Technology |
|-------|-----------|
| **Frontend** | React 18 + TypeScript + Vite |
| **Node Graph** | React Flow v12 (@xyflow/react) |
| **State Management** | Zustand |
| **Backend** | Node.js + Express |
| **Styling** | CSS Modules |
| **API** | OTOY.AI REST endpoints |
| **Logging** | Custom file-based logger |

---

## Project Structure

```
otoyaiWeb/
├── client/                          # React frontend (Vite)
│   ├── src/
│   │   ├── components/
│   │   │   ├── Layout/             # Toolbar, Inspector, NodeBar
│   │   │   └── Nodes/              # Node components + styling
│   │   ├── services/
│   │   │   ├── api.ts              # OTOY.AI API client
│   │   │   └── logger.ts           # File logging service
│   │   ├── types/
│   │   │   └── index.ts            # TypeScript definitions
│   │   ├── utils/
│   │   │   ├── connectionValidator.ts  # Pin type system
│   │   │   └── endpointSchema.ts       # AI model schemas
│   │   ├── App.tsx                 # Main React Flow app
│   │   └── main.tsx                # Entry point
│   ├── public/
│   └── package.json
│
├── server/                          # Express backend
│   ├── server.ts                   # API proxy + endpoint fetching
│   └── package.json
│
├── logs/                           # Runtime logs (git-ignored)
├── README.md                       # This file
├── quickstart.md                   # Installation & running
└── repro_prompt.md                 # AI assistant context loader
```

---

## Color-Coded Pin System

Visual type system inspired by Octane Render's node editor:

### Parameter Types (Inputs)
- **🟠 Orange** `#ffaa44` - String (prompts, text)
- **🟡 Yellow** `#ffdd44` - Integer (steps, seed, width, height)
- **🔵 Cyan** `#00ddff` - Float (guidance_scale, temperature, cfg)
- **🔴 Red** `#ff4444` - Boolean (flags, toggles)
- **🟣 Purple** `#cc44ff` - Enum (scheduler, sampler, style)

### Media Types (Same Color for Input & Output)
- **🟢 Green** `#44ff44` - Image
- **🟡 Magenta** `#ff44ff` - Video
- **🔵 Blue** `#4499ff` - Audio
- **🔷 Teal** `#44ffdd` - JSON
- **⚪ Gray** `#aaaaaa` - Any

**Key Design:** Media types use identical colors for inputs and outputs, making valid connections visually obvious. A green image output connects to a green image input.

---

## Node Types

### Utility Nodes
- **Text Input** - Editable text/prompt source with orange output
- **Image** - Image upload/URL input with green output
- **Video** - Video upload/URL input with magenta output

### AI Endpoint Nodes
Dynamically generated from play.otoy.ai API with:
- **Text-to-Image** - FLUX.1 [Dev], FLUX.1 [Schnell], AuraFlow, etc.
- **Image-to-Image** - FLUX.1 [Dev], style transfer models
- **Image-to-Video** - CogVideoX, Kling Video, etc.
- **LLM** - GPT-4o, Claude, Gemini (text generation)
- **Audio** - Text-to-speech, audio generation models

All AI nodes have color-coded inputs matching parameter types.

---

## Development Commands

```bash
# Start full stack (recommended)
npm run dev                # Client (Vite) + Server (Express)

# Individual services
npm run dev:client         # Frontend only → http://localhost:60023
npm run dev:server         # Backend only → http://localhost:3001

# Production
npm run build              # Build client for production
npm run build:client       # Build client only
```

See [quickstart.md](./quickstart.md) for detailed setup instructions.

---

## API Integration

The server acts as a proxy to OTOY.AI's REST API:

- **Endpoint Listing**: `GET http://localhost:3001/api/endpoints`
- **Model Execution**: `POST http://localhost:3001/api/execute` (planned)
- **Automatic Refresh**: Fetches latest models on startup

Original API: `https://play.otoy.ai/api/endpoints`

---

## Project & Workspace File Management

### Save & Load Files

**Save button** in the main toolbar **always opens a native file dialog** to save projects to your local file system:

- **Projects** (node graphs): Saved as `.otoyai` files
  - Contains: nodes, edges, connections, parameters, visible endpoints
  - File format: JSON
  - Example: `MyProject_1705823456789.otoyai`
  
- **Workspaces** (NodeBar configs): Saved as `.otoyai-workspace` files
  - Contains: visible endpoint configurations only
  - File format: JSON
  - Example: `workspace_1705823456789.otoyai-workspace`

### Where Files Are Stored

#### Browser Storage (localStorage)
- **Key**: `otoyai-storage`
- **Contents**: Recent projects and visible endpoint lists
- **Purpose**: Quick access to recent work
- **Location**: Browser's localStorage (not a real file)

#### File System (via Save button)
- **Location**: User's choice via native file dialog
- **Format**: JSON files with `.otoyai` or `.otoyai-workspace` extensions
- **Benefit**: Portable, version-controllable, shareable

### File System Access API

- **Modern browsers** (Chrome, Edge): Uses `showSaveFilePicker()` / `showOpenFilePicker()`
- **Fallback**: Automatic download/upload for older browsers
- **Security**: User explicitly chooses save location via OS dialog

### Quick Access

Even when saving to file system, projects are **also cached in localStorage** for the "Recent Projects" list visible when clicking the Load button's dropdown (planned feature).

---

## Logger System

Built-in file-based logging for development and debugging:

```typescript
import { logger } from './services/logger';

logger.info('Message', { data: value });
logger.error('Error occurred', error);
logger.debug('Debug info', { details });
```

- Logs saved to `server/logs/app.log`
- Cleared on app restart
- Accessible via toolbar "Reset" button

---

## Current Status

### ✅ Implemented
- Complete node graph system with React Flow
- Color-coded type-safe pin system (9 data types)
- Dynamic AI endpoint node generation from API
- Text, Image, Video utility nodes
- Left toolbar with Add/Clear/Reset buttons
- NodeBar (middle panel) with categorized AI models
- Node inspector (right panel) for parameter editing
- Real-time endpoint fetching from play.otoy.ai
- **Native file save/load dialogs** for projects (.otoyai files)
- **Workspace save/load** for NodeBar configurations (.otoyai-workspace files)
- localStorage caching for quick access to recent projects
- File-based logging system
- Production build pipeline
- CORS enabled for local development

### 🚧 In Progress
- Visual validation during connection drag
- Edge color matching pin types
- Actual API execution calls (POST to endpoints)
- Node result caching

### 📋 Planned
- Recent projects dropdown in Load button
- Export results (download images/videos from executed nodes)
- Octane node for octaneWebR integration
- Batch processing
- Custom node templates
- Undo/redo system
- Node search/filter

---

## UI Layout

```
┌──────┬─────────────┬───────────────────────────────────────┬─────────────┐
│      │             │                                       │             │
│  T   │   NodeBar   │        Node Graph Area               │  Inspector  │
│  O   │             │                                       │             │
│  O   │  - Add      │   (React Flow canvas)                │  Selected   │
│  L   │  - Clear    │                                       │  node       │
│  B   │  - Reset    │   Drag nodes, connect pins           │  parameters │
│  A   │             │                                       │             │
│  R   │  Categories │                                       │  Edit       │
│      │  - Text     │                                       │  values     │
│      │  - Image    │                                       │             │
│      │  - Video    │                                       │             │
│      │  - AI Models│                                       │             │
│      │             │                                       │             │
└──────┴─────────────┴───────────────────────────────────────┴─────────────┘
```

---

## License

MIT

---

## Quick Links

- **Installation**: [quickstart.md](./quickstart.md)
- **AI Context Loader**: [repro_prompt.md](./repro_prompt.md)
- **OTOY.AI Playground**: https://play.otoy.ai
- **Beta UI Reference**: https://beta.otoy.ai
- **React Flow Docs**: https://reactflow.dev
