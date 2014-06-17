#include <stdio.h>

int main() {
    int n, m, c;
    while(scanf("%d %d %d", &n, &m, &c) == 3) {
        if(n+m+c == 0)
            break;
        if(c == 0) {
            printf("%d\n", (n-7)*(m-7)/2);
        } else {
            printf("%d\n", ((n-7)*(m-7)+1)/2);
        }
    }
    return 0;
}
