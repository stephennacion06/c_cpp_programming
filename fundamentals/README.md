# Fundamentals

Core C/C++ programming concepts organized by difficulty level.

## 📚 Topics Covered

### Beginner Level
- [x] **Hello World**: First program, compilation basics - [Documentation](beginner/hello-world.md) | [Code](beginner/hello_world.c)
- [x] **Variables & Data Types**: int, float, char, sizeof - [Documentation](beginner/variables-and-data-types.md) | [Code](beginner/variables_and_data_types.c)
- [x] **Operators**: Arithmetic, relational, logical, bitwise - [Documentation](beginner/operators.md) | [Code](beginner/operators.c)
- [x] **Input/Output**: printf/scanf (C), cin/cout (C++) - [Documentation](beginner/input-output.md) | [Code](beginner/input_output.c)
- [x] **Control Flow**: if-else, switch statements - [Documentation](beginner/control-flow.md) | [Code](beginner/control_flow.c)
- [x] **Loops**: for, while, do-while - [Documentation](beginner/loops.md) | [Code](beginner/loops.c)
- [x] **Functions**: Declaration, definition, parameters, return values - [Documentation](beginner/functions.md) | [Code](beginner/functions.c)
- [x] **Arrays**: Declaration, initialization, accessing elements - [Documentation](beginner/arrays.md) | [Code](beginner/arrays.c)
- [x] **Strings**: Character arrays (C), std::string (C++) - [Documentation](beginner/strings.md) | [Code](beginner/strings.c)

### Intermediate Level
- [ ] **Pointers Basics**: Address-of, dereference operators
- [ ] **Function Pointers**: Callbacks, function tables
- [ ] **Structures**: struct definition, member access
- [ ] **Enumerations**: enum types
- [ ] **Type Qualifiers**: const, volatile, static
- [ ] **Preprocessor**: #define, #include, conditional compilation
- [ ] **Header Files**: Separation of interface and implementation
- [ ] **Multi-file Programs**: Compilation and linking

### Advanced Level
- [ ] **Storage Classes**: auto, register, static, extern
- [ ] **Variable Arguments**: va_list, va_start, va_end
- [ ] **Inline Functions**: Performance optimization
- [ ] **Bit Manipulation**: Bitwise operations, bit fields
- [ ] **Unions**: Memory sharing between types
- [ ] **Type Casting**: Implicit and explicit conversion
- [ ] **Command Line Arguments**: argc, argv
- [ ] **Error Handling**: errno, perror, error codes

## 🚀 Getting Started

Each topic includes:
- **Explanation**: Detailed concept explanation
- **Code Examples**: Commented, compilable code
- **Exercises**: Practice problems with solutions
- **Best Practices**: Common pitfalls and recommendations

## 📖 Learning Path

1. Start with **Beginner** level topics in order
2. Complete exercises for each topic before moving on
3. Progress to **Intermediate** topics once comfortable
4. Explore **Advanced** topics for deeper understanding

## 🔨 Building Examples

```bash
# From repository root
mkdir build && cd build
cmake ..
cmake --build .

# Run a specific example
./bin/fundamentals/hello_world
```

## 📝 Contributing

See [CONTRIBUTING.md](../CONTRIBUTING.md) for guidelines on adding new examples or improving existing content.
