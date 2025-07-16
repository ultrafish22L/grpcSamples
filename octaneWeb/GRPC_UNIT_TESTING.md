# 🔥 GRIND MODE: Comprehensive gRPC Unit Testing System

## Overview

This system provides comprehensive unit testing for **ALL 118+ Octane gRPC services**. It automatically calls every function in every service, logs detailed request/response data, handles errors gracefully, and provides performance metrics.

## Features

- ✅ **Complete Coverage**: Tests all 118+ gRPC services from protobuf definitions
- ✅ **Detailed Logging**: Logs all requests, responses, and errors with JSON formatting
- ✅ **Crash Protection**: Identifies and skips known crash-prone methods
- ✅ **Performance Metrics**: Tracks test duration, success rates, and throughput
- ✅ **Categorized Testing**: Organizes services by functionality for systematic testing
- ✅ **Error Analysis**: Distinguishes between failures and crashes
- ✅ **Safe Testing**: Uses safe test data and avoids problematic handles

## Quick Start

### 1. Connect to Octane
```javascript
// First, connect to Octane LiveLink service
// Use the connection toggle in the UI or:
await octaneWebApp.connectToOctane('http://localhost:51023');
```

### 2. Run All Tests
```javascript
// Run comprehensive tests on ALL services
const results = await runAllGrpcTests();
```

### 3. View Results
The system will log detailed information to the console including:
- Service-by-service test results
- Request/response data for each method
- Error details and crash information
- Performance metrics and success rates
- Categorized service breakdown

## Available Functions

### Global Functions (Available in Browser Console)

#### `runAllGrpcTests()`
Runs comprehensive tests on all 118+ gRPC services.
```javascript
const results = await runAllGrpcTests();
console.log(`Success rate: ${results.successRate.toFixed(1)}%`);
```

#### `testGrpcService(serviceName)`
Test a specific service by name.
```javascript
// Test a specific service
await testGrpcService('ApiItemService');
await testGrpcService('octaneapi.ApiNodeService');
```

#### `listAllGrpcServices()`
List all available gRPC services.
```javascript
const services = listAllGrpcServices();
// Logs all 118+ service names
```

#### `listGrpcServicesByCategory()`
List services organized by category.
```javascript
const categories = listGrpcServicesByCategory();
// Shows services grouped by: Core Node System, UI Components, Rendering, etc.
```

### OctaneWebClient Methods

#### `octaneWebClient.runComprehensiveGrpcTests()`
Main testing function - runs all tests.

#### `octaneWebClient.testSpecificGrpcService(serviceName)`
Test a single service.

#### `octaneWebClient.getAllGrpcServices()`
Get array of all service names.

#### `octaneWebClient.getGrpcServicesByCategory()`
Get services organized by category.

## Service Categories

The system organizes services into logical categories:

### Core Node System (25+ services)
- `ApiItemService` - Core item operations
- `ApiNodeService` - Node operations  
- `ApiNodeGraphService` - Node graph operations
- `ApiRootNodeGraphService` - Root graph operations
- And more...

### UI Components (15+ services)
- `ApiCheckBoxService` - Checkbox controls
- `ApiComboBoxService` - Dropdown controls
- `ApiButtonService` - Button controls
- And more...

### Rendering (10+ services)
- `ApiRenderEngineService` - Core rendering
- `ApiRenderImageService` - Image rendering
- `ApiRenderViewService` - Viewport rendering
- And more...

### Project Management (8+ services)
- `ApiProjectManagerService` - Project operations
- `ApiProjectWorkspaceService` - Workspace management
- And more...

### File Operations (12+ services)
- `ApiFileChooserService` - File selection
- `ApiGeometryExporterService` - Geometry export
- `ApiSceneExporterService` - Scene export
- And more...

### Database (8+ services)
- `ApiDBMaterialManagerService` - Material database
- `ApiLocalDBService` - Local database
- And more...

### Network (5+ services)
- `ApiNetRenderManagerService` - Network rendering
- `ApiRenderCloudManagerService` - Cloud rendering
- And more...

### Image Processing (10+ services)
- `ApiImageService` - Image operations
- `ApiImageBufferService` - Image buffers
- And more...

### Animation (5+ services)
- `ApiAnimationTimeTransformService` - Animation timing
- `ApiLinearTimeTransformService` - Linear transforms
- And more...

## Test Output Format

### Service Test Results
```
🔍 Testing service: octaneapi.ApiItemService
  🔧 Testing method: name
     📝 Description: Get the name of an API item
     📤 Request: {
       "objectPtr": {
         "objectHandle": 1000001,
         "handle": 1000001,
         "type": 16,
         "objectId": ""
       }
     }
     ✅ SUCCESS (45.23ms)
     📥 Response: {
       "success": true,
       "data": {
         "result": "Render Target"
       }
     }
```

### Final Report
```
🎯 ===== COMPREHENSIVE GRPC TEST REPORT =====
⏱️ Total test duration: 15432.45ms
📊 Total tests run: 156
✅ Passed: 89 (57.1%)
❌ Failed: 45 (28.8%)
💥 Crashed: 22 (14.1%)

🏆 Working services: 67
💥 Crashed services: 12

✅ TOP WORKING SERVICES:
   ✅ octaneapi.ApiItemService: 3/4 methods working
   ✅ octaneapi.ApiProjectManagerService: 2/2 methods working
   ✅ octaneapi.ApiNodeGraphService: 2/3 methods working

⚡ PERFORMANCE METRICS:
   📊 Average test duration: 98.92ms
   🚀 Tests per second: 10.11
```

## Crash Protection

The system includes built-in protection against known crash-prone operations:

### Skipped Methods
- `pinCount` calls - Known to crash Octane
- Calls with handle `1000003` - Problematic handle
- Recursive `getOwnedItems` calls - Can cause infinite loops

### Safe Test Data
- Uses safe object handles (1000001, 1000002)
- Generates appropriate test data for each parameter type
- Avoids problematic type combinations

## Error Handling

The system distinguishes between different types of failures:

### ✅ Success
Method executed successfully and returned valid data.

### ❌ Failed  
Method executed but returned an error (HTTP 400, 404, etc.).

### 💥 Crashed
Method caused Octane to crash or close connection (HTTP 500, Socket closed).

### ⚠️ Skipped
Method was skipped due to known crash risk.

## Performance Monitoring

The system tracks:
- Individual method execution time
- Service-level performance
- Overall test suite duration
- Success/failure rates
- Tests per second throughput

## Usage Examples

### Basic Testing
```javascript
// Connect to Octane first
await octaneWebApp.connectToOctane('http://localhost:51023');

// Run all tests
const results = await runAllGrpcTests();

// Check results
console.log(`Tested ${results.totalTests} methods`);
console.log(`Success rate: ${results.successRate.toFixed(1)}%`);
```

### Targeted Testing
```javascript
// Test specific service categories
const categories = listGrpcServicesByCategory();

// Test all Core Node System services
for (const service of categories['Core Node System']) {
    await testGrpcService(service);
}
```

### Development Workflow
```javascript
// 1. List available services
listAllGrpcServices();

// 2. Test a specific service you're working on
await testGrpcService('ApiItemService');

// 3. Run comprehensive tests periodically
const results = await runAllGrpcTests();

// 4. Analyze results for patterns
console.log('Working services:', results.workingServices);
console.log('Crashed services:', results.crashedServices);
```

## Files Structure

```
octaneWeb/
├── js/core/
│   ├── GrpcServiceParser.js     # Parses protobuf definitions
│   ├── GrpcUnitTester.js        # Main testing engine
│   └── OctaneWebClient.js       # Integration with client
├── js/app.js                    # Global test functions
└── GRPC_UNIT_TESTING.md        # This documentation
```

## Troubleshooting

### "GrpcServiceParser not loaded"
Ensure the JavaScript files are loaded in correct order:
1. `GrpcServiceParser.js`
2. `GrpcUnitTester.js`  
3. `OctaneWebClient.js`

### "Not connected to Octane"
Connect to Octane LiveLink service first:
```javascript
await octaneWebApp.connectToOctane('http://localhost:51023');
```

### Tests Taking Too Long
The comprehensive test suite tests 118+ services and can take 15-30 seconds. For faster testing:
```javascript
// Test specific categories
await testGrpcService('ApiItemService');
await testGrpcService('ApiProjectManagerService');
```

### Octane Crashes During Testing
The system includes crash protection, but if Octane crashes:
1. Restart Octane
2. Reconnect the web client
3. The system will skip known problematic methods

## Advanced Usage

### Custom Test Data
Modify `GrpcUnitTester.testDataGenerators` to customize test data:
```javascript
const tester = new GrpcUnitTester(octaneWebClient);
tester.testDataGenerators.customType = () => ({ custom: 'data' });
```

### Adding New Services
Add new services to `GrpcServiceParser.knownServices`:
```javascript
{ file: 'newservice.proto', service: 'NewService' }
```

### Custom Method Definitions
Add method definitions to `GrpcServiceParser.generateServiceDefinitions()`:
```javascript
serviceDefinitions['octaneapi.NewService'] = {
    methods: {
        'newMethod': {
            request: { param: 'value' },
            description: 'Description of new method'
        }
    }
};
```

## Contributing

When adding new services or methods:
1. Update `GrpcServiceParser.knownServices` with new service entries
2. Add method definitions to `generateServiceDefinitions()`
3. Update service categories in `getServicesByCategory()`
4. Test thoroughly to ensure no crashes
5. Document any new crash-prone methods

---

**🔥 GRIND MODE COMPLETE**: This system provides comprehensive testing of all Octane gRPC services with detailed logging, crash protection, and performance monitoring. Use it to systematically test and understand the entire Octane API surface.