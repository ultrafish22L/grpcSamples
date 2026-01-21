# OtoyaiWeb - Comprehensive Development Plan

**Project:** React Node Graph UI for play.otoy.ai API  
**Status:** ✅ Phase 1 Complete - TypeScript Issues Resolved  
**Last Updated:** January 2025  
**Repository:** https://github.com/ultrafish22L/grpcSamples

---

## 📌 Project Overview

A modern React-based node graph editor for the play.otoy.ai AI model API, inspired by octaneWebR and beta.otoy.ai. Built with TypeScript, Vite, ReactFlow, and Zustand.

### Key Features Implemented
- ✅ Node graph editor with ReactFlow
- ✅ 1,136+ AI model endpoints from play.otoy.ai
- ✅ 35+ categories (text-to-image, image-to-video, etc.)
- ✅ Multi-item Image and Video nodes
- ✅ Collapsible previews with add/delete controls
- ✅ Composite + individual output pins
- ✅ Dark theme UI (beta.otoy.ai style)
- ✅ TypeScript 100% (zero compilation errors)

---

## 🎯 Current Status (Phase 1: Complete)

### ✅ Architecture & Setup
- **Frontend:** React 18 + TypeScript + Vite (Port 60023)
- **Backend:** Express + TypeScript (Port 5001)
- **State:** Zustand
- **UI:** ReactFlow + CSS Modules
- **Build:** Vite (374KB bundle, <1s build time)

### ✅ Node Types Implemented
1. **AI Endpoint Node** - Displays model info (vendor, title, categories)
2. **Image Node** - Multi-item support with URL/file upload
3. **Video Node** - Multi-item support with URL/file upload  
4. **Text Input Node** - Simple text area input

### ✅ UI Components
- **Toolbar** (Left sidebar) - Utility node buttons
- **Context Menu** - Expandable categories with endpoints
- **Node Graph** - Main canvas with drag/zoom/pan
- **Minimap** - Navigation overview

### ✅ Recent Fixes (Commit 7d2c4cfd)
- Fixed all TypeScript compilation errors
- Implemented double cast pattern for type safety
- Consistent type usage across all node components
- Build now passes with zero errors

---

## 🗺️ Development Roadmap

## Phase 2: Workflow Execution (Next)

### 2.1 API Integration
**Goal:** Connect nodes and execute AI model workflows

**Tasks:**
- [ ] Implement node connection logic
- [ ] Parse workflow graph into execution plan
- [ ] Call play.otoy.ai API endpoints
- [ ] Handle authentication/API keys
- [ ] Display results in nodes
- [ ] Error handling and retry logic

**Estimated Time:** 2-3 days

### 2.2 Progress & Results Display
**Goal:** Show execution status and results

**Tasks:**
- [ ] Add progress indicators to nodes
- [ ] Display result images/videos in nodes
- [ ] Show execution time/status
- [ ] Handle multiple outputs
- [ ] Cache results for re-execution

**Estimated Time:** 1-2 days

---

## Phase 3: Persistence & Workflows

### 3.1 Save/Load System
**Goal:** Persist workflows and restore them

**Tasks:**
- [ ] Export workflow to JSON
- [ ] Import workflow from JSON
- [ ] Auto-save to localStorage
- [ ] Cloud save/load (optional)
- [ ] Workflow templates/presets

**Estimated Time:** 2 days

### 3.2 Undo/Redo
**Goal:** Allow users to undo/redo actions

**Tasks:**
- [ ] Implement history stack
- [ ] Add keyboard shortcuts (Ctrl+Z, Ctrl+Y)
- [ ] Track node/connection changes
- [ ] UI indicators for undo/redo state

**Estimated Time:** 1 day

---

## Phase 4: UX Improvements

### 4.1 Search & Filter
**Goal:** Make 1,136 endpoints discoverable

**Tasks:**
- [ ] Search bar for endpoints
- [ ] Filter by category
- [ ] Fuzzy search
- [ ] Recently used endpoints
- [ ] Favorites/bookmarks

**Estimated Time:** 2 days

### 4.2 Node Parameter Editing
**Goal:** Edit AI model parameters directly in nodes

**Tasks:**
- [ ] Dynamic parameter forms
- [ ] Type-specific inputs (sliders, dropdowns, etc.)
- [ ] Parameter validation
- [ ] Default values from API
- [ ] Save parameter presets

**Estimated Time:** 3 days

### 4.3 Keyboard Shortcuts
**Goal:** Improve workflow speed

**Shortcuts:**
- [ ] Delete - Remove selected node
- [ ] Ctrl+Z - Undo
- [ ] Ctrl+Y - Redo
- [ ] Ctrl+C/V - Copy/Paste nodes
- [ ] Ctrl+D - Duplicate node
- [ ] Space+Drag - Pan canvas
- [ ] Ctrl+Scroll - Zoom

**Estimated Time:** 1 day

---

## Phase 5: Advanced Features

### 5.1 Drag from Menu
**Goal:** Drag nodes directly from menu to canvas

**Tasks:**
- [ ] Implement drag events from sidebar
- [ ] Show ghost node during drag
- [ ] Drop to create node at position
- [ ] Snap to grid (optional)

**Estimated Time:** 1 day

### 5.2 Node Groups
**Goal:** Organize complex workflows

**Tasks:**
- [ ] Create node groups
- [ ] Collapse/expand groups
- [ ] Color coding
- [ ] Group naming

**Estimated Time:** 2 days

### 5.3 Comments & Annotations
**Goal:** Document workflows

**Tasks:**
- [ ] Add comment nodes
- [ ] Sticky notes
- [ ] Arrow annotations
- [ ] Rich text support

**Estimated Time:** 1 day

---

## Phase 6: Octane Integration

### 6.1 Octane Render Node
**Goal:** Add 3D rendering capabilities

**Tasks:**
- [ ] Create Octane node component
- [ ] Connect to octaneWebR
- [ ] Display 3D preview
- [ ] Material/lighting parameters
- [ ] Render queue management

**Estimated Time:** 5 days

### 6.2 Bridge to octaneWebR
**Goal:** Full integration with Octane

**Tasks:**
- [ ] Shared state between apps
- [ ] Import Octane scenes
- [ ] Export to Octane format
- [ ] Live preview updates

**Estimated Time:** 5 days

---

## 🧪 Testing Strategy

### Unit Tests (Jest)
- [ ] Node component tests
- [ ] State management tests
- [ ] API client tests
- [ ] Utility function tests

### Integration Tests (Playwright)
- [ ] Node creation flow
- [ ] Connection creation
- [ ] Workflow execution
- [ ] Save/load workflows

### Performance Tests
- [ ] Large graph rendering (100+ nodes)
- [ ] Real-time updates
- [ ] Memory usage
- [ ] Bundle size optimization

---

## 📐 Architecture Details

### Component Structure
```
otoyaiWeb/
├── client/
│   ├── src/
│   │   ├── components/
│   │   │   ├── Layout/
│   │   │   │   ├── Toolbar.tsx          # Left sidebar
│   │   │   │   ├── ContextMenu.tsx      # Category/node menu
│   │   │   │   └── MainLayout.tsx       # Root layout
│   │   │   ├── NodeGraph/
│   │   │   │   └── NodeGraph.tsx        # ReactFlow canvas
│   │   │   └── Nodes/
│   │   │       ├── AIEndpointNode.tsx   # AI model node
│   │   │       ├── ImageNode.tsx        # Multi-image node
│   │   │       ├── VideoNode.tsx        # Multi-video node
│   │   │       └── TextInputNode.tsx    # Text input
│   │   ├── services/
│   │   │   ├── api.ts                   # play.otoy.ai client
│   │   │   └── logger.ts                # Logging service
│   │   ├── store/
│   │   │   └── useStore.ts              # Zustand state
│   │   ├── types/
│   │   │   ├── endpoints.ts             # API types
│   │   │   └── nodes.ts                 # Node types
│   │   └── styles/
│   │       └── *.module.css             # Component styles
│   └── vite.config.ts                   # Vite config + CORS
└── server/
    └── src/
        └── index.ts                     # Express logger server
```

### State Management (Zustand)
```typescript
interface AppState {
  // Nodes & Edges
  nodes: AppNode[];
  edges: AppEdge[];
  addNode: (node: AppNode) => void;
  updateNode: (id: string, data: Partial<NodeData>) => void;
  deleteNode: (id: string) => void;
  
  // Endpoints
  endpoints: Endpoint[];
  categories: string[];
  loadEndpoints: () => Promise<void>;
  
  // Execution (Phase 2)
  executeWorkflow: () => Promise<void>;
  executionStatus: Map<string, ExecutionStatus>;
}
```

### API Integration Strategy
```typescript
// Phase 2 implementation plan
interface WorkflowExecutor {
  // 1. Parse graph
  parseGraph(nodes: Node[], edges: Edge[]): ExecutionPlan;
  
  // 2. Topological sort
  getExecutionOrder(plan: ExecutionPlan): string[];
  
  // 3. Execute nodes
  executeNode(node: AIEndpointNode): Promise<Result>;
  
  // 4. Update results
  updateNodeResults(nodeId: string, result: Result): void;
}
```

---

## 🚀 Deployment Options

### Development
```bash
cd grpcSamples/otoyaiWeb
npm run dev  # Starts both frontend + backend
```

### Production Build
```bash
npm run build  # Builds client to dist/
```

### Deployment Targets
- [ ] Vercel (recommended for frontend)
- [ ] Netlify (alternative)
- [ ] Railway/Render (backend)
- [ ] Docker container (full stack)
- [ ] Electron app (desktop version)

---

## 📊 Technical Metrics

### Current (Phase 1)
- **Lines of Code:** ~3,000
- **Bundle Size:** 374 KB (gzipped: 124 KB)
- **Build Time:** 950ms
- **Dependencies:** 111 (client) + 4 (server)
- **TypeScript Errors:** 0
- **Test Coverage:** 0% (Phase 2+)

### Target (Phase 6)
- **Lines of Code:** ~10,000
- **Bundle Size:** <500 KB (gzipped)
- **Build Time:** <2s
- **Test Coverage:** >80%
- **Performance:** 60fps on 100+ node graphs

---

## 🔧 Configuration Files

### TypeScript Config
```json
{
  "compilerOptions": {
    "target": "ES2020",
    "lib": ["ES2020", "DOM"],
    "module": "ESNext",
    "moduleResolution": "bundler",
    "strict": true,
    "jsx": "react-jsx"
  }
}
```

### Vite Config (CORS Proxy)
```typescript
export default defineConfig({
  server: {
    port: parseInt(process.env.WORKER_1 || '60023'),
    proxy: {
      '/api': {
        target: 'https://play.otoy.ai',
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/api/, '/api')
      }
    }
  }
})
```

---

## 📚 API Reference

### play.otoy.ai Endpoints

#### GET /api/endpoints
Returns list of all AI model endpoints.

**Response:**
```json
[
  {
    "title": "AuraFlow",
    "vendor": "Fal.ai",
    "description": "...",
    "category": ["text-to-image"],
    "endpoint": "/workflows/fal-ai/aura-flow",
    "inputTypes": ["text"],
    "outputTypes": ["image"]
  }
]
```

#### POST /workflows/{endpoint}
Execute AI model with parameters.

**Request:**
```json
{
  "prompt": "A beautiful landscape",
  "width": 1024,
  "height": 1024
}
```

**Response:**
```json
{
  "id": "job-123",
  "status": "completed",
  "output": {
    "images": ["https://..."]
  }
}
```

---

## 🐛 Known Issues & Limitations

### Current Limitations
1. ❌ Workflows don't execute yet (Phase 2)
2. ❌ No save/load functionality (Phase 3)
3. ❌ No undo/redo (Phase 3)
4. ❌ No endpoint search (Phase 4)
5. ❌ No parameter editing UI (Phase 4)
6. ❌ File uploads not implemented (Phase 2)
7. ❌ No test coverage (Ongoing)

### Bug Fixes Needed
- [ ] Node drag performance with 50+ nodes
- [ ] Memory leak on repeated node creation
- [ ] Edge routing around nodes
- [ ] Minimap click-to-pan precision

---

## 💡 Future Enhancements

### Nice-to-Have Features
- [ ] **Themes** - Light mode, custom themes
- [ ] **Multi-language** - i18n support
- [ ] **Collaboration** - Real-time multiplayer editing
- [ ] **Version Control** - Workflow versioning
- [ ] **Marketplace** - Share workflow templates
- [ ] **Mobile App** - React Native version
- [ ] **Voice Control** - Speech commands
- [ ] **AI Assistant** - Auto-suggest workflows

---

## 📖 Documentation

### User Documentation
- [x] README.md - Setup and usage guide
- [x] STATUS.md - Current status
- [x] PLAN.md - Original development plan
- [x] PROJECT_REPORT.md - Detailed technical report
- [x] TYPESCRIPT_FIX_REPORT.md - Fix documentation
- [x] COMPREHENSIVE_PLAN.md - This file

### Developer Documentation
- [ ] API.md - API integration guide
- [ ] ARCHITECTURE.md - System architecture
- [ ] CONTRIBUTING.md - Contribution guidelines
- [ ] TESTING.md - Testing strategy

---

## 🤝 Contributing

### Development Workflow
1. Fork repository
2. Create feature branch
3. Make changes with tests
4. Ensure TypeScript passes
5. Submit pull request

### Code Standards
- TypeScript strict mode
- ESLint + Prettier
- Component naming: PascalCase
- File naming: kebab-case
- Commit messages: Conventional Commits

---

## 📞 Support & Contact

### Resources
- **Repository:** https://github.com/ultrafish22L/grpcSamples
- **API Docs:** https://play.otoy.ai/api/endpoints
- **ReactFlow Docs:** https://reactflow.dev
- **Zustand Docs:** https://zustand-demo.pmnd.rs

### Getting Help
- Open GitHub issue for bugs
- Discussion board for questions
- Discord community (TBD)

---

## ✅ Success Metrics

### Phase 1 (Complete)
- ✅ UI matches beta.otoy.ai aesthetic
- ✅ Node graph functional
- ✅ Multi-item nodes working
- ✅ TypeScript 100% typed
- ✅ Zero compilation errors
- ✅ Build < 1 second

### Phase 2 (Next)
- [ ] Workflow execution working
- [ ] API integration complete
- [ ] Results display in nodes
- [ ] Error handling robust

### Phase 3-6 (Future)
- [ ] Save/load functional
- [ ] Search UX excellent
- [ ] Performance optimized
- [ ] Octane integrated
- [ ] Test coverage >80%

---

**Plan Status:** ✅ Phase 1 Complete  
**Next Milestone:** Phase 2 - Workflow Execution  
**Estimated Completion:** Q1 2025  
**Last Updated:** January 2025

---

*This is a living document. Update as project evolves.*

