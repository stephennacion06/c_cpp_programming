/**
 * Exercise 7: Reverse an Array
 * 
 * Description:
 * Reverse the elements of an array in-place.
 * 
 * Requirements:
 * - Display original array
 * - Reverse the array
 * - Display reversed array
 */

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

void print_array(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void reverse_array(int arr[], int size) {
    int left = 0;
    int right = size - 1;

    while (left < right) {
        // Swap elements
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left++;
        right--;
    }
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    int numbers[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("========================================\n");
    printf("        REVERSE AN ARRAY               \n");
    printf("========================================\n\n");

    printf("Original array:\n");
    print_array(numbers, size);

    reverse_array(numbers, size);

    printf("\nReversed array:\n");
    print_array(numbers, size);

    printf("\n✓ Array reversed successfully!\n");

    return 0;
}
