/******************************************************************************

                File System

                        <<interface>>
                      FileSystemItem
                 +----------------------+
                 | + getName()          |
                 | + getSize()          |
                 | + display()          |
                 +----------+-----------+
                            ▲
                  ┌─────────┴─────────┐
                  │                   │
                File              Directory
          +---------------+    +-------------------+
          | name          |    | name              |
          | size          |    | children          |
          +---------------+    | vector<Item*>     |
                               +-------------------+
                               | + add()           |
                               | + getSize()       |
                               | + display()       |
                               +---------+---------+
                                         |
                                         | contains
                                         |
                                         └── FileSystemItem*


*******************************************************************************/


#include <iostream>
#include <string>
#include <vector>


// ---------------------------------
// Component
// ---------------------------------

class FileSystemItem {
public:

    virtual std::string getName() const = 0;

    virtual int getSize() const = 0;

    virtual void display(int depth = 0) const = 0;

    virtual ~FileSystemItem() = default;
};


// ---------------------------------
// Leaf
// ---------------------------------

class File : public FileSystemItem {

private:
    std::string name;
    int size;

public:

    File(
        const std::string& name,
        int size)
        : name(name),
          size(size) {
    }


    std::string getName() const override {
        return name;
    }


    int getSize() const override {
        return size;
    }


    void display(int depth = 0) const override {

        std::cout
            << std::string(depth * 2, ' ')
            << name
            << " (" << size << " KB)"
            << '\n';
    }
};


// ---------------------------------
// Composite
// ---------------------------------

class Directory : public FileSystemItem {

private:
    std::string name;

    std::vector<FileSystemItem*> children;

public:

    Directory(const std::string& name)
        : name(name) {
    }


    std::string getName() const override {
        return name;
    }


    void add(FileSystemItem* item) {
        children.push_back(item);
    }


    int getSize() const override {

        int total = 0;

        for (FileSystemItem* item : children) {
            total += item->getSize();
        }

        return total;
    }


    void display(int depth = 0) const override {

        std::cout
            << std::string(depth * 2, ' ')
            << name
            << "/"
            << '\n';


        for (FileSystemItem* item : children) {

            item->display(depth + 1);
        }
    }
};


// ---------------------------------
// Main
// ---------------------------------

int main() {

    File resume(
        "resume.pdf",
        20
    );

    File photo(
        "photo.jpg",
        50
    );

    File notes(
        "notes.txt",
        10
    );

    File code(
        "code.cpp",
        30
    );


    Directory projects(
        "projects"
    );

    projects.add(&code);


    Directory documents(
        "documents"
    );

    documents.add(&notes);
    documents.add(&projects);


    Directory root(
        "root"
    );

    root.add(&resume);
    root.add(&photo);
    root.add(&documents);


    root.display();


    std::cout
        << "\nTotal size: "
        << root.getSize()
        << " KB\n";


    return 0;
}