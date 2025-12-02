#ifndef HOSPITAL_ROOM_HPP
#define HOSPITAL_ROOM_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace Core {

    // Room Type Enumeration
    enum class RoomType {
        ICU,                // Intensive Care Unit
        EMERGENCY,          // Emergency Room
        WARD,               // General Ward
        OPERATION_THEATER,  // Surgery Room
        RECOVERY,           // Post-op Recovery
        ISOLATION,          // Isolation Room
        TRIAGE,             // Triage Area
        WAITING,            // Waiting Room
        PHARMACY,           // Pharmacy
        LAB,                // Laboratory
        RADIOLOGY,          // X-ray, CT, MRI
        CORRIDOR            // Hallway/Corridor
    };

    // Room Status
    enum class RoomStatus {
        AVAILABLE,
        OCCUPIED,
        CLEANING,
        MAINTENANCE,
        RESERVED,
        CLOSED
    };

    // Coordinates Structure
    struct Coordinates {
        double x;
        double y;
        int floor;

        Coordinates() : x(0), y(0), floor(0) {}
        Coordinates(double x, double y, int f = 0) : x(x), y(y), floor(f) {}

        double distanceTo(const Coordinates& other) const;
    };

    // Equipment Structure
    struct Equipment {
        std::string equipmentID;
        std::string name;
        std::string type;
        bool isAvailable;
        bool requiresMaintenance;

        Equipment() : isAvailable(true), requiresMaintenance(false) {}
        Equipment(const std::string& id, const std::string& n, const std::string& t)
            : equipmentID(id), name(n), type(t), isAvailable(true), requiresMaintenance(false) {}
    };

    class HospitalRoom {
    private:
        std::string roomID;
        std::string roomName;
        RoomType type;
        RoomStatus status;
        Coordinates position;
        std::vector<Equipment> equipmentList;
        int capacity;
        int currentOccupancy;
        std::vector<std::string> assignedPatients;
        std::vector<std::string> assignedStaff;
        bool hasOxygenLine;
        bool hasVentilator;
        bool hasMonitor;
        int priority;  // For resource distribution

    public:
        // Constructors
        HospitalRoom();
        HospitalRoom(const std::string& id, const std::string& name, RoomType type);
        HospitalRoom(const std::string& id, const std::string& name, RoomType type, 
                     const Coordinates& pos, int capacity);
        HospitalRoom(const HospitalRoom& other);
        
        // Destructor
        ~HospitalRoom();

        // Assignment operator
        HospitalRoom& operator=(const HospitalRoom& other);

        // Room Management Methods
        bool addPatient(const std::string& patientID);
        bool removePatient(const std::string& patientID);
        bool addStaff(const std::string& staffID);
        bool removeStaff(const std::string& staffID);
        void addEquipment(const Equipment& equipment);
        bool removeEquipment(const std::string& equipmentID);
        
        // Utility Methods
        bool isAvailable() const;
        bool isFull() const;
        bool hasPatient(const std::string& patientID) const;
        bool hasStaff(const std::string& staffID) const;
        int getAvailableSpace() const;
        double getOccupancyRate() const;

        // Getters
        std::string getRoomID() const { return roomID; }
        std::string getRoomName() const { return roomName; }
        RoomType getType() const { return type; }
        RoomStatus getStatus() const { return status; }
        Coordinates getPosition() const { return position; }
        std::vector<Equipment> getEquipmentList() const { return equipmentList; }
        int getCapacity() const { return capacity; }
        int getCurrentOccupancy() const { return currentOccupancy; }
        std::vector<std::string> getAssignedPatients() const { return assignedPatients; }
        std::vector<std::string> getAssignedStaff() const { return assignedStaff; }
        bool getHasOxygenLine() const { return hasOxygenLine; }
        bool getHasVentilator() const { return hasVentilator; }
        bool getHasMonitor() const { return hasMonitor; }
        int getPriority() const { return priority; }

        // Setters
        void setRoomID(const std::string& id) { roomID = id; }
        void setRoomName(const std::string& name) { roomName = name; }
        void setType(RoomType t) { type = t; }
        void setStatus(RoomStatus s) { status = s; }
        void setPosition(const Coordinates& pos) { position = pos; }
        void setCapacity(int cap) { capacity = cap; }
        void setHasOxygenLine(bool has) { hasOxygenLine = has; }
        void setHasVentilator(bool has) { hasVentilator = has; }
        void setHasMonitor(bool has) { hasMonitor = has; }
        void setPriority(int p) { priority = p; }

        // Utility Methods
        std::string toString() const;
        std::string getRoomTypeString() const;
        std::string getRoomStatusString() const;
        void display() const;

        // Comparison operators
        bool operator==(const HospitalRoom& other) const;
        bool operator!=(const HospitalRoom& other) const;
    };

    // Stream operator
    std::ostream& operator<<(std::ostream& os, const HospitalRoom& room);

} // namespace Core

#endif // HOSPITAL_ROOM_HPP