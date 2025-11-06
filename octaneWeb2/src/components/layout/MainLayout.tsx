import { MenuBar } from './MenuBar';
import { StatusBar } from './StatusBar';
import { RenderViewport } from '../viewport/RenderViewport';
import { SceneOutliner } from '../panels/SceneOutliner';
import { NodeInspector } from '../panels/NodeInspector';
import { NodeGraph } from '../panels/NodeGraph';
import './MainLayout.css';

export const MainLayout = () => {
  return (
    <div className="app-container">
      <MenuBar />
      
      <main className="app-layout">
        <SceneOutliner className="left-panel" />
        
        <section className="center-panel">
          <div className="viewport-section">
            <div className="viewport-header">
              <div className="viewport-title">Render Viewport</div>
            </div>
            <div className="viewport-container">
              <RenderViewport />
            </div>
          </div>
          
          <NodeGraph />
        </section>
        
        <NodeInspector className="right-panel" />
      </main>
      
      <StatusBar />
    </div>
  );
};
