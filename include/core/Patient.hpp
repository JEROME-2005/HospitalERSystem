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
    int severityScore;
    time_t arrivalTime;
    std::string location;
    VitalSigns vitalSigns;
    TriageStatus triageStatus;
    std::string chiefComplaint;
    std::string assignedStaffID;
    bool isProcessed;

public:
    // Constructors
    Patient();
    Patient(const std::string& id, const std::string& name, int age);
    Patient(const std::string& id, const std::string& name, int age, 
            const VitalSigns& vitals, const std::string& complaint);
    
    // Copy constructor and assignment
    Patient(const Patient& other);
    Patient& operator=(const Patient& other);
    
    // Destructor
    ~Patient() = default;
    
    // Severity calculation - combines vitals + wait time
    int calculateSeverity() const;
    void updateSeverity();
    
    // Comparison operators for heap
    bool operator<(const Patient& other) const;
    bool operator>(const Patient& other) const;
    bool operator==(const Patient& other) const;
    
    // Getters
    std::string getPatientID() const { return patientID; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    int getSeverityScore() const { return severityScore; }
    time_t getArrivalTime() const { return arrivalTime; }
    std::string getLocation() const { return location; }
    VitalSigns getVitalSigns() const { return vitalSigns; }
    TriageStatus getTriageStatus() const { return triageStatus; }
    std::string getChiefComplaint() const { return chiefComplaint; }
    std::string getAssignedStaffID() const { return assignedStaffID; }
    bool getIsProcessed() const { return isProcessed; }
    double getWaitTimeMinutes() const;
    
    // Setters
    void setPatientID(const std::string& id) { patientID = id; }
    void setName(const std::string& n) { name = n; }
    void setAge(int a) { age = a; }
    void setSeverityScore(int score) { severityScore = score; }
    void setLocation(const std::string& loc) { location = loc; }
    void setVitalSigns(const VitalSigns& vitals);
    void setTriageStatus(TriageStatus status) { triageStatus = status; }
    void setChiefComplaint(const std::string& complaint) { chiefComplaint = complaint; }
    void setAssignedStaffID(const std::string& staffID) { assignedStaffID = staffID; }
    void setIsProcessed(bool processed) { isProcessed = processed; }
    
    // Utility
    std::string toString() const;
    void printInfo() const;
    
    // Static helper for severity calculation from vitals
    static int calculateVitalityScore(const VitalSigns& vitals);
};

} // namespace HEROS

#endif // PATIENT_HPP