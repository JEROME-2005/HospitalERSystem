#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../core/Patient.hpp"
#include "../core/HospitalRoom.hpp"
#include "../core/MedicalStaff.hpp"
#include "../algorithms/Graph.hpp"
#include <vector>
#include <string>
#include <random>
#include <ctime>

namespace Simulation {

    /**
     * Scenario Configuration
     */
    struct ScenarioConfig {
        int patientCount;
        int staffCount;
        int roomCount;
        double emergencyRate;       // Percentage of emergency patients
        double criticalRate;        // Percentage of critical patients
        int simulationDurationMins;
        int patientArrivalIntervalSecs;
        bool enableRandomEvents;
        std::string scenarioName;

        ScenarioConfig() : patientCount(100), staffCount(20), roomCount(50),
                          emergencyRate(0.3), criticalRate(0.1),
                          simulationDurationMins(60), patientArrivalIntervalSecs(30),
                          enableRandomEvents(true), scenarioName("Default") {}
    };

    /**
     * Simulation Results
     */
    struct SimulationResults {
        int totalPatientsTreated;
        int totalPatientsWaiting;
        double averageWaitTime;
        double averageResponseTime;
        int criticalPatientsSaved;
        int resourceUtilizationPercent;
        double staffEfficiency;
        double mstCostSavingsPercent;
        std::vector<std::pair<time_t, int>> patientLoadOverTime;
        std::string summary;

        SimulationResults() : totalPatientsTreated(0), totalPatientsWaiting(0),
                             averageWaitTime(0), averageResponseTime(0),
                             criticalPatientsSaved(0), resourceUtilizationPercent(0),
                             staffEfficiency(0), mstCostSavingsPercent(0) {}
    };

    /**
     * Random Event Types
     */
    enum class RandomEventType {
        MASS_CASUALTY,          // Multiple patients arrive at once
        EQUIPMENT_FAILURE,       // Equipment breaks down
        STAFF_EMERGENCY,         // Staff becomes unavailable
        POWER_OUTAGE,           // Partial power failure
        PATIENT_DETERIORATION,  // Patient condition worsens
        CODE_BLUE              // Cardiac arrest
    };

    /**
     * EmergencySimulator Class
     * 
     * Generates synthetic patient data and simulates emergency scenarios.
     * Used for testing and validating the H.E.R.O.S. system.
     */
    class EmergencySimulator {
    private:
        std::mt19937 randomGenerator;
        ScenarioConfig currentConfig;
        SimulationResults currentResults;
        std::vector<Core::Patient> generatedPatients;
        std::vector<Core::HospitalRoom> generatedRooms;
        std::vector<Core::MedicalStaff> generatedStaff;
        Algorithms::Graph* hospitalLayout;
        bool isRunning;

        // Random Data Pools
        static const std::vector<std::string> FIRST_NAMES;
        static const std::vector<std::string> LAST_NAMES;
        static const std::vector<std::string> CHIEF_COMPLAINTS;
        static const std::vector<std::string> MEDICAL_HISTORY;

    public:
        // Constructors
        EmergencySimulator();
        EmergencySimulator(const ScenarioConfig& config);
        EmergencySimulator(unsigned int seed);
        
        // Destructor
        ~EmergencySimulator();

        // Configuration
        void setConfiguration(const ScenarioConfig& config);
        ScenarioConfig getConfiguration() const { return currentConfig; }

        // Data Generation
        Core::Patient generateRandomPatient();
        Core::HospitalRoom generateRandomRoom(Core::RoomType type);
        Core::MedicalStaff generateRandomStaff(Core::StaffRole role);
        std::vector<Core::Patient> generateSyntheticPatientData(int count);
        std::vector<Core::HospitalRoom> generateHospitalLayout(int floors, int roomsPerFloor);
        std::vector<Core::MedicalStaff> generateStaffRoster(int count);
        Algorithms::Graph* generateHospitalGraph(const std::vector<Core::HospitalRoom>& rooms);

        // Simulation Control
        SimulationResults runSimulation();
        SimulationResults runSimulation(const ScenarioConfig& config);
        void pauseSimulation();
        void resumeSimulation();
        void stopSimulation();

        // Random Events
        void triggerRandomEvent(RandomEventType eventType);
        void enableRandomEvents(bool enable);

        // Result Analysis
        SimulationResults getCurrentResults() const { return currentResults; }
        void validateResultsAgainstBaseline(const SimulationResults& results);
        std::string generateSimulationReport() const;

        // Preset Scenarios
        static ScenarioConfig createNormalDayScenario();
        static ScenarioConfig createMassCasualtyScenario();
        static ScenarioConfig createCodeBlueScenario();
        static ScenarioConfig createStressTestScenario();

        // Utility
        void setSeed(unsigned int seed);
        void reset();

    private:
        // Helper Methods
        Core::VitalSigns generateRandomVitals(bool critical = false);
        std::string generatePatientID(const std::string& prefix);
        double generateRandomDouble(double min, double max);
        int generateRandomInt(int min, int max);
        std::string getRandomElement(const std::vector<std::string>& vec);
        Core::TriageStatus calculateTriageStatus(const Core::Patient& patient);
    };

} // namespace Simulation

#endif // SIMULATION_HPP