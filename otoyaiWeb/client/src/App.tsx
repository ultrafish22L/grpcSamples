import { useEffect, useState } from 'react';
import { MainBar } from './components/Layout/MainBar';
import { NodeBar } from './components/Layout/NodeBar';
import { NodeInspector } from './components/Layout/NodeInspector';
import { AddNodeDialog } from './components/Layout/AddNodeDialog';
import { NodeGraph } from './components/NodeGraph/NodeGraph';
import { logger } from './services/logger';
import './styles/global.css';

function App() {
  const [showAddNodeDialog, setShowAddNodeDialog] = useState(false);

  useEffect(() => {
    logger.info('OtoyaiWeb application started');

    return () => {
      logger.info('OtoyaiWeb application closed');
    };
  }, []);

  return (
    <>
      <div style={{ display: 'flex', height: '100vh', overflow: 'hidden' }}>
        <MainBar onAddNodeClick={() => setShowAddNodeDialog(true)} />
        <NodeBar />
        <NodeGraph />
        <NodeInspector />
      </div>
      
      {showAddNodeDialog && (
        <AddNodeDialog onClose={() => setShowAddNodeDialog(false)} />
      )}
    </>
  );
}

export default App;
