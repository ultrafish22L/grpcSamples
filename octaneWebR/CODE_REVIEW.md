# octaneWebR - Development Priorities

**Last Updated**: 2025-01-22  
**Branch**: `main`

---

## 📋 Current Status

octaneWebR is a **production-ready** React/TypeScript UI clone of Octane Render Studio Standalone Edition with complete gRPC API integration. All core features are implemented and working with real-time Octane synchronization.

### ✅ Recently Completed (2025-01-22)
- Scene Outliner & Node Inspector context menus (right-click)
- Node Graph Editor vertical button bar layout  
- All fixes pushed to main branch
- Documentation cleanup (removed 16 temporary completion docs)

---

## 🎯 High-Priority Tasks

### P1 - User Experience Improvements
1. **Context Menu Handler Implementation**
   - Scene Outliner: Implement render, save, cut, copy, paste, delete, show-in-graph, show-in-lua actions
   - Node Inspector: Implement save, cut, copy, paste, delete, expand, show-in-outliner, show-in-graph actions
   - Current state: UI implemented, handlers log to console

2. **Cross-Component Event System**
   - "Show in Graph Editor" from Scene Outliner/Node Inspector
   - "Show in Outliner" from Node Inspector  
   - Bidirectional selection sync across all panels

3. **Keyboard Shortcut Enhancement**
   - Full Ctrl+X, Ctrl+C, Ctrl+V clipboard system
   - Context-aware shortcuts (respect focused panel)

### P2 - Feature Parity with Octane SE
4. **Material Database Enhancements**
   - LiveDB search and filtering improvements
   - LocalDB organization and tagging
   - Drag-and-drop material application

5. **Node Graph Advanced Features**
   - Node grouping/commenting
   - Layout auto-arrangement algorithms
   - Zoom-to-fit and frame-selected shortcuts

6. **Viewport Enhancements**
   - Region rendering (render specific viewport area)
   - Viewport LUT/color grading previews
   - Comparison mode (before/after slider)

### P3 - Polish & Optimization
7. **Performance**
   - Large scene optimization (1000+ nodes)
   - Render streaming compression
   - React component memoization audit

8. **Accessibility**
   - ARIA labels for all interactive elements
   - Keyboard navigation for all dialogs
   - Screen reader support

9. **Testing**
   - Unit tests for core utilities
   - Integration tests for gRPC client
   - E2E tests for critical workflows

---

## 📚 Reference for Implementations

### Octane SE Manual Sections (Priority Order)
1. **Interface Layout** → `https://docs.otoy.com/standaloneSE/CoverPage.html`
   - The Graph Editor (context menus, shortcuts)
   - The Node Inspector (parameter editing)
   - The Scene Outliner (hierarchy operations)

2. **Working with Files and Geometry**
   - Importing and Exporting
   - Managing Geometry (all node types)

3. **Materials**
   - Materials Database (LiveDB/LocalDB)
   - All material types

4. **Rendering**
   - Render Settings
   - AOVs and Compositing
   - Network Rendering

### octaneWeb Reference (Original JavaScript Implementation)
- **Location**: `/workspace/project/grpcSamples/octaneWeb/`
- **Key files**: 
  - `js/ui/SceneOutliner.js` - Context menu handlers
  - `js/ui/NodeInspector.js` - Parameter editing patterns
  - `js/ui/NodeGraph.js` - Node graph operations
  - `css/otoy-theme.css` - Styling reference

### Proto Files (gRPC API Definitions)
- **Location**: `/workspace/project/grpcSamples/sdk/src/api/grpc/protodef/`
- **Key files**:
  - `apinodesystem.proto` - Node CRUD operations
  - `apimodulenodegraph.proto` - Graph editor operations
  - `apilocaldb.proto` - Material database
  - `octaneinfos.proto` - Metadata (node types, pin info)

---

## 🔧 Development Guidelines

### Task Assignment Protocol
1. **NEVER start work without explicit user approval**
2. **Always stop and ask for next task** after completion
3. **Present task options** from priority list above
4. **Confirm understanding** before implementing

### Implementation Workflow
1. **Verify feature exists** in Octane SE manual
2. **Check proto files** for required gRPC APIs
3. **Implement** with TypeScript + React best practices
4. **Build check**: `npm run build` (must pass)
5. **Runtime test**: `npm run dev` (check console logs, not browser UI)
6. **Commit** with descriptive message
7. **Push** to main (if authorized)
8. **Stop and report** completion

### Code Quality Standards
- ✅ TypeScript strict mode (no `any` types)
- ✅ All API calls wrapped in try/catch
- ✅ Console logging for debugging (check `octaneWebR_client.log`)
- ✅ Follow existing code patterns
- ✅ No duplicate files (modify originals directly)

### Debugging
- **Primary**: Check `octaneWebR_client.log` (browser console output)
- **Secondary**: Check server logs for gRPC errors
- **Health check**: `curl http://localhost:43930/api/health`

---

## 🎯 Feature Status Matrix

| Component | Feature | Status | Reference |
|-----------|---------|--------|-----------|
| **Node Graph** | Context menus | ✅ Done | Manual: Graph Editor |
| | Multi-select/box select | ✅ Done | |
| | Copy/Paste/Delete | ✅ Done | |
| | Connection cutter | ✅ Done | |
| | Enhanced tooltips | ✅ Done | |
| | Search dialog (Ctrl+F) | ✅ Done | |
| | Minimap | ✅ Done | |
| | Vertical toolbar | ✅ Done | NEW |
| **Scene Outliner** | Hierarchy tree | ✅ Done | Manual: Scene Outliner |
| | Expand/collapse | ✅ Done | |
| | Visibility toggles | ✅ Done | |
| | Context menu | ✅ UI Only | NEW - Needs handlers |
| | LiveDB tab | ✅ Done | |
| | LocalDB tab | ✅ Done | |
| **Node Inspector** | All parameter types | ✅ Done | Manual: Node Inspector |
| | Real-time sync | ✅ Done | |
| | Grouping/sections | ✅ Done | |
| | Context menu | ✅ UI Only | NEW - Needs handlers |
| **Viewport** | Callback streaming | ✅ Done | Manual: Render Viewport |
| | Camera controls | ✅ Done | |
| | Picking tools | ✅ Done | |
| | Toolbar controls | ✅ Done | |
| **Menu System** | File, Edit, Script | ✅ Done | Manual: Interface |
| | View, Window, Help | ✅ Done | |
| **Dialogs** | Preferences | ✅ Done | |
| | Material Database | ✅ Done | |
| | Batch Rendering | ✅ Done | |
| | Turntable Animation | ✅ Done | |
| | GPU Statistics | ✅ Done | |

---

## 📊 Project Statistics

**Codebase** (as of 2025-01-22):
- **Total Lines**: ~18,000 TypeScript/TSX
- **Components**: 35+ React components
- **gRPC Methods**: 200+ API wrappers
- **Node Types**: 755+ supported
- **Commits**: 70+ with clear descriptions

**Documentation** (core only):
- README.md - Main project overview
- OVERVIEW.md - Architecture deep dive
- QUICKSTART.md - Setup guide
- WORKFLOW.md - Development process
- GAP_ANALYSIS.md - Feature comparison
- CODE_REVIEW.md - Current priorities (this file)

---

## 🆘 Known Issues

### None Currently
All blocking issues resolved. Build passes, dev server starts, Octane connection working.

---

## 🚀 Getting Started (Quick Reference)

```bash
# First time setup
cd /workspace/project/grpcSamples/octaneWebR
npm install

# Start Octane with LiveLink enabled (Help → LiveLink)
# Then start dev server:
npm run dev

# Open http://localhost:43930
# Check browser console for "Connected to Octane"
```

**Troubleshooting**: See README.md for detailed troubleshooting guide

---

**Ready for next task assignment** 🎯
