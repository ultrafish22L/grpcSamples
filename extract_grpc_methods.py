#!/usr/bin/env python3
"""
🔥 GRIND MODE: Extract gRPC Methods from Protobuf Files

This script parses all protobuf files and extracts service definitions
and method signatures to enhance the unit testing system.
"""

import os
import re
import json
from pathlib import Path

def extract_service_methods(proto_file_path):
    """Extract service definitions and methods from a protobuf file"""
    services = {}
    
    try:
        with open(proto_file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Find all service definitions
        service_pattern = r'service\s+(\w+)\s*\{([^}]+)\}'
        service_matches = re.findall(service_pattern, content, re.DOTALL)
        
        for service_name, service_body in service_matches:
            methods = {}
            
            # Find all RPC methods in the service
            method_pattern = r'rpc\s+(\w+)\s*\(\s*([^)]+)\s*\)\s*returns\s*\(\s*([^)]+)\s*\)'
            method_matches = re.findall(method_pattern, service_body)
            
            for method_name, request_type, response_type in method_matches:
                methods[method_name] = {
                    'request_type': request_type.strip(),
                    'response_type': response_type.strip(),
                    'description': f'RPC method {method_name} in {service_name}'
                }
            
            if methods:
                services[service_name] = {
                    'methods': methods,
                    'file': os.path.basename(proto_file_path)
                }
    
    except Exception as e:
        print(f"Error processing {proto_file_path}: {e}")
    
    return services

def extract_message_definitions(proto_file_path):
    """Extract message definitions from a protobuf file"""
    messages = {}
    
    try:
        with open(proto_file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Find all message definitions
        message_pattern = r'message\s+(\w+)\s*\{([^}]+)\}'
        message_matches = re.findall(message_pattern, content, re.DOTALL)
        
        for message_name, message_body in message_matches:
            fields = {}
            
            # Find all fields in the message
            field_pattern = r'(\w+)\s+(\w+)\s*=\s*(\d+);'
            field_matches = re.findall(field_pattern, message_body)
            
            for field_type, field_name, field_number in field_matches:
                fields[field_name] = {
                    'type': field_type,
                    'number': int(field_number)
                }
            
            if fields:
                messages[message_name] = {
                    'fields': fields,
                    'file': os.path.basename(proto_file_path)
                }
    
    except Exception as e:
        print(f"Error processing messages in {proto_file_path}: {e}")
    
    return messages

def main():
    """Main extraction function"""
    print("🔥 GRIND MODE: Extracting gRPC methods from protobuf files...")
    
    # Path to protobuf definitions
    proto_dir = Path("sdk/src/api/grpc/protodef")
    
    if not proto_dir.exists():
        print(f"❌ Protobuf directory not found: {proto_dir}")
        return
    
    all_services = {}
    all_messages = {}
    
    # Process all .proto files
    proto_files = list(proto_dir.glob("*.proto"))
    print(f"📁 Found {len(proto_files)} protobuf files")
    
    for proto_file in proto_files:
        print(f"🔍 Processing {proto_file.name}...")
        
        # Extract services
        services = extract_service_methods(proto_file)
        all_services.update(services)
        
        # Extract messages
        messages = extract_message_definitions(proto_file)
        all_messages.update(messages)
    
    # Generate statistics
    total_services = len(all_services)
    total_methods = sum(len(service['methods']) for service in all_services.values())
    total_messages = len(all_messages)
    
    print(f"\n📊 EXTRACTION RESULTS:")
    print(f"   Services: {total_services}")
    print(f"   Methods: {total_methods}")
    print(f"   Messages: {total_messages}")
    
    # Save results
    output_dir = Path("octaneWeb/extracted_grpc_data")
    output_dir.mkdir(exist_ok=True)
    
    # Save services
    services_file = output_dir / "services.json"
    with open(services_file, 'w') as f:
        json.dump(all_services, f, indent=2)
    print(f"💾 Services saved to: {services_file}")
    
    # Save messages
    messages_file = output_dir / "messages.json"
    with open(messages_file, 'w') as f:
        json.dump(all_messages, f, indent=2)
    print(f"💾 Messages saved to: {messages_file}")
    
    # Generate JavaScript file for enhanced testing
    js_output = output_dir / "extracted_services.js"
    with open(js_output, 'w') as f:
        f.write("// 🔥 GRIND MODE: Extracted gRPC Service Definitions\n")
        f.write("// Auto-generated from protobuf files\n\n")
        f.write("const EXTRACTED_GRPC_SERVICES = ")
        f.write(json.dumps(all_services, indent=2))
        f.write(";\n\n")
        f.write("const EXTRACTED_GRPC_MESSAGES = ")
        f.write(json.dumps(all_messages, indent=2))
        f.write(";\n\n")
        f.write("// Export for use in other modules\n")
        f.write("if (typeof module !== 'undefined' && module.exports) {\n")
        f.write("    module.exports = { EXTRACTED_GRPC_SERVICES, EXTRACTED_GRPC_MESSAGES };\n")
        f.write("} else if (typeof window !== 'undefined') {\n")
        f.write("    window.EXTRACTED_GRPC_SERVICES = EXTRACTED_GRPC_SERVICES;\n")
        f.write("    window.EXTRACTED_GRPC_MESSAGES = EXTRACTED_GRPC_MESSAGES;\n")
        f.write("}\n")
    
    print(f"📄 JavaScript file saved to: {js_output}")
    
    # Show top services by method count
    print(f"\n🏆 TOP SERVICES BY METHOD COUNT:")
    sorted_services = sorted(all_services.items(), 
                           key=lambda x: len(x[1]['methods']), 
                           reverse=True)
    
    for i, (service_name, service_data) in enumerate(sorted_services[:10]):
        method_count = len(service_data['methods'])
        file_name = service_data['file']
        print(f"   {i+1:2d}. {service_name:<35} {method_count:3d} methods ({file_name})")
    
    print(f"\n✅ Extraction completed successfully!")

if __name__ == "__main__":
    main()