# Arrays in C

## Concept

An array is a collection of elements of the same data type stored in contiguous memory locations. Arrays allow you to store multiple values under a single variable name and access them using an index.

## Array Declaration

```c
data_type array_name[size];
```

**Example:**
```c
int numbers[5];     // Array of 5 integers
float prices[10];   // Array of 10 floats
char name[50];      // Array of 50 characters (string)
```

## Array Initialization

### Method 1: Initialize During Declaration
```c
int numbers[5] = {10, 20, 30, 40, 50};
```

### Method 2: Size Inferred from Initializer
```c
int numbers[] = {10, 20, 30, 40, 50};  // Size is 5
```

### Method 3: Partial Initialization
```c
int numbers[5] = {10, 20};  // {10, 20, 0, 0, 0}
```

### Method 4: Initialize All to Zero
```c
int numbers[5] = {0};  // {0, 0, 0, 0, 0}
```

### Method 5: Individual Assignment
```c
int numbers[3];
numbers[0] = 10;
numbers[1] = 20;
numbers[2] = 30;
```

## Accessing Array Elements

Arrays use zero-based indexing (first element is at index 0):

```c
int numbers[] = {10, 20, 30, 40, 50};

printf("%d\n", numbers[0]);  // 10 (first element)
printf("%d\n", numbers[2]);  // 30 (third element)
printf("%d\n", numbers[4]);  // 50 (last element)
```

### Modifying Elements
```c
numbers[2] = 99;  // Change third element to 99
numbers[0] = numbers[1] + 10;  // First = second + 10
```

## Array Size

Calculate the number of elements:

```c
int numbers[] = {10, 20, 30, 40, 50};
int size = sizeof(numbers) / sizeof(numbers[0]);
// size = 20 bytes / 4 bytes = 5 elements
```

**Important:** This only works in the scope where the array is defined!

## Iterating Through Arrays

### Using for Loop
```c
int numbers[] = {10, 20, 30, 40, 50};
int size = sizeof(numbers) / sizeof(numbers[0]);

for (int i = 0; i < size; i++) {
    printf("%d ", numbers[i]);
}
```

### Reverse Iteration
```c
for (int i = size - 1; i >= 0; i--) {
    printf("%d ", numbers[i]);
}
```

## Common Array Operations

### 1. Sum of Elements
```c
int sum = 0;
for (int i = 0; i < size; i++) {
    sum += numbers[i];
}
```

### 2. Find Maximum
```c
int max = numbers[0];
for (int i = 1; i < size; i++) {
    if (numbers[i] > max) {
        max = numbers[i];
    }
}
```

### 3. Find Minimum
```c
int min = numbers[0];
for (int i = 1; i < size; i++) {
    if (numbers[i] < min) {
        min = numbers[i];
    }
}
```

### 4. Linear Search
```c
int target = 30;
int found_index = -1;

for (int i = 0; i < size; i++) {
    if (numbers[i] == target) {
        found_index = i;
        break;
    }
}

if (found_index != -1) {
    printf("Found at index %d\n", found_index);
} else {
    printf("Not found\n");
}
```

### 5. Reverse Array
```c
for (int i = 0; i < size / 2; i++) {
    int temp = numbers[i];
    numbers[i] = numbers[size - 1 - i];
    numbers[size - 1 - i] = temp;
}
```

### 6. Copy Array
```c
int source[] = {1, 2, 3, 4, 5};
int destination[5];

for (int i = 0; i < 5; i++) {
    destination[i] = source[i];
}
```

## Passing Arrays to Functions

Arrays are passed by reference (the function receives a pointer):

```c
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void modify_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // Modifies original array!
    }
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    print_array(numbers, size);
    modify_array(numbers, size);
    print_array(numbers, size);  // Array is modified
    
    return 0;
}
```

**Note:** You must pass the size separately because `sizeof()` doesn't work on array parameters.

## Multi-Dimensional Arrays

### 2D Arrays (Matrix)

Declaration:
```c
int matrix[3][4];  // 3 rows, 4 columns
```

Initialization:
```c
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
```

Accessing elements:
```c
printf("%d\n", matrix[0][0]);  // 1 (first row, first column)
printf("%d\n", matrix[1][2]);  // 6 (second row, third column)
```

Iterating through 2D array:
```c
int rows = 3, cols = 3;

for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        printf("%d ", matrix[i][j]);
    }
    printf("\n");
}
```

### 3D Arrays and Beyond

```c
int cube[2][3][4];  // 2 layers, 3 rows, 4 columns

// Initialization
int cube[2][2][2] = {
    {{1, 2}, {3, 4}},
    {{5, 6}, {7, 8}}
};
```

## Character Arrays (Strings)

Strings are arrays of characters ending with `'\0'`:

```c
char name[10] = "Alice";  // {'A', 'l', 'i', 'c', 'e', '\0'}
char message[] = "Hello";  // Size automatically calculated

printf("%s\n", name);  // Print string
printf("%c\n", name[0]);  // Print first character
```

## Array Bounds

⚠️ **C does not check array bounds!** Accessing outside bounds causes undefined behavior:

```c
int numbers[5] = {1, 2, 3, 4, 5};
printf("%d\n", numbers[10]);  // ❌ Undefined behavior!
numbers[10] = 99;              // ❌ May crash or corrupt memory!
```

Always ensure: `0 <= index < size`

## Best Practices

1. **Always pass array size** to functions
2. **Initialize arrays** to avoid garbage values
3. **Check bounds** before accessing elements
4. **Use meaningful names**: `scores[]` not `arr[]`
5. **Use constants for size**:
   ```c
   #define MAX_SIZE 100
   int numbers[MAX_SIZE];
   ```

## Common Pitfalls

⚠️ **Accessing out of bounds**
```c
int arr[5];
arr[5] = 10;  // ❌ Index 5 is out of bounds (max is 4)
```

⚠️ **Not passing size to function**
```c
void print_array(int arr[]) {
    // ❌ Can't determine size here!
    int size = sizeof(arr) / sizeof(arr[0]);  // Wrong!
}
```

⚠️ **Comparing arrays with ==**
```c
int a[] = {1, 2, 3};
int b[] = {1, 2, 3};
if (a == b) {  // ❌ Compares addresses, not contents!
    // ...
}

// ✅ Correct way
int equal = 1;
for (int i = 0; i < 3; i++) {
    if (a[i] != b[i]) {
        equal = 0;
        break;
    }
}
```

⚠️ **Forgetting null terminator in strings**
```c
char name[5] = {'A', 'l', 'i', 'c', 'e'};  // ❌ No '\0'!
printf("%s\n", name);  // Undefined behavior

// ✅ Correct
char name[6] = {'A', 'l', 'i', 'c', 'e', '\0'};
// or
char name[] = "Alice";  // Automatically adds '\0'
```

⚠️ **Partial initialization confusion**
```c
int arr[5] = {1, 2};  // {1, 2, 0, 0, 0} - rest are 0
int arr[5];           // {?, ?, ?, ?, ?} - garbage values!
```

## Complete Examples

### Example 1: Grade Calculator
```c
#include <stdio.h>

int main(void) {
    int grades[] = {85, 92, 78, 90, 88, 95};
    int size = sizeof(grades) / sizeof(grades[0]);
    
    // Calculate average
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += grades[i];
    }
    double average = (double)sum / size;
    
    printf("Average: %.2f\n", average);
    
    // Count grades above average
    int above_avg = 0;
    for (int i = 0; i < size; i++) {
        if (grades[i] > average) {
            above_avg++;
        }
    }
    
    printf("Grades above average: %d\n", above_avg);
    
    return 0;
}
```

### Example 2: Bubble Sort
```c
void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    bubble_sort(numbers, size);
    
    // Print sorted array
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    return 0;
}
```

### Example 3: Matrix Operations
```c
void print_matrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    print_matrix(3, 3, matrix);
    
    return 0;
}
```

## Exercise

Modify `arrays.c` to:
1. Implement binary search (requires sorted array)
2. Find the second largest element in an array
3. Rotate an array left or right by n positions
4. Implement matrix addition and multiplication

## Next Steps

- Learn about [Strings](strings.md) - special character arrays
- Explore [Pointers](../intermediate/pointers.md) for advanced array manipulation
- Study [Dynamic Memory](../intermediate/dynamic-memory.md) for variable-size arrays
