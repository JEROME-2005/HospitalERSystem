#include "../../include/core/EmergencyResponseSystem.hpp"
#include "../../include/utils/PerformanceMonitor.hpp"
#include "../../include/utils/DataValidator.hpp"
#include <iostream>
#include <iomanip>

EmergencyResponseSystem::EmergencyResponseSystem() 
    : systemInitialized(false), totalPatientsRegistered(0), totalStaffAssignments(0) {
    
    initializeHospitalLayout();
    registerRooms();
    registerStaff();
    
    // C++11 compatible way (instead of make_unique which is C++14)
    staffRouter.reset(new DijkstraRouter(&hospitalLayout));
    equipmentDistributor.reset(new MSTGenerator(&hospitalLayout));
    
    systemInitialized = true;
    
    std::cout << "\n* H.E.R.O.S System Initialized Successfully!\n";
}

EmergencyResponseSystem::~EmergencyResponseSystem() {
    std::cout << "\n* H.E.R.O.S System Shutdown Complete\n";
}

void EmergencyResponseSystem::initializeHospitalLayout() {
    std::cout << "-> Initializing hospital layout...\n";
    
    // Create hospital graph with rooms as nodes
    hospitalLayout.addNode("ENTRANCE", Coordinates(0, 0));
    hospitalLayout.addNode("ER", Coordinates(10, 0));
    hospitalLayout.addNode("ICU_1", Coordinates(20, 0));
    hospitalLayout.addNode("ICU_2", Coordinates(20, 10));
    hospitalLayout.addNode("WARD_A", Coordinates(10, 10));
    hospitalLayout.addNode("WARD_B", Coordinates(0, 10));
    hospitalLayout.addNode("OR_1", Coordinates(30, 5));
    hospitalLayout.addNode("OR_2", Coordinates(30, 15));
    hospitalLayout.addNode("PHARMACY", Coordinates(15, 5));
    hospitalLayout.addNode("LAB", Coordinates(15, 15));
    
    // Add corridors (bidirectional edges)
    hospitalLayout.addBidirectionalEdge("ENTRANCE", "ER", 10);
    hospitalLayout.addBidirectionalEdge("ER", "ICU_1", 12);
    hospitalLayout.addBidirectionalEdge("ER", "WARD_A", 8);
    hospitalLayout.addBidirectionalEdge("ICU_1", "ICU_2", 10);
    hospitalLayout.addBidirectionalEdge("ICU_1", "OR_1", 11);
    hospitalLayout.addBidirectionalEdge("ICU_2", "OR_2", 11);
    hospitalLayout.addBidirectionalEdge("WARD_A", "WARD_B", 10);
    hospitalLayout.addBidirectionalEdge("WARD_A", "ICU_2", 8);
    hospitalLayout.addBidirectionalEdge("WARD_B", "ENTRANCE", 10);
    hospitalLayout.addBidirectionalEdge("PHARMACY", "ER", 7);
    hospitalLayout.addBidirectionalEdge("PHARMACY", "WARD_A", 7);
    hospitalLayout.addBidirectionalEdge("LAB", "WARD_A", 7);
    hospitalLayout.addBidirectionalEdge("LAB", "ICU_2", 7);
    
    std::cout << "* Hospital layout initialized\n";
}

void EmergencyResponseSystem::registerRooms() {
    roomRegistry["ER"] = HospitalRoom("ER", RoomType::EMERGENCY, Coordinates(10, 0), 10);
    roomRegistry["ICU_1"] = HospitalRoom("ICU_1", RoomType::ICU, Coordinates(20, 0), 5);
    roomRegistry["ICU_2"] = HospitalRoom("ICU_2", RoomType::ICU, Coordinates(20, 10), 5);
    roomRegistry["WARD_A"] = HospitalRoom("WARD_A", RoomType::WARD, Coordinates(10, 10), 20);
    roomRegistry["WARD_B"] = HospitalRoom("WARD_B", RoomType::WARD, Coordinates(0, 10), 20);
    
    std::cout << "* " << roomRegistry.size() << " rooms registered\n";
}

void EmergencyResponseSystem::registerStaff() {
    staffRegistry["DR001"] = MedicalStaff("DR001", "Dr. Sarah Chen", StaffRole::DOCTOR);
    staffRegistry["DR002"] = MedicalStaff("DR002", "Dr. James Wilson", StaffRole::DOCTOR);
    staffRegistry["DR003"] = MedicalStaff("DR003", "Dr. Emily Brown", StaffRole::SPECIALIST);
    staffRegistry["NR001"] = MedicalStaff("NR001", "Nurse Alice Johnson", StaffRole::NURSE);
    staffRegistry["NR002"] = MedicalStaff("NR002", "Nurse Michael Lee", StaffRole::NURSE);
    staffRegistry["NR003"] = MedicalStaff("NR003", "Nurse Sophie Taylor", StaffRole::NURSE);
    staffRegistry["PM001"] = MedicalStaff("PM001", "Paramedic David Kim", StaffRole::PARAMEDIC);
    
    std::cout << "* " << staffRegistry.size() << " staff members registered\n";
}

void EmergencyResponseSystem::registerNewPatient(const Patient& patient) {
    PerformanceMonitor::startTimer("Patient Registration");
    
    if (!DataValidator::validatePatientData(patient)) {
        std::cout << "* Patient validation failed!\n";
        return;
    }
    
    // Add to triage queue (Min-Heap operation: O(log n))
    triageSystem.addPatient(patient);
    
    // Add to registry
    patientRegistry[patient.getPatientID()] = patient;
    
    // Save state for undo
    PatientState state(patient, OperationType::PATIENT_REGISTERED, 
                      "New patient registered");
    undoSystem.push(state);
    
    totalPatientsRegistered++;
    
    PerformanceMonitor::stopTimer("Patient Registration");
    
    std::cout << "* Patient " << patient.getPatientID() << " registered successfully\n";
}

void EmergencyResponseSystem::assignStaffToPatient(const std::string& staffID, 
                                                   const std::string& patientID) {
    auto staffIt = staffRegistry.find(staffID);
    auto patientIt = patientRegistry.find(patientID);
    
    if (staffIt == staffRegistry.end() || patientIt == patientRegistry.end()) {
        std::cout << "* Staff or Patient not found!\n";
        return;
    }
    
    // Find route from staff location to patient
    RouteInfo route = staffRouter->findShortestPath(
        staffIt->second.getCurrentLocation(),
        patientIt->second.getLocation()
    );
    
    // Assign staff
    staffIt->second.assignToPatient(patientID);
    totalStaffAssignments++;
    
    std::cout << "* " << staffIt->second.getName() << " assigned to patient " 
              << patientID << "\n";
    std::cout << "  Route distance: " << std::fixed << std::setprecision(2) 
              << route.totalDistance << "m\n";
    
    staffRouter->displayRoute(route);
}

Patient EmergencyResponseSystem::processNextCriticalPatient() {
    PerformanceMonitor::startTimer("Process Critical Patient");
    
    if (triageSystem.isEmpty()) {
        PerformanceMonitor::stopTimer("Process Critical Patient");
        throw std::runtime_error("No patients in queue!");
    }
    
    // Extract from Min-Heap: O(log n)
    Patient nextPatient = triageSystem.getNextPatient();
    
    // Update patient status
    patientRegistry[nextPatient.getPatientID()].setStatus(TriageStatus::IN_TREATMENT);
    
    PerformanceMonitor::stopTimer("Process Critical Patient");
    
    return nextPatient;
}

void EmergencyResponseSystem::optimizeEquipmentDistribution() {
    std::cout << "\n-> Optimizing equipment distribution using MST...\n";
    
    PerformanceMonitor::startTimer("MST Generation");
    
    // Generate MST using Kruskal's algorithm: O(E log E)
    MSTResult mst = equipmentDistributor->generateMinimumSpanningTree();
    
    PerformanceMonitor::stopTimer("MST Generation");
    
    equipmentDistributor->displayMST(mst);
    
    std::cout << "\n* Equipment distribution optimized!\n";
    std::cout << "  Cable savings: " << std::fixed << std::setprecision(1) 
              << equipmentDistributor->calculateOptimizationPercentage(mst) << "%\n";
}

RouteInfo EmergencyResponseSystem::findFastestRoute(const std::string& from, 
                                                     const std::string& to) {
    PerformanceMonitor::startTimer("Dijkstra Routing");
    
    // Dijkstra's algorithm: O((V+E) log V)
    RouteInfo route = staffRouter->findShortestPath(from, to);
    
    PerformanceMonitor::stopTimer("Dijkstra Routing");
    
    return route;
}

void EmergencyResponseSystem::undoLastOperation() {
    if (undoSystem.isEmpty()) {
        std::cout << "* No operations to undo!\n";
        return;
    }
    
    // Stack pop: O(1)
    PatientState lastState = undoSystem.pop();
    
    std::cout << "Undoing: ";
    lastState.display();
    
    // Restore previous state
    Patient restoredPatient = lastState.getPatientSnapshot();
    patientRegistry[restoredPatient.getPatientID()] = restoredPatient;
}

void EmergencyResponseSystem::generatePerformanceReport() const {
    std::cout << "\n============================================================\n";
    std::cout << "              H.E.R.O.S PERFORMANCE REPORT                  \n";
    std::cout << "============================================================\n";
    std::cout << " Total Patients Registered:    " << std::setw(27) 
              << totalPatientsRegistered << " \n";
    std::cout << " Patients in Triage Queue:     " << std::setw(27) 
              << triageSystem.getPendingCount() << " \n";
    std::cout << " Total Patients Processed:     " << std::setw(27) 
              << triageSystem.getTotalProcessed() << " \n";
    std::cout << " Staff Assignments Made:       " << std::setw(27) 
              << totalStaffAssignments << " \n";
    std::cout << " Available Undo Operations:    " << std::setw(27) 
              << undoSystem.size() << " \n";
    std::cout << "============================================================\n";
    
    PerformanceMonitor::displayReport();
    PerformanceMonitor::displayComplexityAnalysis();
}

void EmergencyResponseSystem::displaySystemStatus() const {
    std::cout << "\n============================================================\n";
    std::cout << "              H.E.R.O.S SYSTEM STATUS                       \n";
    std::cout << "============================================================\n";
    std::cout << " System Status:               " 
              << (systemInitialized ? "* OPERATIONAL" : "* OFFLINE") << std::setw(18) << " \n";
    std::cout << " Registered Rooms:            " << std::setw(27) 
              << roomRegistry.size() << " \n";
    std::cout << " Registered Staff:            " << std::setw(27) 
              << staffRegistry.size() << " \n";
    std::cout << " Graph Vertices:              " << std::setw(27) 
              << hospitalLayout.getVertexCount() << " \n";
    std::cout << " Graph Edges:                 " << std::setw(27) 
              << hospitalLayout.getEdgeCount() << " \n";
    std::cout << "============================================================\n";
}

void EmergencyResponseSystem::displayTriageQueue() const {
    triageSystem.displayQueue();
}

void EmergencyResponseSystem::simulateEmergencyScenario(const SimulationConfig& config) {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "   EMERGENCY SCENARIO SIMULATION\n";
    std::cout << std::string(60, '=') << "\n";
    
    // Generate synthetic patients
    std::vector<Patient> patients = Simulation::generateSyntheticPatientData(config.patientCount);
    
    // Register all patients
    std::cout << "\n-> Registering " << patients.size() << " emergency patients...\n";
    for (const Patient& p : patients) {
        registerNewPatient(p);
    }
    
    // Display triage queue
    displayTriageQueue();
    
    // Process critical patients
    std::cout << "\n-> Processing critical patients...\n";
    for (int i = 0; i < std::min(5, config.patientCount); i++) {
        if (!triageSystem.isEmpty()) {
            Patient p = processNextCriticalPatient();
            p.display();
        }
    }
    
    // Optimize equipment distribution
    optimizeEquipmentDistribution();
    
    // Test routing
    std::cout << "\n-> Testing emergency routing...\n";
    RouteInfo route = findFastestRoute("ENTRANCE", "ICU_1");
    staffRouter->displayRoute(route);
    
    // Run simulation
    SimulationResults results = Simulation::runEmergencySimulation(config);
    Simulation::displaySimulationResults(results);
    
    // Display final report
    generatePerformanceReport();
}