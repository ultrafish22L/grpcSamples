#!/usr/bin/env python3
"""
STANDALONE Octane Icon Extractor
Run this directly on your local machine where Octane is running
"""

import sys
import os
import grpc
from pathlib import Path
import struct
import zlib
import time

# Configuration
OCTANE_HOST = 'localhost'  # Change to 'host.docker.internal' if running in Docker
OCTANE_PORT = 51022
DELAY_BETWEEN_ICONS = 0.05  # 50ms delay
OUTPUT_DIR = Path.home() / 'Desktop' / 'octane_icons' / 'nodes'  # Save to Desktop

# Add generated protobuf path
script_dir = Path(__file__).parent
sys.path.insert(0, str(script_dir / 'generated'))

try:
    from generated import octaneids_pb2, apiinfo_pb2, apiinfo_pb2_grpc
    from generated import apiimage_pb2, apiimage_pb2_grpc
    print("✅ Protobuf modules loaded")
except ImportError as e:
    print(f"❌ Import error: {e}")
    print(f"\n⚠️  Make sure you run this from: {script_dir}")
    print(f"    And that 'generated/' folder exists with protobuf files")
    sys.exit(1)

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

def extract_icon(api_info_stub, image_stub, icon_ref):
    """Extract icon pixel data"""
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
    
    return create_png(width, height, pixels)

def main():
    print("=" * 70)
    print(" 🎨 Octane Icon Extractor - STANDALONE VERSION")
    print("=" * 70)
    print(f"\n📍 Configuration:")
    print(f"   Host: {OCTANE_HOST}:{OCTANE_PORT}")
    print(f"   Output: {OUTPUT_DIR}")
    print(f"   Delay: {DELAY_BETWEEN_ICONS}s between icons")
    
    # Create output directory
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    print(f"\n✅ Output directory ready")
    
    # Connect to Octane
    print(f"\n🔌 Connecting to Octane...")
    channel = grpc.insecure_channel(f'{OCTANE_HOST}:{OCTANE_PORT}')
    try:
        grpc.channel_ready_future(channel).result(timeout=10)
        print("✅ Connected successfully!")
    except Exception as e:
        print(f"❌ Connection failed: {e}")
        print(f"\n📋 Troubleshooting:")
        print(f"   1. Is Octane running?")
        print(f"   2. Is LiveLink enabled? (Help → LiveLink menu)")
        print(f"   3. Check the port in Octane console")
        sys.exit(1)
    
    api_info_stub = apiinfo_pb2_grpc.ApiInfoServiceStub(channel)
    image_stub = apiimage_pb2_grpc.ApiImageServiceStub(channel)
    
    # Get all node types
    node_types = {}
    for attr_name in dir(octaneids_pb2):
        if attr_name.startswith('NT_') and not attr_name.startswith('NT__'):
            value = getattr(octaneids_pb2, attr_name)
            if isinstance(value, int):
                node_types[attr_name] = value
    
    print(f"\n📊 Found {len(node_types)} node types")
    
    # Check existing icons
    existing = set(f.stem for f in OUTPUT_DIR.glob('*.png'))
    if existing:
        print(f"📂 Found {len(existing)} existing icons (will skip)")
    
    # Extract
    total = len(node_types)
    print(f"\n🚀 Starting extraction...")
    print()
    
    success = skip = error = exists = 0
    start_time = time.time()
    
    for i, (name, type_id) in enumerate(sorted(node_types.items()), 1):
        # Skip if exists
        if name in existing:
            exists += 1
            if i % 100 == 0:
                elapsed = time.time() - start_time
                rate = i / elapsed
                eta = (total - i) / rate
                print(f"  [{i:4}/{total}] {i/total*100:5.1f}% | "
                      f"✅{success} ⚠️{skip} ❌{error} 📂{exists} | "
                      f"{rate:.1f}/s | ETA {eta/60:.0f}m")
            continue
        
        # Progress
        if i % 10 == 0 or i == 1:
            elapsed = time.time() - start_time
            rate = i / elapsed if elapsed > 0 else 0
            eta = (total - i) / rate if rate > 0 else 0
            print(f"  [{i:4}/{total}] {name[:45]:45} | "
                  f"✅{success:3} ⚠️{skip:3} ❌{error:2} | "
                  f"{rate:.1f}/s | ETA {eta/60:.0f}m")
        
        try:
            # Get icon
            req = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
            req.nodeType = type_id
            resp = api_info_stub.nodeIconImage(req, timeout=10)
            
            if resp.result.handle == 0:
                skip += 1
                continue
            
            # Extract and save
            png_data = extract_icon(api_info_stub, image_stub, resp.result)
            output_file = OUTPUT_DIR / f'{name}.png'
            with open(output_file, 'wb') as f:
                f.write(png_data)
            success += 1
            
        except Exception as e:
            error += 1
            err_str = str(e)
            
            if 'UNAVAILABLE' in err_str or 'Socket closed' in err_str:
                print(f"\n⚠️  CONNECTION LOST at {i}/{total}")
                print(f"    ✅ Extracted: {success} icons")
                print(f"    💡 Run script again to resume!")
                break
            
            if error <= 3:  # Only print first 3 errors
                print(f"      ❌ {name}: {err_str[:60]}")
        
        time.sleep(DELAY_BETWEEN_ICONS)
    
    elapsed = time.time() - start_time
    
    print(f"\n{'=' * 70}")
    print(f"📊 RESULTS")
    print(f"{'=' * 70}")
    print(f"   ✅ Extracted: {success}")
    print(f"   ⚠️  No icon: {skip}")
    print(f"   ❌ Errors: {error}")
    print(f"   📂 Already had: {exists}")
    print(f"   ⏱️  Time: {elapsed/60:.1f} minutes")
    print(f"   📈 Rate: {(success+skip+error)/elapsed:.1f} icons/sec")
    print(f"\n💾 Icons saved to: {OUTPUT_DIR}")
    
    channel.close()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n⚠️  Interrupted by user")
        print("💡 Run again to resume from where you left off")

