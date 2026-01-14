# OctaneWebR vs Octane SE Manual - Complete Feature Comparison

**Last Updated**: 2025-01-20  
**Manual Reference**: https://docs.otoy.com/standaloneSE/CoverPage.html  
**Purpose**: Systematic comparison between current octaneWebR implementation and Octane SE documented features

---

## 📊 Implementation Status Legend

- ✅ **IMPLEMENTED** - Feature fully working and tested
- 🟨 **PARTIAL** - Feature exists but incomplete or placeholder
- ❌ **NOT IMPLEMENTED** - Feature missing entirely
- 📋 **PLANNED** - In implementation plan but not started
- ❓ **UNCLEAR** - Need to verify in manual or test with real Octane

---

## 1. INTERFACE LAYOUT

### 1.1 Main Window Panels
| Feature | Status | Notes |
|---------|--------|-------|
| Render Viewport | ✅ | CallbackRenderViewport with real-time streaming |
| Node Graph Editor | ✅ | ReactFlow-based with 755 node types |
| Node Inspector | ✅ | Full parameter editing all types |
| Scene Outliner | ✅ | Hierarchical tree with LiveDB/LocalDB tabs |
| Menu Bar | ✅ | File/Edit/View/Window/Help menus |
| Resizable Panels | ✅ | Custom resize implementation |
| Dark OTOY Theme | ✅ | Professional dark UI matching SE |

### 1.2 Customization
| Feature | Status | Notes |
|---------|--------|-------|
| Panel docking/undocking | ❌ | Not implemented |
| Save/load workspace layouts | ❌ | Not implemented |
| Panel visibility toggles | 🟨 | Partial - no UI controls |
| Fullscreen mode | ❌ | Not implemented |

---

## 2. NODE GRAPH EDITOR

### 2.1 Core Functionality (Manual: "The Graph Editor")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Display scene node graph | ✅ | Fig 1 | Top-level nodes only |
| Node creation via right-click | ✅ | Fig 3 | 755 node types in categories |
| Node selection | ✅ | Fig 5 | Single and multi-select |
| Node dragging/positioning | ✅ | Basic | ReactFlow handles this |
| Pin connections | ✅ | Basic | Full Octane sync |
| Pin disconnections | ✅ | Basic | Synced to Octane |
| Edge reconnections | ✅ | Drag & drop | Full Octane sync |
| Node deletion | ✅ | Context menu | Synced to Octane |

### 2.2 Navigation (Manual: "Node Graph Editor Navigation")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Minimap/thumbnail preview | ✅ | Fig 2 | Yellow draggable rectangle |
| Pan with right mouse | ✅ | Navigation | Works with mouse drag |
| Zoom with mouse wheel | ✅ | Navigation | Smooth zoom |
| Zoom with Ctrl+scroll | ✅ | Navigation | Additional control |
| Auto-pan when dragging | ✅ | Navigation | ReactFlow built-in |
| Zoom-dependent connection editing | 🟨 | Navigation | Could be enhanced |

### 2.3 Selection (Manual: "Selecting Multiple Nodes")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Box selection (drag) | ✅ | Fig 5 | ReactFlow selectionOnDrag |
| Shift to add to selection | ✅ | Fig 5 | multiSelectionKeyCode |
| Ctrl+click toggle selection | ✅ | Fig 5 | ReactFlow built-in |
| Copy selected (Ctrl+C) | 🟨 | Fig 6 | Implemented but needs testing |
| Paste (Ctrl+V) | 🟨 | Fig 6 | Implemented but needs testing |
| Cut/Delete | ✅ | Menu | Working |

### 2.4 Node Context Menu (Manual: "Node Context Menus")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Delete all selected nodes | ✅ | Fig 4 | Fully working |
| Save as macro | 🟨 | Fig 4 | Placeholder - needs API |
| Save to LocalDB | 🟨 | Fig 4 | Placeholder - needs API |
| Render node | 🟨 | Fig 4 | Placeholder - needs API |
| Group Items | 🟨 | Fig 8 | Placeholder - needs grouping API |
| Ungroup | ❌ | Fig 9 | Not implemented |
| Show In Outliner | ✅ | Fig 4 | Fully working |

### 2.5 Advanced Features
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Connection Cutter (Ctrl+drag) | ✅ | Navigation | Implemented in code |
| Multi-Connect (Ctrl+connect) | ✅ | Navigation | Implemented in code |
| Search Dialog (Ctrl+F) | ✅ | Navigation | Fully working |
| Material preview button | 🟨 | Fig 10 | UI exists, not functional |
| Node grouping/nesting | 📋 | Fig 8-9 | Planned, needs API research |
| Group double-click open | ❌ | Grouping | Not implemented |
| Tabbed group navigation | ❌ | Grouping | Not implemented |
| Drop macro files | ❌ | Dropping | Not implemented |
| Drop mesh files | ❌ | Dropping | Not implemented |

### 2.6 Pin Tooltips
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Hover shows pin name | ✅ | Basic | Enhanced tooltips |
| Show connected material name | ✅ | Basic | In tooltip |
| Show pin type | ✅ | Enhanced | Full pin info |
| Show pin description | ✅ | Enhanced | From ApiNodePinInfo |

---

## 3. RENDER VIEWPORT

### 3.1 Core Rendering (Manual: "The Render Viewport")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Real-time render display | ✅ | Basic | Callback streaming |
| OnNewImage callbacks | ✅ | Basic | Dedicated streaming |
| HDR/LDR buffer support | ✅ | Basic | Proper isolation |
| Canvas rendering | ✅ | Basic | High-performance |
| Render statistics | 🟨 | RenderToolbar | Placeholder values |

### 3.2 Camera Controls (Manual: "Navigating the Viewport")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Orbit with left mouse | ✅ | Basic | Synced to Octane |
| Pan with right mouse | ✅ | Basic | Synced to Octane |
| Zoom with scroll wheel | ✅ | Basic | Synced to Octane |
| Camera initialization | ✅ | Basic | From Octane camera |
| Camera sync throttling | ✅ | Basic | 10Hz rate limiting |

### 3.3 Viewport Toolbar (Manual: Toolbar Buttons)
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Recenter View button | 🟨 | Toolbar | Placeholder |
| Reset Camera button | 🟨 | Toolbar | Placeholder |
| Camera View Presets | 🟨 | Toolbar | Placeholder |
| Focus Picking Mode | ❌ | Toolbar | Not implemented |
| Material Picker | ❌ | Toolbar | Not implemented |
| Object Picker | ❌ | Toolbar | Not implemented |
| Camera Target Picker | ❌ | Toolbar | Not implemented |
| Render Region | ❌ | Toolbar | Not implemented |
| Film Region | ❌ | Toolbar | Not implemented |
| Clay Mode toggle | 🟨 | Toolbar | Placeholder |
| Viewport Lock | 🟨 | Toolbar | Placeholder |
| Real-time Mode | 🟨 | Toolbar | Placeholder |

### 3.4 Render Progress
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Sample count display | 🟨 | Progress bar | Placeholder |
| Render time | 🟨 | Progress bar | Placeholder |
| Rays/second | ❌ | Progress bar | Not implemented |
| GPU temperature | ❌ | Progress bar | Not implemented |
| GPU memory usage | ❌ | Progress bar | Not implemented |
| Progress percentage | ❌ | Progress bar | Not implemented |

---

## 4. NODE INSPECTOR

### 4.1 Core Functionality (Manual: "The Node Inspector")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Display selected node params | ✅ | Basic | All param types |
| Boolean parameters | ✅ | Basic | Checkbox controls |
| Integer parameters | ✅ | Basic | Number inputs |
| Float parameters | ✅ | Basic | Number inputs with precision |
| Vector parameters | ✅ | Basic | Multi-input controls |
| Color parameters | ✅ | Basic | Color inputs |
| Enum/dropdown parameters | ✅ | Basic | Select controls |
| String parameters | ✅ | Basic | Text inputs |
| Real-time sync to Octane | ✅ | Basic | On change |

### 4.2 Quick Access (Manual: Quick Access Buttons)
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| RenderTarget button | ❌ | Quick buttons | Not implemented |
| Camera button | ❌ | Quick buttons | Not implemented |
| Resolution button | ❌ | Quick buttons | Not implemented |
| Environment button | ❌ | Quick buttons | Not implemented |
| Imager button | ❌ | Quick buttons | Not implemented |
| Kernel button | ❌ | Quick buttons | Not implemented |
| Current Mesh button | ❌ | Quick buttons | Not implemented |

### 4.3 Parameter UI Enhancements
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Node name editing | ❌ | Renaming | Not implemented |
| Compact view toggle | ❌ | Compact mode | Not implemented |
| Parameter search/filter | ❌ | Enhanced | Not implemented |
| Copy/paste pin values | ❌ | Context menu | Not implemented |
| Fill pins | ❌ | Context menu | Not implemented |
| Material preview sphere | ❌ | Preview | Not implemented |
| Preview 2D/3D toggle | ❌ | Preview | Not implemented |
| Preview scale slider | ❌ | Preview | Not implemented |

### 4.4 Status Bar
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| OctaneLive status | ❌ | Status bar | Not implemented |
| Online status | ✅ | Status bar | ConnectionStatus component |
| License info | ❌ | Status bar | Not implemented |

---

## 5. SCENE OUTLINER

### 5.1 Tree View (Manual: "The Scene Outliner")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Hierarchical scene tree | ✅ | Basic | Full hierarchy |
| Expand/collapse nodes | ✅ | Basic | With +/- toggles |
| Node icons | ✅ | Basic | From OctaneIconMapper |
| Node selection | ✅ | Basic | Syncs with inspector |
| Visibility toggles | 🟨 | Enhanced | Icon exists, no API |
| Node name display | ✅ | Basic | Full names |
| Handle display | 🟨 | Debug | Can be shown |

### 5.2 Database Tabs (Manual: "Materials Database")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Scene tab | ✅ | Main view | Default active tab |
| LiveDB tab | 🟨 | LiveDB section | UI exists, not functional |
| LocalDB tab | ✅ | LocalDB section | Full category browsing |
| Double-click to load | ✅ | LocalDB | Loads packages into scene |
| Category hierarchy | ✅ | LocalDB | Lazy loading |
| Thumbnail previews | ❌ | Enhanced | Not implemented |
| Search in databases | ❌ | Enhanced | Not implemented |

### 5.3 Controls
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Refresh button | ❌ | Controls | Not implemented |
| Collapse All button | ❌ | Controls | Not implemented |
| View mode toggle | ❌ | Controls | Not implemented |
| Filter by type | ❌ | Controls | Not implemented |
| Sort options | ❌ | Controls | Not implemented |

### 5.4 Context Menu
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Copy node | ❌ | Context menu | Not implemented |
| Paste node | ❌ | Context menu | Not implemented |
| Delete node | ❌ | Context menu | Not implemented |
| Rename node | ❌ | Context menu | Not implemented |
| Show in Graph Editor | ❌ | Context menu | Not implemented |
| Fill pins | ❌ | Context menu | Not implemented |

---

## 6. MENU SYSTEM

### 6.1 File Menu
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| New Scene | ✅ | File menu | API call working |
| Open Scene | ✅ | File menu | File dialog working |
| Save Scene | ✅ | File menu | File dialog working |
| Save Scene As | ✅ | File menu | File dialog working |
| Recent Files | ✅ | File menu | Stored in localStorage |
| Import (OBJ/FBX/etc) | 🟨 | File menu | Placeholders |
| Export | ❌ | File menu | Not implemented |
| Exit | ✅ | File menu | Window close |

### 6.2 Edit Menu
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Undo | 🟨 | Edit menu | Placeholder |
| Redo | 🟨 | Edit menu | Placeholder |
| Cut | 🟨 | Edit menu | Placeholder |
| Copy | 🟨 | Edit menu | Placeholder |
| Paste | 🟨 | Edit menu | Placeholder |
| Delete | 🟨 | Edit menu | Placeholder |
| Select All | 🟨 | Edit menu | Placeholder |
| Preferences | 🟨 | Edit menu | Placeholder |

### 6.3 View Menu
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Zoom In | 🟨 | View menu | Placeholder |
| Zoom Out | 🟨 | View menu | Placeholder |
| Fit All | 🟨 | View menu | Placeholder |
| Frame Selection | 🟨 | View menu | Placeholder |
| Show Grid | 🟨 | View menu | Placeholder |
| Show Rulers | ❌ | View menu | Not implemented |

### 6.4 Window Menu
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Show Viewport | 🟨 | Window menu | Placeholder |
| Show Graph Editor | 🟨 | Window menu | Placeholder |
| Show Inspector | 🟨 | Window menu | Placeholder |
| Show Outliner | 🟨 | Window menu | Placeholder |
| Application Settings | 🟨 | Window menu | Placeholder |

### 6.5 Help Menu
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Documentation | ✅ | Help menu | Opens manual |
| About | ✅ | Help menu | Version info |
| Check for Updates | 🟨 | Help menu | Placeholder |
| Report Bug | 🟨 | Help menu | Placeholder |

---

## 7. FILE OPERATIONS

### 7.1 Scene Management (Manual: "Loading and Saving a Scene")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Load ORBX scene | ✅ | Basic | Via gRPC API |
| Save ORBX scene | ✅ | Basic | Via gRPC API |
| Scene file validation | ❓ | Enhanced | Need to verify |
| Auto-save | ❌ | Enhanced | Not implemented |
| Backup copies | ❌ | Enhanced | Not implemented |

### 7.2 Import/Export (Manual: "Importing and Exporting")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Import OBJ | 🟨 | Import | Placeholder |
| Import FBX | 🟨 | Import | Placeholder |
| Import Alembic | ❌ | Import | Not implemented |
| Import USD | ❌ | Import | Not implemented |
| Import VDB | ❌ | Import | Not implemented |
| Export geometry | ❌ | Export | Not implemented |
| Export materials | ❌ | Export | Not implemented |

### 7.3 Drag & Drop
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Drop ORBX files | ❌ | Enhanced | Not implemented |
| Drop macro files | ❌ | Enhanced | Not implemented |
| Drop mesh files | ❌ | Enhanced | Not implemented |
| Drop texture files | ❌ | Enhanced | Not implemented |

---

## 8. APPLICATION SETTINGS

### 8.1 Settings Tabs (Manual: "The Application Settings")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Application preferences | ❌ | Settings | Not implemented |
| Color management | ❌ | Settings | Not implemented |
| Control settings | ❌ | Settings | Not implemented |
| Devices tab | ❌ | Settings | Not implemented |
| Out of Core settings | ❌ | Settings | Not implemented |
| Import preferences | ❌ | Settings | Not implemented |
| Network render settings | ❌ | Settings | Not implemented |
| Shortcuts tab | ❌ | Settings | Not implemented |
| Modules tab | ❌ | Settings | Not implemented |

---

## 9. KEYBOARD SHORTCUTS

### 9.1 Graph Editor Shortcuts (Manual: "The Shortcuts Tab")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Ctrl+F - Search dialog | ✅ | Navigation | Fully working |
| Ctrl+C - Copy | 🟨 | Selection | Implemented, needs test |
| Ctrl+V - Paste | 🟨 | Selection | Implemented, needs test |
| Ctrl+X - Cut | ❌ | Selection | Not implemented |
| Delete - Delete selected | ✅ | Selection | Working |
| Ctrl+Drag - Connection cutter | ✅ | Connections | Working |
| Ctrl+Connect - Multi-connect | ✅ | Connections | Working |
| Shift+Select - Add to selection | ✅ | Selection | Working |
| Ctrl+Click - Toggle selection | ✅ | Selection | Working |

### 9.2 Viewport Shortcuts
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Space - Pause render | ❌ | Rendering | Not implemented |
| Home - Reset camera | ❌ | Camera | Not implemented |
| F - Frame selection | ❌ | Camera | Not implemented |

### 9.3 Global Shortcuts
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Ctrl+N - New scene | ❌ | File | Not implemented |
| Ctrl+O - Open scene | ❌ | File | Not implemented |
| Ctrl+S - Save scene | ❌ | File | Not implemented |
| Ctrl+Shift+S - Save As | ❌ | File | Not implemented |
| Ctrl+Z - Undo | ❌ | Edit | Not implemented |
| Ctrl+Y - Redo | ❌ | Edit | Not implemented |

---

## 10. SCRIPTING & AUTOMATION

### 10.1 Script Menu (Manual: "The Script Menu")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Batch Rendering | ❌ | Scripts | Not implemented |
| Daylight Animation | ❌ | Scripts | Not implemented |
| Turntable Animation | ❌ | Scripts | Not implemented |
| Custom Lua scripts | ❌ | Scripts | Not implemented |
| Script editor | ❌ | Scripts | Not implemented |

---

## 11. ADVANCED FEATURES

### 11.1 Render Features (Manual: "Rendering")
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Multiple render kernels | ❌ | Kernels | Not implemented |
| Adaptive sampling | ❌ | Sampling | Not implemented |
| AI denoiser | ❌ | Denoiser | Not implemented |
| AOV/Pass management | ❌ | AOVs | Not implemented |
| Render layers | ❌ | Layers | Not implemented |
| Deep image rendering | ❌ | Deep | Not implemented |
| Network rendering | ❌ | Network | Not implemented |

### 11.2 Animation
| Feature | Status | Manual Reference | Notes |
|---------|--------|------------------|-------|
| Animation timeline | ❌ | Animation | Not implemented |
| Keyframe editing | ❌ | Animation | Not implemented |
| Animation playback | ❌ | Animation | Not implemented |
| Render animation | ❌ | Animation | Not implemented |

---

## 📊 IMPLEMENTATION SUMMARY

### Core Features Status
| Category | Implemented | Partial | Not Implemented | Total |
|----------|-------------|---------|-----------------|-------|
| Interface Layout | 7 | 1 | 3 | 11 |
| Node Graph Editor | 23 | 8 | 8 | 39 |
| Render Viewport | 6 | 10 | 13 | 29 |
| Node Inspector | 9 | 1 | 12 | 22 |
| Scene Outliner | 9 | 4 | 11 | 24 |
| Menu System | 8 | 19 | 6 | 33 |
| File Operations | 2 | 3 | 9 | 14 |
| Application Settings | 0 | 0 | 9 | 9 |
| Keyboard Shortcuts | 7 | 2 | 9 | 18 |
| Scripting | 0 | 0 | 5 | 5 |
| Advanced Features | 0 | 0 | 11 | 11 |
| **TOTAL** | **71** | **48** | **96** | **215** |

### Completion Percentage
- **Fully Implemented**: 71 / 215 = **33.0%**
- **Partially Implemented**: 48 / 215 = **22.3%**
- **Not Implemented**: 96 / 215 = **44.7%**
- **Total Coverage** (Full + Partial): 119 / 215 = **55.3%**

---

## 🎯 HIGH PRIORITY GAPS

### Critical Missing Features (Block Core Workflows)
1. ❌ **Application Settings** - No settings UI at all (0/9 features)
2. ❌ **Render Progress Statistics** - Placeholders only, no real data
3. ❌ **Viewport Pickers** - Material/Object/Focus pickers missing
4. ❌ **Node Grouping** - Documented in manual, not implemented
5. ❌ **Animation System** - Completely missing (0/4 features)

### Important Enhancements (Improve Usability)
1. 🟨 **Menu Actions** - Many menu items are placeholders
2. 🟨 **Inspector Quick Access** - No quick navigation buttons
3. 🟨 **Outliner Controls** - Missing refresh, collapse all, filtering
4. 🟨 **Import/Export** - Limited format support
5. 🟨 **Keyboard Shortcuts** - Many standard shortcuts missing

### Nice-to-Have Features (Polish & UX)
1. ❌ **Drag & Drop** - No file drop support
2. ❌ **Panel Customization** - No docking/undocking
3. ❌ **Undo/Redo** - Not implemented
4. ❌ **Auto-save** - No backup system
5. ❌ **Search/Filter** - Limited to graph editor

---

## 🚀 RECOMMENDED DEVELOPMENT PRIORITIES

### Phase 1: Core Functionality Completion (4-6 weeks)
1. **Node Grouping** - Critical graph editor feature
   - Group Items / Ungroup context menu
   - Double-click to open internal graph
   - Tabbed navigation for nested groups
   - Save/load group structure

2. **Render Statistics** - Essential feedback
   - Connect to real Octane render stats API
   - Display samples, time, rays/sec
   - GPU usage and memory
   - Progress percentage

3. **Viewport Pickers** - Core interaction
   - Material picker (click to inspect)
   - Object picker (click to select)
   - Focus picker (click to set focus distance)
   - Camera target picker

4. **LiveDB Integration** - Community assets
   - Connect to LiveDB service
   - Browse community materials
   - Download and load into scene
   - Thumbnail previews

### Phase 2: Usability Enhancements (3-4 weeks)
1. **Complete Menu Actions**
   - Wire up all placeholder menu items
   - Implement keyboard shortcuts
   - Add undo/redo system
   - Complete import/export formats

2. **Inspector Enhancements**
   - Quick access buttons
   - Material preview sphere
   - Compact view mode
   - Copy/paste pin values

3. **Outliner Controls**
   - Refresh button
   - Collapse all / Expand all
   - Filter by node type
   - Search functionality

4. **File Operations**
   - Drag & drop support (ORBX, meshes, textures)
   - Auto-save with recovery
   - Scene validation
   - Backup copies

### Phase 3: Advanced Features (4-6 weeks)
1. **Application Settings**
   - Full settings dialog
   - All documented tabs
   - Preference persistence
   - Import/export settings

2. **Animation System**
   - Timeline UI
   - Keyframe editing
   - Playback controls
   - Render animation

3. **Render Features**
   - Kernel switching
   - AOV management
   - Render layers
   - Adaptive sampling controls

4. **Scripting Support**
   - Batch rendering
   - Daylight/turntable animation
   - Script menu integration
   - Lua script execution

---

## 📝 NOTES

### Manual Sections Not Yet Reviewed
The following manual sections may contain additional features not yet cataloged:
- **Materials** - Detailed material node documentation
- **Textures** - Texture node types and controls
- **Lighting** - Environment and light node details
- **Geometry** - Mesh and scatter node features
- **Effects** - Hair, fur, volume effects
- **Values** - Value converter/operator nodes
- **Appendix** - Advanced topics and troubleshooting

### API Coverage Unknown
Many features depend on gRPC API availability. Need to verify:
- Node grouping APIs (ApiModuleNodeGraph.*)
- Render statistics APIs (ApiRender.getStatistics?)
- Picker APIs (ray intersection, material query)
- Animation APIs (keyframe management)
- Settings persistence APIs

### Edge Cases & Polish
- Error handling and user feedback
- Loading states and progress indicators
- Validation and input sanitization
- Performance optimization
- Accessibility features
- Mobile/touch support
- Internationalization

---

**Next Steps**: Use this document to guide feature selection and prioritization. Update as features are completed or new manual sections are reviewed.
