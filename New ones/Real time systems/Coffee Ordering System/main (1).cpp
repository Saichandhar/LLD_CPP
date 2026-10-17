/******************************************************************************

                Coffee Ordering System

                                        <<interface>>
                        Coffee
                 +------------------+
                 | + getCost()      |
                 | + description()  |
                 +---------+--------+
                           ▲
               ┌───────────┴────────────┐
               │                        │
        Simple Coffee             CoffeeDecorator
                                      |
                               HAS-A Coffee*
                                      |
                     ┌────────────────┼───────────────┐
                     │                │               │
                   Milk             Sugar          Vanilla


*******************************************************************************/


#include <iostream>
#include <string>


// -----------------------------
// Component Interface
// -----------------------------

class Coffee {
public:

	virtual double getCost() const = 0;

	virtual std::string getDescription() const = 0;

	virtual ~Coffee() = default;
};


// -----------------------------
// Base Coffee #1
// -----------------------------

class Espresso : public Coffee {
public:

	double getCost() const override {
		return 100;
	}

	std::string getDescription() const override {
		return "Espresso";
	}
};


// -----------------------------
// Base Coffee #2
// -----------------------------

class Cappuccino : public Coffee {
public:

	double getCost() const override {
		return 120;
	}

	std::string getDescription() const override {
		return "Cappuccino";
	}
};


// -----------------------------
// Base Decorator
// -----------------------------

class CoffeeDecorator : public Coffee {

protected:
	Coffee* coffee;

public:

	CoffeeDecorator(Coffee* coffee)
		: coffee(coffee) {
	}
};


// -----------------------------
// Milk Decorator
// -----------------------------

class Milk : public CoffeeDecorator {
public:

	Milk(Coffee* coffee)
		: CoffeeDecorator(coffee) {
	}

	double getCost() const override {

		return coffee->getCost() + 20;
	}

	std::string getDescription() const override {

		return coffee->getDescription()
		       + " + Milk";
	}
};


// -----------------------------
// Sugar Decorator
// -----------------------------

class Sugar : public CoffeeDecorator {
public:

	Sugar(Coffee* coffee)
		: CoffeeDecorator(coffee) {
	}

	double getCost() const override {

		return coffee->getCost() + 10;
	}

	std::string getDescription() const override {

		return coffee->getDescription()
		       + " + Sugar";
	}
};


// -----------------------------
// Vanilla Decorator
// -----------------------------

class Vanilla : public CoffeeDecorator {
public:

	Vanilla(Coffee* coffee)
		: CoffeeDecorator(coffee) {
	}

	double getCost() const override {

		return coffee->getCost() + 30;
	}

	std::string getDescription() const override {

		return coffee->getDescription()
		       + " + Vanilla";
	}
};


// -----------------------------
// Main
// -----------------------------

int main() {

	Espresso espresso;

	Milk milk(&espresso);

	Sugar sugar(&milk);

	Vanilla vanilla(&sugar);


	Coffee* order = &vanilla;


	std::cout
	        << order->getDescription()
	        << '\n';

	std::cout
	        << "Total: Rs."
	        << order->getCost()
	        << '\n';


	return 0;
}