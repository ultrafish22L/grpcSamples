# CSS Color Mapping Reference

**Purpose:** Quick lookup table for converting hardcoded colors to CSS variables

---

## 🎨 Complete Color Mapping Table

### Background Colors

| Hex Code | RGB Equivalent | CSS Variable | Usage |
|----------|----------------|--------------|-------|
| `#2b2b2b` | `rgb(43,43,43)` | `var(--octane-bg-primary)` | Main application background |
| `#3c3c3c` | `rgb(60,60,60)` | `var(--octane-bg-secondary)` | Panel backgrounds |
| `#4c4c4c` | `rgb(76,76,76)` | `var(--octane-bg-parameter)` | Parameter panel backgrounds |
| `#1e1e1e` | `rgb(30,30,30)` | `var(--octane-bg-darker)` | Darker panels, viewport |
| `#1a1a1a` | `rgb(26,26,26)` | `var(--octane-bg-darker)` | Very dark (use bg-darker) |
| `#1f1f1f` | `rgb(31,31,31)` | `var(--octane-bg-darker)` | Very dark (use bg-darker) |
| `#404040` | `rgb(64,64,64)` | `var(--octane-bg-header)` | Header/menu backgrounds |
| `#4a4a4a` | `rgb(74,74,74)` | `var(--octane-bg-selected)` | Selected items |
| `#484848` | `rgb(72,72,72)` | `var(--octane-bg-hover)` | Hover states |
| `#2a2a2a` | `rgb(42,42,42)` | `var(--octane-viewport-bg)` | Viewport background |
| `#3a3a3a` | `rgb(58,58,58)` | `var(--octane-node-bg)` | Node backgrounds |
| `#151515` | `rgb(21,21,21)` | `var(--octane-parameter-bg)` | Parameter input backgrounds |
| `#222` | `rgb(34,34,34)` | `var(--octane-bg-darker)` | Shorthand dark |
| `#333` | `rgb(51,51,51)` | `var(--octane-border-dark)` | Shorthand dark border |

### Text Colors

| Hex Code | RGB Equivalent | CSS Variable | Usage |
|----------|----------------|--------------|-------|
| `#ffffff` | `rgb(255,255,255)` | `var(--octane-text-primary)` | Primary text |
| `#fff` | `rgb(255,255,255)` | `var(--octane-text-primary)` | Primary text (shorthand) |
| `#e0e0e0` | `rgb(224,224,224)` | `var(--octane-text-primary)` | Bright text (use primary) |
| `#cccccc` | `rgb(204,204,204)` | `var(--octane-text-secondary)` | Secondary text |
| `#ccc` | `rgb(204,204,204)` | `var(--octane-text-secondary)` | Secondary text (shorthand) |
| `#aaa` | `rgb(170,170,170)` | `var(--octane-text-secondary)` | Light gray text |
| `#999999` | `rgb(153,153,153)` | `var(--octane-text-muted)` | Muted/disabled text |
| `#999` | `rgb(153,153,153)` | `var(--octane-text-muted)` | Muted text (shorthand) |
| `#888888` | `rgb(136,136,136)` | `var(--octane-text-muted)` | Muted text |
| `#888` | `rgb(136,136,136)` | `var(--octane-text-muted)` | Muted text (shorthand) |
| `#666666` | `rgb(102,102,102)` | `var(--octane-text-disabled)` | Disabled text |
| `#666` | `rgb(102,102,102)` | `var(--octane-text-disabled)` | Disabled text (shorthand) |

### Accent Colors

| Hex Code | RGB Equivalent | CSS Variable | Usage |
|----------|----------------|--------------|-------|
| `#ff8c00` | `rgb(255,140,0)` | `var(--octane-accent-orange)` | Primary accent, warnings |
| `#f39c12` | `rgb(243,156,18)` | `var(--octane-accent-orange)` | Orange accent |
| `#ffc107` | `rgb(255,193,7)` | `var(--octane-accent-yellow)` | Selection highlight |
| `#d4a017` | `rgb(212,160,23)` | `var(--octane-accent-yellow)` | Gold accent |
| `#5cb85c` | `rgb(92,184,92)` | `var(--octane-accent-green)` | Success state |
| `#27ae60` | `rgb(39,174,96)` | `var(--octane-accent-green)` | Success green |
| `#d9534f` | `rgb(217,83,79)` | `var(--octane-accent-red)` | Error state |
| `#e74c3c` | `rgb(231,76,60)` | `var(--octane-accent-red)` | Error red |
| `#3a9bd9` | `rgb(58,155,217)` | `var(--octane-accent-blue)` | Info/link blue ⚠️ ADD THIS |

### Border Colors

| Hex Code | RGB Equivalent | CSS Variable | Usage |
|----------|----------------|--------------|-------|
| `#555555` | `rgb(85,85,85)` | `var(--octane-border)` | Standard borders |
| `#555` | `rgb(85,85,85)` | `var(--octane-border)` | Standard borders (shorthand) |
| `#666666` | `rgb(102,102,102)` | `var(--octane-border-light)` | Light borders |
| `#666` | `rgb(102,102,102)` | `var(--octane-border-light)` | Light borders (shorthand) |
| `#333333` | `rgb(51,51,51)` | `var(--octane-border-dark)` | Dark borders |
| `#444` | `rgb(68,68,68)` | `var(--octane-border)` | Medium borders |
| `#444444` | `rgb(68,68,68)` | `var(--octane-border)` | Medium borders |

### Special/Component Colors

| Hex Code | RGB Equivalent | CSS Variable | Usage |
|----------|----------------|--------------|-------|
| `#888888` | `rgb(136,136,136)` | `var(--octane-connection-line)` | Node graph edges |
| `#000000` | `rgb(0,0,0)` | Leave as-is | True black (rare) |
| `#000` | `rgb(0,0,0)` | Leave as-is | True black (rare) |

---

## 🌈 RGBA Color Mapping

### Transparent Overlays

| RGBA Code | CSS Variable | Suggested Definition | Usage |
|-----------|--------------|----------------------|-------|
| `rgba(0, 0, 0, 0.8)` | `var(--octane-overlay-dark)` | ⚠️ ADD | Modal overlays |
| `rgba(0, 0, 0, 0.6)` | `var(--octane-overlay-medium)` | ⚠️ ADD | Hover overlays |
| `rgba(0, 0, 0, 0.5)` | `var(--octane-overlay-medium)` | ⚠️ ADD | Medium overlays |
| `rgba(0, 0, 0, 0.4)` | `var(--octane-shadow)` | Use existing | Inset shadows |
| `rgba(0, 0, 0, 0.3)` | `var(--octane-shadow)` | Use existing | Drop shadows |
| `rgba(0, 0, 0, 0.25)` | `var(--octane-shadow)` | Use existing | Light shadows |
| `rgba(0, 0, 0, 0.15)` | `var(--octane-shadow-light)` | ⚠️ ADD | Very light shadows |

### Transparent Backgrounds

| RGBA Code | CSS Variable | Suggested Definition | Usage |
|-----------|--------------|----------------------|-------|
| `rgba(255, 255, 255, 0.2)` | `var(--octane-white-overlay)` | ⚠️ ADD | White highlights |
| `rgba(255, 255, 255, 0.15)` | `var(--octane-white-overlay)` | ⚠️ ADD | Subtle highlights |
| `rgba(255, 255, 255, 0.1)` | `var(--octane-white-overlay-faint)` | ⚠️ ADD | Very subtle highlights |
| `rgba(255, 255, 255, 0.05)` | `var(--octane-white-overlay-faint)` | ⚠️ ADD | Barely visible highlights |

---

## 🔧 Conversion Examples

### Example 1: Simple Color Replacement

**Before:**
```css
.panel-header {
  background-color: #404040;
  color: #ffffff;
  border-bottom: 1px solid #555555;
}
```

**After:**
```css
.panel-header {
  background-color: var(--octane-bg-header);
  color: var(--octane-text-primary);
  border-bottom: 1px solid var(--octane-border);
}
```

### Example 2: RGBA Conversion

**Before:**
```css
.modal-overlay {
  background: rgba(0, 0, 0, 0.8);
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.3);
}
```

**After (Option A - Use existing variable):**
```css
.modal-overlay {
  background: var(--octane-overlay-dark); /* Need to define this */
  box-shadow: 0 2px 8px var(--octane-shadow);
}
```

**After (Option B - Keep RGBA with variable fallback):**
```css
.modal-overlay {
  background: rgba(0, 0, 0, 0.8); /* OK - transparent black won't change */
  box-shadow: 0 2px 8px var(--octane-shadow);
}
```

### Example 3: Gradient Conversion

**Before:**
```css
.node-header {
  background: linear-gradient(180deg, #4a4a4a 0%, #3c3c3c 100%);
}
```

**After:**
```css
.node-header {
  background: linear-gradient(180deg, 
    var(--octane-bg-selected) 0%, 
    var(--octane-bg-secondary) 100%
  );
}
```

### Example 4: Complex Shadow

**Before:**
```css
.elevated-card {
  box-shadow: 
    inset 0 1px 0 rgba(255, 255, 255, 0.1),
    inset 0 -1px 0 rgba(0, 0, 0, 0.25),
    0 2px 4px rgba(0, 0, 0, 0.6);
}
```

**After:**
```css
.elevated-card {
  box-shadow: 
    inset 0 1px 0 var(--octane-white-overlay-faint),
    inset 0 -1px 0 rgba(0, 0, 0, 0.25), /* OK - pure black shadow */
    0 2px 4px var(--octane-shadow);
}
```

---

## ⚠️ New Variables to Add

Add these to `octane-theme.css` `:root` section:

```css
:root {
  /* ... existing variables ... */
  
  /* Missing accent color */
  --octane-accent-blue: #3a9bd9;
  
  /* Overlays */
  --octane-overlay-dark: rgba(0, 0, 0, 0.8);
  --octane-overlay-medium: rgba(0, 0, 0, 0.5);
  --octane-overlay-light: rgba(0, 0, 0, 0.2);
  
  /* Highlights */
  --octane-white-overlay: rgba(255, 255, 255, 0.15);
  --octane-white-overlay-faint: rgba(255, 255, 255, 0.05);
  
  /* Shadows */
  --octane-shadow-light: rgba(0, 0, 0, 0.15);
  --octane-shadow-strong: rgba(0, 0, 0, 0.6);
}
```

---

## 🚫 Colors to Leave As-Is

Some colors should NOT be converted:

### 1. Pure Black/White in Shadows
```css
/* OK - shadows use pure black */
box-shadow: 0 2px 4px rgba(0, 0, 0, 0.3);

/* OK - inset highlights use pure white */
box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.1);
```

### 2. Data URL Colors (SVG backgrounds)
```css
/* OK - SVG color in data URL */
background-image: url("data:image/svg+xml;...fill='%23cccccc'...");
```

### 3. Node Type Colors (Dynamic)
```css
/* OK - node-specific colors from API */
.node-type-color[style*="background-color"] {
  /* Inline styles from backend */
}
```

### 4. Transparent
```css
/* OK - keyword, not a color */
background: transparent;
border-color: transparent;
```

---

## 📝 sed Commands for Batch Replacement

Quick find-and-replace for common colors:

```bash
# Background colors
sed -i 's/#2b2b2b/var(--octane-bg-primary)/g' file.css
sed -i 's/#3c3c3c/var(--octane-bg-secondary)/g' file.css
sed -i 's/#1e1e1e/var(--octane-bg-darker)/g' file.css

# Text colors
sed -i 's/#ffffff/var(--octane-text-primary)/g' file.css
sed -i 's/#cccccc/var(--octane-text-secondary)/g' file.css
sed -i 's/#999999/var(--octane-text-muted)/g' file.css

# Borders
sed -i 's/#555555/var(--octane-border)/g' file.css
sed -i 's/#333333/var(--octane-border-dark)/g' file.css

# Accents
sed -i 's/#ff8c00/var(--octane-accent-orange)/g' file.css
sed -i 's/#ffc107/var(--octane-accent-yellow)/g' file.css
```

**⚠️ WARNING:** Always review changes manually! sed can replace in wrong contexts.

---

## 🎯 File-Specific Replacement Priorities

### app.css (377 lines, 50 colors)
**Top 10 colors to replace:**
1. `#1a1a1a` → `var(--octane-bg-darker)` (8 occurrences)
2. `#2a2a2a` → `var(--octane-bg-primary)` (6 occurrences)
3. `#f39c12` → `var(--octane-accent-orange)` (4 occurrences)
4. `#444` → `var(--octane-border)` (5 occurrences)
5. `#e0e0e0` → `var(--octane-text-primary)` (3 occurrences)
6. `#ccc` → `var(--octane-text-secondary)` (4 occurrences)
7. `#888` → `var(--octane-text-muted)` (3 occurrences)
8. `#333` → `var(--octane-border-dark)` (3 occurrences)
9. `#27ae60` → `var(--octane-accent-green)` (2 occurrences)
10. `#e74c3c` → `var(--octane-accent-red)` (2 occurrences)

### MaterialDatabase.css (256 lines, 50 colors)
**Top 10 colors to replace:**
1. `#2b2b2b` → `var(--octane-bg-primary)` (12 occurrences)
2. `#ffffff` → `var(--octane-text-primary)` (8 occurrences)
3. `#555555` → `var(--octane-border)` (6 occurrences)
4. `#3c3c3c` → `var(--octane-bg-secondary)` (5 occurrences)
5. `#cccccc` → `var(--octane-text-secondary)` (4 occurrences)
6. `#ffc107` → `var(--octane-accent-yellow)` (3 occurrences)
7. `#404040` → `var(--octane-bg-header)` (3 occurrences)
8. `#1e1e1e` → `var(--octane-bg-darker)` (2 occurrences)
9. `#888888` → `var(--octane-text-muted)` (2 occurrences)
10. `rgba(0,0,0,0.5)` → `var(--octane-overlay-medium)` (2 occurrences)

### GPUStatisticsDialog.css (193 lines, 27 colors)
**Top 10 colors to replace:**
1. `#2b2b2b` → `var(--octane-bg-primary)` (8 occurrences)
2. `#ffffff` → `var(--octane-text-primary)` (5 occurrences)
3. `#555555` → `var(--octane-border)` (4 occurrences)
4. `#3c3c3c` → `var(--octane-bg-secondary)` (3 occurrences)
5. `#cccccc` → `var(--octane-text-secondary)` (2 occurrences)
6. `#404040` → `var(--octane-bg-header)` (2 occurrences)
7. `#1e1e1e` → `var(--octane-bg-darker)` (1 occurrence)
8. `#888888` → `var(--octane-text-muted)` (1 occurrence)
9. `rgba(0,0,0,0.8)` → `var(--octane-overlay-dark)` (1 occurrence)

---

## ✅ Verification Checklist

After converting a file:

- [ ] All hardcoded hex colors replaced (except SVG data URLs)
- [ ] All rgba colors converted or justified
- [ ] File still uses correct colors visually
- [ ] npm run build passes
- [ ] npm run dev shows no visual regressions
- [ ] Component works in all states (hover, selected, disabled)

---

## 🔍 Find Unconverted Colors

After conversion, check for remaining hardcoded colors:

```bash
# Find remaining hex colors
grep -n "#[0-9a-fA-F]\{3,6\}" app.css | grep -v "data:image"

# Find remaining rgba colors  
grep -n "rgba\?(" app.css

# Expected result: Only colors in comments or data URLs
```

---

**Use this reference while converting CSS files to ensure consistency!**
