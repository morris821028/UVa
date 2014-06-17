#include <stdio.h>
#include <string.h>
#include <queue>
#include <map>
#include <iostream>
#include <algorithm>
#define rename(c) (c-'a')
using namespace std;
struct Node {
    Node *next[26], *fail;
    int label; // which word end.
    /*Node() {
        label = -1;
        memset(next, 0, sizeof(next));
    }*/
    void init() {
        label = -1;
        fail = NULL;
        memset(next, 0, sizeof(next));
    }
};
Node BUF[625000];
int BUFsize;
void insert_Trie(char str[], Node *root, int label) {
    static Node *p;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = rename(str[i]);
        if(p->next[idx] == NULL) {
            //p->next[idx] = new Node();
            BUFsize++;
            BUF[BUFsize].init();
            p->next[idx] = &BUF[BUFsize];
        }
        p = p->next[idx];
    }
    p->label = label;
}
void build_ACautomation(Node *root) {
    queue<Node*> Q;
    Node *nd, *p;
    root->fail = NULL;
    Q.push(root);
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 26; i++) {
            if(nd->next[i] == NULL)
                continue;
            Q.push(nd->next[i]);
            p = nd->fail;
            while(p != NULL && p->next[i] == NULL)
                p = p->fail;
            if(p == NULL)
                nd->next[i]->fail = root;
            else
                nd->next[i]->fail = p->next[i];
        }
    }
}
void query_ACautonmation(char *str, Node *root, int *exist_mark) {
    static Node *p, *q;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = rename(str[i]);
        while(p != root && p->next[idx] == NULL)
            p = p->fail;
        p = p->next[idx];
        p = (p == NULL) ? root : p;
        q = p;
        while(q != root) {
            exist_mark[q->label]++;
            q = q->fail;
        }
    }
}
void free_Trie(Node *root) {
    queue<Node*> Q;
    Node *nd;
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 26; i++) {
            if(nd->next[i] != NULL)
                Q.push(nd->next[i]);
        }
        delete nd;
    }
}
char T[15000][1005], g[105][105], S[1024];
int main() {
    int t, cases = 0;
    scanf("%d", &t);
    getchar();
    int n, q, i, j, k;
    while(t--) {
        scanf("%d", &n);
        BUFsize = 0;
        BUF[BUFsize].init();
        //Node *root = new Node();
        Node *root = &BUF[BUFsize];
        Node *p;
        while(getchar() != '\n');
        for(i = 0; i < n; i++) { // offline process
            gets(T[i]);
            insert_Trie(T[i], root, i);
        }
        scanf("%d", &q);
        printf("Test Case #%d\n", ++cases);
        int a, b, x, y, dir, idx, qcases = 0;
        while(q--) {
            printf("Query #%d\n", ++qcases);
            scanf("%d %d", &a, &b);
            while(getchar() != '\n');
            for(i = 0; i < a; i++)
                gets(g[i]);
            build_ACautomation(root);
            int cnt_mark[15000] = {};
            map<string, int> output;
            int idx;
            for(i = 0; i < a; i++) { // row left-right
                p = root;
                x = i, y = 0, idx = 0;
                while(x < a && x >= 0 && y < b && y >= 0) {
                    S[idx++] = g[x][y];
                    y++;
                }
                S[idx] = '\0';
                query_ACautonmation(S, root, cnt_mark);
            }
            for(i = 0; i < a; i++) { // row right-left
                p = root;
                x = i, y = b-1, idx = 0;
                while(x < a && x >= 0 && y < b && y >= 0) {
                    S[idx++] = g[x][y];
                    y--;
                }
                S[idx] = '\0';
                query_ACautonmation(S, root, cnt_mark);
            }
            for(i = 0; i < b; i++) { // column left-right
                p = root;
                x = 0, y = i, idx = 0;
                while(x < a && x >= 0 && y < b && y >= 0) {
                    S[idx++] = g[x][y];
                    x++;
                }
                S[idx] = '\0';
                query_ACautonmation(S, root, cnt_mark);
            }
            for(i = 0; i < b; i++) { // column right-left
                p = root;
                x = a-1, y = i, idx = 0;
                while(x < a && x >= 0 && y < b && y >= 0) {
                    S[idx++] = g[x][y];
                    x--;
                }
                S[idx] = '\0';
                query_ACautonmation(S, root, cnt_mark);
            }
            for(i = 0; i < a; i++) { // slide down
                p = root;
                x = i, y = 0, idx = 0;
                while(x < a && x >= 0 && y < b && y >= 0) {
                    S[idx++] = g[x][y];
                    x++, y++;
                }
                S[idx] = '\0';
                query_ACautonmation(S, root, cnt_mark);
                for(j = 0, k = idx-1; j < k; j++, k--)
                    swap(S[j], S[k]);
                query_ACautonmation(S, root, cnt_mark);
            }
            for(i = 1; i < b; i++) { // slide down
                p = root;
                x = 0, y = i, idx = 0;
                while(x < a && x >= 0 && y < b && y >= 0) {
                    S[idx++] = g[x][y];
                    x++, y++;
                }
                S[idx] = '\0';
                query_ACautonmation(S, root, cnt_mark);
                for(j = 0, k = idx-1; j < k; j++, k--)
                    swap(S[j], S[k]);
                query_ACautonmation(S, root, cnt_mark);
            }
            for(i = 0; i < a; i++) { // slide up
                p = root;
                x = i, y = 0, idx = 0;
                while(x < a && x >= 0 && y < b && y >= 0) {
                    S[idx++] = g[x][y];
                    x--, y++;
                }
                S[idx] = '\0';
                query_ACautonmation(S, root, cnt_mark);
                for(j = 0, k = idx-1; j < k; j++, k--)
                    swap(S[j], S[k]);
                query_ACautonmation(S, root, cnt_mark);
            }
            for(i = 1; i < b; i++) { // slide up
                p = root;
                x = a-1, y = i, idx = 0;
                while(x < a && x >= 0 && y < b && y >= 0) {
                    S[idx++] = g[x][y];
                    x--, y++;
                }
                S[idx] = '\0';
                query_ACautonmation(S, root, cnt_mark);
                for(j = 0, k = idx-1; j < k; j++, k--)
                    swap(S[j], S[k]);
                query_ACautonmation(S, root, cnt_mark);
            }
            for(i = 0; i < n; i++)
                if(cnt_mark[i])
                    output[T[i]] = cnt_mark[i];
            for(map<string, int>::iterator it = output.begin();
                it != output.end(); it++)
                printf("%s %d\n", (it->first).c_str(), it->second);
        }
        puts("");
        //free_Trie(root);
    }
    return 0;
}
/*
1
1
a
1
1 1
a
*/
