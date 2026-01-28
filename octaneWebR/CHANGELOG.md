# Changelog

All notable changes to octaneWebR will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [Unreleased]

### Added
- OpenHands skills system in `.openhands/skills/` directory
  - `octane-grpc/SKILL.md` - gRPC patterns and troubleshooting
  - `node-inspector/SKILL.md` - NodeInspector architecture and dropdown feature
  - `testing-workflow/SKILL.md` - Complete testing routine and debugging
  - `scene-graph/SKILL.md` - Scene graph structure and patterns
  - `react-patterns/SKILL.md` - React/TypeScript conventions
- Skills README.md documenting the on-demand knowledge system

### Changed
- Refactored `AGENTS.md` from 595 lines to 315 lines (47% reduction)
- Moved domain-specific knowledge from AGENTS.md to specialized skill files
- Updated all core documentation files (README, QUICKSTART, DEVELOPMENT, CHANGELOG)
- Removed external path references from documentation
- Fixed port numbers throughout documentation (58407 → 57341)
- Cleaned up 24 temporary markdown documentation files (icon extraction working docs, session reports, etc.)

### UI Refinements
- **Scene Outliner Tabs**: Added tab bar with right-slanted overlap effect matching Octane SE
  - Black outline (1px solid) with 3px padding
  - Active tab: `--octane-bg-secondary`, Inactive: `--octane-bg-lighter`
  - Z-index stacking for proper left-to-right overlap
- **Node Graph Editor Tabs**: Added matching tab bar with single "Scene" tab
  - Vertical toolbar on left (26px width) extending to top
  - Tab bar positioned to right of toolbar in horizontal row
  - Tabs aligned to bottom of row for proper integration
  - Constrained tab width (max-width: 120px) matching Octane SE reference

---

## [1.0.0] - 2025-01-22

### Added - Core Features

#### Node Graph Editor
- ReactFlow-based node graph with 755+ node types
- Right-click context menu with 25 categories
- Drag-and-drop pin connections with automatic type-based coloring
- Multi-select, copy/paste, duplicate, delete operations
- Connection cutter tool (Ctrl+Drag)
- Node search dialog (Ctrl+F)
- Minimap navigation
- Bidirectional sync with Octane scene

#### Scene Outliner
- Hierarchical tree view with expand/collapse
- Type-specific icons (300+ PNG icons)
- Visibility toggles
- Selection synchronization with Node Graph
- LiveDB tab for OTOY material library
- LocalDB tab for local materials and node groups

#### Node Inspector
- Real-time parameter editor with full type support:
  - Boolean checkboxes
  - Numeric inputs (int/float with range validation)
  - Vector inputs (float2/float3/float4)
  - Color pickers (RGB/RGBA with hex input)
  - Enum dropdowns
  - Text fields
- Collapsible parameter groups
- Instant synchronization with Octane
- **Node type dropdown** for non-end nodes (replacing current node)

#### Render Viewport
- Real-time render output streaming
- Interactive camera controls (orbit, pan, zoom)
- HDR display support
- Resolution and render mode controls
- Picker tools: Material, Object, Focus, Camera Target, White Balance
- Canvas-based display with WebGL support

#### Menu System
- Complete menu bar matching Octane SE:
  - **File**: New, Open, Save, Package, Render State, Preferences
  - **Edit**: Undo, Redo, Cut, Copy, Paste, Delete, Select All
  - **Script**: Batch Rendering, Daylight Animation, Turntable Animation
  - **View**: Panel visibility, Refresh Scene (F5)
  - **Window**: Material Database, Reset Layout, Fullscreen (F11)
  - **Help**: Documentation, Shortcuts, Report Bug, About
- Platform-aware keyboard shortcuts (Ctrl/Cmd)

### Added - Infrastructure

#### Service Layer
- `BaseService` - Abstract base class with event emitter
- `ConnectionService` - WebSocket connection management
- `SceneService` - Scene tree and node operations
- `NodeService` - Node CRUD operations with `replaceNode()` method
- `ViewportService` - Camera and viewport state
- `RenderService` - Render control and streaming
- `MaterialDatabaseService` - LiveDB/LocalDB access
- `DeviceService` - Device and system operations
- `OctaneClient` - Main API facade

#### gRPC Integration
- Vite plugin for embedded gRPC-Web proxy
- TypeScript types auto-generated from proto files
- WebSocket-based callback streaming
- Full type safety across gRPC API
- Connection health monitoring

#### Styling & Theming
- CSS Variables theme system (134 variables)
- `octane-theme.css` - Theme definitions
- Component-scoped CSS files:
  - `app.css` - Menu, panels, status bar
  - `scene-outliner.css` - Tree view
  - `viewport.css` - Render viewport
  - `node-graph.css` - Node editor
  - `node-inspector.css` - Parameter controls
- Dark theme matching Octane SE
- No inline styles, no hardcoded colors

### Added - Build System
- Vite 5 with HMR (Hot Module Replacement)
- TypeScript strict mode with zero `any` types
- Proto file compilation with `grpc-tools`
- Concurrent dev server (client + proxy)
- Production build with tree-shaking and minification

### Added - Documentation
- `README.md` - Project overview and features
- `QUICKSTART.md` - Setup guide
- `DEVELOPMENT.md` - Architecture and patterns
- `AGENTS.md` - AI assistant memory and workflows
- `CHANGELOG.md` - Version history (this file)

---

## [0.9.0] - 2025-01-20

### Added - Beta Features
- Initial UI layout with resizable panels
- Basic node graph with limited node types
- Scene tree viewer (read-only)
- Simple parameter editor
- Static render display
- Menu bar structure

### Changed
- Migrated from REST to gRPC-Web for Octane communication
- Switched from Redux to Zustand for state management
- Refactored from class components to functional components + hooks

---

## [0.5.0] - 2025-01-15

### Added - Alpha Features
- Proof-of-concept React app
- Basic gRPC connection to Octane
- Simple node creation test
- WebSocket streaming prototype

---

## [0.1.0] - 2025-01-10

### Added - Initial Setup
- Project structure
- Dependencies (React, TypeScript, Vite)
- gRPC proto files
- Basic build configuration

---

## Version History Summary

| Version | Date | Milestone |
|---------|------|-----------|
| **1.0.0** | 2025-01-22 | Production-ready release |
| 0.9.0 | 2025-01-20 | Beta with core features |
| 0.5.0 | 2025-01-15 | Alpha prototype |
| 0.1.0 | 2025-01-10 | Initial setup |

---

## Feature Categories

### ✅ Complete
- Node Graph Editor
- Scene Outliner
- Node Inspector
- Render Viewport
- Menu System
- Service Layer
- gRPC Integration
- Theme System
- Build Pipeline

### 🚧 In Progress
- Material Database (LiveDB/LocalDB browsing working, drag-and-drop pending)
- Picker Tools (UI complete, some tools pending)
- Animation Scripts (menu items added, scripts pending)

### 📋 Planned
- Keyboard shortcut customization
- Custom themes (light theme, high contrast)
- Plugin system
- Advanced render settings dialog
- Batch render queue management
- Node library favorites
- Recent files menu
- Scene comparison view

---

## Breaking Changes

None yet (version 1.0.0 is first stable release).

---

## Migration Guide

### From 0.9.x to 1.0.0

**API Changes:**
- `NodeService.createNode()` now returns `Promise<number>` (node handle) instead of full node object
- `SceneService.loadTree()` renamed to `SceneService.loadSceneTree()` for clarity
- Event names standardized: `node-created` → `node:created`, `scene-loaded` → `scene:loaded`

**UI Changes:**
- Node Inspector now shows dropdown for compatible node types
- Scene Outliner icons updated to match Octane SE 2023
- Viewport controls repositioned to match Octane SE layout

**Build Changes:**
- Vite upgraded from 4.x to 5.x
- TypeScript upgraded from 5.0 to 5.2
- ReactFlow upgraded from 11.x to 12.x

**Migration Steps:**
1. Update imports: `import { loadTree }` → `import { loadSceneTree }`
2. Update event listeners: `.on('node-created')` → `.on('node:created')`
3. Update API calls: Handle `createNode()` returns number instead of object
4. Run `npm install` to update dependencies
5. Run `npx tsc --noEmit` to check for type errors
6. Run `npm run build` to verify build succeeds

---

## Credits

- **OTOY Inc.** - Octane Render and gRPC LiveLink API
- **ReactFlow** - Node graph editor library
- **Vite** - Build tool and dev server
- **React** - UI framework

---

**Maintained by**: OTOY Development Team  
**Last Updated**: 2025-01-29  
**Status**: Active Development
