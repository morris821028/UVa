#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
#include <algorithm>
#define rename(c) (c-'a')
using namespace std;
struct Node {
    Node *next[26];
    int label; // which word end.
    void init() {
        label = -1;
        memset(next, 0, sizeof(next));
    }
};
Node BUF[650000];
int BUFsize;
int insert_Trie(char str[], Node *root, int label) {
    static Node *p;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = rename(str[i]);
        if(p->next[idx] == NULL) {
            BUFsize++;
            BUF[BUFsize].init();
            p->next[idx] = &BUF[BUFsize];
        }
        p = p->next[idx];
    }
    if(p->label < 0) {
        p->label = label;
        return 1;
    }
    return 0;
}
char T[15000][1005], g[105][105];
int D[][2] = {{0,1},{1,0},{-1,0},{0,-1},
                {1,1},{1,-1},{-1,1},{-1,-1}};
int main() {
    int t, cases = 0;
    scanf("%d", &t);
    getchar();
    int n, q, i, j, k;
    while(t--) {
        scanf("%d", &n);
        BUFsize = 0;
        BUF[BUFsize].init();
        Node *root = &BUF[BUFsize];
        Node *p;
        while(getchar() != '\n');
        for(i = 0, j = 0; i < n; i++) { // offline process
            gets(T[j]);
            j += insert_Trie(T[j], root, j);
        }
        n = j;
        scanf("%d", &q);
        printf("Test Case #%d\n", ++cases);
        int a, b, x, y, dir, idx, qcases = 0;
        while(q--) {
            printf("Query #%d\n", ++qcases);
            scanf("%d %d", &a, &b);
            while(getchar() != '\n');
            for(i = 0; i < a; i++)
                gets(g[i]);
            int cnt_mark[15000] = {};
            map<string, int> output;
            for(i = 0; i < a; i++) {
                for(j = 0; j < b; j++) {
                    for(dir = 0; dir < 8; dir++) {
                        p = root;
                        x = i, y = j;
                        while(p != NULL && x < a && x >= 0 && y < b && y >= 0) {
                            idx = rename(g[x][y]);
                            if(p->next[idx] == NULL)
                                break;
                            p = p->next[idx];
                            if(p->label >= 0)
                                cnt_mark[p->label]++;
                            x += D[dir][0], y += D[dir][1];
                        }
                    }
                }
            }
            for(i = 0; i < n; i++)
                if(cnt_mark[i])
                    output[T[i]] = cnt_mark[i];
            for(map<string, int>::iterator it = output.begin();
                it != output.end(); it++)
                printf("%s %d\n", (it->first).c_str(), it->second);
        }
        puts("");
    }
    return 0;
}
