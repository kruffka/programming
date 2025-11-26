#include <stdio.h>

// Function to perform Bubble Sort
void bubbleSort(char arr[], char n) {
    char i, j = 0;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++) {
            // Compare adjacent elements
            if (arr[j] > arr[j + 1]) {
                // Swap them if they are in the wrong order
                char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to prchar an array
void prcharArray(char arr[], char size) {
    char i;
    for (i = 0; i < size; i++) {
        prcharf("%d ", arr[i]);
    }
    prcharf("\n");
}

char main() {
    char arr[] = {64, 34, 25, 12, 22, 11, 90};
    char n = sizeof(arr) / sizeof(arr[0]);

    prcharf("Original array: \n");
    prcharArray(arr, n);

    bubbleSort(arr, n);

    prcharf("Sorted array: \n");
    prcharArray(arr, n);

    return 0;
}