# Quick Reference - Icon/Pin Type System

## 🎯 Where to Import From

### For Pin Types (PT_*)
```typescript
import { 
  getPinIconInfo,           // Get icon + color for a PT_ type
  getCompatibleNodeTypes,   // Get NT_ types that can connect
  isNodeTypeCompatible,     // Validate connections
  getIconForType,           // Get icon for ANY type (NT_ or PT_)
  getColorForType           // Get color for ANY type
} from '@/constants/PinTypes';
```

### For Node Types (NT_*)
```typescript
import { 
  OCTANE_NODE_TYPES,        // Full registry with categories
  getNodeIconPath,          // Get icon for NT_ type
  hasIconMapping,           // Check if icon exists
  getCategoriesInOrder,     // Get category list
  getNodeTypesForCategory   // Get NT_ types in category
} from '@/constants/NodeTypes';
```

### For Colors
```typescript
import { 
  formatColorValue,         // Any format → hex
  parseColorValue,          // Hex → RGB object
  formatNodeColor,          // Node color → hex
  lightenColor,             // Lighten a color
  darkenColor,              // Darken a color
  getContrastTextColor      // Get black/white for contrast
} from '@/utils/ColorUtils';
```

## 📋 Common Use Cases

### 1. Display a Pin Icon
```typescript
import { getPinIconInfo } from '@/constants/PinTypes';

const pinInfo = getPinIconInfo('PT_MATERIAL');
// Returns: { icon: '/icons/CATEGORY_MATERIAL node.png', color: '#FF6600' }

<img src={pinInfo.icon} style={{ borderColor: pinInfo.color }} />
```

### 2. Populate Dropdown with Compatible Nodes
```typescript
import { getCompatibleNodeTypes } from '@/constants/PinTypes';

const compatibleNodes = getCompatibleNodeTypes('PT_MATERIAL');
// Returns: ['NT_MAT_DIFFUSE', 'NT_MAT_GLOSSY', 'NT_MAT_UNIVERSAL', ...]

<select>
  {compatibleNodes.map(nodeType => (
    <option key={nodeType} value={nodeType}>{nodeType}</option>
  ))}
</select>
```

### 3. Validate a Connection
```typescript
import { isNodeTypeCompatible } from '@/constants/PinTypes';

// User tries to connect a texture node to a material pin
const valid = isNodeTypeCompatible('NT_TEX_IMAGE', 'PT_MATERIAL');
// Returns: false (can't connect texture to material pin)

const valid2 = isNodeTypeCompatible('NT_MAT_DIFFUSE', 'PT_MATERIAL');
// Returns: true (can connect material node to material pin)
```

### 4. Get Icon for Any Type (Unified)
```typescript
import { getIconForType } from '@/constants/PinTypes';

// Works for pin types
const icon1 = getIconForType('PT_TEXTURE');

// Also works for node types
const icon2 = getIconForType('NT_MAT_DIFFUSE');

// Both return icon paths!
```

### 5. Convert Octane Color to Hex
```typescript
import { formatColorValue } from '@/utils/ColorUtils';

// From array [r, g, b] (0-1 range)
const hex1 = formatColorValue([1, 0, 0]); // '#FF0000'

// From object {x, y, z} (0-1 range)
const hex2 = formatColorValue({x: 0, y: 1, z: 0}); // '#00FF00'

// From packed uint32 (ARGB format)
const hex3 = formatColorValue(0xFFFF0000); // '#FF0000'

// Already hex
const hex4 = formatColorValue('#0000FF'); // '#0000FF'
```

### 6. Node Header Color
```typescript
import { formatNodeColor } from '@/utils/ColorUtils';

const nodeColor = node.color; // Could be undefined, number, or object
const hex = formatNodeColor(nodeColor); // Always returns valid hex, defaults to '#666666'

<div style={{ backgroundColor: hex }}>
  Node Header
</div>
```

## 🔄 Migration from Old Code

### Before (Old Way)
```typescript
import { OctaneIconMapper } from '@/utils/OctaneIconMapper';

const icon = OctaneIconMapper.getNodeIcon('PT_MATERIAL');
const hex = OctaneIconMapper.formatColorValue([1, 0, 0]);
const rgb = OctaneIconMapper.getColorValue('#FF0000');
```

### After (New Way - Recommended)
```typescript
import { getIconForType } from '@/constants/PinTypes';
import { formatColorValue, parseColorValue } from '@/utils/ColorUtils';

const icon = getIconForType('PT_MATERIAL');
const hex = formatColorValue([1, 0, 0]);
const rgb = parseColorValue('#FF0000');
```

**Note:** Old way still works! `OctaneIconMapper` now delegates to these functions.

## 📊 Pin Type Registry

All available pin types in `OCTANE_PIN_TYPES`:

**Value Types:** PT_BOOL, PT_FLOAT, PT_INT, PT_STRING, PT_ENUM  
**Color/Texture:** PT_RGB, PT_TEXTURE, PT_NTYPE  
**Transform/Geometry:** PT_TRANSFORM, PT_GEOMETRY, PT_MESH, PT_PROJECTION, PT_DISPLACEMENT  
**Material/Shading:** PT_MATERIAL, PT_EMISSION, PT_MEDIUM, PT_PHASEFUNCTION, PT_MATERIAL_LAYER, PT_ROUND_EDGES  
**Environment/Lighting:** PT_ENVIRONMENT, PT_LIGHT  
**Render/Camera:** PT_CAMERA, PT_RENDERTARGET, PT_KERNEL, PT_IMAGER, PT_POSTPROCESSING, PT_FILM_SETTINGS  
**AOV/Passes:** PT_RENDER_PASSES, PT_RENDER_LAYER, PT_OUTPUT_AOV_GROUP, PT_OUTPUT_AOV, PT_OUTPUT_AOV_LAYER  
**Special:** PT_OBJECTLAYER, PT_ANIMATION_SETTINGS, PT_LUT, PT_RENDER_JOB, PT_TOON_RAMP, PT_VOLUME_RAMP, ...

## 🎨 Pin Colors

Each pin type has a unique color for visual coding:

| Type | Color | Hex |
|------|-------|-----|
| PT_BOOL | Red | #FF4444 |
| PT_FLOAT | Blue | #4444FF |
| PT_INT | Green | #44FF44 |
| PT_MATERIAL | Orange | #FF6600 |
| PT_TEXTURE | Orange | #FFA500 |
| PT_GEOMETRY | Lime | #32CD32 |
| PT_ENVIRONMENT | Sky Blue | #87CEEB |
| ... | ... | ... |

See `PinTypes.ts` for complete list!

## 📁 File Locations

```
octaneWebR/
└── client/
    └── src/
        ├── constants/
        │   ├── PinTypes.ts       ← Pin types (PT_*) - 558 lines
        │   └── NodeTypes.ts      ← Node types (NT_*) - 1265 lines
        └── utils/
            ├── ColorUtils.ts     ← Color utilities - 246 lines
            └── OctaneIconMapper.ts ← Backward compat - 63 lines
```

## 📚 Documentation

- `REFACTORING_SUMMARY.md` - Complete technical details
- `REFACTORING_COMPLETE.md` - What was accomplished
- `QUICK_REFERENCE.md` - This file!

---

**Quick Start:**  
Import from `PinTypes`, `NodeTypes`, or `ColorUtils` based on what you need.  
Old code using `OctaneIconMapper` still works but is deprecated.
