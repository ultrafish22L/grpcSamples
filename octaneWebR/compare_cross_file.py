#!/usr/bin/env python3
"""
Compare specific CSS selectors across multiple files to find true duplicates.
"""

import re
from pathlib import Path
from collections import defaultdict

def extract_css_rules(file_path):
    """Extract CSS rules with their complete property sets."""
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    rules = []
    lines = content.split('\n')
    
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        
        # Skip comments and empty lines
        if not line or line.startswith('/*') or line.startswith('*'):
            i += 1
            continue
        
        # Check if this line contains a selector
        if '{' in line or (i + 1 < len(lines) and '{' in lines[i + 1]):
            # Collect the full selector
            selector_lines = []
            start_line = i + 1  # 1-indexed
            
            while i < len(lines) and '{' not in lines[i]:
                if lines[i].strip() and not lines[i].strip().startswith('/*'):
                    selector_lines.append(lines[i].strip())
                i += 1
            
            # Add the line with opening brace
            if i < len(lines) and '{' in lines[i]:
                selector_part = lines[i].split('{')[0].strip()
                if selector_part:
                    selector_lines.append(selector_part)
                i += 1  # Move past opening brace
            
            # Collect properties until closing brace
            properties = []
            while i < len(lines) and '}' not in lines[i]:
                prop_line = lines[i].strip()
                if prop_line and not prop_line.startswith('/*') and not prop_line.startswith('*'):
                    # Remove comments from property lines
                    prop_line = re.sub(r'/\*.*?\*/', '', prop_line).strip()
                    if prop_line:
                        properties.append(prop_line)
                i += 1
            
            # Skip closing brace
            if i < len(lines) and '}' in lines[i]:
                i += 1
            
            # Parse selectors
            full_selector = ' '.join(selector_lines).split('{')[0].strip()
            individual_selectors = [s.strip() for s in full_selector.split(',')]
            
            # Store each selector with its properties
            for selector in individual_selectors:
                if selector and not selector.startswith('@'):
                    rules.append({
                        'selector': selector,
                        'line': start_line,
                        'file': file_path.name,
                        'properties': properties,
                        'prop_count': len(properties)
                    })
        else:
            i += 1
    
    return rules

def properties_similarity(props1, props2):
    """Calculate similarity between two property sets (0-1)."""
    set1 = set(props1)
    set2 = set(props2)
    if not set1 and not set2:
        return 1.0
    intersection = len(set1 & set2)
    union = len(set1 | set2)
    return intersection / union if union > 0 else 0

def main():
    css_dir = Path('/workspace/project/grpcSamples/octaneWebR/client/src/styles')
    
    # Target selectors from Phase 2
    target_selectors = [
        '.parameter-label',
        '.parameter-row',
        '.parameter-control',
        '.parameter-slider',
        '.parameter-slider-track',
        '.parameter-slider-thumb',
        '.parameter-slider-thumb:active',
        '.parameter-slider-thumb:hover',
    ]
    
    print("🔍 Cross-File Duplicate Analysis for Phase 2\n")
    print("=" * 80)
    
    # Collect rules from both files
    all_rules = []
    for css_file in ['components.css', 'layout.css']:
        file_path = css_dir / css_file
        rules = extract_css_rules(file_path)
        all_rules.extend(rules)
    
    # Group by selector
    selector_groups = defaultdict(list)
    for rule in all_rules:
        if rule['selector'] in target_selectors:
            selector_groups[rule['selector']].append(rule)
    
    # Analyze each selector
    for selector in target_selectors:
        defs = selector_groups.get(selector, [])
        if len(defs) < 2:
            continue
        
        print(f"\n{selector}")
        print(f"  Occurrences: {len(defs)}")
        
        # Show all definitions
        for i, d in enumerate(defs):
            print(f"\n  Definition {i+1}: {d['file']}:{d['line']} ({d['prop_count']} properties)")
            for prop in d['properties'][:8]:  # Show first 8 props
                print(f"    {prop}")
            if d['prop_count'] > 8:
                print(f"    ... +{d['prop_count'] - 8} more")
        
        # Compare similarities
        if len(defs) == 2:
            sim = properties_similarity(defs[0]['properties'], defs[1]['properties'])
            print(f"\n  Similarity: {sim:.0%}")
            if sim >= 0.7:
                print(f"  ✅ CONSOLIDATION CANDIDATE")
            elif sim >= 0.3:
                print(f"  ⚠️  PARTIAL OVERLAP - review manually")
            else:
                print(f"  ❌ CONTEXTUAL VARIATION - keep both")
        
        print("-" * 80)

if __name__ == '__main__':
    main()
