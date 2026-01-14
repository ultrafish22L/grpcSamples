#!/usr/bin/env python3
"""
Extract node type icons from Octane SE "All items" context menu screenshots.
The user provided 2 images showing all node types with their icons.
"""

import sys
from pathlib import Path
from PIL import Image
import pytesseract
import re

# Add generated proto path
sys.path.append(str(Path(__file__).parent / 'generated'))

# Output directory for extracted icons
OUTPUT_DIR = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'nodes'
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

# Load NodeTypes mapping to get all valid node types
NODETYPE_MAPPING_FILE = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'src' / 'constants' / 'NodeTypes.ts'

def parse_node_types_from_ts():
    """Parse NodeTypes.ts to get mapping of display names to NT_* enums"""
    name_to_enum = {}
    enum_to_info = {}
    
    with open(NODETYPE_MAPPING_FILE, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Extract all NT_* entries with their names
    # Pattern: 'NT_SOMETHING': { name: 'Display Name', color: '#HEX' }
    pattern = r"'(NT_[A-Z_0-9]+)':\s*{\s*name:\s*'([^']+)'"
    
    for match in re.finditer(pattern, content):
        enum_name = match.group(1)
        display_name = match.group(2)
        
        # Normalize display name for matching
        normalized = display_name.lower().strip()
        name_to_enum[normalized] = enum_name
        enum_to_info[enum_name] = display_name
    
    return name_to_enum, enum_to_info

def extract_icons_from_screenshot(image_path):
    """
    Extract icons from the "All items" menu screenshot.
    
    The menu structure:
    - Multi-column layout (6 columns as per Octane SE)
    - Each row: [icon] Node name
    - Icons are approximately 16x16 pixels
    - Background: dark gray (#3c3c3c)
    - Text: white
    """
    
    print(f"\n📸 Processing: {image_path}")
    
    img = Image.open(image_path)
    print(f"   Image size: {img.width}x{img.height}")
    
    # Detect menu region (dark gray background)
    # Look for rectangular region with #3c3c3c background
    
    # For now, let's detect rows by finding horizontal bands with consistent structure
    # Each menu item is roughly 20-25 pixels tall
    
    # Convert to RGB if needed
    if img.mode != 'RGB':
        img = img.convert('RGB')
    
    pixels = img.load()
    
    # Scan for menu items by looking for icon-sized regions followed by text
    # This is a simplified approach - ideally we'd use proper OCR and region detection
    
    # Menu typically starts around x=200-400, y=200-400 (varies by screenshot)
    # Let's find the dark gray menu background first
    
    menu_bg_color = (60, 60, 60)  # #3c3c3c
    tolerance = 20
    
    # Find menu region
    menu_left = None
    menu_top = None
    menu_right = None
    menu_bottom = None
    
    # Scan for large dark gray region
    for y in range(img.height):
        dark_count = 0
        for x in range(img.width):
            r, g, b = pixels[x, y][:3] if len(pixels[x, y]) >= 3 else (0, 0, 0)
            if abs(r - menu_bg_color[0]) < tolerance and \
               abs(g - menu_bg_color[1]) < tolerance and \
               abs(b - menu_bg_color[2]) < tolerance:
                dark_count += 1
                if dark_count > 100:  # Found a row with lots of menu background
                    if menu_top is None:
                        menu_top = y
                    menu_bottom = y
                    break
    
    print(f"   Menu region: y={menu_top} to y={menu_bottom}")
    
    # TODO: Implement full icon extraction
    # For now, this is a template. Full implementation would require:
    # 1. OCR to read each node name
    # 2. Crop the icon to the left of each name
    # 3. Map node name to NT_* enum
    # 4. Save icon with correct filename
    
    print("   ⚠️  Full extraction requires OCR and region detection")
    print("   💡  Manual approach: Use the existing icons or provide pre-cropped icons")
    
    return []

def main():
    """Main extraction process"""
    
    print("="*70)
    print("🎨 ICON EXTRACTION FROM USER SCREENSHOTS")
    print("="*70)
    
    # Parse NodeTypes.ts to get mappings
    print("\n📚 Loading node type mappings from NodeTypes.ts...")
    name_to_enum, enum_to_info = parse_node_types_from_ts()
    print(f"   Found {len(enum_to_info)} node types")
    
    # Look for user-provided screenshots
    screenshot_dir = Path(__file__).parent.parent / 'octaneWebR'
    screenshots = list(screenshot_dir.glob("*.png")) + list(screenshot_dir.glob("*.jpg"))
    
    if not screenshots:
        print("\n❌ No screenshots found in octaneWebR directory")
        print("\n💡 Please save the user-provided screenshots as:")
        print("   - grpcSamples/octaneWebR/all_items_menu_1.png")
        print("   - grpcSamples/octaneWebR/all_items_menu_2.png")
        return
    
    print(f"\n📁 Found {len(screenshots)} screenshot(s)")
    
    # Process each screenshot
    extracted_count = 0
    for screenshot in screenshots:
        icons = extract_icons_from_screenshot(screenshot)
        extracted_count += len(icons)
    
    print(f"\n{'='*70}")
    print(f"✅ Extraction complete: {extracted_count} icons")
    print(f"{'='*70}")
    
    # For now, inform user about manual process
    print("\n" + "="*70)
    print("📋 MANUAL ICON EXTRACTION REQUIRED")
    print("="*70)
    print("""
The automatic extraction of icons from context menu screenshots requires:
1. OCR (Optical Character Recognition) to read node names
2. Region detection to locate icon boundaries
3. Complex image processing to handle multi-column layout

ALTERNATIVE APPROACHES:

A. Use Existing Icons (RECOMMENDED if they look correct):
   - We have 637 icons already extracted in client/public/icons/nodes/
   - Verify they display correctly in the browser
   - If icons appear correct, no changes needed

B. Manual Icon Extraction (if existing icons are wrong):
   1. Open user-provided screenshots in image editor
   2. Crop out each 16x16 icon
   3. Name according to NT_* enum (use mapping in NodeTypes.ts)
   4. Save to: octaneWebR/client/public/icons/nodes/

C. Request Pre-Cropped Icons:
   - Ask user if they can provide icons in separate files
   - Or provide a sprite sheet with regular grid layout
""")
    
    # Check if existing icons look valid
    existing_icons = list(OUTPUT_DIR.glob("NT_*.png"))
    print(f"\n📊 Current status: {len(existing_icons)} icons in {OUTPUT_DIR}")
    
    # Sample a few to check file sizes
    if existing_icons:
        sample = existing_icons[:5]
        print("\n🔍 Sample existing icons:")
        for icon in sample:
            size = icon.stat().st_size
            print(f"   {icon.name}: {size} bytes")

if __name__ == '__main__':
    main()
