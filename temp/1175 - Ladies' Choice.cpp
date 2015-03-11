// Gale-Shapley algorithm, stable marriage problem
#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAXN = 1024;
class GaleShapley { // produce the best possible choice for the mans
public:
    int mOrder[MAXN][MAXN], fOrder[MAXN][MAXN];
    int fPref[MAXN][MAXN];
    int man[MAXN], woman[MAXN];
    int N;
    void init(int n) {
        N = n;
    }
    void stable() {
        int mIdx[MAXN];
        for (int i = 0; i < N; i++)
            man[i] = woman[i] = -1, mIdx[i] = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                fPref[i][fOrder[i][j]] = j;
        }
        for (int i = 0; i < N; i++) {
            int m = i, w;
            while (m >= 0) {
                w = mOrder[m][mIdx[m]++];
                while (m >= 0 && (woman[w] == -1 || fPref[w][woman[w]] > fPref[w][m])) {
                    man[m] = w;
                    swap(m, woman[w]);
                }
            }
        }
    }
} g;
int main() {
    int testcase, N, x;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        g.init(N);
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &x), x--;
                g.mOrder[i][j] = x;
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &x), x--;
                g.fOrder[i][j] = x;
            }
        }
        
        g.stable();
        
        for (int i = 0; i < N; i++)
            printf("%d\n", g.man[i] + 1);
        if (testcase)   puts("");
    }
    return 0;
}
/*
 1
 
 5
 1 2 3 5 4
 5 2 4 3 1
 3 5 1 2 4
 3 4 2 1 5
 4 5 1 2 3
 
 2 5 4 1 3
 3 2 4 1 5
 1 2 4 3 5
 4 1 2 5 3
 5 3 2 4 1
 */
