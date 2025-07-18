# 🚀 OctaneWeb Development Guide
## *Simplified workflow for maximum productivity*

**PHILOSOPHY**: Focus on building, not documenting. Ship early, iterate fast.

---

## ⚡ Three-Command Development

```bash
# FOCUS - Lock scope, evidence-based approach
# DEBUG - Systematic problem analysis  
# SHIP - Complete, test, commit, push
```

---

## 🔧 Development Workflow

### **Starting Development**
```bash
cd octaneWeb
python octane_proxy.py &          # Start proxy server
open index.html                   # Open in browser
# Ctrl-D for debug console
```

### **Making Changes**
```bash
# Edit files directly
# Browser auto-refreshes with cache busting
# Check debug console for errors
```

### **Shipping Changes**
```bash
git add . && git commit -m "Brief description" && git push
```

---

## 🐛 Common Issues & Solutions

### **Click Events Not Working**
```javascript
// Use direct event handling, not CSS pointer-events
element.addEventListener('click', (e) => {
    e.stopPropagation();
    // Handle click
}, true);
```

### **gRPC Connection Issues**
```bash
# Check if proxy is running
curl http://localhost:51023/health

# Docker networking issues
export SANDBOX_USE_HOST_NETWORK=true
```

### **Cache Issues**
- Cache busting is automatic via timestamp
- Force refresh: Ctrl+F5
- Debug console shows cache status

---

## 📁 Key Files

```
octaneWeb/
├── index.html              # Main application
├── js/
│   ├── app.js             # Application entry point
│   ├── OctaneWebClient.js # gRPC client
│   ├── SceneOutliner.js   # Scene tree
│   ├── NodeInspector.js   # Property panels
│   └── NodeGraphEditor.js # Visual node editor
├── css/
│   └── octane-theme.css   # Professional styling
└── octane_proxy.py        # HTTP-to-gRPC proxy
```

---

## 🎯 Development Principles

1. **Simplicity First**: Solve problems with the simplest approach
2. **Evidence-Based**: Test changes immediately in browser
3. **Ship Fast**: Commit working changes frequently
4. **Focus**: One problem at a time, no scope creep

---

*"The best code is no code. The second best is simple code."*