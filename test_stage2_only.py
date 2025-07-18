#!/usr/bin/env python3
"""
🚨 CRASH DEBUGGING: Test Stage 2 in isolation
BUGIT: Run only Stage 2 services to see if they crash when run alone
"""

import asyncio
import sys
import os
from datetime import datetime

# Add current directory to path
sys.path.insert(0, os.path.dirname(__file__))

# Import the main test class
from comprehensive_octane_test import ComprehensiveOctaneTest

class Stage2OnlyTest(ComprehensiveOctaneTest):
    """Test only Stage 2 services"""
    
    async def run_stage2_only_test(self):
        """Run only Stage 2 services"""
        print("🚨 STAGE 2 ISOLATION TEST")
        print("BUGIT: Testing Stage 2 services in isolation")
        print("=" * 60)
        
        start_time = datetime.now()
        
        # Connect to Octane
        if not await self.connect():
            return False
        
        try:
            print("🚀 RUNNING STAGE 2 ONLY: Image & Geometry Services")
            
            # Run only Stage 2
            await self.test_stage2_services()
            
            print(f"✅ STAGE 2 ISOLATION COMPLETE: {len(self.test_results)} tests")
            
            # Check if Octane is still responsive
            print("\n🔍 CHECKING OCTANE RESPONSIVENESS...")
            try:
                # Try a simple call to verify Octane is still alive
                response = await self.project_manager_stub.isValid(self.empty_request)
                print("✅ Octane still responsive after Stage 2")
                return True
            except Exception as e:
                print(f"💥 Octane crashed during Stage 2: {e}")
                return False
            
        finally:
            await self.disconnect()
            
            # Print summary
            end_time = datetime.now()
            duration = end_time - start_time
            
            print("\n" + "=" * 60)
            print("📊 STAGE 2 ISOLATION TEST SUMMARY")
            print("=" * 60)
            
            passed_tests = sum(1 for result in self.test_results if result['success'])
            failed_tests = len(self.test_results) - passed_tests
            
            print(f"Total Tests: {len(self.test_results)}")
            print(f"✅ Passed: {passed_tests}")
            print(f"❌ Failed: {failed_tests}")
            print(f"⏱️ Duration: {duration.total_seconds():.2f} seconds")
            
            if failed_tests > 0:
                print(f"\n❌ FAILED TESTS:")
                for result in self.test_results:
                    if not result['success']:
                        print(f"  - {result['name']}: {result['error']}")
            
            return failed_tests == 0

async def main():
    """Main test runner"""
    print("🔥 STAGE 2 ISOLATION TEST")
    print("BUGIT: Testing Stage 2 services in isolation to identify crash cause")
    print()
    
    # Create test suite
    test_suite = Stage2OnlyTest()
    
    print(f"🎯 Target: {test_suite.octane_host}:{test_suite.octane_port}")
    print()
    
    # Run Stage 2 isolation test
    success = await test_suite.run_stage2_only_test()
    
    if success:
        print("\n🎉 STAGE 2 ISOLATION TEST PASSED!")
        print("   Stage 2 services do not crash when run in isolation")
        return 0
    else:
        print("\n💥 STAGE 2 ISOLATION TEST FAILED!")
        print("   Stage 2 services crash even when run in isolation")
        return 1

if __name__ == "__main__":
    try:
        exit_code = asyncio.run(main())
        sys.exit(exit_code)
    except KeyboardInterrupt:
        print("\n🛑 Test interrupted by user")
        sys.exit(1)
    except Exception as e:
        print(f"💥 Test failed: {e}")
        sys.exit(1)