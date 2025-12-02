#ifndef MEDICAL_STAFF_HPP
#define MEDICAL_STAFF_HPP

#include <string>
#include <vector>
#include <ctime>
#include <iostream>

namespace Core {

    // Staff Role Enumeration
    enum class StaffRole {
        DOCTOR,
        NURSE,
        SURGEON,
        ANESTHESIOLOGIST,
        RADIOLOGIST,
        TECHNICIAN,
        PARAMEDIC,
        RECEPTIONIST,
        ADMINISTRATOR
    };

    // Staff Specialization
    enum class Specialization {
        GENERAL,
        CARDIOLOGY,
        NEUROLOGY,
        ORTHOPEDICS,
        PEDIATRICS,
        EMERGENCY_MEDICINE,
        SURGERY,
        INTERNAL_MEDICINE,
        PULMONOLOGY,
        ANESTHESIA,
        RADIOLOGY,
        PATHOLOGY,
        NONE
    };

    // Availability Status
    enum class AvailabilityStatus {
        AVAILABLE,
        BUSY,
        ON_BREAK,
        IN_SURGERY,
        OFF_DUTY,
        ON_CALL,
        EMERGENCY_RESPONSE
    };

    // Shift Type
    enum class ShiftType {
        MORNING,    // 6 AM - 2 PM
        AFTERNOON,  // 2 PM - 10 PM
        NIGHT,      // 10 PM - 6 AM
        FULL_DAY,   // 6 AM - 6 PM
        ON_CALL     // Variable
    };

    class MedicalStaff {
    private:
        std::string staffID;
        std::string name;
        StaffRole role;
        Specialization specialization;
        std::string currentLocation;
        AvailabilityStatus status;
        ShiftType currentShift;
        std::vector<std::string> assignedPatients;
        std::vector<std::string> qualifications;
        int yearsOfExperience;
        std::string contactNumber;
        std::string email;
        time_t shiftStartTime;
        time_t shiftEndTime;
        int currentWorkload;  // Number of patients currently assigned
        int maxWorkload;      // Maximum patients they can handle
        double responseTime;  // Average response time in minutes

    public:
        // Constructors
        MedicalStaff();
        MedicalStaff(const std::string& id, const std::string& name, StaffRole role);
        MedicalStaff(const std::string& id, const std::string& name, StaffRole role,
                     Specialization spec, const std::string& location);
        MedicalStaff(const MedicalStaff& other);
        
        // Destructor
        ~MedicalStaff();

        // Assignment operator
        MedicalStaff& operator=(const MedicalStaff& other);

        // Staff Management Methods
        bool assignPatient(const std::string& patientID);
        bool unassignPatient(const std::string& patientID);
        void updateLocation(const std::string& newLocation);
        void updateStatus(AvailabilityStatus newStatus);
        bool canTakeMorePatients() const;
        void startShift(ShiftType shift);
        void endShift();

        // Utility Methods
        bool isAvailable() const;
        bool isOnDuty() const;
        bool hasPatient(const std::string& patientID) const;
        double getWorkloadPercentage() const;
        int getRemainingCapacity() const;

        // Getters
        std::string getStaffID() const { return staffID; }
        std::string getName() const { return name; }
        StaffRole getRole() const { return role; }
        Specialization getSpecialization() const { return specialization; }
        std::string getCurrentLocation() const { return currentLocation; }
        AvailabilityStatus getStatus() const { return status; }
        ShiftType getCurrentShift() const { return currentShift; }
        std::vector<std::string> getAssignedPatients() const { return assignedPatients; }
        std::vector<std::string> getQualifications() const { return qualifications; }
        int getYearsOfExperience() const { return yearsOfExperience; }
        std::string getContactNumber() const { return contactNumber; }
        std::string getEmail() const { return email; }
        time_t getShiftStartTime() const { return shiftStartTime; }
        time_t getShiftEndTime() const { return shiftEndTime; }
        int getCurrentWorkload() const { return currentWorkload; }
        int getMaxWorkload() const { return maxWorkload; }
        double getResponseTime() const { return responseTime; }

        // Setters
        void setStaffID(const std::string& id) { staffID = id; }
        void setName(const std::string& n) { name = n; }
        void setRole(StaffRole r) { role = r; }
        void setSpecialization(Specialization s) { specialization = s; }
        void setCurrentLocation(const std::string& loc) { currentLocation = loc; }
        void setStatus(AvailabilityStatus s) { status = s; }
        void setCurrentShift(ShiftType s) { currentShift = s; }
        void addQualification(const std::string& qual) { qualifications.push_back(qual); }
        void setYearsOfExperience(int years) { yearsOfExperience = years; }
        void setContactNumber(const std::string& num) { contactNumber = num; }
        void setEmail(const std::string& e) { email = e; }
        void setMaxWorkload(int max) { maxWorkload = max; }
        void setResponseTime(double time) { responseTime = time; }

        // Utility Methods
        std::string toString() const;
        std::string getRoleString() const;
        std::string getSpecializationString() const;
        std::string getStatusString() const;
        std::string getShiftString() const;
        void display() const;

        // Comparison operators
        bool operator==(const MedicalStaff& other) const;
        bool operator!=(const MedicalStaff& other) const;
        bool operator<(const MedicalStaff& other) const;  // For sorting by workload
    };

    // Stream operator
    std::ostream& operator<<(std::ostream& os, const MedicalStaff& staff);

} // namespace Core

#endif // MEDICAL_STAFF_HPP