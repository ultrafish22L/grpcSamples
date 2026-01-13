# Troubleshooting Like a Pro
## You Diagnose. AI Executes.

---

## 🎯 The Pro Troubleshooting Approach

**You're the diagnostician. AI is your lab tech.**

**You bring:**
- Pattern recognition from experience
- Strategic thinking about root causes
- Judgment on which leads to pursue
- Decision-making under uncertainty

**AI brings:**
- Fast execution of diagnostic commands
- Systematic testing of hypotheses
- Comprehensive logging and reporting
- Tireless iteration through possibilities

**Together:** Faster debugging, less grinding, better solutions.

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

### Battle #4: "Build Succeeds, Runtime Fails"

**Symptoms:**
```
✅ npm run build - No errors
❌ Browser console: Uncaught TypeError: Cannot read property 'x' of undefined
```

**The Problem:**
TypeScript can only check what it knows. Runtime errors happen when real data doesn't match expectations.

**The Solution:**
```typescript
// ❌ Assumes data exists
const name = nodeData.displayName.toUpperCase();

// ✅ Defensive coding
const name = nodeData?.displayName?.toUpperCase() ?? 'UNKNOWN';

// 🏆 Even better - validate at boundaries
function validateNodeData(data: unknown): NodeData {
  if (!data || typeof data !== 'object') {
    throw new Error('Invalid node data');
  }
  if (!('displayName' in data) || typeof data.displayName !== 'string') {
    throw new Error('Missing displayName');
  }
  return data as NodeData;
}
```

**Remember:** Trust types, but verify data.

---

### Battle #5: "Dev Server Won't Start"

**Symptoms:**
```
❌ Port 43929 already in use
❌ Module not found: '@grpc/grpc-js'
❌ Vite hangs on startup
```

**The Checklist:**

```bash
# Problem: Port in use
# Solution: Kill the process
lsof -i :43929  # Find the PID
kill -9 <PID>   # Terminate it

# Problem: Missing dependencies
# Solution: Fresh install
rm -rf node_modules package-lock.json
npm install

# Problem: Stale cache
# Solution: Clear it
rm -rf .vite node_modules/.vite
npm run dev

# Problem: Vite hangs
# Solution: Check for infinite loops in plugin code
# Look at vite-plugin-octane-grpc.ts for blocking operations
```

**Nuclear Option (when nothing else works):**
```bash
# Start fresh
rm -rf node_modules package-lock.json .vite
npm install
npm run dev
```

---

### Battle #6: "Callback Streaming Not Working"

**Symptoms:**
```
✅ Callback registered
❌ No frames received
❌ onNewImage never fires
```

**Debug Steps:**

```typescript
// Step 1: Verify registration
const result = await callbackService.registerCallback({
  callbackType: CallbackType.CT_ON_NEW_IMAGE
});
console.log('Registration result:', result);

// Step 2: Verify streaming setup
const stream = callbackService.callbackChannel({});
stream.on('data', (data) => {
  console.log('Received callback:', data.type);
});
stream.on('error', (err) => {
  console.error('Stream error:', err);
});
stream.on('end', () => {
  console.log('Stream ended');
});

// Step 3: Verify Octane is rendering
// In Octane SE: Start a render
// Callbacks only fire when Octane is actively rendering
```

**Common Mistake:** Expecting callbacks when Octane isn't rendering. Callbacks are **event-driven**.

---

### Battle #7: "Icons Not Displaying"

**Symptoms:**
```
❌ 404 errors for icon files
❌ Broken image icons in node graph
❌ Icons exist but don't load
```

**The Checklist:**

```bash
# Step 1: Verify icons exist
ls client/public/icons/nodes/*.png | wc -l  # Should be 636

# Step 2: Verify paths are correct
# Icon path format: /icons/nodes/NT_MAT_DIFFUSE.png
# NOT: /public/icons/nodes/NT_MAT_DIFFUSE.png

# Step 3: Verify metadata exists
cat client/public/icons/nodes/metadata.json | jq 'length'  # Should be 636

# Step 4: Verify display names exist
cat client/public/icons/nodes/node-display-names.json | jq 'length'  # Should be 755
```

**In React:**
```typescript
// ❌ Wrong path
<img src="/public/icons/nodes/NT_MAT_DIFFUSE.png" />

// ✅ Correct path
<img src="/icons/nodes/NT_MAT_DIFFUSE.png" />

// 🏆 Even better - handle missing icons
<img 
  src={`/icons/nodes/${nodeType}.png`}
  onError={(e) => {
    e.currentTarget.src = '/icons/nodes/fallback.png';
  }}
/>
```

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

## 💎 The Reality of Pro Debugging

### What Makes You Effective

**Your human strengths in debugging:**
- **Pattern recognition** - You've seen similar bugs before
- **Intuition** - You sense where the problem likely is
- **Strategic thinking** - You know which approaches to try first
- **Creative problem solving** - You find novel solutions to novel problems
- **Judgment under uncertainty** - You make calls with incomplete information

**What AI amplifies:**
- **Execution speed** - Run 10 diagnostic tests in seconds
- **Consistency** - Never forgets to check edge cases
- **Documentation** - Captures every step automatically
- **Tireless iteration** - Test hundreds of scenarios without fatigue
- **Comprehensive logging** - Track everything systematically

**Together:** You solve bugs 3x faster because you focus on thinking, not typing.

### Your Debugging Mindset

```
I diagnose strategically. AI executes systematically.
I make the decisions. AI runs the tests.
I identify patterns. AI gathers the data.
I choose the approach. AI implements it.
I validate the fix. AI documents the solution.
I'm the debugger. AI is my force multiplier.
```

---

## 🎤 The Pro's Approach

When the build fails,  
When Octane crashes,  
When nothing makes sense,  
When you've tried everything...

**Don't grind through it manually. Direct AI assistance:**

- **You:** "Octane crashed. Run full diagnostics."
- **AI:** Tests connectivity, checks logs, reports findings
- **You:** "Ah, callback registration is blocking. Try lazy init."
- **AI:** Implements change, tests, confirms fix
- **You:** "Good. Document and move on."

**That's debugging like a pro:**  
Strategic thinking (you) + Fast execution (AI) = Problems solved at velocity.

**You're the toughest debugger because you use every tool effectively.**

---

## 📚 More Resources

- **General Workflow**: `WORKFLOW.md`
- **Developer Mindset**: `DEVELOPER_MINDSET.md`
- **Current Issues**: `CURRENT_BLOCKER.md`
- **Quick Start**: `QUICKSTART.md`

When the docs don't have your answer, you're about to learn something new. **Document it when you do.**
