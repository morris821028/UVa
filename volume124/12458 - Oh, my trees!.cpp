#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;

struct Node {
    Node *r, *l;
    int v, left, right;
    Node() {
        r = l = NULL;
        v = 0;
    }
};
char str[100000];
int num[100000], hnum[100000];
Node *h[100000];
int main() {
    int t, n;
    stringstream sin;
    string line;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        getchar();
        int i, j, idx, x;
        for(i = 0; i < n; i++) {
            getline(cin, line);
            sin.clear();
            sin << line;
            idx = 0;
            while(sin >> x) {
                num[idx++] = x;
            }
            h[i] = new Node[idx];
            for(j = 0; j < idx; j++) {
                h[i][j].v = num[j];
            }
            hnum[i] = idx;
        }
        h[0][0].left = -2147483647;
        h[0][0].right = 2147483647;
        for(i = 1; i < n; i++) {
            idx = 0;
            for(j = 0; j < hnum[i]; j++) {
                int v = h[i][j].v;
                while(true) {
                    if(h[i-1][idx].v > v) {
                        if(h[i-1][idx].left < v && h[i-1][idx].right > v) {
                            h[i-1][idx].l = &h[i][j];
                            h[i][j].left = h[i-1][idx].left;
                            h[i][j].right = h[i-1][idx].v;
                            break;
                        }
                    }
                    if(h[i-1][idx].v < v) {
                        if(h[i-1][idx].left < v && h[i-1][idx].right > v) {
                            h[i-1][idx].r = &h[i][j];
                            h[i][j].left = h[i-1][idx].v;
                            h[i][j].right = h[i-1][idx].right;
                            break;
                        }
                    }
                    idx++;
                }
            }
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < hnum[i]; j++) {
                printf("%d:", h[i][j].v);
                if(h[i][j].l != NULL) {
                    printf("%d", h[i][j].l->v);
                }
                putchar('-');
                if(h[i][j].r != NULL) {
                    printf("%d", h[i][j].r->v);
                }
                puts("");
            }
            delete[] h[i];
        }
    }
    return 0;
}
