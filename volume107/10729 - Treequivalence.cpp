#include <stdio.h> 
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
// special !!!!!!!! normal planar representation
class Tree {
	public:
	vector<int> g[10005];
	char label[10005];
	int n;
	map<vector<int>, int> tmpR;
	int dfsMinExp(int u, int p) {
		vector<int>	branch;
		for(int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if(v == p)	continue;
			branch.push_back(dfsMinExp(v, u));
		}
		sort(branch.begin(), branch.end());
	
		int a = 63689, b = 378551;
		int ret = 0;
		branch.push_back(label[u]);
		for(int i = 0; i < branch.size(); i++)
			ret = ret * a + branch[i], a *= b;
		return ret;
	}
	vector<int> getTreeMinExp() { // simple (no plane)
		if(n == 1)	return vector<int>(1, (int)label[1]);
		int deg[10005] = {}, u, v;
		int topo[10005] = {}, idx = 0;
		queue<int> Q;
		for(int i = 1; i <= n; i++) {
			deg[i] = g[i].size();
			if(deg[i] == 1)	Q.push(i);
		}
		while(!Q.empty()) {
			u = Q.front(), Q.pop();
			topo[idx++] = u;
			for(int i = 0; i < g[u].size(); i++) {
				v = g[u][i];
				if(--deg[v] == 1)
					Q.push(v);
			}
		}
		vector<int> ret;
		ret.push_back(dfsMinExp(topo[idx-1], -1));
		ret.push_back(dfsMinExp(topo[idx-2], -1));
		return ret;
	}
	
	int dfsCheck(Tree& tree, int u, int p) {
		vector<int> branch;
		if (p < 0) { // root
			for (int i = 0; i < tree.g[u].size(); i++) {
				int v = tree.g[u][i];
				branch.push_back(dfsCheck(tree, v, u));
			}
			
			int idx = 0, bn = branch.size();
			for (int s = 1; s < bn; s++) { // find cycle minExp
				for (int i = idx, j = s, k = 0; k < bn; k++) {
					if (branch[i] != branch[j]) {
						if (branch[j] < branch[i])	idx = s;
						break;
					}
					if (++i >= bn)	i = 0;
					if (++j >= bn)	j = 0;
				}
			}
			rotate(branch.begin(), branch.begin() + idx, branch.end());
		} else {
			int idx;
			for (idx = 0; tree.g[u][idx] != p; idx++);
			
			while (true) {
				idx++;
				if (idx >= tree.g[u].size())
					idx = 0;
				int v = tree.g[u][idx];
				if (v == p)	break;
				branch.push_back(dfsCheck(tree, v, u));
			}
		}
		branch.push_back(-tree.label[u]);
		int &ret = tmpR[branch];
		if (ret == 0)	ret = tmpR.size();
		return ret;
	}
	int equal(Tree &other) { // normal planar representation
		if (n != other.n)	return 0;
		tmpR.clear();
		int b = dfsCheck(other, 1, -1);
		for (int i = 1; i <= n; i++) {
			int a = dfsCheck(*this, i, -1);
			if (a == b)
				return 1;
		}
		return 0;
	}
	void init(int N) { 
		for (int i = 0; i <= N; i++)
			g[i].clear();
		n = 0;
	} 
	int read(int p) {
		int x = ++n;
		char c;
		if (p >= 0)	g[x].push_back(p);
		scanf(" %c%c", &label[x], &c);
		if (c != '(') {
			ungetc(c, stdin);
			return x;
		}
		do {
			g[x].push_back(read(x));
			if (scanf("%c", &c) != 1 || c != ',')
				break;
		} while (true);
		return x;
	}
} tree1, tree2;

int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		tree1.init(256); tree2.init(256);
		tree1.read(-1); tree2.read(-1);
		int same = tree1.equal(tree2);
		puts(same ? "same" : "different");
	}
	return 0;
}
/*
2
A(B(C,D),E)
E(A,B(C,D))
A(B(C,D),E)
E(A(B(C,D)))

9999
S(Y(Y(O),U(N(S,E,R(D)))))
D(R(N(U(Y(Y(O),S)),S,E)))
*/
