#!/usr/bin/env python3
"""
Batch Icon Extractor - Extracts 5 icons then exits
Run multiple times to get all icons without crashing Octane
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
BATCH_SIZE = 5  # Extract only 5 icons per run
DELAY_BETWEEN_ICONS = 1.0  # 1 second between icons

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
    png = png_sig + chunk(b'IHDR', ihdr) + chunk(b'IDAT', compressed) + chunk(b'IEND', b'')
    return png

def extract_icon(image_stub, icon_ref, output_path):
    """Extract single icon pixel-by-pixel"""
    try:
        # Get dimensions
        w_req = apiimage_pb2.ApiImage.widthRequest()
        w_req.objectPtr.CopyFrom(icon_ref)
        width = image_stub.width(w_req, timeout=15).result
        
        h_req = apiimage_pb2.ApiImage.heightRequest()
        h_req.objectPtr.CopyFrom(icon_ref)
        height = image_stub.height(h_req, timeout=15).result
        
        if width <= 0 or height <= 0 or width > 256 or height > 256:
            return False, f"Bad dimensions: {width}x{height}"
        
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
            
            # Tiny delay every 4 rows
            if (y + 1) % 4 == 0:
                time.sleep(0.02)
        
        # Create PNG
        png = create_png(width, height, pixels)
        output_path.parent.mkdir(parents=True, exist_ok=True)
        with open(output_path, 'wb') as f:
            f.write(png)
        
        return True, len(png)
        
    except Exception as e:
        return False, str(e)[:50]

def main():
    print("=" * 70)
    print(f"🎨 Batch Icon Extractor - {BATCH_SIZE} icons per run")
    print("=" * 70)
    
    # Connect
    print(f"\n🔌 Connecting to Octane...")
    channel = grpc.insecure_channel(f'{OCTANE_HOST}:{OCTANE_PORT}')
    
    try:
        grpc.channel_ready_future(channel).result(timeout=10)
        print("✅ Connected")
    except Exception as e:
        print(f"❌ Connection failed: {e}")
        print("\n💡 Make sure Octane is running with LiveLink enabled")
        sys.exit(1)
    
    api_info_stub = apiinfo_pb2_grpc.ApiInfoServiceStub(channel)
    image_stub = apiimage_pb2_grpc.ApiImageServiceStub(channel)
    
    # Get node types
    node_types = {}
    for attr in dir(octaneids_pb2):
        if attr.startswith('NT_') and not attr.startswith('NT__'):
            val = getattr(octaneids_pb2, attr)
            if isinstance(val, int):
                node_types[attr] = val
    
    print(f"📊 Total node types: {len(node_types)}")
    
    # Output directory
    output_dir = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'nodes'
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Find what's already extracted
    existing = set(f.stem for f in output_dir.glob('*.png'))
    to_extract = [item for item in sorted(node_types.items()) if item[0] not in existing]
    
    print(f"📂 Already extracted: {len(existing)}")
    print(f"📋 Remaining: {len(to_extract)}")
    
    if not to_extract:
        print("\n✅ ALL ICONS EXTRACTED!")
        channel.close()
        sys.exit(0)
    
    # Extract batch
    batch = to_extract[:BATCH_SIZE]
    print(f"\n🚀 Extracting batch of {len(batch)} icons...")
    print()
    
    success = 0
    skipped = 0
    errors = 0
    
    for i, (name, type_id) in enumerate(batch, 1):
        print(f"[{i}/{len(batch)}] {name[:40]:40} ", end='', flush=True)
        
        try:
            # Get icon
            req = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
            req.nodeType = type_id
            resp = api_info_stub.nodeIconImage(req, timeout=15)
            icon_ref = resp.result
            
            if icon_ref.handle == 0:
                print("⚠️  No icon")
                skipped += 1
            else:
                # Extract
                output_path = output_dir / f'{name}.png'
                ok, result = extract_icon(image_stub, icon_ref, output_path)
                
                if ok:
                    print(f"✅ {result:5} bytes")
                    success += 1
                else:
                    print(f"❌ {result}")
                    errors += 1
            
            # Delay between icons
            if i < len(batch):
                time.sleep(DELAY_BETWEEN_ICONS)
                
        except Exception as e:
            print(f"❌ {str(e)[:40]}")
            errors += 1
    
    # Summary
    print(f"\n{'=' * 70}")
    print(f"📊 BATCH COMPLETE")
    print(f"{'=' * 70}")
    print(f"   ✅ Success: {success}")
    print(f"   ⚠️  Skipped: {skipped}")
    print(f"   ❌ Errors: {errors}")
    print(f"   📂 Total extracted: {len(existing) + success}")
    print(f"   📋 Remaining: {len(to_extract) - len(batch)}")
    
    if len(to_extract) > len(batch):
        print(f"\n💡 Run again to extract next batch of {min(BATCH_SIZE, len(to_extract) - len(batch))} icons")
    else:
        print(f"\n✅ ALL ICONS EXTRACTED!")
    
    print(f"\n💾 Icons: {output_dir}")
    
    channel.close()
    print("\n👋 Done - Octane connection closed cleanly")

if __name__ == '__main__':
    main()
