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
import importlib
import re
import traceback

# Add the current directory to path for protobuf imports
sys.path.append(os.path.dirname(__file__))

try:
    import livelink_pb2
    import livelink_pb2_grpc
    import apiprojectmanager_pb2
    import apiprojectmanager_pb2_grpc
    import apinodesystem_pb2
    import apinodesystem_pb2_grpc
    import common_pb2
    print("✅ Successfully imported gRPC protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import gRPC modules: {e}")
    print("Note: This proxy requires the generated protobuf files")
    sys.exit(1)

class LiveLinkProxy:
    def __init__(self, octane_address='127.0.0.1:51022'):
        # Auto-detect Docker environment and use host.docker.internal
        import socket
        try:
            # Test if we can reach 127.0.0.1:51022 directly
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.settimeout(2)
            result = sock.connect_ex(('127.0.0.1', 51022))
            sock.close()
            
            if result != 0:
                # Try host.docker.internal instead
                sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                sock.settimeout(2)
                result = sock.connect_ex(('host.docker.internal', 51022))
                sock.close()
                
                if result == 0:
                    octane_address = 'host.docker.internal:51022'
                    print("🐳 Docker environment detected - using host.docker.internal:51022")
        except:
            pass
            
        self.octane_address = octane_address
        self.channel = None
        self.stub = None
        self.project_stub = None
        self.node_graph_stub = None
        self.item_array_stub = None
        self.item_stub = None
        
    async def connect_to_octane(self):
        """Connect to Octane gRPC server"""
        try:
            print(f"🔌 Attempting to connect to Octane gRPC server at {self.octane_address}")
            
            # Test basic connectivity first
            import socket
            host, port = self.octane_address.split(':')
            port = int(port)
            
            print(f"🔍 Testing socket connectivity to {host}:{port}")
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.settimeout(5)
            try:
                result = sock.connect_ex((host, port))
                if result == 0:
                    print(f"✅ Socket connection successful to {host}:{port}")
                else:
                    print(f"❌ Socket connection failed to {host}:{port} - error code: {result}")
                    return False
            except Exception as e:
                print(f"❌ Socket test failed: {e}")
                return False
            finally:
                sock.close()
            
            print(f"🔌 Creating gRPC channel to {self.octane_address}")
            self.channel = grpc.aio.insecure_channel(self.octane_address)
            
            print(f"🔌 Creating gRPC stubs...")
            self.stub = livelink_pb2_grpc.LiveLinkServiceStub(self.channel)
            self.project_stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(self.channel)
            self.node_graph_stub = apinodesystem_pb2_grpc.ApiNodeGraphServiceStub(self.channel)
            self.item_array_stub = apinodesystem_pb2_grpc.ApiItemArrayServiceStub(self.channel)
            self.item_stub = apinodesystem_pb2_grpc.ApiItemServiceStub(self.channel)
            
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
            print(f"\n📤 === LOAD PROJECT ===")
            print(f"📤 Project path: {project_path}")
            
            request = apiprojectmanager_pb2.ApiProjectManager.loadProjectRequest()
            request.projectPath = project_path
            request.evaluate = True  # Enable evaluation for full project load
            
            # Set empty callback (we don't need asset missing callback for now)
            request.assetMissingcallback.callbackSource = ""
            request.assetMissingcallback.callbackId = 0
            request.assetMissinguserData = 0
            
            print(f"📤 Request object: {request}")
            print(f"📤 Calling ApiProjectManagerService.loadProject...")
            response = await self.project_stub.loadProject(request)
            
            print(f"📥 === LOAD PROJECT RESPONSE ===")
            print(f"📥 Response type: {type(response).__name__}")
            print(f"📥 Response: {response}")
            print(f"📥 Result: {response.result}")
            
            result = {
                'success': response.result,
                'callbackId': response.callbackId if hasattr(response, 'callbackId') else 0
            }
            
            if response.result:
                print(f"✅ LoadProject successful: {project_path}")
            else:
                print(f"❌ LoadProject failed: {project_path}")
                
            print(f"✅ Final result: {json.dumps(result, indent=2)}")
            return result
            
        except Exception as e:
            print(f"❌ === LOAD PROJECT ERROR ===")
            print(f"❌ LoadProject failed: {e}")
            print(f"❌ Error type: {type(e).__name__}")
            print(f"❌ Traceback: {traceback.format_exc()}")
            raise Exception(f"Failed to load project: {e}")
    
    async def get_root_node_graph(self):
        """Get root node graph from Octane project"""
        try:
            print(f"\n📤 === GET ROOT NODE GRAPH ===")
            
            request = apiprojectmanager_pb2.ApiProjectManager.rootNodeGraphRequest()
            
            print(f"📤 Request object: {request}")
            print(f"📤 Calling ApiProjectManagerService.rootNodeGraph...")
            response = await self.project_stub.rootNodeGraph(request)
            
            print(f"📥 === ROOT NODE GRAPH RESPONSE ===")
            print(f"📥 Response type: {type(response).__name__}")
            print(f"📥 Response: {response}")
            print(f"📥 Result handle: {response.result.handle}")
            print(f"📥 Result type: {response.result.type}")
            print(f"📥 Result objectId: {getattr(response.result, 'objectId', 'N/A')}")
            
            result = {
                'success': True,
                'objectRef': {
                    'objectId': getattr(response.result, 'objectId', ''),
                    'objectHandle': response.result.handle,
                    'type': response.result.type
                }
            }
            
            print(f"✅ RootNodeGraph successful: handle={response.result.handle}, type={response.result.type}")
            print(f"✅ Final result: {json.dumps(result, indent=2)}")
            return result
            
        except Exception as e:
            print(f"❌ === ROOT NODE GRAPH ERROR ===")
            print(f"❌ RootNodeGraph failed: {e}")
            print(f"❌ Error type: {type(e).__name__}")
            print(f"❌ Traceback: {traceback.format_exc()}")
            raise Exception(f"Failed to get root node graph: {e}")
    
    async def get_node_graph_items(self, node_graph_ref):
        """Get owned items from a node graph"""
        try:
            request = apinodesystem_pb2.ApiNodeGraph.getOwnedItemsRequest()
            request.objectPtr.CopyFrom(node_graph_ref)
            
            print(f"📤 Sending GetOwnedItems request to Octane: objectId={node_graph_ref.objectId}")
            response = await self.node_graph_stub.getOwnedItems(request)
            
            result = {
                'success': True,
                'itemArrayRef': {
                    'objectId': response.list.objectId,
                    'objectHandle': response.list.objectHandle
                }
            }
            
            print(f"📥 GetOwnedItems successful: itemArrayId={response.list.objectId}")
            return result
            
        except Exception as e:
            print(f"❌ GetOwnedItems failed: {e}")
            raise Exception(f"Failed to get node graph items: {e}")
    
    async def get_item_array_size(self, item_array_ref):
        """Get size of an item array"""
        try:
            request = apinodesystem_pb2.ApiItemArray.sizeRequest()
            request.objectPtr.CopyFrom(item_array_ref)
            
            print(f"📤 Sending ItemArray.size request to Octane: objectId={item_array_ref.objectId}")
            response = await self.item_array_stub.size(request)
            
            result = {
                'success': True,
                'size': response.result
            }
            
            print(f"📥 ItemArray.size successful: size={response.result}")
            return result
            
        except Exception as e:
            print(f"❌ ItemArray.size failed: {e}")
            raise Exception(f"Failed to get item array size: {e}")
    
    async def get_item_array_item(self, item_array_ref, index):
        """Get item at specific index from item array"""
        try:
            request = apinodesystem_pb2.ApiItemArray.getRequest()
            request.objectPtr.CopyFrom(item_array_ref)
            request.index = index
            
            print(f"📤 Sending ItemArray.get request to Octane: objectId={item_array_ref.objectId}, index={index}")
            response = await self.item_array_stub.get1(request)
            
            result = {
                'success': True,
                'itemRef': {
                    'objectId': response.result.objectId,
                    'objectHandle': response.result.objectHandle,
                    'type': response.result.type
                }
            }
            
            print(f"📥 ItemArray.get successful: itemId={response.result.objectId}, type={response.result.type}")
            return result
            
        except Exception as e:
            print(f"❌ ItemArray.get failed: {e}")
            raise Exception(f"Failed to get item array item: {e}")
    
    async def get_item_name(self, item_ref):
        """Get name of an item"""
        try:
            request = apinodesystem_pb2.ApiItem.nameRequest()
            request.objectPtr.CopyFrom(item_ref)
            
            print(f"📤 Sending Item.name request to Octane: objectId={item_ref.objectId}")
            response = await self.item_stub.name(request)
            
            result = {
                'success': True,
                'name': response.result
            }
            
            print(f"📥 Item.name successful: name='{response.result}'")
            return result
            
        except Exception as e:
            print(f"❌ Item.name failed: {e}")
            raise Exception(f"Failed to get item name: {e}")
    
    async def build_scene_tree(self):
        """Build complete scene tree hierarchy"""
        try:
            print(f"🌳 Building scene tree hierarchy...")
            
            # Get root node graph
            root_result = await self.get_root_node_graph()
            if not root_result['success']:
                return {'success': False, 'error': 'Failed to get root node graph'}
            
            root_ref = common_pb2.ObjectRef()
            root_ref.handle = root_result['objectRef']['objectHandle']
            root_ref.type = root_result['objectRef']['type']
            
            # Build tree recursively
            tree_data = await self._build_node_tree_recursive(root_ref, "Root", 0)
            
            result = {
                'success': True,
                'hierarchy': tree_data
            }
            
            print(f"🌳 Scene tree built successfully with {len(tree_data)} root items")
            return result
            
        except Exception as e:
            print(f"❌ Build scene tree failed: {e}")
            return {'success': False, 'error': str(e)}
    
    async def _build_node_tree_recursive(self, node_ref, name, depth):
        """Recursively build node tree"""
        try:
            if depth > 10:  # Prevent infinite recursion
                print(f"⚠️  Maximum depth reached for node: {name}")
                return []
            
            # Get items from this node graph
            items_result = await self.get_node_graph_items(node_ref)
            if not items_result['success']:
                return []
            
            item_array_ref = common_pb2.ObjectRef()
            item_array_ref.objectId = items_result['itemArrayRef']['objectId']
            item_array_ref.objectHandle = items_result['itemArrayRef']['objectHandle']
            
            # Get array size
            size_result = await self.get_item_array_size(item_array_ref)
            if not size_result['success']:
                return []
            
            items = []
            for i in range(size_result['size']):
                try:
                    # Get item at index
                    item_result = await self.get_item_array_item(item_array_ref, i)
                    if not item_result['success']:
                        continue
                    
                    item_ref = common_pb2.ObjectRef()
                    item_ref.objectId = item_result['itemRef']['objectId']
                    item_ref.objectHandle = item_result['itemRef']['objectHandle']
                    item_ref.type = item_result['itemRef']['type']
                    
                    # Get item name
                    name_result = await self.get_item_name(item_ref)
                    item_name = name_result['name'] if name_result['success'] else f"Item_{i}"
                    
                    # Determine item type
                    item_type = self._get_item_type_string(item_ref.type)
                    
                    # Create item data
                    item_data = {
                        'id': item_ref.objectId,
                        'name': item_name,
                        'type': item_type,
                        'visible': True,  # Default to visible
                        'children': []
                    }
                    
                    # If this is a node graph, recursively get its children
                    if item_ref.type == common_pb2.ObjectRef.ApiNodeGraph:
                        item_data['children'] = await self._build_node_tree_recursive(item_ref, item_name, depth + 1)
                    
                    items.append(item_data)
                    
                except Exception as e:
                    print(f"⚠️  Failed to process item {i}: {e}")
                    continue
            
            return items
            
        except Exception as e:
            print(f"❌ Recursive tree build failed for {name}: {e}")
            return []
    
    def _get_item_type_string(self, object_type):
        """Convert ObjectRef.ObjectType enum to string"""
        type_map = {
            common_pb2.ObjectRef.ApiNode: 'node',
            common_pb2.ObjectRef.ApiNodeGraph: 'group',
            common_pb2.ObjectRef.ApiRootNodeGraph: 'root',
            # Add more mappings as needed
        }
        return type_map.get(object_type, 'unknown')
    
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
    """Handle CORS for browser requests including file:// protocol"""
    response = await handler(request)
    
    # Handle file:// protocol and localhost origins
    origin = request.headers.get('Origin', 'null')
    if origin == 'null' or origin.startswith('file://') or 'localhost' in origin:
        response.headers['Access-Control-Allow-Origin'] = '*'
    else:
        response.headers['Access-Control-Allow-Origin'] = '*'
    
    response.headers['Access-Control-Allow-Methods'] = 'GET, POST, OPTIONS, PUT, DELETE'
    response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Accept, X-Grpc-Web, X-Call-Id, Authorization, X-Requested-With'
    response.headers['Access-Control-Allow-Credentials'] = 'false'
    response.headers['Access-Control-Max-Age'] = '86400'
    
    return response

async def handle_options(request):
    """Handle CORS preflight requests including file:// protocol"""
    origin = request.headers.get('Origin', 'null')
    
    return web.Response(
        headers={
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'GET, POST, OPTIONS, PUT, DELETE',
            'Access-Control-Allow-Headers': 'Content-Type, Accept, X-Grpc-Web, X-Call-Id, Authorization, X-Requested-With',
            'Access-Control-Allow-Credentials': 'false',
            'Access-Control-Max-Age': '86400'
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

async def handle_root_node_graph(request):
    """Handle RootNodeGraph requests"""
    try:
        print(f"🌐 HTTP Request: RootNodeGraph from {request.remote}")
        result = await proxy.get_root_node_graph()
        print(f"🌐 HTTP Response: RootNodeGraph success")
        return web.json_response({'success': True, 'data': result})
    except Exception as e:
        print(f"🌐 HTTP Response: RootNodeGraph failed - {e}")
        return web.json_response({'success': False, 'error': str(e)}, status=500)

async def handle_build_scene_tree(request):
    """Handle BuildSceneTree requests"""
    try:
        print(f"🌐 HTTP Request: BuildSceneTree from {request.remote}")
        result = await proxy.build_scene_tree()
        print(f"🌐 HTTP Response: BuildSceneTree {'success' if result['success'] else 'failed'}")
        return web.json_response({'success': True, 'data': result})
    except Exception as e:
        print(f"🌐 HTTP Response: BuildSceneTree failed - {e}")
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

# ==================== GENERIC GRPC PASS-THROUGH HANDLER ====================

class GrpcServiceRegistry:
    """Registry for dynamically loading gRPC service stubs"""
    
    def __init__(self):
        self.stubs = {}
        self.service_modules = {}
        
    def get_stub(self, service_name, channel):
        """Get or create a gRPC stub for the given service"""
        if service_name in self.stubs:
            return self.stubs[service_name]
            
        try:
            # Map service names to their module names
            service_module_map = {
                'LiveLinkService': 'livelink_pb2_grpc',
                'ApiProjectManagerService': 'apiprojectmanager_pb2_grpc',
                'ApiNodeGraphService': 'apinodesystem_pb2_grpc',
                'ApiNodeService': 'apinodesystem_pb2_grpc',
                'ApiItemService': 'apinodesystem_pb2_grpc',
                'ApiItemArrayService': 'apinodesystem_pb2_grpc',
                'ApiArrayService': 'apiarray_pb2_grpc',
                'ApiAnimationTimeTransformService': 'apianimationtimetransform_pb2_grpc',
                'ApiOutputColorSpaceInfoService': 'apioutputcolorspaceinfo_pb2_grpc',
                'ApiTimeSamplingService': 'apitimesampling_pb2_grpc',
                'CameraControlService': 'camera_control_pb2_grpc',
                'OctaneNetService': 'octanenet_pb2_grpc',
            }
            
            module_name = service_module_map.get(service_name)
            if not module_name:
                raise Exception(f"Unknown service: {service_name}")
                
            # Import the gRPC module
            grpc_module = importlib.import_module(module_name)
            
            # Get the stub class (convention: ServiceNameStub)
            stub_class_name = f"{service_name}Stub"
            stub_class = getattr(grpc_module, stub_class_name)
            
            # Create and cache the stub
            stub = stub_class(channel)
            self.stubs[service_name] = stub
            
            print(f"✅ Created gRPC stub for {service_name}")
            return stub
            
        except Exception as e:
            print(f"❌ Failed to create stub for {service_name}: {e}")
            raise

    def get_request_class(self, service_name, method_name):
        """Get the request class for a specific service method"""
        try:
            # Map service names to their protobuf modules
            service_pb2_map = {
                'LiveLinkService': 'livelink_pb2',
                'ApiProjectManagerService': 'apiprojectmanager_pb2',
                'ApiNodeGraphService': 'apinodesystem_pb2',
                'ApiNodeService': 'apinodesystem_pb2',
                'ApiItemService': 'apinodesystem_pb2',
                'ApiItemArrayService': 'apinodesystem_pb2',
                'ApiArrayService': 'apiarray_pb2',
                'ApiAnimationTimeTransformService': 'apianimationtimetransform_pb2',
                'ApiOutputColorSpaceInfoService': 'apioutputcolorspaceinfo_pb2',
                'ApiTimeSamplingService': 'apitimesampling_pb2',
                'CameraControlService': 'camera_control_pb2',
                'OctaneNetService': 'octanenet_pb2',
            }
            
            pb2_module_name = service_pb2_map.get(service_name)
            if not pb2_module_name:
                raise Exception(f"Unknown service: {service_name}")
                
            # Import the protobuf module
            pb2_module = importlib.import_module(pb2_module_name)
            
            # For nested message classes, we need to navigate the structure
            if service_name == 'LiveLinkService':
                # Direct method access for LiveLinkService
                request_class = getattr(pb2_module, f"{method_name}Request", None)
                if request_class:
                    return request_class
            else:
                # For API services, methods are nested in the service class
                service_class = getattr(pb2_module, service_name.replace('Service', ''))
                request_class = getattr(service_class, f"{method_name}Request", None)
                if request_class:
                    return request_class
                    
            raise Exception(f"Request class not found for {service_name}.{method_name}")
            
        except Exception as e:
            print(f"❌ Failed to get request class for {service_name}.{method_name}: {e}")
            raise

# Global service registry
grpc_registry = GrpcServiceRegistry()

async def handle_generic_grpc(request):
    """Generic handler for any gRPC service call"""
    try:
        # Parse the URL path to extract service and method
        path = request.path
        print(f"\n🌐 === GENERIC gRPC REQUEST ===")
        print(f"🌐 Path: {path}")
        print(f"🌐 Remote: {request.remote}")
        print(f"🌐 Method: {request.method}")
        print(f"🌐 Content-Length: {request.content_length}")
        
        # Extract service and method from path
        # Patterns: /octaneapi.ServiceName/methodName or /livelinkapi.ServiceName/methodName
        path_match = re.match(r'^/(?:octaneapi\.|livelinkapi\.)?([^/]+)/([^/]+)$', path)
        if not path_match:
            print(f"❌ Invalid path format: {path}")
            return web.json_response({'success': False, 'error': 'Invalid path format'}, status=400)
            
        service_name = path_match.group(1)
        method_name = path_match.group(2)
        
        print(f"📤 Service: {service_name}")
        print(f"📤 Method: {method_name}")
        
        # Get the appropriate stub
        print(f"🔌 Getting stub for {service_name}...")
        stub = grpc_registry.get_stub(service_name, proxy.channel)
        print(f"✅ Got stub: {type(stub).__name__}")
        
        # Get the method from the stub
        method = getattr(stub, method_name, None)
        if not method:
            print(f"❌ Method {method_name} not found on {service_name}")
            return web.json_response({'success': False, 'error': f'Method {method_name} not found on {service_name}'}, status=404)
        print(f"✅ Got method: {method}")
        
        # Get request data from HTTP body
        request_data = {}
        if request.content_length and request.content_length > 0:
            try:
                request_data = await request.json()
                print(f"📥 Request data: {json.dumps(request_data, indent=2)}")
            except Exception as json_error:
                print(f"⚠️ JSON parse error: {json_error}")
                pass  # Empty or invalid JSON is OK for some requests
        else:
            print(f"📥 No request data (empty body)")
        
        # Get the request class and create the request
        print(f"🔍 Getting request class for {service_name}.{method_name}...")
        request_class = grpc_registry.get_request_class(service_name, method_name)
        print(f"✅ Got request class: {request_class}")
        grpc_request = request_class()
        print(f"🏗️ Created gRPC request object: {type(grpc_request).__name__}")
        
        # Populate request fields from JSON data
        if request_data:
            print(f"🔧 Populating request object...")
            for key, value in request_data.items():
                print(f"  🔧 Processing field: {key} = {value}")
                if hasattr(grpc_request, key):
                    field_descriptor = None
                    for field in grpc_request.DESCRIPTOR.fields:
                        if field.name == key:
                            field_descriptor = field
                            break
                    
                    if field_descriptor and field_descriptor.type == field_descriptor.TYPE_MESSAGE:
                        print(f"    📦 Nested message field: {key}")
                        # Handle nested message fields
                        nested_message = getattr(grpc_request, key)
                        if isinstance(value, dict):
                            for nested_key, nested_value in value.items():
                                print(f"      🔧 Setting nested: {nested_key} = {nested_value}")
                                if hasattr(nested_message, nested_key):
                                    setattr(nested_message, nested_key, nested_value)
                                else:
                                    print(f"      ⚠️ Nested field {nested_key} not found")
                    else:
                        print(f"    📝 Simple field: {key}")
                        # Handle simple fields
                        setattr(grpc_request, key, value)
                else:
                    print(f"    ⚠️ Field {key} not found on request object")
        
        # Make the gRPC call
        print(f"📤 === CALLING OCTANE ===")
        print(f"📤 Service: {service_name}")
        print(f"📤 Method: {method_name}")
        print(f"📤 Request: {grpc_request}")
        
        response = await method(grpc_request)
        
        print(f"📥 === OCTANE RESPONSE ===")
        print(f"📥 Response type: {type(response).__name__}")
        print(f"📥 Response: {response}")
        
        # Convert protobuf response to JSON
        print(f"🔄 Converting response to JSON...")
        
        def protobuf_to_dict(obj):
            """Convert protobuf object to JSON-serializable dict"""
            if obj is None:
                return None
            
            # Handle RepeatedCompositeContainer and RepeatedScalarContainer
            if str(type(obj).__name__) in ['RepeatedCompositeContainer', 'RepeatedScalarContainer']:
                return [protobuf_to_dict(item) for item in obj]
            
            # Handle other iterables (but not strings or bytes)
            if hasattr(obj, '__iter__') and hasattr(obj, '__len__') and not isinstance(obj, (str, bytes)):
                try:
                    # Check if it's a protobuf repeated field
                    if hasattr(obj, '_values') or 'Repeated' in str(type(obj).__name__):
                        return [protobuf_to_dict(item) for item in obj]
                except:
                    pass
            
            # Handle protobuf message objects
            if hasattr(obj, 'DESCRIPTOR'):
                result = {}
                for field in obj.DESCRIPTOR.fields:
                    field_name = field.name
                    field_value = getattr(obj, field_name)
                    result[field_name] = protobuf_to_dict(field_value)
                return result
            
            # Handle primitive types and anything else
            try:
                # Test if it's JSON serializable
                import json
                json.dumps(obj)
                return obj
            except (TypeError, ValueError):
                # If not serializable, convert to string
                return str(obj)
        
        response_dict = protobuf_to_dict(response)
        print(f"✅ Response converted to dict: {type(response_dict)}")
        
        result = {
            'success': True,
            'data': response_dict
        }
        
        print(f"✅ === SUCCESS ===")
        print(f"✅ {service_name}.{method_name} completed successfully")
        print(f"✅ Response type: {type(response_dict)}")
        
        return web.json_response(result)
        
    except Exception as e:
        print(f"❌ === ERROR ===")
        print(f"❌ Generic gRPC call failed: {e}")
        print(f"❌ Error type: {type(e).__name__}")
        print(f"❌ Traceback: {traceback.format_exc()}")
        return web.json_response({'success': False, 'error': str(e)}, status=500)

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
    app.router.add_post('/ApiProjectManagerService/rootNodeGraph', handle_root_node_graph)
    app.router.add_post('/ApiProjectManagerService/buildSceneTree', handle_build_scene_tree)
    
    # Also support the livelinkapi prefix that the JavaScript client uses
    app.router.add_post('/livelinkapi.LiveLinkService/GetCamera', handle_get_camera)
    app.router.add_post('/livelinkapi.LiveLinkService/SetCamera', handle_set_camera)
    app.router.add_post('/livelinkapi.LiveLinkService/GetMeshes', handle_get_meshes)
    app.router.add_post('/livelinkapi.LiveLinkService/GetMesh', handle_get_mesh)
    
    # ApiProjectManager with octaneapi prefix
    app.router.add_post('/octaneapi.ApiProjectManagerService/loadProject', handle_load_project)
    app.router.add_post('/octaneapi.ApiProjectManagerService/rootNodeGraph', handle_root_node_graph)
    app.router.add_post('/octaneapi.ApiProjectManagerService/buildSceneTree', handle_build_scene_tree)
    
    # ==================== GENERIC GRPC PASS-THROUGH ROUTES ====================
    # These catch-all routes handle any gRPC service call not explicitly defined above
    # Pattern: /[prefix.]ServiceName/methodName
    app.router.add_post('/{service:[^/]+}/{method:[^/]+}', handle_generic_grpc)
    
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
    
    site = web.TCPSite(runner, '0.0.0.0', 51023)
    await site.start()
    
    print("✅ Proxy server started on http://0.0.0.0:51023 (accessible via localhost:51023)")
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