#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <math.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define eps 1e-6
#define MAXN 131072
#define INF 0x3f3f3f3f
int A[MAXN], L[MAXN], R[MAXN];
long long S[MAXN];
long long calc(int l, int r) {
    long long ret = S[r];
    ret -= l ? S[l-1] : 0;
    return ret;
}
int main() {
    int N, cases = 0;
    while (scanf("%d", &N) == 1) {
        for (int i = 0; i < N; i++)
            scanf("%d", &A[i]);
        long long sum = 0;
        for (int i = 0; i < N; i++)
            sum += A[i], S[i] = sum;
        stack<int> stk;
        for (int i = 0; i < N; i++) {
            while (!stk.empty() && A[i] <= A[stk.top()])
                stk.pop();
            L[i] = stk.empty() ? 0 : stk.top()+1;
            stk.push(i);
        }
        while (!stk.empty())    stk.pop();
        for (int i = N-1; i >= 0; i--) {
            while (!stk.empty() && A[i] <= A[stk.top()])
                stk.pop();
            R[i] = stk.empty() ? N-1 : stk.top()-1;
            stk.push(i);
        }
        
        int l = -1, r = -1;
        long long ret = -1;
        for (int i = 0; i < N; i++) {
            if (A[i] > ret)
                ret = A[i], l = i, r = i;
        }
        for (int i = 0; i < N; i++) {
            long long val = calc(L[i], R[i]) * A[i];
            if (val > ret || (val == ret && R[i] - L[i] < r - l)) {
                ret = calc(L[i], R[i]) * A[i];
                l = L[i], r = R[i];
            }
//            printf("[%d %d] %lld\n", L[i], R[i], calc(L[i], R[i]) * A[i]);
        }
        if (cases++)
            puts("");
        printf("%lld\n%d %d\n", ret, l+1, r+1);
    }
    return 0;
}
/*
 
 */