#include <stdio.h>
#include <map>
#include <queue>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 1024
#define MAXM 1024
int N, P[MAXN], M, K;
vector<int> INPUT[MAXM], OUTPUT[MAXM];
void remove(int tid) {
    for (int i = 0; i < INPUT[tid].size(); i++) {
        P[INPUT[tid][i]]--;
    }
}
void resume(int tid) {
    for (int i = 0; i < INPUT[tid].size(); i++) {
        P[INPUT[tid][i]]++;
    }
}
int trigger(int tid) {
    int ok = 1;
    remove(tid);
    for (int i = 0; i < INPUT[tid].size(); i++)
        ok &= P[INPUT[tid][i]] >= 0;
    resume(tid);
    return ok;
}
void action(int tid) {
    remove(tid);
    for (int i = 0; i < OUTPUT[tid].size(); i++)
        P[OUTPUT[tid][i]]++;
}
void simulate() {
    for (int i = 0; i < K; i++) {
        int update = 0;
        for (int j = 0; j < M; j++) {
            if (trigger(j)) {
                update = 1;
                action(j);
                break;
            }
        }
        if (!update) {
            printf("dead after %d transitions\n", i);
            return;
        }
    }
    printf("still live after %d transitions\n", K);
}
int main() {
    int cases = 0;
    while (scanf("%d", &N) == 1 && N) {
        for (int i = 1; i <= N; i++)
            scanf("%d", &P[i]);
        scanf("%d", &M);
        for (int i = 0; i < M; i++) {
            int x;
            INPUT[i].clear(), OUTPUT[i].clear();
            while (scanf("%d", &x) == 1 && x) {
                if (x < 0)
                    INPUT[i].push_back(-x);
                if (x > 0)
                    OUTPUT[i].push_back(x);
            }
        }
        scanf("%d", &K);
        printf("Case %d: ", ++cases);
        simulate();
        printf("Places with tokens:");
        for (int i = 1; i <= N; i++) {
            if (P[i])
                printf(" %d (%d)", i, P[i]);
        }
        puts("\n");
    }
    return 0;
}
/*
 2
 1 0
 2
 -1 2 0
 -2 1 0
 100
 3
 3 0 0
 3
 -1 2 0
 -2 -2 3 0
 -3 1 0
 100
 3
 1 0 0
 3
 -1 2 3 0
 -2 1 0
 -3 1 0
 1
 0
 */