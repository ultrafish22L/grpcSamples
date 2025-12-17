import React from 'react';

interface MenuBarProps {
  connected: boolean;
  connecting: boolean;
  onConnect: () => void;
  onDisconnect: () => void;
}

const MenuBar: React.FC<MenuBarProps> = ({ connected, connecting, onConnect, onDisconnect }) => {
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
        <div className="connection-controls">
          <input 
            type="text" 
            id="serverAddress" 
            placeholder="Server address" 
            value="Node.js Direct gRPC" 
            disabled
            title="Direct gRPC connection via Node.js backend"
          />
          <div className="switch-container">
            <label className="switch" title="Connect/disconnect from Octane">
              <input 
                type="checkbox" 
                id="connectionToggle" 
                checked={connected}
                disabled={connecting}
                onChange={connected ? onDisconnect : onConnect}
              />
              <span className="slider"></span>
            </label>
          </div>
          <div className={`status-led ${connected ? 'connected' : 'disconnected'}`}></div>
          <span className="connection-label">
            {connecting ? 'Connecting...' : connected ? 'Connected' : 'Disconnected'}
          </span>
        </div>
      </div>
    </header>
  );
};

export default MenuBar;
