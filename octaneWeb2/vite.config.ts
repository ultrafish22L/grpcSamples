import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import path from 'path'
import http from 'http'

// Force Node.js to prefer IPv4
// This prevents Node from trying IPv6 (::1) before IPv4 (127.0.0.1)
process.env.NODE_OPTIONS = '--dns-result-order=ipv4first'

export default defineConfig({
  plugins: [react()],
  server: {
    port: 41604,
    host: '0.0.0.0',
    cors: true,
    strictPort: false,
    allowedHosts: ['localhost', '127.0.0.1'],
    proxy: {
      // Proxy /api requests to Python proxy server (avoids CORS issues)
      // Browser: /api/rpc/... → Vite proxy → Python proxy (51023) → Octane (51022)
      // 
      // IMPORTANT: Use 127.0.0.1 (IPv4) not localhost (which resolves to IPv6 ::1)
      // For Docker environments, change to: http://host.docker.internal:51023
      '/api': {
        target: 'http://127.0.0.1:51023',  // Python octane_proxy.py
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/api/, ''),  // Remove /api prefix
        // Force IPv4 connections by specifying agent with IPv4 family
        agent: new http.Agent({
          family: 4  // Force IPv4 (4 = IPv4, 6 = IPv6)
        })
      }
    }
  },
  resolve: {
    alias: {
      '@': path.resolve(__dirname, './src'),
    }
  }
})
