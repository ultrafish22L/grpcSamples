#!/usr/bin/env python3
"""
Debug Log Server for OctaneWeb
Handles saving debug logs to persistent system files
"""

import os
import json
import datetime
from http.server import HTTPServer, BaseHTTPRequestHandler
from urllib.parse import urlparse, parse_qs
import threading
import time

class DebugLogHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        if self.path == '/save-debug-logs':
            self.handle_save_logs()
        else:
            self.send_error(404, "Not Found")
    
    def do_GET(self):
        if self.path.startswith('/debug-logs/'):
            self.handle_get_logs()
        else:
            self.send_error(404, "Not Found")
    
    def handle_save_logs(self):
        try:
            # Read the request body
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data.decode('utf-8'))
            
            # Extract data
            session_id = data.get('sessionId', 'unknown')
            log_content = data.get('content', '')
            timestamp = data.get('timestamp', datetime.datetime.now().isoformat())
            
            # Create logs directory if it doesn't exist
            logs_dir = '/workspace/grpcSamples/octaneWeb/debug_logs'
            os.makedirs(logs_dir, exist_ok=True)
            
            # Create filename
            filename = f"octane-debug-{session_id}.log"
            filepath = os.path.join(logs_dir, filename)
            
            # Write log content to file
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(log_content)
            
            # Send success response
            response = {
                'success': True,
                'filename': filename,
                'filepath': filepath,
                'timestamp': timestamp,
                'size': len(log_content)
            }
            
            self.send_response(200)
            self.send_header('Content-Type', 'application/json')
            self.send_header('Access-Control-Allow-Origin', '*')
            self.send_header('Access-Control-Allow-Methods', 'POST, GET, OPTIONS')
            self.send_header('Access-Control-Allow-Headers', 'Content-Type')
            self.end_headers()
            self.wfile.write(json.dumps(response).encode('utf-8'))
            
            print(f"💾 Debug logs saved: {filepath} ({len(log_content)} bytes)")
            
        except Exception as e:
            print(f"❌ Error saving debug logs: {e}")
            self.send_error(500, f"Internal Server Error: {str(e)}")
    
    def handle_get_logs(self):
        try:
            # Extract session ID from path
            path_parts = self.path.split('/')
            if len(path_parts) >= 3:
                session_id = path_parts[2]
                
                logs_dir = '/workspace/grpcSamples/octaneWeb/debug_logs'
                filename = f"octane-debug-{session_id}.log"
                filepath = os.path.join(logs_dir, filename)
                
                if os.path.exists(filepath):
                    with open(filepath, 'r', encoding='utf-8') as f:
                        content = f.read()
                    
                    self.send_response(200)
                    self.send_header('Content-Type', 'text/plain')
                    self.send_header('Access-Control-Allow-Origin', '*')
                    self.end_headers()
                    self.wfile.write(content.encode('utf-8'))
                else:
                    self.send_error(404, "Log file not found")
            else:
                self.send_error(400, "Invalid path")
                
        except Exception as e:
            print(f"❌ Error retrieving debug logs: {e}")
            self.send_error(500, f"Internal Server Error: {str(e)}")
    
    def do_OPTIONS(self):
        # Handle CORS preflight requests
        self.send_response(200)
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'POST, GET, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        self.end_headers()
    
    def log_message(self, format, *args):
        # Suppress default HTTP server logging
        pass

def run_debug_log_server(port=43332):
    """Run the debug log server"""
    server_address = ('', port)
    httpd = HTTPServer(server_address, DebugLogHandler)
    print(f"🚀 Debug Log Server running on port {port}")
    print(f"📁 Log files will be saved to: /workspace/grpcSamples/octaneWeb/debug_logs/")
    httpd.serve_forever()

if __name__ == '__main__':
    run_debug_log_server()