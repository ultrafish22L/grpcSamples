import React from 'react';

interface StatusBarProps {
  connected: boolean;
}

const StatusBar: React.FC<StatusBarProps> = ({ connected }) => {
  return (
    <footer className="status-bar">
      <div className="status-item">Status: Ready</div>
      <div className="status-item">OctaneWebR - Direct gRPC (No Proxy)</div>
      <div className="status-item">
        Octane: {connected ? 'Connected (127.0.0.1:51022)' : 'Disconnected'}
      </div>
    </footer>
  );
};

export default StatusBar;
