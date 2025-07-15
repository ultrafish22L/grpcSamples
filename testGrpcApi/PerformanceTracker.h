/**
 * PerformanceTracker.h
 * Performance monitoring system matching the HTML interface
 */

#pragma once

#include <chrono>
#include <deque>

class PerformanceTracker {
private:
    std::chrono::steady_clock::time_point lastFrameTime_;
    std::deque<float> frameTimes_;
    size_t maxSamples_ = 60; // Keep 60 samples for averaging
    
    float fps_ = 0.0f;
    float frameTime_ = 0.0f;
    
public:
    PerformanceTracker() {
        lastFrameTime_ = std::chrono::steady_clock::now();
    }
    
    void Update() {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - lastFrameTime_);
        lastFrameTime_ = now;
        
        float frameTimeMs = elapsed.count() / 1000.0f; // Convert to milliseconds
        frameTimes_.push_back(frameTimeMs);
        
        // Keep only the most recent samples
        if (frameTimes_.size() > maxSamples_) {
            frameTimes_.pop_front();
        }
        
        // Calculate average frame time
        float totalTime = 0.0f;
        for (float time : frameTimes_) {
            totalTime += time;
        }
        
        frameTime_ = totalTime / frameTimes_.size();
        fps_ = 1000.0f / frameTime_; // Convert to FPS
    }
    
    float GetFPS() const { return fps_; }
    float GetFrameTime() const { return frameTime_; }
    
    void Reset() {
        frameTimes_.clear();
        lastFrameTime_ = std::chrono::steady_clock::now();
    }
};