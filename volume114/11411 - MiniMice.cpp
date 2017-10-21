#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
const int MAXN = 5000005;
const int MAXL = (MAXN>>5)+1;
int mark[MAXL];
short ff[MAXN];
void sieve() {
    int n = 5000000;
    SET(1);
    for (int i = 0; i <= n; i++)
        ff[i] = 1;
    for (int i = 2; i <= n; i++) {
        if (!GET(i)) {
            for (int k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            ff[i] = 2;
            for (int j = i+i; j <= n; j += i) {
                int t = j/i, k = 1;
                while (t%i == 0)
                    t /= i, k++;
                ff[j] = ff[j] * (k+1);
            }
        }
    }
}

int fetch(int cnt[], int &cidx) {
    for (; cidx < 512; cidx++) {
        if (cnt[cidx]) {
            cnt[cidx]--;
            return cidx;
        }
    }
    return -1;
}
int main() {
    sieve();
    int testcase, l, r;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &l, &r);
        int n = r-l+1, cnt[512] = {}, cidx = 0;
        for (int i = l; i <= r; i++)
            cnt[ff[i]]++;
        
        int ret = 0;
        {
            
            int l = fetch(cnt, cidx);
            int r = l;
            for (int i = 1; i+1 < n; i += 2) {
                int p = fetch(cnt, cidx);
                int q = fetch(cnt, cidx);
                ret = max(ret, p-l);
                ret = max(ret, q-r);
                l = p, r = q;
            }
            if (n%2 == 0) {
                int p = fetch(cnt, cidx);
                ret = max(ret, p-l);
                ret = max(ret, p-r);
            }
            ret = max(ret, r-l);
        }	
        printf("%d\n", ret);
    }
    return 0;
}
/*
 2
 5 8
 21 24
 
 1
 3350083 3350088
 */

