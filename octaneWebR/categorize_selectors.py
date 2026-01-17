#!/usr/bin/env python3
"""
Categorize CSS selectors in octane-theme.css by their proper target file.
Also check for existing selectors to ensure NO PROPERTIES ARE LOST.
"""

import re
from pathlib import Path
from collections import defaultdict
import cssutils
import logging

# Suppress cssutils warnings
cssutils.log.setLevel(logging.CRITICAL)

def extract_selector_blocks(css_content, start_line=199):
    """Extract selector blocks with line numbers from CSS content."""
    lines = css_content.split('\n')
    
    blocks = []
    current_block = None
    current_selector = ""
    brace_depth = 0
    in_comment = False
    
    for line_num, line in enumerate(lines[start_line-1:], start_line):
        # Track multi-line comments
        if '/*' in line and '*/' not in line:
            in_comment = True
        if '*/' in line:
            in_comment = False
            continue
        if in_comment:
            continue
            
        # Skip single-line comments
        if line.strip().startswith('/*') and '*/' in line:
            continue
            
        # Track braces
        open_count = line.count('{')
        close_count = line.count('}')
        
        if open_count > 0 and brace_depth == 0:
            # Start of a new selector block
            selector_part = line.split('{')[0].strip()
            if selector_part and not selector_part.startswith('@'):
                current_selector = selector_part
                current_block = {
                    'selector': current_selector,
                    'start_line': line_num,
                    'lines': [line],
                    'content': line
                }
                brace_depth += open_count - close_count
                
                if brace_depth == 0:
                    # Single-line block
                    blocks.append(current_block)
                    current_block = None
        elif brace_depth > 0:
            # Inside a block
            if current_block:
                current_block['lines'].append(line)
                current_block['content'] += '\n' + line
            
            brace_depth += open_count - close_count
            
            if brace_depth == 0 and current_block:
                # End of block
                current_block['end_line'] = line_num
                blocks.append(current_block)
                current_block = None
    
    return blocks

def categorize_selector(selector):
    """Determine which file a selector belongs to."""
    selector = selector.lower()
    
    # Node Graph selectors
    if any(x in selector for x in [
        'node-graph', 'octane-node', 'react-flow', 
        'toolbar-button', 'toolbar-separator', 'node-btn'
    ]):
        return 'node-graph.css'
    
    # Node Inspector selectors
    if any(x in selector for x in [
        'node-inspector', 'parameter', 'inspector-', 
        'quick-btn', 'control-btn'
    ]):
        return 'node-inspector.css'
    
    # Scene Outliner selectors
    if any(x in selector for x in [
        'scene-outliner', 'tree-node', 'scene-tree', 
        'scene-loading', 'node-palette'
    ]):
        return 'scene-outliner.css'
    
    # Viewport selectors
    if any(x in selector for x in [
        'viewport', 'render-', 'callback-render'
    ]):
        return 'viewport.css'
    
    # App layout and base selectors
    if any(x in selector for x in [
        'app-', 'menu-', 'status-', 'connection-status',
        'panel', 'loading-', 'modal-', 'context-menu'
    ]):
        return 'app.css'
    
    # Catch-all for generic selectors
    if selector in ['*', 'body', 'html', '#root']:
        return 'app.css'
    
    return 'UNKNOWN'

def main():
    styles_dir = Path('/workspace/project/grpcSamples/octaneWebR/client/src/styles')
    octane_theme = styles_dir / 'octane-theme.css'
    
    content = octane_theme.read_text()
    
    # Extract all selector blocks after line 198 (after :root)
    blocks = extract_selector_blocks(content, start_line=199)
    
    print(f"Found {len(blocks)} selector blocks in octane-theme.css (lines 199+)\n")
    
    # Categorize selectors
    by_file = defaultdict(list)
    
    for block in blocks:
        target_file = categorize_selector(block['selector'])
        by_file[target_file].append(block)
    
    # Print summary
    print("=" * 100)
    print("SELECTOR CATEGORIZATION SUMMARY")
    print("=" * 100)
    
    for target_file in sorted(by_file.keys()):
        selectors = by_file[target_file]
        print(f"\n{target_file}: {len(selectors)} selectors")
        print("-" * 100)
        
        for sel in selectors[:10]:  # Show first 10
            line_range = f"{sel['start_line']}"
            if 'end_line' in sel:
                line_range += f"-{sel['end_line']}"
            print(f"  Line {line_range:8s}: {sel['selector'][:70]}")
        
        if len(selectors) > 10:
            print(f"  ... and {len(selectors) - 10} more")
    
    # Print detailed breakdown for migration planning
    print("\n" + "=" * 100)
    print("MIGRATION PLAN")
    print("=" * 100)
    
    total_lines = 0
    for target_file in sorted(by_file.keys()):
        if target_file == 'UNKNOWN':
            continue
        selectors = by_file[target_file]
        line_count = sum(len(s['lines']) for s in selectors)
        total_lines += line_count
        print(f"\n{target_file}:")
        print(f"  Selectors to move: {len(selectors)}")
        print(f"  Lines to move: ~{line_count}")
    
    unknown = by_file.get('UNKNOWN', [])
    if unknown:
        print(f"\nUNKNOWN (need manual categorization):")
        print(f"  Selectors: {len(unknown)}")
        print(f"  Lines: ~{sum(len(s['lines']) for s in unknown)}")
        print(f"\n  Selectors:")
        for sel in unknown[:20]:
            print(f"    Line {sel['start_line']}: {sel['selector']}")
    
    print(f"\n{'=' * 100}")
    print(f"TOTAL: ~{total_lines} lines to migrate from octane-theme.css")
    print(f"REMAINING in octane-theme.css: ~198 lines (CSS variables only)")
    print(f"{'=' * 100}")

if __name__ == '__main__':
    main()
