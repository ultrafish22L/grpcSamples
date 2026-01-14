#!/usr/bin/env python3
"""
Extract display names from NodeTypes.ts - this is what octaneWebR uses!
No API calls needed - the correct names are already in the TypeScript file.
"""

import sys
import json
import re
sys.path.insert(0, '../octaneProxy/generated')
import octaneids_pb2

def extract_from_typescript():
    """Extract NT_* → display name mapping from NodeTypes.ts"""
    
    print("=" * 70)
    print("🎨 EXTRACT DISPLAY NAMES FROM NODETYPES.TS")
    print("=" * 70)
    print("\n📋 This is what octaneWebR uses - the CORRECT names!\n")
    
    # Read NodeTypes.ts
    ts_file = 'client/src/constants/NodeTypes.ts'
    print(f"📖 Reading {ts_file}...")
    
    with open(ts_file, 'r') as f:
        content = f.read()
    
    print(f"✅ Loaded {len(content)} characters\n")
    
    # Extract all NT_* entries with their display names
    # Pattern: 'NT_SOMETHING': { name: 'Display Name', color: '...' }
    pattern = r"'(NT_[A-Z_0-9]+)':\s*\{\s*name:\s*'([^']+)'"
    
    matches = re.findall(pattern, content)
    
    print(f"🔍 Found {len(matches)} NT_* entries\n")
    
    # Create mapping
    mapping = {}
    for nt_name, display_name in matches:
        # Get the ID from octaneids_pb2
        if hasattr(octaneids_pb2, nt_name):
            nt_id = getattr(octaneids_pb2, nt_name)
            mapping[nt_name] = {
                'id': nt_id,
                'displayName': display_name,
                'enumName': nt_name
            }
        else:
            print(f"⚠️  {nt_name} not found in octaneids_pb2")
    
    print(f"✅ Created mapping for {len(mapping)} nodes\n")
    
    # Show samples
    print("📋 Sample display names:")
    samples = list(mapping.items())[:20]
    for nt_name, info in samples:
        print(f"   {nt_name:40} → '{info['displayName']}'")
    
    # Save
    output_file = 'client/public/icons/nodes/node-display-names-FROM-TS.json'
    with open(output_file, 'w') as f:
        json.dump(mapping, f, indent=2)
    
    print(f"\n✅ Saved to: {output_file}")
    print(f"📁 Total: {len(mapping)} nodes")
    
    # Create sorted order (for icon extraction)
    sorted_nodes = sorted(mapping.items(), key=lambda x: x[1]['displayName'].lower())
    
    print(f"\n📋 First 20 nodes sorted by display name:")
    for i, (nt_name, info) in enumerate(sorted_nodes[:20]):
        print(f"  [{i:3}] {info['displayName']:40} ← {nt_name}")
    
    # Save sorted order
    sorted_order = [nt for nt, _ in sorted_nodes]
    order_file = 'client/public/icons/nodes/sorted-order-by-display-name.json'
    with open(order_file, 'w') as f:
        json.dump(sorted_order, f, indent=2)
    
    print(f"\n✅ Sorted order saved to: {order_file}")
    
    return mapping

def main():
    mapping = extract_from_typescript()
    
    if mapping and len(mapping) > 700:
        print(f"\n🎉 SUCCESS! Extracted {len(mapping)} display names from NodeTypes.ts")
        print(f"\n📝 These are the EXACT names octaneWebR uses")
        print(f"📝 No API calls needed - no crashes!")
        return 0
    else:
        print("\n⚠️  Incomplete extraction")
        return 1

if __name__ == '__main__':
    sys.exit(main())
