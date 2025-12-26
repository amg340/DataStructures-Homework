// 02_hanoi/main.c
#include <stdio.h>

long long moves = 0;

void hanoi(int n, char from, char aux, char to) {
    if (n == 1) {
        printf("Move disk 1 from %c -> %c\n", from, to);
        moves++;
        return;
    }
    hanoi(n - 1, from, to, aux);
    printf("Move disk %d from %c -> %c\n", n, from, to);
    moves++;
    hanoi(n - 1, aux, from, to);
}

int main() {
    int n;
    printf("Enter number of disks: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 0;
    }

    hanoi(n, 'A', 'B', 'C');
    printf("Total moves = %lld\n", moves);
    return 0;
}
