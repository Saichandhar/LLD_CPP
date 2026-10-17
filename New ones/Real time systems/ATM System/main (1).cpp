/******************************************************************************

                ATM System

                    ATM
               +-------------------+
               | - currentState    |
               | - noCardState     |
               | - cardState       |
               | - authState       |
               +-------------------+
               | + insertCard()    |
               | + enterPin()      |
               | + withdraw()      |
               | + ejectCard()     |
               +---------+---------+
                         |
                         | HAS-A
                         v
                    <<interface>>
                      ATMState
                         ▲
             ┌───────────┼───────────┐
             │           │           │
        NoCardState   CardState   AuthState


Cash dispensing:

             CashDispenser
                  ▲
                  |
       +----------+----------+
       |          |          |
   ₹500 Handler ₹200 Handler ₹100 Handler

Chain:

₹500 → ₹200 → ₹100


*******************************************************************************/


#include <iostream>

class ATM;


// ======================================================
// ATM STATE
// ======================================================

class ATMState {
public:
    virtual void insertCard(ATM& atm) = 0;
    virtual void enterPin(ATM& atm, int pin) = 0;
    virtual void withdraw(ATM& atm, int amount) = 0;
    virtual void ejectCard(ATM& atm) = 0;

    virtual ~ATMState() = default;
};


class NoCardState : public ATMState {
public:
    void insertCard(ATM& atm) override;
    void enterPin(ATM& atm, int pin) override;
    void withdraw(ATM& atm, int amount) override;
    void ejectCard(ATM& atm) override;
};


class CardInsertedState : public ATMState {
public:
    void insertCard(ATM& atm) override;
    void enterPin(ATM& atm, int pin) override;
    void withdraw(ATM& atm, int amount) override;
    void ejectCard(ATM& atm) override;
};


class AuthenticatedState : public ATMState {
public:
    void insertCard(ATM& atm) override;
    void enterPin(ATM& atm, int pin) override;
    void withdraw(ATM& atm, int amount) override;
    void ejectCard(ATM& atm) override;
};


// ======================================================
// CASH DISPENSER CHAIN
// ======================================================

class CashDispenser {
protected:
    CashDispenser* next = nullptr;

public:

    void setNext(CashDispenser* dispenser) {
        next = dispenser;
    }

    virtual void dispense(int amount) = 0;

    virtual ~CashDispenser() = default;
};


class FiveHundredDispenser : public CashDispenser {
public:

    void dispense(int amount) override {

        int notes = amount / 500;
        int remaining = amount % 500;

        if (notes > 0) {
            std::cout
                << notes
                << " x Rs.500\n";
        }

        if (remaining > 0 && next != nullptr) {
            next->dispense(remaining);
        }
    }
};


class TwoHundredDispenser : public CashDispenser {
public:

    void dispense(int amount) override {

        int notes = amount / 200;
        int remaining = amount % 200;

        if (notes > 0) {
            std::cout
                << notes
                << " x Rs.200\n";
        }

        if (remaining > 0 && next != nullptr) {
            next->dispense(remaining);
        }
    }
};


class OneHundredDispenser : public CashDispenser {
public:

    void dispense(int amount) override {

        int notes = amount / 100;
        int remaining = amount % 100;

        if (notes > 0) {
            std::cout
                << notes
                << " x Rs.100\n";
        }

        if (remaining > 0) {
            std::cout
                << "Cannot dispense remaining Rs."
                << remaining
                << '\n';
        }
    }
};


// ======================================================
// ATM
// ======================================================

class ATM {

private:

    NoCardState noCardState;
    CardInsertedState cardInsertedState;
    AuthenticatedState authenticatedState;

    ATMState* currentState;

    FiveHundredDispenser fiveHundred;
    TwoHundredDispenser twoHundred;
    OneHundredDispenser oneHundred;

public:

    ATM()
        : currentState(&noCardState) {

        // Build cash dispenser chain

        fiveHundred.setNext(&twoHundred);
        twoHundred.setNext(&oneHundred);
    }


    void insertCard() {
        currentState->insertCard(*this);
    }


    void enterPin(int pin) {
        currentState->enterPin(*this, pin);
    }


    void withdraw(int amount) {
        currentState->withdraw(*this, amount);
    }


    void ejectCard() {
        currentState->ejectCard(*this);
    }


    // State transitions

    void setNoCardState() {
        currentState = &noCardState;
    }


    void setCardInsertedState() {
        currentState = &cardInsertedState;
    }


    void setAuthenticatedState() {
        currentState = &authenticatedState;
    }


    void dispenseCash(int amount) {

        if (amount <= 0) {
            std::cout << "Invalid amount\n";
            return;
        }

        if (amount % 100 != 0) {
            std::cout
                << "Amount must be a multiple of Rs.100\n";
            return;
        }

        fiveHundred.dispense(amount);
    }
};


// ======================================================
// NO CARD STATE
// ======================================================

void NoCardState::insertCard(ATM& atm) {

    std::cout << "Card inserted\n";

    atm.setCardInsertedState();
}


void NoCardState::enterPin(ATM&, int) {

    std::cout << "Insert card first\n";
}


void NoCardState::withdraw(ATM&, int) {

    std::cout << "Insert card first\n";
}


void NoCardState::ejectCard(ATM&) {

    std::cout << "No card to eject\n";
}


// ======================================================
// CARD INSERTED STATE
// ======================================================

void CardInsertedState::insertCard(ATM&) {

    std::cout << "Card already inserted\n";
}


void CardInsertedState::enterPin(
    ATM& atm,
    int pin) {

    if (pin == 1234) {

        std::cout << "PIN accepted\n";

        atm.setAuthenticatedState();
    }
    else {

        std::cout << "Incorrect PIN\n";
    }
}


void CardInsertedState::withdraw(ATM&, int) {

    std::cout << "Enter PIN first\n";
}


void CardInsertedState::ejectCard(ATM& atm) {

    std::cout << "Card ejected\n";

    atm.setNoCardState();
}


// ======================================================
// AUTHENTICATED STATE
// ======================================================

void AuthenticatedState::insertCard(ATM&) {

    std::cout << "Card already inserted\n";
}


void AuthenticatedState::enterPin(ATM&, int) {

    std::cout << "Already authenticated\n";
}


void AuthenticatedState::withdraw(
    ATM& atm,
    int amount) {

    std::cout
        << "Dispensing Rs."
        << amount
        << '\n';

    atm.dispenseCash(amount);
}


void AuthenticatedState::ejectCard(ATM& atm) {

    std::cout << "Card ejected\n";

    atm.setNoCardState();
}


// ======================================================
// MAIN
// ======================================================

int main() {

    ATM atm;

    atm.insertCard();

    atm.enterPin(1234);

    atm.withdraw(1800);

    atm.ejectCard();

    return 0;
}