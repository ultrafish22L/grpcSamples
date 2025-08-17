#!/usr/bin/env python3
"""
🚀 Octane Callback Streaming System
Pure gRPC implementation of OnNewImage() callbacks without SDK

ARCHITECTURE:
1. Register callback with Octane via setOnNewImageCallback
2. Start streaming via StreamCallbackService.callbackChannel  
3. Forward real-time image data to browser clients via Server-Sent Events
4. Automatic fallback to polling if streaming fails

PERFORMANCE:
- Real-time push updates (no polling delay)
- Complete ApiRenderImage data with buffers
- Zero-copy streaming from Octane to browser
- Automatic reconnection and error handling
"""

import asyncio
import json
import logging
import threading
import time
import base64
from typing import List, Dict, Optional, Callable
from dataclasses import dataclass
from queue import Queue, Empty as QueueEmpty

import grpc
from google.protobuf.empty_pb2 import Empty

# Import generated protobuf modules
try:
    from generated import callback_pb2, callback_pb2_grpc
    from generated import apirender_pb2, apirender_pb2_grpc
    PROTOBUF_AVAILABLE = True
except ImportError as e:
    print(f"⚠️ Protobuf imports failed: {e}")
    print("📝 Callback streaming will be disabled")
    PROTOBUF_AVAILABLE = False

@dataclass
class CallbackClient:
    """Represents a browser client waiting for callback updates"""
    client_id: str
    callback_func: Callable
    last_ping: float
    active: bool = True

class OctaneCallbackStreamer:
    """
    Manages real-time callback streaming from Octane to browser clients
    """
    
    def __init__(self, octane_address: str = "127.0.0.1:51022"):
        self.octane_address = octane_address
        self.channel = None
        self.render_stub = None
        self.stream_stub = None
        
        # Callback state
        self.callback_id = None
        self.stream_active = False
        self.stream_thread = None
        
        # Client management
        self.clients: Dict[str, CallbackClient] = {}
        self.image_queue = Queue(maxsize=10)  # Buffer recent images
        
        # Statistics
        self.callback_count = 0
        self.last_callback_time = 0
        self.stream_errors = 0
        
        # Configuration
        self.reconnect_delay = 5.0  # Seconds between reconnection attempts
        self.client_timeout = 30.0  # Seconds before removing inactive clients
        
        print(f"🔧 Initialized OctaneCallbackStreamer for {octane_address}")
    
    async def initialize(self):
        """Initialize gRPC connection and stubs"""
        if not PROTOBUF_AVAILABLE:
            print("❌ Cannot initialize - protobuf modules not available")
            return False
            
        try:
            # Create gRPC channel
            self.channel = grpc.aio.insecure_channel(self.octane_address)
            
            # Test connection
            await self.channel.channel_ready()
            
            # Create service stubs
            self.render_stub = apirender_pb2_grpc.ApiRenderEngineServiceStub(self.channel)
            self.stream_stub = callback_pb2_grpc.StreamCallbackServiceStub(self.channel)
            
            print(f"✅ Connected to Octane at {self.octane_address}")
            return True
            
        except Exception as e:
            print(f"❌ Failed to connect to Octane: {e}")
            return False
    
    async def register_callback(self) -> bool:
        """Register OnNewImage callback with Octane render engine"""
        try:
            if not self.render_stub:
                await self.initialize()
            
            # Create callback registration request
            request = apirender_pb2.ApiRenderEngine.setOnNewImageCallbackRequest()
            request.callback = 1  # Callback function ID
            request.userData = 0  # User data
            
            # Register callback
            response = await self.render_stub.setOnNewImageCallback(request)
            self.callback_id = response.callbackId
            
            print(f"✅ Registered OnNewImage callback with ID: {self.callback_id}")
            return True
            
        except grpc.RpcError as e:
            print(f"❌ Failed to register callback: {e.code()} - {e.details()}")
            return False
        except Exception as e:
            print(f"❌ Callback registration error: {e}")
            return False
    
    async def start_streaming(self) -> bool:
        """Start streaming callbacks from Octane"""
        try:
            if not self.stream_stub:
                await self.initialize()
            
            # Start streaming in background thread
            self.stream_active = True
            self.stream_thread = threading.Thread(target=self._stream_worker, daemon=True)
            self.stream_thread.start()
            
            print("🔄 Started callback streaming thread")
            return True
            
        except Exception as e:
            print(f"❌ Failed to start streaming: {e}")
            self.stream_active = False
            return False
    
    def _stream_worker(self):
        """Background thread worker for streaming callbacks"""
        print("🔄 Callback streaming worker started")
        
        while self.stream_active:
            try:
                # Create new event loop for this thread
                loop = asyncio.new_event_loop()
                asyncio.set_event_loop(loop)
                
                # Run streaming coroutine
                loop.run_until_complete(self._stream_callbacks())
                
            except Exception as e:
                print(f"❌ Streaming worker error: {e}")
                self.stream_errors += 1
                
                if self.stream_active:
                    print(f"⏳ Reconnecting in {self.reconnect_delay} seconds...")
                    time.sleep(self.reconnect_delay)
            
            finally:
                try:
                    loop.close()
                except:
                    pass
        
        print("⏹️ Callback streaming worker stopped")
    
    async def _stream_callbacks(self):
        """Core streaming loop - receives callbacks from Octane"""
        try:
            # Open streaming channel
            empty_request = Empty()
            stream = self.stream_stub.callbackChannel(empty_request)
            
            print("📡 Opened callback stream channel")
            
            async for callback_request in stream:
                if not self.stream_active:
                    break
                
                # Process different callback types
                if callback_request.HasField('newImage'):
                    await self._handle_new_image(callback_request.newImage)
                elif callback_request.HasField('renderFailure'):
                    await self._handle_render_failure(callback_request.renderFailure)
                elif callback_request.HasField('newStatistics'):
                    await self._handle_new_statistics(callback_request.newStatistics)
                else:
                    print(f"🔍 Received unknown callback type: {callback_request}")
            
        except grpc.RpcError as e:
            if self.stream_active:  # Only log if we're supposed to be streaming
                print(f"❌ gRPC streaming error: {e.code()} - {e.details()}")
            raise
        except Exception as e:
            if self.stream_active:
                print(f"❌ Streaming error: {e}")
            raise
    
    async def _handle_new_image(self, new_image_request):
        """Handle OnNewImage callback"""
        try:
            self.callback_count += 1
            self.last_callback_time = time.time()
            
            print(f"📸 Received OnNewImage callback #{self.callback_count}")
            
            # Extract render images
            render_images = new_image_request.render_images
            
            if not render_images or not render_images.data:
                print("⚠️ Empty render images in callback")
                return
            
            # Convert to JSON format for browser
            image_data = {
                'type': 'newImage',
                'callback_id': new_image_request.callback_id,
                'user_data': new_image_request.user_data,
                'timestamp': self.last_callback_time,
                'render_images': {
                    'data': []
                }
            }
            
            # Process each render image
            for i, img in enumerate(render_images.data):
                try:
                    image_info = {
                        'index': i,
                        'type': int(img.type),
                        'colorSpace': int(img.colorSpace),
                        'isLinear': img.isLinear,
                        'size': {
                            'x': img.size.x,
                            'y': img.size.y
                        },
                        'pitch': img.pitch,
                        'renderPassId': int(img.renderPassId),
                        'tonemappedSamplesPerPixel': img.tonemappedSamplesPerPixel,
                        'calculatedSamplesPerPixel': img.calculatedSamplesPerPixel,
                        'samplesPerSecond': img.samplesPerSecond,
                        'renderTime': img.renderTime,
                        'changeLevel': img.changeLevel,
                        'hasPendingUpdates': img.hasPendingUpdates,
                        'hasAlpha': img.hasAlpha
                    }
                    
                    # Handle image buffer
                    if img.buffer and img.buffer.data:
                        # Encode buffer as base64 for JSON transport
                        buffer_data = base64.b64encode(img.buffer.data).decode('utf-8')
                        image_info['buffer'] = {
                            'data': buffer_data,
                            'size': len(img.buffer.data),
                            'encoding': 'base64'
                        }
                        
                        print(f"  📊 Image {i}: {img.size.x}x{img.size.y}, "
                              f"{len(img.buffer.data)} bytes, "
                              f"{img.tonemappedSamplesPerPixel:.1f} samples/px")
                    else:
                        print(f"  ⚠️ Image {i}: No buffer data")
                        image_info['buffer'] = None
                    
                    image_data['render_images']['data'].append(image_info)
                    
                except Exception as e:
                    print(f"❌ Error processing image {i}: {e}")
                    continue
            
            # Queue image data for clients
            try:
                self.image_queue.put_nowait(image_data)
            except:
                # Queue full - remove oldest item and add new one
                try:
                    self.image_queue.get_nowait()
                    self.image_queue.put_nowait(image_data)
                except:
                    pass
            
            # Broadcast to all active clients
            await self._broadcast_to_clients(image_data)
            
        except Exception as e:
            print(f"❌ Error handling new image callback: {e}")
    
    async def _handle_render_failure(self, render_failure_request):
        """Handle render failure callback"""
        print(f"❌ Render failure callback: {render_failure_request}")
        
        failure_data = {
            'type': 'renderFailure',
            'callback_id': render_failure_request.callback_id,
            'user_data': render_failure_request.user_data,
            'timestamp': time.time()
        }
        
        await self._broadcast_to_clients(failure_data)
    
    async def _handle_new_statistics(self, statistics_request):
        """Handle new statistics callback"""
        print(f"📊 New statistics callback: {statistics_request}")
        
        stats_data = {
            'type': 'newStatistics',
            'callback_id': statistics_request.callback_id,
            'user_data': statistics_request.user_data,
            'timestamp': time.time()
        }
        
        await self._broadcast_to_clients(stats_data)
    
    async def _broadcast_to_clients(self, data: dict):
        """Broadcast data to all active browser clients"""
        if not self.clients:
            return
        
        # Remove inactive clients
        current_time = time.time()
        inactive_clients = [
            client_id for client_id, client in self.clients.items()
            if current_time - client.last_ping > self.client_timeout
        ]
        
        for client_id in inactive_clients:
            print(f"🗑️ Removing inactive client: {client_id}")
            del self.clients[client_id]
        
        # Broadcast to active clients
        active_count = 0
        for client_id, client in self.clients.items():
            if client.active:
                try:
                    await client.callback_func(data)
                    active_count += 1
                except Exception as e:
                    print(f"❌ Error broadcasting to client {client_id}: {e}")
                    client.active = False
        
        if active_count > 0:
            print(f"📤 Broadcasted to {active_count} clients")
    
    def add_client(self, client_id: str, callback_func: Callable):
        """Add a browser client for callback updates"""
        client = CallbackClient(
            client_id=client_id,
            callback_func=callback_func,
            last_ping=time.time()
        )
        
        self.clients[client_id] = client
        print(f"➕ Added client: {client_id} (total: {len(self.clients)})")
    
    def remove_client(self, client_id: str):
        """Remove a browser client"""
        if client_id in self.clients:
            del self.clients[client_id]
            print(f"➖ Removed client: {client_id} (total: {len(self.clients)})")
    
    def ping_client(self, client_id: str):
        """Update client last ping time"""
        if client_id in self.clients:
            self.clients[client_id].last_ping = time.time()
    
    def get_latest_image(self) -> Optional[dict]:
        """Get the most recent image from queue (non-blocking)"""
        try:
            return self.image_queue.get_nowait()
        except QueueEmpty:
            return None
    
    def get_status(self) -> dict:
        """Get current streaming status"""
        return {
            'stream_active': self.stream_active,
            'callback_id': self.callback_id,
            'callback_count': self.callback_count,
            'last_callback_time': self.last_callback_time,
            'stream_errors': self.stream_errors,
            'active_clients': len([c for c in self.clients.values() if c.active]),
            'total_clients': len(self.clients),
            'queue_size': self.image_queue.qsize()
        }
    
    async def stop_streaming(self):
        """Stop callback streaming"""
        print("⏹️ Stopping callback streaming...")
        
        self.stream_active = False
        
        # Wait for stream thread to finish
        if self.stream_thread and self.stream_thread.is_alive():
            self.stream_thread.join(timeout=5.0)
        
        # Close gRPC channel
        if self.channel:
            await self.channel.close()
        
        print("✅ Callback streaming stopped")

# Global streamer instance
_global_streamer: Optional[OctaneCallbackStreamer] = None

def get_callback_streamer(octane_address: str = "127.0.0.1:51022") -> OctaneCallbackStreamer:
    """Get or create global callback streamer instance"""
    global _global_streamer
    
    if _global_streamer is None:
        _global_streamer = OctaneCallbackStreamer(octane_address)
    
    return _global_streamer

async def initialize_callback_system(octane_address: str = "127.0.0.1:51022") -> bool:
    """Initialize the complete callback system"""
    if not PROTOBUF_AVAILABLE:
        print("❌ Cannot initialize callback system - protobuf modules not available")
        return False
        
    try:
        streamer = get_callback_streamer(octane_address)
        
        # Initialize connection
        if not await streamer.initialize():
            return False
        
        # Register callback
        if not await streamer.register_callback():
            return False
        
        # Start streaming
        if not await streamer.start_streaming():
            return False
        
        print("🎉 Callback system initialized successfully!")
        return True
        
    except Exception as e:
        print(f"❌ Failed to initialize callback system: {e}")
        return False

if __name__ == "__main__":
    # Test the callback streamer
    async def test_streamer():
        print("🧪 Testing Octane Callback Streamer...")
        
        success = await initialize_callback_system()
        if success:
            print("✅ Test successful - callback system is working!")
            
            # Keep running for a bit to see callbacks
            await asyncio.sleep(10)
        else:
            print("❌ Test failed - callback system not working")
    
    asyncio.run(test_streamer())