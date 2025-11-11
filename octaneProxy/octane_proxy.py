#!/usr/bin/env python3
"""
Robust Octane gRPC Proxy Server
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
import uuid
import time
from datetime import datetime
from aiohttp import web, ClientSession
from aiohttp.web import middleware
from aiohttp.web_response import Response
import grpc
from google.protobuf.json_format import MessageToDict, ParseDict
from google.protobuf.message import Message
from google.protobuf.empty_pb2 import Empty

DO_LOGGING_LEVEL = 0

# Import callback streaming system
from callback_streamer import get_callback_streamer, initialize_callback_system

# Add generated directory to path for imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'generated'))

def get_debug_logs_dir(request=None):
    """
    Determine which app is calling and return appropriate debug_logs directory.
    Checks User-Agent, Referer, or Origin headers to detect octaneWeb vs octaneWeb2.
    Defaults to octaneWeb2 for new development.
    """
    app_name = 'octaneWeb2'  # Default to new app
    
    if request:
        # Check headers to determine source
        referer = request.headers.get('Referer', '')
        origin = request.headers.get('Origin', '')
        user_agent = request.headers.get('User-Agent', '')
        
        # If request contains 'octaneWeb' (not octaneWeb2) in path, use old directory
        if ('octaneWeb/' in referer or '/octaneWeb/' in referer) and 'octaneWeb2' not in referer:
            app_name = 'octaneWeb'
        elif 'octaneWeb2' in referer or 'octaneWeb2' in origin:
            app_name = 'octaneWeb2'
    
    logs_dir = os.path.join(os.path.dirname(__file__), '..', app_name, 'debug_logs')
    os.makedirs(logs_dir, exist_ok=True)
    return logs_dir

def get_enum_value(enum_name):
    """Get the integer value for an enum name from octaneenums_pb2"""
    try:
        from generated import octaneenums_pb2 as enums
        if hasattr(enums, enum_name):
            return getattr(enums, enum_name)
        return None
    except Exception as e:
        print(f"❌ Failed get_enum_value(): {enum_name}: {e}")
        return None

# Import core protobuf modules from generated directory
try:
    from generated import common_pb2
    from generated import apiprojectmanager_pb2
    from generated import apiprojectmanager_pb2_grpc
#    print("Successfully imported core gRPC protobuf modules from generated/")
except ImportError as e:
    print(f"❌ Failed to import core gRPC modules from generated/: {e}")
    print("Run ./build_protos.sh to generate protobuf files")
    sys.exit(1)

# Configuration
OCTANE_PORT = 51022  # Octane Server (always)
PROXY_PORT = 51023   # This proxy server (for octaneWeb)

# Docker networking support
def get_octane_address():
    """Get Octane address with automatic Docker/sandbox environment detection"""
    
    # host.docker.internal
    if os.environ.get('SANDBOX_USE_HOST_NETWORK') == 'true':
        print("Using Docker networking: host.docker.internal")
        return f'host.docker.internal:{OCTANE_PORT}'
    
    # openhands
    sandbox_indicators = [
        '/openhands' in os.getcwd(),  # OpenHands workspace path
        os.environ.get('OPENHANDS_WORKSPACE_BASE'),  # OpenHands env var
        os.path.exists('/.dockerenv'),  # Docker container indicator
        os.environ.get('CONTAINER'),  # Generic container indicator
        'sandbox' in os.environ.get('USER', '').lower(),  # Sandbox user
    ]
    
    if any(sandbox_indicators):
        print("Detected sandbox/container environment, using Docker networking: host.docker.internal")
        return f'host.docker.internal:{OCTANE_PORT}'
    
    # localhost for Windows/native environments
    return f'127.0.0.1:{OCTANE_PORT}'

# ==================== GRPC SERVICE REGISTRY ====================

class GrpcServiceRegistry:
    """Registry for dynamically loading gRPC service stubs (from octane_proxy.py)"""

    def __init__(self):
        self.stubs = {}
        self.service_modules = {}

    def get_moduleName(self, service_name, method_name, suffix, iter):
        try:
            base_service_map = {
                'ApiNodeGraph': 'apinodesystem_6',
                'ApiNode': 'apinodesystem_7',
                'ApiItem': 'apinodesystem_3',
                'ApiItemArray': 'apinodesystem_1',
                'ApiNodeArray': 'apinodesystem_5',
                'ApiNodePinInfoEx': 'apinodepininfohelper',
                'LiveLink': 'livelink',
                'ApiRenderEngine': 'apirender',
            }
            module_name = base_service_map.get(service_name)
            if not module_name:
                module_name = service_name.lower()
    
            return module_name + suffix
        
        except Exception as e:
            print(f"❌ Failed get_moduleName(): {service_name}: {e}")
            raise
        
    def get_stub(self, service_name, method_name, channel):
        """Get or create a gRPC stub for the given service"""
        module_name = self.get_moduleName(service_name, method_name, '_pb2_grpc', 1)
        stub = self.stubs.get(module_name)
        if stub:
            return stub

        try:
            grpc_module = importlib.import_module(module_name)
        except ImportError as e:
            print(f"❌ Failed get_stub(): no module {module_name}: {e}")
            raise

        # Get the stub class (convention: ServiceNameStub)
        stub_class_name = f"{service_name}ServiceStub"
        
        try:
            stub_class = getattr(grpc_module, stub_class_name)
        except AttributeError:
            raise Exception(f"Stub class not found: tried {stub_class_name} and {alt_stub_class_name}")

        # Create and cache the stub
        stub = stub_class(channel)
        self.stubs[module_name] = stub

        print(f"Created gRPC stub for {service_name} using {stub_class_name}")
        return stub
    
    def get_request_class(self, service_name, method_name):
        """Get the request class for a service method"""
        try:
            module_name = self.get_moduleName(service_name, method_name, '_pb2', 1)

            if not module_name:
                print(f"❌ Failed get_request_class(): no module {module_name}: {e}")
                return Empty

            # Import the protobuf module
            try:
                pb2_module = importlib.import_module(module_name)
            except ImportError:
                return Empty
 
            pattern = f"{service_name}.{method_name}"
            if service_name == 'LiveLink':
                if method_name == 'GetCamera':
                    pattern = "CameraState"
                elif method_name == 'SetCamera':
                    pattern = "CameraState"
            else:
                if method_name == 'getByAttrID':
                    method_name = 'getValueByID'
                elif method_name == 'setByAttrID':
                    method_name = 'setValueByID'
                elif method_name == 'getByName':
                    method_name = 'getValueByName'
                elif method_name == 'setByAttrName':
                    method_name = 'setValueByName'
                elif method_name == 'getByAttrIx':
                    method_name = 'getValueByIx'
                elif method_name == 'setByAttrIx':
                    method_name = 'setValueByIx'
                elif method_name == 'getApiNodePinInfo':
                    method_name = 'GetNodePinInfo'
                elif method_name == 'info1':
                    method_name = 'info'
                elif method_name == 'size1':
                    method_name = 'size'
                elif method_name == 'get1':
                    method_name = 'get'

                pattern = f"{service_name}.{method_name}Request"

 #           print(f"check request class for {service_name}.{method_name} {pattern}")

            if '.' in pattern:
                parts = pattern.split('.')
                request_class = pb2_module

                for part in parts:
                    if hasattr(request_class, part):
#                        print(f"request class for {part}")
                        request_class = getattr(request_class, part)
                    else:
                        request_class = None
                        break
            else:
                request_class = getattr(pb2_module, pattern, None)

            if request_class:
                if DO_LOGGING_LEVEL > 2:
                    print(f"GOT request class for {service_name}.{method_name} {pattern}")
                return request_class

            # Default to Empty if no request class found
            print(f"❌ Failed get_request_class(): {service_name}.{method_name} = {pattern}")
            return Empty

        except Exception as e:
            print(f"❌ Failed get_request_class(): {service_name}.{method_name}: {e}")
            return Empty

        except Exception as e:
            print(f"❌ Failed get_request_class(): {service_name}.{method_name}: {e}")
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

        print(f"Octane gRPC Passthrough Proxy Server")
        print(f"Proxy Port: {PROXY_PORT}")
        print(f"Octane Target: {self.octane_address}")
        print(f"Docker Support: {os.environ.get('SANDBOX_USE_HOST_NETWORK', 'false')}")

    async def connect_to_octane(self):
        """Connect to Octane with Docker networking support"""
        try:
            self.channel = grpc.aio.insecure_channel(self.octane_address)
            
            # Test connection with a simple call
            print(f"Testing connection with GetCamera request")
            from generated import livelink_pb2
            from generated import livelink_pb2_grpc
            
            stub = livelink_pb2_grpc.LiveLinkServiceStub(self.channel)
            request = livelink_pb2.Empty()
            response = await stub.GetCamera(request)
            print(f"Successfully connected to Octane at {self.octane_address}")
            print(f"Initial camera state: pos=({response.position.x:.2f}, {response.position.y:.2f}, {response.position.z:.2f})")
            return True
        except Exception as e:
            print(f"Failed connect_to_octane(): {self.octane_address}")
            return False

    def clear_debug_logs(self):
        """Clear any existing debug log files for a fresh session"""
        try:
            logs_dir = os.path.join(os.path.dirname(__file__), '..', 'octaneWeb', 'debug_logs')
            if os.path.exists(logs_dir):
                # Remove all existing log files
                for filename in os.listdir(logs_dir):
                    if filename.startswith('octane-debug-') and filename.endswith('.log'):
                        filepath = os.path.join(logs_dir, filename)
                        os.remove(filepath)
                        print(f"Cleared old debug log: {filename}")
        except Exception as e:
            print(f"Could not clear debug logs: {e}")

    async def disconnect(self):
        """Disconnect from Octane"""
        if self.channel:
            await self.channel.close()

# ==================== HTTP HANDLERS ====================

# Global proxy instance
proxy = None

# Track active sessions for log management
active_sessions = set()

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

async def handle_clear_debug_log(request):
    """Handle clearing/initializing the log file for a new session"""
    try:
        # Read the request body
        data = await request.json()
        
        # Extract data
        session_id = data.get('sessionId', 'unknown')
        timestamp = data.get('timestamp', datetime.now().isoformat())
        
        # Create logs directory if it doesn't exist
        logs_dir = os.path.join(os.path.dirname(__file__), '..', 'octaneWeb', 'debug_logs')
        os.makedirs(logs_dir, exist_ok=True)
        
        # Create filename
        filename = f"octane-debug-{session_id}.log"
        filepath = os.path.join(logs_dir, filename)
        
        # Clear/create log file with session header
        header = f"=== OctaneWeb Debug Log Session ===\nSession ID: {session_id}\nStarted: {timestamp}\n" + "="*40 + "\n\n"
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(header)
        
        # Send success response
        return web.json_response({'success': True, 'message': 'Log file cleared and initialized'}, headers={
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'POST, GET, OPTIONS',
            'Access-Control-Allow-Headers': 'Content-Type'
        })
        
    except Exception as e:
        # Silently fail to avoid console spam
        return web.json_response(
            {'error': f'Failed to clear log: {str(e)}'},
            status=500,
            headers={'Access-Control-Allow-Origin': '*'}
        )

async def handle_append_debug_log(request):
    """Handle appending a single log entry to the running log file"""
    try:
        # Read the request body
        data = await request.json()
        
        # Extract data
        session_id = data.get('sessionId', 'unknown')
        log_entry = data.get('logEntry', '')
        timestamp = data.get('timestamp', datetime.now().isoformat())
        
        # Get appropriate logs directory based on caller
        logs_dir = get_debug_logs_dir(request)
        
        # Create filename
        filename = f"octane-debug-{session_id}.log"
        filepath = os.path.join(logs_dir, filename)
        
        # Append log entry to file
        with open(filepath, 'a', encoding='utf-8') as f:
            f.write(log_entry + '\n')
        
        # Send success response (minimal to avoid spam)
        return web.json_response({'success': True}, headers={
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'POST, GET, OPTIONS',
            'Access-Control-Allow-Headers': 'Content-Type'
        })
        
    except Exception as e:
        # Silently fail to avoid console spam
        return web.json_response(
            {'error': f'Failed to append log: {str(e)}'},
            status=500,
            headers={'Access-Control-Allow-Origin': '*'}
        )

async def handle_save_debug_logs(request):
    """Handle saving debug logs to persistent system files (legacy endpoint)"""
    try:
        # Read the request body
        data = await request.json()
        
        # Extract data
        session_id = data.get('sessionId', 'unknown')
        log_content = data.get('content', '')
        timestamp = data.get('timestamp', datetime.now().isoformat())
        
        # Create logs directory if it doesn't exist
        logs_dir = os.path.join(os.path.dirname(__file__), '..', 'octaneWeb', 'debug_logs')
        os.makedirs(logs_dir, exist_ok=True)
        
        # Create filename
        filename = f"octane-debug-{session_id}.log"
        filepath = os.path.join(logs_dir, filename)
        
        # Write log content to file
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(log_content)
        
        # Log the save operation
        print(f"💾 Debug logs saved: {filepath} ({len(log_content)} bytes)")
        
        # Send success response
        response = {
            'success': True,
            'filename': filename,
            'filepath': os.path.abspath(filepath),
            'timestamp': timestamp,
            'size': len(log_content)
        }
        
        return web.json_response(response, headers={
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'POST, GET, OPTIONS',
            'Access-Control-Allow-Headers': 'Content-Type'
        })
        
    except Exception as e:
        print(f"❌ Error handle_save_debug_logs(): {e}")
        return web.json_response(
            {'error': f'Failed to save debug logs: {str(e)}'},
            status=500,
            headers={'Access-Control-Allow-Origin': '*'}
        )

async def handle_get_debug_logs(request):
    """Handle retrieving debug logs from system files"""
    try:
        # Extract session ID from path
        session_id = request.match_info.get('session_id', '')
        
        if not session_id:
            return web.json_response(
                {'error': 'Session ID required'},
                status=400,
                headers={'Access-Control-Allow-Origin': '*'}
            )
        
        logs_dir = os.path.join(os.path.dirname(__file__), '..', 'octaneWeb', 'debug_logs')
        filename = f"octane-debug-{session_id}.log"
        filepath = os.path.join(logs_dir, filename)
        
        if os.path.exists(filepath):
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
            
            return web.Response(
                text=content,
                content_type='text/plain',
                headers={'Access-Control-Allow-Origin': '*'}
            )
        else:
            return web.json_response(
                {'error': 'Log file not found'},
                status=404,
                headers={'Access-Control-Allow-Origin': '*'}
            )
            
    except Exception as e:
        print(f"❌ Error handle_get_debug_logs(): {e}")
        return web.json_response(
            {'error': f'Failed to retrieve debug logs: {str(e)}'},
            status=500,
            headers={'Access-Control-Allow-Origin': '*'}
        )

async def handle_health(request):
    """Health check endpoint - also clears logs for new session"""
    global active_sessions
    
    # Clear old logs when a new session connects (health check indicates new session)
    if proxy:
        proxy.clear_debug_logs()
        # Clear session tracking for fresh start
        active_sessions.clear()
    
    return web.json_response({'status': 'ok', 'connected': proxy.channel is not None})

def recurse_attr(grpc_request, key, value):
    if hasattr(grpc_request, key):
        attr = getattr(grpc_request, key)
        
        if isinstance(value, dict):
            # Handle nested message structures
            for nested_key, nested_value in value.items():
                if hasattr(attr, nested_key):
                    nested_attr = getattr(attr, nested_key)
                    
                    # Handle repeated fields (arrays)
                    if hasattr(nested_attr, 'extend') and isinstance(nested_value, list):
                        # Clear existing data and add new values
                        del nested_attr[:]
                        nested_attr.extend(nested_value)
                    elif isinstance(nested_value, dict):
                        # Recursively handle nested dictionaries
                        recurse_attr(attr, nested_key, nested_value)
                    else:
                        # Handle primitive types
                        if isinstance(nested_attr, bool):
                            if DO_LOGGING_LEVEL > 1:
                                print(f"settattr: {attr} {nested_key}")
                            setattr(attr, nested_key, bool(nested_value))
                        elif isinstance(nested_attr, int) or nested_key == "handle" or hasattr(nested_attr, '__class__') and 'enum' in str(type(nested_attr)).lower():
                            # Handle enum values and integer fields
                            if isinstance(nested_value, str) and nested_value.isupper():
                                enum_value = get_enum_value(nested_value)
                                if enum_value is not None:
                                    setattr(attr, nested_key, enum_value)
                                else:
                                    setattr(attr, nested_key, int(nested_value))
                            else:
                                setattr(attr, nested_key, int(nested_value))
                        else:
                            setattr(attr, nested_key, nested_value)
        elif isinstance(value, list):
            # Handle direct array assignment
            if hasattr(attr, 'extend'):
                del attr[:]
                attr.extend(value)
            else:
                setattr(grpc_request, key, value)
        else:
            # Handle primitive values
            if DO_LOGGING_LEVEL > 1:
                print(f"settattr: {grpc_request} {key} {value}")
            if isinstance(attr, bool):
                setattr(grpc_request, key, bool(value))
            elif isinstance(attr, int) or key == "handle" or hasattr(attr, '__class__') and 'enum' in str(type(attr)).lower():
                # Handle enum values and integer fields
                if isinstance(value, str) and value.isupper():
                    enum_value = get_enum_value(value)
                    if enum_value is not None:
                        setattr(grpc_request, key, enum_value)
                    else:
                        setattr(grpc_request, key, int(value))
                else:
                    setattr(grpc_request, key, int(value))
            else:
                setattr(grpc_request, key, value)
        return True
    
    return False
       
async def handle_generic_grpc(request):
    """Generic handler for any gRPC service call (URL-based routing)"""
    try:
        proxy.request_count += 1
        
        # Parse the URL path to extract service and method
        path = request.path
        
        # Extract service and method from path
        # Patterns: /octaneapi.ServiceName/methodName or /livelinkapi.ServiceName/methodName
        path_match = re.match(r'^/(?:octaneapi\.|livelinkapi\.)?([^/]+)/([^/]+)$', path)
        if not path_match:
            print(f"❌ Error handle_generic_grpc(): call path: {path}")
            return web.json_response({'success': False, 'error': 'Invalid path format'}, status=400)

        service_name = path_match.group(1)
        method_name = path_match.group(2)

        if DO_LOGGING_LEVEL > 0:
            print(f"Service/Method: {service_name}/{method_name}")

        # Get the appropriate stub
        stub = grpc_registry.get_stub(service_name, method_name, proxy.channel)

        # Get the method from the stub
        method = getattr(stub, method_name, None)
        if not method:
            print(f"❌ Error handle_generic_grpc(): no method: {method_name}")
            return web.json_response({'success': False, 'error': f'Method {method_name} not found on {service_name}'}, status=404)

        # Get request data from HTTP body
        request_data = {}
        if request.content_length and request.content_length > 0:
            try:
                request_data = await request.json()
            except Exception:
                pass  # Empty or invalid JSON is OK for some requests

        # Get the request class and create the request
        if DO_LOGGING_LEVEL > 2:
            print(f"Request sent: {json.dumps(request_data, indent=2)}")
        request_class = grpc_registry.get_request_class(service_name, method_name)
        grpc_request = request_class()

        # Populate request fields from JSON data
        if request_data:
            for key, value in request_data.items():
                if not recurse_attr(grpc_request, key, value):
                    if DO_LOGGING_LEVEL > 1:
                        print(f"REQUEST KEY: {key}")
                        print(f"Name: {grpc_request.DESCRIPTOR.name}")
                        print(f"Full Name: {grpc_request.DESCRIPTOR.full_name}")
                        print("Fields:")
                        for field in grpc_request.DESCRIPTOR.fields:
                            print(f"  - Name: {field.name}, Number: {field.number}")

                    if key == "objectPtr":
                        if not recurse_attr(grpc_request, "nodePinInfoRef", value): # GetNodePinInfoRequest
                            if not recurse_attr(grpc_request, "item_ref", value):     # getValueByIDRequest                          
                                print(f"❌ Error handle_generic_grpc(): no REQUEST KEY: {key}")

        # Make the gRPC call
        if DO_LOGGING_LEVEL > 1 and request_data:
            print(f"req:  {grpc_request}")        
        response = await method(grpc_request)

        # Convert response to dict
        success = False
        if hasattr(response, 'DESCRIPTOR'):
            response_dict = MessageToDict(response, preserving_proto_field_name=True)
            proxy.success_count += 1
            success = True
            if DO_LOGGING_LEVEL > 1 and response != Empty():
                print(f"resp: {response}")
        else:
            print(f"❌ Error handle_generic_grpc(): no response dict")
            print(f"resp: {response}")

        return web.json_response({
            'success': success,
            'data': response_dict
        })

    except Exception as e:
        print(f"❌ Error handle_generic_grpc(): {e}")
        print(f"❌ Traceback: {traceback.format_exc()}")
        proxy.error_count += 1

        return web.json_response({
            'success': False,
            'error': str(e)
        }, status=500)

# ==================== CALLBACK STREAMING ENDPOINTS ====================

async def handle_register_callback(request):
    """Register callback and start streaming"""
    try:
        octane_address = get_octane_address()
        
        # Initialize callback system
        success = await initialize_callback_system(octane_address)
        
        if success:
            streamer = get_callback_streamer(octane_address)
            status = streamer.get_status()
            
            return web.json_response({
                'success': True,
                'message': 'Callback streaming initialized',
                'callback_id': status['callback_id'],
                'status': status
            })
        else:
            return web.json_response({
                'success': False,
                'error': 'Failed to initialize callback system'
            }, status=500)
            
    except Exception as e:
        print(f"❌ Error handle_register_callback(): {e}")
        return web.json_response({
            'success': False,
            'error': str(e)
        }, status=500)

async def handle_stream_events(request):
    """Server-Sent Events endpoint for real-time callback streaming"""
    try:
        # Generate unique client ID
        client_id = str(uuid.uuid4())
        
        print(f"Starting SSE stream for client: {client_id}")
        
        # Create response with SSE headers
        response = web.StreamResponse(
            status=200,
            reason='OK',
            headers={
                'Content-Type': 'text/event-stream',
                'Cache-Control': 'no-cache',
                'Connection': 'keep-alive',
                'Access-Control-Allow-Origin': '*',
                'Access-Control-Allow-Headers': 'Cache-Control'
            }
        )
        
        await response.prepare(request)
        
        # Get callback streamer
        streamer = get_callback_streamer()
        
        # Client callback function for broadcasting
        async def client_callback(data):
            try:
                # Format as Server-Sent Event
                event_data = f"data: {json.dumps(data)}\n\n"
                await response.write(event_data.encode('utf-8'))
            except Exception as e:
                print(f"❌ Error client_callback(): sending SSE to {client_id}: {e}")
                raise
        
        # Add client to streamer with main event loop reference
        main_loop = asyncio.get_running_loop()
        streamer.add_client(client_id, client_callback, main_loop)
        
        try:
            # Send initial connection event
            initial_event = {
                'type': 'connected',
                'client_id': client_id,
                'timestamp': time.time(),
                'status': streamer.get_status()
            }
            await client_callback(initial_event)
            
            # Send any queued images
            latest_image = streamer.get_latest_image()
            if latest_image:
                await client_callback(latest_image)
            
            # Keep connection alive and send periodic pings
            while True:
                try:
                    # Send ping every 30 seconds to keep connection alive
                    await asyncio.sleep(30)
                    
                    ping_event = {
                        'type': 'ping',
                        'timestamp': time.time()
                    }
                    await client_callback(ping_event)
                    
                except asyncio.CancelledError:
                    break
                except Exception as e:
                    print(f"❌ Error handle_stream_events(): SSE connection error for {client_id}: {e}")
                    break
        
        finally:
            # Remove client when connection closes
            streamer.remove_client(client_id)
            print(f"SSE stream ended for client: {client_id}")
        
        return response
        
    except Exception as e:
        print(f"❌ Error handle_stream_events(): in SSE stream: {e}")
        return web.json_response({
            'error': str(e)
        }, status=500)

async def handle_callback_status(request):
    """Get current callback streaming status"""
    try:
        streamer = get_callback_streamer()
        status = streamer.get_status()
        
        return web.json_response({
            'success': True,
            'status': status
        })
        
    except Exception as e:
        return web.json_response({
            'success': False,
            'error': str(e)
        }, status=500)

async def handle_ping_client(request):
    """Ping client to keep connection alive"""
    try:
        data = await request.json()
        client_id = data.get('client_id')
        
        if client_id:
            streamer = get_callback_streamer()
            streamer.ping_client(client_id)
            
            return web.json_response({
                'success': True,
                'message': 'Client pinged'
            })
        else:
            return web.json_response({
                'success': False,
                'error': 'Missing client_id'
            }, status=400)
            
    except Exception as e:
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
    
    # Debug log endpoints
    app.router.add_post('/debug/clear-log', handle_clear_debug_log)
    app.router.add_post('/debug/append-log', handle_append_debug_log)
    app.router.add_post('/save-debug-logs', handle_save_debug_logs)
    app.router.add_get('/debug-logs/{session_id}', handle_get_debug_logs)
    
    # Callback streaming endpoints
    app.router.add_post('/render/register-callback', handle_register_callback)
    app.router.add_get('/render/stream', handle_stream_events)
    app.router.add_get('/render/callback-status', handle_callback_status)
    app.router.add_post('/render/ping-client', handle_ping_client)
    
    # Generic catch-all routes for any gRPC service call
    # Pattern: /[prefix.]ServiceName/methodName
    app.router.add_post('/{service:[^/]+}/{method:[^/]+}', handle_generic_grpc)
    
    # CORS options handler (should be last to catch all)
    app.router.add_options('/{path:.*}', handle_options)
    
    return app

async def main():
    """Main entry point"""
    # Create proxy instance
    global proxy
    proxy = ComprehensiveOctaneProxy()
    
    # Connect to Octane, keep trying
    while not await proxy.connect_to_octane():
        print(" - reattempt in 5 secs")
        time.sleep(5)

    # Create web application
    app = create_app()
    
    # Start server
    runner = web.AppRunner(app)
    await runner.setup()
    site = web.TCPSite(runner, '0.0.0.0', PROXY_PORT)
    await site.start()
    
    print(f"Proxy server running on http://0.0.0.0:{PROXY_PORT}")
    print(f"Available endpoints:")
    print(f"  GET /health - Health check")
    print(f"  POST /ServiceName/methodName - json -> grpc -> Octane")
    print(f"Ready to proxy Octane services dynamically")
    
    # Keep server running
    try:
        while True:
            await asyncio.sleep(1)
    except KeyboardInterrupt:
        print("\nShutting down proxy server...")
        if proxy:
            await proxy.disconnect()
        await runner.cleanup()

if __name__ == '__main__':
    import sys
    
    # Check for debug flags
    if len(sys.argv) > 1:
        if sys.argv[1] == '--debug-callback':
            print("Running callback system debug test...")
            asyncio.run(debug_callback_system())
        elif sys.argv[1] == '--debug-camera':
            print("Running camera image comparison debug test...")
            asyncio.run(debug_camera_image_comparison())
        else:
            print("❌ Unknown debug option. Available options:")
            print("   --debug-callback    Test callback system")
            print("   --debug-camera      Test camera changes and image comparison")
            sys.exit(1)
    else:
        asyncio.run(main())