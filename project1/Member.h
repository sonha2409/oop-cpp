#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include "Book.h"

class Member {
  // name, memberID, borrowedBooks
  private: 
    std::string name; 
    int memberID;
    std::vector<Book*> borrowedBooks;

  public:
    // constructor 
    Member(const std::string& name, int memberID);

    // destructor 
    ~Member();

    // Getters 
    std::string getName() const;
    int getMemberID() const;
    std::vector<Book*> getBorrowedBooks() const;

    // Borrow and return methods 
    bool borrowBook(Book* book);
    bool returnBook(Book* book);

    // Debugging purposes
    void displayInfo() const;
    void displayBorrowedBooks() const;


};
#endif