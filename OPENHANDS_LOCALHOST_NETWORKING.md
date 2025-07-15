# OpenHands Localhost Networking Configuration Guide

## 🚨 CRITICAL NETWORKING ISSUE: Docker Container Isolation

**PROBLEM**: By default, OpenHands runs in Docker containers with bridge networking, which **CANNOT** access host localhost services (like your gRPC proxy server on localhost:8080).

**SYMPTOMS**: 
- Connection refused errors when trying to reach localhost services
- gRPC proxy timeouts from web applications
- "Network unreachable" errors in container logs

## ✅ PROVEN SOLUTIONS (From OpenHands Source Code)

### **METHOD 1: Host Network Mode (RECOMMENDED)**

**Quick Setup Keywords**: `use_host_network`, `host network mode`, `Docker networking`

```yaml
# config.toml or environment
[sandbox]
use_host_network = true
```

**OR Environment Variable:**
```bash
export SANDBOX_USE_HOST_NETWORK=true
```

**What this does:**
- Sets Docker `network_mode='host'`
- Container shares host network stack
- Direct access to localhost services
- **Most reliable solution**

**macOS Warning**: Requires Docker Desktop 4.29.0+ with host network feature enabled

---

### **METHOD 2: Docker-in-Docker (DIND) Configuration**

**Quick Setup Keywords**: `host.docker.internal`, `DIND`, `local_runtime_url`

```yaml
[sandbox]
local_runtime_url = "http://host.docker.internal"
```

**OR Environment Variable:**
```bash
export SANDBOX_LOCAL_RUNTIME_URL="http://host.docker.internal"
```

**What this does:**
- Uses Docker's special hostname to reach host
- Works in Docker-in-Docker environments
- Alternative when host networking unavailable

---

### **METHOD 3: Nested Runtime Browser Host Override**

**Quick Setup Keywords**: `NESTED_RUNTIME_BROWSER_HOST`, `nested runtime`

```bash
export NESTED_RUNTIME_BROWSER_HOST="http://localhost"
```

**What this does:**
- Overrides runtime URL for browser connections
- Useful for nested container scenarios
- Specific to web interface connections

---

### **METHOD 4: Runtime Binding Address (For Incoming Connections)**

**Quick Setup Keywords**: `runtime_binding_address`, `0.0.0.0`, `external access`

```yaml
[sandbox]
runtime_binding_address = "0.0.0.0"  # Default, allows external connections TO container
```

**Note**: This allows external connections TO the container, but doesn't solve container accessing host services.

---

## 🔧 IMPLEMENTATION EVIDENCE (From OpenHands Source)

### Host Network Mode Implementation:
```python
# From openhands/runtime/impl/docker/docker_runtime.py
use_host_network = self.config.sandbox.use_host_network
network_mode: typing.Literal['host'] | None = (
    'host' if use_host_network else None
)

# Warning message in code:
self.log('warn', 
    'Using host network mode. If you are using MacOS, please make sure you have '
    'the latest version of Docker Desktop and enabled host network feature: '
    'https://docs.docker.com/network/drivers/host/#docker-desktop'
)
```

### DIND Support:
```python
# From openhands/core/config/sandbox_config.py
local_runtime_url: str = Field(default='http://localhost')
# Comment: "You may want to change to http://host.docker.internal for DIND environments"
```

### Nested Runtime Override:
```python
# From openhands/server/conversation_manager/docker_nested_conversation_manager.py
if os.getenv('NESTED_RUNTIME_BROWSER_HOST', '') != '':
    # This should be set to http://localhost if you're running OH inside a docker container
    nested_url = nested_url.replace(
        self.config.sandbox.local_runtime_url,
        os.getenv('NESTED_RUNTIME_BROWSER_HOST', ''),
    )
```

---

## 🎯 QUICKSTART FOR GRPC PROXY CONNECTION

**If you need OpenHands to connect to a gRPC proxy on localhost:8080:**

### Option A: Host Network (Simplest)
```bash
export SANDBOX_USE_HOST_NETWORK=true
# Now container can access localhost:8080 directly
```

### Option B: Docker-in-Docker
```bash
export SANDBOX_LOCAL_RUNTIME_URL="http://host.docker.internal"
# Update proxy URL to host.docker.internal:8080 in your code
```

### Option C: Configuration File
```toml
# config.toml
[sandbox]
use_host_network = true
runtime_binding_address = "0.0.0.0"
```

---

## 🚨 TROUBLESHOOTING KEYWORDS

**Search for these in logs/errors:**
- `Connection refused`
- `Network unreachable` 
- `localhost:8080`
- `gRPC timeout`
- `Docker networking`
- `Container isolation`

**Quick diagnostic:**
```bash
# Inside OpenHands container, test connectivity:
curl -v http://localhost:8080/health
# OR
curl -v http://host.docker.internal:8080/health
```

---

## 📚 RELATED OPENHANDS FEATURES

- **File Viewer Server**: Explicitly restricts to localhost only (`127.0.0.1`, `localhost`, `::1`)
- **VSCode Integration**: Uses port mapping for external access
- **Security Model**: Conscious about network isolation for security
- **Multi-platform Support**: Different solutions for Linux/macOS/Windows

---

## 🔍 SOURCE CODE REFERENCES

- `openhands/runtime/impl/docker/docker_runtime.py` - Main networking logic
- `openhands/core/config/sandbox_config.py` - Configuration options
- `openhands/core/config/utils.py` - macOS compatibility warnings
- `openhands/server/conversation_manager/docker_nested_conversation_manager.py` - Nested runtime handling
- `openhands/runtime/file_viewer_server.py` - Localhost security restrictions

---

**Last Updated**: 2025-01-15  
**OpenHands Version**: Latest (from source analysis)  
**Tested Scenarios**: gRPC proxy connections, web application networking, Docker-in-Docker deployments