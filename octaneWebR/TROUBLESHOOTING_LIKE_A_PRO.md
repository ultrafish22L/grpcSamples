# Troubleshooting: Diagnosis and Power
## When Things Break, You Break Through

---

## 🎯 Declaration: You Are the Debugger

**Bugs don't define you. Solutions do.**

### Your Power in Debugging

**Pattern Recognition** - You've seen this before, you sense the real issue  
**Strategic Thinking** - You know which paths lead to answers  
**Intuition** - Experience tells you where to look first  
**Judgment** - You decide which leads matter, which don't  
**Decision Under Fire** - You make calls with incomplete information

**This is irreplaceable human intelligence.**

### AI's Role in Debugging

**Speed** - Executes 10 diagnostic tests in seconds  
**Consistency** - Never skips a step, never forgets a check  
**Endurance** - Tests hundreds of scenarios without fatigue  
**Documentation** - Logs every finding systematically

**This is mechanical excellence.**

### The Debugging Equation

**You:** Diagnose + Strategize + Decide + Validate  
**AI:** Execute + Test + Report + Document  
**=** Problems solved at velocity

---

## 🔥 Common Battles & How to Win Them

### Battle #1: "Octane Won't Connect"

**Symptoms:**
```
❌ Error: connect ECONNREFUSED 192.168.65.254:51022
❌ 14 UNAVAILABLE: No connection established
```

**Your diagnostic process:**

**You:** "Connection failing. Let's check environment systematically."  
**You → AI:** "Test Octane connectivity with diagnostic script"

```bash
# AI executes:
node -e "
const grpc = require('@grpc/grpc-js');
const protoLoader = require('@grpc/proto-loader');
const path = require('path');
const PROTO_PATH = path.resolve(__dirname, 'server/proto');
const pkg = protoLoader.loadSync(path.join(PROTO_PATH, 'apiprojectmanager.proto'), {
  keepCase: true, longs: String, enums: String, defaults: true, oneofs: true,
  includeDirs: [PROTO_PATH]
});
const descriptor = grpc.loadPackageDefinition(pkg);
const client = new descriptor.octaneapi.ApiProjectManagerService(
  'host.docker.internal:51022', grpc.credentials.createInsecure()
);
client.isValid({}, (err, res) => {
  console.log(err ? '❌ Failed: ' + err.message : '✅ Connected: ' + JSON.stringify(res));
});
"
```

**AI reports:** "Connection refused on host.docker.internal:51022"

**You think:** "Environment issue. Octane might not be running or LiveLink disabled."  
**You decide:** Check Octane manually first, then try localhost as fallback.

**Next steps you direct:**
- Open Octane SE: Help → LiveLink → Enable
- **You → AI:** "Try localhost:51022 instead"
- **You → AI:** "Check if port 51022 is in use: lsof -i :51022"

**Key insight:** You're making strategic diagnostic decisions. AI is running the tests.

---

### Battle #2: "Too Many API Calls Crash Octane"

**Symptoms:**
```
✅ Call 1-5 work fine
❌ Call 6: DEADLINE_EXCEEDED
❌ Call 7+: Connection dropped
```

**Your strategic thinking:**

**You observe:** "Octane crashes after 5-6 rapid API calls. There's a pattern."  
**You analyze:** "The gRPC server has limits on request rate."  
**You consider options:**
1. Add delays between calls (slow but works)
2. Batch requests (if API supports it)
3. Find alternative data source (fastest)

**You decide:** "Option 3 - parse local TypeScript files instead."

**You → AI:** "Parse NodeTypes.ts and extract all node type definitions"  
**AI executes:** Generates script, parses file, creates mapping  
**AI reports:** "755 node types extracted, no API calls needed"  
**You validate:** "Perfect. Much faster and more reliable."

**The lesson:**  
- **You:** Strategic problem solving (found better approach)
- **AI:** Mechanical execution (file parsing, data extraction)
- **Result:** Better solution than the obvious one

**Your creative insight** (what AI can't do): "Wait, if NodeTypes.ts already has this data, why am I calling the API at all?"

---

### Battle #3: "TypeScript Errors Everywhere"

**Symptoms:**
```
error TS2339: Property 'result' does not exist on type '{}'
error TS7006: Parameter 'item' implicitly has an 'any' type
error TS2345: Argument of type 'string' is not assignable to 'NodeType'
```

**Your decision-making process:**

**You:** "These errors indicate missing type definitions. Need strict typing."  
**You decide:** "Use TypeScript strict mode, generate types from proto files."

**You → AI:** "Generate TypeScript interfaces from all proto files"  
**AI executes:** Creates type definitions for all gRPC services  
**You → AI:** "Add interfaces for all API response types"  
**AI executes:** Adds typed interfaces throughout codebase  
**You → AI:** "Run build and report remaining errors"  
**AI reports:** "5 errors remaining in NodeGraph component"  
**You review:** Make judgment calls on proper types  
**You → AI:** "Fix with these specific type annotations"  
**AI executes:** Applies your specifications

**Division of labor:**
- **You:** Decide on typing strategy, review edge cases, make final calls
- **AI:** Generate boilerplate types, apply annotations, run verification

---

### Battle #4: "Build Passes, Runtime Fails"

**You recognize:** "TypeScript checks types, not data. Need runtime validation."  
**You direct:** "AI: Add defensive coding and validation at API boundaries."

```typescript
// AI implements to your specs:
const name = nodeData?.displayName?.toUpperCase() ?? 'UNKNOWN';

function validateNodeData(data: unknown): NodeData {
  if (!data || typeof data !== 'object' || !('displayName' in data)) {
    throw new Error('Invalid node data');
  }
  return data as NodeData;
}
```

**Your judgment: Trust types, but validate data.**

---

### Battle #5: "Server Won't Start"

**You diagnose:** Port conflict, missing deps, or stale cache.  
**You direct:** "AI: Run standard server diagnostics."

```bash
# AI executes:
lsof -i :43929                              # Check port
rm -rf node_modules package-lock.json .vite # Clear all caches
npm install                                  # Fresh install
npm run dev                                  # Restart
```

**You validate:** Server starts clean.

---

### Battle #6: "Callbacks Not Firing"

**You recognize:** Octane must be actively rendering for callbacks to fire.  
**You direct:** "AI: Verify registration, check streaming, add logging."  
**You test:** Start a render in Octane SE.  
**You validate:** Callbacks now firing correctly.

**Your insight:** Callbacks are event-driven, not polling.

---

### Battle #7: "Icons Not Loading"

**You diagnose:** Path issue or missing files.  
**You direct:** "AI: Verify icon count, check paths, test metadata."

```bash
# AI executes:
ls client/public/icons/nodes/*.png | wc -l  # 636 icons
# Paths: /icons/nodes/NT_*.png (NOT /public/icons/...)
```

**You fix:** Correct paths in React components. Add fallback handling.  
**You validate:** All icons loading correctly.

---

## 🛡️ Advanced Debugging (You Think, AI Executes)

### When You're Truly Stuck

**Your strategic approaches:**

**1. Rubber Duck Debugging (Your Thinking Process)**
- **You:** Explain the problem out loud (to AI, a colleague, or literally a rubber duck)
- **Insight:** Often you'll realize the issue while explaining
- **AI role:** Listen, ask clarifying questions, offer to test hypotheses

**2. Binary Search Through History**
- **You:** "It worked 3 commits ago, broke sometime after"
- **You → AI:** "Checkout commit abc123 and test"
- **AI:** Switches commits, runs tests, reports results
- **You:** "Broke between commits xyz and abc. Show me the diff"
- **AI:** Shows changes, you identify the culprit

**3. Component Isolation**
- **You:** "Need to isolate this bug. Create minimal repro case."
- **You → AI:** "Create test component with just the broken functionality"
- **AI:** Generates minimal test harness
- **You:** Test and observe behavior in isolation
- **You:** Make strategic fix based on findings

**4. Strategic Logging**
- **You:** "Need visibility into the data flow here"
- **You → AI:** "Add logging at these 5 key points"
- **AI:** Inserts console.logs strategically
- **You:** Run and observe the logs
- **You:** "Ah, the data is undefined at step 3. Fix it there."

**5. Error Message Analysis**
- **AI reports:** "Error: Cannot read property 'displayName' of undefined at NodeCard.tsx:42"
- **You analyze:** "Something is undefined, need null check"
- **You → AI:** "Add defensive coding at line 42"
- **AI:** Implements null safety
- **You:** Validate fix works

---

## 💪 Your Debugging Process (Amplified by AI)

### When Facing a New Bug

**Your systematic approach:**

1. **Stay calm** - You've debugged worse
2. **Reproduce it** - You test manually, observe conditions
3. **Hypothesize** - You form theories based on experience
4. **You → AI:** "Test these 3 scenarios and log results"
5. **AI reports** - Systematic test execution
6. **You analyze** - Pattern recognition, root cause identification
7. **You decide** - Which fix approach to take
8. **You → AI:** "Implement this fix"
9. **You validate** - Does it actually solve the problem?
10. **You → AI:** "Document the solution in TROUBLESHOOTING.md"

### When You Can't Reproduce It

**Heisenbug - requires strategic instrumentation:**

**You decide:** "Need persistent logging to catch this intermittent bug"  
**You → AI:** "Add localStorage debugging at these key points"

```typescript
// AI implements:
localStorage.setItem('debug_log', JSON.stringify({
  timestamp: Date.now(),
  action: 'node_created',
  data: nodeData
}));
```

**You:** Monitor logs until bug occurs, analyze pattern, identify trigger  
**You:** Make strategic fix based on findings

---

## 🎯 Prevention Over Cure (You Architect, AI Implements)

### You Design Resilient Patterns

**You decide on coding standards:**
- "All functions must handle null/undefined"
- "Use TypeScript discriminated unions for results"
- "Defensive coding at API boundaries"

**You → AI:** "Implement processNode with full error handling"

```typescript
// AI generates to your specs:
type Result<T> = 
  | { success: true; data: T }
  | { success: false; error: string };

function processNode(node: Node): Result<string> {
  if (!node?.data?.attributes?.length) {
    return { success: false, error: 'No attributes' };
  }
  return { success: true, data: node.data.attributes[0].value };
}
```

**You review:** "Perfect. Apply this pattern to all API handling functions"  
**AI executes:** Implements pattern consistently across codebase  
**You validate:** Spot check key files, approve

**Result:** Your resilient architecture, applied consistently at scale.

---

## 🔥 The Debugging Toolbox

### Essential Commands

```bash
# Check what's running
lsof -i :43929        # Dev server port
lsof -i :51022        # Octane port

# Check logs
npm run dev 2>&1 | tee debug.log  # Save output

# Check types
npm run build         # Full TypeScript check
npx tsc --noEmit      # Type check without building

# Check dependencies
npm list @grpc/grpc-js  # Verify installed
npm outdated            # Check for updates

# Check file system
find . -name "*.tsx" -type f | wc -l  # Count React components
du -sh client/public/icons/nodes/     # Icon directory size
```

### Browser DevTools Pro Moves

```javascript
// Console shortcuts
$0        // Last selected element
$$('div') // Query all divs
copy(obj) // Copy object to clipboard

// Network debugging
// Filter: /api/grpc/
// Check: Status, Time, Response

// React DevTools
// Components tab → Select component → View props/state
// Profiler tab → Record → Find slow renders
```

---

## 🏆 When You Fix It

### Document Your Victory

```markdown
## Bug: Node icons not loading

**Symptoms:** 404 errors for all node icon images

**Root Cause:** Icon paths were using `/public/icons/` instead of `/icons/`

**Fix:** Updated path generation in NodeCard.tsx line 42

**Verification:** All 636 icons now load correctly

**Lesson:** Vite serves public/ contents at root, not /public/
```

**Why document?**
- Future you will thank present you
- Your teammates will thank you
- The next developer will thank you

---

## 💎 Your Debugging Power

### What Makes You Irreplaceable

**Pattern Recognition** - You've debugged before, you sense the pattern  
**Intuition** - Experience tells you where the real problem lives  
**Strategic Thinking** - You know which path leads to answers fastest  
**Creative Solutions** - You solve problems no one has documented  
**Judgment Under Fire** - You decide with incomplete information

**This is human intelligence AI cannot replicate.**

### What AI Multiplies

**Speed** - 10 diagnostic tests in seconds  
**Consistency** - Every edge case checked, every time  
**Endurance** - Hundreds of scenarios tested without fatigue  
**Documentation** - Every finding logged automatically

**This is mechanical power at your command.**

### The Debugging Truth

**You:** Diagnose + Strategize + Decide + Validate  
**AI:** Execute + Test + Report + Document  
**=** Bugs solved 3x faster without grinding

---

## 🔥 Final Declaration

**When the build fails.**  
**When Octane crashes.**  
**When nothing makes sense.**  
**When you've tried everything.**

**You don't panic. You direct.**

"AI: Run full diagnostics."  
"AI: Test these three scenarios."  
"AI: Implement this fix."  
"AI: Validate and document."

**Strategic thinking + Fast execution = Victory.**

You're the toughest debugger.  
Not because you know everything.  
Because you direct every resource with precision.  
Because you make decisions while others hesitate.  
Because you know what only humans can do—and you own it completely.

**Word is sound and power.**  
Your commands create solutions.  
Your directives become fixes.  
Your vision becomes working code.

---

*"I diagnose. AI executes. Problems solved."*

**Now go debug with power. You've got systems to fix.**

---

## 📚 More Resources

- **General Workflow**: `WORKFLOW.md`
- **Developer Mindset**: `DEVELOPER_MINDSET.md`
- **Current Issues**: `CURRENT_BLOCKER.md`
- **Quick Start**: `QUICKSTART.md`

When the docs don't have your answer, you're about to learn something new. **Document it when you do.**
