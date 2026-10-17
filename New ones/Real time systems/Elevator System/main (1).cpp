/******************************************************************************

                 Elevator System
                 
                    ElevatorController
                 +-------------------------+
                 | - elevators             |
                 | - strategy              |
                 +-------------------------+
                 | + requestElevator()     |
                 +------------+------------+
                              |
                              | uses
                              v
                        <<interface>>
                    ElevatorSelectionStrategy
                            ▲
                            |
                    NearestElevatorStrategy


            ElevatorController
               |
               | manages
               v
          +----------+
          | Elevator |
          +----------+
          | id       |
          | floor    |
          | direction|
          +----------+
          | moveTo() |
          +----------+


*******************************************************************************/


#include <iostream>
#include <vector>
#include <cmath>
#include <limits>


enum class Direction {
    UP,
    DOWN,
    IDLE
};


// --------------------------------
// Elevator
// --------------------------------

class Elevator {
private:
    int id;
    int currentFloor;
    Direction direction;

public:

    Elevator(int id, int floor = 0)
        : id(id),
          currentFloor(floor),
          direction(Direction::IDLE) {
    }

    int getId() const {
        return id;
    }

    int getCurrentFloor() const {
        return currentFloor;
    }

    Direction getDirection() const {
        return direction;
    }


    void moveTo(int destinationFloor) {

        if (destinationFloor > currentFloor) {

            direction = Direction::UP;

            std::cout
                << "Elevator "
                << id
                << " moving UP from "
                << currentFloor
                << " to "
                << destinationFloor
                << '\n';
        }

        else if (destinationFloor < currentFloor) {

            direction = Direction::DOWN;

            std::cout
                << "Elevator "
                << id
                << " moving DOWN from "
                << currentFloor
                << " to "
                << destinationFloor
                << '\n';
        }

        else {

            std::cout
                << "Elevator "
                << id
                << " already at floor "
                << destinationFloor
                << '\n';
        }


        currentFloor = destinationFloor;

        direction = Direction::IDLE;

        std::cout
            << "Elevator "
            << id
            << " reached floor "
            << currentFloor
            << '\n';
    }
};


// --------------------------------
// Strategy Interface
// --------------------------------

class ElevatorSelectionStrategy {
public:

    virtual Elevator* selectElevator(
        std::vector<Elevator>& elevators,
        int requestedFloor) = 0;

    virtual ~ElevatorSelectionStrategy() = default;
};


// --------------------------------
// Nearest Elevator Strategy
// --------------------------------

class NearestElevatorStrategy
    : public ElevatorSelectionStrategy {

public:

    Elevator* selectElevator(
        std::vector<Elevator>& elevators,
        int requestedFloor) override {

        Elevator* selected = nullptr;

        int minimumDistance =
            std::numeric_limits<int>::max();


        for (Elevator& elevator : elevators) {

            int distance =
                std::abs(
                    elevator.getCurrentFloor()
                    - requestedFloor
                );


            if (distance < minimumDistance) {

                minimumDistance = distance;

                selected = &elevator;
            }
        }

        return selected;
    }
};


// --------------------------------
// Elevator Controller
// --------------------------------

class ElevatorController {
private:

    std::vector<Elevator> elevators;

    ElevatorSelectionStrategy* strategy;

public:

    ElevatorController(
        ElevatorSelectionStrategy* strategy)
        : strategy(strategy) {
    }


    void addElevator(
        int id,
        int startingFloor) {

        elevators.emplace_back(
            id,
            startingFloor
        );
    }


    Elevator* requestElevator(
        int requestedFloor) {

        Elevator* elevator =
            strategy->selectElevator(
                elevators,
                requestedFloor
            );


        if (elevator == nullptr) {

            std::cout
                << "No elevator available\n";

            return nullptr;
        }


        std::cout
            << "\nElevator "
            << elevator->getId()
            << " selected for floor "
            << requestedFloor
            << '\n';


        elevator->moveTo(
            requestedFloor
        );


        return elevator;
    }
};


// --------------------------------
// Main
// --------------------------------

int main() {

    NearestElevatorStrategy strategy;

    ElevatorController controller(
        &strategy
    );


    controller.addElevator(1, 2);
    controller.addElevator(2, 7);
    controller.addElevator(3, 10);


    // Someone on floor 6 presses the button

    Elevator* elevator =
        controller.requestElevator(6);


    // User enters and presses floor 12

    if (elevator != nullptr) {

        elevator->moveTo(12);
    }


    return 0;
}