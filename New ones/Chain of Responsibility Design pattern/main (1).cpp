/*   
    Definition
        Chain of Responsibility is a behavioral pattern where a request is passed through a chain of handlers until one 
        handles it or the chain ends.

    Memory hook:
        Request → Handler 1 → Handler 2 → Handler 3
    
    Use cases:
        Logging

        DEBUG → INFO → ERROR

        HTTP middleware

        Authentication
            ↓
        Authorization
            ↓
        Validation
            ↓
        Request Handler

*/


#include <iostream>

class Handler {
protected:
    Handler* next = nullptr;

public:
    void setNext(Handler* handler) {
        next = handler;
    }

    virtual void handle(int level) {
        if (next)
            next->handle(level);
    }

    virtual ~Handler() = default;
};

class Level1Support : public Handler {
public:
    void handle(int level) override {
        if (level == 1)
            std::cout << "L1 handled request\n";
        else if (next)
            next->handle(level);
    }
};

class Level2Support : public Handler {
public:
    void handle(int level) override {
        if (level == 2)
            std::cout << "L2 handled request\n";
        else if (next)
            next->handle(level);
    }
};

class Level3Support : public Handler {
public:
    void handle(int level) override {
        if (level >= 3)
            std::cout << "L3 handled request\n";
        else if (next)
            next->handle(level);
    }
};

int main() {
    Level1Support l1;
    Level2Support l2;
    Level3Support l3;

    l1.setNext(&l2);
    l2.setNext(&l3);

    l1.handle(2);
}