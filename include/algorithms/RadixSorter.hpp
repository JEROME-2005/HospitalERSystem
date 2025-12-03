#ifndef RADIX_SORTER_HPP
#define RADIX_SORTER_HPP

#include "../core/Patient.hpp"
#include <vector>
#include <string>

class RadixSorter {
public:
    // Radix Sort for patient IDs - O(nk) complexity where k is ID length
    static void sortPatientsByID(std::vector<Patient>& patients);
    
    // Helper functions
    static int getMaxDigits(const std::vector<Patient>& patients);
    static void countingSortByPosition(std::vector<Patient>& patients, int position);
    
    // For numeric IDs
    static void radixSortNumeric(std::vector<int>& arr);
    
    // Display
    static void displaySortedPatients(const std::vector<Patient>& patients);
};

#endif // RADIX_SORTER_HPP