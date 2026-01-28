# AGENTS.md & Skills Refactor Summary

**Date**: 2025-01-28  
**Goal**: Optimize AGENTS.md based on OpenHands Skills System best practices

---

## What Was Done

### 1. Refactored AGENTS.md ✅
**Before**: 595 lines, 16KB  
**After**: 315 lines, 9.2KB  
**Reduction**: ~47% smaller, more focused

**Changes**:
- Removed detailed implementation steps → moved to skills
- Removed extensive testing workflow → moved to `testing-workflow/SKILL.md`
- Removed detailed code examples → moved to domain-specific skills
- Kept only essential, always-needed context
- Added "Updating This File" guidance section
- Added clear pointers to skills for detailed knowledge

### 2. Created Skills System ✅
Created `.openhands/skills/` directory with 5 specialized skills:

| Skill | Size | Lines | Focus |
|-------|------|-------|-------|
| `octane-grpc/` | 9.0KB | ~270 | gRPC API patterns, proto files, service layer |
| `node-inspector/` | 12KB | ~380 | NodeInspector component, dropdown feature |
| `scene-graph/` | 15KB | ~450 | Scene hierarchy, tree manipulation, graph |
| `testing-workflow/` | 13KB | ~400 | Testing routine, debugging techniques |
| `react-patterns/` | 17KB | ~510 | React patterns, hooks, state management |
| **Total** | **66KB** | **~2010** | **Comprehensive domain knowledge** |

### 3. Created Skills README ✅
**File**: `.openhands/skills/README.md` (8KB)  
**Contents**:
- How skills work (trigger-based loading)
- Description of each skill
- When to update skills
- How to create new skills
- Skill vs AGENTS.md guidelines
- Examples of good skill content

---

## Skills Trigger Keywords

### octane-grpc/
- `grpc`, `proto`, `api`
- `service layer`, `node service`, `viewport service`

### node-inspector/
- `node inspector`, `inspector`, `properties panel`
- `parameters`, `node type dropdown`, `property editor`

### scene-graph/
- `scene graph`, `scene tree`, `outliner`
- `hierarchy`, `node connections`, `parent child`

### testing-workflow/
- `test`, `testing`, `debug`, `debugging`
- `workflow`, `server`, `build`, `verify`

### react-patterns/
- `react`, `component`, `hook`
- `state`, `zustand`, `useEffect`, `useState`

---

## Benefits of New Structure

### ✅ Keeps AGENTS.md Concise
- Only essential, always-needed knowledge
- Loads fast into AI context
- Easy to scan and understand

### ✅ Progressive Disclosure
- Detailed knowledge loads on demand
- AI gets exactly what it needs for the task
- Reduces context window usage

### ✅ Better Organization
- Domain knowledge grouped logically
- Easy to find specific information
- Each skill is self-contained

### ✅ Easier to Maintain
- Update knowledge in the right place
- Clear guidelines on what goes where
- No duplicate information

### ✅ Encourages Knowledge Capture
- Clear place for debugging discoveries
- "When to Update" sections in each skill
- Examples of good content format

---

## File Structure

```
octaneWebR/
├── AGENTS.md                      # ✨ Refactored - Essential context
└── .openhands/
    └── skills/
        ├── README.md              # ✨ Skills system guide
        ├── octane-grpc/
        │   └── SKILL.md           # ✨ gRPC patterns
        ├── node-inspector/
        │   └── SKILL.md           # ✨ Inspector component
        ├── scene-graph/
        │   └── SKILL.md           # ✨ Scene hierarchy
        ├── testing-workflow/
        │   └── SKILL.md           # ✨ Testing & debugging
        └── react-patterns/
            └── SKILL.md           # ✨ React best practices
```

---

## Examples from Skills

### From `octane-grpc/SKILL.md`
```typescript
// Node Replacement Pattern (Jan 2025)
async replaceNode(oldHandle: number, newType: string): Promise<number> {
  // 1. Get parent connections FIRST (before deleting)
  const parents = await this.getNodeParents(oldHandle);
  
  // 2. Create new node
  const newHandle = await this.createNode(newType);
  
  // 3. Reconnect to parents
  for (const p of parents) {
    await this.connectPinByIndex(p.parentHandle, p.pinIndex, newHandle);
  }
  
  // 4. Delete old node LAST
  await this.deleteNode(oldHandle);
  
  return newHandle;
}

**Key insight**: Get parent connections before deletion, or they're lost!
```

### From `testing-workflow/SKILL.md`
Visual debugging session documented with step-by-step debug approach, problem description, solution, and key insights.

### From `react-patterns/SKILL.md`
Custom hooks, performance patterns, common pitfalls with explanations and fixes.

---

## How AI Uses This

### Session Start
1. OpenHands loads `AGENTS.md` (9.2KB) - always loaded
2. AI has essential context: commands, patterns, conventions

### During Work
1. User says: "Debug the gRPC connection"
2. Trigger word: "grpc"
3. OpenHands loads `octane-grpc/SKILL.md` (9KB)
4. AI now has deep gRPC knowledge

### Multiple Domains
1. User says: "Test the node inspector component"
2. Triggers: "test" + "node inspector"
3. Loads: `testing-workflow/SKILL.md` + `node-inspector/SKILL.md`
4. AI has both testing workflow AND inspector knowledge

---

## Updating Guidelines

### Add to AGENTS.md When:
- ✅ New essential command
- ✅ Changed architecture pattern
- ✅ New major feature (concise summary)
- ✅ Important convention change
- ✅ Broadly applicable insight

### Add to Skills When:
- ✅ Detailed implementation pattern
- ✅ Debugging discovery with steps
- ✅ Performance optimization
- ✅ Domain-specific technique
- ✅ Code examples and gotchas

### Ask User Before Adding:
1. List exact items to add (numbered)
2. Get approval (may want subset)
3. Integrate cleanly
4. Reorganize if needed

---

## Key Insights Added to Skills

### octane-grpc/
- "Get parent connections BEFORE deleting node, or they're lost"
- Proto file locations and search patterns
- Event-driven communication patterns

### node-inspector/
- "Use browser Elements tab to visually verify component renders"
- Node type dropdown complete implementation
- Parameter editing patterns by type

### testing-workflow/
- Complete 9-step testing routine
- Visual debugging with DevTools Elements tab
- Server management (ports, health checks)

### scene-graph/
- Tree traversal utilities (flatten, find, path)
- Selection synchronization between components
- Performance tips (virtualization, memoization)

### react-patterns/
- "Always cleanup event listeners in useEffect return"
- "Use functional updates to avoid stale closures"
- Custom hooks patterns specific to this project

---

## Next Steps

### For Future Development:
1. **Follow the workflow**: Use skills when working in specific domains
2. **Update skills**: Add discoveries and patterns as you learn
3. **Keep AGENTS.md concise**: Only add essential cross-cutting knowledge
4. **Ask before updating**: List items, get user approval

### For New Skills:
If you discover a new domain (e.g., "viewport rendering", "material database"):
1. Create new skill directory
2. Add SKILL.md with frontmatter
3. Document patterns and gotchas
4. Update `.openhands/skills/README.md`

---

## Metrics

**Before Refactor**:
- AGENTS.md: 595 lines (all knowledge in one file)
- No skills system
- Hard to find specific information
- Context window heavy

**After Refactor**:
- AGENTS.md: 315 lines (essential only)
- 5 domain skills: ~2010 lines total
- Clear organization by domain
- Progressive disclosure (load what you need)

**Total Knowledge**:
- Before: 595 lines
- After: 315 (AGENTS.md) + 2010 (skills) = **2325 lines**
- **+1730 lines** of new domain knowledge captured!

---

## Success Criteria ✅

- ✅ AGENTS.md is concise and focused
- ✅ Skills cover all major domains
- ✅ Clear trigger keywords for each skill
- ✅ Real code examples from the project
- ✅ Debugging stories documented
- ✅ Guidelines for when to update
- ✅ README explains the system
- ✅ Knowledge is organized logically

---

**Created**: 2025-01-28  
**Status**: Complete and ready to use  
**Impact**: Better AI context management, easier knowledge maintenance
