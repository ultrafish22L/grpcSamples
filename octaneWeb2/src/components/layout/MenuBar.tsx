import { useConnectionStore } from '../../store/connectionStore';
import { octaneClient } from '../../api/octaneClient';
import './MenuBar.css';

export const MenuBar = () => {
  const { isConnected, isConnecting, setConnected, setConnecting, setError } = useConnectionStore();
  
  const handleConnect = async () => {
    if (isConnected) {
      // Disconnect
      await octaneClient.disconnect();
      setConnected(false);
      return;
    }
    
    setConnecting(true);
    setError(null);
    
    try {
      const connected = await octaneClient.connect();
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
          {isConnecting ? 'Connecting...' : isConnected ? 'Disconnect' : 'Connect'}
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
