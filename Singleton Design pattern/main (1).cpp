/******************************************************************************

Singleton is a creational design pattern that ensures a class has only one instance 
throughout the application and provides a global access point to that instance.

*******************************************************************************/

#include <iostream>

using namespace std;

class loggermanager {
    private:
        inline static loggermanager* logger = nullptr;
        
        //no default constructor
        loggermanager() {}
    
    public:
        //no copy
        loggermanager(const loggermanager&) = delete;
        loggermanager& operator=(const loggermanager&) = delete;
    
        //no move
        loggermanager(loggermanager&&) = delete;
        loggermanager& operator=(loggermanager&&) = delete;
        
        static loggermanager* getInstance(){
               if(logger == nullptr){
                    logger = new loggermanager();
               }
               return logger;
        }
};

int main()
{
    loggermanager* obj1 = loggermanager::getInstance();
    loggermanager* obj2 = loggermanager::getInstance();
    
    cout << (obj1 == obj2);
    
    return 0;
}
