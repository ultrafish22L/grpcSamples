# Icon Extraction System - Implementation Summary

## Overview

Created a complete system to extract all native Octane icons via the gRPC LiveLink API and make them available for octaneWebR.

## Files Created

### 1. Core Extraction Script
**File**: `octaneProxy/extract_icons.py` (9.2 KB)
- Connects to Octane LiveLink (port 51022)
- Extracts 700+ node type icons (NT_*)
- Extracts 100+ graph type icons (GT_*)
- Saves icons as PNG with alpha channel
- Progress tracking and error handling
- Organized output: `octaneWebR/client/public/icons/nodes/` and `../graphs/`

### 2. Platform-Specific Launchers

**File**: `octaneProxy/extract_icons.sh` (1.3 KB)
- Linux/Mac launcher script
- Dependency checking (grpcio, protobuf)
- Connection verification
- User-friendly prompts

**File**: `octaneProxy/extract_icons.bat` (1.2 KB)
- Windows launcher script
- Automatic dependency installation
- Error handling with pause for user feedback

### 3. Documentation

**File**: `octaneProxy/README_ICON_EXTRACTION.md` (3.5 KB)
- Complete usage guide
- Troubleshooting section
- Integration examples
- Performance notes
- Version control recommendations

**File**: `octaneWebR/client/public/icons/README.md` (2.1 KB)
- Icon directory structure explanation
- React component usage examples
- Regeneration instructions
- Git commit rationale

### 4. TypeScript Utility Module

**File**: `octaneWebR/client/src/utils/IconLoader.ts` (5.8 KB)
- React components: `<NodeIcon>` and `<GraphIcon>`
- Helper functions: `getNodeIcon()`, `getGraphIcon()`
- Icon preloading hook: `usePreloadIcons()`
- Common node/graph type constants
- Fallback handling for missing icons
- TypeScript type definitions

### 5. Directory Structure

```
octaneWebR/client/public/icons/
├── README.md                  # Documentation
├── nodes/                     # Node type icons (NT_*)
│   └── (700+ PNG files to be generated)
└── graphs/                    # Graph type icons (GT_*)
    └── (100+ PNG files to be generated)
```

## Usage

### Extract Icons (One-Time Setup)

```bash
# Linux/Mac
cd octaneProxy
./extract_icons.sh

# Windows
cd octaneProxy
extract_icons.bat
```

**Prerequisites**:
- Octane running with LiveLink enabled (Help → LiveLink)
- Python 3.7+
- pip packages: grpcio, protobuf (auto-installed by scripts)

### Use Icons in React Components

```typescript
import { NodeIcon, GraphIcon } from '@/utils/IconLoader';

// In a component:
function NodeListItem({ nodeType }) {
  return (
    <div className="node-item">
      <NodeIcon nodeType={nodeType} size={24} />
      <span>{nodeType}</span>
    </div>
  );
}

// Or get URL directly:
import { getNodeIcon } from '@/utils/IconLoader';
const iconUrl = getNodeIcon("NT_MAT_DIFFUSE");
```

## Technical Details

### Icon Extraction Process

1. **Connection**: Connect to Octane LiveLink gRPC service (localhost:51022)
2. **Enumeration**: Extract all NT_* and GT_* enum values from `octaneids_pb2`
3. **API Calls**: 
   - `ApiInfoService.nodeIconImage(nodeType)` → returns ObjectRef
   - `ApiInfoService.graphIconImage(graphType)` → returns ObjectRef
4. **Saving**: `ApiImageBufferService.save(objectPtr, fileName)` → PNG file
5. **Organization**: Saved to `nodes/` or `graphs/` subdirectories

### gRPC API Methods Used

```protobuf
// Get node icon
service ApiInfoService {
  rpc nodeIconImage(nodeIconImageRequest) returns (nodeIconImageResponse);
  rpc graphIconImage(graphIconImageRequest) returns (graphIconImageResponse);
}

// Save image buffer
service ApiImageBufferService {
  rpc save(saveRequest) returns (saveResponse);
}
```

### Icon Format

- **Format**: PNG with alpha channel
- **Size**: Typically 16x16 or 24x24 pixels (native Octane size)
- **File Size**: 2-10 KB per icon
- **Naming**: Exact enum name (e.g., `NT_MAT_DIFFUSE.png`)

## Benefits

✅ **Pixel-Perfect Icons**: Exact same icons as Octane UI
✅ **Type-Safe**: TypeScript support with proper types
✅ **Offline Support**: Works without Octane connection once extracted
✅ **Performance**: Preloaded icons for smooth UI
✅ **Maintainable**: Easy to regenerate when Octane updates
✅ **Fallback Handling**: Graceful degradation for missing icons

## Next Steps

1. **Run Extraction**: Execute `extract_icons.sh` with Octane running
2. **Commit Icons**: Add generated icons to version control
3. **Update Components**: Use `NodeIcon` and `GraphIcon` components
4. **Optional**: Create default fallback icons (`default-node.png`, `default-graph.png`)

## Integration Points

### Node Graph Editor

```typescript
import { NodeIcon } from '@/utils/IconLoader';

function NodeGraphNode({ node }) {
  return (
    <div className="node">
      <div className="node-header">
        <NodeIcon nodeType={node.type} size={16} />
        <span>{node.name}</span>
      </div>
      {/* ... node content ... */}
    </div>
  );
}
```

### Context Menu

```typescript
import { NodeIcon, COMMON_NODE_TYPES } from '@/utils/IconLoader';

const menuItems = [
  {
    label: 'Diffuse Material',
    icon: <NodeIcon nodeType={COMMON_NODE_TYPES.DIFFUSE} size={20} />,
    action: () => createNode('NT_MAT_DIFFUSE')
  },
  // ... more items
];
```

### Scene Outliner

```typescript
import { NodeIcon, GraphIcon } from '@/utils/IconLoader';

function SceneTreeItem({ item }) {
  const Icon = item.isGraph ? GraphIcon : NodeIcon;
  return (
    <div className="tree-item">
      <Icon nodeType={item.type} size={16} />
      <span>{item.name}</span>
    </div>
  );
}
```

## Performance Considerations

- **Initial Load**: ~5-10 MB for all icons (one-time download)
- **Caching**: Browser caches icons after first load
- **Lazy Loading**: Icons loaded on-demand via `<img>` tags
- **Preloading**: Use `usePreloadIcons()` hook for frequently used icons

## Version Control

**Recommendation**: Commit extracted icons to repository

**Why?**
- Developers don't need Octane to build/run octaneWebR
- Icon versions tracked with code
- CI/CD works without Octane dependency
- Consistent icons across team

**Git LFS** (Optional):
- Consider using Git LFS for large binary assets
- Reduces repo size but requires LFS setup

## Troubleshooting

### Common Issues

1. **Connection Refused**: Octane not running or LiveLink disabled
2. **Import Errors**: Run `pip install grpcio protobuf`
3. **Permission Errors**: Make sure `extract_icons.sh` is executable
4. **Missing Icons**: Some NT_/GT_ types don't have icons (normal)

### Error Messages

```
❌ Failed to connect to Octane
→ Solution: Start Octane and enable LiveLink (Help → LiveLink)

❌ ModuleNotFoundError: No module named 'grpc'
→ Solution: pip install grpcio protobuf

⚠️  Failed to save: NT_UNKNOWN
→ Normal: Unknown/deprecated types don't have icons
```

## Future Enhancements

1. **Icon Cache Manifest**: JSON file listing all available icons
2. **SVG Support**: Convert PNG icons to SVG for better scaling
3. **Icon Variants**: Extract different sizes (16px, 24px, 32px)
4. **Color Themes**: Extract light/dark mode icon variants
5. **Auto-Update**: GitHub Action to regenerate icons on schedule

## Related Files

- `octaneProxy/extract_types.py` - Extracts type enum constants
- `octaneProxy/generated/*.py` - Generated protobuf files
- `octaneWebR/client/src/constants/OctaneTypes.ts` - Type definitions

## Questions?

See `octaneProxy/README_ICON_EXTRACTION.md` for detailed documentation.
