/**
 * OctaneWebR - React TypeScript Main Application
 * Port of octaneWeb with identical UI and functionality
 * 
 * Layout Structure (matching octaneWeb exactly):
 * - Menu Bar (top)
 * - App Layout (5-column x 3-row grid):
 *   - Column 1 (full height): Scene Outliner
 *   - Column 2 (full height): Left vertical splitter
 *   - Column 3 (2 rows): Render Viewport (top) + horizontal splitter + Node Graph Editor (bottom)
 *   - Column 4 (full height): Right vertical splitter
 *   - Column 5 (full height): Node Inspector
 * - Status Bar (bottom)
 */

import { useEffect, useState, useRef } from 'react';
import { OctaneProvider, useOctane } from './hooks/useOctane';
import { useResizablePanels } from './hooks/useResizablePanels';
import { MenuBar } from './components/MenuBar';
import { ConnectionStatus } from './components/ConnectionStatus';
import { CallbackRenderViewport, CallbackRenderViewportHandle } from './components/CallbackRenderViewport';
import { RenderToolbar } from './components/RenderToolbar';
import { SceneOutliner } from './components/SceneOutliner';
import { NodeInspector } from './components/NodeInspector';
import { NodeInspectorControls } from './components/NodeInspectorControls';
import { NodeGraphEditor } from './components/NodeGraph';
import { SceneNode } from './services/OctaneClient';
import { NodeType } from './constants/OctaneTypes';

function AppContent() {
  const { client, connect, connected } = useOctane();
  const [selectedNode, setSelectedNode] = useState<SceneNode | null>(null);
  const [sceneTree, setSceneTree] = useState<SceneNode[]>([]);
  const [sceneRefreshTrigger, setSceneRefreshTrigger] = useState(0);
  const [isSyncing, setIsSyncing] = useState(false);
  const [showWorldCoord, setShowWorldCoord] = useState(true); // Display world coordinate axis
  const [viewportLocked, setViewportLocked] = useState(false); // Lock viewport controls
  const { panelSizes, handleSplitterMouseDown, containerRef, isDragging } = useResizablePanels();
  const viewportRef = useRef<CallbackRenderViewportHandle>(null);

  // Scene tree change handler
  const handleSceneTreeChange = (tree: SceneNode[]) => {
    setSceneTree(tree);
  };

  // Scene sync state handler
  const handleSyncStateChange = (syncing: boolean) => {
    setIsSyncing(syncing);
    console.log(syncing ? '🔄 Scene sync started...' : '✅ Scene sync complete');
  };

  // Scene refresh handler for MenuBar
  const handleSceneRefresh = () => {
    setSceneRefreshTrigger(prev => prev + 1);
  };

  // Add Node button handler - creates geometric plane primitive
  const handleAddNode = async () => {
    if (!connected || !client) {
      console.log('⚠️ Cannot create node: not connected to Octane');
      return;
    }

    if (isSyncing) {
      console.log('⚠️ Cannot create node: scene is currently syncing');
      return;
    }

    console.log('➕ Creating geometric plane primitive...');
    
    try {
      const createdHandle = await client.createNode('NT_GEO_PLANE', NodeType.NT_GEO_PLANE);
      if (createdHandle) {
        console.log('✅ Geometric plane created with handle:', createdHandle);
        // Note: UI will auto-refresh via sceneUpdated event listener
      } else {
        console.error('❌ Failed to create geometric plane');
      }
    } catch (error) {
      console.error('❌ Error creating node:', error);
    }
  };

  // Copy render to clipboard handler
  const handleCopyToClipboard = async () => {
    if (!viewportRef.current) {
      console.warn('⚠️ Viewport not available for clipboard copy');
      return;
    }

    try {
      await viewportRef.current.copyToClipboard();
    } catch (error) {
      console.error('❌ Failed to copy to clipboard:', error);
    }
  };

  // Save render to disk handler
  const handleSaveRender = async () => {
    if (!viewportRef.current) {
      console.warn('⚠️ Viewport not available for save render');
      return;
    }

    try {
      await viewportRef.current.saveRenderToDisk();
    } catch (error) {
      console.error('❌ Failed to save render:', error);
    }
  };

  // Viewport lock change handler
  const handleViewportLockChange = (locked: boolean) => {
    setViewportLocked(locked);
    console.log(`🔒 App.tsx: Viewport lock ${locked ? 'enabled' : 'disabled'}`);
  };

  useEffect(() => {
    // Auto-connect on mount
    console.log('🚀 OctaneWebR starting...');
    connect().then(success => {
      if (success) {
        console.log('✅ Auto-connected to server');
      } else {
        console.log('⚠️ Could not connect to server');
      }
    }).catch(error => {
      console.error('❌ App.tsx: connect() threw error:', error);
    });
  }, [connect]);

  // Listen for scene updates (node deletions, additions, etc.)
  useEffect(() => {
    if (!client) return;

    const handleSceneUpdated = (scene: any) => {
      console.log('🔄 Scene updated - refreshing UI components');
      
      // Update scene tree from client's internal state
      const updatedTree = scene.tree || [];
      setSceneTree(updatedTree);
      
      // Trigger SceneOutliner refresh (force re-mount to sync its internal state)
      setSceneRefreshTrigger(prev => prev + 1);
      
      // If selected node was deleted, clear selection (Node Inspector behavior)
      setSelectedNode(current => {
        if (current && !scene.map?.has(current.handle)) {
          console.log('⚠️ Selected node was deleted - clearing selection');
          return null;
        }
        return current;
      });
    };

    // Listen for scene updates (emitted by deleteNodeOptimized, etc.)
    client.on('sceneUpdated', handleSceneUpdated);
    
    console.log('✅ Listening for sceneUpdated events');

    // Cleanup listener on unmount
    return () => {
      client.off('sceneUpdated', handleSceneUpdated);
      console.log('🔇 Stopped listening for sceneUpdated events');
    };
  }, [client]); // Only re-register when client changes, not on every selection

  return (
    <div className="app-container">
      {/* Top Menu Bar */}
      <header className="menu-bar">
        <MenuBar onSceneRefresh={handleSceneRefresh} />
        
        {/* Connection Status & Controls */}
        <ConnectionStatus />
      </header>

      {/* Main Application Layout */}
      <main 
        ref={containerRef}
        className={`app-layout ${isDragging ? 'resizing' : ''}`}
        style={{
          gridTemplateColumns: `${panelSizes.left}px 4px 1fr 4px ${panelSizes.right}px`,
          gridTemplateRows: `${panelSizes.top}px 4px 1fr`,
        }}
      >
        
        {/* Left Panel: Scene Outliner - spans ALL rows (full height to bottom) */}
        <aside className="left-panel panel" style={{ gridRow: '1 / -1' }}>
          <div className="panel-header">
            <h3>Scene outliner</h3>
          </div>
          <div className="panel-content">
            <SceneOutliner 
              key={sceneRefreshTrigger}
              selectedNode={selectedNode}
              onNodeSelect={setSelectedNode}
              onSceneTreeChange={handleSceneTreeChange}
              onSyncStateChange={handleSyncStateChange}
            />
          </div>
        </aside>

        {/* Left Splitter - spans ALL rows (full height) */}
        <div 
          className="panel-splitter vertical left-splitter"
          onMouseDown={() => handleSplitterMouseDown('left')}
          style={{ gridRow: '1 / -1' }}
        />

        {/* Center Panel: Render Viewport - ROW 1, COLUMN 3 (top section of center column) */}
        <section className="center-panel" style={{ gridColumn: '3 / 4', gridRow: '1 / 2' }}>
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
              <CallbackRenderViewport 
                ref={viewportRef} 
                showWorldCoord={showWorldCoord} 
                viewportLocked={viewportLocked}
              />
            ) : (
              <div className="viewport-overlay">
                <div className="viewport-info">
                  <h2>Connecting to Octane...</h2>
                  <p>Ensure Octane LiveLink is enabled (Help → LiveLink)</p>
                </div>
              </div>
            )}
          </div>
          
          {/* Render Toolbar - Official Octane viewport controls */}
          <RenderToolbar 
            onToggleWorldCoord={() => setShowWorldCoord(!showWorldCoord)} 
            onCopyToClipboard={handleCopyToClipboard}
            onSaveRender={handleSaveRender}
            onViewportLockChange={handleViewportLockChange}
          />
        </section>

        {/* Center-Right Splitter - spans ALL rows (full height) */}
        <div 
          className="panel-splitter vertical center-right-splitter"
          onMouseDown={() => handleSplitterMouseDown('right')}
          style={{ gridRow: '1 / -1' }}
        />

        {/* Right Panel: Node Inspector - spans ALL rows (full height to bottom) */}
        <aside className="right-panel panel" style={{ gridRow: '1 / -1' }}>
          <div className="panel-header">
            <h3>Node inspector</h3>
          </div>
          <div className="panel-content">
            <div className="node-inspector-layout">
              <NodeInspectorControls 
                sceneTree={sceneTree}
                onNodeSelect={setSelectedNode}
              />
              <div className="node-inspector-main">
                <NodeInspector node={selectedNode} />
              </div>
            </div>
          </div>
        </aside>

        {/* Horizontal Splitter - ROW 2, COLUMN 3 ONLY (under Viewport only) */}
        <div 
          className="panel-splitter horizontal top-bottom-splitter"
          onMouseDown={() => handleSplitterMouseDown('top')}
          style={{ gridColumn: '3 / 4' }}
        />

        {/* Bottom Panel: Node Graph Editor - ROW 3, COLUMN 3 ONLY (under Viewport only) */}
        <section className="bottom-panel panel" style={{ gridColumn: '3 / 4' }}>
          <div className="node-graph-header">
            <h3>Node graph editor</h3>
            <div className="node-graph-controls">
              <button 
                className="node-btn" 
                title={isSyncing ? "Cannot add node while syncing" : "Add Node"} 
                onClick={handleAddNode}
                disabled={!connected || isSyncing}
              >+</button>
              <button className="node-btn" title="Delete Node">🗑</button>
              <button className="node-btn" title="Fit All">⊞</button>
            </div>
          </div>
          <div className="node-graph-container">
            <NodeGraphEditor 
              sceneTree={sceneTree} 
              selectedNode={selectedNode}
              onNodeSelect={setSelectedNode} 
            />
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
