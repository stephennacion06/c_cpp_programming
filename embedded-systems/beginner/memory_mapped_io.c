/**
 * ============================================================================
 * Memory-Mapped I/O (MMIO) in Embedded Systems
 * ============================================================================
 * 
 * PURPOSE:
 * Demonstrates how software controls hardware by reading/writing memory
 * addresses that correspond to peripheral registers rather than RAM.
 * 
 * CONCEPT:
 * In embedded systems, hardware peripherals (GPIO, UART, SPI, ADC, etc.) are
 * controlled through "registers" that appear at fixed memory addresses.
 * Reading/writing these addresses directly manipulates hardware behavior.
 * 
 * MEMORY IMPLICATIONS:
 * - Register addresses are fixed in hardware (defined in datasheet)
 * - Registers are NOT in RAM - they're inside the peripheral
 * - Size varies: 8-bit, 16-bit, or 32-bit registers common
 * - No malloc/free - addresses are compile-time constants
 * 
 * CPU OVERHEAD:
 * - Bus access: 1-10 cycles depending on bus speed and peripheral location
 * - AHB bus (fast): ~1-2 cycles
 * - APB bus (slow): ~2-10 cycles
 * - Must use volatile to prevent compiler caching
 * 
 * COMPILATION:
 * gcc -O2 memory_mapped_io.c -o mmio_demo
 * 
 * NOTE: This code demonstrates concepts but won't control actual hardware
 *       without running on real embedded hardware (ARM Cortex-M, etc.)
 * 
 * AUTHOR: C/C++ Learning Repository
 * DATE: January 2026
 * ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* ============================================================================
 * PART 1: Understanding Memory-Mapped I/O
 * ============================================================================
 */

/**
 * Memory Map Concept:
 * 
 * Typical ARM Cortex-M4 Memory Map:
 * 
 * 0x00000000 - 0x1FFFFFFF: Flash memory (code, constants)
 * 0x20000000 - 0x3FFFFFFF: SRAM (variables, stack, heap)
 * 0x40000000 - 0x5FFFFFFF: Peripherals (GPIO, UART, SPI, etc.) <- MMIO!
 * 0xE0000000 - 0xE00FFFFF: ARM Cortex-M core peripherals
 * 
 * When you write to 0x40020014, you're NOT writing to RAM.
 * You're triggering hardware logic in the GPIO peripheral!
 */

/* ============================================================================
 * PART 2: STM32F4 GPIO Example (Real Hardware)
 * ============================================================================
 * 
 * STM32F4 has 9 GPIO ports (A-I), each with 16 pins.
 * Each port has these registers:
 */

// Base address for GPIO Port A (from STM32F4 reference manual)
#define GPIOA_BASE      0x40020000UL

// Register offsets (from base address)
#define GPIO_MODER_OFFSET   0x00    // Mode register
#define GPIO_OTYPER_OFFSET  0x04    // Output type register
#define GPIO_OSPEEDR_OFFSET 0x08    // Output speed register
#define GPIO_PUPDR_OFFSET   0x0C    // Pull-up/pull-down register
#define GPIO_IDR_OFFSET     0x10    // Input data register
#define GPIO_ODR_OFFSET     0x14    // Output data register
#define GPIO_BSRR_OFFSET    0x18    // Bit set/reset register
#define GPIO_LCKR_OFFSET    0x1C    // Configuration lock register
#define GPIO_AFRL_OFFSET    0x20    // Alternate function low register
#define GPIO_AFRH_OFFSET    0x24    // Alternate function high register

/**
 * Method 1: Direct pointer dereference
 * 
 * Most explicit but verbose
 */
#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + GPIO_MODER_OFFSET))
#define GPIOA_OTYPER    (*(volatile uint32_t*)(GPIOA_BASE + GPIO_OTYPER_OFFSET))
#define GPIOA_OSPEEDR   (*(volatile uint32_t*)(GPIOA_BASE + GPIO_OSPEEDR_OFFSET))
#define GPIOA_PUPDR     (*(volatile uint32_t*)(GPIOA_BASE + GPIO_PUPDR_OFFSET))
#define GPIOA_IDR       (*(volatile uint32_t*)(GPIOA_BASE + GPIO_IDR_OFFSET))
#define GPIOA_ODR       (*(volatile uint32_t*)(GPIOA_BASE + GPIO_ODR_OFFSET))
#define GPIOA_BSRR      (*(volatile uint32_t*)(GPIOA_BASE + GPIO_BSRR_OFFSET))

/**
 * Method 2: Structure overlay (cleaner, type-safe)
 * 
 * Preferred method in production code
 */
typedef struct {
    volatile uint32_t MODER;    // 0x00: Mode register
    volatile uint32_t OTYPER;   // 0x04: Output type register
    volatile uint32_t OSPEEDR;  // 0x08: Speed register
    volatile uint32_t PUPDR;    // 0x0C: Pull-up/pull-down
    volatile uint32_t IDR;      // 0x10: Input data register (read-only)
    volatile uint32_t ODR;      // 0x14: Output data register
    volatile uint32_t BSRR;     // 0x18: Bit set/reset (write-only)
    volatile uint32_t LCKR;     // 0x1C: Lock register
    volatile uint32_t AFRL;     // 0x20: Alt function low
    volatile uint32_t AFRH;     // 0x24: Alt function high
} GPIO_TypeDef;

// Define pointer to GPIO Port A structure
#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef*)0x40020400)  // Port B is at BASE + 0x400
#define GPIOC ((GPIO_TypeDef*)0x40020800)  // Port C is at BASE + 0x800

// GPIO Configuration Constants
#define GPIO_MODE_INPUT     0x00
#define GPIO_MODE_OUTPUT    0x01
#define GPIO_MODE_AF        0x02  // Alternate function
#define GPIO_MODE_ANALOG    0x03

#define GPIO_OTYPE_PP       0x00  // Push-pull
#define GPIO_OTYPE_OD       0x01  // Open-drain

#define GPIO_SPEED_LOW      0x00
#define GPIO_SPEED_MEDIUM   0x01
#define GPIO_SPEED_HIGH     0x02
#define GPIO_SPEED_VERYHIGH 0x03

#define GPIO_PUPD_NONE      0x00
#define GPIO_PUPD_PULLUP    0x01
#define GPIO_PUPD_PULLDOWN  0x02

/* ============================================================================
 * PART 3: GPIO Control Functions
 * ============================================================================
 */

/**
 * Configure a GPIO pin as output
 * 
 * @param gpio Pointer to GPIO port (GPIOA, GPIOB, etc.)
 * @param pin  Pin number (0-15)
 * 
 * Memory: Modifies 4 hardware registers
 * CPU: ~20-30 cycles total (4 read-modify-write operations)
 * 
 * WHY THIS MATTERS:
 * - Each register access goes to hardware, not cached
 * - Order matters: configure mode before using pin
 * - Atomic operations at bit level (other pins unaffected)
 */
void gpio_init_output(GPIO_TypeDef* gpio, uint8_t pin) {
    // 1. Configure pin mode (2 bits per pin)
    uint32_t mode = gpio->MODER;
    mode &= ~(0x3U << (pin * 2));            // Clear 2 bits
    mode |= (GPIO_MODE_OUTPUT << (pin * 2)); // Set as output
    gpio->MODER = mode;
    
    // 2. Configure output type (1 bit per pin)
    gpio->OTYPER &= ~(1U << pin);            // Push-pull (0)
    
    // 3. Configure speed (2 bits per pin)
    uint32_t speed = gpio->OSPEEDR;
    speed &= ~(0x3U << (pin * 2));
    speed |= (GPIO_SPEED_HIGH << (pin * 2));
    gpio->OSPEEDR = speed;
    
    // 4. Configure pull-up/pull-down (2 bits per pin)
    uint32_t pupd = gpio->PUPDR;
    pupd &= ~(0x3U << (pin * 2));
    pupd |= (GPIO_PUPD_NONE << (pin * 2));
    gpio->PUPDR = pupd;
}

/**
 * Configure a GPIO pin as input
 * 
 * Similar to output but sets mode differently
 */
void gpio_init_input(GPIO_TypeDef* gpio, uint8_t pin, bool pullup) {
    // Configure mode as input
    uint32_t mode = gpio->MODER;
    mode &= ~(0x3U << (pin * 2));            // Input = 00
    gpio->MODER = mode;
    
    // Configure pull resistor
    uint32_t pupd = gpio->PUPDR;
    pupd &= ~(0x3U << (pin * 2));
    if (pullup) {
        pupd |= (GPIO_PUPD_PULLUP << (pin * 2));
    }
    gpio->PUPDR = pupd;
}

/**
 * Set GPIO pin HIGH (Method 1: Using ODR)
 * 
 * CPU: ~5-8 cycles (read-modify-write)
 * Issue: Not atomic - can race with interrupts
 */
void gpio_set_odr(GPIO_TypeDef* gpio, uint8_t pin) {
    gpio->ODR |= (1U << pin);
    
    // Problem: This expands to:
    // 1. Read current ODR value
    // 2. OR with bit mask
    // 3. Write back to ODR
    // If interrupt modifies ODR between 1 and 3, change is lost!
}

/**
 * Set GPIO pin HIGH (Method 2: Using BSRR - RECOMMENDED)
 * 
 * CPU: ~2-4 cycles (single write)
 * Advantage: Atomic operation, no read-modify-write
 * 
 * BSRR register layout:
 * Bits 0-15:  Set bits (write 1 to set corresponding ODR bit)
 * Bits 16-31: Reset bits (write 1 to clear corresponding ODR bit)
 * 
 * Example: BSRR = 0x00000020 sets pin 5 HIGH
 *          BSRR = 0x00200000 sets pin 5 LOW
 */
void gpio_set_bsrr(GPIO_TypeDef* gpio, uint8_t pin) {
    gpio->BSRR = (1U << pin);
    
    // Hardware logic does:
    // ODR[pin] = 1
    // No read required - single write!
}

/**
 * Clear GPIO pin (set LOW)
 */
void gpio_clear(GPIO_TypeDef* gpio, uint8_t pin) {
    gpio->BSRR = (1U << (pin + 16));  // Write to upper half
}

/**
 * Toggle GPIO pin
 * 
 * Note: Uses ODR, so not atomic
 * Some MCUs have dedicated toggle register (not STM32)
 */
void gpio_toggle(GPIO_TypeDef* gpio, uint8_t pin) {
    gpio->ODR ^= (1U << pin);
}

/**
 * Read GPIO pin state
 * 
 * CPU: ~2-4 cycles (single read)
 * Returns: true if pin is HIGH, false if LOW
 */
bool gpio_read(GPIO_TypeDef* gpio, uint8_t pin) {
    return (gpio->IDR & (1U << pin)) != 0;
    
    // IDR is read-only: reflects actual pin voltage
    // ODR is write/read: reflects what you wrote (not actual pin state!)
    // Always read IDR for input, even on output pins (read-back)
}

/* ============================================================================
 * PART 4: Real-World Example - LED Blink
 * ============================================================================
 */

/**
 * Simple delay (blocking, not precise)
 * 
 * In real code: use timer peripheral for accurate delays
 */
void delay_ms(uint32_t ms) {
    // Assuming 168 MHz CPU, ~168 cycles per microsecond
    // This is crude and compiler-dependent!
    for (volatile uint32_t i = 0; i < ms * 168000 / 4; i++) {
        // Empty loop
    }
}

/**
 * Blink LED on PA5 (common LED pin on STM32 boards)
 * 
 * Prerequisites:
 * 1. Clock must be enabled for GPIOA (via RCC register)
 * 2. Pin must be configured as output
 */
void blink_led_example(void) {
    printf("Blinking LED on GPIOA Pin 5...\n");
    
    // Initialize PA5 as output
    gpio_init_output(GPIOA, 5);
    
    // Blink 10 times
    for (int i = 0; i < 10; i++) {
        gpio_set_bsrr(GPIOA, 5);   // LED ON
        delay_ms(500);
        gpio_clear(GPIOA, 5);      // LED OFF
        delay_ms(500);
        
        printf("Blink %d\n", i + 1);
    }
}

/* ============================================================================
 * PART 5: Button Input Example
 * ============================================================================
 */

/**
 * Read button with debouncing
 * 
 * Hardware: Button on PC13 (common on STM32 Nucleo boards)
 * Connection: Button pulls pin LOW when pressed (needs pull-up)
 * 
 * CPU: ~10-15 cycles per read
 * Memory: 0 bytes (uses stack for locals)
 */
bool button_read_debounced(GPIO_TypeDef* gpio, uint8_t pin) {
    // Read pin twice with small delay
    bool state1 = gpio_read(gpio, pin);
    delay_ms(10);  // 10ms debounce delay
    bool state2 = gpio_read(gpio, pin);
    
    // Return true only if both reads agree
    return state1 && state2;
}

/**
 * Wait for button press
 * 
 * Blocks until button is pressed (LOW on STM32 boards)
 */
void wait_for_button(void) {
    printf("Waiting for button press (PC13)...\n");
    
    // Configure PC13 as input with pull-up
    gpio_init_input(GPIOC, 13, true);
    
    // Wait for LOW (button pressed)
    while (gpio_read(GPIOC, 13)) {
        // Spin-wait (inefficient - use interrupt in real code)
    }
    
    // Debounce
    delay_ms(50);
    
    // Wait for release (HIGH)
    while (!gpio_read(GPIOC, 13)) {
        // Wait
    }
    
    printf("Button pressed and released!\n");
}

/* ============================================================================
 * PART 6: Register Dump (Debugging Aid)
 * ============================================================================
 */

/**
 * Print all GPIO register values
 * 
 * Useful for debugging: see actual hardware state
 */
void gpio_dump_registers(GPIO_TypeDef* gpio, const char* port_name) {
    printf("\n=== %s Register Dump ===\n", port_name);
    printf("MODER:   0x%08X\n", gpio->MODER);
    printf("OTYPER:  0x%08X\n", gpio->OTYPER);
    printf("OSPEEDR: 0x%08X\n", gpio->OSPEEDR);
    printf("PUPDR:   0x%08X\n", gpio->PUPDR);
    printf("IDR:     0x%08X\n", gpio->IDR);
    printf("ODR:     0x%08X\n", gpio->ODR);
    printf("BSRR:    0x%08X\n", gpio->BSRR);
    printf("LCKR:    0x%08X\n", gpio->LCKR);
    printf("AFRL:    0x%08X\n", gpio->AFRL);
    printf("AFRH:    0x%08X\n", gpio->AFRH);
    printf("==========================\n\n");
}

/* ============================================================================
 * PART 7: Clock Enable (RCC Register)
 * ============================================================================
 */

/**
 * Before using any peripheral, you must enable its clock!
 * 
 * RCC (Reset and Clock Control) manages peripheral clocks
 * This saves power - disabled peripherals use no energy
 */

#define RCC_BASE        0x40023800UL
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30))

// Bit positions in RCC_AHB1ENR for GPIO clock enable
#define RCC_AHB1ENR_GPIOAEN  (1 << 0)
#define RCC_AHB1ENR_GPIOBEN  (1 << 1)
#define RCC_AHB1ENR_GPIOCEN  (1 << 2)

/**
 * Enable clock for GPIO port
 * 
 * MUST be called before using GPIO!
 * CPU: ~2-4 cycles (single write)
 */
void gpio_enable_clock(GPIO_TypeDef* gpio) {
    if (gpio == GPIOA) {
        RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    } else if (gpio == GPIOB) {
        RCC_AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    } else if (gpio == GPIOC) {
        RCC_AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    }
    
    // Small delay for clock to stabilize
    volatile uint32_t dummy = RCC_AHB1ENR;
    (void)dummy;  // Prevent compiler warning
}

/* ============================================================================
 * MAIN: Demonstration
 * ============================================================================
 */

int main(void) {
    printf("=================================================\n");
    printf("  Memory-Mapped I/O in Embedded Systems\n");
    printf("=================================================\n\n");
    
    printf("This program demonstrates MMIO concepts.\n");
    printf("To run on actual hardware:\n");
    printf("1. Compile for ARM: arm-none-eabi-gcc -mcpu=cortex-m4\n");
    printf("2. Flash to STM32 board\n");
    printf("3. Connect LED to PA5\n");
    printf("4. Connect button to PC13\n\n");
    
    // Demonstrate register addresses
    printf("--- Register Addresses ---\n");
    printf("GPIOA base address: 0x%08lX\n", GPIOA_BASE);
    printf("GPIOA->MODER:       0x%08lX\n", (unsigned long)&GPIOA->MODER);
    printf("GPIOA->ODR:         0x%08lX\n", (unsigned long)&GPIOA->ODR);
    printf("GPIOA->IDR:         0x%08lX\n", (unsigned long)&GPIOA->IDR);
    printf("GPIOA->BSRR:        0x%08lX\n", (unsigned long)&GPIOA->BSRR);
    
    printf("\n--- Structure Size ---\n");
    printf("GPIO_TypeDef size: %zu bytes\n", sizeof(GPIO_TypeDef));
    printf("Each register is 4 bytes (uint32_t)\n");
    
    printf("\n=================================================\n");
    printf("Key Takeaways:\n");
    printf("1. Peripherals live at fixed memory addresses\n");
    printf("2. Use volatile pointers to prevent caching\n");
    printf("3. Structure overlays provide clean syntax\n");
    printf("4. BSRR register enables atomic bit operations\n");
    printf("5. Always enable peripheral clock before use\n");
    printf("6. Read datasheet for exact register layouts\n");
    printf("=================================================\n");
    
    return 0;
}

/* ============================================================================
 * REAL HARDWARE NOTES:
 * ============================================================================
 * 
 * To actually run this on STM32:
 * 
 * 1. Enable clocks first:
 *    gpio_enable_clock(GPIOA);
 * 
 * 2. Configure pin:
 *    gpio_init_output(GPIOA, 5);
 * 
 * 3. Control pin:
 *    gpio_set_bsrr(GPIOA, 5);   // HIGH
 *    delay_ms(1000);
 *    gpio_clear(GPIOA, 5);       // LOW
 * 
 * 4. Read input:
 *    if (gpio_read(GPIOC, 13)) {
 *        // Button not pressed
 *    }
 * 
 * IMPORTANT: This code is educational. Production code should:
 * - Use vendor HAL/LL libraries (STM32CubeMX)
 * - Handle errors (clock enable failures)
 * - Use proper delays (timer-based, not loops)
 * - Employ interrupts instead of polling
 * - Consider power management (sleep modes)
 * 
 * ============================================================================
 * DEBUGGING TIPS:
 * ============================================================================
 * 
 * Problem: Pin doesn't change
 * - Check clock is enabled (RCC register)
 * - Verify pin mode in MODER register
 * - Check if pin is locked (LCKR register)
 * - Use gpio_dump_registers() to see state
 * 
 * Problem: Reads always return 0
 * - Reading ODR instead of IDR?
 * - Clock not enabled?
 * - Pin configured as output?
 * 
 * Problem: Intermittent behavior
 * - Missing volatile keyword?
 * - Using ODR instead of BSRR (race condition)?
 * - Insufficient delay for hardware settling?
 * 
 * ============================================================================
 */
