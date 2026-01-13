#!/usr/bin/env python3
"""
Comprehensive icon scraper for Octane SE documentation
Extracts ALL icons: node icons, toolbar icons, button icons, UI elements
"""

import requests
from bs4 import BeautifulSoup
import os
from pathlib import Path
from urllib.parse import urljoin, urlparse
import time
from PIL import Image
import io

BASE_URL = "https://docs.otoy.com/standaloneSE/"
OUTPUT_DIR = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'scraped'

# Pages likely to contain icons
PAGES_TO_SCAN = [
    "TheGraphEditor.html",
    "Materials.html",
    "Textures.html",
    "Lighting.html",
    "CameraNodes.html",
    "TheRenderViewport.html",
    "TheNodeInspector.html",
    "TheSceneOutliner.html",
    "InterfaceLayout.html",
    "DiffuseMaterial.html",
    "GlossyMaterial.html",
    "UniversalMaterial.html",
    "SpecularMaterial.html",
    "Image-basedTextures.html",
    "ProceduralTextures.html",
    "GeometricTextures.html",
    "ManagingGeometry.html",
]

def is_likely_icon(img_tag, img_url):
    """
    Determine if an image is likely an icon based on:
    - File name patterns
    - Size attributes
    - Context
    """
    src = img_tag.get('src', '').lower()
    
    # Check for icon-like patterns in filename
    icon_patterns = [
        'icon', 'btn', 'button', 'toolbar', 'menu',
        'node', 'mat_', 'tex_', 'geo_', 'cam_',
        'small', 'ui', 'widget', 'glyph'
    ]
    
    if any(pattern in src for pattern in icon_patterns):
        return True
    
    # Check file extensions
    if not any(src.endswith(ext) for ext in ['.png', '.jpg', '.jpeg', '.gif', '.svg']):
        return False
    
    # Check size attributes (icons are typically small)
    width = img_tag.get('width')
    height = img_tag.get('height')
    
    if width and height:
        try:
            w, h = int(width), int(height)
            if w <= 64 and h <= 64:  # Likely an icon
                return True
        except:
            pass
    
    return False

def download_image(url, output_path):
    """Download an image and save it"""
    try:
        response = requests.get(url, timeout=10)
        if response.status_code == 200:
            # Check if it's actually an image
            try:
                img = Image.open(io.BytesIO(response.content))
                # Save it
                img.save(output_path)
                return True, img.size
            except Exception as e:
                return False, f"Not a valid image: {e}"
        else:
            return False, f"HTTP {response.status_code}"
    except Exception as e:
        return False, str(e)

def scan_page(page_url):
    """Scan a single page for icons"""
    print(f"\n{'='*70}")
    print(f"Scanning: {page_url}")
    print(f"{'='*70}")
    
    try:
        response = requests.get(page_url, timeout=15)
        if response.status_code != 200:
            print(f"❌ Failed to load page: HTTP {response.status_code}")
            return []
        
        soup = BeautifulSoup(response.content, 'html.parser')
        
        # Find all images
        all_images = soup.find_all('img')
        print(f"Found {len(all_images)} total images")
        
        # Filter for likely icons
        icon_images = []
        for img in all_images:
            src = img.get('src', '')
            if not src:
                continue
            
            full_url = urljoin(page_url, src)
            
            if is_likely_icon(img, full_url):
                icon_images.append({
                    'url': full_url,
                    'src': src,
                    'alt': img.get('alt', ''),
                    'class': img.get('class', []),
                    'width': img.get('width', ''),
                    'height': img.get('height', ''),
                })
        
        print(f"Found {len(icon_images)} likely icon images")
        
        # Also find all PNG/GIF images in 'lib' directory (common for UI assets)
        lib_images = [img for img in all_images if '/lib/' in img.get('src', '')]
        print(f"Found {len(lib_images)} images in 'lib' directory")
        
        for img in lib_images:
            src = img.get('src', '')
            if not src:
                continue
            full_url = urljoin(page_url, src)
            
            # Check if already in icon_images
            if not any(icon['url'] == full_url for icon in icon_images):
                icon_images.append({
                    'url': full_url,
                    'src': src,
                    'alt': img.get('alt', ''),
                    'class': img.get('class', []),
                    'width': img.get('width', ''),
                    'height': img.get('height', ''),
                })
        
        return icon_images
        
    except Exception as e:
        print(f"❌ Error scanning page: {e}")
        return []

def main():
    print("="*70)
    print("🎨 OCTANE SE DOCUMENTATION ICON SCRAPER")
    print("="*70)
    print("\nExtracting ALL icons from documentation:")
    print("  • Node type icons")
    print("  • Toolbar buttons")
    print("  • UI widgets")
    print("  • Menu icons")
    print("  • Everything visual!")
    
    # Create output directories
    categories = ['nodes', 'toolbar', 'ui', 'misc']
    for cat in categories:
        (OUTPUT_DIR / cat).mkdir(parents=True, exist_ok=True)
    
    print(f"\n💾 Output directory: {OUTPUT_DIR}")
    
    # Collect all icons
    all_icons = {}
    
    for page in PAGES_TO_SCAN:
        page_url = urljoin(BASE_URL, page)
        icons = scan_page(page_url)
        
        for icon in icons:
            url = icon['url']
            if url not in all_icons:
                all_icons[url] = icon
        
        time.sleep(0.5)  # Be nice to the server
    
    print(f"\n{'='*70}")
    print(f"📊 FOUND {len(all_icons)} UNIQUE ICONS")
    print(f"{'='*70}")
    
    # Download all icons
    print(f"\n🔽 Downloading icons...\n")
    
    success = 0
    failed = 0
    skipped = 0
    
    for i, (url, icon) in enumerate(all_icons.items(), 1):
        # Determine filename
        parsed = urlparse(url)
        filename = os.path.basename(parsed.path)
        
        # Categorize
        src = icon['src'].lower()
        if 'node' in src or 'mat_' in src or 'tex_' in src:
            category = 'nodes'
        elif 'toolbar' in src or 'btn' in src or 'button' in src:
            category = 'toolbar'
        elif 'ui' in src or 'widget' in src or 'icon' in src:
            category = 'ui'
        else:
            category = 'misc'
        
        output_path = OUTPUT_DIR / category / filename
        
        # Skip if already exists
        if output_path.exists():
            skipped += 1
            continue
        
        # Download
        print(f"[{i:3}/{len(all_icons)}] {filename[:50]:50} ", end='', flush=True)
        ok, result = download_image(url, output_path)
        
        if ok:
            width, height = result
            print(f"✅ {width}x{height}")
            success += 1
        else:
            print(f"❌ {str(result)[:30]}")
            failed += 1
        
        time.sleep(0.2)  # Be nice
    
    # Summary
    print(f"\n{'='*70}")
    print(f"📊 DOWNLOAD COMPLETE")
    print(f"{'='*70}")
    print(f"   ✅ Success: {success}")
    print(f"   ⚠️  Skipped: {skipped}")
    print(f"   ❌ Failed: {failed}")
    print(f"\n💾 Icons saved to:")
    
    for cat in categories:
        cat_dir = OUTPUT_DIR / cat
        count = len(list(cat_dir.glob('*')))
        if count > 0:
            print(f"   {cat:12} {count:3} icons")
    
    print(f"\n🎉 Done!")

if __name__ == '__main__':
    main()
