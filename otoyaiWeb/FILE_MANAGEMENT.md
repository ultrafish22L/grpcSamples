# File Management Guide

## Overview

The Save/Load buttons in the main toolbar now use **native file system dialogs** for saving and loading projects and workspaces.

---

## Save Button Behavior

**The Save button ALWAYS opens a file save dialog** - there's no silent save to localStorage only.

### What Gets Saved

#### Projects (`.otoyai` files)
- Complete node graph state
- All nodes with their parameters
- All connections between nodes
- Visible endpoints configuration
- Viewport position and zoom level

#### Workspaces (`.otoyai-workspace` files)
- NodeBar configuration (which AI endpoints are visible)
- Used for quickly switching between different sets of AI models

---

## File Formats

Both file types are **JSON format** for portability and version control.

### Example: Project File Structure
```json
{
  "name": "MyProject",
  "created": 1705823456789,
  "modified": 1705823456789,
  "nodes": [...],
  "edges": [...],
  "visibleEndpoints": [...]
}
```

### Example: Workspace File Structure
```json
{
  "name": "Workspace",
  "visibleEndpoints": ["fal-ai/flux-1/dev", ...],
  "saved": 1705823456789
}
```

---

## Storage Locations

### 1. File System (Primary)
- **Location**: User's choice via native OS dialog
- **Files**: `.otoyai` and `.otoyai-workspace` 
- **Benefits**:
  - Portable (can copy to USB, share via email, etc.)
  - Version controllable (can commit to git)
  - Backup-friendly
  - Works across different browsers

### 2. Browser localStorage (Cache)
- **Key**: `otoyai-storage`
- **Purpose**: Quick access to recent projects
- **Limitation**: Browser-specific, not portable
- **Contents**: 
  - Recent projects list
  - Visible endpoints configuration

### 3. Server Logs (Development Only)
- **Location**: `server/logs/app.log`
- **Purpose**: Runtime debugging
- **Cleared**: On app restart
- **NOT saved**: User project data

---

## Browser Compatibility

### Modern Browsers (Chrome, Edge, Opera)
- Uses **File System Access API**
- Functions: `showSaveFilePicker()` and `showOpenFilePicker()`
- Native OS file dialogs
- Can save to any location on disk

### Older Browsers (Firefox, Safari)
- **Save**: Triggers automatic download to Downloads folder
- **Load**: Shows file upload input
- Still works, just less elegant

---

## How to Use

### Save a Project
1. Click **Save Project** button (floppy disk icon)
2. Native file dialog opens
3. Choose location and filename
4. File saved as `[name]_[timestamp].otoyai`
5. Also cached in localStorage for quick access

### Load a Project
1. Click **Load Project** button (down arrow icon)
2. Native file picker opens
3. Select a `.otoyai` or `.json` file
4. Graph loads instantly
5. Also cached in localStorage

### Save a Workspace
1. Click **Save Workspace** button (grid icon)
2. Native file dialog opens
3. File saved as `workspace_[timestamp].otoyai-workspace`

### Load a Workspace
1. Click **Load Workspace** button (grid icon)
2. Native file picker opens
3. Select a `.otoyai-workspace` file
4. NodeBar configuration loads instantly

---

## File Extensions

| Extension | Type | Contains |
|-----------|------|----------|
| `.otoyai` | Project | Full node graph + settings |
| `.otoyai-workspace` | Workspace | NodeBar configuration only |
| `.json` | Generic | Also accepted for loading |

---

## Security

- **User control**: User explicitly chooses where to save via OS dialog
- **No auto-upload**: Files stay on user's machine
- **localStorage**: Standard browser storage, sandboxed per-origin

---

## Tips

- **Naming**: Use descriptive names for projects (auto-timestamp is added)
- **Organization**: Create a dedicated folder for `.otoyai` projects
- **Backups**: Save projects to cloud storage (Dropbox, Google Drive) for automatic backup
- **Version Control**: `.otoyai` files are plain JSON - perfect for git
- **Sharing**: Send `.otoyai` files to collaborators via email or Slack

---

## Troubleshooting

### "Save button doesn't open a dialog"
- Check browser console for errors
- Verify browser supports File System Access API
- Try in Chrome/Edge if using Firefox/Safari

### "Saved file location unknown"
- Check your browser's default Downloads folder
- In fallback mode (older browsers), files go to Downloads

### "Can't load project file"
- Verify file is valid JSON
- Check file extension is `.otoyai` or `.json`
- Try opening in text editor to verify format

### "localStorage quota exceeded"
- Clear browser data for the site
- localStorage limited to ~5-10MB per origin
- This shouldn't happen with normal usage

---

## Future Enhancements

- **Recent Projects Dropdown**: Quick access to recently opened projects
- **Auto-save**: Optional periodic auto-save to prevent data loss
- **Cloud Storage Integration**: Save directly to Google Drive, Dropbox
- **Project Thumbnails**: Preview images in file picker
- **Version History**: Track changes to projects over time
