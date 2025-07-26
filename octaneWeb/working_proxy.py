#!/usr/bin/env python3
"""
Working Octane gRPC Proxy using octaneGrpcTest protobuf files
Implements real gRPC calls to Octane LiveLink service
"""

import json
import asyncio
import aiohttp
from aiohttp import web
import grpc
import sys
import os
import traceback
from datetime import datetime

# Add octaneGrpcTest directory to path for protobuf imports
octane_test_dir = os.path.join(os.path.dirname(__file__), '..', 'octaneGrpcTest')
sys.path.insert(0, octane_test_dir)

# Import protobuf modules from octaneGrpcTest
try:
    from google.protobuf.empty_pb2 import Empty
    import apiprojectmanager_pb2
    import apiprojectmanager_pb2_grpc
    import apinodesystem_pb2
    import apinodesystem_pb2_grpc
    import common_pb2
    print("✅ Successfully imported protobuf modules from octaneGrpcTest")
except ImportError as e:
    print(f"❌ Failed to import protobuf modules: {e}")
    sys.exit(1)

# CORS headers
CORS_HEADERS = {
    'Access-Control-Allow-Origin': '*',
    'Access-Control-Allow-Methods': 'GET, POST, OPTIONS, PUT, DELETE, PATCH',
    'Access-Control-Allow-Headers': 'Content-Type, Accept, X-Grpc-Web, X-Call-Id, Authorization, X-Requested-With, Origin',
    'Access-Control-Allow-Credentials': 'false',
    'Access-Control-Max-Age': '86400'
}

class WorkingOctaneProxy:
    def __init__(self):
        self.octane_hosts = ["127.0.0.1", "host.docker.internal"]
        self.octane_port = 51022
        self.octane_host = None
        self.channel = None
        self.project_stub = None
        self.node_graph_stub = None
        self.item_array_stub = None
        
    async def connect_to_octane(self):
        """Connect to Octane gRPC service - try multiple hosts"""
        for host in self.octane_hosts:
            try:
                print(f"🔍 Trying to connect to Octane at {host}:{self.octane_port}")
                self.channel = grpc.insecure_channel(f'{host}:{self.octane_port}')
                
                # Create service stubs
                self.project_stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(self.channel)
                self.node_graph_stub = apinodesystem_pb2_grpc.ApiNodeGraphServiceStub(self.channel)
                self.item_array_stub = apinodesystem_pb2_grpc.ApiItemArrayServiceStub(self.channel)
                
                # Test the connection with a simple call
                await asyncio.get_event_loop().run_in_executor(
                    None, 
                    lambda: self.project_stub.rootNodeGraph(Empty(), timeout=2.0)
                )
                
                self.octane_host = host
                print(f"✅ Connected to Octane at {host}:{self.octane_port}")
                return True
            except Exception as e:
                print(f"❌ Failed to connect to {host}: {e}")
                if self.channel:
                    self.channel.close()
                    self.channel = None
                continue
        return False
    
    async def test_octane_connection(self, request):
        """Test if Octane is available"""
        try:
            if not self.channel:
                await self.connect_to_octane()
            
            if self.channel and self.project_stub:
                # Test with a simple call
                try:
                    empty_request = Empty()
                    response = await asyncio.get_event_loop().run_in_executor(
                        None, 
                        lambda: self.project_stub.rootNodeGraph(empty_request, timeout=5.0)
                    )
                    return web.json_response({
                        'success': True,
                        'message': 'Octane is available and responding',
                        'host': self.octane_host,
                        'port': self.octane_port,
                        'rootGraphHandle': response.result.handle if hasattr(response, 'result') else 'N/A'
                    }, headers=CORS_HEADERS)
                except Exception as e:
                    return web.json_response({
                        'success': False,
                        'message': 'Octane connected but not responding to API calls',
                        'error': str(e)
                    }, headers=CORS_HEADERS, status=503)
            else:
                return web.json_response({
                    'success': False,
                    'message': 'Cannot connect to Octane',
                    'error': 'Connection failed'
                }, headers=CORS_HEADERS, status=503)
                
        except Exception as e:
            return web.json_response({
                'success': False,
                'message': 'Octane not available',
                'error': str(e)
            }, headers=CORS_HEADERS, status=503)
    
    async def handle_options(self, request):
        """Handle CORS preflight requests"""
        return web.Response(headers=CORS_HEADERS)
    
    async def handle_root_node_graph(self, request):
        """Handle ApiProjectManagerService.rootNodeGraph"""
        try:
            print(f"📤 Calling ApiProjectManagerService.rootNodeGraph")
            
            if not self.project_stub:
                await self.connect_to_octane()
            
            if not self.project_stub:
                raise Exception("Not connected to Octane")
            
            # Create empty request (following octaneGrpcTest pattern)
            empty_request = Empty()
            response = await asyncio.get_event_loop().run_in_executor(
                None, 
                lambda: self.project_stub.rootNodeGraph(empty_request, timeout=10.0)
            )
            
            print(f"📥 rootNodeGraph response: {response}")
            
            if hasattr(response, 'result') and hasattr(response.result, 'handle') and response.result.handle > 0:
                result = {
                    'success': True,
                    'objectRef': {
                        'handle': response.result.handle,
                        'type': response.result.type
                    }
                }
                print(f"✅ rootNodeGraph successful: handle={response.result.handle}, type={response.result.type}")
                return web.json_response(result, headers=CORS_HEADERS)
            else:
                return web.json_response({
                    'success': False,
                    'error': 'No root node graph available',
                    'response': str(response)
                }, headers=CORS_HEADERS)
                
        except Exception as e:
            print(f"❌ rootNodeGraph failed: {e}")
            return web.json_response({
                'success': False,
                'error': str(e),
                'traceback': traceback.format_exc()
            }, headers=CORS_HEADERS, status=500)
    
    async def handle_get_owned_items(self, request):
        """Handle ApiNodeGraphService.getOwnedItems"""
        try:
            data = await request.json()
            object_ptr = data.get('objectPtr')
            
            if not object_ptr:
                raise Exception("objectPtr required")
            
            print(f"📤 Calling ApiNodeGraphService.getOwnedItems with handle={object_ptr.get('handle')}")
            
            if not self.node_graph_stub:
                await self.connect_to_octane()
            
            if not self.node_graph_stub:
                raise Exception("Not connected to Octane")
            
            # Create request (following octaneGrpcTest pattern)
            grpc_request = apinodesystem_pb2.ApiNodeGraph.getOwnedItemsRequest()
            grpc_request.objectPtr.handle = object_ptr['handle']
            # Convert ApiRootNodeGraph (18) to ApiNodeGraph (20) for service calls
            if object_ptr['type'] == 18:  # ApiRootNodeGraph
                grpc_request.objectPtr.type = 20  # ApiNodeGraph
            else:
                grpc_request.objectPtr.type = object_ptr['type']
            
            response = await asyncio.get_event_loop().run_in_executor(
                None, 
                lambda: self.node_graph_stub.getOwnedItems(grpc_request, timeout=10.0)
            )
            
            print(f"📥 getOwnedItems response: {response}")
            
            result = {
                'success': True,
                'objectRef': {
                    'handle': response.list.handle,
                    'type': response.list.type
                }
            }
            
            print(f"✅ getOwnedItems successful: itemArrayHandle={response.list.handle}")
            return web.json_response(result, headers=CORS_HEADERS)
                
        except Exception as e:
            print(f"❌ getOwnedItems failed: {e}")
            return web.json_response({
                'success': False,
                'error': str(e),
                'traceback': traceback.format_exc()
            }, headers=CORS_HEADERS, status=500)
    
    async def handle_item_array_size(self, request):
        """Handle ApiItemArrayService.size"""
        try:
            data = await request.json()
            object_ptr = data.get('objectPtr')
            
            if not object_ptr:
                raise Exception("objectPtr required")
            
            print(f"📤 Calling ApiItemArrayService.size with handle={object_ptr.get('handle')}")
            
            if not self.item_array_stub:
                await self.connect_to_octane()
            
            if not self.item_array_stub:
                raise Exception("Not connected to Octane")
            
            # Create request
            grpc_request = apinodesystem_pb2.ApiItemArray.sizeRequest()
            grpc_request.objectPtr.handle = object_ptr['handle']
            grpc_request.objectPtr.type = object_ptr['type']
            
            response = await asyncio.get_event_loop().run_in_executor(
                None, 
                lambda: self.item_array_stub.size(grpc_request, timeout=10.0)
            )
            
            print(f"📥 size response: {response}")
            
            result = {
                'success': True,
                'size': response.result
            }
            
            print(f"✅ size successful: size={response.result}")
            return web.json_response(result, headers=CORS_HEADERS)
                
        except Exception as e:
            print(f"❌ size failed: {e}")
            return web.json_response({
                'success': False,
                'error': str(e),
                'traceback': traceback.format_exc()
            }, headers=CORS_HEADERS, status=500)
    
    async def handle_item_array_get1(self, request):
        """Handle ApiItemArrayService.get1 calls"""
        try:
            print(f"📤 Calling ApiItemArrayService.get1")
            
            if not self.item_array_stub:
                await self.connect_to_octane()
            
            if not self.item_array_stub:
                raise Exception("Not connected to Octane")
            
            # Parse request data
            data = await request.json()
            object_ptr = data.get('objectPtr', {})
            index = data.get('index', 0)
            
            # Create request
            grpc_request = apinodesystem_pb2.ApiItemArray.getRequest()
            grpc_request.objectPtr.handle = object_ptr['handle']
            grpc_request.objectPtr.type = object_ptr['type']
            grpc_request.index = index
            
            response = await asyncio.get_event_loop().run_in_executor(
                None, 
                lambda: self.item_array_stub.get1(grpc_request, timeout=10.0)
            )
            
            print(f"📥 get1 response: {response}")
            
            result = {
                'success': True,
                'objectRef': {
                    'handle': response.result.handle,
                    'type': response.result.type
                }
            }
            
            print(f"✅ get1 successful: handle={response.result.handle}, type={response.result.type}")
            return web.json_response(result, headers=CORS_HEADERS)
                
        except Exception as e:
            print(f"❌ get1 failed: {e}")
            return web.json_response({
                'success': False,
                'error': str(e),
                'traceback': traceback.format_exc()
            }, headers=CORS_HEADERS, status=500)
    
    async def handle_item_name(self, request):
        """Handle ApiItemService.name calls"""
        try:
            print(f"📤 Calling ApiItemService.name")
            
            if not self.channel:
                await self.connect_to_octane()
            
            if not self.channel:
                raise Exception("Not connected to Octane")
            
            # Create item service stub
            item_stub = apinodesystem_pb2_grpc.ApiItemServiceStub(self.channel)
            
            # Parse request data
            data = await request.json()
            object_ptr = data.get('objectPtr', {})
            
            # Create request - need to convert to ApiItem type (16)
            grpc_request = apinodesystem_pb2.ApiItem.nameRequest()
            grpc_request.objectPtr.handle = object_ptr['handle']
            grpc_request.objectPtr.type = 16  # ApiItem type for name calls
            
            response = await asyncio.get_event_loop().run_in_executor(
                None, 
                lambda: item_stub.name(grpc_request, timeout=10.0)
            )
            
            print(f"📥 name response: {response}")
            
            result = {
                'success': True,
                'name': response.result
            }
            
            print(f"✅ name successful: name='{response.result}'")
            return web.json_response(result, headers=CORS_HEADERS)
                
        except Exception as e:
            print(f"❌ name failed: {e}")
            return web.json_response({
                'success': False,
                'error': str(e),
                'traceback': traceback.format_exc()
            }, headers=CORS_HEADERS, status=500)
    
    async def handle_grpc_call(self, request):
        """Handle generic gRPC calls"""
        try:
            # Get the service and method from URL
            path_parts = request.path.strip('/').split('/')
            if len(path_parts) < 2:
                return web.json_response({
                    'success': False,
                    'error': 'Invalid path format. Use /ServiceName/methodName'
                }, headers=CORS_HEADERS, status=400)
            
            service_name = path_parts[0]
            method_name = path_parts[1]
            
            print(f"📤 gRPC Call: {service_name}.{method_name}")
            
            # Route to specific handlers
            if service_name == 'ApiProjectManagerService' and method_name == 'rootNodeGraph':
                return await self.handle_root_node_graph(request)
            elif (service_name == 'ApiNodeGraphService' or service_name == 'ApiNodeGraph') and method_name == 'getOwnedItems':
                return await self.handle_get_owned_items(request)
            elif (service_name == 'ApiItemArrayService' or service_name == 'ApiItemArray') and method_name == 'size':
                return await self.handle_item_array_size(request)
            elif (service_name == 'ApiItemArrayService' or service_name == 'ApiItemArray') and method_name == 'get1':
                return await self.handle_item_array_get1(request)
            elif (service_name == 'ApiItemService' or service_name == 'ApiItem') and method_name == 'name':
                return await self.handle_item_name(request)
            else:
                return web.json_response({
                    'success': False,
                    'error': f'Method {service_name}.{method_name} not implemented yet',
                    'service': service_name,
                    'method': method_name
                }, headers=CORS_HEADERS, status=501)
                
        except Exception as e:
            print(f"❌ Error handling gRPC call: {e}")
            return web.json_response({
                'success': False,
                'error': str(e),
                'traceback': traceback.format_exc()
            }, headers=CORS_HEADERS, status=500)

async def create_app():
    """Create the web application"""
    proxy = WorkingOctaneProxy()
    
    app = web.Application()
    
    # Add routes
    app.router.add_options('/{path:.*}', proxy.handle_options)
    app.router.add_get('/test', proxy.test_octane_connection)
    app.router.add_post('/test', proxy.test_octane_connection)
    app.router.add_post('/{service}/{method}', proxy.handle_grpc_call)
    
    return app

async def main():
    """Main entry point"""
    print("🚀 Starting Working Octane Proxy Server...")
    print(f"📡 Target: Octane at 127.0.0.1:51022")
    print(f"🌐 Proxy: http://localhost:51998")
    
    app = await create_app()
    
    runner = web.AppRunner(app)
    await runner.setup()
    
    site = web.TCPSite(runner, '0.0.0.0', 51998)
    await site.start()
    
    print("✅ Working Octane Proxy Server started successfully!")
    print("🔗 Test connection: curl http://localhost:51998/test")
    
    # Keep running
    try:
        while True:
            await asyncio.sleep(1)
    except KeyboardInterrupt:
        print("\n🛑 Shutting down proxy server...")
        await runner.cleanup()

if __name__ == '__main__':
    asyncio.run(main())