#!/usr/bin/env python3
"""
Find unused CSS selectors by checking if they appear in TypeScript/TSX files.
CONSERVATIVE: Only flag selectors that are clearly unused.
"""

import re
import subprocess
from pathlib import Path
from collections import defaultdict

def extract_css_selectors(css_dir):
    """Extract all CSS selectors from CSS files."""
    selectors = defaultdict(list)  # selector -> [(file, line)]
    
    for css_file in css_dir.glob('*.css'):
        with open(css_file, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            for i, line in enumerate(lines, 1):
                line = line.strip()
                # Match CSS selectors at start of line
                if line and not line.startswith('/*') and not line.startswith('*') and not line.startswith('@'):
                    # Extract selector before opening brace or comma
                    if '{' in line:
                        selector_part = line.split('{')[0].strip()
                    elif i < len(lines) and '{' in lines[i]:
                        selector_part = line.strip()
                    else:
                        continue
                    
                    # Split multiple selectors
                    for sel in selector_part.split(','):
                        sel = sel.strip()
                        if sel and sel.startswith('.'):
                            # Extract just the class name (before space, :, ., [, etc.)
                            class_match = re.match(r'\.([\w-]+)', sel)
                            if class_match:
                                class_name = class_match.group(1)
                                selectors[class_name].append((css_file.name, i))
    
    return selectors

def check_usage_in_code(class_name, src_dir):
    """Check if a CSS class is used in TypeScript/TSX files."""
    try:
        # Search for the class name in quotes or className assignments
        # Look for: className="xxx", className={`xxx`, "xxx", 'xxx'
        patterns = [
            f'className.*{class_name}',  # className with class
            f'"{class_name}"',            # Double quotes
            f"'{class_name}'",            # Single quotes
            f'`{class_name}`',            # Backticks
        ]
        
        for pattern in patterns:
            result = subprocess.run(
                ['grep', '-r', '-l', '--include=*.tsx', '--include=*.ts', pattern, str(src_dir)],
                capture_output=True,
                text=True
            )
            if result.returncode == 0 and result.stdout.strip():
                return True, result.stdout.strip().split('\n')
        
        return False, []
    except Exception as e:
        print(f"Error checking {class_name}: {e}")
        return False, []

def main():
    base_dir = Path('/workspace/project/grpcSamples/octaneWebR')
    css_dir = base_dir / 'client/src/styles'
    src_dir = base_dir / 'client/src'
    
    print("🔍 CSS Unused Selector Detection\n")
    print("=" * 80)
    
    # Extract all CSS selectors
    print("📋 Extracting CSS selectors...")
    selectors = extract_css_selectors(css_dir)
    print(f"Found {len(selectors)} unique class selectors\n")
    
    # Focus on specific prefixes first
    target_prefixes = ['scene-node-', 'scene-tree-', 'scene-mesh-', 'scene-search-']
    
    print("🎯 Checking 'scene-' related selectors for usage...\n")
    print("=" * 80)
    
    unused_selectors = []
    used_selectors = []
    
    for class_name in sorted(selectors.keys()):
        # Check if it matches our target prefixes
        if any(class_name.startswith(prefix) for prefix in target_prefixes):
            used, files = check_usage_in_code(class_name, src_dir)
            
            locations = selectors[class_name]
            location_str = f"{locations[0][0]}:{locations[0][1]}"
            if len(locations) > 1:
                location_str += f" (+{len(locations)-1} more)"
            
            if not used:
                unused_selectors.append((class_name, location_str))
                print(f"❌ UNUSED: .{class_name}")
                print(f"   Location: {location_str}")
                print()
            else:
                used_selectors.append(class_name)
    
    # Summary
    print("\n" + "=" * 80)
    print("📊 SUMMARY:\n")
    print(f"✅ Used selectors: {len(used_selectors)}")
    print(f"❌ Unused selectors: {len(unused_selectors)}")
    
    if unused_selectors:
        print(f"\n🗑️  SAFE TO REMOVE:\n")
        for class_name, location in unused_selectors:
            print(f"  • .{class_name} ({location})")
    
    print("\n" + "=" * 80)
    print("⚠️  RECOMMENDATION:")
    print("Review unused selectors manually before removing.")
    print("Some may be used in dynamic class generation or external templates.")
    print("=" * 80)

if __name__ == '__main__':
    main()
