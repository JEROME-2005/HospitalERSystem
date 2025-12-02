#ifndef PERFORMANCE_MONITOR_HPP
#define PERFORMANCE_MONITOR_HPP

#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <iostream>

namespace Utils {

    /**
     * Timer Result Structure
     */
    struct TimerResult {
        std::string operationName;
        double durationMs;
        double durationUs;
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point endTime;
        bool isRunning;

        TimerResult() : durationMs(0), durationUs(0), isRunning(false) {}
    };

    /**
     * Complexity Analysis Report
     */
    struct ComplexityReport {
        std::string algorithmName;
        std::string theoreticalComplexity;
        double measuredTimeMs;
        int inputSize;
        double timePerOperation;
        std::vector<std::pair<int, double>> dataPoints;  // (input size, time)
        std::string derivedComplexity;

        ComplexityReport() : measuredTimeMs(0), inputSize(0), timePerOperation(0) {}
    };

    /**
     * Memory Usage Structure
     */
    struct MemoryUsage {
        size_t currentBytes;
        size_t peakBytes;
        size_t allocations;
        size_t deallocations;

        MemoryUsage() : currentBytes(0), peakBytes(0), allocations(0), deallocations(0) {}
    };

    /**
     * PerformanceMonitor Class (Singleton)
     * 
     * Provides timing and complexity analysis utilities.
     * Used for measuring algorithm performance and validating complexity claims.
     */
    class PerformanceMonitor {
    private:
        static PerformanceMonitor* instance;
        std::map<std::string, TimerResult> timers;
        std::map<std::string, ComplexityReport> complexityReports;
        std::map<std::string, std::vector<double>> historicalData;
        MemoryUsage memoryUsage;
        bool isEnabled;

        // Private constructor for Singleton
        PerformanceMonitor();

    public:
        // Singleton Access
        static PerformanceMonitor* getInstance();
        static void destroyInstance();

        // Timer Operations
        void startTimer(const std::string& operationName);
        double stopTimer(const std::string& operationName);
        double getElapsedTime(const std::string& operationName) const;
        void resetTimer(const std::string& operationName);
        void resetAllTimers();

        // Complexity Analysis
        void recordDataPoint(const std::string& algorithmName, int inputSize, double timeMs);
        ComplexityReport analyzeAlgorithmPerformance(const std::string& algorithmName);
        std::string estimateComplexity(const std::vector<std::pair<int, double>>& dataPoints);

        // Memory Tracking
        void recordAllocation(size_t bytes);
        void recordDeallocation(size_t bytes);
        MemoryUsage getMemoryUsage() const { return memoryUsage; }
        void resetMemoryTracking();

        // Reporting
        std::string generatePerformanceReport() const;
        std::string generateComplexityReport(const std::string& algorithmName) const;
        void displayAllTimers() const;
        void displayComplexityAnalysis() const;

        // Enable/Disable
        void enable() { isEnabled = true; }
        void disable() { isEnabled = false; }
        bool getIsEnabled() const { return isEnabled; }

        // Utility Methods
        static double getCurrentTimeMs();
        static std::string formatDuration(double milliseconds);
    };

    /**
     * RAII Timer Class
     * Automatically starts timer on construction and stops on destruction
     */
    class ScopedTimer {
    private:
        std::string timerName;
        PerformanceMonitor* monitor;

    public:
        ScopedTimer(const std::string& name);
        ~ScopedTimer();
    };

} // namespace Utils

#endif // PERFORMANCE_MONITOR_HPP