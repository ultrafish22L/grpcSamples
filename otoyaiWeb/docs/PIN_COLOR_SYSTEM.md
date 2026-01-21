# Pin and Edge Color System

The otoyaiWeb node graph uses a fine-grained color-coding system for pins (handles) and connection lines (edges) based on data types. This system is inspired by Octane Render's node graph interface.

## Color Palette

| Data Type | Color | Hex Code | Usage |
|-----------|-------|----------|-------|
| **String** | 🟠 Orange | `#ffaa44` | Text data, prompts, descriptions |
| **Integer** | 🟡 Yellow | `#ffdd44` | Whole numbers (steps, seed, width, height) |
| **Float** | 🔵 Cyan | `#00ddff` | Decimal numbers (guidance_scale, strength, temperature) |
| **Boolean** | 🔴 Red | `#ff4444` | True/false values (enable_safety_checker) |
| **Enum** | 🟣 Purple | `#cc44ff` | Selection lists (scheduler, sampler, aspect_ratio) |
| **Image** | 🟢 Green | `#44ff44` | Image data (input/output) |
| **Video** | 🟣 Magenta | `#ff44ff` | Video data (input/output) |
| **Audio** | 🔵 Blue | `#4499ff` | Audio data (input/output) |
| **JSON** | 🔵 Teal | `#44ffdd` | Structured JSON data |
| **Any** | ⚪ Gray | `#aaaaaa` | Generic/untyped data |

## Pin (Handle) States

Pins have two visual states:

### 1. **Filled (Solid)** 
- **Output Pins**: Filled when the node has a value to output
- **Input Pins**: Filled when the input has a value AND is not connected
- Visual: Solid circle with matching color

### 2. **Open (Outlined)**
- **Output Pins**: Outlined when the node has no value
- **Input Pins**: Always outlined (empty state for unconnected inputs)
- Visual: Circle with border in matching color, transparent fill

## Connection Lines (Edges)

Connection lines automatically match the color of their **source (output) pin** data type:

- **String connections**: Orange lines (`#ffaa44`)
- **Integer connections**: Yellow lines (`#ffdd44`)
- **Float connections**: Cyan lines (`#00ddff`)
- **Boolean connections**: Red lines (`#ff4444`)
- **Enum connections**: Purple lines (`#cc44ff`)
- **Image connections**: Green lines (`#44ff44`)
- **Video connections**: Magenta lines (`#ff44ff`)
- **Audio connections**: Blue lines (`#4499ff`)
- **JSON connections**: Teal lines (`#44ffdd`)
- **Generic connections**: Gray lines (`#aaaaaa`)

## Type Compatibility

### Exact Matches
Most connections require exact type matches (e.g., string → string, image → image).

### Compatible Conversions
- **Integer ↔ Float**: Automatically converts between whole numbers and decimals
- **Any Type**: Gray "any" type pins can connect to/from any other type

## Implementation Details

### CSS Classes
Pin colors are defined in `nodes.module.css`:
- `.handleString`, `.handleInteger`, `.handleFloat`, etc.
- Each has `.handleOpen` and `.handleFilled` variants

### Utility Functions
Located in `utils/connectionValidator.ts`:
- `getHandleType()`: Determines the data type of a pin
- `getHandleColorClass()`: Returns the CSS class name for a pin type
- `getHandleColorStyle()`: Returns the hex color value for edges
- `areTypesCompatible()`: Validates if two types can connect

### Edge Styling
Edges are styled in `store/useStore.ts` during the `onConnect` callback:
```typescript
const handleType = getHandleType(sourceNode, connection.sourceHandle, true);
const edgeColor = getHandleColorStyle(handleType);
const newEdge = {
  ...connection,
  style: { stroke: edgeColor, strokeWidth: 2 },
  animated: false,
};
```

## Visual Benefits

1. **Quick Type Recognition**: Users can instantly identify data types by color
2. **Connection Validation**: Mismatched colors indicate incompatible connections
3. **Data Flow Visualization**: Color-coded lines make it easy to trace data paths
4. **Professional Aesthetic**: Matches industry-standard node graph interfaces (Octane, Nuke, etc.)

## Example Workflows

### Text-to-Image Generation
- Text Input node (orange output) → FLUX prompt input (orange)
- FLUX guidance_scale input (cyan) ← Number Input node (cyan output)
- FLUX output (green) → Image node (green input)

### Image-to-Video Pipeline
- Image node (green output) → Video Generator image input (green)
- Text Input (orange) → Video Generator prompt (orange)
- Video Generator output (magenta) → Video node (magenta)

## Future Enhancements

Potential improvements to the color system:
- [ ] Hover tooltips showing data type names
- [ ] Color-blind friendly mode (patterns + colors)
- [ ] Custom color themes (dark/light variations)
- [ ] Animated flow direction indicators on edges
- [ ] Pin size variation based on data complexity
