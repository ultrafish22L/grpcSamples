#!/usr/bin/env python3
"""
Find node-graph related selectors and their line numbers in components.css
"""

import re
from pathlib import Path

CSS_FILE = Path("client/src/styles/components.css")

NODE_GRAPH_SELECTORS = [
    'node-graph',
    'node-graph-container',
    'node-graph-canvas',
    'node-graph-viewport',
    'graph-node',
    'graph-node-header',
    'graph-node-body',
    'graph-node-footer',
    'graph-node-input',
    'graph-node-output',
    'graph-connection',
    'graph-port',
    'node-editor',
    'node-canvas',
    'visual-node',
    'connection-line',
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
            rf'\.{selector_name}:',         # pseudo-class/element
            rf'\.{selector_name}\.',        # chained classes
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
                'content': block_content
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
    print("PHASE 4c: NODE GRAPH SELECTORS IN components.css")
    print("=" * 80)
    print()
    
    total_lines = 0
    found_selectors = []
    not_found = []
    
    for selector in NODE_GRAPH_SELECTORS:
        blocks = find_selector_blocks(content, selector)
        
        if blocks:
            found_selectors.append(selector)
            for block in blocks:
                print(f"✗ .{selector}")
                print(f"  Lines: {block['start']}-{block['end']} ({block['lines']} lines)")
                preview = block['content'][:100].replace('\n', ' ')
                print(f"  Preview: {preview}...")
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
    with open('PHASE4C_NODE_GRAPH_REMOVAL_PLAN.md', 'w') as f:
        f.write("# Phase 4c: Node Graph Selectors Removal\n\n")
        f.write(f"## Summary\n\n")
        f.write(f"**Unused selectors found:** {len(found_selectors)}\n")
        f.write(f"**Total lines to remove:** ~{total_lines}\n")
        f.write(f"**Risk Level:** LOW ✅ (Node graph system not implemented)\n\n")
        f.write("---\n\n")
        
        if found_selectors:
            f.write("## Selectors to Remove\n\n")
            for selector in found_selectors:
                blocks = find_selector_blocks(content, selector)
                f.write(f"### .{selector}\n\n")
                for block in blocks:
                    f.write(f"**Lines {block['start']}-{block['end']}** ({block['lines']} lines)\n")
                    f.write(f"```css\n{block['content']}\n```\n\n")
        else:
            f.write("## ✅ No Node Graph Selectors Found\n\n")
            f.write("The components.css file does not contain any node graph related selectors.\n")
            f.write("This feature was likely never started or already cleaned up.\n\n")
        
        if not_found:
            f.write("---\n\n")
            f.write("## Selectors Not Found\n\n")
            for sel in not_found:
                f.write(f"- `.{sel}` - Not present in CSS\n")
        
        f.write("---\n\n")
        f.write("## Verification\n\n")
        f.write("```bash\n")
        if found_selectors:
            for selector in found_selectors:
                f.write(f"grep -r '{selector}' client/src --include='*.tsx' --include='*.ts'\n")
            f.write("# All should return exit code 1 (not found) ✓\n")
        else:
            f.write("# No selectors to verify - none found in CSS\n")
        f.write("```\n")
    
    print()
    print("Detailed removal plan saved to: PHASE4C_NODE_GRAPH_REMOVAL_PLAN.md")
    
    return len(found_selectors) > 0

if __name__ == "__main__":
    import sys
    found_any = main()
    sys.exit(0 if found_any else 2)  # Exit code 2 = none found, skip to next phase
