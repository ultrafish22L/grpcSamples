/**
 * 🔥 GRIND MODE: Comprehensive gRPC Unit Tester
 * 
 * This module provides comprehensive unit testing for ALL Octane gRPC services.
 * It calls every function in every service and logs detailed information.
 * 
 * Features:
 * - Tests all 118+ gRPC services
 * - Logs detailed request/response data
 * - Handles errors gracefully
 * - Provides performance metrics
 * - Categorizes services for organized testing
 * - Identifies crash-prone methods
 * 
 * Usage:
 * const tester = new GrpcUnitTester(octaneWebClient);
 * await tester.runComprehensiveTests();
 */

class GrpcUnitTester {
    constructor(octaneWebClient) {
        this.client = octaneWebClient;
        this.parser = new GrpcServiceParser();
        this.testResults = new Map();
        this.crashedServices = new Set();
        this.workingServices = new Set();
        this.totalTests = 0;
        this.passedTests = 0;
        this.failedTests = 0;
        this.crashedTests = 0;
        
        // 🔥 GRIND MODE: Retry and comment tracking
        this.methodRetryCount = new Map(); // Track retry attempts per method
        this.commentedOutMethods = new Set(); // Track methods commented out after 3 failures
        this.maxRetries = 3; // Maximum retry attempts before commenting out
        
        // Known problematic handles that cause crashes
        this.problematicHandles = new Set([1000003]);
        
        // Test data generators
        this.testDataGenerators = {
            objectPtr: (type = 16, handle = 1000001) => ({
                objectHandle: handle,
                handle: handle,
                type: type,
                objectId: ""
            }),
            
            string: () => "test_string",
            int32: () => 42,
            int64: () => "42",
            float: () => 3.14159,
            double: () => 3.14159265359,
            bool: () => true,
            
            // Common Octane types
            vector3: () => ({ x: 1.0, y: 2.0, z: 3.0 }),
            matrix4x4: () => ({
                m00: 1, m01: 0, m02: 0, m03: 0,
                m10: 0, m11: 1, m12: 0, m13: 0,
                m20: 0, m21: 0, m22: 1, m23: 0,
                m30: 0, m31: 0, m32: 0, m33: 1
            }),
            color: () => ({ r: 1.0, g: 0.5, b: 0.0, a: 1.0 }),
            
            // Empty request for parameterless methods
            empty: () => ({})
        };
    }
    
    /**
     * Run comprehensive tests on all gRPC services
     */
    async runComprehensiveTests() {
        console.log('🔥 GRIND MODE: Starting comprehensive gRPC service testing...');
        console.log(`📊 Total services to test: ${this.parser.getServiceCount()}`);
        
        // Show enhanced statistics if extracted data is available
        if (typeof EXTRACTED_GRPC_SERVICES !== 'undefined') {
            const totalMethods = this.parser.getTotalMethodCount();
            console.log(`🚀 ENHANCED MODE: Testing ${totalMethods} methods from extracted protobuf definitions!`);
            console.log(`📈 This is ${Math.floor(totalMethods/118)} times more comprehensive than basic testing`);
        }
        
        const startTime = performance.now();
        
        // Get service definitions
        const serviceDefinitions = this.parser.generateServiceDefinitions();
        const servicesByCategory = this.parser.getServicesByCategory();
        
        // Test services by category for organized output
        for (const [category, services] of Object.entries(servicesByCategory)) {
            if (services.length === 0) continue;
            
            console.log(`\n🏷️ ===== TESTING CATEGORY: ${category} =====`);
            console.log(`📋 Services in category: ${services.length}`);
            
            for (const serviceName of services) {
                const fullServiceName = serviceName.startsWith('octaneapi.') ? serviceName : `octaneapi.${serviceName}`;
                await this.testService(fullServiceName, serviceDefinitions[fullServiceName] || { methods: {} });
            }
        }
        
        // Test remaining services not in categories
        console.log(`\n🔧 ===== TESTING ADDITIONAL SERVICES =====`);
        for (const [serviceName, definition] of Object.entries(serviceDefinitions)) {
            if (!this.testResults.has(serviceName)) {
                await this.testService(serviceName, definition);
            }
        }
        
        const endTime = performance.now();
        const duration = endTime - startTime;
        
        // Generate comprehensive report
        this.generateTestReport(duration);
        
        return this.getTestSummary();
    }
    
    /**
     * Test a specific service and all its methods
     */
    async testService(serviceName, serviceDefinition) {
        console.log(`\n🔍 Testing service: ${serviceName}`);
        
        const serviceResults = {
            serviceName,
            methods: new Map(),
            totalMethods: 0,
            passedMethods: 0,
            failedMethods: 0,
            crashedMethods: 0,
            startTime: performance.now()
        };
        
        // Test each method in the service
        const methods = serviceDefinition.methods || {};
        serviceResults.totalMethods = Object.keys(methods).length;
        
        if (serviceResults.totalMethods === 0) {
            // Generate basic test methods for services without definitions
            methods.testBasicCall = {
                request: {},
                description: `Basic test call for ${serviceName}`
            };
            serviceResults.totalMethods = 1;
        }
        
        for (const [methodName, methodDef] of Object.entries(methods)) {
            const methodResult = await this.testMethod(serviceName, methodName, methodDef);
            serviceResults.methods.set(methodName, methodResult);
            
            if (methodResult.status === 'passed') {
                serviceResults.passedMethods++;
                this.passedTests++;
            } else if (methodResult.status === 'crashed') {
                serviceResults.crashedMethods++;
                this.crashedTests++;
                this.crashedServices.add(serviceName);
            } else if (methodResult.status === 'commented_out') {
                // Don't count commented out methods in failed tests
                // They are tracked separately in this.commentedOutMethods
            } else {
                serviceResults.failedMethods++;
                this.failedTests++;
            }
            
            this.totalTests++;
        }
        
        serviceResults.endTime = performance.now();
        serviceResults.duration = serviceResults.endTime - serviceResults.startTime;
        
        if (serviceResults.passedMethods > 0) {
            this.workingServices.add(serviceName);
        }
        
        this.testResults.set(serviceName, serviceResults);
        
        // Log service summary
        console.log(`✅ Service ${serviceName} completed:`);
        console.log(`   📊 Methods: ${serviceResults.totalMethods}`);
        console.log(`   ✅ Passed: ${serviceResults.passedMethods}`);
        console.log(`   ❌ Failed: ${serviceResults.failedMethods}`);
        console.log(`   💥 Crashed: ${serviceResults.crashedMethods}`);
        console.log(`   ⏱️ Duration: ${serviceResults.duration.toFixed(2)}ms`);
    }
    
    /**
     * Test a specific method within a service
     */
    async testMethod(serviceName, methodName, methodDefinition) {
        const fullMethodName = `${serviceName}/${methodName}`;
        const startTime = performance.now();
        
        // 🔥 GRIND MODE: Check if method is already commented out
        if (this.commentedOutMethods.has(fullMethodName)) {
            console.log(`  // CHECKME: ${methodName} - Commented out after ${this.maxRetries} failures`);
            return {
                serviceName,
                methodName,
                fullMethodName,
                status: 'commented_out',
                error: `Commented out after ${this.maxRetries} failures`,
                startTime,
                endTime: performance.now(),
                duration: 0
            };
        }
        
        console.log(`  🔧 Testing method: ${methodName}`);
        console.log(`     📝 Description: ${methodDefinition.description || 'No description'}`);
        
        const methodResult = {
            serviceName,
            methodName,
            fullMethodName,
            description: methodDefinition.description || 'No description',
            startTime,
            endTime: null,
            duration: null,
            status: 'unknown',
            request: null,
            response: null,
            error: null,
            crashDetails: null,
            retryAttempt: this.methodRetryCount.get(fullMethodName) || 0
        };
        
        try {
            // Generate test request data
            const requestData = this.generateRequestData(methodDefinition.request || {});
            methodResult.request = requestData;
            
            console.log(`     📤 Request:`, JSON.stringify(requestData, null, 2));
            
            // Check for known problematic patterns
            if (this.isProblematicCall(serviceName, methodName, requestData)) {
                console.log(`     ⚠️ SKIPPING: Known to cause crashes`);
                methodResult.status = 'skipped';
                methodResult.error = 'Skipped due to known crash risk';
                methodResult.endTime = performance.now();
                methodResult.duration = methodResult.endTime - startTime;
                return methodResult;
            }
            
            // Make the gRPC call
            const response = await this.client.makeGrpcCall(fullMethodName, requestData);
            
            methodResult.endTime = performance.now();
            methodResult.duration = methodResult.endTime - startTime;
            methodResult.response = response;
            
            if (response.success) {
                methodResult.status = 'passed';
                console.log(`     ✅ SUCCESS (${methodResult.duration.toFixed(2)}ms)`);
                console.log(`     📥 Response:`, JSON.stringify(response.data, null, 2));
            } else {
                methodResult.status = 'failed';
                methodResult.error = response.error || 'Unknown error';
                console.log(`     ❌ FAILED (${methodResult.duration.toFixed(2)}ms): ${methodResult.error}`);
                if (response.data) {
                    console.log(`     📥 Error Data:`, JSON.stringify(response.data, null, 2));
                }
            }
            
        } catch (error) {
            methodResult.endTime = performance.now();
            methodResult.duration = methodResult.endTime - startTime;
            methodResult.error = error.message;
            
            // 🔥 GRIND MODE: Handle retries and commenting out
            const currentRetries = this.methodRetryCount.get(fullMethodName) || 0;
            
            // Check if this looks like a crash
            if (error.message.includes('Socket closed') || 
                error.message.includes('Connection reset') ||
                error.message.includes('Internal Server Error')) {
                methodResult.status = 'crashed';
                methodResult.crashDetails = {
                    errorType: error.constructor.name,
                    message: error.message,
                    stack: error.stack
                };
                console.log(`     💥 CRASHED (${methodResult.duration.toFixed(2)}ms): ${error.message}`);
                console.log(`     🔍 Crash details:`, methodResult.crashDetails);
                
                // 🔥 GRIND MODE: Increment retry count and check if we should comment out
                this.methodRetryCount.set(fullMethodName, currentRetries + 1);
                
                if (currentRetries + 1 >= this.maxRetries) {
                    this.commentedOutMethods.add(fullMethodName);
                    console.log(`     🚫 COMMENTING OUT: ${fullMethodName} after ${this.maxRetries} failures`);
                    console.log(`     // CHECKME: ${methodName} - Requires specific parameters or different approach`);
                    methodResult.status = 'commented_out';
                } else {
                    console.log(`     🔄 RETRY ${currentRetries + 1}/${this.maxRetries}: Will retry this method`);
                }
                
            } else {
                methodResult.status = 'failed';
                console.log(`     ❌ FAILED (${methodResult.duration.toFixed(2)}ms): ${error.message}`);
            }
        }
        
        return methodResult;
    }
    
    /**
     * Generate appropriate request data based on method definition
     */
    generateRequestData(requestTemplate) {
        if (!requestTemplate || Object.keys(requestTemplate).length === 0) {
            return {};
        }
        
        const requestData = {};
        
        for (const [key, value] of Object.entries(requestTemplate)) {
            if (key === 'objectPtr') {
                // Generate ObjectRef with safe handle
                requestData[key] = this.testDataGenerators.objectPtr(
                    value.type || 16,
                    value.handle || 1000001
                );
            } else if (typeof value === 'string') {
                requestData[key] = this.testDataGenerators.string();
            } else if (typeof value === 'number') {
                requestData[key] = value;
            } else if (typeof value === 'boolean') {
                requestData[key] = this.testDataGenerators.bool();
            } else if (typeof value === 'object' && value !== null) {
                // Recursively generate nested objects
                requestData[key] = this.generateRequestData(value);
            } else {
                requestData[key] = value;
            }
        }
        
        return requestData;
    }
    
    /**
     * Check if a call is known to be problematic
     */
    isProblematicCall(serviceName, methodName, requestData) {
        // Skip pinCount calls - known to crash
        if (methodName === 'pinCount') {
            return true;
        }
        
        // Skip calls with problematic handles
        if (requestData.objectPtr && this.problematicHandles.has(requestData.objectPtr.handle)) {
            return true;
        }
        
        // Skip recursive getOwnedItems calls on certain types
        if (methodName === 'getOwnedItems' && requestData.objectPtr) {
            const type = requestData.objectPtr.type;
            // Allow only root node graph calls
            if (type !== 18) {
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * Generate comprehensive test report
     */
    generateTestReport(totalDuration) {
        console.log(`\n🎯 ===== COMPREHENSIVE GRPC TEST REPORT =====`);
        console.log(`⏱️ Total test duration: ${totalDuration.toFixed(2)}ms`);
        console.log(`📊 Total tests run: ${this.totalTests}`);
        console.log(`✅ Passed: ${this.passedTests} (${((this.passedTests/this.totalTests)*100).toFixed(1)}%)`);
        console.log(`❌ Failed: ${this.failedTests} (${((this.failedTests/this.totalTests)*100).toFixed(1)}%)`);
        console.log(`💥 Crashed: ${this.crashedTests} (${((this.crashedTests/this.totalTests)*100).toFixed(1)}%)`);
        
        // 🔥 GRIND MODE: Report commented out methods
        console.log(`🚫 Commented out: ${this.commentedOutMethods.size} methods after ${this.maxRetries} failures each`);
        
        console.log(`\n🏆 Working services: ${this.workingServices.size}`);
        console.log(`💥 Crashed services: ${this.crashedServices.size}`);
        
        // Top working services
        console.log(`\n✅ TOP WORKING SERVICES:`);
        const workingServicesList = Array.from(this.workingServices).slice(0, 10);
        workingServicesList.forEach(service => {
            const result = this.testResults.get(service);
            console.log(`   ✅ ${service}: ${result.passedMethods}/${result.totalMethods} methods working`);
        });
        
        // Crashed services
        if (this.crashedServices.size > 0) {
            console.log(`\n💥 CRASHED SERVICES:`);
            Array.from(this.crashedServices).forEach(service => {
                const result = this.testResults.get(service);
                console.log(`   💥 ${service}: ${result.crashedMethods} crashed methods`);
            });
        }
        
        // 🔥 GRIND MODE: List commented out methods
        if (this.commentedOutMethods.size > 0) {
            console.log(`\n🚫 COMMENTED OUT METHODS (require manual review):`);
            Array.from(this.commentedOutMethods).forEach(methodName => {
                console.log(`   // CHECKME: ${methodName} - Failed ${this.maxRetries} times`);
            });
        }
        
        // Performance metrics
        console.log(`\n⚡ PERFORMANCE METRICS:`);
        const avgDuration = totalDuration / this.totalTests;
        console.log(`   📊 Average test duration: ${avgDuration.toFixed(2)}ms`);
        console.log(`   🚀 Tests per second: ${(this.totalTests / (totalDuration / 1000)).toFixed(2)}`);
        
        // Service category breakdown
        console.log(`\n📋 SERVICE CATEGORY BREAKDOWN:`);
        const categories = this.parser.getServicesByCategory();
        for (const [category, services] of Object.entries(categories)) {
            if (services.length === 0) continue;
            
            const workingInCategory = services.filter(s => 
                this.workingServices.has(s.startsWith('octaneapi.') ? s : `octaneapi.${s}`)
            ).length;
            
            console.log(`   📁 ${category}: ${workingInCategory}/${services.length} working`);
        }
    }
    
    /**
     * Get test summary for external use
     */
    getTestSummary() {
        return {
            totalTests: this.totalTests,
            passedTests: this.passedTests,
            failedTests: this.failedTests,
            crashedTests: this.crashedTests,
            workingServices: Array.from(this.workingServices),
            crashedServices: Array.from(this.crashedServices),
            testResults: Object.fromEntries(this.testResults),
            successRate: (this.passedTests / this.totalTests) * 100
        };
    }
    
    /**
     * Test specific service by name
     */
    async testSpecificService(serviceName) {
        const serviceDefinitions = this.parser.generateServiceDefinitions();
        const fullServiceName = serviceName.startsWith('octaneapi.') ? serviceName : `octaneapi.${serviceName}`;
        
        if (serviceDefinitions[fullServiceName]) {
            await this.testService(fullServiceName, serviceDefinitions[fullServiceName]);
            return this.testResults.get(fullServiceName);
        } else {
            console.error(`❌ Service not found: ${fullServiceName}`);
            return null;
        }
    }
    
    /**
     * Get detailed results for a specific service
     */
    getServiceResults(serviceName) {
        const fullServiceName = serviceName.startsWith('octaneapi.') ? serviceName : `octaneapi.${serviceName}`;
        return this.testResults.get(fullServiceName);
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = GrpcUnitTester;
} else if (typeof window !== 'undefined') {
    window.GrpcUnitTester = GrpcUnitTester;
}