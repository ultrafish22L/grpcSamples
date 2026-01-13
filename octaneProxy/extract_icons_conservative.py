#!/usr/bin/env python3
"""
Ultra-Conservative Icon Extractor
Much longer delays to prevent Octane from being overwhelmed
Strict checking of all return values
"""

import sys
import os
import grpc
from pathlib import Path
import struct
import zlib
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'generated'))

try:
    from generated import (
        octaneids_pb2,
        apiinfo_pb2,
        apiinfo_pb2_grpc,
        apiimage_pb2,
        apiimage_pb2_grpc
    )
    print("✅ Successfully imported protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import protobuf modules: {e}")
    sys.exit(1)

OCTANE_HOST = 'host.docker.internal'
OCTANE_PORT = 51022

# VERY conservative delays
DELAY_BETWEEN_ICONS = 0.5       # 500ms between icons
DELAY_BETWEEN_API_CALLS = 0.1   # 100ms between API calls
DELAY_PER_ROW = 0.05            # 50ms per row of pixels
DELAY_AFTER_ERROR = 5.0         # 5 seconds after errors

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
        raw_data += b'\x00'  # PNG filter type
        for x in range(width):
            idx = (y * width + x) * 4
            r = max(0.0, min(1.0, pixels[idx]))
            g = max(0.0, min(1.0, pixels[idx+1]))
            b = max(0.0, min(1.0, pixels[idx+2]))
            a = max(0.0, min(1.0, pixels[idx+3]))
            raw_data += bytes([int(r * 255), int(g * 255), int(b * 255), int(a * 255)])
    
    compressed = zlib.compress(raw_data, 9)
    
    png_data = png_signature
    png_data += make_chunk(b'IHDR', ihdr)
    png_data += make_chunk(b'IDAT', compressed)
    png_data += make_chunk(b'IEND', b'')
    
    return png_data

def extract_icon_pixels(image_stub, icon_ref, output_path, node_name):
    """
    Extract icon pixel-by-pixel with extensive checking and delays
    """
    try:
        # Get dimensions with checking
        print(f"      Getting dimensions...", end=' ', flush=True)
        
        width_req = apiimage_pb2.ApiImage.widthRequest()
        width_req.objectPtr.CopyFrom(icon_ref)
        width_resp = image_stub.width(width_req, timeout=15)
        
        # Check if response is valid
        if not hasattr(width_resp, 'result'):
            return False, "Invalid width response"
        
        width = width_resp.result
        time.sleep(DELAY_BETWEEN_API_CALLS)
        
        height_req = apiimage_pb2.ApiImage.heightRequest()
        height_req.objectPtr.CopyFrom(icon_ref)
        height_resp = image_stub.height(height_req, timeout=15)
        
        # Check if response is valid
        if not hasattr(height_resp, 'result'):
            return False, "Invalid height response"
        
        height = height_resp.result
        time.sleep(DELAY_BETWEEN_API_CALLS)
        
        print(f"{width}x{height}", flush=True)
        
        # Validate dimensions
        if width <= 0 or height <= 0:
            return False, f"Invalid dimensions: {width}x{height}"
        
        if width > 256 or height > 256:
            return False, f"Dimensions too large: {width}x{height}"
        
        # Read pixels row by row with progress
        print(f"      Reading pixels: ", end='', flush=True)
        pixels = []
        total_pixels = width * height
        
        for y in range(height):
            for x in range(width):
                pixel_req = apiimage_pb2.ApiImage.pixelAtRequest()
                pixel_req.objectPtr.CopyFrom(icon_ref)
                pixel_req.x = x
                pixel_req.y = y
                
                pixel_resp = image_stub.pixelAt(pixel_req, timeout=15)
                
                # Check if response is valid
                if not hasattr(pixel_resp, 'result'):
                    return False, f"Invalid pixel response at ({x},{y})"
                
                pixel = pixel_resp.result
                
                # Validate pixel data
                if not hasattr(pixel, 'r') or not hasattr(pixel, 'g') or not hasattr(pixel, 'b') or not hasattr(pixel, 'a'):
                    return False, f"Invalid pixel data at ({x},{y})"
                
                pixels.extend([pixel.r, pixel.g, pixel.b, pixel.a])
            
            # Progress indicator every row
            if (y + 1) % 4 == 0 or y == height - 1:
                print(f"{len(pixels)//4}/{total_pixels}", end=' ', flush=True)
            
            # Delay after each row
            time.sleep(DELAY_PER_ROW)
        
        print("✅", flush=True)
        
        # Validate total pixels
        expected_count = width * height * 4
        if len(pixels) != expected_count:
            return False, f"Pixel count mismatch: got {len(pixels)}, expected {expected_count}"
        
        # Create PNG
        print(f"      Creating PNG...", end=' ', flush=True)
        png_data = create_png(width, height, pixels)
        
        if len(png_data) == 0:
            return False, "PNG creation failed"
        
        print(f"{len(png_data)} bytes", flush=True)
        
        # Save to file
        output_path.parent.mkdir(parents=True, exist_ok=True)
        with open(output_path, 'wb') as f:
            f.write(png_data)
        
        # Verify file was created
        if not output_path.exists():
            return False, "File not created"
        
        file_size = output_path.stat().st_size
        if file_size == 0:
            return False, "File is empty"
        
        return True, file_size
        
    except grpc.RpcError as e:
        return False, f"gRPC {e.code()}: {e.details()}"
    except Exception as e:
        return False, f"Exception: {str(e)}"

def main():
    print("=" * 70)
    print("🎨 Octane Icon Extractor - ULTRA-CONSERVATIVE MODE")
    print("=" * 70)
    print("\nFeatures:")
    print("  • Extensive return value checking")
    print("  • Very long delays (500ms between icons)")
    print("  • Row-by-row progress display")
    print("  • Resume capability")
    
    # Connect to Octane with keepalive
    print(f"\n🔌 Connecting to Octane at {OCTANE_HOST}:{OCTANE_PORT}...")
    channel = grpc.insecure_channel(
        f'{OCTANE_HOST}:{OCTANE_PORT}',
        options=[
            ('grpc.max_send_message_length', 50 * 1024 * 1024),
            ('grpc.max_receive_message_length', 50 * 1024 * 1024),
            ('grpc.keepalive_time_ms', 30000),
            ('grpc.keepalive_timeout_ms', 10000),
            ('grpc.http2.max_pings_without_data', 0),
            ('grpc.keepalive_permit_without_calls', 1),
        ]
    )
    
    try:
        grpc.channel_ready_future(channel).result(timeout=10)
        print("✅ Connected successfully")
    except Exception as e:
        print(f"❌ Connection failed: {e}")
        sys.exit(1)
    
    # Create service stubs
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
    
    # Output directory
    output_dir = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'nodes'
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Check existing
    existing_icons = set()
    for icon_file in output_dir.glob('*.png'):
        existing_icons.add(icon_file.stem)
    
    if existing_icons:
        print(f"📂 Found {len(existing_icons)} existing icons (will skip)")
    
    # Start extraction
    total = len(node_types)
    print(f"\n🚀 Starting ULTRA-CONSERVATIVE extraction...")
    print(f"⏱️  Icon delay: {DELAY_BETWEEN_ICONS}s")
    print(f"⏱️  API delay: {DELAY_BETWEEN_API_CALLS}s")
    print(f"⏱️  Row delay: {DELAY_PER_ROW}s")
    print(f"💾 Output: {output_dir}")
    print()
    
    success_count = 0
    skip_count = 0
    error_count = 0
    already_exists = 0
    
    start_time = time.time()
    
    try:
        for i, (name, type_id) in enumerate(sorted(node_types.items()), 1):
            # Skip existing
            if name in existing_icons:
                already_exists += 1
                continue
            
            # Progress
            elapsed = time.time() - start_time
            rate = (i - already_exists) / elapsed if elapsed > 0 else 0
            print(f"[{i:3}/{total}] {name[:35]:35} ", end='', flush=True)
            
            try:
                # Get icon reference
                icon_request = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
                icon_request.nodeType = type_id
                response = api_info_stub.nodeIconImage(icon_request, timeout=15)
                
                # Check response validity
                if not hasattr(response, 'result'):
                    print(f"❌ Invalid response")
                    error_count += 1
                    time.sleep(DELAY_AFTER_ERROR)
                    continue
                
                icon_ref = response.result
                
                # Check if icon exists
                if not hasattr(icon_ref, 'handle'):
                    print(f"❌ No handle in response")
                    error_count += 1
                    time.sleep(DELAY_AFTER_ERROR)
                    continue
                
                if icon_ref.handle == 0:
                    print(f"⚠️  No icon")
                    skip_count += 1
                    time.sleep(DELAY_BETWEEN_ICONS / 2)
                    continue
                
                print(f"(handle={icon_ref.handle})")
                time.sleep(DELAY_BETWEEN_API_CALLS)
                
                # Extract
                output_path = output_dir / f'{name}.png'
                success, result = extract_icon_pixels(image_stub, icon_ref, output_path, name)
                
                if success:
                    print(f"      ✅ Saved: {result} bytes")
                    success_count += 1
                else:
                    print(f"      ❌ Failed: {result}")
                    error_count += 1
                    time.sleep(DELAY_AFTER_ERROR)
                
            except grpc.RpcError as e:
                error_msg = f"gRPC {e.code()}"
                
                # Check for fatal errors
                if e.code() in [grpc.StatusCode.UNAVAILABLE, grpc.StatusCode.DEADLINE_EXCEEDED]:
                    print(f"\n\n⚠️  CONNECTION LOST")
                    print(f"    Error: {e.details()}")
                    raise ConnectionError(error_msg)
                
                print(f"❌ {error_msg}")
                error_count += 1
                time.sleep(DELAY_AFTER_ERROR)
                
            except Exception as e:
                print(f"❌ {str(e)[:50]}")
                error_count += 1
                time.sleep(DELAY_AFTER_ERROR)
            
            # Delay between icons
            if i < total:
                time.sleep(DELAY_BETWEEN_ICONS)
            
            # Status every 10 icons
            if (i - already_exists) % 10 == 0:
                print(f"    Status: ✅{success_count} ⚠️{skip_count} ❌{error_count} | Rate: {rate:.2f}/s")
        
    except ConnectionError:
        print(f"\n📊 Connection Lost - Partial Results:")
        print(f"    ✅ Success: {success_count}")
        print(f"    ⚠️  Skipped: {skip_count}")
        print(f"    ❌ Errors: {error_count}")
        print(f"    📂 Already existed: {already_exists}")
        print(f"\n💡 Run again to resume!")
        channel.close()
        sys.exit(1)
    except KeyboardInterrupt:
        print(f"\n\n⚠️  Interrupted by user")
        print(f"    ✅ Success: {success_count}")
        print(f"    ⚠️  Skipped: {skip_count}")
        print(f"    ❌ Errors: {error_count}")
        channel.close()
        sys.exit(130)
    
    # Success
    elapsed = time.time() - start_time
    
    print(f"\n{'=' * 70}")
    print(f"📊 EXTRACTION COMPLETE")
    print(f"{'=' * 70}")
    print(f"   ✅ Success: {success_count}")
    print(f"   ⚠️  Skipped: {skip_count}")
    print(f"   ❌ Errors: {error_count}")
    print(f"   📂 Already existed: {already_exists}")
    print(f"   ⏱️  Time: {elapsed/60:.1f} minutes")
    if elapsed > 0:
        print(f"   📈 Rate: {(success_count + skip_count)/elapsed:.2f} icons/sec")
    print(f"\n💾 Icons: {output_dir}")
    
    channel.close()

if __name__ == '__main__':
    main()
