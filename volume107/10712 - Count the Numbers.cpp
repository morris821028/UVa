#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string.h>
using namespace std;
struct Node {
    Node *next[10], *fail, *prev;
    int eos;//prefix has a string end
    long long dp[20][2]; // [string length][upper y/n]
    int ASCII;
    Node() {
        fail = NULL, prev = NULL;
        memset(next, 0, sizeof(next));
        memset(dp, 0, sizeof(dp));
        eos = 0;
        ASCII = 0;
    }
};
void insertTrie(const char str[], Node *root, int label) {
    static Node *p;
    static int i, idx, eos;
    p = root, eos = 0;
    for(i = 0; str[i]; i++) {
        idx = str[i] - '0';
        if(p->next[idx] == NULL) {
            p->next[idx] = new Node();
            p->next[idx]->prev = p;
            p->next[idx]->ASCII = idx;
        }
        eos |= p->eos;
        p = p->next[idx];
        p->eos |= eos;
    }
    p->eos |= label;
}
void freeTrie(Node *root) {
    queue<Node*> Q;
    Node *nd;
    Q.push(root);
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 10; i++) {
            if(nd->next[i] != NULL)
                Q.push(nd->next[i]);
        }
        delete nd;
    }
}
void buildACautomation(Node *root) {
    queue<Node*> Q;
    Node *nd, *p;
    root->fail = NULL;
    Q.push(root);
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 10; i++) {
            if(nd->next[i] == NULL)
                continue;
            Q.push(nd->next[i]);
            p = nd->fail;
            while(p != NULL && p->next[i] == NULL)
                p = p->fail;
            if(p == NULL)
                nd->next[i]->fail = root;
            else {
                nd->next[i]->fail = p->next[i];
                nd->next[i]->eos |= p->next[i]->eos;//special for dp
            }
        }
    }
}

void clearDp(Node *root) {
	queue<Node*> Q;
    Node *nd;
    Q.push(root);
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        memset(nd->dp, 0, sizeof(nd->dp));
        for(int i = 0; i < 10; i++) {
            if(nd->next[i] != NULL)
                Q.push(nd->next[i]);
        }
    }
}
long long dp(Node *root, int len, char pattern[]) {
    queue<Node*> Q;
    Node *nd, *p;
    clearDp(root);
    root->dp[0][1] = 1;
    int k, i, j;
    long long ret = 0;
    for(k = 0; k < len; k++) {
        Q.push(root);
        while(!Q.empty()) {
            nd = Q.front(), Q.pop();
            for (j = 0; j < 2; j++) {
	            for (i = (k == 0); i <= (j ? pattern[k]-'0' : 9); i++) {
	                if(nd->next[i] != NULL) {
	                    if(nd->next[i]->eos) { // matching
	                    	if (j && i == pattern[k]-'0') {
	                    		long long t = 0;
	                    		for (int p = k + 1; p < len; p++)
	                    			t = t * 10 + pattern[p] - '0';
	                    		t++;
	                    		ret += nd->dp[k][j] * t;
//	                    		printf("[%d %d] (%d + %d) %lld ++ %lld\n", k, j, nd->ASCII, i, nd->dp[k][j] * t, t);
	                    	} else {
	                    		long long t = 1;
	                    		for (int p = k + 1; p < len; p++)
	                    			t *= 10;	
	                    		ret += nd->dp[k][j] * t;
//	                    		printf("[%d %d] (%d + %d) %d ++\n", k, j, nd->ASCII, i, nd->dp[k][j] * t);
	                    	}
	                    	continue;
	                    } 
						if (j == 0 || (j == 1 && i < pattern[k] - '0'))
	                    	nd->next[i]->dp[k+1][0] += nd->dp[k][j];
	                    else if(j == 1 && i == pattern[k] - '0')
	                    	nd->next[i]->dp[k+1][1] += nd->dp[k][j];
	                    if(j == 0)
	                    	Q.push(nd->next[i]);
	                } else {
	                    p = nd;
	                    while(p != root && p->next[i] == NULL)
	                        p = p->fail;
	                    p = p->next[i];
	                    if(p->eos) { // matching
                    		if (j && i == pattern[k]-'0') {
	                    		long long t = 0;
	                    		for (int p = k + 1; p < len; p++)
	                    			t = t * 10 + pattern[p] - '0';
	                    		t++;
	                    		ret += nd->dp[k][j] * t;
	                    	} else {
	                    		long long t = 1;
	                    		for (int p = k + 1; p < len; p++)
	                    			t *= 10;
	                    		ret += nd->dp[k][j] * t;
//	                    		printf("[%d %d] (%d + %d) %d ++\n", k, j, nd->ASCII, i, nd->dp[k][j] * t);
	                    	}
	                    	continue;
	                    }
						if (j == 0 || (j == 1 && i < pattern[k] - '0'))
	                    	p->dp[k+1][0] += nd->dp[k][j];
	                    else if(j == 1 && i == pattern[k] - '0')
	                    	p->dp[k+1][1] += nd->dp[k][j];
	                }
	            }
        	}
        }
    }
    return ret;
}

long long getDistinctNumberWith(int n, int m) { // #number <= n, has substring m
	if (n < 0) 
		return 0;
	char pattern[26], s[26];
	sprintf(pattern, "%d", m);
	Node *root = new Node();
    insertTrie(pattern, root, 1);
    for(int i = 0; i < 10; i++) {
    	s[0] = i + '0', s[1] = '\0';
    	insertTrie(s, root, 0);
    }
    buildACautomation(root);
    sprintf(pattern, "%d", n);
    long long ret = 0;
    int nlen = strlen(pattern);
	ret += dp(root, nlen, pattern);
	for	(int i = 1; i < nlen; i++) {
		pattern[i-1] = '9', pattern[i] = '\0';
//		printf ("%s %d %d --------\n", pattern, i, dp(root, i, pattern));
		ret += dp(root, i, pattern);
	}
    if (m == 0)	
		ret++;
    freeTrie(root);
    return ret;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
    int n, a, b;
    while(scanf("%d %d %d", &a, &b, &n) == 3 && a >= 0) {
    	long long R, L;
		R = getDistinctNumberWith(b, n);
		L = getDistinctNumberWith(a - 1, n);
        printf("%lld\n", R - L);
    }
    return 0;
}
/*
731653830 735259500 735
735259500 735259500 735
3 17 3
0 20 0
0 150 17
-1 -1 -1
*/
