import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import { octaneGrpcPlugin } from './vite-plugin-octane-grpc'

export default defineConfig({
  plugins: [
    react(),
    octaneGrpcPlugin()
  ],
  root: 'client',
  server: {
    port: 43929,
    host: '0.0.0.0',
    strictPort: false,
    cors: true
  },
  build: {
    outDir: '../dist/client'
  }
})
