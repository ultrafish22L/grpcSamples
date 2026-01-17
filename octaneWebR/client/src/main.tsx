import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App'
import './styles/app.css'
import './styles/octane-theme.css'
import './styles/scene-outliner.css'
import './styles/node-graph.css'
import './styles/node-inspector.css'
import './styles/viewport.css'
import './utils/ClientLogger' // Initialize client-side logging to server

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
)
