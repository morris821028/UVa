#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
#include <map>
using namespace std;

map< set<int>, int > R;
map<int, set<int> > mR;
int rename(set<int> s) {
    int &ret = R[s];
    if (ret == 0)
        ret = (int)R.size(), mR[ret] = s;
    return ret;
}
int main() {
    int testcase, n;
    int a, b;
    char cmd[1024];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        stack<int> stk;
        for (int i = 0; i < n; i++) {
            scanf("%s", cmd);
            if (!strcmp(cmd, "PUSH")) {
                stk.push(rename(set<int>()));
            } else if(!strcmp(cmd, "DUP")) {
                stk.push(stk.top());
            } else if(!strcmp(cmd, "UNION")) {
                a = stk.top(), stk.pop();
                b = stk.top(), stk.pop();
                set<int> &A = mR[a], &B = mR[b], C;
                set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
                stk.push(rename(C));
            } else if(!strcmp(cmd, "INTERSECT")) {
                a = stk.top(), stk.pop();
                b = stk.top(), stk.pop();
                set<int> &A = mR[a], &B = mR[b], C;
                set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
                stk.push(rename(C));
            } else if(!strcmp(cmd, "ADD")) {
                a = stk.top(), stk.pop();
                b = stk.top(), stk.pop();
                set<int> B = mR[b];
                B.insert(a);
                stk.push(rename(B));
            }
            printf("%d\n", (int)mR[stk.top()].size());
        }
        puts("***");
    }
    return 0;
}
/*
 2
 9
 PUSH
 DUP
 ADD
 PUSH
 ADD
 DUP
 ADD
 DUP
 UNION
 5
 PUSH
 PUSH
 ADD
 PUSH
 INTERSECT
*/