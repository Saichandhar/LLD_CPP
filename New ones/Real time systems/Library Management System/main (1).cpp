/******************************************************************************

                Library Management System

                                 +----------------+
              |      Book      |
              +----------------+
              | isbn           |
              | title          |
              | author         |
              +----------------+
                      ▲
                      |
                  describes
                      |
              +----------------+
              |    BookCopy    |
              +----------------+
              | copyId         |
              | available      |
              | Book*          |
              +----------------+


 Member                         Loan
+-------------+          +----------------+
| memberId    | <------- | Member*        |
| name        |          | BookCopy*      |
+-------------+          +----------------+
                              |
                              v
                           BookCopy


                 Library
          +-----------------------+
          | books                 |
          | copies                |
          | activeLoans           |
          +-----------------------+
          | borrowBook()          |
          | returnBook()          |
          +-----------------------+


             <<interface>>
              SearchStrategy
                    ▲
              ┌─────┴─────┐
              │           │
        TitleSearch   AuthorSearch


*******************************************************************************/


#include <iostream>
#include <string>
#include <vector>


// =====================================================
// BOOK
// =====================================================

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;

public:
    Book(const std::string& isbn,
         const std::string& title,
         const std::string& author)
        : isbn(isbn),
          title(title),
          author(author) {
    }

    const std::string& getISBN() const {
        return isbn;
    }

    const std::string& getTitle() const {
        return title;
    }

    const std::string& getAuthor() const {
        return author;
    }
};


// =====================================================
// BOOK COPY
// =====================================================

class BookCopy {
private:
    int copyId;
    Book* book;
    bool available;

public:
    BookCopy(int copyId, Book* book)
        : copyId(copyId),
          book(book),
          available(true) {
    }

    int getCopyId() const {
        return copyId;
    }

    Book* getBook() const {
        return book;
    }

    bool isAvailable() const {
        return available;
    }

    void borrow() {
        available = false;
    }

    void returnCopy() {
        available = true;
    }
};


// =====================================================
// MEMBER
// =====================================================

class Member {
private:
    int memberId;
    std::string name;

public:
    Member(int id, const std::string& name)
        : memberId(id),
          name(name) {
    }

    int getId() const {
        return memberId;
    }

    const std::string& getName() const {
        return name;
    }
};


// =====================================================
// LOAN
// =====================================================

class Loan {
private:
    Member* member;
    BookCopy* copy;

public:
    Loan(Member* member, BookCopy* copy)
        : member(member),
          copy(copy) {
    }

    Member* getMember() const {
        return member;
    }

    BookCopy* getCopy() const {
        return copy;
    }
};


// =====================================================
// SEARCH STRATEGY
// =====================================================

class SearchStrategy {
public:
    virtual bool matches(
        const Book& book,
        const std::string& query) const = 0;

    virtual ~SearchStrategy() = default;
};


class TitleSearch : public SearchStrategy {
public:

    bool matches(
        const Book& book,
        const std::string& query) const override {

        return book.getTitle().find(query)
            != std::string::npos;
    }
};


class AuthorSearch : public SearchStrategy {
public:

    bool matches(
        const Book& book,
        const std::string& query) const override {

        return book.getAuthor().find(query)
            != std::string::npos;
    }
};


// =====================================================
// LIBRARY
// =====================================================

class Library {
private:

    std::vector<Book*> books;
    std::vector<BookCopy*> copies;
    std::vector<Loan> activeLoans;

public:

    void addBook(Book* book) {
        books.push_back(book);
    }


    void addCopy(BookCopy* copy) {
        copies.push_back(copy);
    }


    int getActiveLoanCount(Member* member) const {

        int count = 0;

        for (const Loan& loan : activeLoans) {

            if (loan.getMember() == member) {
                ++count;
            }
        }

        return count;
    }


    BookCopy* findAvailableCopy(
        const std::string& isbn) {

        for (BookCopy* copy : copies) {

            if (copy->getBook()->getISBN() == isbn &&
                copy->isAvailable()) {

                return copy;
            }
        }

        return nullptr;
    }


    void borrowBook(
        Member* member,
        const std::string& isbn) {

        if (getActiveLoanCount(member) >= 3) {

            std::cout
                << member->getName()
                << " has reached the borrowing limit\n";

            return;
        }


        BookCopy* copy =
            findAvailableCopy(isbn);


        if (copy == nullptr) {

            std::cout
                << "No available copy\n";

            return;
        }


        copy->borrow();

        activeLoans.emplace_back(
            member,
            copy
        );


        std::cout
            << member->getName()
            << " borrowed "
            << copy->getBook()->getTitle()
            << " [Copy "
            << copy->getCopyId()
            << "]\n";
    }


    void returnBook(
        Member* member,
        int copyId) {

        for (auto it = activeLoans.begin();
             it != activeLoans.end();
             ++it) {

            if (it->getMember() == member &&
                it->getCopy()->getCopyId() == copyId) {

                BookCopy* copy =
                    it->getCopy();

                copy->returnCopy();

                std::cout
                    << member->getName()
                    << " returned "
                    << copy->getBook()->getTitle()
                    << '\n';

                activeLoans.erase(it);

                return;
            }
        }


        std::cout
            << "Active loan not found\n";
    }


    void search(
        const SearchStrategy& strategy,
        const std::string& query) const {

        std::cout
            << "\nSearch results:\n";


        for (Book* book : books) {

            if (strategy.matches(
                    *book,
                    query)) {

                std::cout
                    << book->getTitle()
                    << " by "
                    << book->getAuthor()
                    << '\n';
            }
        }
    }
};


// =====================================================
// MAIN
// =====================================================

int main() {

    Book cleanCode(
        "ISBN-1",
        "Clean Code",
        "Robert Martin"
    );

    Book cpp(
        "ISBN-2",
        "Effective Modern C++",
        "Scott Meyers"
    );


    BookCopy copy1(
        101,
        &cleanCode
    );

    BookCopy copy2(
        102,
        &cleanCode
    );

    BookCopy copy3(
        201,
        &cpp
    );


    Member amarnath(
        1,
        "Amarnath"
    );


    Library library;

    library.addBook(&cleanCode);
    library.addBook(&cpp);

    library.addCopy(&copy1);
    library.addCopy(&copy2);
    library.addCopy(&copy3);


    // Search

    TitleSearch titleSearch;

    library.search(
        titleSearch,
        "Clean"
    );


    // Borrow

    library.borrowBook(
        &amarnath,
        "ISBN-1"
    );


    // Return physical copy #101

    library.returnBook(
        &amarnath,
        101
    );


    return 0;
}