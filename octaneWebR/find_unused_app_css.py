#!/usr/bin/env python3
"""
Find exact line numbers for unused selectors in app.css
"""

import re
from pathlib import Path

CSS_FILE = Path("client/src/styles/app.css")

UNUSED_SELECTORS = [
    'app-footer', 'app-header', 'app-main', 'app-subtitle', 'app-title',
    'footer-info', 'frame-count',
    'node-properties',
    'octane-app',
    'outliner-header', 'outliner-tree',
    'panel-section',
    'property', 'property-group',
    'raw-data',
    'side-panel',
    'status-message',
    'tree-expand', 'tree-icon', 'tree-label', 'tree-type',
    'viewport-status'
]

def find_selector_blocks(css_content, selector_name):
    """Find all blocks for a given selector"""
    lines = css_content.split('\n')
    blocks = []
    
    i = 0
    while i < len(lines):
        line = lines[i]
        
        # Look for selector (handle multiple formats)
        patterns = [
            rf'^\.{selector_name}\s*{{',  # .selector {
            rf'^\.{selector_name}\s*,',    # .selector,
            rf'^\s+\.{selector_name}\s*{{', # indented
            rf',\s*\.{selector_name}\s*{{', # comma separated
        ]
        
        found = False
        for pattern in patterns:
            if re.search(pattern, line):
                found = True
                break
        
        if found:
            # Find the start line
            start_line = i + 1  # 1-indexed
            
            # Find closing brace
            brace_count = line.count('{') - line.count('}')
            j = i + 1
            
            while j < len(lines) and brace_count > 0:
                brace_count += lines[j].count('{') - lines[j].count('}')
                j += 1
            
            end_line = j  # 1-indexed
            block_content = '\n'.join(lines[i:j])
            
            blocks.append({
                'start': start_line,
                'end': end_line,
                'lines': end_line - start_line + 1,
                'content': block_content[:100] + '...' if len(block_content) > 100 else block_content
            })
            
            i = j
        else:
            i += 1
    
    return blocks

def main():
    if not CSS_FILE.exists():
        print(f"Error: {CSS_FILE} not found")
        return
    
    with open(CSS_FILE, 'r') as f:
        content = f.read()
    
    print("=" * 80)
    print("UNUSED SELECTORS IN app.css - LINE NUMBERS")
    print("=" * 80)
    print()
    
    total_lines = 0
    found_selectors = []
    not_found = []
    
    for selector in UNUSED_SELECTORS:
        blocks = find_selector_blocks(content, selector)
        
        if blocks:
            found_selectors.append(selector)
            for block in blocks:
                print(f"✗ .{selector}")
                print(f"  Lines: {block['start']}-{block['end']} ({block['lines']} lines)")
                print(f"  Preview: {block['content'][:80]}")
                print()
                total_lines += block['lines']
        else:
            not_found.append(selector)
    
    print("=" * 80)
    print(f"FOUND: {len(found_selectors)} selectors")
    print(f"NOT FOUND: {len(not_found)} selectors")
    print(f"TOTAL LINES TO REMOVE: ~{total_lines}")
    print("=" * 80)
    
    if not_found:
        print()
        print("NOT FOUND (may be nested, commented, or false positive):")
        for sel in not_found:
            print(f"  .{sel}")
    
    # Save detailed report
    with open('PHASE4A_APP_CSS_REMOVAL_PLAN.md', 'w') as f:
        f.write("# Phase 4a: app.css Unused Selector Removal\n\n")
        f.write(f"## Summary\n\n")
        f.write(f"**Unused selectors found:** {len(found_selectors)}\n")
        f.write(f"**Total lines to remove:** ~{total_lines}\n\n")
        f.write("---\n\n")
        f.write("## Selectors to Remove\n\n")
        
        for selector in found_selectors:
            blocks = find_selector_blocks(content, selector)
            f.write(f"### .{selector}\n\n")
            for block in blocks:
                f.write(f"**Lines {block['start']}-{block['end']}** ({block['lines']} lines)\n")
                f.write(f"```css\n{block['content']}\n```\n\n")
        
        if not_found:
            f.write("---\n\n")
            f.write("## Not Found (Manual Review Needed)\n\n")
            for sel in not_found:
                f.write(f"- `.{sel}` - May be nested, commented, or false positive\n")
    
    print()
    print("Detailed removal plan saved to: PHASE4A_APP_CSS_REMOVAL_PLAN.md")

if __name__ == "__main__":
    main()
