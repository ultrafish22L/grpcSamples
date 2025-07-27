#!/usr/bin/env node

/**
 * Test script to simulate what the SceneOutliner does
 * This will help us identify if the issue is in the API calls or the DOM updates
 */

const http = require('http');

function makeRequest(path, data = {}) {
    return new Promise((resolve, reject) => {
        const postData = JSON.stringify(data);
        
        const options = {
            hostname: 'localhost',
            port: 51998,
            path: path,
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Content-Length': Buffer.byteLength(postData)
            }
        };

        const req = http.request(options, (res) => {
            let data = '';
            res.on('data', (chunk) => {
                data += chunk;
            });
            res.on('end', () => {
                try {
                    resolve(JSON.parse(data));
                } catch (e) {
                    reject(new Error(`Failed to parse JSON: ${data}`));
                }
            });
        });

        req.on('error', (err) => {
            reject(err);
        });

        req.write(postData);
        req.end();
    });
}

async function testSceneConnection() {
    console.log('🧪 Testing Scene Connection (simulating SceneOutliner.js)...\n');

    try {
        // Step 1: Test proxy connection
        console.log('📡 Step 1: Testing proxy connection...');
        const testResult = await makeRequest('/test');
        console.log('✅ Proxy test result:', testResult);
        
        if (!testResult.success) {
            console.log('❌ Proxy test failed, stopping');
            return;
        }

        // Step 2: Get root node graph
        console.log('\n📡 Step 2: Getting root node graph...');
        const rootResult = await makeRequest('/ApiProjectManagerService/rootNodeGraph', {});
        console.log('✅ Root result:', rootResult);

        if (!rootResult.success) {
            console.log('❌ Root node graph failed, stopping');
            return;
        }

        // Step 3: Get owned items (convert type 18 to 20)
        console.log('\n📋 Step 3: Getting owned items...');
        const ownedItemsResult = await makeRequest('/ApiNodeGraph/getOwnedItems', {
            objectPtr: {
                handle: rootResult.objectRef.handle,
                type: 20  // Convert from ApiRootNodeGraph (18) to ApiNodeGraph (20)
            }
        });
        console.log('✅ Owned items result:', ownedItemsResult);

        if (!ownedItemsResult.success) {
            console.log('❌ Owned items failed, stopping');
            return;
        }

        // Step 4: Get array size
        console.log('\n🔢 Step 4: Getting array size...');
        const sizeResult = await makeRequest('/ApiItemArray/size', {
            objectPtr: ownedItemsResult.objectRef
        });
        console.log('✅ Size result:', sizeResult);

        if (!sizeResult.success) {
            console.log('❌ Size failed, stopping');
            return;
        }

        // Step 5: Get individual items
        console.log('\n🎯 Step 5: Getting individual items...');
        const sceneItems = [];
        
        for (let i = 0; i < sizeResult.size; i++) {
            console.log(`  Getting item ${i}...`);
            
            // Get item at index i
            const itemResult = await makeRequest('/ApiItemArray/get1', {
                objectPtr: ownedItemsResult.objectRef,
                index: i
            });
            
            if (itemResult.success) {
                // Get the name of this item
                const nameResult = await makeRequest('/ApiItem/name', {
                    objectPtr: itemResult.objectRef
                });
                
                const item = {
                    handle: itemResult.objectRef.handle,
                    type: itemResult.objectRef.type,
                    name: nameResult.success ? nameResult.name : `Item_${i}`,
                    index: i
                };
                
                sceneItems.push(item);
                console.log(`  ✅ Item ${i}:`, item);
            } else {
                console.log(`  ❌ Failed to get item ${i}:`, itemResult);
            }
        }

        console.log('\n🎉 FINAL SCENE DATA:');
        console.log('Scene Items:', sceneItems);
        
        // This is what should be displayed in the UI
        console.log('\n📋 UI SHOULD SHOW:');
        sceneItems.forEach(item => {
            const icon = item.name.includes('.obj') ? '🔺' : 
                        item.name === 'Render target' ? '🎯' : '📦';
            console.log(`  ${icon} ${item.name} [${item.handle}]`);
        });

    } catch (error) {
        console.error('❌ Test failed:', error.message);
    }
}

testSceneConnection();