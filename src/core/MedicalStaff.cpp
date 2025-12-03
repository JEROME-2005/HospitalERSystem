#include "../../include/core/MedicalStaff.hpp"
#include <iostream>

MedicalStaff::MedicalStaff() 
    : staffID("S000"), name("Unknown"), role(StaffRole::NURSE),
      currentLocation("STATION"), status(AvailabilityStatus::AVAILABLE),
      assignedPatientID("") {}

MedicalStaff::MedicalStaff(const std::string& id, const std::string& staffName, StaffRole r)
    : staffID(id), name(staffName), role(r), currentLocation("STATION"),
      status(AvailabilityStatus::AVAILABLE), assignedPatientID("") {}

void MedicalStaff::assignToPatient(const std::string& patientID) {
    assignedPatientID = patientID;
    status = AvailabilityStatus::BUSY;
}

void MedicalStaff::clearAssignment() {
    assignedPatientID = "";
    status = AvailabilityStatus::AVAILABLE;
}

std::string MedicalStaff::getRoleString() const {
    switch(role) {
        case StaffRole::DOCTOR: return "Doctor";
        case StaffRole::NURSE: return "Nurse";
        case StaffRole::TECHNICIAN: return "Technician";
        case StaffRole::PARAMEDIC: return "Paramedic";
        case StaffRole::SPECIALIST: return "Specialist";
        default: return "Unknown";
    }
}

std::string MedicalStaff::getStatusString() const {
    switch(status) {
        case AvailabilityStatus::AVAILABLE: return "Available";
        case AvailabilityStatus::BUSY: return "Busy";
        case AvailabilityStatus::ON_BREAK: return "On Break";
        case AvailabilityStatus::OFF_DUTY: return "Off Duty";
        case AvailabilityStatus::EMERGENCY_CALL: return "Emergency Call";
        default: return "Unknown";
    }
}

void MedicalStaff::display() const {
    std::cout << staffID << " - " << name << " (" << getRoleString() << ") - " 
              << getStatusString() << " at " << currentLocation << "\n";
}