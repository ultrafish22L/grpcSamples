# 🚀 OctaneWeb Server Launcher Guide

This guide explains how to use the automated server launcher scripts to run OctaneWeb with both the proxy server and web server.

## 📋 Quick Start

### Windows
```batch
# Start both servers
start_proxy.bat

# Stop all servers (in separate window)
stop_servers.bat
```

### Linux/Mac
```bash
# Start both servers
./start_octane_proxy.sh

# Stop all servers (in separate terminal)
./stop_servers.sh
```

## 🔧 What the Launchers Do

The launcher scripts automatically:

1. **✅ Verify Environment**
   - Check you're in the correct `octaneWeb/` directory
   - Verify `working_proxy.py` exists
   - Check Python 3 installation
   - Install required packages if missing (`grpcio`, `aiohttp`, `protobuf`)

2. **🚀 Start Proxy Server**
   - Runs `working_proxy.py` on port **51998**
   - Connects to Octane at `127.0.0.1:51022`
   - Provides HTTP-to-gRPC translation

3. **🌐 Start Web Server**
   - Runs Python HTTP server on port **8080**
   - Serves the OctaneWeb application files
   - Enables proper CORS and file serving

4. **📊 Provide Status Information**
   - Shows all running endpoints
   - Provides test URLs
   - Displays helpful usage instructions

## 🌐 Access Points

Once both servers are running:

| Service | URL | Purpose |
|---------|-----|---------|
| **Main App** | http://localhost:8080/ | Full OctaneWeb interface |
| **Minimal Test** | http://localhost:8080/minimal_test.html | Lightweight connection test |
| **Proxy Health** | http://localhost:51998/test | Proxy server health check |

## 🎯 Prerequisites

### Required Software
- **Python 3.7+** installed and in PATH
- **Octane Render** running with LiveLink enabled on port 51022

### Required Python Packages
The launcher will auto-install these if missing:
- `grpcio` - gRPC client library
- `aiohttp` - Async HTTP server framework  
- `protobuf` - Protocol buffer support

### Octane Configuration
1. Launch Octane Render
2. Enable **LiveLink** service
3. Verify it's listening on port **51022**
4. Check Windows Firewall allows the connection

## 🔍 Troubleshooting

### Common Issues

**"Python not found in PATH"**
- Install Python from https://python.org/downloads/
- During installation, check "Add Python to PATH"
- Restart command prompt/terminal

**"Connection refused to Octane"**
- Verify Octane Render is running
- Check LiveLink is enabled in Octane
- Confirm port 51022 is not blocked by firewall
- Try connecting to `127.0.0.1:51022` manually

**"Port already in use"**
- Stop existing servers with stop script
- Check for other applications using ports 8080 or 51998
- Use `netstat -an | find "8080"` (Windows) or `lsof -i:8080` (Linux/Mac)

**"Required packages not found"**
- Run manually: `pip install grpcio aiohttp protobuf`
- On Linux/Mac, try: `pip3 install grpcio aiohttp protobuf`
- Check internet connection for package downloads

### Manual Server Control

If the launchers don't work, you can start servers manually:

```bash
# Terminal 1: Start proxy
cd octaneWeb/
python3 working_proxy.py

# Terminal 2: Start web server  
cd octaneWeb/
python3 -m http.server 8080
```

### Log Files

The scripts create log files for debugging:
- `proxy.log` - Proxy server output and errors
- `server.log` - Web server access logs

View logs in real-time:
```bash
# Linux/Mac
tail -f proxy.log
tail -f server.log

# Windows
type proxy.log
type server.log
```

## 🔄 Development Workflow

### Typical Usage Pattern
1. Start Octane Render with LiveLink
2. Run launcher script (`start_proxy.bat` or `./start_octane_proxy.sh`)
3. Open http://localhost:8080/ in browser
4. Develop and test OctaneWeb features
5. Stop servers when done

### Testing Connection
Use the minimal test page to verify connectivity without loading the full UI:
- http://localhost:8080/minimal_test.html

This lightweight page tests the complete API chain and displays real Octane scene data.

### Restarting After Changes
- **Code changes**: Just refresh browser (no restart needed)
- **Proxy changes**: Stop and restart launcher
- **Configuration changes**: Stop and restart launcher

## 📁 File Structure

The launcher scripts expect this directory structure:
```
octaneWeb/
├── start_proxy.bat          # Windows launcher
├── start_octane_proxy.sh    # Linux/Mac launcher  
├── stop_servers.bat         # Windows stopper
├── stop_servers.sh          # Linux/Mac stopper
├── working_proxy.py         # Main proxy server
├── index.html               # Main web application
├── minimal_test.html        # Lightweight test page
├── js/                      # JavaScript modules
├── css/                     # Stylesheets
└── assets/                  # Static assets
```

## 🎯 Next Steps

Once the servers are running successfully:

1. **Test Connection**: Visit http://localhost:8080/minimal_test.html
2. **Use Main App**: Visit http://localhost:8080/
3. **Check Scene Data**: Verify real Octane scene items appear
4. **Develop Features**: Modify code and refresh browser
5. **Monitor Logs**: Watch `proxy.log` for API calls

## 🆘 Getting Help

If you encounter issues:

1. **Check Prerequisites**: Verify Python and Octane are properly installed
2. **Review Logs**: Check `proxy.log` and `server.log` for errors
3. **Test Manually**: Try starting servers individually
4. **Verify Ports**: Ensure ports 8080 and 51998 are available
5. **Check Firewall**: Verify Windows/Mac firewall allows connections

The launcher scripts provide detailed error messages and suggestions for resolving common issues.