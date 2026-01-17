# Phase 4a: app.css - Unused Selector Removal Preview

## 📊 **Summary**

| Metric | Value |
|--------|-------|
| **Total Unused Selectors** | 18 |
| **Total Lines to Remove** | ~117 |
| **Kept (actively used)** | .tree-node + variants (17 lines) |
| **File** | client/src/styles/app.css |
| **Verification** | ✅ All confirmed unused |

---

## 🗑️ **Selectors to Remove (Organized by Category)**

### **1. App Structure (5 selectors, 36 lines)**

| Selector | Lines | Description |
|----------|-------|-------------|
| `.octane-app` | 24-29 (6) | Old app container |
| `.app-header` | 32-40 (9) | Old header layout |
| `.app-title h1` | 42-47 (6) | Title styling |
| `.app-subtitle` | 49-53 (5) | Subtitle styling |
| `.app-main` | 92-96 (5) | Main content area |
| `.app-footer` | 184-194 (11) | Footer layout |

**Why remove:** Old app structure, replaced by current layout system

---

### **2. Outliner/Tree (6 selectors, 31 lines - KEEPING .tree-node)**

| Selector | Lines | Description | Action |
|----------|-------|-------------|--------|
| `.outliner-header` | 229-234 (6) | Old outliner header | ❌ Remove |
| `.outliner-tree` | 259-265 (7) | Old tree container | ❌ Remove |
| `.tree-node` | 267-283 (17) | **Currently USED in SceneOutliner.tsx** | ✅ **KEEP** |
| `.tree-expand` | 285-290 (6) | Old expand icon | ❌ Remove |
| `.tree-icon` | 292-294 (3) | Old tree icon | ❌ Remove |
| `.tree-label` | 296-299 (4) | Old tree label | ❌ Remove |
| `.tree-type` | 301-305 (5) | Old tree type indicator | ❌ Remove |

**Why keep .tree-node:** Actively used with dynamic classes:
- `tree-node level-${depth}` (tree depth)
- `tree-node.selected` (selection state)
- `tree-node.material-item` (material nodes)
- `tree-node.package-item` (package nodes)

**Why remove others:** Old outliner components, replaced by scene-outliner system

---

### **3. Properties/Panels (5 selectors, 28 lines)**

| Selector | Lines | Description |
|----------|-------|-------------|
| `.side-panel` | 152-159 (8) | Old side panel |
| `.panel-section` | 161-164 (4) | Old panel section |
| `.node-properties` | 176-181 (6) | Old properties panel |
| `.property-group` | 320-322 (3) | Old property grouping |
| `.property` | 332-338 (7) | Old property row |

**Why remove:** Old property system, replaced by NodeInspector components

---

### **4. Status/Footer (5 selectors, 30 lines)**

| Selector | Lines | Description |
|----------|-------|-------------|
| `.status-message` | 133-139 (7) | Old status message |
| `.footer-info` | 196-198 (3) | Footer info text |
| `.viewport-status` | 211-220 (10) | Old viewport status |
| `.frame-count` | 222-224 (3) | Frame counter |
| `.raw-data` | 349-358 (10) | Raw data display |

**Why remove:** Old status/debugging UI, replaced by current status bar and RenderToolbar

---

## ⚠️ **IMPORTANT: Keep These Selectors!**

**DO NOT REMOVE (actively used):**
- `.tree-node` ✅ Used in SceneOutliner.tsx
- `.tree-node.level-*` ✅ Dynamic depth classes
- `.tree-node.selected` ✅ Selection state
- `.tree-node.material-item` ✅ Material styling
- `.tree-node.package-item` ✅ Package styling

---

## 📈 **Expected Impact**

### Bundle Size:
- **Current:** 146.24 kB
- **After Phase 4a:** ~144.8 kB (estimated)
- **Reduction:** ~1.4 kB raw

### Total Cleanup Progress:

| Phase | File | Lines | KB Saved |
|-------|------|-------|----------|
| Phase 1 | components.css | 151 | 3.24 |
| Phase 1B | components.css | 104 | 1.88 |
| Phase 2 | layout.css | 64 | 0.95 |
| Phase 3 | app.css | 3 | 0.12 |
| **Phase 4a** | **app.css** | **~117** | **~1.3** |
| **TOTAL** | **3 files** | **~439** | **~7.5 kB** |

---

## 🔍 **Verification Method**

All selectors verified unused:
```bash
# For each selector:
grep -r "selector-name" client/src --include="*.ts" --include="*.tsx"
# Result: Exit code 1 (not found) = UNUSED ✓

# Example checks:
grep -r "octane-app" client/src --include="*.tsx"     # Not found ✓
grep -r "outliner-header" client/src --include="*.tsx" # Not found ✓
grep -r "tree-node" client/src --include="*.tsx"      # FOUND - KEEP! ✅
```

---

## 🚀 **Removal Strategy**

**Approach:** Bottom-to-top removal (prevents line number shifting)

### Removal Order:
1. **Block 5:** Lines 332-358 (property, raw-data) - 27 lines
2. **Block 4:** Lines 285-305 (tree-expand, tree-icon, tree-label, tree-type) - 26 lines **SKIP 267-283** (.tree-node - KEEP!)
3. **Block 3:** Lines 259-265 (outliner-tree) - 7 lines
4. **Block 2:** Lines 229-234 (outliner-header) - 6 lines
5. **Block 1:** Lines 184-224 (app-footer, footer-info, viewport-status, frame-count) - 41 lines
6. **Block 0:** Lines 133-181 (status-message, side-panel, panel-section, node-properties) - 49 lines  
7. **Top:** Lines 24-96 (octane-app, app-header, app-title h1, app-subtitle, app-main) - 37 lines (with gaps)

**⚠️ CRITICAL:** Do NOT remove lines 267-283 (.tree-node) - actively used!

**Build test:** Run `npm run build` after removal

---

## ✅ **Ready to Proceed?**

**Total removal:** ~117 lines from 18 selectors
**Keeping:** .tree-node (lines 267-283, 17 lines) - actively used in SceneOutliner

**Review complete?** Proceed to Phase 4a execution?
