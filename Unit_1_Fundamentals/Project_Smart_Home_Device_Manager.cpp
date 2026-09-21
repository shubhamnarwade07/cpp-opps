#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Class representing a Smart Device
class SmartDevice {
private:
    string deviceId;
    string type; // Light, Thermostat, Camera, Door Lock
    string location;
    bool isOn;
    string statusDetails; // e.g., "72F", "Recording", "Locked"
    string lastUpdated;

public:
    SmartDevice(string id, string deviceType, string loc)
        : deviceId(id), type(deviceType), location(loc), isOn(false), statusDetails("Off/Idle"), lastUpdated("00:00") {}

    // Method to switch device on or off
    void togglePower(bool state, string time) {
        isOn = state;
        lastUpdated = time;
        if (!isOn) {
            statusDetails = "Off";
        } else {
            statusDetails = "On";
        }
    }

    // Method to change specific status like temperature or lock state
    void changeStatus(string newStatus, string time) {
        statusDetails = newStatus;
        lastUpdated = time;
        isOn = true; // Implicitly turn on if status is actively set
    }

    // Accessor for displaying
    void displayDeviceStatus() const {
        cout << "[" << deviceId << "] " << type << " at " << location << " - " 
             << (isOn ? "ON" : "OFF") << " | Status: " << statusDetails 
             << " | Last Updated: " << lastUpdated << endl;
    }
};

// Manager class using a vector of devices
class HomeDashboard {
private:
    vector<SmartDevice> devices;

public:
    void addDevice(const SmartDevice& device) {
        devices.push_back(device);
    }

    void displayDashboard() const {
        cout << "\n=== Smart Home Dashboard ===" << endl;
        for (const auto& device : devices) {
            device.displayDeviceStatus();
        }
        cout << "============================\n" << endl;
    }

    // Allow accessing a specific device for demonstration
    SmartDevice& getDevice(int index) {
        return devices.at(index);
    }
};

int main() {
    HomeDashboard dashboard;

    dashboard.addDevice(SmartDevice("D01", "Light", "Living Room"));
    dashboard.addDevice(SmartDevice("D02", "Thermostat", "Hallway"));
    dashboard.addDevice(SmartDevice("D03", "Camera", "Front Door"));
    dashboard.addDevice(SmartDevice("D04", "Door Lock", "Main Entrance"));

    cout << "Initial state:" << endl;
    dashboard.displayDashboard();

    cout << "Updating device statuses..." << endl;
    dashboard.getDevice(0).togglePower(true, "08:15 AM");
    dashboard.getDevice(1).changeStatus("Set to 22C", "08:16 AM");
    dashboard.getDevice(2).changeStatus("Recording", "08:20 AM");
    dashboard.getDevice(3).changeStatus("Locked", "08:25 AM");

    dashboard.displayDashboard();

    return 0;
}
