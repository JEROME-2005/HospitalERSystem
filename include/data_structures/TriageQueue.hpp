// include/data_structures/TriageQueue.hpp
#ifndef TRIAGE_QUEUE_HPP
#define TRIAGE_QUEUE_HPP

#include "MinHeap.hpp"
#include "../core/Patient.hpp"

namespace HEROS {
namespace DataStructures {

/**
 * TriageQueue - Specialized Priority Queue for Patient Triage
 * 
 * Inherits from MinHeap<Patient> with additional medical functionality.
 * Patients with HIGHER severity scores are extracted first.
 * 
 * Time Complexity:
 *   - addPatient():              O(log n)
 *   - getNextPatient():          O(log n)
 *   - updatePatientPriority():   O(n) for search + O(log n) for reheapify
 *   - getCriticalPatients():     O(k log n) for k patients
 */
class TriageQueue : public MinHeap<Patient> {
private:
    int totalProcessed;
    int redCount;
    int yellowCount;
    int greenCount;
    
    void updateCounts(const Patient& patient, bool adding);

public:
    // Constructors
    TriageQueue();
    TriageQueue(const std::vector<Patient>& patients);
    
    // Destructor
    ~TriageQueue() override = default;
    
    // Patient management
    void addPatient(const Patient& patient);
    Patient getNextPatient();
    Patient peekNextPatient() const;
    
    // Priority updates
    bool updatePatientPriority(const std::string& patientID, const VitalSigns& newVitals);
    bool removePatient(const std::string& patientID);
    
    // Query operations
    std::vector<Patient> getCriticalPatients(int count);
    std::vector<Patient> getPatientsByStatus(TriageStatus status);
    Patient* findPatient(const std::string& patientID);
    bool hasPatient(const std::string& patientID) const;
    
    // Statistics
    int getTotalProcessed() const { return totalProcessed; }
    int getRedCount() const { return redCount; }
    int getYellowCount() const { return yellowCount; }
    int getGreenCount() const { return greenCount; }
    int getWaitingCount() const { return size(); }
    
    // Reporting
    void printQueueStatus() const;
    std::string getQueueStatistics() const;
};

} // namespace DataStructures
} // namespace HEROS

#endif // TRIAGE_QUEUE_HPP