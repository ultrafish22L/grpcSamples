# octaneWebR - Code Review & Reorganization Plan

**Date**: 2025-01-22  
**Status**: Phase 8 Complete - Moving to Code Cleanup (Phase 9)
**Progress**: 8 of 13 phases complete (61%)  
**Goals**: Clean code structure, configurable UI themes, maintainability

---

## 📊 Current State Analysis

### **File Size Audit**
```
2071 lines - services/OctaneClient.ts           ⚠️ TOO LARGE - needs splitting
1577 lines - NodeGraph/NodeGraphEditor.tsx      ⚠️ LARGE - could be refactored
1157 lines - NodeInspector.tsx                  ⚠️ LARGE - needs organization
1131 lines - CallbackRenderViewport.tsx         ⚠️ LARGE - could be split
 854 lines - SceneOutliner.tsx                  ⚠️ MEDIUM - could be improved
 843 lines - RenderToolbar.tsx                  ⚠️ MEDIUM
 534 lines - MenuBar.tsx                        ✅ OK
 371 lines - NodeGraph/OctaneNode.tsx           ✅ OK
```

### **Current Organization Issues**

#### ❌ **Inconsistent Folder Structure**
```
components/
├── NodeGraph/                      ✅ GOOD - all related files together
│   ├── NodeGraphEditor.tsx
│   ├── OctaneNode.tsx
│   ├── NodeTypeContextMenu.tsx
│   └── ... (7 files total)
├── NodeInspector/                  ⚠️ INCONSISTENT - only context menu here
│   └── NodeInspectorContextMenu.tsx
├── NodeInspector.tsx               ⚠️ Main file in wrong place
├── NodeInspectorControls.tsx       ⚠️ Related file separated
├── SceneOutliner/                  ⚠️ INCONSISTENT - only context menu here
│   └── SceneOutlinerContextMenu.tsx
├── SceneOutliner.tsx               ⚠️ Main file in wrong place
├── CallbackRenderViewport/         ⚠️ INCONSISTENT
│   └── ViewportContextMenu.tsx
├── CallbackRenderViewport.tsx      ⚠️ Main file in wrong place
├── AboutDialog.tsx                 ⚠️ Dialogs should be grouped
├── BatchRenderingDialog.tsx        ⚠️ 10 dialog files scattered
├── ... (10 more dialog files)
```

#### ❌ **Monolithic Files**
- **OctaneClient.ts (2071 lines)** contains:
  - gRPC client initialization
  - Scene tree building logic
  - Node CRUD operations
  - Parameter get/set helpers
  - Connection management
  - File operations
  - → **Should be split into 5+ focused modules**

- **NodeInspector.tsx (1157 lines)** contains:
  - Main component logic
  - Parameter rendering
  - Value editing logic
  - Type-specific editors
  - → **Should extract parameter editors**

- **CallbackRenderViewport.tsx (1131 lines)** contains:
  - Viewport rendering
  - Camera controls
  - Picking tools
  - Toolbar UI
  - → **Should extract controls and tools**

#### ❌ **Theme System Limitations**
- Only one theme: "Octane SE Dark"
- No theme switching capability
- Hardcoded to match Octane SE only
- **Need**: Configurable themes for different OTOY products

---

## 🎯 Reorganization Goals

### **1. Consistent Component Structure**
Every major component gets its own folder:
```
ComponentName/
├── index.tsx                    # Main component (or re-export)
├── ComponentName.tsx            # If index.tsx is re-export
├── ComponentNameSubpart.tsx     # Sub-components
├── ComponentNameContextMenu.tsx # Related context menu
└── ComponentNameHelpers.ts      # Helper functions
```

### **2. Split Large Files**
- **OctaneClient.ts** → 5 focused modules
- **NodeInspector.tsx** → Extract parameter editors
- **CallbackRenderViewport.tsx** → Extract controls
- **RenderToolbar.tsx** → Extract tool components

### **3. Group Related Files**
- All dialogs → `components/dialogs/`
- All hooks → `hooks/` (already good)
- All services → `services/` with subfolders
- All types → `types/` (already good)

### **4. Implement Theme System**
- Support multiple themes (Octane SE, OTOY Studio)
- Theme switcher in preferences
- CSS variable-based system (already in place)
- Easy to add new themes

---

## 📁 Proposed New Structure

```
client/src/
├── components/
│   ├── App/
│   │   └── index.tsx                   # Root App component
│   │
│   ├── CallbackRenderViewport/
│   │   ├── index.tsx                   # Main viewport component
│   │   ├── ViewportContextMenu.tsx     # Existing
│   │   ├── ViewportControls.tsx        # Extract: Camera controls, picking tools
│   │   ├── ViewportToolbar.tsx         # Extract: Toolbar UI
│   │   └── ViewportCanvas.tsx          # Extract: Canvas rendering logic
│   │
│   ├── NodeGraph/
│   │   ├── index.ts                    # Re-export (already exists)
│   │   ├── NodeGraphEditor.tsx         # Main editor (keep as is)
│   │   ├── NodeGraphToolbar.tsx        # Existing
│   │   ├── OctaneNode.tsx              # Existing
│   │   ├── EdgeContextMenu.tsx         # Existing
│   │   ├── NodeContextMenu.tsx         # Existing
│   │   ├── NodeTypeContextMenu.tsx     # Existing
│   │   └── SearchDialog.tsx            # Existing
│   │
│   ├── NodeInspector/
│   │   ├── index.tsx                   # Main inspector component (move from root)
│   │   ├── NodeInspectorContextMenu.tsx # Existing
│   │   ├── NodeInspectorControls.tsx   # Move from root
│   │   ├── ParameterEditor.tsx         # Extract: Generic parameter editor
│   │   ├── editors/                    # NEW: Type-specific editors
│   │   │   ├── BooleanEditor.tsx
│   │   │   ├── NumberEditor.tsx
│   │   │   ├── VectorEditor.tsx
│   │   │   ├── ColorEditor.tsx
│   │   │   ├── EnumEditor.tsx
│   │   │   └── StringEditor.tsx
│   │   └── ParameterGroup.tsx          # Extract: Collapsible groups
│   │
│   ├── SceneOutliner/
│   │   ├── index.tsx                   # Main outliner (move from root)
│   │   ├── SceneOutlinerContextMenu.tsx # Existing
│   │   ├── SceneTreeNode.tsx           # Extract: Single tree node rendering
│   │   └── TreeNodeIcon.tsx            # Extract: Node type icons
│   │
│   ├── RenderToolbar/
│   │   ├── index.tsx                   # Main toolbar (move from root)
│   │   ├── PlaybackControls.tsx        # Extract: Play/pause/stop
│   │   ├── RenderSettings.tsx          # Extract: Resolution, samples, etc.
│   │   └── ViewportSettings.tsx        # Extract: Display settings
│   │
│   ├── MenuBar/
│   │   ├── index.tsx                   # Main menu bar (move from root)
│   │   ├── MenuDropdown.tsx            # Move from root
│   │   └── ThemeSelector.tsx           # NEW: Theme switching UI
│   │
│   ├── MaterialDatabase/
│   │   ├── index.tsx                   # Move from root
│   │   ├── LiveDBPanel.tsx             # Extract: Online materials
│   │   └── LocalDBPanel.tsx            # Extract: Local materials
│   │
│   ├── dialogs/                        # NEW: Group all dialog components
│   │   ├── AboutDialog.tsx
│   │   ├── BatchRenderingDialog.tsx
│   │   ├── DaylightAnimationDialog.tsx
│   │   ├── ExportPassesDialog.tsx
│   │   ├── GPUStatisticsDialog.tsx
│   │   ├── KeyboardShortcutsDialog.tsx
│   │   ├── PreferencesDialog.tsx
│   │   ├── SavePackageDialog.tsx
│   │   ├── SaveRenderDialog.tsx
│   │   └── TurntableAnimationDialog.tsx
│   │
│   └── shared/                         # NEW: Shared UI components
│       ├── ConnectionStatus.tsx        # Move from root
│       ├── Button.tsx                  # NEW: Reusable button
│       ├── Input.tsx                   # NEW: Reusable input
│       └── Dialog.tsx                  # NEW: Base dialog component
│
├── services/
│   ├── OctaneClient/                   # NEW: Split into modules
│   │   ├── index.ts                    # Main exports + client class
│   │   ├── OctaneClient.ts             # Core client (connection, initialization)
│   │   ├── SceneTreeBuilder.ts         # Scene graph traversal/building
│   │   ├── NodeOperations.ts           # Create/delete/copy/paste nodes
│   │   ├── ConnectionManager.ts        # Pin connections/disconnections
│   │   ├── ParameterManager.ts         # Get/set parameter values
│   │   └── FileOperations.ts           # Open/save/export scenes
│   │
│   └── CommandHistory/
│       └── index.ts                    # Move from root
│
├── styles/
│   ├── themes/                         # NEW: Theme system
│   │   ├── index.ts                    # Theme registry + switcher
│   │   ├── octane-se.css               # Current "Octane SE" theme (rename from octane-theme.css)
│   │   ├── otoy-studio.css             # NEW: "OTOY Studio" theme (workflow-builder style)
│   │   └── theme-variables.css         # Shared structure (all CSS var names)
│   │
│   ├── app.css                         # Global app styles
│   ├── node-graph.css                  # Node graph specific styles
│   ├── node-inspector.css              # Node inspector styles
│   ├── scene-outliner.css              # Scene outliner styles
│   └── viewport.css                    # Viewport styles
│
├── hooks/                              # ✅ Already well organized
│   ├── useFileDialog.ts
│   ├── useKeyboardShortcuts.ts
│   ├── useOctane.tsx
│   ├── useRecentFiles.ts
│   ├── useResizablePanels.ts
│   └── useTheme.ts                     # NEW: Theme switching hook
│
├── utils/                              # ✅ Already well organized
│   ├── ClientLogger.ts
│   ├── EventEmitter.ts
│   ├── IconLoader.tsx
│   ├── OctaneIconMapper.ts
│   └── debug.ts
│
├── constants/                          # ✅ Already well organized
│   ├── NodeTypes.ts
│   └── OctaneTypes.ts
│
├── types/                              # ✅ Already well organized
│   └── menu.ts
│
├── config/                             # ✅ Already well organized
│   └── menuDefinitions.ts
│
├── commands/                           # ✅ Already well organized
│   └── NodeCommands.ts
│
├── main.tsx                            # Entry point
└── vite-env.d.ts                       # Vite types
```

---

## 🎨 Theme System Design

### **Theme Architecture**

#### **1. Theme Definition Structure**
```typescript
// styles/themes/index.ts
export interface Theme {
  id: string;
  name: string;
  description: string;
  cssFile: string;
}

export const THEMES: Theme[] = [
  {
    id: 'octane-se',
    name: 'Octane SE',
    description: 'Classic Octane Render Studio dark theme',
    cssFile: '/src/styles/themes/octane-se.css'
  },
  {
    id: 'otoy-studio',
    name: 'OTOY Studio',
    description: 'Modern OTOY workflow builder theme',
    cssFile: '/src/styles/themes/otoy-studio.css'
  }
];

export function applyTheme(themeId: string): void {
  document.documentElement.setAttribute('data-theme', themeId);
  localStorage.setItem('octaneWebR-theme', themeId);
}

export function getActiveTheme(): string {
  return localStorage.getItem('octaneWebR-theme') || 'octane-se';
}
```

#### **2. Theme CSS Structure**
```css
/* theme-variables.css - Defines ALL variable names (no values) */
:root {
  /* Backgrounds */
  --bg-primary: ;
  --bg-secondary: ;
  --bg-header: ;
  /* ... all variables */
}

/* octane-se.css - Octane SE theme values */
[data-theme="octane-se"] {
  --bg-primary: #2b2b2b;
  --bg-secondary: #3c3c3c;
  --bg-header: #404040;
  --accent-primary: #ff8c00;
  /* ... all Octane SE colors */
}

/* otoy-studio.css - OTOY Studio theme values */
[data-theme="otoy-studio"] {
  --bg-primary: #0f172a;      /* Slate-900 */
  --bg-secondary: #1e293b;    /* Slate-800 */
  --bg-header: #334155;       /* Slate-700 */
  --accent-primary: #10b981;  /* Green-500 */
  /* ... all OTOY Studio colors */
}
```

#### **3. OTOY Studio Theme Colors**
Based on https://beta.otoy.ai/workflow-builder:

```css
[data-theme="otoy-studio"] {
  /* Backgrounds */
  --bg-primary: #0f172a;          /* Dark blue-slate (slate-900) */
  --bg-secondary: #1e293b;        /* Medium blue-slate (slate-800) */
  --bg-header: #334155;           /* Lighter slate (slate-700) */
  --bg-card: #1e293b;             /* Card backgrounds */
  --bg-hover: #334155;            /* Hover states */
  --bg-active: #475569;           /* Active states (slate-600) */
  
  /* Text */
  --text-primary: #f1f5f9;        /* Light text (slate-100) */
  --text-secondary: #cbd5e1;      /* Secondary text (slate-300) */
  --text-muted: #94a3b8;          /* Muted text (slate-400) */
  --text-disabled: #64748b;       /* Disabled text (slate-500) */
  
  /* Accents */
  --accent-primary: #10b981;      /* Green for primary actions (emerald-500) */
  --accent-primary-hover: #059669; /* Darker green (emerald-600) */
  --accent-secondary: #3b82f6;    /* Blue for info (blue-500) */
  --accent-warning: #f59e0b;      /* Amber for warnings (amber-500) */
  --accent-error: #ef4444;        /* Red for errors (red-500) */
  
  /* Borders */
  --border-primary: #334155;      /* Slate-700 */
  --border-light: #475569;        /* Slate-600 */
  --border-dark: #1e293b;         /* Slate-800 */
  
  /* Shadows */
  --shadow: rgba(0, 0, 0, 0.4);
  --shadow-lg: rgba(0, 0, 0, 0.6);
  
  /* UI Elements */
  --border-radius: 8px;           /* Rounded corners */
  --border-radius-sm: 4px;
  --border-radius-lg: 12px;
  --spacing-unit: 8px;
}
```

#### **4. Theme Switcher UI**
Add to PreferencesDialog:
```tsx
<div className="preference-group">
  <label>Theme</label>
  <select 
    value={currentTheme} 
    onChange={(e) => applyTheme(e.target.value)}
  >
    {THEMES.map(theme => (
      <option key={theme.id} value={theme.id}>
        {theme.name}
      </option>
    ))}
  </select>
  <p className="preference-description">
    {THEMES.find(t => t.id === currentTheme)?.description}
  </p>
</div>
```

---

## 🧹 Code Cleanup Checklist

### **1. Remove Old Code**
- [ ] Remove commented-out code blocks
- [ ] Remove unused imports
- [ ] Remove unused variables
- [ ] Remove debug console.logs (keep only error logging)
- [ ] Remove TODOs that are already done

### **2. Add Documentation**
- [ ] Add JSDoc comments to complex functions
- [ ] Document non-obvious logic
- [ ] Add file header comments for large modules
- [ ] Document type interfaces
- [ ] Add inline comments for tricky algorithms

### **3. Improve Type Safety**
- [ ] Replace `any` types with proper types
- [ ] Add strict null checks
- [ ] Use `unknown` instead of `any` where appropriate
- [ ] Define proper interfaces for API responses
- [ ] Use discriminated unions for state management

### **4. Extract Magic Numbers**
- [ ] Move hardcoded dimensions to constants
- [ ] Move hardcoded colors to theme variables
- [ ] Move timeout values to constants
- [ ] Move API endpoints to config

### **5. Consolidate Duplicate Logic**
- [ ] Extract repeated UI patterns to shared components
- [ ] Extract repeated logic to utility functions
- [ ] Create reusable hooks for common patterns
- [ ] Standardize error handling

### **6. Consistent Naming**
- [ ] Use consistent component naming (PascalCase)
- [ ] Use consistent function naming (camelCase)
- [ ] Use consistent file naming (match component name)
- [ ] Use consistent CSS class naming (kebab-case or BEM)

---

## 🚀 Implementation Plan

**REVISED ORDER**: Code cleanup/reorganization first, then theme system

### **Phase 1: Prepare (Day 1)** ✅ COMPLETED
- [x] Code review and analysis
- [x] Create reorganization plan (this document)
- [x] Get approval for plan
- [x] Create feature branch: `refactor/code-organization`
- [x] Create backup of current working state (tag: backup-before-refactor)

### **Phase 2: Group Dialogs (Days 1-2)** ✅ COMPLETED
- [x] Create `components/dialogs/` folder
- [x] Move all 10 dialog files to `dialogs/`
- [x] Update all imports across codebase
- [x] Test all dialogs still work (open, close, submit)
- [x] Build passes: `npm run build`
- [x] Commit: "Phase 2: Organize dialogs into dedicated folder" (b502fd97)

### **Phase 3: Reorganize Simple Components (Days 2-3)** ✅ COMPLETED
Move components with minimal refactoring:
- [x] **MenuBar**: Create `MenuBar/` folder
  - Move `MenuBar.tsx` → `MenuBar/index.tsx`
  - Move `MenuDropdown.tsx` → `MenuBar/MenuDropdown.tsx`
  - Update imports
  - Test: All menus work
  
- [x] **MaterialDatabase**: Create `MaterialDatabase/` folder
  - Move `MaterialDatabase.tsx` → `MaterialDatabase/index.tsx`
  - Update imports
  - Test: Material database opens, loads content
  
- [x] **ConnectionStatus**: Create `ConnectionStatus/` folder
  - Move `ConnectionStatus.tsx` → `ConnectionStatus/index.tsx`
  - Update imports
  - Test: Status indicator shows connection state

- [x] Build passes: `npm run build`
- [x] Commit: "Phase 3a: Reorganize simple components" (9090f1d5)
- [x] Commit: "Phase 3b: Move NodeInspectorControls" (88355a35)

### **Phase 4: Reorganize SceneOutliner (Days 3-4)** ✅ COMPLETED
- [x] Move `SceneOutliner.tsx` → `SceneOutliner/index.tsx`
- [x] Extract tree node rendering → `SceneOutliner/SceneTreeNode.tsx`
- [x] Extract node icons → `SceneOutliner/TreeNodeIcon.tsx`
- [x] Keep `SceneOutlinerContextMenu.tsx` in folder
- [x] Update all imports
- [x] Test: Scene tree loads, expand/collapse, selection works
- [x] Build passes: `npm run build`
- [x] Commit: "Phase 4: Reorganize SceneOutliner component" (2df18cb3)

### **Phase 5: Reorganize NodeInspector (Days 4-6)** ✅ COMPLETED
- [x] Move `NodeInspector.tsx` → `NodeInspector/index.tsx`
- [x] Move `NodeInspectorControls.tsx` → `NodeInspector/NodeInspectorControls.tsx`
- [x] Extract parameter editor → `NodeInspector/ParameterEditor.tsx`
- [x] Create `NodeInspector/editors/` folder
- [x] Extract type-specific editors:
  - `editors/BooleanEditor.tsx`
  - `editors/NumberEditor.tsx`
  - `editors/VectorEditor.tsx`
  - `editors/ColorEditor.tsx`
  - `editors/EnumEditor.tsx`
  - `editors/StringEditor.tsx`
- [x] Update all imports
- [x] Test: Parameter editing for all types works
- [x] Build passes: `npm run build`
- [x] Commit: "Phase 5: Reorganize NodeInspector component" (53ad854d)

### **Phase 6: Reorganize CallbackRenderViewport (Days 6-7)** ✅ COMPLETED
- [x] Move `CallbackRenderViewport.tsx` → `CallbackRenderViewport/index.tsx`
- [x] Extract viewport controls → `CallbackRenderViewport/ViewportControls.tsx`
- [x] Extract toolbar → `CallbackRenderViewport/ViewportToolbar.tsx`
- [x] Extract picking tools → `CallbackRenderViewport/PickingTools.tsx`
- [x] Keep `ViewportContextMenu.tsx` in folder
- [x] Update all imports
- [x] Test: Rendering, camera controls, picking tools work
- [x] Build passes: `npm run build`
- [x] Commit: "Phase 6: Reorganize CallbackRenderViewport component" (034678e3)

### **Phase 7: Reorganize RenderToolbar (Day 8)** ✅ COMPLETED
- [x] Move `RenderToolbar.tsx` → `RenderToolbar/index.tsx`
- [x] Extract playback controls → `RenderToolbar/PlaybackControls.tsx`
- [x] Extract render settings → `RenderToolbar/RenderSettings.tsx`
- [x] Extract viewport settings → `RenderToolbar/ViewportSettings.tsx`
- [x] Update all imports
- [x] Test: All toolbar controls work
- [x] Build passes: `npm run build`
- [x] Commit: "Phase 7: Reorganize RenderToolbar component" (66df923c)

### **Phase 8: Split OctaneClient Service (Days 9-11)** ✅ COMPLETED
This is the biggest refactor - 2071 lines to split:

- [x] Create `services/octane/` folder
- [x] Create modular service structure:
  ```
  services/
  ├── OctaneClient.ts           # Main orchestrator (429 lines)
  └── octane/
      ├── types.ts              # Shared interfaces & types
      ├── BaseService.ts        # Base class for all services
      ├── index.ts              # Service exports
      ├── ApiService.ts         # Core gRPC API communication
      ├── ConnectionService.ts  # WebSocket & connection mgmt
      ├── CameraService.ts      # 79 camera methods
      ├── RenderService.ts      # Render control & state
      ├── DeviceService.ts      # Device statistics
      ├── ViewportService.ts    # Viewport operations
      ├── SceneService.ts       # Scene tree building
      ├── NodeService.ts        # Node creation & operations
      ├── IconService.ts        # Icon caching
      ├── MaterialDatabaseService.ts  # LocalDB/LiveDB
      └── RenderExportService.ts      # Render exports
  ```

- [x] **Extracted all major services**:
  - Scene tree building (SceneService)
  - Node CRUD operations (NodeService)
  - Connection management (ConnectionService)
  - Camera operations (CameraService)
  - Parameter get/set (via NodeService)
  - Render control (RenderService)
  - File operations (NodeService)
  
- [x] Maintained backward compatibility via proxy methods
- [x] Preserved singleton pattern (getOctaneClient())
- [x] Removed unused code (updateSceneMap)
- [x] Full build passes: `npm run build` ✅
- [x] Commit: "Phase 8a: Split OctaneClient into modular services" (50a00402)

**Results**: 2071 lines → 429 (orchestrator) + 1877 (13 services) = 79% reduction in main file

### **Phase 9: Code Cleanup (Days 12-13)**
Now that structure is clean, clean up the code:

- [ ] **Remove old code**:
  - Remove all commented-out code blocks
  - Remove unused imports (use ESLint auto-fix)
  - Remove unused variables
  - Remove debug console.logs (keep error/warn)
  - Remove completed TODOs
  
- [ ] **Add documentation**:
  - Add JSDoc to all exported functions
  - Add JSDoc to complex internal functions
  - Add file header comments to large modules
  - Document non-obvious logic with inline comments
  - Add README.md to each major component folder
  
- [ ] **Improve type safety**:
  - Replace `any` with proper types
  - Add missing return types
  - Use `unknown` instead of `any` for generic code
  - Define interfaces for API responses
  - Enable strict TypeScript checks
  
- [ ] **Extract magic numbers**:
  - Move dimensions to constants
  - Move timeout values to constants
  - Move API endpoints to config
  - Move default values to constants

- [ ] Build passes: `npm run build`
- [ ] Commit: "Code cleanup: Remove old code, add documentation, improve types"

### **Phase 10: Theme System Foundation (Days 14-15)**
Now build theme system on clean codebase:

- [ ] Create `styles/themes/` structure
- [ ] Create `styles/themes/theme-variables.css` (all CSS var names)
- [ ] Rename `styles/octane-theme.css` → `styles/themes/octane-se.css`
- [ ] Refactor to use `[data-theme="octane-se"]` attribute selector
- [ ] Create `styles/themes/index.ts` (theme registry)
- [ ] Implement `hooks/useTheme.ts` hook
- [ ] Test: Can switch theme via code
- [ ] Build passes: `npm run build`
- [ ] Commit: "Add theme system foundation with Octane SE theme"

### **Phase 11: OTOY Studio Theme (Days 15-16)**
- [ ] Create `styles/themes/otoy-studio.css`
- [ ] Define OTOY Studio color palette (based on workflow-builder)
- [ ] Add OTOY Studio to theme registry
- [ ] Add theme selector UI to PreferencesDialog
- [ ] Test theme switching (should work instantly)
- [ ] Test all components in both themes
- [ ] Build passes: `npm run build`
- [ ] Commit: "Add OTOY Studio theme with theme switcher UI"

### **Phase 12: Testing & Validation (Days 17-18)**
- [ ] **Full manual testing**:
  - Test all dialogs in both themes
  - Test node graph in both themes
  - Test scene outliner in both themes
  - Test node inspector in both themes
  - Test viewport in both themes
  - Test menu bar in both themes
  
- [ ] **Functionality testing**:
  - Create nodes (all types)
  - Connect pins
  - Edit parameters (all types)
  - Camera controls
  - Picking tools
  - File operations (save/load)
  - Search functionality
  - Copy/paste operations
  
- [ ] **Performance testing**:
  - Large scene loading (300+ nodes)
  - Theme switching speed
  - UI responsiveness
  
- [ ] Fix any bugs found
- [ ] Build passes: `npm run build`
- [ ] All tests pass

### **Phase 13: Documentation & Merge (Days 18-19)**
- [ ] Update README.md:
  - Add "Recent Achievements" entry for reorganization
  - Add theme system documentation
  - Update file structure documentation
  
- [ ] Update QUICKSTART.md:
  - Add note about theme selection
  
- [ ] Update REPRO_PROMPT.md:
  - Update directory structure
  - Add theme system info
  - Update debugging guide
  
- [ ] Create migration guide for developers:
  - Document import path changes
  - Document new folder structure
  
- [ ] Final review of all changes
- [ ] Merge feature branch to main
- [ ] Push to remote
- [ ] Create release notes
- [ ] Commit: "Documentation updates for code reorganization and theme system"

---

## 📅 Timeline Summary

**Total Duration**: ~19 working days (~4 weeks)

**Week 1** (Days 1-5):
- Prepare
- Group dialogs
- Reorganize simple components
- Start SceneOutliner, NodeInspector

**Week 2** (Days 6-10):
- Finish NodeInspector
- CallbackRenderViewport
- RenderToolbar
- Start OctaneClient split

**Week 3** (Days 11-15):
- Finish OctaneClient split
- Code cleanup
- Theme system foundation
- Start OTOY Studio theme

**Week 4** (Days 16-19):
- Finish OTOY Studio theme
- Full testing
- Documentation
- Merge and release

---

## 📊 Success Metrics

### **Code Quality**
- ✅ No file > 800 lines (max complexity)
- ✅ All components in dedicated folders
- ✅ Zero `any` types (or < 5 with justification)
- ✅ All major functions have JSDoc comments
- ✅ Zero linting errors

### **Theme System**
- ✅ 2+ themes available
- ✅ Theme switching works instantly
- ✅ Theme preference persists
- ✅ All components respect theme variables
- ✅ Zero hardcoded colors in components

### **Developer Experience**
- ✅ Easy to find component files (folder structure)
- ✅ Easy to understand code (documentation)
- ✅ Easy to add new features (modular design)
- ✅ Easy to add new themes (CSS variables)

### **User Experience**
- ✅ No performance degradation
- ✅ All features still work
- ✅ Theme switching is smooth
- ✅ UI matches Octane SE (octane-se theme)
- ✅ UI matches OTOY Studio (otoy-studio theme)

---

## 🔮 Future Enhancements

### **Additional Themes**
- Light mode theme (if requested)
- High contrast theme (accessibility)
- Custom theme creator (advanced users)

### **Component Library**
- Storybook for component development
- Reusable UI component library
- Design system documentation

### **Advanced Refactoring**
- Convert to TypeScript strict mode
- Implement proper state management (Zustand/Redux)
- Add unit tests for critical logic
- Add E2E tests for workflows

---

## 📝 Notes

### **Breaking Changes**
- Import paths will change (but internal only)
- No user-facing breaking changes
- Theme localStorage key: `octaneWebR-theme`

### **Migration Guide**
For developers working on feature branches:
```bash
# After merge, update your branch
git checkout your-feature-branch
git rebase main

# Update imports (automated with script)
node scripts/update-imports.js

# Manual fixes may be needed for:
# - OctaneClient imports (now from services/OctaneClient/)
# - Component imports (now from component folders)
```

### **Rollback Plan**
If issues arise:
1. Revert merge commit
2. Fix issues in feature branch
3. Re-test thoroughly
4. Re-merge when stable

---

**Document Status**: Draft  
**Last Updated**: 2025-01-22  
**Approval Required**: Yes  
**Estimated Effort**: 5 weeks (1 developer)
