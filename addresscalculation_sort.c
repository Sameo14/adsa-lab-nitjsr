#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void addressCalculationSort(int arr[], int n) {
    int buckets[MAX][MAX];
    int count[MAX] = {0};

    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];

    for (int i = 0; i < n; i++) {
        int index = (arr[i] * MAX) / (max+1);
        buckets[index][count[index]++] = arr[i];
    }

    int k = 0;
    for (int i = 0; i < MAX; i++) {
        if (count[i] > 0) insertionSort(buckets[i], count[i]);
        for (int j = 0; j < count[i]; j++) arr[k++] = buckets[i][j];
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    addressCalculationSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
