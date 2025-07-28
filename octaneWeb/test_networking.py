#!/usr/bin/env python3
"""
Test script to demonstrate automatic networking detection
"""

import os
import sys

# Add the current directory to Python path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

# Import the networking function
from octane_proxy_comprehensive import get_octane_address

def test_networking_detection():
    """Test the automatic networking detection"""
    
    print("🧪 Testing Automatic Networking Detection")
    print("=" * 50)
    
    # Test 1: Current environment (should detect sandbox)
    print("\n1️⃣ Current Environment:")
    print(f"   Working Directory: {os.getcwd()}")
    print(f"   User: {os.environ.get('USER', 'unknown')}")
    print(f"   Docker env exists: {os.path.exists('/.dockerenv')}")
    print(f"   OpenHands workspace: {os.environ.get('OPENHANDS_WORKSPACE_BASE', 'not set')}")
    print(f"   SANDBOX_USE_HOST_NETWORK: {os.environ.get('SANDBOX_USE_HOST_NETWORK', 'not set')}")
    
    current_address = get_octane_address()
    print(f"   🎯 Detected Address: {current_address}")
    
    # Test 2: Simulate Windows environment
    print("\n2️⃣ Simulated Windows Environment:")
    
    # Temporarily clear sandbox indicators
    original_env = {}
    sandbox_env_vars = ['SANDBOX_USE_HOST_NETWORK', 'OPENHANDS_WORKSPACE_BASE', 'CONTAINER']
    
    for var in sandbox_env_vars:
        if var in os.environ:
            original_env[var] = os.environ[var]
            del os.environ[var]
    
    # Simulate Windows by temporarily changing working directory context
    original_cwd = os.getcwd()
    
    try:
        # This simulates what would happen on Windows
        print(f"   Working Directory: C:\\Users\\YourName\\grpcSamples\\octaneWeb (simulated)")
        print(f"   User: YourName (simulated)")
        print(f"   Docker env exists: False (simulated)")
        print(f"   OpenHands workspace: not set")
        print(f"   SANDBOX_USE_HOST_NETWORK: not set")
        
        # Temporarily change to a non-sandbox path for testing
        os.chdir('/tmp')
        
        # Temporarily monkey-patch the Docker detection
        import octane_proxy_comprehensive
        original_exists = os.path.exists
        def mock_exists(path):
            if path == '/.dockerenv':
                return False  # Simulate Windows (no Docker env file)
            return original_exists(path)
        
        os.path.exists = mock_exists
        windows_address = get_octane_address()
        os.path.exists = original_exists  # Restore
        
        print(f"   🎯 Detected Address: {windows_address}")
        
    finally:
        # Restore original environment
        os.chdir(original_cwd)
        for var, value in original_env.items():
            os.environ[var] = value
    
    # Test 3: Explicit override
    print("\n3️⃣ Explicit Override (SANDBOX_USE_HOST_NETWORK=true):")
    os.environ['SANDBOX_USE_HOST_NETWORK'] = 'true'
    override_address = get_octane_address()
    print(f"   🎯 Detected Address: {override_address}")
    
    # Clean up
    if 'SANDBOX_USE_HOST_NETWORK' in original_env:
        os.environ['SANDBOX_USE_HOST_NETWORK'] = original_env['SANDBOX_USE_HOST_NETWORK']
    else:
        del os.environ['SANDBOX_USE_HOST_NETWORK']
    
    print("\n✅ Networking Detection Test Complete!")
    print("\nSummary:")
    print(f"   🐳 Sandbox/Docker: {current_address}")
    print(f"   🖥️ Windows/Native: {windows_address}")
    print(f"   🔧 Explicit Override: {override_address}")

if __name__ == '__main__':
    test_networking_detection()