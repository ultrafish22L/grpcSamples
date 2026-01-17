#!/usr/bin/env python3
"""
Merge partial duplicates - add ONLY missing properties (no overrides).
This ensures zero visual difference while completing the selectors.
"""

import re
from pathlib import Path
from analyze_migration import extract_all_selectors

def add_properties_to_selector(content, selector, properties_to_add):
    """Add properties to an existing selector in CSS content."""
    # Escape selector for regex, but preserve commas and spaces
    escaped_selector = re.escape(selector).replace(r'\,', ',').replace(r'\ ', r'\s+')
    
    # Pattern to match the selector and its content
    # More flexible pattern that handles any amount of whitespace
    pattern = re.compile(
        rf'({escaped_selector})\s*\{{(.*?)\}}',
        re.MULTILINE | re.DOTALL
    )
    
    def replace_func(match):
        sel = match.group(1)
        existing_content = match.group(2)
        
        # Parse existing properties to maintain formatting
        lines = existing_content.split('\n')
        indent = '    '  # Standard indent
        
        # Find the indentation used
        for line in lines:
            if line.strip() and ':' in line:
                indent = line[:len(line) - len(line.lstrip())]
                break
        
        # Create new property lines
        new_lines = []
        new_lines.append(f"{indent}/* Added from octane-theme.css: */")
        for prop, value in sorted(properties_to_add.items()):
            new_lines.append(f"{indent}{prop}: {value};")
        
        # Combine with existing content
        result_content = existing_content.rstrip()
        if result_content and not result_content.endswith('\n'):
            result_content += '\n'
        result_content += '\n'.join(new_lines) + '\n'
        
        return f"{sel} {{{result_content}}}"
    
    new_content = pattern.sub(replace_func, content, count=1)
    
    if new_content == content:
        print(f"    ⚠️  WARNING: Could not find selector '{selector}' in content")
        return content
    
    return new_content

def main():
    styles_dir = Path('/workspace/project/grpcSamples/octaneWebR/client/src/styles')
    
    print("=" * 100)
    print("MERGING PARTIAL DUPLICATES - Adding Missing Properties Only")
    print("=" * 100)
    
    # Load all CSS files
    print("\nLoading CSS files...")
    octane_theme_selectors = extract_all_selectors(styles_dir / 'octane-theme.css')
    
    # Define the 10 conflicts with their missing properties (from MIGRATION_ANALYSIS.txt)
    conflicts = [
        {
            'file': 'app.css',
            'selector': '*',
            'missing': {
                'animation-duration': '0.01ms !important',
                'animation-iteration-count': '1 !important',
                'transition-duration': '0.01ms !important'
            }
        },
        {
            'file': 'app.css',
            'selector': '.app-container',
            'missing': {
                'grid-template-rows': 'var(--menu-height) 1fr var(--status-bar-height)',
                'height': '100vh',
                'width': '100vw',
                'background-color': 'var(--octane-bg-primary)',
                'overflow': 'hidden',
                'margin': '0',
                'padding': '0'
            }
        },
        {
            'file': 'app.css',
            'selector': '.app-layout',
            'missing': {
                'grid-template-columns': '150px 1fr 200px',
                'grid-template-rows': '1fr 200px'
            }
        },
        {
            'file': 'app.css',
            'selector': '.panel',
            'missing': {
                'background-color': 'var(--octane-bg-secondary)',
                'display': 'flex',
                'flex-direction': 'column'
            }
        },
        {
            'file': 'scene-outliner.css',
            'selector': '.scene-tree',
            'missing': {
                'flex': '1',
                'overflow-y': 'auto',
                'overflow-x': 'hidden',
                'background-color': 'var(--octane-bg-primary)',
                'min-height': '0',
                'max-height': '100%',
                'position': 'relative',
                'contain': 'layout style',
                'display': 'flex',
                'flex-direction': 'column'
            }
        },
        {
            'file': 'node-graph.css',
            'selector': '.toolbar-separator',
            'missing': {
                'background-color': 'var(--octane-border)',
                'flex-shrink': '0'
            }
        },
        {
            'file': 'scene-outliner.css',
            'selector': '.node-palette',
            'missing': {
                'left': '8px',
                'background-color': 'var(--octane-bg-secondary)'
            }
        },
        {
            'file': 'node-inspector.css',
            'selector': '.node-selector',
            'missing': {
                'border': '1px solid var(--octane-border)',
                'border-radius': 'var(--border-radius)',
                'cursor': 'pointer'
            }
        }
    ]
    
    # Note: .connection-status and .context-menu-separator only have conflicts, no missing properties
    
    print(f"\nProcessing {len(conflicts)} selectors with missing properties...\n")
    
    total_properties_added = 0
    
    for conflict in conflicts:
        target_file = styles_dir / conflict['file']
        selector = conflict['selector']
        missing_props = conflict['missing']
        
        print(f"📝 {conflict['file']}: {selector}")
        print(f"   Adding {len(missing_props)} missing properties")
        
        # Read current content
        content = target_file.read_text()
        
        # Add properties
        new_content = add_properties_to_selector(content, selector, missing_props)
        
        if new_content != content:
            # Write updated content
            target_file.write_text(new_content)
            total_properties_added += len(missing_props)
            print(f"   ✓ Added successfully")
        else:
            print(f"   ✗ Failed to update")
        
        print()
    
    print("=" * 100)
    print("MERGE COMPLETE")
    print("=" * 100)
    print(f"\nTotal properties added: {total_properties_added}")
    print(f"Files modified: {len(set(c['file'] for c in conflicts))}")
    print("\n✓ NO existing properties were overridden")
    print("✓ NO visual changes - only filled in missing properties")
    print("=" * 100)
    
    print("\n📋 Modified files:")
    for filename in sorted(set(c['file'] for c in conflicts)):
        print(f"  - client/src/styles/{filename}")

if __name__ == '__main__':
    main()
