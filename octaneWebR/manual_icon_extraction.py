#!/usr/bin/env python3
"""
Manual icon extraction with tunable parameters.
Allows visual verification and adjustment of icon positions.
"""

from PIL import Image, ImageDraw
from pathlib import Path
import json

# Paths
SCREENSHOT_1 = Path(__file__).parent / 'octane_allitems1.png'
SCREENSHOT_2 = Path(__file__).parent / 'octane_allitems2.png'
OUTPUT_DIR = Path(__file__).parent / 'extracted_icons_v2'
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

# EXACT GRID PARAMETERS from user measurements
ICON_SIZE = 16
ROW_SPACING = 19  # Consistent spacing between rows
COL_SPACING = 233  # Consistent spacing between columns
NUM_COLUMNS = 6

# Starting positions for each screenshot (different scroll positions)
# IMG1: User provided measurements - pixels 3-19 horizontally, 2-18 vertically
# IMG2: Auto-detected - same X, but scrolled down 13 pixels
GRID_PARAMS = {
    'img1': {'START_X': 3, 'START_Y': 2},   # From user measurements
    'img2': {'START_X': 3, 'START_Y': 15},  # Auto-detected
}

# Don't auto-detect, use exact measurements
AUTO_DETECT_START = False

def detect_first_icon_position(img):
    """
    Try to find the position of the first icon automatically.
    Looks for the first cluster of non-background pixels.
    """
    pixels = img.load()
    width, height = img.size
    
    bg_color = (60, 60, 60)
    tolerance = 20
    
    # Scan from top-left, looking for first non-background region
    for y in range(0, min(100, height)):
        for x in range(0, min(300, width)):
            r, g, b, a = pixels[x, y]
            
            if a > 128:
                # Check if this is not background
                if (abs(r - bg_color[0]) > tolerance or 
                    abs(g - bg_color[1]) > tolerance or 
                    abs(b - bg_color[2]) > tolerance):
                    
                    brightness = r + g + b
                    if brightness > 50:  # Visible pixel
                        # Found a potential icon pixel
                        # Scan backwards to find the actual start
                        icon_x = x
                        icon_y = y
                        
                        # Find leftmost non-bg pixel in this row
                        for check_x in range(x, max(0, x - 20), -1):
                            r2, g2, b2, a2 = pixels[check_x, y]
                            if (abs(r2 - bg_color[0]) < tolerance and 
                                abs(g2 - bg_color[1]) < tolerance and 
                                abs(b2 - bg_color[2]) < tolerance):
                                # Found background, so icon starts after this
                                icon_x = check_x + 1
                                break
                        
                        # Find topmost non-bg pixel in this column
                        for check_y in range(y, max(0, y - 20), -1):
                            r2, g2, b2, a2 = pixels[icon_x, check_y]
                            if (abs(r2 - bg_color[0]) < tolerance and 
                                abs(g2 - bg_color[1]) < tolerance and 
                                abs(b2 - bg_color[2]) < tolerance):
                                # Found background, so icon starts after this
                                icon_y = check_y + 1
                                break
                        
                        return icon_x, icon_y
    
    return None, None

def extract_icon_grid(img, start_x, start_y, save_samples=True):
    """
    Extract icons using a regular grid pattern.
    Returns list of extracted icons with positions.
    """
    icons = []
    
    max_rows = 80  # More than enough
    
    for row in range(max_rows):
        y = start_y + (row * ROW_SPACING)
        
        if y + ICON_SIZE >= img.height:
            break
        
        for col in range(NUM_COLUMNS):
            x = start_x + (col * COL_SPACING)
            
            if x + ICON_SIZE >= img.width:
                continue
            
            # Check if there's actually content here
            icon = img.crop((x, y, x + ICON_SIZE, y + ICON_SIZE))
            
            # Check if icon has any non-background pixels
            pixels = list(icon.getdata())
            has_content = False
            
            for p in pixels:
                r, g, b, a = p
                if a > 128 and (r + g + b) > 50:
                    has_content = True
                    break
            
            if has_content:
                icons.append({
                    'icon': icon,
                    'x': x,
                    'y': y,
                    'row': row,
                    'col': col
                })
    
    return icons

def create_debug_visualization(img, icons, output_path):
    """Create a visualization showing detected icon positions"""
    debug = img.copy()
    draw = ImageDraw.Draw(debug, 'RGBA')
    
    for icon_data in icons[:100]:  # First 100
        x, y = icon_data['x'], icon_data['y']
        
        # Draw rectangle
        draw.rectangle(
            [x, y, x + ICON_SIZE, y + ICON_SIZE],
            outline=(255, 0, 0, 255),
            width=2
        )
    
    debug.save(output_path)

def create_sample_grid(icons, count=50):
    """Create a grid of sample icons for inspection"""
    samples = icons[:count]
    
    cols = 10
    rows = (count + cols - 1) // cols
    
    display_size = 32
    grid = Image.new('RGBA', (cols * display_size, rows * display_size), (40, 40, 40, 255))
    
    for i, icon_data in enumerate(samples):
        row = i // cols
        col = i % cols
        
        # Resize for visibility
        icon_large = icon_data['icon'].resize((display_size, display_size), Image.NEAREST)
        
        grid.paste(icon_large, (col * display_size, row * display_size))
    
    return grid

def main():
    print("="*70)
    print("🎨 MANUAL ICON EXTRACTION WITH ALIGNMENT")
    print("="*70)
    
    # Process first screenshot
    print(f"\n📸 Processing: {SCREENSHOT_1.name}")
    img1 = Image.open(SCREENSHOT_1)
    print(f"   Size: {img1.width}x{img1.height}")
    
    # Use img1-specific parameters
    start_x1 = GRID_PARAMS['img1']['START_X']
    start_y1 = GRID_PARAMS['img1']['START_Y']
    print(f"   Using start position for img1: ({start_x1}, {start_y1})")
    
    # Extract icons
    print(f"   📦 Extracting icons...")
    print(f"      Grid: {NUM_COLUMNS} columns × row_spacing={ROW_SPACING}px × col_spacing={COL_SPACING}px")
    icons1 = extract_icon_grid(img1, start_x1, start_y1)
    print(f"   ✅ Extracted {len(icons1)} icons")
    
    # Create debug visualization
    debug_path1 = OUTPUT_DIR.parent / 'alignment_debug_img1.png'
    create_debug_visualization(img1, icons1, debug_path1)
    print(f"   💾 Debug overlay: {debug_path1}")
    
    # Create sample grid
    sample_grid1 = create_sample_grid(icons1, count=50)
    sample_path1 = OUTPUT_DIR.parent / 'samples_img1.png'
    sample_grid1.save(sample_path1)
    print(f"   💾 Sample grid: {sample_path1}")
    
    # Process second screenshot
    print(f"\n📸 Processing: {SCREENSHOT_2.name}")
    img2 = Image.open(SCREENSHOT_2)
    print(f"   Size: {img2.width}x{img2.height}")
    
    # Use img2-specific parameters
    start_x2 = GRID_PARAMS['img2']['START_X']
    start_y2 = GRID_PARAMS['img2']['START_Y']
    print(f"   Using start position for img2: ({start_x2}, {start_y2})")
    
    icons2 = extract_icon_grid(img2, start_x2, start_y2)
    print(f"   ✅ Extracted {len(icons2)} icons")
    
    debug_path2 = OUTPUT_DIR.parent / 'alignment_debug_img2.png'
    create_debug_visualization(img2, icons2, debug_path2)
    print(f"   💾 Debug overlay: {debug_path2}")
    
    sample_grid2 = create_sample_grid(icons2, count=50)
    sample_path2 = OUTPUT_DIR.parent / 'samples_img2.png'
    sample_grid2.save(sample_path2)
    print(f"   💾 Sample grid: {sample_path2}")
    
    # Save extracted icons
    print(f"\n💾 Saving extracted icons...")
    for i, icon_data in enumerate(icons1):
        filename = f"img1_{i:04d}.png"
        icon_data['icon'].save(OUTPUT_DIR / filename)
    
    for i, icon_data in enumerate(icons2):
        filename = f"img2_{i:04d}.png"
        icon_data['icon'].save(OUTPUT_DIR / filename)
    
    print(f"   ✅ Saved to: {OUTPUT_DIR}")
    
    print(f"\n{'='*70}")
    print("✅ EXTRACTION COMPLETE")
    print(f"{'='*70}")
    print(f"\nTotal icons: {len(icons1) + len(icons2)}")
    print(f"  From img1: {len(icons1)}")
    print(f"  From img2: {len(icons2)}")
    
    print(f"""
📋 VERIFICATION STEPS:

1. Check alignment visualization:
   - Open: {debug_path1}
   - Open: {debug_path2}
   - Red rectangles should be centered on icons

2. Check sample grids:
   - Open: {sample_path1}
   - Open: {sample_path2}
   - Icons should be properly centered, not cut off

3. If misaligned:
   - Adjust START_X, START_Y, ROW_SPACING, or COL_SPACING in this script
   - Re-run: python3 {Path(__file__).name}

4. If aligned correctly:
   - Run: python3 apply_corrected_mapping.py
""")

if __name__ == '__main__':
    main()
