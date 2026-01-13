#!/usr/bin/env python3
"""
Extract ALL icons from screenshot and name them using NT_* enum IDs
"""

import sys
sys.path.insert(0, '../octaneProxy/generated')

from PIL import Image
from pathlib import Path
import json
import octaneids_pb2

INPUT_IMAGE = "octane-add-node-contextmenu.png"
OUTPUT_DIR = Path("client/public/icons/nodes")

# Get all node types from enum
def get_all_node_types():
    """Extract all NT_* node type constants"""
    node_types = {}
    for attr in dir(octaneids_pb2):
        if attr.startswith('NT_'):
            value = getattr(octaneids_pb2, attr)
            if isinstance(value, int) and value > 0:
                node_types[attr] = value
    return node_types

def extract_icon_at(img, x, y, icon_size=16):
    """Extract a single icon at position"""
    box = (x, y, x + icon_size, y + icon_size)
    try:
        icon = img.crop(box)
        # Check if icon has actual content
        extrema = icon.convert('L').getextrema()
        if extrema[1] - extrema[0] > 10:  # Has contrast
            return icon
    except:
        pass
    return None

def extract_all_icons_grid(img):
    """
    Extract icons from grid layout
    Returns list of {image, position, col, row}
    """
    print("🔍 Extracting icons from grid...")
    
    icons = []
    
    # Grid parameters (based on the screenshot analysis)
    icon_size = 16
    start_x = 10
    start_y = 15
    row_height = 14
    col_width = 130
    
    num_columns = 7
    num_rows_per_column = 70
    
    for col in range(num_columns):
        col_x = start_x + (col * col_width)
        col_count = 0
        
        for row in range(num_rows_per_column):
            row_y = start_y + (row * row_height)
            
            icon = extract_icon_at(img, col_x, row_y, icon_size)
            
            if icon:
                icons.append({
                    'image': icon,
                    'position': (col_x, row_y),
                    'column': col,
                    'row': row,
                    'index': len(icons)
                })
                col_count += 1
        
        print(f"  Column {col+1}: Found {col_count} icons")
    
    print(f"\n✅ Extracted {len(icons)} total icons")
    return icons

def save_icons_with_enum_names(icons, node_types, output_dir):
    """
    Save icons using NT_* enum names
    If we have more icons than enum names, save extras as numbered
    """
    output_dir.mkdir(parents=True, exist_ok=True)
    
    print(f"\n💾 Saving icons to {output_dir}/...")
    print(f"📊 Have {len(icons)} icons and {len(node_types)} NT_* enum names")
    
    # Sort node types by value to get consistent ordering
    sorted_types = sorted(node_types.items(), key=lambda x: x[1])
    
    saved_count = 0
    named_count = 0
    metadata = []
    
    for i, icon_data in enumerate(icons):
        icon_img = icon_data['image']
        col = icon_data['column']
        row = icon_data['row']
        pos = icon_data['position']
        
        # Try to match with a node type enum
        if i < len(sorted_types):
            node_name, node_id = sorted_types[i]
            filename = f"{node_name}.png"
            named_count += 1
        else:
            # Extra icons beyond enum list
            filename = f"EXTRA_{i:04d}_col{col+1}_row{row:02d}.png"
        
        filepath = output_dir / filename
        
        try:
            icon_img.save(filepath)
            saved_count += 1
            
            metadata.append({
                'filename': filename,
                'node_name': node_name if i < len(sorted_types) else None,
                'node_id': node_id if i < len(sorted_types) else None,
                'column': col,
                'row': row,
                'position': pos,
                'index': i
            })
            
            if i < 20 or (i < len(sorted_types) and i >= len(sorted_types) - 10):
                # Show first 20 and last 10 node names
                if i < len(sorted_types):
                    print(f"  [{i:3}] {node_name:45} → {filename}")
                
        except Exception as e:
            print(f"❌ Error saving {filename}: {e}")
    
    # Save metadata
    metadata_file = output_dir / 'extraction_metadata.json'
    with open(metadata_file, 'w') as f:
        json.dump(metadata, f, indent=2)
    
    print(f"\n✅ Saved {saved_count} icons ({named_count} with NT_* names)")
    print(f"✅ Metadata saved to {metadata_file}")
    
    return saved_count, named_count

def create_overview(icons, output_path, icons_per_row=30):
    """Create visual overview of all extracted icons"""
    print(f"\n🎨 Creating overview image...")
    
    icon_size = 24
    padding = 2
    
    num_rows = (len(icons) + icons_per_row - 1) // icons_per_row
    
    width = icons_per_row * (icon_size + padding) + padding
    height = num_rows * (icon_size + padding) + padding
    
    overview = Image.new('RGB', (width, height), color=(30, 30, 30))
    
    for i, icon_data in enumerate(icons):
        row = i // icons_per_row
        col = i % icons_per_row
        
        x = padding + col * (icon_size + padding)
        y = padding + row * (icon_size + padding)
        
        icon_resized = icon_data['image'].resize(
            (icon_size, icon_size),
            Image.Resampling.NEAREST
        )
        overview.paste(icon_resized, (x, y))
    
    overview.save(output_path)
    print(f"✅ Overview saved: {output_path}")

def main():
    print("="*70)
    print("🎨 OCTANE ICON EXTRACTOR - With NT_* Enum Names")
    print("="*70)
    
    # Load node types
    print("\n📋 Loading node type enums...")
    node_types = get_all_node_types()
    print(f"✅ Found {len(node_types)} NT_* node types in octaneids_pb2")
    
    # Check input
    input_path = Path(INPUT_IMAGE)
    if not input_path.exists():
        print(f"\n❌ Input image not found: {input_path}")
        return
    
    print(f"\n📂 Input: {input_path}")
    print(f"📂 Output: {OUTPUT_DIR}/")
    
    # Load and analyze image
    img = Image.open(input_path)
    print(f"\n📏 Image: {img.width}x{img.height} ({img.mode})")
    
    # Extract all icons
    icons = extract_all_icons_grid(img)
    
    if not icons:
        print("\n❌ No icons extracted!")
        return
    
    # Save with enum names
    saved, named = save_icons_with_enum_names(icons, node_types, OUTPUT_DIR)
    
    # Create overview
    overview_path = OUTPUT_DIR / '_all_icons_overview.png'
    create_overview(icons, overview_path)
    
    # Summary
    print("\n" + "="*70)
    print("✅ EXTRACTION COMPLETE!")
    print("="*70)
    print(f"\n📊 Statistics:")
    print(f"   Total extracted: {saved} icons")
    print(f"   Named with NT_*: {named} icons")
    print(f"   Extra (unnamed): {saved - named} icons")
    print(f"\n📁 Output directory: {OUTPUT_DIR}/")
    print(f"📊 Overview image: {overview_path}")
    print(f"\n🎉 Icons ready for use in octaneWebR!")

if __name__ == '__main__':
    main()
