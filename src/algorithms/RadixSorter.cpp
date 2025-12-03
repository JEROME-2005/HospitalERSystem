#include "../../include/algorithms/RadixSorter.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>  // ADD THIS LINE

void RadixSorter::sortPatientsByID(std::vector<Patient>& patients) {
    if (patients.empty()) return;
    
    int maxDigits = getMaxDigits(patients);
    
    // Sort by each digit position - O(nk) where k is number of digits
    for (int pos = 0; pos < maxDigits; pos++) {
        countingSortByPosition(patients, pos);
    }
}

int RadixSorter::getMaxDigits(const std::vector<Patient>& patients) {
    int maxLen = 0;
    for (const Patient& p : patients) {
        int len = p.getPatientID().length();
        if (len > maxLen) maxLen = len;
    }
    return maxLen;
}

void RadixSorter::countingSortByPosition(std::vector<Patient>& patients, int position) {
    const int RANGE = 256; // ASCII range
    std::vector<int> count(RANGE, 0);
    std::vector<Patient> output(patients.size());
    
    // Count occurrences
    for (const Patient& p : patients) {
        std::string id = p.getPatientID();
        int charIndex = id.length() - 1 - position;
        int charValue = (charIndex >= 0) ? static_cast<int>(id[charIndex]) : 0;
        count[charValue]++;
    }
    
    // Cumulative count
    for (int i = 1; i < RANGE; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array
    for (int i = patients.size() - 1; i >= 0; i--) {
        std::string id = patients[i].getPatientID();
        int charIndex = id.length() - 1 - position;
        int charValue = (charIndex >= 0) ? static_cast<int>(id[charIndex]) : 0;
        output[count[charValue] - 1] = patients[i];
        count[charValue]--;
    }
    
    patients = output;
}

void RadixSorter::radixSortNumeric(std::vector<int>& arr) {
    if (arr.empty()) return;
    
    int maxVal = *std::max_element(arr.begin(), arr.end());
    
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        std::vector<int> output(arr.size());
        std::vector<int> count(10, 0);
        
        for (size_t i = 0; i < arr.size(); i++) {
            count[(arr[i] / exp) % 10]++;
        }
        
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        
        arr = output;
    }
}

void RadixSorter::displaySortedPatients(const std::vector<Patient>& patients) {
    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║        RADIX SORT RESULTS                      ║\n";
    std::cout << "╠════════════════════════════════════════════════╣\n";
    
    for (const Patient& p : patients) {
        std::cout << "║ " << std::setw(45) << std::left 
                  << p.getPatientID() << " ║\n";
    }
    
    std::cout << "╚════════════════════════════════════════════════╝\n";
}