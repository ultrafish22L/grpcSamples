# 🚀 Icon Extraction - START HERE

## Quick Start (3 Steps)

### 1️⃣ Test Connection & Diagnosis
```bash
cd /workspace/project/grpcSamples/octaneProxy
python3 test_icon_extraction_methods.py
```
**Time:** ~30 seconds  
**Purpose:** Verify Octane connection and test extraction methods

### 2️⃣ Extract All Icons
```bash
python3 extract_icons_fixed.py
```
**Time:** ~5-10 minutes  
**Purpose:** Extract all 755+ node type icons

### 3️⃣ Verify Success
```bash
ls -lh ../octaneWebR/client/public/icons/nodes/ | wc -l
```
**Expected:** 500-600 PNG files

## ✅ Done!
Icons are now available in octaneWebR at:
```
/icons/nodes/NT_MAT_DIFFUSE.png
/icons/nodes/NT_MAT_GLOSSY.png
/icons/nodes/NT_TEX_IMAGE.png
... (500+ more)
```

## 📚 Documentation

- **Quick Summary:** [ICON_FIX_SUMMARY.md](ICON_FIX_SUMMARY.md)
- **Technical Details:** [ICON_EXTRACTION_FIX.md](ICON_EXTRACTION_FIX.md)
- **Testing Guide:** [TESTING_CHECKLIST.md](TESTING_CHECKLIST.md)
- **Complete Overview:** [ICON_EXTRACTION_COMPLETE.md](ICON_EXTRACTION_COMPLETE.md)

## ❓ Problems?

### Octane Not Connected
```
❌ Connection failed
```
**Fix:** Make sure Octane is running with LiveLink enabled (Help → LiveLink)

### Script Crashes
```
⚠️ CONNECTION LOST
```
**Fix:** Just run again - it will resume from where it stopped

### Icons Not Showing
```bash
# Verify icons exist
ls ../octaneWebR/client/public/icons/nodes/NT_*.png | head -5

# Check octaneWebR is running
cd ../octaneWebR && npm run dev
```

## 🎯 What Was Fixed?

**Before:** Old script crashed Octane immediately  
**After:** New script uses hybrid approach - reliable + fast

**Root Cause:** Type mismatch (ApiImage vs ApiImageBuffer)  
**Solution:** Try direct save, fallback to pixel-by-pixel

See [ICON_FIX_SUMMARY.md](ICON_FIX_SUMMARY.md) for details.

---

**Ready to go? Start with step 1 above!** ⬆️
