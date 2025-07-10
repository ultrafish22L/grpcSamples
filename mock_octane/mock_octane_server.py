#!/usr/bin/env python3
"""
Mock Octane gRPC Server
Simulates Octane Render's LiveLink gRPC service for development and testing
"""

import asyncio
import grpc
import sys
import os
import json
import time
import math
from concurrent import futures
from typing import Dict, List

# Add the generated protobuf path
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'proxy'))

try:
    import livelink_pb2
    import livelink_pb2_grpc
    print("✅ Successfully imported gRPC protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import gRPC modules: {e}")
    print("Note: This mock server requires the generated protobuf files")
    print("Run the build process first to generate the protobuf files")
    sys.exit(1)

class MockOctaneLiveLinkService(livelink_pb2_grpc.LiveLinkServiceServicer):
    """Mock implementation of Octane's LiveLink gRPC service"""
    
    def __init__(self):
        print("🎭 Initializing Mock Octane LiveLink Service")
        
        # Mock camera state
        self.camera_state = {
            'position': {'x': 5.0, 'y': 3.0, 'z': 8.0},
            'target': {'x': 0.0, 'y': 0.0, 'z': 0.0},
            'up': {'x': 0.0, 'y': 1.0, 'z': 0.0},
            'fov': 45.0
        }
        
        # Mock mesh data
        self.meshes = self._create_mock_meshes()
        
        # Statistics
        self.stats = {
            'get_camera_calls': 0,
            'set_camera_calls': 0,
            'get_meshes_calls': 0,
            'get_mesh_calls': 0,
            'start_time': time.time()
        }
        
        print(f"📊 Mock server initialized with {len(self.meshes)} mock meshes")
        print(f"📷 Initial camera: pos=({self.camera_state['position']['x']:.1f}, {self.camera_state['position']['y']:.1f}, {self.camera_state['position']['z']:.1f})")
    
    def _create_mock_meshes(self) -> Dict[int, Dict]:
        """Create mock mesh data for testing"""
        meshes = {}
        
        # Cube mesh
        meshes[1001] = {
            'id': 1001,
            'name': 'Mock Cube',
            'objectHandle': 1001,
            'positions': [
                # Front face
                -1.0, -1.0,  1.0,  1.0, -1.0,  1.0,  1.0,  1.0,  1.0, -1.0,  1.0,  1.0,
                # Back face
                -1.0, -1.0, -1.0, -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0, -1.0, -1.0,
                # Top face
                -1.0,  1.0, -1.0, -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
                # Bottom face
                -1.0, -1.0, -1.0,  1.0, -1.0, -1.0,  1.0, -1.0,  1.0, -1.0, -1.0,  1.0,
                # Right face
                 1.0, -1.0, -1.0,  1.0,  1.0, -1.0,  1.0,  1.0,  1.0,  1.0, -1.0,  1.0,
                # Left face
                -1.0, -1.0, -1.0, -1.0, -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0, -1.0
            ],
            'normals': [
                # Front face
                0.0, 0.0, 1.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,
                # Back face
                0.0, 0.0, -1.0,  0.0, 0.0, -1.0,  0.0, 0.0, -1.0,  0.0, 0.0, -1.0,
                # Top face
                0.0, 1.0, 0.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,
                # Bottom face
                0.0, -1.0, 0.0,  0.0, -1.0, 0.0,  0.0, -1.0, 0.0,  0.0, -1.0, 0.0,
                # Right face
                1.0, 0.0, 0.0,  1.0, 0.0, 0.0,  1.0, 0.0, 0.0,  1.0, 0.0, 0.0,
                # Left face
                -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0
            ],
            'vertsPerPoly': [4, 4, 4, 4, 4, 4],  # 6 quads
            'windingOrder': 0
        }
        
        # Sphere mesh (simplified)
        meshes[1002] = {
            'id': 1002,
            'name': 'Mock Sphere',
            'objectHandle': 1002,
            'positions': self._generate_sphere_vertices(),
            'normals': self._generate_sphere_normals(),
            'vertsPerPoly': [3] * 80,  # 80 triangles (simplified sphere)
            'windingOrder': 0
        }
        
        # Teapot mesh (placeholder)
        meshes[1003] = {
            'id': 1003,
            'name': 'Mock Teapot',
            'objectHandle': 1003,
            'positions': self._generate_teapot_vertices(),
            'normals': self._generate_teapot_normals(),
            'vertsPerPoly': [3] * 100,  # 100 triangles
            'windingOrder': 0
        }
        
        return meshes
    
    def _generate_sphere_vertices(self) -> List[float]:
        """Generate simplified sphere vertices"""
        vertices = []
        radius = 1.0
        segments = 10
        rings = 8
        
        for ring in range(rings + 1):
            theta = ring * math.pi / rings
            sin_theta = math.sin(theta)
            cos_theta = math.cos(theta)
            
            for segment in range(segments + 1):
                phi = segment * 2 * math.pi / segments
                sin_phi = math.sin(phi)
                cos_phi = math.cos(phi)
                
                x = radius * sin_theta * cos_phi
                y = radius * cos_theta
                z = radius * sin_theta * sin_phi
                
                vertices.extend([x, y, z])
        
        return vertices[:240]  # Limit to reasonable size
    
    def _generate_sphere_normals(self) -> List[float]:
        """Generate sphere normals (same as normalized positions)"""
        return self._generate_sphere_vertices()  # For a unit sphere, normals = positions
    
    def _generate_teapot_vertices(self) -> List[float]:
        """Generate simplified teapot-like vertices"""
        vertices = []
        # Simple teapot approximation with body, spout, and handle
        
        # Body (cylinder-like)
        for i in range(20):
            angle = i * 2 * math.pi / 20
            x = math.cos(angle) * 0.8
            z = math.sin(angle) * 0.8
            vertices.extend([x, 0.0, z])  # Bottom
            vertices.extend([x, 1.0, z])  # Top
        
        # Spout (simplified)
        for i in range(10):
            t = i / 10.0
            x = 0.8 + t * 0.5
            y = 0.5 + t * 0.2
            z = 0.0
            vertices.extend([x, y, z])
        
        # Handle (simplified)
        for i in range(10):
            angle = i * math.pi / 10
            x = -0.8 - 0.3 * math.cos(angle)
            y = 0.5 + 0.3 * math.sin(angle)
            z = 0.0
            vertices.extend([x, y, z])
        
        return vertices[:300]  # Limit to reasonable size
    
    def _generate_teapot_normals(self) -> List[float]:
        """Generate simplified teapot normals"""
        normals = []
        # Simplified normals pointing outward
        for i in range(100):
            normals.extend([0.0, 1.0, 0.0])  # Simple upward normals
        return normals
    
    async def GetCamera(self, request, context):
        """Get current camera state"""
        self.stats['get_camera_calls'] += 1
        
        print(f"📤 GetCamera request #{self.stats['get_camera_calls']}")
        
        # Add some realistic variation to simulate camera movement
        time_offset = time.time() * 0.1
        pos_variation = math.sin(time_offset) * 0.1
        
        response = livelink_pb2.CameraState(
            position=livelink_pb2.Vec3(
                x=self.camera_state['position']['x'] + pos_variation,
                y=self.camera_state['position']['y'],
                z=self.camera_state['position']['z']
            ),
            target=livelink_pb2.Vec3(
                x=self.camera_state['target']['x'],
                y=self.camera_state['target']['y'],
                z=self.camera_state['target']['z']
            ),
            up=livelink_pb2.Vec3(
                x=self.camera_state['up']['x'],
                y=self.camera_state['up']['y'],
                z=self.camera_state['up']['z']
            ),
            fov=self.camera_state['fov']
        )
        
        print(f"📥 Returning camera: pos=({response.position.x:.2f}, {response.position.y:.2f}, {response.position.z:.2f})")
        return response
    
    async def SetCamera(self, request, context):
        """Set camera state"""
        self.stats['set_camera_calls'] += 1
        
        print(f"📤 SetCamera request #{self.stats['set_camera_calls']}")
        print(f"📥 New camera: pos=({request.position.x:.2f}, {request.position.y:.2f}, {request.position.z:.2f})")
        
        # Update internal camera state
        self.camera_state['position'] = {
            'x': request.position.x,
            'y': request.position.y,
            'z': request.position.z
        }
        self.camera_state['target'] = {
            'x': request.target.x,
            'y': request.target.y,
            'z': request.target.z
        }
        self.camera_state['up'] = {
            'x': request.up.x,
            'y': request.up.y,
            'z': request.up.z
        }
        self.camera_state['fov'] = request.fov
        
        return livelink_pb2.Empty()
    
    async def GetMeshes(self, request, context):
        """Get list of available meshes"""
        self.stats['get_meshes_calls'] += 1
        
        print(f"📤 GetMeshes request #{self.stats['get_meshes_calls']}")
        
        mesh_list = []
        for mesh_id, mesh_data in self.meshes.items():
            mesh_info = livelink_pb2.Mesh(
                id=mesh_data['id'],
                name=mesh_data['name'],
                objectHandle=mesh_data['objectHandle']
            )
            mesh_list.append(mesh_info)
        
        response = livelink_pb2.MeshList(meshes=mesh_list)
        
        print(f"📥 Returning {len(mesh_list)} meshes: {[m.name for m in mesh_list]}")
        return response
    
    async def GetMesh(self, request, context):
        """Get detailed mesh data"""
        self.stats['get_mesh_calls'] += 1
        
        print(f"📤 GetMesh request #{self.stats['get_mesh_calls']} for handle: {request.objectHandle}")
        
        mesh_id = request.objectHandle
        if mesh_id not in self.meshes:
            print(f"❌ Mesh {mesh_id} not found")
            context.set_code(grpc.StatusCode.NOT_FOUND)
            context.set_details(f"Mesh with handle {mesh_id} not found")
            return livelink_pb2.MeshData()
        
        mesh_data = self.meshes[mesh_id]
        
        response = livelink_pb2.MeshData(
            name=mesh_data['name'],
            positions=mesh_data['positions'],
            normals=mesh_data['normals'],
            vertsPerPoly=mesh_data['vertsPerPoly'],
            windingOrder=mesh_data['windingOrder']
        )
        
        print(f"📥 Returning mesh '{mesh_data['name']}': {len(mesh_data['positions'])//3} vertices, {len(mesh_data['vertsPerPoly'])} polygons")
        return response
    
    def print_stats(self):
        """Print server statistics"""
        uptime = time.time() - self.stats['start_time']
        print(f"\n📊 Mock Octane Server Statistics:")
        print(f"   Uptime: {uptime:.1f}s")
        print(f"   GetCamera calls: {self.stats['get_camera_calls']}")
        print(f"   SetCamera calls: {self.stats['set_camera_calls']}")
        print(f"   GetMeshes calls: {self.stats['get_meshes_calls']}")
        print(f"   GetMesh calls: {self.stats['get_mesh_calls']}")
        print(f"   Total calls: {sum(self.stats.values()) - 1}")  # -1 for start_time

async def serve():
    """Start the mock gRPC server"""
    print("🎭 Starting Mock Octane gRPC Server")
    print("=" * 50)
    
    # Create service instance
    service = MockOctaneLiveLinkService()
    
    # Create gRPC server
    server = grpc.aio.server(futures.ThreadPoolExecutor(max_workers=10))
    livelink_pb2_grpc.add_LiveLinkServiceServicer_to_server(service, server)
    
    # Configure server address
    listen_addr = '127.0.0.1:51022'
    server.add_insecure_port(listen_addr)
    
    print(f"🚀 Mock Octane gRPC server starting on {listen_addr}")
    print(f"🎯 This server simulates Octane Render's LiveLink gRPC service")
    print(f"📡 HTML applications can connect via the proxy server")
    print(f"🔧 Use this for development when Octane Render is not available")
    print()
    
    # Start server
    await server.start()
    print(f"✅ Mock server is running and ready for connections!")
    print(f"📝 Available mock meshes:")
    for mesh_id, mesh_data in service.meshes.items():
        print(f"   - {mesh_data['name']} (ID: {mesh_id})")
    print()
    print("Press Ctrl+C to stop the server")
    print("=" * 50)
    
    try:
        # Keep server running
        while True:
            await asyncio.sleep(30)  # Print stats every 30 seconds
            service.print_stats()
            
    except KeyboardInterrupt:
        print("\n🛑 Shutting down mock server...")
        service.print_stats()
        await server.stop(5)
        print("✅ Mock server stopped")

if __name__ == '__main__':
    try:
        asyncio.run(serve())
    except KeyboardInterrupt:
        print("\n👋 Mock server terminated by user")
    except Exception as e:
        print(f"❌ Error starting mock server: {e}")
        sys.exit(1)