// src/algorithms/QuickSorter.cpp
#include "../../include/algorithms/QuickSorter.hpp"

namespace HEROS {
namespace Algorithms {

QuickSorter::QuickSorter() : comparisons(0), swaps(0) {}

void QuickSorter::swap(std::vector<Patient>& patients, int i, int j) {
    Patient temp = patients[i];
    patients[i] = patients[j];
    patients[j] = temp;
    swaps++;
}

int QuickSorter::partition(std::vector<Patient>& patients, int low, int high, bool byID) {
    Patient pivot = patients[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        comparisons++;
        
        bool shouldSwap = false;
        if (byID) {
            shouldSwap = patients[j].getPatientID() < pivot.getPatientID();
        } else {
            // For severity, higher severity should come first
            shouldSwap = patients[j].getSeverityScore() > pivot.getSeverityScore();
        }
        
        if (shouldSwap) {
            i++;
            swap(patients, i, j);
        }
    }
    
    swap(patients, i + 1, high);
    return i + 1;
}

void QuickSorter::quickSortRecursive(std::vector<Patient>& patients, int low, int high, bool byID) {
    if (low < high) {
        int pivotIndex = partition(patients, low, high, byID);
        quickSortRecursive(patients, low, pivotIndex - 1, byID);
        quickSortRecursive(patients, pivotIndex + 1, high, byID);
    }
}

void QuickSorter::sortByID(std::vector<Patient>& patients) {
    auto startTime = std::chrono::high_resolution_clock::now();
    
    comparisons = 0;
    swaps = 0;
    
    if (patients.size() > 1) {
        quickSortRecursive(patients, 0, static_cast<int>(patients.size()) - 1, true);
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    
    lastMetrics.algorithmName = "QuickSort";
    lastMetrics.complexity = "O(n log n) average";
    lastMetrics.executionTimeMs = std::chrono::duration<double, std::milli>(
        endTime - startTime).count();
    lastMetrics.operationsCount = comparisons + swaps;
}

void QuickSorter::sortBySeverity(std::vector<Patient>& patients) {
    auto startTime = std::chrono::high_resolution_clock::now();
    
    comparisons = 0;
    swaps = 0;
    
    if (patients.size() > 1) {
        quickSortRecursive(patients, 0, static_cast<int>(patients.size()) - 1, false);
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    
    lastMetrics.algorithmName = "QuickSort (Severity)";
    lastMetrics.complexity = "O(n log n) average";
    lastMetrics.executionTimeMs = std::chrono::duration<double, std::milli>(
        endTime - startTime).count();
    lastMetrics.operationsCount = comparisons + swaps;
}

} // namespace Algorithms
} // namespace HEROS