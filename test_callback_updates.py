#!/usr/bin/env python3
"""
Test script to verify callback system receives ongoing updates
This will trigger continuous renders in Octane to test if callbacks work for multiple images
"""

import asyncio
import sys
import os
import time

# Add octaneProxy to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'octaneProxy'))

from octaneProxy.callback_streamer import get_callback_streamer, initialize_callback_system

async def test_continuous_callbacks():
    """Test that callback system receives multiple images"""
    print("🧪 Testing continuous callback updates...")
    
    # Initialize callback system
    success = await initialize_callback_system("127.0.0.1:51022")
    if not success:
        print("❌ Failed to initialize callback system")
        return False
    
    streamer = get_callback_streamer()
    
    # Monitor callbacks for a period
    print("📊 Monitoring callbacks for 30 seconds...")
    start_time = time.time()
    initial_count = streamer.callback_count
    
    # Trigger renders periodically to generate new callbacks
    try:
        # Import gRPC modules
        import grpc
        sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'octaneProxy', 'generated'))
        from generated import apichangemanager_pb2, apichangemanager_pb2_grpc
        
        # Create gRPC channel to Octane
        channel = grpc.aio.insecure_channel("127.0.0.1:51022")
        change_stub = apichangemanager_pb2_grpc.ApiChangeManagerServiceStub(channel)
        
        for i in range(10):  # Trigger 10 renders over 30 seconds
            try:
                print(f"🔄 Triggering render #{i+1}...")
                
                # Call ApiChangeManager::update() to trigger render
                request = apichangemanager_pb2.ApiChangeManager.updateRequest()
                await change_stub.update(request)
                
                # Wait and check callback count
                await asyncio.sleep(3)
                current_count = streamer.callback_count
                print(f"📊 Callback count: {current_count} (delta: {current_count - initial_count})")
                
            except Exception as e:
                print(f"⚠️ Error triggering render #{i+1}: {e}")
        
        await channel.close()
        
    except ImportError as e:
        print(f"⚠️ Could not import gRPC modules for render triggering: {e}")
        print("📊 Just monitoring existing callbacks...")
        await asyncio.sleep(30)
    
    # Final statistics
    end_time = time.time()
    final_count = streamer.callback_count
    total_callbacks = final_count - initial_count
    
    print(f"\n📊 === CALLBACK TEST RESULTS ===")
    print(f"⏱️ Test duration: {end_time - start_time:.1f} seconds")
    print(f"📸 Initial callback count: {initial_count}")
    print(f"📸 Final callback count: {final_count}")
    print(f"📸 New callbacks received: {total_callbacks}")
    print(f"📊 Callback rate: {total_callbacks / (end_time - start_time):.2f} callbacks/second")
    
    if total_callbacks > 0:
        print("✅ Callback system is receiving updates!")
        return True
    else:
        print("❌ No new callbacks received - system may not be working")
        return False

if __name__ == "__main__":
    asyncio.run(test_continuous_callbacks())