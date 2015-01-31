#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXN 32767
#define INF 0x3f3f3f3f
int N, R[MAXN];
int A[MAXN][3];
void update(int x, int limit, int &mn) {
    if (x >= limit) mn = min(mn, x);
}
int test(int mid) {
    int limit = mid, x;
    R[N] = N;
    for (int i = N - 1; i >= 0; i--) {
        x = R[i];
        int mn = INF;
        if (i+1 < N && x > R[i+1])
            limit ++;
        update(A[x][0], limit, mn);
        update(A[x][1], limit, mn);
        update(A[x][2], limit, mn);
        update(A[x][0]+A[x][1], limit, mn);
        update(A[x][0]+A[x][2], limit, mn);
        update(A[x][1]+A[x][2], limit, mn);
        update(A[x][0]+A[x][1]+A[x][2], limit, mn);
        if (mn == INF)
            return 0;
        limit = mn;
    }
    return 1;
}

int ReadFloat() {
    static char s[16];
    scanf("%s", s);
    int val = 0, p = 2;
    for (int i = 0; s[i]; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            val = val * 10 + s[i] - '0';
        } else {
            for (i++; s[i]; i++) {
                val = val * 10 + s[i] - '0';
                p--;
            }
            break;
        }
    }
    while (p--)
        val = val * 10;
    return val;
}
int main() {
    int cases = 0;
    while (scanf("%d", &N) == 1 && N) {
        for (int i = 0; i < N; i++) {
            A[i][0] = ReadFloat();
            A[i][1] = ReadFloat();
            A[i][2] = ReadFloat();
        }
        for (int i = 0; i < N; i++) {
            scanf("%d", &R[i]);
            R[i]--;
        }
        int ret = -1, x = R[N-1];
        if (test(A[x][0]))            ret = max(ret, A[x][0]);
        if (test(A[x][1]))            ret = max(ret, A[x][1]);
        if (test(A[x][2]))            ret = max(ret, A[x][2]);
        if (test(A[x][0]+A[x][1]))    ret = max(ret, A[x][0]+A[x][1]);
        if (test(A[x][0]+A[x][2]))            ret = max(ret, A[x][0]+A[x][2]);
        if (test(A[x][1]+A[x][2]))            ret = max(ret, A[x][1]+A[x][2]);
        if (test(A[x][0]+A[x][1]+A[x][2]))    ret = max(ret, A[x][0]+A[x][1]+A[x][2]);
        printf("Case %d: ", ++cases);
        if (ret < 0)
            puts("No solution");
        else
            printf("%d.%02d\n", ret/100, ret%100);
    }
    return 0;
}
/*

*/