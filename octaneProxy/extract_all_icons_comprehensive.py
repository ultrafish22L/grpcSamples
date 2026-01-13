#!/usr/bin/env python3
"""
COMPREHENSIVE ICON EXTRACTOR
Extracts ALL visible icons from Octane SE screenshots:
- Node type icons (with their text labels)
- Toolbar buttons
- Menu icons
- UI controls
- Status bar icons
- Everything!
"""

import sys
from PIL import Image, ImageDraw, ImageFont
from pathlib import Path
import json

# Usage: python3 extract_all_icons_comprehensive.py <screenshot.png>

OUTPUT_BASE = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons'

def extract_icon_grid(img, start_x, start_y, icon_width, icon_height, 
                     spacing_x, spacing_y, num_cols, num_rows, category_name):
    """
    Extract icons arranged in a grid pattern (like the node list)
    """
    icons = []
    
    for row in range(num_rows):
        for col in range(num_cols):
            x = start_x + (col * spacing_x)
            y = start_y + (row * spacing_y)
            
            # Extract icon region
            icon_box = (x, y, x + icon_width, y + icon_height)
            icon = img.crop(icon_box)
            
            # Check if icon is not blank (has some content)
            extrema = icon.convert('L').getextrema()
            if extrema[0] != extrema[1]:  # Not uniform color
                icons.append({
                    'image': icon,
                    'position': (x, y),
                    'category': category_name,
                    'grid_pos': (row, col)
                })
    
    return icons

def extract_toolbar_icons(img, toolbar_y, toolbar_height, icon_size=24):
    """
    Extract icons from horizontal toolbar
    """
    icons = []
    width = img.width
    
    # Scan toolbar area for icon-like regions
    x = 0
    while x < width - icon_size:
        icon_box = (x, toolbar_y, x + icon_size, toolbar_y + toolbar_height)
        icon = img.crop(icon_box)
        
        # Check if this looks like an icon (has enough variation)
        std_dev = icon.convert('L').getextrema()
        if std_dev[1] - std_dev[0] > 30:  # Has contrast
            icons.append({
                'image': icon,
                'position': (x, toolbar_y),
                'category': 'toolbar',
                'type': 'button'
            })
            x += icon_size + 5  # Skip to next likely icon
        else:
            x += 5  # Small increment to scan
    
    return icons

def analyze_screenshot(img_path):
    """
    Analyze screenshot and identify all icon regions
    """
    img = Image.open(img_path)
    print(f"Analyzing screenshot: {img.width}x{img.height}")
    
    all_icons = []
    
    # Based on the reference image structure:
    # 1. Node list on the left (multiple columns with icon + text)
    # 2. Toolbar at the top
    # 3. Right panel with various UI icons
    # 4. Bottom status bar
    
    print("\n📦 Extracting node icons from left panel...")
    # Node icons appear to be ~16x16 with text to the right
    # Starting around x=10, y=15, in a vertical list
    # There appear to be multiple columns
    
    # Column 1
    col1_icons = extract_icon_grid(
        img, 
        start_x=10, start_y=15,
        icon_width=16, icon_height=16,
        spacing_x=0, spacing_y=14,  # Vertical spacing
        num_cols=1, num_rows=60,  # Estimate
        category_name='nodes_col1'
    )
    all_icons.extend(col1_icons)
    print(f"  Found {len(col1_icons)} icons in column 1")
    
    # Column 2 (appears around x=165)
    col2_icons = extract_icon_grid(
        img,
        start_x=165, start_y=15,
        icon_width=16, icon_height=16,
        spacing_x=0, spacing_y=14,
        num_cols=1, num_rows=60,
        category_name='nodes_col2'
    )
    all_icons.extend(col2_icons)
    print(f"  Found {len(col2_icons)} icons in column 2")
    
    # Column 3 (appears around x=300)
    col3_icons = extract_icon_grid(
        img,
        start_x=300, start_y=15,
        icon_width=16, icon_height=16,
        spacing_x=0, spacing_y=14,
        num_cols=1, num_rows=60,
        category_name='nodes_col3'
    )
    all_icons.extend(col3_icons)
    print(f"  Found {len(col3_icons)} icons in column 3")
    
    # Column 4 (appears around x=425)
    col4_icons = extract_icon_grid(
        img,
        start_x=425, start_y=15,
        icon_width=16, icon_height=16,
        spacing_x=0, spacing_y=14,
        num_cols=1, num_rows=60,
        category_name='nodes_col4'
    )
    all_icons.extend(col4_icons)
    print(f"  Found {len(col4_icons)} icons in column 4")
    
    # Column 5 (right side, appears around x=525)
    col5_icons = extract_icon_grid(
        img,
        start_x=525, start_y=15,
        icon_width=16, icon_height=16,
        spacing_x=0, spacing_y=14,
        num_cols=1, num_rows=60,
        category_name='nodes_col5'
    )
    all_icons.extend(col5_icons)
    print(f"  Found {len(col5_icons)} icons in column 5")
    
    # Column 6 (appears around x=655)
    col6_icons = extract_icon_grid(
        img,
        start_x=655, start_y=15,
        icon_width=16, icon_height=16,
        spacing_x=0, spacing_y=14,
        num_cols=1, num_rows=60,
        category_name='nodes_col6'
    )
    all_icons.extend(col6_icons)
    print(f"  Found {len(col6_icons)} icons in column 6")
    
    # Column 7 (appears around x=780)
    col7_icons = extract_icon_grid(
        img,
        start_x=780, start_y=15,
        icon_width=16, icon_height=16,
        spacing_x=0, spacing_y=14,
        num_cols=1, num_rows=60,
        category_name='nodes_col7'
    )
    all_icons.extend(col7_icons)
    print(f"  Found {len(col7_icons)} icons in column 7")
    
    print(f"\n🔧 Extracting toolbar icons...")
    toolbar_icons = extract_toolbar_icons(img, toolbar_y=0, toolbar_height=40)
    all_icons.extend(toolbar_icons)
    print(f"  Found {len(toolbar_icons)} toolbar icons")
    
    print(f"\n📊 TOTAL EXTRACTED: {len(all_icons)} icons")
    
    return all_icons, img

def save_icons(icons, output_base):
    """Save all extracted icons"""
    
    # Create category directories
    categories = set(icon['category'] for icon in icons)
    for cat in categories:
        (output_base / cat).mkdir(parents=True, exist_ok=True)
    
    saved_count = 0
    
    for i, icon_data in enumerate(icons):
        category = icon_data['category']
        image = icon_data['image']
        
        # Save icon
        filename = f"icon_{i:04d}_{category}.png"
        save_path = output_base / category / filename
        
        try:
            image.save(save_path)
            saved_count += 1
        except Exception as e:
            print(f"❌ Failed to save {filename}: {e}")
    
    print(f"\n✅ Saved {saved_count} icons to {output_base}")
    
    # Save metadata
    metadata = []
    for i, icon_data in enumerate(icons):
        metadata.append({
            'id': i,
            'filename': f"icon_{i:04d}_{icon_data['category']}.png",
            'category': icon_data['category'],
            'position': icon_data['position'],
            'type': icon_data.get('type', 'unknown')
        })
    
    metadata_path = output_base / 'extracted_icons_metadata.json'
    with open(metadata_path, 'w') as f:
        json.dump(metadata, f, indent=2)
    
    print(f"✅ Saved metadata to {metadata_path}")

def create_overview_image(icons, original_img, output_path):
    """Create an overview image showing all extracted icons"""
    
    # Create a grid of all icons
    icons_per_row = 20
    icon_size = 32  # Display size
    padding = 4
    
    rows = (len(icons) + icons_per_row - 1) // icons_per_row
    
    overview_width = icons_per_row * (icon_size + padding)
    overview_height = rows * (icon_size + padding)
    
    overview = Image.new('RGB', (overview_width, overview_height), color=(50, 50, 50))
    
    for i, icon_data in enumerate(icons):
        row = i // icons_per_row
        col = i % icons_per_row
        
        x = col * (icon_size + padding) + padding
        y = row * (icon_size + padding) + padding
        
        # Resize icon to display size
        icon_resized = icon_data['image'].resize((icon_size, icon_size), Image.Resampling.NEAREST)
        overview.paste(icon_resized, (x, y))
    
    overview.save(output_path)
    print(f"✅ Saved overview image to {output_path}")

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 extract_all_icons_comprehensive.py <screenshot_file>")
        print("\nExample:")
        print("  python3 extract_all_icons_comprehensive.py octane_reference.png")
        sys.exit(1)
    
    screenshot_path = Path(sys.argv[1])
    
    if not screenshot_path.exists():
        print(f"❌ File not found: {screenshot_path}")
        sys.exit(1)
    
    print("="*70)
    print("🎨 COMPREHENSIVE ICON EXTRACTOR")
    print("="*70)
    print(f"\nInput: {screenshot_path}")
    print(f"Output: {OUTPUT_BASE}/")
    
    # Extract all icons
    icons, original_img = analyze_screenshot(screenshot_path)
    
    if not icons:
        print("\n❌ No icons found!")
        sys.exit(1)
    
    # Save icons
    save_icons(icons, OUTPUT_BASE / 'extracted')
    
    # Create overview
    overview_path = OUTPUT_BASE / 'extracted' / '_overview.png'
    create_overview_image(icons, original_img, overview_path)
    
    print("\n" + "="*70)
    print("✅ EXTRACTION COMPLETE")
    print("="*70)
    print(f"\nExtracted {len(icons)} icons across multiple categories")
    print(f"\nNext steps:")
    print(f"  1. Review: {overview_path}")
    print(f"  2. Match icons to node type names")
    print(f"  3. Rename files with proper NT_* names")

if __name__ == '__main__':
    main()
