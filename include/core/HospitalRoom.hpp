#ifndef HOSPITAL_ROOM_HPP
#define HOSPITAL_ROOM_HPP

#include <string>
#include <vector>

enum class RoomType {
    ICU,
    EMERGENCY,
    WARD,
    OPERATING_ROOM,
    OBSERVATION,
    ISOLATION
};

struct Coordinates {
    double x;
    double y;
    
    Coordinates() : x(0.0), y(0.0) {}
    Coordinates(double _x, double _y) : x(_x), y(_y) {}
};

class HospitalRoom {
private:
    std::string roomID;
    RoomType type;
    Coordinates position;
    std::vector<std::string> equipment;
    bool occupied;
    int capacity;
    int currentOccupancy;

public:
    // Constructor
    HospitalRoom();
    HospitalRoom(const std::string& id, RoomType t, Coordinates pos, int cap);
    
    // Getters
    std::string getRoomID() const { return roomID; }
    RoomType getType() const { return type; }
    Coordinates getPosition() const { return position; }
    bool isOccupied() const { return occupied; }
    int getCapacity() const { return capacity; }
    int getCurrentOccupancy() const { return currentOccupancy; }
    
    // Room management
    bool addEquipment(const std::string& equipmentName);
    bool removeEquipment(const std::string& equipmentName);
    bool hasEquipment(const std::string& equipmentName) const;
    bool admitPatient();
    bool dischargePatient();
    
    // Display
    void display() const;
    std::string getTypeString() const;
};

#endif // HOSPITAL_ROOM_HPP