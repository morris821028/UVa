#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

long long B, P; 
long long tree[262144 + 10], shiftP[131072 + 10];
void modify(int k, int l, int r, int x, int val) {
	if(l > r)	return;
	if(l == r) {
		tree[k] = val;	return ;
	}
	int m = (l + r)>>1;
	if(x <= m)	
		modify(k<<1, l, m, x, val);
	else		
		modify(k<<1|1, m+1, r, x, val);
	tree[k] = (tree[k<<1]*shiftP[r - m] + tree[k<<1|1])%P;
}
long long query(int k, int l, int r, int x, int y) {
	if(l > r)	return 0;
	if(x <= l && r <= y) {
		return tree[k]*shiftP[y - r];
	}
	int m = (l + r)>>1;
	long long ret = 0;
	if(x <= m)
		ret += query(k<<1, l, m, x, y);
	if(y > m)
		ret += query(k<<1|1, m+1, r, x, y);
	return ret%P;
}
int main() { 
	char cmd[1024];
	int a, b, n, q;
	while(scanf("%lld %lld %d %d", &B, &P, &n, &q) == 4 && n) {
		shiftP[0] = 1;
		for(int i = 1; i <= n; i++)
			shiftP[i] = (shiftP[i - 1] * B)%P;
		memset(tree, 0, sizeof(tree));
		while(q--) {
			scanf("%s %d %d", cmd, &a, &b);
			if(cmd[0] == 'E')
				modify(1, 1, n, a, b);
			else
				printf("%lld\n", query(1, 1, n, a, b));
		}
		puts("-");
	}
	return 0;
}
