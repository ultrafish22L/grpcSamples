import { create } from 'zustand';

interface ConnectionState {
  isConnected: boolean;
  connected: boolean;  // Alias for isConnected
  isConnecting: boolean;
  serverUrl: string;
  error: string | null;
  
  setConnected: (connected: boolean) => void;
  setConnecting: (connecting: boolean) => void;
  setError: (error: string | null) => void;
  setServerUrl: (url: string) => void;
}

export const useConnectionStore = create<ConnectionState>((set) => ({
  isConnected: false,
  connected: false,
  isConnecting: false,
  serverUrl: 'http://localhost:51023',
  error: null,
  
  setConnected: (connected) => set({ isConnected: connected, connected }),
  setConnecting: (connecting) => set({ isConnecting: connecting }),
  setError: (error) => set({ error }),
  setServerUrl: (url) => set({ serverUrl: url }),
}));
