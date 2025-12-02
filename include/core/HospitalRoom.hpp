// include/core/HospitalRoom.hpp
#ifndef HOSPITAL_ROOM_HPP
#define HOSPITAL_ROOM_HPP

#include "../utils/CommonTypes.hpp"

namespace HEROS {

class HospitalRoom {
private:
    std::string roomID;
    std::string roomName;
    RoomType type;
    Coordinates position;
    std::vector<std::string> equipment;
    int capacity;
    int currentOccupancy;
    bool isAvailable;
    std::vector<std::string> assignedPatientIDs;
    std::vector<std::string> assignedStaffIDs;

public:
    // ==================== CONSTRUCTORS ====================
    
    HospitalRoom();
    HospitalRoom(const std::string& name, RoomType type, 
                 const Coordinates& pos, int capacity = 1);
    HospitalRoom(const std::string& id, const std::string& name, 
                 RoomType type, const Coordinates& pos, int capacity = 1);
    
    // ==================== ROOM MANAGEMENT ====================
    
    // Add patient to room
    bool addPatient(const std::string& patientID);
    
    // Remove patient from room
    bool removePatient(const std::string& patientID);
    
    // Add staff to room
    bool addStaff(const std::string& staffID);
    
    // Remove staff from room
    bool removeStaff(const std::string& staffID);
    
    // Add equipment
    void addEquipment(const std::string& equipmentName);
    
    // Check if equipment exists
    bool hasEquipment(const std::string& equipmentName) const;
    
    // ==================== GETTERS ====================
    
    std::string getRoomID() const { return roomID; }
    std::string getRoomName() const { return roomName; }
    RoomType getType() const { return type; }
    Coordinates getPosition() const { return position; }
    std::vector<std::string> getEquipment() const { return equipment; }
    int getCapacity() const { return capacity; }
    int getCurrentOccupancy() const { return currentOccupancy; }
    bool getIsAvailable() const { return isAvailable && currentOccupancy < capacity; }
    std::vector<std::string> getAssignedPatientIDs() const { return assignedPatientIDs; }
    std::vector<std::string> getAssignedStaffIDs() const { return assignedStaffIDs; }
    
    // ==================== SETTERS ====================
    
    void setRoomName(const std::string& name) { roomName = name; }
    void setType(RoomType t) { type = t; }
    void setPosition(const Coordinates& pos) { position = pos; }
    void setCapacity(int cap) { capacity = cap; }
    void setIsAvailable(bool available) { isAvailable = available; }
    
    // ==================== UTILITY FUNCTIONS ====================
    
    // Print room information
    void print() const;
    
    // Get distance to another room
    double distanceTo(const HospitalRoom& other) const;
    
    // Check if room is full
    bool isFull() const { return currentOccupancy >= capacity; }
    
    // Get available space
    int getAvailableSpace() const { return capacity - currentOccupancy; }
};

} // namespace HEROS

#endif // HOSPITAL_ROOM_HPP