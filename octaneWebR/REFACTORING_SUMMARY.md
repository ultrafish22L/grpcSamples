# Icon/Pin Type Mapping Refactoring Summary

## Overview
Cleaned up and reorganized icon/pin type mappings in octaneWebR to have clear separation of concerns.

## File Organization

### 1. **PinTypes.ts** - Pin Type Definitions (NEW CENTRAL MODULE)
**Location:** `client/src/constants/PinTypes.ts`

**Purpose:** Central source of truth for all PT_ (Pin Type) definitions

**Exports:**
- `pinIconMapping` - Maps PT_ types to {icon, color}
- `OCTANE_PIN_TYPES` - Complete PT_ type registry with names/colors/icons
- `pinTypeToNodeTypes` - PT_ to compatible NT_ types mapping (for dropdowns)
- `getPinIconInfo(pinType)` - Get icon + color for a PT_ type
- `getCompatibleNodeTypes(pinType)` - Get NT_ types that can connect to this PT_
- `isNodeTypeCompatible(nodeType, pinType)` - Check if connection is valid
- `getAllPinTypes()` - Get all PT_ type keys
- `getPinTypeInfo(pinType)` - Get full info for a PT_ type
- `getIconForType(type, name?)` - **UNIFIED LOOKUP** for both NT_ and PT_ types
- `getColorForType(type)` - Get color for NT_ or PT_ type

**Key Features:**
- ~50 PT_ types fully defined with icons and colors
- Compatibility mapping for node attachment dropdowns
- Handles both NT_ and PT_ type lookups in one place

### 2. **ColorUtils.ts** - Color Conversion Utilities
**Location:** `client/src/utils/ColorUtils.ts`

**Purpose:** All color format conversion functions

**Exports:**
- `formatColorValue(value)` - Convert any color format to hex
- `parseColorValue(hexColor)` - Convert hex to RGB object {x,y,z}
- `formatNodeColor(nodeColor)` - Format node colors specifically
- `hexToRGB(hex)` - Hex string to RGB object
- `rgbToRGBA(color, alpha)` - RGB to CSS rgba string
- `lightenColor(hexColor, percent)` - Lighten a color
- `darkenColor(hexColor, percent)` - Darken a color
- `getContrastTextColor(hexColor)` - Get black/white for contrast
- `interpolateColors(color1, color2, t)` - Interpolate between colors

**Key Features:**
- Handles Octane's ARGB packed uint32 format (0xAARRGGBB)
- Supports RGB objects, arrays, hex strings, and numbers
- Utility functions for UI color manipulation

### 3. **NodeTypes.ts** - Node Type Definitions (EXISTING)
**Location:** `client/src/constants/NodeTypes.ts`

**Purpose:** NT_ (Node Type) definitions and icon mappings

**Key Exports:**
- `OCTANE_NODE_TYPES` - All ~755 NT_ types organized by 26 categories
- `NODE_TYPE_ICON_MAP` - NT_ type to icon filename mappings
- `getNodeIconPath(nodeType)` - Get icon path for NT_ type
- `hasIconMapping(nodeType)` - Check if NT_ has icon
- `getCategoriesInOrder()` - Get category list
- `getNodeTypesForCategory(category)` - Get NT_ types in a category

### 4. **OctaneIconMapper.ts** - Backward Compatibility Layer (DEPRECATED)
**Location:** `client/src/utils/OctaneIconMapper.ts`

**Status:** Now a thin wrapper that delegates to proper modules

**Purpose:** Maintain backward compatibility for existing code

**Delegates to:**
- `PinTypes.getIconForType()` for icon lookups
- `ColorUtils.formatColorValue()` for color conversion
- `ColorUtils.parseColorValue()` for color parsing
- `ColorUtils.formatNodeColor()` for node color formatting

**Migration Path:**
- Old code can continue using `OctaneIconMapper`
- New code should import from `PinTypes`, `NodeTypes`, or `ColorUtils` directly
- All methods marked with `@deprecated` JSDoc annotations

## Usage Examples

### Getting an Icon (Old Way - Still Works)
```typescript
import { OctaneIconMapper } from '@/utils/OctaneIconMapper';
const icon = OctaneIconMapper.getNodeIcon('PT_MATERIAL'); // Works
const icon2 = OctaneIconMapper.getNodeIcon('NT_MAT_DIFFUSE'); // Works
```

### Getting an Icon (New Way - Recommended)
```typescript
import { getIconForType } from '@/constants/PinTypes';
const icon = getIconForType('PT_MATERIAL'); // Pin type
const icon2 = getIconForType('NT_MAT_DIFFUSE'); // Node type
```

### Getting Pin Colors
```typescript
import { getColorForType, getPinIconInfo } from '@/constants/PinTypes';

const color = getColorForType('PT_MATERIAL'); // '#FF6600'
const pinInfo = getPinIconInfo('PT_TEXTURE'); // {icon: '...', color: '#FFA500'}
```

### Getting Compatible Node Types for Dropdown
```typescript
import { getCompatibleNodeTypes, isNodeTypeCompatible } from '@/constants/PinTypes';

// Get all NT_ types that can connect to a PT_MATERIAL pin
const compatibleTypes = getCompatibleNodeTypes('PT_MATERIAL');
// Returns: ['NT_MAT_DIFFUSE', 'NT_MAT_GLOSSY', 'NT_MAT_UNIVERSAL', ...]

// Check if a specific connection is valid
const canConnect = isNodeTypeCompatible('NT_MAT_DIFFUSE', 'PT_MATERIAL'); // true
```

### Color Conversions
```typescript
import { formatColorValue, parseColorValue, formatNodeColor } from '@/utils/ColorUtils';

// Convert Octane color to hex
const hex = formatColorValue([1, 0, 0]); // '#FF0000'
const hex2 = formatColorValue({x: 0, y: 1, z: 0}); // '#00FF00'
const hex3 = formatColorValue(0xFFFF0000); // '#FF0000' (from packed uint32)

// Convert hex to Octane RGB
const rgb = parseColorValue('#FF0000'); // {x: 1, y: 0, z: 0}

// Format node header color
const nodeColor = formatNodeColor(someNodeColorValue); // Handles undefined gracefully
```

## Migration Status

### ✅ Completed
1. Created comprehensive `PinTypes.ts` with all PT_ types
2. Implemented `pinIconMapping` with icons and colors
3. Created `OCTANE_PIN_TYPES` registry (no categories, unlike OCTANE_NODE_TYPES)
4. Built PT_ to NT_ compatibility mapping for dropdowns
5. Moved all color utilities to `ColorUtils.ts`
6. Simplified `OctaneIconMapper.ts` to delegation-only
7. Added unified `getIconForType()` function for both NT_ and PT_

### 📝 Remaining Work
- Update components to import from new modules directly (gradual migration)
- Use compatibility mapping in node inspector dropdowns
- Test pin connection validation with `isNodeTypeCompatible()`
- Eventually remove `OctaneIconMapper.ts` once all references migrated

## Benefits

1. **Clear Separation of Concerns**
   - Pin types in one place
   - Node types in one place  
   - Color utilities in one place

2. **Type Safety**
   - All functions properly typed
   - Compile-time checking for pin/node types

3. **Maintainability**
   - Single source of truth for each concept
   - Easy to add new PT_ or NT_ types
   - Clear documentation with JSDoc

4. **Functionality**
   - Pin connection compatibility checking
   - Dropdown population for node attachment
   - Unified icon/color lookup API

## File Sizes
- PinTypes.ts: ~560 lines (comprehensive PT_ definitions)
- ColorUtils.ts: ~247 lines (complete color toolkit)
- OctaneIconMapper.ts: ~64 lines (thin wrapper)
- NodeTypes.ts: ~1265 lines (all NT_ types, unchanged)
