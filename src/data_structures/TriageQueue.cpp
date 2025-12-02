// src/data_structures/TriageQueue.cpp
#include "../../include/data_structures/TriageQueue.hpp"

namespace HEROS {
namespace DataStructures {

TriageQueue::TriageQueue()
    : MinHeap<Patient>(), totalProcessed(0), redCount(0), yellowCount(0), greenCount(0) {
}

TriageQueue::TriageQueue(const std::vector<Patient>& patients)
    : MinHeap<Patient>(), totalProcessed(0), redCount(0), yellowCount(0), greenCount(0) {
    for (const auto& patient : patients) {
        addPatient(patient);
    }
}

void TriageQueue::updateCounts(const Patient& patient, bool adding) {
    int delta = adding ? 1 : -1;
    switch (patient.getTriageStatus()) {
        case TriageStatus::RED:
            redCount += delta;
            break;
        case TriageStatus::YELLOW:
            yellowCount += delta;
            break;
        case TriageStatus::GREEN:
            greenCount += delta;
            break;
        default:
            break;
    }
}

void TriageQueue::addPatient(const Patient& patient) {
    insert(patient);
    updateCounts(patient, true);
}

Patient TriageQueue::getNextPatient() {
    Patient patient = extractMin();
    updateCounts(patient, false);
    totalProcessed++;
    return patient;
}

Patient TriageQueue::peekNextPatient() const {
    return getMin();
}

bool TriageQueue::updatePatientPriority(const std::string& patientID, 
                                         const VitalSigns& newVitals) {
    // Find patient in heap
    for (size_t i = 0; i < heapArray.size(); ++i) {
        if (heapArray[i].getPatientID() == patientID) {
            // Update counts for old status
            updateCounts(heapArray[i], false);
            
            // Update vitals and recalculate severity
            heapArray[i].setVitalSigns(newVitals);
            
            // Update counts for new status
            updateCounts(heapArray[i], true);
            
            // Rebuild heap to maintain property
            buildHeap(heapArray);
            return true;
        }
    }
    return false;
}

bool TriageQueue::removePatient(const std::string& patientID) {
    for (size_t i = 0; i < heapArray.size(); ++i) {
        if (heapArray[i].getPatientID() == patientID) {
            updateCounts(heapArray[i], false);
            heapArray.erase(heapArray.begin() + i);
            buildHeap(heapArray);
            return true;
        }
    }
    return false;
}

std::vector<Patient> TriageQueue::getCriticalPatients(int count) {
    std::vector<Patient> result;
    std::vector<Patient> backup = heapArray;
    
    int extracted = 0;
    while (!isEmpty() && extracted < count) {
        result.push_back(extractMin());
        extracted++;
    }
    
    // Restore heap
    heapArray = backup;
    
    return result;
}

std::vector<Patient> TriageQueue::getPatientsByStatus(TriageStatus status) {
    std::vector<Patient> result;
    for (const auto& patient : heapArray) {
        if (patient.getTriageStatus() == status) {
            result.push_back(patient);
        }
    }
    return result;
}

Patient* TriageQueue::findPatient(const std::string& patientID) {
    for (auto& patient : heapArray) {
        if (patient.getPatientID() == patientID) {
            return &patient;
        }
    }
    return nullptr;
}

bool TriageQueue::hasPatient(const std::string& patientID) const {
    for (const auto& patient : heapArray) {
        if (patient.getPatientID() == patientID) {
            return true;
        }
    }
    return false;
}

void TriageQueue::printQueueStatus() const {
    std::cout << "\n============ TRIAGE QUEUE STATUS ============" << std::endl;
    std::cout << "Total Waiting: " << getWaitingCount() << std::endl;
    std::cout << "Total Processed: " << totalProcessed << std::endl;
    std::cout << "\nBy Triage Level:" << std::endl;
    std::cout << "  RED (Immediate):    " << redCount << std::endl;
    std::cout << "  YELLOW (Delayed):   " << yellowCount << std::endl;
    std::cout << "  GREEN (Minor):      " << greenCount << std::endl;
    
    if (!isEmpty()) {
        std::cout << "\nNext Patient: " << getMin().toString() << std::endl;
    }
    
    std::cout << "\nAll Patients in Queue:" << std::endl;
    for (size_t i = 0; i < heapArray.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << heapArray[i].toString() << std::endl;
    }
    std::cout << "=============================================" << std::endl;
}

std::string TriageQueue::getQueueStatistics() const {
    std::stringstream ss;
    ss << "Waiting: " << getWaitingCount() 
       << " (R:" << redCount << " Y:" << yellowCount << " G:" << greenCount << ")"
       << " | Processed: " << totalProcessed;
    return ss.str();
}

} // namespace DataStructures
} // namespace HEROS