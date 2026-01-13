#!/usr/bin/env python3
"""
Icon extractor with proper resource cleanup - calls destroy() after each icon
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
    from generated import octaneids_pb2, apiinfo_pb2, apiinfo_pb2_grpc, apiimage_pb2, apiimage_pb2_grpc
    print("✅ Modules imported")
except ImportError as e:
    print(f"❌ Import failed: {e}")
    sys.exit(1)

OCTANE_HOST = 'host.docker.internal'
OCTANE_PORT = 51022
BATCH_SIZE = 10  # Try 10 icons now with proper cleanup

def create_png(width, height, pixels):
    """Create PNG from RGBA floats"""
    png_sig = b'\x89PNG\r\n\x1a\n'
    
    def chunk(ctype, data):
        cdata = ctype + data
        crc = zlib.crc32(cdata) & 0xffffffff
        return struct.pack('>I', len(data)) + cdata + struct.pack('>I', crc)
    
    ihdr = struct.pack('>IIBBBBB', width, height, 8, 6, 0, 0, 0)
    raw = b''
    for y in range(height):
        raw += b'\x00'
        for x in range(width):
            i = (y * width + x) * 4
            r = int(max(0, min(1, pixels[i])) * 255)
            g = int(max(0, min(1, pixels[i+1])) * 255)
            b = int(max(0, min(1, pixels[i+2])) * 255)
            a = int(max(0, min(1, pixels[i+3])) * 255)
            raw += bytes([r, g, b, a])
    
    compressed = zlib.compress(raw, 9)
    return png_sig + chunk(b'IHDR', ihdr) + chunk(b'IDAT', compressed) + chunk(b'IEND', b'')

def extract_icon_with_cleanup(api_info_stub, image_stub, node_name, node_type, output_path):
    """
    Extract icon and DESTROY reference afterwards to free Octane memory
    """
    icon_ref = None
    
    try:
        # Get icon reference
        req = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
        req.nodeType = node_type
        resp = api_info_stub.nodeIconImage(req, timeout=15)
        icon_ref = resp.result
        
        if icon_ref.handle == 0:
            return "SKIP", "No icon"
        
        # Get dimensions
        w_req = apiimage_pb2.ApiImage.widthRequest()
        w_req.objectPtr.CopyFrom(icon_ref)
        width = image_stub.width(w_req, timeout=15).result
        
        h_req = apiimage_pb2.ApiImage.heightRequest()
        h_req.objectPtr.CopyFrom(icon_ref)
        height = image_stub.height(h_req, timeout=15).result
        
        if width <= 0 or height <= 0:
            return "ERROR", f"Bad dims: {width}x{height}"
        
        # Read pixels
        pixels = []
        for y in range(height):
            for x in range(width):
                p_req = apiimage_pb2.ApiImage.pixelAtRequest()
                p_req.objectPtr.CopyFrom(icon_ref)
                p_req.x = x
                p_req.y = y
                p_resp = image_stub.pixelAt(p_req, timeout=15)
                pixels.extend([p_resp.result.r, p_resp.result.g, p_resp.result.b, p_resp.result.a])
        
        # Create PNG
        png = create_png(width, height, pixels)
        output_path.parent.mkdir(parents=True, exist_ok=True)
        with open(output_path, 'wb') as f:
            f.write(png)
        
        return "SUCCESS", len(png)
        
    except Exception as e:
        return "ERROR", str(e)[:50]
        
    finally:
        # CRITICAL: Destroy icon reference to free Octane memory
        if icon_ref and icon_ref.handle != 0:
            try:
                print(f" [destroy]", end='', flush=True)
                destroy_req = apiimage_pb2.ApiImage.destroyRequest()
                destroy_req.objectPtr.CopyFrom(icon_ref)
                image_stub.destroy(destroy_req, timeout=10)
                time.sleep(0.1)  # Give Octane time to clean up
            except Exception as e:
                print(f" [destroy failed: {e}]", end='', flush=True)

def main():
    print("=" * 70)
    print(f"🎨 Icon Extractor with Resource Cleanup - {BATCH_SIZE} icons")
    print("=" * 70)
    print("\n🔑 Key improvement: Calls destroy() after each icon to free memory")
    
    # Connect
    print(f"\n🔌 Connecting to Octane...")
    channel = grpc.insecure_channel(
        f'{OCTANE_HOST}:{OCTANE_PORT}',
        options=[
            ('grpc.keepalive_time_ms', 30000),
            ('grpc.keepalive_timeout_ms', 10000),
        ]
    )
    
    try:
        grpc.channel_ready_future(channel).result(timeout=10)
        print("✅ Connected")
    except Exception as e:
        print(f"❌ Connection failed: {e}")
        sys.exit(1)
    
    api_info_stub = apiinfo_pb2_grpc.ApiInfoServiceStub(channel)
    image_stub = apiimage_pb2_grpc.ApiImageServiceStub(channel)
    
    # Get node types
    node_types = {}
    for attr in dir(octaneids_pb2):
        if attr.startswith('NT_') and not attr.startswith('NT__'):
            val = getattr(octaneids_pb2, attr)
            if isinstance(val, int) and val > 0:  # Skip NT_UNKNOWN (0)
                node_types[attr] = val
    
    print(f"📊 Total: {len(node_types)} node types")
    
    # Output
    output_dir = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'nodes'
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Check existing
    existing = set(f.stem for f in output_dir.glob('*.png'))
    to_extract = [item for item in sorted(node_types.items()) if item[0] not in existing]
    
    print(f"📂 Already: {len(existing)}")
    print(f"📋 Remaining: {len(to_extract)}")
    
    if not to_extract:
        print("\n✅ ALL DONE!")
        channel.close()
        sys.exit(0)
    
    # Extract batch
    batch = to_extract[:BATCH_SIZE]
    print(f"\n🚀 Extracting {len(batch)} icons with cleanup...")
    print()
    
    success = 0
    skipped = 0
    errors = 0
    
    for i, (name, type_id) in enumerate(batch, 1):
        print(f"[{i:2}/{len(batch)}] {name[:35]:35} ", end='', flush=True)
        
        output_path = output_dir / f'{name}.png'
        status, result = extract_icon_with_cleanup(api_info_stub, image_stub, name, type_id, output_path)
        
        if status == "SUCCESS":
            print(f" ✅ {result} bytes")
            success += 1
        elif status == "SKIP":
            print(f" ⚠️  {result}")
            skipped += 1
        else:
            print(f" ❌ {result}")
            errors += 1
        
        # Delay between icons
        time.sleep(0.5)
    
    # Summary
    print(f"\n{'=' * 70}")
    print(f"📊 BATCH COMPLETE")
    print(f"{'=' * 70}")
    print(f"   ✅ Success: {success}")
    print(f"   ⚠️  Skipped: {skipped}")
    print(f"   ❌ Errors: {errors}")
    print(f"   📂 Total: {len(existing) + success}")
    print(f"   📋 Remaining: {len(to_extract) - len(batch)}")
    
    if len(to_extract) > len(batch):
        remaining = len(to_extract) - len(batch)
        print(f"\n💡 Run again to extract next {min(BATCH_SIZE, remaining)} icons")
    else:
        print(f"\n✅ ALL ICONS EXTRACTED!")
    
    channel.close()
    print(f"\n👋 Done")

if __name__ == '__main__':
    main()
