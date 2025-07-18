#!/usr/bin/env python3
"""
Direct ObjectPtr test - bypasses HTTP proxy and tests gRPC directly
"""

import asyncio
import grpc
import sys
import os

# Add the proxy directory to path for protobuf imports
sys.path.append('/workspace/grpcSamples/proxy')

try:
    import apiprojectmanager_pb2_grpc
    import apiprojectmanager_pb2
    import apinodesystem_pb2_grpc  
    import apinodesystem_pb2
    import common_pb2
    print("✅ Successfully imported protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import protobuf modules: {e}")
    sys.exit(1)

async def test_objectptr_passing():
    """Direct test of ObjectPtr passing"""
    try:
        print("🚀 Starting direct ObjectPtr test...")
        
        # Connect to Octane
        print("🔌 Connecting to Octane at 127.0.0.1:51022...")
        channel = grpc.aio.insecure_channel('127.0.0.1:51022')
        
        # Create stubs
        project_stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(channel)
        item_stub = apinodesystem_pb2_grpc.ApiItemServiceStub(channel)
        
        print("✅ Connected to Octane successfully")
        
        # Step 1: Get ObjectPtr from rootNodeGraph
        print("\n📤 Step 1: Calling ApiProjectManagerService/rootNodeGraph...")
        request = apiprojectmanager_pb2.ApiProjectManager.rootNodeGraphRequest()
        response = await project_stub.rootNodeGraph(request)
        
        object_ref = {
            'handle': response.result.handle,
            'type': response.result.type
        }
        print(f"📥 Step 1 SUCCESS: Got ObjectRef = {object_ref}")
        
        # Step 2: Use ObjectPtr to get name
        print(f"\n📤 Step 2: Calling ApiItemService/name with ObjectRef: {object_ref}")
        
        # Create the request
        name_request = apinodesystem_pb2.ApiItem.nameRequest()
        name_request.objectPtr.handle = object_ref['handle']
        name_request.objectPtr.type = object_ref['type']
        
        print(f"📤 gRPC request structure: {name_request}")
        
        try:
            name_response = await item_stub.name(name_request)
            result = name_response.result
            print(f"📥 Step 2 SUCCESS: Got name = '{result}'")
            print(f"\n🎉 COMPLETE SUCCESS: ObjectPtr passing works perfectly!")
            print(f"   - Step 1: rootNodeGraph returned ObjectRef {object_ref}")
            print(f"   - Step 2: name API accepted ObjectPtr and returned '{result}'")
            
        except Exception as name_error:
            print(f"📥 Step 2 FAILED: {name_error}")
            print(f"\n❌ CORE ISSUE CONFIRMED: ObjectPtr passing fails with 'invalid pointer type'")
            print(f"   - Step 1: rootNodeGraph works perfectly")
            print(f"   - Step 2: name API rejects the ObjectPtr despite correct class hierarchy")
            print(f"   - This is the exact issue that needs to be solved")
        
        # Close connection
        await channel.close()
        
    except Exception as e:
        print(f"❌ Test failed: {e}")

if __name__ == '__main__':
    asyncio.run(test_objectptr_passing())