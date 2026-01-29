cmake_minimum_required(VERSION 3.10)
project(EmployeeManagementProject)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Google Test
find_package(GTest QUIET)
if(GTest_FOUND)
  include(GoogleTest)
  # Test executable (provides its own main)
  add_executable(Employee_test Employee_test.cpp Employee.cpp)
  target_include_directories(Employee_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(Employee_test GTest::gtest)  # test file provides main
  gtest_discover_tests(Employee_test)
else()
  message(STATUS "Google Test not found; run with -DGTest_DIR=... or install (e.g. brew install googletest). Skipping test target.")
endif()

# Demo executable
add_executable(employee_demo main.cpp Employee.cpp)
target_include_directories(employee_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
