/**
 * @file main.cpp
 * @brief Example usage of the BankAccount class.
 */

#include "BankAccount.h"
#include <iostream>

int main() {
    std::cout << "=== BankAccount Demo ===\n\n";
    
    // Create two accounts
    BankAccount savings(1000.0, AccountType::SAVINGS);
    BankAccount checking(500.0, AccountType::CHECKING);
    
    std::cout << "Initial balances:\n";
    std::cout << "Savings: $" << savings.getBalance() << "\n";
    std::cout << "Checking: $" << checking.getBalance() << "\n\n";
    
    // Perform some transactions
    std::cout << "Performing transactions...\n";
    savings.deposit(200.0);
    checking.withdraw(100.0);
    savings.transfer(checking, 150.0);
    checking.deposit(50.0);
    
    std::cout << "\nFinal balances:\n";
    std::cout << "Savings: $" << savings.getBalance() << "\n";
    std::cout << "Checking: $" << checking.getBalance() << "\n\n";
    
    // Display transaction history
    std::cout << "Savings Account History:\n";
    savings.displayHistory();
    
    std::cout << "\nChecking Account History:\n";
    checking.displayHistory();
    
    // Test error cases
    std::cout << "\n\nTesting error cases:\n";
    std::cout << "Attempting to deposit -$10: " 
              << (savings.deposit(-10.0) ? "Success" : "Failed (expected)") << "\n";
    std::cout << "Attempting to withdraw $10000: " 
              << (savings.withdraw(10000.0) ? "Success" : "Failed (expected)") << "\n";
    std::cout << "Attempting to transfer $10000: " 
              << (savings.transfer(checking, 10000.0) ? "Success" : "Failed (expected)") << "\n";
    
    return 0;
}
