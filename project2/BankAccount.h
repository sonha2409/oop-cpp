/**
 * @file BankAccount.h
 * @brief Definition of the BankAccount class and related types.
 */

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>

/**
 * @enum AccountType
 * @brief Defines the supported types of bank accounts.
 */
enum class AccountType {
    SAVINGS,   /**< Savings account with potential interest. */
    CHECKING   /**< Standard checking account for daily transactions. */
};

/**
 * @class BankAccount
 * @brief Manages a single bank account's balance and transaction history.
 * * This class provides thread-safe-ready logic (conceptual) for depositing, 
 * withdrawing, and transferring funds between accounts while maintaining 
 * an internal ledger of all activities.
 */
class BankAccount {
private:
    double balance;                         /**< Current balance in the account. */
    AccountType type;                       /**< The type of the account. */
    std::vector<std::string> history;       /**< Log of all transaction descriptions. */

public:
    /**
     * @brief Constructs a new BankAccount object.
     * * @param initialDeposit The starting balance (must be non-negative).
     * @param accountType The category of the account (Savings/Checking).
     */
    BankAccount(double initialDeposit, AccountType accountType);

    /**
     * @brief Deposits a specified amount into the account.
     * * @param amount The sum of money to add.
     * @return true if the deposit was successful (amount > 0).
     * @return false if the amount is invalid.
     * * @note Successful deposits should be recorded in the transaction history.
     */
    bool deposit(double amount);

    /**
     * @brief Withdraws a specified amount from the account.
     * * @param amount The sum of money to remove.
     * @return true if the withdrawal was successful.
     * @return false if the amount is negative or exceeds the current balance.
     * * @pre balance >= amount
     */
    bool withdraw(double amount);

    /**
     * @brief Transfers funds from this account to a destination account.
     * * @param destination A reference to the BankAccount receiving the funds.
     * @param amount The sum of money to transfer.
     * @return true if the transfer was completed.
     * @return false if the amount is invalid or this account has insufficient funds.
     * * @post This account's balance decreases and destination's balance increases.
     */
    bool transfer(BankAccount& destination, double amount);

    /**
     * @brief Retrieves the current balance.
     * @return The current balance as a double.
     */
    double getBalance() const;

    /**
     * @brief Prints the full list of transactions to the console.
     * * Format: [Deposit/Withdraw/Transfer]: $Amount
     */
    void displayHistory() const;
};

#endif // BANKACCOUNT_H