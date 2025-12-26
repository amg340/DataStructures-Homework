#include <stdio.h>

#define MAX 50

void dfs(int g[MAX][MAX], int n, int u, int visited[MAX]) {
    visited[u] = 1;
    printf("%d ", u);
    for (int v = 0; v < n; v++) {
        if (g[u][v] && !visited[v]) dfs(g, n, v, visited);
    }
}

int main() {
    int n = 7;
    int g[MAX][MAX] = {0};

    // Example graph: clusters are {0,1,2} and {3,4} and {5,6}
    g[0][1]=g[1][0]=1;
    g[1][2]=g[2][1]=1;
    g[0][2]=g[2][0]=1;

    g[3][4]=g[4][3]=1;

    g[5][6]=g[6][5]=1;

    int visited[MAX] = {0};
    int comp = 0;

    printf("Clusters (Connected Components):\n");
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            comp++;
            printf("Cluster %d: ", comp);
            dfs(g, n, i, visited);
            printf("\n");
        }
    }

    return 0;
}
