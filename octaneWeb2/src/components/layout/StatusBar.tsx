import { useConnectionStore } from '@/store/connectionStore';
import { useRenderStore } from '@/store/renderStore';
import './StatusBar.css';

export const StatusBar = () => {
  const isConnected = useConnectionStore(state => state.isConnected);
  const fps = useRenderStore(state => state.fps);
  
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
        <span className="status-item">FPS: {fps.toFixed(0)}</span>
      </div>
    </footer>
  );
};
