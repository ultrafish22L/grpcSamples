# OctaneWebR Development Workflow

**Goal**: Create a pixel-perfect UI clone of Octane Render Studio Standalone Edition powered by real-time gRPC API communication.

---

## 🎯 Core Objective

**Clone Octane SE's UI/UX exactly** by using the [Octane SE Manual](https://docs.otoy.com/standaloneSE/CoverPage.html) as the reference specification. Every visual element, interaction pattern, and behavior should match Octane SE as closely as possible.

---

## 🔄 Development Workflow Loop

### 1. **Reference** → Read Octane SE Manual Section
- Pick a major section from the manual (e.g., "Node Graph Editor", "Render Viewport", "Scene Outliner")
- Study the documentation, screenshots, and described behavior
- Note specific UI elements, interactions, shortcuts, and features

### 2. **Identify Issue** → Pick Specific Element to Implement
- Break down the section into specific, implementable issues
- Examples:
  - "Node Graph context menu styling"
  - "Scene Outliner expand/collapse icons"
  - "Render Viewport toolbar buttons"
  - "Node Inspector parameter widgets"

### 3. **Implement** → Code Changes
- Make focused changes to match Octane SE exactly
- Use TypeScript for type safety
- Follow React best practices
- Use real gRPC API calls (never mocks)
- Reference Octane SE screenshots for pixel-perfect accuracy

### 4. **Visual Debug** → Launch & Test
```bash
npm run dev  # Start dev server
```

- Open http://localhost:43929 in browser
- **Visually compare** against Octane SE running side-by-side
- Test interactions (clicks, hovers, drags)
- Check console for errors
- Verify gRPC API calls work correctly

### 5. **Iterate** → Fix Until Pixel-Perfect
- Compare screenshots pixel-by-pixel if needed
- Adjust spacing, colors, fonts, sizes
- Fix any functional bugs
- Ensure hover states, animations match
- Keep iterating until indistinguishable from Octane SE

### 6. **Report** → Document Completion
- Commit changes with descriptive message
- Update documentation if needed
- Note what was accomplished
- Identify any remaining issues

### 7. **Next Issue** → Continue Loop
- Move to next element in current section
- OR move to next section if current complete
- Repeat from step 1

---

## 📋 Current Focus Example

**Section**: Node Graph Editor (NGE)  
**Issue**: Context menu styling and node type organization

**Implementation Steps**:
1. ✅ Added all 755 Octane node types across 25 categories
2. ✅ Fixed context menu arrow indicators
3. ✅ Adjusted vertical spacing (2px padding)
4. ✅ Removed border lines between items
5. ✅ Added separators before special sections
6. ✅ Multi-column "All items" submenu
7. 🚧 Next: Node creation workflow, drag-to-create

**Visual Verification**:
- Right-click in node graph → context menu appears
- Check: arrows on categories? ✅
- Check: tight vertical spacing? ✅
- Check: no border lines? ✅
- Check: separators before "Node graph" and "All items"? ✅
- Check: matches Octane SE screenshot? ✅

---

## 🛠️ Development Commands

### Quick Build Check (No Visual Test)
```bash
npm run build        # TypeScript compilation + Vite build
```
- Use to quickly check for TypeScript errors
- Faster than full visual debug session
- Good for syntax/type validation

### Visual Debug Run (With Browser)
```bash
npm run dev          # Start dev server + open browser
```
- Use when you need to SEE the changes
- Essential for UI/UX work
- Check console logs for debugging info

### Balance
- **Build checks**: Frequent (after every code change)
- **Visual debug**: As needed (when implementing/verifying visual features)
- **Avoid**: Opening browser 100 times per day unnecessarily
- **Do**: Use browser when you need visual confirmation

---

## 📖 Reference Documentation

### Primary Reference
**Octane Render Studio SE Manual**: https://docs.otoy.com/standaloneSE/CoverPage.html

Key Sections:
- **Interface** → Overall UI layout
- **Node Graph Editor** → NGE features, context menus, node types
- **Scene Outliner** → Scene hierarchy, visibility controls
- **Node Inspector** → Parameter editing widgets
- **Render Viewport** → Camera controls, toolbar
- **Menu System** → File/Edit/View/Window/Help menus

### Secondary References
- **Octane SE Screenshots** → Pixel-perfect visual reference
- **gRPC API Proto Files** → `octaneProxy/generated/*_pb2_grpc.py`
- **Implementation Plan** → `OCTANE_STANDALONE_IMPLEMENTATION_PLAN.md`

---

## ✅ Best Practices

### Code Quality
- ✅ **TypeScript strict mode** - Full type safety
- ✅ **Real gRPC only** - No mocks, no simulated data
- ✅ **Component isolation** - Each component owns its behavior
- ✅ **Consistent naming** - Match Octane terminology

### Visual Accuracy
- ✅ **Pixel-perfect CSS** - Match Octane SE exactly
- ✅ **Side-by-side comparison** - Run Octane SE while developing
- ✅ **Screenshot verification** - Compare against reference images
- ✅ **Interaction matching** - Same clicks, drags, shortcuts

### Git Workflow
- ✅ **Descriptive commits** - Explain what and why
- ✅ **Incremental commits** - One logical change per commit
- ✅ **Push regularly** - Keep remote up-to-date
- ✅ **Clean history** - Easy to track progress

---

## 🎨 Design Philosophy

### Priority Order
1. **Visual Accuracy** - Must look like Octane SE
2. **Functional Accuracy** - Must behave like Octane SE
3. **Performance** - Must be responsive and smooth
4. **Code Quality** - Must be maintainable

### When in Doubt
- **Q**: "Should I add this feature?"  
  **A**: Is it in Octane SE? If yes → implement. If no → skip.

- **Q**: "Should this button be 2px or 3px padding?"  
  **A**: Measure it in Octane SE screenshot. Match exactly.

- **Q**: "Should I use a mock for testing?"  
  **A**: No. Always use real Octane gRPC API.

- **Q**: "Should I simplify this interaction?"  
  **A**: No. Match Octane SE exactly, even if complex.

---

## 📊 Progress Tracking

### Completed Sections
- ✅ Basic application structure
- ✅ gRPC proxy integration
- ✅ Scene Outliner (basic)
- ✅ Node Inspector (parameter editing)
- ✅ Render Viewport (basic)
- ✅ Menu System (File/Edit/View/Window/Help)

### In Progress
- 🚧 **Node Graph Editor** - Context menu styling, node creation
- 🚧 **Node Type System** - 755 node types organized

### Upcoming
- ⏳ Material Database (Live DB / Local DB tabs)
- ⏳ Advanced Render Viewport controls
- ⏳ Keyboard shortcuts
- ⏳ Node graph layouts and organization
- ⏳ Advanced scene operations

See **OCTANE_STANDALONE_IMPLEMENTATION_PLAN.md** for complete roadmap.

---

## 🚦 When to Stop and Report

**After Each Issue Completion**:
1. Code changes committed and pushed
2. Visual verification complete (matches Octane SE)
3. Build successful (no TypeScript errors)
4. Functional testing complete (interactions work)

**Report Format**:
```
✅ COMPLETED: [Issue Name]

CHANGES:
- Change 1 description
- Change 2 description

VERIFICATION:
- Visual: Matches Octane SE screenshot? ✅
- Functional: Interactions work correctly? ✅
- Technical: Build passes? ✅

NEXT STEPS:
- Next issue to tackle
- Or: Ready for next task assignment
```

**Then**: Stop and wait for next task assignment. Never start new work without approval.

---

## 🆘 Troubleshooting Workflow Issues

### "Build passes but visual looks wrong"
→ Launch visual debug session, compare side-by-side with Octane SE

### "Visual looks right but doesn't work"
→ Check browser console for errors, verify gRPC API calls

### "Can't tell if it matches Octane SE"
→ Take screenshots of both, compare pixel-by-pixel, measure spacing

### "Too many visual debug sessions"
→ Use `npm run build` for quick type checking between sessions

### "Feature not documented in manual"
→ Check Octane SE directly, document behavior, ask for clarification

---

**Last Updated**: 2025-01-20  
**Current Focus**: Node Graph Editor context menu pixel-perfect matching
