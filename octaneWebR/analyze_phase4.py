#!/usr/bin/env python3
"""
Analyze cross-file duplicates for Phase 4: app.css, layout.css, octane-theme.css
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
        
        # Skip comments, empty lines, and @ rules
        if not line or line.startswith('/*') or line.startswith('*') or line.startswith('@'):
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
    
    print("🔍 Phase 4: Cross-File Layout/Theme Duplicate Analysis\n")
    print("=" * 80)
    
    # Collect rules from target files
    all_rules = []
    files = ['app.css', 'layout.css', 'octane-theme.css']
    
    for css_file in files:
        file_path = css_dir / css_file
        if file_path.exists():
            rules = extract_css_rules(file_path)
            all_rules.extend(rules)
            print(f"✓ Loaded {css_file}: {len(rules)} selectors")
        else:
            print(f"✗ Not found: {css_file}")
    
    print("\n" + "=" * 80)
    
    # Group by selector
    selector_groups = defaultdict(list)
    for rule in all_rules:
        selector_groups[rule['selector']].append(rule)
    
    # Find duplicates across files
    cross_file_dups = []
    for selector, defs in selector_groups.items():
        if len(defs) >= 2:
            # Check if they're in different files
            files_involved = set(d['file'] for d in defs)
            if len(files_involved) >= 2:
                cross_file_dups.append((selector, defs))
    
    print(f"\n📊 Found {len(cross_file_dups)} selectors with cross-file definitions\n")
    print("=" * 80)
    
    # Analyze each duplicate
    high_similarity = []
    medium_similarity = []
    low_similarity = []
    
    for selector, defs in sorted(cross_file_dups, key=lambda x: x[0]):
        # Calculate average similarity for all pairs
        similarities = []
        for i in range(len(defs)):
            for j in range(i + 1, len(defs)):
                sim = properties_similarity(defs[i]['properties'], defs[j]['properties'])
                similarities.append(sim)
        
        avg_sim = sum(similarities) / len(similarities) if similarities else 0
        
        entry = {
            'selector': selector,
            'defs': defs,
            'similarity': avg_sim
        }
        
        if avg_sim >= 0.7:
            high_similarity.append(entry)
        elif avg_sim >= 0.3:
            medium_similarity.append(entry)
        else:
            low_similarity.append(entry)
    
    # Report high similarity candidates
    print(f"\n🎯 HIGH PRIORITY: {len(high_similarity)} selectors with 70%+ similarity\n")
    for entry in high_similarity[:10]:  # Show top 10
        print(f"\n{entry['selector']} ({entry['similarity']:.0%} similar)")
        for d in entry['defs']:
            print(f"  • {d['file']}:{d['line']} ({d['prop_count']} props)")
    
    if len(high_similarity) > 10:
        print(f"\n  ... +{len(high_similarity) - 10} more high-priority candidates")
    
    # Report medium similarity
    print(f"\n\n⚠️  MEDIUM PRIORITY: {len(medium_similarity)} selectors with 30-70% similarity\n")
    for entry in medium_similarity[:5]:  # Show top 5
        print(f"{entry['selector']} ({entry['similarity']:.0%}): ", end="")
        print(", ".join(f"{d['file']}:{d['line']}" for d in entry['defs']))
    
    if len(medium_similarity) > 5:
        print(f"  ... +{len(medium_similarity) - 5} more")
    
    # Summary
    print(f"\n\n" + "=" * 80)
    print(f"SUMMARY:")
    print(f"  High similarity (70%+): {len(high_similarity)} selectors")
    print(f"  Medium similarity (30-70%): {len(medium_similarity)} selectors")
    print(f"  Low similarity (<30%): {len(low_similarity)} selectors")
    print(f"  Total cross-file duplicates: {len(cross_file_dups)} selectors")
    print("=" * 80)

if __name__ == '__main__':
    main()
