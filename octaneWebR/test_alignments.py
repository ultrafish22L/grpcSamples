#!/usr/bin/env python3
"""
Test multiple grid alignments and create a comparison sheet.
This helps identify the correct START_X and START_Y values.
"""

from PIL import Image, ImageDraw, ImageFont
from pathlib import Path

SCREENSHOT = Path(__file__).parent / 'octane_allitems1.png'
OUTPUT = Path(__file__).parent / 'alignment_test_sheet.png'

# Test these parameter combinations
TEST_PARAMS = [
    # (START_X, START_Y, label)
    (0, 0, "0,0 (auto-detect)"),
    (4, 4, "4,4"),
    (6, 4, "6,4"),
    (8, 4, "8,4"),
    (8, 6, "8,6 (bright pixels)"),
    (10, 6, "10,6"),
    (12, 6, "12,6"),
    (6, 6, "6,6"),
    (10, 8, "10,8"),
]

ICON_SIZE = 16
ROW_SPACING = 18
COL_SPACING = 226

def extract_icon(img, start_x, start_y, row, col):
    """Extract one icon with given parameters"""
    x = start_x + (col * COL_SPACING)
    y = start_y + (row * ROW_SPACING)
    
    if x + ICON_SIZE > img.width or y + ICON_SIZE > img.height:
        return None
    
    return img.crop((x, y, x + ICON_SIZE, y + ICON_SIZE))

def create_test_sheet(img):
    """
    Create a contact sheet showing different alignment results.
    For each parameter set, show the first 10 icons extracted.
    """
    num_tests = len(TEST_PARAMS)
    icons_per_test = 10
    
    # Each test shows a label + 10 icons
    cell_size = 48  # Enlarged icon display
    label_width = 200
    test_height = cell_size + 20  # Icon + padding
    
    sheet_width = label_width + (icons_per_test * cell_size) + 20
    sheet_height = num_tests * test_height + 40
    
    sheet = Image.new('RGB', (sheet_width, sheet_height), (40, 40, 40))
    draw = ImageDraw.Draw(sheet)
    
    # Title
    draw.text((10, 10), "ALIGNMENT TESTS - First 10 icons from each setting", fill=(255, 255, 255))
    
    for test_idx, (start_x, start_y, label) in enumerate(TEST_PARAMS):
        y_pos = 40 + (test_idx * test_height)
        
        # Draw label
        draw.text((10, y_pos + 10), label, fill=(200, 200, 200))
        
        # Extract and display first 10 icons
        for icon_idx in range(icons_per_test):
            # Extract from first row, different columns
            icon = extract_icon(img, start_x, start_y, 0, icon_idx)
            
            if icon:
                # Enlarge for visibility
                icon_large = icon.resize((cell_size, cell_size), Image.NEAREST)
                
                x_pos = label_width + (icon_idx * cell_size) + 10
                sheet.paste(icon_large, (x_pos, y_pos))
                
                # Draw border
                draw.rectangle(
                    [x_pos, y_pos, x_pos + cell_size, y_pos + cell_size],
                    outline=(80, 80, 80),
                    width=1
                )
    
    return sheet

def extract_specific_icons(img, start_x, start_y, count=20):
    """Extract first N icons with given parameters"""
    icons = []
    
    for i in range(count):
        row = i // 6
        col = i % 6
        
        icon = extract_icon(img, start_x, start_y, row, col)
        if icon:
            icons.append(icon)
    
    return icons

def main():
    print("="*70)
    print("🧪 TESTING MULTIPLE ALIGNMENTS")
    print("="*70)
    
    print(f"\n📸 Loading: {SCREENSHOT.name}")
    img = Image.open(SCREENSHOT)
    
    print(f"\n🔬 Testing {len(TEST_PARAMS)} parameter combinations...")
    print(f"   Icon size: {ICON_SIZE}x{ICON_SIZE}")
    print(f"   Row spacing: {ROW_SPACING}px")
    print(f"   Col spacing: {COL_SPACING}px")
    
    # Create test sheet
    print("\n🎨 Creating comparison sheet...")
    sheet = create_test_sheet(img)
    sheet.save(OUTPUT)
    print(f"   ✅ Saved: {OUTPUT}")
    
    # Also extract camera icon (index 106) with each parameter
    print("\n📷 Extracting NT_CAM_THINLENS (index 106) with each parameter...")
    
    camera_test_dir = Path(__file__).parent / 'camera_alignment_tests'
    camera_test_dir.mkdir(exist_ok=True)
    
    # Index 106 is in row 106//6=17, col 106%6=4
    camera_row = 106 // 6
    camera_col = 106 % 6
    
    print(f"   Camera icon should be at: row {camera_row}, col {camera_col}")
    
    for start_x, start_y, label in TEST_PARAMS:
        icon = extract_icon(img, start_x, start_y, camera_row, camera_col)
        
        if icon:
            # Save at actual size
            filename = camera_test_dir / f"camera_{label.replace(',', '_').replace(' ', '_')}.png"
            icon.save(filename)
            
            # Also save enlarged
            icon_large = icon.resize((128, 128), Image.NEAREST)
            filename_large = camera_test_dir / f"camera_{label.replace(',', '_').replace(' ', '_')}_large.png"
            icon_large.save(filename_large)
    
    print(f"   ✅ Saved camera tests to: {camera_test_dir}")
    
    print(f"""
{'='*70}
✅ TEST COMPLETE
{'='*70}

REVIEW THESE FILES:

1. {OUTPUT}
   - Shows first 10 icons from each parameter combination
   - Look for the row where icons are properly centered (not cut off)

2. {camera_test_dir}/
   - Contains NT_CAM_THINLENS extracted with each parameter set
   - Compare with your reference screenshot
   - Find which one looks like a properly centered camera icon

Once you identify the correct parameters:
1. Update manual_icon_extraction.py with those START_X, START_Y values
2. Re-run extraction with: python3 manual_icon_extraction.py
3. Apply mapping with: python3 apply_corrected_mapping.py

Example: If "8,6" looks correct, edit manual_icon_extraction.py:
    START_X = 8
    START_Y = 6
""")

if __name__ == '__main__':
    main()
