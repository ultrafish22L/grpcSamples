# Unused CSS Removal Plan

## Overview
**Total unused selectors found:** 12  
**Estimated lines to remove:** ~150 lines  
**Files affected:** 3 (components.css, layout.css, app.css)

## Why These Are Unused

The SceneOutliner component was refactored to use generic tree classes:
- Current: `tree-node`, `node-content`, `node-toggle`, `node-icon`, `node-name`
- Old (unused): `scene-node-*` classes

Icons are now rendered as **emoji text content** in SceneOutliner.tsx (line 81), NOT CSS pseudo-elements.

---

## File 1: components.css

### Location: Lines 50-75 (26 lines)
**Unused selectors:** `.scene-search-container`, `.scene-search-box` and variants

```css
.scene-search-container {
    padding: 4px 6px;
    border-bottom: 1px solid var(--octane-border);
    background: var(--octane-bg-primary);
}

.scene-search-box {
    width: 100%;
    background: var(--octane-bg-secondary);
    border: 1px solid var(--octane-border);
    border-radius: var(--border-radius-sm);
    padding: 3px 6px;
    font-size: var(--font-size-small);
    color: var(--octane-text-primary);
    outline: none;
}

.scene-search-box:focus {
    border-color: var(--octane-accent-red);
    box-shadow: 0 0 0 1px var(--octane-accent-red);
}

.scene-search-box::placeholder {
    color: var(--octane-text-secondary);
    font-style: italic;
}
```

**Reason:** No search box implemented in SceneOutliner

---

### Location: Lines 97-130 (34 lines)
**Unused selector:** `.scene-node-expand` and variants

```css
.scene-node-expand {
    width: 12px;
    text-align: center;
    cursor: pointer;
    color: var(--octane-text-secondary);
    font-size: var(--font-size-xs);
    font-family: var(--font-family-mono);
    line-height: var(--line-height-none);
    flex-shrink: 0;
}

.scene-node-expand:hover {
    color: var(--octane-text-primary);
}

/* Disable pseudo-element symbols for database tree nodes (they have HTML symbols) */
.scene-tab-content .node-toggle::before,
.scene-tab-content .node-toggle::after {
    content: "" !important;
    display: none !important;
}

/* Keep pseudo-element symbols only for main scene tree */
.scene-tree .scene-node-expand.expanded::before {
    content: "▼";
}

.scene-tree .scene-node-expand.collapsed::before {
    content: "▶";
}

.scene-tree .scene-node-expand.leaf::before {
    content: "";
}
```

**Reason:** Using `.node-toggle` instead, with text content (+/−) not pseudo-elements

---

### Location: Lines 132-141 (10 lines)
**Unused selector:** `.scene-node-icon`

```css
.scene-node-icon {
    width: 16px;
    height: 16px;
    margin-right: 4px;
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: var(--font-size-small);
    flex-shrink: 0;
}
```

**Reason:** Using `.node-icon` instead

---

### Location: Lines 143-151 (9 lines)
**Unused selector:** `.scene-node-name`

```css
.scene-node-name {
    flex: 1;
    color: var(--octane-text-primary);
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
    font-weight: var(--font-weight-normal);
    font-size: var(--font-size-small);
}
```

**Reason:** Using `.node-name` instead

---

### Location: Lines 153-163 (11 lines)
**Unused selector:** `.scene-node-handle`

```css
.scene-node-handle {
    color: var(--octane-text-secondary);
    font-size: var(--font-size-xs);
    margin-left: 4px;
    font-family: var(--font-family-mono);
    flex-shrink: 0;
}

.scene-node.selected .scene-node-handle {
    color: var(--octane-highlight-strong);
}
```

**Reason:** Not displaying node handles in current implementation

---

### Location: Lines 169-218 (50 lines) ⚠️ **BIGGEST BLOCK**
**Unused selectors:** `.scene-node-icon.*` type-specific styles

```css
/* Node type specific icons */
.scene-node-icon.scene { color: inherit; }
.scene-node-icon.scene::before { content: "🌍"; }
.scene-node-icon.render-target::before { content: "🎯"; color: var(--octane-accent-red); }
.scene-node-icon.camera::before { content: "📷"; }
.scene-node-icon.light::before { content: "💡"; color: var(--octane-text-primary)f44; }
.scene-node-icon.geometry::before { content: "🔷"; }
.scene-node-icon.material::before { content: "🎨"; }
.scene-node-icon.texture::before { content: "🖼️"; }
.scene-node-icon.group::before { content: "📂"; }
.scene-node-icon.mesh::before { content: "▲"; }
.scene-node-icon.transform::before { content: "🔄"; color: var(--octane-accent-green); }
.scene-node-icon.environment::before { content: "🌅"; color: var(--octane-accent-blue); }
.scene-node-icon.object::before { content: "⬜"; }
.scene-node-icon.node::before { content: "⚪"; }
.scene-node-icon.unknown::before { content: "❓"; }

/* Hide any text content inside icon spans when using CSS icons */
.scene-node-icon.scene,
.scene-node-icon.render-target,
.scene-node-icon.camera,
.scene-node-icon.light,
.scene-node-icon.geometry,
.scene-node-icon.material,
.scene-node-icon.texture,
.scene-node-icon.group,
.scene-node-icon.mesh,
.scene-node-icon.transform,
.scene-node-icon.environment,
.scene-node-icon.object,
.scene-node-icon.node,
.scene-node-icon.unknown {
    font-size: 0; /* Hide text content */
}

.scene-node-icon.scene::before,
.scene-node-icon.render-target::before,
.scene-node-icon.camera::before,
.scene-node-icon.light::before,
.scene-node-icon.geometry::before,
.scene-node-icon.material::before,
.scene-node-icon.texture::before,
.scene-node-icon.group::before,
.scene-node-icon.mesh::before,
.scene-node-icon.transform::before,
.scene-node-icon.environment::before,
.scene-node-icon.object::before,
.scene-node-icon.node::before,
.scene-node-icon.unknown::before {
    font-size: var(--font-size-small); /* Restore font size for pseudo-element */
}
```

**Reason:** Icons rendered as TEXT in React (via OctaneIconMapper), not CSS pseudo-elements

---

### Location: Lines 220-222 (3 lines)
**Unused selector:** `.scene-node-children`

```css
.scene-node-children {
    margin-left: 0;
}
```

**Reason:** Not used in current tree structure

---

**components.css TOTAL:** ~143 lines

---

## File 2: layout.css

### Location: Lines 348-353 (6 lines)
**Unused selector:** `.scene-node-indent`

```css
.scene-node-indent {
    width: 16px;
    display: flex;
    align-items: center;
    justify-content: center;
}
```

**Reason:** Using `level-{depth}` classes with padding for indentation

---

### Location: Lines 355-363 (9 lines)
**Unused selector:** `.scene-node-toggle`

```css
.scene-node-toggle {
    font-size: var(--font-size-xs);
    cursor: pointer;
    transition: transform 0.15s ease;
}

.scene-node.collapsed .scene-node-toggle {
    transform: rotate(-90deg);
}
```

**Reason:** Using `.node-toggle` with `expanded`/`collapsed` classes

---

### Location: Lines 367-373 (7 lines)
**Unused selector:** `.scene-node-label`

```css
.scene-node-label {
    flex: 1;
    color: var(--octane-text-primary);
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
}
```

**Reason:** Using `.node-name` instead

---

### Location: Lines 375-391 (17 lines)
**Unused selector:** `.scene-node-visibility`

```css
.scene-node-visibility {
    width: 16px;
    height: 16px;
    cursor: pointer;
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: var(--font-size-xs);
    color: var(--octane-text-secondary);
    border-radius: var(--border-radius);
    transition: all 0.15s ease;
}

.scene-node-visibility:hover {
    background-color: var(--octane-bg-hover);
    color: var(--octane-text-primary);
}
```

**Reason:** Visibility toggle not implemented

---

**layout.css TOTAL:** ~39 lines

---

## File 3: app.css

### Location: Lines 267-269 (3 lines)
**Unused selector:** `.scene-tree-item`

```css
.scene-tree-item {
  margin: 2px 0;
}
```

**Reason:** Using `.tree-node` directly, no wrapper needed

---

**app.css TOTAL:** ~3 lines

---

## Summary

| File | Selectors | Lines | Priority |
|------|-----------|-------|----------|
| **components.css** | 8 | ~143 | 🔴 HIGH (biggest impact) |
| **layout.css** | 4 | ~39 | 🟡 MEDIUM |
| **app.css** | 1 | ~3 | 🟢 LOW |
| **TOTAL** | **12** | **~185** | |

---

## Recommended Approach

### Phase 1: components.css (Highest Impact)
Remove all unused `scene-node-*` and `scene-search-*` selectors:
- Lines 50-75 (search)
- Lines 97-130 (expand)
- Lines 132-222 (node styles + icons)

### Phase 2: layout.css
Remove structural `scene-node-*` selectors:
- Lines 348-391

### Phase 3: app.css
Remove trivial `.scene-tree-item`:
- Lines 267-269

### Verification After Each Phase
```bash
npm run build  # Check TypeScript + bundle size
# Visual test: Scene Outliner rendering
```

---

## Expected Impact

- **Bundle size:** ~185 lines removed (~4-5 KB raw, minimal gzip impact)
- **Maintainability:** ✅ Eliminates confusion between old and new class names
- **Risk:** 🟢 LOW - All confirmed unused by code search
