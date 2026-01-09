/**
 * ============================================================================
 * Stack vs Heap: Memory Allocation Performance and Behavior
 * ============================================================================
 * 
 * PURPOSE:
 * Demonstrates the fundamental differences between stack and heap allocation
 * in terms of performance, lifetime, size constraints, and use cases.
 * 
 * CONCEPT:
 * - Stack: Fast, automatic, limited size, function-scoped lifetime
 * - Heap: Slower, manual management, large size, flexible lifetime
 * 
 * MEMORY IMPLICATIONS:
 * Stack:
 * - Size: Fixed at program start (1-8MB desktop, 1-16KB embedded)
 * - Allocation: ~1-5 cycles (SUB ESP instruction)
 * - Location: High memory addresses, grows downward
 * - Thread-safety: Each thread has separate stack
 * 
 * Heap:
 * - Size: Limited by available RAM (GBs on desktop, avoid on embedded)
 * - Allocation: ~100-300 cycles (malloc searches free list, locks)
 * - Location: After .bss section, grows upward
 * - Thread-safety: Requires mutex (adds overhead)
 * 
 * CPU OVERHEAD:
 * Operation       | Stack       | Heap
 * ----------------|-------------|------------------
 * Allocate        | 1-5 cycles  | 100-300 cycles
 * Deallocate      | 1-2 cycles  | 50-150 cycles
 * Access          | 1-3 cycles  | 1-10 cycles
 * Fragmentation   | None        | Can be severe
 * 
 * COMPILATION:
 * gcc -O2 -g stack_vs_heap.c -o stack_heap_demo
 * 
 * PROFILING:
 * time ./stack_heap_demo
 * valgrind --tool=massif ./stack_heap_demo  # Heap profiling
 * 
 * AUTHOR: C/C++ Learning Repository
 * DATE: January 2026
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

/* ============================================================================
 * PART 1: Stack Allocation Basics
 * ============================================================================
 */

/**
 * Demonstrate stack allocation
 * 
 * Memory: Allocated on function entry, freed on exit
 * CPU: ~1-5 cycles for entire allocation
 * Lifetime: Automatic (destroyed when function returns)
 */
void stack_allocation_demo(void) {
    // All these allocations are nearly free (just move stack pointer)
    int x = 42;                    // 4 bytes
    double y = 3.14;               // 8 bytes
    char buffer[256];              // 256 bytes
    int array[100];                // 400 bytes
    
    // Total: 668 bytes allocated in ~5 cycles!
    // Stack pointer just decremented by 668
    
    printf("Stack variables:\n");
    printf("  x address:      %p (stack)\n", (void*)&x);
    printf("  buffer address: %p (stack)\n", (void*)buffer);
    printf("  array address:  %p (stack)\n", (void*)array);
    
    // Variables automatically destroyed when function returns
    // No free() needed!
}

/**
 * Demonstrate automatic lifetime
 * 
 * Stack variables are destroyed when function exits
 */
int* stack_lifetime_problem(void) {
    int local = 100;
    
    // ❌ DANGER: Returning pointer to stack variable
    // local is destroyed when function returns!
    return &local;  // Undefined behavior
}

/**
 * Solutions to lifetime problem
 */

// ✅ Solution 1: Return by value
int stack_lifetime_solution1(void) {
    int local = 100;
    return local;  // Copy returned (safe)
}

// ✅ Solution 2: Use output parameter
void stack_lifetime_solution2(int* output) {
    *output = 100;  // Modify caller's variable
}

// ✅ Solution 3: Static storage
int* stack_lifetime_solution3(void) {
    static int value = 100;  // Lives forever (.data section)
    return &value;  // Safe (but not thread-safe!)
}

/* ============================================================================
 * PART 2: Heap Allocation Basics
 * ============================================================================
 */

/**
 * Demonstrate heap allocation
 * 
 * Memory: Allocated by malloc, must be manually freed
 * CPU: ~100-300 cycles per malloc call
 * Lifetime: Manual (survives function return)
 */
void heap_allocation_demo(void) {
    // Each malloc is expensive (searches free list, updates metadata)
    int* x = malloc(sizeof(int));              // ~100-300 cycles
    double* y = malloc(sizeof(double));        // ~100-300 cycles
    char* buffer = malloc(256);                // ~100-300 cycles
    int* array = malloc(100 * sizeof(int));    // ~100-300 cycles
    
    // Check for allocation failures
    if (!x || !y || !buffer || !array) {
        fprintf(stderr, "Allocation failed!\n");
        // Cleanup any successful allocations
        free(x);
        free(y);
        free(buffer);
        free(array);
        return;
    }
    
    printf("\nHeap variables:\n");
    printf("  x address:      %p (heap)\n", (void*)x);
    printf("  buffer address: %p (heap)\n", (void*)buffer);
    printf("  array address:  %p (heap)\n", (void*)array);
    
    // MUST manually free (or memory leaks!)
    free(x);
    free(y);
    free(buffer);
    free(array);
}

/**
 * Heap allocation allows data to outlive function
 */
int* heap_lifetime_correct(void) {
    int* ptr = malloc(sizeof(int));
    if (ptr) {
        *ptr = 100;
    }
    return ptr;  // ✅ Safe: heap memory survives function return
    // ⚠️ Caller MUST free() the returned pointer!
}

/* ============================================================================
 * PART 3: Performance Comparison
 * ============================================================================
 */

#define ITERATIONS 1000000

/**
 * Measure stack allocation performance
 * 
 * Expected: Very fast (optimized to single SUB instruction)
 */
double benchmark_stack(void) {
    clock_t start = clock();
    
    for (int i = 0; i < ITERATIONS; i++) {
        // Allocate on stack
        char buffer[256];
        
        // Prevent optimization (force allocation)
        buffer[0] = (char)i;
        buffer[255] = (char)i;
    }
    
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/**
 * Measure heap allocation performance
 * 
 * Expected: Much slower (malloc overhead)
 */
double benchmark_heap(void) {
    clock_t start = clock();
    
    for (int i = 0; i < ITERATIONS; i++) {
        // Allocate on heap
        char* buffer = malloc(256);
        
        if (buffer) {
            // Use buffer
            buffer[0] = (char)i;
            buffer[255] = (char)i;
            
            // Free (required!)
            free(buffer);
        }
    }
    
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/**
 * Compare allocation strategies
 */
void performance_comparison(void) {
    printf("\n--- Performance Comparison ---\n");
    printf("Running %d iterations...\n", ITERATIONS);
    
    double stack_time = benchmark_stack();
    double heap_time = benchmark_heap();
    
    printf("Stack allocation: %.6f seconds\n", stack_time);
    printf("Heap allocation:  %.6f seconds\n", heap_time);
    printf("Heap is %.2fx slower than stack\n", heap_time / stack_time);
    
    // Typical results:
    // Stack: 0.001 seconds
    // Heap:  0.100 seconds (100x slower!)
}

/* ============================================================================
 * PART 4: Size Limitations
 * ============================================================================
 */

/**
 * Stack size limits
 * 
 * Linux default: ~8MB
 * Windows default: ~1MB
 * Embedded: 1-16KB
 */
void stack_size_limits(void) {
    printf("\n--- Stack Size Limits ---\n");
    
    // ✅ This is fine (4KB on stack)
    char small_buffer[4096];
    small_buffer[0] = 'A';
    printf("4KB stack allocation: OK\n");
    
    // ⚠️ This might work on desktop but not embedded
    // char medium_buffer[100000];  // 100KB
    // printf("100KB stack allocation: %s\n", 
    //        "Maybe OK on desktop, crash on embedded");
    
    // ❌ This will cause stack overflow on most systems
    // char huge_buffer[10000000];  // 10MB
    // printf("10MB stack allocation: CRASH\n");
}

/**
 * Heap size limits
 * 
 * Desktop: Limited by available RAM (GBs)
 * Embedded: Avoid heap or use small pools
 */
void heap_size_limits(void) {
    printf("\n--- Heap Size Limits ---\n");
    
    // ✅ Large allocations OK on heap (if RAM available)
    char* large_buffer = malloc(10 * 1024 * 1024);  // 10MB
    if (large_buffer) {
        printf("10MB heap allocation: OK\n");
        free(large_buffer);
    } else {
        printf("10MB heap allocation: FAILED (out of memory)\n");
    }
    
    // Heap limited by available RAM
    char* huge_buffer = malloc(1024ULL * 1024 * 1024 * 1024);  // 1TB
    if (huge_buffer) {
        printf("1TB heap allocation: OK (you have lots of RAM!)\n");
        free(huge_buffer);
    } else {
        printf("1TB heap allocation: FAILED (as expected)\n");
    }
}

/* ============================================================================
 * PART 5: Fragmentation
 * ============================================================================
 */

/**
 * Demonstrate heap fragmentation
 * 
 * Problem: Repeated alloc/free of varied sizes creates unusable gaps
 */
void heap_fragmentation_demo(void) {
    printf("\n--- Heap Fragmentation ---\n");
    
    void* pointers[10];
    
    // Allocate 10 blocks of varying sizes
    for (int i = 0; i < 10; i++) {
        size_t size = (i + 1) * 100;
        pointers[i] = malloc(size);
        printf("Allocated block %d: %zu bytes at %p\n", 
               i, size, pointers[i]);
    }
    
    // Free every other block (creates gaps)
    for (int i = 0; i < 10; i += 2) {
        free(pointers[i]);
        printf("Freed block %d\n", i);
    }
    
    // Now try to allocate large contiguous block
    void* large = malloc(3000);  // Needs contiguous space
    if (large) {
        printf("Large allocation (3000 bytes): SUCCESS at %p\n", large);
        free(large);
    } else {
        printf("Large allocation (3000 bytes): FAILED (fragmentation)\n");
    }
    
    // Free remaining blocks
    for (int i = 1; i < 10; i += 2) {
        free(pointers[i]);
    }
    
    // Stack has NO fragmentation (always contiguous)
}

/* ============================================================================
 * PART 6: Use Case Guidelines
 * ============================================================================
 */

/**
 * Decision matrix for stack vs heap
 */
void use_case_guidelines(void) {
    printf("\n=== Stack vs Heap Decision Guide ===\n\n");
    
    printf("Use STACK when:\n");
    printf("  ✅ Size known at compile time\n");
    printf("  ✅ Small size (< 1KB recommended)\n");
    printf("  ✅ Short lifetime (function-scoped)\n");
    printf("  ✅ Performance critical\n");
    printf("  ✅ Embedded systems\n");
    printf("  ✅ Single-threaded (automatic thread-safety)\n\n");
    
    printf("Use HEAP when:\n");
    printf("  ✅ Size determined at runtime\n");
    printf("  ✅ Large size (> 4KB)\n");
    printf("  ✅ Lifetime beyond function scope\n");
    printf("  ✅ Data returned to caller\n");
    printf("  ✅ Ample RAM available\n");
    printf("  ✅ Size more critical than speed\n\n");
    
    printf("Avoid HEAP in embedded when:\n");
    printf("  ⚠️  Real-time constraints (non-deterministic)\n");
    printf("  ⚠️  Limited RAM (fragmentation risk)\n");
    printf("  ⚠️  Safety-critical code (MISRA discourages dynamic alloc)\n");
}

/* ============================================================================
 * PART 7: Practical Examples
 * ============================================================================
 */

// Example 1: Processing fixed-size data (use stack)
void process_packet(const uint8_t* data, size_t len) {
    // ✅ Stack: size known, short lifetime
    uint8_t buffer[256];
    
    if (len > sizeof(buffer)) {
        fprintf(stderr, "Packet too large\n");
        return;
    }
    
    memcpy(buffer, data, len);
    // Process buffer...
}

// Example 2: User input (use heap)
char* read_line(FILE* fp) {
    // ✅ Heap: size unknown, lifetime extends beyond function
    size_t capacity = 128;
    char* line = malloc(capacity);
    
    if (!line) return NULL;
    
    size_t length = 0;
    int c;
    while ((c = fgetc(fp)) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char* new_line = realloc(line, capacity);
            if (!new_line) {
                free(line);
                return NULL;
            }
            line = new_line;
        }
        line[length++] = (char)c;
    }
    
    line[length] = '\0';
    return line;  // Caller must free!
}

// Example 3: Lookup table (use static/const)
uint32_t crc32_byte(uint8_t byte) {
    // ✅ Static: computed once, persists, no allocation overhead
    static const uint32_t crc_table[256] = {
        0x00000000, 0x77073096, 0xEE0E612C, /* ... */
    };
    
    return crc_table[byte];
}

/* ============================================================================
 * MAIN: Demonstration
 * ============================================================================
 */

int main(void) {
    printf("=================================================\n");
    printf("  Stack vs Heap: Memory Allocation\n");
    printf("=================================================\n\n");
    
    // Part 1: Basic demonstrations
    printf("--- Part 1: Stack Allocation ---\n");
    stack_allocation_demo();
    
    printf("\n--- Part 2: Heap Allocation ---\n");
    heap_allocation_demo();
    
    // Part 3: Performance
    performance_comparison();
    
    // Part 4: Size limits
    stack_size_limits();
    heap_size_limits();
    
    // Part 5: Fragmentation
    heap_fragmentation_demo();
    
    // Part 6: Guidelines
    use_case_guidelines();
    
    printf("\n=================================================\n");
    printf("Key Takeaways:\n");
    printf("1. Stack is 10-100x faster than heap\n");
    printf("2. Stack is limited in size (~8MB max)\n");
    printf("3. Stack variables auto-cleanup (no leaks)\n");
    printf("4. Heap allows flexible lifetime and size\n");
    printf("5. Heap can fragment with varied allocation sizes\n");
    printf("6. Embedded systems prefer stack over heap\n");
    printf("=================================================\n");
    
    return 0;
}

/* ============================================================================
 * ASSEMBLY INSIGHTS (x86-64):
 * ============================================================================
 * 
 * Stack allocation (char buffer[256]):
 * ----------------------------------
 *   sub    rsp, 256     ; Single instruction! ~1 cycle
 *   ; ... use buffer ...
 *   add    rsp, 256     ; Cleanup
 * 
 * Heap allocation (malloc(256)):
 * ----------------------------------
 *   mov    edi, 256
 *   call   malloc       ; 100+ instructions inside malloc!
 *                       ; - Traverse free list
 *                       ; - Update metadata
 *                       ; - Handle locking (thread-safe)
 *   ; ... use buffer ...
 *   mov    rdi, rax
 *   call   free         ; 50+ instructions
 * 
 * The difference is dramatic: 1 instruction vs 150+ instructions.
 * 
 * ============================================================================
 * EMBEDDED CONSIDERATIONS:
 * ============================================================================
 * 
 * STM32F4 (Cortex-M4) with 128KB RAM:
 * 
 * Typical memory budget:
 * - Stack: 4KB (main thread)
 * - .data + .bss: 50KB (global variables)
 * - Heap: 0KB (disabled! Use memory pools instead)
 * - Reserved: 74KB (DMA, USB buffers, etc.)
 * 
 * Why avoid malloc on embedded:
 * 1. Non-deterministic time (violates real-time requirements)
 * 2. Fragmentation with limited RAM is catastrophic
 * 3. Failure handling is complex (what if malloc returns NULL?)
 * 4. MISRA-C Rule 21.3: "malloc and free shall not be used"
 * 
 * Alternative: Memory pools with fixed-size blocks
 * 
 * ============================================================================
 */
