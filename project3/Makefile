# Makefile for Employee Management System (Project 3)
# Builds demo and optional Google Test-based tests

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

HOMEBREW_PREFIX := $(shell brew --prefix 2>/dev/null || echo "")

# Detect Google Test
GTEST_CFLAGS := $(shell pkg-config --cflags gtest 2>/dev/null)
GTEST_LIBS := $(shell pkg-config --libs gtest 2>/dev/null)

ifeq ($(GTEST_CFLAGS),)
  ifneq ($(HOMEBREW_PREFIX),)
    ifeq ($(shell test -d $(HOMEBREW_PREFIX)/include/gtest && echo yes),yes)
      GTEST_CFLAGS = -I$(HOMEBREW_PREFIX)/include
      GTEST_LIBS = -L$(HOMEBREW_PREFIX)/lib -lgtest -pthread
    endif
  endif
  ifeq ($(GTEST_CFLAGS),)
    ifeq ($(shell test -f /opt/homebrew/include/gtest/gtest.h 2>/dev/null && echo yes),yes)
      GTEST_CFLAGS = -I/opt/homebrew/include
      GTEST_LIBS = -L/opt/homebrew/lib -lgtest -pthread
    else ifeq ($(shell test -f /usr/local/include/gtest/gtest.h 2>/dev/null && echo yes),yes)
      GTEST_CFLAGS = -I/usr/local/include
      GTEST_LIBS = -L/usr/local/lib -lgtest -pthread
    endif
  endif
endif

GTEST_AVAILABLE := $(shell \
  if test -f /opt/homebrew/include/gtest/gtest.h 2>/dev/null; then echo yes; \
  elif test -f /usr/local/include/gtest/gtest.h 2>/dev/null; then echo yes; \
  elif test -n "$(HOMEBREW_PREFIX)" && test -f "$(HOMEBREW_PREFIX)/include/gtest/gtest.h" 2>/dev/null; then echo yes; \
  else echo no; fi)

.PHONY: all test demo clean help

# Default: build demo only
all: employee_demo

# Build demo and tests
all-with-tests: employee_demo Employee_test

employee_demo: main.cpp Employee.cpp Employee.h
	$(CXX) $(CXXFLAGS) -o employee_demo main.cpp Employee.cpp

Employee_test: Employee_test.cpp Employee.cpp Employee.h
	@if [ "$(GTEST_AVAILABLE)" != "yes" ]; then \
		echo "ERROR: Google Test not found."; \
		echo "  Install: brew install googletest"; \
		echo "  Then: make Employee_test"; exit 1; \
	fi
	$(CXX) $(CXXFLAGS) -o Employee_test Employee_test.cpp Employee.cpp $(GTEST_CFLAGS) $(GTEST_LIBS)

test: Employee_test
	./Employee_test

demo: employee_demo
	./employee_demo

clean:
	rm -f employee_demo Employee_test *.o

help:
	@echo "Targets: all (demo), all-with-tests, test, demo, clean"
	@echo "Tests need Google Test: brew install googletest"
