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
#include "../algorithms/RadixSorter.hpp"
#include "../algorithms/QuickSorter.hpp"
#include "../utils/PerformanceMonitor.hpp"
#include "../utils/DataValidator.hpp"
#include "../utils/Simulation.hpp"

#include <map>
#include <string>
#include <vector>

namespace Core {

    /**
     * System Performance Report
     */
    struct SystemPerformanceReport {
        // Patient Statistics
        int totalPatientsRegistered;
        int totalPatientsDischarged;
        int patientsInQueue;
        int criticalPatients;
        double averageWaitTimeMinutes;
        double averageTriageTimeMinutes;

        // Staff Statistics
        int totalStaffOnDuty;
        int availableStaff;
        double averageStaffUtilization;

        // Room Statistics
        int totalRooms;
        int occupiedRooms;
        double roomOccupancyRate;

        // Algorithm Performance
        double averageRoutingTimeMs;
        double mstCostSavingsPercent;
        int undoOperationsPerformed;

        // System Health
        std::string systemStatus;
        time_t reportGeneratedAt;

        SystemPerformanceReport();
        std::string toString() const;
    };

    /**
     * EmergencyResponseSystem Class
     * 
     * Central coordinator for the Hospital Emergency Response System.
     * Integrates all modules and provides unified API for emergency management.
     * 
     * Design Patterns Used:
     * - Singleton: Single system instance
     * - Observer: Staff status updates
     * - Factory: Patient/Room creation
     * - Strategy: Algorithm selection
     * - Command: Undo/Redo functionality
     */
    class EmergencyResponseSystem {
    private:
        // Core Components
        DataStructures::TriageQueue triageSystem;
        DataStructures::StateStack<DataStructures::PatientState> undoStack;
        Algorithms::Graph hospitalLayout;
        Algorithms::DijkstraRouter staffRouter;
        Algorithms::MSTGenerator equipmentDistributor;
        Algorithms::RadixSorter patientSorter;
        Algorithms::QuickSorter comparativeSorter;

        // Data Registries
        std::map<std::string, Patient> patientRegistry;
        std::map<std::string, HospitalRoom> roomRegistry;
        std::map<std::string, MedicalStaff> staffRegistry;

        // System State
        bool isInitialized;
        bool isEmergencyMode;
        std::string systemID;
        time_t systemStartTime;

        // Configuration
        int maxUndoSteps;
        bool enablePerformanceMonitoring;

        // Singleton instance
        static EmergencyResponseSystem* instance;

        // Private constructor for Singleton
        EmergencyResponseSystem();

    public:
        // Singleton Access
        static EmergencyResponseSystem* getInstance();
        static void destroyInstance();

        // System Initialization
        void initialize();
        void shutdown();
        bool isSystemReady() const { return isInitialized; }

        // ==================== PATIENT MANAGEMENT ====================
        
        // Register new patient (triggers triage)
        bool registerNewPatient(const Patient& patient);
        
        // Get next patient based on priority
        Patient getNextPatientForTreatment();
        
        // Update patient information
        bool updatePatient(const std::string& patientID, const Patient& updatedData);
        
        // Discharge patient
        bool dischargePatient(const std::string& patientID);
        
        // Transfer patient to new location
        bool transferPatient(const std::string& patientID, const std::string& newLocation);
        
        // Get patient by ID
        Patient* getPatient(const std::string& patientID);
        
        // Get all patients
        std::vector<Patient> getAllPatients() const;
        
        // Get critical patients
        std::vector<Patient> getCriticalPatients(int count);

        // ==================== STAFF MANAGEMENT ====================
        
        // Register staff member
        bool registerStaff(const MedicalStaff& staff);
        
        // Assign staff to patient
        bool assignStaffToPatient(const std::string& staffID, const std::string& patientID);
        
        // Unassign staff from patient
        bool unassignStaffFromPatient(const std::string& staffID, const std::string& patientID);
        
        // Find optimal staff for patient
        std::string findBestStaffForPatient(const std::string& patientID);
        
        // Get available staff
        std::vector<MedicalStaff> getAvailableStaff();
        
        // Update staff location
        void updateStaffLocation(const std::string& staffID, const std::string& newLocation);

        // ==================== ROOM MANAGEMENT ====================
        
        // Register room
        bool registerRoom(const HospitalRoom& room);
        
        // Find available room of type
        std::string findAvailableRoom(RoomType type);
        
        // Assign patient to room
        bool assignPatientToRoom(const std::string& patientID, const std::string& roomID);
        
        // Get room status
        HospitalRoom* getRoom(const std::string& roomID);
        
        // Get all rooms
        std::vector<HospitalRoom> getAllRooms() const;

        // ==================== ROUTING OPERATIONS ====================
        
        // Find shortest path for staff to reach patient
        std::vector<std::string> findShortestPath(const std::string& fromRoom, 
                                                   const std::string& toRoom);
        
        // Get estimated travel time
        double getEstimatedTravelTime(const std::string& fromRoom, const std::string& toRoom);
        
        // Optimize staff routes for multiple patients
        std::vector<std::string> optimizeMultiPatientRoute(const std::string& staffLocation,
                                                           const std::vector<std::string>& patientLocations);

        // ==================== EQUIPMENT DISTRIBUTION ====================
        
        // Optimize equipment distribution using MST
        Algorithms::MSTResult optimizeEquipmentDistribution();
        
        // Generate oxygen line network
        Algorithms::MSTResult generateOxygenLineNetwork(const std::vector<std::string>& rooms);
        
        // Get equipment distribution cost savings
        double getEquipmentCostSavings();

        // ==================== UNDO SYSTEM ====================
        
        // Undo last operation
        bool undoLastOperation();
        
        // Get number of available undo steps
        int getAvailableUndoSteps() const;
        
        // Clear undo history
        void clearUndoHistory();

        // ==================== SORTING OPERATIONS ====================
        
        // Sort patients by ID using Radix Sort
        void sortPatientsByID(std::vector<Patient>& patients);
        
        // Sort patients by severity using QuickSort
        void sortPatientsBySeverity(std::vector<Patient>& patients);
        
        // Compare sorting algorithms (LO4)
        std::string compareSortingAlgorithms(std::vector<Patient>& patients);

        // ==================== SIMULATION ====================
        
        // Run emergency scenario simulation
        Simulation::SimulationResults simulateEmergencyScenario(
            const Simulation::ScenarioConfig& config);
        
        // Load synthetic test data
        void loadSyntheticData(int patientCount, int staffCount, int roomCount);

        // ==================== REPORTING ====================
        
        // Generate system performance report
        SystemPerformanceReport generatePerformanceReport();
        
        // Get triage statistics
        void displayTriageStatistics() const;
        
        // Export system data
        std::string exportSystemData() const;

        // ==================== EMERGENCY MODE ====================
        
        // Activate emergency mode
        void activateEmergencyMode();
        
        // Deactivate emergency mode
        void deactivateEmergencyMode();
        
        // Check if in emergency mode
        bool isInEmergencyMode() const { return isEmergencyMode; }

        // ==================== CONFIGURATION ====================
        
        // Set maximum undo steps
        void setMaxUndoSteps(int steps) { maxUndoSteps = steps; }
        
        // Enable/disable performance monitoring
        void setPerformanceMonitoring(bool enable) { enablePerformanceMonitoring = enable; }

    private:
        // Helper Methods
        void saveStateForUndo(const Patient& patient, DataStructures::OperationType operation);
        void initializeDefaultLayout();
        void validateSystemIntegrity();
    };

} // namespace Core

#endif // EMERGENCY_RESPONSE_SYSTEM_HPP