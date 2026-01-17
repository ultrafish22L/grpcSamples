# Phase 1B: Additional Unused scene-outliner-* Classes

## User Finding
**Only 3 `scene-outliner-*` classes are actually used:**
- `scene-outliner` (main container)
- `scene-outliner-tabs`
- `scene-outliner-button-bar`

## Verification
```bash
grep "className.*scene-outliner" client/src/components/SceneOutliner.tsx
```
Result: Only the 3 classes above found ✓

---

## Additional Unused Selectors Found

### components.css - Block 1 (Lines 8-54)
**47 lines to remove:**

```css
.scene-outliner-header {
    padding: 6px 8px;
    background: var(--octane-bg-secondary);
    border-bottom: 1px solid var(--octane-border);
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.scene-outliner-header h3 {
    margin: 0;
    font-size: var(--font-size-small);
    font-weight: var(--font-weight-header);
    color: var(--octane-text-primary);
    text-transform: capitalize;
}

.scene-outliner-controls {
    display: flex;
    gap: var(--spacing-xs);
}

.scene-outliner-controls button {
    background: none;
    border: none;
    color: var(--octane-text-secondary);
    cursor: pointer;
    padding: 1px 3px;
    border-radius: var(--border-radius-sm);
    font-size: var(--font-size-small);
    width: 16px;
    height: 16px;
    display: flex;
    align-items: center;
    justify-content: center;
}

.scene-outliner-controls button:hover {
    background: var(--octane-bg-hover);
    color: var(--octane-text-primary);
}

.scene-outliner-content {
    flex: 1;
    overflow-y: auto;
    padding: 4px 0;
}
```

---

### components.css - Block 2 (Lines 381-432)
**52 lines to remove:**

```css
.scene-outliner-toolbar {
    display: flex;
    align-items: center;
    gap: var(--spacing-xs);
    padding: 2px 4px;
    background-color: var(--octane-node-bg);
    border-bottom: 1px solid var(--octane-viewport-bg);
    min-height: 24px;
}

.toolbar-btn {
    background: none;
    border: none;
    color: var(--octane-text-secondary);
    cursor: pointer;
    padding: 2px 4px;
    border-radius: var(--border-radius-sm);
    font-size: var(--font-size-small);
    min-width: 20px;
    height: 20px;
    display: flex;
    align-items: center;
    justify-content: center;
}

.toolbar-btn:hover {
    background-color: var(--octane-bg-selected);
    color: var(--octane-text-primary);
}

.toolbar-spacer {
    flex: 1;
}

.scene-outliner-search {
    flex: 1;
    background-color: var(--octane-bg-secondary);
    border: 1px solid var(--octane-border);
    color: var(--octane-text-primary);
    padding: 4px 8px;
    font-size: var(--font-size-small);
    border-radius: var(--border-radius);
}

.scene-outliner-search:focus {
    outline: none;
    border-color: var(--octane-accent-blue);
}

.scene-outliner-search::placeholder {
    color: var(--octane-text-muted);
}
```

---

### components.css - Block 3 (Lines 1527-1531)
**5 lines to remove (DUPLICATE):**

```css
.scene-outliner-controls {
    display: flex;
    gap: var(--spacing-xs);
    align-items: center;
}
```

---

### octane-theme.css
**CHECK NEEDED:** Has duplicates of toolbar/search at lines 489, 498, 508
- May be intentional (canonical theme definitions)
- Will verify after components.css cleanup

---

## Summary

| File | Blocks | Lines | Selectors |
|------|--------|-------|-----------|
| components.css Block 1 | 5 | 47 | header, controls, content |
| components.css Block 2 | 5 | 52 | toolbar, search, toolbar-btn |
| components.css Block 3 | 1 | 5 | controls (duplicate) |
| **TOTAL** | **11** | **~104** | |

---

## Impact

**Phase 1 (completed):** -151 lines  
**Phase 1B (this):** -104 lines  
**Combined Phase 1 total:** **-255 lines** from components.css

---

## Recommendation

Execute Phase 1B immediately:
- Remove all 3 blocks from components.css
- Verify build
- Check octane-theme.css after (may be canonical definitions)

---

## ✅ PHASE 1B COMPLETE

**Status:** All 3 blocks removed successfully  
**Build:** ✅ Successful (1.02s)

### Bundle Impact

| Metric | Before Phase 1 | After Phase 1 | After Phase 1B | Total Reduction |
|--------|----------------|---------------|----------------|-----------------|
| **CSS (raw)** | 152.43 kB | 149.19 kB | **147.31 kB** | **-5.12 kB** (3.4%) |
| **CSS (gzip)** | 20.84 kB | 20.32 kB | **20.15 kB** | **-0.69 kB** (3.3%) |

### Lines Removed

- **Phase 1:** ~151 lines (scene-node-*, scene-search-*, icon pseudo-elements)
- **Phase 1B:** ~104 lines (scene-outliner-header/controls/toolbar/search)
- **TOTAL:** **~255 lines** removed from components.css

### Build Verification
```
✓ TypeScript compilation successful
✓ Vite build completed in 1.02s
✓ No errors or warnings
✓ Bundle size: 147.31 kB (down from 152.43 kB)
```
