#!/usr/bin/env python3
"""
Extract individual icons from Octane SE documentation screenshots
"""

import requests
from bs4 import BeautifulSoup
from PIL import Image, ImageDraw
import io
from pathlib import Path
import numpy as np

BASE_URL = "https://docs.otoy.com/standaloneSE/"
OUTPUT_DIR = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'extracted'
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

# Screenshots that likely contain node icons
SCREENSHOTS_TO_ANALYZE = [
    "lib/TheGraphEditor_656x341.png",
    "lib/TheGraphEditor3_SEv4.png",
    "lib/Node_Inspector_Fig01_SE_v2022.jpg",
    "lib/Node_Inspector_Fig03_SE_v2020.jpg",
    "lib/Graph_Editor_Fig03_SE_v2022.jpg",
]

def download_screenshot(url):
    """Download a screenshot image"""
    try:
        response = requests.get(url, timeout=15)
        if response.status_code == 200:
            img = Image.open(io.BytesIO(response.content))
            return img
        return None
    except Exception as e:
        print(f"❌ Error downloading {url}: {e}")
        return None

def find_icon_regions(img):
    """
    Detect small icon-like regions in a screenshot
    Returns list of (x, y, width, height) bounding boxes
    """
    # Convert to numpy array
    img_array = np.array(img.convert('RGB'))
    
    # Look for small square regions that might be icons
    # This is a simple approach - could be improved with better computer vision
    
    # For now, just return None to indicate manual extraction needed
    return None

def extract_node_graph_screenshot(page_url):
    """Extract screenshot showing node graph with icons"""
    try:
        response = requests.get(page_url, timeout=15)
        soup = BeautifulSoup(response.content, 'html.parser')
        
        # Find images that look like node graph screenshots
        for img in soup.find_all('img'):
            src = img.get('src', '')
            alt = img.get('alt', '').lower()
            
            if 'graph' in src.lower() or 'node' in src.lower() or 'graph' in alt:
                full_url = BASE_URL + src if not src.startswith('http') else src
                print(f"Found potential node graph screenshot: {src}")
                
                image = download_screenshot(full_url)
                if image:
                    # Save for manual inspection
                    filename = Path(src).name
                    save_path = OUTPUT_DIR / f"screenshot_{filename}"
                    image.save(save_path)
                    print(f"  ✅ Saved: {save_path} ({image.width}x{image.height})")
                    return save_path
        
        return None
    except Exception as e:
        print(f"❌ Error: {e}")
        return None

def main():
    print("="*70)
    print("🔍 ICON EXTRACTION FROM SCREENSHOTS")
    print("="*70)
    print("\nDownloading screenshots that show node icons...\n")
    
    # Download screenshots
    screenshots = []
    for screenshot in SCREENSHOTS_TO_ANALYZE:
        url = BASE_URL + screenshot
        print(f"Downloading: {screenshot}")
        img = download_screenshot(url)
        if img:
            filename = Path(screenshot).name
            save_path = OUTPUT_DIR / filename
            img.save(save_path)
            print(f"  ✅ Saved: {save_path} ({img.width}x{img.height})")
            screenshots.append(save_path)
        else:
            print(f"  ❌ Failed")
    
    print(f"\n{'='*70}")
    print(f"📊 DOWNLOADED {len(screenshots)} SCREENSHOTS")
    print(f"{'='*70}")
    print(f"\n💾 Saved to: {OUTPUT_DIR}")
    print("\n💡 Next steps:")
    print("  1. Open screenshots to identify node icons")
    print("  2. Manually crop or use image processing to extract individual icons")
    print("  3. Match extracted icons to node type names")
    
    # List what we got
    print(f"\nScreenshots downloaded:")
    for path in screenshots:
        print(f"  {path.name}")

if __name__ == '__main__':
    main()
