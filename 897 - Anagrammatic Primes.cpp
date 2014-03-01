#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#define LL long long
#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
using namespace std;
int mark[maxL];
int anaP[30], at = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000000;
    for(i = 2; i < n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
    char buf[10], len, flag;
    for(i = 2; i < n; i++) {
        if(!GET(i)) {
            sprintf(buf, "%d", i);
            len = strlen(buf);
            sort(buf, buf+len);
            flag = 0;
            do {
                sscanf(buf, "%d", &j);
                if(GET(j))  flag = 1;
            } while(next_permutation(buf, buf+len) && !flag);
            if(!flag)
                anaP[at++] = i;
        }
    }
}
main() {
    sieve();
    int n, i;
    while(scanf("%d", &n) == 1 && n) {
        if(n > anaP[at-1]) {
            puts("0");
            continue;
        }
        int n10 = (int)pow(10, (int)log10(n)+1);
        for(i = 0; i < at; i++) {
            if(anaP[i] > n && anaP[i] < n10) {
                printf("%d\n", anaP[i]);
                break;
            }
        }
        if(i == at)
            puts("0");
    }
    return 0;
}
