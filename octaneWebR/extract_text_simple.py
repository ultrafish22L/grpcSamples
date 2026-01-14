#!/usr/bin/env python3
"""
Simple text extraction from Octane menu screenshots.
Uses pixel analysis to read white text on dark background.
"""

from PIL import Image
from pathlib import Path
import json
import re

def load_node_type_mappings():
    """Load all node type display names from NodeTypes.ts"""
    nodetype_file = Path(__file__).parent / 'client' / 'src' / 'constants' / 'NodeTypes.ts'
    
    all_names = []
    
    with open(nodetype_file, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Extract display names
    pattern = r"name:\s*'([^']+)'"
    for match in re.finditer(pattern, content):
        name = match.group(1)
        all_names.append(name.lower())  # Normalize for matching
    
    return all_names

def extract_text_bounding_box(img, icon_x, icon_y, icon_size=16, max_text_width=180):
    """
    Extract text region next to an icon and analyze its content.
    Returns the text region as a binary image for analysis.
    """
    # Text starts a few pixels after the icon
    text_x = icon_x + icon_size + 5
    text_y = icon_y
    text_height = icon_size
    
    # Crop text region
    text_region = img.crop((
        text_x,
        text_y,
        min(text_x + max_text_width, img.width),
        text_y + text_height
    ))
    
    # Convert to grayscale
    gray = text_region.convert('L')
    
    # Threshold to binary (white text on dark background)
    threshold = 150
    binary = gray.point(lambda p: 255 if p > threshold else 0)
    
    # Find the actual width of the text (where white pixels end)
    pixels = list(binary.getdata())
    width, height = binary.size
    
    text_width = 0
    for x in range(width - 1, -1, -1):
        column_has_white = False
        for y in range(height):
            if pixels[y * width + x] == 255:
                column_has_white = True
                break
        if column_has_white:
            text_width = x + 1
            break
    
    # Crop to actual text width
    if text_width > 0:
        final_region = binary.crop((0, 0, text_width, height))
        return final_region
    
    return None

def create_text_extraction_sheet(screenshot_path, icons_metadata):
    """
    Create a reference sheet showing all text regions extracted from a screenshot.
    """
    print(f"\n📄 Processing text from: {screenshot_path.name}")
    
    img = Image.open(screenshot_path)
    
    # Extract text regions using the same positions as icon extraction
    icon_size = 16
    row_spacing = 18
    num_columns = 6
    
    menu_width = img.width
    column_width = menu_width // num_columns
    
    text_regions = []
    
    for row_idx in range(80):  # Max rows
        y = 5 + (row_idx * row_spacing)
        
        if y + icon_size >= img.height:
            break
        
        for col_idx in range(num_columns):
            x = 5 + (col_idx * column_width)
            
            if x + icon_size >= img.width:
                continue
            
            # Extract text region
            text_region = extract_text_bounding_box(img, x, y)
            
            if text_region and text_region.width > 10:  # At least some text
                text_regions.append({
                    'position': (x, y),
                    'row': row_idx,
                    'col': col_idx,
                    'region': text_region
                })
    
    print(f"   Found {len(text_regions)} text regions")
    
    # Create a composite image showing all extracted text
    output_dir = Path(__file__).parent / 'extracted_text'
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Save each text region individually for manual inspection
    for idx, data in enumerate(text_regions):
        output_path = output_dir / f"{screenshot_path.stem}_text_{idx:04d}.png"
        # Make it larger for visibility
        region_large = data['region'].resize((data['region'].width * 2, data['region'].height * 2), Image.NEAREST)
        region_large.save(output_path)
    
    print(f"   💾 Saved text regions to: {output_dir}")
    
    return text_regions

def main():
    print("="*70)
    print("🔤 EXTRACTING TEXT FROM SCREENSHOTS")
    print("="*70)
    
    # Process both screenshots
    screenshots = [
        Path(__file__).parent / 'octane_allitems1.png',
        Path(__file__).parent / 'octane_allitems2.png'
    ]
    
    # Load node type names for reference
    node_names = load_node_type_mappings()
    print(f"\n✅ Loaded {len(node_names)} node type names from NodeTypes.ts")
    
    # Extract text from each screenshot
    all_text_regions = []
    
    for screenshot in screenshots:
        if not screenshot.exists():
            print(f"❌ Not found: {screenshot}")
            continue
        
        text_regions = create_text_extraction_sheet(screenshot, None)
        all_text_regions.extend(text_regions)
    
    print(f"\n{'='*70}")
    print(f"✅ EXTRACTED {len(all_text_regions)} TEXT REGIONS")
    print(f"{'='*70}")
    
    print(f"""
📋 NEXT STEPS:

The text regions have been extracted as binary images.
You can now:

1. Review the extracted text images in: extracted_text/
2. Manually read and create mapping file
3. OR use OCR software to batch-read the text

For manual mapping:
- Each text image corresponds to an icon in the same position
- Match extracted_icons/octane_allitems1_XXXX.png 
- With extracted_text/octane_allitems1_text_XXXX.png
- Create mapping: icon file -> node name

Suggested format for mapping file (icon_mapping.txt):
octane_allitems1_0000.png|2D transformation
octane_allitems1_0001.png|2D rotation
...
""")

if __name__ == '__main__':
    main()
