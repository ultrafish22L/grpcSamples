#!/usr/bin/env python3
"""Check Octane connection status"""
import socket
import time

def check_connection(host, port, timeout=5):
    """Test TCP connection"""
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(timeout)
        result = s.connect_ex((host, port))
        s.close()
        return result == 0
    except Exception as e:
        print(f"Exception: {e}")
        return False

print("🔍 Checking Octane LiveLink connection...\n")

hosts_to_try = [
    ('host.docker.internal', 51022, 'Docker host mapping'),
    ('localhost', 51022, 'Local machine'),
    ('127.0.0.1', 51022, 'Loopback'),
]

for host, port, desc in hosts_to_try:
    print(f"Testing {host}:{port} ({desc})...", end=' ')
    if check_connection(host, port):
        print(f"✅ CONNECTED")
    else:
        print(f"❌ Failed")

print("\n" + "="*60)
print("📋 Troubleshooting:")
print("="*60)
print("1. Is Octane Render running?")
print("2. Is LiveLink enabled? (Help → LiveLink in Octane menu)")
print("3. Check Octane console for LiveLink port (usually 51022)")
print("4. Try disabling firewall temporarily")
print("\n💡 If running in Docker/sandbox, use host.docker.internal")
print("   If running directly on host machine, use localhost")

