// include/algorithms/QuickSorter.hpp
#ifndef QUICK_SORTER_HPP
#define QUICK_SORTER_HPP

#include "../utils/CommonTypes.hpp"
#include "../core/Patient.hpp"

namespace HEROS {
namespace Algorithms {

/**
 * QuickSorter - QuickSort Implementation for Comparison
 * 
 * Time Complexity: 
 *   - Average: O(n log n)
 *   - Worst: O(n²)
 * Space Complexity: O(log n) for recursion stack
 * 
 * Used for empirical comparison with Radix Sort (LO4)
 */
class QuickSorter {
private:
    PerformanceMetrics lastMetrics;
    size_t comparisons;
    size_t swaps;
    
    // Partition function
    int partition(std::vector<Patient>& patients, int low, int high, bool byID);
    
    // Recursive quicksort
    void quickSortRecursive(std::vector<Patient>& patients, int low, int high, bool byID);
    
    // Swap helper
    void swap(std::vector<Patient>& patients, int i, int j);

public:
    // Constructors
    QuickSorter();
    ~QuickSorter() = default;
    
    // Sort patients by ID
    void sortByID(std::vector<Patient>& patients);
    
    // Sort patients by severity
    void sortBySeverity(std::vector<Patient>& patients);
    
    // Performance metrics
    PerformanceMetrics getLastOperationMetrics() const { return lastMetrics; }
    size_t getLastComparisons() const { return comparisons; }
    size_t getLastSwaps() const { return swaps; }
};

} // namespace Algorithms
} // namespace HEROS

#endif // QUICK_SORTER_HPP