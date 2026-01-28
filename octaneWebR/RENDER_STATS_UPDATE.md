# Render Stats Bar Update - Octane Format Match

## Changes Made

### Visual Format
**Before:**
```
1.0 spp, 00:00:00 (finished) | 1 mesh, GPU Name, Version Memory
```

**After (Matching Octane):**
```
[Progress Bar] 0/0/5000 s/px, 0 Ms/sec, 00:00:00/00:00:00 (finished) | 0 prt, 1 mesh, GPU Name, Version/Memory
```

---

## Left Side (Render Progress)

### 1. Progress Bar
- **Visual indicator** showing render completion percentage
- Background color: `rgba(0, 150, 255, 0.15)`
- Width dynamically updates: `(currentSamples / maxSamples) * 100%`
- Positioned absolutely behind stats text

### 2. Samples Format: `current/denoised/max s/px`
**Example:** `1304/2720/5000 s/px`

| Field | Proto Source | Description |
|-------|--------------|-------------|
| `currentSamples` | `beautySamplesPerPixel` | Current samples rendered |
| `denoisedSamples` | `denoisedSamplesPerPixel` | Denoised sample count |
| `maxSamples` | `beautyMaxSamplesPerPixel` | Target max samples |

### 3. Render Speed: `Ms/sec`
**Example:** `695 Ms/sec`

- **Source:** `beautySamplesPerSecond` (proto field)
- **Conversion:** `samplesPerSecond / 1,000,000` = mega-samples/sec
- **Display:** Rounded to integer (no decimals)

### 4. Time Format: `current/estimated`
**Example:** `00:00:02/00:00:03`

| Field | Proto Source | Format |
|-------|--------------|--------|
| `currentTime` | `renderTime` | HH:MM:SS |
| `estimatedTime` | `estimatedRenderTime` | HH:MM:SS |

### 5. Status Display
- **`(rendering...)`** - When render is active (state = 2)
- **`(finished)`** - When render completes (state = 4)
- **`(paused)`** - When render is paused (state = 3)
- **`(stopped)`** - When render is stopped (state = 0)

---

## Right Side (System Info)

### 1. Primitive Count: `prt`
**Example:** `4032 prt`

- **Field:** `primitiveCount`
- **Note:** Currently initialized to `0` (needs data source from proto)

### 2. Mesh Count: `mesh`
**Example:** `1 mesh`

- **Field:** `meshCount`
- **Note:** Static value, needs scene API integration

### 3. GPU Name
**Example:** `NVIDIA GeForce RTX 4090 (RT)`

- **Field:** `gpu`
- **Note:** Needs device info API

### 4. Version / Memory
**Example:** `1:48.21.2/24.0 GB`

- **Format:** `version/memory` (using **`/`** separator)
- **Restored separator** from previous commit that removed it

---

## RenderStats Interface Changes

```typescript
// OLD
interface RenderStats {
  samples: number;              // Single value
  time: string;                 // Only current time
  status: ...
  resolution: string;           // REMOVED
  samplesPerSecond: number;     // Raw value
  meshCount: number;
  gpu: string;
  version: string;
  memory: string;
}

// NEW
interface RenderStats {
  currentSamples: number;       // 1304
  denoisedSamples: number;      // 2720
  maxSamples: number;           // 5000
  megaSamplesPerSec: number;    // 695 (in Ms/sec)
  currentTime: string;          // 00:00:02
  estimatedTime: string;        // 00:00:03
  progressPercent: number;      // 0-100 for bar
  status: ...
  primitiveCount: number;       // 4032 prt (NEW)
  meshCount: number;
  gpu: string;
  version: string;
  memory: string;
}
```

---

## Proto Field Mapping

From `RenderResultStatistics` (octanerenderpasses.proto):

| Proto Field | RenderStats Field | Conversion |
|-------------|-------------------|------------|
| `beautySamplesPerPixel` | `currentSamples` | Direct |
| `denoisedSamplesPerPixel` | `denoisedSamples` | Direct |
| `beautyMaxSamplesPerPixel` | `maxSamples` | Direct |
| `beautySamplesPerSecond` | `megaSamplesPerSec` | ÷ 1,000,000 |
| `renderTime` | `currentTime` | Format HH:MM:SS |
| `estimatedRenderTime` | `estimatedTime` | Format HH:MM:SS |
| `state` | `status` | Enum mapping |

---

## Status Enum Mapping

```typescript
// RenderState proto enum
switch (stats.state) {
  case 0: status = 'stopped'; break;         // RSTATE_STOPPED
  case 1: status = 'waiting'; break;         // RSTATE_WAITING_FOR_DATA
  case 2: status = 'rendering'; break;       // RSTATE_RENDERING
  case 3: status = 'paused'; break;          // RSTATE_PAUSED
  case 4: status = 'finished'; break;        // RSTATE_FINISHED
  default: status = 'error'; break;
}
```

---

## Progress Bar Calculation

```typescript
const progressPercent = maxSamples > 0 
  ? Math.min(100, (currentSamples / maxSamples) * 100) 
  : 0;
```

**Behavior:**
- `0%` when `currentSamples = 0`
- `100%` when `currentSamples >= maxSamples`
- Capped at `100%` using `Math.min()`

---

## CSS Styling

### Progress Bar
```typescript
{
  position: 'absolute',
  left: 0,
  top: 0,
  bottom: 0,
  width: `${progressPercent}%`,
  backgroundColor: 'rgba(0, 150, 255, 0.15)',  // Semi-transparent blue
  transition: 'width 0.3s ease',               // Smooth animation
  pointerEvents: 'none',
  zIndex: 0
}
```

### Stats Text (Layered Above)
```typescript
{
  position: 'relative',
  zIndex: 1,
  display: 'flex',
  alignItems: 'center',
  gap: '4px'
}
```

---

## Testing Recommendations

### 1. Start Development Server
```bash
npm run dev
```

### 2. Monitor Console Logs
Look for full JSON statistics data from server:
```
📊 OnStatisticsData callback received: { ... }
✅ Got render statistics (FULL RESPONSE): { ... }
```

### 3. Verify Display Updates
- **Samples:** Should show `current/denoised/max` format
- **Speed:** Should show mega-samples/sec (Ms/sec)
- **Time:** Should show `current/estimated` format
- **Progress Bar:** Should animate from 0% to 100%
- **Status:** Should show `(rendering...)` when active

### 4. Check for Missing Data
If any values are always `0`:
- `primitiveCount` - May need scene API call
- `meshCount` - May need geometry API call
- `denoisedSamples` - May be 0 if denoising disabled

---

## Known Data Gaps

### Primitive Count
- **Currently:** Initialized to `0`
- **Needs:** Scene/geometry API to fetch primitive count
- **Proto Source:** Unknown (not in `RenderResultStatistics`)

### Mesh Count
- **Currently:** Static value `1`
- **Needs:** Scene API integration
- **Proto Source:** Unknown (not in `RenderResultStatistics`)

### GPU Info
- **Currently:** Static placeholder
- **Needs:** Device info API call
- **Proto Source:** Separate device info API

---

## Summary

✅ **Completed:**
- Progress bar visual indicator
- Three-part samples display (current/denoised/max)
- Mega-samples per second display
- Two-part time display (current/estimated)
- Primitive count field (data pending)
- Status text format
- Version/memory separator restored

📊 **Data Flow:**
1. `OnStatisticsData` callback triggers
2. Call `getRenderStatistics()` API
3. Parse `RenderResultStatistics` fields
4. Update React state
5. Render stats bar updates automatically

🔍 **Next Steps:**
1. Test with dev server running
2. Verify all proto fields populate correctly
3. Identify APIs for missing data (primitives, mesh count, GPU info)
4. Add scene/device info API calls if needed
