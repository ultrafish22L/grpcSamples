# OtoyaiWeb - Development Plan

## Overview
OtoyaiWeb is a modern React-based node graph UI for the play.otoy.ai API, providing an alternative interface for creating AI model workflows using a visual node graph editor similar to octaneWebR.

## Technology Stack

### Frontend
- **React 18** with TypeScript for type safety
- **@xyflow/react** (React Flow v12) for node graph visualization
- **Vite** for fast development and optimized builds
- **Axios** for HTTP API calls to play.otoy.ai
- **Zustand** for lightweight state management
- **CSS Modules** for component-scoped styling

### Backend
- **Express** for local file operations (logging)
- **Node.js** with TypeScript
- **CORS** enabled for local development

## UI Layout Design

Inspired by https://beta.otoy.ai/:

```
+---------------+------------------+----------------------------------------+
|               |                  |                                        |
|   Toolbar     |  Context Menu    |        Node Graph Area                 |
|   (Left)      |  (Categories)    |        (React Flow Canvas)             |
|               |                  |                                        |
|   - Add Node  |  - AI Models     |  [Node] ---> [Node] ---> [Node]       |
|   - Settings  |  - Textures      |    |                          |         |
|   - Execute   |  - Videos        |    v                          v         |
|   - Clear     |  - Utilities     |  [Node]                    [Node]      |
|   - Reset     |                  |                                        |
|               |                  |                                        |
+---------------+------------------+----------------------------------------+
```

## Node Types

### 1. AI Endpoint Nodes
- Dynamically generated from play.otoy.ai/api/endpoints
- Categorized by type (text-to-image, image-to-image, etc.)
- Input handles for parameters
- Output handles for results
- Display: vendor, title, description

### 2. Image/Texture Nodes
- File upload or URL input
- Preview thumbnail
- Output handle to connect to AI nodes

### 3. Video Nodes
- File upload or URL input
- Video preview/thumbnail
- Output handle to connect to AI nodes

### 4. Utility Nodes
- Text Input: For prompts
- Number Input: For parameters
- JSON Input: For structured data
- Output Display: Show results

## API Integration

### Endpoints
- `GET https://play.otoy.ai/api/endpoints` - Fetch available AI models

### Endpoint Data Structure
```typescript
interface Endpoint {
  _id: string;
  endpoint_id: string;
  category: string[];
  vendor: string;
  model_path: string;
  title: string;
  description: string;
}
```

### Categories (from API)
- text-to-image, image-to-image, text-to-video, video-to-video
- audio-to-video, image-to-video, text-to-audio, video-to-audio
- text-to-speech, image-to-3d, vision, llm
- upscale, removal, edit

## State Management (Zustand)

```typescript
interface AppState {
  endpoints: Endpoint[];
  loadingEndpoints: boolean;
  nodes: Node[];
  edges: Edge[];
  selectedCategory: string | null;
  showSettings: boolean;
  fetchEndpoints: () => Promise<void>;
  addNode: (type: string, data: any) => void;
  removeNode: (id: string) => void;
  updateNode: (id: string, data: any) => void;
  addEdge: (edge: Edge) => void;
  removeEdge: (id: string) => void;
}
```

## Logger Service

### Requirements
- Log application events, errors, and user actions
- Save to local file: `server/logs/app.log`
- Clear log file on hard reset
- Timestamp each entry with severity levels: INFO, WARN, ERROR, DEBUG

### Server Endpoints
```
POST /api/log - Write log entry
POST /api/log/clear - Clear log file
GET /api/log - Retrieve logs
```

## Project Structure

```
otoyaiWeb/
├── client/
│   ├── public/
│   ├── src/
│   │   ├── components/
│   │   │   ├── Layout/
│   │   │   ├── NodeGraph/
│   │   │   └── Nodes/
│   │   ├── services/
│   │   ├── store/
│   │   ├── types/
│   │   ├── utils/
│   │   └── styles/
│   ├── package.json
│   ├── tsconfig.json
│   └── vite.config.ts
├── server/
│   ├── src/
│   ├── logs/
│   ├── package.json
│   └── tsconfig.json
├── README.md
└── PLAN.md
```

## Color Scheme (from beta.otoy.ai)
- Background: Dark theme (#1a1a1a, #2a2a2a)
- Primary: Cyan/Blue accent (#00d4ff)
- Text: Light gray (#e0e0e0)
- Borders: Subtle gray (#3a3a3a)

## Success Criteria
1. Fetch and display endpoints from play.otoy.ai
2. Create and connect nodes in graph
3. Logger captures all important events
4. UI matches beta.otoy.ai aesthetic
5. Clean, maintainable code
