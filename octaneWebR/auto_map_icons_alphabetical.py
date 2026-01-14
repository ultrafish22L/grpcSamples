#!/usr/bin/env python3
"""
Automatically map extracted icons to node types assuming alphabetical order.
The Octane "All items" menu appears to show nodes in alphabetical order by display name.
"""

from pathlib import Path
import json
import re
import shutil

# Paths
NODETYPE_MAPPING_FILE = Path(__file__).parent / 'client' / 'src' / 'constants' / 'NodeTypes.ts'
EXTRACTED_ICONS_DIR = Path(__file__).parent / 'extracted_icons'
OUTPUT_ICONS_DIR = Path(__file__).parent / 'client' / 'public' / 'icons' / 'nodes'
METADATA_FILE = EXTRACTED_ICONS_DIR / 'extraction_metadata.json'

def load_node_type_definitions():
    """Load all node types from NodeTypes.ts"""
    with open(NODETYPE_MAPPING_FILE, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Pattern: 'NT_SOMETHING': { name: 'Display Name', color: '#HEX' }
    pattern = r"'(NT_[A-Z_0-9]+)':\s*{\s*name:\s*'([^']+)'"
    
    node_types = []
    for match in re.finditer(pattern, content):
        enum_name = match.group(1)
        display_name = match.group(2)
        node_types.append({
            'enum': enum_name,
            'name': display_name,
            'sort_key': display_name.lower()
        })
    
    # Sort by display name (case-insensitive)
    node_types.sort(key=lambda x: x['sort_key'])
    
    return node_types

def load_extraction_metadata():
    """Load metadata about extracted icons"""
    with open(METADATA_FILE, 'r') as f:
        metadata = json.load(f)
    
    # Sort by source and index to maintain extraction order
    metadata.sort(key=lambda x: (x['source'], x['row'], x['col']))
    
    return metadata

def create_mapping(node_types, extracted_icons):
    """
    Map extracted icons to node types.
    Assumes both are in alphabetical order.
    """
    mapping = []
    
    # Map first N icons to first N node types
    num_to_map = min(len(node_types), len(extracted_icons))
    
    print(f"Node types defined: {len(node_types)}")
    print(f"Icons extracted: {len(extracted_icons)}")
    print(f"Will map: {num_to_map} icons")
    
    for i in range(num_to_map):
        node = node_types[i]
        icon = extracted_icons[i]
        
        mapping.append({
            'extracted_file': icon['file'],
            'node_enum': node['enum'],
            'node_name': node['name'],
            'source': icon['source'],
            'position': f"row={icon['row']}, col={icon['col']}"
        })
    
    return mapping

def apply_mapping(mapping, dry_run=True):
    """
    Copy extracted icons to the output directory with correct NT_* names.
    """
    print(f"\n{'='*70}")
    print(f"{'🔍 DRY RUN' if dry_run else '✅ APPLYING MAPPING'}")
    print(f"{'='*70}\n")
    
    success_count = 0
    error_count = 0
    
    for item in mapping:
        src_path = EXTRACTED_ICONS_DIR / item['extracted_file']
        dst_path = OUTPUT_ICONS_DIR / f"{item['node_enum']}.png"
        
        if not src_path.exists():
            print(f"❌ Source not found: {src_path.name}")
            error_count += 1
            continue
        
        if dry_run:
            print(f"Would copy: {src_path.name} → {dst_path.name}")
            print(f"  Node: {item['node_name']} ({item['node_enum']})")
        else:
            try:
                shutil.copy2(src_path, dst_path)
                print(f"✅ {dst_path.name} ← {item['node_name']}")
                success_count += 1
            except Exception as e:
                print(f"❌ Error copying {src_path.name}: {e}")
                error_count += 1
    
    print(f"\n{'='*70}")
    if dry_run:
        print(f"DRY RUN COMPLETE - {len(mapping)} mappings prepared")
        print(f"{'='*70}")
        print(f"\nTo apply this mapping, run:")
        print(f"  python3 {Path(__file__).name} --apply")
    else:
        print(f"MAPPING APPLIED: {success_count} success, {error_count} errors")
        print(f"{'='*70}")
    
    return success_count, error_count

def save_mapping_report(mapping, output_file='icon_mapping_report.json'):
    """Save the mapping to a JSON file for reference"""
    output_path = Path(__file__).parent / output_file
    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(mapping, f, indent=2)
    print(f"\n📄 Mapping report saved: {output_path}")

def main():
    import sys
    
    print("="*70)
    print("🗺️  AUTOMATIC ICON MAPPING (ALPHABETICAL)")
    print("="*70)
    
    # Load node type definitions
    print("\n📚 Loading node type definitions...")
    node_types = load_node_type_definitions()
    print(f"   ✅ Loaded {len(node_types)} node types")
    
    # Show first 10 for verification
    print("\n   First 10 node types (alphabetically):")
    for i in range(min(10, len(node_types))):
        print(f"      {i+1}. {node_types[i]['name']} ({node_types[i]['enum']})")
    
    # Load extraction metadata
    print("\n📁 Loading extracted icons...")
    extracted_icons = load_extraction_metadata()
    print(f"   ✅ Loaded {len(extracted_icons)} extracted icons")
    
    # Create mapping
    print("\n🔗 Creating mapping...")
    mapping = create_mapping(node_types, extracted_icons)
    
    # Save mapping report
    save_mapping_report(mapping)
    
    # Apply mapping (dry run by default)
    apply_for_real = '--apply' in sys.argv or '--yes' in sys.argv
    apply_mapping(mapping, dry_run=not apply_for_real)
    
    if not apply_for_real:
        print("\n⚠️  NOTE: This was a DRY RUN - no files were copied")
        print("⚠️  Review the mapping report and first 10 examples above")
        print("⚠️  If the mapping looks correct, run with --apply flag")
        print(f"\n💡 Command: python3 {Path(__file__).name} --apply")

if __name__ == '__main__':
    main()
