#include "BankAccount.h"
#include <iostream> 

// private:
//     double balance;                         /**< Current balance in the account. */
//     AccountType type;                       /**< The type of the account. */
//     std::vector<std::string> history;       /**< Log of all transaction descriptions. */

BankAccount:: BankAccount(double initialDeposit, AccountType accountType) {
    this->balance = initialDeposit; 
    this->type = accountType;
}

// Destructor 
BankAccount:: ~BankAccount() {
    std::cout << "BankAccount: " << "destroyed" << std:endl;
}

// getters
double BankAccount:: getBalance() const {
    return this->balance;
} 

// withdraw method
bool BankAccount:: withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "account less than 0, can't withdraw"  << std::endl;
        return false;
    }
    if (amount > getBalance()) {
        std::cout << "insufficient funds" << std::endl;
        return false;
    }
    getBalance() -= amount; 
    history.push_back("withdraw amount is " + std::to_string(amount));
    std::cout << "withdraw ok" << std::endl; 
    return true;
}

// deposit method
bool BankAccount:: deposit(double amount) {
    if (amount <= 0) {
        std::cout << "deposit amount has to be valid" << std::endl; 
        return false; 
    }
    getBalance() += amount;
    history.push_back("deposit amount is " + std::to_string(amount));
    std::cout << "deposit ok:" << std::endl; 
    return true; 
}

bool BankAccount:: transfer(BankAccount& destination, double amount) { 
    if (amount <= 0){ 
        std::cout << "transfer amount invalid" << std::endl; 
        return false; 
    }
    if (amount > getBalance()) { 
        std::cout << "not enough for transferring" << std::endl;
        return false;
    }
    getBalance() -= amount; 
    destination.getBalance() += amount;
    history.push_back("transfer amount is " + std::to_string(amount) + " to destination");
    std::cout << "transfer successfully" << std::endl;
    return true; 
}

void BankAccount:: displayHistory() const { 
    if (history.empty()) { 
        std::cout << " no transaction occurred" << std::endl;
        return; 
    }
    std::cout << "all transaction history: " << std::endl;
    for (size_t i = 0; i < history.size(); ++i) { 
        std::cout << history[i] << std::endl; 
    }
}