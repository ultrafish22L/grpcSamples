# Octane Icons Directory

This directory contains all native Octane icons extracted from the LiveLink API.

## Structure

```
icons/
├── nodes/          # Node type icons (NT_*)
│   ├── NT_MAT_DIFFUSE.png
│   ├── NT_MAT_GLOSSY.png
│   ├── NT_TEX_IMAGE.png
│   └── ... (700+ node icons)
└── graphs/         # Graph type icons (GT_*)
    ├── GT_STANDARD.png
    ├── GT_SWITCH_BOOL.png
    └── ... (100+ graph icons)
```

## How Icons Are Generated

Icons are extracted using the `extract_icons.py` script:

```bash
cd ../../octaneProxy
./extract_icons.sh    # Linux/Mac
# or
extract_icons.bat      # Windows
```

This script:
1. Connects to Octane LiveLink (port 51022)
2. Calls `nodeIconImage()` for each node type (NT_*)
3. Calls `graphIconImage()` for each graph type (GT_*)
4. Saves PNG files with alpha channel

## Usage in React Components

```typescript
import React from 'react';

interface NodeIconProps {
  nodeType: string;  // e.g., "NT_MAT_DIFFUSE"
  size?: number;
}

const NodeIcon: React.FC<NodeIconProps> = ({ nodeType, size = 24 }) => {
  return (
    <img 
      src={`/icons/nodes/${nodeType}.png`}
      alt={nodeType}
      width={size}
      height={size}
      onError={(e) => {
        // Fallback for missing icons
        e.currentTarget.src = '/icons/default-node.png';
      }}
    />
  );
};
```

## Icon Naming Convention

Icons are named exactly after their gRPC enum values:
- **Node Types**: `NT_` prefix (e.g., `NT_MAT_DIFFUSE.png`)
- **Graph Types**: `GT_` prefix (e.g., `GT_STANDARD.png`)

## Re-generating Icons

To update icons after an Octane version update:

1. Ensure Octane is running with LiveLink enabled
2. Run `extract_icons.sh` (or `.bat` on Windows)
3. Commit updated icons to version control

## Why Commit Icons to Git?

Icons are committed to the repository so that:
- ✅ octaneWebR works offline without Octane connection
- ✅ Developers don't need to extract icons individually
- ✅ Icon versions are tracked with code versions
- ✅ CI/CD builds work without Octane dependency

## File Sizes

- **Node icons**: ~2-10 KB each (PNG with alpha)
- **Graph icons**: ~2-10 KB each (PNG with alpha)
- **Total**: ~5-10 MB for all icons

## Related Documentation

- `octaneProxy/README_ICON_EXTRACTION.md` - Detailed extraction guide
- `octaneProxy/extract_icons.py` - Icon extraction script
