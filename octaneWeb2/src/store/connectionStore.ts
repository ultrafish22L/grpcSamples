import { create } from 'zustand'
import { octaneClient } from '../api/octaneClient'
import { emitEvent } from '../core/eventBus'

interface ConnectionState {
  isConnected: boolean
  isConnecting: boolean
  serverUrl: string
  error: string | null
  serverInfo: { version: string; buildDate: string } | null
  
  connect: () => Promise<boolean>
  disconnect: () => void
  setError: (error: string | null) => void
}

export const useConnectionStore = create<ConnectionState>((set, get) => ({
  isConnected: false,
  isConnecting: false,
  serverUrl: 'http://localhost:51023',
  error: null,
  serverInfo: null,
  
  connect: async () => {
    const { serverUrl } = get()
    
    set({ isConnecting: true, error: null })
    emitEvent('connection:connecting', undefined)
    
    try {
      const success = await octaneClient.connect()
      
      if (success) {
        const serverInfo = await octaneClient.getServerInfo()
        
        set({
          isConnected: true,
          isConnecting: false,
          serverInfo: {
            version: serverInfo.version,
            buildDate: serverInfo.buildDate
          }
        })
        
        emitEvent('connection:connected', { serverUrl })
        console.log('✅ Connected to Octane:', serverInfo)
        return true
      } else {
        set({
          isConnected: false,
          isConnecting: false,
          error: 'Failed to connect to Octane'
        })
        return false
      }
    } catch (error) {
      const errorMsg = error instanceof Error ? error.message : 'Unknown error'
      set({
        isConnected: false,
        isConnecting: false,
        error: errorMsg
      })
      emitEvent('connection:error', { error: error as Error })
      console.error('❌ Connection failed:', errorMsg)
      return false
    }
  },
  
  disconnect: () => {
    octaneClient.disconnect()
    set({
      isConnected: false,
      isConnecting: false,
      serverInfo: null
    })
    emitEvent('connection:disconnected', undefined)
    console.log('Disconnected from Octane')
  },
  
  setError: (error) => set({ error })
}))
