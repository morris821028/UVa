#include <stdio.h>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;
const int MAXN = 131072;
struct Edge {
    int x, y, v;
    Edge(int a = 0, int b = 0, int c = 0):
    x(a), y(b), v(c) {}
    bool operator<(const Edge &a) const {
        return v > a.v;
    }
};

int parent[MAXN], weight[MAXN];
void init(int n) {
    for(int i= 0; i <= n; i++)
        parent[i] = i, weight[i] = 1;
}
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y) return 0;
    if(weight[x] > weight[y])
        weight[x] += weight[y], parent[y] = x;
    else
        weight[y] += weight[x], parent[x] = y;
    return 1;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int K, N, M, x, y, v, mxv = 0;
		vector<Edge> A;
		scanf("%d %d %d", &K, &N, &M);
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &x, &y, &v);
			A.push_back(Edge(x, y, v));
			mxv = max(mxv, v);
		}
		sort(A.begin(), A.end());
		if (K == 1) {
			printf("%d\n", 0);
			continue;
		}
		if (K >= N) {
			printf("%d\n", mxv);
			continue;
		}
		init(N);
		int cc = N, ret = 0;
		for (int i = 0; i < A.size(); i++) {
			if (joint(A[i].x, A[i].y))
				cc--;
			ret = A[i].v;
			if (cc < K)		break;
		}
		if (cc >= K)
			printf("0\n");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
2

3 6 4
0 4 9
0 5 14
1 3 31
1 5 5

4 11 11
0 1 6
0 6 23
1 3 23
1 10 5
2 3 24
2 5 11
2 9 55
3 5 9
3 10 8
7 10 7
8 9 5
*/
