# Memory Layout Explained: Stack, Heap, and Program Sections

## Introduction

Every C/C++ program's memory is divided into distinct sections, each serving a specific purpose. Understanding this layout is **critical** for embedded systems where memory is scarce and bugs can be catastrophic.

This guide explains:
- What the memory sections are (stack, heap, .text, .data, .bss)
- Why they exist separately
- Performance characteristics of each
- How to analyze memory usage with tools
- Common pitfalls and solutions

## Memory Map Overview

```
High Memory (0xFFFFFFFF)
│
├─────────────────────────┐
│       Stack             │ ← Grows downward
│    (automatic vars)     │   Started from high address
├─────────────────────────┤
│          ↓              │
│      (unused)           │
│          ↑              │
├─────────────────────────┤
│       Heap              │ ← Grows upward
│   (dynamic alloc)       │   malloc/new allocate here
├─────────────────────────┤
│       .bss              │ ← Uninitialized data
│  (zero-initialized)     │   Static/global vars = 0
├─────────────────────────┤
│       .data             │ ← Initialized data
│  (non-zero init vals)   │   Static/global vars with values
├─────────────────────────┤
│       .rodata           │ ← Read-only data
│   (const, strings)      │   String literals, const arrays
├─────────────────────────┤
│       .text             │ ← Code (executable)
│   (instructions)        │   Your compiled functions
└─────────────────────────┘
Low Memory (0x00000000)
```

**Key insight:** Stack and heap grow toward each other. When they meet = **stack overflow** or **heap exhaustion**.

---

## Section-by-Section Analysis

### 1. `.text` Section (Code)

**Contents:** Compiled machine instructions (your functions)

**Properties:**
- Read-only (attempting to write causes segmentation fault)
- Loaded from executable file
- Shared between processes (one copy in RAM for multiple instances)

**Size:** Fixed at compile time

**Example:**
```c
int add(int a, int b) {
    return a + b;  // This function's assembly code lives in .text
}
```

**Assembly view:**
```bash
$ gcc -c example.c
$ objdump -d example.o

00000000 <add>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   8b 45 08                mov    0x8(%ebp),%eax
   6:   03 45 0c                add    0xc(%ebp),%eax
   9:   5d                      pop    %ebp
   a:   c3                      ret
```

**Performance:** Fast (cached by CPU instruction cache)

---

### 2. `.rodata` Section (Read-Only Data)

**Contents:** 
- String literals: `"Hello, world!"`
- `const` global/static variables
- Lookup tables (const arrays)

**Properties:**
- Read-only (write attempt = crash)
- Loaded from executable
- Often placed in flash memory on embedded systems (saves RAM!)

**Example:**
```c
const char* message = "Hello";      // Pointer in .data, string in .rodata
const int lut[] = {0, 1, 4, 9, 16}; // Array in .rodata

void func() {
    const int x = 5;  // x is on STACK (not .rodata!)
}
```

**Memory impact:**
```bash
$ size example.o
   text    data     bss     dec     hex filename
    100      32       8     140      8c example.o
#  ^^^^ .text + .rodata combined
```

**Embedded tip:** Put lookup tables in `.rodata` to save precious RAM:
```c
// ❌ Uses 1KB of RAM
uint8_t sine_table[256] = {0, 3, 6, ...};

// ✅ Uses 1KB of flash, 0 bytes of RAM
const uint8_t sine_table[256] = {0, 3, 6, ...};
```

---

### 3. `.data` Section (Initialized Data)

**Contents:** Global and static variables with **non-zero** initial values

**Properties:**
- Read-write
- Occupies space in both executable file and RAM
- Initialized by loader before `main()` runs

**Example:**
```c
int global_counter = 42;       // .data section (initialized to 42)
static int file_scope = 100;   // .data section

void func() {
    static int call_count = 0; // .data section (even though it's 0!)
                               // Why? Explicit initializer present
}
```

**Size impact:**
- **File size:** Each initialized byte must be stored in executable
- **RAM usage:** Same size at runtime

**Performance:**
- Access time: ~1-10 cycles (depends on cache)
- Initialization cost: Paid once at startup

**View with objdump:**
```bash
$ objdump -s -j .data example.o

Contents of section .data:
 0000 2a000000 64000000 00000000  *...d.......
```

---

### 4. `.bss` Section (Uninitialized Data)

**Contents:** Global and static variables initialized to **zero** (or no initializer)

**Properties:**
- Read-write
- **NOT stored in executable file** (just size recorded)
- Zeroed by loader at startup (one memset call)

**Example:**
```c
int global_array[1000];        // .bss (no initializer = zero)
static char buffer[512];       // .bss
int initialized_zero = 0;      // COMPILER OPTIMIZES TO .bss!

void func() {
    static int counter;        // .bss (no initializer)
}
```

**Critical insight:**
```c
int array1[1000] = {0};        // .bss (all zeros, optimized)
int array2[1000] = {1};        // .data (4000 bytes in executable!)
```

**Size impact:**
- **File size:** 0 bytes (only metadata)
- **RAM usage:** Full size
- **Startup time:** ~1 cycle per byte for zeroing

**View size:**
```bash
$ size example.o
   text    data     bss     dec     hex filename
    100      32    4000    4132    1024 example.o
#                  ^^^^ .bss = 4KB in RAM, 0 bytes in file
```

**Embedded optimization:**
```c
// ❌ Bad: 10KB in flash
uint8_t large_buffer[10240] = {0};

// ✅ Good: 0 bytes in flash, 10KB in RAM
uint8_t large_buffer[10240];
```

---

### 5. Heap

**Contents:** Dynamically allocated memory (`malloc`, `calloc`, `new`)

**Properties:**
- Managed by allocator (typically Doug Lea's malloc)
- Grows upward from end of .bss
- Must be manually freed (`free`, `delete`)
- Prone to fragmentation

**Example:**
```c
int* ptr = malloc(sizeof(int) * 100);  // 400 bytes on heap
// ... use ptr ...
free(ptr);  // MUST free manually
```

**Memory layout:**
```
Heap block structure (simplified):
┌─────────────┬──────────────────┬─────────────┐
│ Header      │ User data        │ Footer      │
│ (size, etc) │ (your 400 bytes) │ (metadata)  │
└─────────────┴──────────────────┴─────────────┘
       8 bytes        400 bytes        8 bytes
       
Actual allocation = 416 bytes (overhead!)
```

**Performance characteristics:**

| Operation | Best Case | Worst Case | Notes |
|-----------|-----------|------------|-------|
| `malloc`  | O(1)      | O(n)       | May traverse free list |
| `free`    | O(1)      | O(n)       | May coalesce adjacent blocks |
| Fragmentation | Low | High | Depends on allocation pattern |

**CPU overhead:**
- `malloc(100)`: ~100-300 cycles (lock, search, split)
- `free(ptr)`: ~50-150 cycles (lock, coalesce, unlock)

**Fragmentation example:**
```c
// Allocation pattern:
char* a = malloc(100);  // [A:100][FREE:...]
char* b = malloc(100);  // [A:100][B:100][FREE:...]
char* c = malloc(100);  // [A:100][B:100][C:100][FREE:...]

free(b);                // [A:100][FREE:100][C:100][FREE:...]

// Now try to allocate 200 bytes:
char* d = malloc(200);  // FAILS! (fragmentation)
                        // 300 bytes free, but not contiguous
```

**Embedded systems concern:**
- Embedded often **avoids malloc** entirely
- Reason: Non-deterministic time, fragmentation risk
- Solution: Static allocation or memory pools

---

### 6. Stack

**Contents:** 
- Local variables (automatic storage)
- Function parameters
- Return addresses
- Saved registers

**Properties:**
- LIFO (Last In, First Out)
- Grows downward (on most architectures)
- Automatically managed (no free needed)
- Fixed size (typically 1-8MB on desktop, 1-16KB on embedded!)

**Example:**
```c
void func(int param) {      // param on stack
    int local = 5;          // local on stack
    char buffer[100];       // buffer[100] on stack
    
    // All automatically freed when func returns
}
```

**Stack frame layout:**
```
Higher addresses
┌──────────────────┐
│ Previous frame   │
├──────────────────┤
│ Return address   │  ← Pushed by CALL instruction
├──────────────────┤
│ Saved registers  │  ← EBP, etc.
├──────────────────┤
│ param (int)      │  ← Function parameter (4 bytes)
├──────────────────┤
│ local (int)      │  ← Local variable (4 bytes)
├──────────────────┤
│ buffer[100]      │  ← Local array (100 bytes)
│ (100 bytes)      │
└──────────────────┘  ← Stack pointer (ESP/RSP)
Lower addresses
```

**Performance:**
- Allocation: ~1-5 cycles (just `SUB ESP, <size>`)
- Deallocation: ~1-2 cycles (just `ADD ESP, <size>`)
- Access: ~1-3 cycles (cached in L1 cache)

**Stack size limits:**
```bash
# Linux: Check stack size
$ ulimit -s
8192   # 8MB default

# Set stack size
$ ulimit -s 16384  # 16MB

# Embedded (STM32 example):
# Defined in linker script:
_Min_Stack_Size = 0x400;  /* 1KB stack */
```

**Stack overflow example:**
```c
// ❌ Stack overflow on embedded (1KB stack)
void dangerous() {
    char buffer[2048];  // 2KB > 1KB stack = CRASH
    // ...
}

// ❌ Stack overflow via recursion
void recursive(int n) {
    char buffer[1024];
    if (n > 0) recursive(n - 1);  // Each call uses 1KB
}
recursive(10);  // 10KB of stack needed!

// ✅ Safe alternatives
void safe() {
    static char buffer[2048];  // In .bss, not stack
    // OR
    char* buffer = malloc(2048);  // On heap
}
```

---

## Tool-Based Analysis

### Using `size` Command

```bash
$ gcc example.c -o example
$ size example
   text    data     bss     dec     hex filename
   1234     512    2048    3794     ed2 example
```

**Interpretation:**
- `text`: Code + read-only data (~1.2KB)
- `data`: Initialized globals (~512 bytes)
- `bss`: Uninitialized globals (~2KB)
- **Total static RAM:** data + bss = 2560 bytes
- **Not shown:** Stack and heap (dynamic)

### Using `objdump` for Section Inspection

```bash
# View section headers
$ objdump -h example

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         00000452  0000000000001000  0000000000001000  00001000  2**4
  1 .rodata       00000100  0000000000001460  0000000000001460  00001460  2**3
  2 .data         00000200  0000000000002000  0000000000002000  00002000  2**3
  3 .bss          00000800  0000000000002200  0000000000002200  00002200  2**3

# Disassemble code section
$ objdump -d -j .text example | less

# Dump data section contents
$ objdump -s -j .data example
```

### Using `nm` for Symbol Locations

```bash
$ nm example | grep -E "B|D|T"

0000000000001000 T main           # T = .text (code)
0000000000002000 D global_var     # D = .data (initialized)
0000000000002200 B big_array      # B = .bss (uninitialized)
0000000000001100 T add            # T = .text
```

### Using GDB for Runtime Inspection

```bash
$ gdb example
(gdb) break main
(gdb) run
(gdb) info proc mappings  # Show memory map

# Print variable addresses
(gdb) print &stack_var       # On stack (high address)
(gdb) print &global_var      # In .data
(gdb) print &heap_ptr        # Points to heap
```

### Embedded: Using `arm-none-eabi` Tools

```bash
# Compile for ARM Cortex-M4
$ arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O2 main.c -o firmware.elf

# Check sizes
$ arm-none-eabi-size firmware.elf
   text    data     bss     dec     hex filename
  12345     256    4096   16697    4139 firmware.elf

# Flash usage: text + data = 12345 + 256 = 12601 bytes
# RAM usage: data + bss = 256 + 4096 = 4352 bytes

# Generate map file (detailed memory usage)
$ arm-none-eabi-gcc ... -Wl,-Map=firmware.map

# View map file
$ cat firmware.map | grep -A 20 "Memory Configuration"
```

---

## Performance Comparison

| Aspect | Stack | Heap | Static (.data/.bss) |
|--------|-------|------|---------------------|
| **Allocation speed** | ~1-5 cycles | ~100-300 cycles | 0 (compile-time) |
| **Deallocation speed** | ~1-2 cycles | ~50-150 cycles | 0 (lifetime = program) |
| **Access speed** | 1-3 cycles | 1-10 cycles | 1-10 cycles |
| **Fragmentation** | None | High risk | None |
| **Lifetime** | Scope-based | Manual | Entire program |
| **Thread-safe** | Per-thread | Needs locking | Shared (risky) |
| **Overflow risk** | High (fixed size) | Medium (OOM) | None |
| **Embedded suitability** | ✅ Excellent | ⚠️ Risky | ✅ Excellent |

---

## Common Pitfalls and Solutions

### Pitfall 1: Stack Overflow from Large Arrays

```c
// ❌ Stack overflow (1KB array on embedded 1KB stack)
void process() {
    uint8_t buffer[1024];
    // ...
}

// ✅ Solution 1: Static storage
void process() {
    static uint8_t buffer[1024];  // .bss section
}

// ✅ Solution 2: Heap (if malloc is allowed)
void process() {
    uint8_t* buffer = malloc(1024);
    // ... use buffer ...
    free(buffer);
}
```

### Pitfall 2: Dangling Pointers to Stack

```c
// ❌ Returning pointer to stack variable
int* get_value() {
    int x = 42;
    return &x;  // x destroyed when function returns!
}

// ✅ Solution 1: Return by value
int get_value() {
    return 42;
}

// ✅ Solution 2: Static storage
int* get_value() {
    static int x = 42;
    return &x;  // x persists
}

// ✅ Solution 3: Heap allocation
int* get_value() {
    int* x = malloc(sizeof(int));
    *x = 42;
    return x;  // Caller must free!
}
```

### Pitfall 3: Heap Fragmentation

```c
// ❌ Pattern causing fragmentation
for (int i = 0; i < 1000; i++) {
    void* small = malloc(16);
    void* large = malloc(1024);
    free(small);  // Leaves 16-byte holes everywhere
}

// ✅ Solution: Memory pool
#define POOL_SIZE 1024
#define BLOCK_SIZE 16
typedef struct {
    uint8_t pool[POOL_SIZE];
    uint8_t free_map[POOL_SIZE / BLOCK_SIZE];
} MemoryPool;

void* pool_alloc(MemoryPool* pool) {
    // Fixed-size allocation, no fragmentation
}
```

### Pitfall 4: Global Variable Bloat

```c
// ❌ Huge .data section (1MB in executable!)
uint8_t lookup[1024 * 1024] = {1, 2, 3, ...};

// ✅ Generate at runtime or use .rodata
const uint8_t lookup[1024 * 1024] = {...};  // Flash, not RAM
```

---

## Embedded Systems Considerations

### Flash vs RAM

**Typical STM32F4 MCU:**
- Flash: 512KB (code + constants)
- RAM: 128KB (stack + heap + .data + .bss)

**Memory budget:**
```
RAM breakdown (128KB total):
- Stack: 4KB (configurable in linker script)
- .data: 2KB (minimized)
- .bss: 50KB (buffers, state machines)
- Heap: 0KB (avoid malloc!)
- Reserved: 72KB (DMA, USB, etc.)
```

### Linker Script Example (STM32)

```ld
MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
  RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  .text : {
    *(.text*)
    *(.rodata*)
  } > FLASH
  
  .data : {
    *(.data*)
  } > RAM AT> FLASH
  
  .bss : {
    *(.bss*)
    *(COMMON)
  } > RAM
  
  ._user_heap_stack : {
    . = ALIGN(8);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } > RAM
}
```

### Checking Memory Usage at Compile Time

```c
// Static assert for stack size safety
#if (LARGE_BUFFER_SIZE > STACK_SIZE / 2)
#error "Buffer too large for stack!"
#endif

// Linker script can enforce limits
.bss (NOLOAD) : {
    *(.bss*)
    . = ALIGN(4);
    ASSERT(. <= ORIGIN(RAM) + 100K, "BSS too large!");
} > RAM
```

---

## Summary

| Section | Contents | File Size | RAM | Initialized | Performance |
|---------|----------|-----------|-----|-------------|-------------|
| `.text` | Code | Large | Small (cached) | Loader | Fast (I-cache) |
| `.rodata` | Constants | Medium | 0 (flash) | Loader | Fast (cached) |
| `.data` | Init globals | Medium | Medium | Loader | Fast |
| `.bss` | Zero globals | 0 | Large | Zeroed | Fast |
| Heap | malloc | 0 | Dynamic | Manual | Slow (100s of cycles) |
| Stack | Locals | 0 | Small | Auto | Very fast (1-5 cycles) |

**Golden rules:**
1. **Minimize `.data`** - Use zero initializers when possible
2. **Use `.rodata` for lookup tables** - Save RAM on embedded
3. **Avoid malloc on embedded** - Use static allocation or pools
4. **Watch stack usage** - Large arrays belong in .bss
5. **Profile with tools** - `size`, `objdump`, `nm`, linker maps

**Next steps:**
- Analyze your own programs with `size` and `objdump`
- Write a memory pool allocator
- Read your MCU's linker script
- Study compiler optimization effects (`-O0` vs `-O2`)

---

## Further Reading

1. **"Linkers and Loaders" by John R. Levine** - Deep dive into linking process
2. **ARM Cortex-M Programming Guide** - Architecture-specific details
3. **GCC Linker Documentation** - Understanding linker scripts
4. **"Computer Systems: A Programmer's Perspective"** - Chapter 7 (Linking)
5. Your microcontroller's **reference manual** - Memory map section
