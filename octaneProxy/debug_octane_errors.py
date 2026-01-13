#!/usr/bin/env python3
"""
Debug script - captures FULL error messages from Octane
"""

import sys
import os
import grpc
from pathlib import Path
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'generated'))

try:
    from generated import octaneids_pb2, apiinfo_pb2, apiinfo_pb2_grpc, apiimage_pb2, apiimage_pb2_grpc
except ImportError as e:
    print(f"❌ Import failed: {e}")
    sys.exit(1)

OCTANE_HOST = 'host.docker.internal'
OCTANE_PORT = 51022

def test_icon_call(api_info_stub, node_name, node_type):
    """Test getting icon and capture ALL error details"""
    print(f"\n{'='*70}")
    print(f"Testing: {node_name} (type={node_type})")
    print(f"{'='*70}")
    
    try:
        # Create request
        print(f"\n1. Creating request...")
        req = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
        req.nodeType = node_type
        
        print(f"   Request object: {req}")
        print(f"   nodeType field: {req.nodeType}")
        print(f"   nodeType value: {node_type}")
        print(f"   nodeType type: {type(node_type)}")
        
        # Make call
        print(f"\n2. Calling nodeIconImage()...")
        resp = api_info_stub.nodeIconImage(req, timeout=15)
        
        # Check response
        print(f"\n3. Response received:")
        print(f"   Response object: {resp}")
        print(f"   Has 'result' attr: {hasattr(resp, 'result')}")
        
        if hasattr(resp, 'result'):
            icon_ref = resp.result
            print(f"   result.handle: {icon_ref.handle}")
            print(f"   result.type: {icon_ref.type}")
            
            if icon_ref.handle == 0:
                print(f"\n✅ Call succeeded but icon not available (handle=0)")
                return "NO_ICON"
            else:
                print(f"\n✅ Call succeeded - got valid icon reference")
                return "SUCCESS"
        else:
            print(f"\n⚠️  Response missing 'result' field")
            print(f"   Response dir: {dir(resp)}")
            return "INVALID_RESPONSE"
            
    except grpc.RpcError as e:
        print(f"\n❌ gRPC ERROR:")
        print(f"   Code: {e.code()}")
        print(f"   Code name: {e.code().name}")
        print(f"   Code value: {e.code().value}")
        print(f"   Details: {e.details()}")
        print(f"   Debug string: {e.debug_error_string()}")
        
        # Try to get more info
        try:
            print(f"   Initial metadata: {e.initial_metadata()}")
        except:
            pass
            
        try:
            print(f"   Trailing metadata: {e.trailing_metadata()}")
        except:
            pass
        
        return f"GRPC_ERROR_{e.code().name}"
        
    except Exception as e:
        print(f"\n❌ EXCEPTION:")
        print(f"   Type: {type(e).__name__}")
        print(f"   Message: {str(e)}")
        print(f"   Args: {e.args}")
        
        import traceback
        print(f"\n   Traceback:")
        traceback.print_exc()
        
        return f"EXCEPTION_{type(e).__name__}"

def main():
    print("=" * 70)
    print("🔍 OCTANE ERROR DEBUG - Full Error Capture")
    print("=" * 70)
    
    # Connect
    print(f"\n🔌 Connecting to Octane at {OCTANE_HOST}:{OCTANE_PORT}...")
    channel = grpc.insecure_channel(
        f'{OCTANE_HOST}:{OCTANE_PORT}',
        options=[
            ('grpc.max_send_message_length', 50 * 1024 * 1024),
            ('grpc.max_receive_message_length', 50 * 1024 * 1024),
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
    
    # Test several node types
    test_nodes = [
        ("NT_MAT_DIFFUSE", octaneids_pb2.NT_MAT_DIFFUSE),
        ("NT_TEX_IMAGE", octaneids_pb2.NT_TEX_IMAGE),
        ("NT_AOV_ALPHA", octaneids_pb2.NT_AOV_ALPHA),
        ("NT_UNKNOWN", 0),  # Invalid type
    ]
    
    results = {}
    
    for node_name, node_type in test_nodes:
        result = test_icon_call(api_info_stub, node_name, node_type)
        results[node_name] = result
        time.sleep(1)  # Delay between tests
    
    # Summary
    print(f"\n{'='*70}")
    print(f"📊 SUMMARY")
    print(f"{'='*70}")
    for node_name, result in results.items():
        print(f"   {node_name:30} → {result}")
    
    channel.close()
    print(f"\n👋 Done")

if __name__ == '__main__':
    main()
