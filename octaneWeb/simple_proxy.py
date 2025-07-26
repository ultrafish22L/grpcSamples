#!/usr/bin/env python3
"""
Simple HTTP-to-gRPC Proxy for OctaneWeb
Bypasses protobuf version issues by using direct gRPC calls
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

# CORS headers
CORS_HEADERS = {
    'Access-Control-Allow-Origin': '*',
    'Access-Control-Allow-Methods': 'GET, POST, OPTIONS, PUT, DELETE, PATCH',
    'Access-Control-Allow-Headers': 'Content-Type, Accept, X-Grpc-Web, X-Call-Id, Authorization, X-Requested-With, Origin',
    'Access-Control-Allow-Credentials': 'false',
    'Access-Control-Max-Age': '86400'
}

class SimpleOctaneProxy:
    def __init__(self):
        self.octane_host = "127.0.0.1"
        self.octane_port = 51022
        self.channel = None
        
    async def connect_to_octane(self):
        """Connect to Octane gRPC service"""
        try:
            self.channel = grpc.insecure_channel(f'{self.octane_host}:{self.octane_port}')
            # Test connection with a simple call
            print(f"✅ Connected to Octane at {self.octane_host}:{self.octane_port}")
            return True
        except Exception as e:
            print(f"❌ Failed to connect to Octane: {e}")
            return False
    
    async def test_octane_connection(self, request):
        """Test if Octane is available"""
        try:
            if not self.channel:
                await self.connect_to_octane()
            
            if self.channel:
                # Simple connection test - just check if channel exists
                return web.json_response({
                    'success': True,
                    'message': 'Octane is available',
                    'host': self.octane_host,
                    'port': self.octane_port
                }, headers=CORS_HEADERS)
            else:
                return web.json_response({
                    'success': False,
                    'message': 'Octane not available',
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
    
    async def handle_grpc_call(self, request):
        """Handle gRPC calls - placeholder for now"""
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
            
            # Get request data
            try:
                data = await request.json() if request.content_type == 'application/json' else {}
            except:
                data = {}
            
            print(f"📤 gRPC Call: {service_name}.{method_name} with data: {data}")
            
            # For now, return a placeholder response indicating Octane connection status
            if not self.channel:
                await self.connect_to_octane()
            
            if self.channel:
                return web.json_response({
                    'success': False,
                    'error': 'gRPC call implementation needed',
                    'service': service_name,
                    'method': method_name,
                    'data': data,
                    'message': 'Octane is connected but gRPC call not implemented yet'
                }, headers=CORS_HEADERS)
            else:
                return web.json_response({
                    'success': False,
                    'error': 'Octane not available',
                    'message': f'Cannot connect to Octane at {self.octane_host}:{self.octane_port}'
                }, headers=CORS_HEADERS, status=503)
                
        except Exception as e:
            print(f"❌ Error handling gRPC call: {e}")
            return web.json_response({
                'success': False,
                'error': str(e),
                'traceback': traceback.format_exc()
            }, headers=CORS_HEADERS, status=500)

async def create_app():
    """Create the web application"""
    proxy = SimpleOctaneProxy()
    
    app = web.Application()
    
    # Add routes
    app.router.add_options('/{path:.*}', proxy.handle_options)
    app.router.add_get('/test', proxy.test_octane_connection)
    app.router.add_post('/test', proxy.test_octane_connection)
    app.router.add_post('/{service}/{method}', proxy.handle_grpc_call)
    
    return app

async def main():
    """Main entry point"""
    print("🚀 Starting Simple Octane Proxy Server...")
    print(f"📡 Target: Octane at 127.0.0.1:51022")
    print(f"🌐 Proxy: http://localhost:51998")
    
    app = await create_app()
    
    runner = web.AppRunner(app)
    await runner.setup()
    
    site = web.TCPSite(runner, '0.0.0.0', 51998)
    await site.start()
    
    print("✅ Simple Octane Proxy Server started successfully!")
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