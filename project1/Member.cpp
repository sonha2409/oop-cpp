#include "Member.h"
#include <iostream>
#include <algorithm>

// std::string name; 
// int memberID;
// std::vector<Book*> borrowedBooks;


// Constructor
Member:: Member(const std::string& name, int memberID)
    : name(name), memberID(memberID) {} 

// Destructor 
Member::~Member() {
    std::cout << "Member delted" << std::endl;
}

// Getters
std::string Member::getName() const {
    return this->name;
}

int Member::getMemberID() const {
    return this->memberID;
}

std::vector<Book*> Member::getBorrowedBooks() const {
    return this->borrowedBooks;
}

// Borrow a book
bool Member::borrowBook(Book* book) {
  if (book == nullptr) {
    std::cout << "Error: Invalid pointer" << std::endl;
    return false;
  }

  if (!book->getAvailability()) {
    std::cout << "error: Book is not available" << std::endl;
    return false;
  }

  // Check if member has already borrowed the book
  for (Book* borrowed : borrowedBooks) {
    if (borrowed == book) {
      std::cout << "Error: You have already borrowed this book" << std::endl;
      return false;
    }
  }
  
  borrowedBooks.push_back(book);
  book->setAvailability(false);
  std::cout << "Book borrowed successfully:" << book->getTitle() << std::endl;
  return true;
}

//
bool Member::returnBook(Book* book) {

  // Check pointer valid
  if (book == nullptr) {
      std::cout << "Error: invalid" << std::endl;
      return false;
  }

  // Find the book in the borrowedBooks vector
  auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), book);

  if (it == borrowedBooks.end()) {
    std::cout << "Error: You have not borrowed this book" << std::endl;
    return false;
  }

  borrowedBooks.erase(it);
  book->setAvailability(true);
  std::cout << "Successfully returned book: " << book->getTitle() << std::endl;
  return true;
    
}

void Member::displayInfo() const {
  std::cout << "Member Name: " << name << std::endl;
  std::cout << "Member ID: " << memberID << std::endl;
  std::cout << "Number of Borrowed Books: " << borrowedBooks.size() << std::endl;
}

void Member::displayBorrowedBooks() const {
  if (borrowedBooks.empty()) {
    std::cout << "No borrowed books." << std::endl;
    return;
  }

  std::cout << "Borrowed Books:" << std::endl;
  for (size_t i = 0; i < borrowedBooks.size(); ++i) {
    std::cout << "  - " << borrowedBooks[i]->getTitle() << std::endl;
  }
}