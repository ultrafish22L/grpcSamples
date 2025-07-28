# 🌐 Automatic Networking Detection

The OctaneWeb proxy automatically detects your environment and uses the appropriate networking configuration to connect to Octane Render.

## 🔍 How It Works

The proxy uses multiple detection methods to determine the correct Octane address:

### 1️⃣ **Explicit Override** (Highest Priority)
```bash
# Force Docker networking mode
set SANDBOX_USE_HOST_NETWORK=true
python octane_proxy_comprehensive.py
```
**Result**: `host.docker.internal:51022`

### 2️⃣ **Automatic Environment Detection**
The proxy checks for these indicators:
- OpenHands workspace paths (`/openhands` in working directory)
- OpenHands environment variables (`OPENHANDS_WORKSPACE_BASE`)
- Docker container indicators (`/.dockerenv` file exists)
- Generic container indicators (`CONTAINER` environment variable)
- Sandbox user names (contains "sandbox")

**If detected**: `host.docker.internal:51022` (Docker networking)

### 3️⃣ **Default Native Mode**
If no container/sandbox indicators are found:

**Result**: `127.0.0.1:51022` (Native networking)

## 🖥️ Windows Usage

On Windows, the proxy will automatically use `127.0.0.1:51022`:

```batch
# Just run normally - no special configuration needed
start_proxy.bat
```

The proxy will detect it's running natively and connect to Octane on localhost.

## 🐳 Docker/Container Usage

In Docker or sandbox environments, the proxy automatically uses `host.docker.internal:51022`:

```bash
# Runs automatically in containers
python octane_proxy_comprehensive.py
```

## 🧪 Testing Detection

You can test the networking detection:

```bash
python test_networking.py
```

This will show:
- Current environment detection
- Simulated Windows environment
- Explicit override behavior

## 🔧 Manual Override

If automatic detection doesn't work correctly, you can force a specific mode:

```bash
# Force Docker mode
export SANDBOX_USE_HOST_NETWORK=true
python octane_proxy_comprehensive.py

# Force native mode (remove the variable)
unset SANDBOX_USE_HOST_NETWORK
python octane_proxy_comprehensive.py
```

## 📋 Startup Messages

The proxy shows which networking mode it detected:

```
🐳 Detected sandbox/container environment, using Docker networking: host.docker.internal
🎯 Octane Target: host.docker.internal:51022
```

or

```
🖥️ Using native networking: 127.0.0.1
🎯 Octane Target: 127.0.0.1:51022
```

## ✅ Verification

Test the connection:

```bash
curl -X POST http://localhost:51998/test -H "Content-Type: application/json" -d '{}'
```

Should return:
```json
{
  "success": true,
  "message": "Octane is available and responding",
  "host": "127.0.0.1",  // or "host.docker.internal"
  "port": 51022,
  "rootGraphHandle": 1000000
}
```