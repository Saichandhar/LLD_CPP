/******************************************************************************

                Traffic Signal Controller

                        TrafficSignal
                  +----------------------+
                  | - currentState       |
                  | - observers          |
                  +----------------------+
                  | + next()             |
                  | + setState()         |
                  | + subscribe()        |
                  | + notifyObservers()  |
                  +----------+-----------+
                             |
                             | HAS-A
                             v
                       <<interface>>
                       SignalState
                             ▲
                 ┌───────────┼───────────┐
                 │           │           │
              RedState   GreenState   YellowState


                        <<interface>>
                         Observer
                             ▲
                    ┌────────┴────────┐
                    │                 │
           PedestrianDisplay   MonitoringSystem


*******************************************************************************/


#include <iostream>
#include <string>
#include <vector>

class TrafficSignal;


// =====================================================
// OBSERVER
// =====================================================

class Observer {
public:
    virtual void update(
        const std::string& state) = 0;

    virtual ~Observer() = default;
};


class PedestrianDisplay : public Observer {
public:

    void update(
        const std::string& state) override {

        if (state == "RED") {
            std::cout
                << "Pedestrian Display: WALK\n";
        }
        else {
            std::cout
                << "Pedestrian Display: WAIT\n";
        }
    }
};


class MonitoringSystem : public Observer {
public:

    void update(
        const std::string& state) override {

        std::cout
            << "Monitoring System: Signal changed to "
            << state
            << '\n';
    }
};


// =====================================================
// STATE
// =====================================================

class SignalState {
public:

    virtual void next(
        TrafficSignal& signal) = 0;

    virtual std::string getName() const = 0;

    virtual ~SignalState() = default;
};


class RedState : public SignalState {
public:

    void next(TrafficSignal& signal) override;

    std::string getName() const override {
        return "RED";
    }
};


class GreenState : public SignalState {
public:

    void next(TrafficSignal& signal) override;

    std::string getName() const override {
        return "GREEN";
    }
};


class YellowState : public SignalState {
public:

    void next(TrafficSignal& signal) override;

    std::string getName() const override {
        return "YELLOW";
    }
};


// =====================================================
// TRAFFIC SIGNAL
// =====================================================

class TrafficSignal {

private:

    RedState redState;
    GreenState greenState;
    YellowState yellowState;

    SignalState* currentState;

    std::vector<Observer*> observers;

public:

    TrafficSignal()
        : currentState(&redState) {
    }


    void subscribe(Observer* observer) {

        observers.push_back(observer);
    }


    void notifyObservers() {

        std::string state =
            currentState->getName();

        for (Observer* observer : observers) {

            observer->update(state);
        }
    }


    void next() {

        currentState->next(*this);
    }


    void setRed() {

        currentState = &redState;

        std::cout << "\nSignal: RED\n";

        notifyObservers();
    }


    void setGreen() {

        currentState = &greenState;

        std::cout << "\nSignal: GREEN\n";

        notifyObservers();
    }


    void setYellow() {

        currentState = &yellowState;

        std::cout << "\nSignal: YELLOW\n";

        notifyObservers();
    }


    std::string getCurrentState() const {

        return currentState->getName();
    }
};


// =====================================================
// STATE TRANSITIONS
// =====================================================

void RedState::next(
    TrafficSignal& signal) {

    signal.setGreen();
}


void GreenState::next(
    TrafficSignal& signal) {

    signal.setYellow();
}


void YellowState::next(
    TrafficSignal& signal) {

    signal.setRed();
}


// =====================================================
// MAIN
// =====================================================

int main() {

    TrafficSignal signal;

    PedestrianDisplay pedestrianDisplay;
    MonitoringSystem monitoringSystem;


    signal.subscribe(
        &pedestrianDisplay
    );

    signal.subscribe(
        &monitoringSystem
    );


    std::cout
        << "Initial Signal: "
        << signal.getCurrentState()
        << '\n';


    signal.next();   // RED -> GREEN

    signal.next();   // GREEN -> YELLOW

    signal.next();   // YELLOW -> RED


    return 0;
}