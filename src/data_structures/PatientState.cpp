// src/data_structures/PatientState.cpp
#include "../../include/data_structures/PatientState.hpp"

namespace HEROS {
namespace DataStructures {

PatientState::PatientState()
    : timestamp(std::time(nullptr)), operation(OperationType::PATIENT_REGISTER),
      description(""), performedBy("System") {
}

PatientState::PatientState(const Patient& patient, OperationType op, const std::string& desc)
    : patientSnapshot(patient), timestamp(std::time(nullptr)), operation(op),
      description(desc), performedBy("System") {
}

PatientState::PatientState(const PatientState& other)
    : patientSnapshot(other.patientSnapshot), timestamp(other.timestamp),
      operation(other.operation), description(other.description),
      performedBy(other.performedBy) {
}

PatientState& PatientState::operator=(const PatientState& other) {
    if (this != &other) {
        patientSnapshot = other.patientSnapshot;
        timestamp = other.timestamp;
        operation = other.operation;
        description = other.description;
        performedBy = other.performedBy;
    }
    return *this;
}

std::string PatientState::toString() const {
    std::stringstream ss;
    ss << "State[Op=" << operationTypeToString(operation)
       << ", Patient=" << patientSnapshot.getPatientID()
       << ", Time=" << std::ctime(&timestamp)
       << ", Desc=" << description << "]";
    return ss.str();
}

void PatientState::print() const {
    std::cout << "\n=== Patient State Snapshot ===" << std::endl;
    std::cout << "Operation: " << operationTypeToString(operation) << std::endl;
    std::cout << "Timestamp: " << std::ctime(&timestamp);
    std::cout << "Description: " << description << std::endl;
    std::cout << "Performed By: " << performedBy << std::endl;
    patientSnapshot.printInfo();
}

} // namespace DataStructures
} // namespace HEROS