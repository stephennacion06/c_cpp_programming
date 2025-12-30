# Getting Started

Welcome to the C/C++ Knowledge Repository! This guide will help you get started.

## 🚀 Quick Start

### 1. Test the Setup

Let's verify everything works by building and running the "Hello World" example:

```bash
# Navigate to the repository
cd c_cpp_programming

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build .

# Run the hello world example
./bin/hello_world     # Linux/macOS
.\bin\hello_world.exe # Windows
```

You should see: `Hello, World!`

### 2. Explore the Content

The repository is organized by topics with difficulty levels:

```
📁 fundamentals/       → Start here! Variables, functions, loops
📁 data-structures/    → Arrays, linked lists, trees, graphs
📁 algorithms/         → Sorting, searching, dynamic programming
📁 memory-management/  → Pointers, dynamic allocation
📁 best-practices/     → Coding standards, design patterns
📁 projects/           → Complete projects for hands-on practice
📁 exercises/          → Practice problems with solutions
📁 resources/          → Cheatsheets, guides, references
```

### 3. Follow the Learning Path

#### For Complete Beginners:
1. **Fundamentals/Beginner**: Learn basic syntax
   - Hello World
   - Variables and data types
   - Control flow (if, loops)
   - Functions
   - Arrays

2. **Exercises/Beginner**: Practice what you learned

3. **Projects/Beginner**: Build simple projects

#### For Intermediate Learners:
1. **Data Structures**: Understand fundamental structures
2. **Algorithms**: Learn common algorithms
3. **Memory Management**: Master pointers and dynamic memory
4. **Exercises/Intermediate**: Solve problems
5. **Projects/Intermediate**: Build more complex applications

#### For Advanced Users:
1. **Best Practices**: Professional development standards
2. **Advanced Topics**: Complex data structures and algorithms
3. **Projects/Advanced**: Challenging projects

## 📖 How Each Topic is Structured

Each topic includes:
- **README.md**: Overview and roadmap
- **Beginner/Intermediate/Advanced folders**: Difficulty levels
- **Code examples**: Well-commented, compilable code
- **Explanations**: Detailed concept descriptions
- **Exercises**: Practice problems

## 🔨 Building Specific Examples

```bash
# Build everything
cmake --build .

# Build specific target
cmake --build . --target hello_world

# Run examples
./bin/hello_world
```

## 💡 Tips for Success

1. **Don't Rush**: Master each level before moving on
2. **Code Along**: Type examples yourself, don't just read
3. **Practice Daily**: Consistency matters more than duration
4. **Debug**: Learn to use debugging tools (GDB, Valgrind)
5. **Ask Questions**: Use forums, communities when stuck
6. **Build Projects**: Apply what you learn

## 🛠️ Setup Your Environment

If you haven't set up your development environment yet:

1. **Check Resources**: See [tooling-setup](resources/tooling-setup/README.md)
2. **Install Compiler**: GCC, Clang, or MSVC
3. **Install CMake**: Version 3.15 or higher
4. **Choose IDE/Editor**: VS Code, Visual Studio, CLion

## 📚 Additional Resources

- [Cheatsheets](resources/cheatsheets/README.md) - Quick references
- [Debugging Guides](resources/debugging-guides/README.md) - Troubleshooting help
- [Common Pitfalls](resources/common-pitfalls/README.md) - Avoid mistakes
- [External Links](resources/external-links/README.md) - Books, courses, websites

## 🤝 Contributing

This is a living document that grows over time. Contributions are welcome!

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## 📝 Next Steps

1. ✅ Build and run Hello World
2. 📖 Read [Fundamentals README](fundamentals/README.md)
3. 💻 Start with [Hello World tutorial](fundamentals/beginner/hello-world.md)
4. 🏋️ Complete beginner exercises
5. 🚀 Build your first project

Happy Coding! 🎉
