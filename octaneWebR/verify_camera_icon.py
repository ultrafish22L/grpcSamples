#!/usr/bin/env python3
"""
Verify specific icon alignment by checking NT_CAM_THINLENS.
This will help us confirm if the grid alignment is correct.
"""

from PIL import Image
from pathlib import Path
import json
import shutil

# Load the node display names mapping we created earlier
MAPPING_FILE = Path(__file__).parent / 'client/public/icons/nodes/node-display-names.json'
EXTRACTED_DIR = Path(__file__).parent / 'extracted_icons_v2'
TEST_OUTPUT = Path(__file__).parent / 'test_cam_thinlens.png'

def load_node_display_names():
    """Load the node display names mapping"""
    with open(MAPPING_FILE, 'r') as f:
        return json.load(f)

def get_sorted_node_names(mapping):
    """
    Get node display names sorted alphabetically, like Octane's "All items" menu.
    Returns list of (NT_NAME, display_name) tuples in menu order.
    """
    # Create list of (display_name, NT_NAME) for sorting
    items = []
    for nt_name, info in mapping.items():
        display_name = info['displayName']
        items.append((display_name, nt_name))
    
    # Sort by display name (case-insensitive, like Octane does)
    items.sort(key=lambda x: x[0].lower())
    
    # Return as (NT_NAME, display_name)
    return [(nt_name, display_name) for display_name, nt_name in items]

def find_icon_index(node_name, sorted_nodes):
    """Find the index of a node in the sorted list"""
    for i, (nt_name, display_name) in enumerate(sorted_nodes):
        if nt_name == node_name:
            return i, display_name
    return None, None

def main():
    print("="*70)
    print("🔍 VERIFYING CAMERA ICON ALIGNMENT")
    print("="*70)
    
    # Load mapping
    print("\n📚 Loading node display names...")
    mapping = load_node_display_names()
    print(f"   ✅ Loaded {len(mapping)} node types")
    
    # Get sorted list (menu order)
    print("\n🔤 Sorting alphabetically (Octane menu order)...")
    sorted_nodes = get_sorted_node_names(mapping)
    print(f"   ✅ {len(sorted_nodes)} nodes sorted")
    
    # Find NT_CAM_THINLENS
    target_node = 'NT_CAM_THINLENS'
    print(f"\n🎯 Locating {target_node}...")
    index, display_name = find_icon_index(target_node, sorted_nodes)
    
    if index is None:
        print(f"   ❌ {target_node} not found in mapping!")
        return
    
    print(f"   ✅ Found: '{display_name}' at index {index}")
    
    # The first screenshot has ~270 icons, second has the rest
    if index < 270:
        source_file = EXTRACTED_DIR / f"img1_{index:04d}.png"
        screenshot_num = 1
    else:
        source_file = EXTRACTED_DIR / f"img2_{index - 270:04d}.png"
        screenshot_num = 2
    
    print(f"\n📸 Should be in screenshot {screenshot_num}")
    print(f"   Source: {source_file.name}")
    
    # Check if file exists
    if not source_file.exists():
        print(f"   ❌ File not found: {source_file}")
        
        # List what we have
        print(f"\n   Available files in {EXTRACTED_DIR}:")
        files = sorted(EXTRACTED_DIR.glob("*.png"))
        print(f"   Total: {len(files)} files")
        if files:
            print(f"   First: {files[0].name}")
            print(f"   Last: {files[-1].name}")
        
        # Try to find the closest index
        if index >= 270:
            # Try img1 files instead (maybe they're all in img1?)
            alt_source = EXTRACTED_DIR / f"img1_{index:04d}.png"
            if alt_source.exists():
                print(f"\n   ✅ Found in img1: {alt_source.name}")
                source_file = alt_source
            else:
                return
        else:
            return
    
    # Copy to test output for inspection
    print(f"\n💾 Copying to test output...")
    shutil.copy(source_file, TEST_OUTPUT)
    print(f"   ✅ Saved: {TEST_OUTPUT}")
    
    # Also create an enlarged version for easier inspection
    icon = Image.open(source_file)
    large = icon.resize((128, 128), Image.NEAREST)
    large_path = Path(__file__).parent / 'test_cam_thinlens_large.png'
    large.save(large_path)
    print(f"   ✅ Large version: {large_path}")
    
    # Print some context
    print(f"\n📋 CONTEXT:")
    print(f"   Node type: {target_node}")
    print(f"   Display name: '{display_name}'")
    print(f"   Menu position: {index + 1} of {len(sorted_nodes)}")
    print(f"   Screenshot: {screenshot_num}")
    
    # Show neighbors for context
    print(f"\n   Neighbors in menu:")
    for offset in [-2, -1, 0, 1, 2]:
        i = index + offset
        if 0 <= i < len(sorted_nodes):
            nt, dn = sorted_nodes[i]
            marker = " ← THIS" if offset == 0 else ""
            print(f"      {i:3d}. {dn:30s} ({nt}){marker}")
    
    print(f"""
{'='*70}
✅ VERIFICATION COMPLETE
{'='*70}

Please check these files:
1. {TEST_OUTPUT} (actual size)
2. {large_path} (enlarged 8x)

The icon should show a camera symbol, properly centered.

If it looks good:
  → The grid alignment is correct
  → Proceed with full mapping

If it's still misaligned:
  → Adjust parameters in manual_icon_extraction.py
  → Specifically: START_X, START_Y, ROW_SPACING, COL_SPACING
""")

if __name__ == '__main__':
    main()
