# octaneWebR - Code Review & Reorganization Plan

**Date**: 2025-01-22  
**Status**: Planning Phase  
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

### **Phase 1: Prepare (Week 1)**
- [x] Code review and analysis
- [ ] Create reorganization plan (this document)
- [ ] Get approval for plan
- [ ] Create feature branch: `refactor/code-organization`

### **Phase 2: Theme System (Week 1-2)**
- [ ] Create `styles/themes/` structure
- [ ] Rename `octane-theme.css` → `octane-se.css`
- [ ] Create `theme-variables.css` with all variable names
- [ ] Create `otoy-studio.css` with OTOY Studio theme
- [ ] Implement `useTheme` hook
- [ ] Add theme switcher to PreferencesDialog
- [ ] Test theme switching
- [ ] Commit: "Add configurable theme system with OTOY Studio theme"

### **Phase 3: Group Dialogs (Week 2)**
- [ ] Create `components/dialogs/` folder
- [ ] Move all dialog files to dialogs/
- [ ] Update all imports
- [ ] Test all dialogs still work
- [ ] Commit: "Organize dialogs into dedicated folder"

### **Phase 4: Reorganize Components (Week 2-3)**
- [ ] NodeInspector: Move files, extract editors
- [ ] SceneOutliner: Move files, extract tree node
- [ ] CallbackRenderViewport: Move files, extract controls
- [ ] RenderToolbar: Move files, extract controls
- [ ] MenuBar: Move files
- [ ] MaterialDatabase: Move files
- [ ] Test each component after reorganization
- [ ] Commit per component: "Reorganize [ComponentName] into dedicated folder"

### **Phase 5: Split OctaneClient (Week 3-4)**
- [ ] Create `services/OctaneClient/` folder
- [ ] Extract SceneTreeBuilder.ts
- [ ] Extract NodeOperations.ts
- [ ] Extract ConnectionManager.ts
- [ ] Extract ParameterManager.ts
- [ ] Extract FileOperations.ts
- [ ] Keep main OctaneClient.ts as facade
- [ ] Update all imports
- [ ] Test all functionality
- [ ] Commit: "Split OctaneClient into focused modules"

### **Phase 6: Code Cleanup (Week 4-5)**
- [ ] Remove commented code
- [ ] Add JSDoc comments
- [ ] Improve type safety
- [ ] Extract magic numbers
- [ ] Consolidate duplicate logic
- [ ] Run full test suite
- [ ] Commit: "Code cleanup and documentation improvements"

### **Phase 7: Testing & Validation (Week 5)**
- [ ] Full manual testing of all features
- [ ] Test theme switching
- [ ] Test all dialogs
- [ ] Test node operations
- [ ] Test scene tree
- [ ] Test viewport
- [ ] Performance testing
- [ ] Fix any bugs found

### **Phase 8: Merge & Documentation (Week 5)**
- [ ] Update README.md with theme info
- [ ] Update QUICKSTART.md
- [ ] Update REPRO_PROMPT.md with new structure
- [ ] Merge to main
- [ ] Push to remote
- [ ] Create release notes

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
