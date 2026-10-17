/*   
    Definition
        Proxy is a structural design pattern that provides a substitute or placeholder for another object and controls access to that object.

    Memory hook:
        Proxy → stand between client and real object to control access.
    
    Use cases:
    
        Authentication
        Caching
        Lazy loading
        Logging
        Remote access
        Permission checking

*/


#include <iostream>
#include <string>

class Server {
public:
    virtual void request() = 0;
    virtual ~Server() = default;
};

class RealServer : public Server {
public:
    void request() override {
        std::cout << "Real server processing request\n";
    }
};

class ServerProxy : public Server {
private:
    RealServer server;
    bool authenticated;

public:
    ServerProxy(bool authenticated)
        : authenticated(authenticated) {}

    void request() override {
        if (!authenticated) {
            std::cout << "Access denied\n";
            return;
        }

        std::cout << "Proxy: access granted\n";
        server.request();
    }
};

int main() {
    ServerProxy user1(false);
    user1.request();
    std::cout <<"\n";
    
    ServerProxy user2(true);
    user2.request();
}