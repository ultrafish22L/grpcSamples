// Simple test to trigger API calls and check logs
const http = require('http');

async function makeApiCall(service, method, params = {}) {
  return new Promise((resolve, reject) => {
    const data = JSON.stringify(params);
    
    const options = {
      hostname: 'localhost',
      port: 51023,
      path: `/${service}/${method}`,
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Content-Length': data.length,
        'User-Agent': 'octaneWeb2-test',
        'Referer': 'http://localhost:41604/'
      }
    };

    const req = http.request(options, (res) => {
      let responseData = '';
      
      res.on('data', (chunk) => {
        responseData += chunk;
      });
      
      res.on('end', () => {
        try {
          resolve(JSON.parse(responseData));
        } catch (e) {
          reject(new Error(`Failed to parse response: ${responseData}`));
        }
      });
    });

    req.on('error', reject);
    req.write(data);
    req.end();
  });
}

async function testSceneSync() {
  console.log('🧪 Testing Scene Synchronization\n');
  
  try {
    // 1. Get root node graph
    console.log('1️⃣  Getting root node graph...');
    const rootResponse = await makeApiCall('ApiProjectManager', 'rootNodeGraph', {});
    console.log('Response:', JSON.stringify(rootResponse, null, 2));
    
    if (!rootResponse.success || !rootResponse.data?.result?.handle) {
      console.error('❌ Failed to get root node graph');
      return;
    }
    
    const rootHandle = rootResponse.data.result.handle;
    console.log(`✅ Root handle: ${rootHandle}\n`);
    
    // 2. Check if it's a graph
    console.log('2️⃣  Checking if root is a graph...');
    const isGraphResponse = await makeApiCall('ApiItem', 'isGraph', { 
      objectPtr: { handle: rootHandle, type: 16 }  // ApiItem = 16
    });
    console.log('Response:', JSON.stringify(isGraphResponse, null, 2));
    
    if (!isGraphResponse.success) {
      console.error('❌ Failed to check isGraph');
      return;
    }
    
    const isGraph = isGraphResponse.data.result;
    console.log(`✅ Is graph: ${isGraph}\n`);
    
    if (!isGraph) {
      console.log('⚠️  Root is not a graph, stopping here');
      return;
    }
    
    // 3. Get owned items
    console.log('3️⃣  Getting owned items...');
    const ownedResponse = await makeApiCall('ApiNodeGraph', 'getOwnedItems', { 
      objectPtr: { handle: rootHandle, type: 20 }  // ApiNodeGraph = 20
    });
    console.log('Response:', JSON.stringify(ownedResponse, null, 2));
    
    if (!ownedResponse.success || !ownedResponse.data?.list?.handle) {
      console.error('❌ Failed to get owned items');
      return;
    }
    
    const ownedItemsHandle = ownedResponse.data.list.handle;
    console.log(`✅ Owned items handle: ${ownedItemsHandle}\n`);
    
    // 4. Get array size
    console.log('4️⃣  Getting array size...');
    const sizeResponse = await makeApiCall('ApiItemArray', 'size', { 
      objectPtr: { handle: ownedItemsHandle, type: 31 }  // ApiItemArray = 31
    });
    console.log('Response:', JSON.stringify(sizeResponse, null, 2));
    
    if (!sizeResponse.success) {
      console.error('❌ Failed to get array size');
      return;
    }
    
    const size = sizeResponse.data.result;
    console.log(`✅ Array size: ${size} items\n`);
    
    if (size === 0) {
      console.log('⚠️  Scene is empty (0 items)');
      return;
    }
    
    // 5. Get first item
    console.log('5️⃣  Getting first item...');
    const itemResponse = await makeApiCall('ApiItemArray', 'get', { 
      objectPtr: { handle: ownedItemsHandle, type: 31 },  // ApiItemArray = 31
      ix: 0 
    });
    console.log('Response:', JSON.stringify(itemResponse, null, 2));
    
    if (!itemResponse.success || !itemResponse.data?.result?.handle) {
      console.error('❌ Failed to get first item');
      return;
    }
    
    const firstItemHandle = itemResponse.data.result.handle;
    console.log(`✅ First item handle: ${firstItemHandle}\n`);
    
    // 6. Get item name
    console.log('6️⃣  Getting item name...');
    const nameResponse = await makeApiCall('ApiItem', 'name', { 
      objectPtr: { handle: firstItemHandle, type: 16 }  // ApiItem = 16
    });
    console.log('Response:', JSON.stringify(nameResponse, null, 2));
    
    if (!nameResponse.success) {
      console.error('❌ Failed to get item name');
      return;
    }
    
    const name = nameResponse.data.result;
    console.log(`✅ Item name: "${name}"\n`);
    
    console.log('🎉 Scene sync test PASSED! All API calls working correctly.');
    
  } catch (error) {
    console.error('❌ Test failed:', error.message);
    console.error(error.stack);
  }
}

testSceneSync();
