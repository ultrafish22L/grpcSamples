import { memo, useState } from 'react';
import { useStore } from '../../store/useStore';
import styles from './MainBar.module.css';

interface MainBarProps {
  onAddNodeClick: () => void;
}

export const MainBar = memo(({ onAddNodeClick }: MainBarProps) => {
  const { newProject, saveProject, projects, loadProject, currentProject } = useStore();
  const [showProjectDialog, setShowProjectDialog] = useState(false);
  const [showLoadDialog, setShowLoadDialog] = useState(false);
  const [projectName, setProjectName] = useState('');

  const handleNewProject = () => {
    if (confirm('Create new project? Current work will be cleared.')) {
      newProject();
    }
  };

  const handleSaveProject = () => {
    if (currentProject) {
      // Update existing project
      saveProject(currentProject.name);
    } else {
      // Show dialog for new project
      setShowProjectDialog(true);
    }
  };

  const handleSaveProjectConfirm = () => {
    if (projectName.trim()) {
      saveProject(projectName.trim());
      setProjectName('');
      setShowProjectDialog(false);
    }
  };

  const handleLoadProject = () => {
    setShowLoadDialog(true);
  };

  const handleLoadProjectConfirm = (projectId: string) => {
    loadProject(projectId);
    setShowLoadDialog(false);
  };

  return (
    <>
      <div className={styles.mainBar}>
        <div className={styles.mainBarButton} onClick={handleNewProject} title="New Project">
          <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
            <path d="M14 2H6a2 2 0 00-2 2v16a2 2 0 002 2h12a2 2 0 002-2V8z" />
            <polyline points="14 2 14 8 20 8" />
          </svg>
        </div>

        <div className={styles.mainBarButton} onClick={handleLoadProject} title="Load Project">
          <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
            <path d="M3 15v4c0 1.1.9 2 2 2h14a2 2 0 002-2v-4M17 9l-5 5-5-5M12 2.8v11.85" />
          </svg>
        </div>

        <div className={styles.mainBarButton} onClick={handleSaveProject} title="Save Project">
          <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
            <path d="M19 21H5a2 2 0 01-2-2V5a2 2 0 012-2h11l5 5v11a2 2 0 01-2 2z" />
            <polyline points="17 21 17 13 7 13 7 21" />
            <polyline points="7 3 7 8 15 8" />
          </svg>
        </div>

        <div className={styles.separator} />

        <div className={styles.mainBarButton} onClick={onAddNodeClick} title="Add AI Node to NodeBar">
          <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
            <line x1="12" y1="5" x2="12" y2="19" />
            <line x1="5" y1="12" x2="19" y2="12" />
          </svg>
        </div>
      </div>

      {showProjectDialog && (
        <div className={styles.dialogOverlay} onClick={() => setShowProjectDialog(false)}>
          <div className={styles.dialog} onClick={(e) => e.stopPropagation()}>
            <h3>Save Project</h3>
            <input
              type="text"
              placeholder="Project name"
              value={projectName}
              onChange={(e) => setProjectName(e.target.value)}
              onKeyDown={(e) => e.key === 'Enter' && handleSaveProjectConfirm()}
              autoFocus
            />
            <div className={styles.dialogButtons}>
              <button onClick={handleSaveProjectConfirm}>Save</button>
              <button onClick={() => setShowProjectDialog(false)}>Cancel</button>
            </div>
          </div>
        </div>
      )}

      {showLoadDialog && (
        <div className={styles.dialogOverlay} onClick={() => setShowLoadDialog(false)}>
          <div className={styles.dialog} onClick={(e) => e.stopPropagation()}>
            <h3>Load Project</h3>
            <div className={styles.projectList}>
              {projects.length === 0 ? (
                <div className={styles.emptyMessage}>No saved projects</div>
              ) : (
                projects.map((project) => (
                  <div
                    key={project.id}
                    className={styles.projectItem}
                    onClick={() => handleLoadProjectConfirm(project.id)}
                  >
                    <div className={styles.projectName}>{project.name}</div>
                    <div className={styles.projectInfo}>
                      {project.nodes.length} nodes · {new Date(project.modified).toLocaleDateString()}
                    </div>
                  </div>
                ))
              )}
            </div>
            <div className={styles.dialogButtons}>
              <button onClick={() => setShowLoadDialog(false)}>Cancel</button>
            </div>
          </div>
        </div>
      )}
    </>
  );
});

MainBar.displayName = 'MainBar';
