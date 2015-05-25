class Solution {
public:
#define MAXN 20000000
#define MAXL (MAXN>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
    int mark[MAXL];
    int sieve(int n) {
        register int i, j, k;
        int ret = 0;
        SET(1);
        for (i = 2; i < n; i++) {
            if (!GET(i)) {
                for (k = n/i, j = i*k; k >= i; k--, j -= i)
                    SET(j);
            }
            ret += !GET(i);
        }
        return ret;
    }
    int countPrimes(int n) {
        return sieve(n);
    }
};