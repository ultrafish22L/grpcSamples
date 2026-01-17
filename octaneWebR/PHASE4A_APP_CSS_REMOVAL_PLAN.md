# Phase 4a: app.css Unused Selector Removal

## Summary

**Unused selectors found:** 22 (21 found + 1 manual)
**Total lines to remove:** ~134

### Breakdown by Category:

| Category | Selectors | Lines |
|----------|-----------|-------|
| App Structure | 5 | 36 |
| Outliner/Tree | 7 | 33 |
| Properties/Panels | 5 | 28 |
| Status/Footer | 5 | 33 |
| **TOTAL** | **22** | **~134** |

---

## Selectors to Remove

### .app-footer

**Lines 184-194** (11 lines)
```css
.app-footer {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 8...
```

### .app-header

**Lines 32-40** (9 lines)
```css
.app-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 1...
```

### .app-main

**Lines 92-96** (5 lines)
```css
.app-main {
  display: flex;
  flex: 1;
  overflow: hidden;
}
```

### .app-subtitle

**Lines 49-53** (5 lines)
```css
.app-subtitle {
  font-size: var(--font-size-normal);
  color: var(--octane-text-muted);
  margin-le...
```

### .footer-info

**Lines 196-198** (3 lines)
```css
.footer-info {
  font-family: 'Courier New', monospace;
}
```

### .frame-count

**Lines 222-224** (3 lines)
```css
.frame-count {
  color: var(--octane-accent);
}
```

### .node-properties

**Lines 176-181** (6 lines)
```css
.node-properties {
  min-height: 200px;
  padding: 10px;
  background: var(--octane-bg-darker);
  bo...
```

### .octane-app

**Lines 24-29** (6 lines)
```css
.octane-app {
  display: flex;
  flex-direction: column;
  width: 100%;
  height: 100%;
}
```

### .outliner-header

**Lines 229-234** (6 lines)
```css
.outliner-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margi...
```

### .outliner-tree

**Lines 259-265** (7 lines)
```css
.outliner-tree {
  flex: 1;
  overflow-y: auto;
  background: var(--octane-bg-darker);
  border-radi...
```

### .panel-section

**Lines 161-164** (4 lines)
```css
.panel-section {
  padding: 15px;
  border-bottom: 1px solid var(--octane-border);
}
```

### .property

**Lines 332-338** (7 lines)
```css
.property {
  display: flex;
  justify-content: space-between;
  padding: 6px 0;
  border-bottom: 1p...
```

### .property-group

**Lines 320-322** (3 lines)
```css
.property-group {
  margin-bottom: 15px;
}
```

### .raw-data

**Lines 349-358** (10 lines)
```css
.raw-data {
  font-family: 'Courier New', monospace;
  font-size: var(--font-size-small);
  color: v...
```

### .side-panel

**Lines 152-159** (8 lines)
```css
.side-panel {
  width: 320px;
  background: var(--octane-viewport-bg);
  border-left: 1px solid var(...
```

### .status-message

**Lines 133-139** (7 lines)
```css
.status-message {
  text-align: center;
  padding: 40px;
  background: var(--octane-viewport-bg);
  ...
```

### .tree-expand

**Lines 285-290** (6 lines)
```css
.tree-expand {
  display: inline-block;
  width: 16px;
  cursor: pointer;
  user-select: none;
}
```

### .tree-icon

**Lines 292-294** (3 lines)
```css
.tree-icon {
  margin: 0 6px;
}
```

### .tree-label

**Lines 296-299** (4 lines)
```css
.tree-label {
  flex: 1;
  color: var(--octane-text-secondary);
}
```

### .tree-type

**Lines 301-305** (5 lines)
```css
.tree-type {
  font-size: var(--font-size-small);
  color: var(--octane-text-muted);
  font-style: i...
```

### .viewport-status

**Lines 211-220** (10 lines)
```css
.viewport-status {
  display: flex;
  justify-content: space-between;
  padding: 8px 12px;
  backgro...
```

### .app-title h1

**Lines 42-47** (6 lines)
```css
.app-title h1 {
  font-size: var(--font-size-icon);
  font-weight: 600;
  color: var(--octane-accent);
  margin: 0;
}
```

---

## Verification

All 22 selectors verified as unused:
```bash
grep -r "selector-name" client/src --include="*.ts" --include="*.tsx"
# Exit code 1 (not found) for all selectors ✓
```

---

## Removal Strategy

**Approach:** Remove from bottom to top (avoids line number shifting)

**Order:**
1. Lines 332-358 (bottom section)
2. Lines 259-305 (middle section)  
3. Lines 184-224 (lower-middle section)
4. Lines 133-164 (upper-middle section)
5. Lines 24-96 (top section)

**Build verification after removal:** TypeScript + Vite build test
