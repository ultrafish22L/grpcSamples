# 🚀 Run Icon Extraction on Your Local Machine

Since the sandbox can't reliably connect to Octane, run the extraction **directly on your machine** where Octane is running.

---

## ✅ Prerequisites Checklist

Before running the script, ensure:

- [ ] **Octane Render is running**
- [ ] **LiveLink is enabled** - Go to: `Help → LiveLink` in Octane menu
- [ ] **Python 3.7+** installed
- [ ] **Required Python packages** installed:
  ```bash
  pip install grpcio protobuf
  ```

---

## 📋 Step-by-Step Instructions

### Step 1: Verify Octane LiveLink

1. Open Octane Render
2. Go to menu: **Help → LiveLink**
3. Check that LiveLink server shows as **running**
4. Note the port number (usually **51022**)
5. Look for console message like: `LiveLink server started on port 51022`

### Step 2: Navigate to Script Location

Open a terminal/command prompt and navigate to:

```bash
cd /path/to/grpcSamples/octaneProxy
```

**Example paths:**
- Windows: `cd C:\Users\YourName\grpcSamples\octaneProxy`
- Mac/Linux: `cd ~/grpcSamples/octaneProxy`

### Step 3: Test Connection

Run the diagnostic script:

```bash
python3 check_octane.py
```

**Expected output:**
```
Testing localhost:51022 (Local machine)... ✅ CONNECTED
```

If you see ❌ Failed, troubleshoot:
- Restart Octane
- Re-enable LiveLink
- Check firewall settings
- Try different port if Octane shows different number

### Step 4: Run Extraction

**Option A: Extract to octaneWebR (recommended)**

```bash
python3 extract_all_icons.py
```

Icons will be saved to: `octaneWebR/client/public/icons/nodes/`

**Option B: Extract to Desktop (standalone)**

```bash
python3 extract_icons_standalone.py
```

Icons will be saved to: `~/Desktop/octane_icons/nodes/`

### Step 5: Monitor Progress

You'll see output like:

```
======================================================================
 🎨 Octane FULL Icon Extraction
======================================================================

🔌 Connecting to Octane at localhost:51022...
✅ Connected successfully

📊 Found 755 node types
📂 Found 17 existing icons (will skip)

🚀 Starting extraction of 755 node types...
⏱️  Delay between icons: 0.1s

  [   1/755] NT_ANIMATION_SETTINGS                      | ✅  0 ⚠️  0 ❌ 0 | 0.5/s | ETA 25m
  [  10/755] NT_AOV_ALPHA                               | ✅  8 ⚠️  1 ❌ 0 | 0.8/s | ETA 15m
  [  20/755] NT_CAM_PANORAMIC                           | ✅ 17 ⚠️  2 ❌ 0 | 1.2/s | ETA 10m
  ...
```

**Key indicators:**
- ✅ = Successfully extracted
- ⚠️  = No icon available (normal for some types)
- ❌ = Error (will be reported)
- Rate = Icons per second
- ETA = Estimated time remaining

### Step 6: Handle Interruptions

**If connection is lost:**
- The script will save progress and exit
- Just run the script again - it will skip already-extracted icons
- It will resume from where it left off

**If Octane crashes:**
1. Restart Octane
2. Re-enable LiveLink
3. Run script again to resume

**Manual interrupt (Ctrl+C):**
- Progress is automatically saved
- Run again to resume

---

## ⏱️  Expected Duration

- **Per icon:** ~0.5-1 second (256 gRPC calls per 16x16 icon)
- **755 node types:** 15-30 minutes total
- **With resume:** Can be done in multiple sessions

**Factors affecting speed:**
- Network/gRPC performance
- Octane responsiveness
- System load

---

## 📊 After Extraction

### Verify Icons

**Check icon count:**

```bash
# On Windows (PowerShell)
(Get-ChildItem octaneWebR\client\public\icons\nodes\*.png).Count

# On Mac/Linux
ls -1 octaneWebR/client/public/icons/nodes/*.png | wc -l
```

**Expected:** 680-720 icons (not all 755 types have icons)

### View Sample Icons

```bash
# Mac
open octaneWebR/client/public/icons/nodes/

# Windows
explorer octaneWebR\client\public\icons\nodes\

# Linux
xdg-open octaneWebR/client/public/icons/nodes/
```

### Copy Icons to octaneWebR (if using standalone version)

If you used `extract_icons_standalone.py` and icons are on Desktop:

```bash
# Copy from Desktop to project
cp -r ~/Desktop/octane_icons/nodes/*.png octaneWebR/client/public/icons/nodes/
```

---

## 🎯 Extraction Complete - Next Steps

### 1. Verify Icons in Browser

Start the octaneWebR dev server:

```bash
cd octaneWebR
npm run dev
```

Open: `http://localhost:5173/icon-verification.html`

### 2. Use Icons in React Components

```typescript
import { NodeIcon } from '@/utils/IconLoader';

function MyComponent() {
  return <NodeIcon nodeType="NT_MAT_DIFFUSE" size={24} />;
}
```

### 3. Extract Graph Icons (Optional)

Modify `extract_all_icons.py` to also extract GT_* types:

```python
# Add after node types extraction:
graph_types = {}
for attr_name in dir(octaneids_pb2):
    if attr_name.startswith('GT_') and not attr_name.startswith('GT__'):
        value = getattr(octaneids_pb2, attr_name)
        if isinstance(value, int):
            graph_types[attr_name] = value

# Change output_dir to:
output_dir = ... / 'icons' / 'graphs'
```

---

## 🔧 Troubleshooting

### "Import Error: No module named 'generated'"

**Solution:**
```bash
cd octaneProxy
ls generated/  # Verify folder exists
python3 -c "import sys; sys.path.append('generated'); from generated import octaneids_pb2"
```

If files are missing, regenerate from `.proto` files.

### "Connection refused"

**Checklist:**
1. Is Octane running? ✓
2. Is LiveLink enabled? ✓
3. Correct port (51022)? ✓
4. Firewall blocking? Try disabling temporarily
5. Try different host:
   - `localhost`
   - `127.0.0.1`
   - `host.docker.internal` (if in Docker)

### "Socket closed" during extraction

**This is normal!** Just run the script again:
```bash
python3 extract_all_icons.py
```

It will resume from where it left off.

### Very slow extraction (< 0.5 icons/sec)

**Solutions:**
- Close other applications using Octane
- Reduce `DELAY_BETWEEN_ICONS` in script (try `0.01` or `0`)
- Check system resource usage

### Icons are all black/transparent

**Causes:**
- Icon types don't have visual icons (normal for some types)
- Try different node types like `NT_MAT_DIFFUSE`, `NT_TEX_IMAGE`

---

## 📁 File Locations

**Scripts:**
```
octaneProxy/
├── extract_all_icons.py           # Main extractor (saves to octaneWebR)
├── extract_icons_standalone.py    # Standalone (saves to Desktop)
├── check_octane.py                # Connection diagnostic
└── generated/                     # Protobuf files (must exist)
```

**Output:**
```
octaneWebR/client/public/icons/
├── nodes/
│   ├── NT_MAT_DIFFUSE.png
│   ├── NT_MAT_GLOSSY.png
│   └── ... (755 types, ~700 actual icons)
└── graphs/
    └── GT_*.png (to be extracted)
```

---

## 💡 Pro Tips

1. **Run overnight:** If connection is unstable, run overnight with resume
2. **Check logs:** Script saves `extraction_log.txt` for debugging
3. **Batch extraction:** Do 100 icons at a time, modify script:
   ```python
   for i, (name, type_id) in enumerate(sorted(node_types.items())[:100], 1):
   ```
4. **Parallel execution:** Can run multiple instances with different ranges
5. **Use fast SSD:** Save to SSD for faster file I/O

---

## ✅ Success Criteria

When extraction is complete, you should have:

- ✅ 680-720 PNG icon files
- ✅ All files are valid PNG format (16x16 RGBA)
- ✅ Icons viewable in image viewer
- ✅ Icons load in browser (`icon-verification.html`)
- ✅ React `IconLoader.ts` component works

**You're ready to use Octane icons in octaneWebR!** 🎉

