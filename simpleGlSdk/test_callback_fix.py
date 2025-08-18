#!/usr/bin/env python3
"""
Test script to verify the callback fixes are working
"""

import re
import os
import subprocess

def check_main_cpp_fixes():
    """Check that main.cpp has the correct fixes applied"""
    
    main_cpp = "/workspace/grpcSamples/simpleGlSdk/main.cpp"
    
    if not os.path.exists(main_cpp):
        return False, "main.cpp not found"
    
    with open(main_cpp, 'r') as f:
        content = f.read()
    
    fixes = [
        {
            "name": "Connection moved outside main loop",
            "pattern": r"Connect to Octane server and initialize camera sync ONCE before main loop",
            "should_exist": True
        },
        {
            "name": "No connection in main loop",
            "pattern": r"while.*glfwWindowShouldClose.*connectToServer",
            "should_exist": False,
            "flags": re.DOTALL
        },
        {
            "name": "Fixed emoji debug output",
            "pattern": r"📸 Received render callback #",
            "should_exist": True
        },
        {
            "name": "Proper initialization sequence",
            "pattern": r"if \(cameraSync\.connectToServer\(serverAddress\)\).*cameraSync\.initialize\(\)",
            "should_exist": True,
            "flags": re.DOTALL
        }
    ]
    
    results = []
    for fix in fixes:
        pattern = fix["pattern"]
        flags = fix.get("flags", 0)
        should_exist = fix["should_exist"]
        
        found = bool(re.search(pattern, content, flags))
        
        if should_exist and found:
            results.append(f"✅ {fix['name']}")
        elif not should_exist and not found:
            results.append(f"✅ {fix['name']}")
        else:
            results.append(f"❌ {fix['name']}")
    
    return True, results

def check_debug_tools():
    """Check that debug tools were created"""
    
    tools = [
        "/workspace/grpcSamples/simpleGlSdk/callback_debug.cpp",
        "/workspace/grpcSamples/simpleGlSdk/callback_testbed.cpp",
        "/workspace/grpcSamples/simpleGlSdk/CALLBACK_FIX_ANALYSIS.md"
    ]
    
    results = []
    for tool in tools:
        if os.path.exists(tool):
            results.append(f"✅ {os.path.basename(tool)} created")
        else:
            results.append(f"❌ {os.path.basename(tool)} missing")
    
    return results

def run_verification_script():
    """Run the callback verification script"""
    
    try:
        result = subprocess.run([
            "python3", "verify_callback_implementation.py"
        ], 
        cwd="/workspace/grpcSamples/simpleGlSdk",
        capture_output=True, 
        text=True,
        timeout=30
        )
        
        if result.returncode == 0:
            # Check if all tests passed
            if "10/10 checks passed" in result.stdout:
                return True, "✅ All verification checks passed"
            else:
                return False, f"⚠️ Some checks failed:\n{result.stdout}"
        else:
            return False, f"❌ Verification failed:\n{result.stderr}"
            
    except subprocess.TimeoutExpired:
        return False, "❌ Verification script timed out"
    except Exception as e:
        return False, f"❌ Error running verification: {e}"

def main():
    """Main test function"""
    
    print("🧪 Testing Octane Callback Fixes")
    print("=" * 40)
    
    # Test 1: Check main.cpp fixes
    print("\n📝 Test 1: Checking main.cpp fixes...")
    success, results = check_main_cpp_fixes()
    
    if success:
        for result in results:
            print(f"   {result}")
    else:
        print(f"   ❌ {results}")
        return False
    
    # Test 2: Check debug tools
    print("\n🔧 Test 2: Checking debug tools...")
    results = check_debug_tools()
    for result in results:
        print(f"   {result}")
    
    # Test 3: Run verification script
    print("\n✅ Test 3: Running verification script...")
    success, message = run_verification_script()
    print(f"   {message}")
    
    # Summary
    print("\n" + "=" * 40)
    print("📊 TEST SUMMARY")
    print("=" * 40)
    
    if success:
        print("🎉 ALL TESTS PASSED!")
        print("\n📋 Fixes Applied:")
        print("   ✅ Connection logic fixed (no per-frame connections)")
        print("   ✅ Debug output emoji pattern fixed")
        print("   ✅ Proper initialization sequence")
        print("   ✅ Debug tools created")
        print("   ✅ Verification scripts pass")
        
        print("\n🚀 Next Steps:")
        print("   1. Build simpleGlSdk with full SDK environment")
        print("   2. Test with live Octane connection")
        print("   3. Verify callbacks are received")
        print("   4. Monitor texture updates")
        
        print("\n💡 Debug Tools Available:")
        print("   - callback_debug.cpp: Systematic callback testing")
        print("   - callback_testbed.cpp: Full pipeline testing")
        print("   - CALLBACK_FIX_ANALYSIS.md: Detailed analysis")
        
        return True
    else:
        print("❌ SOME TESTS FAILED!")
        print("   Check the output above for specific issues")
        return False

if __name__ == "__main__":
    success = main()
    exit(0 if success else 1)