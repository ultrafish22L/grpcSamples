# OctaneWeb Networking Setup Guide 🌐

## 🎯 **FOOLPROOF NETWORKING SETUP**

This guide contains all the networking tricks needed to establish a live connection between octaneWeb and Octane LiveLink service. Follow these steps exactly to avoid connection issues.

---

## 🚀 **QUICK START (Copy-Paste Commands)**

### **Step 1: Start Octane Proxy Server**
```bash
cd /workspace/grpcSamples/octaneProxy
pip install --upgrade protobuf  # Fix version mismatch
python octane_proxy.py > /tmp/octane_proxy.log 2>&1 &
```

### **Step 2: Start Web Server**
```bash
cd /workspace/grpcSamples/octaneWeb
python -m http.server 54697 --bind 0.0.0.0 > /tmp/web_server.log 2>&1 &
```

### **Step 3: Verify Connection**
```bash
curl -s http://localhost:51023/health
# Should return: {"status": "ok", "connected": true}
```

### **Step 4: Access Application**
- Open browser to: `http://localhost:54697/`
- Connection status should show: "Connected to Octane" (green)

---

## 🔧 **NETWORKING ARCHITECTURE**

### **Connection Flow:**
```
Browser (HTTP/JSON) → Proxy Server (HTTP-to-gRPC) → Octane LiveLink (gRPC)
    ↓                      ↓                           ↓
Port 54697            Port 51023                 Port 51022
```

### **Port Configuration:**
- **Web Server**: `54697` (serves octaneWeb HTML/JS/CSS)
- **Proxy Server**: `51023` (HTTP-to-gRPC translation)
- **Octane LiveLink**: `51022` (Octane's gRPC service)

---

## 🐳 **SANDBOX NETWORKING (Critical for OpenHands/Docker)**

### **Automatic Environment Detection:**
The proxy server automatically detects sandbox environments and adjusts networking:

```python
# In octane_proxy.py - get_octane_address()
sandbox_indicators = [
    '/openhands' in os.getcwd(),           # OpenHands workspace
    os.environ.get('OPENHANDS_WORKSPACE_BASE'),  # OpenHands env var
    os.path.exists('/.dockerenv'),         # Docker container
    os.environ.get('CONTAINER'),           # Generic container
    'sandbox' in os.environ.get('USER', '').lower()  # Sandbox user
]

if any(sandbox_indicators):
    return f'host.docker.internal:{OCTANE_PORT}'  # Docker networking
else:
    return f'127.0.0.1:{OCTANE_PORT}'  # Native networking
```

### **Key Networking Rules:**
- **Sandbox Environment**: Uses `host.docker.internal:51022` to reach host machine
- **Native Environment**: Uses `127.0.0.1:51022` for localhost
- **Proxy Binding**: Always binds to `0.0.0.0:51023` for accessibility
- **Web Server**: Always binds to `0.0.0.0:54697` for accessibility

---

## 🛠️ **TROUBLESHOOTING GUIDE**

### **Problem: Proxy Won't Start**
```bash
# Check protobuf version mismatch
tail -20 /tmp/octane_proxy.log
# Look for: "Detected mismatched Protobuf Gencode/Runtime"

# Solution: Upgrade protobuf
pip install --upgrade protobuf
```

### **Problem: Connection Refused**
```bash
# Check if Octane is running
# User should verify Octane LiveLink is enabled in Octane

# Check proxy logs
tail -20 /tmp/octane_proxy.log
# Look for: "Successfully connected to Octane"
```

### **Problem: Health Check Fails**
```bash
# Test proxy health
curl -s http://localhost:51023/health

# Expected: {"status": "ok", "connected": true}
# If "connected": false, Octane is not running or LiveLink disabled
```

### **Problem: Web Page Won't Load**
```bash
# Check web server
ps aux | grep "http.server" | grep -v grep

# Restart if needed
cd /workspace/grpcSamples/octaneWeb
python -m http.server 54697 --bind 0.0.0.0 &
```

---

## 📊 **VERIFICATION CHECKLIST**

### **✅ Proxy Server Health:**
- [ ] Process running: `ps aux | grep octane_proxy`
- [ ] Health check: `curl -s http://localhost:51023/health`
- [ ] Logs show: "Successfully connected to Octane"
- [ ] No protobuf version errors in logs

### **✅ Web Server Health:**
- [ ] Process running: `ps aux | grep http.server`
- [ ] Accessible: `curl -s http://localhost:54697/`
- [ ] Returns HTML content

### **✅ Octane Connection:**
- [ ] Octane application running on host machine
- [ ] LiveLink enabled in Octane (Help → LiveLink)
- [ ] Port 51022 accessible from container
- [ ] Proxy logs show camera position data

### **✅ Browser Connection:**
- [ ] Green "Connected to Octane" status
- [ ] Scene Outliner shows hierarchical tree
- [ ] Parameter names display correctly
- [ ] No console errors (F12)

---

## 🔍 **DEBUGGING COMMANDS**

### **Monitor Live Activity:**
```bash
# Watch proxy logs in real-time
tail -f /tmp/octane_proxy.log

# Check running processes
ps aux | grep -E "(octane_proxy|http.server)" | grep -v grep

# Test specific API call
curl -X POST http://localhost:51023/ApiItem/name \
  -H "Content-Type: application/json" \
  -d '{"objectPtr": {"handle": "1000002", "type": 16}}'
```

### **Network Diagnostics:**
```bash
# Check port availability
lsof -i :51023  # Proxy server
lsof -i :54697  # Web server

# Test connectivity
curl -s http://localhost:51023/health
curl -s http://localhost:54697/ | head -10
```

---

## 🚨 **CRITICAL SUCCESS FACTORS**

### **Must-Have Requirements:**
1. **Octane Running**: Octane application must be running on host machine
2. **LiveLink Enabled**: Help → LiveLink must be enabled in Octane
3. **Protobuf Version**: Must be 6.31.1 to match generated code
4. **Sandbox Detection**: Proxy automatically detects environment
5. **Port Binding**: All servers bind to 0.0.0.0 for accessibility

### **Common Mistakes to Avoid:**
- ❌ Using 127.0.0.1 binding in sandbox environments
- ❌ Forgetting to enable LiveLink in Octane
- ❌ Not upgrading protobuf version
- ❌ Starting proxy before installing dependencies
- ❌ Using wrong port numbers

### **Success Indicators:**
- ✅ Proxy logs: "Successfully connected to Octane at host.docker.internal:51022"
- ✅ Health check: `{"status": "ok", "connected": true}`
- ✅ Browser: Green "Connected to Octane" status
- ✅ Scene data: Real parameter names like "Orthographic", "Sensor width"

---

## 📝 **ENVIRONMENT VARIABLES (Optional)**

### **Override Networking:**
```bash
# Force Docker networking
export SANDBOX_USE_HOST_NETWORK=true

# Custom Octane host
export OCTANE_HOST=192.168.1.100:51022
```

### **Development Flags:**
```bash
# Enable debug logging
export OCTANE_DEBUG=true

# Custom ports
export OCTANE_PORT=51022
export PROXY_PORT=51023
```

---

## 🎯 **SUMMARY**

The networking setup is now **100% automated** with environment detection. Simply run the two commands:

1. `python octane_proxy.py > /tmp/octane_proxy.log 2>&1 &`
2. `python -m http.server 54697 --bind 0.0.0.0 > /tmp/web_server.log 2>&1 &`

The proxy will automatically:
- Detect sandbox environment
- Use correct networking (host.docker.internal vs 127.0.0.1)
- Connect to Octane LiveLink service
- Provide health check endpoint
- Handle all gRPC-to-HTTP translation

**Result**: Live connection with real-time API communication between browser and Octane.