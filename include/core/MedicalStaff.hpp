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
    std::string currentLocation;
    AvailabilityStatus status;
    std::string specialization;
    std::vector<std::string> assignedPatientIDs;
    int maxPatientLoad;
    time_t shiftStartTime;
    int shiftDurationHours;

public:
    // Constructors
    MedicalStaff();
    MedicalStaff(const std::string& id, const std::string& staffName, StaffRole staffRole);
    MedicalStaff(const std::string& id, const std::string& staffName, StaffRole staffRole,
                 const std::string& spec, int maxLoad);
    
    // Copy constructor and assignment
    MedicalStaff(const MedicalStaff& other);
    MedicalStaff& operator=(const MedicalStaff& other);
    
    // Destructor
    ~MedicalStaff() = default;
    
    // Staff management
    bool assignPatient(const std::string& patientID);
    bool unassignPatient(const std::string& patientID);
    bool hasPatient(const std::string& patientID) const;
    bool canTakeMorePatients() const;
    int getCurrentPatientCount() const;
    
    // Getters
    std::string getStaffID() const { return staffID; }
    std::string getName() const { return name; }
    StaffRole getRole() const { return role; }
    std::string getCurrentLocation() const { return currentLocation; }
    AvailabilityStatus getStatus() const { return status; }
    std::string getSpecialization() const { return specialization; }
    std::vector<std::string> getAssignedPatientIDs() const { return assignedPatientIDs; }
    int getMaxPatientLoad() const { return maxPatientLoad; }
    bool isAvailable() const { return status == AvailabilityStatus::AVAILABLE && canTakeMorePatients(); }
    
    // Setters
    void setStaffID(const std::string& id) { staffID = id; }
    void setName(const std::string& n) { name = n; }
    void setRole(StaffRole r) { role = r; }
    void setCurrentLocation(const std::string& loc) { currentLocation = loc; }
    void setStatus(AvailabilityStatus s) { status = s; }
    void setSpecialization(const std::string& spec) { specialization = spec; }
    void setMaxPatientLoad(int max) { maxPatientLoad = max; }
    
    // Utility
    std::string toString() const;
    void printInfo() const;
    double getWorkloadPercentage() const;
    
    // Comparison
    bool operator==(const MedicalStaff& other) const;
    bool operator<(const MedicalStaff& other) const; // For priority queue (less workload = higher priority)
};

} // namespace HEROS

#endif // MEDICAL_STAFF_HPP