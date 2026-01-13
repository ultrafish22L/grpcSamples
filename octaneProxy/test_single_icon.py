#!/usr/bin/env python3
"""Test extracting a SINGLE icon with detailed logging"""

import sys
import os
import grpc
from pathlib import Path
import struct
import zlib
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'generated'))

from generated import octaneids_pb2, apiinfo_pb2, apiinfo_pb2_grpc
from generated import apiimage_pb2, apiimage_pb2_grpc

OCTANE_HOST = 'host.docker.internal'
OCTANE_PORT = 51022

def create_png(width, height, pixels):
    """Create PNG file from RGBA pixel data"""
    png_signature = b'\x89PNG\r\n\x1a\n'
    
    def make_chunk(chunk_type, data):
        chunk_data = chunk_type + data
        crc = zlib.crc32(chunk_data) & 0xffffffff
        return struct.pack('>I', len(data)) + chunk_data + struct.pack('>I', crc)
    
    ihdr = struct.pack('>IIBBBBB', width, height, 8, 6, 0, 0, 0)
    
    raw_data = b''
    for y in range(height):
        raw_data += b'\x00'
        for x in range(width):
            idx = (y * width + x) * 4
            r = max(0, min(1, pixels[idx]))
            g = max(0, min(1, pixels[idx+1]))
            b = max(0, min(1, pixels[idx+2]))
            a = max(0, min(1, pixels[idx+3]))
            raw_data += bytes([int(r * 255), int(g * 255), int(b * 255), int(a * 255)])
    
    compressed = zlib.compress(raw_data, 9)
    
    png_data = png_signature
    png_data += make_chunk(b'IHDR', ihdr)
    png_data += make_chunk(b'IDAT', compressed)
    png_data += make_chunk(b'IEND', b'')
    
    return png_data

def main():
    print("=" * 70)
    print(" 🧪 Test Single Icon Extraction - DETAILED LOGGING")
    print("=" * 70)
    
    # Connect
    print(f"\n🔌 Connecting to Octane at {OCTANE_HOST}:{OCTANE_PORT}...")
    channel = grpc.insecure_channel(
        f'{OCTANE_HOST}:{OCTANE_PORT}',
        options=[
            ('grpc.keepalive_time_ms', 30000),
            ('grpc.keepalive_timeout_ms', 10000),
        ]
    )
    
    try:
        grpc.channel_ready_future(channel).result(timeout=10)
        print("✅ Connected successfully")
    except Exception as e:
        print(f"❌ Connection failed: {e}")
        sys.exit(1)
    
    api_info_stub = apiinfo_pb2_grpc.ApiInfoServiceStub(channel)
    image_stub = apiimage_pb2_grpc.ApiImageServiceStub(channel)
    
    # Test with NT_MAT_DIFFUSE
    node_type = octaneids_pb2.NT_MAT_DIFFUSE
    print(f"\n🎯 Testing with NT_MAT_DIFFUSE (type={node_type})")
    
    try:
        # Step 1: Get icon reference
        print(f"\n1️⃣ Getting icon reference...")
        node_request = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
        node_request.nodeType = node_type
        response = api_info_stub.nodeIconImage(node_request, timeout=15)
        icon_ref = response.result
        print(f"   ✅ Got icon ref: handle={icon_ref.handle}, type={icon_ref.type}")
        
        if icon_ref.handle == 0:
            print(f"   ⚠️  No icon available for this node type")
            sys.exit(0)
        
        time.sleep(0.1)
        
        # Step 2: Get dimensions
        print(f"\n2️⃣ Getting dimensions...")
        
        width_req = apiimage_pb2.ApiImage.widthRequest()
        width_req.objectPtr.CopyFrom(icon_ref)
        width = image_stub.width(width_req, timeout=15).result
        print(f"   ✅ Width: {width}")
        
        time.sleep(0.1)
        
        height_req = apiimage_pb2.ApiImage.heightRequest()
        height_req.objectPtr.CopyFrom(icon_ref)
        height = image_stub.height(height_req, timeout=15).result
        print(f"   ✅ Height: {height}")
        
        time.sleep(0.1)
        
        # Step 3: Read pixels
        print(f"\n3️⃣ Reading {width}x{height} = {width*height} pixels...")
        pixels = []
        
        for y in range(height):
            print(f"   Row {y+1}/{height}...", end=' ')
            for x in range(width):
                pixel_req = apiimage_pb2.ApiImage.pixelAtRequest()
                pixel_req.objectPtr.CopyFrom(icon_ref)
                pixel_req.x = x
                pixel_req.y = y
                
                try:
                    pixel_resp = image_stub.pixelAt(pixel_req, timeout=15)
                    pixels.extend([
                        pixel_resp.result.r,
                        pixel_resp.result.g,
                        pixel_resp.result.b,
                        pixel_resp.result.a
                    ])
                except Exception as e:
                    print(f"\n   ❌ Error at pixel ({x}, {y}): {e}")
                    raise
            
            print(f"✅")
            time.sleep(0.05)  # Small delay after each row
        
        print(f"   ✅ Read all {len(pixels)//4} pixels")
        
        # Step 4: Create PNG
        print(f"\n4️⃣ Creating PNG...")
        png_data = create_png(width, height, pixels)
        print(f"   ✅ PNG created: {len(png_data)} bytes")
        
        # Step 5: Save
        output_dir = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'test'
        output_dir.mkdir(parents=True, exist_ok=True)
        output_file = output_dir / 'TEST_NT_MAT_DIFFUSE.png'
        
        with open(output_file, 'wb') as f:
            f.write(png_data)
        print(f"   ✅ Saved to: {output_file}")
        
        print(f"\n{'=' * 70}")
        print(f"🎉 SUCCESS! Icon extracted successfully")
        print(f"{'=' * 70}")
        
    except Exception as e:
        print(f"\n❌ FAILED: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)
    finally:
        channel.close()
        print(f"\n🔌 Channel closed")

if __name__ == '__main__':
    main()

