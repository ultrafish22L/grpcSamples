# Phase 4f: Inspector Selectors Removal

## Summary

**Selectors found:** 7
**Total lines:** ~40
**Risk Level:** MEDIUM ⚠️ (Verify .octane-inspector-content usage first)

---

## Selectors Found

### .octane-inspector-header

**Lines 382-392** (11 lines)
```css
.octane-inspector-header {
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 6px 8px;
    background-color: var(--octane-bg-primary);
    border-bottom: 1px solid var(--octane-bg-header);
    font-size: var(--font-size-small);
    color: var(--octane-text-primary);
    flex-shrink: 0;
}
```

### .octane-inspector-icon

**Lines 400-403** (4 lines)
```css
.octane-inspector-icon {
    margin-right: 4px;
    font-size: var(--font-size-normal);
}
```

### .octane-inspector-title

**Lines 394-398** (5 lines)
```css
.octane-inspector-title {
    display: flex;
    align-items: center;
    font-weight: normal;
}
```

### .octane-inspector-content

**Lines 438-442** (5 lines)
```css
.octane-inspector-content {
    flex: 1;
    overflow-y: auto;
    padding: 4px 0;
}
```

### .inspector-section

**Lines 1930-1932** (3 lines)
```css
.inspector-section {
    border-bottom: 1px solid var(--octane-border);
}
```

### .node-inspector-empty

**Lines 3101-3107** (7 lines)
```css
.node-inspector-empty {
    padding: 20px;
    text-align: center;
    color: var(--octane-text-secondary);
    font-size: var(--font-size-small);
    font-style: italic;
}
```

### .panel-content-inspector

**Lines 2651-2655** (5 lines)
```css
.panel-content-inspector {
    flex: 1;
    overflow: auto;
    padding: 0 0 0 4px;
}
```

---

## Not Found

- `.inspector-tab` - Not present in CSS
- `.inspector-tabs` - Not present in CSS
- `.octane-section` - Not present in CSS
- `.octane-section-header` - Not present in CSS
- `.octane-section-content` - Not present in CSS
- `.octane-section-title` - Not present in CSS
- `.octane-subsection` - Not present in CSS
- `.octane-subsection-header` - Not present in CSS
- `.octane-subsection-content` - Not present in CSS
---

## Verification Commands

```bash
grep -r 'octane-inspector-header' client/src --include='*.tsx' --include='*.ts'
grep -r 'octane-inspector-icon' client/src --include='*.tsx' --include='*.ts'
grep -r 'octane-inspector-title' client/src --include='*.tsx' --include='*.ts'
grep -r 'octane-inspector-content' client/src --include='*.tsx' --include='*.ts'
grep -r 'inspector-section' client/src --include='*.tsx' --include='*.ts'
grep -r 'node-inspector-empty' client/src --include='*.tsx' --include='*.ts'
grep -r 'panel-content-inspector' client/src --include='*.tsx' --include='*.ts'
```
