/**
 * OctaneWebR - React TypeScript Main Application
 * Port of octaneWeb with identical UI and functionality
 * 
 * Layout Structure (matching octaneWeb exactly):
 * - Menu Bar (top)
 * - App Layout (grid):
 *   - Left Panel: Scene Outliner
 *   - Center Panel: Render Viewport + Render Toolbar
 *   - Right Panel: Node Inspector
 *   - Bottom Panel: Node Graph Editor
 * - Status Bar (bottom)
 */

import { useEffect, useState } from 'react';
import { OctaneProvider, useOctane } from './hooks/useOctane';
import { useResizablePanels } from './hooks/useResizablePanels';
import { ConnectionStatus } from './components/ConnectionStatus';
import { CallbackRenderViewport } from './components/CallbackRenderViewport';
import { SceneOutliner } from './components/SceneOutliner';
import { NodeInspector } from './components/NodeInspector';
import { NodeGraphEditor } from './components/NodeGraphEditor';
import { SceneNode } from './services/OctaneClient';

function AppContent() {
  const { connect, connected } = useOctane();
  const [selectedNode, setSelectedNode] = useState<SceneNode | null>(null);
  const { panelSizes, handleSplitterMouseDown, containerRef, isDragging } = useResizablePanels();

  useEffect(() => {
    // Auto-connect on mount
    console.log('🚀 OctaneWebR starting...');
    connect().then(success => {
      if (success) {
        console.log('✅ Auto-connected to server');
      } else {
        console.log('⚠️ Could not connect to server');
      }
    });
  }, [connect]);

  return (
    <div className="app-container">
      {/* Top Menu Bar */}
      <header className="menu-bar">
        <nav className="main-menu">
          <div className="menu-item" data-menu="file">File</div>
          <div className="menu-item" data-menu="edit">Edit</div>
          <div className="menu-item" data-menu="script">Script</div>
          <div className="menu-item" data-menu="module">Module</div>
          <div className="menu-item" data-menu="cloud">Cloud</div>
          <div className="menu-item" data-menu="window">Window</div>
          <div className="menu-item" data-menu="help">Help</div>
        </nav>
        
        {/* Connection Status & Controls */}
        <ConnectionStatus />
      </header>

      {/* Main Application Layout */}
      <main 
        ref={containerRef}
        className={`app-layout ${isDragging ? 'resizing' : ''}`}
        style={{
          gridTemplateColumns: `${panelSizes.left}px 4px 1fr 4px ${panelSizes.right}px`,
          gridTemplateRows: `1fr 4px ${panelSizes.bottom}px`,
        }}
      >
        
        {/* Left Panel: Scene Outliner */}
        <aside className="left-panel panel">
          <div className="panel-header">
            <h3>Scene outliner</h3>
          </div>
          <div className="panel-content">
            <SceneOutliner onNodeSelect={setSelectedNode} />
          </div>
        </aside>

        {/* Left Splitter - between Scene Outliner and Center */}
        <div 
          className="panel-splitter vertical left-splitter"
          onMouseDown={() => handleSplitterMouseDown('left')}
        />

        {/* Center Panel: Render Viewport */}
        <section className="center-panel">
          <div className="viewport-header">
            <div className="viewport-title">Render viewport - Render target @ 100%</div>
            <div className="viewport-controls">
              <button className="viewport-btn" title="Fit to Window">⊞</button>
              <button className="viewport-btn" title="Actual Size">1:1</button>
              <button className="viewport-btn" title="Zoom In">🔍+</button>
              <button className="viewport-btn" title="Zoom Out">🔍-</button>
            </div>
          </div>
          
          <div className="viewport-container">
            {connected ? (
              <CallbackRenderViewport />
            ) : (
              <div className="viewport-overlay">
                <div className="viewport-info">
                  <h2>Connecting to Octane...</h2>
                  <p>Ensure Octane LiveLink is enabled (Help → LiveLink)</p>
                </div>
              </div>
            )}
          </div>
          
          {/* Render Toolbar will go here */}
          <div className="render-toolbar-container">
            {/* TODO: Port RenderToolbar component */}
          </div>
        </section>

        {/* Right Splitter - between Center and Node Inspector */}
        <div 
          className="panel-splitter vertical right-splitter"
          onMouseDown={() => handleSplitterMouseDown('right')}
        />

        {/* Right Panel: Node Inspector */}
        <aside className="right-panel panel">
          <div className="panel-header">
            <h3>Node inspector</h3>
          </div>
          <div className="panel-content">
            <NodeInspector node={selectedNode} />
          </div>
        </aside>

        {/* Horizontal Splitter - between top panels and Node Graph Editor */}
        <div 
          className="panel-splitter horizontal bottom-splitter"
          onMouseDown={() => handleSplitterMouseDown('bottom')}
          style={{ gridColumn: '1 / -1' }}
        />

        {/* Bottom Panel: Node Graph Editor */}
        <section className="bottom-panel panel">
          <div className="node-graph-header">
            <h3>Node graph editor</h3>
            <div className="node-graph-controls">
              <button className="node-btn" title="Add Node">+</button>
              <button className="node-btn" title="Delete Node">🗑</button>
              <button className="node-btn" title="Fit All">⊞</button>
            </div>
          </div>
          <div className="node-graph-container">
            <NodeGraphEditor selectedNode={selectedNode} />
          </div>
        </section>
        
      </main>

      {/* Status Bar */}
      <footer className="status-bar">
        <div className="status-left">
          <span className="status-item">Ready</span>
        </div>
        <div className="status-center">
          <span className="status-item">OctaneWebR - React TypeScript + Node.js gRPC</span>
        </div>
        <div className="status-right">
          <span className="status-item">OctaneLive: <span id="octane-status">{connected ? 'connected' : 'disconnected'}</span></span>
          <span className="status-item">FPS: <span id="fps-counter">0</span></span>
        </div>
      </footer>
    </div>
  );
}

function App() {
  return (
    <OctaneProvider>
      <AppContent />
    </OctaneProvider>
  );
}

export default App;
