#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

struct Node {
    int l, r, lson, rson;
    int sum;
} node[1048576 * 23];
int nodesize = 0;
int root[1048576];
int build(int l, int r) {
    if (l > r)  return 0;
    int k = nodesize++;
    node[k].l = l, node[k].r = r, node[k].sum = 0;
    node[k].lson = node[k].rson = 0;
    if (l == r) return k;
    int m = (l + r)/2;
    node[k].lson = build(l, m);
    node[k].rson = build(m+1, r);
    return k;
}

int change(int p, int x, int val) {
    int k = nodesize++;
    node[k] = node[p];
    node[k].sum += val;
    if (node[k].l == node[k].r) return k;
    int m = (node[k].l + node[k].r)/2;
    if (x <= m)
        node[k].lson = change(node[p].lson, x, val);
    else
        node[k].rson = change(node[p].rson, x, val);
    return k;
}

int query(int tp, int tq, int k) {
    if (node[tp].l == node[tp].r)
        return node[tp].l;
    int t = node[node[tp].lson].sum - node[node[tq].lson].sum;
    if (k <= t)
        return query(node[tp].lson, node[tq].lson, k);
    else
        return query(node[tp].rson, node[tq].rson, k - t);
}
#define maxL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[100000], Pt = 0;
void sieve() {
	register int i, j, k;
	SET(1);
	int n = 1000000;
	for(i = 2; i <= n; i++) {
		if(!GET(i)) {
			for (k = n/i, j = i*k; k >= i; k--, j -= i)
				SET(j);
			P[Pt++] = i;
		}
	}
}

int fpath[30];
int rank[1048576], arank[1048576], ridx = 0;
void dfsBuild(int idx, long long v, int mxdep, int dep) {
	if (dep == mxdep) {
		rank[v] = ++ridx;
		arank[ridx] = v;
		return ;
	} 
	for (int i = idx; i < Pt && v * P[i] <= 1000000; i++)
		fpath[dep] = P[i], dfsBuild(i, v * P[i], mxdep, dep+1);
}
void printfactor(int n) {
    for(int i = 0, j; i < Pt && P[i] * P[i] <= n; i++) {
		if(n%P[i] == 0) {
			for(j = 0; n%P[i] == 0; n /= P[i], j++)
				printf(" %d", P[i]);
		}		
	}
	if (n != 1)	printf(" %d", n);
	puts("");
}
int main() {
	sieve();
	for (int i = 1; i < 20; i++)
		dfsBuild(0, 1, i, 0);    
		    
	nodesize = 1;
    root[0] = build(1, 1000000);        
	for (int i = 1; i <= 1000000; i++) {
		if (rank[i])
        	root[i] = change(root[i-1], rank[i], 1);
        else
        	root[i] = root[i-1];
    }
    
    int testcase, cases = 0, x, y, k;
    scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%d %d %d", &x, &y, &k);
    	int ret = arank[query(root[y], root[x-1], k)];
    	printf("Case %d:", ++cases);
		printfactor(ret);
    }
    return 0;
}
/*
 7 3
 1 5 2 6 3 7 4
 2 5 3
 4 4 1
 1 7 3
 */

