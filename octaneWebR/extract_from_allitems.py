#!/usr/bin/env python3
"""
Extract ALL node type icons from the "All items" submenu screenshot
"""

import sys
sys.path.insert(0, '../octaneProxy/generated')

from PIL import Image, ImageDraw
from pathlib import Path
import json
import octaneids_pb2

INPUT_IMAGE = "octaneSE_nodegraphcontext_allitems.png"
OUTPUT_DIR = Path("client/public/icons/nodes")

def get_node_types_sorted():
    """Get all NT_* node types sorted ALPHABETICALLY (matches 'All items' menu order)"""
    node_types = []
    for attr in dir(octaneids_pb2):
        if attr.startswith('NT_'):
            value = getattr(octaneids_pb2, attr)
            if isinstance(value, int) and value > 0:
                node_types.append((attr, value))
    node_types.sort(key=lambda x: x[0])  # Sort alphabetically, not by ID!
    return node_types

def detect_grid_params(img):
    """Detect column positions and row centers"""
    print("🔍 Detecting grid parameters...")
    
    # Find content start
    content_start_y = 9
    
    # Detect columns
    print("\nDetecting columns...")
    columns = []
    last_column_x = -100
    
    for x in range(5, img.width - 20, 1):
        content_count = 0
        for y in range(content_start_y, min(content_start_y + 300, img.height)):
            px = img.getpixel((x, y))
            if px[0] > 80 or px[1] > 80 or px[2] > 80:
                content_count += 1
        
        if content_count > 50 and (x - last_column_x) > 80:
            columns.append(x)
            last_column_x = x
    
    print(f"  Found {len(columns)} columns: {columns}")
    
    # Detect rows from first column
    print("\nDetecting rows...")
    first_col_x = columns[0]
    rows_with_content = []
    
    for y in range(content_start_y, img.height - 10):
        bright_count = 0
        for x in range(first_col_x, first_col_x + 20):
            try:
                px = img.getpixel((x, y))
                if px[0] > 80 or px[1] > 80 or px[2] > 80:
                    bright_count += 1
            except:
                pass
        
        if bright_count > 3:
            rows_with_content.append(y)
    
    # Group into menu items
    menu_items = []
    if rows_with_content:
        current_start = rows_with_content[0]
        current_end = rows_with_content[0]
        
        for y in rows_with_content[1:]:
            if y <= current_end + 3:
                current_end = y
            else:
                center = (current_start + current_end) // 2
                menu_items.append(center)
                current_start = y
                current_end = y
        
        center = (current_start + current_end) // 2
        menu_items.append(center)
    
    print(f"  Found {len(menu_items)} rows")
    
    # Skip first row - it's offset, actual icons start at row 2
    if menu_items:
        menu_items = menu_items[1:]
        print(f"  Skipping first row, using {len(menu_items)} icon rows")
    
    return columns, menu_items

def extract_all_icons(img, columns, rows):
    """Extract icons from all grid positions"""
    print(f"\n📦 Extracting icons from {len(columns)}x{len(rows)} grid...")
    
    icons = []
    icon_size = 16
    icon_x_offset = -1  # Icon is slightly LEFT of column start (was 7, corrected to -1)
    
    for col_idx, col_x in enumerate(columns):
        col_icons = 0
        for row_idx, row_y in enumerate(rows):
            # Icon position
            x = col_x + icon_x_offset
            y = row_y - 8  # Center the 16px icon on the row
            
            try:
                icon = img.crop((x, y, x + icon_size, y + icon_size))
                
                # Check if icon has content
                pixels = list(icon.getdata())
                bright = sum(1 for px in pixels if len(px) >= 3 and (px[0] > 50 or px[1] > 50 or px[2] > 50))
                
                if bright >= 8:  # Has enough content to be a real icon
                    icons.append({
                        'image': icon,
                        'column': col_idx,
                        'row': row_idx,
                        'position': (x, y),
                        'index': len(icons)
                    })
                    col_icons += 1
            except Exception as e:
                pass
        
        print(f"  Column {col_idx+1}: {col_icons} icons")
    
    print(f"\n✅ Extracted {len(icons)} total icons")
    return icons

def save_icons_with_names(icons, node_types, output_dir):
    """Save icons with NT_* enum names"""
    output_dir.mkdir(parents=True, exist_ok=True)
    
    print(f"\n💾 Saving to {output_dir}/")
    print(f"📊 {len(icons)} icons → {len(node_types)} NT_* types\n")
    
    saved = []
    metadata = []
    
    for i, icon_data in enumerate(icons):
        icon_img = icon_data['image']
        col = icon_data['column']
        row = icon_data['row']
        pos = icon_data['position']
        
        # Match with node type
        if i < len(node_types):
            node_name, node_id = node_types[i]
            filename = f"{node_name}.png"
        else:
            filename = f"EXTRA_{i:04d}_c{col}_r{row}.png"
            node_name = None
            node_id = None
        
        filepath = output_dir / filename
        
        try:
            icon_img.save(filepath)
            saved.append(filename)
            
            metadata.append({
                'index': i,
                'filename': filename,
                'node_name': node_name,
                'node_id': node_id,
                'column': col,
                'row': row,
                'position': pos
            })
            
            # Show progress
            if i < 20:
                print(f"  [{i:3}] {node_name or 'UNKNOWN':45} → {filename}")
            elif i == 20:
                print(f"  ... ({len(icons) - 30} more) ...")
            elif i >= len(icons) - 10:
                print(f"  [{i:3}] {node_name or 'UNKNOWN':45} → {filename}")
                
        except Exception as e:
            print(f"❌ Error saving {filename}: {e}")
    
    # Save metadata
    metadata_file = output_dir / 'metadata.json'
    with open(metadata_file, 'w') as f:
        json.dump(metadata, f, indent=2)
    
    print(f"\n✅ Saved {len(saved)} icons")
    print(f"✅ Metadata: {metadata_file}")
    
    return len(saved)

def create_overview(icons, output_path):
    """Create overview visualization"""
    if not icons:
        return
    
    print(f"\n🎨 Creating overview...")
    
    icon_size = 18
    padding = 1
    icons_per_row = 50
    
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
    print(f"✅ Overview: {output_path}")

def main():
    print("="*70)
    print("🎨 EXTRACT ALL NODE ICONS FROM 'ALL ITEMS' MENU")
    print("="*70)
    
    # Load node types
    print("\n📋 Loading NT_* node types...")
    node_types = get_node_types_sorted()
    print(f"✅ {len(node_types)} node types from octaneids_pb2")
    
    # Load image
    input_path = Path(INPUT_IMAGE)
    if not input_path.exists():
        print(f"❌ Image not found: {input_path}")
        return 1
    
    print(f"\n📂 Input: {input_path}")
    img = Image.open(input_path)
    print(f"📏 Size: {img.width}x{img.height}")
    
    # Detect grid
    columns, rows = detect_grid_params(img)
    
    if not columns or not rows:
        print("\n❌ Could not detect grid!")
        return 1
    
    # Extract
    icons = extract_all_icons(img, columns, rows)
    
    if not icons:
        print("\n❌ No icons extracted!")
        return 1
    
    # Save
    count = save_icons_with_names(icons, node_types, OUTPUT_DIR)
    
    # Overview
    overview_path = OUTPUT_DIR / '_overview.png'
    create_overview(icons, overview_path)
    
    # Summary
    print("\n" + "="*70)
    print("✅ EXTRACTION COMPLETE!")
    print("="*70)
    print(f"\n📊 Extracted: {count} node icons")
    print(f"📁 Location: {OUTPUT_DIR}/")
    print(f"🎨 Overview: {overview_path}")
    print(f"\n🎉 Ready to use in octaneWebR!")
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
