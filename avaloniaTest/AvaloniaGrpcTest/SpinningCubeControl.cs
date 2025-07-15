using System;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Media;
using Avalonia.Threading;
using Avalonia.Animation;

namespace AvaloniaGrpcTest;

public class SpinningCubeControl : UserControl
{
    private Canvas _cubeCanvas;
    private DispatcherTimer _animationTimer;
    private double _rotation = 0.0;

    public SpinningCubeControl()
    {
        InitializeCube();
        StartAnimation();
    }

    private void InitializeCube()
    {
        _cubeCanvas = new Canvas
        {
            Width = 200,
            Height = 200,
            HorizontalAlignment = Avalonia.Layout.HorizontalAlignment.Center,
            VerticalAlignment = Avalonia.Layout.VerticalAlignment.Center
        };

        // Create cube faces with 3D effect
        CreateCubeFaces();
        
        Content = _cubeCanvas;
    }

    private void CreateCubeFaces()
    {
        // Back face (darker, offset)
        var backFace = new Border
        {
            Width = 100,
            Height = 100,
            Background = new SolidColorBrush(Color.FromRgb(180, 80, 40)),
            BorderBrush = new SolidColorBrush(Colors.Gray),
            BorderThickness = new Thickness(1),
            RenderTransformOrigin = new RelativePoint(0.5, 0.5, RelativeUnit.Relative)
        };
        Canvas.SetLeft(backFace, 30);
        Canvas.SetTop(backFace, 30);
        _cubeCanvas.Children.Add(backFace);

        // Top face (parallelogram effect)
        var topFace = new Polygon
        {
            Fill = new SolidColorBrush(Color.FromRgb(255, 140, 80)),
            Stroke = new SolidColorBrush(Colors.White),
            StrokeThickness = 1,
            Points = new[]
            {
                new Point(50, 50),   // Front-left
                new Point(150, 50),  // Front-right
                new Point(130, 30),  // Back-right
                new Point(30, 30)    // Back-left
            },
            RenderTransformOrigin = new RelativePoint(0.5, 0.5, RelativeUnit.Relative)
        };
        _cubeCanvas.Children.Add(topFace);

        // Right face (parallelogram effect)
        var rightFace = new Polygon
        {
            Fill = new SolidColorBrush(Color.FromRgb(220, 90, 50)),
            Stroke = new SolidColorBrush(Colors.White),
            StrokeThickness = 1,
            Points = new[]
            {
                new Point(150, 50),   // Top-front
                new Point(150, 150),  // Bottom-front
                new Point(130, 130),  // Bottom-back
                new Point(130, 30)    // Top-back
            },
            RenderTransformOrigin = new RelativePoint(0.5, 0.5, RelativeUnit.Relative)
        };
        _cubeCanvas.Children.Add(rightFace);

        // Front face (brightest)
        var frontFace = new Border
        {
            Width = 100,
            Height = 100,
            Background = new SolidColorBrush(Color.FromRgb(255, 107, 53)), // Octane orange
            BorderBrush = new SolidColorBrush(Colors.White),
            BorderThickness = new Thickness(2),
            RenderTransformOrigin = new RelativePoint(0.5, 0.5, RelativeUnit.Relative)
        };
        Canvas.SetLeft(frontFace, 50);
        Canvas.SetTop(frontFace, 50);
        _cubeCanvas.Children.Add(frontFace);

        // Center dot for reference
        var centerDot = new Ellipse
        {
            Width = 4,
            Height = 4,
            Fill = new SolidColorBrush(Colors.White)
        };
        Canvas.SetLeft(centerDot, 98);
        Canvas.SetTop(centerDot, 98);
        _cubeCanvas.Children.Add(centerDot);
    }

    private void StartAnimation()
    {
        _animationTimer = new DispatcherTimer
        {
            Interval = TimeSpan.FromMilliseconds(16) // ~60 FPS
        };
        
        _animationTimer.Tick += (s, e) =>
        {
            _rotation += 2.0; // Degrees per frame
            if (_rotation >= 360.0) _rotation = 0.0;
            
            UpdateCubeRotation();
        };
        
        _animationTimer.Start();
    }

    private void UpdateCubeRotation()
    {
        // Apply rotation transform to the entire cube canvas
        var transform = new RotateTransform(_rotation);
        _cubeCanvas.RenderTransform = transform;
        
        // Add slight scaling effect for more dynamic appearance
        var scale = 1.0 + 0.1 * Math.Sin(_rotation * Math.PI / 180.0);
        var scaleTransform = new ScaleTransform(scale, scale);
        
        // Combine transforms
        var transformGroup = new TransformGroup();
        transformGroup.Children.Add(scaleTransform);
        transformGroup.Children.Add(transform);
        
        _cubeCanvas.RenderTransform = transformGroup;
    }

    protected override void OnDetachedFromVisualTree(VisualTreeAttachmentEventArgs e)
    {
        _animationTimer?.Stop();
        base.OnDetachedFromVisualTree(e);
    }
}