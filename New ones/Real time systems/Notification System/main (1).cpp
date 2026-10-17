/*

           --> Design a Notification System


                  <<interface>>
              INotificationStrategy
              +--------------------+
              | + send(to, msg)    |
              +----------+---------+
                         ^
                         |
          +--------------+---------------+
          |              |               |
          |              |               |
 +--------+------+ +-----+------+ +------+---------+
 | EmailStrategy | | SMSStrategy| | PushStrategy  |
 +---------------+ +------------+ +---------------+
 | + send()      | | + send()   | | + send()      |
 +---------------+ +------------+ +---------------+


                  NotificationService
              +--------------------------+
              | - strategy               |
              |   INotificationStrategy* |
              +--------------------------+
              | + setStrategy()          |
              | + notify()               |
              +-------------+------------+
                            |
                            | HAS-A
                            v
                  INotificationStrategy
                  
                  

*/




#include <iostream>
#include <string>

// Strategy Interface
class INotificationStrategy {
public:
    virtual void send(const std::string& recipient,
                      const std::string& message) = 0;

    virtual ~INotificationStrategy() = default;
};


// Concrete Strategy 1
class EmailNotification : public INotificationStrategy {
public:
    void send(const std::string& recipient,
              const std::string& message) override {

        std::cout << "Sending EMAIL to "
                  << recipient
                  << ": "
                  << message
                  << '\n';
    }
};


// Concrete Strategy 2
class SMSNotification : public INotificationStrategy {
public:
    void send(const std::string& recipient,
              const std::string& message) override {

        std::cout << "Sending SMS to "
                  << recipient
                  << ": "
                  << message
                  << '\n';
    }
};


// Concrete Strategy 3
class PushNotification : public INotificationStrategy {
public:
    void send(const std::string& recipient,
              const std::string& message) override {

        std::cout << "Sending PUSH notification to "
                  << recipient
                  << ": "
                  << message
                  << '\n';
    }
};


// Context
class NotificationService {

private:
    INotificationStrategy* strategy;

public:
    NotificationService(INotificationStrategy* strategy)
        : strategy(strategy) {
    }

    void setStrategy(INotificationStrategy* newStrategy) {
        strategy = newStrategy;
    }

    void notify(const std::string& recipient,
                const std::string& message) {

        if (strategy != nullptr) {
            strategy->send(recipient, message);
        }
    }
};


int main() {

    EmailNotification email;
    SMSNotification sms;
    PushNotification push;

    NotificationService service(&email);

    service.notify(
        "Amarnath",
        "Your order has been shipped"
    );

    service.setStrategy(&sms);

    service.notify(
        "Amarnath",
        "Your OTP is 123456"
    );

    service.setStrategy(&push);

    service.notify(
        "Amarnath",
        "Your package will arrive today"
    );

    return 0;
}