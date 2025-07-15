using Avalonia.Controls;
using Avalonia.Interactivity;
using Grpc.Net.Client;
using System;
using System.Threading.Tasks;

namespace AvaloniaGrpcTest;

public partial class MainWindow : Window
{
    private GrpcChannel? _channel;
    private Octaneapi.CameraControl.CameraControlClient? _cameraClient;
    private Livelinkapi.LiveLinkService.LiveLinkServiceClient? _livelinkClient;
    private bool _isConnected = false;

    public MainWindow()
    {
        InitializeComponent();
        LogMessage("Avalonia gRPC Test Application Started");
        LogMessage("Ready to connect to Octane LiveLink service...");
    }

    private void LogMessage(string message)
    {
        var timestamp = DateTime.Now.ToString("HH:mm:ss.fff");
        var logEntry = $"[{timestamp}] {message}\n";
        
        if (LogTextBox != null)
        {
            LogTextBox.Text += logEntry;
            // Auto-scroll to bottom
            if (LogTextBox.Parent is ScrollViewer scrollViewer)
            {
                scrollViewer.ScrollToEnd();
            }
        }
    }

    private async void ConnectButton_Click(object? sender, RoutedEventArgs e)
    {
        if (_isConnected)
        {
            // Disconnect
            await DisconnectAsync();
        }
        else
        {
            // Connect
            await ConnectAsync();
        }
    }

    private async Task ConnectAsync()
    {
        try
        {
            var serverAddress = ServerTextBox?.Text ?? "localhost:8080";
            LogMessage($"Connecting to {serverAddress}...");

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
            LogMessage("✅ Connected successfully!");
            LogMessage($"Camera response received: {response}");
        }
        catch (Exception ex)
        {
            LogMessage($"❌ Connection failed: {ex.Message}");
            await DisconnectAsync();
        }
    }

    private async Task DisconnectAsync()
    {
        try
        {
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
        }
        catch (Exception ex)
        {
            LogMessage($"❌ Disconnect error: {ex.Message}");
        }
    }

    private void UpdateConnectionStatus()
    {
        if (StatusText != null)
        {
            StatusText.Text = _isConnected ? "Connected" : "Disconnected";
            StatusText.Foreground = _isConnected ? 
                Avalonia.Media.Brushes.Green : Avalonia.Media.Brushes.Red;
        }

        if (ConnectButton != null)
        {
            ConnectButton.Content = _isConnected ? "Disconnect" : "Connect";
        }

        // Enable/disable API buttons
        var isEnabled = _isConnected;
        if (GetCameraButton != null) GetCameraButton.IsEnabled = isEnabled;
        if (SetCameraButton != null) SetCameraButton.IsEnabled = isEnabled;
        if (GetMeshesButton != null) GetMeshesButton.IsEnabled = isEnabled;
    }

    private async void GetCameraButton_Click(object? sender, RoutedEventArgs e)
    {
        if (_cameraClient == null) return;

        try
        {
            LogMessage("📤 Sending GetCameraPosition request...");
            var request = new Google.Protobuf.WellKnownTypes.Empty();
            var response = await _cameraClient.GetCameraPositionAsync(request);
            LogMessage($"📥 GetCameraPosition response: {response}");
        }
        catch (Exception ex)
        {
            LogMessage($"❌ GetCamera failed: {ex.Message}");
        }
    }

    private async void SetCameraButton_Click(object? sender, RoutedEventArgs e)
    {
        if (_cameraClient == null) return;

        try
        {
            LogMessage("📤 Sending SetCameraPosition request...");
            var request = new Octaneapi.CameraPositionRequest
            {
                Position = new Octaneapi.Vector3 { X = 0, Y = 0, Z = 5 }
            };
            var response = await _cameraClient.SetCameraPositionAsync(request);
            LogMessage($"📥 SetCameraPosition response: {response}");
        }
        catch (Exception ex)
        {
            LogMessage($"❌ SetCamera failed: {ex.Message}");
        }
    }

    private async void GetMeshesButton_Click(object? sender, RoutedEventArgs e)
    {
        if (_livelinkClient == null) return;

        try
        {
            LogMessage("📤 Sending GetMeshes request...");
            var request = new Livelinkapi.Empty();
            var response = await _livelinkClient.GetMeshesAsync(request);
            LogMessage($"📥 GetMeshes response: Found {response.Meshes.Count} meshes");
            
            foreach (var mesh in response.Meshes)
            {
                LogMessage($"  - Mesh: {mesh.Name} (ID: {mesh.Id})");
            }
        }
        catch (Exception ex)
        {
            LogMessage($"❌ GetMeshes failed: {ex.Message}");
        }
    }

    private void ClearLogButton_Click(object? sender, RoutedEventArgs e)
    {
        if (LogTextBox != null)
        {
            LogTextBox.Text = "";
            LogMessage("Log cleared");
        }
    }
}