#!/bin/bash

# Script to regenerate all protobuf files using the correct protoc version

PROTOC_BIN="/workspace/grpcSamples/third_party/protobuf/tools/bin/protoc"
GRPC_PLUGIN="/workspace/grpcSamples/third_party/protobuf/tools/bin/grpc_cpp_plugin"
PROTO_DIR="/workspace/grpcSamples/sdk/src/api/grpc/protodef"
OUTPUT_DIR="/workspace/grpcSamples/sdk/src/api/grpc/protoc"

echo "Regenerating protobuf files..."
echo "Using protoc: $($PROTOC_BIN --version)"
echo "Proto source dir: $PROTO_DIR"
echo "Output dir: $OUTPUT_DIR"

# Remove old generated files
echo "Cleaning old generated files..."
rm -f $OUTPUT_DIR/*.pb.cc
rm -f $OUTPUT_DIR/*.pb.h
rm -f $OUTPUT_DIR/*.grpc.pb.cc
rm -f $OUTPUT_DIR/*.grpc.pb.h

# Generate new files
echo "Generating new protobuf files..."

# Skip problematic files with duplicate definitions
SKIP_FILES="apinodearray.proto"

for proto_file in $PROTO_DIR/*.proto; do
    if [ -f "$proto_file" ]; then
        filename=$(basename "$proto_file")
        
        # Check if this file should be skipped
        skip_file=false
        for skip in $SKIP_FILES; do
            if [ "$filename" = "$skip" ]; then
                echo "Skipping: $filename (duplicate definitions)"
                skip_file=true
                break
            fi
        done
        
        if [ "$skip_file" = false ]; then
            echo "Processing: $filename"
            $PROTOC_BIN \
                --proto_path=$PROTO_DIR \
                --cpp_out=$OUTPUT_DIR \
                --grpc_out=$OUTPUT_DIR \
                --plugin=protoc-gen-grpc=$GRPC_PLUGIN \
                "$proto_file"
            
            if [ $? -ne 0 ]; then
                echo "Error processing $proto_file, continuing..."
                # Don't exit on error, continue with other files
            fi
        fi
    fi
done

echo "Protobuf regeneration complete!"
echo "Generated files:"
ls -la $OUTPUT_DIR/*.pb.cc $OUTPUT_DIR/*.pb.h $OUTPUT_DIR/*.grpc.pb.cc $OUTPUT_DIR/*.grpc.pb.h | wc -l