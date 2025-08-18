#GRPC SDK

## 🚨 **CRITICAL REQUIREMENT: REAL OCTANE ONLY**

**⚠️ NEVER EVER use mock or simulated data - only real live connection with Octane LiveLink service.**

The GRPC API allows remote connections to octane.exe. The GRPC server can be enabled via the GRPC-API tab in the preferences window.

## Demo applications

The `render-example` application demonstrates how to use the grpc-api to achieve the following:
 * create a new project
 * build the node graph
 * render an image
 * recieve events and stream images
 
 It takes two arguments
 1. ip address e.g. "127.0.0.1:51022"
 2. path to copy the viewport images. e.g. "C:\RenderedImages"
 
 To build the demo, a third party folder needs to be added at the same level as the solution file. It should have the following structure:
    thirdparty/
    ├── absl/
    ├── cares/
    ├── curl/
    ├── grpc/
    ├── openssl/
    ├── protobuf/
    ├── re2/
    └── zlib/