# OctaneWeb Development Task: Complete Scene Outliner Parameter Names

## 🎯 CURRENT TASK: Display Real Parameter Names in Scene Outliner

**MISSION**: Make octaneWeb Scene Outliner match Octane standalone UI exactly by showing actual parameter names like "Orthographic", "Sensor width", "Diffuse", "Opacity" instead of generic "Bool value", "Float value".

**STATUS**: 95% Complete - API integration working perfectly, just need UI display enhancement.

## ✅ What's Already Working (commit e3a654c)

1. **Perfect API Integration**: ApiNodePinInfoExService calls successfully returning real parameter data
2. **Perfect Icons**: All icons match Octane UI exactly (📁 Scene, 🫖 teapot.obj, 🎯 Render target, 📷 camera, 🌍 environment, ☑️ Bool, 🔢 Float/Int, 📋 Enum, 🎨 RGB)
3. **Scene Tree Structure**: Hierarchical loading with proper recursive structure
4. **Parameter Data Available**: API returns staticLabel: "Diffuse", staticName: "diffuse", etc.

## 🎯 NEXT STEP: Update UI to Display Real Parameter Names

**SIMPLE TASK**: The API is returning perfect data like this:
```javascript
{
  success: true,
  data: {
    result: {
      nodePinInfo: {
        staticLabel: "Diffuse",           // ← Use this for display!
        staticName: "diffuse", 
        description: "Diffuse reflection channel.",
        type: "PT_TEXTURE"
      }
    }
  }
}
```

**GOAL**: Update Scene Outliner UI to show "Diffuse" instead of "Bool value" or "Float value".

## 📋 Specific Implementation Task

**File**: `octaneWeb/js/components/SceneOutlinerSync.js`
**Function**: `addSceneItem()` around line 255

**Current Logic**:
```javascript
// Use pin info name if available, otherwise get item name
if (pinInfo && pinInfo.staticLabel) {
    itemName = pinInfo.staticLabel;  // ← This should work!
} else if (pinInfo && pinInfo.staticName) {
    itemName = pinInfo.staticName;
} else {
    // Fallback to API call
}
```

**Expected Result**: Scene Outliner should show:
- ✅ "Diffuse" (not "Bool value")
- ✅ "Transmission" (not "Float value") 
- ✅ "Roughness" (not "Float value")
- ✅ "Opacity" (not "Float value")
- ✅ "Bump" (not "Float value")

## 🔍 Debug Steps if Parameter Names Not Showing

1. **Check API Response**: Look in browser console for ApiNodePinInfoExService responses
2. **Verify pinInfo Data**: Console.log the pinInfo object in addSceneItem()
3. **Check staticLabel**: Ensure pinInfo.staticLabel contains the expected name
4. **Test with Simple Case**: Focus on one parameter like "Diffuse" first

## 🚨 CRITICAL DEBUGGING LESSONS LEARNED

### **🛑 #1 DEBUGGING MISTAKE: Using F12 Browser Console**

**WRONG**: Trying to use F12 browser developer console in OpenHands environment
**RIGHT**: Use **Ctrl+D** to open the built-in debug console

- F12 browser console **DOES NOT WORK** in OpenHands environment
- The application has a built-in debug console accessible via **Ctrl+D**
- This shows real-time API calls, errors, and debug information
- **This was the #1 mistake that caused debugging loops**

### **🔧 API Service Mapping Issues**

**Problem**: `ApiNodePinInfoExService` calls failing silently
**Root Cause**: Incorrect protobuf module mapping in proxy
**Solution**: Add to `octaneProxy/octane_proxy.py` service_map:
```python
'ApiNodePinInfoExService': 'apinodepininfohelper'
```

**Symptoms**:
- API calls appear in proxy logs but return empty `{}`
- Debug console shows `❌ SYNC API call failed for ApiNodePinInfoExService/getApiNodePinInfo: {}`
- Parameters show as "undefined" in Scene Outliner

### **📋 API Call Structure Requirements**

**Problem**: `ApiNodePinInfoExService/getApiNodePinInfo` expects specific parameter structure
**Correct Structure**:
```javascript
{
    nodePinInfoRef: {
        handle: pinInfo.handle,
        type: pinInfo.type || 18  // ApiNodePinInfo type
    }
}
```

**Wrong Structure**: Passing `pinInfo.handle` directly

### **🐛 Debugging Workflow**

1. **Primary Debug Tool**: Use **Ctrl+D** debug console, NOT F12
2. **API Call Verification**: Check debug console for API call success/failure
3. **Proxy Logs**: Use `tail -f /tmp/octane_proxy.log` to verify service mapping
4. **Parameter Inspection**: Use debug console to inspect `pinInfo` objects

### **⚠️ Common Pitfalls**

1. **Assuming F12 works**: Browser developer console is not available in OpenHands
2. **Silent API failures**: API calls may appear in proxy logs but fail due to incorrect service mapping
3. **Parameter structure**: gRPC services require exact parameter structure matching protobuf definitions
4. **Mixed success/failure**: Some parameters may work while others fail due to different API call paths

### **🔍 Environment Detection**

**F12 Enhancement**: F12 now opens debug console when running in OpenHands environment:
- Detects OpenHands environment automatically
- F12 opens built-in debug console for automated environments
- F12 works normally (browser console) for regular users

## 🚨 CRITICAL: Don't Break Working Code

- The recursive scene loading is **ESSENTIAL** - don't remove it
- The API integration is working perfectly - don't change proxy code
- Icons are perfect - don't modify icon system
- Connection errors in logs = network issues, not code bugs

## 📚 Reference for New Chat

### Key Files to Check
- `octaneWeb/js/components/SceneOutlinerSync.js` - Main Scene Outliner (line 255 addSceneItem function)
- `octaneProxy/octane_proxy.py` - Proxy with working ApiNodePinInfoExService integration
- `octaneWeb/js/constants/OctaneTypes.js` - Perfect icon system

### Working State (commit e3a654c)
- Scene Outliner loads hierarchical tree with perfect icons
- ApiNodePinInfoExService returns real parameter data with staticLabel
- Recursive scene loading working correctly
- All proxy bugs fixed and API integration successful

### User's Goal
Make octaneWeb Scene Outliner match Octane standalone UI exactly - see `images/octane_ui.png` for reference showing expanded camera with ~30 parameters like "Orthographic", "Sensor width", etc.

### What Should Happen Next
Simple UI update to display pinInfo.staticLabel values instead of generic parameter names. The API data is already there - just needs to be shown in the UI properly.