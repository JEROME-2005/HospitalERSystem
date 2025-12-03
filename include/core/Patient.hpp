#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include <ctime>
#include <iostream>

enum class TriageStatus {
    PENDING,
    IN_TREATMENT,
    STABILIZED,
    CRITICAL,
    DISCHARGED
};

struct VitalSigns {
    int heartRate;        // bpm
    int bloodPressure;    // systolic
    int oxygenLevel;      // percentage
    double temperature;   // Celsius
    
    VitalSigns() : heartRate(80), bloodPressure(120), 
                   oxygenLevel(98), temperature(37.0) {}
};

class Patient {
private:
    std::string patientID;
    int severityScore;
    time_t arrivalTime;
    std::string location;
    VitalSigns vitalSigns;
    TriageStatus status;

public:
    // Constructors
    Patient();
    Patient(const std::string& id, const VitalSigns& vitals, const std::string& loc);
    
    // Getters
    std::string getPatientID() const { return patientID; }
    int getSeverityScore() const { return severityScore; }
    time_t getArrivalTime() const { return arrivalTime; }
    std::string getLocation() const { return location; }
    VitalSigns getVitalSigns() const { return vitalSigns; }
    TriageStatus getStatus() const { return status; }
    
    // Setters
    void setLocation(const std::string& loc) { location = loc; }
    void setStatus(TriageStatus s) { status = s; }
    void setVitalSigns(const VitalSigns& vitals);
    
    // Core functionality
    int calculateSeverity() const;  // Complexity: O(1)
    void updateSeverity();
    
    // Comparison operator for heap
    bool operator>(const Patient& other) const {
        return severityScore < other.severityScore; // Lower score = higher priority
    }
    
    bool operator<(const Patient& other) const {
        return severityScore > other.severityScore;
    }
    
    // Display
    void display() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif // PATIENT_HPP