#!/usr/bin/env python3
"""
Analyze CSS files for REAL duplicates - same selector defined in multiple locations.
Ignore: multi-line selector groups, descendant selectors counted separately
"""

import re
from collections import defaultdict
from pathlib import Path

def extract_css_rules(file_path):
    """Extract CSS rules with their line numbers."""
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Pattern to match CSS rules: selector(s) { properties }
    # This handles multi-line selectors and nested braces
    rules = []
    lines = content.split('\n')
    
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        
        # Skip comments and empty lines
        if not line or line.startswith('/*') or line.startswith('*') or line.startswith('//'):
            i += 1
            continue
        
        # Check if this is a selector line (has { at end or on following lines)
        if '{' in line or (i + 1 < len(lines) and '{' in lines[i + 1]):
            # Collect the full selector (might span multiple lines)
            selector_lines = []
            start_line = i + 1  # 1-indexed for display
            
            # Collect selector lines until we hit the opening brace
            while i < len(lines) and '{' not in lines[i]:
                if lines[i].strip() and not lines[i].strip().startswith('/*'):
                    selector_lines.append(lines[i].strip())
                i += 1
            
            # Add the line with the opening brace
            if i < len(lines) and '{' in lines[i]:
                selector_part = lines[i].split('{')[0].strip()
                if selector_part:
                    selector_lines.append(selector_part)
            
            # Parse out individual selectors (comma-separated)
            full_selector = ' '.join(selector_lines)
            # Remove the opening brace and everything after
            full_selector = full_selector.split('{')[0].strip()
            
            # Split by comma to get individual selectors
            individual_selectors = [s.strip() for s in full_selector.split(',')]
            
            # Store each individual selector
            for selector in individual_selectors:
                if selector and not selector.startswith('@'):  # Skip @media, @keyframes, etc.
                    rules.append({
                        'selector': selector,
                        'line': start_line,
                        'file': file_path.name
                    })
        
        i += 1
    
    return rules

def normalize_selector(selector):
    """Normalize selector for comparison (remove extra spaces)."""
    # Normalize whitespace
    return ' '.join(selector.split())

def find_duplicates(css_files):
    """Find selectors defined in multiple places."""
    selector_locations = defaultdict(list)
    
    for css_file in css_files:
        rules = extract_css_rules(css_file)
        for rule in rules:
            normalized = normalize_selector(rule['selector'])
            selector_locations[normalized].append({
                'file': rule['file'],
                'line': rule['line']
            })
    
    # Filter to only duplicates (appears more than once)
    duplicates = {
        selector: locations 
        for selector, locations in selector_locations.items() 
        if len(locations) > 1
    }
    
    return duplicates

def main():
    css_dir = Path('/workspace/project/grpcSamples/octaneWebR/client/src/styles')
    css_files = list(css_dir.glob('*.css'))
    
    print("🔍 Analyzing CSS files for TRUE duplicates...\n")
    print(f"Files: {[f.name for f in css_files]}\n")
    
    duplicates = find_duplicates(css_files)
    
    # Sort by number of occurrences (descending)
    sorted_duplicates = sorted(
        duplicates.items(), 
        key=lambda x: len(x[1]), 
        reverse=True
    )
    
    print(f"📊 Found {len(duplicates)} selectors with multiple definitions\n")
    print("=" * 80)
    
    # Group by impact level
    high_impact = [(s, l) for s, l in sorted_duplicates if len(l) >= 5]
    medium_impact = [(s, l) for s, l in sorted_duplicates if 3 <= len(l) < 5]
    cross_file = [(s, l) for s, l in sorted_duplicates if len(set(loc['file'] for loc in l)) > 1]
    
    print(f"\n🔴 HIGH IMPACT: {len(high_impact)} selectors with 5+ definitions")
    print("=" * 80)
    for selector, locations in high_impact[:20]:  # Top 20
        print(f"\n.{selector}")
        print(f"  Occurrences: {len(locations)}")
        for loc in locations[:10]:  # Show first 10
            print(f"    → {loc['file']}:{loc['line']}")
    
    print(f"\n\n🟡 MEDIUM IMPACT: {len(medium_impact)} selectors with 3-4 definitions")
    print("=" * 80)
    for selector, locations in medium_impact[:15]:  # Top 15
        print(f"\n.{selector}")
        print(f"  Occurrences: {len(locations)}")
        for loc in locations:
            print(f"    → {loc['file']}:{loc['line']}")
    
    print(f"\n\n🔵 CROSS-FILE DUPLICATES: {len(cross_file)} selectors across multiple files")
    print("=" * 80)
    for selector, locations in cross_file[:30]:  # Top 30
        files = set(loc['file'] for loc in locations)
        if len(files) > 1:  # Only true cross-file
            print(f"\n.{selector}")
            print(f"  Files: {', '.join(sorted(files))}")
            for loc in sorted(locations, key=lambda x: x['file']):
                print(f"    → {loc['file']}:{loc['line']}")

if __name__ == '__main__':
    main()
