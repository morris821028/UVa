#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>
#include <assert.h>
#define MAXCHAR 26
#define MAXS (1024)
#define MAXNODE 256
#pragma comment( linker, "/STACK:1024000000,1024000000")
using namespace std;
class ACmachine {
public:
    struct Node {
        Node *next[MAXCHAR], *fail;
        int cnt, val, id;
        long long dp[30][1024];
		int dpable[30][1024];
        void init() {
            fail = NULL;
            cnt = val = 0;
            id = 0;
            memset(next, 0, sizeof(next));
            memset(dp, 0, sizeof(dp));
            memset(dpable, 0, sizeof(dp));
        }
    } nodes[MAXNODE];
    Node *root;
    int size;
    Node* getNode() {
        Node *p = &nodes[size++];
        p->init();
        return p;
    }
    void init() {
        size = 0;
        root = getNode();
    }
    int toIndex(char c) {
        return c - 'a';
    }
    void dfs(Node *p, Node *q) {
        for (int i = 0; i < MAXCHAR; i++) {
            if (q->next[i]) {
                Node *u = p->next[i], *v = q->next[i];
                if (u == NULL)
                    p->next[i] = getNode(), u = p->next[i];
                u->cnt |= v->cnt;
                dfs(u, v);
            }
        }
    }
    void merge(const ACmachine &other) {
        dfs(root, other.root);
    }
    void insert(const char str[], int sid) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        p->cnt = 1;
        if (sid >= 0)	p->id |= 1<<sid;
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
    void build() { // AC automation
        queue<Node*> Q;
        Node *u, *p;
        Q.push(root), root->fail = NULL;
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            for (int i = 0; i < MAXCHAR; i++) {
                if (u->next[i] == NULL)
                    continue;
                Q.push(u->next[i]);
                p = u->fail;
                while (p != NULL && p->next[i] == NULL)
                    p = p->fail;
                if (p == NULL)
                    u->next[i]->fail = root;
                else
                    u->next[i]->fail = p->next[i];
                u->next[i]->val = u->next[i]->fail->val + u->next[i]->cnt;
                u->next[i]->id = u->next[i]->fail->id | u->next[i]->id;
            }
        }
    }
    int query(const char str[]) {
        Node *u = root, *p;
        int matched = 0;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            while (u->next[idx] == NULL && u != root)
                u = u->fail;
            u = u->next[idx];
            u = (u == NULL) ? root : u;
            p = u;
            matched += p->val;
        }
        return matched;
    }
    long long dp(int len, int N) {
    	queue<Node*> Q;
    	Node *u, *p;
    	root->dp[0][0] = 1;
    	long long ret = 0;
    	for (int k = 0; k <= len; k++) {
    		Q.push(root), ret = 0;
    		while (!Q.empty()) {
    			u = Q.front(), Q.pop();
    			ret += u->dp[len][(1<<N)-1];
    			if (u->dp[len][(1<<N)-1])
    				u->dpable[len][(1<<N)-1] = 1;
    			for (int i = 0; i < (1<<N); i++) {
    				if (i && u->dp[k][i] == 0) 
    					continue;
    				for (int j = 0; j < MAXCHAR; j++) {
    					if (u->next[j] != NULL)
    						if (i == 0)	Q.push(u->next[j]);
    					if (u->dp[k][i] == 0)
    						continue;
    					p = u;
						while (p != root && p->next[j] == NULL)
							p = p->fail;
						p = p->next[j];
						if (p == NULL)	continue;
						if (p->id)
    						p->dp[k+1][i|p->id] += u->dp[k][i];
    					else
    						p->dp[k+1][i] += u->dp[k][i];
    				}
    			}
    		} // <end queue>
    	}
    	
    	// backtrack
    	for (int k = len-1; k >= 0; k--) {
    		Q.push(root);
    		while (!Q.empty()) {
    			u = Q.front(), Q.pop();
    			for (int i = 0; i < (1<<N); i++) {
    				if (i && u->dp[k][i] == 0) 
    					continue;
    				for (int j = 0; j < MAXCHAR; j++) {
    					if (u->next[j] != NULL)
    						if (i == 0)	Q.push(u->next[j]);	
    					if (u->dp[k][i] == 0)
    						continue;
    					p = u;
						while (p != root && p->next[j] == NULL)
							p = p->fail;
						p = p->next[j];
						if (p == NULL)	continue;
						if (p->id >= 0) {
    						if (p->dpable[k+1][i|p->id])
    							u->dpable[k][i] = 1;
    					} else {
    						if (p->dpable[k+1][i])
    							u->dpable[k][i] = 1;
    					}
    				}
    			}
    		} // <end queue>
    	}
    	return ret;
    }
    void dpSearch(Node *u, int s, int len, int N, string str, vector<string> &ret) {
    	if (str.length() == len) {
    		if (s == (1<<N)-1)
    			ret.push_back(str);
    		return ;
    	}
    	if (u->dpable[str.length()][s] == 0)
    		return ;
    	Node *p; 
    	for (int i = 0; i < MAXCHAR; i++) {
			p = u;
			while (p != root && p->next[i] == NULL)
				p = p->fail;
			p = p->next[i];
			if (p == NULL)	continue;
    		int ns = s;
    		if (p->id >= 0)	
				ns = s|p->id;
    		dpSearch(p, ns, len, N, str + (char) (i + 'a'), ret);
    	}
    	
    }
    void free() {
        return ;
        // owner memory pool version
        queue<Node*> Q;
        Q.push(root);
        Node *u;
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            for (int i = 0; i < MAXCHAR; i++) {
                if (u->next[i] != NULL) {
                    Q.push(u->next[i]);
                }
            }
            delete u;
        }
    }
};
ACmachine g;
int main() {
	int M, N, cases = 0;
	char s[1024];
    while (scanf("%d %d", &M, &N) == 2 && M+N) {
       	g.init();
       	for (int i = 0; i < N; i++) {
       		scanf("%s", s);
       		g.insert(s, i);
       	}
       	
       	for (int i = 'a'; i <= 'z'; i++) {
       		s[0] = i, s[1] = '\0';
       		g.insert(s, -1);
       	}
       	g.build();
       	long long way = g.dp(M, N);
       	printf("Case %d: %lld suspects\n", ++cases, way);
       	if (way <= 42) {
       		vector<string> pwd;
       		g.dpSearch(g.root, 0, M, N, "", pwd);
       		sort(pwd.begin(), pwd.end());
       		for (int i = 0; i < pwd.size(); i++)
       			printf("%s\n", pwd[i].c_str());
       	}
        g.free();
    }
    return 0;
}
/*
10 2 
hello 
world 

10 0 

4 1 
icpc 

10 3
mo
mom
omsi

4 4
a
b
c
d

4 3
ab
bc
ca

1 2
a
a

1 0

2 2
b
ab

0 0
 */
