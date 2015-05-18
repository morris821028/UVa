#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;
class SegementTree {
public:
	struct Node {
	    int l, r, lson, rson;
	    int mx;
	} node[1048576];
	int nodesize;
	int init(int l, int r) {
		nodesize = 0;
		int root = build(l, r);
		return root;
	}
	int build(int l, int r) {
	    if (l > r)  return 0;
	    int k = nodesize++;
	    node[k].l = l, node[k].r = r, node[k].mx = -9999;
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
	    node[k].mx = max(node[p].mx, val);
	    if (node[k].l == node[k].r) return k;
	    int m = (node[k].l + node[k].r)/2;
	    if (x <= m)
	        node[k].lson = change(node[p].lson, x, val);
	    else
	        node[k].rson = change(node[p].rson, x, val);
	    return k;
	}
	int query(int k, int l, int r) {
	    if (l <= node[k].l && node[k].r <= r)
	        return node[k].mx;
	    int m = (node[k].l + node[k].r)/2;
	    if (r <= m)
	        return query(node[k].lson, l, r);
	    else if (l > m)
	        return query(node[k].rson, l, r);
	    else
	    	return max(query(node[k].lson, l, r), query(node[k].rson, l, r));
	}
} segTree;

const int MAXN = 2048;
const int SHIFT = 4096, MAXR = 8192;	
class PublicTransitHard {
public:
	vector<int> g[MAXN];
	int dp[MAXN][3];
	int dp2[MAXN][2];
	int ret1, ret2, limitX, testA;
	void dfs(int u, int p) {
		dp[u][0] = 0, dp[u][1] = 0, dp[u][2] = 0;
		dp2[u][0] = 0, dp2[u][0] = 0;
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (v == p)
				continue;
			dfs(v, u);
			int d = dp[v][0]+1;
			if (d > dp[u][2])
				dp[u][2] = d;
			if (dp[u][2] > dp[u][1])
				swap(dp[u][2], dp[u][1]);
			if (dp[u][1] > dp[u][0])
				swap(dp[u][1], dp[u][0]);
				
			d = max(dp[v][0] + dp[v][1], dp2[v][0]);
			if (d > dp2[u][1])
				dp2[u][1] = d;
			if (dp2[u][1] > dp2[u][0])
				swap(dp2[u][0], dp2[u][1]);
		}
	}
	void dfs2(int u, int p, int segId, int depth, int mnLIM) {
		int p2 = depth, v2 = dp[u][0];
		int mx = segTree.query(segId, limitX - p2 - v2 + 1 + SHIFT, MAXR);
		int LIM = limitX - (depth - p2 + mx + v2);
//		printf("query [%d, oo] = %d\n", limitX - p2 - v2 + 1, mx);
//		printf("testA %d - %d, %d %d, LIM = %d, mx = %d\n", testA, u, p2, v2, LIM, mx);
		if (depth > mnLIM)
			return ;
		if (LIM >= 0 && dp[u][0] + dp[u][1] <= limitX && dp2[u][0] <= limitX) {
//			printf("----- connect %d %d, \n", testA, u);
			if (testA == u)	ret1++;
			else			ret2++;
		}
			
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (v == p)
				continue;
				
			int d = dp[v][0]+1;
			if (d != dp[u][0])
				v2 = dp[u][0];
			else
				v2 = dp[u][1];
			
			if (d == dp[u][0]) {
				if (dp[u][1] + dp[u][2] > limitX)
					continue;
			} else if (d == dp[u][1]) {
				if (dp[u][0] + dp[u][2] > limitX)
					continue;
			} else {
				if (dp[u][0] + dp[u][1] > limitX)
					continue;
			}
			
			d = max(dp[v][0] + dp[v][1], dp2[v][0]);
			if (d == dp2[u][0]) {
				if (dp2[u][1] > limitX)
					continue;
			} else {
				if (dp2[u][0] > limitX)
					continue;
			}
			
			
//			printf("dfs %d %d, update [%d] = %d\n", p2, v2, v2 - p2, v2 + p2);
			int mx = segTree.query(segId, limitX - p2 - v2 + 1 + SHIFT, MAXR);
			int LIM2 = limitX - (depth - p2 + mx + v2);
			int segId3 = segTree.change(segId, v2 - p2 + SHIFT, v2 + p2);
//			printf("dfs %d %d, update [%d] = %d, LIM2 = %d\n", p2, v2, v2 - p2, v2 + p2, LIM2);
			dfs2(v, u, segId3, depth+1, min(mnLIM, depth+LIM2));
		}
	}
	int countValidTeleporters(int N, vector<int> edges, int X) {
		ret1 = ret2 = 0, limitX = X;
		for (int i = 0; i < N; i++)
			g[i].clear();
		
		for (int i = 0; i < edges.size(); i++) {
			int u = i+1, v = edges[i];
			g[u].push_back(v);
			g[v].push_back(u);
		}
		
		for (int A = 0; A < N; A++) {
			dfs(A, -1);
			int root = segTree.init(0, MAXR);
			testA = A;
//			puts("-----");
			dfs2(A, -1, root, 0, 9999);
		}
		return ret1 + ret2/2;
	}	
};

int main() {
	PublicTransitHard test;
//	int N = 4;
//	int edges[] = {0, 1, 2};
//	int X = 1;

//	int N = 3;
//	int edges[] = {0, 0};
//	int X = 2;

//	int N = 6;
//	int edges[] = {0, 0, 0, 1, 1};
//	int X = 2;

//	int N = 7;
//	int edges[] = {0, 1, 0, 1, 2, 4};
//	int X = 3;
	
//	int N = 16;
//	int edges[] = {0, 1, 0, 2, 0, 0, 4, 5, 8, 9, 10, 11, 8, 4, 6};
//	int X = 7;
	
	int N = 56;
	int edges[] = {0, 1, 1, 3, 1, 5, 1, 0, 8, 8, 10, 10, 12, 10, 10, 8, 16, 16, 18, 19, 19, 21, 19, 19, 24, 25, 25, 27, 18, 0, 30, 30, 30, 33, 34, 34, 34, 30, 38, 39, 39, 38, 42, 43, 0, 45, 45, 45, 48, 45, 45, 51, 45, 53, 54};
	int X = 12;
	
	int ret = test.countValidTeleporters(N, vector<int>(edges, edges + N - 1), X);
	printf("%d\n", ret);
	return 0;
} 
