// include/core/Patient.hpp
#ifndef PATIENT_HPP
#define PATIENT_HPP

#include "../utils/CommonTypes.hpp"

namespace HEROS {

class Patient {
private:
    std::string patientID;
    std::string name;
    int age;
    int severityScore;          // 0-100 (higher = more severe)
    time_t arrivalTime;
    std::string location;       // Current room ID
    VitalSigns vitalSigns;
    TriageStatus triageStatus;
    std::string assignedStaffID;
    std::string chiefComplaint;
    bool isProcessed;

public:
    // ==================== CONSTRUCTORS ====================
    
    Patient();
    Patient(const std::string& name, int age, const std::string& complaint);
    Patient(const std::string& id, const std::string& name, int age, 
            const VitalSigns& vitals, const std::string& complaint);
    
    // Copy constructor
    Patient(const Patient& other);
    
    // Assignment operator
    Patient& operator=(const Patient& other);
    
    // ==================== SEVERITY CALCULATION ====================
    
    // Calculate overall severity score combining vitals and wait time
    // This is the KEY function for triage priority
    int calculateSeverity() const;
    
    // Update severity score based on current conditions
    void updateSeverity();
    
    // ==================== COMPARISON OPERATORS ====================
    // Used by MinHeap for priority comparison
    
    bool operator<(const Patient& other) const;
    bool operator>(const Patient& other) const;
    bool operator<=(const Patient& other) const;
    bool operator>=(const Patient& other) const;
    bool operator==(const Patient& other) const;
    
    // ==================== GETTERS ====================
    
    std::string getPatientID() const { return patientID; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    int getSeverityScore() const { return severityScore; }
    time_t getArrivalTime() const { return arrivalTime; }
    std::string getLocation() const { return location; }
    VitalSigns getVitalSigns() const { return vitalSigns; }
    TriageStatus getTriageStatus() const { return triageStatus; }
    std::string getAssignedStaffID() const { return assignedStaffID; }
    std::string getChiefComplaint() const { return chiefComplaint; }
    bool getIsProcessed() const { return isProcessed; }
    
    // Get wait time in minutes
    double getWaitTimeMinutes() const;
    
    // ==================== SETTERS ====================
    
    void setPatientID(const std::string& id) { patientID = id; }
    void setName(const std::string& n) { name = n; }
    void setAge(int a) { age = a; }
    void setSeverityScore(int score) { severityScore = std::min(100, std::max(0, score)); }
    void setLocation(const std::string& loc) { location = loc; }
    void setVitalSigns(const VitalSigns& vitals);
    void setTriageStatus(TriageStatus status) { triageStatus = status; }
    void setAssignedStaffID(const std::string& staffID) { assignedStaffID = staffID; }
    void setIsProcessed(bool processed) { isProcessed = processed; }
    
    // ==================== UTILITY FUNCTIONS ====================
    
    // Print patient information
    void print() const;
    
    // Get brief summary
    std::string getSummary() const;
    
    // Check if patient needs immediate attention
    bool needsImmediateAttention() const;
    
    // Validate patient data
    bool isValid() const;
};

} // namespace HEROS

#endif // PATIENT_HPP