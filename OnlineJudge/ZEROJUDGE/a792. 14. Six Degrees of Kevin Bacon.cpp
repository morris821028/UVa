#include <bits/stdc++.h>
using namespace std;
map<string, int> R;
vector<int> g[100005];
int main() {
	int size = 0;
	string line;
	getline(cin, line);
	while (getline(cin, line)) {
		if (line == "[ACTORS]")
			break;
		stringstream sin(line);
		string x;
		vector<int> A;
		while (sin >> x) {
			if (R.count(x))
				A.push_back(R[x]);
			else
				R[x] = size++, A.push_back(R[x]);
		}
		for (int i = 1; i < A.size(); i++) {
			g[A[i]].push_back(A[0]);
			g[A[0]].push_back(A[i]);
		}
	}
	
	if (!R.count("KevinBacon"))
		R["KevinBacon"] = size++;
	while (getline(cin, line)) {
		if (line == "[END]")
			break;
		int st = R[line], ed = R["KevinBacon"];
		int used[100005] = {};
		queue<int> Q;
		used[st] = 1, Q.push(st);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			for (auto &x : g[u]) {
				if (used[x] == 0)
					used[x] = used[u]+1, Q.push(x);
			}
			if (used[ed])
				break;
		} 
		printf("%s has a Bacon number of %d\n", line.c_str(), used[ed]/2);
	}
	return 0;
}
