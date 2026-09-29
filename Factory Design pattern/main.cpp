/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

using namespace std;


// Product Interface
class Car {
public:
    virtual void drive() = 0;
    virtual ~Car() = default;
};


// Concrete Product - Toyota
class ToyotaCar : public Car {
public:
    void drive() override {
        cout << "Here is the Toyota car driving....." << endl;
    }
};


// Concrete Product - BMW
class BMWCar : public Car {
public:
    void drive() override {
        cout << "Here is the BMW car driving....." << endl;
    }
};


// Creator Interface
class CarFactory {
public:
    virtual Car* createCar() = 0;
    virtual ~CarFactory() = default;
};


// Concrete Creator - Toyota
class ToyotaFactory : public CarFactory {
public:
    Car* createCar() override {
        return new ToyotaCar();
    }
};


// Concrete Creator - BMW
class BMWFactory : public CarFactory {
public:
    Car* createCar() override {
        return new BMWCar();
    }
};


int main()
{
    CarFactory* factory = new ToyotaFactory();

    Car* car = factory->createCar();

    car->drive();

    delete car;
    delete factory;

    return 0;
}