#ifndef PATIENT_STATE_HPP
#define PATIENT_STATE_HPP

#include "../core/Patient.hpp"
#include <ctime>
#include <string>

enum class OperationType {
    PATIENT_REGISTERED,
    PATIENT_TREATED,
    PATIENT_TRANSFERRED,
    PATIENT_DISCHARGED,
    STAFF_ASSIGNED,
    EQUIPMENT_ALLOCATED
};

class PatientState {
private:
    Patient patientSnapshot;
    time_t timestamp;
    OperationType operation;
    std::string description;

public:
    PatientState();
    PatientState(const Patient& patient, OperationType op, const std::string& desc);
    
    // Getters
    Patient getPatientSnapshot() const { return patientSnapshot; }
    time_t getTimestamp() const { return timestamp; }
    OperationType getOperation() const { return operation; }
    std::string getDescription() const { return description; }
    
    // Display
    void display() const;
    std::string getOperationString() const;
};

#endif // PATIENT_STATE_HPP