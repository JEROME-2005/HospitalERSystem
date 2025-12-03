#ifndef EMERGENCY_RESPONSE_SYSTEM_HPP
#define EMERGENCY_RESPONSE_SYSTEM_HPP

#include "Patient.hpp"
#include "HospitalRoom.hpp"
#include "MedicalStaff.hpp"
#include "../data_structures/TriageQueue.hpp"
#include "../data_structures/StateStack.hpp"
#include "../data_structures/PatientState.hpp"
#include "../algorithms/Graph.hpp"
#include "../algorithms/DijkstraRouter.hpp"
#include "../algorithms/MSTGenerator.hpp"
#include "../utils/Simulation.hpp"

#include <vector>
#include <unordered_map>
#include <memory>

class EmergencyResponseSystem {
private:
    // Core components
    TriageQueue triageSystem;
    StateStack<PatientState> undoSystem;
    
    // Hospital infrastructure
    Graph hospitalLayout;
    std::unique_ptr<DijkstraRouter> staffRouter;
    std::unique_ptr<MSTGenerator> equipmentDistributor;
    
    // Registries
    std::unordered_map<std::string, Patient> patientRegistry;
    std::unordered_map<std::string, HospitalRoom> roomRegistry;
    std::unordered_map<std::string, MedicalStaff> staffRegistry;
    
    // System state
    bool systemInitialized;
    int totalPatientsRegistered;
    int totalStaffAssignments;

public:
    EmergencyResponseSystem();
    ~EmergencyResponseSystem();
    
    // Initialization
    void initializeHospitalLayout();
    void registerRooms();
    void registerStaff();
    
    // Emergency operations
    void registerNewPatient(const Patient& patient);                            // O(log n)
    void assignStaffToPatient(const std::string& staffID, const std::string& patientID);
    Patient processNextCriticalPatient();                                       // O(log n)
    
    // Resource optimization
    void optimizeEquipmentDistribution();                                       // O(E log E)
    RouteInfo findFastestRoute(const std::string& from, const std::string& to); // O((V+E) log V)
    
    // Undo functionality
    void undoLastOperation();                                                   // O(1)
    bool canUndo() const { return !undoSystem.isEmpty(); }
    
    // Reporting
    void generatePerformanceReport() const;
    void displaySystemStatus() const;
    void displayTriageQueue() const;
    
    // Simulation
    void simulateEmergencyScenario(const SimulationConfig& config);
    
    // Getters
    int getTotalPatientsRegistered() const { return totalPatientsRegistered; }
    int getPendingPatients() const { return triageSystem.getPendingCount(); }
};

#endif // EMERGENCY_RESPONSE_SYSTEM_HPP