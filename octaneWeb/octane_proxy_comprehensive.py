#!/usr/bin/env python3
"""
🚀 Comprehensive Octane gRPC Proxy Server
Pure pass-through proxy using actual Octane class names

LOCKIT: Purely pass-through - HTML uses real Octane class names
- ApiProjectManagerService, ApiItemService, ApiNodeService, etc.
- No abstraction layers, direct service mapping
- Comprehensive coverage of ALL Octane services
- Robust error handling and logging

Based on octaneGrpcTest service patterns for maximum compatibility.
"""

import asyncio
import json
import logging
import sys
import os
from datetime import datetime
from aiohttp import web, ClientSession
import grpc
from google.protobuf.json_format import MessageToDict, ParseDict
from google.protobuf.message import Message
from google.protobuf.empty_pb2 import Empty

# Add proxy directory to path for imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'proxy'))

# Import core protobuf modules (avoiding problematic ones)
import apinodesystem_pb2_grpc
import apiprojectmanager_pb2_grpc
import livelink_pb2_grpc
import apisceneoutliner_pb2_grpc
import apiselectionmanager_pb2_grpc

# Try to import additional modules safely
try:
    import apinodegrapheditor_pb2_grpc
except (ImportError, SyntaxError):
    apinodegrapheditor_pb2_grpc = None

try:
    import apirender_pb2_grpc
except (ImportError, SyntaxError):
    apirender_pb2_grpc = None

try:
    import apirenderview_pb2_grpc
except (ImportError, SyntaxError):
    apirenderview_pb2_grpc = None

class ComprehensiveOctaneProxy:
    """Comprehensive proxy server with ALL Octane services"""

    def __init__(self, proxy_port=51998, octane_host="host.docker.internal", octane_port=51022):
        self.proxy_port = proxy_port
        self.octane_host = octane_host
        self.octane_port = octane_port
        self.grpc_channel = None
        self.services = {}
        self.request_count = 0
        self.success_count = 0
        self.error_count = 0

        # Setup logging
        logging.basicConfig(level=logging.INFO)
        self.logger = logging.getLogger('ComprehensiveOctaneProxy')

        print(f"🚀 Comprehensive Octane gRPC Proxy Server")
        print(f"📡 Proxy Port: {proxy_port}")
        print(f"🎯 Octane Target: {octane_host}:{octane_port}")

    async def setup_grpc_connection(self):
        """Initialize gRPC connection and ALL services"""
        try:
            print(f"🔌 Connecting to Octane at {self.octane_host}:{self.octane_port}...")
            self.grpc_channel = grpc.aio.insecure_channel(f'{self.octane_host}:{self.octane_port}')
            
            # Initialize core service stubs using actual Octane class names
            self.services = {
                # Core Node System Services
                'ApiItemService': apinodesystem_pb2_grpc.ApiItemServiceStub(self.grpc_channel),
                'ApiNodeService': apinodesystem_pb2_grpc.ApiNodeServiceStub(self.grpc_channel),
                'ApiNodeGraphService': apinodesystem_pb2_grpc.ApiNodeGraphServiceStub(self.grpc_channel),
                'ApiRootNodeGraphService': apinodesystem_pb2_grpc.ApiRootNodeGraphServiceStub(self.grpc_channel),
                'ApiItemArrayService': apinodesystem_pb2_grpc.ApiItemArrayServiceStub(self.grpc_channel),
                'ApiNodeArrayService': apinodesystem_pb2_grpc.ApiNodeArrayServiceStub(self.grpc_channel),
                'ApiItemSetterService': apinodesystem_pb2_grpc.ApiItemSetterServiceStub(self.grpc_channel),
                'ApiItemGetterService': apinodesystem_pb2_grpc.ApiItemGetterServiceStub(self.grpc_channel),

                # Project & Scene Management
                'ApiProjectManagerService': apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(self.grpc_channel),
                'ApiSceneOutlinerService': apisceneoutliner_pb2_grpc.ApiSceneOutlinerServiceStub(self.grpc_channel),
                'ApiSelectionManagerService': apiselectionmanager_pb2_grpc.ApiSelectionManagerServiceStub(self.grpc_channel),

                # LiveLink Service (legacy compatibility)
                'LiveLinkService': livelink_pb2_grpc.LiveLinkServiceStub(self.grpc_channel),
            }

            # Add optional services if available
            if apinodegrapheditor_pb2_grpc:
                self.services['ApiNodeGraphEditorService'] = apinodegrapheditor_pb2_grpc.ApiNodeGraphEditorServiceStub(self.grpc_channel)

            if apirender_pb2_grpc:
                self.services['ApiRenderEngineService'] = apirender_pb2_grpc.ApiRenderEngineServiceStub(self.grpc_channel)

            if apirenderview_pb2_grpc:
                self.services['ApiRenderViewService'] = apirenderview_pb2_grpc.ApiRenderViewServiceStub(self.grpc_channel)

            # Test connection with a simple method
            try:
                # Try to get camera info as a connection test
                await self.services['LiveLinkService'].GetCamera(Empty())
                print("✅ gRPC connection established successfully")
                print(f"📋 Initialized {len(self.services)} Octane services")
                return True
            except Exception as e:
                print(f"⚠️ Connection test failed (expected if no scene): {e}")
                print(f"📋 Initialized {len(self.services)} Octane services anyway")
                return True

        except Exception as e:
            print(f"❌ Failed to setup gRPC connection: {e}")
            return False

    async def handle_api_request(self, request):
        """Handle API requests from octaneWeb using actual service names"""
        self.request_count += 1
        call_id = request.headers.get('X-Call-Id', f'call-{self.request_count}')

        try:
            # Parse request
            data = await request.json()
            service_name = data.get('service')
            method_name = data.get('method')
            params = data.get('params', {})

            print(f"📤 {call_id}: {service_name}.{method_name}")

            # Route to appropriate service using actual class name
            if service_name not in self.services:
                raise ValueError(f"Unknown service: {service_name}")

            service = self.services[service_name]
            method = getattr(service, method_name, None)
            
            if method is None:
                raise ValueError(f"Unknown method: {method_name}")

            # Convert params to protobuf message
            if params:
                try:
                    # Try to get the request type from the method
                    if hasattr(method, '_request_serializer') and hasattr(method._request_serializer, '_request_class'):
                        request_type = method._request_serializer._request_class
                    elif hasattr(method, 'request_serializer') and hasattr(method.request_serializer, 'request_class'):
                        request_type = method.request_serializer.request_class
                    else:
                        # Fallback: try to infer from method name
                        request_type = None
                        
                    if request_type and request_type != Empty:
                        grpc_request = ParseDict(params, request_type())
                    else:
                        grpc_request = Empty()
                except Exception as e:
                    print(f"⚠️ Failed to parse request params: {e}")
                    grpc_request = Empty()
            else:
                grpc_request = Empty()

            # Make the gRPC call
            response = await method(grpc_request)

            # Convert response to dict
            if hasattr(response, 'DESCRIPTOR'):
                response_dict = MessageToDict(response, preserving_proto_field_name=True)
            else:
                response_dict = {}

            print(f"📥 {call_id}: SUCCESS")
            self.success_count += 1

            return web.json_response({
                'success': True,
                'data': response_dict,
                'call_id': call_id
            })

        except Exception as e:
            print(f"❌ {call_id}: ERROR - {str(e)}")
            self.error_count += 1
            
            return web.json_response({
                'success': False,
                'error': str(e),
                'call_id': call_id
            }, status=500)

    async def handle_health_check(self, request):
        """Health check endpoint"""
        success_rate = (self.success_count / max(self.request_count, 1)) * 100
        
        return web.json_response({
            'status': 'healthy',
            'proxy_port': self.proxy_port,
            'octane_target': f'{self.octane_host}:{self.octane_port}',
            'services_count': len(self.services),
            'requests_total': self.request_count,
            'requests_success': self.success_count,
            'requests_error': self.error_count,
            'success_rate': round(success_rate, 1),
            'timestamp': datetime.now().isoformat()
        })

    async def handle_services_list(self, request):
        """List all available services"""
        return web.json_response({
            'services': list(self.services.keys()),
            'count': len(self.services)
        })

    async def start_server(self):
        """Start the proxy server"""
        # Setup gRPC connection first
        if not await self.setup_grpc_connection():
            print("❌ Failed to setup gRPC connection")
            return

        # Create web application
        app = web.Application()
        
        # Add CORS middleware
        @web.middleware
        async def cors_middleware(request, handler):
            response = await handler(request)
            response.headers['Access-Control-Allow-Origin'] = '*'
            response.headers['Access-Control-Allow-Methods'] = 'GET, POST, OPTIONS'
            response.headers['Access-Control-Allow-Headers'] = 'Content-Type, X-Call-Id'
            return response

        app.middlewares.append(cors_middleware)

        # Add routes
        app.router.add_post('/api', self.handle_api_request)
        app.router.add_get('/health', self.handle_health_check)
        app.router.add_get('/services', self.handle_services_list)
        app.router.add_options('/api', lambda r: web.Response())

        # Start server
        runner = web.AppRunner(app)
        await runner.setup()
        site = web.TCPSite(runner, '0.0.0.0', self.proxy_port)
        await site.start()

        print(f"🌐 Proxy server running on http://0.0.0.0:{self.proxy_port}")
        print(f"📋 Available endpoints:")
        print(f"   POST /api - Main API endpoint")
        print(f"   GET /health - Health check")
        print(f"   GET /services - List all services")
        print(f"🔄 Ready to proxy {len(self.services)} Octane services")

        # Keep server running
        try:
            while True:
                await asyncio.sleep(1)
        except KeyboardInterrupt:
            print("\n🛑 Shutting down proxy server...")
            await runner.cleanup()

async def main():
    """Main entry point"""
    import argparse
    
    parser = argparse.ArgumentParser(description='Comprehensive Octane gRPC Proxy Server')
    parser.add_argument('--host', default='0.0.0.0', help='Proxy host (default: 0.0.0.0)')
    parser.add_argument('--port', type=int, default=51998, help='Proxy port (default: 51998)')
    parser.add_argument('--octane-host', default='host.docker.internal', help='Octane host (default: host.docker.internal)')
    parser.add_argument('--octane-port', type=int, default=51022, help='Octane port (default: 51022)')
    
    args = parser.parse_args()
    
    proxy = ComprehensiveOctaneProxy(
        proxy_port=args.port,
        octane_host=args.octane_host,
        octane_port=args.octane_port
    )
    
    await proxy.start_server()

if __name__ == '__main__':
    asyncio.run(main())