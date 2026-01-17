#!/usr/bin/env python3
"""
Comprehensive CSS Usage Analyzer
Finds ALL unused CSS selectors in octaneWebR
"""

import re
import os
from pathlib import Path
from collections import defaultdict

# Paths
CSS_DIR = Path("client/src/styles")
SRC_DIR = Path("client/src")

# CSS files to analyze
CSS_FILES = [
    "app.css",
    "components.css",
    "layout.css",
    "octane-theme.css",
    "variables.css"
]

def extract_class_selectors(css_content):
    """Extract all class selectors from CSS content"""
    # Match class selectors: .class-name
    pattern = r'\.([a-zA-Z0-9_-]+)'
    selectors = re.findall(pattern, css_content)
    return set(selectors)

def check_usage_in_codebase(class_name, src_dir):
    """Check if a class name appears in any TS/TSX files"""
    # Search for className="class-name" or className='class-name' or className={`...class-name...`}
    cmd = f'grep -r "{class_name}" {src_dir} --include="*.ts" --include="*.tsx" 2>/dev/null'
    result = os.system(cmd)
    return result == 0  # 0 = found, non-zero = not found

def analyze_css_file(css_file):
    """Analyze a single CSS file for unused selectors"""
    file_path = CSS_DIR / css_file
    
    if not file_path.exists():
        return None
    
    with open(file_path, 'r') as f:
        content = f.read()
    
    selectors = extract_class_selectors(content)
    
    # Special cases to skip (pseudo-classes, states, generic terms)
    skip_patterns = [
        'hover', 'active', 'focus', 'disabled', 'selected', 'collapsed',
        'visible', 'hidden', 'open', 'closed', 'expanded',
        'before', 'after', 'first', 'last', 'child', 'even', 'odd',
        # Common framework/library classes that might be dynamically applied
        'react', 'vite', 'js', 'ts', 'tsx'
    ]
    
    unused = []
    used = []
    skipped = []
    
    for selector in sorted(selectors):
        # Skip pseudo-class suffixes and generic states
        if any(skip in selector.lower() for skip in skip_patterns):
            skipped.append(selector)
            continue
        
        # Check if used in codebase
        if not check_usage_in_codebase(selector, SRC_DIR):
            unused.append(selector)
        else:
            used.append(selector)
    
    return {
        'file': css_file,
        'total': len(selectors),
        'unused': unused,
        'used': used,
        'skipped': skipped
    }

def main():
    print("=" * 80)
    print("COMPREHENSIVE CSS USAGE ANALYSIS")
    print("=" * 80)
    print()
    
    all_results = {}
    total_unused = 0
    
    for css_file in CSS_FILES:
        print(f"Analyzing {css_file}...")
        result = analyze_css_file(css_file)
        
        if result:
            all_results[css_file] = result
            total_unused += len(result['unused'])
            print(f"  ✓ {len(result['used'])} used")
            print(f"  ✗ {len(result['unused'])} unused")
            print(f"  ⊘ {len(result['skipped'])} skipped (pseudo/states)")
        else:
            print(f"  ! File not found")
        print()
    
    # Print detailed report
    print("=" * 80)
    print("DETAILED UNUSED SELECTORS REPORT")
    print("=" * 80)
    print()
    
    for css_file, result in all_results.items():
        if result['unused']:
            print(f"\n### {css_file} - {len(result['unused'])} UNUSED SELECTORS ###")
            print("-" * 80)
            for selector in result['unused']:
                print(f"  .{selector}")
    
    print()
    print("=" * 80)
    print(f"TOTAL UNUSED SELECTORS: {total_unused}")
    print("=" * 80)
    
    # Save detailed report
    with open('UNUSED_CSS_FULL_REPORT.txt', 'w') as f:
        f.write("COMPREHENSIVE CSS USAGE ANALYSIS\n")
        f.write("=" * 80 + "\n\n")
        
        for css_file, result in all_results.items():
            f.write(f"\n{css_file}\n")
            f.write("-" * 80 + "\n")
            f.write(f"Total selectors: {result['total']}\n")
            f.write(f"Used: {len(result['used'])}\n")
            f.write(f"Unused: {len(result['unused'])}\n")
            f.write(f"Skipped: {len(result['skipped'])}\n\n")
            
            if result['unused']:
                f.write("UNUSED SELECTORS:\n")
                for selector in result['unused']:
                    f.write(f"  .{selector}\n")
                f.write("\n")
        
        f.write(f"\nTOTAL UNUSED: {total_unused}\n")
    
    print("\nDetailed report saved to: UNUSED_CSS_FULL_REPORT.txt")

if __name__ == "__main__":
    main()
