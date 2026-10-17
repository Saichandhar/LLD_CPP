/******************************************************************************

                 Logger System
        
        
                  <<abstract>>
                     Logger
          +-------------------------+
          | - next : Logger*        |
          +-------------------------+
          | + setNext(Logger*)      |
          | + log(level, message)   |
          | # write(message)        |
          +------------+------------+
                       ▲
              ┌────────┼────────┐
              │        │        │
              │        │        │
         InfoLogger DebugLogger ErrorLogger


*******************************************************************************/


#include <iostream>
#include <string>

enum class LogLevel {
    INFO,
    DEBUG,
    ERROR
};


// ----------------------------
// Base Handler
// ----------------------------

class Logger {
protected:
    Logger* next = nullptr;

public:

    void setNext(Logger* nextLogger) {
        next = nextLogger;
    }

    virtual void log(
        LogLevel level,
        const std::string& message) = 0;

    virtual ~Logger() = default;
};


// ----------------------------
// INFO Handler
// ----------------------------

class InfoLogger : public Logger {
public:

    void log(
        LogLevel level,
        const std::string& message) override {

        if (level == LogLevel::INFO) {

            std::cout
                << "[INFO] "
                << message
                << '\n';

            return;
        }

        if (next != nullptr) {
            next->log(level, message);
        }
    }
};


// ----------------------------
// DEBUG Handler
// ----------------------------

class DebugLogger : public Logger {
public:

    void log(
        LogLevel level,
        const std::string& message) override {

        if (level == LogLevel::DEBUG) {

            std::cout
                << "[DEBUG] "
                << message
                << '\n';

            return;
        }

        if (next != nullptr) {
            next->log(level, message);
        }
    }
};


// ----------------------------
// ERROR Handler
// ----------------------------

class ErrorLogger : public Logger {
public:

    void log(
        LogLevel level,
        const std::string& message) override {

        if (level == LogLevel::ERROR) {

            std::cout
                << "[ERROR] "
                << message
                << '\n';

            return;
        }

        if (next != nullptr) {
            next->log(level, message);
        }
    }
};


// ----------------------------
// Main
// ----------------------------

int main() {

    InfoLogger info;
    DebugLogger debug;
    ErrorLogger error;

    // Build the chain
    info.setNext(&debug);
    debug.setNext(&error);

    Logger* logger = &info;


    logger->log(
        LogLevel::INFO,
        "Application started"
    );

    logger->log(
        LogLevel::DEBUG,
        "Queue size = 25"
    );

    logger->log(
        LogLevel::ERROR,
        "Camera initialization failed"
    );

    return 0;
}