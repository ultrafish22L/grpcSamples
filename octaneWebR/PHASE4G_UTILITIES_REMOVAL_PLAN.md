# Phase 4g: Utility Selectors Removal

## Summary

**Selectors found:** 4
**Total lines:** ~16
**Risk Level:** MEDIUM ⚠️ (Verify each utility before removing)

---

## Selectors Found

### .flex-center

**Lines 1297-1301** (5 lines)
```css
.flex-center {
    display: flex;
    align-items: center;
    justify-content: center;
}
```

### .flex-between

**Lines 1303-1307** (5 lines)
```css
.flex-between {
    display: flex;
    align-items: center;
    justify-content: space-between;
}
```

### .text-center

**Lines 1289-1291** (3 lines)
```css
.text-center {
    text-align: center !important;
}
```

### .text-right

**Lines 1293-1295** (3 lines)
```css
.text-right {
    text-align: right !important;
}
```

---

## Not Found

- `.panel-divider` - Not present in CSS
- `.divider` - Not present in CSS
- `.status-bar` - Not present in CSS
- `.status-label` - Not present in CSS
- `.status-value` - Not present in CSS
- `.flex-row` - Not present in CSS
- `.flex-col` - Not present in CSS
- `.flex-end` - Not present in CSS
- `.flex-start` - Not present in CSS
- `.flex-wrap` - Not present in CSS
- `.text-left` - Not present in CSS
- `.mt-` - Not present in CSS
- `.mb-` - Not present in CSS
- `.ml-` - Not present in CSS
- `.mr-` - Not present in CSS
- `.pt-` - Not present in CSS
- `.pb-` - Not present in CSS
- `.pl-` - Not present in CSS
- `.pr-` - Not present in CSS
---

## Verification Commands

```bash
grep -r 'flex-center' client/src --include='*.tsx' --include='*.ts'
grep -r 'flex-between' client/src --include='*.tsx' --include='*.ts'
grep -r 'text-center' client/src --include='*.tsx' --include='*.ts'
grep -r 'text-right' client/src --include='*.tsx' --include='*.ts'
```
