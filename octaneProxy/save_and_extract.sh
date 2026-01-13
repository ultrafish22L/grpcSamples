#!/bin/bash
# Helper script to save and extract icons

echo "=============================================================="
echo "📸 ICON EXTRACTION - Step by Step"
echo "=============================================================="
echo ""
echo "I can see your screenshot in the chat, but I need it as a file."
echo ""
echo "Please save the screenshot to:"
echo "  /workspace/project/grpcSamples/octaneProxy/octane_reference.png"
echo ""
echo "Then I'll extract all the icons automatically!"
echo ""
echo "Waiting for file..."

# Check if file exists
while [ ! -f octane_reference.png ]; do
    sleep 2
done

echo ""
echo "✅ File found! Starting extraction..."
echo ""

python3 extract_all_icons_comprehensive.py octane_reference.png

echo ""
echo "✅ Done! Check the output directory for all extracted icons."
