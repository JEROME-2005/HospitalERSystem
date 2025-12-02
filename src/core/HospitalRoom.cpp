// src/core/HospitalRoom.cpp
#include "../../include/core/HospitalRoom.hpp"

namespace HEROS {

// Default constructor
HospitalRoom::HospitalRoom()
    : roomID(""), name("Unknown Room"), type(RoomType::WARD),
      position(), capacity(1), currentOccupancy(0), isAvailable(true) {
}

// Basic constructor
HospitalRoom::HospitalRoom(const std::string& id, const std::string& roomName, RoomType roomType)
    : roomID(id), name(roomName), type(roomType),
      position(), capacity(1), currentOccupancy(0), isAvailable(true) {
}

// Full constructor
HospitalRoom::HospitalRoom(const std::string& id, const std::string& roomName, 
                           RoomType roomType, const Coordinates& pos, int cap)
    : roomID(id), name(roomName), type(roomType),
      position(pos), capacity(cap), currentOccupancy(0), isAvailable(true) {
}

// Copy constructor
HospitalRoom::HospitalRoom(const HospitalRoom& other)
    : roomID(other.roomID), name(other.name), type(other.type),
      position(other.position), equipment(other.equipment),
      capacity(other.capacity), currentOccupancy(other.currentOccupancy),
      isAvailable(other.isAvailable), patientIDs(other.patientIDs) {
}

// Assignment operator
HospitalRoom& HospitalRoom::operator=(const HospitalRoom& other) {
    if (this != &other) {
        roomID = other.roomID;
        name = other.name;
        type = other.type;
        position = other.position;
        equipment = other.equipment;
        capacity = other.capacity;
        currentOccupancy = other.currentOccupancy;
        isAvailable = other.isAvailable;
        patientIDs = other.patientIDs;
    }
    return *this;
}

bool HospitalRoom::addPatient(const std::string& patientID) {
    if (currentOccupancy >= capacity || !isAvailable) {
        return false;
    }
    
    // Check if patient already in room
    if (hasPatient(patientID)) {
        return false;
    }
    
    patientIDs.push_back(patientID);
    currentOccupancy++;
    return true;
}

bool HospitalRoom::removePatient(const std::string& patientID) {
    auto it = std::find(patientIDs.begin(), patientIDs.end(), patientID);
    if (it != patientIDs.end()) {
        patientIDs.erase(it);
        currentOccupancy--;
        return true;
    }
    return false;
}

bool HospitalRoom::hasPatient(const std::string& patientID) const {
    return std::find(patientIDs.begin(), patientIDs.end(), patientID) != patientIDs.end();
}

void HospitalRoom::addEquipment(const std::string& equipmentName) {
    if (!hasEquipment(equipmentName)) {
        equipment.push_back(equipmentName);
    }
}

bool HospitalRoom::hasEquipment(const std::string& equipmentName) const {
    return std::find(equipment.begin(), equipment.end(), equipmentName) != equipment.end();
}

double HospitalRoom::distanceTo(const HospitalRoom& other) const {
    return position.distanceTo(other.position);
}

bool HospitalRoom::operator==(const HospitalRoom& other) const {
    return roomID == other.roomID;
}

std::string HospitalRoom::toString() const {
    std::stringstream ss;
    ss << "Room[ID=" << roomID 
       << ", Name=" << name
       << ", Type=" << roomTypeToString(type)
       << ", Occupancy=" << currentOccupancy << "/" << capacity
       << ", Available=" << (getIsAvailable() ? "Yes" : "No")
       << "]";
    return ss.str();
}

void HospitalRoom::printInfo() const {
    std::cout << "\n========== ROOM INFORMATION ==========" << std::endl;
    std::cout << "ID:           " << roomID << std::endl;
    std::cout << "Name:         " << name << std::endl;
    std::cout << "Type:         " << roomTypeToString(type) << std::endl;
    std::cout << "Position:     (" << position.x << ", " << position.y 
              << ") Floor " << position.floor << std::endl;
    std::cout << "Capacity:     " << currentOccupancy << "/" << capacity << std::endl;
    std::cout << "Available:    " << (getIsAvailable() ? "Yes" : "No") << std::endl;
    
    std::cout << "Equipment:    ";
    if (equipment.empty()) {
        std::cout << "None";
    } else {
        for (size_t i = 0; i < equipment.size(); ++i) {
            std::cout << equipment[i];
            if (i < equipment.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
    
    std::cout << "Patients:     ";
    if (patientIDs.empty()) {
        std::cout << "None";
    } else {
        for (size_t i = 0; i < patientIDs.size(); ++i) {
            std::cout << patientIDs[i];
            if (i < patientIDs.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
}

} // namespace HEROS