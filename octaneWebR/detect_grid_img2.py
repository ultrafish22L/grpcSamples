#!/usr/bin/env python3
"""
Detect grid parameters for octane_allitems2.png by finding the first icon position.
"""

from PIL import Image, ImageDraw
from pathlib import Path

SCREENSHOT_1 = Path(__file__).parent / 'octane_allitems1.png'
SCREENSHOT_2 = Path(__file__).parent / 'octane_allitems2.png'

def find_first_bright_pixel(img, max_search=100):
    """Find the first non-background pixel (likely part of first icon)"""
    pixels = img.load()
    width, height = img.size
    
    bg_threshold = 100  # Background is dark gray (~60)
    
    for y in range(max_search):
        for x in range(max_search):
            r, g, b, a = pixels[x, y]
            
            if a > 128:
                brightness = r + g + b
                if brightness > bg_threshold:
                    return x, y, (r, g, b)
    
    return None, None, None

def find_icon_top_left(img, start_x, start_y, search_range=20):
    """
    Given a pixel that's part of an icon, find the icon's top-left corner.
    Icons are 16x16 and should have consistent boundaries.
    """
    pixels = img.load()
    width, height = img.size
    
    bg_threshold = 100
    
    # Search backwards and upwards from the found pixel to find icon boundaries
    leftmost_x = start_x
    topmost_y = start_y
    
    # Find leftmost pixel with content
    for x in range(start_x, max(0, start_x - search_range), -1):
        has_content = False
        for dy in range(-2, 3):
            test_y = start_y + dy
            if 0 <= test_y < height:
                r, g, b, a = pixels[x, test_y]
                if a > 128 and (r + g + b) > bg_threshold:
                    has_content = True
                    break
        
        if has_content:
            leftmost_x = x
        else:
            # Found background, icon starts after this
            leftmost_x = x + 1
            break
    
    # Find topmost pixel with content
    for y in range(start_y, max(0, start_y - search_range), -1):
        has_content = False
        for dx in range(-2, 3):
            test_x = start_x + dx
            if 0 <= test_x < width:
                r, g, b, a = pixels[test_x, y]
                if a > 128 and (r + g + b) > bg_threshold:
                    has_content = True
                    break
        
        if has_content:
            topmost_y = y
        else:
            # Found background, icon starts after this
            topmost_y = y + 1
            break
    
    return leftmost_x, topmost_y

def scan_for_second_column(img, first_x, first_y, max_search_x=400):
    """Find where the second column starts"""
    pixels = img.load()
    width, height = img.size
    
    bg_threshold = 100
    
    # Start searching from first_x + 20 (skip first icon)
    for x in range(first_x + 20, min(max_search_x, width)):
        # Check if this column has icon content at approximately first_y
        has_content = False
        
        for dy in range(-5, 6):
            test_y = first_y + dy
            if 0 <= test_y < height:
                r, g, b, a = pixels[x, test_y]
                if a > 128 and (r + g + b) > bg_threshold:
                    has_content = True
                    break
        
        if has_content:
            # Found second column, backtrack to find its left edge
            for check_x in range(x, max(first_x + 20, x - 20), -1):
                has_content_here = False
                for dy in range(-5, 6):
                    test_y = first_y + dy
                    if 0 <= test_y < height:
                        r, g, b, a = pixels[check_x, test_y]
                        if a > 128 and (r + g + b) > bg_threshold:
                            has_content_here = True
                            break
                
                if not has_content_here:
                    return check_x + 1
            
            return x
    
    return None

def scan_for_second_row(img, first_x, first_y, max_search_y=100):
    """Find where the second row starts"""
    pixels = img.load()
    width, height = img.size
    
    bg_threshold = 100
    
    # Start searching from first_y + 17 (skip first icon which is 16px tall)
    for y in range(first_y + 17, min(max_search_y, height)):
        # Check if this row has icon content at approximately first_x
        has_content = False
        
        for dx in range(-5, 6):
            test_x = first_x + dx
            if 0 <= test_x < width:
                r, g, b, a = pixels[test_x, y]
                if a > 128 and (r + g + b) > bg_threshold:
                    has_content = True
                    break
        
        if has_content:
            # Found second row, backtrack to find its top edge
            for check_y in range(y, max(first_y + 17, y - 10), -1):
                has_content_here = False
                for dx in range(-5, 6):
                    test_x = first_x + dx
                    if 0 <= test_x < width:
                        r, g, b, a = pixels[test_x, check_y]
                        if a > 128 and (r + g + b) > bg_threshold:
                            has_content_here = True
                            break
                
                if not has_content_here:
                    return check_y + 1
            
            return y
    
    return None

def create_visualization(img, start_x, start_y, col_spacing, row_spacing, output_path):
    """Create a visualization showing detected grid"""
    vis = img.copy()
    draw = ImageDraw.Draw(vis, 'RGBA')
    
    icon_size = 16
    
    # Draw first 50 icons
    for i in range(50):
        row = i // 6
        col = i % 6
        
        x = start_x + (col * col_spacing)
        y = start_y + (row * row_spacing)
        
        if y + icon_size >= img.height:
            break
        
        # Draw rectangle
        draw.rectangle(
            [x, y, x + icon_size, y + icon_size],
            outline=(0, 255, 0, 255),
            width=2
        )
    
    vis.save(output_path)

def main():
    print("="*70)
    print("🔍 DETECTING GRID PARAMETERS FOR BOTH SCREENSHOTS")
    print("="*70)
    
    # Analyze IMG1 (we know these are correct)
    print("\n📸 Analyzing octane_allitems1.png (known correct):")
    img1 = Image.open(SCREENSHOT_1)
    print(f"   Size: {img1.width}x{img1.height}")
    print(f"   ✅ START_X = 3")
    print(f"   ✅ START_Y = 2")
    print(f"   ✅ COL_SPACING = 233")
    print(f"   ✅ ROW_SPACING = 19")
    
    # Analyze IMG2
    print("\n📸 Analyzing octane_allitems2.png (detecting):")
    img2 = Image.open(SCREENSHOT_2)
    print(f"   Size: {img2.width}x{img2.height}")
    
    # Find first bright pixel
    print("\n   🔍 Finding first icon...")
    first_x, first_y, color = find_first_bright_pixel(img2)
    
    if first_x is None:
        print("   ❌ Could not find first icon")
        return
    
    print(f"   Found bright pixel at ({first_x}, {first_y}) - RGB{color}")
    
    # Find icon top-left
    icon_x, icon_y = find_icon_top_left(img2, first_x, first_y)
    print(f"   Icon top-left at ({icon_x}, {icon_y})")
    
    # Find second column
    print("\n   🔍 Finding column spacing...")
    second_col_x = scan_for_second_column(img2, icon_x, icon_y)
    if second_col_x:
        col_spacing = second_col_x - icon_x
        print(f"   Second column at X={second_col_x}")
        print(f"   ✅ COL_SPACING = {col_spacing}")
    else:
        print("   ⚠️  Could not detect second column")
        col_spacing = 233  # Use img1 value as fallback
    
    # Find second row
    print("\n   🔍 Finding row spacing...")
    second_row_y = scan_for_second_row(img2, icon_x, icon_y)
    if second_row_y:
        row_spacing = second_row_y - icon_y
        print(f"   Second row at Y={second_row_y}")
        print(f"   ✅ ROW_SPACING = {row_spacing}")
    else:
        print("   ⚠️  Could not detect second row")
        row_spacing = 19  # Use img1 value as fallback
    
    # Create visualization
    print("\n🎨 Creating visualization...")
    vis_path = Path(__file__).parent / 'grid_detection_img2.png'
    create_visualization(img2, icon_x, icon_y, col_spacing, row_spacing, vis_path)
    print(f"   ✅ Saved: {vis_path}")
    
    # Summary
    print(f"\n{'='*70}")
    print("📋 DETECTED PARAMETERS FOR IMG2")
    print(f"{'='*70}")
    print(f"\nSTART_X = {icon_x}")
    print(f"START_Y = {icon_y}")
    print(f"COL_SPACING = {col_spacing}")
    print(f"ROW_SPACING = {row_spacing}")
    print(f"ICON_SIZE = 16")
    
    print(f"""
{'='*70}
🎯 USE THESE VALUES IN EXTRACTION SCRIPT
{'='*70}

IMG1:
  START_X = 3
  START_Y = 2
  COL_SPACING = 233
  ROW_SPACING = 19

IMG2:
  START_X = {icon_x}
  START_Y = {icon_y}
  COL_SPACING = {col_spacing}
  ROW_SPACING = {row_spacing}

Next step: Update extraction script to use different parameters for each image.
""")

if __name__ == '__main__':
    main()
