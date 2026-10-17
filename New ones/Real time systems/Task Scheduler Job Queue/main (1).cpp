/******************************************************************************

                Task Scheduler  Job Queue

                                         <<interface>>
                          Task
                   +---------------+
                   | + execute()   |
                   +-------+-------+
                           ▲
             ┌─────────────┼─────────────┐
             │             │             │
             │             │             │
        ImageTask       EmailTask     BackupTask


                    TaskScheduler
               +----------------------+
               | queue<Task*>         |
               +----------------------+
               | + submitTask()       |
               | + runNext()          |
               | + runAll()           |
               +----------+-----------+
                          |
                          |
                          v
                     FIFO Queue

                  front         back
                    ↓             ↓
               +-------+-------+-------+
               | Task1 | Task2 | Task3 |
               +-------+-------+-------+


*******************************************************************************/


#include <iostream>
#include <queue>
#include <string>


// =====================================================
// COMMAND INTERFACE
// =====================================================

class Task {
public:

    virtual void execute() = 0;

    virtual ~Task() = default;
};


// =====================================================
// CONCRETE COMMAND #1
// =====================================================

class ImageProcessingTask : public Task {

private:
    int imageId;

public:

    ImageProcessingTask(int id)
        : imageId(id) {
    }

    void execute() override {

        std::cout
            << "Processing image "
            << imageId
            << '\n';
    }
};


// =====================================================
// CONCRETE COMMAND #2
// =====================================================

class EmailTask : public Task {

private:
    std::string recipient;

public:

    EmailTask(
        const std::string& recipient)
        : recipient(recipient) {
    }

    void execute() override {

        std::cout
            << "Sending email to "
            << recipient
            << '\n';
    }
};


// =====================================================
// CONCRETE COMMAND #3
// =====================================================

class DatabaseBackupTask : public Task {

public:

    void execute() override {

        std::cout
            << "Backing up database\n";
    }
};


// =====================================================
// SCHEDULER
// =====================================================

class TaskScheduler {

private:

    std::queue<Task*> tasks;

public:

    void submitTask(Task* task) {

        tasks.push(task);

        std::cout
            << "Task submitted\n";
    }


    void runNext() {

        if (tasks.empty()) {

            std::cout
                << "No tasks available\n";

            return;
        }


        Task* task =
            tasks.front();

        tasks.pop();


        task->execute();
    }


    void runAll() {

        while (!tasks.empty()) {

            runNext();
        }
    }


    bool empty() const {

        return tasks.empty();
    }
};


// =====================================================
// MAIN
// =====================================================

int main() {

    ImageProcessingTask image1(101);

    EmailTask email(
        "user@example.com"
    );

    DatabaseBackupTask backup;


    TaskScheduler scheduler;


    scheduler.submitTask(&image1);

    scheduler.submitTask(&email);

    scheduler.submitTask(&backup);


    std::cout
        << "\nExecuting tasks:\n";


    scheduler.runAll();


    return 0;
}