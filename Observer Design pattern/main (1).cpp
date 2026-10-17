/******************************************************************************

Observer is a behavioral design pattern that defines a one-to-many relationship between objects,
where when the state of one object changes, all subscribed observers are automatically notified.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>


class Iobserver {
    public:
       virtual void update() = 0;
};

class Ipublisher{
    public:
        std::vector<Iobserver*> users;
        virtual void subscribe(Iobserver* user) = 0;
        virtual void unsubscribe(Iobserver* user) = 0;
        virtual void notify() = 0;
};



class observer : public Iobserver{
    public:
        void update() override{
            std::cout << "Here is the update recieved ......."<< std::endl;
        }
};


class publisher : public Ipublisher{
    public:
        void subscribe(Iobserver* user){
            // std::cout << "Hello hello ......    "<< std::endl;
            users.push_back(user);
        }
        
        void unsubscribe(Iobserver* user){
            auto it = std::find(users.begin(),users.end(),user);
            if(it != users.end()){
                users.erase(it);
            }
        }
        
        void notify(){
            for(Iobserver* user : users){
                user->update();
            }
        }
};





int main()
{

    
    Ipublisher* ram = new publisher();
    
    Iobserver* ajay = new observer();
    
    ram->subscribe(ajay);
    
    ram->notify();
    
    delete ajay;
    delete ram;

    return 0;
}