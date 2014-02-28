#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
int map[31][31], mt[31];
struct state {
    int bit, before, next, f, g;
}; // f = g + h
struct cmp {
    bool operator() (state i, state j) {
        return i.f < j.f;
    }
};
int h(int state, int next) {
    static int used, i, j, flag;
    queue<int> Q;
    Q.push(next);
    flag = 0, j = 0;
    while(!Q.empty()) {
        next = Q.front();
        Q.pop();
        for(i = 0; i < mt[next]; i++) {
            if(!(state&(1<<map[next][i]))) {
                state |= 1<<map[next][i];
                Q.push(map[next][i]);
            }
            if(!map[next][i])
                flag = 1;
        }
        j++;
    }
    if(flag)
        return j;
    else
        return -1;
}
void solve(int n) {
    priority_queue<state, vector<state>, cmp> Q;
    int ans = 0, hv, i;
    state s, t;
    s.bit = 1<<0, s.next = 1, s.f = n-1, s.g = 0, s.before = -1;
    Q.push(s);
    while(!Q.empty()) {
        s = Q.top();
        Q.pop();
        if(s.f <= ans)  break;
        //printf("%d %d %d %d %d\n", s.f, s.g, s.bit, s.next, s.before);
        for(i = 0; i < mt[s.next]; i++) {
            if(!(s.bit&(1<<map[s.next][i]))) {
                hv = h(s.bit|(1<<map[s.next][i]), map[s.next][i]);
                if(hv < 0)  continue;
                t.bit = s.bit|(1<<map[s.next][i]);
                t.next = map[s.next][i];
                t.g = s.g+1;
                t.f = t.g+hv;
                t.before = s.next;
                Q.push(t);
            }
            if(map[s.next][i] == 0 && s.before != 0) {
                if(s.g > ans)
                    ans = s.g;
            }
        }
    }
    while(!Q.empty())
        Q.pop();
    printf("%d\n", ans);
}
int main() {
    int N, R, i, j;
    int test = 0;
    while(scanf("%d %d", &N, &R) == 2) {
        memset(mt, 0, sizeof(mt));
        while(R--) {
            scanf("%d %d", &i, &j);
            map[i][mt[i]++] = j;
            map[j][mt[j]++] = i;
        }
        solve(N);
        test++;
        if(test > 10)
            break;
    }
    return 0;
}
