# otoyaiWeb - AI Context Loader

**Copy this prompt into a new OpenHands chat to quickly resume development.**

---

## Project Context

You're working on **otoyaiWeb**, a React node graph UI for the play.otoy.ai API. It's an alternative interface inspired by Octane Render's node editor and beta.otoy.ai's UI.

**Location:** `/workspace/project/grpcSamples/otoyaiWeb/`

**Tech Stack:**
- React 18 + TypeScript + Vite (client)
- Express + TypeScript (server)
- React Flow v12 for node graph
- Zustand for state
- CSS Modules for styling

---

## Architecture

### Directory Structure
```
otoyaiWeb/
├── client/src/
│   ├── components/
│   │   ├── Layout/          # Toolbar, Inspector, NodeBar
│   │   └── Nodes/           # TextInputNode, ImageNode, VideoNode, AIEndpointNode
│   ├── services/
│   │   ├── api.ts           # Axios client for play.otoy.ai
│   │   └── logger.ts        # File logging
│   ├── utils/
│   │   ├── connectionValidator.ts    # Type system and connection rules
│   │   └── endpointSchema.ts         # AI model schemas (FLUX, Kling, etc.)
│   ├── types/index.ts       # TypeScript definitions
│   └── App.tsx              # Main React Flow app
├── server/server.ts         # Express proxy for OTOY.AI API
└── logs/app.log             # Runtime logs
```

### UI Layout
```
[Toolbar] [NodeBar] [React Flow Canvas] [Inspector]
 (left)    (middle)    (main area)       (right)
```

- **Toolbar**: Add/Clear/Reset buttons
- **NodeBar**: Categorized node list (utility + AI models)
- **Canvas**: React Flow graph with nodes and connections
- **Inspector**: Selected node's parameter editor

---

## Type System - Fine-Grained Pin Colors

**Key Design:** Each data type has its own distinct color. Media types (image, video, audio) use the **same color** for both inputs and outputs to make valid connections obvious.

### Parameter Types
| Type | Color | Hex | Use Case |
|------|-------|-----|----------|
| **string** | 🟠 Orange | `#ffaa44` | Prompts, text, descriptions |
| **integer** | 🟡 Yellow | `#ffdd44` | Steps, seed, width, height |
| **float** | 🔵 Cyan | `#00ddff` | guidance_scale, temperature, cfg |
| **boolean** | 🔴 Red | `#ff4444` | Flags, toggles |
| **enum** | 🟣 Purple | `#cc44ff` | Scheduler, sampler, style |

### Media Types (Same for Input & Output)
| Type | Color | Hex |
|------|-------|-----|
| **image** | 🟢 Green | `#44ff44` |
| **video** | 🟡 Magenta | `#ff44ff` |
| **audio** | 🔵 Blue | `#4499ff` |
| **json** | 🔷 Teal | `#44ffdd` |
| **any** | ⚪ Gray | `#aaaaaa` |

### Implementation Files
- **CSS**: `client/src/components/Nodes/nodes.module.css` (`.handleString`, `.handleInteger`, etc.)
- **Mapping**: `connectionValidator.ts` has `mapInputTypeToHandleType()` and `mapOutputTypeToHandleType()`
- **Validation**: `isValidConnection()` enforces type rules (int→float allowed, string→image forbidden)

---

## Node Types

### Utility Nodes
1. **TextInputNode** - Editable text input with orange string output
2. **ImageNode** - Image upload/URL with green image output
3. **VideoNode** - Video upload/URL with magenta video output

### AI Endpoint Nodes
Dynamically generated from `https://play.otoy.ai/api/endpoints`:
- **Text-to-Image**: FLUX.1 [Dev], FLUX.1 [Schnell], AuraFlow
- **Image-to-Video**: Kling Video, CogVideoX
- **LLM**: GPT-4o, Claude, Gemini
- **Audio**: Text-to-speech models

Each AI node has:
- **Inputs** (left side): Color-coded pins for each parameter (prompt, seed, guidance_scale, etc.)
- **Outputs** (right side): Color-coded pins for results (image, video, text, etc.)
- **Schema**: Defined in `endpointSchema.ts` with mappings like:
  ```typescript
  steps: { type: 'integer', default: 30, min: 1, max: 100 }
  guidance_scale: { type: 'float', default: 7.5, min: 0, max: 20 }
  prompt: { type: 'text', default: '' }
  ```

---

## Current Implementation Status

### ✅ Complete
- React Flow graph with pan/zoom/select
- Color-coded type-safe pin system (9 data types)
- Toolbar with Add/Clear/Reset buttons
- NodeBar with categorized node list
- Node Inspector for parameter editing
- Dynamic AI endpoint loading from play.otoy.ai
- File-based logging system
- CORS-enabled server proxy
- Production build pipeline
- TypeScript with strict type checking

### 🚧 In Progress
- Visual validation during connection drag (show valid targets)
- Edge colors matching pin types
- Actual API execution (POST to endpoints)
- Result caching

### 📋 Planned
- Save/load workflows (JSON export/import)
- Export results (download images/videos)
- Octane node for octaneWebR integration
- Batch processing
- Node templates
- Undo/redo

---

## Key Code Patterns

### Adding a New Node Type

1. **Create component** in `client/src/components/Nodes/NewNode.tsx`
2. **Define data type** in `client/src/types/index.ts`:
   ```typescript
   export type NewNodeData = {
     // node-specific data
   };
   ```
3. **Register in React Flow** (`App.tsx`):
   ```typescript
   const nodeTypes = useMemo(
     () => ({
       // ...existing
       newNode: NewNode,
     }),
     []
   );
   ```
4. **Add to NodeBar** (`NodeBar.tsx`): Add creation logic

### Connection Validation

Located in `connectionValidator.ts`:
```typescript
export function isValidConnection(
  sourceHandle: HandleType,
  targetHandle: HandleType
): boolean {
  if (sourceHandle === 'any' || targetHandle === 'any') return true;
  if (sourceHandle === targetHandle) return true;
  if (sourceHandle === 'integer' && targetHandle === 'float') return true;
  // ... more rules
  return false;
}
```

### Logging

```typescript
import { logger } from './services/logger';

logger.info('Action performed', { nodeId, data });
logger.error('Error occurred', error);
logger.debug('Debug info', { details });
```

Logs append to `server/logs/app.log`, cleared on app restart.

---

## Running the App

```bash
cd /workspace/project/grpcSamples/otoyaiWeb
npm run dev    # Start both client (port 60023) and server (port 3001)
```

Access at `http://localhost:60023`

---

## Recent Changes Summary

### Latest Session Work
- Implemented fine-grained pin color system (9 data types)
- Split "number" type into `integer` and `float`
- Updated FLUX.1 schema with correct types (steps=integer, guidance_scale=float)
- Added color mapping functions in connectionValidator.ts
- Updated all nodes to use new type system
- Fixed TypeScript errors across codebase
- Tested in browser with FLUX.1, GPT-4o, Kling Video nodes

### Known Issues
- API execution not yet implemented (nodes display but don't execute)
- Edge colors are default cyan (should match source pin color)
- No visual feedback during connection drag
- No workflow save/load

---

## Development Commands

```bash
npm run dev              # Start full stack
npm run dev:client       # Client only
npm run dev:server       # Server only
npm run build            # Build for production
cd client && npm run type-check   # TypeScript validation
```

---

## Next Steps (Suggested)

1. **Implement API Execution**
   - Create execution handler in `services/api.ts`
   - Add "Run" button to nodes or toolbar
   - POST to play.otoy.ai endpoints with node parameters
   - Display results in nodes

2. **Edge Color Matching**
   - Update edge styles to match source handle color
   - Modify `App.tsx` edge rendering

3. **Visual Connection Feedback**
   - Highlight valid connection targets during drag
   - Show invalid connection indicators

4. **Workflow Save/Load**
   - Export graph as JSON
   - Import JSON to restore graph state
   - LocalStorage persistence

---

## Files to Read First

When resuming, review these files to understand the current state:

1. `README.md` - Project overview
2. `client/src/App.tsx` - Main app logic
3. `client/src/utils/connectionValidator.ts` - Type system
4. `client/src/utils/endpointSchema.ts` - AI model definitions
5. `client/src/components/Nodes/AIEndpointNode.tsx` - Dynamic AI nodes
6. `server/server.ts` - API proxy

---

## Useful Context

- **API Docs**: https://play.otoy.ai/api/endpoints (live endpoint list)
- **React Flow Docs**: https://reactflow.dev
- **Beta UI Reference**: https://beta.otoy.ai (design inspiration)
- **Logger Location**: `server/logs/app.log`

---

**You are now up to speed on otoyaiWeb development. Start by checking the README.md and running `npm run dev` to see the current state.**
