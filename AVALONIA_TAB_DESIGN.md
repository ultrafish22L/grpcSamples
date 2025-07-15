# Avalonia gRPC Testbed - Tab Design Specifications

## 🎯 Overview
Design specifications for expanding the Avalonia gRPC Testbed with comprehensive Node System and Render Engine tabs based on analysis of `apinodesystem.proto` and `apirender.proto`.

## 📊 Proto File Analysis

### apinodesystem.proto (11,292 lines)
**Services:**
- `ApiItemService` - Basic item operations (destroy, name, position, select, time)
- `ApiNodeService` - Node creation, pin management, connections, type handling  
- `ApiNodeGraphService` - Graph operations (create, find nodes, copy, group/ungroup)
- `ApiRootNodeGraphService` - Root graph management

**Key Capabilities:**
- Node creation and management
- Pin connections and data flow
- Graph operations (copy, group, ungroup)
- Node inspection and property access
- Dynamic pin management
- Asset path management
- Time transformation for animation

### apirender.proto (2,265 lines)
**Services:**
- `ApiRenderEngineService` - Core rendering engine with extensive capabilities
- `ApiRenderImageService` - Render image management

**Key Capabilities:**
- Render target management (camera, geometry, render target nodes)
- Render region control
- Tonemap operations (async/sync)
- Render pass management and AOV control
- Image saving (various formats, deep EXR, multi-layer)
- Device management (GPU selection, memory usage, hardware RT)
- Render statistics and performance monitoring
- Material/texture preview rendering
- Out-of-core memory management
- Render priority and device configuration

---

## 🎯 Node System Tab Design Options

### Option A: Node Graph Manager
```
📊 Graph Operations
├── 🔧 Create Node Graph
├── 📋 List All Graphs  
├── 🔍 Find Nodes by Type
├── 📁 Load/Save Graph
└── 🗑️ Clear Graph

🎯 Node Management  
├── ➕ Create Node (dropdown: materials, textures, geometry, etc.)
├── 🔗 Connect Pins (source → target)
├── 📝 Node Properties (name, position, type)
├── 🎨 Pin Inspector (type, connections, values)
└── 🔄 Configure Empty Pins

🎬 Animation & Time
├── ⏱️ Set Time Transform
├── 🎞️ Animation Controls
└── 📈 Time Sampling

📦 Asset Management
├── 📂 Get Asset Paths
├── 🔄 Switch to File Data
└── 💾 Export Plugin Data
```

### Option B: Visual Node Editor ⭐ RECOMMENDED
```
🖼️ Graph Visualization
├── 🎨 Show Node Graph Window
├── 🔍 Node Inspector Panel
├── 📐 Recenter Graph
└── 🎯 Select/Highlight Nodes

🔧 Node Operations
├── 📋 Node Type Browser
├── ⚡ Quick Node Creation
├── 🔗 Pin Connection Matrix
└── 🎛️ Dynamic Pin Manager

🏗️ Graph Structure
├── 📊 Group/Ungroup Items
├── 📋 Copy Item Trees
├── 🔄 Unfold Inspectable Graphs
└── 🗂️ Find Items by Name
```

### Option C: Developer API Tester
```
🧪 API Testing Suite
├── 📝 Raw gRPC Calls
├── 🎯 Service Method Browser
├── 📊 Request/Response Logger
└── ⚡ Batch Operations

🔍 Node Inspection
├── 🎯 Item Properties (ID, name, position)
├── 📌 Pin Analysis (type, connections, info)
├── 🔗 Connection Tracing
└── 📈 Version & Statistics

🎮 Interactive Controls
├── 🎨 Live Node Creation
├── 🔧 Real-time Pin Editing
├── 📊 Graph State Monitoring
└── 🎬 Animation Testing
```

---

## 🎬 Render Tab Design Options

### Option A: Render Control Center ⭐ RECOMMENDED
```
🎯 Render Targets
├── 📷 Set Camera Node
├── 🎭 Set Geometry Node  
├── 🎬 Set Render Target
└── 📊 Get Current Targets

🖼️ Render Operations
├── ▶️ Start/Stop Render
├── 🎨 Grab Render Result
├── 💾 Save Image (PNG/EXR/HDR)
├── 🎞️ Save Render Passes
└── 🔄 Synchronous Tonemap

⚙️ Render Settings
├── 📐 Set Render Region
├── 🎨 Sub-sampling Mode
├── 🏺 Clay Mode Toggle
├── 📊 FPS Control
└── 🎭 AOV Management

📊 Performance Monitor
├── 💾 Memory Usage
├── 📈 Render Statistics
├── ⏱️ Render Progress
└── 🔥 Device Status
```

### Option B: GPU Management Studio
```
🖥️ Device Management
├── 📊 GPU Device List
├── ⚡ Device Activity Control
├── 🎯 Render Priority Settings
├── 🔗 Peer-to-Peer Config
└── 🛠️ Hardware Ray Tracing

💾 Memory Control
├── 📊 Memory Usage Monitor
├── 🔄 Out-of-Core Settings
├── 📈 Resource Statistics
└── ⚙️ GPU Headroom Config

🎨 Render Quality
├── 🎭 Tonemap Parameters
├── 🎨 Color Space Settings
├── 📊 Render Pass Control
└── 🎞️ Deep Image Settings

🔍 Diagnostics
├── ❌ Error State Monitor
├── 📊 Device Statistics
├── 🔧 Compilation Status
└── 📈 Performance Metrics
```

### Option C: Production Pipeline
```
🎬 Render Pipeline
├── 🎯 Batch Render Queue
├── 📊 Multi-Pass Rendering
├── 💾 Export Workflows
└── 🎨 Preview Generation

📊 Quality Control
├── 🔍 Material Preview
├── 🎨 Texture Preview  
├── 📈 Statistics Analysis
└── 🎯 Scene Bounds Check

💾 Export & Save
├── 🖼️ Image Export (all formats)
├── 🎞️ Multi-layer EXR
├── 🌊 Deep Image EXR
└── 💾 Render State Save/Load

🔧 Advanced Settings
├── ⚙️ Async Callbacks
├── 🎨 Custom Tonemap
├── 📊 Render Region Tools
└── 🎯 Clay Render Mode
```

---

## 🏗️ Implementation Strategy

### Phase 1: Core Tab Structure
1. **Replace existing tabs** with Node System and Render tabs
2. **Maintain header** with connection controls and status
3. **Add proto file compilation** for C# gRPC clients
4. **Create base UI layouts** for both tabs

### Phase 2: Node System Tab Implementation
**Recommended: Option B (Visual Node Editor)**
- Left panel: Node creation and management tools
- Center: Graph visualization area (placeholder initially)
- Right panel: Node inspector and properties
- Bottom: Operation log and status

### Phase 3: Render Tab Implementation  
**Recommended: Option A (Render Control Center)**
- Left panel: Render targets and operations
- Center: Render preview/result display
- Right panel: Settings and device management
- Bottom: Performance monitoring and statistics

### Phase 4: Advanced Features
- Real-time status updates
- Comprehensive error handling
- Performance monitoring
- Professional styling consistency

---

## 🎨 UI Layout Specifications

### Node System Tab Layout
```
┌─────────────────────────────────────────────────────────────┐
│ Header: Connection Controls + Status LED                    │
├─────────────────┬─────────────────────┬─────────────────────┤
│ Node Operations │ Graph Visualization │ Node Inspector      │
│                 │                     │                     │
│ 🔧 Create Node  │ [Graph Display]     │ 📝 Properties       │
│ 📋 Node Types   │                     │ 🔗 Connections      │
│ 🔗 Pin Manager  │                     │ 🎨 Pin Details      │
│ 📊 Graph Ops    │                     │ ⚙️ Settings         │
│                 │                     │                     │
├─────────────────┴─────────────────────┴─────────────────────┤
│ 📋 Operation Log + Status                                   │
└─────────────────────────────────────────────────────────────┘
```

### Render Tab Layout
```
┌─────────────────────────────────────────────────────────────┐
│ Header: Connection Controls + Status LED                    │
├─────────────────┬─────────────────────┬─────────────────────┤
│ Render Controls │ Render Preview      │ Settings & Devices  │
│                 │                     │                     │
│ 🎯 Targets      │ [Render Display]    │ 🖥️ GPU Management   │
│ ▶️ Operations   │                     │ ⚙️ Render Settings  │
│ 💾 Export       │                     │ 🎨 Quality Control  │
│ 📊 Passes       │                     │ 📊 Statistics       │
│                 │                     │                     │
├─────────────────┴─────────────────────┴─────────────────────┤
│ 📈 Performance Monitor + Memory Usage                       │
└─────────────────────────────────────────────────────────────┘
```

---

## 🔧 Technical Requirements

### Proto File Integration
- Compile `apinodesystem.proto` and `apirender.proto` to C#
- Generate gRPC client stubs for Avalonia
- Add to existing protobuf build pipeline
- Update CMakeLists.txt for proto generation

### UI Components Needed
- Enhanced TabControl styling
- Professional button layouts
- Real-time status indicators
- Progress bars and statistics displays
- Tree views for node hierarchies
- Property grids for node inspection

### Performance Considerations
- Async/await patterns for all gRPC calls
- UI thread safety with Dispatcher
- Efficient logging and status updates
- Memory management for large node graphs
- Responsive UI during long operations

---

## 🎯 Success Criteria

### Node System Tab
- ✅ Create and manage node graphs
- ✅ Inspect node properties and connections
- ✅ Handle pin management and data flow
- ✅ Provide comprehensive API testing
- ✅ Real-time graph state monitoring

### Render Tab
- ✅ Control render operations and targets
- ✅ Monitor GPU devices and performance
- ✅ Export renders in multiple formats
- ✅ Manage render passes and AOVs
- ✅ Provide detailed render statistics

### Overall Experience
- ✅ Professional Octane-themed interface
- ✅ Comprehensive error handling and logging
- ✅ Real-time status updates and feedback
- ✅ Intuitive workflow for 3D professionals
- ✅ Complete API coverage for both services

---

## 📝 Next Steps

1. **Implement proto compilation** for both files
2. **Create tab structure** with recommended layouts
3. **Build Node System controls** (Option B approach)
4. **Build Render controls** (Option A approach)  
5. **Add comprehensive testing** and error handling
6. **Polish UI** with professional styling
7. **Document usage** and API coverage

---

*Generated: 2025-01-15*  
*Status: Design Complete - Ready for Implementation*  
*Repository: ultrafish22L/grpcSamples*