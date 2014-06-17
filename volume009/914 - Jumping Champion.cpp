#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#define LL long long
#define maxL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
using namespace std;
int mark[maxL];
vector<int> p;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            p.push_back(i);
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}
int buf[100000];
int main() {
    sieve();
    int t, L, U;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &L, &U);
        vector<int>::iterator ii, ij;
        ii = lower_bound(p.begin(), p.end(), L);
        ij = lower_bound(p.begin(), p.end(), U);
        if(*ij > U) ij--;
        int n = 0, last = *ii;
        for(ii++; ii <= ij; ii++) {
            buf[n++] = *ii-last;
            last = *ii;
        }
        sort(buf, buf+n);
        last = buf[0];
        int wc = 0, win, cnt = 1, wcnt = 0;
        int i;
        for(i = 1; i < n; i++) {
            if(buf[i] == last)  cnt++;
            else {
                if(cnt > wc) {
                    wc = cnt, win = buf[i-1], wcnt = 1;
                } else if(cnt == wc) {
                    wcnt++;
                }
                last = buf[i], cnt = 1;
            }
        }
        if(cnt > wc) {
            wc = cnt, win = buf[i-1], wcnt = 1;
        } else if(cnt == wc) {
            wcnt++;
        }
        if(n < 1 || wcnt != 1) {
            puts("No jumping champion");
        } else {
            printf("The jumping champion is %d\n", win);
        }
    }
    return 0;
}
