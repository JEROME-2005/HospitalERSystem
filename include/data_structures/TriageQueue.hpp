#ifndef TRIAGE_QUEUE_HPP
#define TRIAGE_QUEUE_HPP

#include "MinHeap.hpp"
#include "../core/Patient.hpp"
#include <vector>

class TriageQueue {
private:
    MinHeap<Patient> patientHeap;
    int totalPatientsProcessed;

public:
    TriageQueue();
    
    // Core triage operations
    void addPatient(const Patient& patient);                    // O(log n)
    Patient getNextPatient();                                   // O(log n)
    Patient peekNextPatient() const;                            // O(1)
    
    // Advanced operations
    void updatePatientPriority(const std::string& patientID, const VitalSigns& newVitals);
    std::vector<Patient> getCriticalPatients(int count);        // O(k log n)
    
    // Status
    bool isEmpty() const { return patientHeap.isEmpty(); }
    int getPendingCount() const { return patientHeap.size(); }
    int getTotalProcessed() const { return totalPatientsProcessed; }
    
    // Display
    void displayQueue() const;
};

#endif // TRIAGE_QUEUE_HPP