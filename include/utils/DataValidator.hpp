#ifndef DATA_VALIDATOR_HPP
#define DATA_VALIDATOR_HPP

#include "../core/Patient.hpp"
#include "../core/HospitalRoom.hpp"
#include "../core/MedicalStaff.hpp"
#include "../algorithms/Graph.hpp"
#include <string>
#include <vector>

namespace Utils {

    /**
     * Validation Result Structure
     */
    struct ValidationResult {
        bool isValid;
        std::vector<std::string> errors;
        std::vector<std::string> warnings;

        ValidationResult() : isValid(true) {}
        
        void addError(const std::string& error) {
            errors.push_back(error);
            isValid = false;
        }
        
        void addWarning(const std::string& warning) {
            warnings.push_back(warning);
        }

        std::string toString() const;
    };

    /**
     * DataValidator Class
     * 
     * Provides validation methods for all hospital data.
     * Ensures data integrity before processing.
     */
    class DataValidator {
    public:
        // Patient Validation
        static ValidationResult validatePatient(const Core::Patient& patient);
        static ValidationResult validatePatientID(const std::string& patientID);
        static ValidationResult validateVitalSigns(const Core::VitalSigns& vitals);
        static bool isValidPatientAge(int age);
        static bool isValidSeverityScore(int score);

        // Hospital Room Validation
        static ValidationResult validateHospitalRoom(const Core::HospitalRoom& room);
        static ValidationResult validateRoomCapacity(int capacity, int occupancy);
        static bool isValidRoomID(const std::string& roomID);
        static bool isValidCoordinates(const Core::Coordinates& coords);

        // Medical Staff Validation
        static ValidationResult validateMedicalStaff(const Core::MedicalStaff& staff);
        static bool isValidStaffID(const std::string& staffID);
        static bool isValidWorkload(int current, int max);

        // Graph Validation
        static ValidationResult validateHospitalLayout(const Algorithms::Graph& layout);
        static bool isValidEdgeWeight(double weight);
        static bool hasValidConnectivity(const Algorithms::Graph& layout);

        // Batch Validation
        static ValidationResult validatePatientBatch(const std::vector<Core::Patient>& patients);
        static ValidationResult validateRoomBatch(const std::vector<Core::HospitalRoom>& rooms);
        static ValidationResult validateStaffBatch(const std::vector<Core::MedicalStaff>& staff);

        // String Validation Utilities
        static bool isAlphanumeric(const std::string& str);
        static bool isNumeric(const std::string& str);
        static bool isValidEmail(const std::string& email);
        static bool isValidPhoneNumber(const std::string& phone);
        static bool hasValidLength(const std::string& str, size_t minLen, size_t maxLen);

        // Range Validation
        template<typename T>
        static bool isInRange(T value, T min, T max) {
            return value >= min && value <= max;
        }
    };

} // namespace Utils

#endif // DATA_VALIDATOR_HPP