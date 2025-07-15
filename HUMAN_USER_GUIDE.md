# HUMAN USER GUIDE: AI Agent Control & Optimization
## Your Complete Reference for Maximizing AI Agent Performance

*"The right words unlock exponential AI capability. This guide gives you those words."*

---

## 🎯 INSTANT ACTIVATION COMMANDS

### **POWER PHRASES** - Say these to unlock enhanced AI modes:

#### **🔥 AUTONOMOUS WORK MODE**
- **`"GRIND"`** = AI works independently for extended periods, tests frequently, pushes to branch
- **`"stage by stage"`** = AI shows work incrementally, waits for your approval between stages
- **`"test frequently"`** = AI builds test infrastructure alongside main development

#### **🎯 FOCUS & DISCIPLINE MODE**  
- **`"TASK LOCK"`** = AI enters strict focus mode, no scope expansion without permission
- **`"EVIDENCE REQUIRED"`** = AI must provide concrete proof for all claims with source references
- **`"SYSTEMATIC DEBUGGING"`** = AI uses XML-structured root cause analysis with step-by-step verification

#### **🔍 RESEARCH & EXPLORATION MODE**
- **`"search the web"`** = AI uses tavily_search for current information before proceeding
- **`"SCOPE CREEP DETECTED"`** = AI immediately corrects course back to original objective

#### **🚀 DEVELOPMENT WORKFLOW MODE**
- **`"build test rigs"`** = AI creates quick testing infrastructure alongside main development
- **`"quick and dirty test code"`** = AI builds discardable debugging tools for rapid diagnosis
- **`"push to current branch"`** = AI commits and pushes after completing tasks
- **`"create tags"`** = AI tags important working builds with `git tag -a v1.0 -m "message"`

#### **🌐 WEB DEVELOPMENT MODE**
- **`"cache-busting headers"`** = AI adds cache-busting during active HTML/JS development
- **`"custom debug window"`** = AI creates Ctrl-D debug console for browser development
- **`"server restart required"`** = AI remembers when modifying server.js files
- **`"simulate user input"`** = AI acts like real human (normal mouse distances, human timing)

---

## 📚 ANTHROPIC RESEARCH-BACKED TECHNIQUES

### **XML-STRUCTURED THINKING** (10x Performance Boost)
Based on [Anthropic's Chain of Thought documentation](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/chain-of-thought), using XML tags dramatically improves AI reasoning:

**Instead of saying**: *"Debug this issue"*
**Say this**: *"Use XML-structured debugging to analyze this issue with `<debug_analysis>`, `<evidence_collection>`, `<root_cause_investigation>`, and `<solution_implementation>` sections"*

### **ROLE PROMPTING POWER** (Orders of Magnitude Improvement)
Based on [Anthropic's System Prompts guide](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/system-prompts), specific roles dramatically improve performance:

**Generic**: *"You are an expert coding assistant"*
**Powerful**: *"You are a senior software engineer with 15 years experience debugging distributed systems, Docker networking, and gRPC protocols"*

### **MULTISHOT PROMPTING** (Significant Accuracy Gains)
Based on [Anthropic's Multishot documentation](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/multishot-prompting), include examples:

**Instead of**: *"Fix this code"*
**Say this**: *"Fix this code. Here's an example of a similar fix I want: [provide before/after example]"*

---

## 🔧 OPENHANDS-SPECIFIC OPTIMIZATION TRICKS

### **NETWORKING ISSUES** (Critical for Success)
OpenHands runs in Docker containers that can't access localhost by default. Use these commands:

```bash
# Enable host networking (CRITICAL)
export SANDBOX_USE_HOST_NETWORK=true

# Alternative Docker networking fix
export SANDBOX_LOCAL_RUNTIME_URL="http://host.docker.internal"

# Test connectivity
curl -v http://localhost:8080/health || echo "NETWORK ISSUE DETECTED"
```

### **MULTI-TOOL EFFICIENCY** (Faster Execution)
Tell AI to combine operations in single commands:

**Instead of**: *"Check the files, then check git status, then look for package.json"*
**Say this**: *"Use efficient multi-tool commands: `cd /workspace && ls -la && git status && find . -name 'package.json'`"*

### **FILE SYSTEM NAVIGATION** (Avoid Errors)
- Always use absolute paths: `/workspace/project/file.py`
- Verify parent directories exist before creating files
- Use `str_replace_editor` for multiple file edits in single message

---

## 🎨 PROJECT CUSTOMIZATION TEMPLATES

### **For Web Development Projects**:
*"You are a full-stack web developer with expertise in HTML, JavaScript, WebGL, and browser debugging. Your mission is to execute web development tasks with systematic precision. Focus on cache-busting, cross-browser compatibility, and real-time debugging."*

### **For C++ Development Projects**:
*"You are a systems programmer with expertise in C++17, OpenGL, gRPC, and cross-platform development. Your mission is to execute C++ development tasks with systematic precision. Focus on memory management, build systems, and performance optimization."*

### **For Python Server Projects**:
*"You are a backend engineer with expertise in Python, asyncio, gRPC, and server architecture. Your mission is to execute server development tasks with systematic precision. Focus on concurrency, error handling, and API design."*

### **For Debugging Sessions**:
*"You are a debugging specialist who excels at root cause analysis and evidence-based problem solving. Use XML-structured debugging with concrete evidence collection and systematic hypothesis testing."*

---

## 🚀 ADVANCED CONTROL TECHNIQUES

### **EVALUATION-DRIVEN DEVELOPMENT** 
Based on [Anthropic's Building Evals cookbook](https://github.com/anthropics/anthropic-cookbook/blob/main/misc/building_evals.ipynb):

*"Build tests alongside development. Use code-based grading where possible. Create systematic performance measurements."*

### **CHAIN COMPLEX PROMPTS**
For multi-step tasks, break them into phases:

*"Phase 1: Analyze the current state with XML structure. Phase 2: Implement minimal fix. Phase 3: Verify with concrete proof. Wait for my approval between phases."*

### **PREFILL RESPONSES**
Guide AI output format:

*"Start your response with `<task_analysis>` and include REQUEST, CORE_OBJECTIVE, SCOPE_BOUNDARIES, and SUCCESS_CRITERIA."*

---

## 🎯 TROUBLESHOOTING KEYWORDS

### **When AI Goes Off Track**:
- **`"SCOPE CREEP DETECTED"`** - Forces immediate course correction
- **`"TASK LOCK"`** - Refocuses on original objective
- **`"EVIDENCE REQUIRED"`** - Demands concrete proof for claims

### **When AI Makes Assumptions**:
- **`"What evidence supports this?"`** - Forces evidence-based reasoning
- **`"Show me the exact error message"`** - Demands concrete data
- **`"Prove this works"`** - Requires verification before claiming success

### **When AI Overcomplicated Things**:
- **`"Minimal viable solution"`** - Focuses on simplest approach
- **`"One change at a time"`** - Prevents complex multi-step changes
- **`"What's the smallest fix?"`** - Encourages incremental approach

---

## 📊 PERFORMANCE MONITORING

### **SUCCESS INDICATORS** (AI is working well):
- Uses XML-structured thinking for complex tasks
- Provides concrete evidence for all claims
- Asks permission before expanding scope
- Delivers working solutions immediately
- Includes troubleshooting keywords in documentation

### **WARNING SIGNS** (AI needs correction):
- Makes claims without proof
- Expands scope without asking
- Provides generic advice instead of specific commands
- Builds complex solutions for simple problems
- Ignores existing working functionality

---

## 🔥 EMERGENCY COMMANDS

### **IMMEDIATE COURSE CORRECTION**:
- **`"Stop. Re-read my original request."`** - Forces refocus on core objective
- **`"That's not what I asked for."`** - Triggers immediate course correction
- **`"Show me concrete proof this works."`** - Demands verification
- **`"Scope creep detected - return to original task."`** - Forces realignment

### **RESET TO BASELINE**:
- **`"Start over with XML-structured task analysis."`** - Complete restart with proper structure
- **`"What exactly did I ask you to do?"`** - Forces re-reading of original request

---

## 🎖️ MASTERY CHECKLIST

### **✅ BASIC LEVEL** (Getting Started):
- [ ] Use activation keywords like "GRIND" and "TASK LOCK"
- [ ] Request XML-structured thinking for complex tasks
- [ ] Demand concrete evidence for all claims
- [ ] Set up networking with `SANDBOX_USE_HOST_NETWORK=true`

### **✅ INTERMEDIATE LEVEL** (Optimizing Performance):
- [ ] Customize role prompts for specific project types
- [ ] Use multishot prompting with examples
- [ ] Combine multiple operations in single commands
- [ ] Monitor for scope creep and course-correct immediately

### **✅ ADVANCED LEVEL** (Maximum Efficiency):
- [ ] Build evaluation frameworks alongside development
- [ ] Chain complex prompts with phase-by-phase approval
- [ ] Use prefill techniques to guide output format
- [ ] Create project-specific activation templates

---

## 📖 REFERENCE LINKS

### **Anthropic Official Documentation**:
- [Prompt Engineering Overview](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/overview)
- [Be Clear and Direct](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/be-clear-and-direct)
- [Chain of Thought](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/chain-of-thought)
- [System Prompts](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/system-prompts)
- [Multishot Prompting](https://docs.anthropic.com/en/docs/build-with-claude/prompt-engineering/multishot-prompting)

### **Anthropic Cookbook**:
- [Building Evals](https://github.com/anthropics/anthropic-cookbook/blob/main/misc/building_evals.ipynb)
- [Tool Use Examples](https://github.com/anthropics/anthropic-cookbook/tree/main/tool_use)
- [Multimodal Capabilities](https://github.com/anthropics/anthropic-cookbook/tree/main/multimodal)

### **OpenHands Documentation**:
- [OpenHands GitHub Repository](https://github.com/All-Hands-AI/OpenHands)
- [Microagents System](https://github.com/All-Hands-AI/OpenHands/blob/main/openhands/memory/memory.py)

---

**Remember**: The AI agent is designed to be your systematic, disciplined, evidence-based partner. Use these techniques to unlock its full potential while maintaining focus and preventing scope creep.

*Version 2.0 - Based on Anthropic research and OpenHands optimization*
*Last Updated: 2025-01-15*