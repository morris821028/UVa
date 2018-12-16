#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 6000005;
const int INF = 0x3f3f3f3f;
int A[MAXN];
int BLOCK_SIZE;
vector<int> B[4096];
void replace(int pos, int val) {
	int bid = pos/BLOCK_SIZE;
	int oldVal = A[pos];
	vector<int> &b = B[bid];
	for (int i = 0; i < b.size(); i++) {
		if (b[i] == oldVal) {
			b.erase(b.begin()+i);
			break;
		}
	}
	auto it = upper_bound(b.begin(), b.end(), val);
	b.insert(it, val);
	A[pos] = val;
}
int count(int l, int r, int val) {
	int lb = l/BLOCK_SIZE, rb = r/BLOCK_SIZE;
	int ret = 0;
	if (lb == rb) {
		for (int i = l; i <= r; i++) {
			if (A[i] <= val)
				ret++;
		}
		return ret;
	}
	lb++;
	for (int i = l; i < lb*BLOCK_SIZE; i++) {
		if (A[i] <= val)
			ret++;
	}
	for (int i = rb*BLOCK_SIZE; i <= r; i++) {
		if (A[i] <= val)
			ret++;
	}
	for (int i = lb; i < rb; i++)  {
		int cnt = upper_bound(B[i].begin(), B[i].end(), val) - B[i].begin();
		ret += cnt;
	}
	return ret;
}
int main() {
	int n, q;
	int pos, val, l, r, cmd;
	while (scanf("%d %d", &n, &q) == 2) {
		for (int i = 0; i < n; i++)
			A[i] = INF;
		BLOCK_SIZE = max((int)sqrt(n), 128);
		for (int i = 0; i < n/BLOCK_SIZE+1; i++)
			B[i].clear();
		for (int i = 0; i < q; i++) {
			scanf("%d", &cmd);
			if (cmd == 0) {
				scanf("%d %d", &pos, &val);
				replace(pos, val);
			} else {
				scanf("%d %d %d", &l, &r, &val);
				int ret = count(l, r, val);
				printf("%d\n", ret);
			}
		}
	}
	return 0;
}
/*
5  10
0  0  5
0  1  6
0  2  7
1  0  2  5
1  0  2  6
0  3  5
0  4  6
1  0  4  5
0  0  8
1  0  4  7

*/
