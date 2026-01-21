# Quick Reference - New UI Structure

## 🎯 Quick Overview

The UI now has **two bars** instead of one:

```
┌────────┬──────────┬────────────────────────┐
│ Main   │  Node    │                        │
│ Bar    │  Bar     │    Node Graph Area     │
│ (60px) │ (280px)  │                        │
│        │          │                        │
│  📄    │ Utility  │                        │
│  📂    │  📝 Text │                        │
│  💾    │  🖼️ Img  │    (ReactFlow Graph)   │
│        │  🎬 Vid  │                        │
│  ──    │          │                        │
│  ➕    │ AI Models│                        │
│        │  (custom)│                        │
└────────┴──────────┴────────────────────────┘
```

---

## 🎮 Main Bar (Left) - Icon Buttons

| Icon | Function | Action |
|------|----------|--------|
| 📄 | **New Project** | Clear graph, start fresh |
| 📂 | **Load Project** | Open saved project |
| 💾 | **Save Project** | Save current work |
| ──ㅤ | *Separator* | Visual divider |
| ➕ | **Add AI Node** | Open model browser |

---

## 📋 Node Bar (Center) - Draggable Nodes

### Always Visible
- **📝 Text Input** - Add text prompt node
- **🖼️ Image** - Add image input node  
- **🎬 Video** - Add video input node

### AI Models (Customizable)
**Default 8 models shown:**
1. FLUX.1 [Dev]
2. FLUX.1 [Schnell]
3. Stable Diffusion v3
4. Aura Flow
5. FLUX image-to-image
6. Hunyuan Video
7. CogVideoX 5B
8. Whisper Large v3

**Organized by category** (collapsible)

---

## 🖱️ User Actions

### Add AI Model to NodeBar
1. Click **➕** in MainBar
2. Search or browse 1,136 models
3. Click model name
4. Model appears in NodeBar

### Remove Model from NodeBar
1. **Right-click** model in NodeBar
2. Click "Remove from NodeBar"
3. Model disappears (still in + dialog)

### Add Node to Graph
1. Click any node in NodeBar
2. Node appears in graph at random position

### Save Your Work
1. Click **💾** in MainBar
2. Enter project name
3. Everything saved (graph + NodeBar state)

### Load Project
1. Click **📂** in MainBar
2. Select project from list
3. Everything restored

---

## ⌨️ Keyboard Shortcuts

*(None currently - potential future enhancement)*

---

## 💾 What Gets Saved?

### Project Save
- ✅ All nodes in graph
- ✅ All connections (edges)
- ✅ Node positions
- ✅ NodeBar configuration
- ✅ Project name & timestamp

### Auto-Saved (localStorage)
- ✅ NodeBar model list
- ✅ All saved projects
- ✅ Current project reference

---

## 🔄 Workflows

### Common Workflows

**Text-to-Image:**
```
Text Input → FLUX.1 [Dev] → Output
```

**Image-to-Video:**
```
Image Node → Hunyuan Video → Output
```

**Multi-Model Comparison:**
```
          ┌─→ FLUX.1 [Dev]
Text Input ┼─→ SD v3
          └─→ Aura Flow
```

---

## 🎨 Visual Indicators

| Element | Meaning |
|---------|---------|
| **Cyan hover** | Interactive element |
| **✓ Added** badge | Model already in NodeBar |
| **Expanded ▼** | Category open |
| **Collapsed ▶** | Category closed |
| **Context menu** | Right-click options |

---

## 🐛 Troubleshooting

### NodeBar is empty
- **Fix**: Click **➕** to add AI models
- **Or**: Refresh page (defaults will load)

### Can't find a model
- **Fix**: Click **➕** and use search bar
- Try searching by:
  - Model name (e.g., "FLUX")
  - Vendor (e.g., "fal-ai")
  - Category (e.g., "text-to-image")

### Lost my project
- **Fix**: Click **📂** Load Project
- All projects auto-saved to localStorage

### Want fresh start
- **Fix**: Click **📄** New Project
- Confirms before clearing

### Clear localStorage
- Open browser console (F12)
- Run: `localStorage.clear()`
- Refresh page

---

## 📖 More Info

See `UI_RESTRUCTURE_COMPLETE.md` for:
- Complete feature documentation
- Technical implementation details
- Testing procedures
- Developer notes

---

## 🚀 Quick Start

1. **Open**: http://localhost:60023
2. **NodeBar**: Click models to add to graph
3. **Customize**: Click **➕** to add more models
4. **Connect**: Drag between node ports
5. **Save**: Click **💾** when done

**That's it!** 🎉
