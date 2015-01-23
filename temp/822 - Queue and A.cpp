#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <ctype.h>
#include <functional>
using namespace std;

struct Staff {
    int pid;
    vector<int> proc_list;
    bool operator<(const Staff &x) const {
        return pid < x.pid;
    }
};
struct Job {
    int tid, st, proc;
    Job(int t = 0, int s = 0, int e = 0):
    tid(t), st(s), proc(e) {}
};
struct cmpJob {
    bool operator() (const Job &a, const Job &b) const {
        return a.st > b.st;
    }
};
bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}
int main() {
    int N, M, cases = 0;
    while (scanf("%d", &N) == 1 && N) {
        map<int, priority_queue<Job, vector<Job>, cmpJob> > scheduler;
        priority_queue<int, vector<int>, greater<int> > timeline;
        for (int i = 0; i < N; i++) {
            int tid, num, t0, t, dt;
            scanf("%d %d %d %d %d", &tid, &num, &t0, &t, &dt);
            for (int j = 0; j < num; j++) {
                scheduler[tid].push(Job(tid, t0, t));
                timeline.push(t0);
                t0 += dt;
            }
        }
        scanf("%d", &M);
        Staff staffs[10];

        for (int i = 0; i < M; i++) {
            int pid, num, tid;
            scanf("%d %d", &pid, &num);
            staffs[i].pid = pid;
            for (int j = 0; j < num; j++) {
                scanf("%d", &tid);
                staffs[i].proc_list.push_back(tid);
            }
        }
        sort(staffs, staffs+M); // sort by pid
        int working[10] = {}, preReq[10] = {}, finReq[10] = {};
        int totTime = -2, now;
        timeline.push(-1);
        while (!timeline.empty()) {
            now = timeline.top();
            timeline.pop();
            if (now == totTime)
                continue;
            totTime = now;
            for (int i = 0; i < M; i++) {
                if (working[i] && finReq[i] <= now)
                    working[i] = 0;
            }
            vector< pair<int, int> > D;
            for (int i = 0; i < M; i++) {
                if (working[i] == 0) {
                    D.push_back(make_pair(preReq[i], i));
                }
            }
            sort(D.begin(), D.end(), cmp);
            for (int i = 0; i < D.size(); i++) {
                Staff &u = staffs[D[i].second];
                for (int j = 0; j < u.proc_list.size(); j++) {
                    int tid = u.proc_list[j];
                    if (!scheduler[tid].empty()) {
                        Job tmp = scheduler[tid].top();
                        if (tmp.st <= now) {
                            scheduler[tid].pop();
                            preReq[D[i].second] = now;
                            finReq[D[i].second] = now + tmp.proc;
                            working[D[i].second] = 1;
                            timeline.push(finReq[D[i].second]);
                            break;
                        }
                    }
                }
            }
        }
        printf("Scenario %d: All requests are serviced within %d minutes.\n", ++cases, totTime);
    }
    return 0;
}
/*
 3
 128 20 0 5 10
 134 25 5 6 7
 153 30 10 4 5
 4
 10 2 128 134
 11 1 134
 12 2 128 153
 13 1 153
 0
 */