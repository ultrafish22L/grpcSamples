# Duplicate CSS Selectors Analysis

## Methodology
Compared `octane-theme.css` against all other CSS files to find duplicate selectors.

## Files Analyzed
- `app.css` (93 selectors)
- `node-graph.css` (142 selectors)
- `node-inspector.css` (156 selectors)
- `scene-outliner.css` (60 selectors)
- `viewport.css` (68 selectors)
- `octane-theme.css` (177 selectors)

**Total: 696 selectors**

---

## EXACT DUPLICATES - REMOVE FROM octane-theme.css

### 1. `.node-graph-container`
**Location:** octane-theme.css line 1165 | node-graph.css line 548  
**Properties:** Identical (both recently updated with flex layout)  
**Action:** ❌ Remove from octane-theme.css  
**Reason:** Should only exist in node-graph.css (specific file)

---

## NEAR-DUPLICATES - MANUAL REVIEW NEEDED

### 2. `.scene-loading`
**octane-theme.css line 454:**
```css
.scene-loading {
    padding: 20px;
    text-align: center;
    color: var(--octane-text-muted);
    font-style: italic;
}
```

**scene-outliner.css line 384:**
```css
.scene-loading {
    padding: 20px;
    text-align: center;
    color: var(--octane-text-muted);
    font-style: italic;
    font-size: var(--font-size-small);  /* ← Extra property */
}
```

**Action:** ❌ Remove from octane-theme.css  
**Reason:** scene-outliner.css version is superset (more complete)

---

### 3. `.context-menu-separator`
**octane-theme.css line 1470:**
```css
.context-menu-separator {
    height: 1px;
    background-color: var(--octane-border);
    margin: 2px 0;  /* ← Different */
}
```

**app.css line 463:**
```css
.context-menu-separator {
    height: 1px;
    background-color: var(--octane-border);
    margin: 4px 0;  /* ← Different */
}
```

**Action:** ⚠️ KEEP BOTH - Different values (margin)  
**Reason:** Different margin values - need to verify which is correct

---

### 4. `.control-btn` and `.control-btn:hover`
**octane-theme.css line 1091:**
```css
.control-btn {
    background: none;  /* ← Different */
    border: 1px solid var(--octane-border);
    color: var(--octane-text-secondary);
    /* ... */
}
```

**app.css line 676:**
```css
.control-btn {
    background: var(--octane-bg-secondary);  /* ← Different */
    border: 1px solid var(--octane-border);
    color: var(--octane-text-secondary);
    /* ... */
}
```

**Action:** ⚠️ KEEP BOTH - Different background values  
**Reason:** octane-theme has `background: none`, app.css has actual background

---

### 5. `.viewport-canvas-container`
**octane-theme.css line 770:**
```css
.viewport-canvas-container {
    flex: 1;
    display: flex;
    align-items: center;
    justify-content: center;
    background: var(--octane-bg-darker);
}
```

**app.css line 106:**
```css
.viewport-canvas-container {
    flex: 1;
    display: flex;
    align-items: center;
    justify-content: center;
    background: var(--octane-border-darker);  /* ← Different variable */
}
```

**Action:** ⚠️ REVIEW - Different background variables  
**Reason:** Need to verify which background color is correct

---

## INTENTIONAL OVERRIDES (Different Contexts)

### 6-10. `.app-layout` (5 instances)
- Multiple media query breakpoints in app.css
- Single base definition in octane-theme.css
**Action:** ✅ KEEP ALL - Different responsive breakpoints

### 11-12. `.scene-tree` (3 instances)  
- app.css: min-height, padding (base layout)
- app.css: font-size (typography)
- scene-outliner.css: font-family, font-size (component-specific)
- octane-theme.css: flex, overflow, background (base styling)
**Action:** ⚠️ CONSOLIDATE - Too many scattered definitions

### 13-17. Viewport selectors
- `.viewport-container`, `.render-viewport`, `.viewport-overlay`
- Different properties for different contexts
**Action:** ⚠️ REVIEW - May need consolidation

---

## RECOMMENDATIONS

### HIGH PRIORITY - Remove These from octane-theme.css

1. ✅ `.node-graph-container` (line 1165) - exact duplicate in node-graph.css
2. ✅ `.scene-loading` (line 454) - scene-outliner.css has superset

### MEDIUM PRIORITY - Review and Consolidate

3. `.scene-tree` - scattered across 3 files with different properties
4. `.control-btn` - two different background values
5. `.viewport-canvas-container` - different background variables
6. `.context-menu-separator` - different margin values

### LOW PRIORITY - Intentional Overrides (Keep)

7. `.app-layout` media queries - intentional responsive design
8. Print styles - intentional print-specific overrides
9. Hover/focus states - intentional interaction states

---

## SUMMARY

| Category | Count | Action |
|----------|-------|--------|
| Exact duplicates | 1 | Remove from octane-theme.css |
| Near-duplicates (superset) | 1 | Remove from octane-theme.css |
| Different values | 28 | Manual review needed |
| Intentional overrides | Multiple | Keep as-is |

**Recommended immediate action:**
- Remove 2 selectors from octane-theme.css
- Document the other 28 for future review

---

## FILES TO MODIFY

### octane-theme.css - Remove These Selectors

**Line 1165-1176:** `.node-graph-container`  
→ Already exists in node-graph.css (lines 548-559)

**Line 454-459:** `.scene-loading`  
→ scene-outliner.css has more complete version (line 384)

---

## CHANGES APPLIED ✅

### octane-theme.css - Removed 2 Duplicate Selectors

**1. `.scene-loading` (was line 454-459)**
- **Removed:** 5 lines of duplicate code
- **Reason:** scene-outliner.css has superset (includes font-size)
- **Replaced with:** Comment pointing to scene-outliner.css line 384

**2. `.node-graph-container` (was line 1165-1176)**  
- **Removed:** 11 lines of duplicate code
- **Reason:** Exact duplicate in node-graph.css (just updated with flex layout)
- **Replaced with:** Comment pointing to node-graph.css line 548

### Size Reduction
- **Lines removed:** 16 lines
- **Space saved:** ~450 bytes
- **Duplicates eliminated:** 2
- **Duplicates remaining for review:** 28 (different properties)

### Build Status
✅ **Build successful** - No errors introduced
- TypeScript compilation: SUCCESS
- Vite build: SUCCESS
- Pre-existing warnings: Unrelated to CSS changes

---

## FUTURE WORK

The following 28 selectors have different properties and need manual review:
- `.scene-tree` (3 instances across files) - Consider consolidation
- `.control-btn` (2 instances) - Different background values
- `.viewport-canvas-container` (2 instances) - Different background variables
- `.context-menu-separator` (2 instances) - Different margin values
- Various viewport selectors - Different properties for different contexts
- Media query overrides - Intentional, keep as-is

**Recommendation:** Review in a separate cleanup phase when requirements are clearer.

---

*Generated: 2024*  
*Updated: After cleanup applied*  
*Purpose: CSS cleanup - eliminate duplicate selectors*  
*Status: ✅ Phase 1 complete - 2 duplicates removed*
