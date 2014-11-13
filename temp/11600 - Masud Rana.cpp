#include <stdio.h> 
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
// similar 1390 - Interconnect
int parent[32], weight[32];
int findp(int x) {
	return parent[x] == x ? x : findp(parent[x]);
}
void joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x == y)	return;
	if (weight[x] > weight[y])
		parent[y] = x, weight[x] += weight[y];
	else
		parent[x] = y, weight[y] += weight[x];
}

#define hash_mod 1000003
struct state {
	vector<int> c;
	unsigned int hash() {
		unsigned int a = 63689, b = 378551;
		unsigned int value = 0;
		for (int i = 0; i < c.size(); i++) {
			value = value * a + c[i];
			a *= b;
		}
		return value % hash_mod;
	}
	bool operator<(const state &a) const {
		if (c.size() != a.c.size())
			return c.size() < a.c.size();
		for (int i = 0; i < c.size(); i++)
			if (c[i] != a.c[i])
				return c[i] < a.c[i];
		return false;
	}
};
map<state, double> hash[hash_mod];
double dfs(state &u) {
	if (u.c.size() == 1)	return 0;
	sort(u.c.begin() + 1, u.c.end());
	int h = u.hash();
	if (hash[h].find(u) != hash[h].end())
		return hash[h][u];
	double &ret = hash[h][u];
	double self = 0, total = 0;
	ret = 0;
	for (int i = 0; i < u.c.size(); i++)
		total += u.c[i];
	total = total - 1, self = u.c[0] - 1;
	for (int i = 1; i < u.c.size(); i++) {
		state v = u;
		v.c[0] += v.c[i];
		v.c.erase(v.c.begin() + i);
		ret += u.c[i] * dfs(v);
	}
	// E[u] = 1 + E[v] * p + E[u] * q
	ret = (ret / total) + 1;
	ret = ret / (1 - self / total);
	return ret;
}
int main() {
	int n, m, x, y;
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			parent[i] = i, weight[i] = 1;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			joint(x, y);
		}
		
		state st;
		
		for (int i = 1; i <= n; i++) {
			if (parent[i] == i && parent[i] == findp(1))
				st.c.push_back(weight[i]);
		} 
		for (int i = 1; i <= n; i++) {
			if (parent[i] == i && parent[i] != findp(1)) // root
				st.c.push_back(weight[i]);
		}
		printf("Case %d: %lf\n", ++cases, dfs(st));
	}
	return 0;
}
/*
2
3 1
2 3
4 1
2 3

9999
3 3
1 2
2 3
3 1
*/
