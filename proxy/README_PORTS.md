# 🎯 OCTANE LIVELINK PORT CONFIGURATION

## ENFORCED PORT ASSIGNMENTS

**These ports are HARDCODED and cannot be changed:**

| Service | Port | Address | Purpose |
|---------|------|---------|---------|
| **Octane LiveLink Server** | `51022` | `127.0.0.1:51022` | Octane Render's gRPC LiveLink service |
| **Proxy Server** | `51023` | `localhost:51023` | HTTP-to-gRPC proxy (this application) |
| **Web Application** | `51998` or `59489` | `localhost:51998` | OctaneWeb frontend |

## DOCKER ENVIRONMENT

In Docker containers (like OpenHands), the proxy automatically detects the environment and uses:
- **Octane LiveLink**: `host.docker.internal:51022` (instead of 127.0.0.1:51022)
- **Proxy Server**: Still `localhost:51023`

## USAGE

### ✅ CORRECT USAGE:
```bash
# Start proxy (ports are enforced)
python3 grpc_proxy.py

# Or use the startup script
python3 start_proxy.py
```

### ❌ INCORRECT USAGE:
```bash
# These will be REJECTED:
python3 grpc_proxy.py --port 8080        # ❌ No port arguments allowed
python3 start_proxy.py -p 51024          # ❌ Port is enforced
python3 grpc_proxy.py 51025               # ❌ No positional port arguments
```

## WHY PORTS ARE ENFORCED

1. **Consistency**: All OctaneWeb components expect these exact ports
2. **Simplicity**: No configuration needed - just works
3. **Reliability**: Eliminates port mismatch issues
4. **Documentation**: Clear, predictable setup for all users

## CONNECTION FLOW

```
Browser (OctaneWeb) → localhost:51023 (Proxy) → 127.0.0.1:51022 (Octane)
```

## TROUBLESHOOTING

### Port Already in Use
```bash
# Check what's using the ports
netstat -tulpn | grep :51022
netstat -tulpn | grep :51023

# Kill processes if needed
sudo kill -9 $(lsof -t -i:51023)
```

### Connection Refused
- **Port 51022**: Ensure Octane Render is running with LiveLink enabled
- **Port 51023**: Ensure no other proxy instance is running

### Docker Issues
- Set `SANDBOX_USE_HOST_NETWORK=true` for OpenHands
- Proxy automatically detects Docker and uses `host.docker.internal:51022`

## VALIDATION

The proxy validates port configuration on startup:
```
🔧 VALIDATING PORT CONFIGURATION:
   Octane LiveLink Server: 127.0.0.1:51022 (ENFORCED)
   Proxy Server: localhost:51023 (ENFORCED)
   ⚠️  These ports are HARDCODED and cannot be changed
✅ Port configuration validated
```

## MODIFICATION WARNING

⚠️ **DO NOT MODIFY THE PORT CONSTANTS** in `grpc_proxy.py`:
```python
# 🎯 ENFORCED PORT CONFIGURATION - DO NOT CHANGE
OCTANE_PORT = 51022  # Octane LiveLink Server (always)
PROXY_PORT = 51023   # This proxy server (always)
```

Changing these values will break compatibility with OctaneWeb and other components.