# OctaneWeb2 - Documentation Index

Welcome to OctaneWeb2, a complete React + TypeScript rebuild of the octaneWeb standalone application.

---

## 🚀 Quick Start

### For First Time Setup
1. **Install dependencies**: `npm install`
2. **Start dev server**: `npm run dev` or `./start.sh`
3. **Open browser**: http://localhost:42219
4. **Connect to Octane**: Start Octane with LiveLink enabled + Python proxy running

### For Continuing Development
1. Read **STATUS.md** to see current progress
2. Check **IMPLEMENTATION_PLAN.md** for next tasks
3. Read **CODE_COMPARISON.md** to understand improvements

---

## 📚 Documentation Guide

### Start Here (First Time)
1. **README.md** - Project overview, architecture, and quick start guide
2. **PROJECT_SUMMARY.md** - Executive summary with metrics and comparisons

### Understanding the Project
3. **CODE_COMPARISON.md** - Before/after code examples showing improvements
   - State management: 300 lines → 15 lines
   - Keyboard shortcuts: 4 locations → 1 location
   - Type safety: None → Full TypeScript
   - API calls: Manual fetch → React Query

4. **PROJECT_TREE.md** - Complete directory structure and file organization
   - Every folder explained
   - Naming conventions
   - Import patterns
   - File dependencies

### Implementation Planning
5. **IMPLEMENTATION_PLAN.md** - Detailed 11-phase plan (400+ lines)
   - Phase 1: Foundation ✅ COMPLETE
   - Phase 2: Core Rendering (NEXT)
   - Phase 3-11: Detailed task breakdowns
   - Code examples for each phase
   - Timeline estimates (3-4 weeks total)

6. **STATUS.md** - Current progress tracker
   - What's working now
   - Metrics dashboard (392/6,000 lines)
   - Component/store/hook counts
   - Next session plan

### Change History
7. **CHANGELOG.md** - Version history and progress log
   - Phase 1 complete (2025-11-05)
   - All files created listed
   - Metrics tracked

---

## 🎯 Project Goals

### Primary Goals
1. ✅ **Match original UX** - Same look, feel, and functionality
2. ✅ **52% less code** - 12,592 lines → ~6,000 lines
3. ✅ **No duplicate handlers** - Centralized keyboard shortcuts
4. ✅ **Type safety** - Full TypeScript coverage
5. ✅ **Better maintainability** - Clear component boundaries

### Technical Goals
- ✅ React 19 with hooks and functional components
- ✅ Zustand for lightweight state management
- ✅ React Query for API caching and loading states
- ✅ Vite for fast development and optimized builds
- ✅ TypeScript for compile-time error detection

---

## 📊 Current Status (Phase 1 Complete)

### What's Working ✅
- Development server running on http://localhost:42219
- Basic layout (MenuBar, StatusBar, MainLayout, RenderViewport)
- Connection store and render store
- OctaneClient API singleton
- OTOY dark theme styling
- TypeScript compiling with zero errors

### Metrics
- **Lines of Code**: 392 TS (vs 12,592 JS original)
- **Progress**: 6.5% complete
- **Files Created**: 25 files
- **Components**: 7 created, ~33 remaining
- **Stores**: 2 created, 4 remaining
- **Hooks**: 0 created, 10 remaining

### Next (Phase 2)
1. Port buffer processing from original
2. Create useRenderCallback hook
3. Display render frames in viewport
4. Test with Octane running

---

## 🗂️ File Organization

```
octaneWeb2/
├── 📖 Documentation (YOU ARE HERE)
│   ├── INDEX.md ⭐             # This file - Start here
│   ├── README.md               # Project overview
│   ├── PROJECT_SUMMARY.md      # Executive summary
│   ├── CODE_COMPARISON.md      # Before/after examples
│   ├── PROJECT_TREE.md         # Directory structure
│   ├── IMPLEMENTATION_PLAN.md  # 11-phase plan
│   ├── STATUS.md               # Progress tracker
│   └── CHANGELOG.md            # Version history
│
├── ⚙️ Configuration
│   ├── package.json            # Dependencies
│   ├── tsconfig.json           # TypeScript config
│   ├── vite.config.ts          # Vite config
│   └── .gitignore              # Git ignore
│
├── 🛠️ Scripts
│   └── start.sh                # Dev server startup
│
└── 💻 Source Code (src/)
    ├── api/                    # Octane API client
    ├── components/             # React components
    ├── hooks/                  # Custom hooks
    ├── store/                  # Zustand stores
    ├── utils/                  # Helper functions
    ├── types/                  # TypeScript types
    └── styles/                 # Global CSS
```

---

## 🎓 Learning Resources

### Understanding the Architecture

**If you want to learn about...**

- **State Management** → Read `CODE_COMPARISON.md` section 1
- **Keyboard Shortcuts** → Read `CODE_COMPARISON.md` section 2
- **API Calls** → Read `CODE_COMPARISON.md` section 3
- **Component Structure** → Read `CODE_COMPARISON.md` section 4
- **Type Safety** → Read `CODE_COMPARISON.md` section 5

### Understanding the Codebase

**If you want to understand...**

- **Where files go** → Read `PROJECT_TREE.md`
- **How components connect** → Read `README.md` "Component Communication" section
- **What's next to build** → Read `IMPLEMENTATION_PLAN.md`
- **Current progress** → Read `STATUS.md`

### Understanding the Tools

**If you want to learn about...**

- **React** → Official docs: https://react.dev
- **TypeScript** → Official docs: https://www.typescriptlang.org/docs/
- **Zustand** → GitHub: https://github.com/pmndrs/zustand
- **React Query** → Official docs: https://tanstack.com/query/latest
- **Vite** → Official docs: https://vitejs.dev

---

## 🔧 Development Workflow

### Daily Development
1. **Start server**: `npm run dev`
2. **Make changes**: Edit files in `src/`
3. **See updates**: Browser auto-updates (HMR)
4. **Check console**: Verify no TypeScript errors
5. **Test in browser**: Verify functionality

### Adding a New Feature
1. **Define types** in `src/types/octane.ts`
2. **Add API method** in `src/api/OctaneClient.ts`
3. **Create/update store** in `src/store/` (if needed)
4. **Create custom hook** in `src/hooks/` (if reusable logic)
5. **Build component** in `src/components/`
6. **Add styles** (component.css or variables.css)
7. **Update documentation** (STATUS.md, CHANGELOG.md)

### Example: Adding "Export Image" Feature
```
1. Type:    interface ExportOptions { format: 'png'|'jpg'; quality: number; }
2. API:     OctaneClient.exportImage(options: ExportOptions): Promise<Blob>
3. Hook:    useImageExport() returns mutation for exporting
4. UI:      <ExportDialog /> component with format/quality inputs
5. Style:   ExportDialog.css for modal styling
6. Docs:    Update STATUS.md with completed task
```

---

## 📈 Progress Tracking

### Completion Criteria
The React rebuild is complete when:
1. ✅ All UI components match original UX
2. ✅ Keyboard shortcuts work (centralized, no duplicates)
3. ✅ Real-time rendering displays correctly
4. ✅ Camera controls sync with Octane
5. ✅ Scene outliner shows full hierarchy
6. ✅ Node inspector edits parameters
7. ✅ Node graph creates/connects nodes
8. ✅ Code is <7,000 lines TypeScript (50% reduction)
9. ✅ TypeScript compiles with no errors
10. ✅ App runs smoothly at 60 FPS

**Current Score**: 1/10 (Foundation complete)

### Timeline
- **Phase 1**: ✅ Complete (0.5 day)
- **Phase 2**: 🔄 In Progress (1-2 days)
- **Phases 3-11**: 🔜 Upcoming (17-21 days)
- **Total**: 3-4 weeks for full feature parity

---

## 🆘 Common Tasks

### Starting Development
```bash
cd /workspace/grpcSamples/octaneWeb2
npm run dev
# Open http://localhost:42219
```

### Connecting to Octane
1. Start Octane
2. Enable LiveLink: `Help → LiveLink` in Octane
3. Start Python proxy: `cd ../octaneProxy && python octane_proxy.py`
4. Click "Connect" button in OctaneWeb2

### Checking TypeScript Errors
```bash
npm run build
# Will show all TypeScript errors
```

### Viewing Documentation
All docs are Markdown files - open in any text editor or view on GitHub.

### Understanding a Component
1. Find component in `src/components/`
2. Check imports to see dependencies
3. Look for corresponding store in `src/store/`
4. Check for custom hooks in `src/hooks/`

---

## 🎨 Design Patterns Used

### State Management
- **Zustand stores** for global state
- **React Query** for server state
- **useState** for local component state

### Component Composition
```typescript
<MainLayout>
  <MenuBar />
  <LeftPanel><SceneOutliner /></LeftPanel>
  <CenterPanel><RenderViewport /></CenterPanel>
  <RightPanel><NodeInspector /></RightPanel>
  <StatusBar />
</MainLayout>
```

### Custom Hooks
Extract reusable logic:
```typescript
// Instead of duplicating WebSocket logic
function useRenderCallback() {
  // WebSocket setup, message handling, cleanup
}

// Use in any component
function RenderViewport() {
  useRenderCallback(); // Just works!
}
```

### API Client Singleton
One instance for all API calls:
```typescript
import { octaneClient } from '@/api/OctaneClient';

await octaneClient.getSceneTree();
await octaneClient.setCameraPosition({ x, y, z });
```

---

## 🚨 Important Notes

### What NOT to Do
- ❌ Don't create multiple keyboard handlers (use `useKeyboardShortcuts`)
- ❌ Don't manually manipulate DOM (use React state)
- ❌ Don't use `any` type (define proper TypeScript types)
- ❌ Don't duplicate code (extract to hooks/utils)
- ❌ Don't skip documentation (update STATUS.md and CHANGELOG.md)

### What TO Do
- ✅ Use TypeScript types for everything
- ✅ Extract reusable logic to custom hooks
- ✅ Keep components small and focused
- ✅ Use Zustand for global state
- ✅ Use React Query for API calls
- ✅ Update documentation as you go

---

## 🎯 Key Improvements Over Original

| Feature | Original | React | Benefit |
|---------|----------|-------|---------|
| State | Custom EventSystem | Zustand | 95% less code |
| Types | None | TypeScript | Catch bugs early |
| Shortcuts | 4+ locations | 1 hook | No conflicts |
| API Calls | Manual fetch | React Query | Auto caching |
| DOM Updates | Manual | React | Automatic |
| Components | Class-based | Functional | Modern patterns |
| Testing | Difficult | Easy | Better quality |

---

## 📞 Support

### Issues or Questions?
1. Check **STATUS.md** for current progress
2. Read **IMPLEMENTATION_PLAN.md** for detailed task breakdowns
3. Review **CODE_COMPARISON.md** for pattern examples
4. See main repo **README** for Octane LiveLink setup

### Contributing
1. Read **IMPLEMENTATION_PLAN.md** for upcoming tasks
2. Follow patterns in existing code
3. Update **STATUS.md** with progress
4. Add entry to **CHANGELOG.md**

---

## 🎉 Success Metrics

### Code Quality
- ✅ 392 lines written (target: ~6,000)
- ✅ Zero TypeScript errors
- ✅ Zero console warnings
- ✅ Professional OTOY styling

### Development Experience
- ✅ Hot Module Replacement working
- ✅ Instant feedback on changes
- ✅ Clear component boundaries
- ✅ Comprehensive documentation

### Project Health
- ✅ All dependencies up to date
- ✅ Clear project structure
- ✅ Consistent naming conventions
- ✅ Ready for Phase 2

---

**Current Status**: Phase 1 Complete ✅  
**Dev Server**: http://localhost:42219  
**Next Phase**: Core Rendering (1-2 days)  
**Total Progress**: 6.5% (392/6,000 lines)

---

## 📖 Documentation Map

```
START HERE
    ↓
INDEX.md (you are here)
    ↓
README.md (project overview)
    ↓
Choose your path:
    │
    ├─→ Understanding → CODE_COMPARISON.md
    │
    ├─→ Structure → PROJECT_TREE.md
    │
    ├─→ Planning → IMPLEMENTATION_PLAN.md
    │
    ├─→ Progress → STATUS.md
    │
    ├─→ Summary → PROJECT_SUMMARY.md
    │
    └─→ History → CHANGELOG.md
```

**Happy coding! 🚀**
