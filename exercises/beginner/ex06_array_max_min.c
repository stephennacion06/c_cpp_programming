/**
 * Exercise 6: Array Maximum and Minimum
 * 
 * Description:
 * Find the maximum and minimum values in an array.
 * 
 * Requirements:
 * - Create an array of integers
 * - Find both max and min values
 * - Display their values and positions
 */

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

void find_max_min(int arr[], int size, int* max, int* min, int* max_idx, int* min_idx) {
    *max = arr[0];
    *min = arr[0];
    *max_idx = 0;
    *min_idx = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i] > *max) {
            *max = arr[i];
            *max_idx = i;
        }
        if (arr[i] < *min) {
            *min = arr[i];
            *min_idx = i;
        }
    }
}

void print_array(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    int numbers[] = {45, 12, 89, 23, 67, 5, 91, 34, 78, 56};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    int max, min, max_idx, min_idx;

    printf("========================================\n");
    printf("    ARRAY MAXIMUM AND MINIMUM          \n");
    printf("========================================\n\n");

    printf("Array: ");
    print_array(numbers, size);
    printf("Size: %d elements\n\n", size);

    find_max_min(numbers, size, &max, &min, &max_idx, &min_idx);

    printf("Results:\n");
    printf("  Maximum: %d at index %d\n", max, max_idx);
    printf("  Minimum: %d at index %d\n", min, min_idx);
    printf("  Range: %d (difference between max and min)\n", max - min);

    return 0;
}
