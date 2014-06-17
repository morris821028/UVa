#include <stdio.h>
int step = 0;
void subH(int n, char a, char b, char c) {
    if(n > 0) {
        subH(n-1, a, c, b);
        printf("ring %d : %c -> %c\n", n, a, c);
        step++;
        subH(n-1, b, a, c);
    }
}
void H(int n, char a, char b, char c) {
    while(n > 0) {
        subH(n-1, a, c, b);
        printf("ring %d : %c -> %c\n", n, a, c);
        step++;
        n -= 2;
        if(n == 0)  return;
        subH(n-1, b, c, a);
        printf("ring %d : %c -> %c\n", n, b, c);
        step++;
        subH(n-2, a, b, c);
        printf("ring %d : %c -> %c\n", n-1, a, b);
        step++;
        n -= 2;
        if(n == 0)  return;
        subH(n-2, c, b, a);
        printf("ring %d : %c -> %c\n", n-1, c, b);
        step++;
        n -= 2;
    }
}
int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        step = 0;
        H(n, 'a', 'b', 'c');
        printf("共移動了 %d 步\n", step);
    }
    return 0;
}
