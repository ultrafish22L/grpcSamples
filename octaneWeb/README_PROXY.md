# OctaneWeb Proxy Server Setup (Windows)

## 🚀 Quick Start

1. **Double-click** `start_proxy.bat` in this folder
2. **Open browser** to: `file:///C:/path/to/grpcSamples/octaneWeb/index.html`
3. **Verify connection** shows "Connected to Octane"

## 📋 Requirements

### Before Running:
- ✅ **Octane Render** running with LiveLink enabled (port 51022)
- ✅ **Python 3.7+** installed and in PATH
- ✅ **grpcio** and **aiohttp** packages (auto-installed by script)

### Directory Structure:
```
grpcSamples/
├── octaneWeb/
│   ├── start_proxy.bat     ← Run this file
│   ├── index.html
│   └── js/
└── proxy/
    ├── grpc_proxy.py       ← Actual proxy server
    └── *_pb2.py
```

## 🔧 Manual Setup (if batch file fails)

```cmd
cd grpcSamples\proxy
pip install grpcio aiohttp protobuf
python grpc_proxy.py
```

## 🌐 How It Works

```
Browser (octaneWeb) → HTTP → Proxy Server → gRPC → Octane LiveLink
     localhost:file         localhost:51023         127.0.0.1:51022
```

## ⚠️ Troubleshooting

### "Python not found"
- Install Python from https://python.org/downloads/
- Make sure "Add to PATH" is checked during installation

### "Connection refused" 
- Start Octane Render first
- Enable LiveLink in Octane (Tools → LiveLink)
- Check port 51022 is not blocked by firewall

### "Port already in use"
- Kill existing proxy: `taskkill /f /im python.exe`
- Or restart your computer

### "Package installation failed"
- Run as Administrator
- Or manually: `pip install grpcio aiohttp protobuf`

## 📊 Expected Output

```
========================================
 OctaneWeb Proxy Server Launcher
========================================

Python found: Python 3.11.0
Required packages found ✓

========================================
 Starting Proxy Server...
========================================

✅ Successfully connected to Octane LiveLink server at 127.0.0.1:51022
📥 Initial camera state: pos=(1.14, 11.99, 20.61)
✅ Proxy server started on http://0.0.0.0:51023 (accessible via localhost:51023)
   Browser requests will be forwarded to Octane at 127.0.0.1:51022
   Press Ctrl+C to stop
```

## 🎯 Success Indicators

1. **Proxy starts** without errors
2. **Browser shows** "Connected to Octane" 
3. **Scene outliner** loads with scene data
4. **No HTTP 500 errors** in browser console

---

**Need Help?** Check the debug console in octaneWeb (Ctrl+D) for detailed logging.