import { useEffect } from 'react';
import { QueryClient, QueryClientProvider } from '@tanstack/react-query';
import { MainLayout } from './components/layout/MainLayout';
import { useConnectionStore } from './store/connectionStore';
import { octaneClient } from './api/octaneClient';
import './styles/variables.css';

const queryClient = new QueryClient({
  defaultOptions: {
    queries: {
      refetchOnWindowFocus: false,
      retry: 1,
      staleTime: 5000,
    },
  },
});

function AppContent() {
  const { setConnected, setConnecting, setError } = useConnectionStore();

  // Auto-connect on startup
  useEffect(() => {
    const autoConnect = async () => {
      console.log('🔌 Auto-connecting to Octane...');
      setConnecting(true);
      setError(null);
      
      try {
        const connected = await octaneClient.connect();
        setConnected(connected);
        if (connected) {
          console.log('✅ Auto-connect successful');
        } else {
          console.warn('⚠️ Auto-connect failed');
          setError('Failed to connect to Octane LiveLink');
        }
      } catch (error) {
        console.error('❌ Auto-connect error:', error);
        setError(error instanceof Error ? error.message : 'Connection failed');
        setConnected(false);
      } finally {
        setConnecting(false);
      }
    };

    autoConnect();
  }, []);

  return <MainLayout />;
}

function App() {
  return (
    <QueryClientProvider client={queryClient}>
      <AppContent />
    </QueryClientProvider>
  );
}

export default App;
