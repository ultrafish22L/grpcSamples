#!/usr/bin/env python3
"""
Extract Octane Icons via gRPC API (Working Version)
Uses pixel-by-pixel extraction via ApiImage.pixelAt()
"""

import sys
import os
import grpc
from pathlib import Path
import struct
import zlib

sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'generated'))

try:
    from generated import octaneids_pb2, apiinfo_pb2, apiinfo_pb2_grpc
    from generated import apiimage_pb2, apiimage_pb2_grpc
except ImportError as e:
    print(f"❌ Import error: {e}")
    sys.exit(1)

OCTANE_HOST = 'host.docker.internal'
OCTANE_PORT = 51022

def create_png(width, height, pixels):
    """Create PNG file from RGBA pixel data (floats 0-1)"""
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

def extract_icon(api_info_stub, image_stub, icon_ref, output_path):
    """Extract a single icon to PNG file"""
    try:
        # Get dimensions
        width_req = apiimage_pb2.ApiImage.widthRequest()
        width_req.objectPtr.CopyFrom(icon_ref)
        width = image_stub.width(width_req, timeout=5).result
        
        height_req = apiimage_pb2.ApiImage.heightRequest()
        height_req.objectPtr.CopyFrom(icon_ref)
        height = image_stub.height(height_req, timeout=5).result
        
        # Read all pixels
        pixels = []
        for y in range(height):
            for x in range(width):
                pixel_req = apiimage_pb2.ApiImage.pixelAtRequest()
                pixel_req.objectPtr.CopyFrom(icon_ref)
                pixel_req.x = x
                pixel_req.y = y
                pixel_resp = image_stub.pixelAt(pixel_req, timeout=5)
                pixels.extend([
                    pixel_resp.result.r,
                    pixel_resp.result.g,
                    pixel_resp.result.b,
                    pixel_resp.result.a
                ])
        
        # Create and save PNG
        png_data = create_png(width, height, pixels)
        output_path.parent.mkdir(parents=True, exist_ok=True)
        with open(output_path, 'wb') as f:
            f.write(png_data)
        
        return True, len(png_data)
    except Exception as e:
        return False, str(e)

def main():
    print("=" * 60)
    print(" Octane Icon Extraction (Working Version)")
    print("=" * 60)
    
    # Connect to Octane
    print(f"\n🔌 Connecting to Octane at {OCTANE_HOST}:{OCTANE_PORT}...")
    channel = grpc.insecure_channel(f'{OCTANE_HOST}:{OCTANE_PORT}')
    try:
        grpc.channel_ready_future(channel).result(timeout=5)
        print("✅ Connected successfully")
    except Exception as e:
        print(f"❌ Connection failed: {e}")
        sys.exit(1)
    
    api_info_stub = apiinfo_pb2_grpc.ApiInfoServiceStub(channel)
    image_stub = apiimage_pb2_grpc.ApiImageServiceStub(channel)
    
    # Extract node types
    node_types = {}
    for attr_name in dir(octaneids_pb2):
        if attr_name.startswith('NT_') and not attr_name.startswith('NT__'):
            value = getattr(octaneids_pb2, attr_name)
            if isinstance(value, int):
                node_types[attr_name] = value
    
    print(f"\n📊 Found {len(node_types)} node types")
    
    # Output directory
    output_dir = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'nodes'
    
    # Extract (limit to first 10 for testing)
    test_limit = 10
    print(f"\n🎨 Extracting first {test_limit} node icons...")
    
    success_count = 0
    skip_count = 0
    error_count = 0
    
    for i, (name, type_id) in enumerate(sorted(node_types.items())[:test_limit]):
        print(f"  [{i+1}/{test_limit}] {name}...", end=' ')
        
        try:
            # Get icon
            node_request = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
            node_request.nodeType = type_id
            response = api_info_stub.nodeIconImage(node_request, timeout=10)
            icon_ref = response.result
            
            if icon_ref.handle == 0:
                print("⚠️  No icon available")
                skip_count += 1
                continue
            
            # Extract
            output_path = output_dir / f'{name}.png'
            success, result = extract_icon(api_info_stub, image_stub, icon_ref, output_path)
            
            if success:
                print(f"✅ {result} bytes")
                success_count += 1
            else:
                print(f"❌ {result}")
                error_count += 1
                
        except Exception as e:
            print(f"❌ {e}")
            error_count += 1
    
    print(f"\n📊 Results:")
    print(f"   ✅ Success: {success_count}")
    print(f"   ⚠️  Skipped: {skip_count}")
    print(f"   ❌ Errors: {error_count}")
    
    channel.close()

if __name__ == '__main__':
    main()

