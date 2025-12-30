# Hello World - Your First C Program

## Concept

"Hello, World!" is traditionally the first program written when learning a new programming language. It demonstrates the basic syntax and structure of a C program.

## Code

```c
#include <stdio.h>

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
```

## Explanation

### `#include <stdio.h>`
- This is a **preprocessor directive**
- Includes the standard input/output library
- Provides access to `printf()` function

### `int main(void)`
- Entry point of every C program
- `int` indicates the function returns an integer
- `void` means no parameters
- Execution starts here

### `printf("Hello, World!\n");`
- Prints text to the console
- `\n` is a newline character
- Semicolon (`;`) ends the statement

### `return 0;`
- Returns 0 to indicate successful execution
- Non-zero values typically indicate errors

## Compiling and Running

### Using GCC
```bash
gcc hello_world.c -o hello_world
./hello_world
```

### Using Clang
```bash
clang hello_world.c -o hello_world
./hello_world
```

### Using MSVC (Windows)
```cmd
cl hello_world.c
hello_world.exe
```

## Expected Output
```
Hello, World!
```

## Exercises

1. Modify the program to print your name
2. Add multiple `printf()` statements
3. Try removing the `\n` - what happens?
4. Try forgetting the semicolon - observe the error

## Common Mistakes

1. **Forgetting semicolon**: `printf("Hello")` ❌
2. **Wrong quotes**: `printf('Hello')` ❌ (single quotes are for characters)
3. **Typo in main**: `int Main()` ❌ (C is case-sensitive)

## Next Steps

- Learn about [variables and data types](../variables/)
- Explore [input/output](../input-output/)
