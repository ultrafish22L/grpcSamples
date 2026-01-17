#!/usr/bin/env python3
"""
Filter out false positives from unused CSS analysis
Removes timing values, numeric values, etc.
"""

import re

def is_valid_class_selector(name):
    """Check if this is a real class selector, not a timing/numeric value"""
    # Exclude timing values
    if re.match(r'^\d+(\.\d+)?s$', name):  # e.g., .15s, .2s, .3s
        return False
    if re.match(r'^\d+(\.\d+)?ms$', name):  # e.g., .01ms
        return False
    # Exclude numeric values
    if re.match(r'^\d+(\.\d+)?$', name):  # e.g., .053, .042
        return False
    # Exclude CSS units
    if re.match(r'^\d+(\.\d+)?(rem|em|px|vh|vw|%)$', name):  # e.g., .5rem
        return False
    # Exclude single letters/numbers
    if re.match(r'^[a-z]\d+$', name):  # e.g., .w3
        return False
    
    return True

# Read the report
with open('UNUSED_CSS_FULL_REPORT.txt', 'r') as f:
    content = f.read()

# Extract all unused selectors from alphabetical list
lines = content.split('\n')
in_alphabetical = False
unused = []

for line in lines:
    if 'ALPHABETICAL LIST OF ALL UNUSED SELECTORS' in line:
        in_alphabetical = True
        continue
    if in_alphabetical and line.startswith('.'):
        # Extract selector name
        match = re.match(r'^\.([a-zA-Z0-9_-]+)', line)
        if match:
            selector = match.group(1)
            if is_valid_class_selector(selector):
                # Extract occurrence count
                occ_match = re.search(r'\((\d+) occ', line)
                if occ_match:
                    count = int(occ_match.group(1))
                    unused.append((selector, count))

print("=" * 80)
print("FILTERED UNUSED CSS SELECTORS (Real Class Names Only)")
print("=" * 80)
print(f"Total real unused selectors: {len(unused)}")
print()

# Group by likely category
categories = {
    'Loading/Progress': [],
    'Parameters': [],
    'Node Graph': [],
    'Scene Outliner': [],
    'Viewport': [],
    'Sections': [],
    'Drop Indicators': [],
    'Other': []
}

for selector, count in unused:
    if 'loading' in selector or 'progress' in selector or 'spinner' in selector:
        categories['Loading/Progress'].append((selector, count))
    elif 'parameter' in selector or 'param-' in selector:
        categories['Parameters'].append((selector, count))
    elif 'node-' in selector or 'pin-' in selector:
        categories['Node Graph'].append((selector, count))
    elif 'scene-' in selector or 'tree-' in selector:
        categories['Scene Outliner'].append((selector, count))
    elif 'render-' in selector or 'preview-' in selector or 'playback' in selector:
        categories['Viewport'].append((selector, count))
    elif 'section' in selector or 'subsection' in selector:
        categories['Sections'].append((selector, count))
    elif 'drop-' in selector:
        categories['Drop Indicators'].append((selector, count))
    else:
        categories['Other'].append((selector, count))

for category, items in categories.items():
    if items:
        print(f"\n{category} ({len(items)} selectors)")
        print("-" * 80)
        for selector, count in sorted(items):
            print(f"  .{selector:50s} ({count} occurrences)")

# Total count
total_occ = sum(count for _, count in unused)
print(f"\n{'=' * 80}")
print(f"Total: {len(unused)} unused selectors, {total_occ} total occurrences")
print(f"{'=' * 80}")

# Save filtered list
with open('UNUSED_CSS_FILTERED.txt', 'w') as f:
    f.write("FILTERED UNUSED CSS SELECTORS\n")
    f.write("(Excluding timing values, numeric values, etc.)\n")
    f.write("=" * 80 + "\n\n")
    f.write(f"Total real unused selectors: {len(unused)}\n\n")
    
    for category, items in categories.items():
        if items:
            f.write(f"\n{category} ({len(items)} selectors)\n")
            f.write("-" * 80 + "\n")
            for selector, count in sorted(items):
                f.write(f".{selector:50s} ({count} occurrences)\n")
    
    f.write(f"\n{'=' * 80}\n")
    f.write("ALPHABETICAL LIST\n")
    f.write("=" * 80 + "\n\n")
    for selector, count in sorted(unused):
        f.write(f".{selector}\n")

print("\n📄 Filtered list saved to: UNUSED_CSS_FILTERED.txt")
