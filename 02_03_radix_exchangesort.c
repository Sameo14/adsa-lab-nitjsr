#include <stdio.h>

void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) return;
    int i = left, j = right;
    while (i <= j) {
        while (i <= right && ((arr[i] >> bit) & 1) == 0) i++;
        while (j >= left && ((arr[j] >> bit) & 1) == 1) j--;
        if (i < j) {
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    radixExchangeSort(arr, left, j, bit-1);
    radixExchangeSort(arr, j+1, right, bit-1);
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements (non-negative): ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    int bits = 0;
    while (max > 0) { bits++; max >>= 1; }

    radixExchangeSort(arr, 0, n-1, bits-1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
