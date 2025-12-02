// include/core/MedicalStaff.hpp
#ifndef MEDICAL_STAFF_HPP
#define MEDICAL_STAFF_HPP

#include "../utils/CommonTypes.hpp"

namespace HEROS {

class MedicalStaff {
private:
    std::string staffID;
    std::string name;
    StaffRole role;
    std::string currentLocation;       // Current room ID
    AvailabilityStatus status;
    std::vector<std::string> assignedPatientIDs;
    std::vector<std::string> specializations;
    int experienceYears;
    time_t shiftStartTime;
    time_t shiftEndTime;

public:
    // ==================== CONSTRUCTORS ====================
    
    MedicalStaff();
    MedicalStaff(const std::string& name, StaffRole role);
    MedicalStaff(const std::string& id, const std::string& name, 
                 StaffRole role, const std::string& location);
    
    // ==================== ASSIGNMENT MANAGEMENT ====================
    
    // Assign patient to this staff member
    bool assignPatient(const std::string& patientID);
    
    // Unassign patient
    bool unassignPatient(const std::string& patientID);
    
    // Check if staff is handling a patient
    bool isHandlingPatient(const std::string& patientID) const;
    
    // Get number of assigned patients
    int getPatientLoad() const { return assignedPatientIDs.size(); }
    
    // ==================== SPECIALIZATION ====================
    
    void addSpecialization(const std::string& spec);
    bool hasSpecialization(const std::string& spec) const;
    
    // ==================== GETTERS ====================
    
    std::string getStaffID() const { return staffID; }
    std::string getName() const { return name; }
    StaffRole getRole() const { return role; }
    std::string getCurrentLocation() const { return currentLocation; }
    AvailabilityStatus getStatus() const { return status; }
    std::vector<std::string> getAssignedPatientIDs() const { return assignedPatientIDs; }
    std::vector<std::string> getSpecializations() const { return specializations; }
    int getExperienceYears() const { return experienceYears; }
    
    // Check if staff is available
    bool isAvailable() const { return status == AvailabilityStatus::AVAILABLE; }
    
    // ==================== SETTERS ====================
    
    void setName(const std::string& n) { name = n; }
    void setRole(StaffRole r) { role = r; }
    void setCurrentLocation(const std::string& loc) { currentLocation = loc; }
    void setStatus(AvailabilityStatus s) { status = s; }
    void setExperienceYears(int years) { experienceYears = years; }
    void setShiftTimes(time_t start, time_t end);
    
    // ==================== UTILITY FUNCTIONS ====================
    
    // Print staff information
    void print() const;
    
    // Get brief summary
    std::string getSummary() const;
    
    // Check if currently on shift
    bool isOnShift() const;
    
    // Calculate priority for assignment (based on load, experience, etc.)
    int calculateAssignmentPriority() const;
};

} // namespace HEROS

#endif // MEDICAL_STAFF_HPP