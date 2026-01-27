# Quick Setup Guide

## Building Without Tests (No Google Test Required)

You can build and run the demo program immediately:

```bash
make              # Builds demo only
make demo         # Builds and runs demo
```

## Installing Google Test (for running tests)

### macOS (using Homebrew)

```bash
brew install googletest
```

After installation, build and run tests:

```bash
make all-with-tests    # Build everything
make test              # Build and run tests
```

### Manual Installation

If you need to specify custom paths:

```bash
make GTEST_CFLAGS="-I/path/to/gtest/include" \
     GTEST_LIBS="-L/path/to/gtest/lib -lgtest -lgtest_main -pthread" \
     all-with-tests
```

## Troubleshooting

### Error: "no such file or directory: '/include'"

This means Google Test is not installed or not found. Solutions:

1. **Install Google Test:**
   ```bash
   brew install googletest
   ```

2. **Build without tests:**
   ```bash
   make BankAccount_main    # Just the demo
   ```

3. **Use CMake instead:**
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

### Error: "ld: library not found for -lgtest"

Google Test is not installed or the library path is incorrect. Install it with:
```bash
brew install googletest
```

Then try building again.

## Quick Test

After installing Google Test, verify it works:

```bash
make test
```

You should see all tests passing!
