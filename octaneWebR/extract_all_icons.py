#!/usr/bin/env python3
"""
Extract ALL icons from Octane SE context menu screenshot
Automatically detects columns, rows, and extracts each icon
"""

from PIL import Image, ImageDraw
from pathlib import Path
import json

INPUT_IMAGE = "octane-add-node-contextmenu.png"
OUTPUT_DIR = Path("client/public/icons/extracted")

def detect_text_rows(img, start_x, start_y, width, height, threshold=50):
    """
    Detect rows of text (which indicate icon rows) by looking for
    horizontal lines with consistent text/icon patterns
    """
    rows = []
    
    # Sample vertical slices to find rows with content
    y = start_y
    last_has_content = False
    current_row_start = None
    
    while y < start_y + height:
        # Check if this row has content (sample a few pixels across)
        has_content = False
        for x in range(start_x, min(start_x + width, img.width), 20):
            if x < img.width and y < img.height:
                pixel = img.getpixel((x, y))
                # Check if pixel is not background (dark gray ~37,37,37)
                if pixel[0] > threshold or pixel[1] > threshold or pixel[2] > threshold:
                    has_content = True
                    break
        
        # Track row transitions
        if has_content and not last_has_content:
            current_row_start = y
        elif not has_content and last_has_content and current_row_start is not None:
            rows.append(current_row_start)
            current_row_start = None
        
        last_has_content = has_content
        y += 1
    
    return rows

def detect_columns(img, start_x, start_y, width, height):
    """
    Detect columns by looking for vertical separations
    """
    columns = []
    
    # Look for columns - they typically start with icons on the left
    x = start_x
    in_column = False
    column_start = None
    
    while x < start_x + width:
        # Check if this vertical line has content
        has_content = False
        for y in range(start_y, min(start_y + height, img.height), 10):
            if x < img.width and y < img.height:
                pixel = img.getpixel((x, y))
                if pixel[0] > 50 or pixel[1] > 50 or pixel[2] > 50:
                    has_content = True
                    break
        
        if has_content and not in_column:
            column_start = x
            in_column = True
        elif not has_content and in_column and column_start is not None:
            # Found end of column - but let's be generous with width
            pass
        
        # Every ~130-140 pixels is typically a new column based on the reference
        if column_start and x - column_start > 120:
            columns.append(column_start)
            in_column = False
            column_start = None
        
        x += 1
    
    return columns

def extract_icon_at(img, x, y, icon_size=16):
    """Extract a single icon at position"""
    # Icon is typically 16x16 or 20x20
    box = (x, y, x + icon_size, y + icon_size)
    try:
        icon = img.crop(box)
        # Check if icon has actual content (not blank)
        extrema = icon.convert('L').getextrema()
        if extrema[1] - extrema[0] > 10:  # Has some contrast
            return icon
    except:
        pass
    return None

def smart_extract_all_icons(img):
    """
    Intelligently extract all icons by analyzing the image structure
    """
    print("🔍 Analyzing image structure...")
    
    # The context menu appears to be on the left side
    # Based on the screenshot, let's analyze different regions
    
    all_icons = []
    
    # Define search area (left panel with node list)
    search_x = 5
    search_y = 5
    search_width = 900  # Covers all visible columns
    search_height = 1400  # Covers all rows
    
    print(f"📊 Scanning area: {search_x},{search_y} to {search_x+search_width},{search_y+search_height}")
    
    # Systematic grid scan - extract icons at regular intervals
    # Based on the reference, icons appear at ~14px vertical spacing
    
    icon_size = 16
    row_height = 14  # Vertical spacing between icons
    col_width = 130  # Horizontal spacing between columns
    
    num_columns = 7  # Visible columns in screenshot
    num_rows = 70    # Approximate rows per column
    
    print(f"🎯 Extracting icons from {num_columns} columns × {num_rows} rows...")
    
    icon_count = 0
    
    for col in range(num_columns):
        col_x = search_x + (col * col_width)
        col_icons = []
        
        for row in range(num_rows):
            row_y = search_y + (row * row_height)
            
            # Try to extract icon at this position
            icon = extract_icon_at(img, col_x, row_y, icon_size)
            
            if icon:
                all_icons.append({
                    'image': icon,
                    'position': (col_x, row_y),
                    'column': col,
                    'row': row,
                    'category': f'nodes_col{col+1}'
                })
                col_icons.append(icon)
                icon_count += 1
        
        print(f"  Column {col+1}: Found {len(col_icons)} icons")
    
    print(f"\n✅ Total extracted: {icon_count} icons")
    
    return all_icons

def save_all_icons(icons, output_dir):
    """Save all extracted icons"""
    
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Create subdirectories
    categories = set(icon['category'] for icon in icons)
    for cat in categories:
        (output_dir / cat).mkdir(exist_ok=True)
    
    print(f"\n💾 Saving icons to {output_dir}...")
    
    saved_count = 0
    metadata = []
    
    for i, icon_data in enumerate(icons):
        category = icon_data['category']
        col = icon_data['column']
        row = icon_data['row']
        
        # Generate filename
        filename = f"icon_{i:04d}_col{col+1}_row{row:02d}.png"
        filepath = output_dir / category / filename
        
        try:
            icon_data['image'].save(filepath)
            saved_count += 1
            
            metadata.append({
                'id': i,
                'filename': f"{category}/{filename}",
                'column': col,
                'row': row,
                'position': icon_data['position']
            })
        except Exception as e:
            print(f"❌ Error saving {filename}: {e}")
    
    # Save metadata
    metadata_file = output_dir / 'metadata.json'
    with open(metadata_file, 'w') as f:
        json.dump(metadata, f, indent=2)
    
    print(f"✅ Saved {saved_count} icons")
    print(f"✅ Saved metadata to {metadata_file}")
    
    return saved_count

def create_overview_grid(icons, output_path, icons_per_row=20):
    """Create overview image showing all extracted icons"""
    
    if not icons:
        print("❌ No icons to create overview")
        return
    
    print(f"\n🎨 Creating overview image...")
    
    icon_display_size = 32
    padding = 2
    
    num_rows = (len(icons) + icons_per_row - 1) // icons_per_row
    
    width = icons_per_row * (icon_display_size + padding) + padding
    height = num_rows * (icon_display_size + padding) + padding
    
    overview = Image.new('RGB', (width, height), color=(30, 30, 30))
    
    for i, icon_data in enumerate(icons):
        row = i // icons_per_row
        col = i % icons_per_row
        
        x = padding + col * (icon_display_size + padding)
        y = padding + row * (icon_display_size + padding)
        
        # Resize icon for display
        icon_resized = icon_data['image'].resize(
            (icon_display_size, icon_display_size),
            Image.Resampling.NEAREST
        )
        overview.paste(icon_resized, (x, y))
    
    overview.save(output_path)
    print(f"✅ Overview saved to {output_path}")

def main():
    print("="*70)
    print("🎨 OCTANE ICON EXTRACTOR - Comprehensive Edition")
    print("="*70)
    
    input_path = Path(INPUT_IMAGE)
    
    if not input_path.exists():
        print(f"❌ Input image not found: {input_path}")
        return
    
    print(f"\n📂 Input: {input_path}")
    print(f"📂 Output: {OUTPUT_DIR}/")
    
    # Load image
    img = Image.open(input_path)
    print(f"\n📏 Image size: {img.width}x{img.height}")
    
    # Extract all icons
    icons = smart_extract_all_icons(img)
    
    if not icons:
        print("\n❌ No icons found!")
        return
    
    # Save icons
    saved = save_all_icons(icons, OUTPUT_DIR)
    
    # Create overview
    overview_path = OUTPUT_DIR / '_overview.png'
    create_overview_grid(icons, overview_path)
    
    # Summary
    print("\n" + "="*70)
    print("✅ EXTRACTION COMPLETE!")
    print("="*70)
    print(f"\nExtracted: {saved} icons")
    print(f"\nOutput directories:")
    for cat in sorted(set(icon['category'] for icon in icons)):
        cat_dir = OUTPUT_DIR / cat
        count = len(list(cat_dir.glob('*.png')))
        print(f"  {cat:15} {count:4} icons")
    
    print(f"\n📊 Review overview: {overview_path}")
    print("\n🎉 All icons extracted successfully!")
    print("\nNext steps:")
    print("  1. Review extracted icons in _overview.png")
    print("  2. Match icons to node type names")
    print("  3. Rename files from icon_XXXX_colX_rowXX.png to NT_*.png")

if __name__ == '__main__':
    main()
