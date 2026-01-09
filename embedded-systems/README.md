# Embedded Systems Programming in C/C++

This section covers embedded systems concepts with a focus on **hardware interaction**, **resource constraints**, and **deterministic behavior**. These patterns apply to microcontrollers (STM32, ESP32, AVR) and real-time systems.

## 🎯 Learning Objectives

By completing this section, you will understand:
- Why certain C language features exist (volatile, inline, restrict)
- How software directly controls hardware (memory-mapped I/O)
- Trade-offs between memory usage and CPU cycles
- Patterns for reliable embedded systems (state machines, circular buffers)

## 📚 Directory Structure

```
embedded-systems/
├── beginner/           # Hardware interaction fundamentals
│   ├── volatile_keyword.c
│   ├── memory_mapped_io.c
│   ├── bit_manipulation.c
│   └── interrupt_concepts.md
├── intermediate/       # Common embedded patterns
│   ├── circular_buffers.c
│   ├── state_machines.c
│   ├── watchdog_patterns.c
│   └── zero_overhead_abstractions.cpp
└── advanced/          # System-level programming
    ├── rtos_concepts/
    ├── dma_patterns.c
    └── cache_coherency.md
```

## 🔰 Beginner Topics

### volatile Keyword
**Why it exists:** Tells the compiler "this memory location can change outside program control" (hardware registers, interrupts, DMA).

**Memory implications:**
- No memory overhead (just a qualifier)
- Prevents compiler optimizations (register caching, reordering)

**CPU overhead:**
- Forces memory access on every read/write (~1-10 cycles vs 0 for cached)
- Critical for correctness with hardware

**Example:**
```c
volatile uint32_t* GPIO_ODR = (volatile uint32_t*)0x40020014;
*GPIO_ODR |= (1 << 5);  // Set pin 5 HIGH - MUST access memory
```

### Memory-Mapped I/O (MMIO)
Hardware registers appear as memory addresses. Writing to these addresses controls peripherals.

**STM32 GPIO example:**
```c
// GPIO Port A Output Data Register at 0x40020014
#define GPIOA_ODR (*(volatile uint32_t*)0x40020014)

// Turn on LED on PA5
GPIOA_ODR |= (1 << 5);
```

### Bit Manipulation
Embedded systems require precise bit-level control for registers, flags, and protocols.

**Common patterns:**
```c
// Set bit n
register |= (1 << n);

// Clear bit n
register &= ~(1 << n);

// Toggle bit n
register ^= (1 << n);

// Test bit n
if (register & (1 << n)) { /* bit is set */ }
```

## 🔄 Intermediate Topics

### Circular Buffers
**Purpose:** Fixed-size FIFO for UART, sensor data, logging without dynamic allocation.

**Memory:** `sizeof(element) * capacity` - known at compile time  
**CPU:** O(1) for enqueue/dequeue

**Why in embedded:**
- No malloc/free (predictable memory)
- No fragmentation
- Deterministic performance

### State Machines
**Purpose:** Event-driven systems, protocol parsing, button debouncing.

**Pattern:**
```c
typedef enum {
    STATE_IDLE,
    STATE_RECEIVING,
    STATE_PROCESSING,
    STATE_ERROR
} SystemState;

void state_machine_update(Event event) {
    switch (current_state) {
        case STATE_IDLE:
            if (event == EVENT_START) {
                current_state = STATE_RECEIVING;
            }
            break;
        // ... transitions
    }
}
```

### Watchdog Timers
**Purpose:** Automatic recovery from software hangs.

**Pattern:** Periodic "kick" proves system is alive. If missed, hardware resets MCU.

## 🚀 Advanced Topics

### RTOS Concepts
- Task scheduling (cooperative vs preemptive)
- Semaphores and mutexes
- Interrupt priorities and nesting
- Stack sizing per task

### DMA (Direct Memory Access)
- Zero-CPU data transfers
- Circular mode for continuous streaming
- Interrupt on completion
- Cache coherency issues

### Cache Coherency
- Data cache vs instruction cache
- Cache line size alignment
- Volatile not enough for multi-core
- Memory barriers and ordering

## 💡 Best Practices

### 1. **Use volatile for Hardware**
```c
// ✅ Correct - compiler MUST read from memory
volatile uint32_t* ADC_DR = (volatile uint32_t*)0x40012040;
uint32_t value = *ADC_DR;

// ❌ Wrong - compiler may optimize away repeated reads
uint32_t* ADC_DR = (uint32_t*)0x40012040;
uint32_t value = *ADC_DR;
```

### 2. **Minimize Interrupt Duration**
```c
// ✅ Correct - set flag, return quickly
void UART_IRQHandler(void) {
    uart_data_ready = 1;  // Signal main loop
}

// ❌ Wrong - blocking I/O in ISR
void UART_IRQHandler(void) {
    process_uart_packet();  // May take milliseconds!
}
```

### 3. **Know Your Stack Usage**
```c
// ❌ Danger - 1KB on stack in ISR
void Timer_IRQHandler(void) {
    char buffer[1024];  // May overflow!
    sprintf(buffer, "...");
}

// ✅ Better - static or heap
static char buffer[1024];  // In .bss, not stack
```

### 4. **Avoid Dynamic Allocation in Critical Code**
```c
// ❌ Risky - malloc can fail, causes fragmentation
void sensor_task(void) {
    float* data = malloc(sizeof(float) * 100);
    // ... what if malloc returns NULL?
}

// ✅ Safer - fixed allocation
#define MAX_SAMPLES 100
static float data[MAX_SAMPLES];
```

## 🔧 Tools for Embedded Development

### Compilation
```bash
# ARM Cortex-M4 compilation
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O2 -g \
    -Wall -Wextra -o firmware.elf main.c

# View disassembly
arm-none-eabi-objdump -d firmware.elf > firmware.asm

# Check memory sections
arm-none-eabi-size firmware.elf
```

### Debugging
- GDB with OpenOCD (on-chip debugging)
- SEGGER J-Link with RTT (real-time transfer)
- Logic analyzers (protocol decoding)
- Oscilloscopes (signal timing)

### Static Analysis
```bash
# Clang-Tidy for embedded
clang-tidy *.c -- -mcpu=cortex-m4

# Cppcheck
cppcheck --enable=all --platform=unix32 .
```

## 📖 Recommended Reading

1. **"Making Embedded Systems" by Elecia White**
   - Practical patterns and architecture

2. **"Embedded C Coding Standard" by Barr Group**
   - Industry best practices

3. **Microcontroller datasheets (e.g., STM32 Reference Manual)**
   - Register-level documentation

4. **ARM Cortex-M Programming Guide**
   - Architecture specifics

## 🎓 Prerequisites

Before diving into embedded systems:
- Solid understanding of C fundamentals (pointers, arrays, structures)
- Basic digital logic (binary, hexadecimal, bitwise operations)
- Comfort reading datasheets and reference manuals

## 🚦 Next Steps

1. Start with **beginner/volatile_keyword.c** - understand why volatile exists
2. Practice **bit manipulation** patterns - core skill for embedded
3. Build a **circular buffer** - appears in 90% of embedded projects
4. Study **state machines** - pattern for complex logic
5. Read your target MCU's datasheet - apply concepts to real hardware

## 🤝 Contributing

When adding examples:
- Target real hardware (STM32, ESP32, AVR)
- Show disassembly with comments
- Document memory and CPU costs
- Include common pitfalls section
- Provide references to datasheets

---

**Remember:** Embedded programming is about **predictability** over flexibility. Every byte and cycle matters when you have 32KB RAM and a 48MHz CPU!
