import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import path from 'path'

export default defineConfig({
  plugins: [react()],
  server: {
    port: 42219,
    host: '0.0.0.0',
    cors: true,
    strictPort: false,
    proxy: {
      // Proxy /api requests to Python proxy server (avoids CORS issues)
      // Browser: /api/rpc/... → Vite proxy → http://localhost:51023/rpc/... → Octane
      '/api': {
        target: 'http://localhost:51023',  // Python octane_proxy.py
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/api/, '')  // Remove /api prefix
      }
    }
  },
  resolve: {
    alias: {
      '@': path.resolve(__dirname, './src'),
    }
  }
})
