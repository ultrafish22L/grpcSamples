#!/bin/bash
# ========================================
# OctaneWeb Server Stopper
# ========================================
# Stops all OctaneWeb servers cleanly
# ========================================

echo
echo "========================================"
echo "  Stopping OctaneWeb Servers"
echo "========================================"
echo

echo "🛑 Stopping Python HTTP servers..."
pkill -f "python3.*http.server" 2>/dev/null
pkill -f "python3.*octane_proxy.py" 2>/dev/null

echo "🛑 Stopping any remaining server processes..."
# Kill processes on specific ports
lsof -ti:8080 | xargs kill -9 2>/dev/null
lsof -ti:51023 | xargs kill -9 2>/dev/null

echo
echo "========================================"
echo "  All Servers Stopped"
echo "========================================"
echo
echo "✅ You can now restart with ./start_servers.sh"
echo