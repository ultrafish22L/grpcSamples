# Troubleshooting Like a Pro
## When Things Break, Break Through

---

## 🎯 The Troubleshooting Mindset

**Problems don't define you. Solutions do.**

Every developer faces bugs, crashes, and mysterious errors. The difference between average and exceptional is **how you respond** when things go wrong.

---

## 🔥 Common Battles & How to Win Them

### Battle #1: "Octane Won't Connect"

**Symptoms:**
```
❌ Error: connect ECONNREFUSED 192.168.65.254:51022
❌ 14 UNAVAILABLE: No connection established
```

**Don't panic. Execute:**

```bash
# Step 1: Is Octane actually running?
# Open Octane Render Studio SE on your machine

# Step 2: Is LiveLink enabled?
# In Octane: Help → LiveLink → Enable

# Step 3: Test the connection
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

**Still failing?**
- Try `localhost:51022` instead of `host.docker.internal:51022`
- Restart Octane and re-enable LiveLink
- Check firewall settings (port 51022 must be open)
- Look for other apps using port 51022

**Remember:** Connection errors are **environment issues**, not code bugs.

---

### Battle #2: "Too Many API Calls Crash Octane"

**Symptoms:**
```
✅ Call 1-5 work fine
❌ Call 6: DEADLINE_EXCEEDED
❌ Call 7+: Connection dropped
```

**The Reality:**
Octane's gRPC server has limits. Rapid-fire API calls (< 100ms apart) overwhelm it.

**The Solution:**
```javascript
// ❌ This will crash Octane
for (let i = 0; i < 636; i++) {
  await client.nodeInfo({ type: nodeIds[i] });
}

// ✅ This works
for (let i = 0; i < 636; i++) {
  await client.nodeInfo({ type: nodeIds[i] });
  await new Promise(resolve => setTimeout(resolve, 50)); // 50ms delay
}

// 🏆 This is even better - avoid API calls entirely
// Parse existing data files instead (like NodeTypes.ts)
```

**Pro Move:** Ask yourself: "Do I really need this API call, or is the data already available?"

---

### Battle #3: "TypeScript Errors Everywhere"

**Symptoms:**
```
error TS2339: Property 'result' does not exist on type '{}'
error TS7006: Parameter 'item' implicitly has an 'any' type
error TS2345: Argument of type 'string' is not assignable to 'NodeType'
```

**The Fix:**
```typescript
// ❌ Weak typing
const response = await apiCall();
const data = response.result; // TypeScript has no idea what this is

// ✅ Strong typing
interface ApiResponse {
  result: NodeData[];
}
const response: ApiResponse = await apiCall();
const data = response.result; // TypeScript knows exactly what this is

// 🏆 Even better - use generated types from proto files
import { ApiInfo } from './generated/apiinfo_pb';
```

**Pro Tip:** When you see `any`, you're telling TypeScript "I give up." Don't give up.

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

## 🛡️ Advanced Debugging Techniques

### When You're Truly Stuck

**1. Rubber Duck Debugging**
Explain the problem out loud. Seriously. You'll find the bug while explaining it.

**2. Binary Search Your Changes**
```bash
git log --oneline  # See recent commits
git checkout <commit-hash>  # Go back to when it worked
npm run dev  # Test
# Narrow down which commit broke it
```

**3. Isolate the Component**
```typescript
// Create a minimal test case
function TestComponent() {
  const [data, setData] = useState(null);
  
  useEffect(() => {
    // Only the broken part, nothing else
    fetchProblemData().then(setData);
  }, []);
  
  return <div>{JSON.stringify(data)}</div>;
}
```

**4. Add Strategic Logging**
```typescript
console.log('🔵 Before API call');
const result = await apiCall();
console.log('🟢 After API call:', result);
```

**5. Read the Error Message (Actually Read It)**
```
Error: Cannot read property 'displayName' of undefined
  at NodeCard.tsx:42:18
```
- Line 42 in NodeCard.tsx is the problem
- Something is undefined when you expect it to have displayName
- Go to line 42, add null check

---

## 💪 The Pro Developer's Process

### When Facing a New Bug

1. **Don't panic** - Bugs are normal
2. **Reproduce it** - Can you make it happen again?
3. **Isolate it** - What's the smallest code that causes it?
4. **Understand it** - Why is it happening?
5. **Fix it** - Address the root cause
6. **Test it** - Verify the fix works
7. **Document it** - Leave breadcrumbs for future you

### When You Can't Reproduce It

**Heisenbug detected.** These are the toughest.

```typescript
// Add persistence
localStorage.setItem('debug_log', JSON.stringify({
  timestamp: Date.now(),
  action: 'node_created',
  data: nodeData
}));

// Check later
const log = JSON.parse(localStorage.getItem('debug_log'));
console.log('Last known state:', log);
```

---

## 🎯 Prevention Over Cure

### Write Code That's Hard to Break

```typescript
// ❌ Fragile
function processNode(node) {
  return node.data.attributes[0].value;
}

// ✅ Resilient
function processNode(node: Node): string {
  if (!node?.data?.attributes?.length) {
    return 'default';
  }
  return node.data.attributes[0]?.value ?? 'default';
}

// 🏆 Even better - use TypeScript discriminated unions
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

## 💎 Final Wisdom

### The Truth About Debugging

**Every bug you fix makes you stronger.**  
Every error message you decode teaches you something.  
Every crash you survive builds your intuition.

**The best developers aren't the ones who write bug-free code.**  
They're the ones who debug effectively when bugs appear.

### Your Debugging Creed

```
I don't fear errors.
I read them carefully.
I don't skip error messages.
I understand them fully.
I don't blame the tools.
I verify my assumptions.
I don't hack around problems.
I fix root causes.
I don't give up.
I break through.
```

---

## 🎤 Remember

When the build fails,  
When Octane crashes,  
When nothing makes sense,  
When you've tried everything...

**You're not stuck. You're learning.**

Every pro developer has been exactly where you are.  
The difference is they didn't stop.  
They debugged, they learned, they conquered.

**Now go fix that bug. You've got this.**

---

## 📚 More Resources

- **General Workflow**: `WORKFLOW.md`
- **Developer Mindset**: `DEVELOPER_MINDSET.md`
- **Current Issues**: `CURRENT_BLOCKER.md`
- **Quick Start**: `QUICKSTART.md`

When the docs don't have your answer, you're about to learn something new. **Document it when you do.**
