#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXP = 1<<21;
const int MAXN = 4;
const int MAXL = 64;
char pwd[MAXN][MAXL];
int pwdLen[MAXN], A[MAXN], n, sumA;
char dp[MAXP];
int arg_dp[MAXP][2];
void dfs(int dep, int idx[], int v) {
	if (dep == n) {
		int same = 1;
		for (int i = 1; i < n; i++)
			same &= pwd[i][idx[i]] == pwd[0][idx[0]];
		if (same) {
			int s = 0;
			arg_dp[v][0] = -1, arg_dp[v][1] = pwd[0][idx[0]];
			for (int i = 0; i < n; i++) {
				if (idx[i] == 0) {
					dp[v] = 1;
					return ;
				}
				s = s + (idx[i]-1) * A[i];
			}
			dp[v] = dp[s] + 1, arg_dp[v][0] = s;
		} else {
			arg_dp[v][0] = -2;
			for (int i = 0; i < n; i++) {
				if (idx[i] == 0)
					continue;
				if (dp[v - A[i]] > dp[v])
					dp[v] = dp[v - A[i]];
			}
		}
		return ;
	}
	for (int i = 0; i < pwdLen[dep]; i++) {
		idx[dep] = i;
		dfs(dep+1, idx, v + A[dep] * i);
	}
}

// 
#define MAXCHAR (52 + 10)
#define MAXNODE (131072)
class Trie {
public:
    struct Node {
        Node *next[MAXCHAR];
        int cnt;
        set<int> S;
        void init() {
            cnt = 0, S.clear();
            memset(next, 0, sizeof(next));
        }
    } nodes[MAXNODE];
    Node *root;
    int size, cases;
    Node* getNode() {
    	assert(size < MAXNODE);
        Node *p = &nodes[size++];
        p->init();
        return p;
    }
    void init() {
        size = cases = 0;
        root = getNode();
    }
    inline int toIndex(char c) {
    	if (c <= '9')	return c - '0';
    	if (c <= 'Z')	return 10 + c - 'A';
    	if (c <= 'z')	return 36 + c - 'a';
        assert(false);
    }
    inline int toChar(int i) {
    	if (i < 10)		return i + '0';
    	if (i < 36)		return i - 10 + 'A';
    	if (i < 62)		return i - 36 + 'a';
    	assert(false);
    }
    // basis operation
    void insert(const char str[], int w) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        p->cnt += w;
    }
    int find(const char str[]) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        return p->cnt;
    }
        
    void free() {
        return ;
    }
} tool;
char s[MAXL];
void dfsLCS(int idx[], int v, Trie::Node *u) {
	if (v < 0)
		return ;
	
	if (arg_dp[v][0] >= -1) {
		int vidx = tool.toIndex(arg_dp[v][1]);
		if (u->next[vidx] == NULL)	
			u->next[vidx] = tool.getNode();
		u = u->next[vidx];
		if (u->S.count(v))
			return;
		u->S.insert(v);
		if (dp[v] == 1)
			return ;
		if (arg_dp[v][0] != -1) {
			for (int i = 0; i < n; i++)
				idx[i]--;
			dfsLCS(idx, arg_dp[v][0], u);
			for (int i = 0; i < n; i++)
				idx[i]++;
		}
	} else {
		if (u->S.count(v))
			return;
		u->S.insert(v);
		for (int i = 0; i < n; i++) {
			if (idx[i] == 0)
				continue;
			if (dp[v - A[i]] == dp[v]) {
				idx[i]--;
				dfsLCS(idx, v - A[i], u);
				idx[i]++;
			}
		}
	}
}

void printLCS(int dep, Trie::Node *u, char *s, vector<string> &ret) {
	if (u == NULL)	return;
	if (dep == -1) {
		ret.push_back(s+1);
		return;
	}
	for (int i = 0; i < MAXCHAR; i++) {
		*s = tool.toChar(i);
		printLCS(dep-1, u->next[i], s-1, ret);
	}
}
int countLCS(int dep, Trie::Node *u, char *s) {
	if (u == NULL)	return 0;
	if (dep == -1)
		return 1;
	int ret = 0;
	for (int i = 0; i < MAXCHAR; i++) {
		*s = tool.toChar(i);
		ret += countLCS(dep-1, u->next[i], s-1);
	}
	return ret;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", pwd[i]);
			pwdLen[i] = strlen(pwd[i]);
		}
		A[0] = 1;
		for (int i = 1; i < n; i++)
			A[i] = A[i-1] * pwdLen[i-1];
		
		memset(dp, 0, sizeof(char) * A[n-1] * pwdLen[n-1]);
		
		int idx[MAXN], f = A[n-1] * pwdLen[n-1] - 1;
		dfs(0, idx, 0);
		
//		printf("%d\n", (int) dp[f]);
		
		tool.init();
		memset(s, 0, sizeof(s));
		for (int i = 0; i < n; i++)
			idx[i] = pwdLen[i]-1;
		dfsLCS(idx, f, tool.root);
		printf("%d\n", countLCS(dp[f]-1, tool.root, s + dp[f]-1));
		vector<string> ret;
		printLCS(dp[f]-1, tool.root, s + dp[f]-1, ret);
		sort(ret.begin(), ret.end());
		for (int i = 0; i < ret.size(); i++)
			printf("%s\n", ret[i].c_str());
	}
	return 0;
}
/*
999
2
abcdabcdabcdabcdefghefghefghefgh
dcbadcbadcbadcbahgfehgfehgfehgfe
2
abcdabcdabcdabcd
dcbadcbadcbadcba

999

2
abcabcaa
acbacba
2
abcdfgh
abccfdsg
3
3124158592654359
3173415926581359
763141578926536359 
*/
