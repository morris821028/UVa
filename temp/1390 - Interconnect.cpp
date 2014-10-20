#include <stdio.h> 
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

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
	sort(u.c.begin(), u.c.end());
	if (u.c.size() == 1)	return 0;
	
	int h = u.hash();
	if (hash[h].find(u) != hash[h].end())
		return hash[h][u];
	double &ret = hash[h][u];
	double self = 0, total = 0;
	ret = 0;
	for (int i = 0; i < u.c.size(); i++) {
		self += u.c[i] * (u.c[i] - 1) / 2.0;
		total += u.c[i];
	}
	total = total * (total - 1) / 2.0;
	for (int i = 0; i < u.c.size(); i++) {
		for (int j = i+1; j < u.c.size(); j++) {
			state v = u;
			v.c[i] += v.c[j];
			v.c.erase(v.c.begin() + j);
			ret += u.c[i] * u.c[j] * dfs(v);
		}
	}
	// E[u] = 1 + E[v] * p + E[u] * q
	ret = (ret / total) + 1;
	ret = ret / (1 - self / total);
	return ret;
}
int main() {
	int n, m, x, y;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			parent[i] = i, weight[i] = 1;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			joint(x, y);
		}
		
		state st;
		for (int i = 1; i <= n; i++) {
			if (parent[i] == i) // root
				st.c.push_back(weight[i]);
		}
		printf("%lf\n", dfs(st));
	}
	return 0;
}
