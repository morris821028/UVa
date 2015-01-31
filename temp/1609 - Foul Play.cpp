#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
using namespace std;

#define MAXN (1024+5)
char sg[MAXN][MAXN];
vector<int> g[MAXN];
int N;
void adHoc() {
    for (int i = 0; i < N; i++)
        g[i].clear();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (sg[i][j] == '1') {
                g[i].push_back(j);
            }
        }
    }
    set<int> A, B;
    for (int i = 1; i < N; i++) {
        if (sg[0][i] == '1')
            A.insert(i);
        else
            B.insert(i);
    }
    for (int i = 1, M = N; i < N; i *= 2, M /= 2) {
//        assert(A.size() + B.size() + 1 == M);
//        printf("%d\n", (int)(A.size() + B.size() + 1));
        set<int> nA, nB;
        vector<int> lA, lB;
        for (set<int>::iterator it = A.begin(); it != A.end(); ) {
            if (A.size() == 1)
                break;
            int x = *it, match = 0;
            for (int j = 0; j < g[x].size(); j++) {
                if (B.count(g[x][j])) {
                    printf("%d %d\n", x+1, g[x][j]+1);
                    B.erase(g[x][j]), nA.insert(x);
                    match = 1;
                    break;
                }
            }
            if (match)
                A.erase(it++);
            else
                it++;
        }
        for (int j = 0; j < g[0].size(); j++) {
            if (A.count(g[0][j])) {
                printf("%d %d\n", 0+1, g[0][j]+1);
                A.erase(g[0][j]);
                break;
            }
        }
        for (set<int>::iterator it = A.begin(); it != A.end(); it++) {
            lA.push_back(*it);
        }
        for (set<int>::iterator it = B.begin(); it != B.end(); it++) {
            lB.push_back(*it);
        }
        for (int i = 0; i+1 < lB.size(); i+=2) {
            int x = lB[i], y = lB[i+1];
            if (sg[x][y] == '1')
                nB.insert(x), printf("%d %d\n", x+1, y+1);
            else
                nB.insert(y), printf("%d %d\n", y+1, x+1);
        }
        for (int i = 0; i+1 < lA.size(); i+=2) {
            int x = lA[i], y = lA[i+1];
            if (sg[x][y] == '1')
                nA.insert(x), printf("%d %d\n", x+1, y+1);
            else
                nA.insert(y), printf("%d %d\n", y+1, x+1);
        }
        if (lB.size()%2) {
            assert(lB.size()%2 && lA.size()%2);
            int x = lA[lA.size()-1], y = lB[lB.size()-1];
            if (sg[x][y] == '1')
                nA.insert(x), printf("%d %d\n", x+1, y+1);
            else
                nB.insert(y), printf("%d %d\n", y+1, x+1);
        }
        A = nA, B = nB;
    }
}
int main() {
    while (scanf("%d", &N) == 1) {
        for (int i = 0; i < N; i++)
            scanf("%s", sg[i]);
        adHoc();
    }
    return 0;
}
/*
 4
 0110
 0011
 0000
 1010
 8
 00111010
 10101111
 00010010
 01000101
 00110010
 10101011
 00010000
 10101010
 4
 0110
 0011
 0000
 1010
