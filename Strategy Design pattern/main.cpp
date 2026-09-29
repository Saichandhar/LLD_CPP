/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;


// Strategy Interface
class IPayment {
public:
    virtual void pay(int value) = 0;
    virtual ~IPayment() = default;
};


// Concrete Strategy 1
class CreditCardPayment : public IPayment {
public:
    void pay(int value) override {
        cout << "Credit card payment of: " << value << endl;
    }
};


// Concrete Strategy 2
class UPIPayment : public IPayment {
public:
    void pay(int value) override {
        cout << "UPI payment of: " << value << endl;
    }
};


// Concrete Strategy 3
class CashPayment : public IPayment {
public:
    void pay(int value) override {
        cout << "Cash payment of: " << value << endl;
    }
};


// Context
class Payment {
private:
    IPayment* strategy;

public:
    Payment(IPayment* strategy)
        : strategy(strategy) {
    }

    void setPayment(IPayment* strategy) {
        this->strategy = strategy;
    }

    void makePayment(int value) {
        strategy->pay(value);
    }
};


int main()
{
    CreditCardPayment credit;
    UPIPayment upi;
    CashPayment cash;

    Payment payment(&credit);

    payment.makePayment(100);

    // Change strategy at runtime
    payment.setPayment(&upi);
    payment.makePayment(200);

    payment.setPayment(&cash);
    payment.makePayment(300);

    return 0;
}