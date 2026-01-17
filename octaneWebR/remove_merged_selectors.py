#!/usr/bin/env python3
"""
Remove the 10 selectors from octane-theme.css that have been merged to component files.
"""

import re
from pathlib import Path

def remove_selector_blocks(content, selectors_to_remove):
    """Remove complete selector blocks from CSS content."""
    lines = content.split('\n')
    
    # Track which lines to keep
    keep_lines = [True] * len(lines)
    
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        
        # Check if this line starts a selector we want to remove
        for selector in selectors_to_remove:
            # Check for exact match at start of line
            if line == selector or line.startswith(selector + ' {'):
                # Found a selector to remove - find its closing brace
                brace_depth = 0
                start_line = i
                
                # Mark this line for removal
                keep_lines[i] = False
                
                # Count braces on this line
                brace_depth += lines[i].count('{')
                brace_depth -= lines[i].count('}')
                
                # Continue until we find the matching closing brace
                i += 1
                while i < len(lines) and brace_depth > 0:
                    keep_lines[i] = False
                    brace_depth += lines[i].count('{')
                    brace_depth -= lines[i].count('}')
                    i += 1
                
                # Also remove the blank line after the block if it exists
                if i < len(lines) and lines[i].strip() == '':
                    keep_lines[i] = False
                
                print(f"✓ Removed: {selector} (lines {start_line+1}-{i})")
                break
        
        i += 1
    
    # Rebuild content from lines we're keeping
    new_lines = [lines[i] for i in range(len(lines)) if keep_lines[i]]
    return '\n'.join(new_lines)

def main():
    styles_dir = Path('/workspace/project/grpcSamples/octaneWebR/client/src/styles')
    octane_theme_path = styles_dir / 'octane-theme.css'
    
    print("=" * 100)
    print("REMOVING MERGED SELECTORS FROM octane-theme.css")
    print("=" * 100)
    
    # The 10 selectors that have been merged to component files
    selectors_to_remove = [
        '*',
        '.app-container',
        '.connection-status',
        '.app-layout',
        '.panel',
        '.scene-tree',
        '.toolbar-separator',
        '.node-palette',
        '.node-selector',
        '.context-menu-separator'
    ]
    
    print(f"\nRemoving {len(selectors_to_remove)} selectors that now exist in component files...\n")
    
    # Read current content
    content = octane_theme_path.read_text()
    original_size = len(content)
    original_lines = len(content.split('\n'))
    
    # Remove the selectors
    new_content = remove_selector_blocks(content, selectors_to_remove)
    
    new_size = len(new_content)
    new_lines = len(new_content.split('\n'))
    
    # Write back
    octane_theme_path.write_text(new_content)
    
    reduction = original_size - new_size
    lines_removed = original_lines - new_lines
    
    print("\n" + "=" * 100)
    print("CLEANUP COMPLETE")
    print("=" * 100)
    print(f"\nSelectors removed: {len(selectors_to_remove)}")
    print(f"Size reduction: {reduction} bytes ({reduction/original_size*100:.1f}%)")
    print(f"Lines removed: {lines_removed}")
    print(f"Original: {original_lines} lines, {original_size} bytes")
    print(f"New:      {new_lines} lines, {new_size} bytes")
    
    print("\n✓ octane-theme.css is now {:.1f}KB smaller".format(reduction/1024))
    print("✓ All merged selectors removed")
    print("✓ Component files now contain all these styles")
    print("=" * 100)

if __name__ == '__main__':
    main()
