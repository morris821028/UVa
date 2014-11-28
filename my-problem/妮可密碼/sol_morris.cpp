#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

#define MAX_LEN 100+1
#define BASE 26
#define MAX_TOKEN 20
struct Node {
    Node *next[BASE], *fail, *prev;
    int eos;//prefix has a string end
    long long dp[MAX_LEN]; // [string length]
    int ASCII;
    Node() {
        fail = NULL, prev = NULL;
        memset(next, 0, sizeof(next));
        memset(dp, 0, sizeof(dp));
        eos = ASCII = 0;
    }
};
const long long mod = 1000000007LL;

void insertTrie(const char *str, Node *root, int label) {
    static Node *p;
    static int i, idx, eos;
    p = root, eos = 0;
    for(i = 0; str[i]; i++) {
        idx = str[i] - 'a';
        assert(idx >= 0 && idx < BASE);
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
        for(int i = 0; i < BASE; i++) {
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
        for(int i = 0; i < BASE; i++) {
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
        for(int i = 0; i < BASE; i++) {
            if(nd->next[i] != NULL)
                Q.push(nd->next[i]);
        }
    }
}
long long dp(Node *root, const char *pwd) {
	int len = (int) strlen(pwd);
    queue<Node*> Q;
    Node *nd, *p;
    clearDp(root);
    root->dp[0] = 1;
    long long ret = 0;
    for(int k = 0; k < len; k++) {
        Q.push(root);          	
		int L, R;
    	if (pwd[k] != '*')
    		L = R = pwd[k] - 'a';
    	else
    		L = 0, R = BASE - 1;
        while(!Q.empty()) {
            nd = Q.front(), Q.pop();
            for (int i = 0; i < BASE; i++)
            	if (nd->next[i] != NULL)
            		Q.push(nd->next[i]);
            if (nd->dp[k] == 0)
            	continue;
            for (int i = L; i <= R; i++) {
                if (nd->next[i] != NULL) {
                    if (nd->next[i]->eos) {
                		long long t = 1;
                		for (int p = k + 1; p < len; p++) {
                			if(pwd[p] != '*')	continue;
                			t = (t * BASE) %mod;
                		}
                		ret = (ret + (nd->dp[k] * t) %mod) %mod;
                    	continue;
                    } 
                    nd->next[i]->dp[k+1] += nd->dp[k];
                    nd->next[i]->dp[k+1] %= mod;
                } else {
                    p = nd;
                    while(p != root && p->next[i] == NULL)
                        p = p->fail;
                    p = p->next[i];
                    if (p->eos) { // matching
               			long long t = 1;
                		for (int p = k + 1; p < len; p++) {
                			if(pwd[p] != '*')	continue;
                			t = (t * BASE) %mod;
                		}
                		ret = (ret + (nd->dp[k] * t) %mod) %mod;
                    	continue;
                    }
                    p->dp[k+1] += nd->dp[k];
                    p->dp[k+1] %= mod;
                }
            }
        }
    }
    return ret;
}
int main() {

    int n;
    char pattern[MAX_LEN], token[MAX_TOKEN][MAX_LEN], foo[MAX_LEN];
    while(scanf("%d %s", &n, &pattern) == 2) {
    	for (int i = 0; i < n; i++)
    		scanf("%s", token[i]);
    		
    	Node *root = new Node();
    	for (int i = 0; i < n; i++)
    		insertTrie(token[i], root, 1);
    	for(int i = 0; i < BASE; i++) { // insert for easy dp without fail pointer
    		foo[0] = i + 'a', foo[1] = '\0';
    		insertTrie(foo, root, 0);
    	}
    	buildACautomation(root);
    	
    	long long ret = dp(root, pattern); 
    	printf("%lld\n", ret);
    	
    	freeTrie(root);
    }
    return 0;
}
/*
1 m
m
1 moe**
moe
2 ***
moe ta
5 ***e*
fme tge pue bse loew
2 **x**
qy vxeh
2 *****
abca bc
*/
