// Test script to call findAttr endpoint directly
const http = require('http');

const port = 43932; // Current server port
const filmSettingsHandle = "12345"; // Dummy handle for testing

// Create the request body as OctaneClient would
const body = {
  objectPtr: {
    handle: filmSettingsHandle,
    type: 16  // ObjectType.ApiItem
  },
  id: 2672  // P_LOCK_RENDER_AOVS (correct value from common.proto)
};

const options = {
  hostname: 'localhost',
  port: port,
  path: '/api/grpc/ApiItem/findAttr',
  method: 'POST',
  headers: {
    'Content-Type': 'application/json',
  }
};

console.log('📤 Testing findAttr endpoint...');
console.log('   URL:', `http://localhost:${port}${options.path}`);
console.log('   Body:', JSON.stringify(body, null, 2));

const req = http.request(options, (res) => {
  console.log(`\n📥 Response status: ${res.statusCode}`);
  
  let data = '';
  res.on('data', (chunk) => {
    data += chunk;
  });
  
  res.on('end', () => {
    console.log('   Response body:', data);
    try {
      const json = JSON.parse(data);
      console.log('   Parsed:', JSON.stringify(json, null, 2));
    } catch (e) {
      console.log('   (Not valid JSON)');
    }
  });
});

req.on('error', (error) => {
  console.error('❌ Request error:', error.message);
});

req.write(JSON.stringify(body));
req.end();
