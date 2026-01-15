# OctaneWebR Development Workflow

**Mission**: Create a pixel-perfect React/TypeScript clone of Octane Render Studio Standalone Edition with complete functional parity through real-time gRPC API integration.

---

## 🤖 AUTONOMOUS DEVELOPMENT MODE (ACTIVE)

**Process**: Continuous autonomous loop picking tasks from Octane SE manual:

1. **Pick** unimplemented feature from [Octane SE Manual](https://docs.otoy.com/standaloneSE/CoverPage.html)
2. **Implement** with TypeScript/React
3. **Build** (`npm run build`) - check for TypeScript errors
4. **Test** (`npm run dev`) - verify functionality works
5. **Commit** with clear description
6. **Push** to origin/main
7. **Repeat** - immediately pick next task

**No waiting for approval** - continue until explicitly stopped or blocked.

---

## 🎯 Core Principles (Non-Negotiable)

### 1. Manual as Single Source of Truth
- **Reference**: [Octane SE Manual](https://docs.otoy.com/standaloneSE/CoverPage.html)
- **Rule**: If a feature is NOT documented in the manual, DO NOT implement it
- **Why**: Prevents hallucinating features that don't exist in Octane SE
- **Verification**: Always cite manual section when implementing features

### 2. Real Octane API Only (No Mocks)
- **Rule**: Every feature must use real gRPC API calls to live Octane instance
- **Proto Files**: `/grpcSamples/sdk/src/api/grpc/protodef/*.proto`
- **Verification**: Check proto files before implementing any API call
- **Why**: Ensures production-ready integration, not simulated behavior

### 3. **TypeScript Strict Mode (Type Safety Required)**
- **Rule**: All code must pass TypeScript compilation with no errors
- **Build Command**: `npm run build` must pass before any commit
- **Why**: Catch errors at compile time, not runtime

### 4. **Task-Based Development (One Task at a Time)**
- **Rule**: Wait for explicit task approval before starting work
- **Process**: Complete → Build → Test → Commit → Push → Stop → Wait
- **Why**: Maintains focus, ensures quality, prevents scope creep

---

## 🔄 **Development Workflow Loop (Step-by-Step)**

### **STEP 1: Task Assignment** ⏸️ STOP AND WAIT
- **Action**: Wait for user to assign specific task
- **Format**: User will provide task from `OCTANE_STANDALONE_IMPLEMENTATION_PLAN.md`
- **Example**: "Implement TASK 1.5.1 - Enhanced pin tooltips"
- ⚠️ **DO NOT** start any work without explicit task assignment

### **STEP 2: Manual Verification** 📖 VERIFY FIRST
- **Action**: Browse Octane SE manual to verify feature exists
- **URL**: `https://docs.otoy.com/standaloneSE/` (specific section)
- **What to Look For**:
  - Screenshots showing the feature
  - Keyboard shortcuts (if applicable)
  - Behavior descriptions
  - UI element styling
- ⚠️ **CRITICAL**: If feature not found in manual → Ask user for clarification
- **Example**:
  ```
  ✅ VERIFIED: "Copy/Paste nodes with Ctrl+C/Ctrl+V" found in manual
  ❌ NOT FOUND: "Edge context menu" → Ask user if this exists in Octane SE
  ```

### **STEP 3: Proto File Research** 🔍 CHECK API
- **Action**: Identify required gRPC API calls in proto files
- **Location**: `/grpcSamples/sdk/src/api/grpc/protodef/`
- **Key Files**:
  - `apinodesystem.proto` - Node operations
  - `apimodulenodegraph.proto` - Node graph operations
  - `octaneinfos.proto` - Node/pin metadata
  - `apilocaldb.proto` - Material database
- **What to Find**:
  - Exact method names (e.g., `createNode`, not `addNode`)
  - Required parameters
  - Response types
- **Example**:
  ```bash
  # Search for node deletion API
  grep -n "destroy\|delete" apinodesystem.proto
  # Result: ApiNode.destroy() exists (not deleteNode!)
  ```

### **STEP 4: Implementation** 💻 WRITE CODE
- **Action**: Write focused, minimal code changes
- **Guidelines**:
  - Modify existing files directly (never create duplicates like `file_v2.tsx`)
  - Follow existing code patterns in the file
  - Add inline comments explaining complex logic
  - Use descriptive variable/function names
  - Leverage TypeScript types from proto definitions
- **Code Quality**:
  - No console.log spam (use sparingly for debugging)
  - Handle errors gracefully (try/catch for API calls)
  - Clean up temporary code before commit
- **Example**:
  ```typescript
  // ✅ GOOD: Clear, typed, error-handled
  const handlePaste = async () => {
    try {
      const newNodes = await Promise.all(
        copiedNodes.map(node => client.createNode(node.type))
      );
      console.log(`✅ Pasted ${newNodes.length} nodes`);
    } catch (error) {
      console.error('❌ Paste failed:', error);
    }
  };
  
  // ❌ BAD: Untyped, no error handling, unclear
  const paste = () => {
    copiedNodes.forEach(n => {
      client.createNode(n.type); // What if this fails?
    });
  };
  ```

### **STEP 5: Build Check** 🔨 VERIFY TYPES
- **Action**: Run TypeScript compilation and Vite build
- **Command**: `npm run build`
- **Expected Result**: 
  ```
  ✓ 221 modules transformed.
  ✓ built in 985ms
  ```
- **If Build Fails**:
  - Fix TypeScript errors immediately
  - Do NOT proceed to next step until build passes
  - Common fixes:
    - Add missing type annotations
    - Fix import statements
    - Correct interface property names

### **STEP 6: Runtime Test** 🧪 TEST FUNCTIONALITY (Optional but Recommended)
- **Action**: Start dev server and test feature manually
- **Command**: `npm run dev`
- **URL**: `http://localhost:43930` (or port shown in terminal)
- **Test Checklist**:
  - ✅ Feature works as expected
  - ✅ No console errors
  - ✅ gRPC API calls succeed
  - ✅ UI matches Octane SE styling
  - ✅ Keyboard shortcuts work (if applicable)
- **When to Skip**: For simple refactors or documentation changes

### **STEP 7: Commit** 📝 DOCUMENT CHANGES
- **Action**: Commit with descriptive multi-line message
- **Format**:
  ```
  <Title: Short summary (50 chars max)>
  
  <Blank line>
  
  <Detailed description>
  - Bullet point 1
  - Bullet point 2
  
  <Manual reference or verification notes>
  ```
- **Example**:
  ```bash
  git add -A
  git commit -m "Implement Enhanced Pin Hover Tooltips (TASK 1.5.1)
  
  - Add rich tooltips for input pins showing:
    * Pin name/label (staticLabel/staticName from ApiNodePinInfo)
    * Pin description (from ApiNodePinInfo.description)
    * Pin type (NodePinType with human-readable mapping)
    * Connected node name (if connected)
  
  - Add rich tooltips for output pins showing:
    * Node name, description, output type, category
    * Special node flags (isLinker, isTypedTextureNode)
  
  Verification: Build passes, tooltips display multi-line info
  Manual Reference: Node Graph Editor - pin interaction details"
  ```

### **STEP 8: Push** 🚀 DEPLOY TO MAIN
- **Action**: Push to origin/main
- **Command**: `git push origin main`
- **Expected Result**: Remote accepts push without conflicts

### **STEP 9: Update Documentation** 📚 KEEP DOCS CURRENT
- **Action**: Update README.md with new feature in "Recent Achievements"
- **Format**: Add entry at top of Recent Achievements section
- **Example**:
  ```markdown
  - ✅ **2025-01-21**: Implemented Enhanced Pin Tooltips (TASK 1.5.1)
    - Rich input/output tooltips with complete Octane API data
  ```
- **Commit**: Separate commit for documentation updates

### **STEP 10: Report Completion** ✅ STOP AND WAIT
- **Action**: Provide completion summary to user
- **Format**:
  ```
  ✅ TASK COMPLETED: <Task Name>
  
  CHANGES:
  - Change 1
  - Change 2
  
  VERIFICATION:
  - Build: ✅ Passes
  - Testing: ✅ Feature works
  - Commit: <commit hash>
  - Pushed: ✅ origin/main
  
  READY FOR NEXT TASK
  ```
- ⏸️ **STOP HERE**: Do NOT start next task without user approval

---

## 📊 **Task Management System**

### **Task Sources**
1. **Primary**: `OCTANE_STANDALONE_IMPLEMENTATION_PLAN.md` - Complete feature roadmap
2. **User Requests**: Specific tasks assigned during conversation

### **Task Priority Levels**
- ⭐⭐⭐⭐⭐ **Highest**: Core Node Graph Editor features (foundation)
- ⭐⭐⭐⭐ **High**: Scene Outliner, Node Inspector (essential UI)
- ⭐⭐⭐ **Medium**: Render Viewport, Menu System (important features)
- ⭐⭐ **Low**: Advanced features, optimizations
- ⭐ **Lowest**: Polish, minor enhancements

### **Task Selection Criteria**
1. Check implementation plan for highest priority incomplete tasks
2. Verify no dependency blockers (prerequisite tasks incomplete)
3. Confirm feature exists in Octane SE manual
4. Ensure proto files contain necessary APIs
5. Get explicit user approval before starting

---

## 🛠️ **Development Commands Reference**

### **Build & Test**
```bash
# Full build (TypeScript + Vite)
npm run build

# Development server (hot reload)
npm run dev

# Type check only (no build)
npx tsc --noEmit
```

### **Git Workflow**
```bash
# Stage all changes
git add -A

# Check status before commit
git status

# Commit with multi-line message
git commit -m "Title" -m "Details"

# Push to main
git push origin main

# View recent commits
git log --oneline -5
```

### **Proto File Research**
```bash
# Find all proto files
find /workspace/project/grpcSamples/sdk/src/api/grpc/protodef -name "*.proto"

# Search for API method
grep -rn "methodName" *.proto

# View specific proto file
cat octaneinfos.proto | grep -A 20 "ApiNodeInfo"
```

---

## 🚨 **Common Pitfalls to Avoid**

### ❌ **DON'T DO THIS**
1. **Starting work without task assignment** → Always wait for explicit approval
2. **Implementing features not in manual** → Verify everything in manual first
3. **Assuming API method names** → Always check proto files
4. **Creating duplicate files** (`OctaneNode_v2.tsx`) → Modify originals directly
5. **Committing with broken build** → `npm run build` must pass
6. **Using mock/simulated data** → Only real Octane gRPC API
7. **Skipping proto file research** → API names are often surprising
8. **Making multiple unrelated changes in one commit** → One task per commit
9. **Continuing after errors** → Fix errors immediately, don't proceed
10. **Forgetting to push** → Always push after commit

### ✅ **DO THIS INSTEAD**
1. **Wait for task** → User assigns specific task
2. **Verify in manual** → Browse manual section before coding
3. **Check proto files** → Verify exact API method names
4. **Modify existing files** → Edit in place, don't duplicate
5. **Build before commit** → `npm run build` then `git commit`
6. **Use real API** → Connect to live Octane instance
7. **Search proto files** → `grep -rn "methodName" *.proto`
8. **Focused commits** → One task = one commit
9. **Fix errors first** → TypeScript errors block progress
10. **Push immediately** → Commit → push → report completion

---

## 📖 **Manual Navigation Tips**

### **Direct URLs** (When available)
- **Node Graph Editor**: `https://docs.otoy.com/standaloneSE/TheGraphEditor.htm`
- **Scene Outliner**: `https://docs.otoy.com/standaloneSE/TheSceneOutliner.htm`
- **Node Inspector**: `https://docs.otoy.com/standaloneSE/TheNodeInspector.htm`
- **Render Viewport**: `https://docs.otoy.com/standaloneSE/TheRenderViewport.htm`

### **If URL Returns 404**
- Use table of contents from: `https://docs.otoy.com/standaloneSE/CoverPage.html`
- Search for feature description in manual text
- Look for screenshots showing the feature
- Check keyboard shortcuts documentation

### **What to Extract from Manual**
- ✅ **Feature descriptions**: What the feature does
- ✅ **Keyboard shortcuts**: Ctrl+C, Ctrl+V, etc.
- ✅ **UI styling**: Colors, spacing, layout
- ✅ **Interaction patterns**: Click, drag, hover behaviors
- ✅ **Menu structures**: Right-click menus, dropdown menus
- ❌ **Implementation details**: Manual doesn't describe internal code

---

## 🎯 **Current Project Status**

### **✅ Completed Features** (Last 5 Tasks)
1. **Enhanced Pin Tooltips (TASK 1.5.1)** - Rich hover tooltips with complete Octane API data
2. **Multi-Connect (Ctrl+Connect)** - Connect multiple selected nodes to single pin
3. **Connection Cutter (Ctrl+Drag)** - Cut multiple edges with Ctrl+drag line
4. **Copy/Paste (Ctrl+C/Ctrl+V)** - Duplicate nodes with connections preserved
5. **Search Dialog (Ctrl+F)** - Real-time node/pin search with selection

### **🟡 In Progress** (Current Focus)
- Awaiting next task assignment

### **⏳ Upcoming** (High Priority from Plan)
- Node grouping/ungrouping (TASK 1.2.3)
- Node group navigation (TASK 1.2.4)
- Material preview button (TASK 1.5.2)
- Drag & drop macro files (TASK 1.6.1)

---

## 📚 **Key Documentation Files**

- **WORKFLOW.md** ⭐ (This File) - Prime directive, development process
- **README.md** - Project overview, setup instructions, features list
- **OVERVIEW.md** - Architecture, technology stack, design decisions
- **QUICKSTART.md** - Quick setup guide for new developers
- **OCTANE_STANDALONE_IMPLEMENTATION_PLAN.md** - Complete feature roadmap
- **OCTANE_API_REFERENCE.md** - gRPC API patterns and examples

---

## 🔄 **Workflow Quick Reference Card**

```
┌─────────────────────────────────────────────────────────┐
│  OctaneWebR Development Workflow - Quick Reference      │
├─────────────────────────────────────────────────────────┤
│                                                          │
│  1. 🔍 PICK unimplemented feature from Octane SE manual │
│  2. 📖 VERIFY feature exists in manual documentation    │
│  3. 🔍 CHECK proto files for required API methods       │
│  4. 💻 IMPLEMENT focused code changes                   │
│  5. 🔨 BUILD with `npm run build` (must pass)           │
│  6. 🧪 TEST with `npm run dev` (verify works)           │
│  7. 📝 COMMIT with descriptive message                  │
│  8. 🚀 PUSH to origin/main                              │
│  9. 📚 UPDATE README.md with achievement                │
│  10. ✅ IMMEDIATELY pick next task and REPEAT           │
│                                                          │
│  Continue loop autonomously until stopped/blocked       │
│                                                          │
├─────────────────────────────────────────────────────────┤
│  ⚠️  CRITICAL RULES                                     │
│  • Manual is single source of truth                     │
│  • Never use mocks, only real Octane API               │
│  • Always check proto files for API names              │
│  • Autonomous mode - no approval needed                │
│  • Build must pass before commit                       │
└─────────────────────────────────────────────────────────┘
```

---

**Last Updated**: 2025-01-21  
**Status**: Production workflow - actively used  
**Compliance**: 100% adherence required for all development work
