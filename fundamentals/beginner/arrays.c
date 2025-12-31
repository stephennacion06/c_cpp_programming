/**
 * Arrays in C
 * 
 * This program demonstrates:
 * - Array declaration and initialization
 * - Accessing array elements
 * - Multi-dimensional arrays
 * - Array operations
 * - Passing arrays to functions
 */

#include <stdio.h>

// Function prototypes
void print_array(int arr[], int size);
int sum_array(int arr[], int size);
int find_max(int arr[], int size);
int find_min(int arr[], int size);
double average_array(int arr[], int size);
int linear_search(int arr[], int size, int target);
void reverse_array(int arr[], int size);
void print_2d_array(int rows, int cols, int arr[][3]);  // Fixed size for MSVC compatibility

int main(void) {
    printf("=== Arrays in C ===\n\n");
    
    // PART 1: Array declaration and initialization
    printf("1. ARRAY DECLARATION AND INITIALIZATION\n");
    
    // Method 1: Declare then assign
    int numbers[5];
    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;
    numbers[3] = 40;
    numbers[4] = 50;
    
    // Method 2: Initialize during declaration
    int scores[] = {85, 90, 78, 92, 88};
    
    // Method 3: Partial initialization (rest are 0)
    int values[5] = {1, 2};  // {1, 2, 0, 0, 0}
    
    // Method 4: All zeros
    int zeros[5] = {0};
    
    printf("  numbers: ");
    print_array(numbers, 5);
    printf("  scores: ");
    print_array(scores, 5);
    printf("\n");
    
    // PART 2: Accessing array elements
    printf("2. ACCESSING ARRAY ELEMENTS\n");
    printf("  First element: %d\n", scores[0]);
    printf("  Third element: %d\n", scores[2]);
    printf("  Last element: %d\n", scores[4]);
    printf("\n");
    
    // PART 3: Array size
    printf("3. ARRAY SIZE\n");
    int data[] = {1, 2, 3, 4, 5};
    int size = sizeof(data) / sizeof(data[0]);
    printf("  Array has %d elements\n", size);
    printf("  sizeof(data) = %zu bytes\n", sizeof(data));
    printf("  sizeof(data[0]) = %zu bytes\n", sizeof(data[0]));
    printf("\n");
    
    // PART 4: Iterating through arrays
    printf("4. ITERATING THROUGH ARRAYS\n");
    int nums[] = {10, 20, 30, 40, 50};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    
    printf("  Using for loop:\n");
    printf("    ");
    for (int i = 0; i < nums_size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n\n");
    
    // PART 5: Array operations
    printf("5. ARRAY OPERATIONS\n");
    int test_scores[] = {85, 92, 78, 90, 88};
    int test_size = sizeof(test_scores) / sizeof(test_scores[0]);
    
    printf("  Scores: ");
    print_array(test_scores, test_size);
    printf("  Sum: %d\n", sum_array(test_scores, test_size));
    printf("  Average: %.2f\n", average_array(test_scores, test_size));
    printf("  Maximum: %d\n", find_max(test_scores, test_size));
    printf("  Minimum: %d\n", find_min(test_scores, test_size));
    printf("\n");
    
    // PART 6: Searching in arrays
    printf("6. SEARCHING IN ARRAYS\n");
    int search_array[] = {10, 25, 30, 45, 50};
    int search_size = sizeof(search_array) / sizeof(search_array[0]);
    int target = 30;
    
    printf("  Array: ");
    print_array(search_array, search_size);
    
    int index = linear_search(search_array, search_size, target);
    if (index != -1) {
        printf("  Found %d at index %d\n", target, index);
    } else {
        printf("  %d not found\n", target);
    }
    printf("\n");
    
    // PART 7: Modifying array elements
    printf("7. MODIFYING ARRAY ELEMENTS\n");
    int modify[] = {1, 2, 3, 4, 5};
    int modify_size = sizeof(modify) / sizeof(modify[0]);
    
    printf("  Original: ");
    print_array(modify, modify_size);
    
    // Double each element
    for (int i = 0; i < modify_size; i++) {
        modify[i] *= 2;
    }
    
    printf("  Doubled: ");
    print_array(modify, modify_size);
    printf("\n");
    
    // PART 8: Reversing an array
    printf("8. REVERSING AN ARRAY\n");
    int reverse[] = {1, 2, 3, 4, 5};
    int reverse_size = sizeof(reverse) / sizeof(reverse[0]);
    
    printf("  Original: ");
    print_array(reverse, reverse_size);
    
    reverse_array(reverse, reverse_size);
    
    printf("  Reversed: ");
    print_array(reverse, reverse_size);
    printf("\n");
    
    // PART 9: Multi-dimensional arrays
    printf("9. MULTI-DIMENSIONAL ARRAYS\n");
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    printf("  3x3 Matrix:\n");
    print_2d_array(3, 3, matrix);
    printf("\n");
    
    // PART 10: Common array patterns
    printf("10. COMMON PATTERNS\n");
    
    // Finding sum of even numbers
    int pattern_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int pattern_size = sizeof(pattern_arr) / sizeof(pattern_arr[0]);
    int even_sum = 0;
    
    for (int i = 0; i < pattern_size; i++) {
        if (pattern_arr[i] % 2 == 0) {
            even_sum += pattern_arr[i];
        }
    }
    printf("  Sum of even numbers: %d\n", even_sum);
    
    // Counting occurrences
    int count_arr[] = {1, 2, 3, 2, 1, 2, 4, 2};
    int count_size = sizeof(count_arr) / sizeof(count_arr[0]);
    int count_target = 2;
    int count = 0;
    
    for (int i = 0; i < count_size; i++) {
        if (count_arr[i] == count_target) {
            count++;
        }
    }
    printf("  Number %d appears %d times\n", count_target, count);
    printf("\n");
    
    return 0;
}

// Function definitions

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int sum_array(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int find_min(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

double average_array(int arr[], int size) {
    if (size == 0) return 0.0;
    return (double)sum_array(arr, size) / size;
}

int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}

void reverse_array(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

void print_2d_array(int rows, int cols, int arr[][3]) {  // Fixed size for MSVC compatibility
    for (int i = 0; i < rows; i++) {
        printf("    ");
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
