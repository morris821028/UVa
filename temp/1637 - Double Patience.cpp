#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <functional>
#include <deque>
#include <assert.h>
#include <algorithm>
using namespace std;
int toIndex(char s[]) {
    int x = 0;
    switch (s[0]) {
        case '0' ... '9':
            x = s[0] - '0'; break;
        case 'T':
            x = 10; break;
        case 'J':
            x = 11; break;
        case 'Q':
            x = 12; break;
        case 'K':
            x = 13; break;
        case 'A':
            x = 1; break;
    }
    return x - 1;
}
#define MAXSTATE 1953125
// 1953125 = pow(5, 9)
int used[MAXSTATE] = {}, cases = 0;
double dp[MAXSTATE];
void decode(int u, int A[]) {
    for (int i = 0; i < 9; i++)
        A[i] = u%5, u /= 5;
}
int encode(int A[]) {
    int u = 0;
    for (int i = 8; i >= 0; i--)
        u = u * 5 + A[i];
    return u;
}
int main() {
    char s[10];
    int pile[9][4];
    while (true) {
        for (int i = 0; i < 9; i++) {
            for (int j = 3; j >= 0; j--) {
                if (scanf("%s", s) != 1)
                    return 0;
                pile[i][j] = toIndex(s);
            }
        }
        cases++;
        used[0] = cases, dp[0] = 1;
        int u, v, A[9];
        queue<int> Q;
        Q.push(0);
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            decode(u, A);
            vector<int> card[13];
            for (int i = 0; i < 9; i++) {
                if (A[i] != 4)
                    card[pile[i][A[i]]].push_back(i);
//                printf("%d ", A[i]);
            }
//            puts("");
//            printf("%lf\n", dp[u]);
//            getchar();
            int comb = 0;
            for (int i = 0; i < 13; i++) {
                comb += card[i].size() * (card[i].size() - 1) /2;
//                printf("%d\n", card[i].size());
            }
//            printf("combation %d\n", comb);
            for (int i = 0; i < 13; i++) {
                for (int p = 0; p < card[i].size(); p++) {
                    for (int q = p+1; q < card[i].size(); q++) {
                        A[card[i][p]]++, A[card[i][q]]++;
                        v = encode(A);
                        if (used[v] != cases)
                            used[v] = cases, dp[v] = 0, Q.push(v);
                        dp[v] += dp[u] / comb;
                        A[card[i][p]]--, A[card[i][q]]--;
                    }
                }
            }
        }
        if (used[MAXSTATE-1] != cases)
            used[MAXSTATE-1] = cases, dp[MAXSTATE-1] = 0;
        printf("%.6lf\n", dp[MAXSTATE - 1]);
    }
    return 0;
}
/*
 AS 9S 6C KS
 JC QH AC KH
 7S QD JD KD
 QS TS JS 9H
 6D TD AD 8S
 QC TH KC 8D
 8C 9D TC 7C
 9C 7H JH 7D
 8H 6S AH 6H
*/