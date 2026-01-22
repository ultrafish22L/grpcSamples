# octaneWebR - Quick Start Guide

**Get up and running with octaneWebR in 10 minutes**

> 🤖 **AUTONOMOUS DEVELOPMENT MODE ACTIVE** - This project continuously implements features from [Octane SE Manual](https://docs.otoy.com/standaloneSE/CoverPage.html) in autonomous loop

---

## 🎯 **Prerequisites Checklist**

Before you begin, ensure you have:

- [ ] **Octane Render** installed (any recent version with LiveLink support)
- [ ] **Node.js 18+** installed (`node --version` to check)
- [ ] **npm** installed (comes with Node.js)
- [ ] **Git** installed (for version control)
- [ ] **Code editor** (VS Code recommended)
- [ ] **Modern browser** (Chrome, Firefox, Edge, or Safari)

---

## 🚀 **Step 1: Install & Run Octane**

### **Start Octane Render**
1. Launch Octane Render from octaneGRPC/octane.exe
2. Enable grpc server
   - Click Enable
   - Set address to 127.0.0.1:51022
   - Restart Octane
3. Open any scene (or create new empty scene)

---

## 🚀 **Step 2: Clone & Install octaneWebR**

### **Clone Repository**
```bash
git clone https://github.com/ultrafish22L/grpcSamples.git
cd grpcSamples/octaneWebR
```

### **Install Dependencies**
```bash
npm install
```

**Expected output**:
```
added 250 packages in 30s
```

### **Verify Installation**
```bash
npm list react
```

**Expected**: Should show React 18.2.0 or higher

---

## 🚀 **Step 3: Start Development Server**

### **Run Dev Server**
```bash
npm run dev
```

**Expected output**:
```
📦 Proto files ready for lazy loading from: /path/to/server/proto
  VITE v5.4.21  ready in 296 ms
  ➜  Local:   http://localhost:43930/
  ➜  Network: http://172.17.0.3:43930/
```

### **Access Application**
1. Open browser (Chrome recommended)
2. Navigate to **http://localhost:43930**
3. You should see the octaneWebR interface load

---

## 🚀 **Step 4: Verify Connection**

### **Check Browser Console**
Open Chrome DevTools (F12 or right-click → Inspect) and check console:

**Expected logs**:
```
✅ Connected to Octane
✅ Scene tree loaded (X nodes)
```

**If you see errors**:
- ❌ "Cannot connect to Octane" → Go to [Troubleshooting](#troubleshooting)
- ❌ "WebSocket closed" → Octane disconnected, restart Octane

### **Test Basic Functionality**
1. **Scene Outliner** (left panel): Should show nodes from your Octane scene
2. **Node Graph Editor** (center): Should display node graph
3. **Node Inspector** (right panel): Should show "No node selected"

---

## 🎉 **You're Ready!**

At this point, you should have:
- ✅ Octane running with LiveLink enabled
- ✅ octaneWebR dev server running on http://localhost:43930
- ✅ Browser showing octaneWebR UI
- ✅ Connection verified in console logs

---

## 🧪 **Quick Feature Test**

### **Test 1: Create a Node**
1. Right-click in **Node Graph Editor** (center panel)
2. Context menu appears
3. Hover over **Materials** → Select **Diffuse material**
4. New node appears in graph
5. Check Octane SE: Node should be created there too ✅

### **Test 2: Connect Pins**
1. Drag from **output pin** (bottom of node) to **input pin** (top of another node)
2. Edge (connection line) appears
3. Check Octane SE: Connection should appear there too ✅

### **Test 3: Edit Parameter**
1. Click a node in graph
2. **Node Inspector** (right panel) shows parameters
3. Change a value (e.g., toggle a checkbox)
4. Check Octane SE: Parameter should update there too ✅

### **Test 4: Search Nodes**
1. Press **Ctrl+F**
2. Search dialog appears
3. Type "diffuse"
4. Results show matching nodes
5. Click result → Node selected in graph ✅

### **Test 5: Copy/Paste**
1. Select a node (click it)
2. Press **Ctrl+C** (copy)
3. Press **Ctrl+V** (paste)
4. New duplicate node appears
5. Check Octane SE: New node created there too ✅

---

## 📚 **Next Steps**

### **For Users**
- Explore all features in the UI
- Try keyboard shortcuts (Ctrl+C, Ctrl+V, Ctrl+F, Delete)
- Read the **[Octane SE Manual](https://docs.otoy.com/standaloneSE/)** to understand features
- Report bugs or request features

### **For Developers**
1. Read **[README.md](./README.md)** - Full project documentation and current status
2. Read **[REPRO_PROMPT.md](./REPRO_PROMPT.md)** - Context for debugging and AI assistance
3. Browse code starting from **client/src/App.tsx**
4. Understand proto files in **server/proto/**
5. Review [Octane SE Manual](https://docs.otoy.com/standaloneSE/) for feature references
6. Get approval from maintainer before starting work

---

## 🆘 **Troubleshooting**

### **Problem: "Cannot connect to Octane"**

**Symptoms**:
- Browser console shows red error: "Connection refused"
- Scene Outliner is empty
- Node Graph Editor shows no nodes

**Solutions**:
1. **Verify Octane is running**:
   - Is Octane application open?
   - Is there a scene loaded?

2. **Verify LiveLink is enabled**:
   - In Octane: Help → LiveLink (should have checkmark)
   - Try toggling it off and on

3. **Check port 51022**:
   ```bash
   # On Windows (PowerShell)
   Test-NetConnection -ComputerName localhost -Port 51022
   
   # On macOS/Linux
   nc -zv localhost 51022
   ```
   - Should show "Connection successful" or "succeeded"
   - If fails: Port is blocked or Octane LiveLink not running

4. **Firewall check**:
   - Windows: Check Windows Firewall settings
   - macOS: System Preferences → Security → Firewall
   - Ensure port 51022 is allowed

5. **Restart everything**:
   ```bash
   # Stop octaneWebR (Ctrl+C in terminal)
   # Restart Octane
   # Re-enable LiveLink
   # Restart octaneWebR
   npm run dev
   ```

---

### **Problem: "npm install fails"**

**Symptoms**:
- `npm install` shows errors
- Dependencies not installed

**Solutions**:
1. **Check Node.js version**:
   ```bash
   node --version
   ```
   - Must be 18.0.0 or higher
   - If lower: Install latest from https://nodejs.org/

2. **Clear npm cache**:
   ```bash
   npm cache clean --force
   rm -rf node_modules package-lock.json
   npm install
   ```

3. **Check network connection**:
   - npm needs internet to download packages
   - Try different network if behind corporate firewall

4. **Use npm registry mirror** (if slow):
   ```bash
   npm config set registry https://registry.npmmirror.com
   npm install
   ```

---

### **Problem: "Build fails with TypeScript errors"**

**Symptoms**:
- `npm run build` shows red errors
- TypeScript compilation fails

**Solutions**:
1. **Check TypeScript version**:
   ```bash
   npx tsc --version
   ```
   - Should be 5.3.0 or higher

2. **Regenerate proto files** (if missing):
   ```bash
   npm run generate:proto
   ```

3. **Check for syntax errors**:
   - Read error messages carefully
   - Fix any red underlines in code editor
   - Ensure all imports are correct

4. **Ask for help**:
   - Copy error message
   - Share in team chat or GitHub issues

---

### **Problem: "Dev server won't start"**

**Symptoms**:
- `npm run dev` fails immediately
- Port already in use error

**Solutions**:
1. **Check if port 43930 is in use**:
   ```bash
   # On Windows (PowerShell)
   Get-Process -Id (Get-NetTCPConnection -LocalPort 43930).OwningProcess
   
   # On macOS/Linux
   lsof -i :43930
   ```

2. **Kill existing process**:
   ```bash
   # On Windows (PowerShell)
   Stop-Process -Id <PID>
   
   # On macOS/Linux
   kill <PID>
   ```

3. **Use different port**:
   ```bash
   # Edit vite.config.mts and change port
   # Then restart dev server
   npm run dev
   ```

---

### **Problem: "UI is blank/white screen"**

**Symptoms**:
- Browser shows white screen
- No UI elements visible

**Solutions**:
1. **Check browser console**:
   - Open DevTools (F12)
   - Look for red errors in Console tab
   - Share error message if present

2. **Clear browser cache**:
   - Chrome: Ctrl+Shift+Delete → Clear cached images and files
   - Firefox: Ctrl+Shift+Delete → Cache
   - Reload page with Ctrl+F5

3. **Try different browser**:
   - Test in Chrome, Firefox, Edge
   - If works in one but not another: Browser-specific issue

4. **Check for ad blockers**:
   - Disable ad blockers/extensions
   - Try incognito/private mode

---

### **Problem: "Changes not reflected in browser"**

**Symptoms**:
- Made code changes but UI doesn't update
- Old code still running

**Solutions**:
1. **Hard refresh browser**:
   - Windows: Ctrl+Shift+R or Ctrl+F5
   - macOS: Cmd+Shift+R

2. **Restart dev server**:
   ```bash
   # Stop server (Ctrl+C)
   # Start again
   npm run dev
   ```

3. **Clear Vite cache**:
   ```bash
   rm -rf node_modules/.vite
   npm run dev
   ```

4. **Check file is saved**:
   - Ensure code editor saved file (check for unsaved indicator)
   - Some editors require manual save (Ctrl+S)

---

## 🛠️ **Development Workflow (Quick Reference)**

For developers ready to contribute:

```
1. ⏸️  WAIT for task assignment
2. 📖 VERIFY feature exists in Octane SE manual
3. 🔍 CHECK proto files for required API methods
4. 💻 IMPLEMENT code changes
5. 🔨 BUILD with `npm run build` (must pass)
6. 🧪 TEST with `npm run dev` (recommended)
7. 📝 COMMIT with descriptive message
8. 🚀 PUSH to origin/main
9. 📚 UPDATE README.md with achievements
10. ✅ REPORT completion
```

**See README.md Contributing Guidelines for detailed process.**

---

## 📖 **Key Documentation Files**

| File | Purpose | When to Read |
|------|---------|--------------|
| **QUICKSTART.md** | This file! 10-minute setup guide | You're reading it 😊 |
| **README.md** | Complete project overview, features, status | After setup completes |
| **REPRO_PROMPT.md** | AI assistant context for debugging | When debugging or getting AI help |

---

## 🎓 **Learning Resources**

### **Technologies Used**
- [React 18 Docs](https://react.dev/) - UI framework
- [TypeScript Handbook](https://www.typescriptlang.org/docs/) - Type system
- [ReactFlow Docs](https://reactflow.dev/) - Node graph library
- [Vite Guide](https://vitejs.dev/guide/) - Build tool
- [Octane SE Manual](https://docs.otoy.com/standaloneSE/) - UI reference

### **Code Reading Path**
1. **client/src/App.tsx** - Root component, initialization
2. **client/src/services/OctaneClient.ts** - gRPC client, scene management
3. **client/src/components/NodeGraph/NodeGraphEditorNew.tsx** - Node graph editor
4. **client/src/components/NodeGraph/OctaneNode.tsx** - Custom node component
5. **client/src/components/SceneOutliner/SceneOutliner.tsx** - Scene tree viewer

---

## ✅ **Quick Start Checklist**

Before asking for help, verify:

- [ ] Octane is running with LiveLink enabled
- [ ] `npm install` completed successfully
- [ ] `npm run dev` started without errors
- [ ] Browser shows UI (not blank screen)
- [ ] Browser console shows "Connected to Octane"
- [ ] Scene Outliner shows nodes from Octane scene
- [ ] Can create a node via right-click menu
- [ ] Node appears in both octaneWebR and Octane SE

If all checked: **You're ready to go!** 🎉

If any unchecked: **See [Troubleshooting](#troubleshooting) section above**

---

## 🎯 **What's Next?**

### **Explore Features**
- Try all keyboard shortcuts (see UI tooltips)
- Experiment with node creation and connections
- Test parameter editing in Node Inspector
- Explore Scene Outliner tree navigation

### **Read Documentation**
- **README.md** for complete feature list and project status
- **REPRO_PROMPT.md** for debugging context and architecture overview

### **Start Contributing**
- Pick a task from implementation plan
- Get approval from maintainer
- Follow workflow process
- Submit your work

---

## 📞 **Getting Help**

### **Common Issues**
- 90% of issues are connection problems (Octane not running or LiveLink disabled)
- 9% are port conflicts (another process using port 43930 or 51022)
- 1% are actual bugs (report these!)

### **Where to Ask**
- **Team Chat**: Fastest response for quick questions
- **GitHub Issues**: For bugs or feature requests
- **Code Comments**: For specific implementation questions

### **What to Include**
- Your OS (Windows, macOS, Linux)
- Node.js version (`node --version`)
- Octane version
- Error messages (full text or screenshot)
- What you tried already

---

**Congratulations!** You're now ready to use octaneWebR. Happy rendering! 🎨✨

---

**Last Updated**: 2025-01-22  
**Version**: 1.0.0  
**Estimated Setup Time**: 10 minutes
