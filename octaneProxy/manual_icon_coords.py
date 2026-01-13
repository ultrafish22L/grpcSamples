#!/usr/bin/env python3
"""
Manual icon extraction with known coordinates
Once you save octane_reference.png, this will extract specific icons
"""

from PIL import Image
from pathlib import Path

# Icon extraction coordinates from the reference screenshot
# Based on the visible layout: icon at x, text label next to it

# Define the node list - we can see the names in the screenshot
NODES_COL1 = [
    "2D transformation", "3D rotation", "3D scale", "3D transformation",
    "AOV", "AOV out", "Add", "Add Area3", "Add bloom", "Add glare",
    # ... add all visible nodes
]

# Simple extraction if you provide the screenshot
def extract_if_available():
    img_path = Path("octane_reference.png")
    
    if not img_path.exists():
        print("❌ Please save the screenshot to: octane_reference.png")
        print("\nThen run: python3 extract_all_icons_comprehensive.py octane_reference.png")
        return False
    
    print("✅ Found screenshot! Processing...")
    return True

if __name__ == '__main__':
    if extract_if_available():
        print("Ready to extract!")
    else:
        print("\n💡 Quick tip: Right-click the screenshot and save as 'octane_reference.png'")
