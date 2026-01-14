#!/usr/bin/env python3
"""
Manually sample pixels from img2 to find where icons start.
Use same spacing as img1, just find different starting position.
"""

from PIL import Image, ImageDraw
from pathlib import Path

SCREENSHOT_2 = Path(__file__).parent / 'octane_allitems2.png'

def sample_region(img, x, y, size=16):
    """Sample a 16x16 region (icon size) and check if it has content"""
    if x + size > img.width or y + size > img.height:
        return False, 0
    
    icon = img.crop((x, y, x + size, y + size))
    pixels = list(icon.getdata())
    
    total_brightness = 0
    bright_pixels = 0
    
    for r, g, b, a in pixels:
        if a > 128:
            brightness = r + g + b
            total_brightness += brightness
            if brightness > 100:  # Significant brightness
                bright_pixels += 1
    
    has_content = bright_pixels > 10  # At least 10 bright pixels in icon
    
    return has_content, total_brightness

def test_grid_positions(img):
    """
    Test various starting positions using img1's spacing values.
    We know COL_SPACING=233 and ROW_SPACING=19 work for img1,
    so try different START_X and START_Y for img2.
    """
    COL_SPACING = 233
    ROW_SPACING = 19
    ICON_SIZE = 16
    
    # Test various starting positions
    test_positions = []
    
    for start_x in range(0, 30):
        for start_y in range(0, 30):
            # Test first 6 icons in first row (should all have content)
            icons_with_content = 0
            total_brightness = 0
            
            for col in range(6):
                x = start_x + (col * COL_SPACING)
                y = start_y
                
                has_content, brightness = sample_region(img, x, y, ICON_SIZE)
                if has_content:
                    icons_with_content += 1
                    total_brightness += brightness
            
            if icons_with_content >= 4:  # At least 4 of 6 icons have content
                test_positions.append({
                    'start_x': start_x,
                    'start_y': start_y,
                    'icons_found': icons_with_content,
                    'total_brightness': total_brightness
                })
    
    # Sort by most icons found and highest brightness
    test_positions.sort(key=lambda p: (p['icons_found'], p['total_brightness']), reverse=True)
    
    return test_positions

def create_test_visualization(img, test_positions, output_path):
    """Create visualization showing top candidate positions"""
    vis = img.copy()
    draw = ImageDraw.Draw(vis, 'RGBA')
    
    COL_SPACING = 233
    ROW_SPACING = 19
    ICON_SIZE = 16
    
    colors = [
        (255, 0, 0, 255),    # Red - best match
        (255, 128, 0, 255),  # Orange
        (255, 255, 0, 255),  # Yellow
        (0, 255, 0, 255),    # Green
        (0, 255, 255, 255),  # Cyan
    ]
    
    for i, pos in enumerate(test_positions[:5]):
        color = colors[i] if i < len(colors) else (128, 128, 128, 255)
        
        # Draw first 6 icons in first row
        for col in range(6):
            x = pos['start_x'] + (col * COL_SPACING)
            y = pos['start_y']
            
            if x + ICON_SIZE < img.width and y + ICON_SIZE < img.height:
                draw.rectangle(
                    [x, y, x + ICON_SIZE, y + ICON_SIZE],
                    outline=color,
                    width=2 if i == 0 else 1
                )
    
    vis.save(output_path)

def main():
    print("="*70)
    print("🔍 FINDING CORRECT START POSITION FOR IMG2")
    print("="*70)
    
    print(f"\n📸 Loading: octane_allitems2.png")
    img = Image.open(SCREENSHOT_2)
    print(f"   Size: {img.width}x{img.height}")
    
    print(f"\n🔎 Testing grid positions...")
    print(f"   Using: COL_SPACING=233, ROW_SPACING=19 (from img1)")
    print(f"   Testing: Various START_X and START_Y combinations")
    
    test_positions = test_grid_positions(img)
    
    print(f"\n📊 Top 10 candidate positions:")
    print(f"{'Rank':>4} {'START_X':>8} {'START_Y':>8} {'Icons':>6} {'Brightness':>12}")
    print("-"*70)
    
    for i, pos in enumerate(test_positions[:10]):
        print(f"{i+1:4d} {pos['start_x']:8d} {pos['start_y']:8d} {pos['icons_found']:6d} {pos['total_brightness']:12d}")
    
    if test_positions:
        best = test_positions[0]
        print(f"\n✅ BEST MATCH:")
        print(f"   START_X = {best['start_x']}")
        print(f"   START_Y = {best['start_y']}")
        print(f"   Icons found: {best['icons_found']}/6")
        print(f"   Total brightness: {best['total_brightness']}")
    
    # Create visualization
    print(f"\n🎨 Creating visualization...")
    vis_path = Path(__file__).parent / 'img2_grid_candidates.png'
    create_test_visualization(img, test_positions, vis_path)
    print(f"   ✅ Saved: {vis_path}")
    print(f"   Colors: Red=best, Orange=2nd, Yellow=3rd, etc.")
    
    print(f"""
{'='*70}
🎯 RECOMMENDED PARAMETERS FOR IMG2
{'='*70}

START_X = {test_positions[0]['start_x'] if test_positions else 'N/A'}
START_Y = {test_positions[0]['start_y'] if test_positions else 'N/A'}
COL_SPACING = 233  (same as img1)
ROW_SPACING = 19   (same as img1)
ICON_SIZE = 16

Compare with IMG1:
  START_X = 3
  START_Y = 2

Difference:
  ΔX = {test_positions[0]['start_x'] - 3 if test_positions else 'N/A'}
  ΔY = {test_positions[0]['start_y'] - 2 if test_positions else 'N/A'}
""")

if __name__ == '__main__':
    main()
