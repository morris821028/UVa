#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;

#define MAXM 262144
#define MAXN 131072
int IN1[MAXM], IN2[MAXM];
int VAL[MAXM], n, m;
int calc(int div) {
    for (int i = 1; i <= m; i++) {
        int a = IN1[i], b = IN2[i], va, vb;
        va = a < 0 ? -a > div : VAL[a];
        vb = b < 0 ? -b > div : VAL[b];
        VAL[i] = !(va&vb);
    }
    return VAL[m];
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= m; i++)
            scanf("%d %d", &IN1[i], &IN2[i]);
        int v0 = calc(0), v1 = calc(n);
        if (v0 == v1) {
            for (int i = 0; i < n; i++)
                putchar('0');
            puts("");
        } else {
            int l = 1, r = n + 1, mid, ret = 1;
            while (l <= r) {
                mid = (l + r)/2;
                if (calc(mid) == v1)
                    r = mid-1, ret = mid;
                else
                    l = mid+1;
            }
//            printf("%d %d\n", v0, v1);
//            printf("%d %d\n", calc(ret-1), calc(ret));
            for (int i = 1; i < ret; i++)
                putchar('0');
            putchar('x');
            for (int i = ret + 1; i <= n; i++)
                putchar('1');
            puts("");
        }
    }
    return 0;
}
/*
 1
 3 6
 -1 -3 -1 -2 1 2 1 2 4 3 5 5
*/