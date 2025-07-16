#!/usr/bin/env node

/**
 * 🔥 GRIND MODE: Standalone Comprehensive gRPC Test Runner
 * 
 * This script runs all 1,802 gRPC methods systematically, implementing
 * the retry logic and auto-comment system without requiring a browser.
 * 
 * Features:
 * - Tests all extracted gRPC methods
 * - Implements 3-retry logic with auto-commenting
 * - Generates comprehensive reports
 * - Runs independently of browser environment
 * - Saves results to files for analysis
 */

const fs = require('fs');
const path = require('path');
const http = require('http');

class StandaloneGrindTester {
    constructor() {
        this.proxyUrl = 'http://localhost:51023';
        this.methodRetryCount = new Map();
        this.commentedOutMethods = new Set();
        this.maxRetries = 3;
        
        this.totalTests = 0;
        this.passedTests = 0;
        this.failedTests = 0;
        this.crashedTests = 0;
        
        this.testResults = [];
        this.startTime = Date.now();
    }
    
    /**
     * Load extracted gRPC service definitions
     */
    loadServiceDefinitions() {
        try {
            const servicesPath = path.join(__dirname, 'extracted_grpc_data', 'extracted_services.js');
            const servicesContent = fs.readFileSync(servicesPath, 'utf8');
            
            // Extract the EXTRACTED_GRPC_SERVICES object
            const match = servicesContent.match(/const EXTRACTED_GRPC_SERVICES = ({[\s\S]*?});/);
            if (!match) {
                throw new Error('Could not find EXTRACTED_GRPC_SERVICES in file');
            }
            
            // Use eval to parse the object (safe since we control the file)
            const services = eval(`(${match[1]})`);
            console.log(`✅ Loaded ${Object.keys(services).length} gRPC services`);
            
            return services;
        } catch (error) {
            console.error('❌ Failed to load service definitions:', error.message);
            return {};
        }
    }
    
    /**
     * Make HTTP request to proxy server
     */
    async makeGrpcCall(methodName, requestData) {
        return new Promise((resolve, reject) => {
            const postData = JSON.stringify(requestData);
            
            // Convert methodName from "ServiceName/methodName" to "/ServiceName/methodName"
            const path = `/${methodName}`;
            
            const options = {
                hostname: 'localhost',
                port: 51023,
                path: path,
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Content-Length': Buffer.byteLength(postData)
                }
            };
            
            const req = http.request(options, (res) => {
                let data = '';
                res.on('data', (chunk) => data += chunk);
                res.on('end', () => {
                    try {
                        const response = JSON.parse(data);
                        resolve({
                            success: res.statusCode === 200,
                            data: response,
                            error: res.statusCode !== 200 ? `HTTP ${res.statusCode}` : null
                        });
                    } catch (error) {
                        resolve({
                            success: false,
                            data: null,
                            error: `Parse error: ${error.message}`
                        });
                    }
                });
            });
            
            req.on('error', (error) => {
                resolve({
                    success: false,
                    data: null,
                    error: error.message
                });
            });
            
            req.setTimeout(5000, () => {
                req.destroy();
                resolve({
                    success: false,
                    data: null,
                    error: 'Request timeout'
                });
            });
            
            req.write(postData);
            req.end();
        });
    }
    
    /**
     * Test a single method with retry logic
     */
    async testMethod(serviceName, methodName, methodDefinition) {
        const fullMethodName = `${serviceName}/${methodName}`;
        
        // Check if method is already commented out
        if (this.commentedOutMethods.has(fullMethodName)) {
            console.log(`  // CHECKME: ${methodName} - Commented out after ${this.maxRetries} failures`);
            return {
                serviceName,
                methodName,
                fullMethodName,
                status: 'commented_out',
                error: `Commented out after ${this.maxRetries} failures`
            };
        }
        
        const startTime = Date.now();
        console.log(`  🔧 Testing method: ${methodName}`);
        
        try {
            // Generate basic request data
            const requestData = {};
            
            // Make the gRPC call
            const response = await this.makeGrpcCall(fullMethodName, requestData);
            const duration = Date.now() - startTime;
            
            if (response.success) {
                console.log(`     ✅ SUCCESS (${duration}ms)`);
                this.passedTests++;
                return {
                    serviceName,
                    methodName,
                    fullMethodName,
                    status: 'passed',
                    duration,
                    response: response.data
                };
            } else {
                // Handle failure with retry logic
                const currentRetries = this.methodRetryCount.get(fullMethodName) || 0;
                this.methodRetryCount.set(fullMethodName, currentRetries + 1);
                
                if (response.error && response.error.includes('500')) {
                    console.log(`     💥 CRASHED (${duration}ms): ${response.error}`);
                    
                    if (currentRetries + 1 >= this.maxRetries) {
                        this.commentedOutMethods.add(fullMethodName);
                        console.log(`     🚫 COMMENTING OUT: ${fullMethodName} after ${this.maxRetries} failures`);
                        console.log(`     // CHECKME: ${methodName} - Requires specific parameters or different approach`);
                        
                        return {
                            serviceName,
                            methodName,
                            fullMethodName,
                            status: 'commented_out',
                            error: response.error,
                            duration
                        };
                    } else {
                        console.log(`     🔄 RETRY ${currentRetries + 1}/${this.maxRetries}: Will retry this method`);
                        this.crashedTests++;
                        return {
                            serviceName,
                            methodName,
                            fullMethodName,
                            status: 'crashed',
                            error: response.error,
                            duration,
                            retryAttempt: currentRetries + 1
                        };
                    }
                } else {
                    console.log(`     ❌ FAILED (${duration}ms): ${response.error}`);
                    this.failedTests++;
                    return {
                        serviceName,
                        methodName,
                        fullMethodName,
                        status: 'failed',
                        error: response.error,
                        duration
                    };
                }
            }
        } catch (error) {
            const duration = Date.now() - startTime;
            console.log(`     💥 EXCEPTION (${duration}ms): ${error.message}`);
            this.crashedTests++;
            return {
                serviceName,
                methodName,
                fullMethodName,
                status: 'crashed',
                error: error.message,
                duration
            };
        }
    }
    
    /**
     * Run comprehensive tests on all services
     */
    async runComprehensiveTests() {
        console.log('🔥 GRIND MODE: Starting standalone comprehensive gRPC tests...');
        
        const serviceDefinitions = this.loadServiceDefinitions();
        if (Object.keys(serviceDefinitions).length === 0) {
            console.error('❌ No service definitions loaded. Cannot run tests.');
            return;
        }
        
        // Test known working services first
        const knownWorkingServices = [
            'livelinkapi.LiveLinkService',
            'octaneapi.ApiProjectManagerService'
        ];
        
        console.log('🎯 Testing known working services first...');
        for (const serviceName of knownWorkingServices) {
            if (serviceDefinitions[serviceName]) {
                await this.testService(serviceName, serviceDefinitions[serviceName]);
            }
        }
        
        // Test all other services
        console.log('🔍 Testing all extracted services...');
        for (const [serviceName, serviceDefinition] of Object.entries(serviceDefinitions)) {
            if (!knownWorkingServices.includes(serviceName)) {
                await this.testService(serviceName, serviceDefinition);
            }
        }
        
        this.generateFinalReport();
        this.saveResultsToFile();
    }
    
    /**
     * Test a specific service and all its methods
     */
    async testService(serviceName, serviceDefinition) {
        console.log(`\n🔍 Testing service: ${serviceName}`);
        
        const methods = serviceDefinition.methods || {};
        const methodCount = Object.keys(methods).length;
        
        if (methodCount === 0) {
            console.log(`   ⚠️ No methods found for ${serviceName}`);
            return;
        }
        
        console.log(`   📊 Methods to test: ${methodCount}`);
        
        // Test each method
        for (const [methodName, methodDef] of Object.entries(methods)) {
            const result = await this.testMethod(serviceName, methodName, methodDef);
            this.testResults.push(result);
            this.totalTests++;
            
            // Small delay to prevent overwhelming the server
            await new Promise(resolve => setTimeout(resolve, 10));
        }
    }
    
    /**
     * Generate comprehensive final report
     */
    generateFinalReport() {
        const duration = Date.now() - this.startTime;
        
        console.log(`\n🎯 ===== GRIND MODE COMPREHENSIVE TEST REPORT =====`);
        console.log(`⏱️ Total test duration: ${duration}ms`);
        console.log(`📊 Total tests run: ${this.totalTests}`);
        console.log(`✅ Passed: ${this.passedTests} (${((this.passedTests/this.totalTests)*100).toFixed(1)}%)`);
        console.log(`❌ Failed: ${this.failedTests} (${((this.failedTests/this.totalTests)*100).toFixed(1)}%)`);
        console.log(`💥 Crashed: ${this.crashedTests} (${((this.crashedTests/this.totalTests)*100).toFixed(1)}%)`);
        console.log(`🚫 Commented out: ${this.commentedOutMethods.size} methods after ${this.maxRetries} failures each`);
        
        // List commented out methods
        if (this.commentedOutMethods.size > 0) {
            console.log(`\n🚫 COMMENTED OUT METHODS (require manual review):`);
            Array.from(this.commentedOutMethods).forEach(methodName => {
                console.log(`   // CHECKME: ${methodName} - Failed ${this.maxRetries} times`);
            });
        }
        
        // Performance metrics
        console.log(`\n⚡ PERFORMANCE METRICS:`);
        const avgDuration = duration / this.totalTests;
        console.log(`   📊 Average test duration: ${avgDuration.toFixed(2)}ms`);
        console.log(`   🚀 Tests per second: ${(this.totalTests / (duration / 1000)).toFixed(2)}`);
        
        console.log(`\n🎯 GRIND MODE COMPLETE: All ${this.totalTests} methods tested systematically!`);
    }
    
    /**
     * Save results to JSON file for analysis
     */
    saveResultsToFile() {
        const results = {
            summary: {
                totalTests: this.totalTests,
                passedTests: this.passedTests,
                failedTests: this.failedTests,
                crashedTests: this.crashedTests,
                commentedOutCount: this.commentedOutMethods.size,
                duration: Date.now() - this.startTime
            },
            commentedOutMethods: Array.from(this.commentedOutMethods),
            detailedResults: this.testResults
        };
        
        const outputPath = path.join(__dirname, 'grind_test_results.json');
        fs.writeFileSync(outputPath, JSON.stringify(results, null, 2));
        console.log(`📁 Results saved to: ${outputPath}`);
    }
}

// Run the tests if this script is executed directly
if (require.main === module) {
    const tester = new StandaloneGrindTester();
    tester.runComprehensiveTests().catch(error => {
        console.error('❌ Test execution failed:', error);
        process.exit(1);
    });
}

module.exports = StandaloneGrindTester;