#!/usr/bin/env python3
"""
Analyze the menu screenshot to find the exact structure.
This will help us determine the correct grid parameters.
"""

from PIL import Image, ImageDraw, ImageFont
from pathlib import Path
import json

SCREENSHOT = Path(__file__).parent / 'octane_allitems1.png'

def analyze_menu_structure(img):
    """
    Analyze the menu screenshot to find text positions and icon positions.
    """
    pixels = img.load()
    width, height = img.size
    
    # Menu background color
    bg_color = (60, 60, 60)
    tolerance = 15
    
    print(f"Image size: {width}x{height}")
    print("\n" + "="*70)
    print("SCANNING FOR MENU ITEMS")
    print("="*70)
    
    # Find rows with content by scanning horizontally
    rows_with_content = []
    
    for y in range(height):
        # Check if this row has any non-background pixels
        non_bg_count = 0
        first_content_x = None
        
        for x in range(width):
            r, g, b, a = pixels[x, y]
            
            if a > 128:
                # Check if not background
                if (abs(r - bg_color[0]) > tolerance or 
                    abs(g - bg_color[1]) > tolerance or 
                    abs(b - bg_color[2]) > tolerance):
                    
                    if (r + g + b) > 50:  # Some brightness
                        non_bg_count += 1
                        if first_content_x is None:
                            first_content_x = x
        
        if non_bg_count > 5:  # Row has meaningful content
            rows_with_content.append({
                'y': y,
                'pixel_count': non_bg_count,
                'first_x': first_content_x
            })
    
    # Group consecutive rows into menu items
    menu_items = []
    current_item = None
    
    for row_data in rows_with_content:
        if current_item is None:
            current_item = {
                'start_y': row_data['y'],
                'end_y': row_data['y'],
                'rows': [row_data]
            }
        elif row_data['y'] - current_item['end_y'] <= 2:
            # Continue current item
            current_item['end_y'] = row_data['y']
            current_item['rows'].append(row_data)
        else:
            # New item starts
            menu_items.append(current_item)
            current_item = {
                'start_y': row_data['y'],
                'end_y': row_data['y'],
                'rows': [row_data]
            }
    
    if current_item:
        menu_items.append(current_item)
    
    # Analyze menu items
    print(f"\nFound {len(menu_items)} menu items")
    print("\nFirst 20 items:")
    print(f"{'#':>4} {'Y Start':>8} {'Y End':>8} {'Height':>7} {'First X':>8}")
    print("-" * 70)
    
    for i, item in enumerate(menu_items[:20]):
        height = item['end_y'] - item['start_y'] + 1
        first_x = min(r['first_x'] for r in item['rows'])
        center_y = (item['start_y'] + item['end_y']) // 2
        
        print(f"{i:4d} {item['start_y']:8d} {item['end_y']:8d} {height:7d} {first_x:8d}")
    
    # Calculate spacing
    if len(menu_items) > 1:
        spacings = []
        for i in range(1, min(20, len(menu_items))):
            spacing = menu_items[i]['start_y'] - menu_items[i-1]['start_y']
            spacings.append(spacing)
        
        avg_spacing = sum(spacings) / len(spacings)
        print(f"\n{'='*70}")
        print(f"VERTICAL SPACING ANALYSIS")
        print(f"{'='*70}")
        print(f"Average row spacing: {avg_spacing:.1f} pixels")
        print(f"Min spacing: {min(spacings)}")
        print(f"Max spacing: {max(spacings)}")
        
        # Recommend ROW_SPACING
        print(f"\n💡 RECOMMENDED PARAMETER:")
        print(f"   ROW_SPACING = {int(avg_spacing)}")
    
    # Analyze horizontal structure (columns)
    print(f"\n{'='*70}")
    print(f"HORIZONTAL STRUCTURE ANALYSIS")
    print(f"{'='*70}")
    
    # Sample a few rows to find column positions
    test_rows = menu_items[:30]
    first_x_values = []
    
    for item in test_rows:
        first_x = min(r['first_x'] for r in item['rows'])
        first_x_values.append(first_x)
    
    # Find unique X positions (cluster similar values)
    unique_x = []
    for x in sorted(set(first_x_values)):
        if not unique_x or x - unique_x[-1] > 20:
            unique_x.append(x)
    
    print(f"Detected {len(unique_x)} column positions:")
    for i, x in enumerate(unique_x):
        print(f"  Column {i}: X = {x}")
    
    if len(unique_x) > 1:
        col_spacing = unique_x[1] - unique_x[0]
        print(f"\n💡 RECOMMENDED PARAMETER:")
        print(f"   COL_SPACING = {col_spacing}")
        print(f"   START_X = {unique_x[0]}")
    
    # Recommend START_Y
    if menu_items:
        first_item_y = menu_items[0]['start_y']
        print(f"   START_Y = {first_item_y}")
    
    # Create visualization
    print(f"\n{'='*70}")
    print(f"CREATING VISUAL GUIDE")
    print(f"{'='*70}")
    
    vis = img.copy()
    draw = ImageDraw.Draw(vis, 'RGBA')
    
    # Draw detected menu items
    for i, item in enumerate(menu_items[:50]):
        center_y = (item['start_y'] + item['end_y']) // 2
        
        # Draw horizontal line
        draw.line([(0, center_y), (width, center_y)], fill=(255, 0, 0, 128), width=1)
        
        # Draw icon position estimate (16x16 box)
        for col_x in unique_x:
            # Assume icon is 16x16, centered vertically on the menu item
            icon_top = center_y - 8
            icon_left = col_x
            
            draw.rectangle(
                [icon_left, icon_top, icon_left + 16, icon_top + 16],
                outline=(0, 255, 0, 255),
                width=2
            )
    
    vis_path = Path(__file__).parent / 'menu_structure_analysis.png'
    vis.save(vis_path)
    print(f"✅ Saved visualization: {vis_path}")
    
    return menu_items, unique_x

def main():
    print("="*70)
    print("📐 MENU STRUCTURE ANALYSIS")
    print("="*70)
    print()
    
    img = Image.open(SCREENSHOT)
    menu_items, column_positions = analyze_menu_structure(img)
    
    print(f"""
{'='*70}
✅ ANALYSIS COMPLETE
{'='*70}

Review the visual guide: menu_structure_analysis.png

The green rectangles show where icons should be extracted.
If they align with actual icons → parameters are correct
If they're offset → adjust START_X, START_Y based on the output above

Next steps:
1. Check menu_structure_analysis.png
2. Update parameters in manual_icon_extraction.py if needed
3. Re-run extraction with corrected parameters
""")

if __name__ == '__main__':
    main()
