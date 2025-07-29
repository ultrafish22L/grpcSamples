#!/usr/bin/env python3
"""
Extract Octane Type Constants from Generated Protobuf Files
Generates JavaScript constants file from Python protobuf enums
"""

import sys
import os
sys.path.append(os.path.join(os.path.dirname(__file__), 'generated'))

try:
    from generated import common_pb2
    print("✅ Successfully imported common_pb2")
except ImportError as e:
    print(f"❌ Failed to import common_pb2: {e}")
    sys.exit(1)

def extract_enum_values(enum_class, enum_name):
    """Extract enum values from a protobuf enum class"""
    values = {}
    
    # For protobuf enums, we need to access the values differently
    # Try to get the enum descriptor and extract values
    try:
        # Method 1: Direct attribute access
        for name in dir(enum_class):
            if not name.startswith('_') and not name.startswith('DESCRIPTOR'):
                try:
                    value = getattr(enum_class, name)
                    if isinstance(value, int):
                        values[name] = value
                        print(f"   Found {name} = {value}")
                except:
                    pass
    except Exception as e:
        print(f"   Method 1 failed: {e}")
    
    # Method 2: Try accessing enum values through the descriptor
    if not values:
        try:
            if hasattr(enum_class, 'DESCRIPTOR'):
                descriptor = enum_class.DESCRIPTOR
                for value_desc in descriptor.values:
                    values[value_desc.name] = value_desc.number
                    print(f"   Found {value_desc.name} = {value_desc.number}")
        except Exception as e:
            print(f"   Method 2 failed: {e}")
    
    return values

def generate_javascript_constants():
    """Generate JavaScript constants file from protobuf enums"""
    
    js_content = '''/**
 * Octane gRPC Type Constants
 * 
 * AUTO-GENERATED from protobuf files - DO NOT EDIT MANUALLY
 * Generated from: octaneProxy/generated/common_pb2.py
 * 
 * This eliminates hardcoded type values in ObjectPtr requests and ensures
 * consistency with the actual protobuf definitions.
 */

// Make constants available globally
window.OctaneTypes = window.OctaneTypes || {};

'''

    # Extract ObjectRef.ObjectType enum
    try:
        object_type_values = extract_enum_values(common_pb2.ObjectRef.ObjectType, "ObjectType")
        js_content += "// ObjectRef.ObjectType enum values from common.proto\n"
        js_content += "window.OctaneTypes.ObjectType = {\n"
        for name, value in sorted(object_type_values.items(), key=lambda x: x[1]):
            js_content += f"    {name}: {value},\n"
        js_content += "};\n\n"
        print(f"✅ Extracted {len(object_type_values)} ObjectType values")
    except Exception as e:
        print(f"❌ Failed to extract ObjectType: {e}")
        return None

    # Extract ApiItemPtr.PointerType enum
    try:
        api_item_ptr_values = extract_enum_values(common_pb2.ApiItemPtr.PointerType, "PointerType")
        js_content += "// ApiItemPtr.PointerType enum values from common.proto\n"
        js_content += "window.OctaneTypes.ApiItemPointerType = {\n"
        for name, value in sorted(api_item_ptr_values.items(), key=lambda x: x[1]):
            js_content += f"    {name}: {value},\n"
        js_content += "};\n\n"
        print(f"✅ Extracted {len(api_item_ptr_values)} ApiItemPointerType values")
    except Exception as e:
        print(f"❌ Failed to extract ApiItemPointerType: {e}")
        return None

    # Extract ApiNodeGraphPtr.PointerType enum
    try:
        api_node_graph_ptr_values = extract_enum_values(common_pb2.ApiNodeGraphPtr.PointerType, "PointerType")
        js_content += "// ApiNodeGraphPtr.PointerType enum values from common.proto\n"
        js_content += "window.OctaneTypes.ApiNodeGraphPointerType = {\n"
        for name, value in sorted(api_node_graph_ptr_values.items(), key=lambda x: x[1]):
            js_content += f"    {name}: {value},\n"
        js_content += "};\n\n"
        print(f"✅ Extracted {len(api_node_graph_ptr_values)} ApiNodeGraphPointerType values")
    except Exception as e:
        print(f"❌ Failed to extract ApiNodeGraphPointerType: {e}")
        return None

    # Add commonly used type combinations
    js_content += '''// Commonly used type combinations for convenience
window.OctaneTypes.CommonTypes = {
    // For ObjectPtr requests (uses ObjectRef.ObjectType)
    NODE: window.OctaneTypes.ObjectType.ApiNode,                    // 17
    ROOT_NODE_GRAPH: window.OctaneTypes.ObjectType.ApiRootNodeGraph, // 18
    NODE_GRAPH: window.OctaneTypes.ObjectType.ApiNodeGraph,         // 20
    
    // For ApiItemPtr requests (uses ApiItemPtr.PointerType)
    ITEM_NODE: window.OctaneTypes.ApiItemPointerType.ApiNode,       // 1
    ITEM_NODE_GRAPH: window.OctaneTypes.ApiItemPointerType.ApiNodeGraph, // 2
    ITEM_ROOT_NODE_GRAPH: window.OctaneTypes.ApiItemPointerType.ApiRootNodeGraph, // 3
};

// Helper functions for creating properly typed object pointers
window.OctaneTypes.createObjectPtr = (handle, type) => ({
    handle: handle,
    type: type
});

window.OctaneTypes.createApiItemPtr = (handle, pointerType) => ({
    handle: handle,
    type: pointerType
});

window.OctaneTypes.createApiNodeGraphPtr = (handle, pointerType) => ({
    handle: handle,
    pointer_type: pointerType
});

// Validation helpers
window.OctaneTypes.isValidObjectType = (type) => {
    return Object.values(window.OctaneTypes.ObjectType).includes(type);
};

window.OctaneTypes.isValidApiItemPointerType = (type) => {
    return Object.values(window.OctaneTypes.ApiItemPointerType).includes(type);
};

window.OctaneTypes.isValidApiNodeGraphPointerType = (type) => {
    return Object.values(window.OctaneTypes.ApiNodeGraphPointerType).includes(type);
};

// Type name lookup for debugging
window.OctaneTypes.getObjectTypeName = (type) => {
    const entry = Object.entries(window.OctaneTypes.ObjectType).find(([name, value]) => value === type);
    return entry ? entry[0] : `Unknown(${type})`;
};

window.OctaneTypes.getApiItemPointerTypeName = (type) => {
    const entry = Object.entries(window.OctaneTypes.ApiItemPointerType).find(([name, value]) => value === type);
    return entry ? entry[0] : `Unknown(${type})`;
};

window.OctaneTypes.getApiNodeGraphPointerTypeName = (type) => {
    const entry = Object.entries(window.OctaneTypes.ApiNodeGraphPointerType).find(([name, value]) => value === type);
    return entry ? entry[0] : `Unknown(${type})`;
};

// Log successful loading
console.log('✅ OctaneTypes constants loaded successfully (AUTO-GENERATED)');
console.log('📋 Available types:', Object.keys(window.OctaneTypes.ObjectType).length, 'ObjectTypes,', 
           Object.keys(window.OctaneTypes.ApiItemPointerType).length, 'ApiItemPointerTypes,',
           Object.keys(window.OctaneTypes.ApiNodeGraphPointerType).length, 'ApiNodeGraphPointerTypes');
'''

    return js_content

def main():
    print("🔍 Extracting Octane type constants from protobuf files...")
    
    js_content = generate_javascript_constants()
    if js_content is None:
        print("❌ Failed to generate JavaScript constants")
        sys.exit(1)
    
    # Write to octaneWeb constants directory
    output_path = "../octaneWeb/js/constants/OctaneTypes.js"
    try:
        with open(output_path, 'w') as f:
            f.write(js_content)
        print(f"✅ Generated JavaScript constants: {output_path}")
        
        # Show key values for verification
        print("\n📋 Key type values:")
        print(f"   ApiNode = {common_pb2.ObjectRef.ObjectType.ApiNode}")
        print(f"   ApiRootNodeGraph = {common_pb2.ObjectRef.ObjectType.ApiRootNodeGraph}")
        print(f"   ApiNodeGraph = {common_pb2.ObjectRef.ObjectType.ApiNodeGraph}")
        
    except Exception as e:
        print(f"❌ Failed to write JavaScript file: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()