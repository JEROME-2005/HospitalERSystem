#include "../include/data_structures/MinHeap.hpp"
#include "../include/core/Patient.hpp"
#include <iostream>
#include <cassert>

void testMinHeapBasicOperations() {
    std::cout << "\n🧪 Testing Min-Heap Basic Operations...\n";
    
    MinHeap<int> heap;
    
    // Test insert
    heap.insert(5);
    heap.insert(3);
    heap.insert(7);
    heap.insert(1);
    
    assert(heap.size() == 4);
    assert(heap.getMin() == 1);
    
    // Test extract
    int min = heap.extractMin();
    assert(min == 1);
    assert(heap.size() == 3);
    assert(heap.getMin() == 3);
    
    std::cout << "✓ Basic operations test passed!\n";
}

void testMinHeapWithPatients() {
    std::cout << "\n🧪 Testing Min-Heap with Patient Objects...\n";
    
    MinHeap<Patient> patientHeap;
    
    VitalSigns critical;
    critical.heartRate = 40;
    critical.bloodPressure = 80;
    critical.oxygenLevel = 85;
    
    VitalSigns normal;
    normal.heartRate = 80;
    normal.bloodPressure = 120;
    normal.oxygenLevel = 98;
    
    Patient p1("P001", critical, "ER");
    Patient p2("P002", normal, "ER");
    
    patientHeap.insert(p2);
    patientHeap.insert(p1);
    
    Patient mostCritical = patientHeap.getMin();
    assert(mostCritical.getPatientID() == "P001");
    
    std::cout << "✓ Patient heap test passed!\n";
}

void testBuildHeap() {
    std::cout << "\n🧪 Testing Build Heap (O(n) construction)...\n";
    
    std::vector<int> values = {9, 5, 6, 2, 3, 7, 1, 4, 8};
    MinHeap<int> heap;
    heap.buildHeap(values);
    
    assert(heap.getMin() == 1);
    assert(heap.size() == 9);
    
    std::cout << "✓ Build heap test passed!\n";
}

int main() {
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║   MIN-HEAP UNIT TESTS                ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
    
    testMinHeapBasicOperations();
    testMinHeapWithPatients();
    testBuildHeap();
    
    std::cout << "\n✅ All Min-Heap tests passed!\n\n";
    return 0;
}