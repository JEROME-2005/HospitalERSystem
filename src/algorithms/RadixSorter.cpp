// src/algorithms/RadixSorter.cpp
#include "../../include/algorithms/RadixSorter.hpp"

namespace HEROS {
namespace Algorithms {

int RadixSorter::charToIndex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    if (c == '-') return 36;
    if (c == '_') return 37;
    return 38; // Other characters
}

int RadixSorter::getMaxIDLength(const std::vector<Patient>& patients) {
    int maxLen = 0;
    for (const auto& patient : patients) {
        int len = static_cast<int>(patient.getPatientID().length());
        if (len > maxLen) maxLen = len;
    }
    return maxLen;
}

void RadixSorter::countingSortByPosition(std::vector<Patient>& patients, int position) {
    const int ALPHABET_SIZE = 40; // 0-9, A-Z, -, _, others
    int n = static_cast<int>(patients.size());
    
    std::vector<Patient> output(n);
    std::vector<int> count(ALPHABET_SIZE, 0);
    
    // Count occurrences
    for (const auto& patient : patients) {
        std::string id = patient.getPatientID();
        int charIndex = (position < static_cast<int>(id.length())) 
                        ? charToIndex(id[position]) : 0;
        count[charIndex]++;
    }
    
    // Calculate cumulative count
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array (traverse in reverse for stability)
    for (int i = n - 1; i >= 0; i--) {
        std::string id = patients[i].getPatientID();
        int charIndex = (position < static_cast<int>(id.length())) 
                        ? charToIndex(id[position]) : 0;
        output[count[charIndex] - 1] = patients[i];
        count[charIndex]--;
    }
    
    patients = output;
}

void RadixSorter::sortByID(std::vector<Patient>& patients) {
    auto startTime = std::chrono::high_resolution_clock::now();
    
    if (patients.size() <= 1) {
        lastMetrics.algorithmName = "Radix Sort";
        lastMetrics.complexity = "O(n*k)";
        lastMetrics.operationsCount = 0;
        return;
    }
    
    int maxLen = getMaxIDLength(patients);
    size_t operationsCount = 0;
    
    // LSD Radix Sort: process from rightmost character to leftmost
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        countingSortByPosition(patients, pos);
        operationsCount += patients.size();
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    
    lastMetrics.algorithmName = "Radix Sort";
    lastMetrics.complexity = "O(n*k) where k=" + std::to_string(maxLen);
    lastMetrics.executionTimeMs = std::chrono::duration<double, std::milli>(
        endTime - startTime).count();
    lastMetrics.operationsCount = operationsCount;
}

void RadixSorter::sortBySeverity(std::vector<Patient>& patients) {
    auto startTime = std::chrono::high_resolution_clock::now();
    
    if (patients.size() <= 1) return;
    
    // For severity scores (0-100), use counting sort directly
    const int MAX_SEVERITY = 200;
    std::vector<std::vector<Patient>> buckets(MAX_SEVERITY);
    
    // Put patients into buckets
    for (const auto& patient : patients) {
        int score = std::min(patient.getSeverityScore(), MAX_SEVERITY - 1);
        buckets[score].push_back(patient);
    }
    
    // Collect from buckets (highest severity first)
    patients.clear();
    for (int i = MAX_SEVERITY - 1; i >= 0; i--) {
        for (const auto& patient : buckets[i]) {
            patients.push_back(patient);
        }
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    
    lastMetrics.algorithmName = "Counting Sort (Severity)";
    lastMetrics.complexity = "O(n + k)";
    lastMetrics.executionTimeMs = std::chrono::duration<double, std::milli>(
        endTime - startTime).count();
}

bool RadixSorter::isSorted(const std::vector<Patient>& patients) {
    for (size_t i = 1; i < patients.size(); i++) {
        if (patients[i].getPatientID() < patients[i-1].getPatientID()) {
            return false;
        }
    }
    return true;
}

} // namespace Algorithms
} // namespace HEROS