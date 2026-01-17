#!/usr/bin/env python3
"""
Detailed comparison for Phase 4 high-priority candidates.
"""

import re
from pathlib import Path

def extract_css_rule(file_path, selector):
    """Extract a specific CSS rule and its properties."""
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    lines = content.split('\n')
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        
        # Look for the selector
        if line.startswith(selector + ' {') or (line == selector and i + 1 < len(lines) and lines[i + 1].strip() == '{'):
            start_line = i + 1
            
            # Move to opening brace
            while i < len(lines) and '{' not in lines[i]:
                i += 1
            i += 1  # Skip opening brace
            
            # Collect properties
            properties = []
            while i < len(lines) and '}' not in lines[i]:
                prop = lines[i].strip()
                if prop and not prop.startswith('/*') and not prop.startswith('*'):
                    properties.append(prop)
                i += 1
            
            return {
                'selector': selector,
                'line': start_line,
                'properties': properties
            }
        
        i += 1
    
    return None

def compare_rules(rule1, rule2):
    """Compare two CSS rules and show differences."""
    set1 = set(rule1['properties'])
    set2 = set(rule2['properties'])
    
    common = set1 & set2
    only_in_1 = set1 - set2
    only_in_2 = set2 - set1
    
    return {
        'common': sorted(common),
        'only_in_1': sorted(only_in_1),
        'only_in_2': sorted(only_in_2)
    }

def main():
    css_dir = Path('/workspace/project/grpcSamples/octaneWebR/client/src/styles')
    
    # High-priority selector from analysis
    selector = '.callback-render-viewport'
    
    print(f"🔍 Detailed Analysis: {selector}\n")
    print("=" * 80)
    
    # Extract from both files
    app_css = css_dir / 'app.css'
    theme_css = css_dir / 'octane-theme.css'
    
    rule1 = extract_css_rule(app_css, selector)
    rule2 = extract_css_rule(theme_css, selector)
    
    if not rule1 or not rule2:
        print("❌ Could not find selector in both files")
        return
    
    print(f"\n📄 app.css:{rule1['line']} ({len(rule1['properties'])} properties)")
    for prop in rule1['properties']:
        print(f"  {prop}")
    
    print(f"\n📄 octane-theme.css:{rule2['line']} ({len(rule2['properties'])} properties)")
    for prop in rule2['properties']:
        print(f"  {prop}")
    
    # Compare
    diff = compare_rules(rule1, rule2)
    
    print(f"\n\n📊 COMPARISON:")
    print(f"  Common properties: {len(diff['common'])}")
    for prop in diff['common']:
        print(f"    ✓ {prop}")
    
    if diff['only_in_1']:
        print(f"\n  Only in app.css: {len(diff['only_in_1'])}")
        for prop in diff['only_in_1']:
            print(f"    • {prop}")
    
    if diff['only_in_2']:
        print(f"\n  Only in octane-theme.css: {len(diff['only_in_2'])}")
        for prop in diff['only_in_2']:
            print(f"    + {prop}")
    
    # Recommendation
    print(f"\n\n💡 RECOMMENDATION:")
    if not diff['only_in_1']:
        print("  ✅ SAFE TO CONSOLIDATE")
        print("  → Remove app.css version (octane-theme.css is superset)")
    elif not diff['only_in_2']:
        print("  ✅ SAFE TO CONSOLIDATE")
        print("  → Remove octane-theme.css version (app.css is superset)")
    else:
        print("  ⚠️  PROPERTIES DIFFER")
        print("  → Merge into octane-theme.css (canonical theme file)")
        print(f"  → Add missing properties from app.css to octane-theme.css")
        print(f"  → Then remove app.css version")
    
    print("=" * 80)

if __name__ == '__main__':
    main()
