#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
  private: 
    std::string title;
    std::string author;
    std::string isbn;
    bool isAvailable;
  public: 
    // Constructor
    Book(const std::string& title, const std::string& author, const std::string& isbn);

    // Destructor
    ~Book();

    // Getters
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getIBSN() const;
    bool getAvailability() const;

    // Setters
    void setAvailability(bool available);

    // Dispplay book information
    void displayInfo() const;
};

#endif