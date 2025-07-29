#!/usr/bin/env python3
"""
🚀 LOCKIT: Robust Octane gRPC Proxy Server
Octane proxy supporting both pass-through /service/method patterns

ARCHITECTURE:
Browser → HTTP/JSON → Proxy → gRPC → Octane (127.0.0.1:51022 or host.docker.internal:51022)

KEY FEATURES:
- Standalone generic gRPC pass-through handler
- Dynamic service registry for all Octane services
- Docker networking support (SANDBOX_USE_HOST_NETWORK)
- Comprehensive error handling and logging
- CORS support for file:// protocol

PROVEN PATTERNS:
- URL path parsing with regex
- Dynamic stub creation
- Request class resolution
- Protobuf field population
"""

import asyncio
import json
import logging
import sys
import os
import re
import importlib
import traceback
from datetime import datetime
from aiohttp import web, ClientSession
from aiohttp.web import middleware
import grpc
from google.protobuf.json_format import MessageToDict, ParseDict
from google.protobuf.message import Message
from google.protobuf.empty_pb2 import Empty

# Add proxy directory to path for imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'proxy'))

# Import core protobuf modules
try:
    import livelink_pb2
    import livelink_pb2_grpc
    import apiprojectmanager_pb2
    import apiprojectmanager_pb2_grpc
    import apinodesystem_pb2
    import apinodesystem_pb2_grpc
    import common_pb2
    print("✅ Successfully imported core gRPC protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import core gRPC modules: {e}")
    sys.exit(1)

# Configuration
OCTANE_PORT = 51022  # Octane LiveLink Server (always)
PROXY_PORT = 51023   # This proxy server (for octaneWeb)

# Docker networking support
def get_octane_address():
    """Get Octane address with automatic Docker/sandbox environment detection"""
    
    # Method 1: Explicit environment variable (highest priority)
    if os.environ.get('SANDBOX_USE_HOST_NETWORK') == 'true':
        print("🐳 Using Docker networking: host.docker.internal")
        return f'host.docker.internal:{OCTANE_PORT}'
    
    # Method 2: Check for OpenHands/sandbox environment indicators
    sandbox_indicators = [
        '/openhands' in os.getcwd(),  # OpenHands workspace path
        os.environ.get('OPENHANDS_WORKSPACE_BASE'),  # OpenHands env var
        os.path.exists('/.dockerenv'),  # Docker container indicator
        os.environ.get('CONTAINER'),  # Generic container indicator
        'sandbox' in os.environ.get('USER', '').lower(),  # Sandbox user
    ]
    
    if any(sandbox_indicators):
        print("🐳 Detected sandbox/container environment, using Docker networking: host.docker.internal")
        return f'host.docker.internal:{OCTANE_PORT}'
    
    # Method 3: Default to localhost for Windows/native environments
    print("🖥️ Using native networking: 127.0.0.1")
    return f'127.0.0.1:{OCTANE_PORT}'

# ==================== GRPC SERVICE REGISTRY ====================

class GrpcServiceRegistry:
    """Registry for dynamically loading gRPC service stubs (from octane_proxy.py)"""

    def __init__(self):
        self.stubs = {}
        self.service_modules = {}

    def get_moduleName(self, service_name, suffix, iter):
        try:
            service_map = {
                'ApiNodeGraph': 'apinodesystem',
                'ApiNode': 'apinodesystem',
                'ApiItem': 'apinodesystem',
                'ApiItemArray': 'apinodesystem',
            }
            module_name = service_map.get(service_name)
            if not module_name:
                module_name = service_name.lower()
    
            return module_name + suffix
        
        except Exception as e:
            print(f"❌ Failed to find module for {service_name}: {e}")
            raise
        
    def get_stub(self, service_name, channel):
        """Get or create a gRPC stub for the given service"""
        if service_name in self.stubs:
            return self.stubs[service_name]

        module_name = self.get_moduleName(service_name, '_pb2_grpc', 1)

        try:
            grpc_module = importlib.import_module(module_name)
        except AttributeError:
            print(f"❌ Failed to load module {module_name}: {e}")

        # Get the stub class (convention: ServiceNameStub)
        # Handle both "Service" and non-"Service" names
        if service_name.endswith(''):
            stub_class_name = f"{service_name}Stub"
        else:
            stub_class_name = f"{service_name}ServiceStub"
        
        try:
            stub_class = getattr(grpc_module, stub_class_name)
        except AttributeError:
            # Try alternative naming convention
            alt_stub_class_name = f"{service_name}Stub" if not service_name.endswith('') else f"{service_name}ServiceStub"
            try:
                stub_class = getattr(grpc_module, alt_stub_class_name)
                stub_class_name = alt_stub_class_name
            except AttributeError:
                raise Exception(f"Stub class not found: tried {stub_class_name} and {alt_stub_class_name}")

            # Create and cache the stub
            stub = stub_class(channel)
            self.stubs[service_name] = stub

            print(f"✅ Created gRPC stub for {service_name}")
            return stub

    def get_request_class(self, service_name, method_name):
        """Get the request class for a service method"""
        try:
            module_name = self.get_moduleName(service_name, '_pb2', 1)

            if not module_name:
                # Default to Empty for unknown services
                return Empty

            # Import the protobuf module
            try:
                pb2_module = importlib.import_module(module_name)
            except ImportError:
                return Empty

            # Try common request class naming patterns
            request_class_patterns = [
                f"{service_name}.{method_name}Request",  # ApiProjectManager.rootNodeGraphRequest
                f"{method_name}Request",                 # rootNodeGraphRequest
                f"{service_name}_{method_name}Request",  # ApiProjectManager_rootNodeGraph_Request
            ]

            for pattern in request_class_patterns:
                # Handle nested class names (e.g., ApiProjectManager.rootNodeGraphRequest)
                if '.' in pattern:
                    parts = pattern.split('.')
                    request_class = pb2_module
                    for part in parts:
                        if hasattr(request_class, part):
                            request_class = getattr(request_class, part)
                        else:
                            request_class = None
                            break
                else:
                    request_class = getattr(pb2_module, pattern, None)

                if request_class:
                    return request_class

            # Default to Empty if no request class found
            return Empty

        except Exception as e:
            print(f"❌ Failed to get request class for {service_name}.{method_name}: {e}")
            return Empty

# Global service registry
grpc_registry = GrpcServiceRegistry()

# ==================== PROXY SERVER ====================

class ComprehensiveOctaneProxy:
    """Comprehensive proxy server with dynamic gRPC service support"""

    def __init__(self):
        self.octane_address = get_octane_address()
        self.channel = None
        self.request_count = 0
        self.success_count = 0
        self.error_count = 0

        print(f"🚀 LOCKIT: Robust Octane gRPC Proxy Server")
        print(f"📡 Proxy Port: {PROXY_PORT}")
        print(f"🎯 Octane Target: {self.octane_address}")
        print(f"🐳 Docker Support: {os.environ.get('SANDBOX_USE_HOST_NETWORK', 'false')}")

    async def connect_to_octane(self):
        """Connect to Octane with Docker networking support"""
        try:
            print(f"🔌 Creating gRPC channel to {self.octane_address}")
            self.channel = grpc.aio.insecure_channel(self.octane_address)
            
            # Test connection with a simple call
            print(f"📤 Testing connection with GetCamera request")
            stub = livelink_pb2_grpc.LiveLinkServiceStub(self.channel)
            request = livelink_pb2.Empty()
            response = await stub.GetCamera(request)
            print(f"✅ Successfully connected to Octane at {self.octane_address}")
            print(f"📥 Initial camera state: pos=({response.position.x:.2f}, {response.position.y:.2f}, {response.position.z:.2f})")
            return True
            
        except Exception as e:
            print(f"❌ Failed to connect to Octane at {self.octane_address}: {e}")
            return False

    async def disconnect(self):
        """Disconnect from Octane"""
        if self.channel:
            await self.channel.close()

# ==================== HTTP HANDLERS ====================

# Global proxy instance
proxy = None

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
    return web.json_response({'status': 'ok', 'connected': proxy.channel is not None})

async def handle_generic_grpc(request):
    """Generic handler for any gRPC service call (URL-based routing)"""
    try:
        proxy.request_count += 1
        
        # Parse the URL path to extract service and method
        path = request.path
        print(f"\n🌐 === GENERIC gRPC REQUEST ===")
        print(f"🌐 Path: {path}")
        print(f"🌐 Remote: {request.remote}")
        
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
        stub = grpc_registry.get_stub(service_name, proxy.channel)

        # Get the method from the stub
        method = getattr(stub, method_name, None)
        if not method:
            return web.json_response({'success': False, 'error': f'Method {method_name} not found on {service_name}'}, status=404)

        # Get request data from HTTP body
        request_data = {}
        if request.content_length and request.content_length > 0:
            try:
                request_data = await request.json()
                print(f"📥 Request data: {json.dumps(request_data, indent=2)}")
            except Exception:
                pass  # Empty or invalid JSON is OK for some requests

        # Get the request class and create the request
        request_class = grpc_registry.get_request_class(service_name, method_name)
        grpc_request = request_class()
        
        # Populate request fields from JSON data
        if request_data:
            for key, value in request_data.items():
                if hasattr(grpc_request, key):
                    field_descriptor = None


                    for field in grpc_request.DESCRIPTOR.fields:
                        if field.name == key:
                            field_descriptor = field
                            break

                    if field_descriptor and field_descriptor.type == field_descriptor.TYPE_MESSAGE:
                        # Handle nested message fields
                        nested_message = getattr(grpc_request, key)
                        if isinstance(value, dict):
                            for nested_key, nested_value in value.items():
                                if hasattr(nested_message, nested_key):
                                    if (nested_key == 'handle'):
                                        setattr(nested_message, nested_key, int(nested_value))
                                    else:
                                        setattr(nested_message, nested_key, nested_value)
                    else:
                        # Simple field
                        setattr(grpc_request, key, value)

        # Make the gRPC call
        response = await method(grpc_request)

        # Convert response to dict
        if hasattr(response, 'DESCRIPTOR'):
            response_dict = MessageToDict(response, preserving_proto_field_name=True)
        else:
            response_dict = {}

        print(f"📥 SUCCESS: {service_name}.{method_name}")
        proxy.success_count += 1

        return web.json_response({
            'success': True,
            'data': response_dict
        })

    except Exception as e:
        print(f"❌ ERROR: {e}")
        print(f"❌ Traceback: {traceback.format_exc()}")
        proxy.error_count += 1

        return web.json_response({
            'success': False,
            'error': str(e)
        }, status=500)

# ==================== APPLICATION SETUP ====================

def create_app():
    """Create the web application with all routes"""
    app = web.Application(middlewares=[cors_handler])
    
    # Health check
    app.router.add_get('/health', handle_health)
    
    # Generic catch-all routes for any gRPC service call
    # Pattern: /[prefix.]ServiceName/methodName
    app.router.add_post('/{service:[^/]+}/{method:[^/]+}', handle_generic_grpc)
    
    # CORS options handler (should be last to catch all)
    app.router.add_options('/{path:.*}', handle_options)
    
    return app

async def main():
    """Main entry point"""
    global proxy
    
    print(f"🚀 LOCKIT: Starting Robust Octane gRPC Proxy Server")
    print(f"📡 Proxy Port: {PROXY_PORT}")
    print(f"🎯 Octane Target: {get_octane_address()}")
    print(f"🐳 Docker Support: {os.environ.get('SANDBOX_USE_HOST_NETWORK', 'false')}")
    
    # Create proxy instance
    proxy = ComprehensiveOctaneProxy()
    
    # Connect to Octane
    if not await proxy.connect_to_octane():
        print("❌ Failed to connect to Octane - continuing anyway for development")
    
    # Create web application
    app = create_app()
    
    # Start server
    runner = web.AppRunner(app)
    await runner.setup()
    site = web.TCPSite(runner, '0.0.0.0', PROXY_PORT)
    await site.start()
    
    print(f"🌐 Proxy server running on http://0.0.0.0:{PROXY_PORT}")
    print(f"📋 Available endpoints:")
    print(f"   POST /api - octaneWeb JSON format")
    print(f"   POST /ServiceName/methodName - URL-based routing")
    print(f"   POST /octaneapi.ServiceName/methodName - Prefixed routing")
    print(f"   GET /health - Health check")
    print(f"🔄 Ready to proxy ALL Octane services dynamically")
    
    # Keep server running
    try:
        while True:
            await asyncio.sleep(1)
    except KeyboardInterrupt:
        print("\n🛑 Shutting down proxy server...")
        if proxy:
            await proxy.disconnect()
        await runner.cleanup()

if __name__ == '__main__':
    asyncio.run(main())