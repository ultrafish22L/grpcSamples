#!/usr/bin/env python3
"""
Mock LiveLink Server for Testing
Provides HTTP endpoints that simulate Octane LiveLink responses
"""

import json
import asyncio
import aiohttp
from aiohttp import web
from aiohttp.web import middleware
import time
import math

class MockLiveLinkServer:
    def __init__(self):
        self.camera_state = {
            'position': {'x': 5.0, 'y': 3.0, 'z': 8.0},
            'target': {'x': 0.0, 'y': 0.0, 'z': 0.0},
            'up': {'x': 0.0, 'y': 1.0, 'z': 0.0},
            'fov': 45.0
        }
        self.meshes = [
            {'id': 'cube_001', 'name': 'Cube', 'objectHandle': 'cube_001'},
            {'id': 'sphere_002', 'name': 'Sphere', 'objectHandle': 'sphere_002'},
            {'id': 'teapot_003', 'name': 'Teapot', 'objectHandle': 'teapot_003'}
        ]
        self.start_time = time.time()
        
    def get_animated_camera(self):
        """Return camera with slight animation for testing"""
        t = time.time() - self.start_time
        radius = 8.0
        height = 3.0 + math.sin(t * 0.5) * 1.0
        angle = t * 0.2
        
        return {
            'position': {
                'x': radius * math.cos(angle),
                'y': height,
                'z': radius * math.sin(angle)
            },
            'target': {'x': 0.0, 'y': 0.0, 'z': 0.0},
            'up': {'x': 0.0, 'y': 1.0, 'z': 0.0},
            'fov': 45.0
        }

# CORS middleware
@middleware
async def cors_handler(request, handler):
    """Handle CORS for all requests"""
    if request.method == 'OPTIONS':
        # Handle preflight requests
        response = web.Response()
    else:
        response = await handler(request)
    
    # Add CORS headers
    response.headers['Access-Control-Allow-Origin'] = '*'
    response.headers['Access-Control-Allow-Methods'] = 'GET, POST, PUT, DELETE, OPTIONS'
    response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization, X-Call-Id, grpc-web'
    response.headers['Access-Control-Expose-Headers'] = 'grpc-status, grpc-message'
    response.headers['Access-Control-Max-Age'] = '86400'
    
    return response

# Global mock server instance
mock_server = MockLiveLinkServer()

async def handle_options(request):
    """Handle OPTIONS requests for CORS"""
    return web.Response()

async def handle_health(request):
    """Health check endpoint"""
    print("📋 Health check requested")
    return web.json_response({
        'status': 'healthy',
        'server': 'Mock LiveLink Server',
        'uptime': time.time() - mock_server.start_time
    })

async def handle_get_camera(request):
    """Handle GetCamera requests"""
    print("📤 GetCamera request received")
    print(f"   Content-Type: {request.headers.get('Content-Type', 'not set')}")
    print(f"   Accept: {request.headers.get('Accept', 'not set')}")
    
    # Use animated camera for more interesting testing
    camera_data = mock_server.get_animated_camera()
    
    print(f"📥 Returning camera: pos=({camera_data['position']['x']:.2f}, {camera_data['position']['y']:.2f}, {camera_data['position']['z']:.2f})")
    
    # Check if this is a gRPC-Web request
    content_type = request.headers.get('Content-Type', '')
    if 'grpc-web' in content_type:
        # Return gRPC-Web compatible response
        response = web.Response(
            body=b'\x00\x00\x00\x00\x05hello',  # Simple gRPC-Web response
            headers={
                'Content-Type': 'application/grpc-web+proto',
                'grpc-status': '0',
                'grpc-message': 'OK'
            }
        )
        print("📤 Returning gRPC-Web response")
        return response
    else:
        # Return JSON response
        return web.json_response({
            'success': True,
            'data': camera_data
        })

async def handle_set_camera(request):
    """Handle SetCamera requests"""
    print("📤 SetCamera request received")
    
    try:
        data = await request.json()
        print(f"📥 Setting camera: {data}")
        
        # Update mock camera state
        if 'position' in data:
            mock_server.camera_state['position'] = data['position']
        if 'target' in data:
            mock_server.camera_state['target'] = data['target']
        if 'up' in data:
            mock_server.camera_state['up'] = data['up']
        if 'fov' in data:
            mock_server.camera_state['fov'] = data['fov']
            
        print(f"✅ Camera updated successfully")
        
        return web.json_response({
            'success': True,
            'message': 'Camera updated successfully'
        })
        
    except Exception as e:
        print(f"❌ SetCamera failed: {e}")
        return web.json_response({
            'success': False,
            'error': str(e)
        }, status=400)

async def handle_get_meshes(request):
    """Handle GetMeshes requests"""
    print("📤 GetMeshes request received")
    
    meshes = mock_server.meshes
    print(f"📥 Returning {len(meshes)} meshes")
    for mesh in meshes:
        print(f"   - {mesh['name']} (ID: {mesh['id']})")
    
    return web.json_response({
        'success': True,
        'data': {'meshes': meshes}
    })

async def handle_get_mesh(request):
    """Handle GetMesh requests"""
    print("📤 GetMesh request received")
    
    try:
        data = await request.json()
        mesh_id = data.get('objecthandle', '')
        print(f"📥 Requesting mesh: {mesh_id}")
        
        # Generate mock mesh data
        if mesh_id == 'cube_001':
            # Simple cube vertices
            positions = [
                {'x': -1, 'y': -1, 'z': -1}, {'x': 1, 'y': -1, 'z': -1},
                {'x': 1, 'y': 1, 'z': -1}, {'x': -1, 'y': 1, 'z': -1},
                {'x': -1, 'y': -1, 'z': 1}, {'x': 1, 'y': -1, 'z': 1},
                {'x': 1, 'y': 1, 'z': 1}, {'x': -1, 'y': 1, 'z': 1}
            ]
            indices = [0,1,2, 0,2,3, 4,7,6, 4,6,5, 0,4,5, 0,5,1, 2,6,7, 2,7,3, 0,3,7, 0,7,4, 1,5,6, 1,6,2]
        else:
            # Default simple triangle
            positions = [
                {'x': 0, 'y': 1, 'z': 0}, {'x': -1, 'y': -1, 'z': 0}, {'x': 1, 'y': -1, 'z': 0}
            ]
            indices = [0, 1, 2]
        
        mesh_data = {
            'id': mesh_id,
            'positions': positions,
            'indices': indices,
            'vertex_count': len(positions),
            'triangle_count': len(indices) // 3
        }
        
        print(f"✅ Returning mesh data: {len(positions)} vertices, {len(indices)//3} triangles")
        
        return web.json_response({
            'success': True,
            'data': mesh_data
        })
        
    except Exception as e:
        print(f"❌ GetMesh failed: {e}")
        return web.json_response({
            'success': False,
            'error': str(e)
        }, status=400)

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
    print("🎭 Starting Mock LiveLink Server")
    print("   This server simulates Octane LiveLink responses for testing")

    # Start web server
    app = await init_app()
    runner = web.AppRunner(app)
    await runner.setup()

    site = web.TCPSite(runner, '127.0.0.1', 51023)
    await site.start()

    print("✅ Mock server started on http://127.0.0.1:51023")
    print("   Available endpoints:")
    print("     GET  /health - Health check")
    print("     POST /LiveLinkService/GetCamera - Get camera state")
    print("     POST /LiveLinkService/SetCamera - Set camera state")
    print("     POST /LiveLinkService/GetMeshes - Get mesh list")
    print("     POST /LiveLinkService/GetMesh - Get mesh data")
    print("   Press Ctrl+C to stop")

    try:
        await asyncio.Future()  # Run forever
    except KeyboardInterrupt:
        print("\n🛑 Shutting down mock server...")
        await runner.cleanup()

if __name__ == '__main__':
    asyncio.run(main())