# Unused CSS Classes Report

This document lists CSS classes that appear to be unused in the current codebase.
These classes were found during the CSS refactoring where octane-theme.css was 
split into component-specific files.

## Summary
- **Total CSS classes**: 372
- **Used classes**: 256 (69%)
- **Unused classes**: 116 (31%)

## Recommended Actions

Before removing these classes, consider:
1. **Dynamic class names**: Some may be applied via template literals or computed properties
2. **Future features**: Some may be for features not yet implemented
3. **State classes**: Some may be state-based classes (e.g., `.connecting`, `.dragging`)
4. **Library classes**: Some may be from external libraries (e.g., `.react-flow*`)

## Categories of Unused Classes

### React Flow Library Classes (Can be removed - library not used)
```
.react-flow
.react-flow__background
.react-flow__edge
.react-flow__edge-interaction
.react-flow__edge-path
.react-flow__edges
.react-flow__handle
```

### Loading & Status Classes
```
.loading-screen
.loading-content
.loading-spinner
.loading-status
.loading-parameters
.status-dot
.status-indicator
```
Note: ConnectionStatus uses `.status-led` instead of `.status-dot`

### Modal & Dialog Classes
```
.modal-button
.modal-container
.modal-content
.modal-title
```
Note: Current modals may use different class names

### Node Inspector Classes
```
.inspector-dropdown-arrow
.inspector-header
.inspector-icon
.inspector-loading
.inspector-title
.node-inspector-header
.octane-inspector-dropdown-arrow
.octane-section
.octane-subsection
.parameter-checkbox-custom
.parameter-control-group
.parameter-control-wrapper
.parameter-dropdown
.parameter-icon
.parameter-label
.parameter-name
.parameter-number-input
.parameter-row
.parameter-section
.parameter-slider
.parameter-subsection
.parameter-unit
.parameter-value
.parameter-vector3
```
Note: NodeInspector uses similar but differently named classes

### Scene Outliner Classes
```
.tree-toggle
.scene-outliner-search
.scene-outliner-toolbar
.scene-error
.scene-success
.node-children
.node-visibility
.level-0 through .level-6
```
Note: SceneOutliner uses `.node-toggle` instead of `.tree-toggle`

### Node Graph Classes
```
.node-palette
.node-type-item
.node-type-label
.node-type-selector
.node-btn
.node-collapse-icon
.node-graph-controls
.node-graph-section
.node-parameter-row
.node-parameters
.node-selector
```

### Material Database & Preview Classes
```
.db-loading
.preview-btn
.preview-controls
.preview-header
.preview-sphere
.preview-viewport
.color-bar
.color-parameter
```

### Error & Action Classes
```
.error-actions
.error-icon
.error-state
.error-title
.viewport-error
.viewport-status
.scene-error
.scene-success
```

### Render Status Classes
```
.render-status-error
.render-status-finished
.render-status-paused
.render-status-rendering
.render-status-stopped
.render-controls
.render-info
```

### Panel & Control Classes
```
.panel-btn
.panel-controls
.panel-horz
.control-btn
.controls-spacer
.controls-spacer-vertical
.connection-controls
```

### UI & Layout Classes
```
.about-features
.category-arrow
.context-menus
.file-info
.file-path
.file-path-text
.file-stats
.grid-button
.has-children
.octane-logo-large
.param-increment
.progress-bar
.progress-bar-fill
.progress-text
.refresh-btn
.retry-button
.section-content
.section-header
.section-title
.section-toggle
.slider-switch
```

## Verification Steps

To verify a class before removal:
1. Search entire codebase: `grep -r "class-name" client/src`
2. Check for dynamic usage: Look for template literals like `\`...\${someVar}...\``
3. Test in browser: Inspect elements to see if class is applied
4. Check future feature plans: Review backlog for planned features

## Safe to Remove

These classes are confirmed unused and safe to remove:
- All `.react-flow*` classes (library not in use)
- Classes with no matches in grep search AND no related features in progress

## Needs Review

All other classes should be reviewed with the development team before removal
to ensure they're not needed for upcoming features.

---
Generated: January 2025
