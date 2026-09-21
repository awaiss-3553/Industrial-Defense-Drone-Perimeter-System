#include <iostream>
#include <string>
using namespace std;

class DefenseDrone {
protected:
    string droneID;
    double batteryCapacity;

public:
    static int airborneDrones;

    DefenseDrone(string droneID, double batteryCapacity) {
        this->droneID = droneID;
        this->batteryCapacity = batteryCapacity;
        airborneDrones++;
    }

    virtual ~DefenseDrone() {
        cout << "[DOCKED] Drone " << droneID << " safely recalled to charging bay." << endl;
        airborneDrones--;
    }

    virtual double calculateSurveillanceArea() = 0;
    virtual void renderTelemetry() = 0;
};

int DefenseDrone::airborneDrones = 0;

class ReconDrone : public DefenseDrone {
private:
    double cameraZoomMultiplier;

public:
    ReconDrone(string droneID, double batteryCapacity, double cameraZoomMultiplier)
        : DefenseDrone(droneID, batteryCapacity), cameraZoomMultiplier(cameraZoomMultiplier) {}

    double calculateSurveillanceArea() override {
        return (batteryCapacity * 12.5) * cameraZoomMultiplier;
    }

    void renderTelemetry() override {
        cout << "\n--- [RECON DRONE TELEMETRY] ---" << endl;
        cout << "Drone ID        : " << droneID << endl;
        cout << "Battery         : " << batteryCapacity << "%" << endl;
        cout << "Zoom Factor     : " << cameraZoomMultiplier << "x" << endl;
        cout << "Coverage Area   : " << calculateSurveillanceArea() << " sq m" << endl;
    }
};

class ThermalDrone : public DefenseDrone {
private:
    int infraredSensors;

public:
    ThermalDrone(string droneID, double batteryCapacity, int infraredSensors)
        : DefenseDrone(droneID, batteryCapacity), infraredSensors(infraredSensors) {}

    double calculateSurveillanceArea() override {
        return (batteryCapacity * 15.0) + (infraredSensors * 50.0);
    }

    void renderTelemetry() override {
        cout << "\n--- [THERMAL DRONE TELEMETRY] ---" << endl;
        cout << "Drone ID        : " << droneID << endl;
        cout << "Battery         : " << batteryCapacity << "%" << endl;
        cout << "IR Sensors      : " << infraredSensors << endl;
        cout << "Coverage Area   : " << calculateSurveillanceArea() << " sq m" << endl;
    }
};

int main() {
    DefenseDrone* swarm[2];

    swarm[0] = new ReconDrone("RD-X1", 85.0, 4.0);
    swarm[1] = new ThermalDrone("TD-Z9", 92.0, 6);

    for (int i = 0; i < 2; i++) {
        swarm[i]->renderTelemetry();
    }

    cout << "\n=============================================" << endl;
    cout << "Active Airborne Drones: " << DefenseDrone::airborneDrones << endl;
    cout << "=============================================\n" << endl;

    for (int i = 0; i < 2; i++) {
        delete swarm[i];
        swarm[i] = nullptr;
    }

    cout << "\n=============================================" << endl;
    cout << "Airborne Drones After Docking: " << DefenseDrone::airborneDrones << endl;
    cout << "=============================================" << endl;

    return 0;
}
