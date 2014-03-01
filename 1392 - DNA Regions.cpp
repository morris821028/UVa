#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
double get_avg(int l, int r, int sum[]) {
    return (double)(sum[r]-sum[l])/(r-l);
}
int q[150005], sum[150005];
double globalCut;
int nextL;
double mxAvgProblem(int n, int L, int sum[]) {
    double ans = (double)sum[n]/n;
    int front, rear, i, j;
    front = 0, rear = -1;
    for(i = L; i <= n; i++) {
        int tmp = i-L;
        while(front < rear && get_avg(q[rear], tmp, sum) <= get_avg(q[rear-1], q[rear], sum))
            rear--;
        q[++rear] = tmp;
        while(front < rear && get_avg(q[front], i, sum) <= get_avg(q[front+1], i, sum))
            front++;
        double tans = get_avg(q[front], i, sum);
        if(tans > ans)
            ans = tans;
        if(ans >= globalCut) {
            nextL = i-q[front];
            return ans;
        }
    }
    return ans;
}
int main() {
    int n, p;
    int i, j;
    char A[150005], B[150005];
    while(scanf("%d %d", &n, &p) == 2) {
        if(n == 0)  break;
        scanf("%s %s", A+1, B+1);
        double s = (100-p)/100.0, f;
        for(i = 1; i <= n; i++)
            sum[i] = sum[i-1] + (A[i] == B[i]);
        int l = 0, r = n, m;
        int ret = 0;
        globalCut = s;
        while(l <= r) {
            m = (l+r)/2;
            f = mxAvgProblem(n, m, sum);
            if(f >= s)
                l = nextL+1, ret = max(ret, nextL);
            else
                r = m-1;
        }
        if(ret)
            printf("%d\n", ret);
        else
            puts("No solution.");
    }
    return 0;
}
