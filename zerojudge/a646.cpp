#include <stdio.h>
int a, b, n, i, j;
char s[9];
int sol(int n) {
    int r, mn = 0xffff;
    for(i = n; i >= 1; i--) {
        r = i*a/b;
        if(i*a%b < mn)
            mn = i*a%b, j = i;
    }
    if(mn == 0xffff)
        return 0;
    r = j*a/b;
    return sol(n-j+r) + r;
}
int main() {
    while(scanf("%d %s", &n, &s) == 2) {
        for(i = 2, a = 0, b = 1; s[i]; i++)
            b *= 10, a = a*10 + s[i]-'0';
        printf("%d\n", sol(n)+n);
    }
    return 0;
}
