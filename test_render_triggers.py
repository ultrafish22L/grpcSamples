#!/usr/bin/env python3
"""
Test script to trigger multiple renders via the proxy to test callback updates
"""

import asyncio
import aiohttp
import json
import time

async def trigger_render_via_proxy():
    """Trigger a render via the proxy"""
    try:
        async with aiohttp.ClientSession() as session:
            url = "http://localhost:51023/ApiChangeManager/update"
            headers = {
                'Content-Type': 'application/json',
                'X-Call-Id': f'test_render_{int(time.time())}'
            }
            
            async with session.post(url, json={}, headers=headers) as response:
                if response.status == 200:
                    result = await response.json()
                    print(f"✅ Render triggered successfully: {result}")
                    return True
                else:
                    text = await response.text()
                    print(f"❌ Render trigger failed: {response.status} - {text}")
                    return False
                    
    except Exception as e:
        print(f"❌ Error triggering render: {e}")
        return False

async def test_multiple_renders():
    """Test triggering multiple renders to see if callbacks update"""
    print("🧪 Testing multiple render triggers...")
    
    # Check proxy health first
    try:
        async with aiohttp.ClientSession() as session:
            async with session.get("http://localhost:51023/health") as response:
                if response.status == 200:
                    health = await response.json()
                    print(f"✅ Proxy health: {health}")
                else:
                    print(f"❌ Proxy not healthy: {response.status}")
                    return
    except Exception as e:
        print(f"❌ Cannot connect to proxy: {e}")
        return
    
    # Trigger multiple renders
    print("🔄 Triggering 5 renders with 3-second intervals...")
    
    for i in range(5):
        print(f"\n🎬 Triggering render #{i+1}...")
        success = await trigger_render_via_proxy()
        
        if success:
            print(f"✅ Render #{i+1} triggered")
        else:
            print(f"❌ Render #{i+1} failed")
        
        if i < 4:  # Don't wait after the last render
            print("⏳ Waiting 3 seconds...")
            await asyncio.sleep(3)
    
    print("\n✅ Test completed. Check the browser to see if new images appeared.")
    print("💡 If images are updating, the callback system is working correctly.")
    print("💡 If only the first image shows, there may be an issue with ongoing callbacks.")

if __name__ == "__main__":
    asyncio.run(test_multiple_renders())