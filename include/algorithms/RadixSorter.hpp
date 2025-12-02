// include/algorithms/RadixSorter.hpp
#ifndef RADIX_SORTER_HPP
#define RADIX_SORTER_HPP

#include "../utils/CommonTypes.hpp"
#include "../core/Patient.hpp"

namespace HEROS {
namespace Algorithms {

/**
 * RadixSorter - Radix Sort for Patient IDs
 * 
 * Time Complexity: O(n * k) where k = number of digits
 * Space Complexity: O(n + k)
 * 
 * Optimal for fixed-length ID strings like "PAT-0001"
 */
class RadixSorter {
private:
    PerformanceMetrics lastMetrics;
    
    // Helper for counting sort on a specific character position
    static void countingSortByPosition(std::vector<Patient>& patients, int position);
    static int getMaxIDLength(const std::vector<Patient>& patients);
    static int charToIndex(char c);

public:
    // Constructors
    RadixSorter() = default;
    ~RadixSorter() = default;
    
    // Sort patients by ID using Radix Sort
    void sortByID(std::vector<Patient>& patients);
    
    // Sort patients by severity score
    void sortBySeverity(std::vector<Patient>& patients);
    
    // Performance metrics
    PerformanceMetrics getLastOperationMetrics() const { return lastMetrics; }
    
    // Utility
    static bool isSorted(const std::vector<Patient>& patients);
};

} // namespace Algorithms
} // namespace HEROS

#endif // RADIX_SORTER_HPP