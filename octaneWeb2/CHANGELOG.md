# Changelog

All notable changes to OctaneWeb2 will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

---

## [Unreleased]

### Phase 2: Core Rendering (In Progress)
- [ ] Port buffer processing from original CallbackRenderViewport.js
- [ ] Create useRenderCallback hook for WebSocket stream
- [ ] Implement HDR/LDR buffer conversion
- [ ] Display render frames in viewport
- [ ] Update FPS counter in real-time

---

## [0.1.0] - 2025-11-05

### Phase 1: Foundation (COMPLETE) ✅

#### Added
- **Project Setup**
  - Initialized React 19 + TypeScript + Vite project
  - Configured tsconfig with strict mode and path aliases
  - Installed core dependencies: zustand, @tanstack/react-query, clsx
  - Created .gitignore for node_modules and build artifacts

- **Layout Components**
  - `MainLayout.tsx` - 3-panel grid layout (left, center, right)
  - `MenuBar.tsx` - Top menu bar with connection status
  - `StatusBar.tsx` - Bottom status bar with FPS display
  - Responsive CSS with proper overflow handling

- **Viewport**
  - `RenderViewport.tsx` - Canvas component for displaying renders
  - Auto-resize canvas to fill container
  - Ready for ImageData rendering

- **State Management**
  - `connectionStore.ts` - Connection state (isConnected, isConnecting, error)
  - `renderStore.ts` - Render state (imageData, samples, fps, resolution)
  - Zustand integration with TypeScript types

- **API Layer**
  - `OctaneClient.ts` - Singleton API client for Octane communication
  - Type-safe methods: ping, getSceneTree, setCameraPosition, etc.
  - Centralized error handling

- **Styling**
  - `variables.css` - CSS custom properties for OTOY dark theme
  - Color palette: bg-primary, bg-secondary, accent, status colors
  - Typography and spacing system
  - Professional dark UI matching original

- **TypeScript Types**
  - `octane.ts` - Core types: SceneNode, Vector3, RenderStats, etc.
  - Full type coverage for Octane data structures

- **Documentation**
  - README.md - Project overview and quick start guide
  - IMPLEMENTATION_PLAN.md - Detailed 11-phase plan (400+ lines)
  - CODE_COMPARISON.md - Before/after code examples (350+ lines)
  - STATUS.md - Progress tracker (300+ lines)
  - PROJECT_SUMMARY.md - Executive overview (450+ lines)
  - CHANGELOG.md - This file

- **Development Tools**
  - start.sh - Startup script for dev server
  - Vite dev server on port 42219
  - Hot Module Replacement (HMR) working

#### Metrics
- Lines of Code: 392 TypeScript (vs 12,592 in original)
- Files Created: 25 (config, components, stores, docs)
- Dev Server: Running at http://localhost:42219
- TypeScript Errors: 0 ✅

#### Notes
- Foundation is solid and ready for Phase 2
- All core patterns established (stores, hooks, components)
- Project structure matches best practices
- Documentation comprehensive (1,500+ lines total)

---

## Project Statistics

### Codebase Size
- **Original octaneWeb**: 12,592 lines JavaScript
- **OctaneWeb2 (Current)**: 392 lines TypeScript
- **OctaneWeb2 (Target)**: ~6,000 lines TypeScript
- **Progress**: 6.5% complete

### Component Count
- **Created**: 7 components
- **Target**: ~40 components
- **Remaining**: ~33 components

### Stores
- **Created**: 2 stores (connection, render)
- **Target**: 6 stores
- **Remaining**: 4 stores (scene, nodeGraph, ui, console)

### Custom Hooks
- **Created**: 0 hooks
- **Target**: 10 hooks
- **To Create**: useRenderCallback, useCameraControls, useKeyboardShortcuts, etc.

---

## Timeline

| Phase | Duration | Status |
|-------|----------|--------|
| 1. Foundation | 0.5 day | ✅ COMPLETE |
| 2. Core Rendering | 1-2 days | 🔄 IN PROGRESS |
| 3. Camera Controls | 1 day | 🔜 |
| 4. Scene Outliner | 2 days | 🔜 |
| 5. Node Inspector | 2-3 days | 🔜 |
| 6. Node Graph | 3-4 days | 🔜 |
| 7. Keyboard Shortcuts | 0.5 day | 🔜 |
| 8. Debug Console | 1 day | 🔜 |
| 9. Menu Actions | 2 days | 🔜 |
| 10. Polish | 2-3 days | 🔜 |
| 11. Testing | 3 days | 🔜 |

**Total Estimate**: 3-4 weeks
