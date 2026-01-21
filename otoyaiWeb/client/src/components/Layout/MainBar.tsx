import { memo, useState } from 'react';
import { useStore } from '../../store/useStore';
import styles from './MainBar.module.css';

interface MainBarProps {
  onAddNodeClick: () => void;
}

export const MainBar = memo(({ onAddNodeClick }: MainBarProps) => {
  const { 
    newProject, 
    saveProject, 
    projects, 
    loadProject, 
    currentProject,
    visibleEndpoints,
    setVisibleEndpoints 
  } = useStore();
  const [showProjectDialog, setShowProjectDialog] = useState(false);
  const [showLoadDialog, setShowLoadDialog] = useState(false);
  const [projectName, setProjectName] = useState('');
  const [showWorkspaceDialog, setShowWorkspaceDialog] = useState(false);
  const [workspaceName, setWorkspaceName] = useState('');

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

  const handleSaveWorkspace = () => {
    setShowWorkspaceDialog(true);
  };

  const handleSaveWorkspaceConfirm = () => {
    if (workspaceName.trim()) {
      const workspace = {
        name: workspaceName.trim(),
        visibleEndpoints,
        saved: Date.now(),
      };
      const savedWorkspaces = JSON.parse(localStorage.getItem('otoyai-workspaces') || '[]');
      savedWorkspaces.push(workspace);
      localStorage.setItem('otoyai-workspaces', JSON.stringify(savedWorkspaces));
      setWorkspaceName('');
      setShowWorkspaceDialog(false);
    }
  };

  const handleLoadWorkspace = () => {
    const savedWorkspaces = JSON.parse(localStorage.getItem('otoyai-workspaces') || '[]');
    if (savedWorkspaces.length === 0) {
      alert('No saved workspaces found');
      return;
    }
    const workspaceNames = savedWorkspaces.map((w: { name: string; saved: number }, i: number) => 
      `${i + 1}. ${w.name} (${new Date(w.saved).toLocaleDateString()})`
    ).join('\n');
    const choice = prompt(`Select workspace (enter number):\n\n${workspaceNames}`);
    if (choice) {
      const index = parseInt(choice) - 1;
      if (index >= 0 && index < savedWorkspaces.length) {
        setVisibleEndpoints(savedWorkspaces[index].visibleEndpoints);
      }
    }
  };

  return (
    <>
      <div className={styles.mainBar}>
        {/* OTOY Logo - Links to beta.otoy.ai */}
        <a 
          href="https://beta.otoy.ai" 
          target="_blank" 
          rel="noopener noreferrer"
          className={styles.otoyLogo}
          title="Open beta.otoy.ai"
        >
          <svg width="40" height="40" viewBox="0 0 40 40" fill="none">
            {/* OTOY Logo - Red diamond with circular cutout and red dot */}
            <g transform="translate(20, 20) rotate(45)">
              <rect x="-13" y="-13" width="26" height="26" fill="#ff3333" rx="2" />
              <circle cx="0" cy="0" r="10" fill="#1a1a1a" />
              <circle cx="0" cy="0" r="4" fill="#ff3333" />
            </g>
          </svg>
        </a>

        <div className={styles.separator} />

        {/* Project Management */}
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

        {/* Workspace Management - NodeBar State */}
        <div className={styles.mainBarButton} onClick={handleLoadWorkspace} title="Load Workspace (NodeBar)">
          <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
            <rect x="3" y="3" width="7" height="7" rx="1" />
            <rect x="14" y="3" width="7" height="7" rx="1" />
            <rect x="14" y="14" width="7" height="7" rx="1" />
            <rect x="3" y="14" width="7" height="7" rx="1" />
          </svg>
        </div>

        <div className={styles.mainBarButton} onClick={handleSaveWorkspace} title="Save Workspace (NodeBar)">
          <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
            <rect x="3" y="3" width="7" height="7" rx="1" />
            <rect x="14" y="3" width="7" height="7" rx="1" />
            <rect x="14" y="14" width="7" height="7" rx="1" />
            <rect x="3" y="14" width="7" height="7" rx="1" />
            <path d="M12 8v8M8 12h8" strokeWidth="1.5" />
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

      {showWorkspaceDialog && (
        <div className={styles.dialogOverlay} onClick={() => setShowWorkspaceDialog(false)}>
          <div className={styles.dialog} onClick={(e) => e.stopPropagation()}>
            <h3>Save Workspace</h3>
            <p className={styles.dialogDescription}>
              Save the current NodeBar configuration ({visibleEndpoints.length} endpoints)
            </p>
            <input
              type="text"
              placeholder="Workspace name"
              value={workspaceName}
              onChange={(e) => setWorkspaceName(e.target.value)}
              onKeyDown={(e) => e.key === 'Enter' && handleSaveWorkspaceConfirm()}
              autoFocus
            />
            <div className={styles.dialogButtons}>
              <button onClick={handleSaveWorkspaceConfirm}>Save</button>
              <button onClick={() => setShowWorkspaceDialog(false)}>Cancel</button>
            </div>
          </div>
        </div>
      )}
    </>
  );
});

MainBar.displayName = 'MainBar';
