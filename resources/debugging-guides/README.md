# Debugging Guides

Comprehensive guides for debugging C/C++ programs.

## 🐛 Debugging Tools

### 1. GDB (GNU Debugger)
The most powerful debugger for C/C++ on Linux/macOS.

#### Basic Commands
```bash
# Compile with debug symbols
gcc -g program.c -o program

# Start GDB
gdb ./program

# Common GDB commands
(gdb) break main          # Set breakpoint at main
(gdb) run                 # Run the program
(gdb) next                # Execute next line (step over)
(gdb) step                # Execute next line (step into)
(gdb) continue            # Continue execution
(gdb) print variable      # Print variable value
(gdb) backtrace           # Show call stack
(gdb) quit                # Exit GDB
```

#### Advanced GDB
- [GDB Complete Guide](gdb-guide.md)
- [GDB Cheatsheet](gdb-cheatsheet.md)
- [GDB with Core Dumps](gdb-coredumps.md)

### 2. LLDB
The debugger for Clang/LLVM toolchain.

```bash
# Start LLDB
lldb ./program

# Common commands (similar to GDB)
(lldb) breakpoint set --name main
(lldb) run
(lldb) next
(lldb) step
```

### 3. Visual Studio Debugger
Integrated debugger for Windows development.

- Set breakpoints with F9
- Step Over (F10)
- Step Into (F11)
- Continue (F5)
- Watch windows for variables
- Immediate window for expressions

## 🔍 Common Issues and Solutions

### Segmentation Fault
**Symptoms**: Program crashes with "Segmentation fault"

**Common Causes**:
1. Dereferencing NULL pointer
2. Accessing out-of-bounds array element
3. Stack overflow (infinite recursion)
4. Writing to freed memory

**Debugging**:
```bash
# Use GDB to find the crash location
gdb ./program
(gdb) run
# Program crashes
(gdb) backtrace  # Shows where it crashed
```

### Memory Leaks
**Symptoms**: Program uses increasing memory

**Detection**:
```bash
# Valgrind (Linux/macOS)
valgrind --leak-check=full ./program

# AddressSanitizer (GCC/Clang)
gcc -fsanitize=address -g program.c -o program
./program
```

### Undefined Behavior
**Symptoms**: Program works sometimes, crashes other times

**Common Causes**:
1. Uninitialized variables
2. Integer overflow
3. Use after free
4. Race conditions

**Prevention**:
```bash
# Compile with warnings
gcc -Wall -Wextra -Wpedantic program.c

# Use sanitizers
gcc -fsanitize=undefined program.c
```

## 🛠️ Memory Debugging

### Valgrind
```bash
# Memory leak detection
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         ./program

# Memory error detection
valgrind --tool=memcheck ./program
```

### AddressSanitizer
```bash
# Compile with AddressSanitizer
gcc -fsanitize=address -O1 -fno-omit-frame-pointer -g program.c

# Run
./a.out
```

### MemorySanitizer
```bash
# Detect uninitialized memory reads
clang -fsanitize=memory -g program.c
```

## 📊 Profiling

### gprof (Performance Profiling)
```bash
# Compile with profiling
gcc -pg program.c -o program

# Run program (generates gmon.out)
./program

# View profile
gprof program gmon.out > analysis.txt
```

### Valgrind Callgrind
```bash
# Profile program
valgrind --tool=callgrind ./program

# Visualize with kcachegrind
kcachegrind callgrind.out.*
```

## 💡 Debugging Strategies

### 1. Print Debugging
```c
// Strategic printf statements
printf("DEBUG: x = %d, y = %d\n", x, y);
printf("DEBUG: Reached checkpoint A\n");
```

### 2. Assertions
```c
#include <assert.h>

assert(ptr != NULL);
assert(size > 0);
assert(index < array_size);
```

### 3. Logging
```c
// Use different log levels
#define LOG_ERROR(msg) fprintf(stderr, "ERROR: %s\n", msg)
#define LOG_DEBUG(msg) fprintf(stdout, "DEBUG: %s\n", msg)
```

### 4. Rubber Duck Debugging
Explain your code line-by-line to someone (or something) else.

### 5. Binary Search Debugging
Comment out half the code to isolate the problem.

## 📝 Debugging Checklist

- [ ] Compiled with `-g` flag for debug symbols
- [ ] Enabled all compiler warnings (`-Wall -Wextra`)
- [ ] Checked for NULL pointer dereferences
- [ ] Verified array bounds
- [ ] Checked return values of functions
- [ ] Looked for uninitialized variables
- [ ] Verified memory allocation/deallocation
- [ ] Tested edge cases
- [ ] Used appropriate debugging tool
- [ ] Checked for race conditions (multithreaded code)

## 🔗 Additional Resources

- [GDB Tutorial](https://www.gnu.org/software/gdb/documentation/)
- [Valgrind Quick Start](https://valgrind.org/docs/manual/quick-start.html)
- [AddressSanitizer Guide](https://github.com/google/sanitizers/wiki/AddressSanitizer)

## 📝 Contributing

Share your debugging tips! See [CONTRIBUTING.md](../../CONTRIBUTING.md).
