#!/usr/bin/env python3
import re
from pathlib import Path

def extract_css_rule(file_path, selector):
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    lines = content.split('\n')
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        if line.startswith(selector + ' {') or (line == selector and i + 1 < len(lines) and lines[i + 1].strip() == '{'):
            start_line = i + 1
            while i < len(lines) and '{' not in lines[i]:
                i += 1
            i += 1
            properties = []
            while i < len(lines) and '}' not in lines[i]:
                prop = lines[i].strip()
                if prop and not prop.startswith('/*') and not prop.startswith('*'):
                    properties.append(prop)
                i += 1
            return {'selector': selector, 'line': start_line, 'properties': properties}
        i += 1
    return None

css_dir = Path('/workspace/project/grpcSamples/octaneWebR/client/src/styles')
selectors = ['.viewport-canvas-container', '.viewport-container', '.viewport-overlay', '.viewport-status', '.scene-outliner']

for sel in selectors:
    app = extract_css_rule(css_dir / 'app.css', sel)
    theme = extract_css_rule(css_dir / 'octane-theme.css', sel)
    
    if app and theme:
        set_app = set(app['properties'])
        set_theme = set(theme['properties'])
        common = set_app & set_theme
        only_app = set_app - set_theme
        only_theme = set_theme - set_app
        
        print(f"\n{sel}:")
        print(f"  app.css:{app['line']} ({len(app['properties'])} props) vs theme:{theme['line']} ({len(theme['properties'])} props)")
        print(f"  Common: {len(common)}, Only app: {len(only_app)}, Only theme: {len(only_theme)}")
        
        if only_app:
            print(f"  Only in app:")
            for p in sorted(only_app)[:3]:
                print(f"    - {p}")
        if only_theme:
            print(f"  Only in theme:")
            for p in sorted(only_theme)[:3]:
                print(f"    + {p}")
