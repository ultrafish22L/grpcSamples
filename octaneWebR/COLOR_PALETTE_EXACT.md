# Exact Color Palette Analysis
## OctaneSE vs OctaneWebR

**Generated:** Color sampling from reference images  
**Method:** ImageMagick sampling of reference screenshots  
**Note:** Colors sampled from screenshots may vary slightly from actual application values due to compression/color profiles

---

## 📊 SAMPLED VALUES FROM OCTANE SE

### Background Colors (Dark Panels)

| Element | Sampled Color | RGB | Current octaneWebR | Notes |
|---------|--------------|-----|-------------------|-------|
| Scene Outliner BG | `#454545` | 69,69,69 | `#2b2b2b` (43,43,43) | OctaneSE is **lighter** |
| Node Inspector BG | `#675F47`-`#5E605B` | varies | `#2b2b2b` | Sampling hit content/unclear |
| Node Graph BG | `#252525` | 37,37,37 | `#2b2b2b` (43,43,43) | OctaneSE is **darker** |
| Menu Bar BG | `#313131` | 49,49,49 | `#27403C` | OctaneSE is lighter gray |
| Normal tree item | `#1B1B1B` | 27,27,27 | - | Very dark, almost black |

**Analysis:**  
The dark panel backgrounds in OctaneSE appear to range from `#252525` (very dark) to `#454545` (medium-dark gray). Our current `#2b2b2b` falls in this range but may be too dark for some panels.

**Recommended Values:**
```css
--octane-bg-primary: #3c3c3c;      /* Main panels - medium dark gray */
--octane-bg-secondary: #2d2d2d;    /* Darker areas */
--octane-bg-darker: #252525;       /* Very dark (node graph) */
--octane-bg-header: #313131;       /* Menu bar */
```

---

### Selection & Hover States

| Element | Sampled Color | RGB | Current octaneWebR | Notes |
|---------|--------------|-----|-------------------|-------|
| Selected item BG | `#454545` | 69,69,69 | `#4a4a4a` (74,74,74) | Very close! |
| Normal item | `#1B1B1B` | 27,27,27 | - | For contrast reference |

**Observations:**
- Selected items appear slightly darker than our current value
- The contrast between normal and selected is subtle (27 → 69)
- Need to keep hover states even more subtle

**Recommended Values:**
```css
--octane-bg-selected: #454545;          /* Slightly darker than current */
--octane-bg-hover: rgba(255,255,255,0.03);  /* Very subtle overlay */
```

---

### Text Colors

| Element | Sampled Color | RGB | Current octaneWebR | Notes |
|---------|--------------|-----|-------------------|-------|
| Light text (tree) | `#424242` | 66,66,66 | `#ffffff` (255,255,255) | WRONG - but hit dark bg? |
| Gray text (params) | `#808080` | 128,128,128 | `#999999` (153,153,153) | OctaneSE is darker gray |
| Menu text | `#3D3D3D` | 61,61,61 | - | WRONG - likely sampled bg |

**Analysis:**  
Text sampling is unreliable from screenshot due to antialiasing and small sample size. Based on visual inspection of the reference image:

- Primary text appears to be light gray, approximately `#d0d0d0` to `#e0e0e0`
- Secondary text (parameter labels) appears to be medium gray `#808080` to `#999999`
- Disabled text appears darker gray `#606060` to `#707070`

**Recommended Values:**
```css
--octane-text-primary: #d0d0d0;     /* Light gray, not pure white */
--octane-text-secondary: #999999;   /* Medium gray */
--octane-text-muted: #808080;       /* Darker gray */
--octane-text-disabled: #666666;    /* Very dark gray */
```

---

### Borders & Dividers

| Element | Sampled Color | RGB | Current octaneWebR | Notes |
|---------|--------------|-----|-------------------|-------|
| Panel splitter (left) | `#454545` | 69,69,69 | `#555555` (85,85,85) | OctaneSE is darker |
| Panel splitter (right) | `#4A4733` | varies | `#555555` | Hit content area |
| Input border | `#808080` | 128,128,128 | `#555555` (85,85,85) | OctaneSE is **lighter** |

**Analysis:**  
Borders in OctaneSE appear very subtle, barely visible against backgrounds. Panel splitters especially are hard to see.

**Recommended Values:**
```css
--octane-border: #404040;           /* Very subtle, barely visible */
--octane-border-light: #505050;     /* Slightly more visible */
--octane-border-input: #505050;     /* Input field borders */
--octane-splitter: #3a3a3a;         /* Panel splitters (nearly invisible) */
```

---

## 🎨 VISUAL INSPECTION OBSERVATIONS

From careful visual examination of `octane-reference.png`:

### Scene Outliner (Left Panel)
- Background: **Very dark gray**, appears uniform
- Selected item: **Subtle orange tint** on dark background (RenderTarget DL)
- Tree items: Very compact, tight spacing
- Text: Light gray, not pure white
- Checkboxes: Small, subtle, flat design

### Node Inspector (Right Panel)
- Background: **Dark gray**, similar to outliner
- Section headers: **Slightly darker** than main background
- Parameter labels: **Medium gray text** (#808080 to #999999 range)
- Input fields: **Very dark** background, subtle borders
- Sliders: Thin (4px track), subtle blue fill
- Overall: Very tight spacing, compact layout

### Node Graph (Bottom Panel)
- Background: **Darkest** of all panels (appears `#252525` or similar)
- Grid: Barely visible, very subtle
- Nodes: Dark gray, minimal shadows
- Selected node: **Subtle orange border**
- Connections: Smooth curves, thin lines

### Menu Bar
- Background: **Dark gray** (`#313131` range)
- Text: Light gray
- Dropdowns: Dark background, subtle borders

### Status Bar
- Background: **Medium gray**, lighter than panels
- Text: Small (10px), light colored
- Elements: Compact spacing

---

## 🔍 COMPARISON: OctaneWebR Current State

### What's Different?

1. **Backgrounds Too Dark in Some Places:**
   - Current `#2b2b2b` may be too dark for main panels
   - OctaneSE appears closer to `#3c3c3c` for main areas

2. **Text Too Bright:**
   - Current `#ffffff` pure white is too bright
   - Should be `#d0d0d0` or similar light gray

3. **Borders Too Visible:**
   - Current `#555555` stands out too much
   - Should be `#404040` to nearly disappear

4. **Hover/Selected Too Bright:**
   - Current values may be too prominent
   - Need extremely subtle overlays

---

## ✅ RECOMMENDED COLOR PALETTE UPDATE

Based on all sampling and visual inspection:

```css
/* ========================================
   OCTANE SE COLOR PALETTE - EXACT MATCH
   ======================================== */

:root {
  /* === BACKGROUNDS === */
  --octane-bg-primary: #3c3c3c;         /* Main panel background */
  --octane-bg-secondary: #2d2d2d;       /* Secondary/darker background */
  --octane-bg-darker: #252525;          /* Node graph, darkest areas */
  --octane-bg-header: #313131;          /* Menu bar, headers */
  
  /* === INTERACTIVE STATES === */
  --octane-bg-hover: rgba(255,255,255,0.03);    /* Very subtle hover */
  --octane-bg-selected: #454545;        /* Selected items */
  --octane-bg-active: rgba(255,255,255,0.08);   /* Pressed/active */
  
  /* === SECTION BACKGROUNDS === */
  --octane-bg-section-header: #333333;  /* Section headers (slightly darker) */
  --octane-bg-input: #2d2d2d;           /* Input fields background */
  --octane-bg-viewport: #808080;        /* Viewport chrome area */
  
  /* === TEXT COLORS === */
  --octane-text-primary: #d0d0d0;       /* Main text (light gray) */
  --octane-text-secondary: #999999;     /* Secondary text (medium gray) */
  --octane-text-muted: #808080;         /* Muted text (darker gray) */
  --octane-text-disabled: #666666;      /* Disabled text (very dark gray) */
  
  /* === BORDERS === */
  --octane-border: #404040;             /* Standard borders (very subtle) */
  --octane-border-light: #505050;       /* Slightly more visible borders */
  --octane-border-input: #505050;       /* Input field borders */
  --octane-border-dark: #303030;        /* Darker borders */
  --octane-splitter: #3a3a3a;           /* Panel splitters (nearly invisible) */
  
  /* === ACCENTS === */
  --octane-accent-blue: #4060a0;        /* Blue accent (sliders, etc) */
  --octane-accent-orange: #d88030;      /* Orange selection highlight */
  --octane-accent-blue-hover: #5080c0;  /* Blue hover state */
  
  /* === CONTROL BACKGROUNDS === */
  --octane-checkbox-bg: #2d2d2d;        /* Checkbox background */
  --octane-checkbox-border: #505050;    /* Checkbox border */
  --octane-checkbox-checked: #3d4d5d;   /* Checked state (subtle blue tint) */
  
  --octane-slider-track: #2d2d2d;       /* Slider track background */
  --octane-slider-fill: #4060a0;        /* Slider fill (blue) */
  --octane-slider-thumb: #808080;       /* Slider thumb */
  
  --octane-dropdown-bg: #363636;        /* Dropdown background */
  --octane-dropdown-hover: #404040;     /* Dropdown item hover */
}
```

---

## 📝 KEY CHANGES FROM CURRENT

### Backgrounds
| Variable | Old Value | New Value | Change |
|----------|-----------|-----------|---------|
| `--octane-bg-primary` | `#2b2b2b` | `#3c3c3c` | **+17 units lighter** |
| `--octane-bg-secondary` | `#3c3c3c` | `#2d2d2d` | -15 units darker (swap roles) |
| `--octane-bg-darker` | `#323232` | `#252525` | -13 units darker |
| `--octane-bg-header` | `#404040` | `#313131` | -15 units darker |

### Text
| Variable | Old Value | New Value | Change |
|----------|-----------|-----------|---------|
| `--octane-text-primary` | `#ffffff` | `#d0d0d0` | **-47 units dimmer** |
| `--octane-text-secondary` | `#cccccc` | `#999999` | **-51 units darker** |
| `--octane-text-muted` | `#999999` | `#808080` | -25 units darker |

### Borders
| Variable | Old Value | New Value | Change |
|----------|-----------|-----------|---------|
| `--octane-border` | `#555555` | `#404040` | **-21 units darker (more subtle)** |
| `--octane-border-light` | `#666666` | `#505050` | **-22 units darker** |

### Interactive States
| Variable | Old Value | New Value | Change |
|----------|-----------|-----------|---------|
| `--octane-bg-hover` | `#484848` | `rgba(255,255,255,0.03)` | **Much more subtle** |
| `--octane-bg-selected` | `#4a4a4a` | `#454545` | -5 units darker |

---

## 🎯 CONFIDENCE LEVELS

### High Confidence (Reliable sampling)
- ✅ Node graph background: `#252525`
- ✅ Menu bar background: `#313131`
- ✅ Scene outliner background: `#454545` or darker
- ✅ Parameter label text: `#808080` to `#999999` range

### Medium Confidence (Visual inspection + sampling)
- ⚠️ Main panel background: `#3c3c3c` (between `#2b2b2b` and `#454545`)
- ⚠️ Primary text: `#d0d0d0` (visibly not pure white)
- ⚠️ Borders: `#404040` to `#505050` (very subtle)

### Low Confidence (Requires manual verification)
- ⚠️ Exact hover state opacity
- ⚠️ Exact section header background
- ⚠️ Exact accent color values
- ⚠️ Input field backgrounds

---

## 🔬 NEXT STEPS

### 1. Manual Color Picker Verification
**Action:** Use digital color picker tool (Photoshop, GIMP, etc.) on `octane-reference.png` to verify:
- Main panel backgrounds (sample pure BG areas)
- Primary text color (sample white/light text)
- Section header backgrounds
- Input field backgrounds
- Exact accent colors

**Recommended sampling points:**
- `(15, 250)` - Scene outliner pure BG
- `(60, 112)` - Tree item text
- `(920, 153)` - Parameter label text
- `(300, 850)` - Node graph pure BG
- `(100, 155)` - Selected item background

### 2. Test in Actual OctaneSE
If access to Octane Standalone is available, use developer tools or color picker to sample directly from running application (more accurate than screenshot).

### 3. Iterative Refinement
Apply recommended values to octaneWebR, take new screenshot, compare side-by-side with OctaneSE reference, adjust as needed.

---

## 📸 SAMPLING METADATA

**Source Images:**
- OctaneSE: `references-images/octane-reference.png` (1625x1313px)
- OctaneWebR: `references-images/octaneWebR-reference.png` (1582x1372px)

**Sampling Method:**
- Tool: ImageMagick `convert` command
- Sample size: 1x1 pixel and 5x5 pixel areas
- Color format: Hex RGB (#RRGGBB)

**Limitations:**
- Screenshot compression may alter colors
- Color profiles may not match
- Antialiasing affects text sampling
- Small UI elements hard to sample accurately
- Content overlays can contaminate samples

---

**Status:** Ready for Phase 2 implementation (Color Palette Refinement)  
**Recommended:** Manual verification with color picker tool before applying changes
