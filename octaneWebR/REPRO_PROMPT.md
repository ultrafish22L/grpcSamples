# REPRO_PROMPT: Continue octaneWebR Development

Use this as your initial prompt when starting a new session to quickly get back up to speed.

---

## 🎯 Quick Context

**Project**: octaneWebR - React + TypeScript port of octaneWeb  
**Location**: `/workspace/project/grpcSamples/octaneWebR`  
**Tech Stack**: React 18, TypeScript 5.6, Vite 6, ReactFlow, gRPC-Web  
**Purpose**: Browser-based UI for OTOY Octane Render via LiveLink gRPC API

## ✅ What's Working

- **Menu System**: File/Edit/Script/Module/Cloud/Window/Help menus with file dialogs
- **Scene Outliner**: Hierarchical tree view with expand/collapse
- **Node Inspector**: Property editor with all 12 parameter types
- **Node Graph Editor**: ReactFlow-based with context menus and connections
- **Connection Status**: Real-time connection indicator
- **Build System**: Embedded gRPC proxy in Vite (no separate server)

## 🔄 Recent Commits

- `1e788b56` - Add complete menu system with file dialogs and recent files
- `2abb01c5` - Fix fitView to only trigger once on initial scene load
- `a4789b69` - Fix context menu click-outside handler for submenus

## 🏗️ Architecture

```
Browser → Vite Dev Server (gRPC Proxy) → Octane LiveLink (127.0.0.1:51022)
```

**Key Components:**
- `App.tsx` - Main layout, menu bar, panels
- `SceneOutliner.tsx` - Scene tree (left panel)
- `NodeInspector.tsx` - Property editor (right panel)
- `NodeGraphEditorNew.tsx` - ReactFlow graph (bottom panel)
- `CallbackRenderViewport.tsx` - Render viewport (center panel, in progress)
- `OctaneClient.ts` - gRPC client logic
- `MenuBar.tsx` / `MenuDropdown.tsx` - Menu system

## ⏳ In Progress

- **Callback Render Viewport**: Real-time rendering (placeholder implemented)
- **Material Database**: Live DB and Local DB tabs (planned)
- **File Operations**: Menu actions need full Octane API integration

## 🚀 Quick Start Commands

```bash
cd /workspace/project/grpcSamples/octaneWebR

# Install dependencies (if needed)
npm install

# Start dev server (single command - includes gRPC proxy)
npm run dev

# Build for production
npm run build

# TypeScript type check only
tsc --noEmit
```

**Dev Server**: Opens at http://localhost:43929 (or next available port)  
**Health Check**: `curl http://localhost:43929/api/health`

## 💡 Development Principles

1. **Always check octaneWeb reference code** before assuming problems
2. **Use React best practices**: Hooks, functional components, TypeScript
3. **Never start work without user approval** - Always wait for task assignment
4. **Test TypeScript**: Run `npm run build` to check for errors
5. **Check logs**: Look at terminal output and browser console for issues

## 📚 Reference

**octaneWeb Reference Code**: `/workspace/project/grpcSamples/octaneWeb/`
- Check reference implementation before assuming problems
- Key files: `js/app.js`, `js/components/`, `js/utils/GenericNodeRenderer.js`
- Styling: `css/components.css` (lines 3050-3200 for parameters)

**Documentation**:
- **OVERVIEW.md** - Full project details and architecture
- **QUICKSTART.md** - Step-by-step setup instructions

## 🎯 Ready for Task Assignment

**I'm ready to continue development. Please assign the next task.**

Always wait for task assignment before starting work. Never proceed without user approval.
