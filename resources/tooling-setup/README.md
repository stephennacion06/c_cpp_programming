# Tooling Setup

Complete setup guides for C/C++ development environment.

## 🖥️ Platform-Specific Setup

### Windows

#### Option 1: Visual Studio (Recommended)
1. Download [Visual Studio Community](https://visualstudio.microsoft.com/)
2. During installation, select "Desktop development with C++"
3. Includes: MSVC compiler, Windows SDK, debugger

#### Option 2: MinGW-w64 + VS Code
1. Install [MinGW-w64](https://www.mingw-w64.org/)
2. Add MinGW bin directory to PATH
3. Install [VS Code](https://code.visualstudio.com/)
4. Install C/C++ extension

#### Option 3: WSL (Windows Subsystem for Linux)
1. Enable WSL: `wsl --install`
2. Install Ubuntu from Microsoft Store
3. Follow Linux setup instructions

### Linux (Ubuntu/Debian)

```bash
# Install build essentials
sudo apt update
sudo apt install build-essential

# Install GCC/G++
sudo apt install gcc g++

# Install CMake
sudo apt install cmake

# Install debugging tools
sudo apt install gdb valgrind

# Install development libraries (optional)
sudo apt install libncurses5-dev libreadline-dev
```

### macOS

#### Using Xcode Command Line Tools
```bash
# Install Xcode CLT
xcode-select --install

# Verify installation
gcc --version
clang --version
```

#### Using Homebrew
```bash
# Install Homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install tools
brew install gcc
brew install cmake
brew install lldb
```

## 🔧 Essential Tools

### 1. Compilers

#### GCC (GNU Compiler Collection)
```bash
# Check version
gcc --version
g++ --version

# Compile C program
gcc program.c -o program

# Compile with warnings and debug info
gcc -Wall -Wextra -g program.c -o program

# Compile C++ with C++17
g++ -std=c++17 program.cpp -o program
```

#### Clang
```bash
# Check version
clang --version
clang++ --version

# Compile C program
clang program.c -o program

# Compile C++ with modern features
clang++ -std=c++20 program.cpp -o program
```

#### MSVC (Microsoft Visual C++)
```cmd
# From Visual Studio Developer Command Prompt
cl /EHsc program.cpp
```

### 2. Build Systems

#### CMake
```bash
# Install CMake
# Linux
sudo apt install cmake

# macOS
brew install cmake

# Windows
Download from cmake.org

# Basic usage
mkdir build
cd build
cmake ..
cmake --build .
```

#### Make
```bash
# Install Make
# Linux
sudo apt install make

# macOS (included with Xcode CLT)
xcode-select --install

# Windows (via MinGW)
# Included with MinGW installation
```

### 3. IDEs and Editors

#### Visual Studio Code
1. Install from [code.visualstudio.com](https://code.visualstudio.com/)
2. Install extensions:
   - C/C++ (Microsoft)
   - C/C++ Extension Pack
   - CMake Tools
   - Code Runner

**Recommended VS Code Settings**:
```json
{
    "C_Cpp.default.cStandard": "c11",
    "C_Cpp.default.cppStandard": "c++17",
    "C_Cpp.default.intelliSenseMode": "gcc-x64",
    "cmake.configureOnOpen": true
}
```

#### Visual Studio (Windows)
- Full-featured IDE
- Excellent debugger
- IntelliSense code completion

#### CLion (JetBrains)
- Cross-platform IDE
- Powerful refactoring tools
- Integrated CMake support

#### Code::Blocks
- Free, cross-platform IDE
- Good for beginners

### 4. Debugging Tools

#### GDB
```bash
# Linux
sudo apt install gdb

# macOS (use LLDB instead)
# GDB is deprecated on macOS

# Windows (MinGW)
# Included with MinGW installation
```

#### Valgrind
```bash
# Linux
sudo apt install valgrind

# macOS
brew install valgrind

# Windows
# Use WSL or alternative tools
```

#### LLDB
```bash
# macOS (included with Xcode)
lldb --version

# Linux
sudo apt install lldb
```

## 📦 Package Managers

### vcpkg (Cross-platform)
```bash
# Clone vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg

# Bootstrap
./bootstrap-vcpkg.sh  # Linux/macOS
.\bootstrap-vcpkg.bat  # Windows

# Install libraries
./vcpkg install boost
./vcpkg install curl
```

### Conan
```bash
# Install via pip
pip install conan

# Create profile
conan profile detect

# Install dependencies
conan install . --build=missing
```

## 🎨 Code Quality Tools

### Static Analysis
```bash
# cppcheck
sudo apt install cppcheck  # Linux
brew install cppcheck      # macOS

# Usage
cppcheck --enable=all program.c
```

### Code Formatting
```bash
# clang-format
sudo apt install clang-format  # Linux
brew install clang-format      # macOS

# Format code
clang-format -i program.cpp

# Create .clang-format config
clang-format -style=llvm -dump-config > .clang-format
```

## ✅ Verification

### Test Your Setup

Create `test.c`:
```c
#include <stdio.h>

int main() {
    printf("C/C++ environment is ready!\n");
    return 0;
}
```

Compile and run:
```bash
# Using GCC
gcc test.c -o test
./test

# Using Clang
clang test.c -o test
./test
```

Create `test.cpp`:
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3};
    for (const auto& num : vec) {
        std::cout << num << " ";
    }
    std::cout << "\nC++ environment is ready!\n";
    return 0;
}
```

Compile and run:
```bash
g++ -std=c++17 test.cpp -o test
./test
```

## 🔗 Additional Resources

- [GCC Documentation](https://gcc.gnu.org/onlinedocs/)
- [Clang Documentation](https://clang.llvm.org/docs/)
- [CMake Documentation](https://cmake.org/documentation/)
- [VS Code C/C++ Guide](https://code.visualstudio.com/docs/languages/cpp)

## 📝 Contributing

Improve setup guides! See [CONTRIBUTING.md](../../CONTRIBUTING.md).
