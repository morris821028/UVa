#include <stdio.h>
#include <math.h>
void bNum(int n) {
    if(n) {
        bNum(n/2);
        printf("%d", n%2);
    }
}
void transform(int n) {
    if(n == 1) {
        printf("0");
        return;
    }
    transform((int)log2(n));
    bNum(n);
}
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        transform(n);
        puts("");
    }
    return 0;
}
