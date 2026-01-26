#include "Book.h"
#include <iostream>

// private: 
// std::string title;
// std::string author;
// std::string isbn;

// Constructor
Book:: Book(const std::string& title, const std::string& author, const std::string& isbn)
{
    this->title = title;
    this->author = author;
    this->isbn = isbn;
    this->isAvailable = true;
}

// Destructor
Book::~Book() {
  std::cout << "Book: " << title << " destroyed" << std::endl;
}

// Getters
std::string Book::getTitle() const {
  return this->title;
}

std::string Book::getAuthor() const {
  return this->author;
}

std::string Book::getIBSN() const {
  return this->isbn;
}

bool Book::getAvailability() const {
  return this->isAvailable;
}

// Setters
void Book::setAvailability(bool available) {
  this->isAvailable = available;
}

void Book::displayInfo() const {
  std::cout << "Title: " << title << std::endl;
  std::cout << "Author: " << author << std::endl;
  std::cout << "ISBN: " << isbn << std::endl;
  std::cout << "Availability: " << (isAvailable ? "Available" : "Not Available") << std::endl;
}