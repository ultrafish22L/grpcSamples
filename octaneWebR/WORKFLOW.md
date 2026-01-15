# Development Workflow

**Mission**: Pixel-perfect React/TypeScript clone of Octane SE with real-time gRPC API integration.

## Process (Task-Based)

**Always wait for explicit task assignment** - never start without approval.

1. **Wait** - Task assigned from CODE_REVIEW.md
2. **Verify** - Feature exists in [Octane SE Manual](https://docs.otoy.com/standaloneSE/CoverPage.html)
3. **Research** - Check proto files for API methods
4. **Implement** - Minimal, focused code changes
5. **Build** - `npm run build` must pass
6. **Test** - `npm run dev` check logs (minimal visual debug)
7. **Commit** - Clear description
8. **Push** - To origin/main (if authorized)
9. **Report** - Completion and STOP

## Core Principles

### 1. Manual as Truth
- If not in manual, don't implement
- Always cite manual section
- Reference: [Octane SE Manual](https://docs.otoy.com/standaloneSE/CoverPage.html)

### 2. Real API Only
- No mocks or simulated data
- Proto files: `/grpcSamples/sdk/src/api/grpc/protodef/*.proto`
- Check proto files before any API call

### 3. TypeScript Strict
- `npm run build` must pass before commit
- All code fully typed
- No `any` without justification

### 4. One Task at a Time
- Complete → Build → Test → Commit → Push → Stop → Wait
- Never start next task without approval

## Implementation Guidelines

### Code Quality
- Modify existing files directly (never create `file_v2.tsx`)
- Follow existing patterns in file
- Comment complex logic only
- Descriptive names
- No console.log spam
- Try/catch for API calls
- Clean up before commit

### Commit Format
```
Short summary (50 chars)

- Change 1
- Change 2

Verification: Build passes, feature works
```

## Commands

```bash
# Build (must pass before commit)
npm run build

# Dev server
npm run dev

# Type check only
npx tsc --noEmit

# Proto research
grep -rn "methodName" /workspace/project/grpcSamples/sdk/src/api/grpc/protodef/*.proto
```

## Common Mistakes

### DON'T
- Start without task assignment
- Implement features not in manual
- Assume API names (check proto files)
- Create duplicate files (`file_v2.tsx`)
- Commit broken build
- Use mocks/simulated data

### DO
- Wait for assignment
- Verify in manual first
- Check proto files
- Modify existing files
- Build before commit
- Use real Octane API only

## Manual Navigation

- **Base**: https://docs.otoy.com/standaloneSE/CoverPage.html
- Look for: Screenshots, keyboard shortcuts, UI styling, interaction patterns
- Extract: What feature does, how to use it, visual appearance
- Don't extract: Implementation details (not in manual)
