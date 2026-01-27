# BankAccount Test Suite

This directory contains comprehensive unit tests for the `BankAccount` class implementation.

## Test Coverage

The test suite (`BankAccount_test.cpp`) covers:

### Constructor Tests
- Valid initial deposits (Savings and Checking accounts)
- Zero initial deposit
- Large and small initial deposits

### Deposit Tests
- Successful deposits with positive amounts
- Multiple deposits
- Invalid deposits (zero, negative amounts)
- Edge cases (small/large amounts, zero balance accounts)

### Withdraw Tests
- Successful withdrawals
- Withdrawing exact balance
- Insufficient funds scenarios
- Invalid withdrawals (zero, negative amounts)
- Multiple withdrawals
- Edge cases

### Transfer Tests
- Successful transfers between accounts
- Transferring exact balance
- Insufficient funds scenarios
- Invalid transfers (zero, negative amounts)
- Multiple transfers
- Transfers between different account types
- Edge cases

### GetBalance Tests
- Balance after construction
- Balance after various operations
- Const correctness

### Transaction History Tests
- Displaying empty history
- Displaying history after various operations
- Multiple transactions

### Integration Tests
- Complex scenarios with mixed operations
- Sequences of operations
- Failed operations not affecting balance

### Edge Cases
- Very small amounts
- Very large amounts
- Floating point precision

## Building and Running Tests

### Prerequisites
- CMake (version 3.10 or higher)
- Google Test (GTest) library

### Installing Google Test

**On macOS (using Homebrew):**
```bash
brew install googletest
```

**On Ubuntu/Debian:**
```bash
sudo apt-get install libgtest-dev
```

**On Windows (using vcpkg):**
```bash
vcpkg install gtest
```

### Building the Tests

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Run CMake:
```bash
cmake ..
```

3. Build the project:
```bash
make
# or on Windows: cmake --build .
```

### Running the Tests

```bash
./BankAccount_test
# or
ctest
```

### Running Specific Tests

```bash
./BankAccount_test --gtest_filter=Deposit_PositiveAmount_Success
```

## Test Structure

Each test follows the naming convention:
- `TestGroup_TestName_ExpectedBehavior`

For example:
- `Deposit_PositiveAmount_Success` - Tests that a positive deposit succeeds
- `Withdraw_InsufficientFunds_ShouldFail` - Tests that withdrawing more than balance fails

## Notes for Implementation

When implementing `BankAccount.cpp`, ensure:

1. **Constructor**: Handles non-negative initial deposits correctly
2. **deposit()**: Returns `true` only for positive amounts, records in history
3. **withdraw()**: Returns `false` for negative amounts, zero amounts, or insufficient funds
4. **transfer()**: Atomically transfers funds (both accounts update or neither)
5. **getBalance()**: Returns current balance (const method)
6. **displayHistory()**: Prints all transactions in the format: `[Deposit/Withdraw/Transfer]: $Amount`

## Expected Test Results

All tests should pass when the implementation is correct. The test suite includes:
- **Positive tests**: Verify correct behavior
- **Negative tests**: Verify error handling
- **Edge cases**: Verify boundary conditions
- **Integration tests**: Verify complex scenarios

Total test count: 50+ comprehensive test cases
