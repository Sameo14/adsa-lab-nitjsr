#include <stdio.h>
#include <stdlib.h>

#define MAX 1000   // maximum array size

// Structure to represent a subproblem (like recursive call params)
typedef struct {
    int left;
    int right;
    int state;  // 0 = need to split further, 1 = need to merge
} Frame;

// Function to merge two sorted halves
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Non-recursive merge sort using stack (top-down approach)
void mergeSort(int arr[], int n) {
    Frame stack[MAX];
    int top = -1;

    // Push the whole problem (0 to n-1)
    stack[++top] = (Frame){0, n - 1, 0};

    while (top >= 0) {
        Frame f = stack[top--];

        if (f.left < f.right) {
            if (f.state == 0) {
                int mid = (f.left + f.right) / 2;

                // Push current frame again with state=1 (to merge later)
                stack[++top] = (Frame){f.left, f.right, 1};

                // Push right and left halves to sort them first
                stack[++top] = (Frame){mid + 1, f.right, 0};
                stack[++top] = (Frame){f.left, mid, 0};
            } else {
                int mid = (f.left + f.right) / 2;
                merge(arr, f.left, mid, f.right);
            }
        }
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    mergeSort(arr, n);

    printf("Sorted array:   ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
