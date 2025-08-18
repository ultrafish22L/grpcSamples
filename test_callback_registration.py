#!/usr/bin/env python3
"""
Test callback registration directly
"""

import asyncio
import aiohttp
import json

async def test_callback_registration():
    """Test the callback registration endpoint"""
    try:
        print("🧪 Testing callback registration...")
        
        async with aiohttp.ClientSession() as session:
            # Test callback registration
            url = "http://localhost:51023/render/register-callback"
            print(f"📤 POST {url}")
            
            async with session.post(url, 
                                  headers={'Content-Type': 'application/json'},
                                  json={},
                                  timeout=aiohttp.ClientTimeout(total=5)) as response:
                print(f"📥 Status: {response.status}")
                result = await response.json()
                print(f"📥 Result: {json.dumps(result, indent=2)}")
                
                if result.get('success'):
                    print("✅ Callback registration successful!")
                else:
                    print("❌ Callback registration failed!")
                    
    except asyncio.TimeoutError:
        print("⏰ Callback registration timed out - likely Octane not running")
    except Exception as e:
        print(f"❌ Error testing callback registration: {e}")

if __name__ == "__main__":
    asyncio.run(test_callback_registration())