# OctaneWeb Development Guide

## 🎯 Current State: Scene Outliner SUCCESS

**CRITICAL**: The Scene Outliner is in an excellent working state as of commit `e3a654c`. **DO NOT BREAK WORKING FUNCTIONALITY.**

### ✅ What's Working Perfectly

1. **Scene Outliner Icons**: Perfect icon system matching Octane UI exactly
   - 📁 Scene, 🫖 teapot.obj, 🎯 Render target, 📷 camera, 🌍 environment
   - Parameter type icons: ☑️ Bool, 🔢 Float/Int, 📋 Enum, 🎨 RGB color

2. **API Integration**: ApiNodePinInfoExService fully functional
   - Returns real parameter names: "Diffuse", "Transmission", "Roughness", "Opacity", "Bump"
   - Proper staticLabel/staticName extraction from pin info
   - Request class pattern working: `ApiNodePinInfoEx.GetNodePinInfoRequest`

3. **Proxy Server**: Critical bugs fixed
   - get_stub() method now creates stubs properly (was only working in exception handler)
   - Service mapping: ApiNodePinInfoExService -> apinodepininfohelper
   - Enhanced debug logging and error handling

4. **Scene Tree Structure**: Recursive loading working correctly
   - Hierarchical node expansion with proper parameter details
   - Pin info integration for actual parameter names instead of generic "Bool value"

## 🚨 CRITICAL WARNINGS

### DO NOT BREAK WORKING CODE
- The recursive children loading in `addSceneItem()` is **ESSENTIAL** and **WORKING**
- Connection errors in logs are usually network/Octane issues, NOT code bugs
- Always analyze what's actually broken vs. what's actually working
- **PRESERVE FUNCTIONALITY** - don't "fix" things that aren't broken

### Network vs Code Issues
- `Connection refused (10061)` = Octane not running or LiveLink disabled
- `Connection reset (10054)` = Network issue or Octane restart
- These are **NOT** infinite recursion or code bugs
- Test with fresh Octane restart before assuming code problems

## 🏗️ Architecture Overview

### Scene Outliner Flow
```
loadSceneTree() 
  → loadSceneTreeSync(rootHandle)
    → ApiNodeGraph/getOwnedItems
    → ApiItemArray/size + get
    → For each item:
      → ApiNode/pinCount
      → For each pin:
        → ApiNode/pinInfoIx → get pinInfoRef
        → ApiNodePinInfoExService/getApiNodePinInfo → get staticLabel
        → ApiNode/connectedNodeIx → get connected node
        → addSceneItem(connectedNode, pinInfo)
          → Recursive call to loadSceneTreeSync() for children
```

**This recursive structure is ESSENTIAL** - it builds the complete scene hierarchy with proper parameter names.

### API Call Success Pattern
```javascript
// This pattern works perfectly:
result = window.grpcApi.makeApiCallSync(
    'ApiNodePinInfoExService/getApiNodePinInfo',
    pinInfoRef.handle,
    {nodePinInfoRef: pinInfoRef}
);
// Returns: { success: true, data: { result: { nodePinInfo: { staticLabel: "Diffuse" } } } }
```

## 🔧 Technical Implementation

### Proxy Server Fixes (WORKING)
```python
# Fixed get_stub() method - stub creation outside exception handler
def get_stub(self, service_name, channel):
    # ... module loading ...
    try:
        stub_class = getattr(grpc_module, stub_class_name)
    except AttributeError:
        # Try alternative naming
        stub_class = getattr(grpc_module, alt_stub_class_name)
    
    # CRITICAL: Create stub outside exception handler
    stub = stub_class(channel)
    self.stubs[service_name] = stub
    return stub

# Fixed request class pattern
if service_name == "ApiNodePinInfoExService":
    if method_name == "getApiNodePinInfo":
        request_class_patterns.append("ApiNodePinInfoEx.GetNodePinInfoRequest")
```

### Icon System (PERFECT)
```javascript
function getOctaneIconFor(item) {
    // Node type icons
    if (item.name === 'Scene') return '📁';
    if (item.name?.includes('teapot')) return '🫖';
    if (item.name === 'Render target') return '🎯';
    if (item.name?.includes('camera')) return '📷';
    if (item.name?.includes('environment')) return '🌍';
    
    // Parameter type icons based on outtype
    if (item.outtype === 'PT_BOOL') return '☑️';
    if (item.outtype === 'PT_FLOAT' || item.outtype === 'PT_INT') return '🔢';
    if (item.outtype === 'PT_ENUM') return '📋';
    if (item.outtype === 'PT_TEXTURE') return '🎨';
    
    return '📄'; // Default
}
```

## 🎯 Next Steps (SAFE IMPROVEMENTS)

### 1. Parameter Name Display Enhancement
- The API integration is working - parameter names are being extracted
- Focus on UI display of staticLabel values in the Scene Outliner tree
- Ensure proper rendering of "Orthographic", "Sensor width", etc.

### 2. Scene Tree Expansion Control
- Add proper expand/collapse state management
- Implement lazy loading for performance (without breaking recursive structure)
- Add search/filter functionality

### 3. Error Handling Improvements
- Better distinction between network errors and code errors
- Graceful degradation when Octane disconnects
- Retry logic for transient connection issues

## 🚫 What NOT to Do

1. **Don't remove recursive children loading** - it's essential for scene hierarchy
2. **Don't assume connection errors = code bugs** - usually network/Octane issues
3. **Don't break working API integration** - ApiNodePinInfoExService is working perfectly
4. **Don't change icon system** - it matches Octane UI exactly
5. **Don't modify proxy fixes** - get_stub() and request patterns are correct

## 🧪 Testing Guidelines

### Before Making Changes
1. Verify current functionality works
2. Test with fresh Octane restart
3. Check that parameter names are displaying correctly
4. Confirm icons are showing properly

### Connection Error Troubleshooting
1. Is Octane running?
2. Is LiveLink enabled in Octane (Help → LiveLink)?
3. Is port 51022 accessible?
4. Try restarting Octane LiveLink service
5. **Only then** consider code changes

### Success Indicators
- Scene Outliner shows hierarchical tree structure
- Icons match Octane UI exactly (📁 🫖 🎯 📷 🌍 ☑️ 🔢 📋 🎨)
- Parameter names show actual values like "Diffuse", "Opacity", not generic "Bool value"
- ApiNodePinInfoExService calls return success with nodePinInfo data

## 📚 Reference

### Working Commits
- `e3a654c`: Perfect Scene Outliner with working API integration and icons
- Previous commits show the progression of fixes

### Key Files
- `octaneWeb/js/components/SceneOutlinerSync.js`: Main Scene Outliner logic
- `octaneProxy/octane_proxy.py`: Proxy server with critical fixes
- `octaneWeb/js/constants/OctaneTypes.js`: Icon mapping system

### API Documentation
- ApiNodePinInfoExService: Returns detailed pin information with staticLabel/staticName
- ApiNode/pinInfoIx: Gets pin info references for parameter details
- ApiNodeGraph/getOwnedItems: Gets scene hierarchy items

**Remember: The Scene Outliner is working well. Focus on enhancement, not breaking changes.**