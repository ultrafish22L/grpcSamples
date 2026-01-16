# octaneWebR Packaging Scripts

## Quick Start

### Windows Users (PowerShell)
```powershell
# Main interactive menu
.\package.ps1

# Or run directly:
.\package-production.ps1    # Build static files
.\package-electron.ps1      # Setup Electron desktop app
```

### Windows Users (Command Prompt)
```cmd
powershell -ExecutionPolicy Bypass -File .\package.ps1
```

### Linux/Mac Users (Bash)
```bash
# Main interactive menu
./package.sh

# Or run directly:
./package-production.sh     # Build static files
./package-electron.sh       # Setup Electron desktop app
```

### Windows Users (Git Bash / WSL)
```bash
# You can also use the .sh scripts in Git Bash or WSL
./package.sh
./package-production.sh
./package-electron.sh
```

---

## Available Scripts

### Main Menu (Interactive)
- **Windows PowerShell**: `.\package.ps1`
- **Linux/Mac/Git Bash**: `./package.sh`

### Production Build (Static Files)
- **Windows PowerShell**: `.\package-production.ps1`
- **Linux/Mac/Git Bash**: `./package-production.sh`

Creates a lightweight ZIP package (~5-10 MB) with:
- Built static files (HTML, CSS, JS)
- Cross-platform launcher scripts
- README with instructions

### Electron Desktop App Setup
- **Windows PowerShell**: `.\package-electron.ps1`
- **Linux/Mac/Git Bash**: `./package-electron.sh`

Sets up Electron packaging infrastructure:
- Installs `electron` and `electron-builder`
- Creates `electron/main.js` wrapper
- Updates `package.json` with build scripts
- Generates ELECTRON-PACKAGING.md guide

After setup, build with:
```bash
npm run electron:build:win    # Windows
npm run electron:build:mac    # macOS
npm run electron:build:linux  # Linux
```

---

## Troubleshooting

### PowerShell: "script cannot be loaded because running scripts is disabled"

**Solution 1** (Recommended): Bypass execution policy for single script
```powershell
powershell -ExecutionPolicy Bypass -File .\package.ps1
```

**Solution 2**: Set execution policy for current user (one-time setup)
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

Then you can run scripts directly:
```powershell
.\package.ps1
```

### Windows: ".sh files don't work in PowerShell"

**Correct!** `.sh` files are bash scripts and won't run in PowerShell.

**Options**:
1. Use the `.ps1` PowerShell versions (recommended)
2. Install Git Bash and run `.sh` scripts there
3. Use WSL (Windows Subsystem for Linux) and run `.sh` scripts

### Linux/Mac: "Permission denied"

Make scripts executable:
```bash
chmod +x package.sh
chmod +x package-production.sh
chmod +x package-electron.sh
```

---

## Script Equivalents

| Windows PowerShell          | Linux/Mac/Git Bash    |
|----------------------------|----------------------|
| `.\package.ps1`            | `./package.sh`       |
| `.\package-production.ps1` | `./package-production.sh` |
| `.\package-electron.ps1`   | `./package-electron.sh` |

Both sets of scripts do the same thing, just written for different shells!

---

## Distribution Methods Comparison

| Method | Size | Best For | Requirements |
|--------|------|----------|--------------|
| **Production Build** | ~5-10 MB | Web hosting, quick sharing | Python or Node.js |
| **Electron Desktop** | ~100-150 MB | End users, native feel | None (self-contained) |
| **Docker Container** | ~60-150 MB | Cloud, enterprise, DevOps | Docker |

---

## Common Issues

### Issue: "npm: command not found"
**Solution**: Install Node.js from https://nodejs.org/

### Issue: "docker: command not found"
**Solution**: Install Docker Desktop from https://www.docker.com/products/docker-desktop/

### Issue: Electron build fails
**Solution**: Make sure you've run the setup script first:
```bash
# Windows
.\package-electron.ps1

# Linux/Mac
./package-electron.sh
```

### Issue: Production build works but app doesn't connect
**Solution**: Ensure Octane Render is running with LiveLink enabled:
- Open Octane Render
- Go to Help → LiveLink
- Check that LiveLink is enabled on port 51022

---

## Need Help?

- **Documentation**: See `DISTRIBUTION-GUIDE.md` for complete packaging guide
- **Electron Guide**: See `ELECTRON-PACKAGING.md` (generated after running electron setup)
- **Docker Guide**: See `DOCKER-PACKAGING.md` for containerization details
- **GitHub**: https://github.com/ultrafish22L/grpcSamples

---

**Last Updated**: 2025-01-16
