/******************************************************************************

                Camera  Device Management System

                        CameraDevice
                    << Facade / Context >>
                  +-----------------------+
                  | currentState          |
                  | observers             |
                  | sensor                |
                  | inference             |
                  | network               |
                  | storage               |
                  +-----------------------+
                  | start()               |
                  | startStreaming()      |
                  | stopStreaming()       |
                  | shutdown()            |
                  +-----------+-----------+
                              |
                            HAS-A
                              |
                              v
                        CameraState
                              ▲
           ┌──────────┬───────┼───────────┐
           │          │       │           │
          Off       Ready  Streaming    Error


Hub
 |
 v
Command
 ▲
 ├── StartStreamCommand
 ├── StopStreamCommand
 └── RestartCommand


CameraDevice
 |
 | notify()
 v
Observer
 ▲
 ├── Logger
 ├── Telemetry
 └── HealthMonitor


*******************************************************************************/


#include <iostream>
#include <string>
#include <vector>

class CameraDevice;


// =====================================================
// OBSERVER
// =====================================================

class Observer {
public:
    virtual void update(const std::string& event) = 0;
    virtual ~Observer() = default;
};


class Logger : public Observer {
public:
    void update(const std::string& event) override {
        std::cout << "[LOG] " << event << '\n';
    }
};


class Telemetry : public Observer {
public:
    void update(const std::string& event) override {
        std::cout << "[TELEMETRY] " << event << '\n';
    }
};


class HealthMonitor : public Observer {
public:
    void update(const std::string& event) override {
        std::cout << "[HEALTH] " << event << '\n';
    }
};


// =====================================================
// SUBSYSTEMS
// =====================================================

class CameraSensor {
public:
    void initialize() {
        std::cout << "Sensor initialized\n";
    }

    void shutdown() {
        std::cout << "Sensor shutdown\n";
    }
};


class InferenceEngine {
public:
    void loadModel() {
        std::cout << "Inference model loaded\n";
    }

    void stop() {
        std::cout << "Inference engine stopped\n";
    }
};


class NetworkManager {
public:
    void connect() {
        std::cout << "Network connected\n";
    }

    void disconnect() {
        std::cout << "Network disconnected\n";
    }
};


class StorageManager {
public:
    void initialize() {
        std::cout << "Storage initialized\n";
    }

    void shutdown() {
        std::cout << "Storage shutdown\n";
    }
};


// =====================================================
// STATE
// =====================================================

class CameraState {
public:
    virtual void startStreaming(CameraDevice& device) = 0;
    virtual void stopStreaming(CameraDevice& device) = 0;

    virtual std::string name() const = 0;

    virtual ~CameraState() = default;
};


class OffState : public CameraState {
public:
    void startStreaming(CameraDevice&) override {
        std::cout << "Camera is OFF\n";
    }

    void stopStreaming(CameraDevice&) override {
        std::cout << "Camera is already OFF\n";
    }

    std::string name() const override {
        return "OFF";
    }
};


class ReadyState : public CameraState {
public:
    void startStreaming(CameraDevice& device) override;

    void stopStreaming(CameraDevice&) override {
        std::cout << "Camera is not streaming\n";
    }

    std::string name() const override {
        return "READY";
    }
};


class StreamingState : public CameraState {
public:
    void startStreaming(CameraDevice&) override {
        std::cout << "Already streaming\n";
    }

    void stopStreaming(CameraDevice& device) override;

    std::string name() const override {
        return "STREAMING";
    }
};


class ErrorState : public CameraState {
public:
    void startStreaming(CameraDevice&) override {
        std::cout << "Cannot stream: camera is in ERROR\n";
    }

    void stopStreaming(CameraDevice&) override {
        std::cout << "Camera is in ERROR\n";
    }

    std::string name() const override {
        return "ERROR";
    }
};


// =====================================================
// CAMERA DEVICE
// =====================================================

class CameraDevice {

private:
    CameraSensor sensor;
    InferenceEngine inference;
    NetworkManager network;
    StorageManager storage;

    OffState offState;
    ReadyState readyState;
    StreamingState streamingState;
    ErrorState errorState;

    CameraState* currentState;

    std::vector<Observer*> observers;

public:

    CameraDevice()
        : currentState(&offState) {
    }


    // -------------------------
    // Observer
    // -------------------------

    void subscribe(Observer* observer) {
        observers.push_back(observer);
    }


    void notify(const std::string& event) {

        for (Observer* observer : observers) {
            observer->update(event);
        }
    }


    // -------------------------
    // Facade: startup
    // -------------------------

    void start() {

        if (currentState != &offState) {
            std::cout << "Camera already started\n";
            return;
        }

        std::cout << "\nStarting camera...\n";

        notify("Camera INITIALIZING");

        sensor.initialize();

        storage.initialize();

        network.connect();

        inference.loadModel();

        setReadyState();
    }


    // -------------------------
    // State operations
    // -------------------------

    void startStreaming() {
        currentState->startStreaming(*this);
    }


    void stopStreaming() {
        currentState->stopStreaming(*this);
    }


    // -------------------------
    // Facade: shutdown
    // -------------------------

    void shutdown() {

        std::cout << "\nShutting down camera...\n";

        inference.stop();

        network.disconnect();

        storage.shutdown();

        sensor.shutdown();

        currentState = &offState;

        notify("Camera OFF");
    }


    // -------------------------
    // State transitions
    // -------------------------

    void setReadyState() {

        currentState = &readyState;

        notify("Camera READY");
    }


    void setStreamingState() {

        currentState = &streamingState;

        notify("Camera STREAMING");
    }


    void setErrorState() {

        currentState = &errorState;

        notify("Camera ERROR");
    }


    std::string getState() const {
        return currentState->name();
    }
};


// =====================================================
// STATE IMPLEMENTATIONS
// =====================================================

void ReadyState::startStreaming(
    CameraDevice& device) {

    std::cout
        << "Starting video stream\n";

    device.setStreamingState();
}


void StreamingState::stopStreaming(
    CameraDevice& device) {

    std::cout
        << "Stopping video stream\n";

    device.setReadyState();
}


// =====================================================
// COMMAND
// =====================================================

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};


class StartStreamCommand : public Command {

private:
    CameraDevice* device;

public:

    StartStreamCommand(CameraDevice* device)
        : device(device) {
    }

    void execute() override {

        device->startStreaming();
    }
};


class StopStreamCommand : public Command {

private:
    CameraDevice* device;

public:

    StopStreamCommand(CameraDevice* device)
        : device(device) {
    }

    void execute() override {

        device->stopStreaming();
    }
};


class RestartCommand : public Command {

private:
    CameraDevice* device;

public:

    RestartCommand(CameraDevice* device)
        : device(device) {
    }

    void execute() override {

        device->shutdown();

        device->start();
    }
};


// =====================================================
// HUB
// =====================================================

class Hub {

public:

    void sendCommand(Command& command) {

        command.execute();
    }
};


// =====================================================
// MAIN
// =====================================================

int main() {

    CameraDevice camera;


    Logger logger;
    Telemetry telemetry;
    HealthMonitor health;


    camera.subscribe(&logger);
    camera.subscribe(&telemetry);
    camera.subscribe(&health);


    // Facade startup

    camera.start();


    // Commands from hub

    StartStreamCommand startCommand(&camera);
    StopStreamCommand stopCommand(&camera);
    RestartCommand restartCommand(&camera);


    Hub hub;


    std::cout << "\nHub: START_STREAM\n";

    hub.sendCommand(startCommand);


    std::cout << "\nHub: STOP_STREAM\n";

    hub.sendCommand(stopCommand);


    std::cout << "\nHub: RESTART\n";

    hub.sendCommand(restartCommand);


    return 0;
}