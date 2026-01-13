#!/usr/bin/env python3
"""
Extract exactly ONE icon and verify it's valid
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
except ImportError as e:
    print(f"❌ Import failed: {e}")
    sys.exit(1)

OCTANE_HOST = 'host.docker.internal'
OCTANE_PORT = 51022

def create_png(width, height, pixels):
    """Create PNG from RGBA floats (0-1)"""
    png_sig = b'\x89PNG\r\n\x1a\n'
    
    def chunk(ctype, data):
        cdata = ctype + data
        crc = zlib.crc32(cdata) & 0xffffffff
        return struct.pack('>I', len(data)) + cdata + struct.pack('>I', crc)
    
    ihdr = struct.pack('>IIBBBBB', width, height, 8, 6, 0, 0, 0)
    
    raw = b''
    for y in range(height):
        raw += b'\x00'  # PNG filter type
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

def main():
    print("=" * 70)
    print("🧪 SINGLE ICON EXTRACTION TEST")
    print("=" * 70)
    
    # Connect
    print(f"\n1️⃣ Connecting to Octane at {OCTANE_HOST}:{OCTANE_PORT}...")
    channel = grpc.insecure_channel(f'{OCTANE_HOST}:{OCTANE_PORT}')
    
    try:
        grpc.channel_ready_future(channel).result(timeout=10)
        print("   ✅ Connected")
    except Exception as e:
        print(f"   ❌ Failed: {e}")
        sys.exit(1)
    
    api_info_stub = apiinfo_pb2_grpc.ApiInfoServiceStub(channel)
    image_stub = apiimage_pb2_grpc.ApiImageServiceStub(channel)
    
    # Test with NT_MAT_DIFFUSE (a common material)
    node_type = octaneids_pb2.NT_MAT_DIFFUSE
    node_name = "NT_MAT_DIFFUSE"
    
    print(f"\n2️⃣ Getting icon reference for {node_name}...")
    try:
        req = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
        req.nodeType = node_type
        resp = api_info_stub.nodeIconImage(req, timeout=15)
        icon_ref = resp.result
        
        print(f"   ✅ Got reference: handle={icon_ref.handle}, type={icon_ref.type}")
        
        if icon_ref.handle == 0:
            print("   ⚠️  Handle is 0 - no icon available")
            channel.close()
            sys.exit(1)
    except Exception as e:
        print(f"   ❌ Failed: {e}")
        channel.close()
        sys.exit(1)
    
    time.sleep(0.1)
    
    # Get dimensions
    print(f"\n3️⃣ Getting dimensions...")
    try:
        w_req = apiimage_pb2.ApiImage.widthRequest()
        w_req.objectPtr.CopyFrom(icon_ref)
        width = image_stub.width(w_req, timeout=15).result
        
        h_req = apiimage_pb2.ApiImage.heightRequest()
        h_req.objectPtr.CopyFrom(icon_ref)
        height = image_stub.height(h_req, timeout=15).result
        
        print(f"   ✅ Dimensions: {width}x{height}")
        
        if width <= 0 or height <= 0:
            print(f"   ❌ Invalid dimensions!")
            channel.close()
            sys.exit(1)
    except Exception as e:
        print(f"   ❌ Failed: {e}")
        channel.close()
        sys.exit(1)
    
    time.sleep(0.1)
    
    # Read pixels
    print(f"\n4️⃣ Reading {width * height} pixels...")
    print(f"   Progress: ", end='', flush=True)
    
    try:
        pixels = []
        total = width * height
        
        for y in range(height):
            for x in range(width):
                p_req = apiimage_pb2.ApiImage.pixelAtRequest()
                p_req.objectPtr.CopyFrom(icon_ref)
                p_req.x = x
                p_req.y = y
                p_resp = image_stub.pixelAt(p_req, timeout=15)
                
                pixels.extend([
                    p_resp.result.r,
                    p_resp.result.g,
                    p_resp.result.b,
                    p_resp.result.a
                ])
            
            # Progress every row
            if (y + 1) % 4 == 0 or y == height - 1:
                print(f"{len(pixels)//4}/{total}", end=' ', flush=True)
            
            time.sleep(0.02)  # Small delay per row
        
        print("✅")
        print(f"   ✅ Read {len(pixels)//4} pixels ({len(pixels)} values)")
        
    except Exception as e:
        print(f"\n   ❌ Failed: {e}")
        channel.close()
        sys.exit(1)
    
    # Verify pixel data
    print(f"\n5️⃣ Verifying pixel data...")
    non_zero = sum(1 for p in pixels if p > 0.01)
    print(f"   Non-zero values: {non_zero}/{len(pixels)} ({non_zero*100//len(pixels)}%)")
    
    # Sample first few pixels
    print(f"   First pixel: R={pixels[0]:.3f} G={pixels[1]:.3f} B={pixels[2]:.3f} A={pixels[3]:.3f}")
    if len(pixels) >= 8:
        print(f"   Second pixel: R={pixels[4]:.3f} G={pixels[5]:.3f} B={pixels[6]:.3f} A={pixels[7]:.3f}")
    
    # Create PNG
    print(f"\n6️⃣ Creating PNG...")
    try:
        png_data = create_png(width, height, pixels)
        print(f"   ✅ PNG created: {len(png_data)} bytes")
        
        # Verify PNG signature
        if png_data[:8] == b'\x89PNG\r\n\x1a\n':
            print(f"   ✅ PNG signature valid")
        else:
            print(f"   ❌ PNG signature invalid!")
            
    except Exception as e:
        print(f"   ❌ Failed: {e}")
        channel.close()
        sys.exit(1)
    
    # Save to file
    print(f"\n7️⃣ Saving to file...")
    output_dir = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'test'
    output_dir.mkdir(parents=True, exist_ok=True)
    output_file = output_dir / f'TEST_{node_name}.png'
    
    try:
        with open(output_file, 'wb') as f:
            f.write(png_data)
        
        print(f"   ✅ Saved to: {output_file}")
        print(f"   File size: {output_file.stat().st_size} bytes")
        
    except Exception as e:
        print(f"   ❌ Failed: {e}")
        channel.close()
        sys.exit(1)
    
    # Verify with 'file' command
    print(f"\n8️⃣ Verifying PNG with file command...")
    import subprocess
    try:
        result = subprocess.run(['file', str(output_file)], capture_output=True, text=True, timeout=5)
        print(f"   {result.stdout.strip()}")
        
        if 'PNG image data' in result.stdout:
            print(f"   ✅ File is a valid PNG!")
        else:
            print(f"   ⚠️  File command doesn't recognize as PNG")
            
    except Exception as e:
        print(f"   ⚠️  Could not verify with file command: {e}")
    
    # Close connection
    channel.close()
    
    # Final summary
    print(f"\n{'=' * 70}")
    print(f"✅ SUCCESS - Icon extracted and verified!")
    print(f"{'=' * 70}")
    print(f"   Node: {node_name}")
    print(f"   Dimensions: {width}x{height}")
    print(f"   Pixel data: {len(pixels)//4} pixels")
    print(f"   PNG size: {len(png_data)} bytes")
    print(f"   File: {output_file}")
    print(f"\n💡 You can now view the icon:")
    print(f"   {output_file}")
    print()

if __name__ == '__main__':
    main()
