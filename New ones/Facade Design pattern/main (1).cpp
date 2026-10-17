/*   
    Definition
        Facade is a structural design pattern that provides a simple, unified interface to a complex set of subsystems.

    Memory hook:
        Facade → hide complexity behind one simple interface.
        
    Use cases:
        Initialize sensor
        Initialize Hailo
        Initialize network
        Initialize storage
        Start threads
        Start streaming

*/


#include <iostream>

class Camera {
public:
    void initialize() {
        std::cout << "Camera initialized\n";
    }
};

class Network {
public:
    void connect() {
        std::cout << "Network connected\n";
    }
};

class Storage {
public:
    void mount() {
        std::cout << "Storage mounted\n";
    }
};

class SurveillanceSystem {
private:
    Camera camera;
    Network network;
    Storage storage;

public:
    void start() {
        storage.mount();
        network.connect();
        camera.initialize();

        std::cout << "System ready\n";
    }
};

int main() {
    SurveillanceSystem system;

    system.start();
}