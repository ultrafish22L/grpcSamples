/**
 * OctaneWebR - React TypeScript Main Application
 * Port of octaneWeb with identical UI and functionality
 */

import React, { useEffect, useState } from 'react';
import { OctaneProvider, useOctane } from './hooks/useOctane';
import { ConnectionStatus } from './components/ConnectionStatus';
import { CallbackRenderViewport } from './components/CallbackRenderViewport';
import { SceneOutliner } from './components/SceneOutliner';
import { NodeInspector } from './components/NodeInspector';
import { SceneNode } from './services/OctaneClient';

function AppContent() {
  const { connect, connected } = useOctane();
  const [selectedNode, setSelectedNode] = useState<SceneNode | null>(null);

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
    <div className="octane-app">
      <header className="app-header">
        <div className="app-title">
          <h1>OctaneWebR</h1>
          <span className="app-subtitle">React TypeScript + Node.js gRPC</span>
        </div>
        <ConnectionStatus />
      </header>

      <main className="app-main">
        <div className="viewport-container">
          {connected ? (
            <CallbackRenderViewport />
          ) : (
            <div className="viewport-overlay">
              <div className="status-message">
                <h2>Connecting to Octane...</h2>
                <p>Ensure Octane LiveLink is enabled (Help → LiveLink)</p>
              </div>
            </div>
          )}
        </div>

        <aside className="side-panel">
          <div className="panel-section">
            <SceneOutliner />
          </div>

          <div className="panel-section">
            <NodeInspector node={selectedNode} />
          </div>
        </aside>
      </main>

      <footer className="app-footer">
        <span className="footer-info">
          Server: http://localhost:51024 | Octane: localhost:51022
        </span>
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
