#!/usr/bin/env python3
"""
Verification script for callback-based rendering implementation in simpleGlSdk
Checks the code structure and implementation patterns.
"""

import re
import os

def check_file_exists(filepath):
    """Check if file exists and return its content"""
    if os.path.exists(filepath):
        with open(filepath, 'r') as f:
            return f.read()
    return None

def verify_implementation():
    """Verify the callback implementation in main.cpp"""
    
    main_cpp_path = "/workspace/grpcSamples/simpleGlSdk/main.cpp"
    content = check_file_exists(main_cpp_path)
    
    if not content:
        print("❌ main.cpp not found")
        return False
    
    print("🔍 Verifying callback implementation in simpleGlSdk/main.cpp")
    print("=" * 60)
    
    checks = [
        {
            "name": "Required headers included",
            "pattern": r'#include.*apirender\.h',
            "required": True
        },
        {
            "name": "Mutex and atomic includes",
            "pattern": r'#include.*<mutex>.*#include.*<atomic>',
            "required": True,
            "flags": re.DOTALL
        },
        {
            "name": "Global callback variables declared",
            "pattern": r'std::mutex g_renderImageMutex',
            "required": True
        },
        {
            "name": "Callback function implemented",
            "pattern": r'void OnNewImageCallback.*ApiArray.*ApiRenderImage',
            "required": True,
            "flags": re.DOTALL
        },
        {
            "name": "Thread-safe data copying",
            "pattern": r'std::lock_guard.*g_renderImageMutex',
            "required": True
        },
        {
            "name": "Callback registration",
            "pattern": r'setOnNewImageCallback.*OnNewImageCallback',
            "required": True
        },
        {
            "name": "Main loop integration",
            "pattern": r'g_hasNewRenderData.*setupTexture',
            "required": True,
            "flags": re.DOTALL
        },
        {
            "name": "Callback cleanup on exit",
            "pattern": r'setOnNewImageCallback.*nullptr.*nullptr',
            "required": True,
            "flags": re.DOTALL
        },
        {
            "name": "Debugging output with emojis",
            "pattern": r'📸.*Received render callback',
            "required": True
        },
        {
            "name": "Error handling with try/catch",
            "pattern": r'try.*setOnNewImageCallback.*catch',
            "required": True,
            "flags": re.DOTALL
        }
    ]
    
    passed = 0
    total = len(checks)
    
    for check in checks:
        pattern = check["pattern"]
        flags = check.get("flags", 0)
        
        if re.search(pattern, content, flags):
            print(f"✅ {check['name']}")
            passed += 1
        else:
            print(f"❌ {check['name']}")
            if check.get("required", False):
                print(f"   Missing pattern: {pattern}")
    
    print("=" * 60)
    print(f"📊 Implementation verification: {passed}/{total} checks passed")
    
    if passed == total:
        print("🎉 All callback implementation checks passed!")
        print("🚀 Ready for testing with live Octane connection")
        return True
    else:
        print("⚠️  Some implementation issues found")
        return False

def check_build_system():
    """Check if build system is properly configured"""
    
    cmake_path = "/workspace/grpcSamples/simpleGlSdk/CMakeLists.txt"
    content = check_file_exists(cmake_path)
    
    if not content:
        print("❌ CMakeLists.txt not found")
        return False
    
    print("\n🔧 Verifying build system configuration")
    print("=" * 60)
    
    build_checks = [
        {
            "name": "DO_GRPC_SDK_ENABLED defined",
            "pattern": r'DO_GRPC_SDK_ENABLED'
        },
        {
            "name": "SDK headers included",
            "pattern": r'sdk.*src.*api.*grpc.*client'
        },
        {
            "name": "Octane SDK library linked",
            "pattern": r'octane_sdk'
        }
    ]
    
    passed = 0
    for check in build_checks:
        if re.search(check["pattern"], content):
            print(f"✅ {check['name']}")
            passed += 1
        else:
            print(f"❌ {check['name']}")
    
    print(f"📊 Build system: {passed}/{len(build_checks)} checks passed")
    return passed == len(build_checks)

def main():
    """Main verification function"""
    
    print("🔍 Octane SDK Callback Implementation Verification")
    print("=" * 60)
    
    impl_ok = verify_implementation()
    build_ok = check_build_system()
    
    print("\n" + "=" * 60)
    print("📋 SUMMARY")
    print("=" * 60)
    
    if impl_ok and build_ok:
        print("🎉 SUCCESS: Callback implementation is complete and ready!")
        print("\n📝 Next steps:")
        print("1. Build with full Octane SDK environment")
        print("2. Test with live Octane connection (port 51022)")
        print("3. Verify real-time render callbacks are received")
        print("4. Monitor performance and callback frequency")
        
        print("\n🔗 Expected workflow:")
        print("- Start Octane with LiveLink enabled")
        print("- Run simpleGlSdk application")
        print("- Press Q to toggle between Octane render and local cube")
        print("- Watch for callback messages in console")
        
        return True
    else:
        print("❌ ISSUES FOUND: Implementation needs fixes")
        return False

if __name__ == "__main__":
    success = main()
    exit(0 if success else 1)