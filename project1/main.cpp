#include <iostream>
#include "Book.h"
#include "Member.h"

int main() {

  // Create 3 mock books
  Book book1("Tit Kevin ngui si lip", "Son Ha", "123456789");
  Book book2("Xi Trum mat serum", "Tit Kevin", "1231245112");
  Book book3("Long nghien tri tra", "Duc Hoang", "19284012984");

  // Create 2 mock members
  Member member1("Nguyen Van A", 001);
  Member member2("Tran Thi B", 002);

  std::cout << "=== Demo === " << std::endl << std::endl;
  std::cout << "Initial Book Status:" << std::endl;
  book1.displayInfo();
  std::cout << std::endl;
  book2.displayInfo();
  std::cout << std::endl;

  // Member 1 borrow books
  std::cout << " === Member 1 actions === " << std::endl;
  member1.displayInfo();
  std::cout << std::endl;

  member1.borrowBook(&book1);
  member1.borrowBook(&book2);
  std::cout << std::endl;

  member1.displayBorrowedBooks();
  std::cout << std::endl;

  // Member 2 tries to borrow book1 (already borrowed)
  std::cout << " === Member 2 actions === " << std::endl;
  member2.displayInfo();
  member2.borrowBook(&book1); // Should fail
  member2.borrowBook(&book3); // Should succeed

  std::cout << std::endl;
  member2.displayBorrowedBooks();
  std::cout << std::endl;

  // Check book avaialibity after borrowing
  std::cout << " === Book availability after borrowing === " << std::endl;
  book1.displayInfo();
  std::cout << std::endl;
  book2.displayInfo();
  std::cout << std::endl;
  book3.displayInfo();
  std::cout << std::endl;

  // Member 1 returns a book
  std::cout << " === Member 1 returns a book === " << std::endl;
  member1.returnBook(&book1);
  std::cout << std::endl;

  member1.displayBorrowedBooks();
  std::cout << std::endl;


  // Check avaliablity after return
  std::cout << " === Book availability after returning === " << std::endl;
  book1.displayInfo();
  std::cout << std::endl;

  // Member 2 can now borrow book 1
  std::cout << " === Member 2 borrows book 1 === " << std::endl;
  member2.borrowBook(&book1); // Should succeed
  std::cout << std::endl;

  member2.displayBorrowedBooks();
  std::cout << std::endl;

  return 0;










  


}