# Theme System Guide - octaneWebR

## Quick Start: Creating a New Theme

### 1. Copy the base theme
```bash
cd client/src/styles
cp octane-theme.css my-custom-theme.css
```

### 2. Edit theme variables
Open `my-custom-theme.css` and modify the CSS custom properties:

```css
:root {
    /* Change the primary background */
    --octane-bg-primary: #1a1a1a;     /* Was: #252525 */
    
    /* Change the accent color */
    --octane-accent: #00bfff;         /* Was: #ff8c00 */
    
    /* Change text colors */
    --octane-text-primary: #f0f0f0;   /* Was: #ffffff */
    
    /* Modify any other variables... */
}
```

### 3. Update main.tsx
Replace the theme import:
```typescript
// Before:
import './styles/octane-theme.css'

// After:
import './styles/my-custom-theme.css'
```

### 4. Test your theme
```bash
npm run dev
```

All UI components will automatically use your new theme colors!

## Available Theme Variables

### Color Variables

#### Backgrounds
```css
--octane-bg-primary        /* Main background */
--octane-bg-secondary      /* Panel backgrounds */
--octane-bg-parameter      /* Parameter panel backgrounds */
--octane-bg-lighter        /* Render viewport background */
--octane-bg-header         /* Header/menu backgrounds */
--octane-bg-selected       /* Selected items */
--octane-bg-hover          /* Hover states */
--octane-bg-active         /* Active/pressed states */
```

#### Text Colors
```css
--octane-text-primary      /* Primary text */
--octane-text-secondary    /* Secondary text */
--octane-text-muted        /* Muted/less important text */
--octane-text-disabled     /* Disabled text */
```

#### Accent Colors
```css
--octane-accent            /* Primary accent - Octane orange */
--octane-accent-yellow     /* Selection yellow/gold */
--octane-accent-orange     /* Warning/active orange */
--octane-accent-green      /* Success green */
--octane-accent-red        /* Error red */
--octane-accent-blue       /* Info/link blue */
--octane-selection-highlight /* Dark orange for scene outliner */
```

#### Borders
```css
--octane-border            /* Standard borders */
--octane-border-light      /* Light borders */
--octane-border-dark       /* Dark borders */
--octane-border-primary    /* Primary borders/backgrounds */
--octane-border-medium     /* Medium borders */
```

#### Shadows & Overlays
```css
--octane-shadow            /* Drop shadows */
--octane-overlay-darkest   /* Very dark overlays (0.9) */
--octane-overlay-dark      /* Dark modal overlays (0.8) */
--octane-overlay-medium    /* Medium overlays (0.7) */
--octane-overlay-semi      /* Semi-transparent (0.5) */
--octane-overlay-light     /* Light overlays (0.4) */
--octane-overlay-subtle    /* Subtle overlays (0.3) */
```

### Layout Variables

```css
--menu-height              /* Top menu bar height */
--panel-header-height      /* Panel header height */
--status-bar-height        /* Bottom status bar height */
--splitter-size            /* Resize handle thickness */
--left-panel-min-width     /* Min width for scene outliner */
```

### Border Radius
```css
--border-radius-none       /* 0 */
--border-radius-xs         /* 1px */
--border-radius-sm         /* 2px */
--border-radius-md         /* 3px */
--border-radius-base       /* 4px */
--border-radius-lg         /* 6px */
--border-radius-xl         /* 8px */
--border-radius-2xl        /* 18px */
--border-radius-3xl        /* 20px */
--border-radius-circle     /* 50% */
```

### Typography

#### Font Families
```css
--font-family              /* Main UI font */
--font-family-mono         /* Monospace font */
```

#### Font Sizes
```css
--font-size-nano           /* 6px - Ultra-small */
--font-size-micro          /* 7px */
--font-size-tiny           /* 8px */
--font-size-xs             /* 9px */
--font-size-xxs            /* 10px */
--font-size-small          /* 11px */
--font-size-normal         /* 12px - Default body text */
--font-size-medium         /* 13px */
--font-size-large          /* 14px */
--font-size-xl             /* 16px */
--font-size-xxl            /* 18px */
--font-size-xlarge         /* 20px */
--font-size-icon           /* 24px */
--font-size-xxlarge        /* 26px */
--font-size-header         /* 28px */
--font-size-title          /* 32px */
--font-size-huge           /* 48px */
```

#### Font Weights
```css
--font-weight-light        /* 50 */
--font-weight-normal       /* 400 */
--font-weight-bold         /* 600 */
--font-weight-bold7        /* 700 */
--font-weight-header       /* 500 */
```

#### Line Heights
```css
--line-height-none         /* 1 - Tight */
--line-height-tight        /* 1.3 */
--line-height-snug         /* 1.4 */
--line-height-normal       /* 1.5 */
--line-height-pixel        /* 14px */
```

### Spacing System
```css
--spacing-none             /* 0 */
--spacing-xxs              /* 1px */
--spacing-xs               /* 2px */
--spacing-sm               /* 3px */
--spacing-md               /* 4px */
--spacing-lg               /* 6px */
--spacing-xl               /* 8px */
--spacing-2xl              /* 10px */
--spacing-3xl              /* 12px */
--spacing-4xl              /* 15px */
--spacing-5xl              /* 16px */
```

### Opacity Levels
```css
--opacity-invisible        /* 0 */
--opacity-light            /* 0.4 */
--opacity-medium           /* 0.5 */
--opacity-moderate         /* 0.6 */
--opacity-strong           /* 0.7 */
--opacity-heavy            /* 0.8 */
--opacity-full             /* 1 */
```

### Z-Index Layers
```css
--z-base                   /* 0 - Default layer */
--z-low                    /* 1 - Basic stacking */
--z-tab-active             /* 2 - Active tabs */
--z-background             /* 5 - Background elements */
--z-panel                  /* 10 - Panels */
--z-dropdown               /* 100 - Dropdowns */
--z-modal-bg               /* 1000 - Modal backgrounds */
--z-dialog-overlay         /* 9998 - Dialog backdrops */
--z-dialog                 /* 9999 - Dialog windows */
--z-context-menu           /* 10000 - Context menus */
--z-dropdown-content       /* 10001 - Dropdown content */
--z-search-dialog          /* 15000 - Search dialog */
```

## Theme Presets

### Example: Light Theme (Future)
```css
:root {
    --octane-bg-primary: #f5f5f5;
    --octane-bg-secondary: #ffffff;
    --octane-bg-header: #e0e0e0;
    --octane-text-primary: #000000;
    --octane-text-secondary: #333333;
    --octane-accent: #ff6600;
    /* etc... */
}
```

### Example: High Contrast Theme
```css
:root {
    --octane-bg-primary: #000000;
    --octane-bg-secondary: #1a1a1a;
    --octane-text-primary: #ffffff;
    --octane-accent: #00ff00;
    --octane-border: #ffffff;
    /* etc... */
}
```

### Example: Blue Theme
```css
:root {
    --octane-bg-primary: #1e2a3a;
    --octane-bg-secondary: #2d3e50;
    --octane-accent: #3498db;
    --octane-accent-orange: #3498db;  /* Replace orange with blue */
    /* etc... */
}
```

## Using Theme Variables in Components

When creating new components or modifying existing ones, always use theme variables:

### ✅ Good - Uses theme variables
```css
.my-component {
    background-color: var(--octane-bg-primary);
    color: var(--octane-text-primary);
    border: 1px solid var(--octane-border);
    padding: var(--spacing-md);
    border-radius: var(--border-radius-sm);
}
```

### ❌ Bad - Hardcoded colors
```css
.my-component {
    background-color: #252525;  /* Don't do this! */
    color: #ffffff;
    border: 1px solid #555555;
    padding: 4px;
    border-radius: 2px;
}
```

## CSS File Organization

```
client/src/styles/
├── octane-theme.css        ← Theme variables ONLY
├── app.css                 ← App-level UI (loading, menu, panels, status)
├── scene-outliner.css      ← Scene outliner tree view
├── viewport.css            ← Viewport, canvas, render toolbar
├── node-graph.css          ← Node graph editor
└── node-inspector.css      ← Node inspector & parameter controls
```

### Rules:
1. **octane-theme.css**: Only CSS variables (`:root` block)
2. **Component CSS files**: All selectors and styles
3. **Always use variables**: Reference `var(--octane-*)` in component styles
4. **Import order matters**: Theme variables must load first (see `main.tsx`)

## Testing Your Theme

After creating a new theme:

1. **Visual Check**: Run `npm run dev` and check all panels
2. **Hover States**: Test hover effects on buttons, menu items, etc.
3. **Active States**: Click buttons, select items, etc.
4. **Focus States**: Tab through focusable elements
5. **Borders**: Check all borders are visible
6. **Text Contrast**: Ensure text is readable on all backgrounds
7. **Icons**: Verify icons/symbols are visible

## Troubleshooting

### Colors not changing?
- Check import order in `main.tsx` - theme must load first
- Clear browser cache
- Check CSS specificity - component styles might override

### Missing variables?
- Check variable name spelling
- Ensure using `var(--variable-name)` syntax
- Verify variable is defined in `:root` block

### Theme not loading?
- Check file path in import statement
- Verify CSS file syntax (balanced braces)
- Look for console errors in browser dev tools

## Contributing

When adding new theme variables:
1. Add to `octane-theme.css` in the appropriate category
2. Use clear, descriptive names following existing conventions
3. Add a comment explaining the purpose
4. Update this guide with the new variable
5. Use the variable in component CSS files

---

**Reference**: See `CSS_CLEANUP_SUMMARY.md` for refactoring details
**Unused Classes**: See `UNUSED_CSS_CLASSES.md` for cleanup opportunities
