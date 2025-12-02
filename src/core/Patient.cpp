// src/core/Patient.cpp
#include "../../include/core/Patient.hpp"

namespace HEROS {

// Default constructor
Patient::Patient() 
    : patientID(""), name("Unknown"), age(0), severityScore(50),
      arrivalTime(std::time(nullptr)), location("LOBBY"),
      vitalSigns(), triageStatus(TriageStatus::GREEN),
      chiefComplaint(""), assignedStaffID(""), isProcessed(false) {
}

// Basic constructor
Patient::Patient(const std::string& id, const std::string& patientName, int patientAge)
    : patientID(id), name(patientName), age(patientAge), severityScore(50),
      arrivalTime(std::time(nullptr)), location("LOBBY"),
      vitalSigns(), triageStatus(TriageStatus::GREEN),
      chiefComplaint(""), assignedStaffID(""), isProcessed(false) {
    updateSeverity();
}

// Full constructor
Patient::Patient(const std::string& id, const std::string& patientName, int patientAge,
                 const VitalSigns& vitals, const std::string& complaint)
    : patientID(id), name(patientName), age(patientAge), severityScore(50),
      arrivalTime(std::time(nullptr)), location("LOBBY"),
      vitalSigns(vitals), triageStatus(TriageStatus::GREEN),
      chiefComplaint(complaint), assignedStaffID(""), isProcessed(false) {
    updateSeverity();
}

// Copy constructor
Patient::Patient(const Patient& other)
    : patientID(other.patientID), name(other.name), age(other.age),
      severityScore(other.severityScore), arrivalTime(other.arrivalTime),
      location(other.location), vitalSigns(other.vitalSigns),
      triageStatus(other.triageStatus), chiefComplaint(other.chiefComplaint),
      assignedStaffID(other.assignedStaffID), isProcessed(other.isProcessed) {
}

// Assignment operator
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
        chiefComplaint = other.chiefComplaint;
        assignedStaffID = other.assignedStaffID;
        isProcessed = other.isProcessed;
    }
    return *this;
}

// Calculate severity score based on vitals and wait time
int Patient::calculateSeverity() const {
    int vitalScore = calculateVitalityScore(vitalSigns);
    double waitMinutes = getWaitTimeMinutes();
    
    // Wait time adds urgency (max 20 points for waiting > 60 minutes)
    int waitScore = static_cast<int>(std::min(waitMinutes / 3.0, 20.0));
    
    // Age factor (elderly and children get priority)
    int ageScore = 0;
    if (age < 5 || age > 70) ageScore = 10;
    else if (age < 12 || age > 60) ageScore = 5;
    
    return vitalScore + waitScore + ageScore;
}

void Patient::updateSeverity() {
    severityScore = calculateSeverity();
    
    // Update triage status based on severity
    if (severityScore >= 80) triageStatus = TriageStatus::RED;
    else if (severityScore >= 50) triageStatus = TriageStatus::YELLOW;
    else triageStatus = TriageStatus::GREEN;
}

// Static method to calculate score from vitals
int Patient::calculateVitalityScore(const VitalSigns& vitals) {
    int score = 0;
    
    // Heart rate scoring (normal: 60-100)
    if (vitals.heartRate < 40 || vitals.heartRate > 150) score += 30;
    else if (vitals.heartRate < 50 || vitals.heartRate > 120) score += 15;
    else if (vitals.heartRate < 60 || vitals.heartRate > 100) score += 5;
    
    // Blood pressure scoring (systolic normal: 90-120)
    if (vitals.bloodPressureSys < 70 || vitals.bloodPressureSys > 180) score += 30;
    else if (vitals.bloodPressureSys < 80 || vitals.bloodPressureSys > 160) score += 15;
    else if (vitals.bloodPressureSys < 90 || vitals.bloodPressureSys > 140) score += 5;
    
    // Oxygen saturation scoring (normal: 95-100)
    if (vitals.oxygenSaturation < 85) score += 30;
    else if (vitals.oxygenSaturation < 90) score += 20;
    else if (vitals.oxygenSaturation < 95) score += 10;
    
    // Temperature scoring (normal: 36.1-37.2)
    if (vitals.temperature < 35 || vitals.temperature > 40) score += 20;
    else if (vitals.temperature < 36 || vitals.temperature > 39) score += 10;
    else if (vitals.temperature < 36.1 || vitals.temperature > 38) score += 5;
    
    // Respiratory rate scoring (normal: 12-20)
    if (vitals.respiratoryRate < 8 || vitals.respiratoryRate > 30) score += 20;
    else if (vitals.respiratoryRate < 10 || vitals.respiratoryRate > 25) score += 10;
    else if (vitals.respiratoryRate < 12 || vitals.respiratoryRate > 20) score += 5;
    
    return score;
}

// Comparison operators - lower score = lower priority in MIN heap
// We want HIGHER severity to have LOWER value for min-heap extraction first
bool Patient::operator<(const Patient& other) const {
    // Higher severity score should come out first (be "less" in min-heap)
    return severityScore > other.severityScore;
}

bool Patient::operator>(const Patient& other) const {
    return severityScore < other.severityScore;
}

bool Patient::operator==(const Patient& other) const {
    return patientID == other.patientID;
}

double Patient::getWaitTimeMinutes() const {
    time_t now = std::time(nullptr);
    double diffSeconds = std::difftime(now, arrivalTime);
    return diffSeconds / 60.0;
}

void Patient::setVitalSigns(const VitalSigns& vitals) {
    vitalSigns = vitals;
    updateSeverity();
}

std::string Patient::toString() const {
    std::stringstream ss;
    ss << "Patient[ID=" << patientID 
       << ", Name=" << name 
       << ", Age=" << age
       << ", Severity=" << severityScore
       << ", Status=" << triageStatusToString(triageStatus)
       << ", Location=" << location
       << ", Wait=" << std::fixed << std::setprecision(1) << getWaitTimeMinutes() << "min"
       << "]";
    return ss.str();
}

void Patient::printInfo() const {
    std::cout << "\n========== PATIENT INFORMATION ==========" << std::endl;
    std::cout << "ID:              " << patientID << std::endl;
    std::cout << "Name:            " << name << std::endl;
    std::cout << "Age:             " << age << std::endl;
    std::cout << "Severity Score:  " << severityScore << std::endl;
    std::cout << "Triage Status:   " << triageStatusToString(triageStatus) << std::endl;
    std::cout << "Location:        " << location << std::endl;
    std::cout << "Chief Complaint: " << chiefComplaint << std::endl;
    std::cout << "Wait Time:       " << std::fixed << std::setprecision(1) 
              << getWaitTimeMinutes() << " minutes" << std::endl;
    std::cout << "Assigned Staff:  " << (assignedStaffID.empty() ? "None" : assignedStaffID) << std::endl;
    std::cout << "Processed:       " << (isProcessed ? "Yes" : "No") << std::endl;
    std::cout << "\n--- Vital Signs ---" << std::endl;
    std::cout << "Heart Rate:      " << vitalSigns.heartRate << " bpm" << std::endl;
    std::cout << "Blood Pressure:  " << vitalSigns.bloodPressureSys << "/" 
              << vitalSigns.bloodPressureDia << " mmHg" << std::endl;
    std::cout << "Temperature:     " << vitalSigns.temperature << " °C" << std::endl;
    std::cout << "O2 Saturation:   " << vitalSigns.oxygenSaturation << "%" << std::endl;
    std::cout << "Respiratory Rate:" << vitalSigns.respiratoryRate << " breaths/min" << std::endl;
    std::cout << "==========================================" << std::endl;
}

} // namespace HEROS