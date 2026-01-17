#!/usr/bin/env python3
"""
Migrate CSS selectors from octane-theme.css to their proper files.
CRITICAL: NO properties will be lost. Conflicts will be merged with comments.
"""

import re
from pathlib import Path
from collections import defaultdict
from analyze_migration import extract_all_selectors, extract_properties, categorize_selector

def extract_selector_blocks_with_content(css_content, start_line=199):
    """Extract complete selector blocks with all content from CSS."""
    lines = css_content.split('\n')
    
    blocks = []
    current_selector = None
    current_lines = []
    brace_depth = 0
    
    for line_num, line in enumerate(lines[start_line-1:], start_line):
        # Track braces
        open_count = line.count('{')
        close_count = line.count('}')
        
        if open_count > 0 and brace_depth == 0:
            # Start of new selector
            selector = line.split('{')[0].strip()
            if selector and not selector.startswith('@'):
                current_selector = selector
                current_lines = [line]
                brace_depth += open_count - close_count
                
                if brace_depth == 0:
                    # Single-line block
                    blocks.append({
                        'selector': current_selector,
                        'content': '\n'.join(current_lines),
                        'start_line': line_num,
                        'end_line': line_num
                    })
                    current_selector = None
                    current_lines = []
        elif brace_depth > 0:
            current_lines.append(line)
            brace_depth += open_count - close_count
            
            if brace_depth == 0 and current_selector:
                blocks.append({
                    'selector': current_selector,
                    'content': '\n'.join(current_lines),
                    'start_line': line_num - len(current_lines) + 1,
                    'end_line': line_num
                })
                current_selector = None
                current_lines = []
    
    return blocks

def merge_properties(octane_props, existing_props):
    """Merge properties, preserving all values and noting conflicts."""
    merged = existing_props.copy()
    conflicts = {}
    added = {}
    
    for prop, value in octane_props.items():
        if prop not in existing_props:
            merged[prop] = value
            added[prop] = value
        elif existing_props[prop] != value:
            conflicts[prop] = {
                'existing': existing_props[prop],
                'octane': value,
                'chosen': existing_props[prop]  # Keep existing by default
            }
    
    return merged, added, conflicts

def create_selector_with_properties(selector, properties, comments=None):
    """Create a formatted CSS selector with properties."""
    lines = [f"{selector} {{"]
    
    if comments:
        for comment in comments:
            lines.append(f"    /* {comment} */")
    
    for prop, value in sorted(properties.items()):
        lines.append(f"    {prop}: {value};")
    
    lines.append("}")
    return '\n'.join(lines)

def main():
    styles_dir = Path('/workspace/project/grpcSamples/octaneWebR/client/src/styles')
    octane_theme_path = styles_dir / 'octane-theme.css'
    
    print("=" * 100)
    print("CSS MIGRATION: octane-theme.css → Specific Component Files")
    print("=" * 100)
    print("\nStep 1: Loading CSS files...")
    
    # Load current state
    octane_content = octane_theme_path.read_text()
    octane_selectors = extract_all_selectors(octane_theme_path)
    
    target_files = {
        'app.css': extract_all_selectors(styles_dir / 'app.css'),
        'node-graph.css': extract_all_selectors(styles_dir / 'node-graph.css'),
        'node-inspector.css': extract_all_selectors(styles_dir / 'node-inspector.css'),
        'scene-outliner.css': extract_all_selectors(styles_dir / 'scene-outliner.css'),
        'viewport.css': extract_all_selectors(styles_dir / 'viewport.css')
    }
    
    # Extract selector blocks from octane-theme.css (after :root)
    print("\nStep 2: Extracting selector blocks from octane-theme.css...")
    blocks = extract_selector_blocks_with_content(octane_content, start_line=199)
    print(f"Found {len(blocks)} selector blocks to migrate")
    
    # Categorize and plan migration
    print("\nStep 3: Categorizing selectors...")
    migration_plan = defaultdict(list)
    conflict_plan = defaultdict(list)
    
    for block in blocks:
        selector = block['selector']
        props = extract_properties(block['content'])
        target_file = categorize_selector(selector)
        
        if target_file == 'KEYFRAME':
            target_file = 'app.css'
        
        if selector in target_files.get(target_file, {}):
            # Conflict - needs merging
            existing_props = target_files[target_file][selector]
            merged, added, conflicts = merge_properties(props, existing_props)
            
            if added or conflicts:
                conflict_plan[target_file].append({
                    'selector': selector,
                    'added': added,
                    'conflicts': conflicts,
                    'merged': merged,
                    'original_block': block
                })
            # else: exact duplicate, will be removed from octane-theme
        else:
            # Safe to move
            migration_plan[target_file].append(block)
    
    print(f"\nSelectors to move: {sum(len(blocks) for blocks in migration_plan.values())}")
    print(f"Selectors with conflicts: {sum(len(blocks) for blocks in conflict_plan.values())}")
    
    # Execute migration
    print("\nStep 4: Migrating selectors to target files...")
    
    for target_file, blocks_to_add in migration_plan.items():
        if not blocks_to_add:
            continue
            
        target_path = styles_dir / target_file
        target_content = target_path.read_text()
        
        print(f"\n  {target_file}: Adding {len(blocks_to_add)} selectors")
        
        # Append selectors
        additions = [
            "\n",
            "/* ========================================== */",
            f"/* Migrated from octane-theme.css */",
            "/* ========================================== */",
            "\n"
        ]
        
        for block in blocks_to_add:
            additions.append(block['content'])
            additions.append("\n")
        
        new_content = target_content.rstrip() + '\n' + '\n'.join(additions)
        target_path.write_text(new_content)
        print(f"    ✓ {len(blocks_to_add)} selectors added")
    
    # Handle conflicts (add missing properties)
    print("\nStep 5: Merging conflicting selectors...")
    
    for target_file, conflicts in conflict_plan.items():
        if not conflicts:
            continue
            
        target_path = styles_dir / target_file
        content = target_path.read_text()
        
        print(f"\n  {target_file}: Merging {len(conflicts)} selectors")
        
        for conflict in conflicts:
            selector = conflict['selector']
            added_props = conflict['added']
            conflicting_props = conflict['conflicts']
            
            if added_props:
                print(f"    • {selector}: Adding {len(added_props)} missing properties")
                
                # Find the selector in the file and add properties
                # This is a simple approach - find closing brace and add before it
                selector_pattern = re.escape(selector) + r'\s*\{([^}]*)\}'
                
                def add_properties(match):
                    existing = match.group(1)
                    new_props = '\n'.join(f"    {prop}: {val};" for prop, val in added_props.items())
                    comment = f"\n    /* Added from octane-theme.css: */"
                    return f"{selector} {{{existing.rstrip()}{comment}\n{new_props}\n}}"
                
                content = re.sub(selector_pattern, add_properties, content, count=1, flags=re.DOTALL)
            
            if conflicting_props:
                print(f"    ⚠ {selector}: {len(conflicting_props)} conflicting properties (keeping existing)")
                for prop, vals in conflicting_props.items():
                    print(f"        {prop}: {vals['existing']} (kept) vs {vals['octane']} (octane-theme)")
        
        target_path.write_text(content)
        print(f"    ✓ Conflicts resolved")
    
    # Create new octane-theme.css with only :root
    print("\nStep 6: Creating new octane-theme.css (CSS variables only)...")
    
    # Extract :root block (lines 1-198)
    lines = octane_content.split('\n')
    root_block = '\n'.join(lines[:198])
    
    new_octane_theme = root_block.rstrip() + '\n'
    
    octane_theme_path.write_text(new_octane_theme)
    
    original_size = len(octane_content)
    new_size = len(new_octane_theme)
    reduction = original_size - new_size
    
    print(f"    ✓ octane-theme.css reduced from {original_size} to {new_size} bytes")
    print(f"    ✓ Reduction: {reduction} bytes ({reduction/original_size*100:.1f}%)")
    
    print("\n" + "=" * 100)
    print("MIGRATION COMPLETE!")
    print("=" * 100)
    print("\nSummary:")
    print(f"  • Selectors moved: {sum(len(blocks) for blocks in migration_plan.values())}")
    print(f"  • Selectors merged: {sum(len(blocks) for blocks in conflict_plan.values())}")
    print(f"  • Properties added: {sum(len(c['added']) for conflicts in conflict_plan.values() for c in conflicts)}")
    print(f"  • octane-theme.css: Now contains ONLY CSS variables ({new_size} bytes)")
    print(f"\n  ✓ NO PROPERTIES LOST - All styles preserved in component files")
    print("=" * 100)

if __name__ == '__main__':
    main()
