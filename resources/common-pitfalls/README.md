# Common Pitfalls in C/C++

A comprehensive guide to common mistakes and how to avoid them.

## 🚨 Memory-Related Pitfalls

### 1. Memory Leaks
**Problem**: Allocated memory is never freed.

```c
// BAD
void process_data() {
    int *data = (int*)malloc(100 * sizeof(int));
    // ... use data ...
    // Oops! Forgot to free(data)
}

// GOOD
void process_data() {
    int *data = (int*)malloc(100 * sizeof(int));
    if (data == NULL) return;
    // ... use data ...
    free(data);
}
```

**Prevention**:
- Always pair `malloc` with `free`
- Use RAII in C++ (smart pointers)
- Enable memory leak detection tools

### 2. Double Free
**Problem**: Freeing the same memory twice.

```c
// BAD
int *ptr = (int*)malloc(sizeof(int));
free(ptr);
free(ptr);  // ERROR: Double free!

// GOOD
int *ptr = (int*)malloc(sizeof(int));
free(ptr);
ptr = NULL;  // Set to NULL after free
```

### 3. Use After Free
**Problem**: Accessing memory after it's been freed.

```c
// BAD
int *ptr = (int*)malloc(sizeof(int));
*ptr = 42;
free(ptr);
printf("%d\n", *ptr);  // ERROR: Use after free!

// GOOD
int *ptr = (int*)malloc(sizeof(int));
*ptr = 42;
printf("%d\n", *ptr);
free(ptr);
ptr = NULL;
```

### 4. Buffer Overflow
**Problem**: Writing beyond array bounds.

```c
// BAD
char buffer[10];
strcpy(buffer, "This string is too long!");  // Overflow!

// GOOD
char buffer[30];
strncpy(buffer, "This string fits", sizeof(buffer) - 1);
buffer[sizeof(buffer) - 1] = '\0';
```

### 5. Dangling Pointers
**Problem**: Pointer points to deallocated memory.

```c
// BAD
int* get_local_address() {
    int x = 42;
    return &x;  // ERROR: Returning address of local variable!
}

// GOOD
int* allocate_int() {
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    return ptr;  // Caller must free this
}
```

## 🔢 Logic Errors

### 6. Off-by-One Errors
**Problem**: Loop iterates one too many or too few times.

```c
// BAD
int arr[10];
for (int i = 0; i <= 10; i++) {  // Goes to 10, but array is 0-9!
    arr[i] = i;
}

// GOOD
int arr[10];
for (int i = 0; i < 10; i++) {
    arr[i] = i;
}
```

### 7. Integer Overflow
**Problem**: Arithmetic operation exceeds type limits.

```c
// BAD
int x = 2147483647;  // INT_MAX
int y = x + 1;  // Overflow! Undefined behavior

// GOOD
#include <limits.h>
if (x > INT_MAX - 1) {
    // Handle overflow
} else {
    int y = x + 1;
}
```

### 8. Uninitialized Variables
**Problem**: Using variables before assigning values.

```c
// BAD
int x;
printf("%d\n", x);  // Undefined behavior!

// GOOD
int x = 0;  // Always initialize
printf("%d\n", x);
```

## 🔤 String Pitfalls

### 9. Missing Null Terminator
**Problem**: String functions expect null-terminated strings.

```c
// BAD
char str[5] = {'H', 'e', 'l', 'l', 'o'};
printf("%s\n", str);  // No null terminator!

// GOOD
char str[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
// Or better:
char str[] = "Hello";
```

### 10. strcmp Misuse
**Problem**: Using `==` to compare strings instead of `strcmp`.

```c
// BAD
char *str1 = "hello";
char *str2 = "hello";
if (str1 == str2) {  // Comparing pointers, not content!
    // May or may not execute
}

// GOOD
if (strcmp(str1, str2) == 0) {  // Comparing content
    // Correct comparison
}
```

## 🔀 Pointer Pitfalls

### 11. Null Pointer Dereference
**Problem**: Dereferencing NULL pointer.

```c
// BAD
int *ptr = NULL;
*ptr = 42;  // CRASH!

// GOOD
int *ptr = (int*)malloc(sizeof(int));
if (ptr != NULL) {
    *ptr = 42;
    free(ptr);
}
```

### 12. Pointer Arithmetic Errors
**Problem**: Incorrect pointer arithmetic.

```c
// BAD
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;
ptr = ptr + 10;  // Points outside array!
*ptr = 99;  // Undefined behavior

// GOOD
int *ptr = arr;
if (ptr + 10 < arr + 5) {  // Check bounds
    *(ptr + 10) = 99;
}
```

## 🔄 Control Flow Pitfalls

### 13. Assignment in Condition
**Problem**: Using `=` instead of `==` in conditions.

```c
// BAD
int x = 5;
if (x = 10) {  // Assignment, not comparison!
    printf("This always executes\n");
}

// GOOD
int x = 5;
if (x == 10) {  // Comparison
    printf("This is correct\n");
}
```

### 14. Missing Break in Switch
**Problem**: Forgetting break causes fall-through.

```c
// BAD
switch(x) {
    case 1:
        printf("One\n");
        // Missing break!
    case 2:
        printf("Two\n");
        break;
}

// GOOD
switch(x) {
    case 1:
        printf("One\n");
        break;
    case 2:
        printf("Two\n");
        break;
}
```

## 📦 Type-Related Pitfalls

### 15. Implicit Type Conversion
**Problem**: Unexpected type conversions.

```c
// BAD
unsigned int x = 10;
int y = -5;
if (x + y < 0) {  // Never true! y is converted to unsigned
    printf("Negative\n");
}

// GOOD
int x = 10;
int y = -5;
if (x + y < 0) {
    printf("Negative\n");
}
```

### 16. Ignoring Return Values
**Problem**: Not checking function return values.

```c
// BAD
malloc(100);  // Not checking if allocation succeeded

// GOOD
int *ptr = (int*)malloc(100 * sizeof(int));
if (ptr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return -1;
}
```

## 🧵 Multithreading Pitfalls

### 17. Race Conditions
**Problem**: Multiple threads accessing shared data without synchronization.

```cpp
// BAD
int counter = 0;
void increment() {
    counter++;  // Not thread-safe!
}

// GOOD
#include <mutex>
int counter = 0;
std::mutex mtx;
void increment() {
    std::lock_guard<std::mutex> lock(mtx);
    counter++;
}
```

### 18. Deadlock
**Problem**: Threads waiting for each other's resources.

```cpp
// BAD
std::mutex m1, m2;
// Thread 1
m1.lock(); m2.lock();
// Thread 2
m2.lock(); m1.lock();  // Deadlock!

// GOOD
// Always acquire locks in the same order
m1.lock(); m2.lock();  // Both threads
```

## ✅ Prevention Checklist

- [ ] Enable all compiler warnings (`-Wall -Wextra -Wpedantic`)
- [ ] Use static analysis tools (cppcheck, clang-tidy)
- [ ] Use sanitizers (AddressSanitizer, UndefinedBehaviorSanitizer)
- [ ] Initialize all variables
- [ ] Check return values
- [ ] Validate input
- [ ] Use const where appropriate
- [ ] Review code regularly
- [ ] Write unit tests
- [ ] Use modern C++ features (RAII, smart pointers)

## 📚 Additional Resources

- [C Traps and Pitfalls](https://en.wikipedia.org/wiki/C_Traps_and_Pitfalls)
- [Common C++ Mistakes](https://isocpp.github.io/CppCoreGuidelines/)
- [Secure Coding in C/C++](https://www.securecoding.cert.org/)

## 📝 Contributing

Know more pitfalls? Share them! See [CONTRIBUTING.md](../../CONTRIBUTING.md).
