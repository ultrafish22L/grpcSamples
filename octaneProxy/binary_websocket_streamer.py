#!/usr/bin/env python3
"""
Binary WebSocket Streaming System for Octane Callbacks
Optimized replacement for base64 Server-Sent Events transport

PERFORMANCE IMPROVEMENTS:
- Eliminates 33% base64 encoding overhead
- Reduces CPU usage for encoding/decoding
- Enables binary data streaming without JSON wrapper
- Supports efficient buffer pooling and reuse

ARCHITECTURE:
1. WebSocket connection for bidirectional communication
2. Binary message format with structured headers
3. Direct buffer transmission without encoding
4. Client-side binary buffer processing
"""

import asyncio
import json
import logging
import struct
import time
from typing import Dict, Optional, Callable, List
from dataclasses import dataclass
from aiohttp import web, WSMsgType
import weakref

# Import callback streaming base functionality
from callback_streamer import OctaneCallbackStreamer, CallbackClient

class BinaryMessage:
    """Binary message structure for WebSocket transport"""
    def __init__(self, message_type: int, timestamp: float, payload_size: int, payload: bytes):
        self.type = message_type          # Match JavaScript naming
        self.message_type = message_type  # Keep both for compatibility
        self.timestamp = timestamp
        self.payloadSize = payload_size   # Match JavaScript naming
        self.payload_size = payload_size  # Keep both for compatibility
        self.payload = payload

class BinaryMessageTypes:
    """Message type constants"""
    CONNECTED = 1
    NEW_IMAGE = 2
    RENDER_FAILURE = 3
    NEW_STATISTICS = 4
    PROJECT_CHANGED = 5
    PING = 6
    ERROR = 7

class BinaryWebSocketStreamer(OctaneCallbackStreamer):
    """
    Enhanced callback streamer using binary WebSocket transport
    Extends base OctaneCallbackStreamer with optimized binary communication
    """
    
    def __init__(self, octane_address: str = "127.0.0.1:51022"):
        super().__init__(octane_address)
        
        # WebSocket client management
        self.websocket_clients: Dict[str, web.WebSocketResponse] = {}
        self.client_metadata: Dict[str, dict] = {}
        
        # Binary message statistics
        self.binary_stats = {
            'messages_sent': 0,
            'bytes_sent': 0,
            'encoding_time_saved': 0.0,  # Estimated time saved vs base64
            'bandwidth_saved': 0         # Bytes saved vs base64
        }
        
        print(f"Initialized BinaryWebSocketStreamer for {octane_address}")
    
    def pack_binary_message(self, message_type: int, payload: bytes, timestamp: float = None) -> bytes:
        """
        Pack binary message with structured header
        Format: [type:4][timestamp:8][payload_size:4][payload:N] = 16 byte header
        """
        if timestamp is None:
            timestamp = time.time()
        
        # Use double for timestamp to get 8 bytes
        header = struct.pack('!IdI', message_type, timestamp, len(payload))
        return header + payload
    
    def unpack_binary_message(self, data: bytes) -> BinaryMessage:
        """Unpack binary message from structured format"""
        if len(data) < 16:  # Minimum header size
            raise ValueError("Invalid binary message: too short")
        
        # Use double for timestamp to match packing
        message_type, timestamp, payload_size = struct.unpack('!IdI', data[:16])
        
        if len(data) != 16 + payload_size:
            raise ValueError("Invalid binary message: payload size mismatch")
        
        payload = data[16:16 + payload_size]
        
        return BinaryMessage(message_type, timestamp, payload_size, payload)
    
    async def handle_websocket_connection(self, request):
        """Handle new WebSocket connection for binary streaming"""
        ws = web.WebSocketResponse()
        await ws.prepare(request)
        
        # Generate client ID
        client_id = f"ws_{int(time.time() * 1000)}_{len(self.websocket_clients)}"
        
        # Store WebSocket connection
        self.websocket_clients[client_id] = ws
        self.client_metadata[client_id] = {
            'connected_at': time.time(),
            'messages_sent': 0,
            'bytes_sent': 0,
            'last_ping': time.time()
        }
        
        print(f"🔌 WebSocket client connected: {client_id}")
        
        try:
            # Send initial connection message
            await self.send_binary_message(client_id, BinaryMessageTypes.CONNECTED, 
                                         json.dumps({
                                             'client_id': client_id,
                                             'server_time': time.time(),
                                             'protocol': 'binary_websocket_v1'
                                         }).encode('utf-8'))
            
            # Send any queued image if available
            latest_image = self.get_latest_image()
            if latest_image:
                await self.send_image_binary(client_id, latest_image)
            
            # Handle incoming messages
            async for msg in ws:
                if msg.type == WSMsgType.BINARY:
                    await self.handle_binary_message(client_id, msg.data)
                elif msg.type == WSMsgType.TEXT:
                    await self.handle_text_message(client_id, msg.data)
                elif msg.type == WSMsgType.ERROR:
                    print(f'❌ WebSocket error for {client_id}: {ws.exception()}')
                    break
                elif msg.type == WSMsgType.CLOSE:
                    print(f'🔌 WebSocket closed for {client_id}')
                    break
        
        except Exception as e:
            print(f"❌ WebSocket error for {client_id}: {e}")
        
        finally:
            # Cleanup client
            if client_id in self.websocket_clients:
                del self.websocket_clients[client_id]
            if client_id in self.client_metadata:
                del self.client_metadata[client_id]
            print(f"🔌 WebSocket client disconnected: {client_id}")
        
        return ws
    
    async def handle_binary_message(self, client_id: str, data: bytes):
        """Handle incoming binary message from client"""
        try:
            message = self.unpack_binary_message(data)
            
            if message.message_type == BinaryMessageTypes.PING:
                # Update client ping time
                if client_id in self.client_metadata:
                    self.client_metadata[client_id]['last_ping'] = time.time()
                
                # Send pong response
                await self.send_binary_message(client_id, BinaryMessageTypes.PING, b'pong')
            
        except Exception as e:
            print(f"❌ Error handling binary message from {client_id}: {e}")
    
    async def handle_text_message(self, client_id: str, data: str):
        """Handle incoming text message from client (for compatibility)"""
        try:
            message = json.loads(data)
            
            if message.get('type') == 'ping':
                # Update client ping time
                if client_id in self.client_metadata:
                    self.client_metadata[client_id]['last_ping'] = time.time()
        
        except Exception as e:
            print(f"❌ Error handling text message from {client_id}: {e}")
    
    async def send_binary_message(self, client_id: str, message_type: int, payload: bytes):
        """Send binary message to specific client"""
        if client_id not in self.websocket_clients:
            return False
        
        ws = self.websocket_clients[client_id]
        if ws.closed:
            return False
        
        try:
            # Pack binary message
            binary_data = self.pack_binary_message(message_type, payload)
            
            # Send binary message
            await ws.send_bytes(binary_data)
            
            # Update statistics
            self.client_metadata[client_id]['messages_sent'] += 1
            self.client_metadata[client_id]['bytes_sent'] += len(binary_data)
            self.binary_stats['messages_sent'] += 1
            self.binary_stats['bytes_sent'] += len(binary_data)
            
            # Calculate bandwidth savings vs base64 (33% overhead)
            if message_type == BinaryMessageTypes.NEW_IMAGE:
                base64_size = len(payload) * 1.33  # 33% base64 overhead
                self.binary_stats['bandwidth_saved'] += int(base64_size - len(payload))
            
            return True
            
        except Exception as e:
            print(f"❌ Error sending binary message to {client_id}: {e}")
            return False
    
    async def send_image_binary(self, client_id: str, image_data: dict):
        """Send image data as optimized binary message"""
        try:
            # Extract image buffer from callback data
            if not image_data.get('render_images', {}).get('data'):
                return False
            
            first_image = image_data['render_images']['data'][0]
            if not first_image.get('buffer', {}).get('data'):
                return False
            
            # Create binary payload with image metadata + buffer
            metadata = {
                'callback_id': image_data.get('callback_id', 0),
                'timestamp': image_data.get('timestamp', time.time()),
                'image_info': {
                    'type': first_image.get('type', 0),
                    'colorSpace': first_image.get('colorSpace', 0),
                    'isLinear': first_image.get('isLinear', False),
                    'size': first_image.get('size', {'x': 0, 'y': 0}),
                    'pitch': first_image.get('pitch', 0),
                    'renderPassId': first_image.get('renderPassId', 0),
                    'tonemappedSamplesPerPixel': first_image.get('tonemappedSamplesPerPixel', 0),
                    'calculatedSamplesPerPixel': first_image.get('calculatedSamplesPerPixel', 0),
                    'samplesPerSecond': first_image.get('samplesPerSecond', 0),
                    'renderTime': first_image.get('renderTime', 0),
                    'hasAlpha': first_image.get('hasAlpha', False)
                }
            }
            
            # Encode metadata as JSON
            metadata_json = json.dumps(metadata).encode('utf-8')
            metadata_size = len(metadata_json)
            
            # Get raw image buffer (decode from base64 if needed)
            buffer_data = first_image['buffer']['data']
            if first_image['buffer'].get('encoding') == 'base64':
                import base64
                raw_buffer = base64.b64decode(buffer_data)
            else:
                raw_buffer = buffer_data if isinstance(buffer_data, bytes) else buffer_data.encode('utf-8')
            
            # Create binary payload: [metadata_size:4][metadata:N][buffer:M]
            payload = struct.pack('!I', metadata_size) + metadata_json + raw_buffer
            
            # Send as binary message
            return await self.send_binary_message(client_id, BinaryMessageTypes.NEW_IMAGE, payload)
            
        except Exception as e:
            print(f"❌ Error sending binary image to {client_id}: {e}")
            return False
    
    async def broadcast_binary_to_clients(self, message_type: int, payload: bytes):
        """Broadcast binary message to all connected WebSocket clients"""
        if not self.websocket_clients:
            return
        
        # Remove closed connections
        closed_clients = [
            client_id for client_id, ws in self.websocket_clients.items()
            if ws.closed
        ]
        
        for client_id in closed_clients:
            if client_id in self.websocket_clients:
                del self.websocket_clients[client_id]
            if client_id in self.client_metadata:
                del self.client_metadata[client_id]
        
        # Broadcast to active clients
        active_count = 0
        for client_id in list(self.websocket_clients.keys()):
            if await self.send_binary_message(client_id, message_type, payload):
                active_count += 1
        
        if active_count > 0 and message_type != BinaryMessageTypes.PING:
            print(f"📡 Broadcasted binary message to {active_count} WebSocket clients")
    
    async def _handle_new_image(self, new_image_request):
        """Override to use binary WebSocket transport"""
        try:
            last_callback_time = time.time()
            
            # Extract render images
            render_images = new_image_request.render_images
            
            if not render_images or not render_images.data:
                print("Empty render images in callback")
                return

            self.callback_count += 1
            if (self.callback_count % 2 == 0):
                # TODO: Fix double callback issue at source
                return
        
            self.last_callback_time = last_callback_time
            
            # Process first image for binary transmission
            if render_images.data:
                img = render_images.data[0]
                
                if img.buffer and img.buffer.data:
                    # Create optimized binary payload
                    metadata = {
                        'callback_id': new_image_request.callback_id,
                        'user_data': new_image_request.user_data,
                        'timestamp': self.last_callback_time,
                        'image_info': {
                            'type': int(img.type),
                            'colorSpace': int(img.colorSpace),
                            'isLinear': img.isLinear,
                            'size': {'x': img.size.x, 'y': img.size.y},
                            'pitch': img.pitch,
                            'renderPassId': int(img.renderPassId),
                            'tonemappedSamplesPerPixel': img.tonemappedSamplesPerPixel,
                            'calculatedSamplesPerPixel': img.calculatedSamplesPerPixel,
                            'samplesPerSecond': img.samplesPerSecond,
                            'renderTime': img.renderTime,
                            'hasAlpha': img.hasAlpha
                        }
                    }
                    
                    # Encode metadata as JSON
                    metadata_json = json.dumps(metadata).encode('utf-8')
                    metadata_size = len(metadata_json)
                    
                    # Create binary payload: [metadata_size:4][metadata:N][buffer:M]
                    payload = struct.pack('!I', metadata_size) + metadata_json + img.buffer.data
                    
                    # Broadcast binary message to WebSocket clients
                    await self.broadcast_binary_to_clients(BinaryMessageTypes.NEW_IMAGE, payload)
                    
                    # Also maintain compatibility with SSE clients (if any)
                    await super()._handle_new_image(new_image_request)
            
        except Exception as e:
            print(f"❌ Error handling binary new image callback: {e}")
    
    def get_binary_stats(self) -> dict:
        """Get binary WebSocket performance statistics"""
        return {
            **self.binary_stats,
            'active_websocket_clients': len(self.websocket_clients),
            'total_clients': len(self.websocket_clients) + len(self.clients),
            'bandwidth_savings_mb': self.binary_stats['bandwidth_saved'] / (1024 * 1024)
        }

# Global instance
_binary_websocket_streamer = None

def get_binary_websocket_streamer() -> BinaryWebSocketStreamer:
    """Get global binary WebSocket streamer instance"""
    global _binary_websocket_streamer
    return _binary_websocket_streamer

async def initialize_binary_websocket_system(octane_address: str) -> bool:
    """Initialize binary WebSocket streaming system"""
    global _binary_websocket_streamer
    
    try:
        if _binary_websocket_streamer is None:
            _binary_websocket_streamer = BinaryWebSocketStreamer(octane_address)
        
        # Initialize connection to Octane
        if not await _binary_websocket_streamer.initialize():
            return False
        
        # Register callback
        if not await _binary_websocket_streamer.register_callback():
            return False
        
        # Start streaming
        if not await _binary_websocket_streamer.start_streaming():
            return False
        
        print("✅ Binary WebSocket streaming system initialized successfully")
        return True
        
    except Exception as e:
        print(f"❌ Failed to initialize binary WebSocket system: {e}")
        return False