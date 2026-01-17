#!/usr/bin/env python3
"""
Analyze CSS migration from octane-theme.css to specific files.
CRITICAL: Ensure NO properties are lost during migration.
"""

import re
from pathlib import Path
from collections import defaultdict

def extract_properties(selector_content):
    """Extract property: value pairs from a selector block."""
    # Remove the selector line and braces
    lines = selector_content.split('\n')
    properties = {}
    
    for line in lines:
        line = line.strip()
        if '{' in line:
            line = line.split('{', 1)[1]
        if '}' in line:
            line = line.split('}', 1)[0]
        
        # Parse property: value
        if ':' in line and not line.startswith('/*'):
            parts = line.split(':', 1)
            if len(parts) == 2:
                prop = parts[0].strip()
                value = parts[1].strip().rstrip(';').strip()
                if prop and value:
                    properties[prop] = value
    
    return properties

def extract_all_selectors(css_file):
    """Extract all selectors with their properties from a CSS file."""
    if not css_file.exists():
        return {}
    
    content = css_file.read_text()
    lines = content.split('\n')
    
    selectors = {}
    current_selector = None
    current_content = []
    brace_depth = 0
    
    for line in lines:
        # Skip pure comment lines
        if line.strip().startswith('/*') and '*/' in line:
            continue
            
        open_count = line.count('{')
        close_count = line.count('}')
        
        if open_count > 0 and brace_depth == 0:
            # New selector
            selector = line.split('{')[0].strip()
            if selector and not selector.startswith('@'):
                current_selector = selector
                current_content = [line]
                brace_depth += open_count - close_count
                
                if brace_depth == 0:
                    # Single line selector
                    props = extract_properties('\n'.join(current_content))
                    selectors[current_selector] = props
                    current_selector = None
                    current_content = []
        elif brace_depth > 0:
            current_content.append(line)
            brace_depth += open_count - close_count
            
            if brace_depth == 0 and current_selector:
                # End of block
                props = extract_properties('\n'.join(current_content))
                selectors[current_selector] = props
                current_selector = None
                current_content = []
    
    return selectors

def categorize_selector(selector):
    """Determine which file a selector belongs to."""
    sel_lower = selector.lower()
    
    # Scene Outliner node-related selectors (more specific first)
    if any(x in sel_lower for x in [
        'node-toggle', 'node-icon', 'node-name', 'node-handle',
        'node-visibility', 'node-spacer', 'node-count', 'node-type',
        'node-children', 'node-selected', 'tree-toggle'
    ]):
        return 'scene-outliner.css'
    
    # Scene Outliner selectors
    if any(x in sel_lower for x in [
        'scene-outliner', 'tree-node', 'scene-tree',
        'scene-loading', 'node-palette', 'node-content'
    ]):
        return 'scene-outliner.css'
    
    # Node Graph selectors
    if any(x in sel_lower for x in [
        'node-graph', 'octane-node', 'react-flow', 
        'toolbar-button', 'node-btn', 'toolbar-separator'
    ]):
        return 'node-graph.css'
    
    # Node Inspector selectors  
    if any(x in sel_lower for x in [
        'node-inspector', 'parameter', 'inspector-',
        'quick-btn', 'control-btn', 'octane-section',
        'octane-subsection', 'node-selector'
    ]):
        return 'node-inspector.css'
    
    # Viewport selectors
    if any(x in sel_lower for x in [
        'viewport', 'render-', 'callback-render',
        'stats-separator', 'toolbar-icon-btn', 'camera-'
    ]):
        return 'viewport.css'
    
    # App layout selectors
    if any(x in sel_lower for x in [
        'app-', 'menu-', 'status-', 'connection',
        'panel', 'loading-', 'modal-', 'context-menu',
        'splitter', 'left-panel', 'right-panel',
        'bottom-panel', 'top-panel', 'main-menu'
    ]):
        return 'app.css'
    
    # Generic base selectors
    if sel_lower in ['*', 'body', 'html', 'html, body'] or sel_lower.startswith('#root'):
        return 'app.css'
    
    # Keyframes and animations
    if '@keyframes' in sel_lower or sel_lower in ['from', 'to', '0%, 100%', '50%']:
        return 'KEYFRAME'
    
    # Logo and branding
    if 'logo' in sel_lower:
        return 'app.css'
    
    # Generic UI elements and base styles
    if any(x in sel_lower for x in [
        'scrollbar', 'select', 'input', 'textarea',
        'context-submenu', 'category-arrow'
    ]):
        return 'app.css'
    
    return 'UNKNOWN'

def main():
    styles_dir = Path('/workspace/project/grpcSamples/octaneWebR/client/src/styles')
    
    # Load all CSS files
    print("Loading CSS files...")
    octane_theme_selectors = extract_all_selectors(styles_dir / 'octane-theme.css')
    app_selectors = extract_all_selectors(styles_dir / 'app.css')
    node_graph_selectors = extract_all_selectors(styles_dir / 'node-graph.css')
    node_inspector_selectors = extract_all_selectors(styles_dir / 'node-inspector.css')
    scene_outliner_selectors = extract_all_selectors(styles_dir / 'scene-outliner.css')
    viewport_selectors = extract_all_selectors(styles_dir / 'viewport.css')
    
    target_files = {
        'app.css': app_selectors,
        'node-graph.css': node_graph_selectors,
        'node-inspector.css': node_inspector_selectors,
        'scene-outliner.css': scene_outliner_selectors,
        'viewport.css': viewport_selectors
    }
    
    print(f"Found {len(octane_theme_selectors)} selectors in octane-theme.css\n")
    
    # Skip :root block selectors
    selectors_to_migrate = {k: v for k, v in octane_theme_selectors.items() 
                           if not k.startswith(':root')}
    
    print(f"Selectors to analyze (excluding :root): {len(selectors_to_migrate)}\n")
    
    # Categorize and analyze
    migration_plan = defaultdict(list)
    conflicts = []
    safe_moves = []
    unknown_selectors = []
    
    for selector, props in selectors_to_migrate.items():
        target_file = categorize_selector(selector)
        
        if target_file == 'UNKNOWN':
            unknown_selectors.append((selector, props))
            continue
        
        if target_file == 'KEYFRAME':
            migration_plan['app.css'].append({
                'selector': selector,
                'action': 'MOVE',
                'reason': 'Animation keyframe',
                'properties': props
            })
            continue
        
        # Check if selector already exists in target file
        target_selectors = target_files.get(target_file, {})
        
        if selector in target_selectors:
            # Compare properties
            existing_props = target_selectors[selector]
            missing_props = {}
            conflicting_props = {}
            
            for prop, value in props.items():
                if prop not in existing_props:
                    missing_props[prop] = value
                elif existing_props[prop] != value:
                    conflicting_props[prop] = {
                        'octane_theme': value,
                        'target_file': existing_props[prop]
                    }
            
            if missing_props or conflicting_props:
                conflicts.append({
                    'selector': selector,
                    'target_file': target_file,
                    'missing_props': missing_props,
                    'conflicting_props': conflicting_props,
                    'all_octane_props': props
                })
            else:
                # Selector exists with identical properties - can be removed from octane-theme
                safe_moves.append({
                    'selector': selector,
                    'target_file': target_file,
                    'action': 'DELETE',
                    'reason': 'Exact duplicate already exists'
                })
        else:
            # Selector doesn't exist in target - safe to move
            migration_plan[target_file].append({
                'selector': selector,
                'action': 'MOVE',
                'reason': 'Does not exist in target',
                'properties': props
            })
    
    # Print results
    print("=" * 100)
    print("MIGRATION ANALYSIS RESULTS")
    print("=" * 100)
    
    print("\n### SAFE TO DELETE FROM octane-theme.css (already exist with same properties)")
    print(f"Total: {len(safe_moves)}")
    for item in safe_moves[:10]:
        print(f"  - {item['selector']} (in {item['target_file']})")
    if len(safe_moves) > 10:
        print(f"  ... and {len(safe_moves) - 10} more")
    
    print("\n### SAFE TO MOVE (don't exist in target files)")
    for target_file, items in sorted(migration_plan.items()):
        print(f"\n{target_file}: {len(items)} selectors")
        for item in items[:5]:
            print(f"  - {item['selector']} ({len(item['properties'])} properties)")
        if len(items) > 5:
            print(f"  ... and {len(items) - 5} more")
    
    print("\n### ⚠️ CONFLICTS - Need Manual Review")
    print(f"Total: {len(conflicts)}")
    for conflict in conflicts[:10]:
        print(f"\n  Selector: {conflict['selector']}")
        print(f"  Target: {conflict['target_file']}")
        if conflict['missing_props']:
            print(f"  Missing in target: {len(conflict['missing_props'])} properties")
            for prop, val in list(conflict['missing_props'].items())[:3]:
                print(f"    + {prop}: {val}")
        if conflict['conflicting_props']:
            print(f"  Conflicting: {len(conflict['conflicting_props'])} properties")
            for prop, vals in list(conflict['conflicting_props'].items())[:3]:
                print(f"    ≠ {prop}:")
                print(f"        octane-theme: {vals['octane_theme']}")
                print(f"        {conflict['target_file']}: {vals['target_file']}")
    
    if len(conflicts) > 10:
        print(f"\n  ... and {len(conflicts) - 10} more conflicts")
    
    print("\n### ❓ UNKNOWN CATEGORIZATION")
    print(f"Total: {len(unknown_selectors)}")
    for selector, props in unknown_selectors[:15]:
        print(f"  - {selector} ({len(props)} properties)")
    if len(unknown_selectors) > 15:
        print(f"  ... and {len(unknown_selectors) - 15} more")
    
    print("\n" + "=" * 100)
    print("SUMMARY")
    print("=" * 100)
    print(f"Safe to delete (duplicates): {len(safe_moves)}")
    print(f"Safe to move: {sum(len(items) for items in migration_plan.values())}")
    print(f"Conflicts (need merge): {len(conflicts)}")
    print(f"Unknown categorization: {len(unknown_selectors)}")
    print(f"Total to process: {len(safe_moves) + sum(len(items) for items in migration_plan.values()) + len(conflicts) + len(unknown_selectors)}")
    print("=" * 100)
    
    # Save detailed report
    report_path = Path('/workspace/project/grpcSamples/octaneWebR/MIGRATION_ANALYSIS.txt')
    with open(report_path, 'w') as f:
        f.write("DETAILED MIGRATION ANALYSIS\n")
        f.write("=" * 100 + "\n\n")
        
        f.write("CONFLICTS REQUIRING PROPERTY MERGING:\n")
        f.write("-" * 100 + "\n")
        for conflict in conflicts:
            f.write(f"\nSelector: {conflict['selector']}\n")
            f.write(f"Target File: {conflict['target_file']}\n")
            if conflict['missing_props']:
                f.write("  Properties MISSING in target (need to ADD):\n")
                for prop, val in conflict['missing_props'].items():
                    f.write(f"    {prop}: {val};\n")
            if conflict['conflicting_props']:
                f.write("  Properties CONFLICTING (need to DECIDE):\n")
                for prop, vals in conflict['conflicting_props'].items():
                    f.write(f"    {prop}:\n")
                    f.write(f"      octane-theme.css: {vals['octane_theme']}\n")
                    f.write(f"      {conflict['target_file']}: {vals['target_file']}\n")
            f.write("\n")
    
    print(f"\nDetailed report saved to: {report_path}")

if __name__ == '__main__':
    main()
