#!/usr/bin/env python3
"""
Extract icons by detecting menu items and matching text regions with known node names.
This avoids the need for perfect grid alignment.
"""

from PIL import Image, ImageDraw, ImageFont
from pathlib import Path
import json

SCREENSHOT_1 = Path(__file__).parent / 'octane_allitems1.png'
SCREENSHOT_2 = Path(__file__).parent / 'octane_allitems2.png'
MAPPING_FILE = Path(__file__).parent / 'client/public/icons/nodes/node-display-names.json'
OUTPUT_DIR = Path(__file__).parent / 'extracted_icons_text_matched'
OUTPUT_DIR.mkdir(exist_ok=True)

def load_node_names():
    """Load known node display names"""
    with open(MAPPING_FILE, 'r') as f:
        data = json.load(f)
    
    # Create sorted list of (display_name, NT_name)
    items = [(info['displayName'], nt_name) for nt_name, info in data.items()]
    items.sort(key=lambda x: x[0].lower())
    
    return items

def detect_menu_rows(img):
    """
    Detect individual menu item rows by finding horizontal bands with content.
    Returns list of (y_start, y_end, y_center) for each menu item.
    """
    pixels = img.load()
    width, height = img.size
    
    # Scan vertically to find rows with content
    row_data = []
    
    for y in range(height):
        # Count non-background pixels in this row
        non_bg_count = 0
        
        # Check first ~200 pixels (where icon and text would be)
        for x in range(min(200, width)):
            r, g, b, a = pixels[x, y]
            
            if a > 128:
                brightness = r + g + b
                # Look for bright pixels (text or icon content)
                if brightness > 100:
                    non_bg_count += 1
        
        row_data.append(non_bg_count)
    
    # Find peaks (rows with lots of content)
    menu_items = []
    in_item = False
    item_start = None
    
    threshold = 10  # Minimum pixels to consider a row as having content
    
    for y, count in enumerate(row_data):
        if count > threshold and not in_item:
            # Start of menu item
            in_item = True
            item_start = y
        elif count <= threshold and in_item:
            # End of menu item
            in_item = False
            if item_start is not None:
                item_end = y - 1
                item_center = (item_start + item_end) // 2
                menu_items.append({
                    'y_start': item_start,
                    'y_end': item_end,
                    'y_center': item_center,
                    'height': item_end - item_start + 1
                })
                item_start = None
    
    return menu_items

def extract_icon_from_row(img, row_info):
    """
    Extract icon from a menu row.
    Assumes icon is at left edge, 16x16 pixels.
    """
    y_center = row_info['y_center']
    
    # Icon is centered vertically on the row
    icon_y = y_center - 8  # 16/2 = 8
    icon_x = 8  # Estimated left padding
    
    # Try a few different X positions
    best_icon = None
    best_score = 0
    
    for test_x in range(4, 16):
        if test_x + 16 > img.width or icon_y + 16 > img.height:
            continue
        
        icon = img.crop((test_x, icon_y, test_x + 16, icon_y + 16))
        
        # Score by amount of non-background content
        pixels = list(icon.getdata())
        score = 0
        
        for r, g, b, a in pixels:
            if a > 128:
                brightness = r + g + b
                if brightness > 100:
                    score += brightness
        
        if score > best_score:
            best_score = score
            best_icon = icon
    
    return best_icon

def create_debug_visualization(img, menu_items, node_names, output_path):
    """Create visualization showing detected rows"""
    debug = img.copy()
    draw = ImageDraw.Draw(debug, 'RGBA')
    
    try:
        font = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 10)
    except:
        font = None
    
    for i, item in enumerate(menu_items[:50]):  # First 50
        y = item['y_center']
        
        # Draw horizontal line at row center
        draw.line([(0, y), (min(300, img.width), y)], fill=(255, 0, 0, 128), width=1)
        
        # Draw icon box
        icon_x = 8
        icon_y = y - 8
        draw.rectangle(
            [icon_x, icon_y, icon_x + 16, icon_y + 16],
            outline=(0, 255, 0, 255),
            width=2
        )
        
        # Label with expected node name
        if i < len(node_names):
            text = f"{i}: {node_names[i][0][:20]}"
            if font:
                draw.text((20, icon_y), text, fill=(255, 255, 0), font=font)
            else:
                draw.text((20, icon_y), text, fill=(255, 255, 0))
    
    debug.save(output_path)

def main():
    print("="*70)
    print("🎯 ICON EXTRACTION BY TEXT MATCHING")
    print("="*70)
    
    # Load known node names
    print("\n📚 Loading node display names...")
    node_names = load_node_names()
    print(f"   ✅ Loaded {len(node_names)} node types (alphabetically sorted)")
    print(f"   First few: {[name for name, _ in node_names[:5]]}")
    
    # Process first screenshot
    print(f"\n📸 Processing: {SCREENSHOT_1.name}")
    img1 = Image.open(SCREENSHOT_1)
    print(f"   Size: {img1.width}x{img1.height}")
    
    print("   🔍 Detecting menu rows...")
    menu_items_1 = detect_menu_rows(img1)
    print(f"   ✅ Found {len(menu_items_1)} menu items")
    
    # Create debug visualization
    debug_path_1 = Path(__file__).parent / 'text_match_debug_img1.png'
    create_debug_visualization(img1, menu_items_1, node_names, debug_path_1)
    print(f"   💾 Debug visualization: {debug_path_1}")
    
    # Extract icons
    print("   📦 Extracting icons...")
    icons_1 = []
    for i, item in enumerate(menu_items_1):
        if i >= len(node_names):
            break  # No more node names to match
        
        icon = extract_icon_from_row(img1, item)
        if icon:
            display_name, nt_name = node_names[i]
            icons_1.append({
                'icon': icon,
                'nt_name': nt_name,
                'display_name': display_name,
                'index': i
            })
    
    print(f"   ✅ Extracted {len(icons_1)} icons")
    
    # Process second screenshot
    print(f"\n📸 Processing: {SCREENSHOT_2.name}")
    img2 = Image.open(SCREENSHOT_2)
    
    menu_items_2 = detect_menu_rows(img2)
    print(f"   ✅ Found {len(menu_items_2)} menu items")
    
    debug_path_2 = Path(__file__).parent / 'text_match_debug_img2.png'
    # Continue from where img1 left off
    remaining_names = node_names[len(icons_1):]
    create_debug_visualization(img2, menu_items_2, remaining_names, debug_path_2)
    print(f"   💾 Debug visualization: {debug_path_2}")
    
    print("   📦 Extracting icons...")
    icons_2 = []
    for i, item in enumerate(menu_items_2):
        overall_index = len(icons_1) + i
        if overall_index >= len(node_names):
            break
        
        icon = extract_icon_from_row(img2, item)
        if icon:
            display_name, nt_name = node_names[overall_index]
            icons_2.append({
                'icon': icon,
                'nt_name': nt_name,
                'display_name': display_name,
                'index': overall_index
            })
    
    print(f"   ✅ Extracted {len(icons_2)} icons")
    
    # Save all extracted icons
    print(f"\n💾 Saving icons with NT_* names...")
    all_icons = icons_1 + icons_2
    
    for icon_data in all_icons:
        filename = f"{icon_data['nt_name']}.png"
        icon_data['icon'].save(OUTPUT_DIR / filename)
    
    print(f"   ✅ Saved {len(all_icons)} icons to: {OUTPUT_DIR}")
    
    # Check for our camera icon
    camera_icon = next((ic for ic in all_icons if ic['nt_name'] == 'NT_CAM_THINLENS'), None)
    if camera_icon:
        print(f"\n📷 NT_CAM_THINLENS verification:")
        print(f"   Display name: '{camera_icon['display_name']}'")
        print(f"   Position: {camera_icon['index']} in alphabetical list")
        
        # Save enlarged version
        camera_large = camera_icon['icon'].resize((128, 128), Image.NEAREST)
        camera_path = Path(__file__).parent / 'camera_icon_text_matched.png'
        camera_large.save(camera_path)
        print(f"   ✅ Saved enlarged: {camera_path}")
    
    print(f"""
{'='*70}
✅ EXTRACTION COMPLETE
{'='*70}

Total icons extracted: {len(all_icons)}
  From img1: {len(icons_1)}
  From img2: {len(icons_2)}

VERIFICATION STEPS:

1. Check debug visualizations:
   - {debug_path_1}
   - {debug_path_2}
   - Green boxes should align with icons
   - Yellow text shows expected node names

2. Check camera icon:
   - {Path(__file__).parent / 'camera_icon_text_matched.png'}
   - Should show properly centered camera symbol

3. If alignment looks good:
   - Icons are saved in: {OUTPUT_DIR}/
   - Ready to copy to client/public/icons/nodes/

4. If misaligned:
   - Adjust icon_x in extract_icon_from_row()
   - Re-run this script
""")

if __name__ == '__main__':
    main()
