#include "../../include/utils/DataValidator.hpp"
#include <iostream>

bool DataValidator::validatePatientData(const Patient& patient) {
    if (!validatePatientID(patient.getPatientID())) {
        std::cout << "✗ Invalid Patient ID\n";
        return false;
    }
    
    if (!validateVitalSigns(patient.getVitalSigns())) {
        std::cout << "✗ Invalid Vital Signs\n";
        return false;
    }
    
    return true;
}

bool DataValidator::validateVitalSigns(const VitalSigns& vitals) {
    if (vitals.heartRate < 0 || vitals.heartRate > 300) return false;
    if (vitals.bloodPressure < 0 || vitals.bloodPressure > 300) return false;
    if (vitals.oxygenLevel < 0 || vitals.oxygenLevel > 100) return false;
    if (vitals.temperature < 30.0 || vitals.temperature > 45.0) return false;
    
    return true;
}

bool DataValidator::validatePatientID(const std::string& id) {
    return !id.empty() && id.length() >= 3;
}

bool DataValidator::validateRoomData(const HospitalRoom& room) {
    return validateNonEmpty(room.getRoomID()) && 
           validateCoordinates(room.getPosition());
}

bool DataValidator::validateCoordinates(const Coordinates& coords) {
    return coords.x >= 0 && coords.y >= 0;
}

bool DataValidator::validateNonEmpty(const std::string& str) {
    return !str.empty();
}

bool DataValidator::validatePositiveNumber(double num) {
    return num > 0;
}

void DataValidator::displayValidationErrors(const std::string& context) {
    std::cout << "⚠ Validation Error in: " << context << "\n";
}