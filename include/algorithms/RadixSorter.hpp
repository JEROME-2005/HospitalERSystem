#ifndef RADIX_SORTER_HPP
#define RADIX_SORTER_HPP

#include "../core/Patient.hpp"
#include <vector>
#include <string>
#include <map>

namespace Algorithms {

    /**
     * Sorting Performance Result
     */
    struct SortPerformance {
        double timeTakenMs;
        int comparisons;
        int swaps;
        std::string algorithmName;
        int inputSize;

        SortPerformance() : timeTakenMs(0), comparisons(0), swaps(0), inputSize(0) {}
    };

    /**
     * RadixSorter Class
     * 
     * Implements Radix Sort for patient ID processing.
     * Optimized for fixed-length alphanumeric IDs (e.g., "ICU-005", "WARD-012").
     * 
     * Time Complexity: O(nk) where:
     *   - n = number of elements
     *   - k = number of digits/characters in the key
     * 
     * Space Complexity: O(n + k)
     * 
     * Advantages over comparison sorts:
     * - Linear time for fixed-length keys
     * - Stable sorting (maintains relative order of equal elements)
     * - Faster than O(n log n) sorts for large datasets with small k
     */
    class RadixSorter {
    private:
        SortPerformance lastPerformance;
        bool trackPerformance;

    public:
        // Constructors
        RadixSorter();
        
        // Destructor
        ~RadixSorter();

        // Core Radix Sort Operations
        
        // Sort patient IDs (alphanumeric)
        void radixSortPatients(std::vector<Core::Patient>& patients);
        
        // Sort by numeric portion of ID
        void radixSortByNumericID(std::vector<Core::Patient>& patients);
        
        // Sort by ward prefix (e.g., ICU, WARD, ER)
        void radixSortByWard(std::vector<Core::Patient>& patients);
        
        // Generic radix sort for strings
        void radixSortStrings(std::vector<std::string>& strings);
        
        // Generic radix sort for integers
        void radixSortIntegers(std::vector<int>& numbers);

        // LSD (Least Significant Digit) Radix Sort
        void lsdRadixSort(std::vector<std::string>& strings);
        
        // MSD (Most Significant Digit) Radix Sort
        void msdRadixSort(std::vector<std::string>& strings);

        // Performance Tracking
        void enablePerformanceTracking(bool enable) { trackPerformance = enable; }
        SortPerformance getLastPerformance() const { return lastPerformance; }
        
        // Utility Methods
        static int getMaxDigits(const std::vector<int>& numbers);
        static int getMaxLength(const std::vector<std::string>& strings);
        static int extractNumericPart(const std::string& patientID);
        static std::string extractWardPrefix(const std::string& patientID);

    private:
        // Helper Methods
        void countingSortByDigit(std::vector<int>& numbers, int exp);
        void countingSortByCharPosition(std::vector<std::string>& strings, int position);
        void countingSortPatientsByDigit(std::vector<Core::Patient>& patients, int position);
    };

} // namespace Algorithms

#endif // RADIX_SORTER_HPP