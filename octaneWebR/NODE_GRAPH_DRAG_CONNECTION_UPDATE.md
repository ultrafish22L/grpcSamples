# Node Graph Connection Drag Enhancement

**Date:** 2025-01-20  
**Component:** NodeGraphEditorNew.tsx  
**Status:** ✅ Complete - Build Successful (Correct Octane behavior)

---

## 🎯 Octane Connection Behavior

**Output Pins (Source):**
- Can connect to **multiple** input pins (one-to-many)
- When dragging from output, original connections **stay visible**
- New connection is **added**, not replaced

**Input Pins (Target):**
- Can only connect to **one** output pin (many-to-one)
- When dragging from input, original connection **stays visible during drag**
- Original connection is **replaced only on successful connection**
- If cancelled (dropped in empty space), original connection stays

---

## 🎯 Features Implemented

### 1. **Pin Color Matching During Connection Drag**
When you drag a connection line from a pin, the line color dynamically matches the source pin's color.

**Implementation:**
- Added `connectionLineColor` state to track current drag color
- `onConnectStart` handler captures source handle color from pin metadata
- `connectionLineStyle` prop applies dynamic color to dragging line
- `onConnectEnd` resets color to default when drag completes

**Visual Result:**
- Red pin → Red drag line
- Blue pin → Blue drag line
- Green pin → Green drag line
- Matches the colored pins exactly

---

### 2. **Smart Connection Replacement (Octane Behavior)**

**Output Pins:** Support multiple connections (one-to-many)
- Original edges stay visible during drag
- New connection is added alongside existing ones

**Input Pins:** Support single connection only (many-to-one)
- Original edge stays visible during drag
- Old connection replaced only when new connection succeeds
- If drag cancelled, original connection preserved

**Implementation:**
- `connectingEdgeRef` tracks if dragging FROM an input pin (for source replacement)
- `onConnectStart` detects handleType to distinguish output vs input behavior
- `onConnect` checks both source and target for existing input connections
- Old edges removed only on successful connection (not during drag)

**User Experience:**
- Drag from output → adds new connection (multi-connect)
- Drag from input → replaces old connection on success
- All original edges visible during drag (Octane standard behavior)
- Cancel drag (drop in empty space) → no changes made

---

## 🔧 Technical Details

### New State Variables
```typescript
const [connectionLineColor, setConnectionLineColor] = useState('#4a90e2');
const connectingEdgeRef = useRef<Edge | null>(null);
```

### New Event Handlers

#### onConnectStart
- **Purpose:** Capture source pin color when drag starts
- **Color Detection:** Checks `nodeData.output.pinInfo.pinColor` (source) or `nodeData.inputs[].pinInfo.pinColor` (target)
- **Edge Detection:** Finds existing edges connected to the handle being dragged
- **Logging:** Console logs with 🔌 marker

#### onConnectEnd
- **Purpose:** Cleanup when drag ends (successful or cancelled)
- **Actions:** Resets connection color to default, clears connecting edge reference

#### onConnect (Enhanced)
- **Purpose:** Create new connection with proper color
- **Disconnect Logic:** Removes old edge from state if reconnecting
- **Pin Index:** Extracts pin index from `targetHandle` (format: "input-N")
- **Color Preservation:** Uses captured `connectionLineColor` for new edge styling

#### onEdgesChange (Enhanced)
- **Purpose:** Track edge removals during reconnection
- **Actions:** Stores removed edge reference for reconnection handling
- **Base Handler:** Calls original `onEdgesChangeBase` from `useEdgesState`

---

## 📊 ReactFlow Props Added

```typescript
<ReactFlow
  // ... existing props
  onConnectStart={onConnectStart}      // NEW: Track drag start
  onConnectEnd={onConnectEnd}          // NEW: Track drag end
  connectionLineStyle={{               // NEW: Dynamic line color
    stroke: connectionLineColor,
    strokeWidth: 3,
  }}
/>
```

---

## 🎨 Color Flow

1. **Scene Load:** Edges created with pin colors from `nodeInfo.inputs[].pinInfo.pinColor`
2. **Drag Start:** `onConnectStart` reads pin color → sets `connectionLineColor` state
3. **During Drag:** `connectionLineStyle` applies `connectionLineColor` to dragging line
4. **Connection Made:** `onConnect` creates edge with same `connectionLineColor`
5. **Drag End:** `onConnectEnd` resets color to default

---

## 🧪 Testing Checklist

### Manual Testing (Requires Octane Running)
- [ ] Load scene with connected nodes
- [ ] Drag new connection from output pin → line matches pin color
- [ ] Drag new connection from input pin → line matches pin color
- [ ] Drag from connected pin → old line disappears
- [ ] Complete reconnection → new connection appears with correct color
- [ ] Cancel reconnection (release in empty space) → original connection restored
- [ ] Test with multiple pin colors (red, blue, green, etc.)

### Console Log Patterns
Look for these emoji markers in browser console:
- `🔌` Connection drag started/ended
- `🎨` Setting connection line color
- `📌` Reconnecting existing edge
- `🔄` Disconnecting old edge
- `🔗` Creating connection

---

## 📝 Known Limitations

1. **Octane API Disconnect:** TODO comment in code - need to call Octane API to properly disconnect old connection
   - Current: Only removes edge from UI state
   - Needed: Call `ApiNode.disconnectPin` or similar before creating new connection

2. **Multiple Connections:** Logic assumes one connection per handle
   - Octane may allow multiple outputs from one source
   - Current implementation only tracks one edge per handle

3. **Pin Index Extraction:** Assumes format "input-N" for target handles
   - Works for current implementation
   - May need adjustment if handle ID format changes

---

## 🚀 Future Enhancements

1. **Edge Hover Preview:** Show connection color on edge hover
2. **Connection Validation:** Check if connection types are compatible before allowing
3. **Animated Reconnection:** Smooth animation when moving existing connection
4. **Undo/Redo:** Track connection changes for undo functionality
5. **Multi-Select Reconnect:** Reconnect multiple edges at once

---

## 📁 Files Modified

- `client/src/components/NodeGraph/NodeGraphEditorNew.tsx` - Main implementation

## 📦 Build Status

✅ TypeScript compilation successful  
✅ Vite build successful  
✅ Bundle size: 379.43 kB (gzip: 120.29 kB)  
✅ No TypeScript errors

---

**Implementation Complete** - Ready for testing with live Octane instance
