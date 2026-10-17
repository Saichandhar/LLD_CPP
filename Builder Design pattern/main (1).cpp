/******************************************************************************

Builder is a creational design pattern used to construct a complex object step by step.
It separates the construction process from the final object and is especially useful 
when an object has many optional or configurable parameters.

*******************************************************************************/
#include <iostream>


struct Computer {
    std::string cpu;
    int ram;
    int storage;
    std::string gpu;
};


class ComputerBuilder {
private: 
    Computer c;
    
public:   
    void setcpu(std::string str){
        c.cpu = str;
    }
    void setram(int r){
        c.ram = r;
    }
    void setstorage(int st){
        c.storage = st;
    }
    void setgpu(std::string g){
        c.gpu = g;
    }
    Computer build(){
        return c;
    }
        
};

int main()
{
    ComputerBuilder c;
    
    c.setcpu("INTEL");
    c.setram(4);
    c.setstorage(64);
    c.setgpu("NVIDIA");
    
    Computer com =  c.build();

    return 0;
}