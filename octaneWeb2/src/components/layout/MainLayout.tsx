import { MenuBar } from './MenuBar';
import { StatusBar } from './StatusBar';
import { RenderViewport } from '../viewport/RenderViewport';
import './MainLayout.css';

export const MainLayout = () => {
  return (
    <div className="app-container">
      <MenuBar />
      
      <main className="app-layout">
        <aside className="left-panel">
          <div className="panel-header">
            <h3>Scene Outliner</h3>
          </div>
          <div className="panel-content">
            <div className="empty-message">Scene tree coming soon...</div>
          </div>
        </aside>
        
        <section className="center-panel">
          <div className="viewport-header">
            <div className="viewport-title">Render Viewport</div>
          </div>
          <div className="viewport-container">
            <RenderViewport />
          </div>
        </section>
        
        <aside className="right-panel">
          <div className="panel-header">
            <h3>Node Inspector</h3>
          </div>
          <div className="panel-content">
            <div className="empty-message">Empty</div>
          </div>
        </aside>
      </main>
      
      <StatusBar />
    </div>
  );
};
