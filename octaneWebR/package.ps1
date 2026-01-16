# octaneWebR Distribution Packager
# Interactive menu to choose packaging method

Clear-Host
Write-Host "╔═══════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║      octaneWebR Distribution Packager             ║" -ForegroundColor Cyan
Write-Host "╠═══════════════════════════════════════════════════╣" -ForegroundColor Cyan
Write-Host "║  Choose your distribution method:                 ║" -ForegroundColor Cyan
Write-Host "╚═══════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""
Write-Host "1️⃣  Production Build (Static Files)" -ForegroundColor Yellow
Write-Host "   📦 Size: ~5-10 MB" -ForegroundColor Gray
Write-Host "   👥 Best for: Web hosting, quick sharing" -ForegroundColor Gray
Write-Host "   ⚙️  Requirements: Python or Node.js" -ForegroundColor Gray
Write-Host ""
Write-Host "2️⃣  Electron Desktop App" -ForegroundColor Yellow
Write-Host "   📦 Size: ~100-150 MB per platform" -ForegroundColor Gray
Write-Host "   👥 Best for: End users, desktop feel" -ForegroundColor Gray
Write-Host "   ⚙️  Requirements: None for end users" -ForegroundColor Gray
Write-Host ""
Write-Host "3️⃣  Docker Container" -ForegroundColor Yellow
Write-Host "   📦 Size: ~60-150 MB" -ForegroundColor Gray
Write-Host "   👥 Best for: Cloud, enterprise, DevOps" -ForegroundColor Gray
Write-Host "   ⚙️  Requirements: Docker" -ForegroundColor Gray
Write-Host ""
Write-Host "4️⃣  View Documentation" -ForegroundColor Yellow
Write-Host "   📖 Read DISTRIBUTION-GUIDE.md" -ForegroundColor Gray
Write-Host ""
Write-Host "5️⃣  Exit" -ForegroundColor Yellow
Write-Host ""
$choice = Read-Host "Enter your choice (1-5)"
Write-Host ""

switch ($choice) {
    "1" {
        Write-Host "🚀 Building Production Package..." -ForegroundColor Green
        Write-Host ""
        if (Test-Path "package-production.ps1") {
            & .\package-production.ps1
        } elseif (Test-Path "package-production.sh") {
            Write-Host "⚠️  Found bash script, but PowerShell script recommended on Windows" -ForegroundColor Yellow
            Write-Host "    Run in Git Bash: ./package-production.sh" -ForegroundColor Yellow
        } else {
            Write-Host "❌ Error: package-production.ps1 or package-production.sh not found" -ForegroundColor Red
            exit 1
        }
    }
    "2" {
        Write-Host "🚀 Setting up Electron Packaging..." -ForegroundColor Green
        Write-Host ""
        if (Test-Path "package-electron.ps1") {
            & .\package-electron.ps1
            Write-Host ""
            Write-Host "✅ Electron setup complete!" -ForegroundColor Green
            Write-Host ""
            Write-Host "📋 Next steps:" -ForegroundColor Cyan
            Write-Host "   • Read ELECTRON-PACKAGING.md for detailed instructions"
            Write-Host "   • Run build commands:"
            Write-Host "     - npm run electron:build:win    (Windows)"
            Write-Host "     - npm run electron:build:mac    (macOS)"
            Write-Host "     - npm run electron:build:linux  (Linux)"
            Write-Host ""
        } elseif (Test-Path "package-electron.sh") {
            Write-Host "⚠️  Found bash script, but PowerShell script recommended on Windows" -ForegroundColor Yellow
            Write-Host "    Run in Git Bash: ./package-electron.sh" -ForegroundColor Yellow
        } else {
            Write-Host "❌ Error: package-electron.ps1 or package-electron.sh not found" -ForegroundColor Red
            exit 1
        }
    }
    "3" {
        Write-Host "🚀 Building Docker Container..." -ForegroundColor Green
        Write-Host ""
        if (Test-Path "Dockerfile") {
            Write-Host "Building Docker image (this may take a few minutes)..." -ForegroundColor Yellow
            
            # Check if docker-compose or docker compose command exists
            $dockerComposeCmd = Get-Command docker-compose -ErrorAction SilentlyContinue
            if ($dockerComposeCmd) {
                docker-compose build
            } else {
                # Try docker compose (newer syntax)
                docker compose build
            }
            
            if ($LASTEXITCODE -eq 0) {
                Write-Host ""
                Write-Host "✅ Docker image built successfully!" -ForegroundColor Green
                Write-Host ""
                Write-Host "📋 Next steps:" -ForegroundColor Cyan
                Write-Host ""
                Write-Host "Test locally:" -ForegroundColor Yellow
                Write-Host "  docker-compose up -d"
                Write-Host "  Open http://localhost:43930"
                Write-Host ""
                Write-Host "Create TAR archive for distribution:" -ForegroundColor Yellow
                Write-Host "  docker save octanewebr:latest | gzip > octanewebr-docker.tar.gz"
                Write-Host ""
                Write-Host "Push to Docker Hub:" -ForegroundColor Yellow
                Write-Host "  docker tag octanewebr:latest yourusername/octanewebr:latest"
                Write-Host "  docker push yourusername/octanewebr:latest"
                Write-Host ""
                Write-Host "📖 Read DOCKER-PACKAGING.md for complete guide" -ForegroundColor Cyan
                Write-Host ""
            } else {
                Write-Host "❌ Error: Docker build failed" -ForegroundColor Red
                Write-Host "   Ensure Docker is installed and running" -ForegroundColor Yellow
                exit 1
            }
        } else {
            Write-Host "❌ Error: Dockerfile not found" -ForegroundColor Red
            exit 1
        }
    }
    "4" {
        Write-Host "📖 Opening Documentation..." -ForegroundColor Green
        Write-Host ""
        if (Test-Path "DISTRIBUTION-GUIDE.md") {
            # Open in default editor/viewer
            Invoke-Item "DISTRIBUTION-GUIDE.md"
        } else {
            Write-Host "❌ Error: DISTRIBUTION-GUIDE.md not found" -ForegroundColor Red
            exit 1
        }
    }
    "5" {
        Write-Host "👋 Exiting..." -ForegroundColor Green
        exit 0
    }
    default {
        Write-Host "❌ Invalid choice. Please run the script again and choose 1-5." -ForegroundColor Red
        exit 1
    }
}
