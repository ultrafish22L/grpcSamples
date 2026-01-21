import { memo } from 'react';
import { useStore } from '../../store/useStore';
import { logger } from '../../services/logger';
import styles from './Layout.module.css';

export const Toolbar = memo(() => {
  const { clearGraph, saveProject, saveProjectAs, currentProject } = useStore();

  const handleSave = () => {
    const projectName = currentProject?.name || prompt('Enter project name:');
    if (projectName) {
      saveProject(projectName);
    }
  };

  const handleSaveAs = () => {
    const projectName = prompt('Enter new project name:');
    if (projectName) {
      saveProjectAs(projectName);
    }
  };

  const handleClear = () => {
    if (confirm('Clear the entire graph?')) {
      clearGraph();
    }
  };

  const handleReset = async () => {
    if (confirm('Reset application and clear logs?')) {
      await logger.clear();
      clearGraph();
      window.location.reload();
    }
  };

  return (
    <div className={styles.toolbar}>
      <div className={styles.toolbarButton} title="Add Node">
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
          <line x1="12" y1="5" x2="12" y2="19"></line>
          <line x1="5" y1="12" x2="19" y2="12"></line>
        </svg>
      </div>

      <div className={styles.toolbarButton} onClick={handleSave} title="Save Project">
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
          <path d="M19 21H5a2 2 0 01-2-2V5a2 2 0 012-2h11l5 5v11a2 2 0 01-2 2z"></path>
          <polyline points="17 21 17 13 7 13 7 21"></polyline>
          <polyline points="7 3 7 8 15 8"></polyline>
        </svg>
      </div>

      <div className={styles.toolbarButton} onClick={handleSaveAs} title="Save As...">
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
          <path d="M19 21H5a2 2 0 01-2-2V5a2 2 0 012-2h11l5 5v11a2 2 0 01-2 2z"></path>
          <polyline points="17 21 17 13 7 13 7 21"></polyline>
          <polyline points="7 3 7 8 15 8"></polyline>
          <line x1="14" y1="3" x2="14" y2="8"></line>
        </svg>
      </div>

      <div className={styles.toolbarButton} title="Settings">
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
          <circle cx="12" cy="12" r="3"></circle>
          <path d="M12 1v6m0 6v6m6-12l-4.2 4.2m-3.6 3.6L6 19m13-7h-6m-6 0H1m18-6l-4.2 4.2m-3.6 3.6L7 5"></path>
        </svg>
      </div>

      <div className={styles.toolbarButton} onClick={handleClear} title="Clear Graph">
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
          <path d="M3 6h18M19 6v14a2 2 0 01-2 2H7a2 2 0 01-2-2V6m3 0V4a2 2 0 012-2h4a2 2 0 012 2v2"></path>
        </svg>
      </div>

      <div className={styles.toolbarButton} onClick={handleReset} title="Reset">
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
          <path d="M1 4v6h6M23 20v-6h-6"></path>
          <path d="M20.49 9A9 9 0 005.64 5.64L1 10m22 4l-4.64 4.36A9 9 0 013.51 15"></path>
        </svg>
      </div>
    </div>
  );
});

Toolbar.displayName = 'Toolbar';
