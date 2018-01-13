#include <bits/stdc++.h>
using namespace std;
const int MAXN = 131072;
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
static const int MAXQ = 131072;
vector<pair<int, int>> Q[MAXN];
vector<int> A[MAXN], B[MAXN];
int ret[MAXQ], tree[MAXN<<1];
void add(int k, int l, int r, int x, int val) {
	if (l == r) {
		tree[k] += val;
		return;
	}
	tree[k] += val;
	int mid = (l+r)/2;
	if (x <= mid)
		add(k<<1, l, mid, x, val);
	else
		add(k<<1|1, mid+1, r, x, val);
}
int indexOf(int k, int l, int r, int val) {
	if (l == r)
		return l;
	int mid = (l+r)/2;
	if (val <= tree[k<<1])
		return indexOf(k<<1, l, mid, val);
	else
		return indexOf(k<<1|1, mid+1, r, val-tree[k<<1]);
}
int main() {
	int testcase;
	int q, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", in.str);
		n = strlen(in.str);
		for (int i = 0; i < n; i++)
			in.str[i] = in.str[i]-'a'+1;
		in.str[n] = 26, in.str[n+1] = '\0';
		in.build(n+1), in.buildH();
		
		for (int i = 0; i <= n; i++)
			A[i].clear(), B[i].clear(), Q[i].clear();
		
//		in.dump();
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			int m, k;
			scanf("%d %d", &m, &k);
			Q[m].push_back({k, i});
		}
		
		// offline processing
		for (int i = 0; i < n; i++) {
			B[n-in.sa[i]].push_back(i);
			if (in.h[i])
				A[in.h[i]].push_back(i);
		}
		
		memset(ret, -1, sizeof(ret[0])*q);
		
		int st_size = 1;
		for (st_size = 1; st_size <= 2*n; st_size <<= 1);
		memset(tree, 0, sizeof(tree[0])*st_size);
		for (int i = n; i >= 1; i--) {
			for (auto e : B[i])
				add(1, 0, n-1, e, 1);
			for (auto e : A[i])
				add(1, 0, n-1, e, -1);
			for (auto e : Q[i]) {
				if (tree[1] >= e.first)
					ret[e.second] = in.sa[indexOf(1, 0, n-1, e.first)];
			}
		}
		for (int i = 0; i < q; i++) {
			if (ret[i] == -1)
				puts("Not found");
			else
				printf("%d\n", ret[i]);
		}
	}
	return 0;
}
/*
1
abdcabdc
13
1 1
1 2
1 3
1 4
1 5
2 1
2 2
2 3
2 4
2 5
4 2
4 4
4 5
*/
