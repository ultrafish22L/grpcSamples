#!/usr/bin/env python3
"""
🎯 OCTANE PROXY STARTUP SCRIPT
Enforces correct port configuration and starts the proxy server

ENFORCED CONFIGURATION:
- Octane LiveLink: 127.0.0.1:51022 (or host.docker.internal:51022 in Docker)
- Proxy Server: localhost:51023

⚠️  CRITICAL: These ports cannot be changed via command line arguments.
"""

import sys
import os
import subprocess

def main():
    print("🎯 OCTANE LIVELINK PROXY STARTUP")
    print("=" * 50)
    
    # Check if user tried to pass port arguments
    if len(sys.argv) > 1:
        for arg in sys.argv[1:]:
            if '--port' in arg or '-p' in arg or arg.isdigit():
                print("❌ ERROR: Port configuration is ENFORCED and cannot be changed!")
                print("   Octane LiveLink: ALWAYS 127.0.0.1:51022")
                print("   Proxy Server: ALWAYS localhost:51023")
                print("   Remove any port arguments and run again.")
                sys.exit(1)
    
    # Get the directory of this script
    script_dir = os.path.dirname(os.path.abspath(__file__))
    proxy_script = os.path.join(script_dir, 'grpc_proxy.py')
    
    # Check if proxy script exists
    if not os.path.exists(proxy_script):
        print(f"❌ ERROR: Proxy script not found at {proxy_script}")
        sys.exit(1)
    
    print("🚀 Starting Octane LiveLink Proxy with ENFORCED port configuration...")
    print("   Press Ctrl+C to stop")
    print()
    
    try:
        # Start the proxy with no arguments (ports are hardcoded)
        subprocess.run([sys.executable, proxy_script], check=True)
    except KeyboardInterrupt:
        print("\n🛑 Proxy stopped by user")
    except subprocess.CalledProcessError as e:
        print(f"❌ Proxy failed with exit code {e.returncode}")
        sys.exit(e.returncode)
    except Exception as e:
        print(f"❌ Unexpected error: {e}")
        sys.exit(1)

if __name__ == '__main__':
    main()