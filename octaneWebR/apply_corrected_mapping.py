#!/usr/bin/env python3
"""
Apply corrected icon mapping using properly aligned extracted icons.
Maps extracted icons to NT_* names based on alphabetical ordering.
"""

from PIL import Image
from pathlib import Path
import json
import shutil

EXTRACTED_DIR = Path(__file__).parent / 'extracted_icons_v2'
MAPPING_FILE = Path(__file__).parent / 'client/public/icons/nodes/node-display-names.json'
OUTPUT_DIR = Path(__file__).parent / 'client/public/icons/nodes'
BACKUP_DIR = Path(__file__).parent / 'icon_backup_before_remap'

def load_node_names():
    """Load known node display names and sort alphabetically"""
    with open(MAPPING_FILE, 'r') as f:
        data = json.load(f)
    
    # Create sorted list of (display_name, NT_name)
    items = [(info['displayName'], nt_name) for nt_name, info in data.items()]
    items.sort(key=lambda x: x[0].lower())
    
    return items

def backup_existing_icons():
    """Backup existing icons before overwriting"""
    if BACKUP_DIR.exists():
        print(f"   ⚠️  Backup already exists: {BACKUP_DIR}")
        return
    
    BACKUP_DIR.mkdir(parents=True, exist_ok=True)
    
    # Copy existing icons
    existing_icons = list(OUTPUT_DIR.glob('NT_*.png'))
    for icon_path in existing_icons:
        shutil.copy(icon_path, BACKUP_DIR / icon_path.name)
    
    print(f"   ✅ Backed up {len(existing_icons)} existing icons to: {BACKUP_DIR}")

def apply_mapping(sorted_nodes, extracted_dir):
    """
    Apply mapping from extracted icons to NT_* names.
    
    The Octane "All items" menu shows nodes alphabetically by display name.
    We have extracted icons in that order, so we can map directly.
    """
    # Get list of extracted icon files
    img1_icons = sorted(extracted_dir.glob('img1_*.png'))
    img2_icons = sorted(extracted_dir.glob('img2_*.png'))
    all_extracted = img1_icons + img2_icons
    
    print(f"\n📦 Found {len(all_extracted)} extracted icons")
    print(f"   From img1: {len(img1_icons)}")
    print(f"   From img2: {len(img2_icons)}")
    
    # Map icons to node types
    mapping_results = []
    
    for i, (display_name, nt_name) in enumerate(sorted_nodes):
        if i < len(all_extracted):
            source_icon = all_extracted[i]
            target_path = OUTPUT_DIR / f"{nt_name}.png"
            
            # Copy icon to target
            shutil.copy(source_icon, target_path)
            
            mapping_results.append({
                'index': i,
                'display_name': display_name,
                'nt_name': nt_name,
                'source': source_icon.name,
                'target': target_path.name,
                'success': True
            })
        else:
            # No icon available for this node type
            mapping_results.append({
                'index': i,
                'display_name': display_name,
                'nt_name': nt_name,
                'source': None,
                'target': None,
                'success': False
            })
    
    return mapping_results

def save_mapping_report(results, output_path):
    """Save detailed mapping report as JSON"""
    with open(output_path, 'w') as f:
        json.dump(results, f, indent=2)

def main():
    print("="*70)
    print("🎯 APPLYING CORRECTED ICON MAPPING")
    print("="*70)
    
    # Load node names
    print("\n📚 Loading node display names...")
    sorted_nodes = load_node_names()
    print(f"   ✅ Loaded {len(sorted_nodes)} node types (alphabetically sorted)")
    
    # Show first few for verification
    print(f"\n   First 10 in alphabetical order:")
    for i, (display_name, nt_name) in enumerate(sorted_nodes[:10]):
        print(f"      {i:3d}. {display_name:30s} → {nt_name}")
    
    # Backup existing icons
    print(f"\n💾 Backing up existing icons...")
    backup_existing_icons()
    
    # Apply mapping
    print(f"\n🔄 Mapping extracted icons to NT_* names...")
    results = apply_mapping(sorted_nodes, EXTRACTED_DIR)
    
    # Count successes
    successful = [r for r in results if r['success']]
    failed = [r for r in results if not r['success']]
    
    print(f"   ✅ Successfully mapped: {len(successful)} icons")
    if failed:
        print(f"   ⚠️  Missing icons: {len(failed)} node types")
    
    # Save report
    report_path = Path(__file__).parent / 'icon_mapping_report_corrected.json'
    save_mapping_report(results, report_path)
    print(f"\n📋 Mapping report saved: {report_path}")
    
    # Verify camera icon
    print(f"\n🔍 Verifying NT_CAM_THINLENS...")
    camera_result = next((r for r in results if r['nt_name'] == 'NT_CAM_THINLENS'), None)
    
    if camera_result and camera_result['success']:
        print(f"   ✅ Display name: '{camera_result['display_name']}'")
        print(f"   ✅ Position: {camera_result['index']}")
        print(f"   ✅ Source: {camera_result['source']}")
        print(f"   ✅ Target: {camera_result['target']}")
        
        # Create enlarged verification
        camera_path = OUTPUT_DIR / f"{camera_result['nt_name']}.png"
        if camera_path.exists():
            camera_icon = Image.open(camera_path)
            camera_large = camera_icon.resize((128, 128), Image.NEAREST)
            verify_path = Path(__file__).parent / 'camera_icon_final_verification.png'
            camera_large.save(verify_path)
            print(f"   💾 Enlarged verification: {verify_path}")
    
    # Show some examples
    print(f"\n📋 Sample mappings:")
    for result in results[104:109]:  # Around the camera icon
        marker = " ← NT_CAM_THINLENS" if result['nt_name'] == 'NT_CAM_THINLENS' else ""
        status = "✅" if result['success'] else "❌"
        print(f"   {status} {result['index']:3d}. {result['display_name']:30s} → {result['nt_name']}{marker}")
    
    print(f"""
{'='*70}
✅ MAPPING COMPLETE
{'='*70}

Summary:
  Total node types: {len(results)}
  Successfully mapped: {len(successful)}
  Missing icons: {len(failed)}

Files:
  Icon directory: {OUTPUT_DIR}
  Backup: {BACKUP_DIR}
  Report: {report_path}

Next steps:
  1. Verify camera icon looks correct: camera_icon_final_verification.png
  2. Test in application: npm run dev
  3. If icons look good, commit and push changes
""")

if __name__ == '__main__':
    main()
