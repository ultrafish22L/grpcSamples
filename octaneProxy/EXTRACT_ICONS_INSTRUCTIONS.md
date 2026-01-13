# How to Extract ALL Icons from Octane SE Reference Screenshot

## Step 1: Save the Reference Image

Save the reference screenshot you provided to:
```
/workspace/project/grpcSamples/octaneProxy/octane_reference.png
```

## Step 2: Run the Comprehensive Extractor

```bash
cd /workspace/project/grpcSamples/octaneProxy
python3 extract_all_icons_comprehensive.py octane_reference.png
```

This will extract:
- ✅ **Node icons** (all 755+ types from the left panel)
- ✅ **Toolbar icons** (top button bar)
- ✅ **UI control icons** (right panel controls)
- ✅ **Menu icons**
- ✅ **Status bar icons**
- ✅ **Everything visible!**

## What Gets Extracted

### Node Icons (Left Panel)
The script scans 7 columns of node types:
- Column 1: Starting with "2D transformation", "3D rotation", etc.
- Column 2: "Check texture", "Checks", "Circle spiral", etc.
- Column 3: "Enum value", "Environment AOV", etc.
- Column 4: "Fit to float", "Hit value", etc.
- Column 5: "OCIO view in", "OCIO view out", etc.
- Column 6: "Remove hot pixels", "Render AOV", etc.
- Column 7: "Tangent", "TeaColor", "Texture", etc.

### Toolbar Icons (Top)
All buttons from the top toolbar including:
- File operations
- Edit tools
- View controls
- Render controls
- etc.

### UI Control Icons (Right Panel)
Icons from the Node Inspector and other panels:
- Collapse/expand arrows
- Lock icons
- Visibility toggles
- Parameter controls
- etc.

## Output Structure

```
octaneWebR/client/public/icons/extracted/
├── nodes_col1/         # First column of nodes
│   ├── icon_0000_nodes_col1.png
│   ├── icon_0001_nodes_col1.png
│   └── ...
├── nodes_col2/         # Second column
├── nodes_col3/         # Third column
├── nodes_col4/         # Fourth column
├── nodes_col5/         # Fifth column
├── nodes_col6/         # Sixth column
├── nodes_col7/         # Seventh column
├── toolbar/            # Toolbar buttons
├── extracted_icons_metadata.json  # Metadata with positions
└── _overview.png       # Visual overview of all extracted icons
```

## Step 3: Match Icons to Node Names

After extraction, you'll need to match the extracted icons to their node type names.

The reference screenshot shows the names next to each icon, so you can:

1. Open `_overview.png` to see all extracted icons
2. Match each icon to its text label from the screenshot
3. Rename files from `icon_0000_nodes_col1.png` to proper names like `NT_MAT_DIFFUSE.png`

## Alternative: OCR-Based Extraction

For automatic name matching, we can use OCR (Optical Character Recognition) to read the text labels next to each icon and automatically name the files.

Would you like me to create an OCR-enhanced version that automatically matches icon names?

## Manual Extraction (If Automated Fails)

If the automated extraction doesn't work perfectly, you can manually extract regions:

```python
from PIL import Image

img = Image.open('octane_reference.png')

# Extract a specific icon (example coordinates)
icon = img.crop((10, 15, 26, 31))  # (left, top, right, bottom)
icon.save('NT_SOME_NODE.png')
```

Find the coordinates by opening the screenshot in an image editor that shows pixel positions.

## Next Steps

Once icons are extracted:

1. Review the `_overview.png` to verify quality
2. Match icons to proper NT_* names
3. Move to `octaneWebR/client/public/icons/nodes/`
4. Use in the React app!

---

**Ready to extract?** Just save the reference screenshot to `octane_reference.png` and run the script!
