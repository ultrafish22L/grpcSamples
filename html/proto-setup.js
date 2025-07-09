/**
 * Proto setup script - Ensures proto namespace is properly set up
 * This script should be loaded after the generated gRPC-Web files
 */

console.log('Proto setup starting...');

// The generated files should have already created the proto namespace via goog.provide
// Let's check what's available
console.log('window.proto:', window.proto);
console.log('window.proto.livelinkapi:', window.proto?.livelinkapi);

if (window.proto && window.proto.livelinkapi) {
    console.log('Proto namespace found. Available classes:', Object.keys(window.proto.livelinkapi));
    console.log('LiveLinkServiceClient available:', !!window.proto.livelinkapi.LiveLinkServiceClient);
} else {
    console.log('Proto namespace not found. Checking for alternative locations...');
    
    // Check all global variables for proto-related objects
    for (let key in window) {
        if (key.includes('LiveLink') || key.includes('proto')) {
            console.log('Found proto-related global:', key, window[key]);
        }
    }
}

console.log('Proto setup complete.');