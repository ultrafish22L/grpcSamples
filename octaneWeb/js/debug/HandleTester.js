/**
 * Handle-specific tester to isolate Octane crashes
 * Tests individual handles to find problematic ones
 */

class HandleTester {
    constructor() {
        this.results = [];
    }
    
    /**
     * Test a specific handle with detailed logging
     * @param {string} handle - Handle to test
     * @param {number} type - Object type
     */
    testHandle(handle, type) {
        console.log(`🔍 TESTING HANDLE: ${handle} (type: ${type})`);
        
        const result = {
            handle: handle,
            type: type,
            nameSuccess: false,
            superclassSuccess: false,
            nameResult: null,
            superclassResult: null,
            crashed: false
        };
        
        // Test name call
        try {
            console.log(`🔍 Testing ApiItem/name for handle ${handle}...`);
            const nameResult = window.grpcApi.makeApiCallSync('ApiItem/name', handle);
            
            if (nameResult.success) {
                result.nameSuccess = true;
                result.nameResult = nameResult.data.result;
                console.log(`✅ NAME SUCCESS: "${result.nameResult}" for handle ${handle}`);
            } else {
                console.log(`❌ NAME FAILED: ${nameResult.error} for handle ${handle}`);
                result.nameResult = nameResult.error;
            }
            
        } catch (error) {
            console.error(`💥 NAME CRASHED: ${error.message} for handle ${handle}`);
            result.crashed = true;
            result.nameResult = error.message;
            this.results.push(result);
            return result; // Don't test superclass if name crashed
        }
        
        // Test superclass call
        try {
            console.log(`🔍 Testing ApiItem/superclass for handle ${handle}...`);
            const superclassResult = window.grpcApi.makeApiCallSync('ApiItem/superclass', handle);
            
            if (superclassResult.success) {
                result.superclassSuccess = true;
                result.superclassResult = superclassResult.data.result;
                console.log(`✅ SUPERCLASS SUCCESS: "${result.superclassResult}" for handle ${handle}`);
            } else {
                console.log(`❌ SUPERCLASS FAILED: ${superclassResult.error} for handle ${handle}`);
                result.superclassResult = superclassResult.error;
            }
            
        } catch (error) {
            console.error(`💥 SUPERCLASS CRASHED: ${error.message} for handle ${handle}`);
            result.crashed = true;
            result.superclassResult = error.message;
        }
        
        this.results.push(result);
        return result;
    }
    
    /**
     * Test all handles from scene items
     * @param {Array} items - Items from ApiItemArray/items
     */
    testAllHandles(items) {
        console.log(`🔍 TESTING ${items.length} HANDLES...`);
        
        for (let i = 0; i < items.length; i++) {
            const item = items[i];
            console.log(`\n🔍 === TESTING ITEM ${i + 1}/${items.length} ===`);
            
            const result = this.testHandle(item.handle, item.type);
            
            if (result.crashed) {
                console.error(`💥 CRASH DETECTED ON HANDLE ${item.handle}! Stopping tests.`);
                break;
            }
        }
        
        this.printSummary();
    }
    
    /**
     * Print test summary
     */
    printSummary() {
        console.log(`\n📊 === TEST SUMMARY ===`);
        console.log(`Total handles tested: ${this.results.length}`);
        
        const successful = this.results.filter(r => !r.crashed && r.nameSuccess && r.superclassSuccess);
        const failed = this.results.filter(r => !r.crashed && (!r.nameSuccess || !r.superclassSuccess));
        const crashed = this.results.filter(r => r.crashed);
        
        console.log(`✅ Successful: ${successful.length}`);
        console.log(`❌ Failed: ${failed.length}`);
        console.log(`💥 Crashed: ${crashed.length}`);
        
        if (crashed.length > 0) {
            console.log(`\n💥 CRASH DETAILS:`);
            crashed.forEach(r => {
                console.log(`  Handle ${r.handle}: ${r.nameResult || r.superclassResult}`);
            });
        }
        
        if (failed.length > 0) {
            console.log(`\n❌ FAILURE DETAILS:`);
            failed.forEach(r => {
                if (!r.nameSuccess) {
                    console.log(`  Handle ${r.handle} name failed: ${r.nameResult}`);
                }
                if (!r.superclassSuccess) {
                    console.log(`  Handle ${r.handle} superclass failed: ${r.superclassResult}`);
                }
            });
        }
    }
    
    /**
     * Get scene items for testing
     */
    async getSceneItems() {
        console.log(`🔍 Getting scene items for handle testing...`);
        
        try {
            // Get root node graph
            const rootResult = window.grpcApi.makeApiCallSync('ApiProjectManager/rootNodeGraph');
            if (!rootResult.success) throw new Error('Failed to get root node graph');
            
            // Get owned items
            const ownedItemsResult = window.grpcApi.makeApiCallSync(
                'ApiNodeGraph/getOwnedItems', 
                rootResult.data.result.handle
            );
            if (!ownedItemsResult.success) throw new Error('Failed to get owned items');
            
            // Get items array
            const itemsResult = window.grpcApi.makeApiCallSync(
                'ApiItemArray/items', 
                ownedItemsResult.data.list.handle
            );
            if (!itemsResult.success) throw new Error('Failed to get items array');
            
            return itemsResult.data.result.data;
            
        } catch (error) {
            console.error(`💥 Failed to get scene items: ${error.message}`);
            throw error;
        }
    }
    
    /**
     * Run complete handle test
     */
    async runTest() {
        try {
            const items = await this.getSceneItems();
            console.log(`🔍 Found ${items.length} items to test:`, items);
            
            this.testAllHandles(items);
            
        } catch (error) {
            console.error(`💥 Handle test failed: ${error.message}`);
        }
    }
}

// Make available globally for testing
window.HandleTester = HandleTester;

// Auto-run test when loaded
console.log('🔍 HandleTester loaded, setting up auto-run...');

window.addEventListener('load', () => {
    setTimeout(() => {
        console.log('🔍 Starting automatic handle testing...');
        const tester = new HandleTester();
        tester.runTest();
    }, 3000); // Wait 3 seconds for app to initialize
});

// Also provide manual trigger
window.runHandleTest = function() {
    console.log('🔍 Manual handle test triggered...');
    const tester = new HandleTester();
    tester.runTest();
};