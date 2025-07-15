# Avalonia Cross-Platform Setup Guide

## Overview

This guide covers installing all necessary dependencies to build and run the Avalonia gRPC Test Application on Windows, Linux, and macOS. The application provides a modern GUI interface for testing Octane's gRPC API.

## Prerequisites

All platforms require:
- **Git** (for repository cloning)
- **CMake 3.10+** (for C++ components)
- **.NET SDK 8.0+** (for Avalonia application)

## Windows Setup

### 1. Install .NET SDK
```powershell
# Download and install from Microsoft
# https://dotnet.microsoft.com/download/dotnet/8.0

# Or using winget
winget install Microsoft.DotNet.SDK.8

# Or using Chocolatey
choco install dotnet-8.0-sdk
```

### 2. Install Visual Studio Build Tools
```powershell
# Visual Studio 2022 Community (recommended)
winget install Microsoft.VisualStudio.2022.Community

# Or Visual Studio Build Tools (minimal)
winget install Microsoft.VisualStudio.2022.BuildTools
```

### 3. Install CMake
```powershell
# Using winget
winget install Kitware.CMake

# Or using Chocolatey
choco install cmake
```

### 4. Install Git
```powershell
winget install Git.Git
```

### 5. Verify Installation
```powershell
dotnet --version          # Should show 8.0.x
cmake --version           # Should show 3.10+
git --version            # Should show git version
```

### 6. Build and Run
```powershell
git clone https://github.com/ultrafish22L/grpcSamples.git
cd grpcSamples
mkdir build
cd build
cmake ..
cmake --build . --target AvaloniaGrpcTest

# Run the application
cd ..\avaloniaTest\AvaloniaGrpcTest
dotnet run --configuration Release
```

## Linux Setup (Ubuntu/Debian)

### 1. Update Package Manager
```bash
sudo apt update
sudo apt upgrade -y
```

### 2. Install .NET SDK
```bash
# Add Microsoft package repository
wget https://packages.microsoft.com/config/ubuntu/$(lsb_release -rs)/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
sudo dpkg -i packages-microsoft-prod.deb
rm packages-microsoft-prod.deb

# Install .NET SDK
sudo apt update
sudo apt install -y dotnet-sdk-8.0
```

### 3. Install Build Dependencies
```bash
# Essential build tools
sudo apt install -y build-essential cmake git

# OpenGL and graphics libraries
sudo apt install -y libgl1-mesa-dev libglu1-mesa-dev

# X11 development libraries (for GUI)
sudo apt install -y libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev

# Wayland development libraries (optional)
sudo apt install -y libwayland-dev libxkbcommon-dev

# gRPC and Protocol Buffers
sudo apt install -y libgrpc++-dev libprotobuf-dev protobuf-compiler-grpc

# Additional libraries for Avalonia
sudo apt install -y libfontconfig1-dev libfreetype6-dev
```

### 4. Install Avalonia Dependencies
```bash
# Runtime libraries for Avalonia
sudo apt install -y libice6 libsm6 libxext6 libxrender1

# Audio libraries (if needed)
sudo apt install -y libasound2-dev

# Additional graphics libraries
sudo apt install -y libgtk-3-dev
```

### 5. Verify Installation
```bash
dotnet --version          # Should show 8.0.x
cmake --version           # Should show 3.10+
git --version            # Should show git version
```

### 6. Build and Run
```bash
git clone https://github.com/ultrafish22L/grpcSamples.git
cd grpcSamples

# Initialize submodules
git submodule update --init --recursive

# Build
mkdir build
cd build
cmake ..
make -j$(nproc) AvaloniaGrpcTest

# Run the application (requires X11 or Wayland)
cd ../avaloniaTest/AvaloniaGrpcTest
dotnet run --configuration Release
```

## Linux Setup (CentOS/RHEL/Fedora)

### 1. Install .NET SDK
```bash
# Fedora
sudo dnf install dotnet-sdk-8.0

# CentOS/RHEL (add Microsoft repository first)
sudo rpm -Uvh https://packages.microsoft.com/config/centos/8/packages-microsoft-prod.rpm
sudo dnf install dotnet-sdk-8.0
```

### 2. Install Build Dependencies
```bash
# Fedora
sudo dnf groupinstall "Development Tools"
sudo dnf install cmake git mesa-libGL-devel mesa-libGLU-devel
sudo dnf install libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel
sudo dnf install grpc-devel protobuf-devel

# CentOS/RHEL
sudo yum groupinstall "Development Tools"
sudo yum install cmake git mesa-libGL-devel mesa-libGLU-devel
sudo yum install libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel
```

## macOS Setup

### 1. Install Xcode Command Line Tools
```bash
xcode-select --install
```

### 2. Install Homebrew (if not installed)
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 3. Install .NET SDK
```bash
# Using Homebrew
brew install --cask dotnet

# Or download from Microsoft
# https://dotnet.microsoft.com/download/dotnet/8.0
```

### 4. Install Build Dependencies
```bash
# Essential tools
brew install cmake git

# gRPC and Protocol Buffers
brew install grpc protobuf abseil

# Additional libraries
brew install pkg-config
```

### 5. Verify Installation
```bash
dotnet --version          # Should show 8.0.x
cmake --version           # Should show 3.10+
git --version            # Should show git version
```

### 6. Build and Run
```bash
git clone https://github.com/ultrafish22L/grpcSamples.git
cd grpcSamples

# Initialize submodules
git submodule update --init --recursive

# Build
mkdir build
cd build
cmake ..
make -j$(sysctl -n hw.ncpu) AvaloniaGrpcTest

# Run the application
cd ../avaloniaTest/AvaloniaGrpcTest
dotnet run --configuration Release
```

## Troubleshooting

### Common Issues

#### .NET SDK Not Found
```bash
# Verify installation
dotnet --info

# Check PATH
echo $PATH | grep dotnet

# Reinstall if necessary
```

#### Missing Graphics Libraries (Linux)
```bash
# Install additional graphics packages
sudo apt install -y libgdiplus libc6-dev

# For older systems
sudo apt install -y libicu-dev
```

#### Permission Issues (Linux/macOS)
```bash
# Fix permissions for .NET
sudo chown -R $(whoami) ~/.dotnet
sudo chown -R $(whoami) ~/.nuget
```

#### Display Issues (Linux)
```bash
# Check display environment
echo $DISPLAY

# For WSL2 users
export DISPLAY=:0

# For remote systems
ssh -X user@hostname
```

### Platform-Specific Notes

#### Windows
- **Visual Studio**: Full IDE provides better debugging experience
- **Windows Terminal**: Recommended for better PowerShell experience
- **WSL2**: Can run Linux version if preferred

#### Linux
- **Desktop Environment**: Works with GNOME, KDE, XFCE, etc.
- **Wayland**: Supported but X11 is more stable
- **Remote Desktop**: May require additional X11 forwarding setup

#### macOS
- **Rosetta 2**: Required for Apple Silicon Macs running x64 dependencies
- **Security**: May need to allow applications in System Preferences
- **Homebrew**: Recommended package manager for dependencies

## Build Targets

### CMake Targets
```bash
# Build only Avalonia application
make AvaloniaGrpcTest

# Run Avalonia application (requires display)
make run-avalonia

# Build all C++ components
make all

# Clean build
make clean
```

### Direct .NET Commands
```bash
cd avaloniaTest/AvaloniaGrpcTest

# Restore packages
dotnet restore

# Build application
dotnet build --configuration Release

# Run application
dotnet run --configuration Release

# Publish self-contained
dotnet publish -c Release -r win-x64 --self-contained
dotnet publish -c Release -r linux-x64 --self-contained
dotnet publish -c Release -r osx-x64 --self-contained
```

## Development Environment

### Recommended IDEs

#### Windows
- **Visual Studio 2022** (full IDE experience)
- **Visual Studio Code** (lightweight, cross-platform)
- **JetBrains Rider** (premium, excellent Avalonia support)

#### Linux
- **Visual Studio Code** (recommended)
- **JetBrains Rider** (premium)
- **MonoDevelop** (open source)

#### macOS
- **Visual Studio for Mac** (being discontinued)
- **Visual Studio Code** (recommended)
- **JetBrains Rider** (premium)

### Useful Extensions

#### Visual Studio Code
- C# Dev Kit
- Avalonia for VSCode
- CMake Tools
- GitLens

#### Visual Studio
- Avalonia for Visual Studio
- CMake integration (built-in)

## Next Steps

After successful installation:

1. **Test the build**: Follow the build instructions for your platform
2. **Run the application**: Verify the GUI launches correctly
3. **Test gRPC connectivity**: Use the application to test Octane connections
4. **Explore the code**: Review the implementation in `avaloniaTest/AvaloniaGrpcTest/`
5. **Customize**: Modify the UI or add new gRPC API calls

For detailed implementation information, see `AVALONIA_INTEGRATION.md`.