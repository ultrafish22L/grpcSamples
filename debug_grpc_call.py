#!/usr/bin/env python3
"""
Debug the exact gRPC call being made to understand the "invalid pointer type" error
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

async def debug_grpc_calls():
    """Debug the exact gRPC calls and responses"""
    
    # Connect to Octane
    channel = grpc.aio.insecure_channel('host.docker.internal:51022')
    project_stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(channel)
    item_stub = apinodesystem_pb2_grpc.ApiItemServiceStub(channel)
    
    try:
        print("🔍 STEP 1: Get root node graph")
        request = apiprojectmanager_pb2.ApiProjectManager.rootNodeGraphRequest()
        print(f"📤 Request: {request}")
        print(f"📤 Request serialized: {request.SerializeToString().hex()}")
        
        response = await project_stub.rootNodeGraph(request)
        print(f"📥 Response: {response}")
        print(f"📥 Response serialized: {response.SerializeToString().hex()}")
        
        root_obj_ref = response.result
        print(f"🎯 Root ObjectRef: handle={root_obj_ref.handle}, type='{root_obj_ref.type}'")
        
        print("\n🔍 STEP 2: Try to get name of root node graph")
        name_request = apinodesystem_pb2.ApiItem.nameRequest()
        name_request.objectPtr.CopyFrom(root_obj_ref)
        
        print(f"📤 Name request: {name_request}")
        print(f"📤 Name request serialized: {name_request.SerializeToString().hex()}")
        
        try:
            name_response = await item_stub.name(name_request)
            print(f"📥 Name response: {name_response}")
            print(f"✅ SUCCESS: Name = '{name_response.result}'")
        except grpc.RpcError as e:
            print(f"❌ gRPC Error: {e.code()} - {e.details()}")
            print(f"❌ Debug error: {e.debug_error_string}")
            
            # Let's try to understand what types ARE valid
            print("\n🔍 STEP 3: Let's try to get scene tree to find objects that DO have names")
            try:
                # Try buildSceneTree if it exists
                scene_request = apiprojectmanager_pb2.ApiProjectManager.buildSceneTreeRequest()
                scene_request.rootNodeGraph.CopyFrom(root_obj_ref)
                scene_response = await project_stub.buildSceneTree(scene_request)
                
                print(f"📥 Scene tree response: {scene_response}")
                
                # Try to get name of first scene object
                if hasattr(scene_response, 'result') and hasattr(scene_response.result, 'children'):
                    for child in scene_response.result.children[:1]:  # Just try first child
                        print(f"🎯 Trying child: {child}")
                        child_name_request = apinodesystem_pb2.ApiItem.nameRequest()
                        child_name_request.objectPtr.CopyFrom(child)
                        
                        try:
                            child_name_response = await item_stub.name(child_name_request)
                            print(f"✅ Child name SUCCESS: '{child_name_response.result}'")
                            break
                        except grpc.RpcError as child_e:
                            print(f"❌ Child name failed: {child_e.details()}")
                            
            except Exception as scene_e:
                print(f"❌ Scene tree failed: {scene_e}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        await channel.close()

if __name__ == "__main__":
    asyncio.run(debug_grpc_calls())