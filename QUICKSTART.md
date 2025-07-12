# QUICKSTART Guide

Quick setup instructions for running the OTOY WebGL-Octane LiveLink Sync application.

## 🚀 Web Application (Recommended)

### Windows

1. **Open Command Prompt or PowerShell**
   ```cmd
   cd path\to\grpcSamples\html
   python -m http.server 8000
   ```

2. **Open your browser**
   - Navigate to: `http://localhost:8000`
   - The main application will load automatically

### Linux

1. **Open Terminal**
   ```bash
   cd /path/to/grpcSamples/html
   python3 -m http.server 8000
   ```

2. **Open your browser**
   - Navigate to: `http://localhost:8000`
   - The main application will load automatically

## 🔧 gRPC Proxy Server (Optional)

The proxy server enables communication between the web app and Octane LiveLink service.

### Windows

1. **Install Python dependencies**
   ```cmd
   cd path\to\grpcSamples\proxy
   pip install grpcio aiohttp aiohttp-cors
   ```

2. **Run the proxy server**
   ```cmd
   python grpc_proxy.py
   ```
   - Server runs on: `http://localhost:8080`

### Linux

1. **Install Python dependencies**
   ```bash
   cd /path/to/grpcSamples/proxy
   pip3 install grpcio aiohttp aiohttp-cors
   ```

2. **Run the proxy server**
   ```bash
   python3 grpc_proxy.py
   ```
   - Server runs on: `http://localhost:8080`

## 🎯 Usage

1. **Start the web application** (see above)
2. **Optional**: Start the proxy server for Octane connectivity
3. **Open browser** to `http://localhost:8000`
4. **Configure connection** in the web interface:
   - Default proxy address: `http://127.0.0.1:8080`
   - Toggle connection switch to connect to Octane LiveLink

## 📋 Requirements

- **Python 3.6+** (built into most modern systems)
- **Modern web browser** (Chrome, Firefox, Safari, Edge)
- **Octane LiveLink service** (optional, for full functionality)

## 🔍 Troubleshooting

- **Port conflicts**: Change `8000` to another port (e.g., `8001`, `3000`)
- **Python not found**: Install Python from [python.org](https://python.org)
- **Permission errors**: Run terminal/command prompt as administrator
- **Firewall issues**: Allow Python through Windows Firewall

## 📚 More Information

- See `html/README.md` for detailed web application documentation
- See `proxy/README.md` for proxy server configuration options
- See main `README.md` for complete repository overview