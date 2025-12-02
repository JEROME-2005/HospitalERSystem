#ifndef PATIENT_STATE_HPP
#define PATIENT_STATE_HPP

#include "../core/Patient.hpp"
#include <string>
#include <ctime>
#include <iostream>

namespace DataStructures {

    /**
     * Operation Type Enumeration
     * Defines types of operations that can be undone
     */
    enum class OperationType {
        PATIENT_REGISTERED,
        PATIENT_DISCHARGED,
        PATIENT_TRANSFERRED,
        TRIAGE_UPDATED,
        STAFF_ASSIGNED,
        STAFF_UNASSIGNED,
        VITALS_UPDATED,
        LOCATION_CHANGED,
        PRIORITY_CHANGED,
        EQUIPMENT_ASSIGNED,
        EQUIPMENT_REMOVED,
        CUSTOM
    };

    /**
     * PatientState Class
     * 
     * Stores a snapshot of patient data for undo functionality.
     * Used with StateStack for the Command pattern implementation.
     */
    class PatientState {
    private:
        Core::Patient patientSnapshot;
        time_t timestamp;
        OperationType operation;
        std::string operationDescription;
        std::string performedBy;  // Staff ID who performed the operation
        std::string additionalData;

    public:
        // Constructors
        PatientState();
        PatientState(const Core::Patient& patient, OperationType op);
        PatientState(const Core::Patient& patient, OperationType op, 
                     const std::string& description, const std::string& staffID = "");
        PatientState(const PatientState& other);
        
        // Destructor
        ~PatientState();

        // Assignment operator
        PatientState& operator=(const PatientState& other);

        // Getters
        Core::Patient getPatientSnapshot() const { return patientSnapshot; }
        time_t getTimestamp() const { return timestamp; }
        OperationType getOperation() const { return operation; }
        std::string getOperationDescription() const { return operationDescription; }
        std::string getPerformedBy() const { return performedBy; }
        std::string getAdditionalData() const { return additionalData; }

        // Setters
        void setPatientSnapshot(const Core::Patient& patient) { patientSnapshot = patient; }
        void setTimestamp(time_t t) { timestamp = t; }
        void setOperation(OperationType op) { operation = op; }
        void setOperationDescription(const std::string& desc) { operationDescription = desc; }
        void setPerformedBy(const std::string& staffID) { performedBy = staffID; }
        void setAdditionalData(const std::string& data) { additionalData = data; }

        // Utility Methods
        std::string getOperationTypeString() const;
        std::string getFormattedTimestamp() const;
        std::string toString() const;
        void display() const;

        // Comparison operators
        bool operator==(const PatientState& other) const;
        bool operator!=(const PatientState& other) const;

        // For display in StateStack
        friend std::ostream& operator<<(std::ostream& os, const PatientState& state);
    };

} // namespace DataStructures

#endif // PATIENT_STATE_HPP