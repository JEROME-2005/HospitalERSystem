#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include <ctime>
#include <vector>
#include <iostream>

namespace Core {

    // Vital Signs Structure
    struct VitalSigns {
        double heartRate;        // beats per minute (60-100 normal)
        double bloodPressureSys; // systolic (90-120 normal)
        double bloodPressureDia; // diastolic (60-80 normal)
        double oxygenSaturation; // percentage (95-100 normal)
        double temperature;      // celsius (36.1-37.2 normal)
        double respiratoryRate;  // breaths per minute (12-20 normal)

        VitalSigns() : heartRate(80), bloodPressureSys(120), bloodPressureDia(80),
                       oxygenSaturation(98), temperature(36.6), respiratoryRate(16) {}

        VitalSigns(double hr, double bpS, double bpD, double o2, double temp, double rr)
            : heartRate(hr), bloodPressureSys(bpS), bloodPressureDia(bpD),
              oxygenSaturation(o2), temperature(temp), respiratoryRate(rr) {}
    };

    // Triage Status Enum (WHO Triage Tags)
    enum class TriageStatus {
        RED = 1,      // Immediate - Life threatening
        YELLOW = 2,   // Delayed - Serious but stable
        GREEN = 3,    // Minor - Walking wounded
        BLACK = 4,    // Deceased/Expectant
        WHITE = 5     // Not yet triaged
    };

    // Patient Condition Enum
    enum class PatientCondition {
        CRITICAL,
        SERIOUS,
        STABLE,
        FAIR,
        GOOD
    };

    class Patient {
    private:
        std::string patientID;
        std::string name;
        int age;
        std::string gender;
        int severityScore;         // 1-100 (higher = more severe)
        time_t arrivalTime;
        std::string location;      // Current room/location
        VitalSigns vitalSigns;
        TriageStatus status;
        PatientCondition condition;
        std::string chiefComplaint;
        std::vector<std::string> medicalHistory;
        bool isEmergency;
        std::string assignedDoctor;
        std::string assignedNurse;

    public:
        // Constructors
        Patient();
        Patient(const std::string& id, const std::string& name, int age, 
                const std::string& gender, const std::string& complaint);
        Patient(const Patient& other);
        
        // Destructor
        ~Patient();

        // Assignment operator
        Patient& operator=(const Patient& other);

        // Core Methods
        int calculateSeverity() const;
        void updateVitalSigns(const VitalSigns& newVitals);
        void updateTriageStatus();
        double getWaitTime() const;
        
        // Comparison operators for heap
        bool operator<(const Patient& other) const;
        bool operator>(const Patient& other) const;
        bool operator==(const Patient& other) const;
        bool operator!=(const Patient& other) const;

        // Getters
        std::string getPatientID() const { return patientID; }
        std::string getName() const { return name; }
        int getAge() const { return age; }
        std::string getGender() const { return gender; }
        int getSeverityScore() const { return severityScore; }
        time_t getArrivalTime() const { return arrivalTime; }
        std::string getLocation() const { return location; }
        VitalSigns getVitalSigns() const { return vitalSigns; }
        TriageStatus getTriageStatus() const { return status; }
        PatientCondition getCondition() const { return condition; }
        std::string getChiefComplaint() const { return chiefComplaint; }
        std::vector<std::string> getMedicalHistory() const { return medicalHistory; }
        bool getIsEmergency() const { return isEmergency; }
        std::string getAssignedDoctor() const { return assignedDoctor; }
        std::string getAssignedNurse() const { return assignedNurse; }

        // Setters
        void setPatientID(const std::string& id) { patientID = id; }
        void setName(const std::string& n) { name = n; }
        void setAge(int a) { age = a; }
        void setGender(const std::string& g) { gender = g; }
        void setSeverityScore(int score) { severityScore = score; }
        void setArrivalTime(time_t t) { arrivalTime = t; }
        void setLocation(const std::string& loc) { location = loc; }
        void setVitalSigns(const VitalSigns& vs) { vitalSigns = vs; }
        void setTriageStatus(TriageStatus s) { status = s; }
        void setCondition(PatientCondition c) { condition = c; }
        void setChiefComplaint(const std::string& cc) { chiefComplaint = cc; }
        void addMedicalHistory(const std::string& history) { medicalHistory.push_back(history); }
        void setIsEmergency(bool emergency) { isEmergency = emergency; }
        void setAssignedDoctor(const std::string& doctor) { assignedDoctor = doctor; }
        void setAssignedNurse(const std::string& nurse) { assignedNurse = nurse; }

        // Utility Methods
        std::string toString() const;
        std::string getTriageStatusString() const;
        std::string getConditionString() const;
        void display() const;

        // Static Helper Methods
        static std::string generatePatientID(const std::string& wardPrefix);
        static int calculateVitalScore(const VitalSigns& vitals);
    };

    // Stream operator for easy printing
    std::ostream& operator<<(std::ostream& os, const Patient& patient);

} // namespace Core

#endif // PATIENT_HPP