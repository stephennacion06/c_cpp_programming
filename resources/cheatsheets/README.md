# C/C++ Cheatsheets

Quick reference guides for common C/C++ syntax and patterns.

## 📄 Available Cheatsheets

### C Programming
- [C Basics Cheatsheet](c-basics.md) - Variables, operators, control flow
- [C Pointers Cheatsheet](c-pointers.md) - Pointer syntax and usage
- [C Standard Library](c-stdlib.md) - Common functions reference
- [C Preprocessor](c-preprocessor.md) - Macros and directives

### C++ Programming
- [C++ Basics Cheatsheet](cpp-basics.md) - Modern C++ essentials
- [C++ STL Containers](cpp-stl-containers.md) - Vector, map, set, etc.
- [C++ STL Algorithms](cpp-stl-algorithms.md) - sort, find, transform
- [C++ Smart Pointers](cpp-smart-pointers.md) - unique_ptr, shared_ptr
- [C++ Move Semantics](cpp-move-semantics.md) - Move and perfect forwarding
- [C++ Lambda Expressions](cpp-lambdas.md) - Lambda syntax guide

### Data Structures
- [Array Operations](ds-arrays.md) - Common array patterns
- [Linked Lists](ds-linked-lists.md) - List operations
- [Trees](ds-trees.md) - Tree traversals and operations
- [Graphs](ds-graphs.md) - Graph representations and algorithms

### Algorithms
- [Sorting Algorithms](algo-sorting.md) - Comparison of sorting methods
- [Searching Algorithms](algo-searching.md) - Search techniques
- [Time Complexity](algo-complexity.md) - Big O reference

### Memory Management
- [Memory Allocation](mem-allocation.md) - malloc, new, smart pointers
- [Memory Debugging](mem-debugging.md) - Valgrind, sanitizers

## 📥 Download Printable PDFs

PDF versions of all cheatsheets will be available in the `pdfs/` directory.

## 🔗 Quick Links

### C Syntax Quick Reference

```c
// Variable Declaration
int x = 10;
float pi = 3.14f;
char c = 'A';

// Arrays
int arr[5] = {1, 2, 3, 4, 5};
char str[] = "Hello";

// Pointers
int *ptr = &x;
*ptr = 20;  // Dereference

// Functions
int add(int a, int b) {
    return a + b;
}

// Structures
struct Point {
    int x;
    int y;
};

// Dynamic Memory
int *p = (int*)malloc(sizeof(int) * 10);
free(p);
```

### C++ Syntax Quick Reference

```cpp
// Auto type inference
auto x = 10;
auto str = "Hello"s;  // std::string

// Range-based loops
for (const auto& item : container) {
    // ...
}

// Lambda expressions
auto add = [](int a, int b) { return a + b; };

// Smart pointers
auto ptr = std::make_unique<int>(42);
auto shared = std::make_shared<int>(100);

// Move semantics
std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2 = std::move(v1);  // v1 is now empty
```

## 📝 Contributing

Help improve these cheatsheets! See [CONTRIBUTING.md](../../CONTRIBUTING.md).
