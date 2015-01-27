// WTFFFFFFF, always TLE.
#include <stdio.h>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <string.h>
#include <sstream>
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
long long llgcd(long long x, long long y) {
    long long t;
    if (x < 0)  x = -x;
    if (y < 0)  y = -y;
    while (x%y)
        t = x, x = y, y = t%y;
    return y;
}
int H(long long a, long long b, long long i) {
    return (int) (ceil((double) a * i / b));
}
long long from(long long a, long long b, long long i) { // (a/b) >= (1/i)
    for (; ; i++) {
        if (a * i >= b) {
            return i;
        }
    }
    return 1;
}
int ida_depth, solved;
int ban[1024];
long long path[128], ret[128];
void update(int dep) {
    int ok = 0;
    for (int i = dep - 1; i >= 0; i--) {
        if (path[i] != ret[i]) {
            ok = ret[i] == -1 || path[i] < ret[i];
            break;
        }
    }
    if (ok) {
        for (int i = 0; i < dep; i++) {
            ret[i] = path[i];
        }
    }
}
int IDA(long long a, long long b, long long i, int dep, int hv) {
    if (dep == ida_depth) {
        if (a != 0) return dep + hv;
        solved = 1;
        update(dep);
        return dep;
    }
    if (dep + hv > ida_depth)
        return dep + hv;

    long long x, y, g;
    int back = 0x3f3f3f3f, tmp, shv;
//    if (dep == 0)
//        printf("it %lld\n", max(i, from(a, b, i)));
    for (i = max(i, from(a, b, i)); b * (ida_depth - dep + 1) >= i * a; i++) {
//        if (dep == 0)
//            printf("%lld\n", i);
        if (i < 1024 && ban[i])
            continue;
        if (solved && ret[ida_depth - 1] < i)
            break;
        x = a * i - b, y = b * i;
        g = llgcd(x, y);
        x /= g, y /= g;
        path[dep] = i, shv = H(x, y, i+1);
//        if (dep == 0)
//            printf("%lld %lld %lld\n", i, a, b);
//        printf("\n%lld %lld %lld %lld i = %lld\n", a, b, x, y, i);
        tmp = IDA(x, y, i+1, dep+1, shv);
        back = min(back, tmp);
    }
    return back;
}

int main() {
    int testcase, cases = 0, n, x;
    scanf("%d", &testcase);
    while (testcase--) {
        int a, b;
        scanf("%d %d %d", &a, &b, &n);
        memset(ban, 0, sizeof(ban));
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            ban[x] = 1;
        }
        printf("Case %d: %d/%d=", ++cases, a, b);
        solved = 0;
        memset(ret, -1, sizeof(ret));
        for (ida_depth = 1; ida_depth < 20 && solved == 0; ) {
            ida_depth = IDA(a, b, 1, 0, 0);
        }
        if (solved)
        for (int i = 0; i < ida_depth; i++)
            printf("1/%lld%c", ret[i], i == ida_depth - 1 ? '\n' : '+');
    }
    return 0;
}
/*
 5
 2 3 0
 19 45 0
 2 3 1 2
 5 121 0
 5 121 1 33
 */