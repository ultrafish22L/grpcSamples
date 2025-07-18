#!/usr/bin/env python3
"""
Test using the correct services for each object type
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

async def test_correct_services():
    """Test using correct services for each object type"""
    
    # Connect to Octane
    channel = grpc.aio.insecure_channel('host.docker.internal:51022')
    project_stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(channel)
    
    # Try all available services
    item_stub = apinodesystem_pb2_grpc.ApiItemServiceStub(channel)
    node_stub = apinodesystem_pb2_grpc.ApiNodeServiceStub(channel)
    root_graph_stub = apinodesystem_pb2_grpc.ApiRootNodeGraphServiceStub(channel)
    
    try:
        print("🔍 STEP 1: Get root node graph")
        request = apiprojectmanager_pb2.ApiProjectManager.rootNodeGraphRequest()
        response = await project_stub.rootNodeGraph(request)
        root_obj_ref = response.result
        print(f"🎯 Root ObjectRef: handle={root_obj_ref.handle}, type='{root_obj_ref.type}'")
        
        print("\n🔍 STEP 2: Try ApiRootNodeGraphService for root graph")
        try:
            # Check what methods are available on root graph service
            print("Available methods on ApiRootNodeGraphService:")
            for attr in dir(root_graph_stub):
                if not attr.startswith('_') and callable(getattr(root_graph_stub, attr)):
                    print(f"  - {attr}")
                    
            # Try name method if it exists
            if hasattr(root_graph_stub, 'name'):
                name_request = apinodesystem_pb2.ApiRootNodeGraph.nameRequest()
                name_request.objectPtr.CopyFrom(root_obj_ref)
                name_response = await root_graph_stub.name(name_request)
                print(f"✅ SUCCESS with ApiRootNodeGraphService: '{name_response.result}'")
            else:
                print("❌ No name method on ApiRootNodeGraphService")
                
        except Exception as e:
            print(f"❌ ApiRootNodeGraphService failed: {e}")
        
        print("\n🔍 STEP 3: Get material ball (ApiNode)")
        material_request = apiprojectmanager_pb2.ApiProjectManager.materialBallRequest()
        material_response = await project_stub.materialBall(material_request)
        material_obj = material_response.result
        print(f"🎯 Material ObjectRef: handle={material_obj.handle}, type='{material_obj.type}'")
        
        print("\n🔍 STEP 4: Try ApiNodeService for material ball")
        try:
            # Check what methods are available on node service
            print("Available methods on ApiNodeService:")
            for attr in dir(node_stub):
                if not attr.startswith('_') and callable(getattr(node_stub, attr)):
                    print(f"  - {attr}")
                    
            # Try name method if it exists
            if hasattr(node_stub, 'name'):
                name_request = apinodesystem_pb2.ApiNode.nameRequest()
                name_request.objectPtr.CopyFrom(material_obj)
                name_response = await node_stub.name(name_request)
                print(f"✅ SUCCESS with ApiNodeService: '{name_response.result}'")
            else:
                print("❌ No name method on ApiNodeService")
                
        except Exception as e:
            print(f"❌ ApiNodeService failed: {e}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        await channel.close()

if __name__ == "__main__":
    asyncio.run(test_correct_services())