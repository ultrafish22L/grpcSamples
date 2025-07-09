#!/usr/bin/env python3
"""
Simple HTTP server for testing HTML demos
Serves files from the html directory with CORS headers
"""

import http.server
import socketserver
import os
import sys
from urllib.parse import urlparse

class CORSHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        super().end_headers()

    def do_OPTIONS(self):
        self.send_response(200)
        self.end_headers()

def main():
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 52481
    
    # Change to html directory
    html_dir = os.path.dirname(os.path.abspath(__file__))
    os.chdir(html_dir)
    
    print(f"Starting HTTP server on port {port}")
    print(f"Serving files from: {html_dir}")
    print(f"Access demos at:")
    print(f"  http://localhost:{port}/livelink_demo.html")
    print(f"  http://localhost:{port}/grpc_test.html")
    print(f"  http://localhost:{port}/web3d_octane_sync.html")
    print()
    print("Press Ctrl+C to stop the server")
    
    with socketserver.TCPServer(("", port), CORSHTTPRequestHandler) as httpd:
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            print("\nServer stopped")

if __name__ == "__main__":
    main()