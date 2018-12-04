#include <bits/stdc++.h>
using namespace std;

const int MAXN = 262144;
struct SuffixArray {
    int sa[MAXN], h[MAXN], n;
    int w[MAXN], ta[MAXN], tb[MAXN];
    char str[MAXN];
    void sort(int *x, int *y, int m) {
        for (int i = 0; i < m; i++) w[i] = 0;
        for (int i = 0; i < n; i++) w[x[y[i]]]++;
        for (int i = 1; i < m; i++) w[i] += w[i-1];
        for (int i = n-1; i >= 0; i--)  sa[--w[x[y[i]]]] = y[i];
    }
    bool cmp(int *r, int a, int b, int l) {
        if (r[a] == r[b]) {
            if (a+l >= n || b+l >= n)
                return false;
            return r[a+l] == r[b+l];
        }
        return false;
    }
    void buildH() {
        for (int i = 0; i < n; i++)  ta[sa[i]] = i;
        for (int i = 0; i < n; i++) {
            if(ta[i] == 0) {
                h[ta[i]] = 0;
                continue;
            }
            int k;
            if (i == 0 || h[ta[i-1]] <= 1)
                k = 0;
            else
                k = h[ta[i-1]]-1;
            while (str[sa[ta[i]-1]+k] == str[sa[ta[i]]+k])
                k++;
            h[ta[i]] = k;
        }
    }
    void build(int n) {// x: rank, y: second key
        int m = 128;
        int *x = ta, *y = tb, *z;
        this->n = n;
        x[n] = 0;
        for (int i = 0; i < n; i++)
            x[i] = str[i], y[i] = i;
        sort(x, y, m);
        for (int k = 1, p = 1, i; p < n; k *= 2, m = p) {
            for (p = 0, i = n-k; i < n; i++)
                y[p++] = i;
            for (i = 0; i < n; i++) {
                if(sa[i] >= k) {
                    y[p++] = sa[i]-k;
                }
            }
            sort(x, y, m);
            z = x, x = y, y = z;
            for (i = 1, p = 1, x[sa[0]] = 0; i < n; i++)
                x[sa[i]] = cmp(y, sa[i-1], sa[i], k) ? p-1 : p++;
        }
    }
    void dump() {
    	printf("-- %d\n", n);
    	for (int i = 0; i < n; i++)
    		printf("%s %d\n", str + sa[i], h[i]);
	}
};
SuffixArray in;
static char s[MAXN];

int64_t distinct(int n) {
	in.build(n);
	in.buildH();
	int64_t ret = 0;
	for (int i = 0; i < n; i++)
		ret += n-in.sa[i] - in.h[i];
	return ret;
}

int64_t distinct_k(char s[], int k) {
	int n = strlen(s);
	memcpy(in.str, s, sizeof(s[0])*n);
	memcpy(in.str+n, s, sizeof(s[0])*n);
	in.str[2*n] = '\0';
	int64_t p = distinct(2*n);
	if (k == 2)
		return p;
	memcpy(in.str+2*n, s, sizeof(s[0])*n);
	in.str[3*n] = '\0';
	int64_t q = distinct(3*n);
	return p + (q-p)*(k-2);
}
int main() {
	int testcase, cases = 0, k;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s %d", s, &k);
		assert(k >= 2);
		int64_t ret = distinct_k(s, k);
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
4
ab  2
ab  3
abc  5
aba  4
*/
