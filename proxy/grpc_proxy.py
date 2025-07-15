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

# Add the current directory to path for protobuf imports
sys.path.append(os.path.dirname(__file__))

try:
    import livelink_pb2
    import livelink_pb2_grpc
    import apiprojectmanager_pb2
    import apiprojectmanager_pb2_grpc
    import common_pb2
    print("✅ Successfully imported gRPC protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import gRPC modules: {e}")
    print("Note: This proxy requires the generated protobuf files")
    sys.exit(1)

class LiveLinkProxy:
    def __init__(self, octane_address='127.0.0.1:51022'):
        self.octane_address = octane_address
        self.channel = None
        self.stub = None
        self.project_stub = None
        
    async def connect_to_octane(self):
        """Connect to Octane gRPC server"""
        try:
            print(f"🔌 Connecting to Octane gRPC server at {self.octane_address}")
            self.channel = grpc.aio.insecure_channel(self.octane_address)
            self.stub = livelink_pb2_grpc.LiveLinkServiceStub(self.channel)
            self.project_stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(self.channel)
            
            # Test connection
            print(f"📤 Testing connection with GetCamera request")
            request = livelink_pb2.Empty()
            response = await self.stub.GetCamera(request)
            print(f"✅ Successfully connected to Octane LiveLink server at {self.octane_address}")
            print(f"📥 Initial camera state: pos=({response.position.x:.2f}, {response.position.y:.2f}, {response.position.z:.2f})")
            return True
            
        except Exception as e:
            print(f"❌ Failed to connect to Octane at {self.octane_address}: {e}")
            return False
    
    async def disconnect(self):
        """Disconnect from Octane"""
        if self.channel:
            await self.channel.close()
            
    async def get_camera(self):
        """Get camera state from Octane"""
        try:
            request = livelink_pb2.Empty()
            print(f"📤 Sending GetCamera request to Octane")
            response = await self.stub.GetCamera(request)
            
            camera_data = {
                'position': {'x': response.position.x, 'y': response.position.y, 'z': response.position.z},
                'target': {'x': response.target.x, 'y': response.target.y, 'z': response.target.z},
                'up': {'x': response.up.x, 'y': response.up.y, 'z': response.up.z}
            }
            print(f"📥 Received GetCamera response from Octane: pos=({response.position.x:.2f}, {response.position.y:.2f}, {response.position.z:.2f})")
            return camera_data
        except Exception as e:
            print(f"❌ GetCamera failed: {e}")
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
            
            print(f"📤 Sending SetCamera request to Octane: pos=({request.position.x:.2f}, {request.position.y:.2f}, {request.position.z:.2f})")
            response = await self.stub.SetCamera(request)
            print(f"📥 Received SetCamera response from Octane: success")
            return True
        except Exception as e:
            print(f"❌ SetCamera failed: {e}")
            raise Exception(f"Failed to set camera: {e}")
    
    async def get_meshes(self):
        """Get mesh list from Octane"""
        try:
            request = livelink_pb2.Empty()
            print(f"📤 Sending GetMeshes request to Octane")
            response = await self.stub.GetMeshes(request)
            
            meshes = []
            for mesh in response.meshes:
                meshes.append({
                    'id': mesh.id,
                    'name': mesh.name,
                    'objectHandle': mesh.objectHandle
                })
            
            print(f"📥 Received GetMeshes response from Octane: {len(meshes)} meshes found")
            for mesh in meshes:
                print(f"   - {mesh['name']} (ID: {mesh['id']}, Handle: {mesh['objectHandle']})")
            return meshes
        except Exception as e:
            print(f"❌ GetMeshes failed: {e}")
            raise Exception(f"Failed to get meshes: {e}")
    
    async def load_project(self, project_path):
        """Load project from .orbx file"""
        try:
            request = apiprojectmanager_pb2.ApiProjectManager.loadProjectRequest()
            request.projectPath = project_path
            request.evaluate = True  # Enable evaluation for full project load
            
            # Set empty callback (we don't need asset missing callback for now)
            request.assetMissingcallback.callbackSource = ""
            request.assetMissingcallback.callbackId = 0
            request.assetMissinguserData = 0
            
            print(f"📤 Sending LoadProject request to Octane: {project_path}")
            response = await self.project_stub.loadProject(request)
            
            result = {
                'success': response.result,
                'callbackId': response.callbackId if hasattr(response, 'callbackId') else 0
            }
            
            if response.result:
                print(f"📥 LoadProject successful: {project_path}")
            else:
                print(f"📥 LoadProject failed: {project_path}")
                
            return result
            
        except Exception as e:
            print(f"❌ LoadProject failed: {e}")
            raise Exception(f"Failed to load project: {e}")
    
    async def get_mesh(self, mesh_id):
        """Get specific mesh data from Octane"""
        try:
            request = livelink_pb2.MeshRequest()
            request.objecthandle = mesh_id
            
            print(f"📤 Sending GetMesh request to Octane: objecthandle='{mesh_id}'")
            response = await self.stub.GetMesh(request)
            
            # Convert protobuf Vec3 objects to simple dictionaries
            positions = []
            if hasattr(response, 'positions'):
                for pos in response.positions:
                    positions.append({'x': pos.x, 'y': pos.y, 'z': pos.z})
            
            normals = []
            if hasattr(response, 'normals'):
                for norm in response.normals:
                    normals.append({'x': norm.x, 'y': norm.y, 'z': norm.z})
            
            mesh_data = {
                'name': response.name,
                'positions': positions,
                'normals': normals,
                'vertsPerPoly': list(response.vertsPerPoly) if hasattr(response, 'vertsPerPoly') else [],
                'polyVertIndices': list(response.polyVertIndices) if hasattr(response, 'polyVertIndices') else [],
                'polyNormalIndices': list(response.polyNormalIndices) if hasattr(response, 'polyNormalIndices') else [],
                'windingOrder': response.windingOrder if hasattr(response, 'windingOrder') else 0
            }
            
            vertex_count = len(positions)
            face_count = len(mesh_data['vertsPerPoly'])
            print(f"📥 Received GetMesh response from Octane: name='{response.name}', {vertex_count} vertices, {face_count} faces")
            return mesh_data
        except Exception as e:
            print(f"❌ GetMesh failed for '{mesh_id}': {e}")
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
        print(f"🌐 HTTP Request: GetCamera from {request.remote}")
        camera_data = await proxy.get_camera()
        print(f"🌐 HTTP Response: GetCamera success")
        return web.json_response({'success': True, 'data': camera_data})
    except Exception as e:
        print(f"🌐 HTTP Response: GetCamera failed - {e}")
        return web.json_response({'success': False, 'error': str(e)}, status=500)

async def handle_set_camera(request):
    """Handle SetCamera requests"""
    try:
        print(f"🌐 HTTP Request: SetCamera from {request.remote}")
        data = await request.json()
        await proxy.set_camera(data)
        print(f"🌐 HTTP Response: SetCamera success")
        return web.json_response({'success': True})
    except Exception as e:
        print(f"🌐 HTTP Response: SetCamera failed - {e}")
        return web.json_response({'success': False, 'error': str(e)}, status=500)

async def handle_get_meshes(request):
    """Handle GetMeshes requests"""
    try:
        print(f"🌐 HTTP Request: GetMeshes from {request.remote}")
        meshes = await proxy.get_meshes()
        print(f"🌐 HTTP Response: GetMeshes success - {len(meshes)} meshes")
        return web.json_response({'success': True, 'data': meshes})
    except Exception as e:
        print(f"🌐 HTTP Response: GetMeshes failed - {e}")
        return web.json_response({'success': False, 'error': str(e)}, status=500)

async def handle_get_mesh(request):
    """Handle GetMesh requests"""
    try:
        print(f"🌐 HTTP Request: GetMesh from {request.remote}")
        data = await request.json()
        mesh_id = data['objecthandle']
        mesh_data = await proxy.get_mesh(mesh_id)
        print(f"🌐 HTTP Response: GetMesh success for '{mesh_id}'")
        return web.json_response({'success': True, 'data': mesh_data})
    except Exception as e:
        print(f"🌐 HTTP Response: GetMesh failed - {e}")
        return web.json_response({'success': False, 'error': str(e)}, status=500)

async def handle_load_project(request):
    """Handle LoadProject requests"""
    try:
        print(f"🌐 HTTP Request: LoadProject from {request.remote}")
        data = await request.json()
        project_path = data['projectPath']
        result = await proxy.load_project(project_path)
        print(f"🌐 HTTP Response: LoadProject {'success' if result['success'] else 'failed'}")
        return web.json_response({'success': True, 'data': result})
    except Exception as e:
        print(f"🌐 HTTP Response: LoadProject failed - {e}")
        return web.json_response({'success': False, 'error': str(e)}, status=500)

async def handle_static_files(request):
    """Serve static HTML files"""
    path = request.match_info.get('path', 'index.html')
    
    # Security: only allow specific files
    allowed_files = {
        'index.html', 'livelink.js', 'shared.js', 'webgl-utils.js', 'otoy-theme.css'
    }
    
    if path not in allowed_files:
        return web.Response(status=404, text="File not found")
    
    # Get the HTML directory path
    html_dir = os.path.join(os.path.dirname(__file__), '..', 'html')
    file_path = os.path.join(html_dir, path)
    
    if not os.path.exists(file_path):
        return web.Response(status=404, text="File not found")
    
    # Determine content type
    content_type = 'text/html'
    if path.endswith('.js'):
        content_type = 'application/javascript'
    elif path.endswith('.css'):
        content_type = 'text/css'
    
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        return web.Response(text=content, content_type=content_type)
    except Exception as e:
        print(f"❌ Error serving {path}: {e}")
        return web.Response(status=500, text="Internal server error")

async def init_app():
    """Initialize the web application"""
    app = web.Application(middlewares=[cors_handler])
    
    # Add specific routes first (more specific routes should come before general ones)
    app.router.add_get('/health', handle_health)
    
    # Support both URL patterns for compatibility
    app.router.add_post('/LiveLinkService/GetCamera', handle_get_camera)
    app.router.add_post('/LiveLinkService/SetCamera', handle_set_camera)
    app.router.add_post('/LiveLinkService/GetMeshes', handle_get_meshes)
    app.router.add_post('/LiveLinkService/GetMesh', handle_get_mesh)
    
    # ApiProjectManager endpoints
    app.router.add_post('/ApiProjectManagerService/loadProject', handle_load_project)
    
    # Also support the livelinkapi prefix that the JavaScript client uses
    app.router.add_post('/livelinkapi.LiveLinkService/GetCamera', handle_get_camera)
    app.router.add_post('/livelinkapi.LiveLinkService/SetCamera', handle_set_camera)
    app.router.add_post('/livelinkapi.LiveLinkService/GetMeshes', handle_get_meshes)
    app.router.add_post('/livelinkapi.LiveLinkService/GetMesh', handle_get_mesh)
    
    # ApiProjectManager with octaneapi prefix
    app.router.add_post('/octaneapi.ApiProjectManagerService/loadProject', handle_load_project)
    
    # Static file serving
    app.router.add_get('/', handle_static_files)  # Serve index.html by default
    app.router.add_get('/{path}', handle_static_files)  # Serve specific files
    
    # CORS options handler (should be last to catch all)
    app.router.add_options('/{path:.*}', handle_options)
    
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
    
    site = web.TCPSite(runner, '127.0.0.1', 8090)
    await site.start()
    
    print("✅ Proxy server started on http://127.0.0.1:8090")
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