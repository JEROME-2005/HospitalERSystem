// src/core/MedicalStaff.cpp
#include "../../include/core/MedicalStaff.hpp"

namespace HEROS {

// Default constructor
MedicalStaff::MedicalStaff()
    : staffID(""), name("Unknown"), role(StaffRole::NURSE),
      currentLocation("LOBBY"), status(AvailabilityStatus::OFF_DUTY),
      specialization("General"), maxPatientLoad(5),
      shiftStartTime(std::time(nullptr)), shiftDurationHours(8) {
}

// Basic constructor
MedicalStaff::MedicalStaff(const std::string& id, const std::string& staffName, StaffRole staffRole)
    : staffID(id), name(staffName), role(staffRole),
      currentLocation("LOBBY"), status(AvailabilityStatus::AVAILABLE),
      specialization("General"), maxPatientLoad(staffRole == StaffRole::DOCTOR ? 10 : 15),
      shiftStartTime(std::time(nullptr)), shiftDurationHours(8) {
}

// Full constructor
MedicalStaff::MedicalStaff(const std::string& id, const std::string& staffName, 
                           StaffRole staffRole, const std::string& spec, int maxLoad)
    : staffID(id), name(staffName), role(staffRole),
      currentLocation("LOBBY"), status(AvailabilityStatus::AVAILABLE),
      specialization(spec), maxPatientLoad(maxLoad),
      shiftStartTime(std::time(nullptr)), shiftDurationHours(8) {
}

// Copy constructor
MedicalStaff::MedicalStaff(const MedicalStaff& other)
    : staffID(other.staffID), name(other.name), role(other.role),
      currentLocation(other.currentLocation), status(other.status),
      specialization(other.specialization), assignedPatientIDs(other.assignedPatientIDs),
      maxPatientLoad(other.maxPatientLoad), shiftStartTime(other.shiftStartTime),
      shiftDurationHours(other.shiftDurationHours) {
}

// Assignment operator
MedicalStaff& MedicalStaff::operator=(const MedicalStaff& other) {
    if (this != &other) {
        staffID = other.staffID;
        name = other.name;
        role = other.role;
        currentLocation = other.currentLocation;
        status = other.status;
        specialization = other.specialization;
        assignedPatientIDs = other.assignedPatientIDs;
        maxPatientLoad = other.maxPatientLoad;
        shiftStartTime = other.shiftStartTime;
        shiftDurationHours = other.shiftDurationHours;
    }
    return *this;
}

bool MedicalStaff::assignPatient(const std::string& patientID) {
    if (!canTakeMorePatients()) {
        return false;
    }
    
    if (hasPatient(patientID)) {
        return false;
    }
    
    assignedPatientIDs.push_back(patientID);
    
    if (!canTakeMorePatients()) {
        status = AvailabilityStatus::BUSY;
    }
    
    return true;
}

bool MedicalStaff::unassignPatient(const std::string& patientID) {
    auto it = std::find(assignedPatientIDs.begin(), assignedPatientIDs.end(), patientID);
    if (it != assignedPatientIDs.end()) {
        assignedPatientIDs.erase(it);
        if (status == AvailabilityStatus::BUSY && canTakeMorePatients()) {
            status = AvailabilityStatus::AVAILABLE;
        }
        return true;
    }
    return false;
}

bool MedicalStaff::hasPatient(const std::string& patientID) const {
    return std::find(assignedPatientIDs.begin(), assignedPatientIDs.end(), patientID) 
           != assignedPatientIDs.end();
}

bool MedicalStaff::canTakeMorePatients() const {
    return static_cast<int>(assignedPatientIDs.size()) < maxPatientLoad;
}

int MedicalStaff::getCurrentPatientCount() const {
    return static_cast<int>(assignedPatientIDs.size());
}

double MedicalStaff::getWorkloadPercentage() const {
    if (maxPatientLoad == 0) return 100.0;
    return (static_cast<double>(assignedPatientIDs.size()) / maxPatientLoad) * 100.0;
}

bool MedicalStaff::operator==(const MedicalStaff& other) const {
    return staffID == other.staffID;
}

bool MedicalStaff::operator<(const MedicalStaff& other) const {
    // Lower workload = higher priority (available first)
    return getWorkloadPercentage() < other.getWorkloadPercentage();
}

std::string MedicalStaff::toString() const {
    std::stringstream ss;
    ss << "Staff[ID=" << staffID 
       << ", Name=" << name
       << ", Role=" << staffRoleToString(role)
       << ", Patients=" << assignedPatientIDs.size() << "/" << maxPatientLoad
       << ", Location=" << currentLocation
       << "]";
    return ss.str();
}

void MedicalStaff::printInfo() const {
    std::cout << "\n========== STAFF INFORMATION ==========" << std::endl;
    std::cout << "ID:             " << staffID << std::endl;
    std::cout << "Name:           " << name << std::endl;
    std::cout << "Role:           " << staffRoleToString(role) << std::endl;
    std::cout << "Specialization: " << specialization << std::endl;
    std::cout << "Location:       " << currentLocation << std::endl;
    std::cout << "Status:         " << (status == AvailabilityStatus::AVAILABLE ? "Available" :
                                        status == AvailabilityStatus::BUSY ? "Busy" :
                                        status == AvailabilityStatus::ON_BREAK ? "On Break" : "Off Duty") << std::endl;
    std::cout << "Patient Load:   " << assignedPatientIDs.size() << "/" << maxPatientLoad 
              << " (" << std::fixed << std::setprecision(1) << getWorkloadPercentage() << "%)" << std::endl;
    
    std::cout << "Assigned Patients: ";
    if (assignedPatientIDs.empty()) {
        std::cout << "None";
    } else {
        for (size_t i = 0; i < assignedPatientIDs.size(); ++i) {
            std::cout << assignedPatientIDs[i];
            if (i < assignedPatientIDs.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
}

} // namespace HEROS