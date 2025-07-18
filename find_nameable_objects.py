#!/usr/bin/env python3
"""
Find objects that DO support the name() API
"""

import asyncio
import grpc
import sys
import os

# Add the proxy directory to path for protobuf imports
script_dir = os.path.dirname(os.path.abspath(__file__))
proxy_dir = os.path.join(script_dir, 'proxy')
sys.path.append(proxy_dir)

import apiprojectmanager_pb2_grpc
import apiprojectmanager_pb2
import apinodesystem_pb2_grpc
import apinodesystem_pb2
import common_pb2

async def find_nameable_objects():
    """Find objects that support name() API"""
    
    # Connect to Octane
    channel = grpc.aio.insecure_channel('host.docker.internal:51022')
    project_stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(channel)
    item_stub = apinodesystem_pb2_grpc.ApiItemServiceStub(channel)
    
    try:
        print("🔍 TESTING: materialBall object")
        material_request = apiprojectmanager_pb2.ApiProjectManager.materialBallRequest()
        material_response = await project_stub.materialBall(material_request)
        
        print(f"📥 Material ball response: {material_response}")
        
        if hasattr(material_response, 'result'):
            material_obj = material_response.result
            print(f"🎯 Material ObjectRef: handle={material_obj.handle}, type='{material_obj.type}'")
            
            # Try to get name
            name_request = apinodesystem_pb2.ApiItem.nameRequest()
            name_request.objectPtr.CopyFrom(material_obj)
            
            try:
                name_response = await item_stub.name(name_request)
                print(f"✅ SUCCESS: Material ball name = '{name_response.result}'")
            except grpc.RpcError as e:
                print(f"❌ Material ball name failed: {e.details()}")
        
        print("\n🔍 TESTING: previewRenderTarget object")
        preview_request = apiprojectmanager_pb2.ApiProjectManager.previewRenderTargetRequest()
        preview_response = await project_stub.previewRenderTarget(preview_request)
        
        print(f"📥 Preview render target response: {preview_response}")
        
        if hasattr(preview_response, 'result'):
            preview_obj = preview_response.result
            print(f"🎯 Preview ObjectRef: handle={preview_obj.handle}, type='{preview_obj.type}'")
            
            # Try to get name
            name_request = apinodesystem_pb2.ApiItem.nameRequest()
            name_request.objectPtr.CopyFrom(preview_obj)
            
            try:
                name_response = await item_stub.name(name_request)
                print(f"✅ SUCCESS: Preview render target name = '{name_response.result}'")
            except grpc.RpcError as e:
                print(f"❌ Preview render target name failed: {e.details()}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        await channel.close()

if __name__ == "__main__":
    asyncio.run(find_nameable_objects())