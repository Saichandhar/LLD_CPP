/*   
    Definition:
        Command is a behavioral design pattern that encapsulates a request or operation as an object, separating the object that requests an operation from the object that performs it.
        
    Memory hook:
        Command → turn an action/request into an object.
        
    Use cases:
    
        Remote control
            Button → Command → Device

        GUI
            Button → SaveCommand → Document

        Robot
            Controller → MoveCommand → Motor

        Camera system
            Hub → StartStreamCommand → Camera

        Job queue
            Queue → Task/Command → Worker

*/


#include <iostream>

class Light {
public:
    void turnOn() {
        std::cout << "Light ON\n";
    }

    void turnOff() {
        std::cout << "Light OFF\n";
    }
};

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class TurnOnCommand : public Command {
private:
    Light* light;

public:
    TurnOnCommand(Light* light) : light(light) {}

    void execute() override {
        light->turnOn();
    }
};

class TurnOffCommand : public Command {
private:
    Light* light;

public:
    TurnOffCommand(Light* light) : light(light) {}

    void execute() override {
        light->turnOff();
    }
};

class RemoteControl {
private:
    Command* command;

public:
    void setCommand(Command* cmd) {
        command = cmd;
    }

    void pressButton() {
        command->execute();
    }
};

int main() {
    Light light;

    TurnOnCommand on(&light);
    TurnOffCommand off(&light);

    RemoteControl remote;

    remote.setCommand(&on);
    remote.pressButton();

    remote.setCommand(&off);
    remote.pressButton();
}