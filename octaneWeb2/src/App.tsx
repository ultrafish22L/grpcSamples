import { QueryClient, QueryClientProvider } from '@tanstack/react-query'
import { MainLayout } from './components/layout/MainLayout'
import { useConnectionStore } from './store/connectionStore'
import { useEffect, useState } from 'react'
import './styles/variables.css'

const queryClient = new QueryClient({
  defaultOptions: {
    queries: {
      refetchOnWindowFocus: false,
      retry: 1,
      staleTime: 5000,
    },
  },
})

function AppContent() {
  const { isConnected, isConnecting, connect, disconnect, error } = useConnectionStore()
  const [showConnectDialog, setShowConnectDialog] = useState(!isConnected)

  const handleConnect = async () => {
    setShowConnectDialog(false)
    const success = await connect()
    if (!success) {
      setShowConnectDialog(true)
    }
  }

  // Auto-connect on mount
  useEffect(() => {
    console.log('🚀 OctaneWeb2 starting...')
    if (!isConnected) {
      handleConnect()
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [])

  if (showConnectDialog && !isConnected) {
    return (
      <div style={{
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        justifyContent: 'center',
        height: '100vh',
        background: '#1e1e1e',
        color: '#fff',
        fontFamily: 'system-ui, -apple-system, sans-serif'
      }}>
        <div style={{
          background: '#2d2d2d',
          padding: '40px',
          borderRadius: '8px',
          boxShadow: '0 4px 12px rgba(0,0,0,0.5)',
          maxWidth: '400px',
          width: '90%'
        }}>
          <h1 style={{ margin: '0 0 20px 0', fontSize: '24px' }}>Connect to Octane</h1>
          <p style={{ margin: '0 0 20px 0', color: '#aaa' }}>
            Make sure Octane Standalone is running with LiveLink enabled.
          </p>
          {error && (
            <div style={{
              background: '#4a2020',
              border: '1px solid #8b0000',
              padding: '12px',
              borderRadius: '4px',
              marginBottom: '20px',
              color: '#ff6b6b'
            }}>
              ❌ {error}
            </div>
          )}
          <button
            onClick={handleConnect}
            disabled={isConnecting}
            style={{
              width: '100%',
              padding: '12px 24px',
              background: isConnecting ? '#555' : '#0066cc',
              color: '#fff',
              border: 'none',
              borderRadius: '4px',
              fontSize: '16px',
              cursor: isConnecting ? 'not-allowed' : 'pointer',
              transition: 'background 0.2s'
            }}
          >
            {isConnecting ? 'Connecting...' : 'Connect'}
          </button>
        </div>
      </div>
    )
  }

  return (
    <div>
      {isConnected && (
        <div style={{
          position: 'fixed',
          top: '10px',
          right: '10px',
          zIndex: 9999,
          background: '#2d2d2d',
          padding: '8px 16px',
          borderRadius: '4px',
          display: 'flex',
          gap: '10px',
          alignItems: 'center'
        }}>
          <span style={{ color: '#4ade80' }}>● Connected</span>
          <button
            onClick={disconnect}
            style={{
              padding: '4px 12px',
              background: '#444',
              color: '#fff',
              border: 'none',
              borderRadius: '4px',
              cursor: 'pointer',
              fontSize: '12px'
            }}
          >
            Disconnect
          </button>
        </div>
      )}
      <MainLayout />
    </div>
  )
}

function App() {
  return (
    <QueryClientProvider client={queryClient}>
      <AppContent />
    </QueryClientProvider>
  )
}

export default App
