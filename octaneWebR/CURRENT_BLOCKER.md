# Current Technical Blocker

**Date**: 2025-01-20  
**Status**: 🔴 BLOCKED - Server hangs on startup

---

## Issue Summary

The Vite dev server hangs completely after startup when attempting to register Octane gRPC callbacks during initialization. The server reports "ready" but all HTTP requests timeout (including health checks and static file serving).

## Symptoms

1. Server starts successfully and logs show:
   - ✅ Connected to Octane at host.docker.internal:51022
   - ✅ Callback registered with Octane
   - ✅ Callback streaming active
   - ✅ Vite ready

2. But then:
   - ❌ All HTTP requests timeout (5+ seconds)
   - ❌ Health endpoint `/api/health` unresponsive
   - ❌ Static file serving unresponsive
   - ❌ gRPC proxy endpoints unresponsive

## Root Cause Hypothesis

The callback streaming connection (`streamCallbackService.callbackChannel()`) established during server initialization appears to block the Node.js event loop, preventing the Vite HTTP server from processing incoming requests.

**Affected Code**: `vite-plugin-octane-grpc.ts` lines 265-372
- `registerOctaneCallbacks()` - Registers callback with Octane
- `startCallbackStreaming()` - Opens gRPC stream that may be blocking

## Reproduction Steps

1. Ensure Octane SE is running (host.docker.internal:51022)
2. Start dev server: `npm run dev`
3. Wait for "ready" message
4. Try to access any endpoint: `curl http://localhost:43929/api/health`
5. Result: Request hangs indefinitely

## Attempted Solutions

1. ✅ Restarted Octane - No effect
2. ✅ Killed zombie processes - No effect
3. ✅ Temporarily disabled callback registration - **Server then works**

## Next Steps

1. **Investigate callback stream blocking issue**:
   - Review gRPC stream event handlers
   - Check if stream callbacks are synchronous/blocking
   - Consider moving callback registration to lazy initialization (after first client connection)

2. **Alternative approaches**:
   - Register callbacks on-demand instead of at startup
   - Use polling instead of streaming for callbacks
   - Move callback handling to separate process/worker thread

3. **Required for icon extraction task**:
   - Need stable server to implement `ApiInfo.nodeInfo()` endpoint
   - Must map NT_/GT_ enum IDs to display names for icon extraction
   - Cannot proceed until server stability restored

## Task Context

**Original Goal**: Extract all 755+ Octane node type icons as PNG files, using NT_* enum IDs from `octaneids_pb2`. Required endpoint to map enum IDs to friendly display names using `ApiInfo.nodeInfo()`.

**Blocked By**: Cannot make any gRPC calls until server HTTP layer is responsive.

---

## For Future Reference

When debugging similar issues:
1. Test basic server responsiveness first (curl health endpoint)
2. Check if Octane is responsive before assuming server issue
3. Disable complex initialization code to isolate root cause
4. Work methodically - don't panic and revert prematurely
5. Document findings before cleanup
