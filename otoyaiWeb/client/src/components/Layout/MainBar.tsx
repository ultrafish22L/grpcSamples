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
    setVisibleEndpoints,
    resetVisibleEndpoints 
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

  const handleSaveProject = async () => {
    // Always show file save dialog
    const { nodes, edges } = useStore.getState();
    const projectData = {
      name: currentProject?.name || 'Untitled',
      created: currentProject?.created || Date.now(),
      modified: Date.now(),
      nodes,
      edges,
      visibleEndpoints,
    };
    
    const jsonString = JSON.stringify(projectData, null, 2);
    const blob = new Blob([jsonString], { type: 'application/json' });
    const filename = `${projectData.name.replace(/[^a-z0-9]/gi, '_')}_${Date.now()}.otoyai`;
    
    // Use modern File System Access API if available
    if ('showSaveFilePicker' in window) {
      try {
        const handle = await (window as any).showSaveFilePicker({
          suggestedName: filename,
          types: [{
            description: 'OTOY AI Project',
            accept: { 'application/json': ['.otoyai'] },
          }],
        });
        const writable = await handle.createWritable();
        await writable.write(blob);
        await writable.close();
        
        // Also save to localStorage for quick access
        if (currentProject) {
          saveProject(currentProject.name);
        } else {
          saveProject(projectData.name);
        }
      } catch (err) {
        // User cancelled
        console.log('Save cancelled');
      }
    } else {
      // Fallback: trigger download
      const url = URL.createObjectURL(blob);
      const a = document.createElement('a');
      a.href = url;
      a.download = filename;
      a.click();
      URL.revokeObjectURL(url);
      
      // Also save to localStorage
      if (currentProject) {
        saveProject(currentProject.name);
      } else {
        setShowProjectDialog(true);
      }
    }
  };

  const handleSaveProjectConfirm = () => {
    if (projectName.trim()) {
      saveProject(projectName.trim());
      setProjectName('');
      setShowProjectDialog(false);
    }
  };

  const handleLoadProject = async () => {
    // Show file picker for loading .otoyai files
    if ('showOpenFilePicker' in window) {
      try {
        const [handle] = await (window as any).showOpenFilePicker({
          types: [{
            description: 'OTOY AI Project',
            accept: { 'application/json': ['.otoyai', '.json'] },
          }],
          multiple: false,
        });
        const file = await handle.getFile();
        const text = await file.text();
        const projectData = JSON.parse(text);
        
        // Load the project data into store
        const { setNodes, setEdges, setVisibleEndpoints } = useStore.getState();
        setNodes(projectData.nodes || []);
        setEdges(projectData.edges || []);
        if (projectData.visibleEndpoints) {
          setVisibleEndpoints(projectData.visibleEndpoints);
        }
        
        // Optionally save to localStorage for recent projects
        if (projectData.name) {
          saveProject(projectData.name);
        }
      } catch (err) {
        console.log('Load cancelled');
      }
    } else {
      // Fallback: show input for file upload
      const input = document.createElement('input');
      input.type = 'file';
      input.accept = '.otoyai,.json';
      input.onchange = async (e) => {
        const file = (e.target as HTMLInputElement).files?.[0];
        if (file) {
          const text = await file.text();
          const projectData = JSON.parse(text);
          
          const { setNodes, setEdges, setVisibleEndpoints } = useStore.getState();
          setNodes(projectData.nodes || []);
          setEdges(projectData.edges || []);
          if (projectData.visibleEndpoints) {
            setVisibleEndpoints(projectData.visibleEndpoints);
          }
          
          if (projectData.name) {
            saveProject(projectData.name);
          }
        }
      };
      input.click();
    }
  };

  const handleLoadProjectConfirm = (projectId: string) => {
    loadProject(projectId);
    setShowLoadDialog(false);
  };

  const handleSaveWorkspace = async () => {
    // Always show file save dialog for workspace
    const workspaceData = {
      name: 'Workspace',
      visibleEndpoints,
      saved: Date.now(),
    };
    
    const jsonString = JSON.stringify(workspaceData, null, 2);
    const blob = new Blob([jsonString], { type: 'application/json' });
    const filename = `workspace_${Date.now()}.otoyai-workspace`;
    
    // Use modern File System Access API if available
    if ('showSaveFilePicker' in window) {
      try {
        const handle = await (window as any).showSaveFilePicker({
          suggestedName: filename,
          types: [{
            description: 'OTOY AI Workspace',
            accept: { 'application/json': ['.otoyai-workspace'] },
          }],
        });
        const writable = await handle.createWritable();
        await writable.write(blob);
        await writable.close();
        
        // Also save to localStorage
        const savedWorkspaces = JSON.parse(localStorage.getItem('otoyai-workspaces') || '[]');
        savedWorkspaces.push(workspaceData);
        localStorage.setItem('otoyai-workspaces', JSON.stringify(savedWorkspaces));
      } catch (err) {
        console.log('Save cancelled');
      }
    } else {
      // Fallback: trigger download
      const url = URL.createObjectURL(blob);
      const a = document.createElement('a');
      a.href = url;
      a.download = filename;
      a.click();
      URL.revokeObjectURL(url);
      
      // Also save to localStorage
      setShowWorkspaceDialog(true);
    }
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

  const handleLoadWorkspace = async () => {
    // Show file picker for loading workspace files
    if ('showOpenFilePicker' in window) {
      try {
        const [handle] = await (window as any).showOpenFilePicker({
          types: [{
            description: 'OTOY AI Workspace',
            accept: { 'application/json': ['.otoyai-workspace', '.json'] },
          }],
          multiple: false,
        });
        const file = await handle.getFile();
        const text = await file.text();
        const workspaceData = JSON.parse(text);
        
        if (workspaceData.visibleEndpoints) {
          setVisibleEndpoints(workspaceData.visibleEndpoints);
        }
      } catch (err) {
        console.log('Load cancelled');
      }
    } else {
      // Fallback: show input for file upload
      const input = document.createElement('input');
      input.type = 'file';
      input.accept = '.otoyai-workspace,.json';
      input.onchange = async (e) => {
        const file = (e.target as HTMLInputElement).files?.[0];
        if (file) {
          const text = await file.text();
          const workspaceData = JSON.parse(text);
          
          if (workspaceData.visibleEndpoints) {
            setVisibleEndpoints(workspaceData.visibleEndpoints);
          }
        }
      };
      input.click();
    }
  };

  const handleResetWorkspace = () => {
    if (confirm('Reset workspace to default popular models (62 models)? This will replace your current NodeBar configuration.')) {
      resetVisibleEndpoints();
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
          <svg width="40" height="40" viewBox="0 0 152.21 154" fill="none" xmlns="http://www.w3.org/2000/svg">
            {/* OTOY Logo - Official SVG from beta.otoy.ai */}
            <defs>
              <linearGradient id="otoy-gradient" x1="-1746.44" y1="-41.64" x2="-1745.44" y2="-41.64" gradientTransform="translate(128374.51 114010.34) rotate(40.24) scale(98.25)" gradientUnits="userSpaceOnUse">
                <stop offset="0" stopColor="#f10101"/>
                <stop offset="1" stopColor="#c90303"/>
              </linearGradient>
            </defs>
            <path fill="url(#otoy-gradient)" d="M62.96,10.44L10.44,62.96c-7.26,7.26-7.26,19.03,0,26.29h0l52.52,52.52c7.26,7.26,19.03,7.26,26.29,0h0l52.52-52.52c7.26-7.26,7.26-19.03,0-26.29h0L89.25,10.44c-3.63-3.63-8.39-5.44-13.15-5.44h0c-4.76,0-9.51,1.81-13.15,5.44M46.45,105.77c-16.38-16.38-16.38-42.94,0-59.32h0c16.38-16.38,42.94-16.38,59.32,0h0c16.38,16.38,16.38,42.94,0,59.32h0c-8.19,8.19-18.92,12.29-29.66,12.29h0c-10.74,0-21.47-4.1-29.66-12.29"/>
            <path fill="url(#otoy-gradient)" d="M58.37,58.37c-9.8,9.79-9.8,25.67,0,35.47h0c9.8,9.8,25.68,9.8,35.47,0h0c9.8-9.79,9.8-25.67,0-35.47h0c-4.9-4.9-11.31-7.35-17.73-7.35h0c-6.42,0-12.84,2.45-17.74,7.35"/>
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

        <div className={styles.mainBarButton} onClick={handleResetWorkspace} title="Reset Workspace to Default (62 Popular Models)">
          <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2">
            <path d="M3 12a9 9 0 0 1 9-9 9.75 9.75 0 0 1 6.74 2.74L21 8" />
            <path d="M21 3v5h-5" />
            <path d="M21 12a9 9 0 0 1-9 9 9.75 9.75 0 0 1-6.74-2.74L3 16" />
            <path d="M3 21v-5h5" />
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
