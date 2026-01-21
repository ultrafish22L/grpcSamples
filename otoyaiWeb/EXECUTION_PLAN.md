# AI Endpoint Execution System - Implementation Plan

**Status:** 🔄 In Progress  
**Last Updated:** 2025-01-21

---

## 📋 Overview

Complete implementation of the AI endpoint execution system to allow users to run AI models through the node graph interface.

---

## ✅ Completed Work

### 1. Parameter Packaging System
**File:** `client/src/utils/parameterPackager.ts`

- ✅ `packageParameters()` - Main packaging function
- ✅ Support for all input types:
  - Text (string conversion)
  - Integer (validation with min/max)
  - Float (validation with min/max)
  - Boolean (flexible parsing)
  - Select/Enum (option validation)
  - Image (URL, File, Blob, base64)
  - Video (URL, File, Blob, base64)
  - Audio (URL, File, Blob, base64)
- ✅ `validatePackagedParameters()` - Schema validation
- ✅ `resolveConnectedParameters()` - Merge node params with connected values
- ✅ File/Blob to base64 conversion
- ✅ Error handling and logging

### 2. API Service Methods
**File:** `client/src/services/api.ts`

- ✅ `ExecutionRequest` interface
- ✅ `ExecutionResponse` interface  
- ✅ `executeEndpoint()` method with:
  - 2-minute timeout for long operations
  - Request/response logging
  - Error handling

### 3. Server Proxy Route
**File:** `server/src/index.ts`

- ✅ `POST /otoy-api/execute` endpoint
- ✅ Request validation (endpoint_id required)
- ✅ Dynamic URL construction: `https://play.otoy.ai/api/{endpoint_id}`
- ✅ 2-minute timeout
- ✅ Error response handling:
  - API errors (4xx/5xx)
  - Network timeouts (504)
  - Request setup errors (500)
- ✅ 50MB JSON limit for base64 media
- ✅ Axios import added

### 4. AIEndpointNode Execution Logic
**File:** `client/src/components/Nodes/AIEndpointNode.tsx`

- ✅ `handleExecute()` callback
- ✅ `getConnectedValues()` - Extract values from connected nodes
- ✅ Execution status state: `idle | executing | completed | error`
- ✅ Status UI indicators:
  - ▶ Play button (idle)
  - ⟳ Spinning icon (executing)
  - ✓ Check mark (completed)
  - ✕ X mark (error)
- ✅ Button disable during execution
- ✅ Auto-reset to idle after 2-3 seconds
- ✅ Result storage in node data
- ✅ Error message storage

---

## 🐛 Current Issues

### 1. TypeScript Error (BLOCKING)
**Location:** `AIEndpointNode.tsx:73`

```typescript
const item = sourceNode.data.items?.find((i: any) => i.id === itemId);
//                             ^^^^
// Error: Property 'find' does not exist on type '{}'
```

**Cause:** `sourceNode.data` is typed as `Record<string, unknown>` which doesn't have `.find()`

**Solution:** Add type guards to check node type before accessing properties

```typescript
// Type guard approach
if (sourceNode.type === 'image' || sourceNode.type === 'video') {
  const mediaData = sourceNode.data as ImageNodeData | VideoNodeData;
  const item = mediaData.items?.find((i) => i.id === itemId);
  // ...
}
```

### 2. Parameter Collection Type Safety
**Location:** `AIEndpointNode.tsx:54-87` (`getConnectedValues`)

**Issue:** Accessing properties on `sourceNode.data` without type checking

**Solution:** Use discriminated union with node type checks

---

## 🔄 Remaining Tasks

### Phase 1: Fix Build Errors (HIGH PRIORITY)

- [ ] **Task 1.1:** Fix TypeScript error in `getConnectedValues()`
  - Add type guards for each node type
  - Use discriminated union based on `sourceNode.type`
  - Test compilation with `npm run build`

### Phase 2: Result Handling & Display

- [ ] **Task 2.1:** Parse API response formats
  - Research OTOY API response structure
  - Handle URL responses (most common for images/videos)
  - Handle base64 data URLs
  - Handle JSON/text responses
  - Handle error responses

- [ ] **Task 2.2:** Update preview display
  - Show image results in preview area (already partially done)
  - Show video results with `<video>` element
  - Show text/JSON results
  - Show error messages in red
  - Add loading skeleton during execution

- [ ] **Task 2.3:** Output value propagation
  - Ensure results are accessible to downstream nodes
  - Test connection from AI node output to another AI node input
  - Verify media results can connect to Image/Video nodes

### Phase 3: Testing & Validation

- [ ] **Task 3.1:** Unit test parameter packager
  - Test each type conversion
  - Test validation (min/max, required, options)
  - Test error cases

- [ ] **Task 3.2:** Integration test with simple endpoint
  - Choose a fast, reliable endpoint (e.g., FLUX text-to-image)
  - Create test graph:
    - Text node → AI node
    - Verify execution
    - Verify result display
  - Document test results

- [ ] **Task 3.3:** Test complex workflows
  - Image → AI (image-to-image)
  - Text + Image → AI (style transfer)
  - AI → AI (chained generation)
  - Multiple inputs test

### Phase 4: UX Improvements

- [ ] **Task 4.1:** Better error messages
  - User-friendly error text
  - Show validation errors before execution
  - Network error guidance

- [ ] **Task 4.2:** Execution feedback
  - Progress indicator (if API supports progress)
  - Estimated time remaining
  - Cancel button for long operations

- [ ] **Task 4.3:** Result actions
  - Download button for generated media
  - Copy URL to clipboard
  - Open in new tab
  - Delete result

### Phase 5: Advanced Features

- [ ] **Task 5.1:** Result caching
  - Cache results by hash of parameters
  - Avoid re-running identical requests
  - Show cached indicator

- [ ] **Task 5.2:** Batch execution
  - Execute all connected nodes in order
  - Dependency resolution
  - Parallel execution where possible

- [ ] **Task 5.3:** Execution history
  - Log all executions
  - Show history in inspector
  - Replay previous executions

---

## 🎯 Next Immediate Steps

1. **Fix TypeScript error** (15 minutes)
   - Update `getConnectedValues()` with type guards
   - Test build passes

2. **Test basic execution** (30 minutes)
   - Start dev servers
   - Create simple text → AI endpoint graph
   - Execute and verify response handling
   - Debug any API issues

3. **Improve result display** (30 minutes)
   - Add proper preview for image results
   - Add error display in node
   - Test with different result types

4. **Document execution flow** (15 minutes)
   - Update ARCHITECTURE.md with execution system
   - Add example execution flow diagram
   - Document API response formats

---

## 📊 Implementation Status

| Component | Status | Confidence |
|-----------|--------|------------|
| Parameter Packager | ✅ Complete | 95% |
| API Service | ✅ Complete | 90% |
| Server Proxy | ✅ Complete | 95% |
| Parameter Collection | 🔄 Needs Fix | 60% |
| Execution Logic | ✅ Complete | 85% |
| UI Status Display | ✅ Complete | 90% |
| Result Handling | ⏳ Not Started | 40% |
| Error Handling | 🔄 Partial | 70% |
| Testing | ⏳ Not Started | 10% |

**Overall Completion:** ~70%

---

## 🔬 Testing Plan

### Test Case 1: Simple Text-to-Image
**Endpoint:** `fal-ai/flux-1/dev`

**Graph:**
```
[Text Node: "a cat"] → [AI Node: FLUX.1 Dev]
```

**Expected:**
1. Text node provides prompt parameter
2. AI node packages parameters correctly
3. Server proxies request to play.otoy.ai
4. API returns image URL
5. Result displayed in preview
6. Output pin fills (green)

### Test Case 2: Image-to-Image
**Endpoint:** Any style transfer model

**Graph:**
```
[Image Node: uploaded image] → [AI Node: Style Transfer]
[Text Node: "oil painting"] → [AI Node: Style Transfer (prompt)]
```

**Expected:**
1. Image node provides image parameter (base64 or URL)
2. Text node provides prompt parameter
3. Both parameters collected correctly
4. API returns styled image
5. Result displayed

### Test Case 3: Error Handling
**Setup:** Invalid parameters or missing required params

**Expected:**
1. Validation error caught before API call
2. Error status shown (✕ icon)
3. Error message logged
4. Error displayed in inspector

---

## 🔍 API Response Format Research

Based on OTOY.AI documentation and common patterns:

### Expected Response Format
```json
{
  "success": true,
  "data": {
    "images": [
      {
        "url": "https://storage.googleapis.com/...",
        "width": 1024,
        "height": 1024
      }
    ],
    "seed": 12345,
    "prompt": "..."
  },
  "request_id": "req_abc123",
  "timings": {
    "inference": 2.5
  }
}
```

### Response Variations by Endpoint Type

**Text-to-Image:**
- `data.images[]` - Array of image URLs
- `data.image` - Single image URL

**Image-to-Video:**
- `data.video` - Video URL
- `data.video.url` - Nested URL

**LLM (Text Generation):**
- `data.text` - Generated text
- `data.choices[0].message.content` - OpenAI format

**Audio:**
- `data.audio_url` - Audio file URL
- `data.audio` - Base64 audio

---

## 🚀 Deployment Checklist

Before considering this feature complete:

- [ ] Build passes without errors
- [ ] At least 3 different endpoint types tested
- [ ] Error handling tested
- [ ] Documentation updated (ARCHITECTURE.md, FEATURES.md)
- [ ] User-facing error messages are clear
- [ ] Logging captures enough detail for debugging
- [ ] Performance acceptable (< 5s for most operations)
- [ ] No memory leaks in repeated executions

---

## 📝 Notes

### Known Limitations
1. **No progress tracking** - OTOY API doesn't provide progress events
2. **No cancellation** - Once sent, requests can't be cancelled
3. **Rate limiting** - Need to handle API rate limits gracefully
4. **Large files** - Base64 encoding inflates file sizes by ~33%

### Future Considerations
- WebSocket support for real-time progress
- Queue system for batch operations
- Cost estimation before execution
- Result export/download functionality

---

## 🔗 Related Files

**Core Implementation:**
- `client/src/components/Nodes/AIEndpointNode.tsx` - Main execution logic
- `client/src/utils/parameterPackager.ts` - Parameter preparation
- `client/src/services/api.ts` - API client
- `server/src/index.ts` - Proxy server

**Supporting Files:**
- `client/src/utils/endpointSchema.ts` - Schema inference
- `client/src/utils/connectionValidator.ts` - Type validation
- `client/src/services/logger.ts` - Debugging

**Documentation:**
- `README.md` - Project overview
- `ARCHITECTURE.md` - Technical docs
- `FEATURES.md` - Feature list

---

## 📞 Questions to Resolve

1. **API Authentication:** Does play.otoy.ai require API keys? (Check with test call)
2. **Response Format:** Is response structure consistent? (Test multiple endpoints)
3. **Rate Limits:** What are the limits? How to handle them?
4. **File Size Limits:** Max upload size for images/videos?
5. **Cost Display:** Show token cost before/after execution?
