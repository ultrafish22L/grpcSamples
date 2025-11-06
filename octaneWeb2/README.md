# OctaneWeb2 - React Edition

A complete rebuild of the OctaneWeb standalone application using modern React, TypeScript, and best practices.

## 🎉 Status: ✅ Phase 1-4 Complete

**All UI components built, API integrated, zero errors, ready for live data integration!**

See [DEVELOPMENT_STATUS.md](./DEVELOPMENT_STATUS.md) for full details.

## Overview

This is a ground-up rewrite of the original octaneWeb application with:

- ✅ **React 19** with TypeScript for type safety
- ✅ **Zustand** for lightweight, performant state management
- ✅ **Vite** for blazing-fast development and optimized builds
- ✅ **Centralized event handling** - no duplicate keyboard handlers
- ✅ **Clean architecture** - no code duplication
- ✅ **Modular components** - easy to maintain and extend
- ✅ **Zero TypeScript errors** - full type coverage
- ✅ **Zero runtime errors** - verified with Playwright

## Project Structure

```
octaneWeb2/
├── src/
│   ├── api/                  # Octane gRPC API client
│   │   ├── OctaneClient.ts   # Main API client
│   │   └── endpoints/        # Endpoint-specific logic
│   ├── components/
│   │   ├── layout/           # App layout (MenuBar, StatusBar, MainLayout)
│   │   ├── viewport/         # Render viewport
│   │   ├── sceneOutliner/    # Scene tree view
│   │   ├── nodeInspector/    # Node parameter editor
│   │   ├── nodeGraph/        # Visual node graph editor
│   │   ├── common/           # Reusable UI components
│   │   └── debug/            # Debug console
│   ├── hooks/                # Custom React hooks
│   ├── store/                # Zustand stores
│   │   ├── connectionStore.ts
│   │   ├── renderStore.ts
│   │   ├── sceneStore.ts
│   │   └── uiStore.ts
│   ├── utils/                # Helper functions
│   ├── styles/               # Global styles and themes
│   │   └── variables.css     # CSS variables for theming
│   └── types/                # TypeScript type definitions
└── public/                   # Static assets
```

## Key Improvements Over Original

### 1. Centralized State Management
- **Before**: Custom EventSystem with manual subscriptions scattered across files
- **After**: Zustand stores with React hooks - type-safe and predictable

### 2. Event Handling
- **Before**: 4+ locations handling keyboard shortcuts independently
- **After**: Single centralized keyboard handler in `useKeyboardShortcuts` hook

### 3. Code Organization
- **Before**: 12,600 lines of vanilla JS across 23 files
- **After**: ~6,000 lines of TypeScript with clear component boundaries

### 4. Type Safety
- **Before**: No type checking, runtime errors
- **After**: Full TypeScript coverage catches errors at compile time

### 5. Performance
- **Before**: Manual DOM manipulation and event listeners
- **After**: React's virtual DOM and optimized re-renders

## Quick Start

### Prerequisites
- Node.js 18+ installed
- Octane running with LiveLink enabled (Help → LiveLink in Octane)
- Python proxy server running (from ../octaneProxy/)

### Installation

```bash
# Install dependencies
npm install

# Start development server
npm run dev
```

The app will be available at http://localhost:42219

### Production Build

```bash
# Build for production
npm run build

# Preview production build
npm run preview
```

## Architecture

### State Management (Zustand)

We use Zustand for minimal boilerplate and excellent performance:

```typescript
// connectionStore.ts - Connection state
const useConnectionStore = create((set) => ({
  isConnected: false,
  connect: () => set({ isConnected: true })
}));

// Usage in component
const isConnected = useConnectionStore(state => state.isConnected);
```

### API Client

All Octane communication goes through a singleton `OctaneClient`:

```typescript
import { octaneClient } from '@/api/OctaneClient';

// Get scene tree
const sceneTree = await octaneClient.getSceneTree();

// Set camera position
await octaneClient.setCameraPosition({ x: 0, y: 5, z: 10 });
```

### Custom Hooks

Common patterns are extracted into reusable hooks:

- `useKeyboardShortcuts` - Global keyboard handling
- `useRenderCallback` - WebSocket render stream
- `useCameraControls` - Mouse-based camera movement
- `useSceneSync` - Scene tree synchronization

## Development Workflow

### Running the Full Stack

1. **Start Octane** with LiveLink enabled
2. **Start Python proxy**:
   ```bash
   cd ../octaneProxy
   python octane_proxy.py
   ```
3. **Start this app**:
   ```bash
   npm run dev
   ```

### Hot Module Replacement (HMR)

Vite provides instant feedback - edit any file and see changes immediately without page reload.

### Debugging

- Open browser DevTools (F12)
- React DevTools extension recommended
- Check Console for logs
- Network tab shows API calls to proxy

## Component Communication

Components communicate through Zustand stores:

```
User Input → Component → Store Action → State Update → All Subscribed Components Re-render
```

Example:
1. User clicks "Connect" button in MenuBar
2. MenuBar calls `connectionStore.connect()`
3. Store updates `isConnected` state
4. StatusBar automatically updates because it subscribes to `isConnected`

## Keyboard Shortcuts

All shortcuts are defined in one place (`useKeyboardShortcuts` hook):

- `Ctrl+S` - Save scene
- `Ctrl+O` - Open scene
- `Space` - Start/stop render
- `Ctrl+D` - Toggle debug console
- `F11` - Toggle fullscreen

## API Reference

### OctaneClient Methods

#### Connection
- `ping(): Promise<boolean>` - Test connection

#### Scene
- `getSceneTree(): Promise<SceneNode[]>` - Get scene hierarchy
- `setNodeVisibility(id, visible): Promise<void>` - Show/hide node

#### Camera
- `setCameraPosition(pos): Promise<void>` - Move camera
- `setCameraTarget(target): Promise<void>` - Aim camera

#### Rendering
- `startRender(): Promise<void>` - Begin rendering
- `stopRender(): Promise<void>` - Stop rendering

## TypeScript Types

All Octane data structures are typed in `src/types/octane.ts`:

```typescript
interface SceneNode {
  id: string;
  name: string;
  type: string;
  visible: boolean;
  children: SceneNode[];
}

interface Vector3 {
  x: number;
  y: number;
  z: number;
}
```

## Performance Considerations

- React Query caches API responses (5s stale time)
- Canvas rendering uses direct ImageData for speed
- Zustand selectors prevent unnecessary re-renders
- Vite code-splitting reduces initial bundle size

## Browser Support

- Chrome/Edge 90+
- Firefox 88+
- Safari 14+

## Contributing

This is a cleaner, more maintainable codebase. When adding features:

1. Create types first in `src/types/`
2. Add API methods to `OctaneClient`
3. Create/update Zustand store if needed
4. Build UI components using existing patterns
5. Extract reusable logic into custom hooks

## Migration from Original octaneWeb

The original octaneWeb is deprecated. This React version provides:
- Same UI/UX
- Better performance
- Easier maintenance
- Type safety
- Modern tooling

## License

Same as parent grpcSamples repository.
