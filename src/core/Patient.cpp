#include "../../include/core/Patient.hpp"
#include <sstream>
#include <iomanip>

Patient::Patient() 
    : patientID("P000"), severityScore(0), arrivalTime(std::time(nullptr)),
      location("ENTRANCE"), vitalSigns(), status(TriageStatus::PENDING) {}

Patient::Patient(const std::string& id, const VitalSigns& vitals, const std::string& loc)
    : patientID(id), severityScore(0), arrivalTime(std::time(nullptr)),
      location(loc), vitalSigns(vitals), status(TriageStatus::PENDING) {
    updateSeverity();
}

void Patient::setVitalSigns(const VitalSigns& vitals) {
    vitalSigns = vitals;
    updateSeverity();
}

int Patient::calculateSeverity() const {
    int score = 100;
    
    if (vitalSigns.heartRate < 50 || vitalSigns.heartRate > 120) score -= 30;
    else if (vitalSigns.heartRate < 60 || vitalSigns.heartRate > 100) score -= 15;
    
    if (vitalSigns.bloodPressure < 90 || vitalSigns.bloodPressure > 160) score -= 25;
    else if (vitalSigns.bloodPressure < 100 || vitalSigns.bloodPressure > 140) score -= 10;
    
    if (vitalSigns.oxygenLevel < 90) score -= 35;
    else if (vitalSigns.oxygenLevel < 95) score -= 20;
    
    if (vitalSigns.temperature > 39.0 || vitalSigns.temperature < 35.0) score -= 15;
    
    time_t currentTime = std::time(nullptr);
    int waitMinutes = static_cast<int>((currentTime - arrivalTime) / 60);
    score -= (waitMinutes / 10);
    
    return std::max(0, score);
}

void Patient::updateSeverity() {
    severityScore = calculateSeverity();
}

void Patient::display() const {
    std::cout << "\n+-------------------------------------+\n";
    std::cout << "| Patient ID: " << std::setw(23) << std::left << patientID << " |\n";
    std::cout << "| Severity Score: " << std::setw(19) << severityScore << " |\n";
    std::cout << "| Location: " << std::setw(25) << location << " |\n";
    std::cout << "| Heart Rate: " << std::setw(23) << vitalSigns.heartRate << " |\n";
    std::cout << "| Blood Pressure: " << std::setw(19) << vitalSigns.bloodPressure << " |\n";
    std::cout << "| Oxygen Level: " << std::setw(21) << vitalSigns.oxygenLevel << "% |\n";
    std::cout << "| Temperature: " << std::setw(20) << std::fixed << std::setprecision(1) 
              << vitalSigns.temperature << "C |\n";
    std::cout << "+-------------------------------------+\n";
}

std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << "[" << p.patientID << " | Severity: " << p.severityScore << "]";
    return os;
}