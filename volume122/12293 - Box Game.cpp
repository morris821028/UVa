#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) && n)
        n++, puts((n&(n-1)) ? "Alice" : "Bob");
    return 0;
}
