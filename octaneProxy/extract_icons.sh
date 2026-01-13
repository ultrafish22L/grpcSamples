#!/bin/bash
# Octane Icon Extraction Wrapper Script
# Extracts all Octane icons via gRPC and saves them for octaneWebR

set -e  # Exit on error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "=================================================="
echo "🎨 Octane Icon Extraction Tool"
echo "=================================================="
echo ""

# Check if Octane is likely running (basic check)
if ! nc -z localhost 51022 2>/dev/null; then
    echo "⚠️  WARNING: Cannot connect to localhost:51022"
    echo "   Make sure Octane is running with LiveLink enabled"
    echo "   (Help → LiveLink in Octane menu)"
    echo ""
    read -p "Continue anyway? (y/N) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "❌ Aborted"
        exit 1
    fi
fi

# Check Python dependencies
echo "🔍 Checking Python dependencies..."
if ! python3 -c "import grpc, google.protobuf" 2>/dev/null; then
    echo "❌ Missing Python dependencies"
    echo "   Installing grpcio and protobuf..."
    pip install grpcio protobuf
fi

# Run extraction
echo ""
echo "🚀 Starting icon extraction..."
echo ""
python3 extract_icons.py

echo ""
echo "✅ Done! Check octaneWebR/client/public/icons/"
