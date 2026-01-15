# Quick Start

Get octaneWebR running in 5 minutes.

## Prerequisites

- **Octane Render** with LiveLink support
- **Node.js 18+** (`node --version`)
- Modern browser (Chrome/Firefox/Edge)

## Setup

**1. Start Octane**
```bash
# Launch Octane → Help → LiveLink (enable it)
# Default port: 51022
```

**2. Install octaneWebR**
```bash
git clone https://github.com/ultrafish22L/grpcSamples.git
cd grpcSamples/octaneWebR
npm install
```

**3. Run Dev Server**
```bash
npm run dev
# Opens at http://localhost:43930
```

**4. Verify**
- Open browser console (F12)
- Should see: `✅ Connected to Octane`
- Scene Outliner (left) shows your scene nodes
- Node Graph Editor (bottom) shows node graph

## Quick Test

1. **Create node**: Right-click in graph editor → Materials → Diffuse
2. **Connect pins**: Drag from output to input pin
3. **Edit parameter**: Click node, change value in Node Inspector (right)
4. **Search**: Ctrl+F, type node name
5. **Copy/Paste**: Ctrl+C, Ctrl+V

All changes sync to Octane in real-time.

## Troubleshooting

**Cannot connect to Octane?**
- Verify Octane is running
- Check LiveLink is enabled (Help menu)
- Test port: `nc -zv localhost 51022` (Mac/Linux) or `Test-NetConnection localhost -Port 51022` (Windows)

**npm install fails?**
- Check Node.js version ≥ 18
- Clear cache: `npm cache clean --force && rm -rf node_modules package-lock.json && npm install`

**TypeScript build errors?**
- Check TypeScript version: `npx tsc --version` (should be 5.3+)
- Regenerate protos: `npm run generate:proto`

**Port conflict?**
- Kill process on 43930: `lsof -i :43930` then `kill <PID>`
- Or edit `vite.config.mts` to use different port

## Next Steps

**For Users**: Read [README.md](./README.md) for full feature list  
**For Developers**: Read [WORKFLOW.md](./WORKFLOW.md) and [CODE_REVIEW.md](./CODE_REVIEW.md)

## Resources

- [React 18](https://react.dev/) - UI framework
- [ReactFlow](https://reactflow.dev/) - Node graph
- [Octane SE Manual](https://docs.otoy.com/standaloneSE/) - Feature reference
