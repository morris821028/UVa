#include <stdio.h>
#include <string.h>
#include <map>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <assert.h>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 32
int n, hour;
int f[MAXN], d[MAXN], t[MAXN];
struct cmp {
    bool operator() (pair<int, int> a, pair<int, int> b) const {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    }
};
void solve() {
    int ret = 0, solution[MAXN] = {};
    solution[0] = hour * 60;
    
    // brute
    for (int i = 0; i < n; i++) {
        int leave_time = hour * 60 - t[i] * 5;
        if (leave_time <= 0)
            continue;
        int tret = 0, tsol[MAXN] = {};
        priority_queue< pair<int, int>, vector< pair<int, int> >, cmp > pool;
        for (int j = 0; j <= i; j++) {
            if (f[j] != 0)
                pool.push(make_pair(f[j], j));
        }
        while (!pool.empty() && leave_time >= 5) {
            pair<int, int> u = pool.top();
            pool.pop();
            tret += u.first, tsol[u.second] += 5;
            leave_time -= 5;
            if (u.first - d[u.second] > 0)
                pool.push(make_pair(u.first - d[u.second], u.second));
        }
        if (leave_time > 0)
            tsol[0] += leave_time;
        if (tret > ret) {
            ret = tret;
            for (int j = 0; j < n; j++) {
                solution[j] = tsol[j];
            }
        }
    }
    
    for (int i = 0; i < n; i++)
        printf("%s%d", i ? ", " : "", solution[i]);
    puts("");
    printf("Number of fish expected: %d\n", ret);
}
int main() {
    int cases = 0;
    while (scanf("%d", &n) == 1 && n) {
        scanf("%d", &hour);
        for (int i = 0; i < n; i++)
            scanf("%d", &f[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &d[i]);
        for (int i = 1; i < n; i++)
            scanf("%d", &t[i]);
        
        for (int i = 1; i < n; i++)
            t[i] += t[i-1];
        
        if (cases++)    puts("");
        solve();
    }
    return 0;
}
/*
 2
 1
 10 1
 2 5
 2
 4
 4
 10 15 20 17
 0 3 4 3
 1 2 3
 4
 4
 10 15 50 30
 0 3 4 3
 1 2 3
 0
 */
