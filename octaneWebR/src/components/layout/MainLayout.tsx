import React, { useEffect } from 'react';
import { useSceneStore } from '../../store/sceneStore';
import { octaneClient } from '../../api/octaneClient';
import MenuBar from './MenuBar';
import SceneOutliner from '../panels/SceneOutliner';
import RenderViewport from '../panels/RenderViewport';
import NodeInspector from '../panels/NodeInspector';
import NodeGraphEditor from '../panels/NodeGraphEditor';
import StatusBar from './StatusBar';

export const MainLayout: React.FC = () => {
  const { connected, setConnected, loadScene } = useSceneStore();
  const [connecting, setConnecting] = React.useState(false);

  const handleConnect = async () => {
    setConnecting(true);
    try {
      const isConnected = await octaneClient.checkHealth();
      setConnected(isConnected);
      if (isConnected) {
        await loadScene();
      }
    } catch (error) {
      console.error('Connection failed:', error);
      setConnected(false);
    } finally {
      setConnecting(false);
    }
  };

  const handleDisconnect = () => {
    setConnected(false);
  };

  // Auto-connect on mount
  useEffect(() => {
    handleConnect();
  }, []);

  return (
    <div className="app-container">
      <MenuBar
        connected={connected}
        connecting={connecting}
        onConnect={handleConnect}
        onDisconnect={handleDisconnect}
      />
      
      <main className="main-content">
        <aside className="scene-outliner">
          <SceneOutliner connected={connected} />
        </aside>

        <section className="center-panels">
          <div className="render-viewport">
            <RenderViewport connected={connected} />
          </div>
          
          <div className="node-graph-editor">
            <NodeGraphEditor connected={connected} />
          </div>
        </section>

        <aside className="node-inspector">
          <NodeInspector connected={connected} />
        </aside>
      </main>

      <StatusBar connected={connected} />
    </div>
  );
};
