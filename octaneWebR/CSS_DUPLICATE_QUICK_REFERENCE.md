# CSS Duplicate Quick Reference

**For**: Immediate cleanup actions  
**See**: `CSS_DUPLICATE_COMPREHENSIVE_ANALYSIS.md` for full details

---

## 🔴 HIGH PRIORITY: Fix These First

### 1. `.inspector-content` - 3 FILES CONFLICT!
```
❌ DELETE from app.css (line ~96)
❌ DELETE from components.css (line ~335)
✅ KEEP in layout.css (line ~189)
```

### 2. `.node-graph-toolbar` - 2 FILES + 4 DUPLICATES!
```
❌ DELETE from octane-theme.css (line ~850)
✅ KEEP ONE in components.css
❌ DELETE duplicate at line 1247
❌ DELETE duplicate at line 3886
❌ DELETE duplicate at line 4920
⚠️ ADD z-index: var(--z-dropdown) to remaining definition
```

### 3. `.parameter-row` - 6 DUPLICATES!
```
✅ KEEP in layout.css (line ~195)
❌ DELETE all 6 instances from components.css
   (use grep -n "^\.parameter-row" to find)
```

**Estimated Savings**: ~150 lines, 3 conflicts resolved

---

## 🟡 MEDIUM PRIORITY: Within-File Duplicates (components.css)

| Selector | Instances | Action |
|----------|-----------|--------|
| `.parameter-checkbox` | 5x | Lines 378, 988, 1095, 2856, 3678 → Merge to 1 |
| `.scene-loading` | 4x | Lines 251, 481, 2246 → Merge to 1 |
| `.parameter-checkbox-custom` | 4x | Scattered → Merge to 1 |
| `.parameter-unit` | 3x | Merge to 1 |
| `.parameter-text-input` | 3x | Merge to 1 |
| `.parameter-spinner-btn` | 3x | Merge to 1 |
| `.parameter-number-input` | 3x | Merge to 1 |
| `.parameter-dropdown` | 3x | Merge to 1 |

**Estimated Savings**: ~350-400 lines

---

## 🟢 LOW PRIORITY: Cross-File Style Duplicates

**Strategy**: Pick one file to own each selector, delete from others

| Selector | Found In | Recommended Owner |
|----------|----------|------------------|
| `.control-btn` | components.css, octane-theme.css | components.css |
| `.loading-spinner` | components.css, octane-theme.css | components.css |
| `.context-menu-separator` | components.css, octane-theme.css | octane-theme.css |
| `.node-graph-container` | components.css, octane-theme.css | octane-theme.css |
| `.node-palette` | components.css, octane-theme.css | components.css |
| `.parameter-label` | components.css (3x), layout.css | layout.css |
| `.parameter-control` | components.css (2x), layout.css | layout.css |
| `.parameter-slider` | components.css (3x), layout.css | layout.css |

**Estimated Savings**: ~100-150 lines

---

## 🛠️ Quick Cleanup Commands

### Find Duplicate
```bash
cd /workspace/project/grpcSamples/octaneWebR
grep -n "^\.selector-name" client/src/styles/*.css
```

### Extract Full Rule
```bash
# View lines X to Y (adjust based on grep output)
sed -n 'X,Yp' client/src/styles/filename.css
```

### Delete Lines
```bash
# Use file_editor str_replace to remove duplicate rules
```

### Verify Build
```bash
npm run build  # Must pass with no errors
npm run dev    # Visual check
```

---

## 📊 Impact Summary

### Current State
- **Duplicate Selectors**: 50+ conflicts
- **Wasted Lines**: ~600-700 lines
- **Bundle Size**: 156.66 KB CSS

### After Cleanup
- **Duplicate Selectors**: 0 critical conflicts
- **Lines Removed**: ~600-700 lines (-8-10%)
- **Bundle Size**: ~145 KB (-7-8%)

---

## ⚠️ Safety Rules

1. ✅ **Fix one selector at a time** (easier to rollback)
2. ✅ **Run `npm run build` after each fix** (catch errors immediately)
3. ✅ **Commit after each selector** (granular history)
4. ✅ **Visual test in browser** (check affected components)
5. ✅ **Remember CSS cascade**: layout.css loads last (wins in conflicts)

---

## 🎯 Recommended Workflow

```bash
# 1. Start with HIGH PRIORITY
cd /workspace/project/grpcSamples/octaneWebR

# 2. Find all instances
grep -n "^\.inspector-content" client/src/styles/*.css

# 3. View each instance
sed -n '96,105p' client/src/styles/app.css

# 4. Remove duplicates (keep layout.css version)
# Use file_editor str_replace

# 5. Test
npm run build

# 6. Commit
git add -A
git commit -m "CSS cleanup: Remove .inspector-content duplicates

Removed duplicate definitions from app.css and components.css.
Kept single definition in layout.css.

Lines removed: 15
Conflicts resolved: 1/3"

# 7. Next selector
grep -n "^\.node-graph-toolbar" client/src/styles/*.css
```

---

## 🔄 CSS File Load Order (Important!)

```
main.tsx import order:
1. app.css          ← Lowest priority
2. octane-theme.css
3. components.css
4. layout.css       ← HIGHEST priority (wins conflicts)
```

**Implication**: If same selector exists in multiple files, **layout.css wins**.

---

## 📝 Tracking Progress

**Phase 1 - Critical Conflicts** (3 tasks)
- [ ] Fix `.inspector-content` (3 files)
- [ ] Fix `.node-graph-toolbar` (2 files + 4 duplicates)
- [ ] Fix `.parameter-row` (6 duplicates)

**Phase 2 - Component Deduplication** (8 tasks)
- [ ] Deduplicate `.parameter-checkbox` (5x)
- [ ] Deduplicate `.scene-loading` (4x)
- [ ] Deduplicate `.parameter-checkbox-custom` (4x)
- [ ] Deduplicate `.parameter-unit` (3x)
- [ ] Deduplicate `.parameter-text-input` (3x)
- [ ] Deduplicate `.parameter-spinner-btn` (3x)
- [ ] Deduplicate `.parameter-number-input` (3x)
- [ ] Deduplicate `.parameter-dropdown` (3x)

**Phase 3 - Cross-File Cleanup** (8 tasks)
- [ ] Consolidate `.parameter-label`
- [ ] Consolidate `.parameter-control`
- [ ] Consolidate `.parameter-slider`
- [ ] Consolidate `.control-btn`
- [ ] Consolidate `.loading-spinner`
- [ ] Consolidate `.context-menu-separator`
- [ ] Consolidate `.node-graph-container`
- [ ] Consolidate `.node-palette`

---

**Total Estimated Time**: 8-12 hours (can be split across multiple sessions)

**Next Action**: Start with Phase 1, Task 1 → `.inspector-content`
