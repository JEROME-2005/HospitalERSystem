#include "../../include/data_structures/TriageQueue.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>  // ADD THIS LINE

TriageQueue::TriageQueue() : totalPatientsProcessed(0) {}

void TriageQueue::addPatient(const Patient& patient) {
    patientHeap.insert(patient);
    std::cout << "✓ Patient " << patient.getPatientID() 
              << " added to triage queue (Severity: " 
              << patient.getSeverityScore() << ")\n";
}

Patient TriageQueue::getNextPatient() {
    if (patientHeap.isEmpty()) {
        throw std::runtime_error("No patients in queue!");
    }
    
    Patient nextPatient = patientHeap.extractMin();
    totalPatientsProcessed++;
    
    std::cout << "→ Next patient: " << nextPatient.getPatientID() 
              << " (Severity: " << nextPatient.getSeverityScore() << ")\n";
    
    return nextPatient;
}

Patient TriageQueue::peekNextPatient() const {
    return patientHeap.getMin();
}

void TriageQueue::updatePatientPriority(const std::string& patientID, const VitalSigns& newVitals) {
    // For simplicity, we rebuild the heap after update
    // In production, this would use a decrease-key operation
    std::vector<Patient> tempPatients;
    
    while (!patientHeap.isEmpty()) {
        Patient p = patientHeap.extractMin();
        if (p.getPatientID() == patientID) {
            p.setVitalSigns(newVitals);
            p.updateSeverity();
            std::cout << "✓ Updated priority for patient " << patientID << "\n";
        }
        tempPatients.push_back(p);
    }
    
    patientHeap.buildHeap(tempPatients);
}

std::vector<Patient> TriageQueue::getCriticalPatients(int count) {
    std::vector<Patient> criticalPatients;
    std::vector<Patient> tempStorage;
    
    int retrieved = 0;
    while (!patientHeap.isEmpty() && retrieved < count) {
        Patient p = patientHeap.extractMin();
        criticalPatients.push_back(p);
        tempStorage.push_back(p);
        retrieved++;
    }
    
    // Restore heap
    while (!patientHeap.isEmpty()) {
        tempStorage.push_back(patientHeap.extractMin());
    }
    patientHeap.buildHeap(tempStorage);
    
    return criticalPatients;
}

void TriageQueue::displayQueue() const {
    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║         TRIAGE QUEUE STATUS                    ║\n";
    std::cout << "╠════════════════════════════════════════════════╣\n";
    std::cout << "║ Pending Patients: " << std::setw(28) << getPendingCount() << " ║\n";
    std::cout << "║ Total Processed: " << std::setw(29) << totalPatientsProcessed << " ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
}