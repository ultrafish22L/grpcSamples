# Phase 4d: Notification Selectors Removal

## Summary

**Unused selectors found:** 9
**Total lines to remove:** ~51
**Risk Level:** LOW ✅ (Notification system not implemented)

---

## Selectors to Remove

### .notification-container

**Lines 1045-1051** (7 lines)
```css
.notification-container {
    position: fixed;
    top: 60px;
    right: 20px;
    z-index: var(--z-notification);
    pointer-events: none;
}
```

### .notification-content

**Lines 1081-1086** (6 lines)
```css
.notification-content {
    display: flex;
    align-items: center;
    padding: 12px 16px;
    gap: var(--spacing-2xl);
}
```

### .notification-icon

**Lines 1088-1091** (4 lines)
```css
.notification-icon {
    font-size: var(--font-size-xl);
    flex-shrink: 0;
}
```

### .notification-message

**Lines 1093-1098** (6 lines)
```css
.notification-message {
    flex: 1;
    color: var(--octane-text-primary);
    font-size: var(--font-size-small);
    line-height: var(--line-height-snug);
}
```

### .notification-close

**Lines 1100-1115** (16 lines)
```css
.notification-close {
    background: none;
    border: none;
    color: var(--octane-text-muted);
    cursor: pointer;
    font-size: var(--font-size-xxl);
    padding: 0;
    width: 20px;
    height: 20px;
    display: flex;
    align-items: center;
    justify-content: center;
    border-radius: var(--border-radius-circle);
    transition: all 0.15s ease;
    flex-shrink: 0;
}
```

### .notification-error

**Lines 1069-1071** (3 lines)
```css
.notification-error {
    border-left: 4px solid var(--octane-error);
}
```

### .notification-info

**Lines 1077-1079** (3 lines)
```css
.notification-info {
    border-left: 4px solid var(--octane-accent-blue);
}
```

### .notification-success

**Lines 1065-1067** (3 lines)
```css
.notification-success {
    border-left: 4px solid var(--octane-success);
}
```

### .notification-warning

**Lines 1073-1075** (3 lines)
```css
.notification-warning {
    border-left: 4px solid var(--octane-warning);
}
```

---

## Verification

```bash
grep -r 'notification-container' client/src --include='*.tsx' --include='*.ts'
grep -r 'notification-content' client/src --include='*.tsx' --include='*.ts'
grep -r 'notification-icon' client/src --include='*.tsx' --include='*.ts'
grep -r 'notification-message' client/src --include='*.tsx' --include='*.ts'
grep -r 'notification-close' client/src --include='*.tsx' --include='*.ts'
grep -r 'notification-error' client/src --include='*.tsx' --include='*.ts'
grep -r 'notification-info' client/src --include='*.tsx' --include='*.ts'
grep -r 'notification-success' client/src --include='*.tsx' --include='*.ts'
grep -r 'notification-warning' client/src --include='*.tsx' --include='*.ts'
# All should return exit code 1 (not found) ✓
```
