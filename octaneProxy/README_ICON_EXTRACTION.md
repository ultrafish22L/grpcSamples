# Octane Icon Extraction Tool

## ⚠️ IMPORTANT: Use Fixed Version

**OLD SCRIPT ISSUE:** `extract_icons.py` crashes Octane on first icon call due to API type mismatch.

**✅ USE THIS INSTEAD:** `extract_icons_fixed.py` - Fixed version with hybrid approach that works reliably.

## Quick Start (Fixed Version)

```bash
cd /workspace/project/grpcSamples/octaneProxy

# Step 1: Run diagnostic test (recommended first)
python3 test_icon_extraction_methods.py

# Step 2: Extract all icons
python3 extract_icons_fixed.py
```

See [ICON_EXTRACTION_FIX.md](ICON_EXTRACTION_FIX.md) for detailed explanation of the fix.

## Overview

Icon extraction extracts all native Octane icons via the gRPC LiveLink API and saves them for use in octaneWebR.

## Prerequisites

1. **Octane running** with LiveLink enabled (Help → LiveLink in menu)
2. **Python dependencies** installed:
   ```bash
   pip install grpcio protobuf
   ```
3. **Generated protobuf files** in `octaneProxy/generated/`

## Usage

```bash
cd /workspace/project/grpcSamples/octaneProxy
python3 extract_icons.py
```

## Output Structure

Icons are saved to:
```
octaneWebR/client/public/icons/
├── nodes/          # Node type icons (NT_*)
│   ├── NT_MAT_DIFFUSE.png
│   ├── NT_MAT_GLOSSY.png
│   ├── NT_TEX_IMAGE.png
│   └── ... (700+ icons)
└── graphs/         # Graph type icons (GT_*)
    ├── GT_STANDARD.png
    ├── GT_SWITCH_BOOL.png
    └── ... (100+ icons)
```

## Icon Naming Convention

Icons are named exactly after their type enum:
- **Node Types**: `NT_*` (e.g., `NT_MAT_DIFFUSE.png`)
- **Graph Types**: `GT_*` (e.g., `GT_STANDARD.png`)

This allows octaneWebR to dynamically load icons by constructing paths like:
```javascript
const iconPath = `/icons/nodes/${nodeType}.png`;
```

## Integration with octaneWebR

### React Component Example

```typescript
interface NodeIconProps {
  nodeType: string; // e.g., "NT_MAT_DIFFUSE"
  size?: number;
}

const NodeIcon: React.FC<NodeIconProps> = ({ nodeType, size = 24 }) => {
  const iconPath = `/icons/nodes/${nodeType}.png`;
  
  return (
    <img 
      src={iconPath} 
      alt={nodeType}
      width={size}
      height={size}
      onError={(e) => {
        // Fallback to default icon if specific icon not found
        e.currentTarget.src = '/icons/default-node.png';
      }}
    />
  );
};
```

### TypeScript Type Definitions

```typescript
// client/src/types/OctaneTypes.ts
export type NodeType = 
  | 'NT_MAT_DIFFUSE'
  | 'NT_MAT_GLOSSY'
  | 'NT_TEX_IMAGE'
  // ... add all node types

export type GraphType =
  | 'GT_STANDARD'
  | 'GT_SWITCH_BOOL'
  // ... add all graph types
```

## Features

- ✅ Extracts 700+ node type icons
- ✅ Extracts 100+ graph type icons  
- ✅ Automatic connection to Octane LiveLink (localhost:51022)
- ✅ Progress tracking during extraction
- ✅ Error handling with retry logic
- ✅ Organized output structure (nodes/ and graphs/ subdirectories)
- ✅ PNG format with alpha channel preservation

## Troubleshooting

### Connection Errors

**Problem**: `Failed to connect to Octane`

**Solutions**:
1. Check Octane is running
2. Enable LiveLink: Help → LiveLink in Octane menu
3. Verify port 51022 is not blocked by firewall
4. Try restarting Octane

### Missing Icons

**Problem**: Some icons show as "skipped"

**Explanation**: Not all node/graph types have associated icons in Octane. This is normal behavior.

### gRPC Timeout Errors

**Problem**: `grpc.StatusCode.DEADLINE_EXCEEDED`

**Solution**: 
- Network congestion or slow Octane response
- Script already has 10-second timeout per icon
- Icons that succeed are saved even if others timeout

## Performance

- **Typical extraction time**: 2-5 minutes for all icons
- **Progress updates**: Every 50 node icons, every 10 graph icons
- **Network overhead**: ~1-2 MB total for all icons

## Re-running Extraction

Running the script again will **overwrite** existing icons. This is useful when:
- Octane is updated with new icon designs
- Icons were corrupted or incomplete
- New node/graph types are added to Octane

## Version Control

The extracted icons should be **committed to the repository** so that:
- octaneWebR works offline without requiring Octane connection
- Icon extraction doesn't need to be repeated by every developer
- Icon assets are version-controlled with the app

## Related Files

- `extract_types.py` - Extracts type enums to JavaScript constants
- `octaneProxy/generated/` - Generated protobuf files
- `octaneWebR/client/public/icons/` - Output directory for icons
