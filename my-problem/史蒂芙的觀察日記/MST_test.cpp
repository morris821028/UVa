#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 131072;
struct Edge {
    int x, y, v;
    Edge(int a = 0, int b = 0, int c = 0):
    x(a), y(b), v(c) {}
    bool operator<(const Edge &a) const {
        return v < a.v;
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
	int n, m, x, y, w, u, v, cmd;
	int cases = 0; 
	while (scanf("%d %d", &n, &m) == 2) {
		printf("Case #%d\n", ++cases);
		vector<Edge> A;
		int mst = 0;
		init(n);
		for (int i = 1; i <= m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			if (!(A.size() == n-1 && A.back().v <= w)) {
				if (joint(x, y)) {
					A.push_back(Edge(x, y, w));
					sort(A.begin(), A.end());
					mst += w;
				} else {
					mst = 0;
					init(n);
					A.push_back(Edge(x, y, w));
					sort(A.begin(), A.end());
					vector<Edge> B;
					
					for (int j = 0; j < A.size(); j++) {
					    x = A[j].x, y = A[j].y;
		                if (joint(x, y)) {
		                    mst += A[j].v;
		                    B.push_back(A[j]);
		                } else {
	//	                	printf("eeeeee %d %d %d\n", x, y, A[j].v);
		                }
					}
					A = B;
				}
			}
			printf("%d\n", mst);
		}
	}
	return 0;
}
/*
3 3
1 2 1
1 3 2
2 3 4
*/
