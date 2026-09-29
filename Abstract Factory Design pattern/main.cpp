/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

using namespace std;


class Dashboard{
public:
        virtual void build() = 0;
  
};


class Toyota_Dashboard : public Dashboard{
public:
       void build() override{
           cout << "Here is the toyota dashboard built ...... "<<endl;
       }
  
};

class BMW_Dashboard : public Dashboard{
public:

        void build() override{
            cout << "Here is the BMW dashboard built.......    "<< endl;
            
        }
    
  
};

class Engine{
public:
     virtual void build() = 0;
};


class Toyota_Engine : public Engine{
    public:
      void build() override{
          cout << "Here is the toyota engine ...... "<< endl;
      }
};


class BMW_Engine : public Engine{
    public:
      void build() override{
          cout << "Here is the BMW engine ....... "<< endl;
      }
};


class Seat {
public: 
    virtual void build() = 0;
};

class Toyota_seat : public Seat{
 public: 
    void build() override{
        cout << "Here is the toyota seat ....... "<< endl;
    }
    
};

class BMW_seat : public Seat{
public:
    void build() override{
        cout << "Here is the BMW seat .............. "<< endl;
    }
};




class CarFactory {
public:
    virtual Dashboard* create_dashboard() = 0;
    virtual Engine* create_engine() = 0;
    virtual Seat* create_seat() = 0;
};

class BMWCar : public CarFactory{
public:
   Dashboard* create_dashboard() override {
       return new BMW_Dashboard();
        
    }
    Engine* create_engine() override {
        return new BMW_Engine();
        
    }
    Seat* create_seat() override {
       return new BMW_seat();
    }
    
};


class ToyotaCar : public CarFactory {
public:
        Dashboard* create_dashboard() override {
            return new Toyota_Dashboard();
            
        }
        Engine* create_engine() override {
            return new Toyota_Engine();
           
        }
        Seat* create_seat() override {
            return new Toyota_seat();
        }
};






int main() {
    
    
   CarFactory* obj1 = new ToyotaCar();
   Engine* obj2 = obj1->create_engine();
   obj2->build();
   
    
   return 0;
    
}