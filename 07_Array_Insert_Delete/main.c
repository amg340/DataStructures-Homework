#include <stdio.h>

#define CAP 100

int insertAt(int arr[], int *n, int index, int value) {
    if (*n >= CAP) return 0;
    if (index < 0 || index > *n) return 0;

    for (int i = *n; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    (*n)++;
    return 1;
}

int deleteAt(int arr[], int *n, int index) {
    if (*n <= 0) return 0;
    if (index < 0 || index >= *n) return 0;

    for (int i = index; i < *n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*n)--;
    return 1;
}

void printArr(int arr[], int n) {
    printf("Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[CAP] = {10, 20, 30, 40};
    int n = 4;

    printArr(arr, n);
    insertAt(arr, &n, 2, 99);  // insert 99 at index 2
    printArr(arr, n);

    deleteAt(arr, &n, 1);      // delete index 1
    printArr(arr, n);

    return 0;
}
