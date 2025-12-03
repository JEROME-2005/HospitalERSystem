#ifndef QUICK_SORTER_HPP
#define QUICK_SORTER_HPP

#include "../core/Patient.hpp"
#include <vector>

class QuickSorter {
private:
    static int partition(std::vector<Patient>& patients, int low, int high);
    static void quickSortHelper(std::vector<Patient>& patients, int low, int high);

public:
    // QuickSort for patient IDs - O(n log n) average, O(n²) worst
    static void sortPatientsByID(std::vector<Patient>& patients);
    
    // Display
    static void displaySortedPatients(const std::vector<Patient>& patients);
};

#endif // QUICK_SORTER_HPP