#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

int A[32767], B[32767];
int main() {
    int testcase, n, m, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        map<int, int> R;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        for (int i = 0; i < m; i++) {
            scanf("%d", &B[i]);
            R[B[i]]++;
        }
        int diff = (int)R.size();
        long long ret = 0;
        for (int i = 0; i < n; i++) {
            int &x = R[A[i]];
            if (x == 1)
                diff--;
            else if(x == 0)
                diff++;
            x--;
            if (i - m >= 0) {
                int &y = R[A[i-m]];
                if (y == 0)
                    diff++;
                else if(y == -1)
                    diff--;
                y++;
            }
            if (diff == 0) {
                long long pos = i - m + 2;
                ret += pos * pos;
//                printf("pos %d\n", pos);
            }
        }
        printf("%lld\n", ret);
    }
    return 0;
}

/*
 2
 3 2
 10 11 10
 10 11
 4 3
 10 11 11 10
 10 11 11
 */