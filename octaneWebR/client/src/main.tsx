import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App'
import { ThemeProvider } from './hooks/useTheme'
import './styles/app.css'
import './styles/octane-theme.css'
import './styles/octane-theme-light.css'
import './styles/components.css'
import './styles/layout.css'
import './utils/ClientLogger' // Initialize client-side logging to server

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <ThemeProvider>
      <App />
    </ThemeProvider>
  </React.StrictMode>,
)
