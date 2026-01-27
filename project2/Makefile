# Makefile for BankAccount project
# Alternative to CMake for simpler builds

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Get Homebrew prefix if available (used for detection)
HOMEBREW_PREFIX := $(shell brew --prefix 2>/dev/null || echo "")

# Try to detect Google Test location automatically
# Check common Homebrew locations and pkg-config
GTEST_CFLAGS := $(shell pkg-config --cflags gtest 2>/dev/null)
GTEST_LIBS := $(shell pkg-config --libs gtest 2>/dev/null)

# If pkg-config didn't work, try common paths
ifeq ($(GTEST_CFLAGS),)
  # Try Homebrew locations first (Apple Silicon or Intel)
  ifneq ($(HOMEBREW_PREFIX),)
    ifeq ($(shell test -d $(HOMEBREW_PREFIX)/include/gtest && echo yes),yes)
      GTEST_CFLAGS = -I$(HOMEBREW_PREFIX)/include
      GTEST_LIBS = -L$(HOMEBREW_PREFIX)/lib -lgtest -lgtest_main -pthread
    endif
  endif
  
  # Fallback to common locations
  ifeq ($(GTEST_CFLAGS),)
    ifeq ($(shell test -d /opt/homebrew/include/gtest && echo yes),yes)
      GTEST_CFLAGS = -I/opt/homebrew/include
      GTEST_LIBS = -L/opt/homebrew/lib -lgtest -lgtest_main -pthread
    else ifeq ($(shell test -d /usr/local/include/gtest && echo yes),yes)
      GTEST_CFLAGS = -I/usr/local/include
      GTEST_LIBS = -L/usr/local/lib -lgtest -lgtest_main -pthread
    else
      # Fallback - user can override with: make GTEST_CFLAGS="-I/path/to/include" GTEST_LIBS="-L/path/to/lib -lgtest -lgtest_main -pthread"
      GTEST_CFLAGS = -I/opt/homebrew/include
      GTEST_LIBS = -L/opt/homebrew/lib -lgtest -lgtest_main -pthread
    endif
  endif
endif

# Default target - build demo only (tests require Google Test)
all: BankAccount_main

# Build everything including tests
all-with-tests: BankAccount_test BankAccount_main

# Check if Google Test is available
# Check common locations - ensure only one "yes" or "no" is output
GTEST_AVAILABLE := $(shell \
  if test -f /opt/homebrew/include/gtest/gtest.h 2>/dev/null; then \
    echo yes; \
  elif test -f /usr/local/include/gtest/gtest.h 2>/dev/null; then \
    echo yes; \
  elif test -n "$(HOMEBREW_PREFIX)" && test -f "$(HOMEBREW_PREFIX)/include/gtest/gtest.h" 2>/dev/null; then \
    echo yes; \
  else \
    echo no; \
  fi)

# Test executable
BankAccount_test: BankAccount_test.cpp BankAccount.cpp BankAccount.h
	@if [ "$(GTEST_AVAILABLE)" != "yes" ]; then \
		echo "ERROR: Google Test is not installed or not found."; \
		echo ""; \
		echo "To install Google Test:"; \
		echo "  brew install googletest"; \
		echo ""; \
		echo "After installation, run: make test"; \
		echo ""; \
		echo "Or build without tests: make demo"; \
		exit 1; \
	fi
	$(CXX) $(CXXFLAGS) -o BankAccount_test BankAccount_test.cpp BankAccount.cpp \
		$(GTEST_CFLAGS) $(GTEST_LIBS)

# Main executable
BankAccount_main: main.cpp BankAccount.cpp BankAccount.h
	$(CXX) $(CXXFLAGS) -o BankAccount_main main.cpp BankAccount.cpp

# Run tests
test: BankAccount_test
	./BankAccount_test

# Run demo
demo: BankAccount_main
	./BankAccount_main

# Clean build artifacts
clean:
	rm -f BankAccount_test BankAccount_main *.o

# Help target
help:
	@echo "Available targets:"
	@echo "  all           - Build the demo executable (default, no tests required)"
	@echo "  all-with-tests - Build both test and demo executables (requires Google Test)"
	@echo "  test          - Build and run tests (requires Google Test)"
	@echo "  demo          - Build and run the demo program"
	@echo "  clean         - Remove build artifacts"
	@echo ""
	@echo "Note: Tests require Google Test to be installed."
	@echo "  Install with: brew install googletest"
	@echo "  Then use: make all-with-tests"
	@echo "  Or override paths: make GTEST_CFLAGS='-I/path' GTEST_LIBS='-L/path -lgtest -lgtest_main -pthread'"

.PHONY: all all-with-tests test demo clean help
