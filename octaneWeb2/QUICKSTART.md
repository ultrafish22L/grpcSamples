# OctaneWeb2 - Quick Start Guide

Get OctaneWeb2 running locally in your browser in 5 minutes.

---

## ⚡ TL;DR (Quick Commands)

```bash
# Clone the repo
git clone https://github.com/ultrafish22L/grpcSamples.git
cd grpcSamples/octaneWeb2

# Install dependencies
npm install

# Start development server
npm run dev

# Open browser
# Navigate to http://localhost:46466
```

---

## 📋 Prerequisites

### Required Software

1. **Node.js** (v18 or higher)
   - Download: https://nodejs.org/
   - Verify: `node --version` (should show v18+)

2. **npm** (comes with Node.js)
   - Verify: `npm --version` (should show v8+)

3. **Git**
   - Download: https://git-scm.com/
   - Verify: `git --version`

4. **Octane Render** (for full functionality)
   - With LiveLink enabled (Help → LiveLink in Octane)
   - Running on default port 51022

5. **Web Browser** (modern browser with ES2020+ support)
   - Chrome 90+
   - Firefox 88+
   - Edge 90+
   - Safari 14+

---

## 🚀 Installation Steps

### Step 1: Clone the Repository

```bash
# Clone from GitHub
git clone https://github.com/ultrafish22L/grpcSamples.git

# Navigate to the project
cd grpcSamples/octaneWeb2
```

### Step 2: Install Dependencies

```bash
# Install all npm packages
npm install

# This will install:
# - React 19.2.0
# - TypeScript 5.9.3
# - Vite 7.2.0
# - Zustand 5.0.8
# - React Query 5.90.7
# - Other dependencies
```

**Expected output**:
```
added 342 packages, and audited 343 packages in 15s
found 0 vulnerabilities
```

### Step 3: Start Development Server

```bash
# Start Vite dev server
npm run dev
```

**Expected output**:
```
  VITE v7.2.0  ready in 140 ms

  ➜  Local:   http://localhost:46466/
  ➜  Network: http://172.17.0.3:46466/
  ➜  press h + enter to show help
```

### Step 4: Open in Browser

1. Open your web browser
2. Navigate to: **http://localhost:46466**
3. You should see the OctaneWeb2 interface!

---

## 🎨 What You'll See

When you first open OctaneWeb2, you'll see:

```
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃ File Edit Script Module Cloud Window Help    [●] Ready [Connect] ┃
┣━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━┫
┃ Scene Outliner │   Render Viewport        │  Node Inspector   ┃
┃ ━━━━━━━━━━━━━━ │   ━━━━━━━━━━━━━━━        │  ━━━━━━━━━━━━━━━  ┃
┃                │                          │                   ┃
┃ No scene loaded│        🎨                │ No node selected  ┃
┃                │                          │                   ┃
┃ Connect to     │  Render viewport ready   │ Select a node to  ┃
┃ Octane to view │                          │ view parameters   ┃
┃ scene hierarchy│  Connect to Octane to    │                   ┃
┃                │  start rendering         │                   ┃
┣━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━┫
┃ Status: Ready  │ Samples: 0  │ FPS: 0  OctaneWeb2 - React Ed. ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
```

**UI Features**:
- **Menu Bar** (top) - File operations and connection controls
- **Scene Outliner** (left) - Scene hierarchy tree
- **Render Viewport** (center) - Live render display
- **Node Inspector** (right) - Node parameter editor
- **Status Bar** (bottom) - Status info and FPS counter

---

## 🔌 Connecting to Octane (Optional)

To connect OctaneWeb2 to Octane Render:

### Step 1: Start Octane with LiveLink

1. **Launch Octane Render**
2. **Enable LiveLink**:
   - Menu: `Help → LiveLink`
   - Or press the LiveLink button in Octane toolbar
3. **Verify port**: Default is `51022`

### Step 2: Start the Python Proxy

The proxy bridges browser HTTP to Octane gRPC:

```bash
# Open a new terminal
cd grpcSamples/octaneProxy

# Start the proxy
python octane_proxy.py
```

**Expected output**:
```
Starting Octane HTTP-to-gRPC Proxy Server...
Server running on http://0.0.0.0:51023
Connected to Octane LiveLink at localhost:51022
```

**Note**: Keep this terminal running while using OctaneWeb2.

### Step 3: Connect in Browser

1. In OctaneWeb2, click the **"Connect"** button (top-right)
2. Connection status should change:
   - Dot color: Yellow → Green
   - Text: "Ready" → "Connected"
3. Scene hierarchy will appear in left panel
4. Render frames will display in center viewport

---

## 📁 Project Structure

```
octaneWeb2/
├── src/                    # Source code
│   ├── components/         # React components
│   ├── hooks/              # Custom hooks
│   ├── store/              # Zustand state stores
│   ├── api/                # API client
│   ├── types/              # TypeScript types
│   ├── utils/              # Helper functions
│   └── styles/             # Global CSS
├── public/                 # Static assets
├── node_modules/           # Dependencies (created by npm install)
├── package.json            # Project dependencies
├── tsconfig.json           # TypeScript config
├── vite.config.ts          # Vite config
└── index.html              # HTML entry point
```

---

## 🛠️ Development Workflow

### Hot Module Replacement (HMR)

Vite provides **instant feedback** on code changes:

1. Edit any file in `src/`
2. Save the file
3. Browser **automatically updates** (no page reload!)

**What triggers HMR**:
- `.tsx` / `.ts` files - Component/logic updates
- `.css` files - Style updates
- Most config changes (some require restart)

### TypeScript Compilation

TypeScript errors show in terminal as you code:

```bash
# Terminal shows:
src/components/MyComponent.tsx:12:5 - error TS2322: 
  Type 'string' is not assignable to type 'number'.
```

Fix the error, save, and it disappears instantly.

### Browser DevTools

Press **F12** to open DevTools:
- **Console** - View logs and errors
- **Network** - Inspect API calls
- **React DevTools** - Inspect component tree (install extension)

---

## 📝 Common Tasks

### View Current Status

Check project progress and metrics:

```bash
cat STATUS.md
```

### Build for Production

Create optimized production build:

```bash
npm run build
```

Output goes to `dist/` folder.

### Preview Production Build

Test the production build locally:

```bash
npm run preview
```

Opens at http://localhost:4173

### Check TypeScript Errors

Compile TypeScript and show all errors:

```bash
npm run build
```

If successful, shows: `✓ built in 2.5s`

### Clean Install

Remove and reinstall dependencies:

```bash
rm -rf node_modules package-lock.json
npm install
```

---

## 🚨 Troubleshooting

### Port Already in Use

**Error**: `Port 46466 is in use`

**Solution**:
```bash
# Option 1: Kill the process using the port
# On Windows:
netstat -ano | findstr :46466
taskkill /PID <PID> /F

# On Mac/Linux:
lsof -ti:46466 | xargs kill

# Option 2: Change port in vite.config.ts
# Edit line 8: port: 46466 → port: 3000
```

### Module Not Found

**Error**: `Cannot find module 'react'`

**Solution**:
```bash
npm install
```

### TypeScript Errors

**Error**: `Property 'X' does not exist on type 'Y'`

**Solution**: Check type definitions in `src/types/octane.ts`

### Can't Connect to Octane

**Symptoms**: Click "Connect" but nothing happens

**Checklist**:
1. ✅ Is Octane running?
2. ✅ Is LiveLink enabled? (Help → LiveLink)
3. ✅ Is Python proxy running? (`python octane_proxy.py`)
4. ✅ Is port 51022 accessible?
5. ✅ Check browser console for errors (F12)

**Test proxy manually**:
```bash
curl http://localhost:51023/ping
# Should return: {"status": "ok"}
```

### Browser Not Auto-Refreshing

**Solution**: Hard refresh
- **Windows/Linux**: `Ctrl + Shift + R`
- **Mac**: `Cmd + Shift + R`

### White Screen / Nothing Renders

**Check**:
1. Open browser console (F12)
2. Look for error messages
3. Verify dev server is running: `npm run dev`

---

## 🎯 Current Status (Phase 1)

### What's Implemented ✅

- ✅ **Basic UI Layout** - 3-panel grid with menu and status bars
- ✅ **React Components** - MainLayout, MenuBar, StatusBar, RenderViewport
- ✅ **State Management** - Zustand stores for connection and render
- ✅ **API Client** - Type-safe OctaneClient singleton
- ✅ **TypeScript** - Full type coverage, strict mode
- ✅ **OTOY Theme** - Professional dark theme with orange accents
- ✅ **Development Server** - Vite with HMR

### What's Coming Next 🔜

**Phase 2: Core Rendering** (1-2 days)
- WebSocket render callback stream
- HDR/LDR buffer processing
- Live render display in viewport
- FPS counter updates

**Phase 3: Camera Controls** (1 day)
- Mouse drag to rotate camera
- Mouse wheel to zoom
- Sync with Octane in real-time

**Phase 4-11**: Scene outliner, node inspector, node graph, keyboard shortcuts, etc.

**See**: `IMPLEMENTATION_PLAN.md` for full roadmap

---

## 📚 Additional Documentation

### Essential Docs (Read These First)
- **INDEX.md** - Documentation hub with quick links
- **README.md** - Project overview and architecture
- **QUICKSTART.md** - This file

### Learning Resources
- **CODE_COMPARISON.md** - Before/after code examples
- **PROJECT_TREE.md** - File structure and organization
- **UI_MOCKUP.md** - Visual layout and styling guide

### Planning & Progress
- **IMPLEMENTATION_PLAN.md** - Detailed 11-phase plan
- **STATUS.md** - Current progress and metrics
- **CHANGELOG.md** - Version history

### Reference
- **PROJECT_SUMMARY.md** - Executive overview
- **COMPLETION_SUMMARY.md** - Phase 1 completion report

---

## 💡 Tips for Success

### For First-Time Users

1. **Start Simple**: Just run `npm install` and `npm run dev`
2. **Explore the UI**: Click around, see the layout
3. **Read the Docs**: Check INDEX.md for navigation
4. **Connect Later**: Octane connection is optional for UI exploration

### For Developers

1. **Use TypeScript**: Let the compiler catch errors
2. **Follow Patterns**: Check existing components for examples
3. **Use `@/` imports**: Cleaner than `../../` paths
4. **Check STATUS.md**: See what's done and what's next
5. **Update docs**: Keep STATUS.md and CHANGELOG.md current

### For Contributors

1. **Read IMPLEMENTATION_PLAN.md**: Understand the roadmap
2. **Pick a Phase**: Choose tasks from upcoming phases
3. **Follow Structure**: Put files in correct directories
4. **Test Locally**: Verify changes before committing
5. **Update Progress**: Mark tasks complete in STATUS.md

---

## 🔗 Useful Links

### Project Links
- **GitHub Repo**: https://github.com/ultrafish22L/grpcSamples
- **OctaneWeb2 Folder**: `/grpcSamples/octaneWeb2/`

### External Resources
- **React Docs**: https://react.dev
- **TypeScript Docs**: https://www.typescriptlang.org/docs/
- **Vite Docs**: https://vitejs.dev
- **Zustand**: https://github.com/pmndrs/zustand
- **React Query**: https://tanstack.com/query/latest

### Octane Resources
- **Octane Render**: https://home.otoy.com/render/octane-render/
- **LiveLink Guide**: (in Octane docs)

---

## 📞 Support

### Getting Help

1. **Check Documentation**: Read INDEX.md for doc navigation
2. **Check Troubleshooting**: See section above
3. **Browser Console**: Press F12, check for errors
4. **GitHub Issues**: Open issue on GitHub repo
5. **Original octaneWeb**: Compare with `/grpcSamples/octaneWeb/`

### Reporting Issues

Include this info:
- Node.js version: `node --version`
- npm version: `npm --version`
- Operating system
- Browser and version
- Error messages (from terminal and browser console)
- Steps to reproduce

---

## ✅ Verification Checklist

After installation, verify everything works:

- [ ] Node.js installed (v18+)
- [ ] npm installed (v8+)
- [ ] Repository cloned
- [ ] `npm install` completed successfully
- [ ] `npm run dev` starts server
- [ ] Browser opens http://localhost:46466
- [ ] UI loads with 3-panel layout
- [ ] Menu bar visible at top
- [ ] Status bar visible at bottom
- [ ] No errors in browser console
- [ ] No errors in terminal

**Optional (with Octane)**:
- [ ] Octane running with LiveLink enabled
- [ ] Python proxy running (`python octane_proxy.py`)
- [ ] "Connect" button turns green
- [ ] Scene appears in outliner
- [ ] Render displays in viewport

---

## 🎉 Success!

If you see the OctaneWeb2 interface in your browser, you're all set!

**Next Steps**:
1. Explore the UI
2. Read **STATUS.md** to see progress
3. Check **IMPLEMENTATION_PLAN.md** for upcoming features
4. (Optional) Connect to Octane for full functionality

**Questions?** Check **INDEX.md** for documentation navigation.

---

## 📈 Project Metrics

- **Lines of Code**: 542 TypeScript (Phase 1)
- **Target**: ~6,000 TypeScript (full project)
- **Progress**: 9% complete
- **Components**: 7 created, ~33 remaining
- **Stores**: 2 created, 4 remaining
- **Hooks**: 0 created, 10 remaining

**Status**: ✅ Phase 1 Complete | 🔄 Phase 2 In Progress

---

**Happy coding! 🚀**

*Last Updated: 2025-11-05*
