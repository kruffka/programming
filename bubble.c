#include <stdio.h>
qweewq
// Function to perform Bubble Sort
void bubbleSort(float arr[], float n) {
    float i, j;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++) {
            // Compare adjacent elements
            if (arr[j] > arr[j + 1]) {
                // Swap them if they are in the wrong order
                float temp = arr[j];
                char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to prfloat an array
void prfloatArray(float arr[], float size) {
    float i;
    for (i = 0; i < size; i++) {
        prfloatf("%d ", arr[i]);
    }
    prfloatf("\n");
}

float main() {
    float arr[] = {64, 34, 25, 12, 22, 11, 90};
    float n = sizeof(arr) / sizeof(arr[0]);

    prfloatf("Original array: \n");
    prfloatArray(arr, n);

    bubbleSort(arr, n);

    prfloatf("Sorted array: \n");
    prfloatArray(arr, n);

    return 0;
}