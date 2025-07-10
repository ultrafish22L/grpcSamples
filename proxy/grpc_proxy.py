#!/usr/bin/env python3
"""
Simple HTTP-to-gRPC proxy for Octane LiveLink
Converts HTTP requests from browser to gRPC calls to Octane server
"""

import json
import asyncio
import aiohttp
from aiohttp import web
from aiohttp.web import middleware
import grpc
import sys
import os

# Add the generated protobuf path
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'shared', 'generated'))

try:
    import livelink_pb2
    import livelink_pb2_grpc
    print("✅ Successfully imported gRPC protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import gRPC modules: {e}")
    print("Note: This proxy requires the generated protobuf files from the C++ build")
    sys.exit(1)

class LiveLinkProxy:
    def __init__(self, octane_address='127.0.0.1:51022'):
        self.octane_address = octane_address
        self.channel = None
        self.stub = None
        
    async def connect_to_octane(self):
        """Connect to Octane gRPC server"""
        try:
            print(f"Connecting to Octane gRPC server at {self.octane_address}")
            self.channel = grpc.aio.insecure_channel(self.octane_address)
            self.stub = livelink_pb2_grpc.LiveLinkServiceStub(self.channel)
            
            # Test connection
            request = livelink_pb2.Empty()
            response = await self.stub.GetCamera(request)
            print("✅ Successfully connected to Octane LiveLink server")
            return True
            
        except Exception as e:
            print(f"❌ Failed to connect to Octane: {e}")
            return False
    
    async def disconnect(self):
        """Disconnect from Octane"""
        if self.channel:
            await self.channel.close()
            
    async def get_camera(self):
        """Get camera state from Octane"""
        try:
            request = livelink_pb2.Empty()
            response = await self.stub.GetCamera(request)
            
            return {
                'position': {'x': response.position.x, 'y': response.position.y, 'z': response.position.z},
                'target': {'x': response.target.x, 'y': response.target.y, 'z': response.target.z},
                'up': {'x': response.up.x, 'y': response.up.y, 'z': response.up.z}
            }
        except Exception as e:
            raise Exception(f"Failed to get camera: {e}")
    
    async def set_camera(self, camera_data):
        """Set camera state in Octane"""
        try:
            request = livelink_pb2.CameraState()
            
            # Handle position (oneof field)
            if 'position' in camera_data:
                pos = camera_data['position']
                request.position.x = pos['x']
                request.position.y = pos['y']
                request.position.z = pos['z']
            
            # Handle target (oneof field)
            if 'target' in camera_data:
                target = camera_data['target']
                request.target.x = target['x']
                request.target.y = target['y']
                request.target.z = target['z']
            
            # Handle up vector (oneof field)
            if 'up' in camera_data:
                up = camera_data['up']
                request.up.x = up['x']
                request.up.y = up['y']
                request.up.z = up['z']
            
            # Handle field of view (oneof field)
            if 'fov' in camera_data:
                request.fov = camera_data['fov']
            
            response = await self.stub.SetCamera(request)
            return True
        except Exception as e:
            raise Exception(f"Failed to set camera: {e}")
    
    async def get_meshes(self):
        """Get mesh list from Octane"""
        try:
            request = livelink_pb2.Empty()
            response = await self.stub.GetMeshes(request)
            
            meshes = []
            for mesh in response.meshes:
                meshes.append({
                    'id': mesh.name,
                    'name': mesh.name,
                    'vertices': len(mesh.positions) if hasattr(mesh, 'positions') else 0,
                    'faces': len(mesh.polyVertIndices) // 3 if hasattr(mesh, 'polyVertIndices') else 0
                })
            
            return meshes
        except Exception as e:
            raise Exception(f"Failed to get meshes: {e}")
    
    async def get_mesh(self, mesh_id):
        """Get specific mesh data from Octane"""
        try:
            request = livelink_pb2.MeshRequest()
            request.objecthandle = mesh_id
            
            response = await self.stub.GetMesh(request)
            
            return {
                'id': mesh_id,
                'name': response.name,
                'vertices': len(response.positions) if hasattr(response, 'positions') else 0,
                'faces': len(response.polyVertIndices) // 3 if hasattr(response, 'polyVertIndices') else 0
            }
        except Exception as e:
            raise Exception(f"Failed to get mesh: {e}")

# Global proxy instance
proxy = LiveLinkProxy()

@middleware
async def cors_handler(request, handler):
    """Handle CORS for browser requests"""
    response = await handler(request)
    response.headers['Access-Control-Allow-Origin'] = '*'
    response.headers['Access-Control-Allow-Methods'] = 'GET, POST, OPTIONS'
    response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Accept, X-Grpc-Web, X-Call-Id'
    return response

async def handle_options(request):
    """Handle CORS preflight requests"""
    return web.Response(
        headers={
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'GET, POST, OPTIONS',
            'Access-Control-Allow-Headers': 'Content-Type, Accept, X-Grpc-Web, X-Call-Id'
        }
    )

async def handle_health(request):
    """Health check endpoint"""
    return web.json_response({'status': 'ok', 'connected': proxy.stub is not None})

async def handle_get_camera(request):
    """Handle GetCamera requests"""
    try:
        camera_data = await proxy.get_camera()
        return web.json_response({'success': True, 'data': camera_data})
    except Exception as e:
        return web.json_response({'success': False, 'error': str(e)}, status=500)

async def handle_set_camera(request):
    """Handle SetCamera requests"""
    try:
        data = await request.json()
        await proxy.set_camera(data)
        return web.json_response({'success': True})
    except Exception as e:
        return web.json_response({'success': False, 'error': str(e)}, status=500)

async def handle_get_meshes(request):
    """Handle GetMeshes requests"""
    try:
        meshes = await proxy.get_meshes()
        return web.json_response({'success': True, 'data': meshes})
    except Exception as e:
        return web.json_response({'success': False, 'error': str(e)}, status=500)

async def handle_get_mesh(request):
    """Handle GetMesh requests"""
    try:
        data = await request.json()
        mesh_data = await proxy.get_mesh(data['objecthandle'])
        return web.json_response({'success': True, 'data': mesh_data})
    except Exception as e:
        return web.json_response({'success': False, 'error': str(e)}, status=500)

async def init_app():
    """Initialize the web application"""
    app = web.Application(middlewares=[cors_handler])
    
    # Add routes
    app.router.add_options('/{path:.*}', handle_options)
    app.router.add_get('/health', handle_health)
    
    # Support both URL patterns for compatibility
    app.router.add_post('/LiveLinkService/GetCamera', handle_get_camera)
    app.router.add_post('/LiveLinkService/SetCamera', handle_set_camera)
    app.router.add_post('/LiveLinkService/GetMeshes', handle_get_meshes)
    app.router.add_post('/LiveLinkService/GetMesh', handle_get_mesh)
    
    # Also support the livelinkapi prefix that the JavaScript client uses
    app.router.add_post('/livelinkapi.LiveLinkService/GetCamera', handle_get_camera)
    app.router.add_post('/livelinkapi.LiveLinkService/SetCamera', handle_set_camera)
    app.router.add_post('/livelinkapi.LiveLinkService/GetMeshes', handle_get_meshes)
    app.router.add_post('/livelinkapi.LiveLinkService/GetMesh', handle_get_mesh)
    
    return app

async def main():
    """Main function"""
    print("🚀 Starting LiveLink HTTP-to-gRPC Proxy")
    
    # Connect to Octane
    connected = await proxy.connect_to_octane()
    if not connected:
        print("⚠️  Could not connect to Octane, but starting proxy anyway (will retry)")
    
    # Start web server
    app = await init_app()
    runner = web.AppRunner(app)
    await runner.setup()
    
    site = web.TCPSite(runner, '127.0.0.1', 51023)
    await site.start()
    
    print("✅ Proxy server started on http://127.0.0.1:51023")
    print("   Browser requests will be forwarded to Octane at 127.0.0.1:51022")
    print("   Press Ctrl+C to stop")
    
    try:
        await asyncio.Future()  # Run forever
    except KeyboardInterrupt:
        print("\n🛑 Shutting down proxy...")
        await proxy.disconnect()
        await runner.cleanup()

if __name__ == '__main__':
    asyncio.run(main())