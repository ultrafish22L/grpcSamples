# 🔥 OPENHANDS: Docker Development Environment

## 🎯 CRITICAL NETWORKING SETUP

**Docker Container Isolation**: OpenHands cannot access host localhost services by default. For gRPC proxy connectivity:

```bash
export SANDBOX_USE_HOST_NETWORK=true
```

**Docker-in-Docker Alternative:**
```bash
export SANDBOX_LOCAL_RUNTIME_URL="http://host.docker.internal"
```

**Troubleshooting Keywords**: `Connection refused`, `localhost:8080`, `gRPC timeout`, `Network unreachable`

## 🔧 OPENHANDS OPTIMIZATION TECHNIQUES

### Multi-Action Efficiency:
```bash
# Combine multiple operations in single commands
find . -name "*.py" | xargs grep -l "localhost" | head -10 && git status
cd /workspace && ls -la && git branch -a && git remote -v
```

### Efficient Exploration Patterns:
```bash
grep -r "TODO\|FIXME\|BUG" --include="*.py" --include="*.js" . | head -20
find . -type f \( -name "*.py" -o -name "*.js" -o -name "*.cpp" \) | head -20
```

### Tool Combination Strategies:
- Use `str_replace_editor` for multiple file edits in single message
- Chain `execute_bash` commands with `&&` and `;` for efficiency
- Leverage `execute_ipython_cell` for data analysis and calculations
- Apply `fetch` for real-time information when needed

## 🚨 CRITICAL WEB DEVELOPMENT PROTOCOLS

### 🔥 MANDATORY CACHE BUSTING:
```javascript
// 🚨 CRITICAL: ALWAYS use cache busting to prevent stale code
const timestamp = new Date().toISOString().replace(/[-:]/g, '').slice(0, 15);
const cacheBuster = `?v=${timestamp}`;
```

### 🔥 NEVER USE F12 - BUILD CONSOLE CAPTURE:
```javascript
// 🚨 CRITICAL: ALWAYS implement browser console message capture
// 🚨 NEVER rely on F12 developer tools - build it into the application
```

### 🔥 VISUAL VERIFICATION PROTOCOL:
```xml
<!-- 🚨 ULTRA CRITICAL: Always check ACTUAL BROWSER DISPLAY -->
<!-- 🚨 "EXISTS IN DOM" ≠ "VISUALLY DISPLAYS" -->
<verification_visual_check>
SCREENSHOT_REQUIRED: [Take screenshot and verify actual display]
DOM_VS_VISUAL: [Distinguish between DOM existence and visual rendering]
USER_PERSPECTIVE: [What does the user actually see on screen?]
</verification_visual_check>
```

## 🔧 DEVELOPMENT ENVIRONMENT SETUP

### Sandbox Limitations:
**Network Isolation**: Development environments may have network isolation preventing direct connection to localhost services. This affects:
- Connection to live Octane LiveLink service at 127.0.0.1:51022
- Proxy server binding to specific ports
- Real-time testing of live Octane integration

### Workarounds:
- Mock server provides full Octane API simulation for development
- Proxy server includes graceful degradation and retry logic
- Applications detect connection failures and provide appropriate fallbacks

### Development Workflow:
1. **Mock Development**: Use mock_octane_server.py for initial development
2. **Proxy Testing**: Test HTTP-to-gRPC translation with comprehensive logging
3. **Live Integration**: Connect to real Octane LiveLink service for production testing
4. **Cross-platform Validation**: Build and test on multiple operating systems

## 🚨 NETWORKING DIAGNOSTICS

### Test Localhost Connectivity:
```bash
curl -v http://localhost:8080/health || echo "NETWORK ISSUE: Use SANDBOX_USE_HOST_NETWORK=true"
```

### Docker Networking Fixes:
```bash
export SANDBOX_USE_HOST_NETWORK=true
export SANDBOX_LOCAL_RUNTIME_URL="http://host.docker.internal"
```

### Port Configuration:
- **Octane gRPC**: Default 51023 (configurable in Octane Preferences)
- **Bulletproof Proxy**: Default 51998 (configurable in bulletproof_proxy.py)
- **Mock Server**: Default 51023 (configurable in mock_octane_server.py)

## 🔥 OPENHANDS SUCCESS PATTERNS

### What Works Best:
- **Evidence-based conclusions** with source code references
- **Concrete actionable solutions** (export commands, specific fixes)
- **Systematic exploration** using efficient bash commands and grep patterns
- **Clear documentation** with troubleshooting keywords and quick-fix commands
- **Consistent version control** with descriptive commits and branch management
- **Scope confirmation** before research expansion or feature addition

### Critical Failure Patterns (Require User Supervision):
- **Visual verification failure** - claiming success without checking actual display
- **Cache dependency** - not implementing fresh cache busting with every change
- **F12 dependency** - relying on developer tools instead of built-in logging
- **Scope creep during debugging** - fixing unrelated issues when focused task requested
- **Evidence avoidance** - making claims without concrete proof

## 🎖️ OPENHANDS EXCELLENCE STANDARDS

### Multi-Tool Efficiency:
- Combine multiple bash commands in single execution
- Use str_replace_editor for multiple file edits per message
- Leverage tool combinations for maximum productivity
- Apply efficient exploration patterns with grep and find

### Professional Development:
- Test-driven development with incremental verification
- Clear commit messages with descriptive scope
- Documentation with troubleshooting keywords
- Error handling with graceful degradation
- Performance monitoring and connection health tracking

### OpenHands Environment Mastery:
- Docker networking configuration for localhost access
- File system navigation with absolute paths
- Version control with proper staging and commits
- Web development with cache-busting and debug consoles
- Cross-platform compatibility verification

---

**OpenHands provides a powerful development environment when used with proper networking configuration and systematic development practices. Follow these protocols for maximum productivity and reliability.**