#!/usr/bin/env python3
"""
Find CSS selectors where the PROPERTIES are identical or nearly identical.
These are true candidates for consolidation.
"""

import re
from collections import defaultdict
from pathlib import Path

def extract_css_rules_with_properties(file_path):
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
                    # Normalize properties (sort and dedupe)
                    norm_props = sorted(set(properties))
                    rules.append({
                        'selector': selector,
                        'line': start_line,
                        'file': file_path.name,
                        'properties': norm_props,
                        'prop_count': len(norm_props)
                    })
        else:
            i += 1
    
    return rules

def normalize_properties(props):
    """Normalize property list for comparison."""
    # Sort and create a signature
    return tuple(sorted(props))

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
    css_file = css_dir / 'components.css'
    
    print("🔍 Finding IDENTICAL duplicates in components.css...\n")
    
    rules = extract_css_rules_with_properties(css_file)
    
    # Group by selector
    selector_groups = defaultdict(list)
    for rule in rules:
        selector_groups[rule['selector']].append(rule)
    
    # Find selectors with multiple definitions
    duplicates = {sel: rules for sel, rules in selector_groups.items() if len(rules) > 1}
    
    print(f"Found {len(duplicates)} selectors with multiple definitions\n")
    print("=" * 80)
    
    # Analyze each duplicate group
    identical = []
    similar = []
    contextual = []
    
    for selector, defs in sorted(duplicates.items()):
        if len(defs) < 2:
            continue
        
        # Compare first two definitions
        props1 = set(defs[0]['properties'])
        props2 = set(defs[1]['properties'])
        
        similarity = properties_similarity(defs[0]['properties'], defs[1]['properties'])
        
        if similarity == 1.0:
            identical.append((selector, defs))
        elif similarity >= 0.7:
            similar.append((selector, defs, similarity))
        else:
            contextual.append((selector, defs, similarity))
    
    print(f"\n✅ IDENTICAL DUPLICATES: {len(identical)}")
    print("These can be safely removed - properties are 100% identical")
    print("=" * 80)
    for selector, defs in identical[:10]:
        print(f"\n{selector}")
        print(f"  Occurrences: {len(defs)}")
        for d in defs:
            print(f"    → {d['file']}:{d['line']} ({d['prop_count']} properties)")
    
    print(f"\n\n⚠️  SIMILAR DUPLICATES: {len(similar)}")
    print("These share 70%+ properties - candidates for consolidation")
    print("=" * 80)
    for selector, defs, sim in similar[:10]:
        print(f"\n{selector} (similarity: {sim:.0%})")
        print(f"  Occurrences: {len(defs)}")
        for d in defs:
            print(f"    → {d['file']}:{d['line']} ({d['prop_count']} properties)")
    
    print(f"\n\n📋 CONTEXTUAL VARIATIONS: {len(contextual)}")
    print("These are likely intentional variations for different contexts")
    print("(showing first 5)")
    print("=" * 80)
    for selector, defs, sim in contextual[:5]:
        print(f"\n{selector} (similarity: {sim:.0%})")
        print(f"  Occurrences: {len(defs)}")
        for d in defs[:3]:
            print(f"    → {d['file']}:{d['line']} ({d['prop_count']} properties)")

if __name__ == '__main__':
    main()
