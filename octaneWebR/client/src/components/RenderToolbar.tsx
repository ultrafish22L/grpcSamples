/**
 * RenderToolbar.tsx - React/TypeScript port of octaneWeb's RenderToolbar.js
 * Official Octane-style render toolbar component with render statistics and viewport controls
 * Located below the render viewport, above the node graph editor
 */

import { useState, useEffect } from 'react';
import { useOctane } from '../hooks/useOctane';

interface RenderStats {
  samples: number;
  time: string;
  status: 'rendering' | 'finished' | 'paused' | 'stopped' | 'error';
  resolution: string;
  meshCount: number;
  gpu: string;
  version: string;
  memory: string;
}

interface ToolbarState {
  realTimeMode: boolean;
  viewportLocked: boolean;
  clayMode: boolean;
  subSampling: 'none' | '2x2' | '4x4';
  renderPriority: 'low' | 'normal' | 'high';
  currentPickingMode: 'none' | 'focus' | 'whiteBalance' | 'material' | 'object' | 'cameraTarget' | 'renderRegion' | 'filmRegion';
  decalWireframe: boolean;
  worldCoordinateDisplay: boolean;
  objectControlMode: 'world' | 'local';
  activeGizmo: 'none' | 'translate' | 'rotate' | 'scale';
  viewportResolutionLock: boolean;
}

interface RenderToolbarProps {
  className?: string;
  onToggleWorldCoord?: () => void;
  onCopyToClipboard?: () => void;
  onSaveRender?: () => void;
  onViewportLockChange?: (locked: boolean) => void;
}

export function RenderToolbar({ className = '', onToggleWorldCoord, onCopyToClipboard, onSaveRender, onViewportLockChange }: RenderToolbarProps) {
  const { connected, client } = useOctane();
  
  const [renderStats, setRenderStats] = useState<RenderStats>({
    samples: 1.0,
    time: '00:00:00',
    status: 'finished',
    resolution: '1920x1080',
    meshCount: 1,
    gpu: 'NVIDIA GeForce RTX 4090 (RT)',
    version: '1:48.21.2',
    memory: '24.0 GB'
  });

  const [state, setState] = useState<ToolbarState>({
    realTimeMode: false,
    viewportLocked: false,
    clayMode: false,
    subSampling: 'none',
    renderPriority: 'normal',
    currentPickingMode: 'none',
    decalWireframe: false,
    worldCoordinateDisplay: true,
    objectControlMode: 'world',
    activeGizmo: 'none',
    viewportResolutionLock: false
  });

  // Initialize rendering settings from Octane on connect
  useEffect(() => {
    if (!connected) return;

    const initializeRenderSettings = async () => {
      try {
        // Initialize clay mode
        const clayModeValue = await client.getClayMode();
        setState(prev => ({ ...prev, clayMode: clayModeValue !== 0 }));
        console.log('🎨 Clay mode initialized:', clayModeValue === 0 ? 'OFF' : 'ON');

        // Initialize sub-sampling mode
        const subSampleValue = await client.getSubSampleMode();
        const subSamplingMode = subSampleValue === 2 ? '2x2' : subSampleValue === 4 ? '4x4' : 'none';
        setState(prev => ({ ...prev, subSampling: subSamplingMode }));
        console.log('📐 Sub-sampling initialized:', subSamplingMode.toUpperCase());

        // Initialize viewport resolution lock
        const resolutionLock = await client.getViewportResolutionLock();
        setState(prev => ({ ...prev, viewportResolutionLock: resolutionLock }));
        console.log('🔒 Viewport resolution lock initialized:', resolutionLock ? 'ON' : 'OFF');
      } catch (err) {
        console.error('❌ Failed to initialize render settings:', err);
      }
    };

    initializeRenderSettings();
  }, [connected, client]);

  // Listen for real-time render statistics from WebSocket callbacks
  useEffect(() => {
    if (!connected) return;
    
    const handleStatistics = (data: any) => {
      try {
        // Parse the statistics object from Octane callback
        // The statistics object contains setSize (resolution), usedSize, etc.
        const stats = data.statistics;
        if (stats) {
          const width = stats.setSize?.x || stats.setSize?.[0] || renderStats.resolution.split('x')[0];
          const height = stats.setSize?.y || stats.setSize?.[1] || renderStats.resolution.split('x')[1];
          const resolution = `${width}x${height}`;
          
          // Update render stats with real data from callback
          setRenderStats(prev => ({
            ...prev,
            resolution,
            // Add more fields as we parse the statistics object
          }));
        }
      } catch (error) {
        console.error('Failed to process render statistics:', error);
      }
    };

    // Subscribe to OnNewStatistics callback
    client.on('OnNewStatistics', handleStatistics);

    return () => {
      client.off('OnNewStatistics', handleStatistics);
    };
  }, [connected, client]);

  // ========================================
  // TOOLBAR ACTIONS
  // ========================================

  const handleToolbarAction = (actionId: string) => {
    console.log(`🔧 RenderToolbar action: ${actionId}`);

    switch (actionId) {
      // Camera & View Controls
      case 'recenter-view':
        console.log('Recenter view');
        // TODO: API call to recenter viewport
        break;
      case 'reset-camera':
        console.log('📷 Reset camera to original position');
        client.resetCamera().then(() => {
          console.log('✅ Camera reset successful');
        }).catch(err => {
          console.error('❌ Failed to reset camera:', err);
        });
        break;
      case 'camera-presets':
        console.log('Show camera presets menu');
        // TODO: Show camera presets dropdown
        break;

      // Render Controls
      case 'stop-render':
        console.log('🛑 Stop render');
        client.stopRender().then(() => {
          setRenderStats(prev => ({ ...prev, status: 'stopped' }));
        }).catch(err => {
          console.error('❌ Failed to stop render:', err);
        });
        break;
      case 'restart-render':
        console.log('🔄 Restart render');
        client.restartRender().then(() => {
          setRenderStats(prev => ({ ...prev, samples: 0, time: '00:00:00', status: 'rendering' }));
        }).catch(err => {
          console.error('❌ Failed to restart render:', err);
        });
        break;
      case 'pause-render':
        console.log('⏸️ Pause render');
        client.pauseRender().then(() => {
          setRenderStats(prev => ({ ...prev, status: 'paused' }));
        }).catch(err => {
          console.error('❌ Failed to pause render:', err);
        });
        break;
      case 'start-render':
        console.log('▶️ Start render');
        client.startRender().then(() => {
          setRenderStats(prev => ({ ...prev, status: 'rendering' }));
        }).catch(err => {
          console.error('❌ Failed to start render:', err);
        });
        break;
      case 'real-time-render':
        setState(prev => ({ ...prev, realTimeMode: !prev.realTimeMode }));
        console.log(`Real-time mode: ${!state.realTimeMode ? 'ON' : 'OFF'}`);
        // TODO: API call to toggle real-time rendering
        break;

      // Picking Tools
      case 'focus-picker':
        togglePickingMode('focus');
        break;
      case 'white-balance-picker':
        togglePickingMode('whiteBalance');
        break;
      case 'material-picker':
        togglePickingMode('material');
        break;
      case 'object-picker':
        togglePickingMode('object');
        break;
      case 'camera-target-picker':
        togglePickingMode('cameraTarget');
        break;

      // Region Tools
      case 'render-region-picker':
        togglePickingMode('renderRegion');
        break;
      case 'film-region-picker':
        togglePickingMode('filmRegion');
        break;

      // Rendering Settings
      case 'clay-mode':
        const newClayMode = !state.clayMode;
        setState(prev => ({ ...prev, clayMode: newClayMode }));
        console.log(`🎨 Clay mode: ${newClayMode ? 'ON' : 'OFF'}`);
        // CLAY_MODE_NONE = 0, CLAY_MODE_GREY = 1
        client.setClayMode(newClayMode ? 1 : 0).then(() => {
          console.log('✅ Clay mode updated in Octane');
        }).catch(err => {
          console.error('❌ Failed to set clay mode:', err);
          // Revert UI state on error
          setState(prev => ({ ...prev, clayMode: !newClayMode }));
        });
        break;
      case 'subsample-2x2':
        const new2x2Mode = state.subSampling === '2x2' ? 'none' : '2x2';
        setState(prev => ({ ...prev, subSampling: new2x2Mode }));
        console.log(`📐 Sub-sampling 2x2: ${new2x2Mode === '2x2' ? 'ON' : 'OFF'}`);
        // SUBSAMPLEMODE_NONE = 1, SUBSAMPLEMODE_2X2 = 2
        client.setSubSampleMode(new2x2Mode === '2x2' ? 2 : 1).then(() => {
          console.log('✅ Sub-sampling mode updated in Octane');
        }).catch(err => {
          console.error('❌ Failed to set sub-sampling mode:', err);
          setState(prev => ({ ...prev, subSampling: state.subSampling }));
        });
        break;
      case 'subsample-4x4':
        const new4x4Mode = state.subSampling === '4x4' ? 'none' : '4x4';
        setState(prev => ({ ...prev, subSampling: new4x4Mode }));
        console.log(`📐 Sub-sampling 4x4: ${new4x4Mode === '4x4' ? 'ON' : 'OFF'}`);
        // SUBSAMPLEMODE_NONE = 1, SUBSAMPLEMODE_4X4 = 4
        client.setSubSampleMode(new4x4Mode === '4x4' ? 4 : 1).then(() => {
          console.log('✅ Sub-sampling mode updated in Octane');
        }).catch(err => {
          console.error('❌ Failed to set sub-sampling mode:', err);
          setState(prev => ({ ...prev, subSampling: state.subSampling }));
        });
        break;
      case 'decal-wireframe':
        setState(prev => ({ ...prev, decalWireframe: !prev.decalWireframe }));
        console.log(`Decal wireframe: ${!state.decalWireframe ? 'ON' : 'OFF'}`);
        // TODO: API call to toggle decal wireframe
        break;
      case 'render-priority':
        console.log('Show render priority menu');
        // TODO: Show priority menu dropdown
        break;

      // Output Controls
      case 'copy-clipboard':
        console.log('📋 Copy render to clipboard');
        if (onCopyToClipboard) {
          onCopyToClipboard();
        } else {
          console.warn('⚠️ onCopyToClipboard handler not provided');
        }
        break;
      case 'save-render':
        console.log('💾 Save render to disk');
        if (onSaveRender) {
          onSaveRender();
        } else {
          console.warn('⚠️ onSaveRender handler not provided');
        }
        break;
      case 'export-passes':
        console.log('Export render passes');
        // TODO: Show render passes export window
        break;
      case 'background-image':
        console.log('Set background image');
        // TODO: Show file dialog for background image
        break;

      // Viewport Controls
      case 'viewport-resolution-lock':
        const newResLockState = !state.viewportResolutionLock;
        setState(prev => ({ ...prev, viewportResolutionLock: newResLockState }));
        console.log(`🔒 Viewport resolution lock: ${newResLockState ? 'ON' : 'OFF'}`);
        client.setViewportResolutionLock(newResLockState).then(() => {
          console.log('✅ Viewport resolution lock updated in Octane');
        }).catch(err => {
          console.error('❌ Failed to set viewport resolution lock:', err);
          // Revert UI state on error
          setState(prev => ({ ...prev, viewportResolutionLock: !newResLockState }));
        });
        break;
      case 'lock-viewport':
        const newLockState = !state.viewportLocked;
        setState(prev => ({ ...prev, viewportLocked: newLockState }));
        console.log(`🔒 Viewport lock: ${newLockState ? 'ON' : 'OFF'}`);
        if (onViewportLockChange) {
          onViewportLockChange(newLockState);
        }
        break;

      // Object Manipulation
      case 'object-control-alignment':
        setState(prev => ({
          ...prev,
          objectControlMode: prev.objectControlMode === 'world' ? 'local' : 'world'
        }));
        console.log(`Object control alignment: ${state.objectControlMode === 'world' ? 'local' : 'world'}`);
        // TODO: API call to set object control alignment
        break;
      case 'translate-gizmo':
        toggleGizmo('translate');
        break;
      case 'rotate-gizmo':
        toggleGizmo('rotate');
        break;
      case 'scale-gizmo':
        toggleGizmo('scale');
        break;
      case 'world-coordinate':
        setState(prev => ({ ...prev, worldCoordinateDisplay: !prev.worldCoordinateDisplay }));
        console.log(`World coordinate display: ${!state.worldCoordinateDisplay ? 'ON' : 'OFF'}`);
        onToggleWorldCoord?.();
        break;

      default:
        console.warn(`Unknown toolbar action: ${actionId}`);
    }
  };

  const togglePickingMode = (mode: ToolbarState['currentPickingMode']) => {
    setState(prev => ({
      ...prev,
      currentPickingMode: prev.currentPickingMode === mode ? 'none' : mode
    }));
    console.log(`Picking mode: ${state.currentPickingMode === mode ? 'none' : mode}`);
    // TODO: API calls for picking modes
  };

  const toggleGizmo = (gizmo: 'translate' | 'rotate' | 'scale') => {
    setState(prev => ({
      ...prev,
      activeGizmo: prev.activeGizmo === gizmo ? 'none' : gizmo
    }));
    console.log(`Active gizmo: ${state.activeGizmo === gizmo ? 'none' : gizmo}`);
    // TODO: API calls for gizmos
  };

  const getButtonActiveClass = (buttonId: string): string => {
    switch (buttonId) {
      case 'real-time-render':
        return state.realTimeMode ? 'active' : '';
      case 'lock-viewport':
        return state.viewportLocked ? 'active' : '';
      case 'clay-mode':
        return state.clayMode ? 'active' : '';
      case 'subsample-2x2':
        return state.subSampling === '2x2' ? 'active' : '';
      case 'subsample-4x4':
        return state.subSampling === '4x4' ? 'active' : '';
      case 'decal-wireframe':
        return state.decalWireframe ? 'active' : '';
      case 'viewport-resolution-lock':
        return state.viewportResolutionLock ? 'active' : '';
      case 'object-control-alignment':
        return state.objectControlMode === 'world' ? 'active' : '';
      case 'translate-gizmo':
        return state.activeGizmo === 'translate' ? 'active' : '';
      case 'rotate-gizmo':
        return state.activeGizmo === 'rotate' ? 'active' : '';
      case 'scale-gizmo':
        return state.activeGizmo === 'scale' ? 'active' : '';
      case 'world-coordinate':
        return state.worldCoordinateDisplay ? 'active' : '';
      case 'focus-picker':
        return state.currentPickingMode === 'focus' ? 'active' : '';
      case 'white-balance-picker':
        return state.currentPickingMode === 'whiteBalance' ? 'active' : '';
      case 'material-picker':
        return state.currentPickingMode === 'material' ? 'active' : '';
      case 'object-picker':
        return state.currentPickingMode === 'object' ? 'active' : '';
      case 'camera-target-picker':
        return state.currentPickingMode === 'cameraTarget' ? 'active' : '';
      case 'render-region-picker':
        return state.currentPickingMode === 'renderRegion' ? 'active' : '';
      case 'film-region-picker':
        return state.currentPickingMode === 'filmRegion' ? 'active' : '';
      default:
        return '';
    }
  };

  // Official Octane render viewport controls based on documentation
  const toolbarIcons = [
    // Camera & View Controls
    { id: 'recenter-view', icon: '⌖', tooltip: 'Recenter View - Centers the render view display area in the Render Viewport.' },
    { id: 'reset-camera', icon: '⌂', tooltip: 'Reset Camera - Resets the camera back to the original position.' },
    { id: 'camera-presets', icon: '◉', tooltip: 'Camera View Presets - Provides preset camera views of the scene.' },
    
    { type: 'separator' },
    
    // Render Controls
    { id: 'stop-render', icon: '■', tooltip: 'Stop Render - Aborts the rendering process and frees all resources.', important: true },
    { id: 'restart-render', icon: '↻', tooltip: 'Restart Render - Halts and restarts the rendering process at zero samples.', important: true },
    { id: 'pause-render', icon: '❚❚', tooltip: 'Pause Render - Pauses the rendering without losing rendered data.', important: true },
    { id: 'start-render', icon: '▶', tooltip: 'Start Render - Starts or resumes the rendering process.', important: true },
    { id: 'real-time-render', icon: '⚡', tooltip: 'Real Time Rendering - Uses more GPU memory for interactive experience.' },
    
    { type: 'separator' },
    
    // Picking Tools
    { id: 'focus-picker', icon: '◎', tooltip: 'Auto Focus Picking Mode - Click on scene to focus camera on that point.' },
    { id: 'white-balance-picker', icon: '○', tooltip: 'White Balance Picking Mode - Select part of scene for white point colors.' },
    { id: 'material-picker', icon: '●', tooltip: 'Material Picker - Select rendered scene to inspect material.' },
    { id: 'object-picker', icon: '□', tooltip: 'Object Picker - Select objects to inspect attributes.' },
    { id: 'camera-target-picker', icon: '⊙', tooltip: 'Camera Target Picker - Set center of rotation and zooming.' },
    
    { type: 'separator' },
    
    // Region Tools
    { id: 'render-region-picker', icon: '◇', tooltip: 'Render Region Picker - Specify a region in viewport to view changes.' },
    { id: 'film-region-picker', icon: '▭', tooltip: 'Film Region Picker - Set region for Film Settings parameters.' },
    
    { type: 'separator' },
    
    // Rendering Settings
    { id: 'clay-mode', icon: '◐', tooltip: 'Clay Mode - Shows model details without complex texturing.' },
    { id: 'subsample-2x2', icon: '▦', tooltip: 'Sub-Sampling 2×2 - Smoother navigation by reducing render resolution.' },
    { id: 'subsample-4x4', icon: '▣', tooltip: 'Sub-Sampling 4×4 - Maximum navigation smoothness.' },
    { id: 'decal-wireframe', icon: '▢', tooltip: 'Decal Wireframe - Toggles wireframe along decal boundaries.' },
    { id: 'render-priority', icon: '⚙', tooltip: 'Render Priority Settings - Set GPU render priority.' },
    
    { type: 'separator' },
    
    // Output Controls
    { id: 'copy-clipboard', icon: '⎘', tooltip: 'Copy to Clipboard - Copies current render in LDR format.' },
    { id: 'save-render', icon: '⬇', tooltip: 'Save Render - Saves current render to disk.' },
    { id: 'export-passes', icon: '⇪', tooltip: 'Export Render Passes - Brings up Render Passes Export window.' },
    { id: 'background-image', icon: '▣', tooltip: 'Set Background Image - Places background image in viewport.' },
    
    { type: 'separator' },
    
    // Viewport Controls
    { id: 'viewport-resolution-lock', icon: '⊡', tooltip: 'Viewport Resolution Lock - Adjusts render resolution to viewport size.' },
    { id: 'lock-viewport', icon: '⚿', tooltip: 'Lock Viewport - Prevents accidental changes or render restarts.' },
    
    { type: 'separator' },
    
    // Object Manipulation
    { id: 'object-control-alignment', icon: '⊕', tooltip: 'Object Control Alignment - World or local coordinate system.' },
    { id: 'translate-gizmo', icon: '↔', tooltip: 'Placement Translation Tool - Move objects along axes.' },
    { id: 'rotate-gizmo', icon: '⟲', tooltip: 'Placement Rotation Tool - Rotate objects around axes.' },
    { id: 'scale-gizmo', icon: '◳', tooltip: 'Placement Scale Tool - Scale objects uniformly or per axis.' },
    { id: 'world-coordinate', icon: '⊞', tooltip: 'Display World Coordinate - Shows world axis in viewport corner.' }
  ];

  return (
    <div className={`render-toolbar-container ${className}`}>
      {/* Render Statistics Bar - Matching Octane format exactly */}
      <div className="render-stats-bar">
        <div className="render-stats-left">
          <span id="render-samples-display">{Math.floor(renderStats.samples)}/1 @/pv</span>
          <span className="stats-separator">, </span>
          <span id="render-time-display">{renderStats.time}</span>
          <span> </span>
          <span id="render-status-display" className={`render-status-${renderStats.status}`}>
            ({renderStats.status})
          </span>
        </div>
        <div className="render-stats-right">
          <span id="render-resolution-display">{renderStats.resolution} pti </span>
          <span id="render-mesh-count">{renderStats.meshCount} mesh</span>
          <span className="stats-separator">, </span>
          <span id="render-gpu-info">{renderStats.gpu}</span>
          <span className="stats-separator">, </span>
          <span id="render-memory-combined">{renderStats.version}/{renderStats.memory}</span>
        </div>
      </div>

      {/* Render Toolbar Icons */}
      <div className="render-toolbar">
        <div className="render-toolbar-icons">
          {toolbarIcons.map((iconData, index) => {
            if ('type' in iconData && iconData.type === 'separator') {
              return <div key={`sep-${index}`} className="toolbar-separator" />;
            }
            
            const { id, icon, tooltip, important } = iconData as {
              id: string;
              icon: string;
              tooltip: string;
              important?: boolean;
            };
            
            return (
              <button
                key={id}
                id={id}
                className={`toolbar-icon-btn ${important ? 'important' : ''} ${getButtonActiveClass(id)}`}
                title={tooltip}
                onClick={() => handleToolbarAction(id)}
              >
                {icon}
              </button>
            );
          })}
        </div>
      </div>
    </div>
  );
}
