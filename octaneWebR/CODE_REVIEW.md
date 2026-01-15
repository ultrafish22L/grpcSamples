# Code Review & Development Priorities

**Status**: ~30% feature parity, solid architecture, needs refinement  
**Last Updated**: 2025-01-22

---

## Architecture Review

### ✅ What's Working Well

**React/TypeScript Foundation**
- Strict TypeScript mode enforced
- Context API for global state (OctaneClient)
- Custom hooks pattern (`useOctane`, `useKeyboardShortcuts`, `useResizablePanels`)
- No prop drilling issues

**ReactFlow Integration**
- Proper use of `ReactFlowProvider` wrapper
- Custom node component (`OctaneNode`) with type safety
- `useNodesState`/`useEdgesState` hooks for state management
- `useReactFlow` for viewport control
- Controlled vs uncontrolled pattern correctly applied

**State Management**
- Single OctaneClient instance (singleton pattern)
- EventEmitter for cross-component communication
- Scene tree managed in client, derived graph state in UI
- No Redux/Zustand needed (appropriate for app size)

**gRPC Communication**
- Embedded proxy in Vite plugin (elegant solution)
- Real API calls only (no mocks)
- WebSocket for callbacks
- Proto-based type generation

### ⚠️ Areas Needing Improvement

**Performance Issues**
1. **No memoization** - Components re-render unnecessarily
   - `OctaneNode` should use `React.memo`
   - `NodeGraphEditorInner` converts full scene tree on every render
   - `SceneOutliner` recursively renders on parent state change
2. **ReactFlow performance** - Not using ReactFlow best practices
   - No `nodeOrigin` optimization
   - No `zoomOnScroll`/`preventScrolling` config
   - Not using `useUpdateNodeInternals` for position updates
3. **Large scene handling** - O(n²) algorithms in conversion functions
   - `convertSceneToGraph` loops through tree multiple times
   - No virtualization for tree views (1000+ nodes will lag)

**State Management Anti-Patterns**
1. **Multiple sources of truth**
   - Scene tree in `OctaneClient`
   - Derived nodes/edges in `NodeGraphEditor`
   - Selected node in both `App` and components
   - Should centralize in context or lift to App
2. **Event emitter overuse**
   - Custom EventEmitter when React Context would suffice
   - Mixing event-driven and prop-driven patterns
3. **Ref overuse**
   - Many `useRef` for state that should be `useState`
   - Example: `connectingEdgeRef`, `isMultiConnectingRef`
   - Makes logic harder to follow

**React Best Practices Violations**
1. **Effect dependencies**
   - Missing deps in useEffect arrays
   - Should use `useCallback` for stable function references
2. **Key prop issues**
   - Using array index as key in some places
   - Should use stable IDs (node handle)
3. **Component size**
   - `NodeGraphEditorInner` is 800+ lines
   - Should extract: connection logic, context menu logic, keyboard logic
4. **Props drilling starting**
   - `selectedNode` passed through 3+ levels
   - Consider lifting to context

**TypeScript Issues**
1. **any types escaping**
   - Scene node types use `any` for `graphInfo`, `nodeInfo`
   - Should define proper interfaces
2. **Type assertions**
   - Excessive use of `as` casting
   - Indicates incomplete type definitions
3. **Optional chaining overuse**
   - `node?.data?.handle` everywhere
   - Should guarantee types higher up

**ReactFlow Specific Issues**
1. **Custom edge components missing**
   - Using default edges when should customize for pin types
   - No edge labels showing connection info
2. **Node dimensions**
   - Hardcoded dimensions instead of measuring
   - Causes layout issues
3. **Minimap not optimized**
   - Renders all nodes, should use `nodeStrokeColor`/`nodeColor` callbacks
4. **Selection mode**
   - Not configuring `selectionMode` for box select behavior

---

## Priority Tasks (Technical Debt First)

### P0 - Critical Performance (Do First)

**Task 1: Memoize OctaneNode Component**
- Add `React.memo` with custom comparison function
- Only re-render when data/selected state changes
- **Impact**: 10x faster with 100+ nodes
- **Effort**: 30 minutes
- **Files**: `client/src/components/NodeGraph/OctaneNode.tsx`

**Task 2: Optimize convertSceneToGraph**
- Single-pass algorithm instead of multiple loops
- Cache node map, reuse across renders
- Use `useMemo` for conversion result
- **Impact**: 5x faster scene updates
- **Effort**: 1 hour
- **Files**: `client/src/components/NodeGraph/NodeGraphEditorNew.tsx`

**Task 3: Add Virtual Scrolling to Scene Outliner**
- Use react-window or react-virtuoso
- Only render visible tree nodes
- **Impact**: Handle 10,000+ node scenes
- **Effort**: 2 hours
- **Files**: `client/src/components/SceneOutliner.tsx`

### P1 - Architecture Improvements

**Task 4: Centralize Selection State**
- Move `selectedNode` to OctaneContext
- Remove prop drilling
- Single source of truth
- **Impact**: Simpler code, fewer bugs
- **Effort**: 1 hour
- **Files**: `client/src/hooks/useOctane.tsx`, `client/src/App.tsx`

**Task 5: Replace EventEmitter with Context**
- Create `GraphEditorContext` for cross-panel events
- Use React Context instead of custom emitter
- **Impact**: Better React integration
- **Effort**: 2 hours
- **Files**: `client/src/utils/EventEmitter.ts` → new context

**Task 6: Split NodeGraphEditorInner**
- Extract connection logic → `useNodeConnections` hook
- Extract context menu logic → `useGraphContextMenu` hook
- Extract keyboard logic → `useGraphKeyboard` hook
- **Impact**: Maintainable code, testable logic
- **Effort**: 3 hours
- **Files**: `client/src/components/NodeGraph/NodeGraphEditorNew.tsx`

### P2 - ReactFlow Best Practices

**Task 7: Custom Edge Component**
- Create `OctaneEdge` component
- Color by pin type (already computing)
- Add edge labels for connection info
- **Impact**: Better UX, matches Octane SE
- **Effort**: 1 hour
- **Files**: New `client/src/components/NodeGraph/OctaneEdge.tsx`

**Task 8: ReactFlow Performance Config**
```typescript
<ReactFlow
  nodeOrigin={[0.5, 0.5]}  // Center node anchoring
  zoomOnScroll={false}      // Explicit zoom mode
  preventScrolling={false}  // Allow page scroll
  elevateNodesOnSelect={true}
  selectNodesOnDrag={false}
  ...
/>
```
- **Impact**: Smoother UX, standard behavior
- **Effort**: 15 minutes
- **Files**: `client/src/components/NodeGraph/NodeGraphEditorNew.tsx`

**Task 9: Minimap Optimization**
```typescript
<MiniMap
  nodeStrokeColor={(node) => node.selected ? '#ff0' : '#666'}
  nodeColor={(node) => getNodeCategoryColor(node.data.category)}
  nodeBorderRadius={2}
/>
```
- **Impact**: Better minimap visibility
- **Effort**: 30 minutes
- **Files**: `client/src/components/NodeGraph/NodeGraphEditorNew.tsx`

### P3 - TypeScript Improvements

**Task 10: Define Proper Node Data Interfaces**
```typescript
interface GraphNodeInfo {
  position: { x: number; y: number };
  // ... all known properties
}

interface SceneNode {
  handle: number;  // Required, not optional
  name: string;
  type: string;
  graphInfo?: GraphNodeInfo;  // Properly typed
  // ... no `any` types
}
```
- **Impact**: Type safety, fewer bugs
- **Effort**: 2 hours
- **Files**: `client/src/services/OctaneClient.ts`

**Task 11: Remove Excessive Optional Chaining**
- Guarantee types at data boundaries (API responses)
- Remove `?.` chains in components
- **Impact**: Cleaner code, better performance
- **Effort**: 1 hour
- **Files**: All component files

### P4 - User-Facing Features

**Task 12: Context Menu Handlers**
- Implement Scene Outliner actions (render, save, cut, copy, paste, delete, show-in-graph)
- Implement Node Inspector actions (save, cut, copy, paste, delete, expand, show-in-outliner)
- **Impact**: Complete feature
- **Effort**: 3 hours
- **Files**: Context menu components

**Task 13: Cross-Panel Navigation**
- "Show in Graph Editor" from Scene Outliner/Inspector
- "Show in Outliner" from Graph/Inspector
- Use centralized selection state (requires Task 4)
- **Impact**: Critical UX feature
- **Effort**: 2 hours (after Task 4)
- **Files**: Event handlers in each component

**Task 14: Keyboard Shortcut System**
- Context-aware shortcuts (focused panel)
- Ctrl+X, Ctrl+C, Ctrl+V with full clipboard
- F key shortcuts (frame selected, fit view)
- **Impact**: Power user features
- **Effort**: 2 hours
- **Files**: `client/src/hooks/useKeyboardShortcuts.ts`

### P5 - Testing Infrastructure

**Task 15: Unit Tests for Utilities**
- `OctaneIconMapper` tests
- `ClientLogger` tests
- Type conversion utilities
- **Impact**: Prevent regressions
- **Effort**: 4 hours
- **Files**: New `*.test.ts` files

**Task 16: Integration Tests for OctaneClient**
- Mock gRPC responses
- Test scene tree conversion
- Test connection lifecycle
- **Impact**: Catch API issues early
- **Effort**: 6 hours
- **Files**: New `OctaneClient.test.ts`

---

## React/ReactFlow Best Practices Checklist

### Component Design
- [ ] Use `React.memo` for pure components (OctaneNode, list items)
- [ ] Extract custom hooks from large components
- [ ] Keep components under 300 lines
- [ ] Single responsibility per component

### Performance
- [ ] Use `useMemo` for expensive computations
- [ ] Use `useCallback` for event handlers passed to children
- [ ] Avoid creating functions/objects in render
- [ ] Virtual scrolling for large lists

### State Management
- [ ] Single source of truth for shared state
- [ ] Context for global state, props for local
- [ ] Lift state only as high as needed
- [ ] Avoid redundant state (derive when possible)

### Effects & Dependencies
- [ ] Complete dependency arrays (no eslint-disable)
- [ ] Cleanup in useEffect returns
- [ ] Ref vs state decision clear
- [ ] Avoid effect chains (A updates, triggers B, triggers C)

### TypeScript
- [ ] No `any` types without explicit justification
- [ ] Define interfaces for all data shapes
- [ ] Use strict mode
- [ ] Type event handlers properly

### ReactFlow Specific
- [ ] Custom node/edge components for complex UI
- [ ] `nodeOrigin` set for correct anchoring
- [ ] Performance config (zoom, scroll, drag)
- [ ] Use hooks (`useReactFlow`, `useUpdateNodeInternals`)
- [ ] Proper key props (stable IDs, not indices)

---

## Task Assignment Protocol

**NEVER start without approval** - always ask for task assignment.

Present options like:
```
Ready for next task. Recommend priorities:

1. P0.1 - Memoize OctaneNode (30min, huge perf win)
2. P0.2 - Optimize convertSceneToGraph (1hr, 5x faster)
3. P1.4 - Centralize selection state (1hr, architectural improvement)

Which should I tackle?
```

After completion:
```
✅ TASK COMPLETE: P0.1 - Memoize OctaneNode

Changes:
- Wrapped OctaneNode in React.memo with custom comparison
- Only re-renders when data/selected/icon changes
- Tested with 200 node scene: 60fps vs 15fps before

Ready for next task.
```

---

## Implementation Notes

### When Adding Features
1. Check Octane SE Manual first
2. Check proto files for API
3. Check octaneWeb (original JS) for reference
4. Implement with React/ReactFlow best practices above
5. Consider performance impact (100+ nodes)
6. Add TypeScript types (no `any`)
7. Test with real Octane scene

### When Refactoring
1. One refactor at a time
2. Ensure build passes
3. Test manually (check logs)
4. No behavior changes (refactor = same output)
5. Commit with "refactor:" prefix

### When Debugging
1. Check `octaneWebR_client.log` (browser console)
2. Check network tab for gRPC calls
3. Add temporary logs, remove before commit
4. Use React DevTools for component tree
5. Use ReactFlow DevTools extension

---

## Resources

**React**
- [React Docs](https://react.dev/) - Official docs
- [React Performance](https://react.dev/learn/render-and-commit) - Rendering guide
- [Hooks Reference](https://react.dev/reference/react) - All hooks

**ReactFlow**
- [ReactFlow Docs](https://reactflow.dev/) - Official docs
- [Examples](https://reactflow.dev/examples) - Interactive examples
- [Best Practices](https://reactflow.dev/learn/advanced-use/performance) - Performance guide

**TypeScript**
- [TypeScript Handbook](https://www.typescriptlang.org/docs/) - Language guide
- [React TypeScript Cheatsheet](https://react-typescript-cheatsheet.netlify.app/) - React patterns

---

**Current Recommendation**: Start with P0 tasks (performance). These are quick wins with huge impact.
