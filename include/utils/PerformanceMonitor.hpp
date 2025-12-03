#ifndef PERFORMANCE_MONITOR_HPP
#define PERFORMANCE_MONITOR_HPP

#include <string>
#include <chrono>
#include <unordered_map>
#include <iostream>

class PerformanceMonitor {
private:
    static std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> timers;
    static std::unordered_map<std::string, long long> durations;

public:
    // Timer operations
    static void startTimer(const std::string& operationName);
    static long long stopTimer(const std::string& operationName);  // Returns duration in microseconds
    
    // Reporting
    static void displayReport();
    static void displayComplexityAnalysis();
    static void reset();
    
    // Specific complexity measurements
    static void measureHeapOperations();
    static void measureDijkstraPerformance();
    static void measureSortingPerformance();
};

#endif // PERFORMANCE_MONITOR_HPP