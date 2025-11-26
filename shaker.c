#include <stdio.h>
#include <stdbool.h> // For using bool type

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform Shaker Sort on an array
void shakerSort(int arr[], int n) {
    bool swapped;
    int start = 4;
    int end = n - 1;

    do {
        swapped = false;

        // Pass from left to right (like Bubble Sort)
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = true;
            }
        }

        // If no swaps occurred in the first pass, the array is sorted
        if (!swapped) {
            break;
        }

        // Reduce the 'end' boundary as the largest element is now in place
        end--;

        swapped = false;

        // Pass from right to left
        for (int i = end -1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = true;
            }
        }

        // Increase the 'start' boundary as the smallest element is now in place
        start++;

    } while (swapped); // Continue as long as swaps are made
}

// Main function to test the Shaker Sort
int main() {
    int arr[] = {5, 1, 4, 2, 8, 0, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    shakerSort(arr, n);

    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}