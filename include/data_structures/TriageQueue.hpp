#ifndef TRIAGE_QUEUE_HPP
#define TRIAGE_QUEUE_HPP

#include "MinHeap.hpp"
#include "../core/Patient.hpp"
#include <vector>
#include <string>
#include <map>

namespace DataStructures {

    /**
     * TriageQueue Class
     * 
     * Specialized priority queue for hospital patient triage.
     * Inherits from MinHeap<Patient> and adds triage-specific functionality.
     * 
     * Patients are prioritized based on:
     * 1. Severity Score (vital signs + medical condition)
     * 2. Wait Time (longer wait increases priority)
     * 3. Triage Status (WHO color coding)
     * 
     * Time Complexities:
     * - addPatient(): O(log n)
     * - getNextPatient(): O(log n)
     * - updatePatientPriority(): O(n) search + O(log n) heapify
     * - getCriticalPatients(): O(k log n) where k is count
     */
    class TriageQueue : public MinHeap<Core::Patient> {
    private:
        std::map<std::string, Core::Patient> patientLookup;  // For O(1) patient lookup by ID
        int totalPatientsProcessed;
        int redTagCount;    // Critical patients
        int yellowTagCount; // Urgent patients
        int greenTagCount;  // Non-urgent patients
        double averageWaitTime;

    public:
        // Constructors
        TriageQueue();
        TriageQueue(const TriageQueue& other);
        
        // Destructor
        ~TriageQueue();

        // Assignment operator
        TriageQueue& operator=(const TriageQueue& other);

        // Core Triage Operations
        void addPatient(const Core::Patient& patient);
        Core::Patient getNextPatient();
        Core::Patient peekNextPatient() const;
        
        // Priority Management
        void updatePatientPriority(const std::string& patientID, int newSeverity);
        void recalculateAllPriorities();  // Update all based on wait time
        
        // Retrieval Operations
        std::vector<Core::Patient> getCriticalPatients(int count);
        std::vector<Core::Patient> getPatientsByTriageStatus(Core::TriageStatus status);
        Core::Patient* findPatient(const std::string& patientID);
        
        // Patient Management
        bool removePatient(const std::string& patientID);
        bool hasPatient(const std::string& patientID) const;
        
        // Statistics
        int getTotalPatients() const { return heapSize; }
        int getRedTagCount() const { return redTagCount; }
        int getYellowTagCount() const { return yellowTagCount; }
        int getGreenTagCount() const { return greenTagCount; }
        double getAverageWaitTime() const { return averageWaitTime; }
        int getTotalProcessed() const { return totalPatientsProcessed; }
        
        // Update Counts
        void updateTriageCounts();
        void calculateAverageWaitTime();
        
        // Display
        void displayQueue() const;
        void displayStatistics() const;
        std::string getQueueReport() const;
    };

} // namespace DataStructures

#endif // TRIAGE_QUEUE_HPP