# Octane WebR Icon Mapping Summary

## Overview
OctaneWebR now uses actual Octane UI icons extracted from the official Octane Standalone application, providing an authentic visual experience that matches the desktop application.

## Completed Work

### 1. Scene Outliner Icon Mappings
**File**: `client/src/constants/IconMapping.ts`
- **Total Node Types Mapped**: 278
- **Icons Applied**: Node type icons for all NT_ constants

#### Key Node Type Icon Mappings:
- **Render Kernels** (6 types): `RENDER KERNEL node.png`
  - NT_KERN_PATHTRACING, NT_KERN_DIRECTLIGHT, NT_KERN_PMC, NT_KERN_INFOCHANNEL, NT_KERN_PHOTON_TRACING, NT_KERN_LIGHT_SWITCH
  
- **Render Layers** (3 types): `render_layer.png`
  - NT_RENDER_LAYER, NT_RENDER_LAYER_MASK_AOV, NT_RENDER_LAYER_MASK_LAYER
  
- **Render AOVs** (4 types): `aov-output.png` and `aov-output-group.png`
  - NT_RENDER_AOV → `aov-output.png`
  - NT_RENDER_AOV_GROUP → `aov-output-group.png`
  
- **Animation Settings** (4 types): `animation_settings_node.png`
  - NT_ANIMATION_SETTINGS, NT_ANIMATION_SETTINGS_IN, NT_ANIMATION_SETTINGS_OUT, NT_ANIMATION_SETTINGS_LINK
  
- **Post Processing** (3 types): `POSTPROC node.png`
  - NT_POST_PROCESSING, NT_POSTPROCESSING_IN, NT_POSTPROCESSING_OUT
  
- **Output AOVs** (~40 types): `aov-output-group.png`
  - All NT_OUTPUT_AOV_* variants (ALPHA, AMBIENT, BEAUTY, DIFFUSE, etc.)

### 2. Toolbar Icon Implementation
**Files**:
- `client/src/constants/ToolbarIconMapping.ts` - Icon mappings
- `client/src/components/UI/ToolbarIcon.tsx` - Icon component
- `client/src/components/RenderToolbar/index.tsx` - Updated to use icons
- `client/src/styles/octane-theme.css` - Icon styling

#### Toolbar Icons Mapped (40+ actions):

##### Render Controls
- `start-render` → `RENDER KERNEL node.png`
- `pause-render` → `PAUSE window.png`
- `stop-render` → `STOP window.png`
- `restart-render` → `STOP window.png` (placeholder)
- `realtime-mode` → `RENDER TARGET node.png`
- `clay-mode` → `CLAY window.png`
- `clay-mode-off` → `CLAY OFF window.png`
- `subsampling-menu` → `SUBSAMPLING window.png`

##### Camera/Picking Tools
- `pick-focus` → `MOUSE pipette focus.png`
- `pick-white-balance` → `MOUSE pipette color.png`
- `pick-material` → `MOUSE pipette material.png`
- `pick-object` → `MOUSE pipette object.png`
- `pick-camera-target` → `MOUSE pipette zoom.png`
- `render-region` → `MOUSE pipette region.png`
- `film-region` → `MOUSE pipette film region.png`
- `camera-presets` → `camera_view_presets.png`
- `recenter-view` → `RECENTER window.png`

##### Export and Save
- `copy-clipboard` → `COPY TO CLIPBOARD image.png`
- `save-render` → `SAVE RENDER general.png`
- `export-passes` → `render_passes_export.png`
- `background-image` → `Background.png`

##### Viewport Controls
- `viewport-resolution-lock` → `LOCK_RES-3 window.png`
- `lock-viewport` → `LOCK window.png`
- `unlock-viewport` → `UNLOCK window.png`

##### Object Manipulation (Gizmos)
- `object-control-alignment-world` → `GIZMO world mode.png`
- `object-control-alignment-local` → `GIZMO local mode.png`
- `object-control-alignment` → `GIZMO world mode.png` (default)
- `translate-gizmo` → `GIZMO move frame.png`
- `rotate-gizmo` → `GIZMO rotate frame.png`
- `scale-gizmo` → `GIZMO scale frame.png`
- `world-coordinate` → `GIZMO world indicator.png`

##### Render Priority
- `render-priority-low` → `PRIORITY low.png`
- `render-priority-normal` → `PRIORITY med.png`
- `render-priority-high` → `PRIORITY high.png`

### 3. Icon Styling
**File**: `client/src/styles/octane-theme.css`

```css
.toolbar-icon {
    width: 16px;
    height: 16px;
    object-fit: contain;
    pointer-events: none;
    user-select: none;
    filter: brightness(0.85);
}

.toolbar-icon-btn:hover .toolbar-icon {
    filter: brightness(1.0);
}

.toolbar-icon-btn.active .toolbar-icon {
    filter: brightness(1.2);
}
```

## Icon Resources

### Total Icons Available
- **386 icon files** in `client/public/icons/`
- PNG format, various sizes (typically 16x16 to 32x32)
- Extracted from official Octane Standalone application

### Icon Categories
1. **Node Type Icons** (e.g., `CAMERA node.png`, `MATERIAL_DIFFUSE node.png`)
2. **Window Icons** (e.g., `PAUSE window.png`, `STOP window.png`)
3. **General Icons** (e.g., `SAVE RENDER general.png`)
4. **Mouse/Cursor Icons** (e.g., `MOUSE pipette focus.png`)
5. **Gizmo Icons** (e.g., `GIZMO move frame.png`)
6. **Parameter Icons** (e.g., `PARAM_BOOLEAN.png`, `PARAM_FLOAT.png`)

### Commonly Used Icon Patterns
```
[Category] [Descriptor] [Type].png

Examples:
- RENDER KERNEL node.png
- MOUSE pipette focus.png  
- GIZMO world mode.png
- PARAM_BOOLEAN.png
- LOCK window.png
```

## Future Enhancement Opportunities

### 1. Menu Bar Icons
**File**: `client/src/components/MenuBar/index.tsx`
- File menu icons (New, Open, Save, Import, Export)
- Edit menu icons (Undo, Redo, Cut, Copy, Paste)
- View menu icons (Panels, Reset Layout)
- Script menu icons (Batch Render, Daylight, Turntable)

**Available Icons**:
```
- NEW FILE general.png
- OPEN FILE general.png
- SAVE FILE general.png
- IMPORT general.png
- EXPORT general.png
- UNDO general.png
- REDO general.png
- CUT general.png
- COPY general.png
- PASTE general.png
```

### 2. Dialog Icons
- PreferencesDialog → `PREFERENCES general.png`
- SaveRenderDialog → `SAVE RENDER general.png`
- ExportPassesDialog → `render_passes_export.png`
- BatchRenderingDialog → `BATCH RENDER general.png`

### 3. Context Menu Icons
**File**: `client/src/components/NodeInspector/NodeInspectorContextMenu.tsx`
- Add icons to context menu items
- Delete → `delete.png`
- Copy → `copy-general.png`
- Paste → `paste-general.png`

### 4. Node Graph Editor Icons
**File**: `client/src/components/NodeGraph/NodeGraphToolbar.tsx`
- Currently using SVG icons
- Could replace with actual Octane icons:
  - Recenter → `RECENTER window.png`
  - Grid → `GRID window.png`
  - Preview windows → Various preview icons

### 5. Parameter Type Icons
**File**: `client/src/constants/OctaneIconMapper.ts`
- Already has parameter type mappings
- Apply to Node Inspector parameter displays
- Icons available for all Octane parameter types:
  - PARAM_BOOLEAN.png, PARAM_FLOAT.png, PARAM_INT.png
  - PARAM_TEXTURE.png, PARAM_MATERIAL.png
  - PARAM_COLOR.png, PARAM_TRANSFORM.png
  - etc.

## Implementation Pattern

### Adding New Icon Mappings

1. **Find the icon file**:
   ```bash
   ls client/public/icons/ | grep -i "keyword"
   ```

2. **Add to mapping file**:
   ```typescript
   // In ToolbarIconMapping.ts or IconMapping.ts
   export const ICON_MAP = {
     'action-id': 'ICON_FILE_NAME.png',
   };
   ```

3. **Use in component**:
   ```tsx
   import { ToolbarIcon } from '../UI/ToolbarIcon';
   
   <button>
     <ToolbarIcon id="action-id" fallback="◯" alt="Action Name" />
   </button>
   ```

4. **Add CSS if needed**:
   ```css
   .custom-icon-style {
     width: 20px;
     height: 20px;
   }
   ```

## Commit History

1. **0bb611e7** - "fix: Update scene outliner icon mappings to match Octane UI"
   - Scene outliner icon mappings
   - Kernel, render layer, AOV, animation, post-processing icons

2. **2631a551** - "feat: Add actual Octane UI icons to RenderToolbar"
   - Toolbar icon mapping system
   - ToolbarIcon component
   - RenderToolbar icon integration
   - CSS styling for icons

## Documentation Reference

### Octane Standalone Manual
- **Base URL**: https://docs.otoy.com/standaloneSE/
- **Interface Layout**: https://docs.otoy.com/standaloneSE/InterfaceLayout.html
- **Render Viewport**: https://docs.otoy.com/standaloneSE/TheRenderViewport.html
- **Scene Outliner**: https://docs.otoy.com/standaloneSE/TheSceneOutliner.html
- **Graph Editor**: https://docs.otoy.com/standaloneSE/TheGraphEditor.html

### Icon Extraction
Icons were extracted from the official Octane Standalone application UI and matched with documentation screenshots to ensure accuracy.

---

**Last Updated**: January 23, 2025  
**Total Icons**: 386 available, 318 mapped (278 node types + 40 toolbar actions)  
**Documentation Source**: Octane Render Standalone Manual v2023+
