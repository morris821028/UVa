#include <stdio.h> 
#include <stack>
#include <algorithm>
using namespace std;
int A[100005];
pair<int, int> Tree[262144 + 10];
#define oo 0x7f7f7f7f
void build(int k, int l, int r) {
	if(l > r)	{
		Tree[k] = make_pair(-oo, -1);
		return ;
	}
	if(l == r) {
		Tree[k] = make_pair(A[l], l);
		return ;
	}
	int m = (l+r)/2;
	build(k<<1, l, m);
	build(k<<1|1, m+1, r);
	Tree[k] = max(Tree[k<<1], Tree[k<<1|1]);
}
pair<int, int> query(int k, int l, int r, int ql, int qr) {
    if(l > r)    return make_pair(-oo, -1);
    if(ql <= l && r <= qr)
        return Tree[k];
    int m = (l + r)/2;
    if(m >= qr)
        return query(k<<1, l, m, ql, qr);
    if(m < ql)
        return query(k<<1|1, m+1, r, ql, qr);
    return max(query(k<<1, l, m, ql, qr),
                query(k<<1|1, m+1, r, ql, qr));
}
int BIT[262144];
void modifyBIT(int idx, int val, int L) {
	while(idx <= L) {
		BIT[idx] = min(BIT[idx], val);
		idx += idx&(-idx);
	}
}
int queryBIT(int idx) {
	int ret = oo;
	while(idx) {
		ret = min(ret, BIT[idx]);
		idx -= idx&(-idx);
	}
	return ret;
}
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		int ret = 1, x;
		stack<int> stk;
		for(int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		build(1, 0, n-1);
		for(int i = n; i >= 1; i--)
			BIT[i] = oo;
		for(int i = n-1; i >= 0; i--) {
			modifyBIT(A[i], i, n);
			int r = queryBIT(A[i]-1);
			if(r == oo)
				r = n-1;
			pair<int, int> LL = query(1, 0, n-1, i, r);
			ret = max(ret, LL.second - i + 1);
		}
		printf("%d\n", ret);
	}
	return 0;
}
