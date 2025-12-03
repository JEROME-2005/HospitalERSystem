#include "../../include/algorithms/QuickSorter.hpp"
#include <iostream>

void QuickSorter::sortPatientsByID(std::vector<Patient>& patients) {
    if (!patients.empty()) {
        quickSortHelper(patients, 0, patients.size() - 1);
    }
}

int QuickSorter::partition(std::vector<Patient>& patients, int low, int high) {
    std::string pivot = patients[high].getPatientID();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (patients[j].getPatientID() < pivot) {
            i++;
            std::swap(patients[i], patients[j]);
        }
    }
    
    std::swap(patients[i + 1], patients[high]);
    return i + 1;
}

void QuickSorter::quickSortHelper(std::vector<Patient>& patients, int low, int high) {
    if (low < high) {
        int pi = partition(patients, low, high);
        quickSortHelper(patients, low, pi - 1);
        quickSortHelper(patients, pi + 1, high);
    }
}

void QuickSorter::displaySortedPatients(const std::vector<Patient>& patients) {
    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║        QUICKSORT RESULTS                       ║\n";
    std::cout << "╠════════════════════════════════════════════════╣\n";
    
    for (const Patient& p : patients) {
        std::cout << "║ " << std::setw(45) << std::left 
                  << p.getPatientID() << " ║\n";
    }
    
    std::cout << "╚════════════════════════════════════════════════╝\n";
}