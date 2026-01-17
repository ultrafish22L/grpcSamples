# Phase 4e: Modal/Dialog/Error/Loading Selectors Removal

## Summary

**Unused selectors found:** 20
**Total lines to remove:** ~177
**Risk Level:** MEDIUM ⚠️ (Verify MUI Dialog usage first)

---

## Modal Selectors (7 found)

### .modal-button

**Lines 1157-1166** (10 lines)
```css
.modal-button {
    background-color: var(--octane-bg-header);
    border: 1px solid var(--octane-border);
    color: var(--octane-text-primary);
    padding: 6px 12px;
    font-size: var(--font-size-small);
    border-radius: var(--border-radius);
    cursor: pointer;
    transition: all 0.15s ease;
}
```

**Lines 1168-1170** (3 lines)
```css
.modal-button:hover {
    background-color: var(--octane-bg-hover);
}
```

**Lines 1172-1176** (5 lines)
```css
.modal-button.primary {
    background-color: var(--octane-accent-blue);
    border-color: var(--octane-accent-blue);
    color: white;
}
```

**Lines 1178-1180** (3 lines)
```css
.modal-button.primary:hover {
    background-color: var(--octane-accent-blue);
}
```

### .modal-content

**Lines 1148-1153** (6 lines)
```css
.modal-content {
    padding: 16px;
    flex: 1;
    overflow: auto;
    color: var(--octane-text-primary);
}
```

### .modal-title

**Lines 1126-1130** (5 lines)
```css
.modal-title {
    font-size: var(--font-size-small);
    font-weight: var(--font-weight-bold);
    color: var(--octane-text-primary);
}
```

### .modal-overlay

**Lines 1098-1110** (13 lines)
```css
.modal-overlay {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: var(--octane-overlay-semi);
    display: flex;
    align-items: center;
    justify-content: center;
    z-index: var(--z-context-menu);
    pointer-events: auto;
}
```

**Lines 3377-3388** (12 lines)
```css
.modal-overlay {
    position: fixed;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background: var(--octane-overlay-medium-dark);
    display: flex;
    align-items: center;
    justify-content: center;
    z-index: var(--z-dialog-overlay);
}
```

### .modal-header

**Lines 3402-3409** (8 lines)
```css
.modal-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 12px 16px;
    border-bottom: 1px solid var(--octane-border);
    background: var(--octane-bg-secondary);
}
```

### .modal-body

**Lines 3439-3442** (4 lines)
```css
.modal-body {
    padding: 16px;
    overflow-y: auto;
}
```

### .modal-footer

**Lines 3444-3451** (8 lines)
```css
.modal-footer {
    display: flex;
    justify-content: flex-end;
    gap: var(--spacing-xl);
    padding: 12px 16px;
    border-top: 1px solid var(--octane-border);
    background: var(--octane-bg-secondary);
}
```

## Error Selectors (6 found)

### .error-actions

**Lines 220-222** (3 lines)
```css
.error-actions {
    margin-top: 12px;
}
```

### .error-icon

**Lines 193-196** (4 lines)
```css
.error-icon, .success-icon {
    font-size: var(--font-size-icon);
    margin-bottom: 8px;
}
```

**Lines 2179-2182** (4 lines)
```css
.error-icon {
    font-size: var(--font-size-title);
    margin-bottom: 12px;
}
```

### .error-state

**Lines 2170-2177** (8 lines)
```css
.error-state {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    padding: 40px 20px;
    color: var(--octane-text-secondary);
}
```

### .error-title

**Lines 198-202** (5 lines)
```css
.error-title, .success-title {
    font-weight: var(--font-weight-bold);
    margin-bottom: 8px;
    color: var(--octane-text-primary);
}
```

### .error-message

**Lines 204-209** (6 lines)
```css
.error-message, .success-message {
    font-size: var(--font-size-small);
    color: var(--octane-text-secondary);
    line-height: var(--line-height-snug);
    margin-bottom: 12px;
}
```

**Lines 3517-3525** (9 lines)
```css
.error-message {
    margin-top: 12px;
    padding: 8px 10px;
    background: var(--octane-error-bg-bright);
    border-left: 3px solid var(--octane-accent-red);
    border-radius: var(--border-radius-md);
    color: var(--octane-accent-red);
    font-size: var(--font-size-small);
}
```

### .scene-error

**Lines 174-179** (6 lines)
```css
.scene-error, .scene-success {
    padding: 20px;
    text-align: center;
    border-radius: var(--border-radius);
    margin: 10px;
}
```

**Lines 181-185** (5 lines)
```css
.scene-error {
    background-color: var(--octane-error-bg-alpha);
    border: 1px solid var(--octane-error-border-alpha);
    color: var(--octane-text-primary);
}
```

## Success Selectors (4 found)

### .success-icon

**Lines 193-196** (4 lines)
```css
.error-icon, .success-icon {
    font-size: var(--font-size-icon);
    margin-bottom: 8px;
}
```

### .success-message

**Lines 204-209** (6 lines)
```css
.error-message, .success-message {
    font-size: var(--font-size-small);
    color: var(--octane-text-secondary);
    line-height: var(--line-height-snug);
    margin-bottom: 12px;
}
```

### .success-title

**Lines 198-202** (5 lines)
```css
.error-title, .success-title {
    font-weight: var(--font-weight-bold);
    margin-bottom: 8px;
    color: var(--octane-text-primary);
}
```

### .scene-success

**Lines 174-179** (6 lines)
```css
.scene-error, .scene-success {
    padding: 20px;
    text-align: center;
    border-radius: var(--border-radius);
    margin: 10px;
}
```

**Lines 187-191** (5 lines)
```css
.scene-success {
    background-color: var(--octane-success-bg-alpha);
    border: 1px solid var(--octane-success-border-alpha);
    color: var(--octane-text-primary);
}
```

## Loading Selectors (3 found)

### .loading-spinner

**Lines 2155-2163** (9 lines)
```css
.loading-spinner {
    width: 24px;
    height: 24px;
    border: 2px solid var(--octane-border);
    border-top: 2px solid var(--octane-accent);
    border-radius: var(--border-radius-circle);
    animation: spin 1s linear infinite;
    margin-bottom: 12px;
}
```

### .loading-parameters

**Lines 2146-2153** (8 lines)
```css
.loading-parameters {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    padding: 40px 20px;
    color: var(--octane-text-secondary);
}
```

### .scene-loading

**Lines 1791-1797** (7 lines)
```css
.scene-loading {
    padding: 20px;
    text-align: center;
    color: var(--octane-text-muted);
    font-style: italic;
    font-size: var(--font-size-small);
}
```

---

## Not Found

- `.modal-container` - Not present in CSS
- `.success-state` - Not present in CSS
- `.loading-status` - Not present in CSS
- `.loading-message` - Not present in CSS
- `.loading-overlay` - Not present in CSS
- `.inspector-loading` - Not present in CSS
- `.loading-screen` - Not present in CSS
- `.loading-content` - Not present in CSS
---

## Verification Required

Before removing, verify that:
1. All dialogs use MUI Dialog component (not custom .modal-*)
2. Error states use new error handling system
3. Loading states use new loading components

```bash
# Check for MUI Dialog usage:
grep -r 'from.*@mui.*Dialog' client/src --include='*.tsx'
grep -r '<Dialog' client/src --include='*.tsx'

# Check for custom modal usage:
grep -r 'modal-button' client/src --include='*.tsx' --include='*.ts'
grep -r 'modal-content' client/src --include='*.tsx' --include='*.ts'
grep -r 'modal-title' client/src --include='*.tsx' --include='*.ts'
grep -r 'modal-overlay' client/src --include='*.tsx' --include='*.ts'
grep -r 'modal-header' client/src --include='*.tsx' --include='*.ts'
grep -r 'modal-body' client/src --include='*.tsx' --include='*.ts'
grep -r 'modal-footer' client/src --include='*.tsx' --include='*.ts'
```
