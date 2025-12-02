// src/core/Patient.cpp
#include "../../include/core/Patient.hpp"

namespace HEROS {

// ==================== CONSTRUCTORS ====================

Patient::Patient() 
    : patientID(generateID("PAT")),
      name("Unknown"),
      age(0),
      severityScore(0),
      arrivalTime(getCurrentTimestamp()),
      location("RECEPTION"),
      vitalSigns(),
      triageStatus(TriageStatus::GREEN),
      assignedStaffID(""),
      chiefComplaint("Not specified"),
      isProcessed(false) {
    updateSeverity();
}

Patient::Patient(const std::string& name, int age, const std::string& complaint)
    : patientID(generateID("PAT")),
      name(name),
      age(age),
      severityScore(0),
      arrivalTime(getCurrentTimestamp()),
      location("RECEPTION"),
      vitalSigns(),
      triageStatus(TriageStatus::GREEN),
      assignedStaffID(""),
      chiefComplaint(complaint),
      isProcessed(false) {
    updateSeverity();
}

Patient::Patient(const std::string& id, const std::string& name, int age,
                 const VitalSigns& vitals, const std::string& complaint)
    : patientID(id),
      name(name),
      age(age),
      severityScore(0),
      arrivalTime(getCurrentTimestamp()),
      location("RECEPTION"),
      vitalSigns(vitals),
      triageStatus(TriageStatus::GREEN),
      assignedStaffID(""),
      chiefComplaint(complaint),
      isProcessed(false) {
    updateSeverity();
}

Patient::Patient(const Patient& other) 
    : patientID(other.patientID),
      name(other.name),
      age(other.age),
      severityScore(other.severityScore),
      arrivalTime(other.arrivalTime),
      location(other.location),
      vitalSigns(other.vitalSigns),
      triageStatus(other.triageStatus),
      assignedStaffID(other.assignedStaffID),
      chiefComplaint(other.chiefComplaint),
      isProcessed(other.isProcessed) {
}

Patient& Patient::operator=(const Patient& other) {
    if (this != &other) {
        patientID = other.patientID;
        name = other.name;
        age = other.age;
        severityScore = other.severityScore;
        arrivalTime = other.arrivalTime;
        location = other.location;
        vitalSigns = other.vitalSigns;
        triageStatus = other.triageStatus;
        assignedStaffID = other.assignedStaffID;
        chiefComplaint = other.chiefComplaint;
        isProcessed = other.isProcessed;
    }
    return *this;
}

// ==================== SEVERITY CALCULATION ====================

int Patient::calculateSeverity() const {
    // Base severity from vital signs (0-100)
    int vitalScore = vitalSigns.calculateVitalScore();
    
    // Wait time factor (increases priority over time)
    double waitMinutes = getWaitTimeMinutes();
    int waitScore = static_cast<int>(std::min(30.0, waitMinutes / 2.0)); // Max 30 points
    
    // Age factor (very young and elderly get higher priority)
    int ageScore = 0;
    if (age < 5 || age > 75) ageScore = 15;
    else if (age < 12 || age > 65) ageScore = 10;
    else if (age < 18 || age > 55) ageScore = 5;
    
    // Combined severity (capped at 100)
    int totalSeverity = vitalScore + waitScore + ageScore;
    return std::min(100, totalSeverity);
}

void Patient::updateSeverity() {
    severityScore = calculateSeverity();
    
    // Update triage status based on severity
    if (severityScore >= 80) {
        triageStatus = TriageStatus::RED;
    } else if (severityScore >= 50) {
        triageStatus = TriageStatus::YELLOW;
    } else if (severityScore >= 20) {
        triageStatus = TriageStatus::GREEN;
    } else {
        triageStatus = TriageStatus::WHITE;
    }
}

// ==================== COMPARISON OPERATORS ====================
// For Min-Heap: HIGHER severity = HIGHER priority = comes FIRST
// So we use REVERSE comparison (patient with higher severity is "smaller")

bool Patient::operator<(const Patient& other) const {
    // Higher severity should come first (treated as "smaller" for min-heap)
    if (severityScore != other.severityScore) {
        return severityScore > other.severityScore; // Reverse!
    }
    // If same severity, earlier arrival has priority
    return arrivalTime < other.arrivalTime;
}

bool Patient::operator>(const Patient& other) const {
    return other < *this;
}

bool Patient::operator<=(const Patient& other) const {
    return !(other < *this);
}

bool Patient::operator>=(const Patient& other) const {
    return !(*this < other);
}

bool Patient::operator==(const Patient& other) const {
    return patientID == other.patientID;
}

// ==================== GETTERS ====================

double Patient::getWaitTimeMinutes() const {
    time_t now = getCurrentTimestamp();
    return difftime(now, arrivalTime) / 60.0;
}

// ==================== SETTERS ====================

void Patient::setVitalSigns(const VitalSigns& vitals) {
    vitalSigns = vitals;
    updateSeverity();
}

// ==================== UTILITY FUNCTIONS ====================

void Patient::print() const {
    std::cout << "\n======== Patient Information ========" << std::endl;
    std::cout << "ID: " << patientID << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Chief Complaint: " << chiefComplaint << std::endl;
    std::cout << "Severity Score: " << severityScore << "/100" << std::endl;
    std::cout << "Triage Status: " << triageStatusToString(triageStatus) << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Wait Time: " << std::fixed << std::setprecision(1) 
              << getWaitTimeMinutes() << " minutes" << std::endl;
    std::cout << "Arrival: " << formatTimestamp(arrivalTime) << std::endl;
    std::cout << "Assigned Staff: " << (assignedStaffID.empty() ? "None" : assignedStaffID) << std::endl;
    std::cout << "Processed: " << (isProcessed ? "Yes" : "No") << std::endl;
    std::cout << "--- Vital Signs ---" << std::endl;
    std::cout << "Heart Rate: " << vitalSigns.heartRate << " bpm" << std::endl;
    std::cout << "Blood Pressure: " << vitalSigns.bloodPressureSys << "/" 
              << vitalSigns.bloodPressureDia << " mmHg" << std::endl;
    std::cout << "Temperature: " << vitalSigns.temperature << " °C" << std::endl;
    std::cout << "O2 Saturation: " << vitalSigns.oxygenSaturation << "%" << std::endl;
    std::cout << "Respiratory Rate: " << vitalSigns.respiratoryRate << " /min" << std::endl;
    std::cout << "=====================================\n" << std::endl;
}

std::string Patient::getSummary() const {
    std::stringstream ss;
    ss << patientID << " | " << name << " | Severity: " << severityScore 
       << " | " << triageStatusToString(triageStatus);
    return ss.str();
}

bool Patient::needsImmediateAttention() const {
    return triageStatus == TriageStatus::RED || severityScore >= 80;
}

bool Patient::isValid() const {
    return !patientID.empty() && !name.empty() && age >= 0 && age <= 150;
}

} // namespace HEROS