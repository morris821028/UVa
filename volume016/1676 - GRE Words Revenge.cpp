#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#define MAXCHAR 2
#define MAXS (5000005)
#define MAXNODE 526288
#pragma comment( linker, "/STACK:1024000000,1024000000")
using namespace std;
class ACmachine {
public:
    struct Node {
        Node *next[MAXCHAR], *fail;
        int cnt, val;
        void init() {
            fail = NULL;
            cnt = val = 0;
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
        return c - '0';
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
    void insert(const char str[]) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        p->cnt = 1;
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
char s[MAXS];
void decodeString(char s[], int L) {
    static char buf[MAXS];
    int n = (int) strlen(s);
    L %= n;
    for (int i = L, j = 0; i < n; i++, j++)
        buf[j] = s[i];
    for (int i = 0, j = n - L; i < L; i++, j++)
        buf[j] = s[i];
    for (int i = 0; i < n; i++)
        s[i] = buf[i];
}
ACmachine cache, disk;
int main() {
    int testcase, cases = 0;
    int N;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        printf("Case #%d:\n", ++cases);
        int L = 0; // encrypted key
        int cFlag = 0, dFlag = 0;
        cache.init(), disk.init();
        for (int i = 0; i < N; i++) {
            scanf("%s", s);
            decodeString(s+1, L);
            //            printf("%s\n", s);
#define THRESHOLD 4096
            if (s[0] == '+') {
                if (disk.find(s+1) || cache.find(s+1))
                    continue;
                cache.insert(s+1), cFlag = 0;
                if (cache.size > THRESHOLD) {
                    disk.merge(cache), dFlag = 0;
                    cache.free();
                    cache.init(), cFlag = 0;
                }
            } else {
                if (!cFlag) cache.build();
                if (!dFlag) disk.build();
                int ret = disk.query(s+1) + cache.query(s+1);
                printf("%d\n", ret);
                L = ret;
            }
        }
        disk.free(), cache.free();
    }
    return 0;
}
/*
 99999
 10
 +01
 +110
 ?010
 +110
 +00
 +0
 ?001001
 ?001001
 +110110
 ?1101001101
 
 6
 +01
 +110
 +110
 +00
 +0
 ?001001
 
 20
 +101001011
 ?110100
 +11010100
 ?0011001101
 +111011
 ?00010011
 +0111010110
 +0000101
 +0
 +11000
 ?1
 +1010101
 +0001
 +0110
 +0111101111
 ?1100
 +0111
 +1001
 ?0110111011
 ?1010010100
 
 10
 +00
 ?010110100
 +0100000100
 +111
 +000000
 ?0000110
 +110
 +00
 +0011
 ?101001
 
 5
 +0
 +1000100
 +01
 +0
 ?1110010011
 
 2
 3
 +01
 +01
 ?01001
 3
 +01
 ?010
 ?011
 */