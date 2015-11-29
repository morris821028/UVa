#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXS = 131072;
struct SuffixArray {
    int sa[MAXS], h[MAXS], n;
    int w[MAXS], ta[MAXS], tb[MAXS];
    char str[MAXS];
    void sort(int *x, int *y, int m) {
        static int i;
        for(i = 0; i < m; i++)
            w[i] = 0;
        for(i = 0; i < n; i++)
            w[x[y[i]]]++;
        for(i = 1; i < m; i++)
            w[i] += w[i-1];
        for(i = n-1; i >= 0; i--)
            sa[--w[x[y[i]]]] = y[i];
    }
    bool cmp(int *r, int a, int b, int l) {
        if(r[a] == r[b]) {
            if(a+l >= n || b+l >= n)
                return false;
            return r[a+l] == r[b+l];
        }
        return false;
    }
    void build_h() {
        int i, j, k;
        for(i = 0; i < n; i++)  ta[sa[i]] = i;
        for(i = 0; i < n; i++) {
            if(ta[i] == 0) {
                h[ta[i]] = 0;
                continue;
            }
            if(i == 0 || h[ta[i-1]] <= 1)
                k = 0;
            else
                k = h[ta[i-1]]-1;
            while(str[sa[ta[i]-1]+k] == str[sa[ta[i]]+k])
                k++;
            h[ta[i]] = k;
        }
    }
    void build() {// x: rank, y: second key
        int i, k, m = 128, p;
        int *x = ta, *y = tb, *z;
        n = strlen(str);
        x[n] = 0;
        for(i = 0; i < n; i++)
            x[i] = str[i], y[i] = i;
        sort(x, y, m);
        for(k = 1, p = 1; p < n; k *= 2, m = p) {
            for(p = 0, i = n-k; i < n; i++)
                y[p++] = i;
            for(i = 0; i < n; i++) {
                if(sa[i] >= k) {
                    y[p++] = sa[i]-k;
                }
            }
            sort(x, y, m);
            z = x, x = y, y = z;
            for(i = 1, p = 1, x[sa[0]] = 0; i < n; i++)
                x[sa[i]] = cmp(y, sa[i-1], sa[i], k) ? p-1 : p++;
        }
    }
};
SuffixArray in;
const int MOD = 1e9 + 7;
int main() {
	int testcase, K, cases = 0;
	scanf("%d", &testcase);
    while(testcase--) {
    	scanf("%s %d", in.str, &K);
    	
        in.build();
        in.build_h();
//        for(int i = 0; i < in.n; i++)
//        	printf("%s %d\n", in.str + in.sa[i], in.h[i]);
        long long ret = 0;
        for (int i = 0; i < in.n; ) {
    		long long cnt = 0;
    		long long sum = in.n - in.sa[i] - K + 1;
    		if (sum > 0) {
	    		cnt += sum * (sum-1)/2, i++;
	    		while (i < in.n && in.h[i] >= K) {
	    			long long t = in.n - in.sa[i] + 1 - K;
	    			cnt += (sum * t)%MOD + t * (t-1) / 2;
	    			cnt %= MOD;
	    			sum += t;
	    			sum %= MOD;
					i++;
	    		}
	    		ret += cnt;
	    		ret %= MOD;
	    	} else {
	    		i++;
			}
		}
        printf("Case #%d: %lld\n", ++cases, ret);
    }
    return 0;
}
