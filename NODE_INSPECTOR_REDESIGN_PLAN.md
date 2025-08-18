# Node Inspector Redesign Plan - Match Octane Studio Exactly

## 🚨 **CRITICAL REQUIREMENT: REAL OCTANE ONLY**

**⚠️ NEVER EVER use mock or simulated data - only real live connection with Octane LiveLink service.**

## 🎯 OBJECTIVE
Redesign octaneWeb's Node Inspector to match the professional Octane Studio interface exactly as shown in the reference screenshot.

## 📸 REFERENCE ANALYSIS
From the Octane Studio screenshot, the Node Inspector shows:

### Header Section
- **Dropdown**: "Thin lens camera" (selected node type)
- **Clean dark theme** with professional styling

### Parameter Groups (Collapsible)
1. **▼ Physical camera parameters** (expanded)
   - ☐ Orthographic (checkbox, unchecked)
   - ► Sensor width: 36.000 (number input with slider)
   - ► Focal length: 50.000 (number input with slider) 
   - ► F-stop: 2.8 (number input with slider)

2. **▼ Viewing angle** (expanded)
   - ► Field of view: 39.597752 (number input with slider)
   - ► Scale of view: 17.144243 (number input with slider)
   - ► Distortion: 0.000 (number input with slider)
   - ► Lens shift: 0.000 | 0.000 (dual number inputs)
   - ☐ Perspective correction (checkbox, unchecked)
   - ► Pixel aspect ratio: 1.000 (number input with slider)

3. **▼ Clipping** (expanded)
   - ► Near clip depth: 0.000 (number input with slider)
   - ► Far clip depth: ∞ (number input with slider)

4. **▼ Depth of field** (expanded)
   - ☑ Auto-focus (checkbox, checked)
   - ► Focal depth: 1.118034 (number input with slider)
   - ► Aperture: 0.8928572 (number input with slider)
   - ► Aperture aspect ratio: 0.994 (number input with slider)
   - ► Aperture edge: 1.000 (number input with slider)
   - ► Bokeh side count: 6 (number input with slider)
   - ► Bokeh rotation: 0.000 (number input with slider)
   - ► Bokeh roundedness: 1.000 (number input with slider)

5. **▼ Position** (expanded)
   - ► Position: 1.144515 | 11.985998 | 20.607536 (triple number inputs)
   - ► Target: 0.1783928 | 1.336309 | -0.6681547 (triple number inputs)
   - ► Up-vector: 0.000 | 1.000 | 0.000 (triple number inputs)

6. **▼ Stereo** (expanded)
   - ► Stereo output: Disabled (dropdown)
   - ► Stereo mode: Off-axis (dropdown)
   - ► Eye distance: 0.065 (number input with slider)
   - ☐ Swap eyes (checkbox, unchecked)
   - ► Left stereo filter: [Pink color bar]
   - ► Right stereo filter: [Pink color bar]

## 🎨 VISUAL DESIGN REQUIREMENTS

### Color Scheme
- **Background**: Dark gray (#3a3a3a)
- **Group headers**: Slightly lighter gray with expand/collapse triangles
- **Parameter labels**: Light gray text
- **Input controls**: Dark input fields with light borders
- **Checkboxes**: Custom styled with checkmarks
- **Sliders**: Professional slider controls
- **Color bars**: Actual color representation

### Typography
- **Font**: Clean, professional sans-serif
- **Sizes**: Consistent hierarchy (group headers larger, parameters smaller)
- **Colors**: Light text on dark background

### Layout
- **Spacing**: Consistent padding and margins
- **Alignment**: Labels left-aligned, controls right-aligned
- **Grouping**: Clear visual separation between parameter groups
- **Icons**: Small triangular expand/collapse indicators

## 🔧 IMPLEMENTATION PLAN

### Phase 1: Parameter Type System Enhancement
1. **Enhance ParameterTypes.js**
   - Add Octane-specific parameter groups mapping
   - Define exact parameter types for camera nodes
   - Map parameter names to UI control types

2. **Update ParameterRenderer.js**
   - Create professional UI controls matching Octane's style
   - Implement dual/triple number inputs for vectors
   - Add color picker controls for color parameters
   - Create custom checkbox styling
   - Implement professional slider controls

### Phase 2: CSS Styling Overhaul
1. **Update components.css**
   - Match exact Octane color scheme
   - Implement professional dark theme
   - Style collapsible group headers
   - Create consistent spacing and alignment
   - Add hover effects and transitions

2. **Control-specific styling**
   - Custom checkbox styling with checkmarks
   - Professional number input + slider combinations
   - Dropdown styling to match Octane
   - Color bar representations
   - Vector input groupings (dual/triple inputs)

### Phase 3: Parameter Grouping Logic
1. **Create OctaneParameterGroups.js**
   - Define exact parameter groups for each node type
   - Map parameters to their correct groups
   - Handle group expand/collapse state
   - Implement group ordering to match Octane

2. **Update NodeInspector.js**
   - Use new parameter grouping system
   - Implement collapsible group functionality
   - Handle parameter value updates
   - Maintain group state across selections

### Phase 4: Node Type Specific Layouts
1. **Camera Node Layout**
   - Physical camera parameters
   - Viewing angle parameters
   - Clipping parameters
   - Depth of field parameters
   - Position parameters (vector3 inputs)
   - Stereo parameters

2. **Other Node Types**
   - Material nodes (diffuse, specular, etc.)
   - Light nodes (intensity, color, etc.)
   - Geometry nodes (transform, etc.)
   - Render target nodes

## 📋 DETAILED IMPLEMENTATION TASKS

### Task 1: Parameter Type Definitions
```javascript
// OctaneParameterGroups.js
const CAMERA_PARAMETER_GROUPS = {
    'Physical camera parameters': [
        { name: 'Orthographic', type: 'boolean', default: false },
        { name: 'Sensor width', type: 'float', min: 0, max: 100, default: 36.0 },
        { name: 'Focal length', type: 'float', min: 0, max: 200, default: 50.0 },
        { name: 'F-stop', type: 'float', min: 0.1, max: 32, default: 2.8 }
    ],
    'Viewing angle': [
        { name: 'Field of view', type: 'float', min: 0, max: 180 },
        { name: 'Scale of view', type: 'float', min: 0, max: 100 },
        { name: 'Distortion', type: 'float', min: -1, max: 1, default: 0 },
        { name: 'Lens shift', type: 'vector2', default: [0, 0] },
        { name: 'Perspective correction', type: 'boolean', default: false },
        { name: 'Pixel aspect ratio', type: 'float', min: 0.1, max: 10, default: 1.0 }
    ],
    // ... other groups
};
```

### Task 2: Professional UI Controls
```javascript
// ParameterRenderer.js enhancements
renderFloatParameter(param) {
    return `
        <div class="parameter-row">
            <label class="parameter-label">${param.label}:</label>
            <div class="parameter-control-group">
                <input type="range" class="parameter-slider" 
                       min="${param.min}" max="${param.max}" 
                       value="${param.value}" step="0.001">
                <input type="number" class="parameter-number" 
                       value="${param.value}" step="0.001">
            </div>
        </div>
    `;
}

renderVector3Parameter(param) {
    return `
        <div class="parameter-row">
            <label class="parameter-label">${param.label}:</label>
            <div class="parameter-vector3">
                <input type="number" value="${param.value[0]}" step="0.001">
                <input type="number" value="${param.value[1]}" step="0.001">
                <input type="number" value="${param.value[2]}" step="0.001">
            </div>
        </div>
    `;
}
```

### Task 3: CSS Styling to Match Octane
```css
/* Professional dark theme matching Octane */
.node-inspector {
    background: #3a3a3a;
    color: #e0e0e0;
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
}

.parameter-group-header {
    background: #4a4a4a;
    padding: 8px 12px;
    border-bottom: 1px solid #555;
    cursor: pointer;
    display: flex;
    align-items: center;
}

.parameter-group-icon {
    margin-right: 8px;
    font-size: 12px;
    transition: transform 0.2s;
}

.parameter-group-header.collapsed .parameter-group-icon {
    transform: rotate(-90deg);
}

.parameter-row {
    display: flex;
    align-items: center;
    padding: 6px 12px;
    border-bottom: 1px solid #444;
}

.parameter-label {
    flex: 1;
    font-size: 13px;
    color: #d0d0d0;
}

.parameter-control-group {
    display: flex;
    align-items: center;
    gap: 8px;
}

.parameter-slider {
    width: 100px;
    height: 4px;
    background: #555;
    outline: none;
    border-radius: 2px;
}

.parameter-number {
    width: 80px;
    background: #2a2a2a;
    border: 1px solid #555;
    color: #e0e0e0;
    padding: 4px 8px;
    border-radius: 3px;
    font-size: 12px;
}

.parameter-checkbox {
    width: 16px;
    height: 16px;
    background: #2a2a2a;
    border: 1px solid #555;
    border-radius: 3px;
    position: relative;
}

.parameter-checkbox:checked::after {
    content: '✓';
    position: absolute;
    top: -2px;
    left: 2px;
    color: #4CAF50;
    font-size: 12px;
}

.parameter-vector3 {
    display: flex;
    gap: 4px;
}

.parameter-vector3 input {
    width: 70px;
    background: #2a2a2a;
    border: 1px solid #555;
    color: #e0e0e0;
    padding: 4px 6px;
    border-radius: 3px;
    font-size: 11px;
}
```

## 🚀 SUCCESS CRITERIA

1. **Visual Match**: Node Inspector looks identical to Octane Studio
2. **Parameter Groups**: All parameter groups match Octane's organization
3. **Control Types**: Each parameter uses the correct UI control type
4. **Styling**: Professional dark theme matches Octane exactly
5. **Functionality**: All controls work and update parameter values
6. **Responsiveness**: Layout adapts to different panel sizes
7. **Performance**: Fast parameter loading using optimized cache system

## 📅 IMPLEMENTATION TIMELINE

- **Day 1**: Parameter type system and grouping logic
- **Day 2**: UI control rendering and CSS styling
- **Day 3**: Integration with existing optimization system
- **Day 4**: Testing and refinement
- **Day 5**: Additional node types and edge cases

This redesign will make octaneWeb's Node Inspector indistinguishable from Octane Studio's professional interface.