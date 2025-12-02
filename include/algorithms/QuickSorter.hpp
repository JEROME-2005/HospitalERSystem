#ifndef QUICK_SORTER_HPP
#define QUICK_SORTER_HPP

#include "../core/Patient.hpp"
#include "RadixSorter.hpp"  // For SortPerformance struct
#include <vector>
#include <string>
#include <functional>

namespace Algorithms {

    /**
     * Pivot Selection Strategy
     */
    enum class PivotStrategy {
        FIRST,          // First element as pivot
        LAST,           // Last element as pivot
        MIDDLE,         // Middle element as pivot
        RANDOM,         // Random element as pivot
        MEDIAN_OF_THREE // Median of first, middle, last
    };

    /**
     * QuickSorter Class
     * 
     * Implements QuickSort for patient sorting and comparison with RadixSort.
     * Provides multiple pivot selection strategies.
     * 
     * Time Complexity:
     * - Average Case: O(n log n)
     * - Best Case: O(n log n)
     * - Worst Case: O(n²) - when array is already sorted and using first/last pivot
     * 
     * Space Complexity: O(log n) average for recursion stack
     * 
     * Used for LO4: Comparing RadixSort vs QuickSort performance
     */
    class QuickSorter {
    private:
        SortPerformance lastPerformance;
        bool trackPerformance;
        PivotStrategy pivotStrategy;

    public:
        // Constructors
        QuickSorter(PivotStrategy strategy = PivotStrategy::MEDIAN_OF_THREE);
        
        // Destructor
        ~QuickSorter();

        // Core QuickSort Operations
        
        // Sort patients by severity score
        void quickSortPatientsBySeverity(std::vector<Core::Patient>& patients);
        
        // Sort patients by ID
        void quickSortPatientsByID(std::vector<Core::Patient>& patients);
        
        // Sort patients by arrival time
        void quickSortPatientsByArrival(std::vector<Core::Patient>& patients);
        
        // Generic template quicksort
        template<typename T>
        void quickSort(std::vector<T>& arr);
        
        template<typename T, typename Compare>
        void quickSort(std::vector<T>& arr, Compare comp);

        // Sort with custom comparator
        void quickSortCustom(std::vector<Core::Patient>& patients,
                            std::function<bool(const Core::Patient&, 
                                               const Core::Patient&)> comparator);

        // Pivot Strategy Management
        void setPivotStrategy(PivotStrategy strategy) { pivotStrategy = strategy; }
        PivotStrategy getPivotStrategy() const { return pivotStrategy; }
        std::string getPivotStrategyString() const;

        // Performance Tracking
        void enablePerformanceTracking(bool enable) { trackPerformance = enable; }
        SortPerformance getLastPerformance() const { return lastPerformance; }

        // Algorithm Comparison (LO4)
        static void compareWithRadixSort(std::vector<Core::Patient>& patients);
        static std::string generateComparisonReport(const std::vector<SortPerformance>& results);

    private:
        // Core QuickSort Implementation
        template<typename T>
        void quickSortHelper(std::vector<T>& arr, int low, int high);
        
        template<typename T, typename Compare>
        void quickSortHelper(std::vector<T>& arr, int low, int high, Compare comp);
        
        // Partition Functions
        template<typename T>
        int partition(std::vector<T>& arr, int low, int high);
        
        template<typename T, typename Compare>
        int partition(std::vector<T>& arr, int low, int high, Compare comp);
        
        // Pivot Selection
        template<typename T>
        int selectPivot(std::vector<T>& arr, int low, int high);
        
        template<typename T>
        int medianOfThree(std::vector<T>& arr, int low, int high);

        // Utility
        template<typename T>
        void swap(std::vector<T>& arr, int i, int j);
    };

    // ==================== TEMPLATE IMPLEMENTATIONS ====================

    template<typename T>
    void QuickSorter::quickSort(std::vector<T>& arr) {
        if (arr.size() <= 1) return;
        
        if (trackPerformance) {
            lastPerformance = SortPerformance();
            lastPerformance.algorithmName = "QuickSort";
            lastPerformance.inputSize = arr.size();
        }
        
        quickSortHelper(arr, 0, arr.size() - 1);
    }

    template<typename T, typename Compare>
    void QuickSorter::quickSort(std::vector<T>& arr, Compare comp) {
        if (arr.size() <= 1) return;
        
        if (trackPerformance) {
            lastPerformance = SortPerformance();
            lastPerformance.algorithmName = "QuickSort";
            lastPerformance.inputSize = arr.size();
        }
        
        quickSortHelper(arr, 0, arr.size() - 1, comp);
    }

    template<typename T>
    void QuickSorter::quickSortHelper(std::vector<T>& arr, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(arr, low, high);
            quickSortHelper(arr, low, pivotIndex - 1);
            quickSortHelper(arr, pivotIndex + 1, high);
        }
    }

    template<typename T, typename Compare>
    void QuickSorter::quickSortHelper(std::vector<T>& arr, int low, int high, Compare comp) {
        if (low < high) {
            int pivotIndex = partition(arr, low, high, comp);
            quickSortHelper(arr, low, pivotIndex - 1, comp);
            quickSortHelper(arr, pivotIndex + 1, high, comp);
        }
    }

    template<typename T>
    int QuickSorter::partition(std::vector<T>& arr, int low, int high) {
        int pivotIdx = selectPivot(arr, low, high);
        swap(arr, pivotIdx, high);
        
        T pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (trackPerformance) lastPerformance.comparisons++;
            
            if (arr[j] < pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        
        swap(arr, i + 1, high);
        return i + 1;
    }

    template<typename T, typename Compare>
    int QuickSorter::partition(std::vector<T>& arr, int low, int high, Compare comp) {
        int pivotIdx = selectPivot(arr, low, high);
        swap(arr, pivotIdx, high);
        
        T pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (trackPerformance) lastPerformance.comparisons++;
            
            if (comp(arr[j], pivot)) {
                i++;
                swap(arr, i, j);
            }
        }
        
        swap(arr, i + 1, high);
        return i + 1;
    }

    template<typename T>
    int QuickSorter::selectPivot(std::vector<T>& arr, int low, int high) {
        switch (pivotStrategy) {
            case PivotStrategy::FIRST:
                return low;
            case PivotStrategy::LAST:
                return high;
            case PivotStrategy::MIDDLE:
                return low + (high - low) / 2;
            case PivotStrategy::RANDOM:
                return low + (rand() % (high - low + 1));
            case PivotStrategy::MEDIAN_OF_THREE:
                return medianOfThree(arr, low, high);
            default:
                return high;
        }
    }

    template<typename T>
    int QuickSorter::medianOfThree(std::vector<T>& arr, int low, int high) {
        int mid = low + (high - low) / 2;
        
        if (arr[low] > arr[mid]) swap(arr, low, mid);
        if (arr[low] > arr[high]) swap(arr, low, high);
        if (arr[mid] > arr[high]) swap(arr, mid, high);
        
        return mid;
    }

    template<typename T>
    void QuickSorter::swap(std::vector<T>& arr, int i, int j) {
        if (i != j) {
            if (trackPerformance) lastPerformance.swaps++;
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

} // namespace Algorithms

#endif // QUICK_SORTER_HPP