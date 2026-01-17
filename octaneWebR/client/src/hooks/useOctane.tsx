/**
 * React hooks and context for Octane client
 */

import React, { createContext, useContext, useEffect, useState, useCallback } from 'react';
import { OctaneClient, getOctaneClient, RenderState, Scene, NodeAddedEvent } from '../services/OctaneClient';

interface OctaneContextValue {
  client: OctaneClient;
  connected: boolean;
  scene: Scene | null;
  renderState: RenderState;
  connect: () => Promise<boolean>;
  disconnect: () => Promise<void>;
}

const OctaneContext = createContext<OctaneContextValue | null>(null);

export function OctaneProvider({ children }: { children: React.ReactNode }) {
  const [client] = useState(() => getOctaneClient());
  const [connected, setConnected] = useState(false);
  const [scene, setScene] = useState<Scene | null>(null);
  const [renderState, setRenderState] = useState<RenderState>({
    isRendering: false,
    progress: 0,
    samples: 0,
    renderTime: 0,
    resolution: { width: 1920, height: 1080 }
  });

  useEffect(() => {
    console.log('🎯 useOctane: Setting up event listeners for client');
    
    // Setup event listeners
    const handleConnected = () => {
      console.log('🎯 useOctane: handleConnected called, setting connected = true');
      setConnected(true);
    };
    const handleDisconnected = () => {
      console.log('🎯 useOctane: handleDisconnected called, setting connected = false');
      setConnected(false);
    };
    const handleSceneTreeUpdated = (newScene: Scene) => {
      console.log('🎯 useOctane: handleSceneTreeUpdated called with', newScene.tree.length, 'items');
      setScene(newScene);
    };
    const handleNodeAdded = (event: NodeAddedEvent) => {
      console.log('🎯 useOctane: handleNodeAdded called for node:', event.node.name, 'handle:', event.handle);
      // Incremental update - just update the scene reference to trigger re-render
      // The scene object itself was already mutated by OctaneClient.buildSceneTree
      setScene(prevScene => {
        if (!prevScene) return prevScene;
        // Create a shallow copy to trigger React re-render
        return { ...prevScene, tree: [...prevScene.tree] };
      });
    };
    const handleRenderStateChanged = (newState: RenderState) => {
      console.log('🎯 useOctane: handleRenderStateChanged called');
      setRenderState(newState);
    };

    client.on('connected', handleConnected);
    client.on('disconnected', handleDisconnected);
    client.on('sceneTreeUpdated', handleSceneTreeUpdated);
    client.on('nodeAdded', handleNodeAdded);
    client.on('renderStateChanged', handleRenderStateChanged);

    console.log('🎯 useOctane: Event listeners registered');

    // Cleanup
    return () => {
      client.off('connected', handleConnected);
      client.off('disconnected', handleDisconnected);
      client.off('sceneTreeUpdated', handleSceneTreeUpdated);
      client.off('nodeAdded', handleNodeAdded);
      client.off('renderStateChanged', handleRenderStateChanged);
    };
  }, [client]);

  const connect = useCallback(async () => {
    return await client.connect();
  }, [client]);

  const disconnect = useCallback(async () => {
    await client.disconnect();
  }, [client]);

  const value: OctaneContextValue = {
    client,
    connected,
    scene,
    renderState,
    connect,
    disconnect
  };

  return <OctaneContext.Provider value={value}>{children}</OctaneContext.Provider>;
}

export function useOctane() {
  const context = useContext(OctaneContext);
  if (!context) {
    throw new Error('useOctane must be used within OctaneProvider');
  }
  return context;
}
