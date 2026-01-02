/**
 * Basic Sorting Algorithms
 * 
 * Implements three fundamental sorting algorithms:
 * 1. Bubble Sort - Repeatedly swap adjacent elements if they're in wrong order
 * 2. Selection Sort - Find minimum element and place it at the beginning
 * 3. Insertion Sort - Build sorted array one element at a time
 * 
 * All three have O(n²) time complexity but differ in their approach
 * and practical performance characteristics.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE 10

// Function declarations
void print_array(const char* label, int arr[], int size);
void copy_array(int dest[], int src[], int size);
void bubble_sort(int arr[], int size);
void selection_sort(int arr[], int size);
void insertion_sort(int arr[], int size);
bool is_sorted(int arr[], int size);

int main(void) {
    printf("========================================\n");
    printf("    BASIC SORTING ALGORITHMS DEMO      \n");
    printf("========================================\n\n");
    
    // Original unsorted array
    int original[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    int arr[ARRAY_SIZE];
    
    printf("Original Array:\n");
    print_array("", original, ARRAY_SIZE);
    printf("\n");
    
    // ==========================================
    // 1. BUBBLE SORT
    // ==========================================
    printf("========================================\n");
    printf("1. BUBBLE SORT\n");
    printf("========================================\n");
    printf("Algorithm: Repeatedly compare adjacent elements\n");
    printf("           and swap if they're in wrong order\n\n");
    
    copy_array(arr, original, ARRAY_SIZE);
    printf("Before: ");
    print_array("", arr, ARRAY_SIZE);
    
    bubble_sort(arr, ARRAY_SIZE);
    
    printf("After:  ");
    print_array("", arr, ARRAY_SIZE);
    printf("Status: %s\n", is_sorted(arr, ARRAY_SIZE) ? "✓ Sorted" : "✗ Not sorted");
    printf("\nComplexity:\n");
    printf("  • Best:    O(n)   - Already sorted\n");
    printf("  • Average: O(n²)  - Random order\n");
    printf("  • Worst:   O(n²)  - Reverse sorted\n");
    printf("  • Space:   O(1)   - In-place sorting\n");
    printf("  • Stable:  Yes    - Equal elements maintain order\n\n");
    
    // ==========================================
    // 2. SELECTION SORT
    // ==========================================
    printf("========================================\n");
    printf("2. SELECTION SORT\n");
    printf("========================================\n");
    printf("Algorithm: Find minimum element and place it\n");
    printf("           at the beginning of unsorted part\n\n");
    
    copy_array(arr, original, ARRAY_SIZE);
    printf("Before: ");
    print_array("", arr, ARRAY_SIZE);
    
    selection_sort(arr, ARRAY_SIZE);
    
    printf("After:  ");
    print_array("", arr, ARRAY_SIZE);
    printf("Status: %s\n", is_sorted(arr, ARRAY_SIZE) ? "✓ Sorted" : "✗ Not sorted");
    printf("\nComplexity:\n");
    printf("  • Best:    O(n²)  - Always scans entire array\n");
    printf("  • Average: O(n²)  - Random order\n");
    printf("  • Worst:   O(n²)  - Reverse sorted\n");
    printf("  • Space:   O(1)   - In-place sorting\n");
    printf("  • Stable:  No     - May change relative order\n\n");
    
    // ==========================================
    // 3. INSERTION SORT
    // ==========================================
    printf("========================================\n");
    printf("3. INSERTION SORT\n");
    printf("========================================\n");
    printf("Algorithm: Build sorted array one element at a time\n");
    printf("           by inserting each element in correct position\n\n");
    
    copy_array(arr, original, ARRAY_SIZE);
    printf("Before: ");
    print_array("", arr, ARRAY_SIZE);
    
    insertion_sort(arr, ARRAY_SIZE);
    
    printf("After:  ");
    print_array("", arr, ARRAY_SIZE);
    printf("Status: %s\n", is_sorted(arr, ARRAY_SIZE) ? "✓ Sorted" : "✗ Not sorted");
    printf("\nComplexity:\n");
    printf("  • Best:    O(n)   - Already sorted\n");
    printf("  • Average: O(n²)  - Random order\n");
    printf("  • Worst:   O(n²)  - Reverse sorted\n");
    printf("  • Space:   O(1)   - In-place sorting\n");
    printf("  • Stable:  Yes    - Equal elements maintain order\n\n");
    
    // ==========================================
    // COMPARISON
    // ==========================================
    printf("========================================\n");
    printf("WHEN TO USE EACH ALGORITHM\n");
    printf("========================================\n");
    printf("Bubble Sort:\n");
    printf("  • Educational purposes\n");
    printf("  • Nearly sorted data (optimized version)\n");
    printf("  • Small datasets\n\n");
    
    printf("Selection Sort:\n");
    printf("  • Memory write is costly operation\n");
    printf("  • Small datasets\n");
    printf("  • When auxiliary memory is limited\n\n");
    
    printf("Insertion Sort:\n");
    printf("  • Small datasets\n");
    printf("  • Nearly sorted data\n");
    printf("  • Online sorting (data arrives over time)\n");
    printf("  • Part of more complex algorithms (Timsort)\n\n");
    
    printf("========================================\n");
    printf("     ALL ALGORITHMS COMPLETED           \n");
    printf("========================================\n");
    
    return 0;
}

/**
 * Print array with optional label
 */
void print_array(const char* label, int arr[], int size) {
    if (strlen(label) > 0) {
        printf("%s: ", label);
    }
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * Copy array from source to destination
 */
void copy_array(int dest[], int src[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

/**
 * Bubble Sort
 * Time Complexity: O(n²) average and worst case, O(n) best case
 * Space Complexity: O(1)
 * 
 * Works by repeatedly stepping through the list, comparing adjacent
 * elements and swapping them if they're in the wrong order.
 */
void bubble_sort(int arr[], int size) {
    printf("\nSorting process:\n");
    
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        
        // Last i elements are already in place
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        
        // Print after each pass
        printf("  Pass %2d: ", i + 1);
        print_array("", arr, size);
        
        // Optimization: if no swaps occurred, array is sorted
        if (!swapped) {
            printf("  No swaps made - array is sorted!\n");
            break;
        }
    }
    printf("\n");
}

/**
 * Selection Sort
 * Time Complexity: O(n²) in all cases
 * Space Complexity: O(1)
 * 
 * Works by repeatedly finding the minimum element from unsorted part
 * and putting it at the beginning.
 */
void selection_sort(int arr[], int size) {
    printf("\nSorting process:\n");
    
    for (int i = 0; i < size - 1; i++) {
        // Find minimum element in unsorted array
        int min_idx = i;
        
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Swap found minimum element with first element
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
        
        // Print after each selection
        printf("  Step %2d: ", i + 1);
        print_array("", arr, size);
    }
    printf("\n");
}

/**
 * Insertion Sort
 * Time Complexity: O(n²) average and worst case, O(n) best case
 * Space Complexity: O(1)
 * 
 * Works by building a sorted array one item at a time by inserting
 * each element into its proper position.
 */
void insertion_sort(int arr[], int size) {
    printf("\nSorting process:\n");
    
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        arr[j + 1] = key;
        
        // Print after each insertion
        printf("  Step %2d: ", i);
        print_array("", arr, size);
    }
    printf("\n");
}

/**
 * Check if array is sorted in ascending order
 */
bool is_sorted(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}
