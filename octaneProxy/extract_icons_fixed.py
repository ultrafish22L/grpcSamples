#!/usr/bin/env python3
"""
Fixed Octane Icon Extractor
Hybrid approach: tries direct save first, falls back to pixel-by-pixel
With robust error handling and crash prevention
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
        apiimage_pb2_grpc,
        apiimagebuffer_pb2,
        apiimagebuffer_pb2_grpc
    )
    print("✅ Successfully imported protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import protobuf modules: {e}")
    sys.exit(1)

OCTANE_HOST = 'host.docker.internal'
OCTANE_PORT = 51022

# Conservative delays to prevent overwhelming Octane
DELAY_BETWEEN_ICONS = 0.15      # 150ms between icon extractions
DELAY_BETWEEN_API_CALLS = 0.05  # 50ms between API calls
DELAY_AFTER_ERROR = 2.0         # 2 seconds after errors
MAX_RETRIES = 2                 # Retry failed icons once

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
        raw_data += b'\x00'  # PNG filter type (no filter)
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

def extract_icon_via_buffer_save(channel, icon_ref, output_path):
    """
    Try Method 1: Use ApiImageBuffer.save() directly
    This might work if the icon_ref actually points to an ImageBuffer
    """
    try:
        buffer_stub = apiimagebuffer_pb2_grpc.ApiImageBufferServiceStub(channel)
        
        # Create save request properly
        save_request = apiimagebuffer_pb2.ApiImageBuffer.saveRequest()
        save_request.objectPtr.CopyFrom(icon_ref)
        save_request.fileName = str(output_path.absolute())
        # metaData field is optional, leave it unset
        
        # Call save with timeout
        response = buffer_stub.save(save_request, timeout=10)
        
        if response.result:
            # Verify file was created
            if output_path.exists() and output_path.stat().st_size > 0:
                return True, output_path.stat().st_size
        
        return False, "Save returned false or file not created"
        
    except grpc.RpcError as e:
        if e.code() == grpc.StatusCode.INVALID_ARGUMENT:
            # Type mismatch - icon_ref is ApiImage not ApiImageBuffer
            return False, "TYPE_MISMATCH"
        elif e.code() == grpc.StatusCode.NOT_FOUND:
            return False, "INVALID_REFERENCE"
        else:
            return False, f"gRPC error: {e.code()}"
    except Exception as e:
        return False, str(e)

def extract_icon_via_pixels(image_stub, icon_ref, output_path):
    """
    Method 2: Pixel-by-pixel extraction (fallback)
    More reliable but slower
    """
    try:
        # Get dimensions
        width_req = apiimage_pb2.ApiImage.widthRequest()
        width_req.objectPtr.CopyFrom(icon_ref)
        width = image_stub.width(width_req, timeout=10).result
        time.sleep(DELAY_BETWEEN_API_CALLS)
        
        height_req = apiimage_pb2.ApiImage.heightRequest()
        height_req.objectPtr.CopyFrom(icon_ref)
        height = image_stub.height(height_req, timeout=10).result
        time.sleep(DELAY_BETWEEN_API_CALLS)
        
        # Sanity check dimensions
        if width <= 0 or height <= 0 or width > 256 or height > 256:
            return False, f"Invalid dimensions: {width}x{height}"
        
        # Read pixels with batching and delays
        pixels = []
        for y in range(height):
            for x in range(width):
                pixel_req = apiimage_pb2.ApiImage.pixelAtRequest()
                pixel_req.objectPtr.CopyFrom(icon_ref)
                pixel_req.x = x
                pixel_req.y = y
                
                pixel_resp = image_stub.pixelAt(pixel_req, timeout=10)
                pixels.extend([
                    pixel_resp.result.r,
                    pixel_resp.result.g,
                    pixel_resp.result.b,
                    pixel_resp.result.a
                ])
                
                # Small delay every row
                if x == width - 1:
                    time.sleep(DELAY_BETWEEN_API_CALLS / 2)
        
        # Create PNG
        png_data = create_png(width, height, pixels)
        output_path.parent.mkdir(parents=True, exist_ok=True)
        
        with open(output_path, 'wb') as f:
            f.write(png_data)
        
        return True, len(png_data)
        
    except Exception as e:
        return False, str(e)

def extract_single_icon(channel, api_info_stub, image_stub, node_name, node_type, output_path, attempt=1):
    """
    Extract a single icon with hybrid approach and retry logic
    """
    try:
        # Get icon reference
        icon_request = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
        icon_request.nodeType = node_type
        response = api_info_stub.nodeIconImage(icon_request, timeout=15)
        icon_ref = response.result
        
        time.sleep(DELAY_BETWEEN_API_CALLS)
        
        # Check if icon exists
        if icon_ref.handle == 0:
            return 'SKIP', "No icon available"
        
        # Try Method 1: Direct buffer save (fast)
        success, result = extract_icon_via_buffer_save(channel, icon_ref, output_path)
        
        if success:
            return 'SUCCESS', result
        
        # If type mismatch, try Method 2: Pixel-by-pixel (slower but reliable)
        if result == "TYPE_MISMATCH":
            time.sleep(DELAY_BETWEEN_API_CALLS)
            success, result = extract_icon_via_pixels(image_stub, icon_ref, output_path)
            
            if success:
                return 'SUCCESS', result
        
        return 'ERROR', result
        
    except grpc.RpcError as e:
        error_msg = f"gRPC {e.code()}: {e.details()}"
        
        # Check for connection errors
        if e.code() in [grpc.StatusCode.UNAVAILABLE, grpc.StatusCode.DEADLINE_EXCEEDED]:
            return 'CONNECTION_LOST', error_msg
        
        # Retry on transient errors
        if attempt < MAX_RETRIES and e.code() in [grpc.StatusCode.UNKNOWN, grpc.StatusCode.INTERNAL]:
            time.sleep(DELAY_AFTER_ERROR)
            return extract_single_icon(channel, api_info_stub, image_stub, node_name, node_type, output_path, attempt + 1)
        
        return 'ERROR', error_msg
        
    except Exception as e:
        return 'ERROR', str(e)

def main():
    print("=" * 70)
    print("🎨 Octane Icon Extractor - FIXED VERSION")
    print("=" * 70)
    print("\nFeatures:")
    print("  • Hybrid extraction (fast + fallback)")
    print("  • Automatic retry on transient errors")
    print("  • Resume capability")
    print("  • Connection loss detection")
    print("  • Conservative delays to prevent crashes")
    
    # Connect to Octane
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
        print(f"\n💡 Make sure:")
        print(f"   1. Octane is running")
        print(f"   2. LiveLink is enabled (Help → LiveLink)")
        print(f"   3. Port 51022 is accessible")
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
    
    # Setup output directory
    output_dir = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'nodes'
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Check for existing icons
    existing_icons = set()
    for icon_file in output_dir.glob('*.png'):
        existing_icons.add(icon_file.stem)
    
    if existing_icons:
        print(f"📂 Found {len(existing_icons)} existing icons (will skip)")
    
    # Start extraction
    total = len(node_types)
    print(f"\n🚀 Starting extraction of {total} node types...")
    print(f"⏱️  Delay between icons: {DELAY_BETWEEN_ICONS}s")
    print(f"💾 Output directory: {output_dir}")
    print()
    
    success_count = 0
    skip_count = 0
    error_count = 0
    already_exists = 0
    
    start_time = time.time()
    
    try:
        for i, (name, type_id) in enumerate(sorted(node_types.items()), 1):
            # Skip if already extracted
            if name in existing_icons:
                already_exists += 1
                if i % 50 == 0:
                    elapsed = time.time() - start_time
                    rate = i / elapsed if elapsed > 0 else 0
                    eta = (total - i) / rate if rate > 0 else 0
                    print(f"  [{i:3}/{total}] Progress: {i/total*100:5.1f}% | "
                          f"✅{success_count} ⚠️{skip_count} ❌{error_count} 📂{already_exists} | "
                          f"Rate: {rate:.1f}/s | ETA: {eta/60:.1f}m")
                continue
            
            # Progress update
            if i % 25 == 0 or i == 1:
                elapsed = time.time() - start_time
                rate = i / elapsed if elapsed > 0 else 0
                eta = (total - i) / rate if rate > 0 else 0
                print(f"  [{i:3}/{total}] {name[:40]:40} | "
                      f"✅{success_count} ⚠️{skip_count} ❌{error_count} | "
                      f"Rate: {rate:.1f}/s | ETA: {eta/60:.1f}m")
            
            # Extract icon
            output_path = output_dir / f'{name}.png'
            status, result = extract_single_icon(channel, api_info_stub, image_stub, name, type_id, output_path)
            
            if status == 'SUCCESS':
                success_count += 1
            elif status == 'SKIP':
                skip_count += 1
            elif status == 'CONNECTION_LOST':
                print(f"\n⚠️  CONNECTION LOST at icon {i}/{total}")
                print(f"    Node: {name}")
                print(f"    Error: {result}")
                raise ConnectionError(result)
            else:  # ERROR
                error_count += 1
                if error_count <= 5:  # Only show first 5 errors
                    print(f"      ❌ Error on {name}: {result[:80]}")
                time.sleep(DELAY_AFTER_ERROR)
            
            # Delay between icons
            if i < total:
                time.sleep(DELAY_BETWEEN_ICONS)
        
    except ConnectionError:
        print(f"\n📊 Partial Results (connection lost):")
        print(f"    ✅ Success: {success_count}")
        print(f"    ⚠️  Skipped: {skip_count}")
        print(f"    ❌ Errors: {error_count}")
        print(f"    📂 Already existed: {already_exists}")
        print(f"\n💡 To resume: Run this script again!")
        print(f"    It will skip the {success_count + already_exists} icons already extracted.")
        channel.close()
        sys.exit(1)
    except KeyboardInterrupt:
        print(f"\n\n⚠️  Interrupted by user at icon {i}/{total}")
        print(f"\n📊 Partial Results:")
        print(f"    ✅ Success: {success_count}")
        print(f"    ⚠️  Skipped: {skip_count}")
        print(f"    ❌ Errors: {error_count}")
        print(f"    📂 Already existed: {already_exists}")
        print(f"\n💡 Run again to resume from where you left off")
        channel.close()
        sys.exit(130)
    
    # Success summary
    elapsed = time.time() - start_time
    
    print(f"\n{'=' * 70}")
    print(f"📊 EXTRACTION COMPLETE")
    print(f"{'=' * 70}")
    print(f"   ✅ Success: {success_count}")
    print(f"   ⚠️  Skipped (no icon): {skip_count}")
    print(f"   ❌ Errors: {error_count}")
    print(f"   📂 Already existed: {already_exists}")
    print(f"   ⏱️  Total time: {elapsed/60:.1f} minutes")
    if elapsed > 0:
        print(f"   📈 Average rate: {total/elapsed:.2f} icons/second")
    print(f"\n💾 Icons saved to: {output_dir}")
    print(f"\n✨ Icons are now ready for use in octaneWebR!")
    
    channel.close()

if __name__ == '__main__':
    main()
