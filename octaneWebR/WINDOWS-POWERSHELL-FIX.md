# Windows PowerShell Encoding Fix

## Problem (BEFORE)

Running PowerShell scripts created on Linux resulted in garbled output and failures:

```powershell
PS> .\package-electron.ps1

â• â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•—
â•      Building octaneWebR Electron Desktop App     â•
â•šâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•

âš ï¸ This script will set up Electron packaging.
ðŸ¦ Installing Electron dependencies...
âœ… Electron packaging setup complete!

all : The term 'all' is not recognized as a cmdlet
At package-electron.ps1:243 char:52
```

**Cause**: Windows PowerShell misinterpreted UTF-8 characters without BOM.

---

## Solution (AFTER)

All scripts now use **pure ASCII** + **UTF-8 BOM**:

```powershell
PS> .\package-electron.ps1

+===================================================+
|      Building octaneWebR Electron Desktop App     |
+===================================================+

[Warning]  This script will set up Electron packaging.
[Package] Installing Electron dependencies...
[OK] Electron packaging setup complete!

[Steps] Next steps:
   1. Read ELECTRON-PACKAGING.md for detailed instructions
   2. Test development build:
      - Terminal 1: npm run dev
      - Terminal 2: npm run electron:dev
   3. Build production app:
      - npm run electron:build        (all platforms)
      - npm run electron:build:win    (Windows only)

[Package] Built apps will be in: dist/electron/
```

**Result**: Clean, readable output without encoding errors!

---

## Character Replacements

| Before (UTF-8) | After (ASCII) | Description |
|----------------|---------------|-------------|
| `╔═══╗` | `+===+` | Box top |
| `║` | `|` | Box sides |
| `╚═══╝` | `+===+` | Box bottom |
| `📦` | `[Package]` | Package emoji |
| `🚀` | `[Start]` | Start emoji |
| `✅` | `[OK]` | Checkmark emoji |
| `⚠️` | `[Warning]` | Warning emoji |
| `❌` | `[Error]` | Error emoji |
| `📋` | `[Steps]` | Steps emoji |
| `•` | `-` | Bullet point |

---

## Technical Details

### What Changed

1. **All non-ASCII characters removed** (chars with value > 127)
2. **UTF-8 BOM added** (0xEF 0xBB 0xBF at file start)
3. **Files saved with `utf-8-sig` encoding**

### Why This Works

- **ASCII characters (0-127)** work universally across all systems
- **UTF-8 BOM** signals to PowerShell: "This file is UTF-8 encoded"
- Without BOM, PowerShell guesses encoding and often gets it wrong
- With BOM, PowerShell knows exactly how to read the file

### Verification

All three PowerShell scripts are now safe:
- ✅ `package-electron.ps1` - 100% ASCII + BOM
- ✅ `package-production.ps1` - 100% ASCII + BOM  
- ✅ `package.ps1` - 100% ASCII + BOM

---

## How to Use

Simply run the scripts in Windows PowerShell:

```powershell
# Navigate to octaneWebR directory
cd C:\otoyla\GRPC\dev\grpcSamples\octaneWebR

# Run interactive menu
.\package.ps1

# Or run directly:
.\package-electron.ps1      # Setup Electron desktop app
.\package-production.ps1    # Build production package
```

### If Scripts Won't Run

PowerShell execution policy might block scripts:

**Quick fix (one-time):**
```powershell
powershell -ExecutionPolicy Bypass -File .\package.ps1
```

**Permanent fix (allow your scripts):**
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

Then run scripts normally:
```powershell
.\package.ps1
```

---

## Notes for Linux/Mac Users

The bash scripts (`.sh` files) still work perfectly on Linux/Mac with all the fancy Unicode:

```bash
# Linux/Mac/Git Bash
./package.sh               # Interactive menu
./package-electron.sh      # Electron setup
./package-production.sh    # Production build
```

**Choose the right script for your platform:**
- Windows PowerShell → Use `.ps1` files (ASCII-safe)
- Linux/Mac/Git Bash → Use `.sh` files (Unicode-pretty)

---

## Summary

| Issue | Status |
|-------|--------|
| Garbled box-drawing characters | ✅ Fixed - ASCII art instead |
| Broken emojis | ✅ Fixed - [Bracketed text] instead |
| "all is not recognized" error | ✅ Fixed - No encoding issues |
| UTF-8 without BOM | ✅ Fixed - BOM added |
| Scripts work on Windows | ✅ Fixed - All scripts tested |

**All packaging scripts now work perfectly on Windows PowerShell!** 🎉

---

**Last Updated**: 2025-01-16  
**Tested On**: Windows PowerShell 5.1+  
**Encoding**: UTF-8 with BOM (utf-8-sig)  
**Character Set**: Pure ASCII (0x00-0x7F only)
