/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

class coffee {
public:
      virtual void make() = 0;
      virtual ~coffee() = default;
          
};

class coffeeDecorator : public coffee {
public:
    coffee* c;
    
    coffeeDecorator(coffee* c) {
        this->c = c;
    }
    
    void make() override{
        c->make();
        // std::cout << "Here is coffee ....."<< std::endl;
    }
};


class simplecoffee : public coffee{
public:
        
        void make() override {
            
            std::cout<<"Here is simple coffee.....   "<< std::endl;
        }
};


class milk : public coffeeDecorator {
public:
        milk(coffee* c) : coffeeDecorator(c){}
        void make() override {
            c->make();
            std::cout << "Here is milk ........ "<< std::endl;
        }
};

class sugar : public coffeeDecorator {
public:
        sugar(coffee* c) : coffeeDecorator(c) {}
        void make() override {
            c->make();
            std::cout << "Here is the sugar......... "<< std::endl;
        }
};

class vanilla : public coffeeDecorator {
public:
     vanilla(coffee* c) : coffeeDecorator(c){}
    void make() override {
        c->make();
        std::cout << "Here is the vanilla with total price.......... "<< std::endl;
    }
};


int main()
{
    //Here is one simplecoffee
      coffee* c = new simplecoffee();
     
     coffee* m = new milk(c);
     
     coffee* v = new vanilla(m);
     
     
    //  s->make();
    
    v->make();
    
    delete v;
    
    delete m;
    
    delete c;
    

    return 0;
}