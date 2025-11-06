# OctaneWeb2 Quick Start Guide

## Getting Started

This guide will help you set up and start building the React-based octaneWeb2 application.

## Prerequisites

- Node.js 18+ installed
- npm or yarn package manager
- Python 3.8+ (for the proxy server - already working)
- Octane Render with LiveLink enabled

## Step 1: Create the Project

```bash
cd /workspace/grpcSamples

# Create React + TypeScript project with Vite
npm create vite@latest octaneWeb2 -- --template react-ts

cd octaneWeb2

# Install core dependencies
npm install

# Install state management
npm install zustand

# Install React Query for async state
npm install @tanstack/react-query

# Install utility libraries
npm install clsx

# Install development dependencies
npm install -D @types/node

# Clean up
rm -rf src/App.css src/index.css src/assets
```

## Step 2: Configure Vite

Edit `vite.config.ts`:

```typescript
import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import path from 'path'

export default defineConfig({
  plugins: [react()],
  server: {
    port: 42219,  // Use the port from RUNTIME_INFORMATION
    host: '0.0.0.0',  // Allow external access
    cors: true,
    proxy: {
      // Proxy API calls to the Python proxy server
      '/api': {
        target: 'http://localhost:51023',
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/api/, '')
      }
    }
  },
  resolve: {
    alias: {
      '@': path.resolve(__dirname, './src'),
    }
  }
})
```

## Step 3: Setup Project Structure

```bash
cd src

# Create folder structure
mkdir -p api/endpoints
mkdir -p components/{layout,viewport,sceneOutliner,nodeInspector,nodeGraph,common,debug}
mkdir -p hooks
mkdir -p store
mkdir -p utils
mkdir -p styles
mkdir -p types

# Remove default files
rm App.tsx App.css index.css
```

## Step 4: Create Core Files

### 4.1 Theme & Styles

**`src/styles/variables.css`**
```css
:root {
  /* OTOY Brand Colors */
  --color-bg-primary: #1a1a1a;
  --color-bg-secondary: #252525;
  --color-bg-tertiary: #2f2f2f;
  --color-bg-hover: #333333;
  
  --color-text-primary: #e0e0e0;
  --color-text-secondary: #a0a0a0;
  --color-text-disabled: #666666;
  
  --color-accent: #00d4ff;
  --color-accent-hover: #00b8e6;
  
  --color-border: #3a3a3a;
  --color-divider: #2a2a2a;
  
  --color-success: #4caf50;
  --color-warning: #ff9800;
  --color-error: #f44336;
  
  /* Spacing */
  --spacing-xs: 4px;
  --spacing-sm: 8px;
  --spacing-md: 16px;
  --spacing-lg: 24px;
  --spacing-xl: 32px;
  
  /* Typography */
  --font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
  --font-size-sm: 12px;
  --font-size-md: 14px;
  --font-size-lg: 16px;
  
  /* Layout */
  --header-height: 40px;
  --status-bar-height: 24px;
}

* {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}

body {
  font-family: var(--font-family);
  font-size: var(--font-size-md);
  color: var(--color-text-primary);
  background: var(--color-bg-primary);
  overflow: hidden;
}
```

### 4.2 TypeScript Types

**`src/types/octane.ts`**
```typescript
export interface SceneNode {
  id: string;
  name: string;
  type: string;
  visible: boolean;
  children: SceneNode[];
}

export interface Vector3 {
  x: number;
  y: number;
  z: number;
}

export interface RenderStats {
  samples: number;
  renderTime: number;
  fps: number;
}

export interface NodeParameter {
  name: string;
  type: 'number' | 'color' | 'boolean' | 'string' | 'enum';
  value: any;
  min?: number;
  max?: number;
  options?: string[];
}
```

### 4.3 Connection Store

**`src/store/connectionStore.ts`**
```typescript
import { create } from 'zustand';

interface ConnectionState {
  isConnected: boolean;
  isConnecting: boolean;
  serverUrl: string;
  error: string | null;
  
  setConnected: (connected: boolean) => void;
  setConnecting: (connecting: boolean) => void;
  setError: (error: string | null) => void;
  setServerUrl: (url: string) => void;
}

export const useConnectionStore = create<ConnectionState>((set) => ({
  isConnected: false,
  isConnecting: false,
  serverUrl: 'http://localhost:51023',
  error: null,
  
  setConnected: (connected) => set({ isConnected: connected }),
  setConnecting: (connecting) => set({ isConnecting: connecting }),
  setError: (error) => set({ error }),
  setServerUrl: (url) => set({ serverUrl: url }),
}));
```

### 4.4 API Client

**`src/api/OctaneClient.ts`**
```typescript
import { SceneNode, Vector3, NodeParameter } from '@/types/octane';

class OctaneClient {
  private baseUrl: string;
  
  constructor(baseUrl: string) {
    this.baseUrl = baseUrl;
  }
  
  private async request<T>(endpoint: string, data?: any): Promise<T> {
    const response = await fetch(`${this.baseUrl}/${endpoint}`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: data ? JSON.stringify(data) : undefined,
    });
    
    if (!response.ok) {
      throw new Error(`API Error: ${response.statusText}`);
    }
    
    return response.json();
  }
  
  // Connection
  async ping(): Promise<boolean> {
    try {
      await this.request('ping');
      return true;
    } catch {
      return false;
    }
  }
  
  // Scene Management
  async getSceneTree(): Promise<SceneNode[]> {
    return this.request<SceneNode[]>('buildSceneTree');
  }
  
  async setNodeVisibility(id: string, visible: boolean): Promise<void> {
    return this.request('setNodeVisibility', { id, visible });
  }
  
  // Camera Control
  async setCameraPosition(position: Vector3): Promise<void> {
    return this.request('setCameraPosition', position);
  }
  
  async setCameraTarget(target: Vector3): Promise<void> {
    return this.request('setCameraTarget', target);
  }
  
  // Node Parameters
  async getNodeParameters(nodeId: string): Promise<NodeParameter[]> {
    return this.request<NodeParameter[]>('getNodeParameters', { nodeId });
  }
  
  async setNodeParameter(nodeId: string, paramName: string, value: any): Promise<void> {
    return this.request('setNodeParameter', { nodeId, paramName, value });
  }
}

// Singleton instance
export const octaneClient = new OctaneClient('http://localhost:51023');
```

### 4.5 Main App Component

**`src/App.tsx`**
```typescript
import { QueryClient, QueryClientProvider } from '@tanstack/react-query';
import { MainLayout } from './components/layout/MainLayout';
import './styles/variables.css';

const queryClient = new QueryClient({
  defaultOptions: {
    queries: {
      refetchOnWindowFocus: false,
      retry: 1,
      staleTime: 5000,
    },
  },
});

function App() {
  return (
    <QueryClientProvider client={queryClient}>
      <MainLayout />
    </QueryClientProvider>
  );
}

export default App;
```

### 4.6 Main Layout

**`src/components/layout/MainLayout.tsx`**
```typescript
import { MenuBar } from './MenuBar';
import { StatusBar } from './StatusBar';
import './MainLayout.css';

export const MainLayout = () => {
  return (
    <div className="app-container">
      <MenuBar />
      
      <main className="app-layout">
        <aside className="left-panel">
          <div className="panel-header">
            <h3>Scene Outliner</h3>
          </div>
          <div className="panel-content">
            {/* SceneOutliner will go here */}
            <div>Scene tree coming soon...</div>
          </div>
        </aside>
        
        <section className="center-panel">
          <div className="viewport-header">
            <div className="viewport-title">Render Viewport</div>
          </div>
          <div className="viewport-container">
            {/* RenderViewport will go here */}
            <canvas style={{ width: '100%', height: '100%', background: '#2a2a2a' }} />
          </div>
        </section>
        
        <aside className="right-panel">
          <div className="panel-header">
            <h3>Node Inspector</h3>
          </div>
          <div className="panel-content">
            {/* NodeInspector will go here */}
            <div className="empty-message">Empty</div>
          </div>
        </aside>
      </main>
      
      <StatusBar />
    </div>
  );
};
```

**`src/components/layout/MainLayout.css`**
```css
.app-container {
  display: flex;
  flex-direction: column;
  height: 100vh;
  overflow: hidden;
}

.app-layout {
  display: grid;
  grid-template-columns: 300px 1fr 300px;
  flex: 1;
  overflow: hidden;
  gap: 1px;
  background: var(--color-divider);
}

.left-panel,
.right-panel {
  background: var(--color-bg-secondary);
  display: flex;
  flex-direction: column;
  overflow: hidden;
}

.center-panel {
  background: var(--color-bg-primary);
  display: flex;
  flex-direction: column;
  overflow: hidden;
}

.panel-header {
  padding: var(--spacing-sm) var(--spacing-md);
  border-bottom: 1px solid var(--color-border);
  background: var(--color-bg-tertiary);
}

.panel-header h3 {
  font-size: var(--font-size-md);
  font-weight: 500;
  color: var(--color-text-primary);
}

.panel-content {
  flex: 1;
  overflow: auto;
  padding: var(--spacing-sm);
}

.viewport-header {
  padding: var(--spacing-sm) var(--spacing-md);
  border-bottom: 1px solid var(--color-border);
  background: var(--color-bg-secondary);
}

.viewport-title {
  font-size: var(--font-size-sm);
  color: var(--color-text-secondary);
}

.viewport-container {
  flex: 1;
  position: relative;
  overflow: hidden;
  display: flex;
  align-items: center;
  justify-content: center;
}

.empty-message {
  text-align: center;
  padding: var(--spacing-lg);
  color: var(--color-text-disabled);
}
```

### 4.7 Menu Bar

**`src/components/layout/MenuBar.tsx`**
```typescript
import { useConnectionStore } from '@/store/connectionStore';
import { octaneClient } from '@/api/OctaneClient';
import './MenuBar.css';

export const MenuBar = () => {
  const { isConnected, isConnecting, setConnected, setConnecting, setError } = useConnectionStore();
  
  const handleConnect = async () => {
    setConnecting(true);
    setError(null);
    
    try {
      const connected = await octaneClient.ping();
      setConnected(connected);
      if (!connected) {
        setError('Failed to connect to Octane LiveLink');
      }
    } catch (error) {
      setError(error instanceof Error ? error.message : 'Connection failed');
      setConnected(false);
    } finally {
      setConnecting(false);
    }
  };
  
  return (
    <header className="menu-bar">
      <nav className="main-menu">
        <div className="menu-item">File</div>
        <div className="menu-item">Edit</div>
        <div className="menu-item">Script</div>
        <div className="menu-item">Module</div>
        <div className="menu-item">Cloud</div>
        <div className="menu-item">Window</div>
        <div className="menu-item">Help</div>
      </nav>
      
      <div className="connection-status">
        <button 
          className="connect-btn"
          onClick={handleConnect}
          disabled={isConnecting}
        >
          {isConnecting ? 'Connecting...' : isConnected ? 'Connected' : 'Connect'}
        </button>
        <div className={`status-indicator ${isConnected ? 'connected' : 'disconnected'}`}>
          <span className="status-dot" />
          <span className="status-text">
            {isConnected ? 'Connected' : 'Disconnected'}
          </span>
        </div>
      </div>
    </header>
  );
};
```

**`src/components/layout/MenuBar.css`**
```css
.menu-bar {
  height: var(--header-height);
  background: var(--color-bg-secondary);
  border-bottom: 1px solid var(--color-border);
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0 var(--spacing-md);
}

.main-menu {
  display: flex;
  gap: var(--spacing-sm);
}

.menu-item {
  padding: var(--spacing-sm) var(--spacing-md);
  cursor: pointer;
  font-size: var(--font-size-sm);
  color: var(--color-text-primary);
  transition: background-color 0.2s;
}

.menu-item:hover {
  background: var(--color-bg-hover);
}

.connection-status {
  display: flex;
  align-items: center;
  gap: var(--spacing-md);
}

.connect-btn {
  padding: var(--spacing-xs) var(--spacing-md);
  background: var(--color-accent);
  color: white;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  font-size: var(--font-size-sm);
  transition: background-color 0.2s;
}

.connect-btn:hover:not(:disabled) {
  background: var(--color-accent-hover);
}

.connect-btn:disabled {
  opacity: 0.5;
  cursor: not-allowed;
}

.status-indicator {
  display: flex;
  align-items: center;
  gap: var(--spacing-xs);
}

.status-dot {
  width: 8px;
  height: 8px;
  border-radius: 50%;
  background: var(--color-error);
}

.status-indicator.connected .status-dot {
  background: var(--color-success);
}

.status-text {
  font-size: var(--font-size-sm);
  color: var(--color-text-secondary);
}
```

### 4.8 Status Bar

**`src/components/layout/StatusBar.tsx`**
```typescript
import { useConnectionStore } from '@/store/connectionStore';
import './StatusBar.css';

export const StatusBar = () => {
  const isConnected = useConnectionStore(state => state.isConnected);
  
  return (
    <footer className="status-bar">
      <div className="status-left">
        <span className="status-item">Ready</span>
      </div>
      <div className="status-center">
        <span className="status-item">OctaneWeb2 - React Edition</span>
      </div>
      <div className="status-right">
        <span className="status-item">
          Octane: {isConnected ? 'Connected' : 'Disconnected'}
        </span>
        <span className="status-item">FPS: 0</span>
      </div>
    </footer>
  );
};
```

**`src/components/layout/StatusBar.css`**
```css
.status-bar {
  height: var(--status-bar-height);
  background: var(--color-bg-tertiary);
  border-top: 1px solid var(--color-border);
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0 var(--spacing-md);
}

.status-left,
.status-center,
.status-right {
  display: flex;
  gap: var(--spacing-md);
  align-items: center;
}

.status-item {
  font-size: var(--font-size-sm);
  color: var(--color-text-secondary);
}
```

### 4.9 Update main.tsx

**`src/main.tsx`**
```typescript
import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App.tsx'

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
)
```

### 4.10 Update index.html

**`index.html`**
```html
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>OctaneRender Studio - Web Edition (React)</title>
  </head>
  <body>
    <div id="root"></div>
    <script type="module" src="/src/main.tsx"></script>
  </body>
</html>
```

## Step 5: Run the Application

```bash
# Make sure you're in octaneWeb2 directory
cd /workspace/grpcSamples/octaneWeb2

# Start the dev server
npm run dev
```

The application should now be running at http://localhost:42219

## Step 6: Start the Python Proxy

In a separate terminal:

```bash
cd /workspace/grpcSamples/octaneWeb

# Start the proxy server (it will handle both old and new frontends)
./start_servers.bat  # or use the appropriate command for your OS
```

## Step 7: Connect to Octane

1. Make sure Octane is running
2. Enable LiveLink in Octane: Help → LiveLink
3. Click "Connect" button in the octaneWeb2 interface
4. Status should change to "Connected" with a green indicator

## Next Steps

Now that you have the basic skeleton running, you can implement components one by one:

### Phase 1: Scene Outliner
1. Create `SceneOutliner.tsx` component
2. Create `useSceneTree` hook
3. Implement recursive tree rendering
4. Add expand/collapse functionality

### Phase 2: Render Viewport
1. Create `RenderViewport.tsx` component
2. Implement callback streaming hook
3. Add canvas rendering
4. Implement mouse drag camera controls

### Phase 3: Node Inspector
1. Create `NodeInspector.tsx` component
2. Create parameter editing controls
3. Implement live updates to Octane

### Phase 4: Node Graph Editor
1. Create canvas-based node graph
2. Implement node creation and connections
3. Add pan/zoom functionality

## Useful Commands

```bash
# Development
npm run dev          # Start dev server
npm run build        # Build for production
npm run preview      # Preview production build

# Code Quality
npm run lint         # Run ESLint
npm run type-check   # Check TypeScript types
```

## Debugging

1. **React DevTools**: Install browser extension for component inspection
2. **Zustand DevTools**: Already included in dev mode
3. **React Query DevTools**: Import and add to App.tsx:
```typescript
import { ReactQueryDevtools } from '@tanstack/react-query-devtools';

// In App.tsx
<QueryClientProvider client={queryClient}>
  <MainLayout />
  <ReactQueryDevtools initialIsOpen={false} />
</QueryClientProvider>
```

## Troubleshooting

### Port Already in Use
```bash
# Kill process on port 42219
npx kill-port 42219
```

### Proxy Connection Fails
- Make sure Python proxy is running on port 51023
- Check firewall settings
- Verify Octane LiveLink is enabled

### Module Not Found
```bash
# Clear node_modules and reinstall
rm -rf node_modules package-lock.json
npm install
```

## Resources

- **React Docs**: https://react.dev
- **TypeScript**: https://www.typescriptlang.org/docs
- **Zustand**: https://github.com/pmndrs/zustand
- **React Query**: https://tanstack.com/query/latest/docs/react
- **Vite**: https://vitejs.dev

## Next Documentation

Refer to:
- `OCTANEWEB2_REACT_REBUILD_PLAN.md` - Complete implementation plan
- `OCTANEWEB2_ARCHITECTURE.md` - Architecture details
- `OCTANEWEB2_IMPROVEMENTS.md` - Code improvement examples

Happy coding! 🚀
