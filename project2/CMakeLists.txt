cmake_minimum_required(VERSION 3.10)
project(BankAccountProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Google Test
find_package(GTest REQUIRED)
include(GoogleTest)

# Add executable for tests
add_executable(BankAccount_test BankAccount_test.cpp BankAccount.cpp)
target_link_libraries(BankAccount_test GTest::gtest GTest::gtest_main GTest::gmock)

# Register tests with CTest
gtest_discover_tests(BankAccount_test)

# Optional: Add main executable if needed
add_executable(BankAccount_main main.cpp BankAccount.cpp)
