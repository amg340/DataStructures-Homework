// 01_sparse_matrix/main.c
#include <stdio.h>

#define MAX 50

typedef struct {
    int r, c, v;
} Triplet;

int dense_to_sparse(int a[MAX][MAX], int rows, int cols, Triplet out[]) {
    int k = 0;
    // out[0] stores metadata
    out[k].r = rows;
    out[k].c = cols;
    out[k].v = 0;
    k++;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (a[i][j] != 0) {
                out[k].r = i;
                out[k].c = j;
                out[k].v = a[i][j];
                k++;
                out[0].v++;
            }
        }
    }
    return k; // number of triplets used
}

void sparse_to_dense(Triplet sp[], int used, int out[MAX][MAX]) {
    int rows = sp[0].r;
    int cols = sp[0].c;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            out[i][j] = 0;

    for (int k = 1; k < used; k++) {
        int r = sp[k].r, c = sp[k].c, v = sp[k].v;
        out[r][c] = v;
    }
}

void print_dense(int a[MAX][MAX], int rows, int cols) {
    printf("Dense Matrix (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%3d ", a[i][j]);
        printf("\n");
    }
}

void print_sparse(Triplet sp[], int used) {
    printf("Sparse (Triplet) [row col val]\n");
    for (int k = 0; k < used; k++)
        printf("%3d %3d %3d\n", sp[k].r, sp[k].c, sp[k].v);
}

int main() {
    int rows = 4, cols = 5;
    int a[MAX][MAX] = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0}
    };

    Triplet sp[500];
    int used = dense_to_sparse(a, rows, cols, sp);

    print_dense(a, rows, cols);
    printf("\n");
    print_sparse(sp, used);

    int rebuilt[MAX][MAX];
    sparse_to_dense(sp, used, rebuilt);
    printf("\nRebuilt from Sparse:\n");
    print_dense(rebuilt, rows, cols);

    return 0;
}
