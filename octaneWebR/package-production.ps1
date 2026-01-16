# Package octaneWebR for Production Distribution
# Creates a portable package with built files and launcher

Write-Host "╔═══════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║     Building octaneWebR Production Package        ║" -ForegroundColor Cyan
Write-Host "╚═══════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

# Step 1: Clean previous builds
Write-Host "🧹 Cleaning previous builds..." -ForegroundColor Green
if (Test-Path "dist") { Remove-Item -Recurse -Force "dist" }
if (Test-Path "octaneWebR-production.zip") { Remove-Item -Force "octaneWebR-production.zip" }

# Step 2: Install dependencies
Write-Host "📦 Installing dependencies..." -ForegroundColor Green
npm install --production=false

# Step 3: Build production bundle
Write-Host "🔨 Building production bundle..." -ForegroundColor Green
npm run build

# Step 4: Create distribution package
Write-Host "📦 Creating distribution package..." -ForegroundColor Green
New-Item -ItemType Directory -Force -Path "dist/production" | Out-Null

# Copy built files
Copy-Item -Path "dist/client/*" -Destination "dist/production/" -Recurse -Force

# Create launcher script (bash)
$startServerSh = @'
#!/bin/bash
# octaneWebR Production Launcher
# Starts HTTP server on port 43930

echo "╔═══════════════════════════════════════════════════╗"
echo "║              Starting octaneWebR                  ║"
echo "╠═══════════════════════════════════════════════════╣"
echo "║  URL: http://localhost:43930                      ║"
echo "║  Requirements: Octane with LiveLink enabled       ║"
echo "╚═══════════════════════════════════════════════════╝"
echo ""
echo "📡 Starting HTTP server..."
echo "🌐 Open http://localhost:43930 in your browser"
echo ""
echo "Press Ctrl+C to stop server"
echo ""

# Check if Python is available
if command -v python3 &> /dev/null; then
    python3 -m http.server 43930
elif command -v python &> /dev/null; then
    python -m http.server 43930
else
    echo "❌ Error: Python not found. Please install Python or use Node.js:"
    echo "   npm install -g serve"
    echo "   serve -s . -p 43930"
    exit 1
fi
'@

Set-Content -Path "dist/production/start-server.sh" -Value $startServerSh

# Create Windows launcher
$startServerBat = @'
@echo off
REM octaneWebR Production Launcher for Windows
REM Starts HTTP server on port 43930

echo ╔═══════════════════════════════════════════════════╗
echo ║              Starting octaneWebR                  ║
echo ╠═══════════════════════════════════════════════════╣
echo ║  URL: http://localhost:43930                      ║
echo ║  Requirements: Octane with LiveLink enabled       ║
echo ╚═══════════════════════════════════════════════════╝
echo.
echo 📡 Starting HTTP server...
echo 🌐 Open http://localhost:43930 in your browser
echo.
echo Press Ctrl+C to stop server
echo.

REM Check if Python is available
where python >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    python -m http.server 43930
) else (
    echo ❌ Error: Python not found. Please install Python or use Node.js:
    echo    npm install -g serve
    echo    serve -s . -p 43930
    pause
    exit /b 1
)
'@

Set-Content -Path "dist/production/start-server.bat" -Value $startServerBat

# Create PowerShell launcher
$startServerPs1 = @'
# octaneWebR Production Launcher for Windows PowerShell
# Starts HTTP server on port 43930

Write-Host "╔═══════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║              Starting octaneWebR                  ║" -ForegroundColor Cyan
Write-Host "╠═══════════════════════════════════════════════════╣" -ForegroundColor Cyan
Write-Host "║  URL: http://localhost:43930                      ║" -ForegroundColor Cyan
Write-Host "║  Requirements: Octane with LiveLink enabled       ║" -ForegroundColor Cyan
Write-Host "╚═══════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""
Write-Host "📡 Starting HTTP server..." -ForegroundColor Green
Write-Host "🌐 Open http://localhost:43930 in your browser" -ForegroundColor Yellow
Write-Host ""
Write-Host "Press Ctrl+C to stop server" -ForegroundColor Yellow
Write-Host ""

# Check if Python is available
$pythonCmd = Get-Command python -ErrorAction SilentlyContinue
if ($pythonCmd) {
    python -m http.server 43930
} else {
    Write-Host "❌ Error: Python not found. Please install Python or use Node.js:" -ForegroundColor Red
    Write-Host "   npm install -g serve"
    Write-Host "   serve -s . -p 43930"
    Read-Host "Press Enter to exit"
    exit 1
}
'@

Set-Content -Path "dist/production/start-server.ps1" -Value $startServerPs1

# Create README
$readmeTxt = @'
╔═══════════════════════════════════════════════════╗
║        octaneWebR - Production Distribution       ║
╚═══════════════════════════════════════════════════╝

QUICK START:
1. Ensure Octane Render is running with LiveLink enabled
   (Help → LiveLink in Octane menu)

2. Run the launcher:
   • Windows (PowerShell): .\start-server.ps1
   • Windows (Command): start-server.bat
   • Linux/Mac: ./start-server.sh

3. Open browser to: http://localhost:43930

REQUIREMENTS:
✓ Octane Render with LiveLink enabled (port 51022)
✓ Modern web browser (Chrome, Firefox, Edge, Safari)
✓ Python 3 (for HTTP server) OR Node.js with 'serve' package

WHAT IS octaneWebR?
A web-based UI clone of Octane Render Studio Standalone Edition.
Full pixel-perfect React/TypeScript implementation with real-time
gRPC API integration to Octane.

FEATURES:
✓ Node Graph Editor with 755+ node types
✓ Scene Outliner with hierarchical tree view
✓ Node Inspector with real-time parameter editing
✓ Render Viewport with live HDR streaming
✓ Full keyboard shortcuts (Ctrl+C, Ctrl+V, Ctrl+F, etc.)
✓ Material Database (LiveDB + LocalDB)
✓ Complete menu system matching Octane SE

TROUBLESHOOTING:
• Cannot connect: Ensure Octane LiveLink is enabled
• Port in use: Change port in launcher script
• Blank screen: Clear browser cache, check console for errors

For more info: https://github.com/ultrafish22L/grpcSamples
'@

Set-Content -Path "dist/production/README.txt" -Value $readmeTxt

# Step 5: Create ZIP archive
Write-Host "📦 Creating ZIP archive..." -ForegroundColor Green
Compress-Archive -Path "dist/production/*" -DestinationPath "octaneWebR-production.zip" -Force

# Step 6: Summary
Write-Host ""
Write-Host "✅ Production package created successfully!" -ForegroundColor Green
Write-Host ""
Write-Host "📦 Distribution files:" -ForegroundColor Cyan
Write-Host "   • dist/production/          (ready to deploy)"
Write-Host "   • octaneWebR-production.zip (portable package)"
Write-Host ""
Write-Host "📋 Package contents:" -ForegroundColor Cyan
Write-Host "   • index.html + assets       (built app)"
Write-Host "   • start-server.ps1          (PowerShell launcher)"
Write-Host "   • start-server.bat          (Windows CMD launcher)"
Write-Host "   • start-server.sh           (Linux/Mac launcher)"
Write-Host "   • README.txt                (user instructions)"
Write-Host ""
Write-Host "🚀 To test production build:" -ForegroundColor Yellow
Write-Host "   cd dist/production"
Write-Host "   .\start-server.ps1          (PowerShell)"
Write-Host "   start-server.bat            (or CMD on Windows)"
Write-Host "   Open http://localhost:43930"
Write-Host ""
Write-Host "📤 To distribute:" -ForegroundColor Yellow
Write-Host "   Share octaneWebR-production.zip"
Write-Host "   Users extract and run launcher script"
Write-Host ""
