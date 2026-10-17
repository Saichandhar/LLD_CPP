/*   
    Definition
        Prototype is a creational design pattern that creates new objects by copying or cloning an existing object instead of constructing them from scratch.

    Memory hook:
        Prototype → create from a copy.
    
    Use cases:
    
        Game enemies
        Document templates
        UI configurations
        Simulation objects
        Preconfigured devices

*/


#include <iostream>
#include <string>

class Robot {
private:
    std::string model;
    int speed;

public:
    Robot(std::string model, int speed)
        : model(model), speed(speed) {}

    Robot* clone() const {
        return new Robot(*this);
    }

    void show() const {
        std::cout << model
                  << " speed = "
                  << speed << '\n';
    }
};

int main() {
    Robot original("RX100", 10);

    Robot* copy = original.clone();

    original.show();
    copy->show();

    delete copy;
}