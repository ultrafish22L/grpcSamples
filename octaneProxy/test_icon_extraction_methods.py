#!/usr/bin/env python3
"""
Test different icon extraction methods to diagnose the issue
This helps identify which method works and why
"""

import sys
import os
import grpc
from pathlib import Path

sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'generated'))

try:
    from generated import (
        octaneids_pb2,
        apiinfo_pb2,
        apiinfo_pb2_grpc,
        apiimage_pb2,
        apiimage_pb2_grpc,
        apiimagebuffer_pb2,
        apiimagebuffer_pb2_grpc,
        common_pb2
    )
except ImportError as e:
    print(f"❌ Import failed: {e}")
    sys.exit(1)

OCTANE_HOST = 'host.docker.internal'
OCTANE_PORT = 51022

def test_connection():
    """Test basic connection to Octane"""
    print("\n" + "="*70)
    print("TEST 1: Connection Test")
    print("="*70)
    
    try:
        channel = grpc.insecure_channel(f'{OCTANE_HOST}:{OCTANE_PORT}')
        grpc.channel_ready_future(channel).result(timeout=10)
        print("✅ Connection successful")
        return channel
    except Exception as e:
        print(f"❌ Connection failed: {e}")
        return None

def test_get_icon_reference(channel):
    """Test getting icon reference from nodeIconImage"""
    print("\n" + "="*70)
    print("TEST 2: Get Icon Reference")
    print("="*70)
    
    try:
        api_info_stub = apiinfo_pb2_grpc.ApiInfoServiceStub(channel)
        
        # Try to get icon for NT_MAT_DIFFUSE (a common material node)
        node_type = octaneids_pb2.NT_MAT_DIFFUSE
        print(f"Requesting icon for NT_MAT_DIFFUSE (type={node_type})...")
        
        icon_request = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
        icon_request.nodeType = node_type
        
        response = api_info_stub.nodeIconImage(icon_request, timeout=15)
        icon_ref = response.result
        
        print(f"✅ Got icon reference:")
        print(f"   handle: {icon_ref.handle}")
        print(f"   type: {icon_ref.type}")
        
        if icon_ref.handle == 0:
            print("⚠️  Warning: handle is 0 (no icon available)")
            return None
        
        return icon_ref
        
    except Exception as e:
        print(f"❌ Failed: {e}")
        import traceback
        traceback.print_exc()
        return None

def test_buffer_save_method(channel, icon_ref, output_path):
    """Test Method 1: ApiImageBuffer.save()"""
    print("\n" + "="*70)
    print("TEST 3: ApiImageBuffer.save() Method")
    print("="*70)
    
    try:
        buffer_stub = apiimagebuffer_pb2_grpc.ApiImageBufferServiceStub(channel)
        
        print("Creating save request...")
        save_request = apiimagebuffer_pb2.ApiImageBuffer.saveRequest()
        save_request.objectPtr.CopyFrom(icon_ref)
        save_request.fileName = str(output_path.absolute())
        
        print(f"Calling ApiImageBuffer.save()...")
        print(f"  objectPtr.handle: {save_request.objectPtr.handle}")
        print(f"  objectPtr.type: {save_request.objectPtr.type}")
        print(f"  fileName: {save_request.fileName}")
        
        response = buffer_stub.save(save_request, timeout=15)
        
        print(f"✅ Save returned: {response.result}")
        
        if output_path.exists():
            size = output_path.stat().st_size
            print(f"✅ File created: {size} bytes")
            return True
        else:
            print(f"⚠️  File not created even though save returned true")
            return False
            
    except grpc.RpcError as e:
        print(f"❌ gRPC Error:")
        print(f"   Code: {e.code()}")
        print(f"   Details: {e.details()}")
        
        if e.code() == grpc.StatusCode.INVALID_ARGUMENT:
            print(f"\n💡 This likely means icon_ref is ApiImage, not ApiImageBuffer")
        
        return False
        
    except Exception as e:
        print(f"❌ Failed: {e}")
        import traceback
        traceback.print_exc()
        return False

def test_image_dimensions(channel, icon_ref):
    """Test getting image dimensions via ApiImage"""
    print("\n" + "="*70)
    print("TEST 4: ApiImage Dimension Methods")
    print("="*70)
    
    try:
        image_stub = apiimage_pb2_grpc.ApiImageServiceStub(channel)
        
        print("Getting width...")
        width_req = apiimage_pb2.ApiImage.widthRequest()
        width_req.objectPtr.CopyFrom(icon_ref)
        width_resp = image_stub.width(width_req, timeout=10)
        width = width_resp.result
        print(f"✅ Width: {width}")
        
        print("Getting height...")
        height_req = apiimage_pb2.ApiImage.heightRequest()
        height_req.objectPtr.CopyFrom(icon_ref)
        height_resp = image_stub.height(height_req, timeout=10)
        height = height_resp.result
        print(f"✅ Height: {height}")
        
        print(f"\n✅ Icon dimensions: {width}x{height}")
        return width, height
        
    except Exception as e:
        print(f"❌ Failed: {e}")
        import traceback
        traceback.print_exc()
        return None, None

def test_pixel_read(channel, icon_ref):
    """Test reading a single pixel via ApiImage.pixelAt()"""
    print("\n" + "="*70)
    print("TEST 5: ApiImage.pixelAt() Method")
    print("="*70)
    
    try:
        image_stub = apiimage_pb2_grpc.ApiImageServiceStub(channel)
        
        print("Reading pixel at (0, 0)...")
        pixel_req = apiimage_pb2.ApiImage.pixelAtRequest()
        pixel_req.objectPtr.CopyFrom(icon_ref)
        pixel_req.x = 0
        pixel_req.y = 0
        
        pixel_resp = image_stub.pixelAt(pixel_req, timeout=10)
        pixel = pixel_resp.result
        
        print(f"✅ Pixel at (0,0):")
        print(f"   R: {pixel.r:.3f}")
        print(f"   G: {pixel.g:.3f}")
        print(f"   B: {pixel.b:.3f}")
        print(f"   A: {pixel.a:.3f}")
        
        return True
        
    except Exception as e:
        print(f"❌ Failed: {e}")
        import traceback
        traceback.print_exc()
        return False

def main():
    print("=" * 70)
    print("🧪 Octane Icon Extraction - DIAGNOSTIC TEST")
    print("=" * 70)
    print("\nThis script tests different methods to identify the issue")
    
    # Test 1: Connection
    channel = test_connection()
    if not channel:
        print("\n❌ Cannot proceed without connection")
        sys.exit(1)
    
    # Test 2: Get icon reference
    icon_ref = test_get_icon_reference(channel)
    if not icon_ref:
        print("\n❌ Cannot proceed without icon reference")
        channel.close()
        sys.exit(1)
    
    # Setup test output
    output_dir = Path(__file__).parent.parent / 'octaneWebR' / 'client' / 'public' / 'icons' / 'test'
    output_dir.mkdir(parents=True, exist_ok=True)
    test_file = output_dir / 'TEST_BUFFER_SAVE.png'
    
    # Test 3: Try ApiImageBuffer.save()
    buffer_save_works = test_buffer_save_method(channel, icon_ref, test_file)
    
    # Test 4: Get dimensions via ApiImage
    width, height = test_image_dimensions(channel, icon_ref)
    
    # Test 5: Read a single pixel
    pixel_read_works = test_pixel_read(channel, icon_ref)
    
    # Summary
    print("\n" + "=" * 70)
    print("📊 TEST SUMMARY")
    print("=" * 70)
    print(f"✅ Connection: SUCCESS")
    print(f"✅ Get icon reference: SUCCESS")
    print(f"{'✅' if buffer_save_works else '❌'} ApiImageBuffer.save(): {'SUCCESS' if buffer_save_works else 'FAILED'}")
    print(f"{'✅' if width and height else '❌'} ApiImage dimensions: {'SUCCESS' if width and height else 'FAILED'}")
    print(f"{'✅' if pixel_read_works else '❌'} ApiImage.pixelAt(): {'SUCCESS' if pixel_read_works else 'FAILED'}")
    
    print("\n💡 DIAGNOSIS:")
    if buffer_save_works:
        print("   ✅ Direct buffer save works! Use extract_icons_fixed.py")
    elif width and height and pixel_read_works:
        print("   ⚠️  Icon is ApiImage (not ApiImageBuffer)")
        print("   → Must use pixel-by-pixel extraction")
        print("   → Use extract_icons_fixed.py (it will auto-fallback)")
    else:
        print("   ❌ Unknown issue - check Octane connection and LiveLink")
    
    channel.close()
    print("\n👋 Tests complete")

if __name__ == '__main__':
    main()
