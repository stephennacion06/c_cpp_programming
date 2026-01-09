/**
 * ============================================================================
 * Bit Manipulation for Embedded Systems
 * ============================================================================
 * 
 * PURPOSE:
 * Master the essential bit operations used in embedded programming for:
 * - GPIO control (set/clear/toggle pins)
 * - Register configuration (enable/disable features)
 * - Protocol parsing (extract fields from data)
 * - Efficient storage (pack multiple flags in one byte)
 * 
 * CONCEPT:
 * Most embedded peripherals are controlled through registers where individual
 * bits or bit fields have specific meanings. Bit manipulation lets you modify
 * specific bits without affecting others.
 * 
 * MEMORY IMPLICATIONS:
 * - Operations on registers: in-place modification (0 bytes allocated)
 * - Bit fields in structs: compiler may add padding for alignment
 * - Bit arrays: 8x more space-efficient than bool arrays
 * 
 * CPU OVERHEAD:
 * - Single bit operations: 1-3 cycles (and, or, xor, shift)
 * - Multi-bit fields: 3-6 cycles (mask, shift, combine)
 * - Much faster than function calls or conditionals
 * 
 * COMPILATION:
 * gcc -O2 bit_manipulation.c -o bit_demo
 * gcc -S -O2 bit_manipulation.c  # View optimized assembly
 * 
 * AUTHOR: C/C++ Learning Repository
 * DATE: January 2026
 * ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* ============================================================================
 * PART 1: Fundamental Bit Operations
 * ============================================================================
 */

/**
 * Set bit n to 1
 * 
 * Pattern: register |= (1 << n)
 * 
 * Example: 0b00000000 -> 0b00100000 (set bit 5)
 * 
 * CPU: 2 instructions (shift, or)
 * ~2-3 cycles on ARM Cortex-M
 */
void bit_set(uint32_t* reg, uint8_t bit_pos) {
    *reg |= (1U << bit_pos);
    
    // Why (1U << bit_pos)?
    // - 1U: unsigned to avoid sign extension issues
    // - <<: left shift = multiply by 2^bit_pos
    // - |=: OR preserves other bits
}

/**
 * Clear bit n to 0
 * 
 * Pattern: register &= ~(1 << n)
 * 
 * Example: 0b11111111 -> 0b11011111 (clear bit 5)
 * 
 * CPU: 3 instructions (shift, not, and)
 * ~3-4 cycles on ARM Cortex-M
 */
void bit_clear(uint32_t* reg, uint8_t bit_pos) {
    *reg &= ~(1U << bit_pos);
    
    // Explanation:
    // 1. (1U << bit_pos)  creates mask: 0b00100000
    // 2. ~(...)            inverts mask: 0b11011111
    // 3. &=                clears bit, preserves others
}

/**
 * Toggle bit n (0->1 or 1->0)
 * 
 * Pattern: register ^= (1 << n)
 * 
 * Example: 0b00100000 -> 0b00000000 (toggle bit 5)
 *          0b00000000 -> 0b00100000 (toggle again)
 * 
 * CPU: 2 instructions (shift, xor)
 * Useful for LED blinking, flag toggling
 */
void bit_toggle(uint32_t* reg, uint8_t bit_pos) {
    *reg ^= (1U << bit_pos);
    
    // XOR truth table:
    // 0 ^ 1 = 1 (set)
    // 1 ^ 1 = 0 (clear)
}

/**
 * Test if bit n is set
 * 
 * Pattern: (register & (1 << n)) != 0
 * 
 * Returns: true if bit is 1, false if 0
 * 
 * CPU: 2 instructions + compare
 * Used for button input, flag checking
 */
bool bit_test(uint32_t reg, uint8_t bit_pos) {
    return (reg & (1U << bit_pos)) != 0;
    
    // Alternative compact form:
    // return !!(reg & (1U << bit_pos));
    // The !! converts any non-zero to 1
}

/**
 * Read bit value (0 or 1)
 * 
 * Returns: 0 or 1, not just true/false
 * Useful when you need the actual bit value
 */
uint8_t bit_read(uint32_t reg, uint8_t bit_pos) {
    return (reg >> bit_pos) & 1U;
    
    // Steps:
    // 1. Shift bit to position 0
    // 2. Mask off all other bits
}

/**
 * Write bit value (0 or 1)
 * 
 * Sets bit if value is 1, clears if value is 0
 * More flexible than set/clear when value is variable
 */
void bit_write(uint32_t* reg, uint8_t bit_pos, bool value) {
    if (value) {
        *reg |= (1U << bit_pos);   // Set
    } else {
        *reg &= ~(1U << bit_pos);  // Clear
    }
    
    // Branchless version (faster on some CPUs):
    // *reg = (*reg & ~(1U << bit_pos)) | ((uint32_t)value << bit_pos);
}

/* ============================================================================
 * PART 2: Multi-Bit Field Operations
 * ============================================================================
 */

/**
 * Read multi-bit field from register
 * 
 * Example: Extract bits 8-11 (4 bits) from register
 * 
 * @param reg       Register value
 * @param start_bit Starting bit position (LSB of field)
 * @param num_bits  Number of bits in field
 * @return          Field value (right-justified)
 * 
 * CPU: ~4-5 cycles (shift, mask)
 */
uint32_t field_read(uint32_t reg, uint8_t start_bit, uint8_t num_bits) {
    // Create mask: (1 << num_bits) - 1
    // For 4 bits: (1 << 4) - 1 = 16 - 1 = 15 = 0b1111
    uint32_t mask = (1U << num_bits) - 1;
    
    // Shift field to LSB position and mask
    return (reg >> start_bit) & mask;
}

/**
 * Write multi-bit field to register
 * 
 * Example: Write value 0b1010 to bits 8-11
 * Preserves all other bits in the register
 * 
 * CPU: ~6-7 cycles (shifts, mask, combine)
 */
void field_write(uint32_t* reg, uint8_t start_bit, uint8_t num_bits, uint32_t value) {
    uint32_t mask = (1U << num_bits) - 1;
    
    // Clear the field
    *reg &= ~(mask << start_bit);
    
    // Set the new value (mask value to prevent overflow)
    *reg |= ((value & mask) << start_bit);
}

/**
 * Modify field with read-modify-write
 * 
 * Common pattern in embedded: read register, modify field, write back
 * This function does it atomically
 */
void field_modify(volatile uint32_t* reg, uint8_t start_bit, uint8_t num_bits, uint32_t value) {
    uint32_t mask = (1U << num_bits) - 1;
    uint32_t temp = *reg;                           // Read
    temp &= ~(mask << start_bit);                   // Clear field
    temp |= ((value & mask) << start_bit);          // Set new value
    *reg = temp;                                    // Write
    
    // Note: Still not truly atomic on multi-core!
    // Would need mutex or hardware atomic operations
}

/* ============================================================================
 * PART 3: Real-World GPIO Example (STM32 Style)
 * ============================================================================
 */

// Simulated STM32 GPIO registers
typedef struct {
    volatile uint32_t MODER;    // Mode register (2 bits per pin)
    volatile uint32_t OTYPER;   // Output type (1 bit per pin)
    volatile uint32_t OSPEEDR;  // Speed register (2 bits per pin)
    volatile uint32_t PUPDR;    // Pull-up/pull-down (2 bits per pin)
    volatile uint32_t IDR;      // Input data register
    volatile uint32_t ODR;      // Output data register
    volatile uint32_t BSRR;     // Bit set/reset register
    volatile uint32_t LCKR;     // Lock register
} GPIO_TypeDef;

// GPIO modes (for MODER field)
#define GPIO_MODE_INPUT     0b00
#define GPIO_MODE_OUTPUT    0b01
#define GPIO_MODE_ALTERNATE 0b10
#define GPIO_MODE_ANALOG    0b11

// GPIO output types
#define GPIO_OTYPE_PUSHPULL  0
#define GPIO_OTYPE_OPENDRAIN 1

// GPIO speeds
#define GPIO_SPEED_LOW      0b00
#define GPIO_SPEED_MEDIUM   0b01
#define GPIO_SPEED_HIGH     0b10
#define GPIO_SPEED_VERYHIGH 0b11

/**
 * Configure GPIO pin as output
 * 
 * Demonstrates multi-bit field modification on real hardware
 * 
 * Memory: Accesses hardware registers via memory-mapped I/O
 * CPU: ~10-15 cycles total (read-modify-write on 3 registers)
 */
void gpio_configure_output(GPIO_TypeDef* gpio, uint8_t pin) {
    // Configure mode: 2-bit field per pin
    uint32_t moder = gpio->MODER;
    moder &= ~(0x3U << (pin * 2));              // Clear 2 bits
    moder |= (GPIO_MODE_OUTPUT << (pin * 2));   // Set as output
    gpio->MODER = moder;
    
    // Configure output type: 1-bit field per pin
    gpio->OTYPER &= ~(1U << pin);               // Clear bit (push-pull)
    
    // Configure speed: 2-bit field per pin
    uint32_t ospeedr = gpio->OSPEEDR;
    ospeedr &= ~(0x3U << (pin * 2));
    ospeedr |= (GPIO_SPEED_HIGH << (pin * 2));
    gpio->OSPEEDR = ospeedr;
}

/**
 * Set GPIO pin HIGH (efficient method)
 * 
 * Uses BSRR register: write-only, atomic set/reset
 * Lower 16 bits: set pins, Upper 16 bits: reset pins
 * 
 * CPU: 1 store instruction (~2-4 cycles)
 * Better than read-modify-write on ODR
 */
void gpio_set_pin(GPIO_TypeDef* gpio, uint8_t pin) {
    gpio->BSRR = (1U << pin);  // Set bit in lower half
    
    // Why BSRR instead of ODR |= (1 << pin)?
    // 1. Atomic operation (no read-modify-write race)
    // 2. Single instruction (faster)
    // 3. No need to disable interrupts
}

/**
 * Set GPIO pin LOW (efficient method)
 */
void gpio_reset_pin(GPIO_TypeDef* gpio, uint8_t pin) {
    gpio->BSRR = (1U << (pin + 16));  // Set bit in upper half
    
    // Upper 16 bits reset corresponding pins
    // Pin 5 reset: BSRR = (1 << 21) = 0x00200000
}

/**
 * Toggle GPIO pin using ODR
 * 
 * Note: Not atomic! Could race with interrupts
 * Better: Use dedicated toggle register if available
 */
void gpio_toggle_pin(GPIO_TypeDef* gpio, uint8_t pin) {
    gpio->ODR ^= (1U << pin);
}

/**
 * Read GPIO pin state
 */
bool gpio_read_pin(GPIO_TypeDef* gpio, uint8_t pin) {
    return (gpio->IDR & (1U << pin)) != 0;
}

/* ============================================================================
 * PART 4: Bit Fields in Structures
 * ============================================================================
 */

/**
 * Bit fields allow packing multiple flags in one byte/word
 * 
 * Pros:
 * - Space efficient (8 bools = 8 bytes, 8 bit fields = 1 byte)
 * - Clear syntax (field.enabled instead of masking)
 * 
 * Cons:
 * - Not addressable (can't take pointer to bit field)
 * - Padding/alignment can negate space savings
 * - Bit order implementation-defined
 * - Slower than direct bit operations (compiler generates mask/shift code)
 */

// Example: Configuration flags (8 bits total)
typedef struct {
    uint8_t enabled:1;      // Bit 0
    uint8_t autostart:1;    // Bit 1
    uint8_t verbose:1;      // Bit 2
    uint8_t reserved:5;     // Bits 3-7 (reserved for future)
} ConfigFlags;

// Same thing using explicit bits (more control)
typedef struct {
    uint8_t flags;
} ConfigFlagsExplicit;

#define CONFIG_ENABLED    (1 << 0)
#define CONFIG_AUTOSTART  (1 << 1)
#define CONFIG_VERBOSE    (1 << 2)

void compare_bitfield_styles(void) {
    // Style 1: Bit fields
    ConfigFlags cfg1 = {0};
    cfg1.enabled = 1;
    cfg1.verbose = 1;
    printf("Bit field size: %zu bytes\n", sizeof(cfg1));
    
    // Style 2: Explicit bits (more common in embedded)
    ConfigFlagsExplicit cfg2 = {0};
    cfg2.flags |= CONFIG_ENABLED | CONFIG_VERBOSE;
    printf("Explicit bits size: %zu bytes\n", sizeof(cfg2));
    
    // Recommendation for embedded: Use explicit bits
    // - More portable
    // - Clearer what's happening at hardware level
    // - Easier to map to register diagrams
}

/* ============================================================================
 * PART 5: Advanced Patterns
 * ============================================================================
 */

/**
 * Count number of set bits (population count)
 * 
 * Useful for: checking how many interrupts pending, data validation
 * 
 * CPU: O(number of set bits) - Brian Kernighan's algorithm
 * Modern CPUs have __builtin_popcount() that uses dedicated instruction
 */
uint32_t count_set_bits(uint32_t n) {
    uint32_t count = 0;
    while (n) {
        n &= (n - 1);  // Clear least significant set bit
        count++;
    }
    return count;
    
    // Example: n = 0b10110
    // Iteration 1: n &= 0b10101 -> n = 0b10100, count = 1
    // Iteration 2: n &= 0b10011 -> n = 0b10000, count = 2
    // Iteration 3: n &= 0b01111 -> n = 0b00000, count = 3
}

/**
 * Find first set bit (count trailing zeros)
 * 
 * Useful for: interrupt priority resolution, bitboard games
 * 
 * Returns: position of first set bit (0-31), or 32 if no bits set
 */
uint32_t find_first_set(uint32_t n) {
    if (n == 0) return 32;
    
    // Isolate lowest set bit
    uint32_t isolated = n & (~n + 1);
    
    // Count trailing zeros (log2 of isolated bit)
    uint32_t pos = 0;
    while (isolated > 1) {
        isolated >>= 1;
        pos++;
    }
    return pos;
    
    // Modern: __builtin_ctz(n) for "count trailing zeros"
}

/**
 * Reverse bits in a 32-bit word
 * 
 * Useful for: protocols with LSB-first bit order, CRC calculations
 */
uint32_t reverse_bits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result <<= 1;              // Make room for next bit
        result |= (n & 1);         // Copy LSB
        n >>= 1;                   // Move to next bit
    }
    return result;
}

/**
 * Check if number is power of 2
 * 
 * Useful for: validating buffer sizes, alignment checks
 * 
 * Trick: Powers of 2 have exactly one bit set
 * Example: 8 = 0b1000, 8-1 = 0b0111, 8 & 7 = 0
 */
bool is_power_of_2(uint32_t n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

/**
 * Align value up to next power of 2
 * 
 * Used for: memory allocation, DMA buffer alignment
 */
uint32_t align_up(uint32_t value, uint32_t alignment) {
    // Alignment must be power of 2
    if (!is_power_of_2(alignment)) return value;
    
    return (value + alignment - 1) & ~(alignment - 1);
    
    // Example: align_up(13, 8)
    // = (13 + 7) & ~7
    // = 20 & 0xFFFFFFF8
    // = 16
}

/* ============================================================================
 * PART 6: Endianness Handling
 * ============================================================================
 */

/**
 * Swap bytes in 16-bit value
 * 
 * Converts between big-endian and little-endian
 * Example: 0x1234 <-> 0x3412
 */
uint16_t swap_bytes_16(uint16_t value) {
    return (value >> 8) | (value << 8);
}

/**
 * Swap bytes in 32-bit value
 * 
 * Example: 0x12345678 <-> 0x78563412
 */
uint32_t swap_bytes_32(uint32_t value) {
    return ((value >> 24) & 0xFF) |
           ((value >> 8)  & 0xFF00) |
           ((value << 8)  & 0xFF0000) |
           ((value << 24) & 0xFF000000);
}

/* ============================================================================
 * MAIN: Demonstration
 * ============================================================================
 */

int main(void) {
    printf("=================================================\n");
    printf("  Bit Manipulation for Embedded Systems\n");
    printf("=================================================\n\n");
    
    // Part 1: Basic operations
    printf("--- Part 1: Basic Bit Operations ---\n");
    uint32_t reg = 0x00;
    
    bit_set(&reg, 5);
    printf("After set bit 5:   0x%08X (0b", reg);
    for (int i = 7; i >= 0; i--) printf("%d", (reg >> i) & 1);
    printf(")\n");
    
    bit_set(&reg, 0);
    bit_set(&reg, 7);
    printf("After set 0 & 7:   0x%08X (0b", reg);
    for (int i = 7; i >= 0; i--) printf("%d", (reg >> i) & 1);
    printf(")\n");
    
    bit_clear(&reg, 5);
    printf("After clear bit 5: 0x%08X (0b", reg);
    for (int i = 7; i >= 0; i--) printf("%d", (reg >> i) & 1);
    printf(")\n");
    
    bit_toggle(&reg, 0);
    printf("After toggle bit 0: 0x%08X (0b", reg);
    for (int i = 7; i >= 0; i--) printf("%d", (reg >> i) & 1);
    printf(")\n");
    
    printf("Is bit 7 set? %s\n", bit_test(reg, 7) ? "Yes" : "No");
    printf("Is bit 5 set? %s\n", bit_test(reg, 5) ? "Yes" : "No");
    
    printf("\n");
    
    // Part 2: Multi-bit fields
    printf("--- Part 2: Multi-Bit Fields ---\n");
    uint32_t config = 0x12345678;
    printf("Original register: 0x%08X\n", config);
    
    uint32_t field = field_read(config, 8, 4);
    printf("Bits 8-11 value: 0x%X\n", field);
    
    field_write(&config, 8, 4, 0xA);
    printf("After writing 0xA to bits 8-11: 0x%08X\n", config);
    
    printf("\n");
    
    // Part 3: Advanced patterns
    printf("--- Part 3: Advanced Patterns ---\n");
    uint32_t test = 0b10110110;
    printf("Number: 0b%s\n", "10110110");
    printf("Set bits: %u\n", count_set_bits(test));
    printf("First set bit position: %u\n", find_first_set(test));
    
    printf("\nPower of 2 tests:\n");
    printf("8 is power of 2: %s\n", is_power_of_2(8) ? "Yes" : "No");
    printf("10 is power of 2: %s\n", is_power_of_2(10) ? "Yes" : "No");
    
    printf("\nAlignment:\n");
    printf("align_up(13, 8) = %u\n", align_up(13, 8));
    printf("align_up(16, 8) = %u\n", align_up(16, 8));
    printf("align_up(17, 8) = %u\n", align_up(17, 8));
    
    printf("\n");
    
    // Part 4: Endianness
    printf("--- Part 4: Endianness ---\n");
    uint16_t val16 = 0x1234;
    printf("Original: 0x%04X\n", val16);
    printf("Swapped:  0x%04X\n", swap_bytes_16(val16));
    
    uint32_t val32 = 0x12345678;
    printf("Original: 0x%08X\n", val32);
    printf("Swapped:  0x%08X\n", swap_bytes_32(val32));
    
    printf("\n=================================================\n");
    printf("Key Takeaways:\n");
    printf("1. Master: set, clear, toggle, test\n");
    printf("2. Read-modify-write for multi-bit fields\n");
    printf("3. Use BSRR-style registers for atomic operations\n");
    printf("4. Prefer explicit bits over bit fields in structs\n");
    printf("5. Know your endianness for network protocols\n");
    printf("=================================================\n");
    
    return 0;
}

/* ============================================================================
 * PERFORMANCE NOTES:
 * ============================================================================
 * 
 * On ARM Cortex-M4 (typical embedded CPU):
 * 
 * Operation          | Cycles | Instructions
 * -------------------|--------|-------------
 * Set bit            | 2-3    | LSL, ORR
 * Clear bit          | 3-4    | LSL, MVN, AND
 * Toggle bit         | 2-3    | LSL, EOR
 * Test bit           | 2-3    | LSL, TST
 * Field read         | 4-5    | LSR, AND
 * Field write        | 6-8    | BIC, LSL, ORR
 * 
 * Compare to function call: ~8-12 cycles (push, branch, pop)
 * Conclusion: Inline bit operations, don't wrap in functions
 * 
 * Modern compilers will inline these if declared with 'inline' or in headers.
 * 
 * ============================================================================
 */
