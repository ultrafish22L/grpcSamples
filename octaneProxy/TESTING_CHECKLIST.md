# Icon Extraction - Testing Checklist

## Prerequisites (Before Testing)

- [ ] Octane Render Studio SE is running
- [ ] LiveLink is enabled in Octane (Help → LiveLink in menu)
- [ ] Port 51022 is accessible (not blocked by firewall)
- [ ] Python 3 is installed with grpcio and protobuf packages

## Phase 1: Diagnostic Test

### Run Diagnostic Script
```bash
cd /workspace/project/grpcSamples/octaneProxy
python3 test_icon_extraction_methods.py
```

### Expected Output
```
TEST 1: Connection Test
✅ Connection successful

TEST 2: Get Icon Reference
✅ Got icon reference: handle=XXXX, type=X

TEST 3: ApiImageBuffer.save() Method
[Either ✅ SUCCESS or ❌ FAILED with TYPE_MISMATCH]

TEST 4: ApiImage Dimension Methods
✅ Width: 16
✅ Height: 16

TEST 5: ApiImage.pixelAt() Method
✅ Pixel at (0,0): R:X.XXX G:X.XXX B:X.XXX A:X.XXX

📊 TEST SUMMARY
✅ Connection: SUCCESS
✅ Get icon reference: SUCCESS
[...diagnostic results...]
```

### Verify
- [ ] Connection test passes
- [ ] Icon reference retrieved (handle > 0)
- [ ] At least one extraction method works
- [ ] No connection errors
- [ ] No Octane crashes

### If Diagnostic Fails
- Check Octane is running with LiveLink enabled
- Verify network connectivity to localhost:51022
- Check Python dependencies: `pip3 install grpcio protobuf`
- Review error messages for specific issues

## Phase 2: Extract Single Icon Test

### Run Fixed Extraction Script (Limited)
```bash
# Edit extract_icons_fixed.py temporarily to limit to first 5 icons
# Or just let it run and interrupt after first few succeed
python3 extract_icons_fixed.py
```

### Monitor First 5 Icons
Watch for:
- [ ] No Octane crashes
- [ ] Progress updates appear
- [ ] Icons save to disk
- [ ] File sizes are reasonable (>100 bytes)
- [ ] PNG format is valid

### Verify Files Created
```bash
ls -lh ../octaneWebR/client/public/icons/nodes/
file ../octaneWebR/client/public/icons/nodes/NT_*.png | head -5
```

Expected:
```
NT_MAT_DIFFUSE.png: PNG image data, 16 x 16, 8-bit/color RGBA
```

### Check Icon Quality
```bash
# View an icon (if you have image viewer)
open ../octaneWebR/client/public/icons/nodes/NT_MAT_DIFFUSE.png
# or
xdg-open ../octaneWebR/client/public/icons/nodes/NT_MAT_DIFFUSE.png
```

Verify:
- [ ] Icon is visible (not corrupted)
- [ ] Icon has correct aspect ratio
- [ ] Icon shows expected Octane node graphic
- [ ] Alpha channel preserved (transparency visible)

## Phase 3: Full Extraction

### Run Complete Extraction
```bash
python3 extract_icons_fixed.py
```

### Monitor During Extraction
Watch for:
- [ ] Progress updates every 25 icons
- [ ] Success count increasing
- [ ] Rate staying steady (1-3 icons/sec)
- [ ] ETA reasonable (5-10 minutes total)
- [ ] No connection errors
- [ ] Octane remains stable

### If Interrupted
Just run again:
```bash
python3 extract_icons_fixed.py
```
It will skip already-extracted icons and resume.

### Expected Duration
- **Fast path (Method 1 works):** ~3-5 minutes for 755 icons
- **Fallback path (Method 2):** ~8-12 minutes for 755 icons
- **Hybrid (some of each):** ~5-8 minutes

## Phase 4: Verification

### Count Icons Extracted
```bash
cd ../octaneWebR/client/public/icons/nodes
ls *.png | wc -l
```

Expected: **500-600 icons** (some node types don't have icons)

### Check File Sizes
```bash
ls -lh | head -20
```

Expected: Most files 200-800 bytes (16x16 PNG with alpha)

### Validate PNG Format
```bash
file *.png | grep -v "PNG image data" | wc -l
```

Expected: **0** (all files should be valid PNGs)

### Test Random Sample
```bash
# Check 5 random icons
ls *.png | shuf -n 5 | while read f; do
    echo "$f: $(file "$f")"
done
```

All should show: `PNG image data, 16 x 16, 8-bit/color RGBA`

### Disk Space Used
```bash
du -sh .
```

Expected: **~300KB - 1MB** total for all icons

## Phase 5: Integration with octaneWebR

### Check Icons Accessible
```bash
cd /workspace/project/grpcSamples/octaneWebR
npm run dev
```

### Test Icon Display
1. Open http://localhost:43929 in browser
2. Open Node Graph Editor
3. Right-click → Create Node
4. Check if node type icons appear in menus
5. Create a node → Check if node has icon

### Verify in Browser Console
```javascript
// Test icon loading
const img = new Image();
img.src = '/icons/nodes/NT_MAT_DIFFUSE.png';
img.onload = () => console.log('✅ Icon loaded:', img.width, 'x', img.height);
img.onerror = () => console.error('❌ Icon failed to load');
```

Expected: `✅ Icon loaded: 16 x 16`

## Troubleshooting

### Problem: Octane Crashes During Extraction
**Solution:** Use more conservative delays
```python
# Edit extract_icons_fixed.py
DELAY_BETWEEN_ICONS = 0.3      # Increase to 300ms
DELAY_BETWEEN_API_CALLS = 0.1  # Increase to 100ms
```

### Problem: Connection Lost Mid-Extraction
**Solution:** Just run again - it resumes automatically
```bash
python3 extract_icons_fixed.py
```

### Problem: Some Icons Corrupted
**Solution:** Delete and re-extract
```bash
rm ../octaneWebR/client/public/icons/nodes/NT_SPECIFIC_NODE.png
python3 extract_icons_fixed.py  # Will re-extract missing ones
```

### Problem: Very Slow Extraction (>20 minutes)
**Solution:** Method 2 (pixel-by-pixel) is being used. This is normal but slow.
- Check diagnostic test to confirm Method 1 fails
- Consider batching: extract in chunks with breaks

### Problem: Icons Not Showing in octaneWebR
**Checklist:**
1. Icons exist in `client/public/icons/nodes/`
2. File names match node type constants (e.g., `NT_MAT_DIFFUSE.png`)
3. Vite dev server is running
4. Browser cache cleared (hard refresh: Ctrl+Shift+R)
5. Check browser console for 404 errors

## Success Criteria

- [ ] ✅ 500+ icons extracted without crashing Octane
- [ ] ✅ All PNG files valid and properly formatted
- [ ] ✅ Icons display correctly in octaneWebR UI
- [ ] ✅ Node menus show appropriate icons
- [ ] ✅ No console errors related to icon loading
- [ ] ✅ Icons match Octane SE appearance

## Report Template

After testing, report results:

```
ICON EXTRACTION TEST RESULTS
============================

Date: YYYY-MM-DD
Octane Version: X.X
Python Version: 3.X

Phase 1: Diagnostic Test
- Connection: [PASS/FAIL]
- Icon Reference: [PASS/FAIL]
- Method 1 (Buffer Save): [PASS/FAIL]
- Method 2 (Pixel-by-Pixel): [PASS/FAIL]

Phase 2: Single Icon Test
- First 5 icons extracted: [PASS/FAIL]
- No crashes: [PASS/FAIL]
- Valid PNG format: [PASS/FAIL]

Phase 3: Full Extraction
- Total icons: XXX
- Duration: XX minutes
- Method used: [1/2/Hybrid]
- Errors encountered: XXX
- Octane stability: [Stable/Crashed X times]

Phase 4: Verification
- Valid PNG files: XXX/XXX
- Average file size: XXX bytes
- Corrupted files: XXX

Phase 5: Integration
- Icons display in octaneWebR: [YES/NO]
- Node menus show icons: [YES/NO]
- Browser console errors: [NONE/SOME/MANY]

Overall: [SUCCESS/PARTIAL/FAILED]

Notes:
[Any observations, issues, or recommendations]
```
