#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../core/Patient.hpp"
#include <vector>
#include <string>

struct SimulationConfig {
    int patientCount;
    int emergencyDuration;  // in minutes
    double criticalPatientRatio;
    bool enableLogging;
    
    SimulationConfig() : patientCount(50), emergencyDuration(120), 
                        criticalPatientRatio(0.3), enableLogging(true) {}
};

struct SimulationResults {
    int totalPatients;
    int criticalPatients;
    double averageWaitTime;
    double averageTreatmentTime;
    int successfulTreatments;
    double systemEfficiency;
    
    SimulationResults() : totalPatients(0), criticalPatients(0), 
                         averageWaitTime(0.0), averageTreatmentTime(0.0),
                         successfulTreatments(0), systemEfficiency(0.0) {}
};

class Simulation {
public:
    // Data generation
    static std::vector<Patient> generateSyntheticPatientData(int count);
    static Patient generateRandomPatient(int id);
    static VitalSigns generateRandomVitals(bool critical = false);
    
    // Simulation execution
    static SimulationResults runEmergencySimulation(const SimulationConfig& config);
    
    // Reporting
    static void displaySimulationResults(const SimulationResults& results);
    static void compareAlgorithmPerformance();
};

#endif // SIMULATION_HPP