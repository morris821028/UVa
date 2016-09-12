#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	void bfs(int st, int ed, vector<vector<int>> &g, vector<int> &dist) {
		queue<int> Q;
        Q.push(st), dist[st] = 1;
        while (!Q.empty()) {
        	int u, d;
        	u = Q.front();
        	d = dist[u];
        	Q.pop();
        	if (u == ed)
        		return ;
        	for (auto v : g[u]) {
        		if (dist[v] == 0) {
        			dist[v] = d+1;
        			Q.push(v);
        		}
			}
		}
	}
	void dfs(int st, int ed, int d, vector<vector<int>> &g, 
			vector<int> &dist1, vector<int> &dist2, vector<string> &dict, 
			vector<string> &path, vector<vector<string>> &ret) {
		path[dist1[st]-1] = dict[st];
		if (st == ed) {
			ret.push_back(path);
			return ;
		}
		for (auto v : g[st]) {
			if (dist1[v] + dist2[v] == d+1 && dist1[v] == dist1[st]+1 && dist1[v] && dist2[v]) {
				dfs(v, ed, d, g, dist1, dist2, dict, path, ret);
			}
		}
	}
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        wordList.insert(beginWord);
        wordList.insert(endWord);
        
        unordered_map<string, int> R;
        int n = wordList.size(), size = 0;
        vector<string> dict(n);
        
        for (auto e: wordList) {
        	R[e] = size;
        	dict[size] = e;
        	size++;
		}
		
		vector<vector<int>> g(n, vector<int>());
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				if (dict[i].length() != dict[j].length())
					continue;
				int diff = 0;
				for (int k = dict[i].length()-1; k >= 0 && diff < 2; k--)
					diff += dict[i][k] != dict[j][k];
				if (diff == 1)
					g[i].push_back(j), g[j].push_back(i);
			}
		}
		
		vector<vector<string>> ret;
		vector<int> dist1(n, 0), dist2(n, 0);
		int st = R[beginWord];
        int ed = R[endWord];
		bfs(st, ed, g, dist1);
		bfs(ed, st, g, dist2);
		if (dist1[ed] == 0)
			return ret;		
		vector<string> path(dist1[ed], "");
		dfs(st, ed, dist1[ed], g, dist1, dist2, dict, path, ret);
		return ret;
    }
};

int main() {
	string w[] = {"hot","dot","dog","lot","log"};
	unordered_set<string> wordList;
	for (int i = 0; i < 5; i++)
		wordList.insert(w[i]);
	Solution t;
	vector<vector<string>> ret = t.findLadders("hit", "cog", wordList);
	for (auto e1 : ret) {
		for (auto e2 : e1)
			printf("%s ", e2.c_str());
		puts("");
	}
	return 0;
}
/*
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
*/


