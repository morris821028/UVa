#include <stdio.h>
void hanoi(int n, char A, char B, char C) {
    if(n > 0) {
        hanoi(n-1, A, C, B);
        printf("Move ring %d from %c to %c\n", n, A, C);
        hanoi(n-1, B, A, C);
    }
}
int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        hanoi(n, 'A', 'B', 'C');
        puts("");
    }
    return 0;
}
