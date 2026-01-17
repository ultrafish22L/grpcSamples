#!/usr/bin/env python3
"""
Generate detailed report of unused CSS selectors with exact line ranges.
"""

import re
from pathlib import Path
from collections import defaultdict

def find_css_blocks(file_path, class_names):
    """Find the full CSS blocks for given class names."""
    blocks = defaultdict(list)  # class_name -> [(start_line, end_line, content)]
    
    with open(file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()
    
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        
        # Check if this line contains any of our target class names
        for class_name in class_names:
            pattern = rf'\.{re.escape(class_name)}(?:[,\s:{{]|$)'
            if re.search(pattern, line):
                # Found a selector, now find the complete block
                start_line = i + 1  # 1-indexed
                
                # Collect selector lines (might span multiple lines)
                selector_lines = [line]
                j = i + 1
                while j < len(lines) and '{' not in lines[i:j+1]:
                    selector_lines.append(lines[j].strip())
                    j += 1
                
                # Find opening brace
                while j < len(lines) and '{' not in lines[j]:
                    j += 1
                
                if j >= len(lines):
                    break
                
                # Find closing brace
                brace_count = 0
                block_start = j
                while j < len(lines):
                    for char in lines[j]:
                        if char == '{':
                            brace_count += 1
                        elif char == '}':
                            brace_count -= 1
                            if brace_count == 0:
                                end_line = j + 1  # 1-indexed
                                
                                # Extract full block content
                                content = ''.join(lines[i:j+1])
                                
                                blocks[class_name].append({
                                    'file': file_path.name,
                                    'start': start_line,
                                    'end': end_line,
                                    'lines': end_line - start_line + 1,
                                    'content': content.strip()
                                })
                                break
                    j += 1
                    if brace_count == 0:
                        break
                
                break
        
        i += 1
    
    return blocks

def main():
    base_dir = Path('/workspace/project/grpcSamples/octaneWebR')
    css_dir = base_dir / 'client/src/styles'
    
    # Unused selectors from previous analysis
    unused = [
        'scene-node-children',
        'scene-node-expand',
        'scene-node-handle',
        'scene-node-icon',
        'scene-node-indent',
        'scene-node-label',
        'scene-node-name',
        'scene-node-toggle',
        'scene-node-visibility',
        'scene-search-box',
        'scene-search-container',
        'scene-tree-item',
    ]
    
    print("🗑️  UNUSED CSS SELECTORS - DETAILED REPORT")
    print("=" * 80)
    print()
    
    total_lines = 0
    file_stats = defaultdict(lambda: {'count': 0, 'lines': 0, 'selectors': []})
    
    # Process each CSS file
    for css_file in sorted(css_dir.glob('*.css')):
        blocks = find_css_blocks(css_file, unused)
        
        if not blocks:
            continue
        
        print(f"📄 {css_file.name}")
        print("-" * 80)
        
        for class_name in sorted(blocks.keys()):
            for block in blocks[class_name]:
                print(f"\n  .{class_name}")
                print(f"    Lines: {block['start']}-{block['end']} ({block['lines']} lines)")
                print(f"    Preview:")
                
                # Show first 3 lines of content
                preview_lines = block['content'].split('\n')[:3]
                for line in preview_lines:
                    print(f"      {line}")
                if len(block['content'].split('\n')) > 3:
                    print(f"      ...")
                
                total_lines += block['lines']
                file_stats[css_file.name]['count'] += 1
                file_stats[css_file.name]['lines'] += block['lines']
                file_stats[css_file.name]['selectors'].append({
                    'name': class_name,
                    'start': block['start'],
                    'end': block['end'],
                    'lines': block['lines']
                })
        
        print()
    
    print("\n" + "=" * 80)
    print("📊 SUMMARY BY FILE:")
    print()
    
    for file_name in sorted(file_stats.keys()):
        stats = file_stats[file_name]
        print(f"  {file_name}:")
        print(f"    • {stats['count']} unused selectors")
        print(f"    • {stats['lines']} lines to remove")
        print()
    
    print("=" * 80)
    print(f"📈 TOTAL IMPACT:")
    print(f"  • {len(unused)} unused selectors")
    print(f"  • ~{total_lines} lines to remove")
    print("=" * 80)
    print()
    print("✅ RECOMMENDATION:")
    print("  Remove these selectors phase-by-phase, testing after each file.")
    print("  Start with files that have the most unused code.")
    print()

if __name__ == '__main__':
    main()
