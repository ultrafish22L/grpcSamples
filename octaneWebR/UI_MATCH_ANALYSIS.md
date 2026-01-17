# OctaneWebR → OctaneSE UI Match Analysis

**Goal:** Make octaneWebR's UI pixel-perfect match to Octane Standalone Edition

**Reference Images:**
- Target: `references-images/octane-reference.png` (OctaneSE)
- Current: `references-images/octaneWebR-reference.png` (octaneWebR)

---

## 🎨 **1. COLOR PALETTE DIFFERENCES**

### Background Colors
| Element | OctaneSE | OctaneWebR | Action |
|---------|----------|------------|--------|
| Main BG | `#3c3c3c` (darker gray) | Similar but may be lighter | Verify exact hex values |
| Secondary BG | `#2d2d2d` | Needs verification | Match precisely |
| Panel BG | `#333333` | Needs verification | Match precisely |
| Hover BG | Subtle lighter gray | May be too bright | Reduce brightness |
| Selected BG | Dark with subtle highlight | May be too saturated | Tune down |

### Border Colors
| Element | OctaneSE | OctaneWebR | Action |
|---------|----------|------------|--------|
| Panel borders | Very subtle `#404040` | May be too visible | Reduce contrast |
| Dividers | Almost invisible | Too visible | Make more subtle |
| Input borders | `#505050` | May differ | Match precisely |

### Text Colors
| Element | OctaneSE | OctaneWebR | Action |
|---------|----------|------------|--------|
| Primary text | `#d0d0d0` (light gray) | May be too white | Reduce brightness |
| Secondary text | `#999999` | May differ | Match precisely |
| Disabled text | `#666666` | May differ | Match precisely |

### Accent Colors
| Element | OctaneSE | OctaneWebR | Action |
|---------|----------|------------|--------|
| Blue accent | Muted blue | May be too saturated | Reduce saturation |
| Selection highlight | Subtle orange/yellow | May differ | Match precisely |
| Active parameter | Subtle highlight | May be too bright | Tune down |

---

## 📐 **2. SPACING & SIZING SYSTEM**

### Scene Outliner
| Property | OctaneSE | OctaneWebR | Fix |
|----------|----------|------------|-----|
| Tree item height | ~20px | Appears taller (~24-26px) | Reduce to 20px |
| Left indent per level | 16px | May be 20-24px | Reduce to 16px |
| Icon size | 14px | May be 16px | Reduce to 14px |
| Icon-to-text spacing | 4px | May be 6-8px | Reduce to 4px |
| Top/bottom padding | 2px | May be 4px | Reduce to 2px |
| Vertical spacing | Tight, ~0-1px | Looser, 2-4px | Tighten spacing |

### Node Inspector
| Property | OctaneSE | OctaneWebR | Fix |
|----------|----------|------------|-----|
| Section header height | ~22px | Appears ~28-30px | Reduce to 22px |
| Parameter row height | ~18-20px | Appears ~24-26px | Reduce to 18-20px |
| Label width | ~120px | May be wider | Reduce to 120px |
| Input height | 16px | Appears 18-20px | Reduce to 16px |
| Section padding | 4px vertical | May be 6-8px | Reduce to 4px |
| Row spacing | 1-2px | 4-6px | Reduce to 1-2px |
| Checkbox size | 12px | 14-16px | Reduce to 12px |
| Slider height | 4px track | May be 6px | Reduce to 4px |

### Node Graph
| Property | OctaneSE | OctaneWebR | Fix |
|----------|----------|------------|-----|
| Grid size | 20px | May be 25px | Match to 20px |
| Node min-width | ~160px | May differ | Match precisely |
| Node header height | 24px | May be 28px | Reduce to 24px |
| Pin size | 10px | May be 12px | Reduce to 10px |
| Node padding | 8px | May be 12px | Reduce to 8px |

### General
| Property | OctaneSE | OctaneWebR | Fix |
|----------|----------|------------|-----|
| Border radius | 2px (very subtle) | 3-4px | Reduce to 2px |
| Font size base | 11px | 12px | Reduce to 11px |
| Font size small | 10px | 11px | Reduce to 10px |
| Line height | 1.2 | May be 1.4-1.5 | Reduce to 1.2 |

---

## 🎯 **3. COMPONENT-SPECIFIC STYLING**

### A. Scene Outliner Tree Items

**OctaneSE Style:**
- Very compact, tight spacing
- Subtle triangle toggle (▸/▾)
- Icons are small, muted colors
- Selected item: subtle background, no bold text
- Hover: very subtle highlight
- Checkboxes: small, square, flat

**OctaneWebR Issues:**
- ❌ Too much vertical spacing
- ❌ Icons may be too large
- ❌ Font may be too bold
- ❌ Selected highlighting too prominent
- ❌ Checkboxes too large/styled

**Fix:**
```css
.tree-node {
    height: 20px;
    padding: 2px 4px;
    font-size: 11px;
    line-height: 16px;
}

.tree-node-icon {
    width: 14px;
    height: 14px;
    margin-right: 4px;
}

.tree-node.selected {
    background: rgba(255, 255, 255, 0.05); /* Very subtle */
}

.tree-node:hover {
    background: rgba(255, 255, 255, 0.03); /* Even more subtle */
}
```

---

### B. Node Inspector Parameters

**OctaneSE Style:**
- Very compact rows (~18-20px height)
- Checkboxes to left of label
- Labels are gray, not bold
- Numeric inputs are small, minimal borders
- Sliders are thin (4px track)
- Sections have minimal headers
- No excessive spacing between parameters

**OctaneWebR Issues:**
- ❌ Rows too tall (24-26px)
- ❌ Too much padding/spacing
- ❌ Input controls too large
- ❌ Section headers too prominent
- ❌ Font size too large

**Fix:**
```css
.parameter-row {
    height: 18px;
    padding: 1px 4px;
    margin-bottom: 1px;
    font-size: 11px;
}

.parameter-label {
    color: #999;
    font-weight: normal;
    width: 120px;
    font-size: 11px;
}

.parameter-checkbox {
    width: 12px;
    height: 12px;
    margin-right: 4px;
}

.parameter-input {
    height: 16px;
    font-size: 11px;
    padding: 0 4px;
    border: 1px solid #505050;
}

.parameter-slider-track {
    height: 4px;
    border-radius: 1px;
}

.parameter-slider-thumb {
    width: 8px;
    height: 12px;
    border-radius: 1px;
}
```

---

### C. Node Graph Editor

**OctaneSE Style:**
- Grid: subtle, dark, 20px squares
- Nodes: compact, minimal shadows
- Pins: small circles (10px)
- Connections: smooth curves, thin lines
- Selected node: subtle orange border

**OctaneWebR Issues:**
- ❌ Grid may be too visible/large
- ❌ Nodes may be too large/spaced
- ❌ Pins may be too large
- ❌ Shadows may be too prominent

**Fix:**
```css
/* Grid pattern */
.react-flow__background {
    background-size: 20px 20px;
    background-color: #2d2d2d;
}

.react-flow__background-pattern {
    stroke: #383838;
    stroke-width: 0.5;
}

/* Nodes */
.node {
    min-width: 160px;
    border-radius: 2px;
    box-shadow: 0 1px 3px rgba(0,0,0,0.3);
}

.node-header {
    height: 24px;
    padding: 4px 8px;
    font-size: 11px;
}

/* Pins */
.node-pin {
    width: 10px;
    height: 10px;
    border-radius: 5px;
}
```

---

### D. Menu Bar & Dropdowns

**OctaneSE Style:**
- Dark gray background (#2d2d2d)
- Menu items: light gray text, normal weight
- Spacing: 16px between items
- Dropdown: dark, subtle border, compact items
- Font size: 11-12px

**OctaneWebR Issues:**
- ❌ Font may be too bold/large
- ❌ Spacing may be too generous
- ❌ Dropdown backgrounds transparent (known bug)

**Fix:**
```css
.menu-bar {
    background: #2d2d2d;
    height: 28px;
    padding: 0 8px;
}

.menu-item {
    padding: 6px 16px;
    font-size: 12px;
    font-weight: normal;
    color: #d0d0d0;
}

.menu-dropdown {
    background: #3c3c3c;
    border: 1px solid #505050;
    padding: 2px 0;
}

.menu-dropdown-item {
    height: 20px;
    padding: 2px 24px 2px 12px;
    font-size: 11px;
}
```

---

### E. Status Bar

**OctaneSE Style:**
- Dark gray background
- Compact height (~24px)
- Small icons and text (10-11px)
- Tight spacing between elements
- Subtle separators

**OctaneWebR Issues:**
- ❌ May be too tall
- ❌ Font may be too large
- ❌ Spacing may be too generous

**Fix:**
```css
.status-bar {
    height: 24px;
    background: #2d2d2d;
    border-top: 1px solid #404040;
    padding: 0 8px;
    font-size: 10px;
}

.status-item {
    padding: 0 8px;
    height: 24px;
    line-height: 24px;
}
```

---

## 🔤 **4. TYPOGRAPHY**

### Font Family
**OctaneSE:** Uses system fonts, appears to be:
- Windows: Segoe UI
- macOS: San Francisco / Helvetica Neue

**OctaneWebR:** Currently using system fonts via CSS variable

**Action:** Verify font stack matches exactly:
```css
--font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Arial, sans-serif;
```

### Font Sizes
| Context | OctaneSE | OctaneWebR | Fix |
|---------|----------|------------|-----|
| Base UI | 11px | 12px | Reduce to 11px |
| Menu bar | 12px | 13px? | Reduce to 12px |
| Tree items | 11px | 12px | Reduce to 11px |
| Parameters | 11px | 12px | Reduce to 11px |
| Status bar | 10px | 11px | Reduce to 10px |
| Small labels | 10px | 11px | Reduce to 10px |

### Font Weights
| Context | OctaneSE | OctaneWebR | Fix |
|---------|----------|------------|-----|
| Normal text | 400 | May be 500 | Use 400 |
| Headers | 400-500 | May be 600 | Use 400-500 |
| Bold | 600 | May be 700 | Use 600 |

### Font Rendering
**OctaneSE:** Uses system rendering
**Action:** Ensure antialiasing matches:
```css
body {
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-rendering: optimizeLegibility;
}
```

---

## 🎛️ **5. CONTROL STYLING DETAILS**

### Checkboxes
**OctaneSE:**
- Size: 12x12px
- Border: 1px solid #505050
- Background: #2d2d2d
- Checked: small checkmark, subtle blue tint
- Border radius: 1-2px (very subtle)

**Fix:**
```css
.checkbox {
    width: 12px;
    height: 12px;
    border: 1px solid #505050;
    background: #2d2d2d;
    border-radius: 1px;
}

.checkbox:checked {
    background: #3d4d5d;
    border-color: #5080a0;
}
```

### Sliders
**OctaneSE:**
- Track: 4px height, dark gray (#2d2d2d)
- Fill: subtle blue (#4060a0)
- Thumb: 8px wide, 12px tall, light gray
- Border radius: 1px (minimal)

**Fix:**
```css
.slider-track {
    height: 4px;
    background: #2d2d2d;
    border: 1px solid #404040;
    border-radius: 1px;
}

.slider-fill {
    background: #4060a0;
    height: 100%;
}

.slider-thumb {
    width: 8px;
    height: 12px;
    background: #808080;
    border: 1px solid #606060;
    border-radius: 1px;
}
```

### Number Inputs
**OctaneSE:**
- Height: 16px
- Font: 11px
- Padding: 0 4px
- Border: 1px solid #505050
- Background: #2d2d2d
- Text align: right (for numbers)

**Fix:**
```css
.number-input {
    height: 16px;
    font-size: 11px;
    padding: 0 4px;
    border: 1px solid #505050;
    background: #2d2d2d;
    color: #d0d0d0;
    text-align: right;
    border-radius: 2px;
}

.number-input:focus {
    border-color: #6080a0;
    outline: none;
}
```

### Dropdowns
**OctaneSE:**
- Height: 16-18px
- Font: 11px
- Padding: 0 20px 0 4px (space for arrow)
- Arrow: small, subtle, right-aligned
- Border: 1px solid #505050

**Fix:**
```css
.dropdown {
    height: 16px;
    font-size: 11px;
    padding: 0 20px 0 4px;
    border: 1px solid #505050;
    background: #2d2d2d;
    border-radius: 2px;
}

.dropdown-arrow {
    width: 0;
    height: 0;
    border-left: 3px solid transparent;
    border-right: 3px solid transparent;
    border-top: 4px solid #808080;
}
```

### Color Pickers
**OctaneSE:**
- Preview: 16x16px square
- Border: 1px solid #505050
- Shows actual color with alpha checkerboard behind
- Click opens full color picker dialog

**Fix:**
```css
.color-preview {
    width: 16px;
    height: 16px;
    border: 1px solid #505050;
    border-radius: 2px;
    cursor: pointer;
}

.color-preview:hover {
    border-color: #6080a0;
}
```

---

## 📊 **6. SECTION HEADERS & COLLAPSIBLE GROUPS**

### Node Inspector Section Headers
**OctaneSE:**
- Height: ~22px
- Background: slightly darker than rows
- Triangle toggle: small (▸/▾), left side
- Text: 11px, normal weight, light gray
- Padding: 3px 4px
- No bold, no large font

**Fix:**
```css
.section-header {
    height: 22px;
    padding: 3px 4px;
    background: #333;
    border-bottom: 1px solid #3a3a3a;
    font-size: 11px;
    font-weight: normal;
    color: #b0b0b0;
    cursor: pointer;
}

.section-toggle {
    width: 12px;
    height: 12px;
    margin-right: 4px;
    font-size: 10px;
}

.section-header:hover {
    background: #373737;
}
```

---

## 🎨 **7. VISUAL EFFECTS**

### Shadows
**OctaneSE:** Very minimal shadows, barely noticeable

| Element | OctaneSE | OctaneWebR | Fix |
|---------|----------|------------|-----|
| Panels | `0 1px 2px rgba(0,0,0,0.2)` | May be stronger | Reduce opacity |
| Nodes | `0 1px 3px rgba(0,0,0,0.3)` | May be stronger | Reduce opacity |
| Dropdowns | `0 2px 4px rgba(0,0,0,0.25)` | May be stronger | Reduce opacity |
| Modals | `0 4px 8px rgba(0,0,0,0.3)` | May be stronger | Reduce opacity |

### Border Radius
**OctaneSE:** Very subtle, mostly 1-2px

**Fix all border-radius values:**
```css
--border-radius-sm: 1px;
--border-radius: 2px;
--border-radius-md: 2px;
--border-radius-lg: 3px;
```

### Transitions
**OctaneSE:** Quick, subtle transitions

**Fix:**
```css
--transition-fast: 0.1s ease;
--transition-normal: 0.15s ease;
--transition-slow: 0.2s ease;
```

---

## 🔍 **8. SPECIFIC COMPONENT FIXES NEEDED**

### Scene Outliner
**Files:** `scene-outliner.css`, `octane-theme.css`

**Changes:**
1. Reduce tree item height to 20px
2. Reduce indent per level to 16px
3. Make icons 14x14px
4. Reduce spacing between icon and text to 4px
5. Make selected/hover backgrounds more subtle
6. Reduce checkbox size to 12px
7. Tighten vertical spacing between items
8. Use lighter font weight
9. Reduce font size to 11px

### Node Inspector
**Files:** `node-inspector.css`, `octane-theme.css`

**Changes:**
1. Reduce parameter row height to 18-20px
2. Reduce section header height to 22px
3. Reduce all control sizes (checkboxes, sliders, inputs)
4. Tighten spacing between rows to 1-2px
5. Reduce font size to 11px
6. Make section headers less prominent
7. Reduce input control heights to 16px
8. Make slider tracks 4px height
9. Reduce padding throughout

### Node Graph
**Files:** `node-graph.css`

**Changes:**
1. Match grid size to 20px
2. Reduce node padding to 8px
3. Reduce node header height to 24px
4. Make pins 10px diameter
5. Reduce shadows
6. Tighten overall spacing
7. Match connection line thickness

### Menu Bar
**Files:** `app.css`, `octane-theme.css`

**Changes:**
1. Reduce height to 28px
2. Use font-size: 12px, font-weight: normal
3. Fix dropdown backgrounds (known bug)
4. Reduce spacing between items
5. Make dropdowns more compact
6. Match dropdown item height to 20px

### Status Bar
**Files:** `app.css`, `octane-theme.css`

**Changes:**
1. Reduce height to 24px
2. Use font-size: 10px
3. Tighten spacing between elements
4. Make icons smaller
5. Reduce padding

---

## 📋 **9. CSS VARIABLE UPDATES NEEDED**

### Colors
```css
/* Update in octane-theme.css */
--octane-bg-primary: #3c3c3c;           /* Main background */
--octane-bg-secondary: #2d2d2d;         /* Secondary/darker background */
--octane-bg-tertiary: #333333;          /* Panel backgrounds */
--octane-bg-hover: rgba(255,255,255,0.03); /* Very subtle hover */
--octane-bg-selected: rgba(255,255,255,0.05); /* Very subtle selected */

--octane-border: #404040;               /* Subtle borders */
--octane-border-light: #505050;         /* Slightly lighter borders */
--octane-border-dark: #303030;          /* Darker borders */

--octane-text-primary: #d0d0d0;         /* Main text */
--octane-text-secondary: #999999;       /* Secondary text */
--octane-text-tertiary: #808080;        /* Tertiary/disabled text */

--octane-accent-blue: #4060a0;          /* Muted blue */
--octane-accent-orange: #d88030;        /* Muted orange */
```

### Sizing
```css
/* Update in octane-theme.css */
--font-size-base: 11px;
--font-size-small: 10px;
--font-size-large: 12px;

--line-height-base: 1.2;
--line-height-compact: 1.1;

--spacing-xs: 2px;
--spacing-sm: 4px;
--spacing-md: 8px;
--spacing-lg: 12px;

--control-height-sm: 16px;
--control-height-md: 18px;
--control-height-lg: 20px;

--border-radius-sm: 1px;
--border-radius: 2px;
--border-radius-md: 2px;
--border-radius-lg: 3px;
```

---

## 🛠️ **10. IMPLEMENTATION PLAN**

### Phase 1: Typography & Base Sizing (CRITICAL)
**Impact:** Cascading effect on all components
**Tasks:**
1. Reduce base font size from 12px to 11px
2. Reduce line-height to 1.2
3. Update all font-weight values to be lighter
4. Verify font-family stack
5. Test rendering on multiple browsers/OS

**Files:** `octane-theme.css` (CSS variables)

---

### Phase 2: Color Palette Refinement
**Impact:** Visual consistency across all components
**Tasks:**
1. Update all gray values to exact OctaneSE values
2. Reduce hover/selected background opacity
3. Make borders more subtle
4. Update accent colors to be less saturated
5. Fix text color brightness

**Files:** `octane-theme.css` (color variables)

---

### Phase 3: Scene Outliner Compact Layout
**Impact:** Left panel visual match
**Tasks:**
1. Reduce tree item height to 20px
2. Reduce indent to 16px per level
3. Shrink icons to 14x14px
4. Tighten all spacing
5. Update checkbox styling
6. Reduce font sizes

**Files:** `scene-outliner.css`, `layout.css`

---

### Phase 4: Node Inspector Compact Layout
**Impact:** Right panel visual match (CRITICAL - most visible)
**Tasks:**
1. Reduce parameter row height to 18-20px
2. Reduce section headers to 22px
3. Shrink all input controls
4. Tighten vertical spacing to 1-2px
5. Update slider styling (4px track)
6. Update checkbox size (12x12px)
7. Update dropdown styling
8. Reduce padding throughout

**Files:** `node-inspector.css`, `octane-theme.css`

---

### Phase 5: Node Graph Refinement
**Impact:** Bottom panel visual match
**Tasks:**
1. Match grid size to 20px
2. Reduce node sizes and spacing
3. Update pin sizes to 10px
4. Reduce shadows
5. Update connection styling
6. Tighten toolbar

**Files:** `node-graph.css`

---

### Phase 6: Menu Bar & Status Bar
**Impact:** Top and bottom chrome
**Tasks:**
1. Reduce menu bar to 28px height
2. Fix dropdown backgrounds (known bug)
3. Update menu item styling
4. Reduce status bar to 24px
5. Shrink status bar fonts to 10px
6. Tighten spacing

**Files:** `app.css`, `octane-theme.css`

---

### Phase 7: Control Refinement
**Impact:** Fine-tuning for pixel-perfect match
**Tasks:**
1. Update all checkbox styling
2. Update all slider styling
3. Update all input field styling
4. Update all dropdown styling
5. Update color picker styling
6. Test all interactive states (hover, focus, active, disabled)

**Files:** `octane-theme.css`, component-specific CSS files

---

### Phase 8: Visual Effects Polish
**Impact:** Final polish
**Tasks:**
1. Reduce shadow strengths
2. Update border-radius to 1-2px everywhere
3. Speed up transitions to 0.1-0.15s
4. Test on different displays/zoom levels
5. Fine-tune any remaining visual differences

**Files:** All CSS files

---

## 🎯 **11. PRIORITY ORDER**

### 🔥 **Critical (Do First)**
These have the most visible impact:

1. **Typography & Base Sizing** (Phase 1)
   - Reduces 12px → 11px everywhere
   - Cascading effect on all components
   - Single file change: `octane-theme.css` variables

2. **Node Inspector Compact Layout** (Phase 4)
   - Most visible panel in typical workflow
   - Most parameters to adjust
   - Biggest visual difference currently

3. **Color Palette Refinement** (Phase 2)
   - Affects all components
   - Makes hover/selected states match
   - Single file change: `octane-theme.css` variables

### ⚡ **High Priority (Do Second)**

4. **Scene Outliner Compact Layout** (Phase 3)
   - Highly visible left panel
   - Many spacing adjustments needed

5. **Menu Bar & Status Bar** (Phase 6)
   - Always visible chrome
   - Includes dropdown background bug fix

### ✅ **Medium Priority (Do Third)**

6. **Node Graph Refinement** (Phase 5)
   - Less critical than inspector/outliner
   - Still important for overall feel

7. **Control Refinement** (Phase 7)
   - Fine-tuning of individual controls
   - Depends on earlier phases

### 🎨 **Polish (Do Last)**

8. **Visual Effects Polish** (Phase 8)
   - Final pixel-perfect tuning
   - Test on multiple displays
   - Cross-browser verification

---

## 📸 **12. VERIFICATION CHECKLIST**

After each phase, verify against reference images:

### Visual Comparison
- [ ] Take screenshot of same scene/view
- [ ] Overlay with OctaneSE reference
- [ ] Check spacing matches pixel-perfect
- [ ] Check colors match exactly
- [ ] Check font rendering looks identical

### Functional Testing
- [ ] All controls still work
- [ ] Hover states function correctly
- [ ] Selected states show properly
- [ ] Transitions feel smooth
- [ ] No layout breaks at different sizes

### Cross-browser Testing
- [ ] Chrome/Edge (Chromium)
- [ ] Firefox
- [ ] Safari (if on macOS)
- [ ] Test on Windows and macOS if possible

### Zoom Level Testing
- [ ] Test at 100% zoom
- [ ] Test at 90% zoom
- [ ] Test at 110% zoom
- [ ] Test at 125% zoom

---

## 📐 **13. MEASUREMENT REFERENCE**

### Key Measurements from OctaneSE (Pixel Counts)

**Scene Outliner:**
- Tree item height: ~20px
- Indent per level: ~16px
- Icon size: ~14x14px
- Checkbox size: ~12x12px
- Font size: appears to be 11px

**Node Inspector:**
- Parameter row: ~18-20px height
- Section header: ~22px height
- Input controls: ~16px height
- Checkbox: ~12x12px
- Slider track: ~4px height
- Label width: ~120px
- Font size: appears to be 11px

**Node Graph:**
- Grid squares: ~20x20px
- Node header: ~24px height
- Pin diameter: ~10px
- Node min-width: ~160px

**Chrome:**
- Menu bar: ~28px height
- Status bar: ~24px height
- Splitter width: ~4-6px

---

## 🎨 **14. COLOR SAMPLER VALUES**

*Note: These should be sampled directly from octane-reference.png using a color picker for exact values*

**Recommended sampling points:**
1. Main background (viewport area)
2. Panel backgrounds (outliner, inspector)
3. Menu bar background
4. Selected tree item background
5. Hover state background
6. Input field background
7. Border colors (various locations)
8. Primary text color
9. Secondary text color
10. Disabled text color

**TODO:** Use digital color picker on reference image to get exact hex values.

---

## ✅ **15. SUCCESS CRITERIA**

The UI match will be considered successful when:

1. **Visual Comparison Test Passes:**
   - Screenshot overlay shows <5px difference in positioning
   - Colors match within <5 RGB units
   - Font sizes match exactly
   - Spacing matches within 2px

2. **User Can't Tell Difference:**
   - Side-by-side comparison is nearly indistinguishable
   - Muscle memory from OctaneSE works in octaneWebR
   - No "off" feeling when switching between them

3. **All Components Match:**
   - Scene Outliner: ✓
   - Node Inspector: ✓
   - Node Graph: ✓
   - Menu Bar: ✓
   - Status Bar: ✓
   - All controls: ✓

4. **Functional Parity:**
   - All interactions work smoothly
   - Hover/focus/active states match
   - Transitions feel identical
   - Performance is good (no jank)

---

## 📝 **NOTES**

1. **Font Rendering:** Different browsers and OS render fonts differently. May need to test adjustments per platform.

2. **Retina/HiDPI:** Test on both standard and retina displays to ensure pixel-perfect rendering.

3. **Browser Zoom:** OctaneSE is native app, so it doesn't zoom. But web apps should still look good at common zoom levels (90%-125%).

4. **Color Accuracy:** Use actual color picker on reference image, don't guess values.

5. **Measurement Tools:** Use browser DevTools pixel ruler or dedicated screen measurement tools for exact values.

6. **Iterative Process:** This will require multiple iterations. Start broad (typography, colors), then narrow down to specific components.

7. **Known Bug:** Transparent dropdown backgrounds need fix (already identified).

8. **Documentation:** Keep this doc updated as changes are made. Mark phases as complete.

---

**Last Updated:** 2024 (Initial analysis)
**Status:** Ready for implementation
**Next Step:** Begin Phase 1 (Typography & Base Sizing)
