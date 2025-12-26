#include <stdio.h>

#define CAP 100

typedef struct {
    int a[CAP];
    int size;
    int isMin; // 1 = MinHeap, 0 = MaxHeap
} Heap;

void initHeap(Heap *h, int isMin) {
    h->size = 0;
    h->isMin = isMin;
}

int better(Heap *h, int x, int y) {
    // return 1 if x should be above y
    return h->isMin ? (x < y) : (x > y);
}

void swap(int *x, int *y) { int t=*x; *x=*y; *y=t; }

void heapifyUp(Heap *h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (better(h, h->a[i], h->a[p])) {
            swap(&h->a[i], &h->a[p]);
            i = p;
        } else break;
    }
}

void heapifyDown(Heap *h, int i) {
    while (1) {
        int l = 2*i + 1, r = 2*i + 2;
        int best = i;

        if (l < h->size && better(h, h->a[l], h->a[best])) best = l;
        if (r < h->size && better(h, h->a[r], h->a[best])) best = r;

        if (best != i) {
            swap(&h->a[i], &h->a[best]);
            i = best;
        } else break;
    }
}

void insert(Heap *h, int x) {
    if (h->size >= CAP) return;
    h->a[h->size] = x;
    heapifyUp(h, h->size);
    h->size++;
}

int peek(Heap *h) {
    if (h->size == 0) return -1;
    return h->a[0];
}

int extractTop(Heap *h) {
    if (h->size == 0) return -1;
    int top = h->a[0];
    h->a[0] = h->a[h->size - 1];
    h->size--;
    heapifyDown(h, 0);
    return top;
}

void printHeap(Heap *h) {
    printf("%sHeap: ", h->isMin ? "Min" : "Max");
    for (int i = 0; i < h->size; i++) printf("%d ", h->a[i]);
    printf("\n");
}

int main() {
    Heap maxH, minH;
    initHeap(&maxH, 0);
    initHeap(&minH, 1);

    int nums[] = {10, 4, 7, 1, 20, 15, 3};
    int n = sizeof(nums)/sizeof(nums[0]);

    for (int i = 0; i < n; i++) {
        insert(&maxH, nums[i]);
        insert(&minH, nums[i]);
    }

    printHeap(&maxH);
    printHeap(&minH);

    printf("MaxHeap extract: %d\n", extractTop(&maxH));
    printf("MinHeap extract: %d\n", extractTop(&minH));

    printHeap(&maxH);
    printHeap(&minH);

    return 0;
}
