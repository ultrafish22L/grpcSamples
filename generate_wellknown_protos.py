#!/usr/bin/env python3
"""
Generate well-known protobuf headers for Windows build
This script generates the missing .pb.h files that are needed for compilation
"""

import os
import subprocess
import sys
from pathlib import Path

def main():
    # Paths
    repo_root = Path(__file__).parent
    protobuf_src = repo_root / "third_party" / "protobuf" / "src"
    output_dir = repo_root / "third_party" / "protobuf" / "windows" / "include"
    
    # Well-known proto files that need to be generated
    well_known_protos = [
        "google/protobuf/empty.proto",
        "google/protobuf/any.proto", 
        "google/protobuf/descriptor.proto",
        "google/protobuf/duration.proto",
        "google/protobuf/timestamp.proto",
        "google/protobuf/struct.proto",
        "google/protobuf/wrappers.proto",
        "google/protobuf/field_mask.proto",
        "google/protobuf/api.proto",
        "google/protobuf/type.proto",
        "google/protobuf/source_context.proto",
    ]
    
    # Find protoc
    protoc_paths = [
        "protoc",
        "protoc.exe",
        str(repo_root / "third_party" / "protobuf" / "windows" / "bin" / "protoc.exe"),
        str(repo_root / "third_party" / "protobuf" / "bin" / "protoc.exe"),
    ]
    
    protoc = None
    for path in protoc_paths:
        try:
            result = subprocess.run([path, "--version"], capture_output=True, text=True)
            if result.returncode == 0:
                protoc = path
                print(f"Found protoc: {protoc}")
                break
        except FileNotFoundError:
            continue
    
    if not protoc:
        print("ERROR: protoc not found. Please install protobuf compiler.")
        return 1
    
    # Create output directory
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Generate headers for each well-known proto
    for proto_file in well_known_protos:
        proto_path = protobuf_src / proto_file
        if not proto_path.exists():
            print(f"WARNING: {proto_path} not found, skipping")
            continue
            
        print(f"Generating headers for {proto_file}")
        
        # Run protoc to generate C++ headers
        cmd = [
            protoc,
            f"--cpp_out={output_dir}",
            f"--proto_path={protobuf_src}",
            str(proto_path)
        ]
        
        try:
            result = subprocess.run(cmd, capture_output=True, text=True, cwd=repo_root)
            if result.returncode == 0:
                print(f"  ✅ Generated {proto_file}")
            else:
                print(f"  ❌ Failed to generate {proto_file}")
                print(f"     Error: {result.stderr}")
        except Exception as e:
            print(f"  ❌ Exception generating {proto_file}: {e}")
    
    print("\nGeneration complete!")
    print(f"Generated headers are in: {output_dir}")
    
    # List generated files
    generated_files = list(output_dir.rglob("*.pb.h"))
    print(f"\nGenerated {len(generated_files)} header files:")
    for f in sorted(generated_files):
        print(f"  {f.relative_to(output_dir)}")
    
    return 0

if __name__ == "__main__":
    sys.exit(main())