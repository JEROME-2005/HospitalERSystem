#ifndef DATA_VALIDATOR_HPP
#define DATA_VALIDATOR_HPP

#include "../core/Patient.hpp"
#include "../core/HospitalRoom.hpp"
#include <string>

class DataValidator {
public:
    // Patient validation
    static bool validatePatientData(const Patient& patient);
    static bool validateVitalSigns(const VitalSigns& vitals);
    static bool validatePatientID(const std::string& id);
    
    // Room validation
    static bool validateRoomData(const HospitalRoom& room);
    static bool validateCoordinates(const Coordinates& coords);
    
    // General validation
    static bool validateNonEmpty(const std::string& str);
    static bool validatePositiveNumber(double num);
    
    // Display errors
    static void displayValidationErrors(const std::string& context);
};

#endif // DATA_VALIDATOR_HPP