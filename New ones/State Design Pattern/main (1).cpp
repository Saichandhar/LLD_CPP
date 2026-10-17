/*   
    Definition:
        State is a behavioral design pattern that allows an object to change its behavior when its internal state changes. Each state is encapsulated in a separate class.
    
    Memory hook:
        State → same object, different behavior depending on current state.
        
    Real-world use cases :
        Camera
            OFF → INITIALIZING → STREAMING → ERROR

        OTA Updater
            IDLE → DOWNLOADING → INSTALLING → VALIDATING → ROLLBACK

        Elevator
            IDLE → MOVING → DOOR_OPEN

        Media Player
            STOPPED → PLAYING → PAUSED

*/

#include <iostream>

class State {
public:
    virtual void handle() = 0;
    virtual ~State() = default;
};

class IdleState : public State {
public:
    void handle() override {
        std::cout << "System is IDLE\n";
    }
};

class RunningState : public State {
public:
    void handle() override {
        std::cout << "System is RUNNING\n";
    }
};

class ErrorState : public State {
public:
    void handle() override {
        std::cout << "System is in ERROR state\n";
    }
};

class Machine {
private:
    State* state;

public:
    Machine(State* state) : state(state) {}

    void setState(State* newState) {
        state = newState;
    }

    void execute() {
        state->handle();
    }
};

int main() {
    IdleState idle;
    RunningState running;
    ErrorState error;

    Machine machine(&idle);
    machine.execute();

    machine.setState(&running);
    machine.execute();

    machine.setState(&error);
    machine.execute();
}