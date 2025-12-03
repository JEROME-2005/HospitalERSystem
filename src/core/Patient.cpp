#include "../../include/core/Patient.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

namespace Core {

    // Static patient ID counter
    static int patientCounter = 0;

    // ==================== CONSTRUCTORS ====================

    Patient::Patient() 
        : patientID(""), name("Unknown"), age(0), gender("Unknown"),
          severityScore(50), arrivalTime(time(nullptr)), location("TRIAGE"),
          status(TriageStatus::WHITE), condition(PatientCondition::STABLE),
          chiefComplaint("Not specified"), isEmergency(false),
          assignedDoctor(""), assignedNurse("") {}

    Patient::Patient(const std::string& id, const std::string& name, int age,
                     const std::string& gender, const std::string& complaint)
        : patientID(id), name(name), age(age), gender(gender),
          severityScore(50), arrivalTime(time(nullptr)), location("TRIAGE"),
          status(TriageStatus::WHITE), condition(PatientCondition::STABLE),
          chiefComplaint(complaint), isEmergency(false),
          assignedDoctor(""), assignedNurse("") {
        // Calculate initial severity
        severityScore = calculateSeverity();
        updateTriageStatus();
    }

    Patient::Patient(const Patient& other) 
        : patientID(other.patientID), name(other.name), age(other.age),
          gender(other.gender), severityScore(other.severityScore),
          arrivalTime(other.arrivalTime), location(other.location),
          vitalSigns(other.vitalSigns), status(other.status),
          condition(other.condition), chiefComplaint(other.chiefComplaint),
          medicalHistory(other.medicalHistory), isEmergency(other.isEmergency),
          assignedDoctor(other.assignedDoctor), assignedNurse(other.assignedNurse) {}

    Patient::~Patient() {}

    Patient& Patient::operator=(const Patient& other) {
        if (this != &other) {
            patientID = other.patientID;
            name = other.name;
            age = other.age;
            gender = other.gender;
            severityScore = other.severityScore;
            arrivalTime = other.arrivalTime;
            location = other.location;
            vitalSigns = other.vitalSigns;
            status = other.status;
            condition = other.condition;
            chiefComplaint = other.chiefComplaint;
            medicalHistory = other.medicalHistory;
            isEmergency = other.isEmergency;
            assignedDoctor = other.assignedDoctor;
            assignedNurse = other.assignedNurse;
        }
        return *this;
    }

    // ==================== CORE METHODS ====================

    int Patient::calculateSeverity() const {
        int vitalScore = calculateVitalScore(vitalSigns);
        double waitTime = getWaitTime();
        
        // Wait time increases severity (1 point per 10 minutes)
        int waitBonus = static_cast<int>(waitTime / 10.0);
        
        // Age factor (elderly and young children get priority)
        int ageFactor = 0;
        if (age < 5 || age > 70) {
            ageFactor = 10;
        } else if (age < 12 || age > 60) {
            ageFactor = 5;
        }
        
        // Emergency flag adds significant severity
        int emergencyBonus = isEmergency ? 20 : 0;
        
        // Calculate total (capped at 100)
        int total = vitalScore + waitBonus + ageFactor + emergencyBonus;
        return std::min(100, std::max(1, total));
    }

    void Patient::updateVitalSigns(const VitalSigns& newVitals) {
        vitalSigns = newVitals;
        severityScore = calculateSeverity();
        updateTriageStatus();
    }

    void Patient::updateTriageStatus() {
        if (severityScore >= 80) {
            status = TriageStatus::RED;
            condition = PatientCondition::CRITICAL;
        } else if (severityScore >= 60) {
            status = TriageStatus::YELLOW;
            condition = PatientCondition::SERIOUS;
        } else if (severityScore >= 40) {
            status = TriageStatus::GREEN;
            condition = PatientCondition::STABLE;
        } else {
            status = TriageStatus::GREEN;
            condition = PatientCondition::GOOD;
        }
    }

    double Patient::getWaitTime() const {
        time_t now = time(nullptr);
        double diffMinutes = difftime(now, arrivalTime) / 60.0;
        return diffMinutes;
    }

    // ==================== COMPARISON OPERATORS ====================

    bool Patient::operator<(const Patient& other) const {
        // Higher severity should be treated first (min-heap with negated comparison)
        // First compare by severity (higher is more urgent)
        if (severityScore != other.severityScore) {
            return severityScore > other.severityScore;
        }
        // If same severity, earlier arrival time has priority
        return arrivalTime < other.arrivalTime;
    }

    bool Patient::operator>(const Patient& other) const {
        return other < *this;
    }

    bool Patient::operator==(const Patient& other) const {
        return patientID == other.patientID;
    }

    bool Patient::operator!=(const Patient& other) const {
        return !(*this == other);
    }

    // ==================== UTILITY METHODS ====================

    std::string Patient::toString() const {
        std::stringstream ss;
        ss << "Patient[ID=" << patientID << ", Name=" << name 
           << ", Severity=" << severityScore 
           << ", Triage=" << getTriageStatusString()
           << ", Location=" << location << "]";
        return ss.str();
    }

    std::string Patient::getTriageStatusString() const {
        switch (status) {
            case TriageStatus::RED: return "RED (Immediate)";
            case TriageStatus::YELLOW: return "YELLOW (Delayed)";
            case TriageStatus::GREEN: return "GREEN (Minor)";
            case TriageStatus::BLACK: return "BLACK (Deceased)";
            case TriageStatus::WHITE: return "WHITE (Pending)";
            default: return "UNKNOWN";
        }
    }

    std::string Patient::getConditionString() const {
        switch (condition) {
            case PatientCondition::CRITICAL: return "Critical";
            case PatientCondition::SERIOUS: return "Serious";
            case PatientCondition::STABLE: return "Stable";
            case PatientCondition::FAIR: return "Fair";
            case PatientCondition::GOOD: return "Good";
            default: return "Unknown";
        }
    }

    void Patient::display() const {
        std::cout << "========================================" << std::endl;
        std::cout << "PATIENT INFORMATION" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "ID:              " << patientID << std::endl;
        std::cout << "Name:            " << name << std::endl;
        std::cout << "Age:             " << age << std::endl;
        std::cout << "Gender:          " << gender << std::endl;
        std::cout << "Chief Complaint: " << chiefComplaint << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Severity Score:  " << severityScore << "/100" << std::endl;
        std::cout << "Triage Status:   " << getTriageStatusString() << std::endl;
        std::cout << "Condition:       " << getConditionString() << std::endl;
        std::cout << "Location:        " << location << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "VITAL SIGNS:" << std::endl;
        std::cout << "  Heart Rate:    " << vitalSigns.heartRate << " bpm" << std::endl;
        std::cout << "  Blood Pressure:" << vitalSigns.bloodPressureSys << "/" 
                  << vitalSigns.bloodPressureDia << " mmHg" << std::endl;
        std::cout << "  O2 Saturation: " << vitalSigns.oxygenSaturation << "%" << std::endl;
        std::cout << "  Temperature:   " << vitalSigns.temperature << " °C" << std::endl;
        std::cout << "  Respiratory:   " << vitalSigns.respiratoryRate << " /min" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Wait Time:       " << std::fixed << std::setprecision(1) 
                  << getWaitTime() << " minutes" << std::endl;
        std::cout << "Emergency:       " << (isEmergency ? "YES" : "NO") << std::endl;
        std::cout << "Assigned Doctor: " << (assignedDoctor.empty() ? "None" : assignedDoctor) << std::endl;
        std::cout << "Assigned Nurse:  " << (assignedNurse.empty() ? "None" : assignedNurse) << std::endl;
        std::cout << "========================================" << std::endl;
    }

    // ==================== STATIC METHODS ====================

    std::string Patient::generatePatientID(const std::string& wardPrefix) {
        std::stringstream ss;
        ss << wardPrefix << "-" << std::setfill('0') << std::setw(5) << (++patientCounter);
        return ss.str();
    }

    int Patient::calculateVitalScore(const VitalSigns& vitals) {
        int score = 0;
        
        // Heart rate scoring (normal: 60-100)
        if (vitals.heartRate < 40 || vitals.heartRate > 150) score += 25;
        else if (vitals.heartRate < 50 || vitals.heartRate > 120) score += 15;
        else if (vitals.heartRate < 60 || vitals.heartRate > 100) score += 5;
        
        // Blood pressure scoring (normal systolic: 90-120)
        if (vitals.bloodPressureSys < 70 || vitals.bloodPressureSys > 180) score += 25;
        else if (vitals.bloodPressureSys < 80 || vitals.bloodPressureSys > 160) score += 15;
        else if (vitals.bloodPressureSys < 90 || 