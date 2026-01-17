#!/usr/bin/env python3
"""
Comprehensive CSS Unused Selector Analysis
Searches all CSS files and verifies usage in TypeScript files
"""

import re
import subprocess
from pathlib import Path
from collections import defaultdict

CSS_DIR = Path("client/src/styles")
TS_DIR = Path("client/src")

def extract_class_selectors_from_file(css_file):
    """Extract all class selectors from a CSS file with line numbers"""
    selectors = []
    
    with open(css_file, 'r') as f:
        lines = f.readlines()
    
    for line_num, line in enumerate(lines, 1):
        # Match class selectors like .classname
        # Exclude pseudo-classes and pseudo-elements
        pattern = r'\.([a-zA-Z0-9_-]+)(?![:\w-])'
        matches = re.findall(pattern, line)
        
        for match in matches:
            selectors.append({
                'name': match,
                'file': css_file.name,
                'line': line_num
            })
    
    return selectors

def check_usage_in_ts(class_name):
    """Check if class is used in TS/TSX files"""
    try:
        result = subprocess.run(
            ['grep', '-r', class_name, str(TS_DIR), '--include=*.tsx', '--include=*.ts'],
            capture_output=True,
            text=True
        )
        return result.returncode == 0, result.stdout
    except:
        return False, ""

def get_parent_pattern(class_name):
    """Extract parent pattern from class name"""
    # Examples:
    # 'category-arrow' -> 'category-'
    # 'node-graph-tool' -> 'node-graph-'
    # 'btn-primary' -> 'btn-'
    
    parts = class_name.split('-')
    if len(parts) > 1:
        # Return all but last part
        return '-'.join(parts[:-1]) + '-'
    return None

def main():
    # Get all CSS files
    css_files = sorted(CSS_DIR.glob("*.css"))
    
    print("=" * 80)
    print("COMPREHENSIVE CSS UNUSED SELECTOR ANALYSIS")
    print("=" * 80)
    print(f"Analyzing CSS files in: {CSS_DIR}")
    print(f"Searching TypeScript files in: {TS_DIR}")
    print()
    
    all_selectors = []
    for css_file in css_files:
        print(f"📄 Extracting selectors from {css_file.name}...")
        selectors = extract_class_selectors_from_file(css_file)
        all_selectors.extend(selectors)
    
    # Get unique selector names
    unique_selectors = {}
    for sel in all_selectors:
        name = sel['name']
        if name not in unique_selectors:
            unique_selectors[name] = []
        unique_selectors[name].append(sel)
    
    print(f"\n✓ Found {len(all_selectors)} total class selector occurrences")
    print(f"✓ Found {len(unique_selectors)} unique class selectors")
    print()
    print("=" * 80)
    print("CHECKING USAGE IN TYPESCRIPT FILES")
    print("=" * 80)
    
    used = {}
    unused = {}
    parent_check_needed = {}
    
    total = len(unique_selectors)
    for idx, (selector, occurrences) in enumerate(sorted(unique_selectors.items()), 1):
        if idx % 10 == 0 or idx == total:
            print(f"Progress: {idx}/{total} selectors checked...", end='\r')
        
        is_used, usage_output = check_usage_in_ts(selector)
        
        if is_used:
            used[selector] = occurrences
        else:
            # Not found directly, might need parent check
            parent = get_parent_pattern(selector)
            if parent:
                parent_check_needed[selector] = {
                    'occurrences': occurrences,
                    'parent': parent
                }
            else:
                unused[selector] = occurrences
    
    print("\n")
    print("=" * 80)
    print("PARENT PATTERN VERIFICATION")
    print("=" * 80)
    
    # Check parent patterns
    confirmed_unused = {}
    for selector, data in parent_check_needed.items():
        parent = data['parent']
        is_parent_used, _ = check_usage_in_ts(parent)
        
        if is_parent_used:
            # Parent pattern found, might be used
            used[selector] = data['occurrences']
            print(f"✓ {selector:40s} - parent pattern '{parent}' found")
        else:
            # Parent not found either, definitely unused
            confirmed_unused[selector] = data['occurrences']
            print(f"✗ {selector:40s} - parent pattern '{parent}' NOT found")
    
    # Merge confirmed unused
    unused.update(confirmed_unused)
    
    print("\n")
    print("=" * 80)
    print("RESULTS SUMMARY")
    print("=" * 80)
    print(f"Total unique selectors: {len(unique_selectors)}")
    print(f"✓ Used selectors: {len(used)}")
    print(f"✗ UNUSED selectors: {len(unused)}")
    print()
    
    # Generate detailed report
    print("=" * 80)
    print("UNUSED SELECTORS BY FILE")
    print("=" * 80)
    print()
    
    # Group by file
    by_file = defaultdict(list)
    for selector, occurrences in sorted(unused.items()):
        for occ in occurrences:
            by_file[occ['file']].append({
                'selector': selector,
                'line': occ['line']
            })
    
    total_unused_count = 0
    for css_file in sorted(by_file.keys()):
        selectors_in_file = by_file[css_file]
        print(f"\n📄 {css_file} ({len(selectors_in_file)} unused selectors)")
        print("-" * 80)
        
        for item in sorted(selectors_in_file, key=lambda x: x['line']):
            selector = item['selector']
            line = item['line']
            count = len([o for o in unused[selector] if o['file'] == css_file])
            print(f"  Line {line:4d}: .{selector:40s} ({count} occurrence(s))")
            total_unused_count += count
    
    # Save detailed report
    with open('UNUSED_CSS_FULL_REPORT.txt', 'w') as f:
        f.write("COMPREHENSIVE UNUSED CSS SELECTOR REPORT\n")
        f.write("=" * 80 + "\n\n")
        f.write(f"Total unique selectors analyzed: {len(unique_selectors)}\n")
        f.write(f"Used selectors: {len(used)}\n")
        f.write(f"UNUSED selectors: {len(unused)}\n")
        f.write(f"Total unused occurrences: {total_unused_count}\n\n")
        
        f.write("=" * 80 + "\n")
        f.write("UNUSED SELECTORS BY FILE\n")
        f.write("=" * 80 + "\n\n")
        
        for css_file in sorted(by_file.keys()):
            selectors_in_file = by_file[css_file]
            f.write(f"\n{css_file} ({len(selectors_in_file)} unused selectors)\n")
            f.write("-" * 80 + "\n")
            
            for item in sorted(selectors_in_file, key=lambda x: x['line']):
                selector = item['selector']
                line = item['line']
                count = len([o for o in unused[selector] if o['file'] == css_file])
                f.write(f"  Line {line:4d}: .{selector:40s} ({count} occurrence(s))\n")
        
        f.write("\n\n" + "=" * 80 + "\n")
        f.write("ALPHABETICAL LIST OF UNUSED SELECTORS\n")
        f.write("=" * 80 + "\n\n")
        
        for selector in sorted(unused.keys()):
            occurrences = unused[selector]
            files = set(o['file'] for o in occurrences)
            f.write(f".{selector}\n")
            for file in sorted(files):
                lines = [o['line'] for o in occurrences if o['file'] == file]
                f.write(f"  {file}: lines {', '.join(map(str, sorted(lines)))}\n")
    
    print("\n\n" + "=" * 80)
    print("ALPHABETICAL LIST OF ALL UNUSED SELECTORS")
    print("=" * 80)
    print()
    for selector in sorted(unused.keys()):
        occurrences = unused[selector]
        total_occ = len(occurrences)
        files = set(o['file'] for o in occurrences)
        print(f".{selector:45s} ({total_occ} occ in {len(files)} file(s))")
    
    print("\n" + "=" * 80)
    print(f"📄 Detailed report saved to: UNUSED_CSS_FULL_REPORT.txt")
    print("=" * 80)

if __name__ == "__main__":
    main()
