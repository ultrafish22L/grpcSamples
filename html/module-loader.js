/**
 * Simple module loader for browser compatibility with CommonJS-style generated files
 * This provides a basic require() function and module system for the browser
 */

// Create a global module system
window.modules = {};
window.require = function(name) {
    if (name === 'google-protobuf') {
        return window.jspb || window.protobuf;
    }
    if (name === 'grpc-web') {
        return window.grpc.web;
    }
    if (name.startsWith('./')) {
        // Handle relative imports
        const moduleName = name.replace('./', '').replace('.js', '');
        return window.modules[moduleName] || window.proto?.livelinkapi;
    }
    return window.modules[name] || window[name];
};

// Module export system
window.module = { exports: {} };
window.exports = window.module.exports;

// Initialize proto namespace
window.proto = window.proto || {};
window.proto.livelinkapi = window.proto.livelinkapi || {};

// Override module.exports to also set global proto
const originalModuleExports = window.module.exports;
Object.defineProperty(window.module, 'exports', {
    get: function() { return originalModuleExports; },
    set: function(value) {
        originalModuleExports = value;
        if (value && typeof value === 'object') {
            // Merge exports into global proto namespace
            Object.assign(window.proto.livelinkapi, value);
        }
    }
});

// Global object setup for protobuf
window.global = window;



// Setup goog object for Google Closure Library compatibility
window.goog = window.goog || {};
window.goog.provide = function(name) {
    const parts = name.split('.');
    let current = window;
    for (let i = 0; i < parts.length - 1; i++) {
        if (!current[parts[i]]) {
            current[parts[i]] = {};
        }
        current = current[parts[i]];
    }
    // Don't overwrite if it already exists (for the final part)
    if (!current[parts[parts.length - 1]]) {
        current[parts[parts.length - 1]] = {};
    }
    console.log('goog.provide created:', name);
};

window.goog.require = function(name) {
    // Handle specific gRPC-Web requirements
    if (name.startsWith('grpc.web.')) {
        const grpcPart = name.replace('grpc.web.', '');
        if (window.grpc && window.grpc.web && window.grpc.web[grpcPart]) {
            return window.grpc.web[grpcPart];
        }
        // Return a mock object for missing grpc.web components
        return {};
    }
    
    // Handle proto requirements
    if (name.startsWith('proto.livelinkapi.')) {
        const protoPart = name.replace('proto.livelinkapi.', '');
        if (window.proto && window.proto.livelinkapi && window.proto.livelinkapi[protoPart]) {
            return window.proto.livelinkapi[protoPart];
        }
        // Return empty object for proto types that will be defined later
        return {};
    }
    
    // Return the required module from global scope
    const parts = name.split('.');
    let current = window;
    for (let i = 0; i < parts.length; i++) {
        if (current[parts[i]]) {
            current = current[parts[i]];
        } else {
            console.warn('Module not found:', name);
            return {};
        }
    }
    return current;
};

window.goog.requireType = function(name) {
    // Type requirements are ignored in runtime
    return {};
};

window.goog.scope = function(fn) {
    // Execute the function immediately
    fn();
};

window.goog.exportSymbol = function(name, value, global) {
    const parts = name.split('.');
    let current = global || window;
    for (let i = 0; i < parts.length - 1; i++) {
        if (!current[parts[i]]) {
            current[parts[i]] = {};
        }
        current = current[parts[i]];
    }
    if (value !== null) {
        current[parts[parts.length - 1]] = value;
    }
};

window.goog.inherits = function(childCtor, parentCtor) {
    childCtor.superClass_ = parentCtor.prototype;
    childCtor.prototype = Object.create(parentCtor.prototype);
    childCtor.prototype.constructor = childCtor;
};

// Add goog.object for Google Closure Library compatibility
window.goog.object = window.goog.object || {};
window.goog.object.extend = function(target, source) {
    for (let key in source) {
        if (source.hasOwnProperty(key)) {
            target[key] = source[key];
        }
    }
    // Also extend global proto namespace
    if (target === window.exports && source) {
        Object.assign(window.proto.livelinkapi, source);
    }
};

// Create minimal grpc.web implementation for the generated files
// Since the CDN approach isn't working, let's create the minimal objects needed
window.grpc = window.grpc || {};
window.grpc.web = window.grpc.web || {};

// Create minimal MethodDescriptor class
window.grpc.web.MethodDescriptor = function(path, methodType, requestType, responseType) {
    this.path = path;
    this.methodType = methodType;
    this.requestType = requestType;
    this.responseType = responseType;
};

// Create MethodType enum
window.grpc.web.MethodType = {
    UNARY: 'unary',
    SERVER_STREAMING: 'server_streaming',
    CLIENT_STREAMING: 'client_streaming',
    BIDI_STREAMING: 'bidi_streaming'
};

// Create minimal GrpcWebClientBase class
window.grpc.web.GrpcWebClientBase = function(options) {
    this.hostname_ = options.hostname || '';
    this.credentials_ = options.credentials || null;
    this.options_ = options || {};
};

window.grpc.web.GrpcWebClientBase.prototype.unaryCall = function(method, request, metadata, methodDescriptor) {
    // This is a stub implementation - in a real app you'd implement the actual gRPC-Web call
    console.log('gRPC unary call:', method, request);
    return Promise.reject(new Error('gRPC-Web not fully implemented - this is just for demo'));
};

// Create other minimal classes that might be needed
window.grpc.web.AbstractClientBase = window.grpc.web.GrpcWebClientBase;
window.grpc.web.ClientReadableStream = function() {};
window.grpc.web.RpcError = function(code, message) {
    this.code = code;
    this.message = message;
};

console.log('Minimal gRPC-Web implementation created');

// Make sure jspb has the same functions as goog (since generated files do var goog = jspb)
if (typeof window.jspb !== 'undefined') {
    window.jspb.provide = window.goog.provide;
    window.jspb.require = window.goog.require;
    window.jspb.requireType = window.goog.requireType;
    window.jspb.scope = window.goog.scope;
    window.jspb.exportSymbol = window.goog.exportSymbol;
    window.jspb.inherits = window.goog.inherits;
    window.jspb.object = window.goog.object;
    console.log('jspb functions added');
}

console.log('Module loader initialized');

// Debug function to check what's available
window.debugProto = function() {
    console.log('window.proto:', window.proto);
    console.log('window.proto.livelinkapi:', window.proto?.livelinkapi);
    console.log('window.exports:', window.exports);
    console.log('window.module.exports:', window.module.exports);
    console.log('window.grpc:', window.grpc);
    console.log('window.grpc.web:', window.grpc?.web);
};