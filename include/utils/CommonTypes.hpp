// include/utils/CommonTypes.hpp
#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP

#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <map>
#include <limits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
#include <queue>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <random>
#include <fstream>

namespace HEROS {

// ==================== ENUMERATIONS ====================

// Patient triage status based on WHO triage tags
enum class TriageStatus {
    RED = 1,      // Immediate - life threatening
    YELLOW = 2,   // Urgent - serious but stable
    GREEN = 3,    // Delayed - minor injuries
    BLACK = 4,    // Deceased or expectant
    WHITE = 5     // Dismissed - no treatment needed
};

// Hospital room types
enum class RoomType {
    ICU,          // Intensive Care Unit
    EMERGENCY,    // Emergency Room
    WARD,         // General Ward
    OPERATING,    // Operating Theater
    RECOVERY,     // Recovery Room
    TRIAGE,       // Triage Area
    CORRIDOR,     // Hallway/Corridor
    RECEPTION     // Reception/Waiting Area
};

// Staff roles
enum class StaffRole {
    DOCTOR,
    NURSE,
    SURGEON,
    TECHNICIAN,
    PARAMEDIC,
    ADMINISTRATOR
};

// Staff availability status
enum class AvailabilityStatus {
    AVAILABLE,
    BUSY,
    ON_BREAK,
    OFF_DUTY,
    EMERGENCY_ASSIGNED
};

// Operation types for undo system
enum class OperationType {
    PATIENT_REGISTER,
    PATIENT_DISCHARGE,
    PATIENT_TRANSFER,
    STAFF_ASSIGN,
    STAFF_UNASSIGN,
    PRIORITY_UPDATE,
    STATUS_CHANGE
};

// ==================== STRUCTURES ====================

// Vital signs structure
struct VitalSigns {
    float heartRate;       // beats per minute (normal: 60-100)
    float bloodPressureSys;// systolic pressure (normal: 90-120)
    float bloodPressureDia;// diastolic pressure (normal: 60-80)
    float temperature;     // celsius (normal: 36.1-37.2)
    float oxygenSaturation;// percentage (normal: 95-100)
    float respiratoryRate; // breaths per minute (normal: 12-20)
    
    VitalSigns() : heartRate(75), bloodPressureSys(120), 
                   bloodPressureDia(80), temperature(36.5),
                   oxygenSaturation(98), respiratoryRate(16) {}
    
    // Calculate severity based on vital signs (0-100 scale)
    int calculateVitalScore() const {
        int score = 0;
        
        // Heart rate scoring
        if (heartRate < 40 || heartRate > 150) score += 25;
        else if (heartRate < 50 || heartRate > 120) score += 15;
        else if (heartRate < 60 || heartRate > 100) score += 5;
        
        // Blood pressure scoring
        if (bloodPressureSys < 70 || bloodPressureSys > 200) score += 25;
        else if (bloodPressureSys < 90 || bloodPressureSys > 160) score += 15;
        else if (bloodPressureSys < 100 || bloodPressureSys > 140) score += 5;
        
        // Temperature scoring
        if (temperature < 35 || temperature > 40) score += 20;
        else if (temperature < 36 || temperature > 39) score += 10;
        else if (temperature < 36.1 || temperature > 37.2) score += 3;
        
        // Oxygen saturation scoring
        if (oxygenSaturation < 85) score += 25;
        else if (oxygenSaturation < 90) score += 15;
        else if (oxygenSaturation < 95) score += 5;
        
        // Respiratory rate scoring
        if (respiratoryRate < 8 || respiratoryRate > 30) score += 15;
        else if (respiratoryRate < 10 || respiratoryRate > 25) score += 8;
        else if (respiratoryRate < 12 || respiratoryRate > 20) score += 3;
        
        return std::min(score, 100);
    }
};

// 2D coordinates for hospital map
struct Coordinates {
    double x;
    double y;
    
    Coordinates(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    
    // Calculate Euclidean distance
    double distanceTo(const Coordinates& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
    
    bool operator==(const Coordinates& other) const {
        return (x == other.x && y == other.y);
    }
};

// Graph edge structure
struct Edge {
    std::string from;
    std::string to;
    double weight;
    
    Edge(const std::string& f, const std::string& t, double w)
        : from(f), to(t), weight(w) {}
    
    // For Kruskal's algorithm sorting
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Performance metrics structure
struct PerformanceMetrics {
    double executionTimeMs;
    size_t operationCount;
    size_t memoryUsedBytes;
    std::string algorithmName;
    std::string complexity;
    
    void print() const {
        std::cout << "=== Performance Metrics ===" << std::endl;
        std::cout << "Algorithm: " << algorithmName << std::endl;
        std::cout << "Complexity: " << complexity << std::endl;
        std::cout << "Execution Time: " << executionTimeMs << " ms" << std::endl;
        std::cout << "Operations: " << operationCount << std::endl;
        std::cout << "Memory Used: " << memoryUsedBytes << " bytes" << std::endl;
    }
};

// System performance report
struct SystemPerformanceReport {
    int totalPatients;
    int criticalPatients;
    double avgTriageTime;
    double avgRouteLength;
    double avgResponseTime;
    PerformanceMetrics heapMetrics;
    PerformanceMetrics routingMetrics;
    PerformanceMetrics mstMetrics;
    PerformanceMetrics sortingMetrics;
    
    void print() const {
        std::cout << "\n========================================" << std::endl;
        std::cout << "   SYSTEM PERFORMANCE REPORT" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Total Patients: " << totalPatients << std::endl;
        std::cout << "Critical Patients: " << criticalPatients << std::endl;
        std::cout << "Average Triage Time: " << avgTriageTime << " ms" << std::endl;
        std::cout << "Average Route Length: " << avgRouteLength << " units" << std::endl;
        std::cout << "Average Response Time: " << avgResponseTime << " ms" << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
};

// Simulation configuration
struct ScenarioConfig {
    int patientCount;
    int staffCount;
    int roomCount;
    double emergencyIntensity; // 0.0 - 1.0
    bool usePriorityQueue;
    bool useDijkstra;
    bool useMST;
    int simulationDurationMinutes;
    
    ScenarioConfig() : patientCount(50), staffCount(10), roomCount(20),
                       emergencyIntensity(0.5), usePriorityQueue(true),
                       useDijkstra(true), useMST(true), 
                       simulationDurationMinutes(60) {}
};

// Simulation results
struct SimulationResults {
    int patientsProcessed;
    int patientsSaved;
    int patientsLost;
    double avgWaitTime;
    double avgTreatmentTime;
    double totalOptimizationSavings;
    std::vector<PerformanceMetrics> metrics;
    
    void print() const {
        std::cout << "\n========================================" << std::endl;
        std::cout << "   SIMULATION RESULTS" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Patients Processed: " << patientsProcessed << std::endl;
        std::cout << "Patients Saved: " << patientsSaved << std::endl;
        std::cout << "Patients Lost: " << patientsLost << std::endl;
        std::cout << "Survival Rate: " << std::fixed << std::setprecision(1)
                  << (patientsProcessed > 0 ? 
                      (100.0 * patientsSaved / patientsProcessed) : 0) << "%" << std::endl;
        std::cout << "Avg Wait Time: " << avgWaitTime << " min" << std::endl;
        std::cout << "Avg Treatment Time: " << avgTreatmentTime << " min" << std::endl;
        std::cout << "Optimization Savings: " << totalOptimizationSavings << "%" << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
};

// ==================== UTILITY FUNCTIONS ====================

// Convert TriageStatus to string
inline std::string triageStatusToString(TriageStatus status) {
    switch (status) {
        case TriageStatus::RED: return "RED (Immediate)";
        case TriageStatus::YELLOW: return "YELLOW (Urgent)";
        case TriageStatus::GREEN: return "GREEN (Delayed)";
        case TriageStatus::BLACK: return "BLACK (Deceased)";
        case TriageStatus::WHITE: return "WHITE (Dismissed)";
        default: return "UNKNOWN";
    }
}

// Convert RoomType to string
inline std::string roomTypeToString(RoomType type) {
    switch (type) {
        case RoomType::ICU: return "ICU";
        case RoomType::EMERGENCY: return "Emergency";
        case RoomType::WARD: return "Ward";
        case RoomType::OPERATING: return "Operating Theater";
        case RoomType::RECOVERY: return "Recovery";
        case RoomType::TRIAGE: return "Triage Area";
        case RoomType::CORRIDOR: return "Corridor";
        case RoomType::RECEPTION: return "Reception";
        default: return "Unknown";
    }
}

// Convert StaffRole to string
inline std::string staffRoleToString(StaffRole role) {
    switch (role) {
        case StaffRole::DOCTOR: return "Doctor";
        case StaffRole::NURSE: return "Nurse";
        case StaffRole::SURGEON: return "Surgeon";
        case StaffRole::TECHNICIAN: return "Technician";
        case StaffRole::PARAMEDIC: return "Paramedic";
        case StaffRole::ADMINISTRATOR: return "Administrator";
        default: return "Unknown";
    }
}

// Generate unique ID
inline std::string generateID(const std::string& prefix) {
    static int counter = 0;
    std::stringstream ss;
    ss << prefix << "-" << std::setfill('0') << std::setw(5) << ++counter;
    return ss.str();
}

// Get current timestamp
inline time_t getCurrentTimestamp() {
    return std::time(nullptr);
}

// Format timestamp to string
inline std::string formatTimestamp(time_t timestamp) {
    char buffer[80];
    struct tm* timeinfo = localtime(&timestamp);
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

} // namespace HEROS

#endif // COMMON_TYPES_HPP