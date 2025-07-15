using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Media;
using Avalonia.Threading;
using Grpc.Net.Client;
using System;
using System.Diagnostics;
using System.Numerics;
using System.Threading.Tasks;
using System.Threading;

namespace AvaloniaGrpcTest;

public partial class MainWindow : Window
{
    private GrpcChannel? _channel;
    private Octaneapi.CameraControl.CameraControlClient? _cameraClient;
    private Livelinkapi.LiveLinkService.LiveLinkServiceClient? _livelinkClient;
    private bool _isConnected = false;
    
    // Performance tracking
    private int _requestCount = 0;
    private long _totalResponseTime = 0;
    private string _lastError = "None";
    
    // Camera state
    private Vector3 _cameraPosition = new Vector3(0, 0, 5);
    private Vector3 _cameraTarget = new Vector3(0, 0, 0);
    private int _meshCount = 0;
    
    // Real-time sync
    private Timer? _syncTimer;
    private readonly object _syncLock = new object();
    
    // LiveLink debug logging
    private int _liveLinkLogLines = 1;
    private int _liveLinkErrors = 0;
    private int _liveLinkSyncCount = 0;
    private DateTime _lastSyncTime = DateTime.Now;
    private Timer? _performanceTimer;

    public MainWindow()
    {
        InitializeComponent();
        InitializeApplication();
    }

    private void InitializeApplication()
    {
        LogMessage("🔥 Octane gRPC Testbed - Professional Edition");
        LogMessage("Ready to connect to Octane LiveLink service...");
        
        // Initialize LiveLink debug log
        LogLiveLinkMessage("🔥 Octane gRPC Testbed - Professional Edition", "System");
        LogLiveLinkMessage("Ready to connect to Octane LiveLink service...", "System");
        
        UpdateCameraUI();
        UpdatePerformanceUI();
        StartPerformanceMonitoring();
    }

    private void LogMessage(string message)
    {
        var timestamp = DateTime.Now.ToString("HH:mm:ss.fff");
        var logEntry = $"[{timestamp}] {message}\n";
        
        Dispatcher.UIThread.InvokeAsync(() =>
        {
            if (LogTextBox != null)
            {
                LogTextBox.Text += logEntry;
                // Auto-scroll to bottom
                if (LogScrollViewer != null)
                {
                    LogScrollViewer.ScrollToEnd();
                }
            }
        });
    }

    private void LogLiveLinkMessage(string message, string category = "Info", bool isError = false)
    {
        var timestamp = DateTime.Now.ToString("HH:mm:ss.fff");
        var icon = GetLogIcon(category, isError);
        var logEntry = $"{icon} [{timestamp}] {message}\n";
        
        if (isError) _liveLinkErrors++;
        _liveLinkLogLines++;
        
        Dispatcher.UIThread.InvokeAsync(() =>
        {
            if (LiveLinkLogTextBox != null)
            {
                LiveLinkLogTextBox.Text += logEntry;
                
                // Auto-scroll to bottom
                if (LiveLinkLogScrollViewer != null)
                {
                    LiveLinkLogScrollViewer.ScrollToEnd();
                }
            }
            
            // Update log stats
            UpdateLiveLinkLogStats();
            
            // Update error count in performance overlay
            if (LiveLinkErrorsText != null)
            {
                LiveLinkErrorsText.Text = $"Errors: {_liveLinkErrors}";
            }
        });
        
        // Also log to verbose if enabled
        if (VerboseLoggingCheckBox?.IsChecked == true)
        {
            LogMessage($"[LiveLink] {message}");
        }
    }

    private string GetLogIcon(string category, bool isError)
    {
        if (isError) return "❌";
        
        return category switch
        {
            "System" => "🗒️",
            "Connection" => "🔌",
            "Camera" => "📷",
            "Sync" => "🔄",
            "Success" => "✅",
            "Warning" => "⚠️",
            "Performance" => "📊",
            _ => "🗒️"
        };
    }

    private void UpdateLiveLinkLogStats()
    {
        if (LogStatsText != null)
        {
            LogStatsText.Text = $"Lines: {_liveLinkLogLines}";
        }
    }

    private async void ConnectButton_Click(object? sender, RoutedEventArgs e)
    {
        if (_isConnected)
        {
            await DisconnectAsync();
        }
        else
        {
            await ConnectAsync();
        }
    }

    private async Task ConnectAsync()
    {
        var stopwatch = Stopwatch.StartNew();
        try
        {
            var serverAddress = ServerTextBox?.Text ?? "localhost:51022";
            LogMessage($"🔌 Connecting to {serverAddress}...");
            LogLiveLinkMessage($"Connecting to {serverAddress}...", "Connection");

            // Create gRPC channel
            _channel = GrpcChannel.ForAddress($"http://{serverAddress}");
            
            // Create clients
            _cameraClient = new Octaneapi.CameraControl.CameraControlClient(_channel);
            _livelinkClient = new Livelinkapi.LiveLinkService.LiveLinkServiceClient(_channel);

            // Test connection with a simple call
            var healthRequest = new Google.Protobuf.WellKnownTypes.Empty();
            var response = await _cameraClient.GetCameraPositionAsync(healthRequest);
            
            _isConnected = true;
            UpdateConnectionStatus();
            UpdatePerformanceStats(stopwatch.ElapsedMilliseconds, null);
            LogMessage("✅ Connected successfully!");
            LogLiveLinkMessage("✅ Connected to Octane LiveLink successfully!", "Success");
            LogLiveLinkMessage($"Initial camera position: ({response?.Position?.X:F2}, {response?.Position?.Y:F2}, {response?.Position?.Z:F2})", "Camera");
            
            // Update camera position from response
            if (response?.Position != null)
            {
                _cameraPosition = new Vector3(response.Position.X, response.Position.Y, response.Position.Z);
                UpdateCameraUI();
            }
            
            // Start real-time sync if enabled
            if (RealTimeCheckBox?.IsChecked == true)
            {
                StartRealTimeSync();
            }
        }
        catch (Exception ex)
        {
            UpdatePerformanceStats(stopwatch.ElapsedMilliseconds, ex.Message);
            LogMessage($"❌ Connection failed: {ex.Message}");
            LogLiveLinkMessage($"Connection failed: {ex.Message}", "Connection", true);
            await DisconnectAsync();
        }
    }

    private async Task DisconnectAsync()
    {
        try
        {
            StopRealTimeSync();
            
            if (_channel != null)
            {
                await _channel.ShutdownAsync();
                _channel.Dispose();
                _channel = null;
            }

            _cameraClient = null;
            _livelinkClient = null;
            _isConnected = false;
            UpdateConnectionStatus();
            LogMessage("🔌 Disconnected");
            LogLiveLinkMessage("Disconnected from Octane LiveLink", "Connection");
        }
        catch (Exception ex)
        {
            LogMessage($"❌ Disconnect error: {ex.Message}");
            LogLiveLinkMessage($"Disconnect error: {ex.Message}", "Connection", true);
        }
    }

    private void StartPerformanceMonitoring()
    {
        _performanceTimer = new Timer(_ =>
        {
            Dispatcher.UIThread.InvokeAsync(() =>
            {
                // Update FPS (simulated for now - would be real in OpenGL implementation)
                if (LiveLinkFpsText != null)
                {
                    var fps = _isConnected ? 60 : 0;
                    LiveLinkFpsText.Text = $"FPS: {fps}";
                }
                
                // Update sync rate
                if (LiveLinkSyncText != null)
                {
                    var syncRate = CalculateSyncRate();
                    LiveLinkSyncText.Text = $"Sync: {syncRate:F1}/s";
                }
            });
        }, null, TimeSpan.Zero, TimeSpan.FromMilliseconds(500)); // Update every 500ms
    }

    private double CalculateSyncRate()
    {
        var now = DateTime.Now;
        var timeDiff = (now - _lastSyncTime).TotalSeconds;
        if (timeDiff > 0 && _liveLinkSyncCount > 0)
        {
            return _liveLinkSyncCount / timeDiff;
        }
        return 0.0;
    }

    private void UpdateConnectionStatus()
    {
        Dispatcher.UIThread.InvokeAsync(() =>
        {
            // Update status indicator
            if (StatusIndicator != null)
            {
                StatusIndicator.Fill = _isConnected ? Brushes.Green : Brushes.Red;
            }
            
            if (StatusText != null)
            {
                StatusText.Text = _isConnected ? "Connected" : "Disconnected";
            }

            if (ConnectButton != null)
            {
                ConnectButton.Content = _isConnected ? "Disconnect" : "Connect";
            }

            // Enable/disable all API buttons
            var isEnabled = _isConnected;
            EnableButton(GetCameraButton, isEnabled);
            EnableButton(SetCameraButton, isEnabled);
            EnableButton(ResetCameraButton, isEnabled);
            EnableButton(GetMeshesButton, isEnabled);
            EnableButton(ApiGetCameraButton, isEnabled);
            EnableButton(ApiSetCameraButton, isEnabled);
            EnableButton(ApiGetMeshesButton, isEnabled);
            EnableButton(ApiGetRenderInfoButton, isEnabled);
            EnableButton(PingServerButton, isEnabled);
        });
    }

    private void EnableButton(Button? button, bool enabled)
    {
        if (button != null) button.IsEnabled = enabled;
    }

    private void UpdateCameraUI()
    {
        Dispatcher.UIThread.InvokeAsync(() =>
        {
            if (CameraPosX != null) CameraPosX.Text = _cameraPosition.X.ToString("F2");
            if (CameraPosY != null) CameraPosY.Text = _cameraPosition.Y.ToString("F2");
            if (CameraPosZ != null) CameraPosZ.Text = _cameraPosition.Z.ToString("F2");
            
            if (CameraTargetX != null) CameraTargetX.Text = _cameraTarget.X.ToString("F2");
            if (CameraTargetY != null) CameraTargetY.Text = _cameraTarget.Y.ToString("F2");
            if (CameraTargetZ != null) CameraTargetZ.Text = _cameraTarget.Z.ToString("F2");
        });
    }

    private void UpdatePerformanceStats(long responseTime, string? error)
    {
        _requestCount++;
        _totalResponseTime += responseTime;
        if (error != null) _lastError = error;
        
        UpdatePerformanceUI();
    }

    private void UpdatePerformanceUI()
    {
        Dispatcher.UIThread.InvokeAsync(() =>
        {
            if (RequestCountText != null)
                RequestCountText.Text = $"Requests: {_requestCount}";
            
            if (AvgResponseTimeText != null)
            {
                var avgTime = _requestCount > 0 ? _totalResponseTime / _requestCount : 0;
                AvgResponseTimeText.Text = $"Avg Response: {avgTime}ms";
            }
            
            if (LastErrorText != null)
                LastErrorText.Text = $"Last Error: {_lastError}";
            
            if (MeshCountText != null)
                MeshCountText.Text = $"Meshes: {_meshCount}";
        });
    }

    private async void GetCameraButton_Click(object? sender, RoutedEventArgs e)
    {
        await ExecuteApiCall("GetCameraPosition", async () =>
        {
            var request = new Google.Protobuf.WellKnownTypes.Empty();
            var response = await _cameraClient!.GetCameraPositionAsync(request);
            
            if (response?.Position != null)
            {
                _cameraPosition = new Vector3(response.Position.X, response.Position.Y, response.Position.Z);
                UpdateCameraUI();
                LogLiveLinkMessage($"Camera retrieved: ({response.Position.X:F2}, {response.Position.Y:F2}, {response.Position.Z:F2})", "Camera");
                _liveLinkSyncCount++;
            }
            
            return $"Position: ({response?.Position?.X:F2}, {response?.Position?.Y:F2}, {response?.Position?.Z:F2})";
        });
    }

    private async void SetCameraButton_Click(object? sender, RoutedEventArgs e)
    {
        await ExecuteApiCall("SetCameraPosition", async () =>
        {
            // Get values from UI
            if (float.TryParse(CameraPosX?.Text, out float x) &&
                float.TryParse(CameraPosY?.Text, out float y) &&
                float.TryParse(CameraPosZ?.Text, out float z))
            {
                var request = new Octaneapi.CameraPositionRequest
                {
                    Position = new Octaneapi.Vector3 { X = x, Y = y, Z = z }
                };
                
                var response = await _cameraClient!.SetCameraPositionAsync(request);
                _cameraPosition = new Vector3(x, y, z);
                LogLiveLinkMessage($"Camera set to: ({x:F2}, {y:F2}, {z:F2})", "Camera");
                _liveLinkSyncCount++;
                
                return $"Camera set to: ({x:F2}, {y:F2}, {z:F2})";
            }
            else
            {
                throw new ArgumentException("Invalid camera position values");
            }
        });
    }

    private void ResetCameraButton_Click(object? sender, RoutedEventArgs e)
    {
        _cameraPosition = new Vector3(0, 0, 5);
        _cameraTarget = new Vector3(0, 0, 0);
        UpdateCameraUI();
        LogLiveLinkMessage("Camera reset to default position", "Camera");
        SetCameraButton_Click(sender, e);
    }

    private async void GetMeshesButton_Click(object? sender, RoutedEventArgs e)
    {
        await ExecuteApiCall("GetMeshes", async () =>
        {
            var request = new Livelinkapi.Empty();
            var response = await _livelinkClient!.GetMeshesAsync(request);
            
            _meshCount = response.Meshes.Count;
            UpdatePerformanceUI();
            
            var result = $"Found {response.Meshes.Count} meshes:";
            foreach (var mesh in response.Meshes)
            {
                result += $"\n  - {mesh.Name} (ID: {mesh.Id})";
            }
            
            return result;
        });
    }

    private async void GetRenderInfoButton_Click(object? sender, RoutedEventArgs e)
    {
        await ExecuteApiCall("GetRenderInfo", async () =>
        {
            // This would be a new API call - placeholder for now
            await Task.Delay(100); // Simulate API call
            return "Render info: 1920x1080, 64 samples, GPU rendering";
        });
    }

    private async void PingServerButton_Click(object? sender, RoutedEventArgs e)
    {
        await ExecuteApiCall("Ping", async () =>
        {
            var request = new Google.Protobuf.WellKnownTypes.Empty();
            var response = await _cameraClient!.GetCameraPositionAsync(request);
            return "Server is responding";
        });
    }

    private async Task ExecuteApiCall(string apiName, Func<Task<string>> apiCall)
    {
        if (!_isConnected || _cameraClient == null) return;

        var stopwatch = Stopwatch.StartNew();
        try
        {
            LogMessage($"📤 {apiName} request...");
            var result = await apiCall();
            UpdatePerformanceStats(stopwatch.ElapsedMilliseconds, null);
            LogMessage($"📥 {apiName} response: {result}");
        }
        catch (Exception ex)
        {
            UpdatePerformanceStats(stopwatch.ElapsedMilliseconds, ex.Message);
            LogMessage($"❌ {apiName} failed: {ex.Message}");
        }
    }

    private void StartRealTimeSync()
    {
        if (_syncTimer != null) return;
        
        _syncTimer = new Timer(_ =>
        {
            if (_isConnected && AutoSyncCheckBox?.IsChecked == true)
            {
                Task.Run(() => GetCameraButton_Click(null, new RoutedEventArgs()));
            }
        }, null, TimeSpan.Zero, TimeSpan.FromMilliseconds(100)); // 10 FPS
        
        LogMessage("🔄 Real-time sync started");
    }

    private void StopRealTimeSync()
    {
        if (_syncTimer != null)
        {
            _syncTimer.Dispose();
            _syncTimer = null;
            LogMessage("⏹️ Real-time sync stopped");
        }
    }

    private void ClearLogButton_Click(object? sender, RoutedEventArgs e)
    {
        if (LogTextBox != null)
        {
            LogTextBox.Text = "";
            LogMessage("🗑️ Log cleared");
        }
    }

    private void LiveLinkClearLogButton_Click(object? sender, RoutedEventArgs e)
    {
        if (LiveLinkLogTextBox != null)
        {
            LiveLinkLogTextBox.Text = "🗒️ [System] LiveLink debug log cleared\n";
            _liveLinkLogLines = 1;
            _liveLinkErrors = 0;
            UpdateLiveLinkLogStats();
            
            // Reset error count in performance overlay
            if (LiveLinkErrorsText != null)
            {
                LiveLinkErrorsText.Text = "Errors: 0";
            }
        }
    }

    private async void LiveLinkSaveLogButton_Click(object? sender, RoutedEventArgs e)
    {
        try
        {
            if (LiveLinkLogTextBox?.Text != null)
            {
                var timestamp = DateTime.Now.ToString("yyyyMMdd_HHmmss");
                var filename = $"LiveLink_Log_{timestamp}.txt";
                var desktopPath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
                var filepath = System.IO.Path.Combine(desktopPath, filename);
                
                await System.IO.File.WriteAllTextAsync(filepath, LiveLinkLogTextBox.Text);
                LogLiveLinkMessage($"Log saved to: {filepath}", "System");
            }
        }
        catch (Exception ex)
        {
            LogLiveLinkMessage($"Failed to save log: {ex.Message}", "System", true);
        }
    }

    protected override void OnClosed(EventArgs e)
    {
        // Cleanup timers
        _syncTimer?.Dispose();
        _performanceTimer?.Dispose();
        
        // Cleanup gRPC channel
        if (_channel != null)
        {
            Task.Run(async () => await _channel.ShutdownAsync());
        }
        
        base.OnClosed(e);
    }
}