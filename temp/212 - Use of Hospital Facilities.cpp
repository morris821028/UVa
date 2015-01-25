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
using namespace std;

struct Patient {
    string name;
    int pa, pb;
    int aBegin, aEnd, bBegin, bEnd, aid, bid;
    Patient(int a = 0, int b = 0, string s = ""):
    pa(a), pb(b), name(s) {}
} D[2048];
int main() {
    int N, M, K, ST_T, PA_T, PB_T, PAB_T;
    char s[1024];
    int x, y;
    while (scanf("%d %d %d %d %d %d %d", &N, &M, &ST_T, &PAB_T, &PA_T, &PB_T, &K) == 7) {
        for (int i = 0; i < K; i++) {
            scanf("%s %d %d", s, &x, &y);
            D[i] = Patient(x, y, s);
        }
        int aWorking[32] = {}, bWorking[32] = {};
        int aFinTime[32] = {}, bFinTime[32] = {};
        int aPid[32], bPid[32], aUsed[32] = {}, bUsed[32] = {};
        int preTime = -1, pid = 0;
        
        memset(aPid, -1, sizeof(aPid));
        memset(bPid, -1, sizeof(bPid));
        
        priority_queue<int, vector<int>, greater<int> > timeline;
        timeline.push(ST_T * 60);
        while (!timeline.empty()) {
            int now = timeline.top();
            timeline.pop();
            if (now == preTime) continue;
            preTime = now;
            vector<int> A2B;
            for (int i = 0; i < N; i++) {
                if (aWorking[i] && aFinTime[i] <= now) {
                    aWorking[i] = 0;
                    if (aPid[i] >= 0) {
                        A2B.push_back(aPid[i]);
                        aWorking[i] = 1;
                        aFinTime[i] = now + PA_T;
                        aPid[i] = -1;
                        timeline.push(now + PA_T);
                    }
                }
            }
            for (int i = 0; i < M; i++) {
                if (bWorking[i] && bFinTime[i] <= now) {
                    bWorking[i] = 0;
                    if (bPid[i] >= 0) {
                        bWorking[i] = 1;
                        bFinTime[i] = now + PB_T;
                        bPid[i] = -1;
                        timeline.push(now + PB_T);
                    }
                }
            }
            for (int i = 0; i < A2B.size(); i++) {
                int x = A2B[i];
                for (int j = 0; j < M; j++) {
                    if (bWorking[j] == 0) {
                        bWorking[j] = 1;
                        bFinTime[j] = PAB_T + now + D[x].pb;
                        bPid[j] = x, bUsed[j] += D[x].pb;
                        D[x].bid = j;
                        D[x].bBegin = now + PAB_T, D[x].bEnd = bFinTime[j];
                        timeline.push(bFinTime[j]);
                        break;
                    }
                }
            }
            for ( ; pid < K; pid++) {
                int ok = 0;
                for (int i = 0; i < N; i++) {
                    if (aWorking[i] == 0) {
                        aWorking[i] = 1;
                        aFinTime[i] = now + D[pid].pa;
                        aPid[i] = pid, aUsed[i] += D[pid].pa;
                        D[pid].aid = i;
                        D[pid].aBegin = now, D[pid].aEnd = aFinTime[i];
                        timeline.push(aFinTime[i]);
                        ok = 1;
                        break;
                    }
                }
                if (!ok)
                    break;
            }
        }
        
        int ST = 0x3f3f3f3f, ED = 0;
        puts(" Patient          Operating Room          Recovery Room");
        puts(" #  Name     Room#  Begin   End      Bed#  Begin    End");
        puts(" ------------------------------------------------------");
        for (int i = 0; i < K; i++) {
            printf("%2d  %-9s %2d  %3d:%02d  %3d:%02d    %3d  %3d:%02d  %3d:%02d\n",
                   i+1, D[i].name.c_str(), D[i].aid+1,
                   D[i].aBegin/60, D[i].aBegin%60, D[i].aEnd/60, D[i].aEnd%60, D[i].bid+1,
                   D[i].bBegin/60, D[i].bBegin%60, D[i].bEnd/60, D[i].bEnd%60);
            ST = min(ST, D[i].aBegin);
            ED = max(ED, D[i].bEnd);
        }
        puts("");
        puts("Facility Utilization");
        puts("Type  # Minutes  % Used");
        puts("-------------------------");
        for (int i = 0; i < N; i++) {
            printf("%-4s %2d %7d %7.2lf\n", "Room", i+1, aUsed[i], (double) aUsed[i]*100/(ED - ST));
        }
        for (int i = 0; i < M; i++) {
            printf("%-4s %2d %7d %7.2lf\n", "Bed", i+1, bUsed[i], (double) bUsed[i]*100/(ED - ST));
        }
        puts("");
    }
    return 0;
}
/*
 
 */