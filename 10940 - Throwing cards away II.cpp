#include <stdio.h>

int f(int n) {
    if(n <= 1)
        return 1;
    if(n&1)
        return (f((n+1)/2)-1)*2;
    else
        return f(n/2)*2;
}
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        printf("%d\n", f(n));
    }
    return 0;
}
