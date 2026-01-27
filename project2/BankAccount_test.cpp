/**
 * @file BankAccount_test.cpp
 * @brief Comprehensive unit tests for the BankAccount class.
 */

#include <gtest/gtest.h>
#include "BankAccount.h"
#include <sstream>
#include <iostream>

// Test fixture for BankAccount tests
class BankAccountTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// ============================================================================
// Constructor Tests
// ============================================================================

TEST_F(BankAccountTest, Constructor_ValidInitialDeposit_Savings) {
    BankAccount account(100.0, AccountType::SAVINGS);
    EXPECT_DOUBLE_EQ(100.0, account.getBalance());
}

TEST_F(BankAccountTest, Constructor_ValidInitialDeposit_Checking) {
    BankAccount account(50.5, AccountType::CHECKING);
    EXPECT_DOUBLE_EQ(50.5, account.getBalance());
}

TEST_F(BankAccountTest, Constructor_ZeroInitialDeposit) {
    BankAccount account(0.0, AccountType::SAVINGS);
    EXPECT_DOUBLE_EQ(0.0, account.getBalance());
}

TEST_F(BankAccountTest, Constructor_LargeInitialDeposit) {
    BankAccount account(1000000.99, AccountType::CHECKING);
    EXPECT_DOUBLE_EQ(1000000.99, account.getBalance());
}

TEST_F(BankAccountTest, Constructor_SmallInitialDeposit) {
    BankAccount account(0.01, AccountType::SAVINGS);
    EXPECT_DOUBLE_EQ(0.01, account.getBalance());
}

// ============================================================================
// Deposit Tests
// ============================================================================

TEST_F(BankAccountTest, Deposit_PositiveAmount_Success) {
    BankAccount account(100.0, AccountType::SAVINGS);
    bool result = account.deposit(50.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(150.0, account.getBalance());
}

TEST_F(BankAccountTest, Deposit_MultipleDeposits) {
    BankAccount account(100.0, AccountType::CHECKING);
    account.deposit(25.0);
    account.deposit(75.0);
    account.deposit(10.5);
    EXPECT_DOUBLE_EQ(210.5, account.getBalance());
}

TEST_F(BankAccountTest, Deposit_ZeroAmount_ShouldFail) {
    BankAccount account(100.0, AccountType::SAVINGS);
    bool result = account.deposit(0.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(100.0, account.getBalance()); // Balance unchanged
}

TEST_F(BankAccountTest, Deposit_NegativeAmount_ShouldFail) {
    BankAccount account(100.0, AccountType::CHECKING);
    bool result = account.deposit(-10.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(100.0, account.getBalance()); // Balance unchanged
}

TEST_F(BankAccountTest, Deposit_SmallAmount) {
    BankAccount account(100.0, AccountType::SAVINGS);
    bool result = account.deposit(0.01);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(100.01, account.getBalance());
}

TEST_F(BankAccountTest, Deposit_LargeAmount) {
    BankAccount account(100.0, AccountType::CHECKING);
    bool result = account.deposit(999999.99);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(1000099.99, account.getBalance());
}

TEST_F(BankAccountTest, Deposit_ToZeroBalanceAccount) {
    BankAccount account(0.0, AccountType::SAVINGS);
    bool result = account.deposit(100.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(100.0, account.getBalance());
}

// ============================================================================
// Withdraw Tests
// ============================================================================

TEST_F(BankAccountTest, Withdraw_ValidAmount_Success) {
    BankAccount account(100.0, AccountType::SAVINGS);
    bool result = account.withdraw(30.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(70.0, account.getBalance());
}

TEST_F(BankAccountTest, Withdraw_ExactBalance) {
    BankAccount account(100.0, AccountType::CHECKING);
    bool result = account.withdraw(100.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(0.0, account.getBalance());
}

TEST_F(BankAccountTest, Withdraw_InsufficientFunds_ShouldFail) {
    BankAccount account(100.0, AccountType::SAVINGS);
    bool result = account.withdraw(150.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(100.0, account.getBalance()); // Balance unchanged
}

TEST_F(BankAccountTest, Withdraw_MoreThanBalance_ShouldFail) {
    BankAccount account(50.0, AccountType::CHECKING);
    bool result = account.withdraw(50.01);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(50.0, account.getBalance()); // Balance unchanged
}

TEST_F(BankAccountTest, Withdraw_ZeroAmount_ShouldFail) {
    BankAccount account(100.0, AccountType::SAVINGS);
    bool result = account.withdraw(0.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(100.0, account.getBalance()); // Balance unchanged
}

TEST_F(BankAccountTest, Withdraw_NegativeAmount_ShouldFail) {
    BankAccount account(100.0, AccountType::CHECKING);
    bool result = account.withdraw(-10.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(100.0, account.getBalance()); // Balance unchanged
}

TEST_F(BankAccountTest, Withdraw_FromZeroBalance_ShouldFail) {
    BankAccount account(0.0, AccountType::SAVINGS);
    bool result = account.withdraw(1.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(0.0, account.getBalance());
}

TEST_F(BankAccountTest, Withdraw_MultipleWithdrawals) {
    BankAccount account(200.0, AccountType::CHECKING);
    account.withdraw(50.0);
    account.withdraw(30.0);
    account.withdraw(20.0);
    EXPECT_DOUBLE_EQ(100.0, account.getBalance());
}

TEST_F(BankAccountTest, Withdraw_SmallAmount) {
    BankAccount account(100.0, AccountType::SAVINGS);
    bool result = account.withdraw(0.01);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(99.99, account.getBalance());
}

// ============================================================================
// Transfer Tests
// ============================================================================

TEST_F(BankAccountTest, Transfer_ValidAmount_Success) {
    BankAccount source(200.0, AccountType::SAVINGS);
    BankAccount destination(100.0, AccountType::CHECKING);
    
    bool result = source.transfer(destination, 50.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(150.0, source.getBalance());
    EXPECT_DOUBLE_EQ(150.0, destination.getBalance());
}

TEST_F(BankAccountTest, Transfer_ExactBalance) {
    BankAccount source(100.0, AccountType::SAVINGS);
    BankAccount destination(0.0, AccountType::CHECKING);
    
    bool result = source.transfer(destination, 100.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(0.0, source.getBalance());
    EXPECT_DOUBLE_EQ(100.0, destination.getBalance());
}

TEST_F(BankAccountTest, Transfer_InsufficientFunds_ShouldFail) {
    BankAccount source(50.0, AccountType::SAVINGS);
    BankAccount destination(100.0, AccountType::CHECKING);
    
    bool result = source.transfer(destination, 100.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(50.0, source.getBalance()); // Unchanged
    EXPECT_DOUBLE_EQ(100.0, destination.getBalance()); // Unchanged
}

TEST_F(BankAccountTest, Transfer_MoreThanBalance_ShouldFail) {
    BankAccount source(100.0, AccountType::CHECKING);
    BankAccount destination(50.0, AccountType::SAVINGS);
    
    bool result = source.transfer(destination, 100.01);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(100.0, source.getBalance()); // Unchanged
    EXPECT_DOUBLE_EQ(50.0, destination.getBalance()); // Unchanged
}

TEST_F(BankAccountTest, Transfer_ZeroAmount_ShouldFail) {
    BankAccount source(100.0, AccountType::SAVINGS);
    BankAccount destination(50.0, AccountType::CHECKING);
    
    bool result = source.transfer(destination, 0.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(100.0, source.getBalance()); // Unchanged
    EXPECT_DOUBLE_EQ(50.0, destination.getBalance()); // Unchanged
}

TEST_F(BankAccountTest, Transfer_NegativeAmount_ShouldFail) {
    BankAccount source(100.0, AccountType::SAVINGS);
    BankAccount destination(50.0, AccountType::CHECKING);
    
    bool result = source.transfer(destination, -10.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(100.0, source.getBalance()); // Unchanged
    EXPECT_DOUBLE_EQ(50.0, destination.getBalance()); // Unchanged
}

TEST_F(BankAccountTest, Transfer_ToZeroBalanceAccount) {
    BankAccount source(100.0, AccountType::SAVINGS);
    BankAccount destination(0.0, AccountType::CHECKING);
    
    bool result = source.transfer(destination, 50.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(50.0, source.getBalance());
    EXPECT_DOUBLE_EQ(50.0, destination.getBalance());
}

TEST_F(BankAccountTest, Transfer_MultipleTransfers) {
    BankAccount source(300.0, AccountType::SAVINGS);
    BankAccount destination(100.0, AccountType::CHECKING);
    
    source.transfer(destination, 50.0);
    source.transfer(destination, 30.0);
    source.transfer(destination, 20.0);
    
    EXPECT_DOUBLE_EQ(200.0, source.getBalance());
    EXPECT_DOUBLE_EQ(200.0, destination.getBalance());
}

TEST_F(BankAccountTest, Transfer_SmallAmount) {
    BankAccount source(100.0, AccountType::SAVINGS);
    BankAccount destination(50.0, AccountType::CHECKING);
    
    bool result = source.transfer(destination, 0.01);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(99.99, source.getBalance());
    EXPECT_DOUBLE_EQ(50.01, destination.getBalance());
}

TEST_F(BankAccountTest, Transfer_BetweenDifferentAccountTypes) {
    BankAccount savings(200.0, AccountType::SAVINGS);
    BankAccount checking(100.0, AccountType::CHECKING);
    
    bool result = savings.transfer(checking, 75.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(125.0, savings.getBalance());
    EXPECT_DOUBLE_EQ(175.0, checking.getBalance());
}

// ============================================================================
// GetBalance Tests
// ============================================================================

TEST_F(BankAccountTest, GetBalance_AfterConstruction) {
    BankAccount account(123.45, AccountType::SAVINGS);
    EXPECT_DOUBLE_EQ(123.45, account.getBalance());
}

TEST_F(BankAccountTest, GetBalance_AfterDeposit) {
    BankAccount account(100.0, AccountType::CHECKING);
    account.deposit(25.0);
    EXPECT_DOUBLE_EQ(125.0, account.getBalance());
}

TEST_F(BankAccountTest, GetBalance_AfterWithdraw) {
    BankAccount account(100.0, AccountType::SAVINGS);
    account.withdraw(40.0);
    EXPECT_DOUBLE_EQ(60.0, account.getBalance());
}

TEST_F(BankAccountTest, GetBalance_AfterTransfer) {
    BankAccount source(200.0, AccountType::SAVINGS);
    BankAccount destination(100.0, AccountType::CHECKING);
    source.transfer(destination, 50.0);
    EXPECT_DOUBLE_EQ(150.0, source.getBalance());
    EXPECT_DOUBLE_EQ(150.0, destination.getBalance());
}

TEST_F(BankAccountTest, GetBalance_ConstMethod) {
    const BankAccount account(100.0, AccountType::SAVINGS);
    EXPECT_DOUBLE_EQ(100.0, account.getBalance());
}

// ============================================================================
// Transaction History Tests
// ============================================================================

TEST_F(BankAccountTest, DisplayHistory_EmptyHistory) {
    BankAccount account(100.0, AccountType::SAVINGS);
    // Should not crash when displaying empty history
    EXPECT_NO_THROW(account.displayHistory());
}

TEST_F(BankAccountTest, DisplayHistory_AfterDeposit) {
    BankAccount account(100.0, AccountType::SAVINGS);
    account.deposit(50.0);
    // Should not crash when displaying history
    EXPECT_NO_THROW(account.displayHistory());
}

TEST_F(BankAccountTest, DisplayHistory_AfterWithdraw) {
    BankAccount account(100.0, AccountType::CHECKING);
    account.withdraw(30.0);
    // Should not crash when displaying history
    EXPECT_NO_THROW(account.displayHistory());
}

TEST_F(BankAccountTest, DisplayHistory_AfterTransfer) {
    BankAccount source(200.0, AccountType::SAVINGS);
    BankAccount destination(100.0, AccountType::CHECKING);
    source.transfer(destination, 50.0);
    // Should not crash when displaying history
    EXPECT_NO_THROW(source.displayHistory());
    EXPECT_NO_THROW(destination.displayHistory());
}

TEST_F(BankAccountTest, DisplayHistory_MultipleTransactions) {
    BankAccount account(100.0, AccountType::SAVINGS);
    account.deposit(50.0);
    account.withdraw(30.0);
    account.deposit(25.0);
    account.withdraw(10.0);
    // Should not crash when displaying history
    EXPECT_NO_THROW(account.displayHistory());
}

// ============================================================================
// Integration Tests - Complex Scenarios
// ============================================================================

TEST_F(BankAccountTest, Integration_MixedOperations) {
    BankAccount account1(500.0, AccountType::SAVINGS);
    BankAccount account2(200.0, AccountType::CHECKING);
    
    account1.deposit(100.0);
    account1.withdraw(50.0);
    account1.transfer(account2, 75.0);
    account2.deposit(25.0);
    account2.withdraw(30.0);
    
    EXPECT_DOUBLE_EQ(475.0, account1.getBalance());
    // account2: 200.0 (start) + 75.0 (transfer) + 25.0 (deposit) - 30.0 (withdraw) = 270.0
    EXPECT_DOUBLE_EQ(270.0, account2.getBalance());
}

TEST_F(BankAccountTest, Integration_SequenceOfOperations) {
    BankAccount account(0.0, AccountType::SAVINGS);
    
    // Start with zero, deposit, withdraw, deposit again
    account.deposit(100.0);
    account.withdraw(30.0);
    account.deposit(50.0);
    account.withdraw(20.0);
    
    EXPECT_DOUBLE_EQ(100.0, account.getBalance());
}

TEST_F(BankAccountTest, Integration_FailedOperationsDoNotChangeBalance) {
    BankAccount account(100.0, AccountType::CHECKING);
    double initialBalance = account.getBalance();
    
    // Attempt invalid operations
    account.deposit(-10.0);
    account.withdraw(200.0);
    account.withdraw(-5.0);
    
    EXPECT_DOUBLE_EQ(initialBalance, account.getBalance());
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(BankAccountTest, EdgeCase_VerySmallAmounts) {
    BankAccount account(0.01, AccountType::SAVINGS);
    bool result = account.withdraw(0.01);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(0.0, account.getBalance());
}

TEST_F(BankAccountTest, EdgeCase_VeryLargeAmounts) {
    BankAccount account(1000000.0, AccountType::CHECKING);
    bool result = account.deposit(999999.99);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(1999999.99, account.getBalance());
}

TEST_F(BankAccountTest, EdgeCase_PrecisionTest) {
    BankAccount account(100.0, AccountType::SAVINGS);
    account.deposit(0.1);
    account.deposit(0.2);
    account.deposit(0.3);
    // Should handle floating point precision correctly
    EXPECT_NEAR(100.6, account.getBalance(), 0.0001);
}

// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
