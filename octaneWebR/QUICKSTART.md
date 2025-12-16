# OctaneWebR Quick Start Guide

**Get up and running in 60 seconds.**

---

## 🚀 Launch (Single Command)

### Linux/Mac
```bash
cd /workspace/grpcSamples/octaneWebR
./start.sh
```

### Windows
```cmd
cd C:\path\to\grpcSamples\octaneWebR
start.bat
```

### Manual
```bash
npm run dev
```

---

## 📍 Access Points

Once servers start:

- **Frontend**: http://localhost:5173
- **Backend**: http://localhost:51024
- **WebSocket**: ws://localhost:51024/api/callbacks

---

## ✅ System Check

### 1. Check Servers Running
```bash
# Should show Vite and Node.js processes
ps aux | grep -E "vite|ts-node"
```

### 2. Check Frontend
```bash
curl http://localhost:5173/
# Should return HTML with "OctaneWebR"
```

### 3. Check Backend
```bash
curl http://localhost:51024/api/health
# Should return JSON: {"status":"unhealthy"...} (unhealthy is OK if no Octane)
```

---

## 🔧 Troubleshooting

### Port Already in Use

```bash
# Find and kill process using port
lsof -ti:5173 | xargs kill -9   # Frontend
lsof -ti:51024 | xargs kill -9  # Backend
```

### Dependencies Missing

```bash
npm install
```

### TypeScript Errors

```bash
# Check TypeScript compilation
npx tsc --noEmit
```

---

## 🎯 Next Steps

1. **Without Octane**: App will show "Disconnected" status (expected)
2. **With Octane**: 
   - Start Octane
   - Enable LiveLink (Help → LiveLink menu)
   - Refresh browser
   - Should show "Connected" with green LED

---

## 📚 Full Documentation

- **README.md** - Complete project documentation
- **VALIDATION.md** - Testing and validation guide
- **PORT_COMPLETE.md** - Port status and technical details

---

## 🆘 Common Issues

### "Cannot find module"
```bash
rm -rf node_modules package-lock.json
npm install
```

### "Address already in use"
Kill all Node.js processes:
```bash
pkill -f "node|vite|ts-node"
npm run dev
```

### Vite fails to start
```bash
# Clear Vite cache
rm -rf client/.vite
npm run client:dev
```

---

## 🎉 Success Indicators

✅ **Console shows**:
```
[client:dev]   VITE v5.4.21  ready in XXX ms
[server:dev] ✅ OctaneWebR Server Started
```

✅ **Browser shows**: Dark OTOY-themed UI with connection status

✅ **No errors** in browser console (F12)

---

**Ready to go? Run `./start.sh` and open http://localhost:5173**
