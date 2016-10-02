#include <bits/stdc++.h>
using namespace std;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>
#include <assert.h>
#include <assert.h>
#pragma comment( linker, "/STACK:1024000000,1024000000")
using namespace std;

const int MAXCHAR = 26;
const int MAXNODE = 1048576;

class ACmachine {
public:
    struct Node {
        Node *next[MAXCHAR], *fail;
        Node *has;
        int cnt, id;
        void init() {
            fail = has = NULL;
            cnt = 0;
            id = -1;
            memset(next, 0, sizeof(next));
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
    	assert(c - 'a' >= 0 && c - 'a' < MAXCHAR);
        return c - 'a';
    }
    void insert(const char str[], int sid) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        p->cnt = 1, p->id = sid;
    }
    int find(const char str[]) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                return -1;
            p = p->next[idx];
        }
        return p->id;
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
                if (p == NULL || p->next[i] == NULL) {
                    u->next[i]->fail = root;
                    u->next[i]->has = root;
                } else {
                    u->next[i]->fail = p->next[i];
                    u->next[i]->has = p->next[i];
                    if (p->next[i]->id == -1)
                    	u->next[i]->has = p->next[i]->has;
                }
            }
        }
    }
    int query(const char str[], vector< vector<int> > &fpos) {
        Node *u = root, *p;
        int matched = 0;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            while (u->next[idx] == NULL && u != root)
                u = u->fail;
            u = u->next[idx];
            u = (u == NULL) ? root : u;
            p = u;
            while (p != root && p->cnt != -1) {
            	if (p->id != -1)
            		fpos[p->id].push_back(i);
            	p = p->has;
			}
        }
        return matched;
    }
    void free() {
        return ;
    }
} AC;

int countMatch(char S[], char T[]) {
	int n = strlen(S), m = strlen(T);
	if (m > n)
		return 0;
	AC.init();
	static int gap[100005], wid[100005], wlen[100005];
	int gsize = 0, cnt = 0;
	int wsize = 0, lsize = 0;
	vector< vector<int> > fpos;
	for (int i = 0; i < m; i++) {
		if (T[i] == '?') {
			cnt++;
		} else {
			gap[gsize++] = cnt;
			char *t_str = T+i;
			while (T[i] != '?' && i < m)
				i++;
			T[i] = '\0';
			int id = AC.find(t_str);
			wlen[wsize] = strlen(t_str);
			if (id != -1) {
				wid[wsize++] = id;
			} else {
				wid[wsize++] = lsize;
				fpos.push_back(vector<int>());
				AC.insert(t_str, lsize), lsize++;
			}
			cnt = 0;
			if (i != m)
				cnt = 1;
			else
				gap[gsize++] = 0;
//			printf("%s %d\n", t_str, wid[wsize-1]);
		}
	}
	if (cnt)
		gap[gsize++] = cnt;
	if (wsize == 0)
		return strlen(S) - strlen(T) + 1;
		
	AC.build();
	AC.query(S, fpos);
	
	vector<int> fidx(wsize, 0);
	int ret = 0;
	while (true) {
		int end = 0;
		for (int i = 0; i < wsize; i++) {
			int id = wid[i];
			if (fidx[i] == fpos[id].size()) {
				end = 1;
				break;
			}
		}
		if (end)
			break;
		
		int ok = 1;
		if (fpos[wid[0]][fidx[0]] - wlen[0] + 1 < gap[0])
			ok = 0;
		for (int i = 1; i < wsize && ok; i++) {
			int id = wid[i], pos, last;
			last = fpos[wid[i-1]][fidx[i-1]];
			while (fidx[i] < fpos[id].size()) {
				pos = fpos[id][fidx[i]] - wlen[i];
				if (pos - gap[i] < last) {
					fidx[i]++;
				} else if (pos - gap[i] == last) {
					break;
				} else {
					ok = 0;
					break;
				}					
			}
			if (fidx[i] == fpos[id].size())
				ok = 0;
		}
		if (ok && fpos[wid[wsize-1]][fidx[wsize-1]] + gap[gsize-1] >= n)
			ok = 0;
		ret += ok;
		fidx[0]++;
	}
	return ret;
}
int main() {
	static char S[100005], T[100005];
	while (scanf("%s", S) == 1) {
		scanf("%s", T);
		printf("%d\n", countMatch(S, T));
	}
	return 0;
}
/*
banana
?a?
bananas
?a?
abide
a??d
abide
a?d
abracadabra
a?a
acisredis
?b
acisredis
??
icpc
world?finals
*/

