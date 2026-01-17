# Phase 1: Scene Node Consolidation - Detailed Changes

**CSS Load Order**: app.css → octane-theme.css → components.css → **layout.css (WINS)**

---

## Analysis of Each Duplicate

### 1. `.scene-node` (components:91, layout:327)

**components.css** (currently LOSES):
```css
.scene-node {
    cursor: pointer;
    user-select: none;
    display: flex;
    align-items: center;
    padding: 1px 6px;
    margin: 0;
    height: 18px;
}
```

**layout.css** (currently WINS):
```css
.scene-node {
    display: flex;
    align-items: center;
    padding: 2px 4px;
    cursor: pointer;
    border-radius: var(--border-radius);
    transition: background-color 0.15s ease;
}
```

**ACTION**: Keep in layout.css, merge useful properties from components.css
- Add: `user-select: none`, `margin: 0`, `height: 18px`
- Remove from components.css

---

### 2. `.scene-node.selected` (components:103, layout:340)

**components.css** (currently LOSES):
```css
.scene-node.selected {
    background-color: var(--octane-accent-red);  /* RED */
    color: white;
}
```

**layout.css** (currently WINS):
```css
.scene-node.selected {
    background-color: var(--octane-accent-yellow);  /* YELLOW */
}
```

**ACTION**: Keep layout.css (YELLOW is what currently displays)
- Remove from components.css
- Note: If red was intended, this is a bug that's been hidden!

---

### 3. `.scene-node-indent` (components:108, layout:344)

**components.css** (currently LOSES):
```css
.scene-node-indent {
    width: 12px;
    flex-shrink: 0;
}
```

**layout.css** (currently WINS):
```css
.scene-node-indent {
    width: 16px;
    display: flex;
    align-items: center;
    justify-content: center;
}
```

**ACTION**: Keep layout.css (16px is current behavior)
- Optionally add `flex-shrink: 0` if needed
- Remove from components.css

---

### 4. `.scene-node-icon` (components:148, layout:361)

**components.css** (has icon type definitions!):
```css
.scene-node-icon {
    width: 14px;
    text-align: center;
    margin-right: 4px;
    font-size: var(--font-size-small);
    flex-shrink: 0;
}
/* PLUS 14+ icon type variations (.scene-node-icon.camera::before, etc.) */
```

**layout.css** (currently WINS, but no icon types):
```css
.scene-node-icon {
    width: 16px;
    height: 16px;
    margin-right: 4px;
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: var(--font-size-normal);
}
```

**ACTION**: Keep in components.css (has all icon type definitions)
- Merge from layout.css: `display: flex`, `height: 16px`, update width to 16px
- Remove from layout.css
- **EXCEPTION**: This breaks the "structural → layout.css" rule, but necessary because icon types are in components.css

---

### 5. `.scene-node-visibility` (components:178, layout:379)

**components.css** (currently LOSES):
```css
.scene-node-visibility {
    margin-left: 6px;
    cursor: pointer;
    opacity: var(--opacity-moderate);
    font-size: var(--font-size-small);
    width: 14px;
    text-align: center;
    flex-shrink: 0;
}
```

**layout.css** (currently WINS - better styling):
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
```

**ACTION**: Keep layout.css (more complete, currently active)
- Remove from components.css

---

### 6. `.scene-node-visibility:hover` (components:188, layout:392)

**components.css** (currently LOSES):
```css
.scene-node-visibility:hover {
    opacity: var(--opacity-full);
}
```

**layout.css** (currently WINS):
```css
.scene-node-visibility:hover {
    background-color: var(--octane-bg-hover);
    color: var(--octane-text-primary);
}
```

**ACTION**: Keep layout.css (current behavior)
- Remove from components.css

---

## Summary of Actions

### In components.css:
1. **REMOVE** `.scene-node` (lines ~91-98)
2. **REMOVE** `.scene-node.selected` (lines ~103-106)
3. **REMOVE** `.scene-node-indent` (lines ~108-111)
4. **ENHANCE** `.scene-node-icon` (line 148) - merge properties from layout.css
5. **REMOVE** `.scene-node-visibility` (lines ~178-186)
6. **REMOVE** `.scene-node-visibility:hover` (lines ~188-190)

### In layout.css:
1. **ENHANCE** `.scene-node` (line 327) - add properties from components.css
2. **KEEP** `.scene-node.selected` (line 340)
3. **KEEP** `.scene-node-indent` (line 344)
4. **REMOVE** `.scene-node-icon` (lines ~361-369)
5. **KEEP** `.scene-node-visibility` (line 379)
6. **KEEP** `.scene-node-visibility:hover` (line 392)

---

## Expected Result

- **layout.css**: Owns scene node structure and layout (5 selectors)
- **components.css**: Owns scene node icon content types (1 selector + variants)
- **Eliminated**: 6 duplicate definitions
- **No visual change** (preserving currently-winning styles)
