#ifndef MEDICAL_STAFF_HPP
#define MEDICAL_STAFF_HPP

#include <string>

enum class StaffRole {
    DOCTOR,
    NURSE,
    TECHNICIAN,
    PARAMEDIC,
    SPECIALIST
};

enum class AvailabilityStatus {
    AVAILABLE,
    BUSY,
    ON_BREAK,
    OFF_DUTY,
    EMERGENCY_CALL
};

class MedicalStaff {
private:
    std::string staffID;
    std::string name;
    StaffRole role;
    std::string currentLocation;
    AvailabilityStatus status;
    std::string assignedPatientID;

public:
    // Constructor
    MedicalStaff();
    MedicalStaff(const std::string& id, const std::string& staffName, StaffRole r);
    
    // Getters
    std::string getStaffID() const { return staffID; }
    std::string getName() const { return name; }
    StaffRole getRole() const { return role; }
    std::string getCurrentLocation() const { return currentLocation; }
    AvailabilityStatus getStatus() const { return status; }
    std::string getAssignedPatientID() const { return assignedPatientID; }
    
    // Setters
    void setCurrentLocation(const std::string& loc) { currentLocation = loc; }
    void setStatus(AvailabilityStatus s) { status = s; }
    void assignToPatient(const std::string& patientID);
    void clearAssignment();
    
    // Display
    void display() const;
    std::string getRoleString() const;
    std::string getStatusString() const;
};

#endif // MEDICAL_STAFF_HPP