#include "../../include/core/HospitalRoom.hpp"
#include <iostream>
#include <algorithm>

HospitalRoom::HospitalRoom() 
    : roomID("R000"), type(RoomType::WARD), position(),
      occupied(false), capacity(1), currentOccupancy(0) {}

HospitalRoom::HospitalRoom(const std::string& id, RoomType t, Coordinates pos, int cap)
    : roomID(id), type(t), position(pos),
      occupied(false), capacity(cap), currentOccupancy(0) {}

bool HospitalRoom::addEquipment(const std::string& equipmentName) {
    equipment.push_back(equipmentName);
    return true;
}

bool HospitalRoom::removeEquipment(const std::string& equipmentName) {
    auto it = std::find(equipment.begin(), equipment.end(), equipmentName);
    if (it != equipment.end()) {
        equipment.erase(it);
        return true;
    }
    return false;
}

bool HospitalRoom::hasEquipment(const std::string& equipmentName) const {
    return std::find(equipment.begin(), equipment.end(), equipmentName) != equipment.end();
}

bool HospitalRoom::admitPatient() {
    if (currentOccupancy < capacity) {
        currentOccupancy++;
        occupied = (currentOccupancy > 0);
        return true;
    }
    return false;
}

bool HospitalRoom::dischargePatient() {
    if (currentOccupancy > 0) {
        currentOccupancy--;
        occupied = (currentOccupancy > 0);
        return true;
    }
    return false;
}

std::string HospitalRoom::getTypeString() const {
    switch(type) {
        case RoomType::ICU: return "ICU";
        case RoomType::EMERGENCY: return "Emergency";
        case RoomType::WARD: return "Ward";
        case RoomType::OPERATING_ROOM: return "Operating Room";
        case RoomType::OBSERVATION: return "Observation";
        case RoomType::ISOLATION: return "Isolation";
        default: return "Unknown";
    }
}

void HospitalRoom::display() const {
    std::cout << "Room " << roomID << " (" << getTypeString() << ") at (" 
              << position.x << ", " << position.y << ") - Occupancy: " 
              << currentOccupancy << "/" << capacity << "\n";
}