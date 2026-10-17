/*   
    Definition
        Template Method is a behavioral pattern that defines the overall structure of an algorithm in a base class while allowing subclasses to
        customize individual steps without changing the algorithm's structure.

    Memory hook:
        Algorithm stays fixed; some steps can change.
    
    Use cases:
        read()
          ↓
        process()
          ↓
        save()

*/


#include <iostream>

class DataProcessor {
public:
    void execute() {
        read();
        process();
        save();
    }

    virtual ~DataProcessor() = default;

protected:
    virtual void read() = 0;
    virtual void process() = 0;

    void save() {
        std::cout << "Saving result\n";
    }
};

class ImageProcessor : public DataProcessor {
protected:
    void read() override {
        std::cout << "Reading image\n";
    }

    void process() override {
        std::cout << "Processing image\n";
    }
};

class VideoProcessor : public DataProcessor {
protected:
    void read() override {
        std::cout << "Reading video\n";
    }

    void process() override {
        std::cout << "Processing video\n";
    }
};

int main() {
    ImageProcessor image;
    image.execute();

    std::cout << '\n';

    VideoProcessor video;
    video.execute();
}