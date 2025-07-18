# PROJECT DISCIPLINE (PD) - OCTANEWEB DEVELOPMENT
## Project-Specific Engineering Rules and Constraints

**Version 2.0 - OctaneWeb Development Discipline**
*Extends ENGINEERING_DISCIPLINE.md with project-specific requirements*

---

## 🚨 CRITICAL STOP CONDITIONS

### OCTANE CONNECTION FAILURES
```xml
<octane_connection_failure>
TRIGGER: Connection refused, timeout, or gRPC error to Octane LiveLink (port 51022)
MANDATORY_CHECK: Docker networking protocol (SANDBOX_USE_HOST_NETWORK=true, host.docker.internal)
ACTION: STOP IMMEDIATELY - Do not continue building
REQUIRED: Report to user and propose alternatives (mock server, UI-only, investigation)
FORBIDDEN: Assuming "offline mode" without explicit user approval
</octane_connection_failure>
```

### BROWSER COMPATIBILITY FAILURES
```xml
<browser_compatibility_failure>
TRIGGER: file:// protocol restrictions, CORS errors, WebGL failures
ACTION: STOP IMMEDIATELY - Do not switch to localhost servers
REQUIRED: Report specific browser/version and propose alternatives
FORBIDDEN: Changing protocol requirements without user approval
</browser_compatibility_failure>
```

### PROTOBUF/GRPC IMPORT FAILURES
```xml
<protobuf_import_failure>
TRIGGER: Missing protobuf files, import errors, stub generation failures
ACTION: STOP IMMEDIATELY - Do not create mock implementations
REQUIRED: Report missing dependencies and propose generation/installation plan
FORBIDDEN: Creating fake protobuf classes without user approval
</protobuf_import_failure>
```

---

## 🐳 OCTANEWEB NETWORKING REQUIREMENTS

### MANDATORY DOCKER SETUP
```bash
# Required before any Octane connection attempts
export SANDBOX_USE_HOST_NETWORK=true

# octane_proxy.py must use host.docker.internal (not 127.0.0.1)
def __init__(self, octane_host='host.docker.internal', octane_port=51022, proxy_port=51024)
```

### CONNECTION DIAGNOSTIC SEQUENCE
1. Verify SANDBOX_USE_HOST_NETWORK environment variable
2. Confirm octane_proxy.py uses host.docker.internal
3. Test proxy health: `curl http://localhost:51024/health`
4. Only then attempt Octane LiveLink connection
5. "Connection refused (111)" = Docker isolation issue, not Octane failure

---

## 🎯 OCTANEWEB SUCCESS CRITERIA

### FUNCTIONAL REQUIREMENTS
- **Primary**: Web UI loads via file:// protocol with custom debug console
- **Secondary**: Proxy server connects to live Octane LiveLink (port 51022)
- **Tertiary**: Real-time camera sync, scene outliner, node graph editor

### DEVELOPMENT CONSTRAINTS
- **Cache Busting**: MANDATORY timestamp-based cache busting for all JS/CSS
- **Debug Console**: Built-in logging, never rely on F12 developer tools
- **Port Separation**: octaneWeb (51024) vs html legacy (51023)
- **Protocol Lock**: file:// protocol only, no localhost servers without approval

### VALIDATION REQUIREMENTS
- **Visual Verification**: Screenshot proof of actual browser display
- **API Testing**: Debug console Unit Test button with live endpoint coverage
- **Connection Health**: Real-time proxy status and Octane connectivity monitoring
- **Error Handling**: Graceful degradation when Octane unavailable

---

## 🔧 OCTANEWEB TECHNICAL ARCHITECTURE

### FILE STRUCTURE DISCIPLINE
```
octaneWeb/
├── octane_proxy.py          # Custom HTTP-to-gRPC proxy (port 51024)
├── index.html               # Main application entry point
├── js/utils/CacheBuster.js  # Timestamp-based cache management
├── js/utils/DebugConsole.js # Built-in development console
└── shared/js/livelink.js    # gRPC-Web client implementation
```

### PROXY SERVER REQUIREMENTS
- **Port**: 51024 (dedicated to octaneWeb)
- **Target**: host.docker.internal:51022 (Octane LiveLink)
- **Health Check**: /health endpoint with connection status
- **Test Suite**: /test endpoint with comprehensive API coverage
- **Error Handling**: Graceful degradation with mock responses when Octane unavailable

### WEB CLIENT CONSTRAINTS
- **Protocol**: file:// only, no web servers
- **Cache Busting**: Every JS/CSS load must include timestamp parameter
- **Debug Console**: Ctrl+D toggle, comprehensive logging with emoji indicators
- **API Client**: Custom gRPC-Web implementation, no external CDN dependencies

---

## 🚫 FORBIDDEN ACTIONS WITHOUT USER APPROVAL

### SCOPE EXPANSION
- Adding features not explicitly requested
- Fixing unrelated issues during focused tasks
- Implementing comprehensive error handling beyond basic requirements
- Building test infrastructure without explicit request

### PROTOCOL CHANGES
- Switching from file:// to localhost servers
- Changing port assignments (51024 for octaneWeb)
- Modifying Docker networking configuration
- Adding external dependencies or CDN libraries

### DEVELOPMENT SHORTCUTS
- Using F12 developer tools instead of built-in debug console
- Skipping cache busting during active development
- Assuming Octane connection status without testing
- Creating mock implementations without user approval

---

## 📊 PROJECT-SPECIFIC ACTIVATION KEYWORDS

### OCTANEWEB COMMANDS
- `BUSTIT` = Add cache busting during active HTML/JS development
- `WEBIT` = Focus on web UI development with file:// protocol constraints
- `PROXEIT` = Work on octane_proxy.py with Docker networking awareness

### VALIDATION TRIGGERS
- `VISUALIT` = Require screenshot proof of browser display
- `CONNECTIT` = Test Octane connectivity with full diagnostic sequence
- `HEALTHIT` = Check proxy server health and API coverage

---

**PROJECT DISCIPLINE COMMITMENT**: *"I will stop immediately on Octane connection failures and check Docker networking first. I will maintain file:// protocol constraints and never switch to localhost without approval. I will use built-in debug console and implement mandatory cache busting. I will validate with visual proof and maintain port separation discipline."*

---

*Version 2.0 - OctaneWeb Development Discipline*
*Extends: ENGINEERING_DISCIPLINE.md v2.0*