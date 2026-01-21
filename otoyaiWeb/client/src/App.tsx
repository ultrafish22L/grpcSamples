import { useEffect } from 'react';
import { Toolbar } from './components/Layout/Toolbar';
import { ContextMenu } from './components/Layout/ContextMenu';
import { NodeGraph } from './components/NodeGraph/NodeGraph';
import { logger } from './services/logger';
import './styles/global.css';

function App() {
  useEffect(() => {
    logger.info('OtoyaiWeb application started');

    return () => {
      logger.info('OtoyaiWeb application closed');
    };
  }, []);

  return (
    <div style={{ display: 'flex', height: '100vh', overflow: 'hidden' }}>
      <Toolbar />
      <ContextMenu />
      <NodeGraph />
    </div>
  );
}

export default App;
