# QUICKSTART Guide

Quick setup instructions for running the OTOY WebGL-Octane LiveLink Sync application.

## 🚀 Web Application (Recommended)

### Windows

1. **Start Octane grpc**
   In Preferences enable grpc server
   restart Octane

2. **Start the proxy server**
   - double click html/start_proxy.bat

2. **View in browser**
   - double click html/index.html

### Linux

1. **Start Octane grpc**
   In Preferences enable grpc server
   restart Octane

2. **Start the proxy server**
   - bash html/start_proxy.sh

2. **View in browser**
   - html/index.html

## 🎯 Usage

1. **Start the web application** (see above)
2. **Proxy server**: Start the proxy server for Octane connectivity
3. **View in browser** to `index.html`

## 📋 Requirements

- **Python 3.6+** (built into most modern systems)
- **Modern web browser** (Chrome, Firefox, Safari, Edge)
- **Octane with LiveLink service** 

## 🔍 Troubleshooting

- **Port conflicts**: Change `8000` to another port (e.g., `8001`, `3000`)
- **Python not found**: Install Python from [python.org](https://python.org)
- **Permission errors**: Run terminal/command prompt as administrator
- **Firewall issues**: Allow Python through Windows Firewall

## 📚 More Information

- See `html/README.md` for detailed web application documentation
- See `proxy/README.md` for proxy server configuration options
- See main `README.md` for complete repository overview