# 🔥 PROJECT DISCIPLINE: Bulletproof Development Standards

## 🎯 PROJECT MISSION
**OctaneWeb is a professional 3D web application providing real-time scene management, node graph editing, and seamless Octane Render integration through bulletproof gRPC architecture.**

## 🔥 CORE PROJECT PRINCIPLES

### 1. **REAL DATA OR NOTHING**
- No mock data, no fallbacks - connect to live Octane or show empty UI
- Every feature must work with actual Octane data
- User has working Octane instance - use it
- Mock servers only for development when Octane unavailable

### 2. **BULLETPROOF ARCHITECTURE**
- Multiple connection strategies (file://, localhost, Docker networking)
- Graceful degradation when services unavailable
- Pure pass-through proxy with no transformations
- Error transparency with detailed logging

### 3. **PROFESSIONAL GRADE**
- OTOY branding and industry-standard UI patterns
- Dark theme matching professional 3D software
- Responsive design for all screen sizes
- Zero external dependencies

### 4. **PROVEN PATTERNS ONLY**
- Study working code (testGrpcApi, octaneGrpcTest) before implementing
- Copy successful patterns exactly
- ObjectPtr.type must match service class (FUNDAMENTAL LAW)
- Incremental testing with real data

## 🚨 PROJECT CRITICAL SUCCESS FACTORS

### Scene Outliner Requirements:
- ✅ Shows "Scene" as root (not "Root")
- ✅ Displays real Octane hierarchy: Scene → Render target, teapot.obj
- ✅ Expand/collapse functionality with proper icons
- ✅ Visibility toggles for scene objects
- ✅ Real-time updates from live Octane data

### Node Graph Editor Requirements:
- ✅ Right-click context menus for node creation
- ✅ Hierarchical node types (Geometry, Lights, Cameras)
- ✅ Visual node connections and editing
- ✅ Auto-fit and zoom functionality
- ✅ Professional node rendering

### BulletproofClient Requirements:
- ✅ Multiple fallback connection strategies
- ✅ Real data enforcement (no mock fallbacks)
- ✅ Proper ObjectRef extraction from nested responses
- ✅ Service selection based on working patterns
- ✅ Error handling with user-friendly messages

### Bulletproof Proxy Requirements:
- ✅ Pure pass-through HTTP-to-gRPC translation
- ✅ Dynamic service registry (7+ gRPC services)
- ✅ Comprehensive logging with emoji indicators
- ✅ CORS compliance for web clients
- ✅ No hardcoded type transformations

## 🔧 DEVELOPMENT WORKFLOW

### Phase 1: Study Working Code
```bash
# MANDATORY - Check existing patterns first
cd testGrpcApi && grep -r "scene\|tree\|children" .
cd proxy && grep -A10 -B10 "getOwnedItems" grpc_proxy.py
```

### Phase 2: Test Individual Components
```bash
# MANDATORY - Verify each API call works
curl -X POST http://localhost:51998/ApiProjectManagerService/rootNodeGraph -d '{}'
curl -X POST http://localhost:51998/ApiNodeGraphService/getOwnedItems -d '{"objectPtr": {"handle": X, "type": Y}}'
```

### Phase 3: Implement Following Proven Patterns
- Copy exact patterns from working implementations
- Use pure pass-through proxy approach
- Test with real Octane data at each step
- No hardcoded type mappings or transformations

### Phase 4: Verify with Real Data
- Test with live Octane instance
- Screenshot actual browser display
- Verify scene outliner shows real hierarchy
- Confirm all features work with actual data

## 🚨 FORBIDDEN ANTI-PATTERNS

### ❌ NEVER DO THESE:
- **Mock Data Fallbacks**: No fake data when real data unavailable
- **Type Transformations**: Never modify ObjectPtr.type values
- **Hardcoded Mappings**: Proxy must be pure pass-through
- **F12 Dependency**: Build debug console into app
- **Scope Creep**: Fix only what's explicitly requested
- **Assumption Cascades**: Gather evidence before making claims

### ❌ IMMEDIATE SUPERVISION TRIGGERS:
- Claiming success without visual verification
- Using mock data instead of attempting real connection
- Hardcoding service/type mappings in proxy
- Relying on browser F12 instead of built-in logging
- Going down rabbit holes instead of following working patterns

## 🎖️ PROJECT SUCCESS METRICS

### Technical Excellence:
- ✅ Scene outliner populated with real Octane data
- ✅ All API calls use proven patterns from working code
- ✅ Bulletproof proxy running with 7+ services registered
- ✅ BulletproofClient connecting with multiple fallback strategies
- ✅ Professional UI matching octane_ui.png requirements

### User Experience:
- ✅ Shows "Scene" with children like "Render target" and "teapot.obj"
- ✅ Expand/collapse scene hierarchy works smoothly
- ✅ Right-click context menus in node graph
- ✅ Debug console accessible via Ctrl-D
- ✅ Professional OTOY branding and dark theme

### Development Quality:
- ✅ No mock data, no fallbacks - real data or empty UI
- ✅ Cache busting implemented for development
- ✅ Error transparency with detailed logging
- ✅ Cross-platform compatibility verified
- ✅ Zero external dependencies

## 🔥 PROJECT COMMANDMENTS

### 1. **THOU SHALL STUDY WORKING CODE FIRST**
Before implementing any feature, study existing working implementations in testGrpcApi and octaneGrpcTest.

### 2. **THOU SHALL USE REAL DATA ONLY**
No mock data, no fallbacks. Connect to live Octane or show empty UI.

### 3. **THOU SHALL FOLLOW PROVEN PATTERNS**
Copy exact patterns from working code. ObjectPtr.type must match service class.

### 4. **THOU SHALL TEST INCREMENTALLY**
Every API call tested individually before integration. Every change verified with real data.

### 5. **THOU SHALL MAINTAIN BULLETPROOF ARCHITECTURE**
Pure pass-through proxy, multiple connection strategies, graceful degradation.

---

**This project discipline ensures OctaneWeb delivers professional-grade 3D web application capabilities with bulletproof reliability and industry-standard user experience.**