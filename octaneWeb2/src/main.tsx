import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App.tsx'
import { initDebugLogger } from './utils/DebugLogger'

// Initialize debug logger FIRST - captures all console output
// Logs saved to: octaneWeb2/debug_logs/octane-debug-{sessionId}.log
// AI agents can read logs with: tail -100 /workspace/grpcSamples/octaneWeb2/debug_logs/octane-debug-*.log
initDebugLogger('/api')

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
)
