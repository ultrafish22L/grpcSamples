# OtoyaiWeb

A modern React-based node graph interface for the [play.otoy.ai](https://play.otoy.ai/) API. Create AI model workflows using an intuitive visual node graph editor inspired by octaneWebR and beta.otoy.ai.

## Features

- 🎨 **Visual Node Graph**: Drag-and-drop interface using React Flow
- 🤖 **AI Endpoint Nodes**: Dynamically loaded from play.otoy.ai API
- 🖼️ **Media Nodes**: Image and video input nodes with preview
- 📝 **Utility Nodes**: Text input and output nodes
- 🔗 **Node Connections**: Connect nodes to create AI workflows
- 📊 **Logger**: Best practices logging to local file for debugging
- 🎯 **Modern UI**: Clean, dark theme inspired by beta.otoy.ai

## Technology Stack

- **Frontend**: React 18 + TypeScript + Vite
- **Node Graph**: @xyflow/react (React Flow v12)
- **State Management**: Zustand
- **HTTP Client**: Axios
- **Backend**: Express + TypeScript
- **Styling**: CSS Modules

## Quick Start

### Prerequisites

- Node.js 18+ and npm

### Installation

1. Clone the repository and navigate to the project:
```bash
cd grpcSamples/otoyaiWeb
```

2. Install dependencies for both client and server:
```bash
npm run install:all
```

### Development

Start both client and server in development mode:
```bash
npm run dev
```

This will start:
- **Client**: http://localhost:60023 (React app, or port from $WORKER_1 env var, defaults to 5173)
- **Server**: http://localhost:3001 (Express logger server)

### Individual Commands

Start client only:
```bash
npm run dev:client
```

Start server only:
```bash
npm run dev:server
```

### Production Build

Build the client for production:
```bash
npm run build
```

Preview production build:
```bash
npm run preview
```

## Project Structure

```
otoyaiWeb/
├── client/                  # React frontend
│   ├── src/
│   │   ├── components/      # React components
│   │   │   ├── Layout/      # Toolbar, ContextMenu
│   │   │   ├── NodeGraph/   # ReactFlow graph component
│   │   │   └── Nodes/       # Custom node components
│   │   ├── services/        # API and logger services
│   │   ├── store/           # Zustand state management
│   │   ├── types/           # TypeScript type definitions
│   │   └── styles/          # Global CSS and variables
│   ├── package.json
│   └── vite.config.ts
├── server/                  # Express backend
│   ├── src/
│   │   └── index.ts         # Logger API endpoints
│   ├── logs/                # Application logs
│   └── package.json
├── README.md
└── package.json             # Root package for scripts
```

## Usage

### Adding Nodes

1. **Utility Nodes**: Click on "Text Input", "Image", or "Video" in the context menu
2. **AI Endpoint Nodes**: 
   - Expand a category (e.g., "text-to-image")
   - Click on an endpoint to add it to the graph

### Connecting Nodes

- Drag from an output handle (right side) to an input handle (left side)
- Connections appear as cyan lines

### Graph Controls

- **Pan**: Click and drag on the background
- **Zoom**: Mouse wheel or use the controls in the bottom-left
- **Select**: Click on nodes or edges
- **Delete**: Select and press Delete/Backspace
- **Clear Graph**: Click the trash icon in the toolbar
- **Reset**: Click the reset icon to clear everything and logs

### Node Types

#### AI Endpoint Node
- Represents an AI model from play.otoy.ai
- Shows vendor, title, description, and categories
- Can be connected to input and output nodes

#### Image Node
- Upload an image file or provide a URL
- Shows preview thumbnail
- Outputs image data to connected nodes

#### Video Node
- Upload a video file or provide a URL
- Shows video preview
- Outputs video data to connected nodes

#### Text Input Node
- Multi-line text input
- Use for prompts, descriptions, etc.
- Outputs text to connected nodes

## API Integration

### Fetching Endpoints

The app automatically fetches available AI endpoints from:
```
https://play.otoy.ai/api/endpoints
```

### Endpoint Categories

Endpoints are organized by category:
- text-to-image
- image-to-image
- text-to-video
- video-to-video
- audio-to-video
- image-to-video
- text-to-audio
- And more...

## Logger

The application includes a comprehensive logger that records:
- Application startup/shutdown
- API calls with timing
- Node additions and connections
- User interactions
- Errors with stack traces

### Logger API

Logs are stored in `server/logs/app.log`

**View logs:**
```bash
cat server/logs/app.log
```

**Clear logs:**
- Use the Reset button in the toolbar
- Or manually: `echo "" > server/logs/app.log`

### Logger Endpoints

- `POST /api/log` - Write log entry
- `POST /api/log/clear` - Clear logs
- `GET /api/log` - Retrieve all logs

## Development

### Adding New Node Types

1. Create a new component in `client/src/components/Nodes/`
2. Define the node data type in `client/src/types/nodes.ts`
3. Register the node type in `client/src/components/NodeGraph/NodeGraph.tsx`
4. Add creation logic in `client/src/components/Layout/ContextMenu.tsx`

### Customizing Styles

Global CSS variables are defined in `client/src/styles/variables.css`:
- Colors
- Spacing
- Typography
- Layout dimensions

## Future Enhancements

- [ ] Octane node integration
- [ ] Workflow execution (call API endpoints)
- [ ] Save/load workflows
- [ ] Export workflow as JSON
- [ ] Workflow templates
- [ ] Node search/filter
- [ ] Undo/Redo
- [ ] Real-time collaboration
- [ ] Batch processing

## License

[Your License Here]

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Support

For issues or questions, please open an issue on GitHub.

---

**Built with ❤️ using React and React Flow**
