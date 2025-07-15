/**
 * ActivityLogger.h
 * Activity logging system matching the HTML interface
 */

#pragma once

// Windows compatibility layer (must come first)
#include "../shared/windows_headers.h"

#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <mutex>

class ActivityLogger {
public:
    enum class LogLevel {
        DEBUG,
        STATUS,
        SUCCESS,
        WARNING,
        ERROR
    };
    
    struct LogEntry {
        std::string timestamp;
        std::string message;
        LogLevel level;
        
        LogEntry(const std::string& msg, LogLevel lvl) 
            : message(msg), level(lvl) {
            // Generate timestamp
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()) % 1000;
            
            std::stringstream ss;
            ss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
            ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
            timestamp = ss.str();
        }
    };
    
private:
    std::vector<LogEntry> logs_;
    size_t maxLogs_ = 1000;
    
public:
    ActivityLogger() = default;
    
    void Log(const std::string& message, LogLevel level = LogLevel::DEBUG) {
        logs_.emplace_back(message, level);
        
        // Keep only the most recent logs
        if (logs_.size() > maxLogs_) {
            logs_.erase(logs_.begin(), logs_.begin() + (logs_.size() - maxLogs_));
        }
    }
    
    const std::vector<LogEntry>& GetLogs() const {
        return logs_;
    }
    
    void Clear() {
        logs_.clear();
    }
    
    void SetMaxLogs(size_t maxLogs) {
        maxLogs_ = maxLogs;
    }
    
    // Export logs to string (for debug export)
    std::string ExportLogs() const {
        std::stringstream ss;
        ss << "Activity Log Export - " << logs_.size() << " entries\n";
        ss << "Generated: " << GetCurrentTimestamp() << "\n\n";
        
        for (const auto& log : logs_) {
            ss << "[" << log.timestamp << "] ";
            
            switch (log.level) {
                case LogLevel::ERROR: ss << "ERROR: "; break;
                case LogLevel::WARNING: ss << "WARNING: "; break;
                case LogLevel::SUCCESS: ss << "SUCCESS: "; break;
                case LogLevel::STATUS: ss << "STATUS: "; break;
                case LogLevel::DEBUG: ss << "DEBUG: "; break;
            }
            
            ss << log.message << "\n";
        }
        
        return ss.str();
    }
    
private:
    std::string GetCurrentTimestamp() const {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};