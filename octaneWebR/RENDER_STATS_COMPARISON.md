# Render Stats Bar Comparison - octaneWebR vs Octane

## Reference Analysis

**Octane Official Format:**
```
Left:  1400.100 spp, 00:00:21 (finished)
Right: 1 sec, 69999 prt 1 mesh, NVIDIA GeForce RTX 4090 (RT), 1:48.21.2 24.0 GB
```

**octaneWebR Current Format:**
```
Left:  1.0 spp (1.2 sps), 00:00:00 (finished)
Right: 1920x1080, 1 mesh, NVIDIA GeForce RTX 4090 (RT), 1:48.21.2 / 24.0 GB
```

---

## Differences Identified

### ✅ CORRECT (Matches Octane):
1. **Left side format** - "spp, time (status)" ✅
2. **Mesh count** - "X mesh" ✅
3. **GPU name** - Shows full GPU name ✅
4. **Memory** - Shows total GB ✅

### ❌ DIFFERENCES (Need to match Octane):

#### 1. **SPS Display During Rendering**
- **Octane:** Does NOT show "(X.X sps)" during rendering
- **octaneWebR:** Currently shows "(1.2 sps)" when rendering
- **Action:** Remove or make optional

#### 2. **Resolution Display**
- **Octane:** Does NOT show resolution in stats bar
- **octaneWebR:** Shows "1920x1080"
- **Action:** Consider removing resolution (users can see viewport size)

#### 3. **Missing Metrics in Right Section**
- **Octane:** Shows "1 sec, 69999 prt" (render time in sec, particle/primitive count)
- **octaneWebR:** Missing these metrics
- **Action:** Add if data available from gRPC API

#### 4. **Version/Memory Separator**
- **Octane:** Space separator "1:48.21.2 24.0 GB"
- **octaneWebR:** Slash separator "1:48.21.2 / 24.0 GB"
- **Action:** Change "/" to " " (space)

---

## Proposed Format Changes

**New octaneWebR format (matching Octane exactly):**

```typescript
// Left side (render progress)
`${samples.toFixed(1)} spp, ${time} (${status})`

// Right side (GPU/system info)
`${meshCount} mesh, ${gpu}, ${version} ${memory}`
```

**Remove:**
- Samples per second display "(X.X sps)"
- Resolution display "1920x1080"

**Change:**
- Version/memory separator from "/" to " "

---

## Implementation Changes Needed

### File: `client/src/components/RenderToolbar/index.tsx`

**Current (lines 729-740):**
```typescript
<span id="render-samples-display">
  {renderStats.samples.toFixed(1)} spp
  {renderStats.status === 'rendering' && renderStats.samplesPerSecond > 0 && (
    <span className="samples-per-second"> ({renderStats.samplesPerSecond.toFixed(2)} sps)</span>
  )}
</span>
<span className="stats-separator">, </span>
<span id="render-time-display">{renderStats.time}</span>
<span> </span>
<span id="render-status-display" className={`render-status-${renderStats.status}`}>
  ({renderStats.status})
</span>
```

**Proposed:**
```typescript
<span id="render-samples-display">
  {renderStats.samples.toFixed(1)} spp
</span>
<span className="stats-separator">, </span>
<span id="render-time-display">{renderStats.time}</span>
<span> </span>
<span id="render-status-display" className={`render-status-${renderStats.status}`}>
  ({renderStats.status})
</span>
```

**Current (lines 748-754):**
```typescript
<span id="render-resolution-display">{renderStats.resolution}</span>
<span className="stats-separator">, </span>
<span id="render-mesh-count">{renderStats.meshCount} mesh</span>
<span className="stats-separator">, </span>
<span id="render-gpu-info">{renderStats.gpu}</span>
<span className="stats-separator">, </span>
<span id="render-memory-combined">{renderStats.version} / {renderStats.memory}</span>
```

**Proposed:**
```typescript
<span id="render-mesh-count">{renderStats.meshCount} mesh</span>
<span className="stats-separator">, </span>
<span id="render-gpu-info">{renderStats.gpu}</span>
<span className="stats-separator">, </span>
<span id="render-memory-combined">{renderStats.version} {renderStats.memory}</span>
```

---

## Visual Comparison

**Before (current octaneWebR):**
```
2.5 spp (1.2 sps), 00:00:12 (rendering) | 1920x1080, 1 mesh, NVIDIA GeForce RTX 4090 (RT), 1:48.21.2 / 24.0 GB
```

**After (matching Octane):**
```
2.5 spp, 00:00:12 (rendering) | 1 mesh, NVIDIA GeForce RTX 4090 (RT), 1:48.21.2 24.0 GB
```

---

## Summary

**Changes to make:**
1. ❌ Remove samples-per-second display "(X.X sps)"
2. ❌ Remove resolution display "1920x1080"
3. ✏️ Change version/memory separator from "/" to " "

**Result:** Stats bar will exactly match Octane's format.

