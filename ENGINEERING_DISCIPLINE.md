# Engineering Discipline: Session Management & Code Quality Standards

## 🚨 **CRITICAL REQUIREMENT: REAL OCTANE ONLY**

**⚠️ NEVER EVER use mock or simulated data - only real live connection with Octane LiveLink service.**

## 🎯 Core Philosophy: Preserve Working Code, Enhance Systematically

**FUNDAMENTAL PRINCIPLE**: Never break working functionality. Always understand what's working before attempting to fix what's broken.

## 📋 REPRO_PROMPT.md Pattern

### Standard Project Structure
The repository folder structure should contain:
root - `ENGINEERING_DISCIPLINE.md` - This file, for session management standards across all projects
    folder - `REPRO_PROMPT.md` - Project-focused reproduction prompt from last session to immediately restart a work chat session

### REPRO_PROMPT.md Requirements
```markdown
# Project Name: Current Task Title

## 🎯 CURRENT TASK: [Specific, actionable task]
**STATUS**: [% complete] - [Brief status summary]

## ✅ What's Already Working
[List working functionality - celebrate successes]

## 🎯 NEXT STEP: [Specific implementation task]
[Exact files, functions, line numbers to modify]

## 🔍 Debug Steps if Issues
[Specific troubleshooting steps]

## 📚 Reference for New Chat
[Key files, working commits, user goals]
```

### Session Start Protocol
1. **Auto-detect REPRO_PROMPT.md** in current directory
2. **Read and understand current task state** before any action
3. **Confirm understanding** of what's working vs. what needs work
4. **Ask clarifying questions** about specific goals

## 🚨 Critical Error Patterns to Avoid

### 1. The "Server Abandonment" Anti-Pattern
**WRONG**:
- Start servers for testing and leave them running indefinitely
- Forget to stop servers after completing tests
- Accumulate multiple running server processes

**RIGHT**:
- **ALWAYS stop servers immediately after testing**
- Use `pkill -f octane_proxy.py` and `pkill -f "python -m http.server"` to stop servers
- Verify no servers are running with `ps aux | grep -E "(octane_proxy|http.server)" | grep -v grep`
- Never leave servers running between sessions or after task completion

### 2. The "Panic Fix" Anti-Pattern
**WRONG**:
- See error logs → Assume code bug → Make destructive changes
- Break working functionality to "fix" unrelated issues
- Remove essential code without understanding its purpose

**RIGHT**:
- Analyze what's working vs. what's failing
- Distinguish network/environment issues from code bugs

### 2. The "Wrong Debug Tool" Anti-Pattern
**WRONG**:
- Try to use F12 browser developer console in OpenHands environment
- Waste time trying to get browser console to work
- Miss critical debug information due to wrong tool

**RIGHT**:
- Use **Ctrl+D** to open built-in debug console in web applications
- Check for application-specific debugging tools first
- F12 browser console **DOES NOT WORK** in OpenHands environment

### 3. The "Silent API Failure" Anti-Pattern
**WRONG**:
- Assume API calls are working because they appear in proxy logs
- Ignore empty `{}` responses from API calls
- Continue debugging UI when the real issue is API service mapping

**RIGHT**:
- Check debug console for `❌ SYNC API call failed` messages
- Verify proxy service mapping for new API services
- Test API calls independently before debugging UI issues
- Test with fresh environment before assuming code problems
- Preserve working functionality while addressing real issues

### 2. The "Connection Error = Code Bug" Fallacy
**Network Errors Are NOT Code Bugs**:
- `Connection refused (10061)` = Service not running
- `Connection reset (10054)` = Network interruption
- `Socket closed` = Normal disconnection
- `Timeout` = Network latency or service overload

**Before Assuming Code Issues**:
1. Is the service running?
2. Are network settings correct?
3. Try restarting services
4. Test with minimal requests
5. **Only then** consider code changes

### 3. The "Over-Engineering" Trap
**WRONG**:
- Add complex solutions for simple problems
- Refactor working code unnecessarily
- Implement features not requested by user

**RIGHT**:
- Make minimal changes to achieve specific goals
- Focus on the exact task requested
- Enhance working code, don't replace it

## 🔧 Proper Development Workflow

### Phase 1: Understanding Current State
1. **Read REPRO_PROMPT.md** thoroughly
2. **Examine working code** to understand current functionality
3. **Identify what's actually broken** vs. what's working
4. **Confirm task understanding** with user if unclear

### Phase 2: Analysis Before Action
1. **Distinguish problem types**:
   - Network/environment issues
   - Configuration problems
   - Actual code bugs
   - Missing features
2. **Test current functionality** to establish baseline
3. **Identify root cause** before proposing solutions

### Phase 3: Minimal Targeted Changes
1. **Make smallest possible change** to address specific issue
2. **Test incrementally** - don't make multiple changes at once
3. **Preserve all working functionality**
4. **Document what was changed and why**

### Phase 4: Validation & Documentation
1. **Verify fix addresses the specific problem**
2. **Confirm no working functionality was broken**
3. **ALWAYS stop servers immediately after testing** - Never leave servers running
4. **Update REPRO_PROMPT.md** with new state
5. **Commit with clear, descriptive messages**

## 🎯 Code Quality Standards

### Preservation Principles
- **Working code is sacred** - understand before modifying
- **Recursive patterns** often essential - don't remove without understanding
- **API integrations** that return data successfully are working correctly
- **UI systems** with proper visual output are functioning

### Change Discipline
- **One change at a time** - test each modification
- **Minimal scope** - don't refactor while fixing bugs
- **Clear purpose** - every change should address specific requirement
- **Reversible** - use git properly to enable rollbacks

### Testing Approach
- **Test current state first** - establish what works
- **Fresh environment testing** - restart services, clear caches
- **Incremental validation** - test each change separately
- **User validation** - confirm changes meet requirements
- **ALWAYS stop servers immediately after testing** - Never leave servers running

## 🔍 Error Analysis Framework

### Network vs. Code Issue Checklist
```
❌ Connection refused → Check if service is running
❌ Connection reset → Network interruption, restart service
❌ Timeout → Service overload or network latency
❌ Socket closed → Normal disconnection, reconnect
✅ API returns data → Integration working correctly
✅ UI displays content → Rendering system functional
✅ Icons show correctly → Asset system working
```

### Debugging Hierarchy
1. **Environment Issues** (service not running, ports blocked)
2. **Configuration Issues** (wrong URLs, missing settings)
3. **Network Issues** (connectivity, timeouts, interruptions)
4. **Integration Issues** (API call patterns, data parsing)
5. **Code Logic Issues** (actual bugs in implementation)

**Work through this hierarchy systematically** - don't jump to code changes.

## 📊 Success Metrics & Validation

### Session Success Indicators
- **Specific task completed** as requested by user
- **No working functionality broken** during changes
- **Clear documentation** of what was accomplished
- **Updated REPRO_PROMPT.md** for next session

### Code Quality Indicators
- **Minimal changes** to achieve goals
- **Clear commit messages** explaining what and why
- **Working functionality preserved** and validated
- **User requirements met** without over-engineering

### Communication Quality
- **Clear understanding** of current state before starting
- **Regular progress updates** during implementation
- **Honest assessment** of what's working vs. broken
- **Specific questions** when requirements unclear

## 🚫 Anti-Patterns to Avoid

### Destructive Patterns
- **Breaking working code** to fix unrelated issues
- **Removing essential functionality** without understanding purpose
- **Making multiple changes** without testing each one
- **Assuming code bugs** from network error messages

### Communication Anti-Patterns
- **Jumping to solutions** without understanding problems
- **Making assumptions** about what's broken
- **Over-promising** capabilities or timeline
- **Under-communicating** progress and blockers

### Technical Anti-Patterns
- **Premature optimization** of working systems
- **Over-engineering** simple solutions
- **Ignoring existing patterns** in favor of new approaches
- **Breaking API contracts** that are working correctly

## 🎯 Session Management Protocol

### Start of Session
1. **Check for REPRO_PROMPT.md** in current directory
2. **Read and internalize** current task state
3. **Examine key files** mentioned in prompt
4. **Confirm understanding** with user before proceeding

### During Session
1. **Focus on specific task** outlined in REPRO_PROMPT.md
2. **Make minimal changes** to achieve goals
3. **Test incrementally** and report progress
4. **ALWAYS stop servers immediately after testing** - Never leave servers running
5. **Ask for clarification** when requirements unclear

### End of Session
1. **Update REPRO_PROMPT.md** with new state and next steps
2. **Commit changes** with clear, descriptive messages
3. **Document what was accomplished** and what remains
4. **Prepare context** for next session

## 📚 Reference Standards

### Commit Message Format
```
🎯 [TYPE]: [Brief description]

✅ ACCOMPLISHED:
- [Specific achievements]
- [Working functionality preserved]

🎯 NEXT STEPS:
- [What remains to be done]
- [Any blockers or considerations]
```

### REPRO_PROMPT.md Update Pattern
- **Always update** at end of session
- **Reflect current working state** accurately
- **Specify next concrete steps** for continuation
- **Include any new discoveries** or changed requirements

### Documentation Standards
- **Task-focused** rather than comprehensive
- **Specific file/line references** for implementation
- **Clear success criteria** for validation
- **Troubleshooting steps** for common issues

## 🏆 Excellence Standards

### Technical Excellence
- **Preserve working functionality** at all costs
- **Make minimal, targeted changes** to achieve goals
- **Test thoroughly** before declaring success
- **Document clearly** for future sessions

### Communication Excellence
- **Understand before acting** on any request
- **Report progress honestly** and regularly
- **Ask clarifying questions** when uncertain
- **Celebrate successes** while addressing problems

### Process Excellence
- **Follow systematic workflow** for all changes
- **Use proper version control** with clear commits
- **Maintain project documentation** consistently
- **Enable smooth session transitions** with good context

**Remember: The goal is sustainable progress through disciplined engineering practices. Preserve what works, enhance systematically, and always understand the current state before making changes.**

## 🔥 LEGACY PRINCIPLES (Preserved for Reference)

### 1. **EVIDENCE OVER INTUITION**
- Every claim must be backed by working code, logs, or screenshots
- No assumptions about API behavior - test everything
- When debugging, gather concrete evidence before proposing solutions
- "It should work" is not evidence - "Here's the curl output" is evidence

### 2. **PROVEN PATTERNS OVER CLEVER SOLUTIONS**
- Study existing working code (testGrpcApi, octaneGrpcTest) before implementing
- Copy successful patterns exactly before attempting modifications
- Simple, boring solutions that work beat clever solutions that might work
- When in doubt, follow the pattern that's already proven

### 3. **INCREMENTAL VERIFICATION**
- Test each component individually before integration
- Every API call verified with curl before building complex logic
- Build in small, verifiable steps with clear success criteria
- Never build complex systems without proven building blocks

### 4. **REAL DATA ENFORCEMENT**
## 🚨 **CRITICAL REQUIREMENT: REAL OCTANE ONLY**
**⚠️ NEVER EVER use mock or simulated data - only real live connection with Octane LiveLink service.**

- Connect to live Octane or show empty UI - no fallbacks
- Every feature must work with actual Octane data
- User has working Octane instance - use it

## 🚨 CRITICAL TECHNICAL STANDARDS

### ObjectPtr Type Matching (FUNDAMENTAL LAW)
```javascript
// ✅ CORRECT - ObjectPtr.type must match service class
const response = await client.makeGrpcCall('ApiNodeGraphService', 'getOwnedItems', {
    objectPtr: {handle: 1000001, type: 20}  // type 20 = ApiNodeGraph
});

// ❌ FORBIDDEN - Type mismatch causes "invalid pointer type"
const response = await client.makeGrpcCall('ApiNodeGraphService', 'getOwnedItems', {
    objectPtr: {handle: 1000001, type: 18}  // type 18 = ApiRootNodeGraph (WRONG)
});
```

### Proxy Pass-Through Principle
```python
# ✅ CORRECT - Pure pass-through, no transformations
def handle_grpc_call(service_name, method_name, params):
    service = get_service(service_name)
    method = getattr(service, method_name)
    return method(params)  # Exact pass-through

# ❌ FORBIDDEN - Hardcoded type mappings
def handle_grpc_call(service_name, method_name, params):
    if params.objectPtr.type == 18:
        params.objectPtr.type = 20  # NEVER transform types
    return method(params)
```

### Cache Busting Requirement
```javascript
// ✅ MANDATORY - Always use cache busting during development
const timestamp = new Date().toISOString().replace(/[-:]/g, '').slice(0, 15);
const cacheBuster = `?v=${timestamp}`;

// ❌ FORBIDDEN - Relying on browser cache during development
// This leads to stale code and wasted debugging time
```

## 🔧 DEVELOPMENT WORKFLOW STANDARDS

### 1. **Study Phase** (Before Writing Code)

### 2. **Test Phase** (Before Integration)


### 3. **Implementation Phase** (Follow Proven Patterns)
- Copy exact patterns from working code
- Make minimal changes to proven implementations
- Test each change immediately with real data
- Document any deviations from standard patterns

### 4. **Verification Phase** (Prove It Works)
- Screenshot actual browser display (not just DOM inspection)
- Capture real API responses with timestamps
- Test with live Octane data only - NEVER use mock responses
- Verify cross-platform compatibility

## 🚨 ANTI-PATTERNS (IMMEDIATE SUPERVISION REQUIRED)

### 🔥 VISUAL VERIFICATION FAILURE
- Claiming success without checking actual browser display
- Assuming DOM existence equals visual rendering
- Not testing with real user interactions

### 🔥 CACHE DEPENDENCY
- Not implementing fresh cache busting with every change
- Relying on manual browser refresh during development
- Debugging stale code instead of fresh implementations

### 🔥 F12 DEPENDENCY
- Relying on browser developer tools instead of built-in logging
- Not implementing custom debug console in application
- Making users open F12 to see error messages

### 🔥 SCOPE CREEP
- Fixing unrelated issues when focused task requested
- Adding features not explicitly requested
- Optimizing code that already works correctly

### 🔥 ASSUMPTION CASCADES
- Making claims without concrete proof
- Building on unverified assumptions
- Proposing solutions without studying working code

## 🎖️ SUCCESS METRICS

### Code Quality Indicators:
- ✅ Every API call has working curl example
- ✅ Every feature tested with real Octane data
- ✅ No hardcoded type mappings or transformations
- ✅ Cache busting implemented and working
- ✅ Debug console built into application

### User Experience Indicators:
- ✅ User says "exactly what I needed"
- ✅ Problem solved with minimal changes
- ✅ Solution works immediately without iteration
- ✅ No scope creep or tangent drift
- ✅ Professional UI matching industry standards

### Technical Excellence Indicators:
- ✅ Follows proven patterns from working code
- ✅ Pure pass-through proxy with no transformations
- ✅ Real data enforcement with graceful degradation
- ✅ Cross-platform compatibility verified
- ✅ Performance monitoring and error handling

## 🔥 THE ENGINEERING OATH

*"I will study working code before implementing new features. I will test each component with real data before integration. I will follow proven patterns over clever solutions. I will gather evidence before making claims. I will build incrementally with clear verification at each step. I will prioritize discipline over cleverness, evidence over intuition, and proven patterns over theoretical solutions."*

---

**This discipline exists because professional software requires systematic, evidence-based development. Follow these standards religiously to deliver bulletproof systems that work reliably in production environments.**