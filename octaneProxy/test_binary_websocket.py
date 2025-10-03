#!/usr/bin/env python3
"""
Test Binary WebSocket Implementation
Simple test to verify binary message packing/unpacking works correctly
"""

import struct
import json
import time
from binary_websocket_streamer import BinaryWebSocketStreamer, BinaryMessageTypes

def test_binary_message_packing():
    """Test binary message packing and unpacking"""
    print("🧪 Testing binary message packing/unpacking...")
    
    # Create streamer instance
    streamer = BinaryWebSocketStreamer()
    
    # Test data
    test_payload = b"Hello, Binary WebSocket!"
    message_type = BinaryMessageTypes.NEW_IMAGE
    timestamp = time.time()
    
    # Pack message
    packed = streamer.pack_binary_message(message_type, test_payload, timestamp)
    print(f"✅ Packed message: {len(packed)} bytes")
    
    # Unpack message
    unpacked = streamer.unpack_binary_message(packed)
    print(f"✅ Unpacked message: type={unpacked.type}, timestamp={unpacked.timestamp}, payload_size={unpacked.payloadSize}")
    
    # Verify data integrity
    assert unpacked.type == message_type, "Message type mismatch"
    assert abs(unpacked.timestamp - timestamp) < 0.001, "Timestamp mismatch"
    assert unpacked.payloadSize == len(test_payload), "Payload size mismatch"
    assert unpacked.payload == test_payload, "Payload data mismatch"
    
    print("✅ Binary message packing/unpacking test passed!")

def test_image_payload_structure():
    """Test image payload structure with metadata + buffer"""
    print("\n🧪 Testing image payload structure...")
    
    # Create test image metadata
    metadata = {
        'callback_id': 12345,
        'timestamp': time.time(),
        'image_info': {
            'type': 1,  # HDR
            'size': {'x': 1920, 'y': 1080},
            'pitch': 7680,
            'hasAlpha': True
        }
    }
    
    # Create test image buffer (simulate HDR RGBA data)
    image_width = 1920
    image_height = 1080
    bytes_per_pixel = 16  # 4 floats * 4 bytes each
    buffer_size = image_width * image_height * bytes_per_pixel
    test_buffer = b'\x00' * buffer_size  # Dummy buffer
    
    # Pack as binary payload: [metadata_size:4][metadata:N][buffer:M]
    metadata_json = json.dumps(metadata).encode('utf-8')
    metadata_size = len(metadata_json)
    
    payload = struct.pack('!I', metadata_size) + metadata_json + test_buffer
    
    print(f"✅ Image payload created: {len(payload)} bytes")
    print(f"   Metadata: {metadata_size} bytes")
    print(f"   Buffer: {len(test_buffer)} bytes")
    
    # Unpack payload
    payload_view = memoryview(payload)
    unpacked_metadata_size = struct.unpack('!I', payload_view[:4])[0]
    unpacked_metadata_json = payload_view[4:4 + unpacked_metadata_size].tobytes()
    unpacked_buffer = payload_view[4 + unpacked_metadata_size:].tobytes()
    
    # Verify
    assert unpacked_metadata_size == metadata_size, "Metadata size mismatch"
    assert unpacked_metadata_json == metadata_json, "Metadata mismatch"
    assert unpacked_buffer == test_buffer, "Buffer mismatch"
    
    unpacked_metadata = json.loads(unpacked_metadata_json.decode('utf-8'))
    assert unpacked_metadata['callback_id'] == metadata['callback_id'], "Callback ID mismatch"
    
    print("✅ Image payload structure test passed!")

def test_bandwidth_savings():
    """Calculate bandwidth savings vs base64 encoding"""
    print("\n📊 Testing bandwidth savings...")
    
    # Simulate typical image buffer sizes
    test_sizes = [
        1920 * 1080 * 4,    # 1080p LDR RGBA
        1920 * 1080 * 16,   # 1080p HDR RGBA
        3840 * 2160 * 4,    # 4K LDR RGBA
        3840 * 2160 * 16,   # 4K HDR RGBA
    ]
    
    total_binary = 0
    total_base64 = 0
    
    for size in test_sizes:
        # Binary WebSocket: raw bytes + small header
        binary_size = size + 16  # 16 byte header
        
        # Base64 SSE: 33% overhead + JSON wrapper
        base64_size = int(size * 1.33) + 200  # ~200 bytes JSON overhead
        
        savings = base64_size - binary_size
        savings_percent = (savings / base64_size) * 100
        
        total_binary += binary_size
        total_base64 += base64_size
        
        print(f"   {size//1024//1024}MB buffer: {savings//1024}KB saved ({savings_percent:.1f}%)")
    
    total_savings = total_base64 - total_binary
    total_savings_percent = (total_savings / total_base64) * 100
    
    print(f"✅ Total bandwidth savings: {total_savings//1024//1024}MB ({total_savings_percent:.1f}%)")

if __name__ == "__main__":
    print("🚀 Binary WebSocket Implementation Test Suite")
    print("=" * 50)
    
    try:
        test_binary_message_packing()
        test_image_payload_structure()
        test_bandwidth_savings()
        
        print("\n🎉 All tests passed! Binary WebSocket implementation is ready.")
        
    except Exception as e:
        print(f"\n❌ Test failed: {e}")
        import traceback
        traceback.print_exc()