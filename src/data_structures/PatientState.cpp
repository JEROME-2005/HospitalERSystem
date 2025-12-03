#include "../../include/data_structures/PatientState.hpp"
#include <iostream>

PatientState::PatientState() 
    : timestamp(std::time(nullptr)), operation(OperationType::PATIENT_REGISTERED),
      description("Default state") {}

PatientState::PatientState(const Patient& patient, OperationType op, const std::string& desc)
    : patientSnapshot(patient), timestamp(std::time(nullptr)), 
      operation(op), description(desc) {}

std::string PatientState::getOperationString() const {
    switch(operation) {
        case OperationType::PATIENT_REGISTERED: return "Patient Registered";
        case OperationType::PATIENT_TREATED: return "Patient Treated";
        case OperationType::PATIENT_TRANSFERRED: return "Patient Transferred";
        case OperationType::PATIENT_DISCHARGED: return "Patient Discharged";
        case OperationType::STAFF_ASSIGNED: return "Staff Assigned";
        case OperationType::EQUIPMENT_ALLOCATED: return "Equipment Allocated";
        default: return "Unknown Operation";
    }
}

void PatientState::display() const {
    std::cout << "State: " << getOperationString() << " - " << description 
              << " [Patient: " << patientSnapshot.getPatientID() << "]\n";
}