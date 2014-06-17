#include <stdio.h>
#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int main() {
    int n, i, j, x;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf("%d", &x), SET(x);
    for(i = 0, j = 0; i < 10000000; i++) {
        if(GET(i)) {
            if(j == 0) printf("%d ", i);
            j++;
            if(j >= 10)  j = 0;
        }
    }
    return 0;
}
