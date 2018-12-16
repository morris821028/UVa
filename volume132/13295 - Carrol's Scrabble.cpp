#include <bits/stdc++.h>
using namespace std;

const int pt[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
unordered_map<string, int> W;
unordered_map<string, vector<string>> SW;

void solve(string st, string ed) {
	if (st.length() != ed.length()) {
		printf("%s TO %s IMPOSSIBLE\n", st.c_str(), ed.c_str());
		return;
	}
	if (st == ed) {
		printf("%s TO %s 0 0\n", st.c_str(), ed.c_str());
		return;
	}
	queue<string> Q;
	unordered_map<string, pair<int, int>> dist;
	Q.push(st), dist[st] = {0, 0};
	while (!Q.empty()) {
		string u = Q.front(); Q.pop();
		pair<int, int> d = dist[u];
		if (u == ed) {
			printf("%s TO %s %d %d\n", st.c_str(), ed.c_str(), d.first, d.second-W[ed]);
			return;
		}
		for (int i = 0; i < u.length(); i++) {
			char c = u[i];
			for (int j = 'a'; j <= 'z'; j++) {
				if (j == c)
					continue;
				u[i] = j;
				auto it = W.find(u);
				if (it == W.end())
					continue;
				auto dt = dist.find(u);
				if (dt == dist.end()) {
					Q.push(u);
					dist[u] = {d.first+1, d.second + it->second};
				} else if (dt->second.first == d.first+1) {
					dt->second = {d.first+1, max(dt->second.second, d.second + it->second)};
				}
			}
			u[i] = c;
		}
		sort(u.begin(), u.end());
		for (auto v : SW[u]) {
			auto it = W.find(v);
			auto dt = dist.find(v);
			if (dt == dist.end()) {
				Q.push(v);
				dist[v] = {d.first+1, d.second + it->second};
			} else if (dt->second.first == d.first+1) {
				dt->second = {d.first+1, max(dt->second.second, d.second + it->second)};
			}
		}
	}
	printf("%s TO %s IMPOSSIBLE\n", st.c_str(), ed.c_str());
}
int main() {
	int n, m;
	char word[32], st[32], ed[32];
	while (scanf("%d", &n) == 1) {
		W.clear(), SW.clear();
		for (int i = 0; i < n; i++) {
			scanf("%s", &word);
			int s = 0;
			for (int j = 0; word[j]; j++)
				s += pt[word[j]-'a'];
			W[word] = s;
			string sw = word;
			sort(sw.begin(), sw.end());
			SW[sw].push_back(word);
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s %*s %s", st, ed);
			solve(st, ed);
		}
	}
	return 0;
}
/*
14
hot
iron
icon
coin
corn
cord
lord
load
lead
lion
cold
gold
worm
warm
5
iron TO lead
lead TO gold
iron TO icon
warm TO hot
warm TO cold
*/
