# Contributing Guidelines

Thank you for your interest in contributing to the C/C++ Knowledge Repository! This document provides guidelines for contributing.

## 🎯 Contribution Goals

- Provide clear, accurate, and educational content
- Maintain consistent formatting and organization
- Include working, compilable code examples
- Focus on practical applications and best practices

## 📝 How to Contribute

### Types of Contributions

1. **New Content**: Tutorials, examples, or explanations
2. **Code Examples**: Compilable programs demonstrating concepts
3. **Bug Fixes**: Corrections to existing code or documentation
4. **Improvements**: Enhanced explanations or better examples
5. **Resources**: Cheatsheets, guides, or external links

### Content Guidelines

#### Code Standards

- **C Code**: Follow C11 standard or later
- **C++ Code**: Follow C++17 standard or later
- **Style**: Use consistent indentation (4 spaces)
- **Comments**: Include explanatory comments for complex logic
- **Error Handling**: Demonstrate proper error handling
- **Compilation**: Ensure all code compiles without warnings

#### Example Code Format

```c
/*
 * File: example_name.c
 * Description: Brief description of what this example demonstrates
 * Difficulty: Beginner/Intermediate/Advanced
 */

#include <stdio.h>

int main(void) {
    // Your code here
    printf("Hello, World!\n");
    return 0;
}
```

#### Documentation Standards

- Use clear, concise language
- Include code examples where appropriate
- Organize content by difficulty level when relevant
- Provide explanations for "why" not just "how"
- Link to related topics within the repository

### File Naming Conventions

- Use lowercase with hyphens: `linked-list.c`, `smart-pointers.cpp`
- Descriptive names: `bubble-sort.c` not `sort1.c`
- Include difficulty prefix for exercises: `beginner-calculator.c`

### Directory Structure for New Content

When adding new content:

1. Place C content in `c/` subdirectories
2. Place C++ content in `cpp/` subdirectories
3. Place algorithms in `algorithms/` by category
4. Place complete projects in `projects/` by difficulty
5. Update the relevant `README.md` index

## 🔧 Build System

### Adding New Examples to CMake

When adding compilable examples, update `CMakeLists.txt`:

```cmake
add_executable(example_name path/to/example.c)
```

### Testing Your Changes

Before submitting:

1. Ensure all code compiles without errors or warnings
2. Test with multiple compilers if possible (GCC, Clang, MSVC)
3. Verify documentation renders correctly
4. Check that links work properly

## 📋 Submission Process

### Before Submitting

- [ ] Code compiles without errors or warnings
- [ ] Documentation is clear and free of typos
- [ ] Examples are well-commented
- [ ] File naming follows conventions
- [ ] CMakeLists.txt updated if necessary
- [ ] README.md updated in relevant directory

### Quality Checklist

- **Accuracy**: Information is correct and up-to-date
- **Clarity**: Explanations are easy to understand
- **Completeness**: Examples are complete and runnable
- **Consistency**: Follows repository style and organization
- **Value**: Adds meaningful content to the repository

## 🎨 Style Guide

### Code Style

```c
// Good: Clear variable names, proper spacing
int calculate_average(int numbers[], int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    return sum / count;
}

// Avoid: Unclear names, cramped style
int calc(int n[],int c){int s=0;for(int i=0;i<c;i++)s+=n[i];return s/c;}
```

### Documentation Style

- Use proper markdown formatting
- Include code blocks with syntax highlighting
- Add sections with clear headings
- Use lists for better readability
- Include examples where helpful

## 🐛 Reporting Issues

If you find errors or have suggestions:

1. Check if the issue already exists
2. Provide clear description of the problem
3. Include code samples if relevant
4. Suggest potential solutions if possible

## 💡 Content Suggestions

Priority areas for contributions:

- **Beginner tutorials**: Step-by-step guides for newcomers
- **Data structures**: Implementation and analysis
- **Algorithms**: Classic and modern algorithms
- **Best practices**: Common patterns and anti-patterns
- **Modern C++**: C++17/20 features and usage
- **Real-world projects**: Practical applications
- **Debugging guides**: Common issues and solutions

## 📞 Questions?

If you have questions about contributing, feel free to:

- Open an issue for discussion
- Review existing content for examples
- Check this guide for standards

---

Thank you for helping make this repository a valuable resource for the C/C++ community!
