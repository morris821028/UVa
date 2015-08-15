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

double random() {
	return (double) rand() / RAND_MAX;
}
const int MAXN = 131072;
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
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 1; 
	while (testcase--) {
		n = 20000, m = 100000;
		init(n);
		printf("%d %d\n", n, m);
		vector< pair<int, int> > fa;
		for (int i = 2; i <= n; i++) {
			if (i <= 10 || rand()%1028 == 0) {
				fa.push_back({i, rand()%(i-1)+1});
			} else if (rand()%10 == 0) {
				fa.push_back({i, i - 1});
			} else {
				fa.push_back({i, i - rand()%2 - 1});
			}
		}
		random_shuffle(fa.begin(), fa.end());
		int idx = 0;
		for (int i = 0; i < m; i++) {
			if (((idx == fa.size() || rand()%3) && idx > n*3/10) || rand()%10000 == 0) {
				int test = 0;
				do {
					x = min(rand()%n + 1, n);
					y = min(rand()%n + 1, n);
//					y = max(min(x + rand()%50 - 25, n), 1);
					if (test++ > 10000)
						break;
				} while (findp(x) != findp(y));
				printf("sim %d %d\n", x, y);
			} else {
				printf("news %d %d\n", fa[idx].first, fa[idx].second);
				joint(fa[idx].first, fa[idx].second);
				idx++;
			}
		}
	}	
	return 0;
}
