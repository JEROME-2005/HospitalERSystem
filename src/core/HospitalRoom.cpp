// src/core/HospitalRoom.cpp
#include "../../include/core/HospitalRoom.hpp"

namespace HEROS {

// ==================== CONSTRUCTORS ====================

HospitalRoom::HospitalRoom()
    : roomID(generateID("ROOM")),
      roomName("Unnamed Room"),
      type(RoomType::WARD),
      position(0, 0),
      capacity(1),
      currentOccupancy(0),
      isAvailable(true) {
}

HospitalRoom::HospitalRoom(const std::string& name, RoomType type,
                           const Coordinates& pos, int capacity)
    : roomID(generateID("ROOM")),
      roomName(name),
      type(type),
      position(pos),
      capacity(capacity),
      currentOccupancy(0),
      isAvailable(true) {
}

HospitalRoom::HospitalRoom(const std::string& id, const std::string& name,
                           RoomType type, const Coordinates& pos, int capacity)
    : roomID(id),
      roomName(name),
      type(type),
      position(pos),
      capacity(capacity),
      currentOccupancy(0),
      isAvailable(true) {
}

// ==================== ROOM MANAGEMENT ====================

bool HospitalRoom::addPatient(const std::string& patientID) {
    if (isFull() || !isAvailable) {
        return false;
    }
    
    // Check if patient already in room
    for (const auto& id : assignedPatientIDs) {
        if (id == patientID) return false;
    }
    
    assignedPatientIDs.push_back(patientID);
    currentOccupancy++;
    return true;
}

bool HospitalRoom::removePatient(const std::string& patientID) {
    for (auto it = assignedPatientIDs.begin(); it != assignedPatientIDs.end(); ++it) {
        if (*it == patientID) {
            assignedPatientIDs.erase(it);
            currentOccupancy--;
            return true;
        }
    }
    return false;
}

bool HospitalRoom::addStaff(const std::string& staffID) {
    // Check if staff already in room
    for (const auto& id : assignedStaffIDs) {
        if (id == staffID) return false;
    }
    
    assignedStaffIDs.push_back(staffID);
    return true;
}

bool HospitalRoom::removeStaff(const std::string& staffID) {
    for (auto it = assignedStaffIDs.begin(); it != assignedStaffIDs.end(); ++it) {
        if (*it == staffID) {
            assignedStaffIDs.erase(it);
            return true;
        }
    }
    return false;
}

void HospitalRoom::addEquipment(const std::string& equipmentName) {
    if (!hasEquipment(equipmentName)) {
        equipment.push_back(equipmentName);
    }
}

bool HospitalRoom::hasEquipment(const std::string& equipmentName) const {
    for (const auto& eq : equipment) {
        if (eq == equipmentName) return true;
    }
    return false;
}

// ==================== UTILITY FUNCTIONS ====================

void HospitalRoom::print() const {
    std::cout << "\n======== Room Information ========" << std::endl;
    std::cout << "ID: " << roomID << std::endl;
    std::cout << "Name: " << roomName << std::endl;
    std::cout << "Type: " << roomTypeToString(type) << std::endl;
    std::cout << "Position: (" << position.x << ", " << position.y << ")" << std::endl;
    std::cout << "Capacity: " << currentOccupancy << "/" << capacity << std::endl;
    std::cout << "Available: " << (getIsAvailable() ? "Yes" : "No") << std::endl;
    
    std::cout << "Equipment: ";
    if (equipment.empty()) {
        std::cout << "None";
    } else {
        for (size_t i = 0; i < equipment.size(); i++) {
            std::cout << equipment[i];
            if (i < equipment.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
    
    std::cout << "Patients: " << assignedPatientIDs.size() << std::endl;
    std::cout << "Staff: " << assignedStaffIDs.size() << std::endl;
    std::cout << "==================================\n" << std::endl;
}

double HospitalRoom::distanceTo(const HospitalRoom& other) const {
    return position.distanceTo(other.position);
}

} // namespace HEROS