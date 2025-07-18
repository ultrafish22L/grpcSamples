#!/usr/bin/env python3
"""
Simple gRPC test call to Octane
"""

import asyncio
import grpc
import sys
import os

# Add the proxy directory to path for protobuf imports
script_dir = os.path.dirname(os.path.abspath(__file__))
proxy_dir = os.path.join(script_dir, 'proxy')
sys.path.append(proxy_dir)

try:
    import apiprojectmanager_pb2_grpc
    import apiprojectmanager_pb2
    import common_pb2
    print("✅ Successfully imported protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import protobuf modules: {e}")
    sys.exit(1)

async def test_octane_grpc():
    """Test basic gRPC call to Octane"""
    
    # Connect to Octane
    channel = grpc.aio.insecure_channel('host.docker.internal:51022')
    stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(channel)
    
    try:
        print("🔌 Testing gRPC connection to Octane...")
        
        # Try to get root node graph (simple call)
        request = apiprojectmanager_pb2.GetRootNodeGraphRequest()
        
        print("📤 Sending GetRootNodeGraph request...")
        response = await stub.GetRootNodeGraph(request, timeout=5.0)
        
        print("✅ SUCCESS! Received response from Octane:")
        print(f"📥 Response type: {type(response)}")
        print(f"📥 Response: {response}")
        
    except grpc.RpcError as e:
        print(f"❌ gRPC Error: {e.code()} - {e.details()}")
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        await channel.close()

if __name__ == "__main__":
    asyncio.run(test_octane_grpc())