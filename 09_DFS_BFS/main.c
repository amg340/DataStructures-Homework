#include <stdio.h>

#define MAX 50

void dfs(int g[MAX][MAX], int n, int u, int visited[MAX]) {
    visited[u] = 1;
    printf("%d ", u);
    for (int v = 0; v < n; v++) {
        if (g[u][v] && !visited[v]) dfs(g, n, v, visited);
    }
}

void bfs(int g[MAX][MAX], int n, int start) {
    int visited[MAX] = {0};
    int dist[MAX];
    for (int i = 0; i < n; i++) dist[i] = -1;

    int q[MAX], front = 0, back = 0;

    visited[start] = 1;
    dist[start] = 0;
    q[back++] = start;

    printf("BFS order: ");
    while (front < back) {
        int u = q[front++];
        printf("%d ", u);

        for (int v = 0; v < n; v++) {
            if (g[u][v] && !visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                q[back++] = v;
            }
        }
    }
    printf("\n");

    printf("BFS distances from %d:\n", start);
    for (int i = 0; i < n; i++) {
        printf("node %d -> dist %d\n", i, dist[i]);
    }
}

int main() {
    int n = 6;
    int g[MAX][MAX] = {0};

    // sample edges
    g[0][1]=g[1][0]=1;
    g[0][2]=g[2][0]=1;
    g[1][3]=g[3][1]=1;
    g[2][3]=g[3][2]=1;
    g[3][4]=g[4][3]=1;
    g[4][5]=g[5][4]=1;

    int visited[MAX] = {0};
    printf("DFS order from 0: ");
    dfs(g, n, 0, visited);
    printf("\n\n");

    bfs(g, n, 0);
    return 0;
}
