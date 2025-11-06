#!/bin/bash

# OctaneWeb2 Development Server Startup Script

echo "========================================"
echo "  OctaneWeb2 - React Edition"
echo "========================================"
echo ""

# Check if node_modules exists
if [ ! -d "node_modules" ]; then
    echo "📦 Installing dependencies..."
    npm install
    echo ""
fi

echo "🚀 Starting development server..."
echo ""
echo "Server will be available at:"
echo "  http://localhost:42219"
echo ""
echo "Press Ctrl+C to stop"
echo ""

npm run dev
