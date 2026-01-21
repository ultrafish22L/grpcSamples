# UI Restructure Plan - Main Bar + Customizable Node Bar

## Current Structure
```
[Toolbar] [ContextMenu with all nodes] [NodeGraph]
```

## New Structure
```
[MainBar] [NodeBar (customizable)] [NodeGraph]
```

## Components to Create

### 1. MainBar (Leftmost)
**Width**: 60px (icon buttons)
**Buttons**:
- 📄 New Project
- 📂 Load Project  
- 💾 Save Project
- 🔖 Save Workflow (saves node bar configuration)
- ➕ Add Node (opens dialog to add AI nodes to NodeBar)

### 2. NodeBar (Right of MainBar)
**Width**: 280px (same as current ContextMenu)
**Content**:
- Utility Nodes (always visible)
  - Text Input
  - Image
  - Video
- AI Model Nodes (customizable)
  - Starts with 8 most popular models
  - Organized by collapsible categories
  - Can be added via + button
  - Right-click to remove from NodeBar

### 3. AddNodeDialog
**Purpose**: Select AI models to add to NodeBar
**Features**:
- Search/filter through all 1,136+ endpoints
- Browse by category
- Click to add to NodeBar
- Shows which nodes are already added

### 4. ContextMenuOverlay
**Purpose**: Right-click menu on NodeBar items
**Options**:
- Remove from NodeBar

## Default 8 Popular Models

Based on common AI workflows:

### Text-to-Image (3 models)
1. FLUX.1 [pro] (text-to-image, BFL)
2. Stable Diffusion XL (text-to-image, Stability AI)
3. Midjourney (if available)

### Text-to-Text (2 models)
4. GPT-4 / Claude (llm)
5. LLaMA 3 (llm)

### Image-to-Image (1 model)
6. Stable Diffusion Inpainting (image-to-image)

### Audio (1 model)
7. Whisper (speech-to-text)

### Video (1 model)
8. Stable Video Diffusion (image-to-video or text-to-video)

## State Management

### New Store Properties
```typescript
interface AppState {
  // Existing...
  endpoints: Endpoint[];
  nodes: AppNode[];
  edges: AppEdge[];
  
  // New
  visibleEndpoints: string[]; // endpoint_ids visible in NodeBar
  projects: Project[];
  currentProject: Project | null;
  
  // New Actions
  addVisibleEndpoint: (endpointId: string) => void;
  removeVisibleEndpoint: (endpointId: string) => void;
  setVisibleEndpoints: (endpointIds: string[]) => void;
  saveProject: () => void;
  loadProject: (project: Project) => void;
  saveWorkflow: () => void;
  loadWorkflow: (workflow: Workflow) => void;
}
```

### Types
```typescript
interface Project {
  id: string;
  name: string;
  created: number;
  modified: number;
  nodes: AppNode[];
  edges: AppEdge[];
  workflow: Workflow;
}

interface Workflow {
  visibleEndpoints: string[];
}
```

## File Structure

```
components/
├── Layout/
│   ├── MainBar.tsx (NEW)
│   ├── MainBar.module.css (NEW)
│   ├── NodeBar.tsx (renamed from ContextMenu.tsx)
│   ├── NodeBar.module.css (updated)
│   ├── AddNodeDialog.tsx (NEW)
│   ├── AddNodeDialog.module.css (NEW)
│   ├── Toolbar.tsx (REMOVE - functionality moves to MainBar)
│   └── Layout.module.css (updated)
```

## Implementation Steps

### Phase 1: Create New Components (30 min)
1. ✅ Create MainBar component
2. ✅ Create AddNodeDialog component
3. ✅ Update store with workflow state
4. ✅ Identify 8 popular models from API

### Phase 2: Restructure Layout (20 min)
5. ✅ Rename ContextMenu to NodeBar
6. ✅ Update NodeBar to use visibleEndpoints
7. ✅ Update main layout to use MainBar + NodeBar
8. ✅ Remove old Toolbar

### Phase 3: Add Functionality (30 min)
9. ✅ Implement Add Node dialog
10. ✅ Implement right-click context menu
11. ✅ Implement save/load workflow
12. ✅ Implement save/load project

### Phase 4: Testing (10 min)
13. ✅ Test add node to NodeBar
14. ✅ Test remove node from NodeBar
15. ✅ Test save/load workflow
16. ✅ Test save/load project

## Default Popular Models (by endpoint_id)

Need to identify from API response. Will select:
- Most used/favorited models
- Representative of different categories
- Good starting point for typical workflows

## CSS Updates

### MainBar Styles
```css
.mainBar {
  width: 60px;
  background: #1a1a1a;
  display: flex;
  flex-direction: column;
  gap: 4px;
  padding: 8px 4px;
}

.mainBarButton {
  width: 48px;
  height: 48px;
  display: flex;
  align-items: center;
  justify-content: center;
  cursor: pointer;
  border-radius: 8px;
  transition: background 0.2s;
}

.mainBarButton:hover {
  background: #2a2a2a;
}
```

### NodeBar Updates
```css
.nodeBar {
  width: 280px;
  background: #1a1a1a;
  overflow-y: auto;
}

.nodeBarItem {
  position: relative; /* for context menu */
}
```

## User Workflows

### Adding a New AI Model
1. Click + button in MainBar
2. AddNodeDialog opens showing all 1,136 endpoints
3. Search or browse by category
4. Click model to add to NodeBar
5. Model appears in NodeBar under its category

### Removing an AI Model
1. Right-click model in NodeBar
2. Context menu appears with "Remove" option
3. Click Remove
4. Model removed from NodeBar (but still available in + dialog)

### Saving Workflow
1. Customize NodeBar with desired models
2. Click "Save Workflow" in MainBar
3. Workflow saved to localStorage
4. Next session: NodeBar shows same models

### Saving Project
1. Create node graph with connections
2. Click "Save Project" in MainBar
3. Enter project name
4. Project saved (includes nodes, edges, AND workflow)

### Loading Project
1. Click "Load Project" in MainBar
2. Select project from list
3. Node graph and NodeBar restored

## Persistence Strategy

- **Workflows**: localStorage (visibleEndpoints array)
- **Projects**: localStorage (full project objects)
- **Default**: If no workflow, use 8 popular models
