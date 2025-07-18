# PROJECT DISCIPLINE (PD) - OCTANEWEB DEVELOPMENT

**Version 1.0 - Project-Specific Rules for OctaneWeb Development**
*Created: 2025-01-18*

---

## 🚨 CRITICAL PROJECT-SPECIFIC STOP CONDITIONS

### **OCTANE CONNECTION FAILURES - NEVER CONTINUE**
```xml
<octane_connection_failure>
TRIGGER: Connection refused, timeout, or gRPC error to Octane LiveLink (port 51022)
ACTION: STOP IMMEDIATELY - Do not continue building
REQUIRED: Report to user and propose alternatives
FORBIDDEN: Assuming "offline mode" or "mock mode" without explicit user approval
</octane_connection_failure>
```

### **BROWSER COMPATIBILITY FAILURES - NEVER CONTINUE**
```xml
<browser_compatibility_failure>
TRIGGER: file:// protocol restrictions, CORS errors, or WebGL failures
ACTION: STOP IMMEDIATELY - Do not continue with workarounds
REQUIRED: Report specific browser/version and propose alternatives
FORBIDDEN: Switching to localhost servers without user approval
</browser_compatibility_failure>
```

### **PROTOBUF/GRPC IMPORT FAILURES - NEVER CONTINUE**
```xml
<protobuf_import_failure>
TRIGGER: Missing protobuf files, import errors, or stub generation failures
ACTION: STOP IMMEDIATELY - Do not continue with mock implementations
REQUIRED: Report missing dependencies and propose generation/installation plan
FORBIDDEN: Creating fake protobuf classes or mock stubs without user approval
</protobuf_import_failure>
```

---

## 🎯 PROJECT-SPECIFIC SUCCESS CRITERIA

### **OCTANEWEB FUNCTIONAL REQUIREMENTS**
- **Primary**: Web UI loads via file:// protocol with custom debug console
- **Secondary**: Proxy server connects to live Octane LiveLink on port 51022
- **Tertiary**: Real-time camera sync, scene outliner, and node graph editor

### **DEVELOPMENT WORKFLOW REQUIREMENTS**
- **Cache Busting**: MANDATORY timestamp-based cache busting for all JS/CSS
- **Debug Console**: MANDATORY Ctrl+D toggleable console, never rely on F12
- **Visual Verification**: MANDATORY screenshot verification of actual browser display
- **Port Separation**: octaneWeb uses 51024, html project uses 51023

---

## 🔧 PROJECT-SPECIFIC TECHNICAL CONSTRAINTS

### **NETWORKING ARCHITECTURE**
```
Browser (file://) → Custom Proxy (51024) → Octane LiveLink (51022)
```

### **DEPENDENCY HIERARCHY**
1. **Core**: HTML/CSS/JS files must work standalone
2. **Proxy**: Python proxy server with protobuf bindings
3. **Octane**: Live Octane Render with LiveLink enabled
4. **Optional**: Mock server for development without live Octane

### **FILE PROTOCOL REQUIREMENTS**
- All resources must load via file:// protocol
- No external CDN dependencies
- No localhost assumptions in client code
- CORS-compliant proxy server configuration

---

## 🚫 PROJECT-SPECIFIC FORBIDDEN ACTIONS

### **NEVER DO WITHOUT USER APPROVAL**
- Switch from file:// to localhost servers
- Continue after Octane connection failures
- Modify protobuf files or generate new ones
- Change port assignments (51024 for octaneWeb, 51023 for html)
- Install system-level dependencies
- Create mock implementations of real APIs

### **NEVER ASSUME**
- Octane is running and available
- User wants offline/mock mode when connections fail
- Browser supports all WebGL features
- File system permissions allow file:// access
- Python dependencies are installed

---

## 🎖️ PROJECT-SPECIFIC VALIDATION PROTOCOLS

### **OCTANE CONNECTION VALIDATION**
```bash
# Test Octane LiveLink availability
curl -v telnet://127.0.0.1:51022 || echo "❌ STOP: Octane not available"

# Test proxy server health
curl -s http://localhost:51024/health | python3 -m json.tool
```

### **BROWSER COMPATIBILITY VALIDATION**
```javascript
// Test file:// protocol compatibility
if (window.location.protocol !== 'file:') {
    console.error('❌ STOP: Must run via file:// protocol');
}

// Test WebGL availability
const canvas = document.createElement('canvas');
const gl = canvas.getContext('webgl2') || canvas.getContext('webgl');
if (!gl) {
    console.error('❌ STOP: WebGL not available');
}
```

### **CACHE BUSTING VALIDATION**
```javascript
// Verify timestamp-based cache busting is active
const timestamp = new Date().toISOString().replace(/[-:]/g, '').slice(0, 15);
console.log(`✅ Cache buster active: ${timestamp}`);
```

---

## 📊 PROJECT-SPECIFIC SUCCESS METRICS

### **PERFORMANCE TARGETS**
- **Proxy Response Time**: < 100ms for API calls
- **WebGL Frame Rate**: > 30 FPS for 3D rendering
- **Connection Establishment**: < 2 seconds to Octane LiveLink
- **UI Responsiveness**: < 50ms for debug console toggle

### **RELIABILITY TARGETS**
- **API Success Rate**: > 95% for live Octane connections
- **Browser Compatibility**: Chrome 90+, Firefox 88+, Safari 14+
- **Error Recovery**: Graceful degradation when Octane unavailable
- **Cache Consistency**: 100% fresh code loading during development

---

## 🔄 PROJECT-SPECIFIC ERROR RECOVERY

### **CONNECTION FAILURE RECOVERY**
1. **STOP** - Halt all development immediately
2. **DIAGNOSE** - Check Octane LiveLink status and port availability
3. **REPORT** - Provide specific error details to user
4. **PROPOSE** - Offer mock server, different ports, or alternative approaches
5. **WAIT** - For explicit user approval before continuing

### **BROWSER COMPATIBILITY RECOVERY**
1. **STOP** - Halt all browser-specific development
2. **IDENTIFY** - Specific browser, version, and capability limitations
3. **REPORT** - Exact compatibility issues and affected features
4. **PROPOSE** - Polyfills, fallbacks, or alternative implementations
5. **WAIT** - For user decision on compatibility vs. feature trade-offs

### **DEVELOPMENT ENVIRONMENT RECOVERY**
1. **STOP** - Halt all environment-dependent operations
2. **ASSESS** - Available tools, permissions, and system capabilities
3. **REPORT** - Specific limitations and missing dependencies
4. **PROPOSE** - Installation steps, workarounds, or alternative tools
5. **WAIT** - For user approval of environment modifications

---

## 🎯 PROJECT-SPECIFIC ACTIVATION KEYWORDS

### **OCTANE-SPECIFIC COMMANDS**
- `"OCTANEIT"` = Focus exclusively on Octane LiveLink integration
- `"PROXYIT"` = Work on HTTP-to-gRPC proxy server functionality
- `"MOCKIT"` = Switch to mock server development (requires user approval)
- `"LIVEIT"` = Attempt live Octane connection (with failure handling)

### **WEB-SPECIFIC COMMANDS**
- `"FILEIT"` = Ensure file:// protocol compatibility
- `"WEBGLIT"` = Focus on WebGL 3D rendering functionality
- `"DEBUGIT"` = Enhance custom debug console capabilities
- `"CACHEBUSTIT"` = Implement/verify cache busting mechanisms

---

## 🚨 PROJECT-SPECIFIC CRITICAL FAILURE PATTERNS

### **SILENT FAILURES - REQUIRE IMMEDIATE USER SUPERVISION**
- **🔥 OCTANE CONNECTION ASSUMED** - Continuing without verifying Octane availability
- **🔥 BROWSER COMPATIBILITY ASSUMED** - Not testing file:// protocol restrictions
- **🔥 CACHE DEPENDENCY** - Relying on browser cache instead of fresh code loading
- **🔥 MOCK MODE ASSUMPTION** - Switching to offline mode without user approval
- **🔥 PORT CONFLICTS** - Using wrong ports or conflicting with existing services

### **DEVELOPMENT ANTI-PATTERNS**
- Building features that require live Octane without connection verification
- Creating localhost dependencies in file:// protocol applications
- Implementing browser-specific code without compatibility testing
- Modifying generated protobuf files instead of regenerating properly
- Assuming system permissions for file access or network operations

---

## 🎖️ PROJECT DISCIPLINE OATH

*"I will verify Octane LiveLink connectivity before building dependent features. I will test file:// protocol compatibility before assuming browser capabilities. I will implement cache busting for all development iterations. I will stop immediately when core assumptions fail and consult the user before proceeding. I will never assume offline mode or mock implementations without explicit approval."*

---

**This PROJECT_DISCIPLINE.md works in conjunction with ENGINEERING_DISCIPLINE.md to provide project-specific constraints while maintaining generic engineering best practices. When conflicts arise, project-specific rules take precedence for this codebase.**

*Last Updated: 2025-01-18*
*Project: OctaneWeb Development*
*Repository: grpcSamples/octaneWeb*