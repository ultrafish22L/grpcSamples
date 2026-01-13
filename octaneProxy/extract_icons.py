#!/usr/bin/env python3
"""
Extract Octane Icons via gRPC API
Calls nodeIconImage() and graphIconImage() for all node/graph types
Saves icons to octaneWebR/client/public/icons/
"""

import sys
import os
import grpc
from pathlib import Path

# Add generated protobuf files to path
sys.path.append(os.path.join(os.path.dirname(__file__), 'generated'))

try:
    from generated import (
        octaneids_pb2,
        apiinfo_pb2,
        apiinfo_pb2_grpc,
        apiimagebuffer_pb2_grpc,
        common_pb2
    )
    print("✅ Successfully imported protobuf modules")
except ImportError as e:
    print(f"❌ Failed to import protobuf modules: {e}")
    print("   Make sure generated protobuf files exist in octaneProxy/generated/")
    sys.exit(1)

# Octane LiveLink default address
# Use host.docker.internal for Docker/sandbox environments
OCTANE_HOST = 'host.docker.internal'
OCTANE_PORT = 51022

def connect_to_octane():
    """Establish gRPC connection to Octane LiveLink"""
    try:
        channel = grpc.insecure_channel(f'{OCTANE_HOST}:{OCTANE_PORT}')
        # Test connection
        grpc.channel_ready_future(channel).result(timeout=5)
        print(f"✅ Connected to Octane at {OCTANE_HOST}:{OCTANE_PORT}")
        return channel
    except Exception as e:
        print(f"❌ Failed to connect to Octane: {e}")
        print(f"   Make sure Octane is running with LiveLink enabled")
        print(f"   (Help → LiveLink in Octane menu)")
        return None

def get_all_node_types():
    """Extract all NodeType enum values"""
    node_types = {}
    try:
        # Get all attributes that start with NT_
        for attr_name in dir(octaneids_pb2):
            if attr_name.startswith('NT_') and not attr_name.startswith('NT__'):
                value = getattr(octaneids_pb2, attr_name)
                if isinstance(value, int):
                    node_types[attr_name] = value
        print(f"✅ Found {len(node_types)} node types")
        return node_types
    except Exception as e:
        print(f"❌ Failed to extract node types: {e}")
        return {}

def get_all_graph_types():
    """Extract all NodeGraphType enum values"""
    graph_types = {}
    try:
        # Get all attributes that start with GT_
        for attr_name in dir(octaneids_pb2):
            if attr_name.startswith('GT_') and not attr_name.startswith('GT__'):
                value = getattr(octaneids_pb2, attr_name)
                if isinstance(value, int):
                    graph_types[attr_name] = value
        print(f"✅ Found {len(graph_types)} graph types")
        return graph_types
    except Exception as e:
        print(f"❌ Failed to extract graph types: {e}")
        return {}

def save_icon_image(channel, image_ref, output_path):
    """Save an icon image buffer to PNG file"""
    try:
        # Create ApiImageBuffer service stub
        buffer_stub = apiimagebuffer_pb2_grpc.ApiImageBufferServiceStub(channel)
        
        # Create save request - note: protobuf uses camelCase for nested message types
        from generated.apiimagebuffer_pb2 import ApiImageBuffer
        save_request = ApiImageBuffer.saveRequest()
        save_request.objectPtr.CopyFrom(image_ref)
        save_request.fileName = str(output_path)
        # metaData is optional, we don't need to set it
        
        # Call save method
        response = buffer_stub.save(save_request)
        return response.result
        
    except Exception as e:
        print(f"   ⚠️  Error saving image: {e}")
        return False

def extract_node_icons(channel, node_types, output_dir):
    """Extract icons for all node types"""
    print(f"\n🎨 Extracting {len(node_types)} node icons...")
    
    # Create ApiInfo service stub
    api_info_stub = apiinfo_pb2_grpc.ApiInfoServiceStub(channel)
    
    success_count = 0
    skip_count = 0
    error_count = 0
    
    for node_name, node_value in sorted(node_types.items()):
        # Skip unknown/invalid types
        if node_name == 'NT_UNKNOWN' or node_name.startswith('_'):
            skip_count += 1
            continue
            
        try:
            # Create request for node icon
            icon_request = apiinfo_pb2.ApiInfo.nodeIconImageRequest()
            icon_request.nodeType = node_value
            
            # Call nodeIconImage
            response = api_info_stub.nodeIconImage(icon_request, timeout=10)
            
            if response.result.handle != 0:
                # Save icon to file
                icon_path = output_dir / f"{node_name}.png"
                if save_icon_image(channel, response.result, icon_path):
                    success_count += 1
                    if success_count % 50 == 0:
                        print(f"   📊 Progress: {success_count}/{len(node_types)} icons saved...")
                else:
                    print(f"   ⚠️  Failed to save: {node_name}")
                    error_count += 1
            else:
                skip_count += 1
                
        except grpc.RpcError as e:
            if e.code() == grpc.StatusCode.UNIMPLEMENTED:
                print(f"   ℹ️  Node icon not available: {node_name}")
                skip_count += 1
            else:
                print(f"   ❌ Error getting icon for {node_name}: {e}")
                error_count += 1
        except Exception as e:
            print(f"   ❌ Unexpected error for {node_name}: {e}")
            error_count += 1
    
    print(f"✅ Node icons: {success_count} saved, {skip_count} skipped, {error_count} errors")
    return success_count

def extract_graph_icons(channel, graph_types, output_dir):
    """Extract icons for all graph types"""
    print(f"\n🎨 Extracting {len(graph_types)} graph icons...")
    
    # Create ApiInfo service stub
    api_info_stub = apiinfo_pb2_grpc.ApiInfoServiceStub(channel)
    
    success_count = 0
    skip_count = 0
    error_count = 0
    
    for graph_name, graph_value in sorted(graph_types.items()):
        # Skip unknown/invalid types
        if graph_name == 'GT_UNKNOWN' or graph_name.startswith('_'):
            skip_count += 1
            continue
            
        try:
            # Create request for graph icon
            icon_request = apiinfo_pb2.ApiInfo.graphIconImageRequest()
            icon_request.nodeGraphType = graph_value
            
            # Call graphIconImage
            response = api_info_stub.graphIconImage(icon_request, timeout=10)
            
            if response.result.handle != 0:
                # Save icon to file
                icon_path = output_dir / f"{graph_name}.png"
                if save_icon_image(channel, response.result, icon_path):
                    success_count += 1
                    if success_count % 10 == 0:
                        print(f"   📊 Progress: {success_count}/{len(graph_types)} icons saved...")
                else:
                    print(f"   ⚠️  Failed to save: {graph_name}")
                    error_count += 1
            else:
                skip_count += 1
                
        except grpc.RpcError as e:
            if e.code() == grpc.StatusCode.UNIMPLEMENTED:
                print(f"   ℹ️  Graph icon not available: {graph_name}")
                skip_count += 1
            else:
                print(f"   ❌ Error getting icon for {graph_name}: {e}")
                error_count += 1
        except Exception as e:
            print(f"   ❌ Unexpected error for {graph_name}: {e}")
            error_count += 1
    
    print(f"✅ Graph icons: {success_count} saved, {skip_count} skipped, {error_count} errors")
    return success_count

def main():
    print("=" * 70)
    print("🎨 Octane Icon Extractor")
    print("=" * 70)
    
    # Setup output directory
    script_dir = Path(__file__).parent
    output_dir = script_dir.parent / "octaneWebR" / "client" / "public" / "icons"
    output_dir.mkdir(parents=True, exist_ok=True)
    print(f"📁 Output directory: {output_dir}")
    
    # Create subdirectories for node and graph icons
    node_icons_dir = output_dir / "nodes"
    graph_icons_dir = output_dir / "graphs"
    node_icons_dir.mkdir(exist_ok=True)
    graph_icons_dir.mkdir(exist_ok=True)
    
    # Get all type enums
    node_types = get_all_node_types()
    graph_types = get_all_graph_types()
    
    if not node_types and not graph_types:
        print("❌ No types found to extract")
        sys.exit(1)
    
    # Connect to Octane
    channel = connect_to_octane()
    if not channel:
        sys.exit(1)
    
    try:
        # Extract node icons
        node_count = 0
        if node_types:
            node_count = extract_node_icons(channel, node_types, node_icons_dir)
        
        # Extract graph icons
        graph_count = 0
        if graph_types:
            graph_count = extract_graph_icons(channel, graph_types, graph_icons_dir)
        
        # Summary
        print("\n" + "=" * 70)
        print("📊 EXTRACTION COMPLETE")
        print("=" * 70)
        print(f"✅ Total icons extracted: {node_count + graph_count}")
        print(f"   • Node icons: {node_count} → {node_icons_dir}")
        print(f"   • Graph icons: {graph_count} → {graph_icons_dir}")
        print("\n💡 Icons are now available for octaneWebR to use!")
        
    finally:
        channel.close()
        print("\n👋 Connection closed")

if __name__ == "__main__":
    main()
