// include/core/HospitalRoom.hpp
#ifndef HOSPITAL_ROOM_HPP
#define HOSPITAL_ROOM_HPP

#include "../utils/CommonTypes.hpp"

namespace HEROS {

class HospitalRoom {
private:
    std::string roomID;
    std::string name;
    RoomType type;
    Coordinates position;
    std::vector<std::string> equipment;
    int capacity;
    int currentOccupancy;
    bool isAvailable;
    std::vector<std::string> patientIDs;

public:
    // Constructors
    HospitalRoom();
    HospitalRoom(const std::string& id, const std::string& roomName, RoomType roomType);
    HospitalRoom(const std::string& id, const std::string& roomName, RoomType roomType,
                 const Coordinates& pos, int cap);
    
    // Copy constructor and assignment
    HospitalRoom(const HospitalRoom& other);
    HospitalRoom& operator=(const HospitalRoom& other);
    
    // Destructor
    ~HospitalRoom() = default;
    
    // Room management
    bool addPatient(const std::string& patientID);
    bool removePatient(const std::string& patientID);
    bool hasPatient(const std::string& patientID) const;
    void addEquipment(const std::string& equipmentName);
    bool hasEquipment(const std::string& equipmentName) const;
    
    // Getters
    std::string getRoomID() const { return roomID; }
    std::string getName() const { return name; }
    RoomType getType() const { return type; }
    Coordinates getPosition() const { return position; }
    std::vector<std::string> getEquipment() const { return equipment; }
    int getCapacity() const { return capacity; }
    int getCurrentOccupancy() const { return currentOccupancy; }
    bool getIsAvailable() const { return isAvailable && currentOccupancy < capacity; }
    std::vector<std::string> getPatientIDs() const { return patientIDs; }
    
    // Setters
    void setRoomID(const std::string& id) { roomID = id; }
    void setName(const std::string& n) { name = n; }
    void setType(RoomType t) { type = t; }
    void setPosition(const Coordinates& pos) { position = pos; }
    void setCapacity(int cap) { capacity = cap; }
    void setIsAvailable(bool available) { isAvailable = available; }
    
    // Utility
    std::string toString() const;
    void printInfo() const;
    double distanceTo(const HospitalRoom& other) const;
    
    // Comparison
    bool operator==(const HospitalRoom& other) const;
};

} // namespace HEROS

#endif // HOSPITAL_ROOM_HPP