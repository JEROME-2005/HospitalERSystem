#include "include/core/EmergencyResponseSystem.hpp"
#include "include/utils/Simulation.hpp"
#include "include/utils/PerformanceMonitor.hpp"
#include "include/algorithms/RadixSorter.hpp"
#include "include/algorithms/QuickSorter.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

void displayMainMenu() {
    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "   HOSPITAL EMERGENCY RESPONSE SYSTEM (H.E.R.O.S)         \n";
    std::cout << "============================================================\n";
    std::cout << "  1. Run Full Emergency Simulation\n";
    std::cout << "  2. Register Individual Patient\n";
    std::cout << "  3. Process Next Critical Patient\n";
    std::cout << "  4. Assign Staff to Patient\n";
    std::cout << "  5. Optimize Equipment Distribution (MST)\n";
    std::cout << "  6. Find Optimal Route (Dijkstra)\n";
    std::cout << "  7. Compare Sorting Algorithms (Radix vs QuickSort)\n";
    std::cout << "  8. Undo Last Operation\n";
    std::cout << "  9. Display System Status\n";
    std::cout << " 10. Display Triage Queue\n";
    std::cout << " 11. Display Performance Report\n";
    std::cout << " 12. Display Hospital Layout\n";
    std::cout << "  0. Exit System\n";
    std::cout << "============================================================\n";
    std::cout << "Enter choice: ";
}

void runFullSimulation(EmergencyResponseSystem& system) {
    SimulationConfig config;
    
    std::cout << "\n-> Enter number of patients (default 50): ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) {
        config.patientCount = std::stoi(input);
    }
    
    std::cout << "-> Enter emergency duration in minutes (default 120): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        config.emergencyDuration = std::stoi(input);
    }
    
    system.simulateEmergencyScenario(config);
}

void registerManualPatient(EmergencyResponseSystem& system) {
    std::cout << "\n-> Enter Patient ID: ";
    std::string id;
    std::getline(std::cin, id);
    
    std::cout << "-> Enter location: ";
    std::string location;
    std::getline(std::cin, location);
    
    std::cout << "-> Is patient critical? (y/n): ";
    std::string criticalInput;
    std::getline(std::cin, criticalInput);
    bool isCritical = (criticalInput == "y" || criticalInput == "Y");
    
    VitalSigns vitals = Simulation::generateRandomVitals(isCritical);
    
    Patient patient(id, vitals, location);
    system.registerNewPatient(patient);
}

void compareSortingAlgorithms() {
    std::cout << "\n============================================================\n";
    std::cout << "         SORTING ALGORITHM COMPARISON (LO4)                 \n";
    std::cout << "============================================================\n";
    
    // Generate test data
    std::vector<Patient> patientsRadix = Simulation::generateSyntheticPatientData(100);
    std::vector<Patient> patientsQuick = patientsRadix; // Copy
    
    std::cout << "\nTest Dataset: 100 patients\n";
    std::cout << "------------------------------------------------------------\n";
    
    // Test Radix Sort
    PerformanceMonitor::startTimer("Radix Sort");
    RadixSorter::sortPatientsByID(patientsRadix);
    long long radixTime = PerformanceMonitor::stopTimer("Radix Sort");
    
    // Test QuickSort
    PerformanceMonitor::startTimer("QuickSort");
    QuickSorter::sortPatientsByID(patientsQuick);
    long long quickTime = PerformanceMonitor::stopTimer("QuickSort");
    
    // Display results
    std::cout << "\nRESULTS:\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "Radix Sort:  " << radixTime << " microseconds\n";
    std::cout << "QuickSort:   " << quickTime << " microseconds\n";
    std::cout << "------------------------------------------------------------\n";
    
    if (radixTime < quickTime) {
        double speedup = (double)quickTime / radixTime;
        std::cout << "* Radix Sort is " << std::fixed << std::setprecision(2) 
                  << speedup << "x FASTER\n";
    } else {
        double speedup = (double)radixTime / quickTime;
        std::cout << "* QuickSort is " << std::fixed << std::setprecision(2) 
                  << speedup << "x FASTER\n";
    }
    
    std::cout << "\nComplexity Analysis:\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "Radix Sort:  O(nk) where k = ID length\n";
    std::cout << "QuickSort:   O(n log n) average case\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "For fixed-length IDs, Radix Sort performs better!\n";
}

void demonstrateAllFeatures(EmergencyResponseSystem& system) {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "   COMPREHENSIVE DEMONSTRATION OF ALL DSA FEATURES\n";
    std::cout << std::string(70, '=') << "\n";
    
    // 1. Priority Queue (Min-Heap)
    std::cout << "\n1. PRIORITY QUEUE (MIN-HEAP) DEMONSTRATION\n";
    std::cout << std::string(60, '-') << "\n";
    std::vector<Patient> testPatients = Simulation::generateSyntheticPatientData(5);
    for (const Patient& p : testPatients) {
        system.registerNewPatient(p);
    }
    system.displayTriageQueue();
    
    // 2. Stack (Undo System)
    std::cout << "\n2. STACK (UNDO SYSTEM) DEMONSTRATION\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << "Performing undo operation...\n";
    if (system.canUndo()) {
        system.undoLastOperation();
    }
    
    // 3. Graph + Dijkstra
    std::cout << "\n3. DIJKSTRA'S SHORTEST PATH DEMONSTRATION\n";
    std::cout << std::string(60, '-') << "\n";
    RouteInfo route = system.findFastestRoute("ENTRANCE", "ICU_1");
    
    // 4. Kruskal's MST
    std::cout << "\n4. KRUSKAL'S MST DEMONSTRATION\n";
    std::cout << std::string(60, '-') << "\n";
    system.optimizeEquipmentDistribution();
    
    // 5. Sorting Comparison
    std::cout << "\n5. SORTING ALGORITHM COMPARISON\n";
    std::cout << std::string(60, '-') << "\n";
    compareSortingAlgorithms();
    
    // Final Report
    std::cout << "\n6. FINAL PERFORMANCE REPORT\n";
    std::cout << std::string(60, '-') << "\n";
    system.generatePerformanceReport();
}

int main() {
    try {
        // Initialize system
        EmergencyResponseSystem system;
        
        // Display welcome banner
        std::cout << "\n";
        std::cout << "================================================================\n";
        std::cout << "                                                                \n";
        std::cout << "   HOSPITAL EMERGENCY RESPONSE OPTIMIZATION SYSTEM (H.E.R.O.S) \n";
        std::cout << "                                                                \n";
        std::cout << "   A Data Structures & Algorithms Project                      \n";
        std::cout << "   Demonstrating: Heaps, Graphs, Trees, Sorting & Stacks       \n";
        std::cout << "                                                                \n";
        std::cout << "================================================================\n";
        
        std::cout << "\nLearning Outcomes Covered:\n";
        std::cout << "   LO1: Priority Queue (Min-Heap) for Triage\n";
        std::cout << "   LO2: Stack for Undo Functionality\n";
        std::cout << "   LO3: Graph Algorithms (Dijkstra, Kruskal)\n";
        std::cout << "   LO4: Sorting Comparison (Radix vs QuickSort)\n";
        std::cout << "   LO5: Complexity-Driven Design & Optimization\n";
        
        // Ask for demo mode
        std::cout << "\nWould you like to run the full demonstration? (y/n): ";
        std::string demoChoice;
        std::getline(std::cin, demoChoice);
        
        if (demoChoice == "y" || demoChoice == "Y") {
            demonstrateAllFeatures(system);
            std::cout << "\n* Demonstration complete!\n";
            return 0;
        }
        
        // Interactive menu loop
        while (true) {
            displayMainMenu();
            
            std::string choice;
            std::getline(std::cin, choice);
            
            if (choice.empty()) continue;
            
            int option = std::stoi(choice);
            
            switch (option) {
                case 1:
                    runFullSimulation(system);
                    break;
                    
                case 2:
                    registerManualPatient(system);
                    break;
                    
                case 3:
                    try {
                        Patient p = system.processNextCriticalPatient();
                        p.display();
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                    break;
                    
                case 4: {
                    std::cout << "Enter Staff ID: ";
                    std::string staffID;
                    std::getline(std::cin, staffID);
                    std::cout << "Enter Patient ID: ";
                    std::string patientID;
                    std::getline(std::cin, patientID);
                    system.assignStaffToPatient(staffID, patientID);
                    break;
                }
                    
                case 5:
                    system.optimizeEquipmentDistribution();
                    break;
                    
                case 6: {
                    std::cout << "Enter start location: ";
                    std::string start;
                    std::getline(std::cin, start);
                    std::cout << "Enter end location: ";
                    std::string end;
                    std::getline(std::cin, end);
                    RouteInfo route = system.findFastestRoute(start, end);
                    break;
                }
                    
                case 7:
                    compareSortingAlgorithms();
                    break;
                    
                case 8:
                    system.undoLastOperation();
                    break;
                    
                case 9:
                    system.displaySystemStatus();
                    break;
                    
                case 10:
                    system.displayTriageQueue();
                    break;
                    
                case 11:
                    system.generatePerformanceReport();
                    break;
                    
                case 12:
                    std::cout << "Hospital layout graph visualization\n";
                    break;
                    
                case 0:
                    std::cout << "\n* Thank you for using H.E.R.O.S!\n";
                    std::cout << "============================================\n";
                    return 0;
                    
                default:
                    std::cout << "Invalid choice! Please try again.\n";
            }
            
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}