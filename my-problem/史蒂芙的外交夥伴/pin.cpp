#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
using namespace std;

const int MAXN = 65536;

int A[MAXN];
int dep[MAXN];
int parent[MAXN], weight[MAXN];
vector<int> g[MAXN];
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x == y)	return 0;
	if (weight[x] > weight[y])
		weight[x] += weight[y], parent[y] = x;
	else
		weight[y] += weight[x], parent[x] = y;
	return 1;
}
void merge(int X, int Y) {
	if (joint(X, Y))
		g[X].push_back(Y), g[Y].push_back(X);
}
int route[MAXN];
int dfs(int idx, int u, int p, int Y, int K, int &ret) {
	if (u == Y) {
		for (int i = 0; i < idx; i++)
			ret += A[route[i]] <= K;
		return 1;
	}
	for (auto v : g[u]) {
		if (v == p)	continue;
		route[idx] = v;
		if (dfs(idx+1, v, u, Y, K, ret))
			return 1;
	}
	return 0;
}
int path(int X, int Y, int K) {
	if (findp(X) != findp(Y))	return 0;
	int ret = 0;
	route[0] = X;
	dfs(1, X, 0, Y, K, ret);
	return ret;
}

int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 1; 
	while (testcase--) {
		int N = 50000, Q = 100000;
		int cmd;
		int X, Y, K;
		
		printf("%d %d\n", N, Q);
		for (int i = 1; i <= N; i++) { 
//			A[i] = rand()%N+1;
			A[i] = rand()%10000+1;
			printf("%d%c", A[i], i == N-1 ? '\n' : ' ');
		} 
		for (int i = 1; i <= N; i++)
			parent[i] = i, g[i].clear(), dep[i] = 0;
		
		vector<int> VV;
		vector< pair<int,int> > EE;
//		for (int i = 1; i <= N; i++)
//			VV.push_back(i);
//		while (VV.size() > 1) {
//			vector<int> NT;
//			for (int i = 0; i+1 < VV.size(); i+=2) {
//				EE.push_back({VV[i], VV[i+1]});
//				if (rand()%2)
//					NT.push_back(VV[i]);
//				else
//					NT.push_back(VV[i+1]);
//			}
//			if (VV.size() %2 == 1) 
//				NT.push_back(VV.back());
//			VV = NT;
//		}

		for (int i = 2; i <= N; i++) {
			if (i <= 10)
				EE.push_back({i, i-1});
			else
				EE.push_back({i, i - rand()%5 - 1});
		}
		random_shuffle(EE.begin(), EE.end());
		int d = 0, eidx = 0;
		for (int i = 0; i < Q; i++) {
			if (eidx < EE.size() && rand()%514) {
				printf("0 %d %d\n", EE[eidx].first^d, EE[eidx].second^d);
				merge(EE[eidx].first, EE[eidx].second);
				eidx++;
			} else {
				int L, R, K;
				L = rand()*rand()%N+1;
				R = rand()*rand()%N+1;
				K = rand()*rand()%N+1;
				printf("1 %d %d %d\n", L^d, R^d, K^d);
				d = path(L, R, K);
			}
//			int L, R, K;
//			L = rand()*rand()%N+1;
//			R = rand()*rand()%N+1;
//			K = rand()*rand()%N+1;
//			if (L > R)	swap(L, R);
//			if (rand()%2) {
//				printf("1 %d %d %d\n", L^d, R^d, K^d);
//				d = path(L, R, K);
//			} else {
//				printf("0 %d %d\n", L^d, R^d);
//				merge(L, R);
//			}

//			d = 0;
		}
	
		if (testcase)
			puts("");
	}	
	return 0;
}
