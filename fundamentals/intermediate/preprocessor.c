/**
 * Preprocessor Directives
 * 
 * Demonstrates C preprocessor capabilities:
 * - Macro definitions (#define)
 * - Conditional compilation (#ifdef, #ifndef, #if, #elif, #else, #endif)
 * - File inclusion (#include)
 * - Macro functions
 * - Predefined macros
 * - Stringification and token pasting
 * - Common pitfalls and best practices
 * 
 * The preprocessor runs BEFORE compilation, performing text substitution
 * and conditional inclusion of code.
 */

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

// ========================================
// 1. SIMPLE MACROS (#define)
// ========================================

#define PI 3.14159265359
#define MAX_BUFFER_SIZE 1024
#define PROJECT_NAME "C Knowledge Repository"
#define VERSION_MAJOR 1
#define VERSION_MINOR 0

// ========================================
// 2. FUNCTION-LIKE MACROS
// ========================================

// Simple macros (BEWARE: No type checking!)
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))

// Multi-line macro (use backslash for continuation)
#define SWAP(a, b, type) \
    do { \
        type temp = (a); \
        (a) = (b); \
        (b) = temp; \
    } while(0)

// Macro with side effects (DANGEROUS!)
#define BAD_SQUARE(x) x * x  // Missing parentheses!

// ========================================
// 3. CONDITIONAL COMPILATION
// ========================================

// Debug mode flag
#define DEBUG_MODE 1

// Platform detection
#ifdef _WIN32
    #define PLATFORM "Windows"
#elif defined(__linux__)
    #define PLATFORM "Linux"
#elif defined(__APPLE__)
    #define PLATFORM "macOS"
#else
    #define PLATFORM "Unknown"
#endif

// Feature flags
#define ENABLE_LOGGING 1
#define ENABLE_PROFILING 0

// ========================================
// 4. STRINGIFICATION & TOKEN PASTING
// ========================================

// Stringification: converts token to string literal
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Token pasting: combines tokens
#define CONCAT(a, b) a##b

// ========================================
// FUNCTION DECLARATIONS
// ========================================

void demonstrate_simple_macros(void);
void demonstrate_function_macros(void);
void demonstrate_conditional_compilation(void);
void demonstrate_predefined_macros(void);
void demonstrate_advanced_features(void);
void demonstrate_pitfalls(void);

// ========================================
// MAIN FUNCTION
// ========================================

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    printf("========================================\n");
    printf("     PREPROCESSOR DIRECTIVES           \n");
    printf("========================================\n\n");

    demonstrate_simple_macros();
    demonstrate_function_macros();
    demonstrate_conditional_compilation();
    demonstrate_predefined_macros();
    demonstrate_advanced_features();
    demonstrate_pitfalls();

    printf("========================================\n");
    printf("     ALL DEMONSTRATIONS COMPLETED      \n");
    printf("========================================\n");

    return 0;
}

/**
 * Simple Macros
 * Constant definitions and replacements
 */
void demonstrate_simple_macros(void) {
    printf("========================================\n");
    printf("1. SIMPLE MACROS (#define)\n");
    printf("========================================\n\n");

    printf("Constant Macros:\n");
    printf("  PI = %.10f\n", PI);
    printf("  MAX_BUFFER_SIZE = %d\n", MAX_BUFFER_SIZE);
    printf("  PROJECT_NAME = %s\n", PROJECT_NAME);
    printf("  Version: %d.%d\n\n", VERSION_MAJOR, VERSION_MINOR);

    // Macro usage in calculations
    float radius = 5.0f;
    float area = PI * radius * radius;
    float circumference = 2 * PI * radius;

    printf("Circle (radius = %.1f):\n", radius);
    printf("  Area = %.2f\n", area);
    printf("  Circumference = %.2f\n\n", circumference);
}

/**
 * Function-like Macros
 * Macros that behave like functions
 */
void demonstrate_function_macros(void) {
    printf("========================================\n");
    printf("2. FUNCTION-LIKE MACROS\n");
    printf("========================================\n\n");

    int x = 5, y = 10;

    printf("Basic Math Macros:\n");
    printf("  x = %d, y = %d\n", x, y);
    printf("  SQUARE(x) = %d\n", SQUARE(x));
    printf("  SQUARE(x + 1) = %d\n", SQUARE(x + 1));  // Expands correctly
    printf("  MAX(x, y) = %d\n", MAX(x, y));
    printf("  MIN(x, y) = %d\n", MIN(x, y));
    printf("  ABS(-15) = %d\n\n", ABS(-15));

    // SWAP macro demonstration
    printf("SWAP Macro:\n");
    int a = 100, b = 200;
    printf("  Before: a = %d, b = %d\n", a, b);
    SWAP(a, b, int);
    printf("  After:  a = %d, b = %d\n\n", a, b);

    // Inline expansion efficiency
    printf("Why Macros?\n");
    printf("  ✓ No function call overhead\n");
    printf("  ✓ Type-generic (works with any type)\n");
    printf("  ✗ No type safety\n");
    printf("  ✗ Code bloat if used frequently\n");
    printf("  ✗ Debugging is harder\n\n");
}

/**
 * Conditional Compilation
 * Compile different code based on conditions
 */
void demonstrate_conditional_compilation(void) {
    printf("========================================\n");
    printf("3. CONDITIONAL COMPILATION\n");
    printf("========================================\n\n");

    printf("Platform Detection:\n");
    printf("  Running on: %s\n\n", PLATFORM);

    printf("Debug Mode:\n");
#if DEBUG_MODE
    printf("  ✓ Debug mode is ENABLED\n");
    printf("  • Extra logging available\n");
    printf("  • Assertions enabled\n");
#else
    printf("  Debug mode is DISABLED\n");
#endif
    printf("\n");

    printf("Feature Flags:\n");
#if ENABLE_LOGGING
    printf("  ✓ Logging: ENABLED\n");
#else
    printf("  ✗ Logging: DISABLED\n");
#endif

#if ENABLE_PROFILING
    printf("  ✓ Profiling: ENABLED\n");
#else
    printf("  ✗ Profiling: DISABLED\n");
#endif
    printf("\n");

    // Conditional code compilation
#ifdef DEBUG_MODE
    int debug_counter = 0;
    printf("Debug Info:\n");
    printf("  debug_counter initialized to %d\n\n", debug_counter);
#endif
}

/**
 * Predefined Macros
 * Compiler-provided macros
 */
void demonstrate_predefined_macros(void) {
    printf("========================================\n");
    printf("4. PREDEFINED MACROS\n");
    printf("========================================\n\n");

    printf("Compilation Info:\n");
    printf("  File: %s\n", __FILE__);
    printf("  Line: %d\n", __LINE__);
    printf("  Date: %s\n", __DATE__);
    printf("  Time: %s\n\n", __TIME__);

    printf("Compiler Info:\n");
#ifdef __STDC__
    printf("  ✓ Standard C conforming compiler\n");
#endif
#ifdef __STDC_VERSION__
    printf("  C Standard Version: %ldL\n", __STDC_VERSION__);
#endif
    printf("\n");

    // Function name macro (C99+)
    printf("Function Name: %s\n\n", __func__);
}

/**
 * Advanced Features
 * Stringification and token pasting
 */
void demonstrate_advanced_features(void) {
    printf("========================================\n");
    printf("5. ADVANCED FEATURES\n");
    printf("========================================\n\n");

    // Stringification
    printf("Stringification (#):\n");
    printf("  STRINGIFY(Hello) = \"%s\"\n", STRINGIFY(Hello));
    printf("  TOSTRING(100 + 200) = \"%s\"\n", TOSTRING(100 + 200));
    printf("  TOSTRING(VERSION_MAJOR) = \"%s\"\n\n", TOSTRING(VERSION_MAJOR));

    // Token pasting
    printf("Token Pasting (##):\n");
    int value1 = 10;
    int value2 = 20;
    printf("  value1 = %d\n", value1);
    printf("  value2 = %d\n", value2);
    printf("  CONCAT(value, 1) = %d\n", CONCAT(value, 1));
    printf("  CONCAT(value, 2) = %d\n\n", CONCAT(value, 2));

    // Practical use: creating variable names
    #define CREATE_VAR(name, val) int var_##name = val
    CREATE_VAR(test, 42);
    printf("Dynamic variable creation:\n");
    printf("  var_test = %d\n\n", var_test);
}

/**
 * Common Pitfalls
 * Things to avoid with macros
 */
void demonstrate_pitfalls(void) {
    printf("========================================\n");
    printf("6. COMMON PITFALLS\n");
    printf("========================================\n\n");

    int n = 5;

    printf("Pitfall 1: Missing Parentheses\n");
    printf("  BAD_SQUARE(n) expands to: n * n\n");
    printf("  BAD_SQUARE(2 + 3) = %d (WRONG! Should be 25)\n", BAD_SQUARE(2 + 3));
    printf("  Expands to: 2 + 3 * 2 + 3 = 11\n");
    printf("  SQUARE(2 + 3) = %d (CORRECT!)\n\n", SQUARE(2 + 3));

    printf("Pitfall 2: Side Effects\n");
    int counter = 0;
    printf("  counter = %d\n", counter);
    printf("  SQUARE(counter++) may evaluate counter++ TWICE!\n");
    // Don't do: SQUARE(counter++) - demonstrates the issue
    printf("  Always use simple expressions in macros\n\n");

    printf("Pitfall 3: Semicolon Issues\n");
    printf("  Use do-while(0) for multi-statement macros\n");
    printf("  This ensures it works correctly in if/else\n\n");

    printf("Best Practices:\n");
    printf("  ✓ Always use parentheses in macro definitions\n");
    printf("  ✓ Use UPPERCASE for macro names\n");
    printf("  ✓ Avoid side effects in macro arguments\n");
    printf("  ✓ Use inline functions instead when possible (C99+)\n");
    printf("  ✓ Use const for constants in Modern C\n");
    printf("  ✓ Document complex macros thoroughly\n\n");
}

// Conditional compilation examples
#ifdef DEBUG_MODE
void debug_function(void) {
    printf("This function only exists in debug builds\n");
}
#endif

// Example: Include guard (typically in header files)
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
// Header content would go here
#endif
