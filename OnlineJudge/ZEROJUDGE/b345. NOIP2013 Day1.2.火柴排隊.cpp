#include <bits/stdc++.h>
using namespace std;

int C[131072], D[131072];
long long ret = 0;
const long long mod = 99999997;
void merge(int l, int mid, int r) {
	int idx1 = l, idx2 = mid+1;
	int top = 0, cnt = 0;
	while (idx1 <= mid && idx2 <= r) {
		if (C[idx1] < C[idx2])
			D[top++] = C[idx1++], ret = (ret + cnt)%mod;
		else
			D[top++] = C[idx2++], cnt++;
	}
	while (idx1 <= mid)
		D[top++] = C[idx1++], ret = (ret + cnt)%mod;
	while (idx2 <= r)
		D[top++] = C[idx2++], cnt++;
	for (int i = 0, j = l; i < top; i++, j++)
		C[j] = D[i];
}
void DC(int l, int r) {
	if (l == r)
		return ;
	int mid = (l + r)/2;
	DC(l, mid);
	DC(mid+1, r);
	merge(l, mid, r);
}
int main() {
	int n, x;
	while (scanf("%d", &n) == 1) {
		vector< pair<int, int> > A, B;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			A.push_back({x, i});
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			B.push_back({x, i});
		}
		sort(A.begin(), A.end());
		sort(B.begin(), B.end());
		for (int i = 0; i < n; i++)
			C[B[i].second] = A[i].second;
		ret = 0;
		DC(0, n-1);
		printf("%lld\n", ret);
	}
	return 0;
}

