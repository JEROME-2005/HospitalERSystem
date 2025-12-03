#include "../../include/utils/PerformanceMonitor.hpp"
#include <iostream>
#include <iomanip>

std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> PerformanceMonitor::timers;
std::unordered_map<std::string, long long> PerformanceMonitor::durations;

void PerformanceMonitor::startTimer(const std::string& operationName) {
    timers[operationName] = std::chrono::high_resolution_clock::now();
}

long long PerformanceMonitor::stopTimer(const std::string& operationName) {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto startTime = timers[operationName];
    
    long long duration = std::chrono::duration_cast<std::chrono::microseconds>(
        endTime - startTime
    ).count();
    
    durations[operationName] = duration;
    return duration;
}

void PerformanceMonitor::displayReport() {
    std::cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║              PERFORMANCE MONITORING REPORT                 ║\n";
    std::cout << "╠════════════════════════════════════════════════════════════╣\n";
    std::cout << "║ Operation                          Time (μs)      Time (ms) ║\n";
    std::cout << "╠════════════════════════════════════════════════════════════╣\n";
    
    for (const auto& pair : durations) {
        std::cout << "║ " << std::setw(35) << std::left << pair.first 
                  << std::setw(12) << std::right << pair.second 
                  << std::setw(14) << std::fixed << std::setprecision(3) 
                  << (pair.second / 1000.0) << " ║\n";
    }
    
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";
}

void PerformanceMonitor::displayComplexityAnalysis() {
    std::cout << "\n╔═══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║           ALGORITHMIC COMPLEXITY ANALYSIS                     ║\n";
    std::cout << "╠═══════════════════════════════════════════════════════════════╣\n";
    std::cout << "║ Algorithm             Complexity        Implementation        ║\n";
    std::cout << "╠═══════════════════════════════════════════════════════════════╣\n";
    std::cout << "║ Min-Heap Insert       O(log n)          Triage Queue          ║\n";
    std::cout << "║ Min-Heap Extract      O(log n)          Triage Queue          ║\n";
    std::cout << "║ Dijkstra's            O((V+E) log V)    Staff Routing         ║\n";
    std::cout << "║ Kruskal's MST         O(E log E)        Equipment Distrib.    ║\n";
    std::cout << "║ Radix Sort            O(nk)             Patient ID Sort       ║\n";
    std::cout << "║ Quick Sort            O(n log n) avg    Comparison Baseline   ║\n";
    std::cout << "║ Stack Push/Pop        O(1)              Undo System           ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════════════╝\n";
}

void PerformanceMonitor::reset() {
    timers.clear();
    durations.clear();
}