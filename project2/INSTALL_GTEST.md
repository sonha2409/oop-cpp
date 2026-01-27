# Installing Google Test

Google Test is required to build and run the test suite. Here's how to install it:

## macOS (using Homebrew)

Simply run:
```bash
brew install googletest
```

After installation, verify it's installed:
```bash
brew list googletest
```

Then build and run tests:
```bash
make test
```

## Verify Installation

After installing, you can verify Google Test is found:
```bash
ls /opt/homebrew/include/gtest/gtest.h    # Apple Silicon Mac
# or
ls /usr/local/include/gtest/gtest.h       # Intel Mac
```

## Alternative: Use CMake

CMake can automatically download and build Google Test if it's not found. This is often easier:

```bash
mkdir build
cd build
cmake ..
make
```

CMake will handle Google Test installation automatically.

## Troubleshooting

### "brew: command not found"
Install Homebrew first:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### Still getting "file not found" errors
Try specifying the path manually:
```bash
make GTEST_CFLAGS="-I/opt/homebrew/include" \
     GTEST_LIBS="-L/opt/homebrew/lib -lgtest -lgtest_main -pthread" \
     test
```

### Build without tests
You can always build and run the demo without tests:
```bash
make demo
```
