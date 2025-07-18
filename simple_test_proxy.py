#!/usr/bin/env python3
"""
Simple test proxy server for ObjectPtr passing test
Only handles rootNodeGraph and name API calls
"""

import asyncio
import json
import grpc
from aiohttp import web, ClientSession
import sys
import os
import socket
import subprocess

# Add the proxy directory to path for protobuf imports
script_dir = os.path.dirname(os.path.abspath(__file__))
proxy_dir = os.path.join(script_dir, 'proxy')
sys.path.append(proxy_dir)

def detect_octane_host():
    """Smart detection of Octane host based on environment"""
    
    def is_docker_container():
        """Check if we're running in a Docker container"""
        return (
            os.path.exists('/.dockerenv') or 
            os.environ.get('DOCKER_CONTAINER') == 'true' or
            os.environ.get('SANDBOX_USE_HOST_NETWORK') == 'true'
        )
    
    def can_resolve_host(hostname):
        """Check if hostname resolves"""
        try:
            socket.gethostbyname(hostname)
            return True
        except socket.gaierror:
            return False
    
    def can_connect_to_port(host, port, timeout=2):
        """Test if we can connect to host:port"""
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.settimeout(timeout)
            result = sock.connect_ex((host, port))
            sock.close()
            return result == 0
        except:
            return False
    
    # List of hosts to try in order
    candidates = []
    
    if is_docker_container():
        print("🐳 Docker environment detected")
        # In Docker, try Docker-specific hosts first
        if can_resolve_host('host.docker.internal'):
            candidates.append('host.docker.internal')
        candidates.extend(['172.17.0.1', '192.168.65.2', '127.0.0.1'])
    else:
        print("🖥️  Native environment detected")
        # Native environment, localhost should work
        candidates.append('127.0.0.1')
    
    # Test each candidate
    for host in candidates:
        print(f"🔍 Testing connection to {host}:51022...")
        if can_connect_to_port(host, 51022):
            print(f"✅ Found Octane at {host}:51022")
            return host
        else:
            print(f"❌ No connection to {host}:51022")
    
    # Fallback to localhost
    print("⚠️  No working host found, falling back to 127.0.0.1")
    return '127.0.0.1'

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

class SimpleTestProxy:
    def __init__(self):
        self.channel = None
        self.project_stub = None
        self.item_stub = None
        
    async def connect_to_octane(self, host=None, port=51022):
        """Connect to Octane gRPC server"""
        try:
            # Auto-detect host if not provided
            if host is None:
                host = detect_octane_host()
            
            print(f"🔌 Connecting to Octane at {host}:{port}...")
            self.channel = grpc.aio.insecure_channel(f'{host}:{port}')
            
            # Create stubs
            self.project_stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(self.channel)
            self.item_stub = apinodesystem_pb2_grpc.ApiItemServiceStub(self.channel)
            
            print("✅ Connected to Octane successfully")
            return True
            
        except Exception as e:
            print(f"❌ Failed to connect to Octane: {e}")
            return False
    
    async def get_root_node_graph(self):
        """Call ApiProjectManagerService/rootNodeGraph"""
        try:
            print("📤 Calling ApiProjectManagerService/rootNodeGraph...")
            request = apiprojectmanager_pb2.ApiProjectManager.rootNodeGraphRequest()
            response = await self.project_stub.rootNodeGraph(request)
            
            result = {
                'handle': response.result.handle,
                'type': response.result.type
            }
            print(f"📥 rootNodeGraph response: {result}")
            
            # Immediately test ObjectPtr passing by calling get_item_name
            print("🔄 Testing ObjectPtr passing: calling get_item_name with returned ObjectPtr...")
            try:
                name_result = await self.get_item_name(response.result)
                print(f"✅ ObjectPtr passing SUCCESS: name = '{name_result}'")
            except Exception as name_error:
                print(f"❌ ObjectPtr passing FAILED: {name_error}")
            
            return result
            
        except Exception as e:
            print(f"❌ rootNodeGraph failed: {e}")
            raise
    
    async def get_item_name(self, object_ref):
        """Call ApiItemService/name with ObjectRef"""
        try:
            print(f"📤 Calling ApiItemService/name with ObjectRef: {object_ref}")
            
            # Create the request
            request = apinodesystem_pb2.ApiItem.nameRequest()
            
            # Handle both protobuf ObjectRef and dictionary formats
            if hasattr(object_ref, 'handle') and hasattr(object_ref, 'type'):
                # Direct protobuf ObjectRef - pass it directly
                request.objectPtr.CopyFrom(object_ref)
                print(f"📤 Using protobuf ObjectRef directly: handle={object_ref.handle}, type={object_ref.type}")
            else:
                # Dictionary format
                request.objectPtr.handle = object_ref['handle']
                request.objectPtr.type = object_ref['type']
                print(f"📤 Using dictionary ObjectRef: handle={object_ref['handle']}, type={object_ref['type']}")
            
            print(f"📤 gRPC request: {request}")
            response = await self.item_stub.name(request)
            
            result = response.result
            print(f"📥 name response: '{result}'")
            return result
            
        except Exception as e:
            print(f"❌ name failed: {e}")
            raise

# Global proxy instance
proxy = SimpleTestProxy()

async def handle_root_node_graph(request):
    """Handle /octaneapi.ApiProjectManagerService/rootNodeGraph"""
    try:
        result = await proxy.get_root_node_graph()
        return web.json_response({
            'success': True,
            'data': {'result': result}
        })
    except Exception as e:
        return web.json_response({
            'success': False,
            'error': str(e)
        }, status=500)

async def handle_item_name(request):
    """Handle /octaneapi.ApiItemService/name"""
    try:
        # Get ObjectRef from request body
        request_data = await request.json()
        object_ref = request_data.get('objectPtr', {})
        
        result = await proxy.get_item_name(object_ref)
        return web.json_response({
            'success': True,
            'data': {'result': result}
        })
    except Exception as e:
        return web.json_response({
            'success': False,
            'error': str(e)
        }, status=500)

async def handle_options(request):
    """Handle CORS preflight requests - COMPREHENSIVE for file:// protocol"""
    return web.Response(
        headers={
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'GET, POST, PUT, DELETE, OPTIONS, HEAD, PATCH',
            'Access-Control-Allow-Headers': '*',
            'Access-Control-Allow-Credentials': 'true',
            'Access-Control-Max-Age': '86400',
            'Access-Control-Expose-Headers': '*',
        }
    )

def add_cors_headers(response):
    """Add CORS headers to response - COMPREHENSIVE for file:// protocol"""
    response.headers['Access-Control-Allow-Origin'] = '*'
    response.headers['Access-Control-Allow-Methods'] = 'GET, POST, PUT, DELETE, OPTIONS, HEAD, PATCH'
    response.headers['Access-Control-Allow-Headers'] = '*'
    response.headers['Access-Control-Allow-Credentials'] = 'true'
    response.headers['Access-Control-Max-Age'] = '86400'
    response.headers['Access-Control-Expose-Headers'] = '*'
    return response

async def create_app():
    """Create the web application"""
    app = web.Application()
    
    # Add CORS middleware
    @web.middleware
    async def cors_middleware(request, handler):
        if request.method == 'OPTIONS':
            return await handle_options(request)
        response = await handler(request)
        return add_cors_headers(response)
    
    app.middlewares.append(cors_middleware)
    
    # Add routes
    app.router.add_post('/octaneapi.ApiProjectManagerService/rootNodeGraph', handle_root_node_graph)
    app.router.add_post('/octaneapi.ApiItemService/name', handle_item_name)
    app.router.add_options('/{path:.*}', handle_options)
    
    return app

async def main():
    """Main function"""
    print("🚀 Starting Simple Test Proxy Server...")
    
    # Connect to Octane
    if not await proxy.connect_to_octane():
        print("❌ Failed to connect to Octane. Exiting.")
        return
    
    # Create and start web server
    app = await create_app()
    runner = web.AppRunner(app)
    await runner.setup()
    
    site = web.TCPSite(runner, '0.0.0.0', 51023)
    await site.start()
    
    print("✅ Simple Test Proxy Server started on http://0.0.0.0:51023")
    print("   Ready to test ObjectPtr passing!")
    
    # Keep running
    try:
        while True:
            await asyncio.sleep(1)
    except KeyboardInterrupt:
        print("\n🛑 Shutting down...")
        await runner.cleanup()

if __name__ == '__main__':
    asyncio.run(main())