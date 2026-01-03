/**
 * Searching Algorithms
 * 
 * Implements two fundamental searching algorithms:
 * 1. Linear Search - Sequential search through array
 * 2. Binary Search - Divide and conquer on sorted array
 * 
 * Demonstrates the importance of data organization for
 * algorithm efficiency.
 */

#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define ARRAY_SIZE 15

// Function declarations
void print_array(const char* label, int arr[], int size);
int linear_search(int arr[], int size, int target);
int binary_search(int arr[], int size, int target);
int binary_search_recursive(int arr[], int left, int right, int target);
void print_search_result(const char* algorithm, int result, int target);

int main(void) {
#ifdef _WIN32
    // Enable UTF-8 output on Windows console
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    printf("========================================\n");
    printf("      SEARCHING ALGORITHMS DEMO        \n");
    printf("========================================\n\n");
    
    // Unsorted array for linear search
    int unsorted[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50, 32, 78, 56, 23, 67};
    
    // Sorted array for binary search
    int sorted[] = {11, 12, 22, 23, 25, 32, 34, 45, 50, 56, 64, 67, 78, 88, 90};
    
    // ==========================================
    // 1. LINEAR SEARCH
    // ==========================================
    printf("========================================\n");
    printf("1. LINEAR SEARCH (Sequential Search)\n");
    printf("========================================\n");
    printf("Algorithm: Check each element sequentially\n");
    printf("           until target is found or array ends\n\n");
    
    printf("Array (unsorted):\n");
    print_array("", unsorted, ARRAY_SIZE);
    printf("\n");
    
    // Test cases for linear search
    int targets[] = {90, 11, 45, 99, 12};
    int num_targets = 5;
    
    printf("Search results:\n");
    for (int i = 0; i < num_targets; i++) {
        int result = linear_search(unsorted, ARRAY_SIZE, targets[i]);
        print_search_result("Linear", result, targets[i]);
    }
    
    printf("\nComplexity:\n");
    printf("  • Best:    O(1)  - Target at first position\n");
    printf("  • Average: O(n)  - Target in middle\n");
    printf("  • Worst:   O(n)  - Target at end or not found\n");
    printf("  • Space:   O(1)  - No extra space needed\n\n");
    
    printf("Use cases:\n");
    printf("  • Unsorted data\n");
    printf("  • Small datasets\n");
    printf("  • Single search operation\n");
    printf("  • Linked lists (no random access)\n\n");
    
    // ==========================================
    // 2. BINARY SEARCH (Iterative)
    // ==========================================
    printf("========================================\n");
    printf("2. BINARY SEARCH (Iterative)\n");
    printf("========================================\n");
    printf("Algorithm: Repeatedly divide search interval in half\n");
    printf("           by comparing target with middle element\n");
    printf("Requirement: Array MUST be sorted\n\n");
    
    printf("Array (sorted):\n");
    print_array("", sorted, ARRAY_SIZE);
    printf("\n");
    
    printf("Search results:\n");
    for (int i = 0; i < num_targets; i++) {
        int result = binary_search(sorted, ARRAY_SIZE, targets[i]);
        print_search_result("Binary", result, targets[i]);
    }
    
    printf("\nComplexity:\n");
    printf("  • Best:    O(1)      - Target at middle\n");
    printf("  • Average: O(log n)  - Divide array each step\n");
    printf("  • Worst:   O(log n)  - Target at end or not found\n");
    printf("  • Space:   O(1)      - Iterative version\n\n");
    
    // ==========================================
    // 3. BINARY SEARCH (Recursive)
    // ==========================================
    printf("========================================\n");
    printf("3. BINARY SEARCH (Recursive)\n");
    printf("========================================\n");
    printf("Algorithm: Same logic as iterative but uses\n");
    printf("           function call stack for tracking\n\n");
    
    printf("Array (sorted):\n");
    print_array("", sorted, ARRAY_SIZE);
    printf("\n");
    
    printf("Search results:\n");
    for (int i = 0; i < num_targets; i++) {
        int result = binary_search_recursive(sorted, 0, ARRAY_SIZE - 1, targets[i]);
        print_search_result("Binary (Recursive)", result, targets[i]);
    }
    
    printf("\nComplexity:\n");
    printf("  • Time:  O(log n)  - Same as iterative\n");
    printf("  • Space: O(log n)  - Recursive call stack\n\n");
    
    // ==========================================
    // COMPARISON
    // ==========================================
    printf("========================================\n");
    printf("LINEAR vs BINARY SEARCH COMPARISON\n");
    printf("========================================\n\n");
    
    printf("┌─────────────┬──────────────┬──────────────┐\n");
    printf("│ Aspect      │ Linear       │ Binary       │\n");
    printf("├─────────────┼──────────────┼──────────────┤\n");
    printf("│ Time (Avg)  │ O(n)         │ O(log n)     │\n");
    printf("│ Space       │ O(1)         │ O(1)*        │\n");
    printf("│ Sorted?     │ No           │ Yes (MUST)   │\n");
    printf("│ Data Type   │ Any          │ Array        │\n");
    printf("│ Best For    │ Small/Unsort │ Large/Sorted │\n");
    printf("└─────────────┴──────────────┴──────────────┘\n");
    printf("* O(log n) for recursive version\n\n");
    
    printf("Example: Searching in 1,000,000 elements\n");
    printf("  • Linear Search: ~500,000 comparisons (average)\n");
    printf("  • Binary Search: ~20 comparisons (log₂ 1,000,000)\n\n");
    
    printf("========================================\n");
    printf("     ALL SEARCHES COMPLETED            \n");
    printf("========================================\n");
    
    return 0;
}

/**
 * Print array with optional label
 */
void print_array(const char* label, int arr[], int size) {
    if (label[0] != '\0') {
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
 * Linear Search (Sequential Search)
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * 
 * Searches for target by checking each element sequentially
 * from start to end.
 * 
 * Returns: Index of target if found, -1 otherwise
 */
int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // Found at index i
        }
    }
    return -1; // Not found
}

/**
 * Binary Search (Iterative)
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 * 
 * Searches for target by repeatedly dividing search interval in half.
 * Requires array to be sorted.
 * 
 * Returns: Index of target if found, -1 otherwise
 */
int binary_search(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        // Calculate middle index (avoid overflow)
        int mid = left + (right - left) / 2;
        
        // Check if target is at mid
        if (arr[mid] == target) {
            return mid;
        }
        
        // If target is greater, ignore left half
        if (arr[mid] < target) {
            left = mid + 1;
        }
        // If target is smaller, ignore right half
        else {
            right = mid - 1;
        }
    }
    
    return -1; // Not found
}

/**
 * Binary Search (Recursive)
 * Time Complexity: O(log n)
 * Space Complexity: O(log n) - due to recursive call stack
 * 
 * Recursive implementation of binary search.
 * Requires array to be sorted.
 * 
 * Returns: Index of target if found, -1 otherwise
 */
int binary_search_recursive(int arr[], int left, int right, int target) {
    // Base case: element not found
    if (left > right) {
        return -1;
    }
    
    // Calculate middle index
    int mid = left + (right - left) / 2;
    
    // Check if target is at mid
    if (arr[mid] == target) {
        return mid;
    }
    
    // If target is greater, search right half
    if (arr[mid] < target) {
        return binary_search_recursive(arr, mid + 1, right, target);
    }
    
    // If target is smaller, search left half
    return binary_search_recursive(arr, left, mid - 1, target);
}

/**
 * Print formatted search result
 */
void print_search_result(const char* algorithm, int result, int target) {
    printf("  %s search for %2d: ", algorithm, target);
    if (result != -1) {
        printf("✓ Found at index %2d\n", result);
    } else {
        printf("✗ Not found\n");
    }
}
