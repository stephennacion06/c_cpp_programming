/**
 * ============================================================================
 * The volatile Keyword in Embedded C
 * ============================================================================
 * 
 * PURPOSE:
 * Demonstrates why 'volatile' is critical for hardware interaction and when
 * the compiler's optimization assumptions break down.
 * 
 * CONCEPT:
 * The compiler assumes memory doesn't change unless the program changes it.
 * This is FALSE for:
 * - Hardware registers (peripherals modify them)
 * - Memory modified by interrupts
 * - Memory modified by DMA
 * - Memory shared between threads
 * 
 * MEMORY IMPLICATIONS:
 * - Zero memory overhead (volatile is just a type qualifier)
 * - Prevents compiler from caching values in registers
 * - Each access generates actual memory read/write instructions
 * 
 * CPU OVERHEAD:
 * - Non-volatile: 0 cycles (value cached in register)
 * - Volatile: 1-10 cycles per access (depends on bus/cache)
 * - Trade-off: Correctness over speed
 * 
 * COMPILATION:
 * gcc -O2 volatile_keyword.c -o volatile_demo
 * gcc -S -O2 volatile_keyword.c  # View assembly output
 * 
 * AUTHOR: C/C++ Learning Repository
 * DATE: January 2026
 * ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* ============================================================================
 * PART 1: Hardware Register Simulation
 * ============================================================================
 * Simulates a hardware status register that changes "magically" from the
 * program's perspective (in real hardware, this happens via peripherals)
 */

// Simulated hardware register (in real embedded: memory-mapped I/O address)
static uint32_t simulated_hardware_register = 0x00;

// Helper to simulate hardware changing the register
void simulate_hardware_update(void) {
    simulated_hardware_register = 0xFF;  // Hardware sets ready flag
}

/**
 * DEMONSTRATION 1: Without volatile (BROKEN)
 * 
 * The compiler sees the variable never changes within the loop,
 * so it optimizes the check away or reads it only once.
 */
void wait_for_hardware_broken(void) {
    uint32_t* status_register = &simulated_hardware_register;
    
    printf("Waiting for hardware (non-volatile)...\n");
    
    // ❌ PROBLEM: Compiler may optimize this to infinite loop
    // With -O2, the compiler might:
    // 1. Read *status_register once before loop
    // 2. Cache value in CPU register
    // 3. Never read from memory again
    while (*status_register == 0) {
        // Spin-wait for hardware to set flag
        // In assembly with optimization: may be "jmp <itself>"
    }
    
    printf("Hardware ready (but we might never get here!)\n");
}

/**
 * DEMONSTRATION 2: With volatile (CORRECT)
 * 
 * Forces compiler to read from memory on every iteration.
 * Assembly will show actual load instruction in the loop.
 */
void wait_for_hardware_correct(void) {
    volatile uint32_t* status_register = (volatile uint32_t*)&simulated_hardware_register;
    
    printf("Waiting for hardware (volatile)...\n");
    
    // ✅ CORRECT: Compiler MUST read from memory every time
    // Assembly will show:
    // loop:
    //   ldr r0, [status_register]  ; Load from memory
    //   cmp r0, #0                 ; Compare
    //   beq loop                   ; Branch if equal
    while (*status_register == 0) {
        // Genuine memory read each iteration
    }
    
    printf("Hardware ready!\n");
}

/* ============================================================================
 * PART 2: Memory-Mapped I/O Example (Real Embedded Pattern)
 * ============================================================================
 * Shows actual embedded code for STM32 GPIO control
 */

// Example: STM32F4 GPIOA registers (real memory addresses)
#define GPIOA_BASE      0x40020000UL
#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + 0x00))  // Mode register
#define GPIOA_ODR       (*(volatile uint32_t*)(GPIOA_BASE + 0x14))  // Output data
#define GPIOA_IDR       (*(volatile uint32_t*)(GPIOA_BASE + 0x10))  // Input data

/**
 * Configure GPIO pin as output
 * 
 * Memory: Accesses hardware register at 0x40020000
 * CPU: ~3-5 cycles for read-modify-write on AHB1 bus
 */
void gpio_pin_set_output(uint8_t pin) {
    // Read current mode register
    uint32_t mode = GPIOA_MODER;
    
    // Clear the 2 bits for this pin
    mode &= ~(0x3 << (pin * 2));
    
    // Set to output mode (01b)
    mode |= (0x1 << (pin * 2));
    
    // Write back to register
    GPIOA_MODER = mode;
    
    // Without volatile, compiler might:
    // 1. Optimize away the read if mode was "just written"
    // 2. Reorder writes (breaking hardware sequencing)
    // 3. Eliminate "redundant" writes
}

/**
 * Toggle GPIO pin (turn LED on/off)
 * 
 * Memory: Single write to output data register
 * CPU: ~2-4 cycles per toggle
 */
void gpio_toggle_pin(uint8_t pin) {
    GPIOA_ODR ^= (1 << pin);  // XOR toggles the bit
    
    // volatile ensures:
    // 1. Actual write to 0x40020014 happens
    // 2. Write not eliminated as "dead store"
    // 3. Write not reordered with other operations
}

/**
 * Read GPIO input pin (button state)
 * 
 * Returns: true if pin is HIGH, false if LOW
 */
bool gpio_read_pin(uint8_t pin) {
    // Must use volatile - hardware can change IDR any time
    return (GPIOA_IDR & (1 << pin)) != 0;
}

/* ============================================================================
 * PART 3: Interrupt Flag Example
 * ============================================================================
 * Shared variable between interrupt handler and main code
 */

// Flag set by interrupt handler
static volatile bool data_ready = false;

// Simulated interrupt handler
void UART_IRQHandler(void) {
    // Hardware interrupt occurred - data received
    data_ready = true;  // Signal main loop
    
    // Without volatile, compiler might optimize away the write
    // thinking "no one reads this variable"
}

/**
 * Wait for data in main loop
 * 
 * Pattern: Polling a flag set by interrupt
 * CPU overhead: Spin-wait burns CPU cycles
 * Better approach: Use sleep/WFI instruction in real embedded
 */
void wait_for_uart_data(void) {
    printf("Waiting for UART interrupt...\n");
    
    // Must be volatile - ISR modifies it
    while (!data_ready) {
        // Busy-wait (inefficient but simple)
        // In real embedded: __WFI() to sleep until interrupt
    }
    
    printf("Data received!\n");
    data_ready = false;  // Clear flag
}

/* ============================================================================
 * PART 4: Performance Comparison
 * ============================================================================
 * Demonstrates the CPU cost of volatile
 */

#define ITERATIONS 10000000

void performance_test_non_volatile(void) {
    uint32_t counter = 0;
    uint32_t sum = 0;
    
    // Compiler can optimize heavily:
    // - Keep counter and sum in registers
    // - Unroll loop
    // - Vectorize
    for (uint32_t i = 0; i < ITERATIONS; i++) {
        counter++;
        sum += counter;
    }
    
    printf("Non-volatile sum: %u\n", sum);
}

void performance_test_volatile(void) {
    volatile uint32_t counter = 0;
    volatile uint32_t sum = 0;
    
    // Compiler must:
    // - Load from memory each time
    // - Store to memory after each operation
    // - No loop optimizations
    for (uint32_t i = 0; i < ITERATIONS; i++) {
        counter++;
        sum += counter;
    }
    
    printf("Volatile sum: %u\n", sum);
}

/* ============================================================================
 * PART 5: Common Pitfalls
 * ============================================================================
 */

/**
 * PITFALL 1: Volatile doesn't mean atomic
 * 
 * On 32-bit ARM, 32-bit reads/writes are atomic, but 64-bit are not!
 */
void volatile_not_atomic_example(void) {
    volatile uint64_t counter = 0;
    
    // ❌ PROBLEM: On 32-bit CPU, this is TWO memory operations:
    // 1. Load low 32 bits
    // 2. Load high 32 bits
    // An interrupt between them = torn read!
    
    uint64_t value = counter;  // Not atomic on 32-bit CPU
    
    // ✅ SOLUTION: Disable interrupts or use mutex
    // __disable_irq();
    // uint64_t value = counter;
    // __enable_irq();
    
    printf("Counter: %llu (may be corrupted!)\n", value);
}

/**
 * PITFALL 2: Volatile doesn't prevent reordering across different variables
 * 
 * The compiler won't reorder volatile accesses to THE SAME variable,
 * but can reorder between different volatiles!
 */
void volatile_reordering_example(void) {
    volatile uint32_t* reg1 = (volatile uint32_t*)0x40000000;
    volatile uint32_t* reg2 = (volatile uint32_t*)0x40000004;
    
    *reg1 = 0x1;  // Enable peripheral
    *reg2 = 0x2;  // Configure peripheral
    
    // Compiler MIGHT reorder these (reg1 and reg2 are different)
    // Solution: Memory barrier or compiler barrier
    // __DMB();  // Data Memory Barrier on ARM
}

/**
 * PITFALL 3: Volatile pointer vs pointer to volatile
 */
void volatile_pointer_confusion(void) {
    // Pointer to volatile uint32_t - correct for hardware registers
    volatile uint32_t* ptr1;  // *ptr1 is volatile, ptr1 is not
    
    // Volatile pointer to uint32_t - rarely useful
    uint32_t* volatile ptr2;  // ptr2 is volatile, *ptr2 is not
    
    // Both volatile - overkill for most cases
    volatile uint32_t* volatile ptr3;
    
    // For hardware registers, you want:
    volatile uint32_t* hardware_reg = (volatile uint32_t*)0x40020000;
}

/* ============================================================================
 * MAIN: Demonstration Entry Point
 * ============================================================================
 */

int main(void) {
    printf("=================================================\n");
    printf("  volatile Keyword in Embedded C\n");
    printf("=================================================\n\n");
    
    // Demonstration 1: Hardware register access
    printf("--- Demo 1: Hardware Register Polling ---\n");
    simulated_hardware_register = 0;  // Start not ready
    
    // Simulate hardware becoming ready after function starts
    // (In real code, an interrupt or DMA would do this)
    simulate_hardware_update();
    
    wait_for_hardware_correct();
    
    printf("\n");
    
    // Demonstration 2: GPIO operations (simulated)
    printf("--- Demo 2: GPIO Operations ---\n");
    printf("Configuring GPIO pin 5 as output\n");
    gpio_pin_set_output(5);
    printf("Toggling GPIO pin 5\n");
    gpio_toggle_pin(5);
    
    printf("\n");
    
    // Demonstration 3: Interrupt flag
    printf("--- Demo 3: Interrupt Flag ---\n");
    data_ready = false;
    UART_IRQHandler();  // Simulate interrupt
    wait_for_uart_data();
    
    printf("\n");
    
    // Demonstration 4: Performance comparison
    printf("--- Demo 4: Performance Impact ---\n");
    printf("Note: Run with 'time ./volatile_demo' to see difference\n");
    performance_test_non_volatile();
    performance_test_volatile();
    
    printf("\n");
    
    // Demonstration 5: Common pitfalls
    printf("--- Demo 5: Common Pitfalls ---\n");
    volatile_not_atomic_example();
    
    printf("\n=================================================\n");
    printf("Key Takeaways:\n");
    printf("1. Use volatile for hardware registers\n");
    printf("2. Use volatile for ISR-modified variables\n");
    printf("3. volatile ≠ atomic (use mutexes for multi-byte)\n");
    printf("4. volatile ≠ memory barrier (use __DMB on ARM)\n");
    printf("5. Accept the performance cost for correctness\n");
    printf("=================================================\n");
    
    return 0;
}

/* ============================================================================
 * ASSEMBLY ANALYSIS (with -O2 optimization)
 * ============================================================================
 * 
 * NON-VOLATILE READ:
 * ----------------
 *   mov r0, #0           ; Load constant 0 once
 * loop:
 *   cmp r0, #0           ; Compare cached value
 *   beq loop             ; Loop forever (value never changes!)
 * 
 * VOLATILE READ:
 * ------------
 * loop:
 *   ldr r0, [r1]         ; Load from memory address EVERY time
 *   cmp r0, #0           ; Compare fresh value
 *   beq loop             ; Loop until memory changes
 * 
 * The difference: ldr instruction in every iteration
 * Cost: ~2-10 cycles depending on bus speed and caching
 * 
 * ============================================================================
 * FURTHER READING:
 * ============================================================================
 * 
 * 1. ISO C99 Standard, Section 6.7.3 (Type Qualifiers)
 * 2. "volatile Considered Harmful" - but not for embedded!
 * 3. ARM Cortex-M Programming Guide (Memory Barriers)
 * 4. Your microcontroller's reference manual (register map)
 * 
 * ============================================================================
 */
