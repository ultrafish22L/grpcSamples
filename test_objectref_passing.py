#!/usr/bin/env python3
"""
Test to demonstrate the difference between passing raw protobuf ObjectRef vs dictionary
This shows what the user meant by "passing the objectptr returned"
"""

import sys
import os

# Add the proxy directory to path for protobuf imports
sys.path.append('/workspace/grpcSamples/proxy')

try:
    import apiprojectmanager_pb2_grpc
    import apiprojectmanager_pb2
    import apinodesystem_pb2_grpc  
    import apinodesystem_pb2
    import common_pb2
    print("✅ Successfully imported protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import protobuf modules: {e}")
    sys.exit(1)

def test_objectref_formats():
    """Test different ways of handling ObjectRef"""
    
    print("🧪 Testing ObjectRef format handling...")
    
    # Simulate a rootNodeGraph response
    print("\n1️⃣ Simulating rootNodeGraph response...")
    mock_response = apiprojectmanager_pb2.ApiProjectManager.rootNodeGraphResponse()
    mock_response.result.handle = 1000000
    mock_response.result.type = 18
    
    print(f"   Raw protobuf ObjectRef: {mock_response.result}")
    print(f"   Handle: {mock_response.result.handle}")
    print(f"   Type: {mock_response.result.type}")
    
    # Method 1: Convert to dictionary (OLD WAY)
    print("\n2️⃣ OLD WAY: Converting to dictionary...")
    dict_format = {
        'handle': mock_response.result.handle,
        'type': mock_response.result.type
    }
    print(f"   Dictionary format: {dict_format}")
    
    # Method 2: Pass protobuf object directly (NEW WAY)
    print("\n3️⃣ NEW WAY: Using protobuf ObjectRef directly...")
    protobuf_format = mock_response.result
    print(f"   Protobuf format: {protobuf_format}")
    
    # Test creating name request with both methods
    print("\n4️⃣ Creating name requests...")
    
    # Dictionary method
    print("   📤 Dictionary method:")
    request1 = apinodesystem_pb2.ApiItem.nameRequest()
    request1.objectPtr.handle = dict_format['handle']
    request1.objectPtr.type = dict_format['type']
    print(f"      Request: {request1}")
    
    # Direct protobuf method
    print("   📤 Direct protobuf method:")
    request2 = apinodesystem_pb2.ApiItem.nameRequest()
    request2.objectPtr.CopyFrom(protobuf_format)
    print(f"      Request: {request2}")
    
    # Compare the results
    print("\n5️⃣ Comparison:")
    print(f"   Dictionary method - Handle: {request1.objectPtr.handle}, Type: {request1.objectPtr.type}")
    print(f"   Protobuf method   - Handle: {request2.objectPtr.handle}, Type: {request2.objectPtr.type}")
    
    if (request1.objectPtr.handle == request2.objectPtr.handle and 
        request1.objectPtr.type == request2.objectPtr.type):
        print("   ✅ Both methods produce identical results")
    else:
        print("   ❌ Methods produce different results")
    
    print("\n🎯 KEY INSIGHT:")
    print("   The user's change from 'result' to 'response.result' means:")
    print("   - OLD: Pass dictionary {'handle': 1000000, 'type': 18}")
    print("   - NEW: Pass protobuf ObjectRef directly")
    print("   - This preserves any additional protobuf metadata that might be important")

if __name__ == '__main__':
    test_objectref_formats()