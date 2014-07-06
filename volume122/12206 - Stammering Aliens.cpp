#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

struct SuffixArray {
    int sa[40005], h[40005], n;
    int w[40005], ta[40005], tb[40005];
    char str[40005];
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
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
    int m;
    while(scanf("%d", &m) == 1 && m) {
    	scanf("%s", in.str);
        in.build();
        in.build_h();
        if(m == 1) {
        	printf("%d %d\n", in.n, 0);
        	continue;
    	}
//        for(int i = 0; i < in.n; i++)
//        	printf("%s %d\n", in.str + in.sa[i], in.h[i]);
        int l = 1, r = in.n, mid, ret = -1, retpos;
        while(l <= r) {
        	mid = (l + r)/2;
        	int cnt = 1, mxtime = 0, mxpos = 0;
        	for(int i = 0; i <= in.n; i++) {
        		if(i != in.n && in.h[i] >= mid)
        			cnt++;
        		else {
        			if(mxtime < cnt)
        				mxtime = cnt;
        			if(cnt >= m) {
        				int j = i;
        				do {
        					j--;
        					mxpos = max(mxpos, in.sa[j]);
        				} while(in.h[j] >= mid && j >= 0);
        			}
        			cnt = 1;
        		}
        	}
        	if(mxtime >= m)
        		l = mid + 1, ret = mid, retpos = mxpos;
        	else
        		r = mid - 1;
        }
        if(ret == -1)
        	puts("none");
        else
        	printf("%d %d\n", ret, retpos);
    }
    return 0;
}
/*
1
aaaaa
2
ufzyetzjulljnkbaohjsqpiucxjo
*/
