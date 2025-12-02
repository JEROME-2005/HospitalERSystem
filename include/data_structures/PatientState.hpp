// include/data_structures/PatientState.hpp
#ifndef PATIENT_STATE_HPP
#define PATIENT_STATE_HPP

#include "../utils/CommonTypes.hpp"
#include "../core/Patient.hpp"

namespace HEROS {
namespace DataStructures {

/**
 * PatientState - Snapshot of patient data for undo operations
 */
class PatientState {
private:
    Patient patientSnapshot;
    time_t timestamp;
    OperationType operation;
    std::string description;
    std::string performedBy;

public:
    // Constructors
    PatientState();
    PatientState(const Patient& patient, OperationType op, const std::string& desc = "");
    
    // Copy constructor and assignment
    PatientState(const PatientState& other);
    PatientState& operator=(const PatientState& other);
    
    // Destructor
    ~PatientState() = default;
    
    // Getters
    Patient getPatientSnapshot() const { return patientSnapshot; }
    time_t getTimestamp() const { return timestamp; }
    OperationType getOperation() const { return operation; }
    std::string getDescription() const { return description; }
    std::string getPerformedBy() const { return performedBy; }
    
    // Setters
    void setPatientSnapshot(const Patient& patient) { patientSnapshot = patient; }
    void setOperation(OperationType op) { operation = op; }
    void setDescription(const std::string& desc) { description = desc; }
    void setPerformedBy(const std::string& by) { performedBy = by; }
    
    // Utility
    std::string toString() const;
    void print() const;
};

} // namespace DataStructures
} // namespace HEROS

#endif // PATIENT_STATE_HPP