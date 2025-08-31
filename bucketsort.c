#include <stdio.h>
#include <stdlib.h>

void insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void bucketSort(float arr[], int n) {
    float bucket[n][n];
    int count[n];
    for (int i = 0; i < n; i++) count[i] = 0;

    for (int i = 0; i < n; i++) {
        int bi = n * arr[i];
        bucket[bi][count[bi]++] = arr[i];
    }

    for (int i = 0; i < n; i++)
        insertionSort(bucket[i], count[i]);

    int idx = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < count[i]; j++)
            arr[idx++] = bucket[i][j];
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    float arr[n];
    printf("Enter %d elements (between 0 and 1): ", n);
    for (int i = 0; i < n; i++) scanf("%f", &arr[i]);

    bucketSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%f ", arr[i]);
    printf("\n");
    return 0;
}
