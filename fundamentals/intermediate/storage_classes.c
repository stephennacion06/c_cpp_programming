/**
 * ============================================================================
 * Storage Classes in C: static, extern, auto, register
 * ============================================================================
 * 
 * PURPOSE:
 * Demonstrates the four storage classes in C and their impact on memory
 * layout, scope, lifetime, and linkage. Critical for understanding where
 * variables live and how long they persist.
 * 
 * CONCEPT:
 * Storage class specifies:
 * 1. **Scope**: Where the variable is visible
 * 2. **Lifetime**: When memory is allocated and freed
 * 3. **Linkage**: Whether visible across translation units
 * 4. **Storage location**: Stack, .data, .bss, or register
 * 
 * STORAGE CLASSES:
 * - **auto**: Default for local variables (stack, function scope)
 * - **static**: Persistent lifetime (stack or data segment depending on scope)
 * - **extern**: Declaration (not definition), external linkage
 * - **register**: Hint to store in CPU register (rarely used modern C)
 * 
 * MEMORY IMPLICATIONS:
 * 
 * | Storage | Location | Lifetime | Scope | Linkage |
 * |---------|----------|----------|-------|---------|
 * | auto | Stack | Function | Block | None |
 * | static (local) | .data/.bss | Program | Block | Internal |
 * | static (global) | .data/.bss | Program | File | Internal |
 * | extern | .data/.bss | Program | Global | External |
 * | register | Register? | Function | Block | None |
 * 
 * CPU OVERHEAD:
 * - auto: ~1-5 cycles (stack allocation)
 * - static: 0 cycles (allocated at program start)
 * - extern: 0 cycles (references existing symbol)
 * - register: 0 cycles (CPU register, if honored)
 * 
 * COMPILATION:
 * gcc -O2 -g storage_classes.c -o storage_demo
 * 
 * VIEW SYMBOLS:
 * nm storage_demo | grep -E "function_name|variable_name"
 * 
 * AUTHOR: C/C++ Learning Repository
 * DATE: January 2026
 * ============================================================================
 */

#include <stdio.h>
#include <stdint.h>

/* ============================================================================
 * PART 1: auto Storage Class (Default)
 * ============================================================================
 */

/**
 * auto variables: Stack-allocated, automatic lifetime
 * 
 * Memory: Stack (high addresses, grows down)
 * Lifetime: Created on function entry, destroyed on exit
 * Scope: Block scope (visible only in declaring block)
 * Linkage: None (not accessible from other functions)
 * 
 * CPU: ~1-5 cycles to allocate (SUB ESP instruction)
 */
void auto_storage_demo(void) {
    // 'auto' is implicit (rarely written explicitly)
    auto int x = 10;        // Explicit auto (same as: int x = 10;)
    int y = 20;             // Implicit auto (more common)
    
    printf("--- auto Storage Class ---\n");
    printf("x = %d (address: %p, on stack)\n", x, (void*)&x);
    printf("y = %d (address: %p, on stack)\n", y, (void*)&y);
    
    // Variables destroyed when function returns
    // Memory automatically reclaimed
}

/**
 * Auto variables are NOT initialized automatically
 * 
 * ⚠️  Reading uninitialized auto variables = undefined behavior
 */
void auto_uninitialized_danger(void) {
    int uninitialized;  // Contains garbage!
    
    printf("\nUninitialized auto: %d (garbage value)\n", uninitialized);
    // This is undefined behavior - could be any value
}

/* ============================================================================
 * PART 2: static Storage Class (Local)
 * ============================================================================
 */

/**
 * static local variables: Persistent across function calls
 * 
 * Memory: .data or .bss section (depending on initializer)
 * Lifetime: Entire program (initialized before main, persists after)
 * Scope: Block scope (only visible in declaring block)
 * Linkage: None (not accessible from other functions)
 * 
 * CPU: 0 cycles to "allocate" (memory exists at program start)
 * 
 * USE CASES:
 * - Counters that persist across calls
 * - Caching computed values
 * - State machines
 */
void static_local_demo(void) {
    static int call_count = 0;  // Initialized ONCE, persists forever
    call_count++;
    
    int temp = 0;  // Re-created each call
    temp++;
    
    printf("\n--- static Local Variables ---\n");
    printf("call_count = %d (persists, address: %p)\n", 
           call_count, (void*)&call_count);
    printf("temp = %d (reset each call, address: %p)\n", 
           temp, (void*)&temp);
}

/**
 * static variables are ZERO-INITIALIZED by default
 * 
 * Unlike auto variables, static variables are guaranteed to be zero
 * if no explicit initializer is provided.
 */
void static_zero_initialization(void) {
    static int counter;        // Guaranteed to be 0
    static int array[100];     // All elements are 0
    
    printf("\nstatic zero-init: counter = %d\n", counter);
    printf("static array[50] = %d\n", array[50]);
}

/**
 * Practical example: Function call counter
 */
void function_with_counter(void) {
    static uint32_t calls = 0;
    calls++;
    printf("This function has been called %u times\n", calls);
}

/* ============================================================================
 * PART 3: static Storage Class (Global)
 * ============================================================================
 */

/**
 * static global variables: File-scoped, internal linkage
 * 
 * Memory: .data or .bss section
 * Lifetime: Entire program
 * Scope: File scope (visible in entire file)
 * Linkage: INTERNAL (NOT visible to other translation units)
 * 
 * USE CASES:
 * - Hide implementation details
 * - Prevent name conflicts between files
 * - Encapsulation (C's version of private)
 */

// This variable is visible only in THIS file
static int file_private_counter = 0;

// This function is visible only in THIS file
static void file_private_function(void) {
    printf("\n--- static Global (File Scope) ---\n");
    printf("file_private_counter = %d\n", file_private_counter);
    printf("This function cannot be called from other files\n");
}

void static_global_demo(void) {
    file_private_counter++;
    file_private_function();
}

/* ============================================================================
 * PART 4: extern Storage Class
 * ============================================================================
 */

/**
 * extern variables: Declaration (not definition), external linkage
 * 
 * Memory: Defined in another translation unit
 * Lifetime: Depends on actual definition
 * Scope: Global (visible after declaration)
 * Linkage: EXTERNAL (visible to all translation units)
 * 
 * USE CASES:
 * - Share global variables across multiple .c files
 * - Access variables defined in libraries
 */

// Declaration: "This variable exists somewhere else"
extern int global_shared_counter;  // Defined in another file or below

// Definition: "Allocate memory for this variable"
int global_shared_counter = 100;   // Actual storage allocated here

/**
 * extern functions (default for non-static functions)
 * 
 * Functions are extern by default (can be called from other files)
 */
void extern_function_demo(void) {
    printf("\n--- extern Storage Class ---\n");
    printf("global_shared_counter = %d\n", global_shared_counter);
    printf("This function is 'extern' by default\n");
    printf("Can be called from other translation units\n");
}

// Explicit extern (redundant but shows intent)
extern void extern_function_demo(void);

/* ============================================================================
 * PART 5: register Storage Class
 * ============================================================================
 */

/**
 * register variables: Hint to store in CPU register
 * 
 * Memory: CPU register (if compiler honors hint)
 * Lifetime: Function scope
 * Scope: Block scope
 * Linkage: None
 * 
 * MODERN NOTE:
 * - Compilers ignore 'register' keyword (they're smarter than you!)
 * - C++17 deprecated it
 * - Included here for completeness
 * 
 * RESTRICTIONS:
 * - Cannot take address (&register_var is illegal)
 * - No pointers to register variables
 */
void register_storage_demo(void) {
    register int fast_counter = 0;  // Compiler may put in register
    
    printf("\n--- register Storage Class ---\n");
    printf("register fast_counter = %d\n", fast_counter);
    // printf("Address: %p\n", (void*)&fast_counter);  // ❌ ILLEGAL!
    
    // Modern approach: Let compiler optimize
    // -O2 or -O3 optimization will use registers automatically
}

/**
 * When register keyword was useful (1980s)
 * 
 * In tight loops on slow CPUs, register made a difference.
 * Today: Compiler knows better.
 */
void register_legacy_usage(void) {
    // 1980s style (register keyword)
    register int i;
    for (i = 0; i < 1000000; i++) {
        // Loop variable in register
    }
    
    // Modern style (let compiler optimize)
    for (int j = 0; j < 1000000; j++) {
        // Compiler will use register with -O2
    }
}

/* ============================================================================
 * PART 6: Memory Layout Visualization
 * ============================================================================
 */

int global_initialized = 42;        // .data section (non-zero init)
int global_zero = 0;                // .bss section (zero init)
static int file_static = 10;       // .data section, internal linkage
const int global_const = 100;      // .rodata section (read-only)

void memory_layout_visualization(void) {
    static int func_static = 5;     // .data section
    int local_auto = 1;             // Stack
    
    printf("\n=== Memory Layout ===\n");
    printf("\n.text section (code):\n");
    printf("  Function address: %p\n", (void*)memory_layout_visualization);
    
    printf("\n.rodata section (constants):\n");
    printf("  global_const at %p\n", (void*)&global_const);
    
    printf("\n.data section (initialized globals):\n");
    printf("  global_initialized at %p\n", (void*)&global_initialized);
    printf("  file_static at %p\n", (void*)&file_static);
    printf("  func_static at %p\n", (void*)&func_static);
    
    printf("\n.bss section (zero-initialized):\n");
    printf("  global_zero at %p\n", (void*)&global_zero);
    
    printf("\nStack (local variables):\n");
    printf("  local_auto at %p\n", (void*)&local_auto);
    
    // Typical output shows:
    // - .text around 0x400000 (low addresses)
    // - .data/.bss around 0x600000 (after .text)
    // - Stack around 0x7fff... (high addresses)
}

/* ============================================================================
 * PART 7: Practical Examples and Best Practices
 * ============================================================================
 */

/**
 * Example 1: Singleton pattern using static
 * 
 * Ensures only one instance of data structure exists
 */
typedef struct {
    int initialized;
    int data[100];
} Singleton;

Singleton* get_singleton(void) {
    static Singleton instance = {0};  // Allocated once, persists
    
    if (!instance.initialized) {
        // Initialize on first call
        for (int i = 0; i < 100; i++) {
            instance.data[i] = i;
        }
        instance.initialized = 1;
        printf("\nSingleton initialized\n");
    }
    
    return &instance;
}

/**
 * Example 2: Module-private helpers (static functions)
 * 
 * Hide implementation details from users
 */

// ✅ Good: Internal helper, not exposed
static int helper_function(int x) {
    return x * 2;
}

// ✅ Good: Public API
int public_api_function(int x) {
    return helper_function(x) + 1;
}

/**
 * Example 3: Configuration with extern
 * 
 * Define once, use everywhere
 */

// In config.c (definition):
// int debug_mode = 0;

// In multiple .c files (declaration):
extern int debug_mode;  // Reference to variable in config.c

/**
 * Example 4: Embedded systems - hardware register access
 */
#define GPIO_ODR (*(volatile uint32_t*)0x40020014)

void toggle_led_with_static_state(void) {
    static uint8_t led_state = 0;  // Persistent state
    
    led_state = !led_state;
    if (led_state) {
        GPIO_ODR |= (1 << 5);  // Turn on
    } else {
        GPIO_ODR &= ~(1 << 5);  // Turn off
    }
}

/* ============================================================================
 * PART 8: Common Pitfalls
 * ============================================================================
 */

/**
 * Pitfall 1: Forgetting static for file-scope functions
 */

// ❌ Bad: This function visible to all files (name collision risk)
void utility_function(void) {
    // ...
}

// ✅ Good: This function private to this file
static void utility_function_private(void) {
    // ...
}

/**
 * Pitfall 2: Returning pointer to auto variable
 */

// ❌ Undefined behavior
char* bad_function(void) {
    char buffer[100];  // auto, destroyed on return
    return buffer;     // ❌ DANGLING POINTER!
}

// ✅ Solution 1: static storage
char* good_function_static(void) {
    static char buffer[100];  // Persists
    return buffer;            // ✅ Safe
}

// ✅ Solution 2: Caller provides buffer
void good_function_caller_buffer(char* output, size_t size) {
    // Use caller's buffer
}

/**
 * Pitfall 3: Uninitialized auto variables
 */
void pitfall_uninitialized(void) {
    int x;  // ❌ Contains garbage
    printf("x = %d\n", x);  // Undefined behavior
    
    static int y;  // ✅ Zero-initialized
    printf("y = %d\n", y);  // Always 0
}

/* ============================================================================
 * MAIN: Demonstration
 * ============================================================================
 */

int main(void) {
    printf("=================================================\n");
    printf("  Storage Classes in C\n");
    printf("=================================================\n\n");
    
    // Part 1: auto
    auto_storage_demo();
    auto_uninitialized_danger();
    
    // Part 2: static local
    printf("\nCalling static_local_demo() three times:\n");
    for (int i = 0; i < 3; i++) {
        static_local_demo();
    }
    static_zero_initialization();
    
    printf("\nCalling function_with_counter() three times:\n");
    for (int i = 0; i < 3; i++) {
        function_with_counter();
    }
    
    // Part 3: static global
    static_global_demo();
    
    // Part 4: extern
    extern_function_demo();
    
    // Part 5: register
    register_storage_demo();
    
    // Part 6: Memory layout
    memory_layout_visualization();
    
    // Part 7: Practical examples
    printf("\nCalling get_singleton() twice:\n");
    Singleton* s1 = get_singleton();
    Singleton* s2 = get_singleton();
    printf("s1 address: %p\n", (void*)s1);
    printf("s2 address: %p (same as s1 - singleton!)\n", (void*)s2);
    
    printf("\n=================================================\n");
    printf("Key Takeaways:\n");
    printf("1. auto: Stack, automatic lifetime (default)\n");
    printf("2. static local: Persistent, block scope\n");
    printf("3. static global: Internal linkage (file-private)\n");
    printf("4. extern: External linkage (cross-file)\n");
    printf("5. register: Obsolete hint (ignored by modern compilers)\n");
    printf("=================================================\n");
    
    return 0;
}

/* ============================================================================
 * LINKER SYMBOLS:
 * ============================================================================
 * 
 * View with: nm storage_demo | grep -v " U "
 * 
 * Output interpretation:
 * 
 * T = .text (function code)
 * D = .data (initialized data)
 * B = .bss (uninitialized data)
 * R = .rodata (read-only)
 * t/d/b = local symbol (static)
 * 
 * Example:
 * 0000000000400500 T main                    # extern function
 * 0000000000400520 t file_private_function   # static function
 * 0000000000601000 D global_initialized      # extern variable
 * 0000000000601004 d file_static             # static variable
 * 0000000000601100 B global_zero             # extern, .bss
 * 
 * Capital = external linkage (visible to linker)
 * Lowercase = internal linkage (not visible to linker)
 * 
 * ============================================================================
 * EMBEDDED IMPLICATIONS:
 * ============================================================================
 * 
 * static vs auto trade-off:
 * 
 * STM32F4 with 4KB stack:
 * 
 * ❌ Stack overflow risk:
 * void process() {
 *     char buffer[2048];  // Half the stack!
 * }
 * 
 * ✅ Use static:
 * void process() {
 *     static char buffer[2048];  // In .bss, not stack
 * }
 * 
 * BUT: static is NOT re-entrant (not thread-safe, not recursive-safe)
 * 
 * ============================================================================
 */
