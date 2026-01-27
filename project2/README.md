# BankAccount Project

A C++ implementation of a bank account management system with transaction history tracking.

## Project Structure

```
project2/
├── BankAccount.h          # Header file with class definition
├── BankAccount.cpp        # Implementation file
├── BankAccount_test.cpp   # Comprehensive unit tests
├── main.cpp               # Example usage/demo program
├── CMakeLists.txt         # CMake build configuration
├── Makefile               # Alternative Makefile build
├── README.md              # This file
└── README_TESTS.md        # Detailed test documentation
```

## Features

The `BankAccount` class provides:

- **Account Management**: Create accounts with initial deposits (Savings or Checking)
- **Deposits**: Add funds to an account (only positive amounts)
- **Withdrawals**: Remove funds from an account (with balance validation)
- **Transfers**: Transfer funds between accounts (with validation)
- **Transaction History**: Track all transactions with automatic logging
- **Balance Queries**: Get current account balance

## Building the Project

### Using CMake (Recommended)

```bash
mkdir build
cd build
cmake ..
make
```

This will create:
- `BankAccount_test` - Test executable
- `BankAccount_main` - Demo program

### Using Makefile

```bash
make              # Build both test and demo
make test         # Build and run tests
make demo         # Build and run demo
make clean        # Clean build artifacts
```

**Note**: Make sure Google Test is installed. On macOS:
```bash
brew install googletest
```

## Running

### Run Tests
```bash
./build/BankAccount_test
# or
cd build && ctest
```

### Run Demo
```bash
./build/BankAccount_main
```

## Implementation Details

### Constructor
- Accepts `initialDeposit` (must be non-negative) and `AccountType`
- If negative initial deposit is provided, balance is set to 0.0
- Initializes empty transaction history

### Deposit
- Returns `true` only if `amount > 0`
- Updates balance and records transaction in history
- Format: `[Deposit]: $XX.XX`

### Withdraw
- Returns `true` only if `amount > 0` AND `balance >= amount`
- Updates balance and records transaction in history
- Format: `[Withdraw]: $XX.XX`

### Transfer
- Returns `true` only if `amount > 0` AND source `balance >= amount`
- Atomically updates both accounts' balances
- Records transaction in both accounts' history
- Format: `[Transfer]: $XX.XX`

### Get Balance
- Returns current balance as `double`
- Const method (doesn't modify state)

### Display History
- Prints all transactions to console, one per line
- Format: `[Deposit/Withdraw/Transfer]: $XX.XX`

## Example Usage

```cpp
#include "BankAccount.h"

// Create accounts
BankAccount savings(1000.0, AccountType::SAVINGS);
BankAccount checking(500.0, AccountType::CHECKING);

// Perform transactions
savings.deposit(200.0);
checking.withdraw(100.0);
savings.transfer(checking, 150.0);

// Check balances
std::cout << "Savings: $" << savings.getBalance() << std::endl;
std::cout << "Checking: $" << checking.getBalance() << std::endl;

// View history
savings.displayHistory();
```

## Testing

The project includes 50+ comprehensive unit tests covering:
- ✅ Constructor scenarios
- ✅ Valid and invalid deposits
- ✅ Valid and invalid withdrawals
- ✅ Valid and invalid transfers
- ✅ Balance queries
- ✅ Transaction history
- ✅ Edge cases (precision, large/small amounts)
- ✅ Integration scenarios

See `README_TESTS.md` for detailed test documentation.

## Requirements

- C++17 or higher
- CMake 3.10+ (for CMake build)
- Google Test library (for running tests)
- A C++ compiler with C++17 support (g++, clang++, etc.)

## Notes

- All monetary amounts are stored as `double` (consider using a decimal library for production)
- Transaction history is stored in memory (consider persistence for production)
- The implementation is designed to be thread-safe-ready (conceptual, not actually thread-safe)
