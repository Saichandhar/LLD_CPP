/******************************************************************************

        Vending Machine
        
        Problem
            Design a vending machine that supports:
                - Selecting a product
                - Inserting money
                - Dispensing the selected product
                - Returning to idle after dispensing
                - Preventing invalid operations depending on the machine's current condition
                
                
            
            
                    <<interface>>
                         State
              +-------------------------+
              | + selectProduct()       |
              | + insertMoney()         |
              | + dispense()            |
              +------------+------------+
                           ▲
              ┌────────────┼─────────────┐
              │            │             │
         IdleState   HasSelectionState  DispensingState


                         VendingMachine
              +---------------------------+
              | - currentState : State*   |
              | - idleState               |
              | - selectionState          |
              | - dispensingState         |
              +---------------------------+
              | + selectProduct()         |
              | + insertMoney()           |
              | + dispense()              |
              | + setState()              |
              +-------------+-------------+
                            |
                            | HAS-A
                            ▼
                           State

*******************************************************************************/
#include <iostream>

// Forward declaration
class VendingMachine;


// --------------------
// State Interface
// --------------------

class State {
public:
    virtual void selectProduct(VendingMachine& machine) = 0;
    virtual void insertMoney(VendingMachine& machine) = 0;
    virtual void dispense(VendingMachine& machine) = 0;

    virtual ~State() = default;
};


// --------------------
// Concrete States
// --------------------

class IdleState : public State {
public:
    void selectProduct(VendingMachine& machine) override;
    void insertMoney(VendingMachine& machine) override;
    void dispense(VendingMachine& machine) override;
};


class HasSelectionState : public State {
public:
    void selectProduct(VendingMachine& machine) override;
    void insertMoney(VendingMachine& machine) override;
    void dispense(VendingMachine& machine) override;
};


class DispensingState : public State {
public:
    void selectProduct(VendingMachine& machine) override;
    void insertMoney(VendingMachine& machine) override;
    void dispense(VendingMachine& machine) override;
};


// --------------------
// Context
// --------------------

class VendingMachine {

private:
    IdleState idleState;
    HasSelectionState selectionState;
    DispensingState dispensingState;

    State* currentState;

public:

    VendingMachine()
        : currentState(&idleState) {
    }

    void selectProduct() {
        currentState->selectProduct(*this);
    }

    void insertMoney() {
        currentState->insertMoney(*this);
    }

    void dispense() {
        currentState->dispense(*this);
    }


    void setIdleState() {
        currentState = &idleState;
    }

    void setSelectionState() {
        currentState = &selectionState;
    }

    void setDispensingState() {
        currentState = &dispensingState;
    }
};


// --------------------
// Idle State
// --------------------

void IdleState::selectProduct(VendingMachine& machine) {

    std::cout << "Product selected\n";

    machine.setSelectionState();
}


void IdleState::insertMoney(VendingMachine&) {

    std::cout << "Select a product first\n";
}


void IdleState::dispense(VendingMachine&) {

    std::cout << "Cannot dispense. No product selected\n";
}


// --------------------
// Has Selection State
// --------------------

void HasSelectionState::selectProduct(VendingMachine&) {

    std::cout << "Product already selected\n";
}


void HasSelectionState::insertMoney(VendingMachine& machine) {

    std::cout << "Rs.50 received\n";

    machine.setDispensingState();
}


void HasSelectionState::dispense(VendingMachine&) {

    std::cout << "Insert money first\n";
}


// --------------------
// Dispensing State
// --------------------

void DispensingState::selectProduct(VendingMachine&) {

    std::cout << "Please wait. Dispensing product\n";
}


void DispensingState::insertMoney(VendingMachine&) {

    std::cout << "Money already received\n";
}


void DispensingState::dispense(VendingMachine& machine) {

    std::cout << "Product dispensed\n";

    machine.setIdleState();
}


// --------------------
// Main
// --------------------

int main() {

    VendingMachine machine;

    machine.selectProduct();
    machine.insertMoney();
    machine.dispense();

    std::cout << "\n";

    // Machine should now be IDLE again
    machine.insertMoney();

    return 0;
}