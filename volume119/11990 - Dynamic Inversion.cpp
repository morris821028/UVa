#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXN 200005
int N, M, DEL;
int ST[20][MAXN], BIT[20][MAXN];
int MP[MAXN];
long long invPair;
void modifySUM(int BIT[], int x, int v, int L) {
	while(x <= L) {
		BIT[x] += v;
		x += x&(-x);
	}
} 
int querySUM(int BIT[], int x) {
	int ret = 0;
	while(x) {
		ret += BIT[x];
		x -= x&(-x); 
	} 
	return ret;
} 
void buildST(int k, int l, int r, int dep) {
	for(int i = l; i <= r; i++)
		ST[dep][i] = ST[dep-1][i], BIT[dep][i] = 0;
	if(l >= r)	return ;
	int m = (l + r)/2;
	buildST(k<<1, l, m, dep+1);
	buildST(k<<1|1, m+1, r, dep+1);
	sort(ST[dep] + l, ST[dep] + r+1);
}
void queryPrefix(int k, int l, int r, int dep, int x, int y, int val) {
	if(x <= l && r <= y) {
		int pos = upper_bound(ST[dep] + l, ST[dep] + r+1, val) - ST[dep];
		int pre = querySUM(BIT[dep]+l-1, pos - l);
		invPair -= (r - pos + 1) - (querySUM(BIT[dep]+l-1, r-l + 1) - pre);
		return ;
	}
	if(l >= r)	return ;
	int m = (l + r)/2;
	if(x <= m)
		queryPrefix(k<<1, l, m, dep+1, x, y, val);
	if(y > m)
		queryPrefix(k<<1|1, m+1, r, dep+1, x, y, val);
}
void querySuffix(int k, int l, int r, int dep, int x, int y, int val) {
	if(x <= l && r <= y) {
		int pos = upper_bound(ST[dep] + l, ST[dep] + r+1, val) - ST[dep];
		int pre = querySUM(BIT[dep]+l-1, pos - l);
		invPair -= (pos - l) - pre;
		return ;
	}
	if(l >= r)	return ;
	int m = (l + r)/2;
	if(x <= m)
		querySuffix(k<<1, l, m, dep+1, x, y, val);
	if(y > m)
		querySuffix(k<<1|1, m+1, r, dep+1, x, y, val);
}
void update(int k, int l, int r, int dep, int x, int val) {
	if(l == r) {
		modifySUM(BIT[dep]+l-1, 1, 1, r-l+1);
		return;
	}
	if(l >= r)	return ;
	int m = (l + r)/2;
	if(x <= m)
		update(k<<1, l, m, dep+1, x, val);
	else
		update(k<<1|1, m+1, r, dep+1, x, val);
	int pos = lower_bound(ST[dep] + l, ST[dep] + r+1, val) - ST[dep];
	modifySUM(BIT[dep]+l-1, pos - l + 1, 1, r-l+1);
}
int main() {
	while(scanf("%d %d", &N, &M) == 2) {
		invPair = 0;
		for(int i = 1; i <= N; i++)
			BIT[0][i] = 0;
		for(int i = 1; i <= N; i++) {
			scanf("%d", &ST[0][i]);
			MP[ST[0][i]] = i;
			invPair += i - 1 - querySUM(BIT[0], ST[0][i]);
			modifySUM(BIT[0], ST[0][i], 1, N);
		}
		buildST(1, 1, N, 1);
		
		while(M--) {
			scanf("%d", &DEL);
			printf("%lld\n", invPair);
			queryPrefix(1, 1, N, 1, 1, MP[DEL] - 1, DEL);
			querySuffix(1, 1, N, 1, MP[DEL] + 1, N, DEL);
			update(1, 1, N, 1, MP[DEL], DEL);
		}
	}
	return 0;
}
/*
5 4
1
5
3
4
2
5
*/
